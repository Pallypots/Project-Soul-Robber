/* Area r4i: effect shot update (0x00190D50). Names inferred. */
#include "r4i.h"

/* 0x00190D50: per-frame update of the kind 0x18/0x19 shot: move by the
   velocity, add the step length to the distance travelled, set the glow
   size from the height (3.3 below -100, else 1.5 - 0.018 * y), and unless
   0x00190B40 handled a hit, test a sphere (radius 3 or 5) at the position
   against the collision mask 1. With no hit, no wall/floor contact and
   at most 450 units travelled, spin the node; otherwise kill it.
   Stack args (o a); calls 0x00190B40 with EAX=o and 0x00190A00 with EDI=o.
   The original leaves the mask, radius and spin rate uninitialised for
   other kinds (only 0x18 and 0x19 use this callback); here the mask is 1. */
void r4i_FxShotUpdate(R4cNode *o, R4cActor *a)
{
    R4cFxB *w = (R4cFxB *)a->work;
    float *vel = w->v14;
    float *pos = o->pos;
    float *glow;
    float *spin;
    float hit[4];
    R4iSphere s;
    int mask;
    int kind;

    r4c_VecAdd(pos, pos, vel);
    w->f24 = r4c_VecLen(vel) + w->f24;
    kind = o->kind;
    mask = 1;
    if (kind == 0x19) {
        s.r = 3.0f;
        spin = r4i_spin32C658;
    } else if (kind == 0x18) {
        s.r = 5.0f;
        spin = r4i_spin32C668;
    }
    glow = &w->f08;
    if (glow) {
        if (-100.0f > o->pos[1]) {
            *glow = 3.3f;
        } else {
            *glow = (o->pos[1] * -0.01f) * 1.8f + 1.5f;
        }
    }
    if (r4c_FxCollide(o))
        return;
    sub_000F5D40(s.c, pos);
    if (sub_000F61D0(o, &s, mask, hit) == -1 && !(o->flags128 & 0xA) && !(w->f24 > 450.0f)) {
        r4c_Spin(o, spin);
        return;
    }
    r4c_FxKill(o);
}

/* 0x00190BC0: aim the lobbed shot: pick the target point (0x00101340)
   with a random +-10 unit spread in X and Z and lowered by 12 or 0.5
   (by 0x00101360), clear the distance travelled, and set the velocity
   towards it. The step length is the distance to Jack divided by the
   speed (36 or 34 per 1/60 s), clamped to 110..320 per second.
   Stack args (o a). */
void r4i_FxLobInit(R4cNode *o, R4cActor *a)
{
    R4iShot *w = (R4iShot *)a->work;
    float rate = 1.0f / r4c_fps;
    float lo = rate * 110.0f;
    float hi = rate * 320.0f;
    float tgt[4];
    float diff[4];
    float *vel;
    float speed;
    float step;

    o->flagsC &= ~0x20u;
    sub_00101340(tgt);
    tgt[0] = (float)(sub_001C7EE1() % 2000 - 1000) * 0.01f + tgt[0];
    tgt[2] = (float)(sub_001C7EE1() % 2000 - 1000) * 0.01f + tgt[2];
    if (sub_00101360())
        tgt[1] = tgt[1] - 12.0f;
    else
        tgt[1] = tgt[1] - 0.5f;
    w->dist24 = 0.0f;
    speed = (sub_00101360() ? 36.0f : 34.0f) / r4c_frameUnits;
    r4c_VecSub(diff, o->pos, r4i_player->pos);
    step = r4c_VecLen(diff) / speed;
    if (lo > step)
        step = lo;
    else if (step > hi)
        step = hi;
    vel = w->vel14;
    r4c_VecSub(vel, tgt, o->pos);
    vel[3] = 0.0f;
    sub_001AD7E0(vel, vel);
    r4c_VecScale(vel, vel, step);
}
