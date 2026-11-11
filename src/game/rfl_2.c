/* Area rfl, group 2: turning and target distances (0x000F7B80, 0x00113520..0x001135F8). Names inferred. */
#include "rfl.h"

#define RFL_PI     3.14159274f
#define RFL_TWO_PI 6.28318548f

/* 0x000F7B80: turn the actor toward pos by at most maxStep radians and
   return the step taken; 0 when there is no actor. */
float rfl_TurnToward(RflActor *a, const float *pos, float maxStep)
{
    float d, step, h, yaw;
    if (!a)
        return 0.0f;
    d = rfl_TurnDelta(a, pos);
    if (d > maxStep) {
        step = maxStep;
    } else {
        step = d;
        if (0.0f - maxStep > step)
            step = 0.0f - maxStep;
    }
    h = 0.0f - a->yaw54 - 1.57079637f - step;
    if (h > RFL_PI)
        h -= RFL_TWO_PI;
    else if (h < -RFL_PI)
        h += RFL_TWO_PI;
    yaw = 0.0f - h - 1.57079637f;
    a->yaw54 = yaw;
    if (yaw < -RFL_PI)
        a->yaw54 = yaw + RFL_TWO_PI;
    return step;
}

/* 0x00113520: distance from obj to a lock-on target (kind 1: the target
   actor's position, kind 2: the point stored at +0x104); 0 otherwise. */
float rfl_TargetDistance(RflActor *obj, RflTarget *t)
{
    switch (t->kindF8) {
    case 1: return r4_Distance(obj->pos60, ((RflActor *)t->ref104)->pos60);
    case 2: return r4_Distance(obj->pos60, (const float *)&t->ref104);
    }
    return 0.0f;
}

/* 0x00113570: as rfl_TargetDistance but on the ground plane (0x001B2770). */
float rfl_TargetDistanceXZ(RflActor *obj, RflTarget *t)
{
    switch (t->kindF8) {
    case 1: return r4_DistanceXZ(obj->pos60, ((RflActor *)t->ref104)->pos60);
    case 2: return r4_DistanceXZ(obj->pos60, (const float *)&t->ref104);
    }
    return 0.0f;
}

/* 0x001135C0: as rfl_TargetDistance but through 0x00113200, which takes
   obj itself. */
float rfl_TargetDistance113200(void *obj, RflTarget *t)
{
    switch (t->kindF8) {
    case 1: return sub_00113200(obj, ((RflActor *)t->ref104)->pos60);
    case 2: return sub_00113200(obj, (const float *)&t->ref104);
    }
    return 0.0f;
}
