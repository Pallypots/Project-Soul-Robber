/* Area r6f: script process steps and task handlers around 0x0008CFB0-0x0008EBEF (r6f_4). Names inferred. */
#include "r6f.h"

/* 0x0008CFB0: process step: when running, play the sound for the reference's
   id (a fixed one for a set of ids, else id + 50) and go to state 4. */
int r6f_ProcPlayIdSound(R6eProc *p)
{
    if (p->flags & 1) {
        switch (sub_000894D0(p->ref)) {
        case 14: case 18: case 23: case 47: case 48: case 66: case 69:
        case 70: case 72: case 73: case 75: case 80: case 240:
            sub_00048A00(4, 0);
            break;
        default:
            sub_00048A00(sub_000894D0(p->ref) + 0x32, 0);
            break;
        }
        p->state = 4;
        p->timer = 0;
    }
    return 0;
}

/* 0x0008D290: process step: first time, reset the task heaps, set the six
   pool sizes, switch the texture group and open the stage reference; state 3. */
int r6f_ProcOpenStage(R6eProc *p)
{
    if (!(p->flags & 8)) {
        sub_0008BD10();
        sub_0008BCF0(0, 0);
        sub_0008BCF0(1, 1);
        sub_0008BCF0(2, 2);
        sub_0008BCF0(3, 5);
        sub_0008BCF0(4, 1);
        sub_0008BCF0(5, 1);
        p->w14 = sub_001BA0D0();
        sub_001BA0B0(0x6000);
        p->ref = (R6eProcRef *)sub_00089C10(p->i10, r6f_stageTbl2700C0[sub_000529F0()]);
        if (!p->ref)
            return -1;
        ((R6eArg44 *)p->ref)->i44 = sub_0003D090(0);
        p->flags = (p->flags & ~4) | 8;
    }
    p->state = 3;
    p->timer = 0;
    return 0;
}

/* 0x0008D6B0: merge blob b into blob a (task list, then node chain with
   duplicate removal), rebind references and free the removed nodes. */
int r6f_BlobMerge(R6fBlob *a, R6fBlob *b)
{
    R6fTask *removed;
    int r;
    if (!a)
        return -1;
    if (!b)
        return -1;
    removed = 0;
    if (b->tasks) {
        r = sub_0008B7C0(&a->tasks, &b->tasks, 0);
        if (r)
            return r;
        b->flags &= ~1;
    }
    if (b->nodes) {
        r = sub_0008CA80(&a->nodes, &b->nodes, &removed);
        if (r)
            return r;
        sub_0008C4D0(&a->nodes, &removed);
        b->flags &= ~2;
    }
    sub_0008B680(a->tasks, a->nodes, removed);
    sub_0008BF70(removed);
    return 0;
}

/* 0x0008EB10: task handler: for an idle task without an effect list, allocate
   its 0xF8-byte block in its heap and start the effect list for a->i04. */
int r6f_TaskFxStart(R6fTask *t, R6fFxArg *a)
{
    if (!a)
        return -1;
    switch (t->state) {
    case 2:
        if (!(t->f18.b0 & 2)) {
            sub_0007F4A0(2, sub_0008BCD0(t->heap));
            t->p3C = sub_00053BC0(r6f_fxName2702F8, 0xF8);
            sub_000366F0(&t->p28, a->i04);
            sub_00053BE0();
            t->f18.u = (t->f18.u & ~0xC) | 2;
        }
        break;
    case 1:
    case 3:
    case 4:
        return -1;
    }
    return 0;
}

/* 0x0008EBA0: task handler: for an idle task with an effect list, free its
   block and the list. */
int r6f_TaskFxStop(R6eTask *t, void *a)
{
    if (!t || !a)
        return -1;
    switch (t->state) {
    case 2:
        if (t->f18.b & 2) {
            sub_00053880(t->p3C);
            t->p3C = 0;
            sub_000341C0(&t->p28);
            t->f18.b &= ~2;
        }
        break;
    case 1:
    case 3:
    case 4:
        return -1;
    }
    return 0;
}
