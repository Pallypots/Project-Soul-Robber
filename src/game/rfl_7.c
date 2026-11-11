/* Area rfl, group 7: callers of the facing-angle helper (0x00145940..0x00145A37). Names inferred. */
#include "rfl.h"

#define RFL_PI 3.14159274f

/* 0x00145940: 1 when the angle from the actor's facing to (x, z) lies in
   [lo, hi] (a wrapped range when lo > hi). Both bounds must be in
   [-pi, pi]. */
int rfl_FacingInRange(RflActor *a, float x, float z, float lo, float hi)
{
    float ang;
    /* the original re-reads and re-compares each bound on every spin */
    if (lo < -RFL_PI) for (;;) ;
    if (RFL_PI < lo) for (;;) ;
    if (hi < -RFL_PI) for (;;) ;
    if (RFL_PI < hi) for (;;) ;
    ang = rfl_FacingAngleXZ(a, x, z);
    if (ang >= lo && hi >= ang)
        return 1;
    if (lo > hi && (hi >= ang || ang >= lo))
        return 1;
    return 0;
}

/* 0x001459D0: turn the actor's matrix toward (x, z) by at most maxStep;
   returns 1 when it now faces the point. */
int rfl_TurnFacingXZ(RflActor *a, float x, float z, float maxStep)
{
    float ang = rfl_FacingAngleXZ(a, x, z);
    int done;
    if (ang > maxStep) {
        ang = maxStep;
        done = 0;
    } else if (0.0f - maxStep > ang) {
        ang = 0.0f - maxStep;
        done = 0;
    } else {
        done = 1;
    }
    sub_001AD8E0((float *)a->part20, (float *)a->part20, ang);
    return done;
}

/* 0x00155FB0: as rfl_TurnFacingXZ but rotating the actor's matrix about
   the Y axis through 0x00145AA0; returns 1 when it now faces (x, z).
   regargs: a=EDI */
int rfl_TurnFacingXZAxis(RflActor *a, float x, float z, float maxStep)
{
    float up[4];
    float ang;
    int done;
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    ang = rfl_FacingAngleXZ(a, x, z);
    if (ang > maxStep) {
        ang = maxStep;
        done = 0;
    } else if (0.0f - maxStep > ang) {
        ang = 0.0f - maxStep;
        done = 0;
    } else {
        done = 1;
    }
    rfl_MtxRotateAxis((float *)a->part20, (float *)a->part20, up, ang);
    return done;
}
