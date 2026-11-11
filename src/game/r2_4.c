/* Area r2, group 4: callers of the register-argument helpers and resets. Names inferred. */
#include "r2.h"

/* 0x000D7040: reset the mode block at 0x3EDB60 (first part). */
void r2_ResetModesA(void)
{
    r2_modes3EDB60.i00 = 0;
    r2_modes3EDB60.i04 = 0;
    r2_modes3EDB60.i0C = -1;
    r2_modes3EDB60.f14 = 0.0f;
    r2_modes3EDB60.i2C[0] = -1;
    r2_modes3EDB60.i2C[1] = -1;
    r2_modes3EDB60.i2C[2] = -1;
    r2_modes3EDB60.i2C[3] = -1;
    r2_modes3EDB60.i2C[4] = -1;
    r2_modes3EDB60.i40 = 0;
    r2_modes3EDB60.i44 = 0;
}

/* 0x000D7440: reset the mode block at 0x3EDB60 (second part). */
void r2_ResetModesB(void)
{
    r2_modes3EDB60.i48[0] = 0;
    r2_modes3EDB60.i48[1] = 0;
    r2_modes3EDB60.i48[2] = 0;
    r2_modes3EDB60.i48[3] = 0;
    r2_modes3EDB60.i48[4] = 0;
    r2_modes3EDB60.i48[5] = 0;
    r2_modes3EDB60.i8C = -1;
    r2_modes3EDB60.i90 = -1;
    r2_modes3EDB60.i94 = 0;
    r2_modes3EDB60.f98 = 0.0f;
}

/* 0x000D7480: as 0x0D7440 but enable the first two words and store v in the third. */
void r2_ResetModesC(int v)
{
    r2_modes3EDB60.i48[0] = 1;
    r2_modes3EDB60.i48[1] = 1;
    r2_modes3EDB60.i48[2] = v;
    r2_modes3EDB60.i48[3] = 0;
    r2_modes3EDB60.i48[4] = 0;
    r2_modes3EDB60.i48[5] = 0;
    r2_modes3EDB60.i8C = -1;
    r2_modes3EDB60.i90 = -1;
    r2_modes3EDB60.i94 = 0;
    r2_modes3EDB60.f98 = 0.0f;
}

/* 0x000D8F80: reset the block at 0x3EDC00. */
void r2_ResetBlk3EDC00(void)
{
    r2_blk3EDC00.v00[0] = 0.0f;
    r2_blk3EDC00.v00[1] = 0.0f;
    r2_blk3EDC00.v00[2] = 0.0f;
    r2_blk3EDC00.i2C = 0;
    r2_blk3EDC00.i24 = 0;
    r2_blk3EDC00.i14 = -1;
    r2_blk3EDC00.i18 = -1;
    r2_blk3EDC00.i30 = 0;
    r2_blk3EDC00.i28 = 0;
    r2_blk3EDC00.i1C = -1;
    r2_blk3EDC00.i20 = -1;
    r2_blk3EDC00.i10 = -1;
    r2_blk3EDC00.f0C = 1.0f;
}

/* 0x000EFCF0: zero the +0xF0 velocity (each component scaled by the frame time).
   regargs: obj=EAX */
void r2_ClearVel(R2Mover *obj)
{
    if (!obj)
        for (;;) ;
    obj->velF0[0] = a50_frameSeconds * 0.0f;
    obj->velF0[1] = a50_frameSeconds * 0.0f;
    obj->velF0[2] = a50_frameSeconds * 0.0f;
    obj->velF0[3] = a50_frameSeconds * 0.0f;
}

/* 0x000FCA00: start animation 2 on the helper's +0x8C part, clear its +0xF4 and set
   +0x100 when 0x0F7720(a, 0x318E18) is positive.  Stack arg a. */
void r2_HelperFace(void *a)
{
    R2Helper *h = (R2Helper *)afc_helper;
    R2Actor *l = h->link8C;
    if (!l)
        for (;;) ;
    sub_000832D0(l->part30, 2);
    h->fF4 = 0.0f;
    if (sub_000F7720(a, afc_vec318E18) > 0.0f)
        h->i100 = 1;
    else
        h->i100 = 0;
}

/* 0x0010F0D0: set obj's scale to s and derive its +0xB0 / +0xB4 / +0xA4 values and
   the kind-13 component's +0x18.  regargs: obj=ESI; s is the stack arg */
void r2_SetScale(R2Mover *obj, float s)
{
    R2Comp13 *c;
    float z;
    if (!obj)
        for (;;) ;
    c = (R2Comp13 *)sub_0001D960(obj, 0xD);
    obj->fB0 = s * 6.5f;
    obj->scale70[2] = s;
    obj->scale70[1] = s;
    obj->scale70[0] = s;
    z = s * 0.0f;
    obj->fB4 = s * -50.0f;
    obj->fA4 = z;
    c->f18 = z;
}

/* 0x00114DC0: is the target picked by c within [min, max] distance of self?
   calls 0x00114D60 with EAX=c ECX=ctx self=stack */
int r2_TargetInRange(void *self, R2Ctx *ctx, const R2Cond *c)
{
    R2Actor *t = (R2Actor *)r2_PickTarget(c, ctx, self);
    float d;
    if (t) {
        d = sub_001B2770(((R2Actor *)self)->pos60, t->pos60);
        if (d >= c->min10 && c->max14 >= d)
            return 1;
    }
    return 0;
}

/* 0x0011EE90: as 0x114DC0 using picker 0x11EE30.
   calls 0x0011EE30 with EAX=c ECX=ctx self=stack */
int r2_TargetInRangeB(void *self, R2Ctx *ctx, const R2Cond *c)
{
    R2Actor *t = (R2Actor *)r2_PickTargetB(c, ctx, self);
    float d;
    if (t) {
        d = sub_001B2770(((R2Actor *)self)->pos60, t->pos60);
        if (d >= c->min10 && c->max14 >= d)
            return 1;
    }
    return 0;
}

/* 0x0011EEF0: is the target picked by c within [min, max] height difference of self?
   calls 0x0011EE30 with EAX=c ECX=ctx self=stack */
int r2_TargetHeightInRange(R2Body *self, R2Ctx *ctx, const R2Cond *c)
{
    R2Body *t = (R2Body *)r2_PickTargetB(c, ctx, self);
    float d;
    if (t) {
        d = sub_001A3F30(self->y64 - t->y64);
        if (d >= c->min10 && c->max14 >= d)
            return 1;
    }
    return 0;
}

/* 0x0011FB10: is any other actor of kind 5 or 15 flagged 0x2000?
   regargs: self=EAX; calls 0x0011FAC0 with EAX=kind EDI=self */
int r2_AnyFlag2000Kinds(void *self)
{
    if (r2_AnyFlag2000(5, self))
        return 1;
    return r2_AnyFlag2000(15, self) != 0;
}

/* 0x0011FB90: is any other actor of kind 5 or 15 flagged with mask?
   regargs: mask=EAX self=ECX; calls 0x0011FB40 with EAX=kind EDI=self ESI=mask */
int r2_AnyFlagKinds(uint32_t mask, void *self)
{
    if (r2_AnyFlagMask(5, self, mask))
        return 1;
    return r2_AnyFlagMask(15, self, mask) != 0;
}

/* 0x0012E590: free slots = 20 - used - actors of kinds 0/14; when it grows, report
   the gain (if flag 1) and set flags 0xC00.  regargs: obj=EAX */
void r2_UpdateFreeSlotsB(R2Body *obj)
{
    R2State *st = obj->st278;
    int n = 20 - st->used190 - r2_CountKinds0E();
    if (n > st->free194) {
        if (st->flags0C & 1)
            sub_00025C10(2, n - st->free194);
        st->flags0C |= 0xC00;
        st->free194 = n;
    }
}
