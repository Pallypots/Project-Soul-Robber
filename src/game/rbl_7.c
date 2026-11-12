/* Area rbl: boss and minion set-up functions (0x0017F050 and 0x00181E00 families).
   Names inferred. */
#include "rbl.h"

/* 0x001824F0: set up record k (0..3) of 0x003FE2D8 for body o / actor a: links them,
   flags the body, detaches and re-attaches its units (0x0001EB80, 0x0001E9B0 with
   12/5/17, 0x0001EBF0 with 3), installs callbacks and state tables, takes health from the
   stat table, sizes the body (0x000F5D60), sets the rate 2.5 (0x0001EEC0), scale 1, clears
   the record's vector and enters state 0. Returns 1. A missing body or k >= 4 hangs.
   Stack args (o a k). */
int rbl_BossInit1824F0(RblBody *o, RblBossAct *a, int k)
{
    RblRec24 *r;
    float hp;

    if (o == 0)
        for (;;) ;
    if (k >= 4)
        for (;;) ;
    r = &b7c_idRecs3FE2D8[k];
    a->work278 = r;
    r->obj04 = o;
    o->flags0C = (o->flags0C & ~0xE0u) | 0x201;
    o->flags10 |= 0x44D;
    sub_0001EB80(o);
    sub_0001E9B0(a80_ctx42C8E4, o, 0xC, 5, 0x11);
    sub_0001EBF0(o, 3);
    a->tab28C = rbl_states32B870;
    a->tab290 = rbl_states32B874;
    a->fn27C = sub_00181E00;
    a->fn288 = sub_00181EF0;
    a->fn29C = sub_00182060;
    hp = sub_00171D50(o->i04, o->i08, 0);
    a->maxHp270 = hp;
    a->hp274 = hp;
    o->i124 = 0;
    sub_000F5D60(o, 1.0f, -25.0f, 9.9f, rbl_place27A8E4);
    a->f28 = 8.0f;
    a->f2C = -18.0f;
    sub_0001EEC0(o, 2.5f);
    o->scale70[2] = 1.0f;
    o->scale70[1] = 1.0f;
    o->scale70[0] = 1.0f;
    r->v18[0] = 0.0f;
    r->v18[1] = 0.0f;
    r->v18[2] = 0.0f;
    sub_00113040(o, a, 0);
    return 1;
}

/* 0x001807D0: set up record k (0..2) of 0x003FE0C0 for body o / actor a (returns 0 for
   any other k): links them, installs callbacks and state tables, flags the body, takes
   the health from 0x003FE09C, scale 1, sizes the body (0x000F5D60), clears the record's
   timers and vectors (+0x30 = 1) and enters state 0. Returns 1. Stack args (o a k).
   The original stores body +0x124 = 0 twice; written once. */
int rbl_BossInit1807D0(RblBody *o, RblBossAct *a, int k)
{
    RblRec58 *r;

    if (k < 0 || k >= 3)
        return 0;
    r = &r3e_recs3FE0C0[k];
    a->work278 = r;
    r->obj00 = o;
    r->act04 = a;
    r->i0C = k;
    a->tab28C = rbl_states32B818;
    a->tab290 = rbl_states32B82C;
    a->fn27C = sub_0017F050;
    a->fn288 = sub_001806E0;
    a->fn29C = sub_0017F0F0;
    o->flags0C = (o->flags0C & ~0xE0u) | 0x203;
    o->i124 = 0;
    o->flags10 |= 0x44D;
    a->hp274 = rbl_hp3FE09C[k];
    o->scale70[2] = 1.0f;
    o->scale70[1] = 1.0f;
    o->scale70[0] = 1.0f;
    o->f7C = 1.0f;
    sub_000F5D60(o, 1.0f, -21.5f, 7.2f, rbl_place27A768);
    a->f28 = -8.0f;
    a->f2C = -28.0f;
    a->i24 = 5;
    r->f1C = 0.0f;
    r->f20 = 0.0f;
    r->v34[0] = 0.0f;
    r->v34[1] = 0.0f;
    r->v34[2] = 0.0f;
    r->i18 = 0;
    r->v24[0] = 0.0f;
    r->v24[1] = 0.0f;
    r->v24[2] = 0.0f;
    r->v24[3] = 1.0f;
    sub_00113040(o, a, 0);
    return 1;
}
