/* Area r4i: following glow effect (0x00195F60). Names inferred. */
#include "r4i.h"

/* 0x00195F60: per-frame step of a glow following a target node. While
   sinking the glow size follows the target height
   (1.7 - 0.9 * (85 + y) / 85); otherwise it grows by 0.34 up to 1.7.
   While following and the target is below -68, move the node in XZ
   towards Jack at 70 units per second, snapping onto him when closer;
   once the target rises above -68 following stops. Stack args (o a). */
void r4i_FxFollow(R4iNode *o, R4iActor *a)
{
    R4iFollow *w = (R4iFollow *)a->work;
    R4iNode *t = w->target;
    float *jack = r4i_jack->pos60;
    float *pos;
    float d[4];
    float spd;
    float ang;

    if (w->sink88 != 0) {
        w->size18 = 1.7f - (85.0f - (0.0f - t->pos60[1])) * 0.011764706f * 0.9f;
    } else {
        w->size18 = w->size18 + 0.34f;
        if (w->size18 > 1.7f)
            w->size18 = 1.7f;
    }
    if (w->follow8A == 0)
        return;
    if (!(-68.0f > t->pos60[1])) {
        w->follow8A = 0;
        return;
    }
    spd = 70.0f / r4i_fps;
    pos = o->pos60;
    r4i_VecSub(d, pos, jack);
    if (!(spd >= r4i_VecLenXZ(d))) {
        ang = -sub_001A3EC0(d[0], d[2]) - 1.5707964f;
        o->pos60[0] = sub_001A3EE0(ang) * spd + o->pos60[0];
        o->pos60[2] = sub_001A3ED0(ang) * spd + o->pos60[2];
        return;
    }
    pos[0] = jack[0];
    o->pos60[2] = jack[2];
}

/* 0x00199090: start of an aimed effect: clear joint 2's +0x38, set the
   actor timer to the aim time, pitch the node to aim at a random point
   (-40 +- 10 high) from its height, add a random +-5 degree yaw, set the
   per-frame motion to (0 0 -y/n x/n) for n = aim time in frames, take
   the camera point, attach effect 0 to the node and place it there.
   Stack args (o a); calls 0x00198DA0 with ESI=point and EDI=o. */
void r4i_FxAimInit(R4iNode *o, R4iActor *a)
{
    R4iAim *w = (R4iAim *)a->work;
    R4iJoint *j = r4i_Joint(o, 2);
    float pt[4];
    float frames;
    float y;
    float x;
    float inv;

    a->f70 = r4i_aimTime;
    frames = r4i_fps * r4i_aimTime;
    x = (float)(sub_001C7EE1() % 10000);
    y = o->pos60[1] * -1.0f;
    x = x * 0.0001f * r4i_aimSpread;
    x = x + x + r4i_aimBase - r4i_aimSpread;
    o->rot50[0] = 3.1415927f - sub_001A3EC0(y, x);
    o->rot50[1] = (float)(sub_001C7EE1() % 10000) * 0.0001f * r4i_aimYawSpread * 2.0f - r4i_aimYawSpread + o->rot50[1];
    j->f38 = 0.0f;
    w->v0C[0] = r4i_frameSeconds * 0.0f;
    w->v0C[1] = r4i_frameSeconds * 0.0f;
    inv = 1.0f / frames;
    w->v0C[2] = inv * y;
    w->v0C[3] = inv * x;
    r4i_CamPoint(pt, o);
    w->h04 = sub_00036750(o, 0);
    sub_00034CF0(w->h04, pt[0], pt[1], pt[2], pt[3]);
}

/* 0x001961D0: per-frame update of a bolt fired from the owner's parts
   2/13 or 3/5 (hangs when neither exists). Unless touching floor or
   ceiling it remembers its position and moves. On the first frame,
   when 0x000F6A80 is clear and the probe 0x001954C0 hits, it flashes
   and marks the hit; after a hit it is destroyed 12 frames later.
   Without floor contact it faces along its motion and flies on while
   within 150 of its origin (XZ), destroyed after 4 s; otherwise it
   flashes (looping) and is destroyed. A flash plays the owner's motion
   effect with colour (0 1 0 1) at the effect matrix and sound 0x15A. Stack args (o a); calls
   0x001954C0 with EAX=work and the part flag 0 on the stack. */
void r4i_FxBoltUpdate(R4iNodeV *o, R4iActor *a)
{
    R4iBolt *w = (R4iBolt *)a->work;
    R4iSysNode *n = w->owner;
    float up[4];
    float col[4];
    float m[16];
    void *fx;
    int h2 = r4i_PartFind(n, 2, 0xD);
    int h3 = r4i_PartFind(n, 3, 5);

    if (!h2 && !h3)
        for (;;)
            ;
    if (!(o->flags128 & 0x18)) {
        sub_000F5D40(w->prev60, o->pos60);
        sub_001ADAF0(o->pos60, o->pos60, w->vel44);
    }
    if (w->hit58 == 0) {
        if (sub_000F6A80() || r4i_BoltProbe(w, 0) == -1)
            goto fly;
        col[0] = 0.0f;
        col[1] = 1.0f;
        col[2] = 0.0f;
        col[3] = 1.0f;
        fx = r4i_ListPlayMotion(o, w->owner->motion130, 0, 1);
        sub_00033880(fx, m);
        sub_00034DD0(fx, &m[12], &m[8], col);
        r4i_Effect494D0(0x15A, o->pos60, 1);
        w->hit58 = 1;
        w->t5C = 0.0f;
        return;
    }
    if (w->t5C > r4i_frameSeconds * 12.0f)
        goto destroy;
    w->t5C = w->t5C + r4i_frameSeconds;
fly:
    if (!(o->flags128 & 0x18)) {
        up[0] = 0.0f;
        up[1] = 0.0f;
        up[2] = 0.0f;
        up[3] = 1.0f;
        sub_000F5D40(o->v108, up);
        r4i_VecSub(o->vF8, w->prev60, o->pos60);
        if (!(sub_001B2770(o->pos60, w->v24) > 150.0f)) {
            if (a->time6C > 4.0f)
                goto destroy;
            return;
        }
    }
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    fx = r4i_ListPlayMotion(o, w->owner->motion130, 1, 1);
    sub_00033880(fx, m);
    sub_00034DD0(fx, &m[12], &m[8], col);
    r4i_Effect494D0(0x15A, o->pos60, 1);
destroy:
    r4i_ObjDestroyV(o);
}
