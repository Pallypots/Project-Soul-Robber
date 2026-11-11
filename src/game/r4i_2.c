/* Area r4i: falling effect movement (0x001902D0). Names inferred. */
#include "r4i.h"

/* 0x001902D0: movement step of the falling effect. Move by the velocity
   with gravity (4.5 per second squared, capped at 140 per second). While
   falling: in mode 1 the pitch is damped towards 0 by 2.2 degrees per
   frame unit and the roll grows to 90 degrees; otherwise the pitch spins
   (direction by bit 0 of the mode), yaw is cleared and the roll grows to
   68 degrees. On landing (moving down, floor bit 8) it bounces with 0.65
   of its speed up to two times, then stops (scale 1, roll 90 degrees).
   Once landed it stops on floor/ceiling contact, grows and fades out at
   2 and 128 per second, and is destroyed when fully faded.
   Stack args (o a). */
void r4i_FxFallMove(R4iNode *o, R4iActor *a)
{
    R4iFall *w = (R4iFall *)a->work;
    float *vel = w->vel0C;
    float lim;
    float k;
    float zero;

    sub_001ADAF0(o->pos60, o->pos60, vel);
    w->vel0C[1] = 4.5f / r4i_fps + w->vel0C[1];
    lim = 140.0f / r4i_fps;
    if (w->vel0C[1] > lim)
        w->vel0C[1] = lim;
    if (w->landed04 == 0) {
        k = r4i_frameUnits * 0.038397245f;
        if (w->bounce08 == 1) {
            zero = 0.0f;
            if (o->rot50[0] > k)
                o->rot50[0] = o->rot50[0] - k;
            else if (zero - k > o->rot50[0])
                o->rot50[0] = o->rot50[0] + k;
            else
                o->rot50[0] = zero;
            if (1.5707964f > o->rot50[2]) {
                o->rot50[2] = r4i_frameUnits * 0.016580628f + o->rot50[2];
                if (o->rot50[2] > 1.5707964f)
                    o->rot50[2] = 1.5707964f;
            }
        } else {
            if (w->bounce08 & 1)
                o->rot50[0] = o->rot50[0] + k;
            else
                o->rot50[0] = o->rot50[0] - k;
            sub_000F5ED0(o->rot50);
            zero = 0.0f;
            o->rot50[1] = zero;
            if (1.18682396f > o->rot50[2]) {
                o->rot50[2] = r4i_frameUnits * 0.017453292f + o->rot50[2];
                if (o->rot50[2] > 1.18682396f)
                    o->rot50[2] = 1.18682396f;
            }
        }
        if (w->vel0C[1] > zero && (o->flags128 & 8)) {
            if (w->bounce08 >= 2) {
                w->landed04 = 1;
                o->rot50[2] = 1.5707964f;
                w->vel0C[1] = zero;
                w->vel0C[2] = zero;
                w->vel0C[3] = zero;
                w->scale20 = 1.0f;
                vel[0] = zero;
                return;
            }
            w->bounce08++;
            w->vel0C[1] = w->vel0C[1] * -0.65f;
        }
        return;
    }
    if (o->flags128 & 0x18) {
        vel[0] = 0.0f;
        w->vel0C[1] = 0.0f;
        w->vel0C[2] = 0.0f;
        w->vel0C[3] = 0.0f;
    }
    w->scale20 = 2.0f / (60.0f / r4i_frameUnits) + w->scale20;
    o->alpha9C = o->alpha9C - 128.0f / (60.0f / r4i_frameUnits);
    r4i_SetScale(o, w->scale20);
    if (0.0f > o->alpha9C) {
        o->alpha9C = 0.0f;
        r4i_ObjDestroy(o);
    }
}

/* 0x00190070: per-frame update of the homing effect. Spin the yaw at 450
   per second (wrapped past pi), turn the velocity in the XZ plane towards
   the manager's target node: the signed angle between the current
   direction and the target is limited to +-37 per second, or, while the
   manager's steer flag is set, replaced by its turn rate (the flag drops
   once the target is on the other side). Then move. Unless 0x0018F950
   reports a hit or the manager is in state 0x21..0x23, stop the sound
   handle and remove the effect.
   Stack args (o a); calls 0x0018F950 with EDI=work and 0x0018F8D0 with
   EAX=o. */
void r4i_FxHomeUpdate(R4iNode *o, R4iActor *a)
{
    R4iMgr *mgr = r4i_GetMgr();
    R4iHome *w = (R4iHome *)a->work;
    float *tgt;
    float m[16];
    float dir[4];
    float to[4];
    float ang;
    float d;
    float lim;
    int st;

    o->rot50[1] = 450.0f / r4i_fps + o->rot50[1];
    if (o->rot50[1] > 3.1415927f)
        o->rot50[1] = o->rot50[1] - 6.2831855f;
    tgt = mgr->node8C->pos60;
    sub_000F5D40(dir, w->vel0C);
    dir[1] = 0.0f;
    dir[3] = 0.0f;
    sub_001AD7E0(dir, dir);
    r4c_VecSub(to, tgt, o->pos60);
    to[1] = 0.0f;
    to[3] = 0.0f;
    sub_001AD7E0(to, to);
    ang = sub_001A3EC0(to[0], to[2]);
    d = ang - sub_001A3EC0(dir[0], dir[2]);
    sub_000F5ED0(&d);
    if (mgr->steer1CA != 0) {
        if (mgr->turn1E4 > 0.0f ? !(d >= 0.0f) : !(0.0f >= d))
            mgr->steer1CA = 0;
        else
            d = mgr->turn1E4;
    } else {
        lim = 37.0f / r4i_fps;
        if (d > lim)
            d = lim;
        else if (0.0f - lim > d)
            d = 0.0f - lim;
    }
    sub_001AD940(m);
    sub_001AD8E0(m, m, d);
    sub_001AD9B0(w->vel0C, m, w->vel0C);
    sub_001ADAF0(o->pos60, o->pos60, w->vel0C);
    if (r4i_HomeHit(w))
        return;
    st = mgr->state6C;
    if (st == 0x21 || st == 0x22 || st == 0x23)
        return;
    if (mgr->h134 != -1) {
        sub_00048250(mgr->h134);
        mgr->h134 = -1;
    }
    r4i_FxDetach(o);
    r4i_ObjDestroy(o);
}
