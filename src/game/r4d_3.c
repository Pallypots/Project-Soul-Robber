/* Area r4d: semaphore slot table around 0x001AA1A0-0x001AA51E (r4d_3). Names inferred. */
#include "r4d.h"

/* 0x001AA1A0: allocate a 0x1C-byte physical block and hand it to kernel thunk slot 2. No inputs. */
void *r4d_AllocPersist(void)
{
    void *p = sub_001BD517(0x1C, -1, 0, 4);
    if (!p)
        return 0;
    r4d_Kernel25F8E8(p);
    return p;
}

static int r4d_semFindFree(void)
{
    int i;
    for (i = 0; i < 64; i++)
        if (!r4d_sems40C058[i].open1C)
            return i;
    return -1;
}

static R4dSem *r4d_semGet(int i)
{
    if (i >= 0 && i < 64)
        return &r4d_sems40C058[i];
    return 0;
}

/* 0x001AA240: create a semaphore in a free slot; returns the slot or -1. Stack arg (d). */
int r4d_SemCreate(const R4dSemDesc *d)
{
    R4dSem *s;
    void *h;
    int i;
    sub_001BD1CC(r4d_semLock40C858, (uint32_t)-1);
    i = r4d_semFindFree();
    if (i < 0) {
        sub_001BCFF2(r4d_semLock40C858);
        return -1;
    }
    s = r4d_semGet(i);
    h = sub_001BCF19(0, d->init, d->max, 0);
    if (!h) {
        sub_001BCFF2(r4d_semLock40C858);
        return -1;
    }
    s->h = h;
    s->open1C = 1;
    s->info.count = d->init;
    s->info.max = d->max;
    s->info.init = d->init;
    s->info.waiters = 0;
    s->info.f10 = d->f10;
    s->info.f14 = d->f14;
    sub_001BCFF2(r4d_semLock40C858);
    return i;
}

/* 0x001AA3E0: signal a slot's semaphore n times (count capped at max); returns the slot or -1.
   Stack args (i n). */
int r4d_SemSignal(int i, int n)
{
    R4dSem *s = r4d_semGet(i);
    int count, max;
    if (!s || !s->h)
        return -1;
    count = s->info.count;
    max = s->info.max;
    if (count >= max)
        return -1;
    if (s->info.waiters > 0) {
        s->info.waiters -= n;
        if (s->info.waiters < n)
            s->info.waiters = 0;
    }
    s->info.count = count + n;
    if (s->info.count > s->info.max)
        s->info.count = max;
    if (!sub_001BCF74(s->h, n, 0)) {
        sub_001BC741();
        return -1;
    }
    return i;
}

/* 0x001AA460: wait on a slot's semaphore (alertable, retrying on timeout and APC), then take
   one count, yielding while it is negative. Returns the slot or -1. Stack arg (i). */
int r4d_SemWait(int i)
{
    R4dSem *s = r4d_semGet(i);
    uint32_t r;
    if (!s || !s->h)
        return -1;
    s->info.waiters++;
    do {
        r = WaitForSingleObjectEx(s->h, (uint32_t)-1, 1);
    } while (r == 0x102 || r == 0xC0);
    s->info.count--;
    while (s->info.count < 0)
        SwitchToThread();
    return i;
}

/* 0x001AA4D0: copy a slot's counters out; returns the slot or -1. Stack args (i out). */
int r4d_SemGetInfo(int i, R4dSemInfo *out)
{
    R4dSem *s = r4d_semGet(i);
    if (!s || !s->h)
        return -1;
    *out = s->info;
    return i;
}
