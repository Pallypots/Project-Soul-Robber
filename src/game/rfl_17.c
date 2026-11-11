/* Area rfl, group 17: turning and motion helpers (0x00172EE0..0x00173097). Names inferred. */
#include "rfl.h"

/* 0x00172EE0: turn the actor toward pos by at most maxStep; returns 1 when
   the remaining angle was within maxStep.
   regargs: o=ESI pos=EAX (maxStep on the stack) */
int rfl_TurnTowardStep(RflActor *o, const float *pos, float maxStep)
{
    float a = sub_00113200(o, pos);
    int done = 0;
    if (maxStep >= sub_001A3F30(a))
        done = 1;
    if (a > maxStep)
        a = maxStep;
    if (0.0f - maxStep > a)
        a = 0.0f - maxStep;
    o->yaw54 = a + o->yaw54;
    return done;
}

/* 0x00173030: shorten the part's motion vector so one step does not pass
   pos; returns 1 when it was scaled down.
   regargs: o=ECX pos=EAX */
int rfl_ClampMotionTo(RflActor *o, const float *pos)
{
    float d = r4_DistanceXZ(o->pos60, pos);
    float len = sub_00082D70((const float *)(o->p34 + 0x70));
    float *v;
    if (len > d) {
        v = (float *)(o->p34 + 0x70);
        sub_001ADB60(v, v, d / len);
        return 1;
    }
    return 0;
}
