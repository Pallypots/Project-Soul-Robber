/* Area r3: register-argument helpers around 0x00172000..0x0017D000 (r3_9). Names inferred. */
#include "r3.h"

/* 0x00172C90: play animation anim on object a (restart if it is already b's current one) and refresh its effects.
   regargs: b=EAX a=ESI anim=EDI; calls 0x00172B80 with EAX=a EBX=b (flag on the stack). Hangs if the animation did not take. */
void r3_PlayAnim172C90(R3Ctl *b, R3Obj2 *a, int anim)
{
    sub_00172B80(a, b, 0);
    if (!sub_00083120(a->anim30, anim))
        return;
    if (b->anim60 == anim) {
        sub_000832D0(a->anim30, -1);
    } else {
        sub_000832D0(a->anim30, anim);
        b->anim60 = anim;
    }
    sub_0001D7F0(a->p3C, anim, 0);
    if (a->anim30->cur08 != b->anim60)
        for (;;) ;
    b->f64 = 0.0f;
    if (a->kind08 != 15 && a->kind08 != 1)
        sub_0001D4E0((R3Obj *)a);
    sub_00172B80(a, b, 1);
}

/* 0x0017C670: two-phase timer: phase 1 waits, then starts phase 2 (pulse, copy the base colour); phase 2 pulses until it runs out and sets state 8.
   regargs: s=ESI; calls 0x0017C5D0 with EAX=s. */
void r3_Tick17C670(R3Pulse *s)
{
    if (s->mode24 == 1) {
        if (s->t28 < 0.0f) {
            s->w50 = 1;
            s->mode24 = 2;
            s->t28 = 1.5f;
            sub_000F5D40(s->obj00->v90, r3_vec32B6A8);
            return;
        }
    } else if (s->mode24 == 2) {
        r3_Pulse17C5D0(s);
        if (s->t28 < 0.0f) {
            sub_00113040(s->obj00, s->act04, 8);
            return;
        }
    } else {
        return;
    }
    s->t28 -= r3_frameDelta;
}
