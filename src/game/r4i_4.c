/* Area r4i: slot effect landing step (0x00193040). Names inferred. */
#include "r4i.h"

/* 0x00193040: thrown slot effect (slots 2 and 3) flying back: spin, set
   the position to the slot offset plus the velocity, accelerate the
   velocity (X/Z by dir1C, Y by the gravity difference) and shrink the
   slot scale from 2.9 to 1 over the flight time. Before the flight time
   is up only the state time advances. Then, if 0x000F40C0 refuses,
   enter state 6; otherwise hand the XZ direction to the partner slot
   (index - 2), put the partner in state 2 at scale 1, enter state 1,
   and play motion effect 6 at Jack's joint 13 (6 units lower) with the
   colour (0 1 0 1). Stack args (o a); calls 0x00192630 with EAX=slot
   index and the scale on the stack. */
void r4i_FxSlotLand(R4iNode *o, R4iActor *a)
{
    R4iSlot *w = (R4iSlot *)a->work;
    R4iSlot *rec;
    float frames = w->t0C * r4i_fps;
    float v[4];
    float col[4];
    float m[16];
    void *fx;

    r4i_SpinNode(o, r4i_spin32C708);
    sub_001ADAF0(o->pos60, w->off3C, w->vel2C);
    w->vel2C[0] = w->dir1C[0] + w->vel2C[0];
    w->vel2C[2] = w->dir1C[2] + w->vel2C[2];
    w->vel2C[1] = w->vel2C[1] - (w->v54 - w->v50);
    w->v50 = w->g4C + w->v50;
    r4i_SlotScale(w->idx08, (1.0f - frames / w->time5C) * 1.9f + 1.0f);
    if (!(frames > w->time5C)) {
        w->t0C = w->t0C + r4i_frameSeconds;
        return;
    }
    if (sub_000F40C0())
        goto partner;
    r4i_SetState(o, a, 6);
    return;
partner:
    rec = &r4i_slots400A88[w->idx08 - 2];
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    sub_000F5D40(v, w->vel2C);
    v[1] = 0.0f;
    v[3] = 0.0f;
    sub_001AD7E0(rec->dir1C, v);
    r4i_SetState(rec->obj, rec->actor, 2);
    r4i_SlotScale(w->idx08, 1.0f);
    r4i_SetState(o, a, 1);
    sub_000F5D40(v, r4i_Joint(r4i_GetSys()->node8C, 0xD)->pos70);
    v[1] = v[1] - 6.0f;
    fx = sub_00035DD0(rec->obj, r4i_GetSys()->node8C->motion130, 1, 1);
    sub_00033880(fx, m);
    sub_00034DD0(fx, v, &m[8], col);
    sub_000F3F90(6);
}

/* 0x00193260: throw a slot effect. Within +-25 degrees of camera yaw
   (0x000F3F80 +0x114) the velocity is the forward vector (0 0 -1) turned
   by a random +-10 degrees; otherwise the current velocity is flattened,
   normalised and turned 40-60 degrees away from the camera side. The
   horizontal speed is (4.5 + 0..3.49) * 10 per second (negated in the
   second case), the vertical speed -60 per second; scale 1 and the
   bounce/flown counters are reset. Returns 0. Stack args (o a); calls
   0x00192630 with EAX=slot index and 1.0 on the stack. */
int r4i_FxSlotThrow(R4iNode *o, R4iActor *a)
{
    R4iSlot *w = (R4iSlot *)a->work;
    float *vel;
    float fwd[4];
    float m[16];
    float yaw;
    float ang;
    float s;

    fwd[0] = 0.0f;
    fwd[1] = 0.0f;
    fwd[2] = -1.0f;
    fwd[3] = 0.0f;
    yaw = r4i_GetSys()->yaw114;
    sub_001AD940(m);
    if (0.43633232f > yaw && yaw > -0.43633232f) {
        ang = (float)(sub_001C7EE1() % 21 - 10) * 3.1415927f * 0.0055555557f;
        sub_001AD8E0(m, m, ang);
        vel = w->vel2C;
        sub_001AD9B0(vel, m, fwd);
        s = ((float)(sub_001C7EE1() % 350) * 0.01f + 4.5f) * 10.0f / r4i_fps;
    } else {
        if (yaw > 0.0f)
            ang = 0.0f - (float)(sub_001C7EE1() % 21 + 40) * 3.1415927f * 0.0055555557f;
        else
            ang = (float)(sub_001C7EE1() % 21 + 40) * 3.1415927f * 0.0055555557f;
        vel = w->vel2C;
        w->vel2C[3] = 0.0f;
        w->vel2C[1] = 0.0f;
        sub_001AD7E0(vel, vel);
        sub_001AD8E0(m, m, ang);
        sub_001AD9B0(vel, m, vel);
        s = ((float)(sub_001C7EE1() % 350) * 0.01f + 4.5f) * 10.0f / r4i_fps * -1.0f;
    }
    vel[0] = vel[0] * s;
    w->vel2C[2] = w->vel2C[2] * s;
    w->vel2C[1] = -60.0f / r4i_fps;
    w->scale58 = 1.0f;
    r4i_SlotScale(w->idx08, 1.0f);
    w->flown62 = 0;
    w->bounce60 = 0;
    return 0;
}
