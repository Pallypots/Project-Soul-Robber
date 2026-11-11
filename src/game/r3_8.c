/* Area r3: register-argument leaf helpers around 0x0017C000..0x0017F000 (r3_8). Names inferred. */
#include "r3.h"

/* 0x0017C5D0: move f4C up toward 3.4 (mode 0) or down toward 0.7 (mode 1), flipping mode at the ends, and apply it to the object.
   regargs: s=EAX. */
void r3_Pulse17C5D0(R3Pulse *s)
{
    float v;

    if (s->w50 == 0) {
        v = 2.7f / (r3_fps42C964 * 0.325f) + s->f4C;
        s->f4C = v;
        if (v > 3.4f) {
            s->w50 = 1;
            s->f4C = 3.4f;
        }
    } else if (s->w50 == 1) {
        v = s->f4C - 2.7f / (r3_fps42C964 * 0.325f);
        s->f4C = v;
        if (v < 0.7f) {
            s->w50 = 0;
            s->f4C = 0.7f;
        }
    }
    sub_000EE760(s->obj00, s->f4C);
}

/* 0x0017E4D0: clear a 0xBC-byte record (handles at +0x20/+0x24 become -1).
   regargs: r=EAX. */
void r3_ClearRec17E4D0(R3Rec17E *r)
{
    int i;

    r->f28 = 0.0f;
    r->i00[0] = 0;
    r->i00[1] = 0;
    r->i00[2] = 0;
    r->i00[3] = 0;
    r->i00[4] = 0;
    r->i20 = -1;
    r->i24 = -1;
    for (i = 0; i < 6; i++) {
        r->i2C[i] = 0;
        r->f44[i] = 0.0f;
        r->v5C[i][0] = 0.0f;
        r->v5C[i][1] = 0.0f;
        r->v5C[i][2] = 0.0f;
        r->v5C[i][3] = 0.0f;
    }
}

/* 0x0017A2B0: leave the current state and enter a new one (variant D; state 1 also sets work +0x20 to 5).
   regargs: obj=EBX act=ESI state=stack. */
void r3_SetStateD(R3Obj *obj, R3Actor *act, int state)
{
    R3WorkD *w = (R3WorkD *)act->work278;

    sub_001134B0(act);
    obj->flags10 &= ~7u;
    act->flags4C &= ~0x100u;
    w->flags00 &= ~8u;
    obj->f58 = 0.0f;
    if (state == 1)
        w->f20 = 5.0f;
    if (act->h6C >= 0) {
        sub_00048250(act->h6C);
        act->h6C = -1;
    }
    if (!sub_00048100(w->h28))
        w->h28 = -1;
    if (w->h24) {
        sub_00033A70(w->h24);
        w->h24 = 0;
    }
    sub_00113040(obj, act, state);
}
