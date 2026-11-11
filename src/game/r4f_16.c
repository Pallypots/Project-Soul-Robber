/* Area r4f: thread table at 0x001AD260-0x001AD7B2 (r4f_16). Names inferred. */
#include "r4f.h"

/* 0x001AD260: clear the 32-entry thread table, enter the main thread as entry 0 (its
   duplicated handle and id), set 0x001BD3B2(13) and create the table lock. No inputs.
   Kernel callees are stdcall. */
void r4f_ThreadTableInit(void)
{
    R4dThread *t = r4d_threads40EDD8;
    int n;
    for (n = 32; n != 0; n--, t++) {
        t->h00 = (void *)-1;
        t->id04 = -1;
        t->state0C = 0;
        t->f10 = 0;
        t->ev14 = 0;
    }
    sub_001BC71B(0, (void *)-2, 0, &r4d_threads40EDD8[0].h00, 0, 0, 0);
    r4d_threads40EDD8[0].id04 = sub_001BD50A();
    sub_001BD3B2(0xD);
    r4d_threadLock40F0D8 = r4d_AllocPersist();
}

/* 0x001AD720: under the table lock create a suspended thread for d (64 KB stack), enter
   it in the first free table slot with its wake event and entry point, and set its
   priority. Returns the thread id. Stack args (d arg). Kernel callees are stdcall. */
int r4f_ThreadCreate(const R4fThreadDesc *d, void *arg)
{
    R4dThread *t;
    int32_t id;
    void *h;
    sub_001AA1E0(r4d_threadLock40F0D8);
    h = sub_001BD49C(0, 0x10000, d->fn04, arg, 4, &id);
    for (t = r4d_threads40EDD8; t != r4d_threads40EDD8 + 32; t++)
        if (t->h00 == (void *)-1)
            break;
    if (t == r4d_threads40EDD8 + 32)
        t = 0;
    t->h00 = h;
    t->id04 = id;
    t->state0C = 1;
    t->ev14 = (int32_t)(intptr_t)sub_001BCE98(0, 0, 0, 0);
    t->f08 = (int32_t)(intptr_t)d->fn04;
    sub_001AD570(id, d->prio14);
    sub_001AA1F0(r4d_threadLock40F0D8);
    return id;
}
