/* Area r4c: slot effect callbacks around 0x001923B0-0x00193E4E (r4c_3). Names inferred. */
#include "r4c.h"

/* 0x001923B0: spawn the four slot effects and place them at their start points. No inputs. */
void r4c_SlotsSpawn(void)
{
    sub_000ED630(5, 0x0B, 0, 0, 0);
    sub_000ED630(5, 0x0C, 0, 0, 1);
    sub_000ED630(5, 0x0D, 0, 0, 2);
    sub_000ED630(5, 0x0E, 0, 0, 3);
    sub_000F5D40(r4c_recs400A88[0].obj->pos, r4c_v27B00C);
    sub_000F5D40(r4c_recs400A88[1].obj->pos, r4c_v27B01C);
    sub_000F5D40(r4c_recs400A88[2].obj->pos, r4c_v27AFE8);
    sub_000F5D40(r4c_recs400A88[3].obj->pos, r4c_v27AFF8);
}

/* 0x00192470: stop callback of a slot effect: reset its slot record and detach it; returns 1 when stopped. Stack args (o a). */
int r4c_SlotStop(R4cNode *o, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    if (!(o->flagsC & 1))
        return 0;
    w->f0C = 0.0f;
    w->v2C[0] = 0.0f;
    w->v2C[1] = 0.0f;
    w->v2C[2] = 0.0f;
    w->v2C[3] = 0.0f;
    w->v1C[0] = 0.0f;
    w->v1C[1] = 0.0f;
    w->v1C[2] = 0.0f;
    w->v1C[3] = 0.0f;
    w->obj = 0;
    w->i04 = 0;
    w->idx08 = -1;
    w->s10 = 0;
    w->q3C[0] = 0.0f;
    w->q3C[1] = 0.0f;
    w->q3C[2] = 0.0f;
    w->q3C[3] = 1.0f;
    w->f4C = 0.0f;
    w->f50 = 0.0f;
    w->f64 = 0.0f;
    w->f58 = 1.0f;
    w->f68 = 1.7f;
    w->s6C = 0;
    a->work = 0;
    sub_0001EB80(o);
    o->flagsC &= ~3u;
    o->flags10 |= 0xD;
    return 1;
}

/* 0x00192530: message handler of a slot effect. Stack args (o a msg). */
int r4c_SlotMsg(R4cNode *o, R4cActor *a, R4cMsg *msg)
{
    R4cSlot *w = (R4cSlot *)a->work;
    R4cSys *sys;
    switch (msg->id) {
    case 14: case 40:
        sub_000832D0(o->anim30, 1);
        sub_00189DA0(o, a, 3);
        sub_001AD940(sub_0001D0F0(o, 0));
        return 1;
    case 26: case 27: case 28:
        sub_00189DA0(o, a, 7);
        return 0;
    case 42:
        sys = sub_000F3F80();
        if (sub_000CB9B0() == (int)sys->p8C) {
            sub_00189DA0(o, a, 5);
            return 0;
        }
        r4c_VecScale(w->v2C, msg->v20, r4c_frameUnits);
        sub_00189DA0(o, a, 4);
        return 0;
    }
    return 0;
}

/* 0x00192880: start a slot effect: attach it to part 15, scale 1, place it at its side's start point. Stack args (o a). */
void r4c_SlotStart(R4cNode *o, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    int k;
    r4c_SlotAttach(w->idx08, 0xF);
    o->flags10 |= 0x14D;
    o->rot50[0] = 0.0f;
    o->rot50[1] = 0.0f;
    o->rot50[2] = 0.0f;
    o->rot50[3] = 1.0f;
    r4c_SlotScale(w->idx08, 1.0f);
    k = w->idx08;
    if (k == 0 || k == 2)
        sub_000F5D40(o->pos, r4c_v27B00C);
    else if (k == 1 || k == 3)
        sub_000F5D40(o->pos, r4c_v27B01C);
}

/* 0x00192970: launch a slot effect from scene part 15 with a random speed. Stack args (o a). */
void r4c_SlotLaunch(R4cNode *o, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    void *scene = sub_000F3F80()->p8C;
    float k;
    sub_0001EB80(o);
    sub_0001E9B0(r4c_ctx42C8E4, o, o->i14C, 5, 0x11);
    o->flagsC &= ~0xE0u;
    sub_000F5D40(o->pos, (char *)sub_0001D0F0(scene, 0xF) + 0x70);
    w->f58 = 1.0f;
    r4c_SlotScale(w->idx08, 1.0f);
    k = ((float)(sub_001C7EE1() % 80) * 0.01f + 5.2f) * 10.0f / r4c_fps;
    w->v2C[0] = w->v1C[0] * k;
    w->v2C[2] = w->v1C[2] * k;
    w->v2C[1] = -63.0f / r4c_fps;
    w->v2C[3] = 0.0f;
    w->s62 = 0;
    w->s60 = 0;
    w->s10 = 0;
}

/* 0x00192CE0: grow a slot effect to scale 2.2 and reset its pulse. Stack args (unused a). */
void r4c_SlotGrow(void *unused, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    r4c_SlotScale(w->idx08, 2.2f);
    w->f14 = 0.7f;
    w->f64 = 0.0f;
    w->f68 = 1.7f;
    w->s6C = 0;
}

/* 0x00192D30: animate a slot effect: restart its animation after 0.95 s and pulse its size between 2 and 5. Stack args (o a). */
void r4c_SlotPulse(R4cNode *o, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    float v;
    if (sub_000F5D00(o)) {
        if (w->f64 > 0.95f) {
            sub_000832D0(o->anim30, -1);
            sub_000832D0(o->anim30, 1);
            w->f64 = 0.0f;
        } else {
            w->f64 = r4c_frameSeconds + w->f64;
        }
    }
    if (w->s6C == 0) {
        v = 3.0f / (r4c_fps * 0.925f) + w->f68;
        w->f68 = v;
        if (v > 5.0f) {
            w->s6C = 1;
            w->f68 = 5.0f;
        }
    } else if (w->s6C == 1) {
        v = w->f68 - 3.0f / (r4c_fps * 0.925f);
        w->f68 = v;
        if (2.0f > v) {
            w->s6C = 0;
            w->f68 = 2.0f;
        }
    }
    sub_000EE760(o, w->f68);
}

/* 0x00192E30: grow a slot effect to scale 2.9. Stack args (unused a). */
void r4c_SlotGrowBig(void *unused, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    r4c_SlotScale(w->idx08, 2.9f);
    w->f18 = 0.0f;
}

/* 0x00192E60: move a slot effect; switch to state 7 after 60 units or on contact. Stack args (o a). */
void r4c_SlotFly(R4cNode *o, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    r4c_VecAdd(o->pos, o->pos, w->v2C);
    w->f18 = r4c_VecLenXZ(w->v2C) + w->f18;
    if (w->f18 >= 60.0f || (o->flags128 & 0xA))
        sub_00189DA0(o, a, 7);
}

/* 0x00193670: reset a slot effect at scale 2.9 and remember its start position. Stack args (o a). */
void r4c_SlotReset(R4cNode *o, R4cActor *a)
{
    R4cSlot *w = (R4cSlot *)a->work;
    o->flags10 &= ~0x41u;
    r4c_SlotScale(w->idx08, 2.9f);
    o->rot50[0] = 0.0f;
    o->rot50[1] = 0.0f;
    o->rot50[2] = 0.0f;
    o->rot50[3] = 1.0f;
    w->v2C[0] = 0.0f;
    w->v2C[1] = 0.0f;
    w->v2C[2] = 0.0f;
    w->v2C[3] = 0.0f;
    w->f0C = 0.0f;
    w->s10 = 0;
    w->f68 = 1.7f;
    w->s6C = 0;
    w->i70 = 0;
    sub_000F5D40(w->v78, o->pos);
}

/* 0x00193E10: claim a free record at 0x00400CA8 (bit 0 clear), zero it and mark it used; returns it or 0. No inputs. */
R4cRec1C *r4c_Rec1CAlloc(void)
{
    R4cRec1C *r;
    int i;
    i = 0;
    for (r = r4c_recs400CA8; r < r4c_recs400CA8 + 15; r++, i++)
        if (!(r->flags & 1))
            goto found;
    return 0;
found:
    r = &r4c_recs400CA8[i];
    r->flags = 0;
    r->f[0] = 0;
    r->f[1] = 0;
    r->f[2] = 0;
    r->f[3] = 0;
    r->f[4] = 0;
    r->f[5] = 0;
    r->flags |= 1;
    return r;
}
