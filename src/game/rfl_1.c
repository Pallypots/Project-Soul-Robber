/* Area rfl, group 1: heading helpers (0x000F76B0..0x000F7843). Names inferred. */
#include "rfl.h"

#define RFL_PI     3.14159274f
#define RFL_TWO_PI 6.28318548f

/* 0x000F76B0: an actor's heading, -yaw - pi/2 wrapped into [-pi, pi];
   0 when there is no actor. */
float rfl_ActorHeading(const RflActor *a)
{
    float h;
    if (!a)
        return 0.0f;
    h = 0.0f - a->yaw54 - 1.57079637f;
    if (h > RFL_PI)
        h -= RFL_TWO_PI;
    else if (h < -RFL_PI)
        h += RFL_TWO_PI;
    return h;
}

/* 0x000F7720: signed angle the actor must turn (about Y) to face pos,
   wrapped into [-pi, pi]; 0 when there is no actor. */
float rfl_TurnDelta(RflActor *a, const float *pos)
{
    float dir[4];
    float h, c, s, d;
    if (!a)
        return 0.0f;
    sub_001AD9F0(dir, pos, a->pos60);
    dir[3] = 0.0f;
    dir[1] = 0.0f;
    sub_001AD7E0(dir, dir);
    h = 0.0f - a->yaw54 - 1.57079637f;
    if (h > RFL_PI)
        h -= RFL_TWO_PI;
    else if (h < -RFL_PI)
        h += RFL_TWO_PI;
    c = sub_001A3EE0(h);
    s = sub_001A3ED0(h);
    d = sub_001A3EC0(dir[0], dir[2]) - sub_001A3EC0(c, s);
    if (d > RFL_PI)
        d -= RFL_TWO_PI;
    else if (d < -RFL_PI)
        d += RFL_TWO_PI;
    return d;
}

/* 0x000F7C70: move the actor dist units along its heading on the ground
   plane. */
void rfl_ActorStep(RflActor *a, float dist)
{
    float h;
    if (!a)
        return;
    h = 0.0f - a->yaw54 - 1.57079637f;
    if (h > RFL_PI)
        h -= RFL_TWO_PI;
    else if (h < -RFL_PI)
        h += RFL_TWO_PI;
    a->pos60[0] += sub_001A3EE0(h) * dist;
    a->pos60[2] += sub_001A3ED0(h) * dist;
}
