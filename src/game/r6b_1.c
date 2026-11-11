/* Area r6b: script process and task handlers around 0x0008D140-0x0008EA10 (r6b_1). Names inferred. */
#include "r6b.h"

/* 0x0008D140: process step that waits on its reference; stack arg p. */
int r6b_ProcWaitRef(R6bProc *p)
{
    int r = sub_00089DD0(p->ref);
    if (r)
        return r;
    if (p->flags & 2) {
        p->state = 1;
        p->timer = 0;
    }
    return 0;
}

/* 0x0008D1C0: run one step of a process and restart it when the step is done; stack arg p. */
void r6b_ProcStep(R6bProc *p)
{
    if (r6b_procStates[p->state].step(p)) {
        p->state = 1;
        p->timer = 0;
    }
}

/* 0x0008D3A0: restart a process, run it until it stops, return 0; stack arg p. */
int r6b_ProcRestartRun(R6bProc *p)
{
    if (p) {
        p->state = 1;
        p->timer = 0;
    }
    sub_0008D220(p);
    return sub_000AD090();
}

/* 0x0008D410: task descriptor getter. */
R6bDesc *r6b_GetDesc2E1130(void) { return &r6b_desc2E1130; }
/* 0x0008D470: task descriptor getter. */
R6bDesc *r6b_GetDesc2E11A0(void) { return &r6b_desc2E11A0; }

/* 0x0008D480: task handler forwarding arg 2 to 0x00089700; returns 0. */
int r6b_TaskFwdSub4C(R6bTask *t, void *a)
{
    a80_ForwardSub4C(a);
    return 0;
}

/* 0x0008D490: task handler forwarding arg 2 to 0x00089720; returns 0. */
int r6b_TaskFwdStr(R6bTask *t, void *a)
{
    a80_ForwardStr(a);
    return 0;
}

/* 0x0008D4E0: task handler releasing the object at +0x1C; returns 0. */
int r6b_TaskRelease1C(R6bTask *t)
{
    sub_0008B3E0(t->p1C);
    return 0;
}

/* 0x0008D610: task descriptor getter. */
R6bDesc *r6b_GetDesc2E1238(void) { return &r6b_desc2E1238; }
/* 0x0008D660: task descriptor getter. */
R6bDesc *r6b_GetDesc2E12B0(void) { return &r6b_desc2E12B0; }

/* 0x0008D750: initialise the "Demo Time Table" header; returns 0. */
int r6b_DemoTableInit(R6bNamed *n)
{
    a6b_StrCopy(n->hdr.name, r6b_strDemoTimeTable);
    n->hdr.kind = 0x65;
    n->i00 = 0;
    n->i24 = 0;
    n->i28 = 0;
    return 0;
}

/* 0x0008D840: task descriptor getter. */
R6bDesc *r6b_GetDesc2E1328(void) { return &r6b_desc2E1328; }
/* 0x0008D850: task descriptor getter. */
R6bDesc *r6b_GetDesc270194(void) { return &r6b_desc270194; }

/* 0x0008D860: clear task flags and +0x23; returns 0. */
int r6b_TaskClearFlags(R6bTask *t)
{
    t->flags18 = 0;
    t->b23 = 0;
    return 0;
}

/* 0x0008D870: set task mode bits to "active"; returns 0. */
int r6b_TaskSetActive(R6bTask *t)
{
    t->flags18 = (t->flags18 & ~0xC) | 2;
    return 0;
}

/* 0x0008D890: clear the task's active bit; returns 0. */
int r6b_TaskClearActive(R6bTask *t)
{
    t->flags18 &= ~2;
    return 0;
}

/* 0x0008D8D0: task descriptor getter. */
R6bDesc *r6b_GetDesc2701B8(void) { return &r6b_desc2701B8; }
/* 0x0008D8E0: task descriptor getter. */
R6bDesc *r6b_GetDesc2701DC(void) { return &r6b_desc2701DC; }

/* 0x0008D8F0: release the task's camera animation; returns 0. */
int r6b_TaskReleaseAnim(R6bTask *t)
{
    a6b_CamAnim_Release(t->u28.p28);
    t->u28.p28 = 0;
    return 0;
}

/* 0x0008DE30: task descriptor getter. */
R6bDesc *r6b_GetDesc27021C(void) { return &r6b_desc27021C; }

/* 0x0008DE40: start a running task; returns 0. */
int r6b_TaskStartRun(R6bTask *t)
{
    t->state = 3;
    t->i120 = 0;
    t->i124 = -1;
    t->f44 = 0.0f;
    t->i3C = 0;
    return 0;
}

/* 0x0008E1B0: value +0x5C of the task's animation object. */
int r6b_TaskAnimValue(R6bTask *t)
{
    return ((R6bAnimRef *)t->u28.p28)->i5C;
}

/* 0x0008E780: task descriptor getter. */
R6bDesc *r6b_GetDesc27026C(void) { return &r6b_desc27026C; }

/* 0x0008E790: reset a task to idle and clear +0x24/+0x28; returns 0. */
int r6b_TaskIdleClear2(R6bTask *t)
{
    t->state = 2;
    t->u24.i24 = 0;
    t->u28.i28 = 0;
    return 0;
}

/* 0x0008E7B0: release the current reference when arg 2 is its +0x1C value; returns 0. */
int r6b_TaskDropIfCurrent(R6bTask *t, void *a)
{
    void *ref = a80_CurRefX0C();
    if (a == a80_Sub4CX1C(ref))
        sub_00089740(ref, 0);
    return 0;
}

/* 0x0008E990: task descriptor getter. */
R6bDesc *r6b_GetDesc2702AC(void) { return &r6b_desc2702AC; }

/* 0x0008E9A0: reset a task to idle; returns 0. */
int r6b_TaskIdle(R6bTask *t)
{
    t->state = 2;
    return 0;
}

/* 0x0008E9B0: activate an idle task; -1 when it is not idle. */
int r6b_TaskActivateIdle(R6bTask *t)
{
    if (t->state != 2)
        return -1;
    t->flags18 = (t->flags18 & ~0xC) | 2;
    return 0;
}

/* 0x0008E9E0: argument parser: store one word into +0x24; returns bytes used (4) or -1. */
int r6b_TaskArgWord(R6bTask *t, const int32_t *args, int n)
{
    if (!args || n <= 0)
        return -1;
    t->u24.i24 = args[0];
    return (uint32_t)n < 4 ? -1 : 4;
}

/* 0x0008EA10: task descriptor getter. */
R6bDesc *r6b_GetDesc2702D0(void) { return &r6b_desc2702D0; }
