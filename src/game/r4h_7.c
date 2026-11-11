/* Area r4h: effect family with 0x1C-byte records at 0x00400CA8 (r4h_7). Names inferred. */
#include "r4h.h"

/* 0x00194620: per-frame step of the effect: run the common step
   0x00194410, play motion 5 once when hit hard enough, stop on landing,
   end (state 2) when the life runs out, grow while less than 3 units of
   life are left and blink the model (alpha 1.0 / 0.9999 every life/8
   seconds) in that time. Stack args (o a). */
void r4h_FxBlinkStep(R4hFxNodeC *o, R4hFxActC *a)
{
    R4hRec1C *w = a->work;
    float v[4];
    float alpha;

    r4h_FxThrowMove(o, a);
    if ((o->flags128 & 8) && o->vel80[1] > 0.1f) {
        w->flags |= 0x40;
        sub_00035DD0(o, o->list130, 5, 1);
    }
    if (o->flags128 & 0x18) {
        o->vel80[0] = 0.0f;
        o->vel80[1] = 0.0f;
        o->vel80[2] = 0.0f;
        o->vel80[3] = 1.0f;
    }
    if (0.0f > a->life70)
        sub_00189DA0(o, a, 2);
    if (3.0f > a->life70) {
        v[0] = (3.0f - a->life70) * 0.33333334f + 1.0f;
        v[1] = 1.0f;
        v[2] = 1.0f;
        v[3] = 1.0f;
        sub_000EEA60(o, v);
    }
    w->timer14 = w->timer14 - r4c_frameSeconds;
    if (0.0f > w->timer14 && 3.0f > a->life70) {
        if ((int8_t)w->flags < 0) {
            w->flags &= ~0x80u;
            alpha = 1.0f;
        } else {
            w->flags |= 0x80;
            alpha = 0.9999f;
        }
        sub_000EE6D0(o, alpha);
        w->timer14 = a->life70 * 0.125f;
    }
}

/* 0x00194B50: spawn callback of the effect thrown by src: take a free
   0x1C-byte record, copy the motion list of src, set callbacks, kind,
   sizes and collision, then enter state 0. Returns 0 without src or a
   free record. Stack args (o a src). */
int r4h_FxSpawnC(R4hFxNodeC *o, R4hFxActC *a, R4hFxNodeC *src)
{
    R4hRec1C *rec;

    if (!src || !(rec = r4c_Rec1CAlloc()))
        return 0;
    a->work = rec;
    rec->src18 = src;
    o->list130 = src->list130;
    a->p84 = r4h_d32C780;
    a->p88 = r4h_d32C79C;
    a->fn78 = (void *)sub_001940D0;
    a->fn7C = (void *)sub_001942B0;
    a->fn80 = (void *)sub_00194100;
    o->kindD0 = sub_0001BC40(o);
    o->fB0 = 2.8f;
    o->fB4 = -5.5f;
    o->fA4 = 2.75f;
    o->fE8 = 2.7f;
    o->f10C = 2.5f;
    o->fDC = 0.0f;
    o->iEC = 1;
    o->i118 = 0;
    o->fFC = -5.0f;
    o->iF0 = 2;
    o->iF4 = (int32_t)0x80000000u;
    o->i11C = 1;
    o->i120 = (int32_t)0x80000000u;
    a->f28 = 0.0f;
    a->f2C = -8.0f;
    o->flags10 |= 0x200;
    o->flagsC |= 0x160;
    sub_00189DA0(o, a, 0);
    return 1;
}
