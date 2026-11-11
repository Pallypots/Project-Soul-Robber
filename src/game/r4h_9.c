/* Area r4h: slot effect spawner at 0x00400A88 (r4h_9). Names inferred. */
#include "r4h.h"

/* 0x00193C10: spawn callback of the four slot effects: bind slot idx
   (0..3, hangs otherwise) to the node and actor, set callbacks, collision
   and the texture vector. Slots 0 and 1 are scaled to 1.0 and enter
   state 1; slots 2 and 3 get the message handler, a 120 degree yaw, play
   animation 1 and enter state 2. Returns 0 without a node or actor.
   Stack args (o a idx); calls 0x00192630 with EAX=idx and 1.0 on the stack. */
int r4h_FxSlotSpawn(R4hFxNodeD *o, R4hFxActD *a, int idx)
{
    R4hSlot88 *rec;
    float v[4];

    if (!o || !a)
        return 0;
    while (idx < 0 || idx >= 4)
        ;
    rec = &r4c_recs400A88[idx];
    rec->obj = o;
    rec->actor = a;
    rec->idx = idx;
    a->work = rec;
    o->flagsC |= 3;
    a->fn78 = (void *)r4c_SlotStop;
    a->fn7C = (void *)r4h_FxSlotStep;
    a->flags20 |= 0x80000000u;
    rec->f68 = 1.7f;
    rec->h6C = 0;
    o->iF0 = 2;
    o->iF4 = 2;
    o->i120 = 2;
    v[0] = 0.0f;
    v[2] = 0.0f;
    o->i11C = 1;
    v[1] = 2.5f;
    v[3] = 1.0f;
    sub_0001EF00(o, v);
    if (idx < 2) {
        a->p84 = r4h_d32C728;
        a->p88 = r4h_d32C734;
        o->flagsC &= ~0xE0u;
        o->flags10 |= 0x5CD;
        o->i124 = 1;
        r4c_SlotScale(idx, 1.0f);
        rec->f14 = 0.0f;
        sub_00189DA0(o, a, 1);
        a->f28 = 0.0f;
        return 1;
    }
    a->p84 = r4h_d32C740;
    a->p88 = r4h_d32C760;
    a->fn80 = (void *)r4c_SlotMsg;
    o->flags10 |= 0x200;
    a->i24 = 0;
    o->rot50[3] = 1.0f;
    o->rot50[0] = 0.0f;
    o->rot50[1] = 0.0f;
    o->rot50[2] = 0.0f;
    o->rot50[1] = 2.0943952f;
    o->i124 = 1;
    a->f28 = 0.0f;
    a->f2C = -8.7f;
    sub_000832D0(o->anim30, 1);
    sub_00189DA0(o, a, 2);
    return 1;
}

/* 0x00193A30: per-frame step of a slot effect: apply the slot rate; for
   slots 2 and 3 keep the node visible unless the player context is in
   mode 1 and neither of those slots is in state 3. In state 7 (flying),
   when 0.01 < XZ distance < 20 and above height -4, pull the position to
   20 units from 0x00318DC8 on the ground, enter state 7 again and scale
   the slot to 2.9; when higher than 30 or farther than 90, reset it to
   its home position, enter state 2 and scale to 2.2. Outside states 2
   and 7 set the model value 1.7. Stack args (o a); calls 0x00192630 with
   EAX=slot index and the scale on the stack. */
void r4h_FxSlotStep(R4hFxNodeD *o, R4hFxActD *a)
{
    R4hSlot88 *rec = a->work;
    R4hPlayCtx *ctx;
    float *pos;
    float d;
    int st;

    sub_0001EEC0(o, rec->f14);
    if (rec->idx < 2)
        return;
    ctx = sub_000E0770();
    if (ctx->i324 == 1 && r4c_recs400A88[2].actor->state60 != 3 && r4c_recs400A88[3].actor->state60 != 3)
        o->flags10 &= ~1u;
    else
        o->flags10 |= 1;
    if (a->state60 == 7) {
        pos = o->pos60;
        d = sub_000F5F50(pos);
        if (d > 0.01f && 20.0f > d && o->pos60[1] > -4.0f) {
            o->rot50[0] = 0.0f;
            o->rot50[1] = 0.0f;
            o->rot50[2] = 0.0f;
            o->rot50[3] = 1.0f;
            sub_001AD9F0(pos, pos, r4h_v318DC8);
            sub_001ADB60(pos, pos, 20.0f / d);
            o->pos60[1] = 0.0f;
            o->pos60[3] = 1.0f;
            sub_00189DA0(o, a, 7);
            r4c_SlotScale(rec->idx, 2.9f);
            o->flagsC |= 0xE0;
        }
        if (o->pos60[1] > 30.0f || d > 90.0f) {
            o->rot50[0] = 0.0f;
            o->rot50[1] = 0.0f;
            o->rot50[2] = 0.0f;
            o->rot50[3] = 1.0f;
            o->rot50[1] = 2.0943952f;
            sub_000F5D40(pos, rec->idx == 2 ? r4c_v27AFE8 : r4c_v27AFF8);
            sub_00189DA0(o, a, 2);
            r4c_SlotScale(rec->idx, 2.2f);
            o->flagsC |= 0xE0;
        }
    }
    st = a->state60;
    if (st != 2 && st != 7)
        sub_000EE760(o, 1.7f);
}

/* 0x00193490: flying state of a slot effect: move by the velocity with
   gravity (capped at 140 per second), grow the slot scale towards 2.9,
   mark it flown once 34.5 units out (XZ), slow it down while faster than
   14 per second, bounce off walls (bit 1) and the floor (bit 3, up to
   three bounces with the vertical speed scaled by -0.75 and capped at
   -20 per second; then state 7). Stack args (o a); calls 0x00192630
   with EAX=slot index and the scale on the stack. */
void r4h_FxSlotFly(R4hFxNodeD *o, R4hFxActD *a)
{
    R4hSlot88 *rec = a->work;
    float *vel = rec->vel2C;
    float *pos = o->pos60;
    float lim;

    sub_000F6450(o, r4h_d32C718);
    sub_001ADAF0(pos, pos, vel);
    rec->vel2C[1] = 3.0f / a50_framesPerSecond + rec->vel2C[1];
    lim = 140.0f / a50_framesPerSecond;
    if (rec->vel2C[1] > lim)
        rec->vel2C[1] = lim;
    if (2.9f > rec->scale58) {
        rec->scale58 = 1.9f / (30.0f / r4c_frameUnits) + rec->scale58;
        if (rec->scale58 > 2.9f)
            rec->scale58 = 2.9f;
        r4c_SlotScale(rec->idx, rec->scale58);
    }
    if (rec->flown62 == 0) {
        if (sub_000F5F50(pos) > 34.5f) {
            rec->flown62 = 1;
            o->flagsC |= 0xE0;
        }
    } else if (sub_000F5F50(vel) > 14.0f / a50_framesPerSecond) {
        vel[0] = vel[0] * 0.98f;
        rec->vel2C[2] = rec->vel2C[2] * 0.98f;
    }
    if (o->flags128 & 2) {
        vel[0] = vel[0] * -1.0f;
        rec->vel2C[2] = rec->vel2C[2] * -1.0f;
        sub_000832D0(o->anim30, -1);
        sub_000832D0(o->anim30, 1);
    }
    if (o->flags128 & 8) {
        sub_000832D0(o->anim30, -1);
        sub_000832D0(o->anim30, 1);
        if (rec->bounce60 < 3) {
            rec->bounce60++;
            rec->vel2C[1] = rec->vel2C[1] * -0.75f;
            lim = -20.0f / a50_framesPerSecond;
            if (rec->vel2C[1] > lim)
                rec->vel2C[1] = lim;
            return;
        }
        sub_00189DA0(o, a, 7);
    }
}

/* 0x00193700: held state of slots 0 and 1: fall with gravity until
   landing (sub-state 0), then wait on the ground (sub-state 1: after 3
   seconds in player mode 1 throw it with 0x00192730 and switch to
   sub-state 2; replay the idle animation every 0.6 seconds), or ride the
   parent at 2.9 times its position (sub-state 2) until active again.
   Finally pulse the model value between 2.0 and 5.0. Stack args (o a);
   calls 0x00192730 with ESI=rec. */
void r4h_FxSlotHold(R4hFxNodeD *o, R4hFxActD *a)
{
    R4hSlot88 *rec = a->work;
    float v[4];
    float lim;

    if (rec->sub10 != 2) {
        rec->vel2C[1] = 3.0f / a50_framesPerSecond + rec->vel2C[1];
        lim = 140.0f / a50_framesPerSecond;
        if (rec->vel2C[1] > lim)
            rec->vel2C[1] = lim;
        o->pos60[1] = o->pos60[1] + rec->vel2C[1];
        if (o->flags128 & 0x18) {
            rec->vel2C[0] = 0.0f;
            rec->vel2C[1] = 0.0f;
            rec->vel2C[2] = 0.0f;
            rec->vel2C[3] = 0.0f;
        }
    }
    switch (rec->sub10) {
    case 0:
        if (!(o->flags128 & 0x18))
            break;
        sub_000832D0(o->anim30, -1);
        sub_000832D0(o->anim30, 1);
        goto landed;
    case 1:
        if (sub_000E0770()->i324 == 1) {
            if (rec->t0C > 3.0f) {
                if (sub_000F5D00(o)) {
                    sub_000832D0(o->anim30, 2);
                    r4h_SlotThrow(rec);
                    rec->sub10 = 2;
                    break;
                }
            } else {
                rec->t0C = rec->t0C + r4c_frameSeconds;
            }
        }
        if (sub_000F5D00(o)) {
            if (rec->t64 > 0.6f) {
                sub_000832D0(o->anim30, -1);
                sub_000832D0(o->anim30, 1);
                rec->t64 = 0.0f;
            } else {
                rec->t64 = r4c_frameSeconds + rec->t64;
            }
        }
        break;
    case 2:
        sub_001ADB60(v, o->parent34->pos70, 2.9f);
        o->pos60[0] = o->pos60[0] + v[0];
        o->pos60[1] = o->pos60[1] + v[1];
        o->pos60[2] = o->pos60[2] + v[2];
        o->pos60[3] = o->pos60[3];
        if (sub_000F5D00(o)) {
            rec->t64 = 0.0f;
            goto landed;
        }
        break;
    }
    goto pulse;
landed:
    rec->sub10 = 1;
    rec->t0C = 0.0f;
pulse:
    if (rec->h6C == 0) {
        rec->f68 = 3.0f / (a50_framesPerSecond * 0.925f) + rec->f68;
        if (rec->f68 > 5.0f) {
            rec->f68 = 5.0f;
            sub_000EE760(o, rec->f68);
            rec->h6C = 1;
            return;
        }
    } else if (rec->h6C == 1) {
        rec->f68 = rec->f68 - 3.0f / (a50_framesPerSecond * 0.925f);
        if (2.0f > rec->f68) {
            rec->f68 = 2.0f;
            rec->h6C = 0;
        }
    }
    sub_000EE760(o, rec->f68);
}

/* 0x00192A70: thrown state of slots 0 and 1. Sub-state 0: fly as
   0x00193490 (slower drag threshold 18, no bounce animation, up to five
   floor bounces with -0.77, then upright and sub-state 1). Otherwise fade:
   reset the model value, lower the slot rate (seven times faster while
   alpha is at most 35) and the alpha by 128 per 180 frames, destroying
   the node at zero. Stack args (o a); calls 0x00192630 with EAX=slot
   index and the scale on the stack. */
void r4h_FxSlotFlyB(R4hFxNodeD *o, R4hFxActD *a)
{
    R4hSlot88 *rec = a->work;
    float *vel;
    float *pos;
    float lim;
    float k;

    if (rec->sub10 == 0) {
        sub_000F6450(o, r4h_d32C6F8);
        vel = rec->vel2C;
        pos = o->pos60;
        sub_001ADAF0(pos, pos, vel);
        rec->vel2C[1] = 3.0f / a50_framesPerSecond + rec->vel2C[1];
        lim = 140.0f / a50_framesPerSecond;
        if (rec->vel2C[1] > lim)
            rec->vel2C[1] = lim;
        if (2.9f > rec->scale58) {
            rec->scale58 = 1.9f / (30.0f / r4c_frameUnits) + rec->scale58;
            if (rec->scale58 > 2.9f)
                rec->scale58 = 2.9f;
            r4c_SlotScale(rec->idx, rec->scale58);
        }
        if (rec->flown62 == 0) {
            if (sub_000F5F50(pos) > 34.5f) {
                rec->flown62 = 1;
                o->flagsC |= 0xE0;
            }
        } else if (sub_000F5F50(vel) > 18.0f / a50_framesPerSecond) {
            vel[0] = vel[0] * 0.98f;
            rec->vel2C[2] = rec->vel2C[2] * 0.98f;
        }
        if (o->flags128 & 2) {
            vel[0] = vel[0] * -1.0f;
            rec->vel2C[2] = rec->vel2C[2] * -1.0f;
        }
        if (!(o->flags128 & 8))
            return;
        if (rec->bounce60 < 5) {
            rec->bounce60++;
            rec->vel2C[1] = rec->vel2C[1] * -0.77f;
            lim = -20.0f / a50_framesPerSecond;
            if (rec->vel2C[1] > lim)
                rec->vel2C[1] = lim;
            return;
        }
        o->rot50[0] = 0.0f;
        o->rot50[1] = 0.0f;
        o->rot50[2] = 0.0f;
        o->rot50[3] = 1.0f;
        rec->sub10 = 1;
        return;
    }
    sub_000EE760(o, 1.0f);
    k = 0.218225f / (180.0f / r4c_frameUnits);
    if (!(o->alpha9C > 35.0f))
        k = k * 7.0f;
    rec->f14 = rec->f14 - k;
    if (0.0f > rec->f14)
        rec->f14 = 0.0f;
    o->alpha9C = o->alpha9C - 128.0f / (180.0f / r4c_frameUnits);
    if (0.0f > o->alpha9C) {
        o->alpha9C = 0.0f;
        sub_000ED780(o);
    }
}
