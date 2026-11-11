/* Area r4d: thread table helpers around 0x001AD2C0-0x001AD4A0 (r4d_15). Names inferred. */
#include "r4d.h"

/* 0x001AD2C0: close the handles of thread id and free its entry; 0 or -1. Stack arg (id). */
int r4d_ThreadClose(int id)
{
    R4dThread *t;
    sub_001AA1E0(r4d_threadLock40F0D8);
    for (t = r4d_threads40EDD8; t != r4d_threads40EDD8 + 32; t++)
        if (t->id04 == id)
            break;
    if (t == r4d_threads40EDD8 + 32) {
        sub_001AA1F0(r4d_threadLock40F0D8);
        return -1;
    }
    sub_001BC6FD(t->ev14);
    sub_001BC6FD(t->h00);
    t->h00 = (void *)-1;
    t->id04 = -1;
    t->state0C = 0;
    t->ev14 = 0;
    sub_001AA1F0(r4d_threadLock40F0D8);
    return 0;
}

/* 0x001AD3D0: mark thread id running (state 2) and resume it; returns id or -1. Stack arg (id). */
int r4d_ThreadStart(int id)
{
    R4dThread *t;
    sub_001AA1E0(r4d_threadLock40F0D8);
    for (t = r4d_threads40EDD8; t != r4d_threads40EDD8 + 32; t++)
        if (t->id04 == id)
            break;
    if (t == r4d_threads40EDD8 + 32) {
        sub_001AA1F0(r4d_threadLock40F0D8);
        return -1;
    }
    t->state0C = 2;
    sub_001AA1F0(r4d_threadLock40F0D8);
    if (sub_001BD2B6(t->h00) == -1)
        return -1;
    return id;
}

/* 0x001AD440: mark thread id stopping (state 3) and signal its event; returns id. Stack arg (id). */
int r4d_ThreadStop(int id)
{
    R4dThread *t;
    sub_001AA1E0(r4d_threadLock40F0D8);
    for (t = r4d_threads40EDD8; t != r4d_threads40EDD8 + 32; t++)
        if (t->id04 == id)
            break;
    if (t == r4d_threads40EDD8 + 32) {
        sub_001AA1F0(r4d_threadLock40F0D8);
        return id;
    }
    t->state0C = 3;
    if (t->ev14)
        sub_001BCEF9(t->ev14);
    sub_001AA1F0(r4d_threadLock40F0D8);
    return id;
}
