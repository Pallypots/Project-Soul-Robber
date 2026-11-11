/* Area r1e, group 8: page table, job queues and buckets 0x00057690..0x00059D00. Names inferred. */
#include "r1e.h"

/* 0x00057690: split page t into its chapter (*chap) and the page within
   it (*page); returns -1 (both 0) when t is past the last page. */
int r1e_PageSplit(unsigned t, int *chap, int *page)
{
    int i;
    if (t >= 0x5E) {
        if (chap != 0)
            *chap = 0;
        if (page != 0)
            *page = 0;
        return -1;
    }
    for (i = 12; i >= 0 && r1e_chapters26C2D0[i].start > t; i--)
        ;
    if (chap != 0)
        *chap = i;
    if (page != 0)
        *page = t - r1e_chapters26C2D0[i].start;
    return 0;
}

/* 0x00057E00: release every queued handle in turn (the queue is shifted
   up by one slot each time). */
void r1e_QueueDrain(R1eHQueue *q)
{
    int k, first;
    int32_t *d, *s;
    for (k = q->count; k > 0; k--) {
        first = q->items[0];
        s = q->items;
        for (d = &q->items[1]; d != &q->items[q->count]; d++, s++)
            *d = *s;
        *s = -1;
        q->count--;
        sub_001AD4F0(first);
    }
}

/* 0x00057FC0: find the job with this key and owner in any bucket. */
R1eJob *r1e_JobFind(int key, int owner)
{
    R1eBucket *b;
    R1eRes *r;
    for (b = r1e_buckets3E46E0; b < r1e_buckets3E46E0 + 6; b++) {
        for (r = sub_0003DBC0(b, sub_00057F10, key); r != 0; r = sub_0003DC10(r, sub_00057F10, key))
            if (((R1eJob *)((char *)r->data + 0x10))->owner == owner)
                return (R1eJob *)((char *)r->data + 0x10);
    }
    return 0;
}

/* 0x00058060: the next job with this key after j (same bucket first,
   then the later buckets). */
R1eJob *r1e_JobFindNext(R1eJob *j, int key)
{
    R1eRes *r;
    int i;
    if (j == 0)
        return 0;
    r = sub_0003DC10((char *)j - 0x10, sub_00057F10, key);
    if (r != 0)
        return (R1eJob *)((char *)r->data + 0x10);
    for (i = j->bucket + 1; i < 6; i++) {
        r = sub_0003DBC0(&r1e_buckets3E46E0[i], sub_00057F10, key);
        if (r != 0)
            return (R1eJob *)((char *)r->data + 0x10);
    }
    return 0;
}

/* 0x000584E0: finish a job: run its completion callback, close its
   handle, reset it and leave the job thread. */
void r1e_JobEnd(R1eJob *j)
{
    if (j->done != 0)
        j->done(j->arg);
    if (j->handle != -1)
        sub_001AA310(j->handle);
    j->d00 = 0;
    j->d04 = -1;
    j->handle = -1;
    j->d10 = 0;
    j->d14 = 0;
    j->done = 0;
    j->arg = 0;
    r1b_PktOp(0);
    sub_001AD520();
}

/* 0x00058670: dispatch queued jobs while the scheduler runs. */
void r1e_JobPump(void)
{
    R1eJob *j;
    int t;
    while (r1e_running3E3F7C != 0) {
        sub_001AD6E0();
        j = sub_00057F30();
        if (j == &r1e_mainJob3E3F64) {
            sub_001AD6A0();
        } else if (j != 0) {
            sub_001AA460(j->handle);
        } else {
            t = sub_001AD560();
            r1e_idle3E46A0[r1e_nIdle3E46DC] = t;
            r1e_nIdle3E46DC++;
            sub_001AD4B0(t);
        }
        sub_001AD6E0();
    }
}

/* 0x000589E0: move the pending job into bucket b and reset it.
   regargs: b=EDI */
R1eJob *r1e_JobMove(int b)
{
    R1eRes *r = r1e_pending3E3F58;
    R1eJob *j;
    if (r == 0)
        return 0;
    sub_0003D8C0(r);
    sub_0003D880(&r1e_buckets3E46E0[b], r);
    j = (R1eJob *)((char *)r->data + 0x10);
    if (j != 0) {
        j->d00 = 0;
        j->d04 = -1;
        j->handle = -1;
        j->d10 = 0;
        j->d14 = 0;
        j->done = 0;
        j->arg = 0;
    }
    j->bucket = b;
    return j;
}

/* 0x00058B00: play sound (c, d) through 0x00058A40. */
int r1e_SndPlay(int a, void *b, int c, int d, void *e, int f, int g)
{
    return sub_00058A40(a, b, sub_00053850(c, d, 0, 0), d, e, f, g);
}

/* 0x00059D00: reset the 32 spread slots and give each an even share.
   calls 0x00058ED0 with EAX=i */
void r1e_SpreadInit(void)
{
    int i;
    for (i = 0; i < 32; i++) {
        sub_00058ED0(i);
        r1e_bank3E474C->spread[i].share = r1e_total2DD1C0 / (float)r1e_parts2DD1BE * (float)i;
    }
}
