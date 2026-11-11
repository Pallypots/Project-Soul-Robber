/* Area r2, group 3: callees with register inputs (0x00112CD0..0x0012E588). Names inferred. */
#include "r2.h"

/* 0x00112CD0: blend the four rows of two 4x4 matrices with weight t via 0x1ADC60.
   regargs: a=EAX b=ECX dst=EDX; t is the stack arg */
void r2_LerpMat(const float *a, const float *b, float *dst, float t)
{
    sub_001ADC60(dst, b, a, t);
    sub_001ADC60(dst + 4, b + 4, a + 4, t);
    sub_001ADC60(dst + 8, b + 8, a + 8, t);
    sub_001ADC60(dst + 12, b + 12, a + 12, t);
}

/* 0x00114D10: run step script idx of table 0x31A380; every step's handler (by type)
   must succeed.  regargs: idx=EAX a=EBX b=EDI */
int r2_RunSteps31A380(int idx, void *a, void *b)
{
    R2Step *s = r2_steps31A380[idx];
    if (!s)
        for (;;) ;
    for (; s->key00; s++)
        if (!r2_stepFn31A394[s->type04](a, b, s))
            return 0;
    return 1;
}

/* 0x00115440: free slots = 20 - used - number of kind-1 actors; raise the stored
   value and set flag 0x80 when it grows.  regargs: obj=EAX */
void r2_UpdateFreeSlots(R2Body *obj)
{
    R2State *st = obj->st278;
    int n = 0, f;
    if (sub_000EDC20(2, 1))
        do
            n++;
        while (sub_000EDC20(-1, -1));
    f = 20 - st->used54 - n;
    if (f > st->free58) {
        st->free58 = f;
        st->flags04 |= 0x80;
    }
}

/* 0x0011B020: call handler a of table 0x31B0C4 with (arg, b, vector a of 0x279598).
   regargs: a=EAX b=EDX; arg is the stack arg */
int r2_CallTbl31B0C4(int a, int b, int arg)
{
    return r2_fn31B0C4[a](arg, b, r2_vec279598[a]);
}

/* 0x0011B0D0: report a pending hit from the state flags: 0x10 -> 5 (and stop +0x74),
   0x40 -> 4.  Returns 1 when one was reported.  regargs: obj=ECX out=EDX */
int r2_GetHitKind(R2Body *obj, int *out)
{
    uint32_t f = obj->st278->flags04;
    if (f & 0x10) {
        *out = 5;
        obj->f74 = 0.0f;
        return 1;
    }
    if (f & 0x40) {
        *out = 4;
        return 1;
    }
    return 0;
}

/* 0x0011B110: forward (p, b, c) to 0x1130F0 and 0x119FF0 for kind-2 records of
   sub-kind 3 or 4.  regargs: p=ESI b=EBX c=EDI */
void r2_RecNotify(R2Rec *p, void *b, int c)
{
    if (p && p->kind04 == 2 && (p->sub08 == 3 || p->sub08 == 4)) {
        sub_001130F0(p, b, c);
        sub_00119FF0(p, b, c);
    }
}

/* 0x0011B140: map kind 3 -> 0x0EDBE0(2, 4) and kind 4 -> 0x0EDBE0(2, 3), else 0.
   regargs: kind=EAX */
void *r2_SelectKind(int kind)
{
    switch (kind) {
    case 3:
        return sub_000EDBE0(2, 4);
    case 4:
        return sub_000EDBE0(2, 3);
    }
    return 0;
}

/* 0x0011B170: for sub-kind 3/4 records whose kind-4 component is active and in
   state 5 or 6, pass it to 0x113040 and return 1.  regargs: p=ESI; arg is the stack arg */
int r2_RecHit(R2Rec *p, int arg)
{
    R2Comp4 *c;
    if (p && (p->sub08 == 3 || p->sub08 == 4)) {
        c = (R2Comp4 *)sub_0001D960(p, 4);
        if ((c->flags22 & 1) && (c->state50 == 5 || c->state50 == 6)) {
            sub_00113040(p, c, arg);
            return 1;
        }
    }
    return 0;
}

/* 0x0011B1C0: attach obj to b, reset its +0x20 effect scale to 1 and replace its
   +0x34 handle with a new kind-4 attachment of b.  regargs: obj=EAX b=EDI */
void r2_BodyReattach(R2Body *obj, void *b)
{
    R2State *st = obj->st278;
    sub_00113AA0(b, obj);
    if (st->h20)
        sub_000EE660(st->h20, 1.0f);
    if (st->h34) {
        sub_00033560(st->h34);
        st->h34 = 0;
    }
    st->h34 = sub_00036750(b, 4);
}

/* 0x0011EDE0: as 0x114D10 for table 0x31C110.  regargs: idx=EAX a=EBX b=EDI */
int r2_RunSteps31C110(int idx, void *a, void *b)
{
    R2Step *s = r2_steps31C110[idx];
    if (!s)
        for (;;) ;
    for (; s->key00; s++)
        if (!r2_stepFn31C174[s->type04](a, b, s))
            return 0;
    return 1;
}

/* 0x0011FA60: set flag 4, copy +0xF8 into +0xB8, rebuild the +0x138 matrix for kind
   and store kind and f.  regargs: obj=EAX kind=EBX; f is the stack arg;
   calls 0x0011F640 with EAX=kind ESI=&st->mat138 */
void r2_BodyResetMat(R2Body *obj, int kind, float f)
{
    R2State *st = obj->st278;
    st->flags04 |= 4;
    sub_001ADA40(st->vecF8, st->vecB8);
    sub_0011F640(kind, st->mat138);
    st->f17C = 0.0f;
    st->kind178 = kind;
    st->f180 = f;
}

/* 0x0011FAC0: is any other actor of `kind` flagged 0x2000 in its kind-4 state?
   regargs: kind=EAX self=EDI */
int r2_AnyFlag2000(int kind, void *self)
{
    void *e = sub_000EDC20(2, kind);
    while (e) {
        if (e != self && (((R2Comp4 *)sub_0001D960(e, 4))->st278->flags04 & 0x2000))
            return 1;
        e = sub_000EDC20(-1, -1);
    }
    return 0;
}

/* 0x0011FB40: as 0x11FAC0 with a caller-given flag mask.
   regargs: kind=EAX self=EDI mask=ESI */
int r2_AnyFlagMask(int kind, void *self, uint32_t mask)
{
    void *e = sub_000EDC20(2, kind);
    while (e) {
        if (e != self && (((R2Comp4 *)sub_0001D960(e, 4))->st278->flags04 & mask))
            return 1;
        e = sub_000EDC20(-1, -1);
    }
    return 0;
}

/* 0x0012DC90: as 0x114D10 for table 0x31C510.  regargs: idx=EAX a=EBX b=EDI */
int r2_RunSteps31C510(int idx, void *a, void *b)
{
    R2Step *s = r2_steps31C510[idx];
    if (!s)
        for (;;) ;
    for (; s->key00; s++)
        if (!r2_stepFn31C524[s->type04](a, b, s))
            return 0;
    return 1;
}

/* 0x0012E330: copy point idx into dst: from 0x31C538 (the vector after the matching
   key) when the state flag 1 is set, else from 0x31C618.
   regargs: obj=ECX idx=EAX key=ESI dst=EDI */
void r2_GetPoint(R2Body *obj, int idx, int key, float *dst)
{
    if (obj->st278->flags0C & 1) {
        R2PtRec *r = &r2_pts31C538[idx];
        int i;
        for (i = 0; i < 2; i++)
            if (r->key30[i] == key)
                break;
        if (i >= 2)
            for (;;) ;
        sub_000F5D40(dst, r->v[i + 1]);
    } else {
        sub_000F5D40(dst, r2_pts31C618[idx]);
    }
}

/* 0x0012E540: number of actors of kinds 0 and 14 (via the 0x0EDC20 iterator). */
int r2_CountKinds0E(void)
{
    int n = 0;
    if (sub_000EDC20(2, 0))
        do
            n++;
        while (sub_000EDC20(-1, -1));
    if (sub_000EDC20(2, 0xE))
        do
            n++;
        while (sub_000EDC20(-1, -1));
    return n;
}

/* 0x00114D60: pick the target named by condition c: 1 = player, 2 = ctx's linked
   actor when it is an active kind-13 actor, 3 = self, 4 = none.
   regargs: c=EAX ctx=ECX; self is the stack arg */
void *r2_PickTarget(const R2Cond *c, R2Ctx *ctx, void *self)
{
    switch (c->kind) {
    case 1:
        return r2_player;
    case 2:
        if (ctx->mode0F8 == 1 && (ctx->link104->flags0C & 1) && ctx->link104->kind04 == 0xD)
            return ctx->link104;
        return 0;
    case 3:
        return self;
    case 4:
        return 0;
    default:
        for (;;) ;
    }
}
