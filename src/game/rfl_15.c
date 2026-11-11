/* Area rfl, group 15: pickup/grab helpers (0x00166F50..0x00168DC5). Names inferred. */
#include "rfl.h"

/* 0x00166F50: 1 (with the distance and vertical angle written to outD and
   outA) when point p is within 50 units of the actor, -50..20 above it and
   within +-70 degrees of its vertical angle.
   regargs: o=EDI p=ESI (outD and outA on the stack) */
int rfl_InGrabRange(RflActor *o, const float *p, float *outD, float *outA)
{
    float d = r4_Distance(o->pos60, p);
    float h, a;
    if (d > 50.0f)
        return 0;
    h = p[1] - o->pos60[1];
    if (-50.0f > h || h > 20.0f)
        return 0;
    a = sub_00113290(o, p);
    if (-1.22173047f > a || a > 1.22173047f)
        return 0;
    *outD = d;
    *outA = a;
    return 1;
}

/* 0x00168CD0: play animation 0 and turn the actor to face away from its
   link's point; clear link flags 0x0C. */
void rfl_PickFaceLink(RflActor *o, RflPick *e)
{
    RflLink *l;
    float t[4];
    sub_00167200(o, e, 0);
    l = e->link74;
    sub_001ADBA0(t, l->pos1C, -1.0f);
    r4c_VecAdd(t, t, o->pos60);
    o->yaw54 = sub_00113200(o, t) + o->yaw54;
    o->flags10 |= 4;
    l->flags0 &= ~0xCu;
}

/* 0x00168D40: carried step: follow the link's point and drain +0x50 by
   2 degrees per frame unit; state 0x0B on body flags 6 or once the player
   is 60 units away. */
void rfl_PickCarried(RflActor *o, RflPick *e)
{
    RflLink *l = e->link74;
    if ((o->flags128 & 6) || r4_DistanceXZ(o->pos60, rfl_playerObj->pos60) >= 60.0f) {
        sub_001671D0(o, e, 0xB);
        return;
    }
    sub_000C56B0(o);
    sub_000F5D40(o->v80, l->pos1C);
    o->f50 -= a50_frameUnits * 0.0349065848f;
}
