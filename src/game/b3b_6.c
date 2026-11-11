/* Area b3b, group 6: helpers 0x00145xxx-0x00146xxx. Names inferred. */
#include "b3b.h"

/* 0x001457C0: animation time in [lo, hi); hangs if the range is inverted. */
int b3b_AnimInRange1457C0(B3bActor *a, float lo, float hi)
{
    float t;
    /* the original re-compares hi and lo on every spin */
    if (hi < lo) for (;;) ;   /* assert-style hang */
    t = a->model30->anim14->timeD8;
    if (t >= lo && hi > t) return 1;
    return 0;
}

/* 0x001460A0: active object of type 2/7 whose work flag 0x100 is set. */
int b3b_IsFlagged1460A0(B3bObj *obj)
{
    B3bEnemy *c;
    if (obj && (obj->flagsC & 1) && obj->type4 == 2 && obj->sub8 == 7) {
        c = (B3bEnemy *)sub_0001D960(obj, 4);
        if (c) return (c->work->flags50 >> 8) & 1;
    }
    return 0;
}

/* 0x00146820: two-step start: wait for the owner's handle, then call 0x000ED780. */
void b3b_Start146820(B3bOwner *o, B3bEnemy *e)
{
    switch (e->counter58) {
    case 0:
        if (!sub_000833E0(o->handle30)) return;
        e->counter58++;
        /* fall through */
    case 1:
        sub_000ED780(o);
        break;
    }
}
