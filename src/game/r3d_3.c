/* Area r3d: game functions in 0x00180000..0x0018FFFF (r3d_3). Names inferred. */
#include "r3d.h"

/* 0x0018B620: clear the fifteen 0x44-byte records at 0x003FF738. */
void r3d_ClearRecs18B620(void)
{
    int i;

    R3D_ZERO(r3c_recs3FF738, sizeof(r3c_recs3FF738));
    for (i = 0; i < 15; i++)
        r3c_recs3FF738[i].i0 = 0;
}

/* 0x001853E0: clear the eight 0xA0-byte records at 0x003FE488. */
void r3d_ClearRecs1853E0(void)
{
    int i;

    R3D_ZERO(r3c_recs3FE488, sizeof(r3c_recs3FE488));
    for (i = 0; i < 8; i++)
        r3c_recs3FE488[i].i0 = 0;
}

/* 0x00185630: free the 0x003FE488 record whose id matches (hang if none) and clear o->work278. */
int r3d_Release185630(int id, R3cObj *o)
{
    int i;

    for (i = 0; i < 8; i++)
        if (r3c_recs3FE488[i].i0 == id)
            break;
    if (i >= 8)
        for (;;)
            ;
    r3c_recs3FE488[i].i0 = 0;
    o->work278 = 0;
    return 1;
}

/* 0x00184610: fail while any active 0x003FE3B0 record's actor is in state 1; else release the
   current object's handle +0x138 and succeed. */
int r3d_Release184610(void)
{
    R3cObj *o = sub_00100110();
    int i;

    for (i = 0; i < 4; i++)
        if (r3c_recs3FE3B0[i].i0 && ((R3cObj *)(intptr_t)r3c_recs3FE3B0[i].i8)->state50 == 1)
            return 0;
    if (o->i138 != -1) {
        sub_00048250(o->i138);
        o->i138 = -1;
    }
    return 1;
}

/* 0x001827E0: detach a live object: clear the 0x003FE368 block, act's work pointer and o's live flag. */
int r3d_Detach1827E0(R3cObj *o, R3cObj *act)
{
    if (!(o->flags0C & 1))
        return 0;
    r3c_obj3FE368 = 0;
    r3c_act3FE36C = 0;
    r3c_i3FE37C = 0;
    r3c_i3FE378 = 0;
    r3c_f3FE380 = 0.0f;
    r3c_f3FE384 = 0.0f;
    act->work278 = 0;
    sub_0001EB80(o);
    o->flags0C &= ~1u;
    o->flags10 |= 0xD;
    return 1;
}

/* 0x00184670: detach a live object listed in the 0x003FE3B0 records (0 when not listed). */
int r3d_Detach184670(R3cObj *o, R3cObj *act)
{
    int i;

    if (!(o->flags0C & 1))
        return 0;
    for (i = 0; i < 4; i++)
        if (r3c_recs3FE3B0[i].i0 == (int32_t)(intptr_t)o)
            break;
    if (i >= 4)
        return 0;
    sub_00033B30(o);
    act->work278 = 0;
    sub_0001EB80(o);
    o->flags0C &= ~1u;
    o->flags10 |= 0xD;
    return 1;
}

/* 0x00189D30: run o's kind-7 component mode handler; while live advance its timers and call its tick. */
void r3d_Update189D30(R3cObj *o)
{
    R3dComp7 *c = (R3dComp7 *)sub_0001D960(o, 7);
    R3cCompFn fn;

    if (!c)
        for (;;)
            ;
    fn = c->fns88[c->mode60];
    if (!fn)
        for (;;)
            ;
    fn(o, c);
    if (o->flags0C & 1) {
        c->f6C += r3c_frameSeconds;
        c->f70 -= r3c_frameSeconds;
        c->fn7C(o, c);
    }
}

/* 0x0018AD00: finish (0x000ED780) when act->f70 runs out; else rise by one frame unit (motion flag
   0x10000) or by 1 - f70, and reset act's timers. */
void r3d_Rise18AD00(R3cObj *obj, R3cObj *act)
{
    if (0.0f >= act->f70) {
        sub_000ED780(obj);
        return;
    }
    if (act->p74->i08 & 0x10000)
        obj->pos60[1] += r3c_frameUnits;
    else
        obj->pos60[1] += 1.0f - act->f70;
    act->flags4C = 0;
    act->f50 = 0.0f;
    act->f54 = 0.0f;
    act->f58 = 1.0f;
}

/* 0x00188240: run condition 4 (act flag byte bit 0) or 3, reset the work vector at +0x20 to
   (0, 0, 0, 1), set obj flags 5 and work flag 0x1000. */
void r3d_Reset188240(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;
    R3cWork *v;

    sub_001456E0(obj, act, (act->b20 & 1) ? 4 : 3, 0);
    v = act->work278;
    v->f28 = 0.0f;
    v->f24 = 0.0f;
    v->f20 = 0.0f;
    v->f2C = 1.0f;
    obj->flags10 |= 5;
    w->flags18 |= 0x1000;
}

/* 0x001882F0: as 0x00188240 with condition 1 (act flag byte bit 0) or 0. */
void r3d_Reset1882F0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;
    R3cWork *v;

    sub_001456E0(obj, act, (act->b20 & 1) ? 1 : 0, 0);
    v = act->work278;
    v->f28 = 0.0f;
    v->f24 = 0.0f;
    v->f20 = 0.0f;
    v->f2C = 1.0f;
    obj->flags10 |= 5;
    w->flags18 |= 0x1000;
}

/* 0x00185890: retarget act to the player: directly, or (work flag 0x4000) once its current
   target is gone or no longer live, switching the flag to 0x8000. */
void r3d_Retarget185890(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;
    uint32_t f = w->flags18;
    R3cObj *t;

    if (f & 0x4000) {
        if (act->iF8 == 1) {
            t = act->p104;
            if (!t || !(t->flags0C & 1)) {
                w->flags18 = (f & ~0x4000u) | 0x8000;
                act->p104 = (R3cObj *)g_playerObj;
                act->iF8 = 1;
            }
        }
        return;
    }
    act->p104 = (R3cObj *)g_playerObj;
    act->iF8 = 1;
}

/* 0x001895A0: reset the 0x003FEAB8 block (mode 5, fresh time base) and free both handles. */
void r3d_Reset1895A0(void)
{
    r3c_s3FEAB8 = 5;
    r3c_f3FEAC0 = 0.0f;
    r3c_f3FEAC4 = 0.0f;
    r3c_f3FEAC8 = sub_001065B0();
    r3c_f3FEABC = 0.0f;
    if (r3c_i3FEB10)
        sub_00189510(r3c_i3FEB10);
    if (r3c_i3FEB14)
        sub_00189510(r3c_i3FEB14);
    r3c_i3FEB10 = 0;
    r3c_i3FEB14 = 0;
}

/* 0x0018F6F0: detach a live object: clear act's 0x24-byte motion block and pointer. */
int r3d_Detach18F6F0(R3cObj *o, R3cObj *act)
{
    R3cBlk74 *m;

    if (!(o->flags0C & 1))
        return 0;
    m = act->p74;
    memset(m, 0, 0x24);
    m->flags = 0;
    sub_00033B30(o);
    act->p74 = 0;
    sub_0001EB80(o);
    o->flags0C &= ~1u;
    o->flags10 |= 0xD;
    return 1;
}

/* 0x00181E80: detach a live object listed first in a 0x003FE2D8 pair (0 when not listed). */
int r3d_Detach181E80(R3cObj *o, R3cObj *act)
{
    int i;
    R3dPair *p;

    if (!(o->flags0C & 1))
        return 0;
    for (i = 0; i < 4; i++)
        if (b7c_idRecs3FE2D8[i].a == o)
            break;
    if (i >= 4)
        return 0;
    p = &b7c_idRecs3FE2D8[i];
    p->a = 0;
    p->owner = 0;
    act->work278 = 0;
    sub_0001EB80(o);
    o->flags0C &= ~1u;
    o->flags10 |= 0xD;
    return 1;
}

/* 0x00187DF0: run condition 0x40, reset the work vectors (+0x20 to (0, 0, 0, 1), +0x88/+0x8C
   and +0x94/+0x98 to 0) and clear obj flag 0x20 (+0x0C). */
void r3d_Reset187DF0(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;
    R3cWork *v;

    sub_001456E0(obj, act, 0x40, 0);
    v = act->work278;
    v->f28 = 0.0f;
    v->f24 = 0.0f;
    v->f20 = 0.0f;
    v->f2C = 1.0f;
    w->f88 = 0.0f;
    w->f8C = 0.0f;
    w->f94 = 0.0f;
    w->f98 = 0.0f;
    obj->flags0C &= ~0x20u;
}

/* 0x0018A920: spawn burst for o: start part 0, fire effect 0xDF at o and emit particle
   kind 0xB from o's first sub-node.
   regargs: o=ESI. */
void r3d_Burst18A920(R3cObj *o)
{
    float v[4];
    R3cObj *n;

    sub_00035D80(o, 0, 1);
    sub_000494D0(0xDF, o->pos60, 0);
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    n = (R3cObj *)sub_0001D0F0(o, 1);
    sub_000C4D30(o, 0xB, 30.0f, 2, 20.0f, 0.5f, 5.0f, &n->f70, v, v);
}

/* 0x0018E900: clear obj flags 5, store the handle of effect 0x8B in the motion block and
   set its vertical speed toward the player's height (0.2667 per frame unit). */
void r3d_Follow18E900(R3cObj *obj, R3cObj *act)
{
    R3dBlk74 *m = (R3dBlk74 *)act->p74;
    float d, v;

    obj->flags10 &= 0xFFFFFFFA;
    m->s02 = (int16_t)sub_000494D0(0x8B, obj->pos60, 1);
    d = obj->pos60[1] - ((R3dCtx *)((R3cObj *)g_playerObj)->m20)->banksC4[2].f74;
    v = r3c_frameUnits * 0.26666668f;
    m->f2C = v;
    if (d > 0.0f)
        m->f2C = 0.0f - v;
}

/* 0x0018CA90: spin step: set the motion rate (pi per second) and flags 0xC, clear obj flag
   0x20, advance obj->f54 by pi (wrapping past pi), scale +0x80 by -2 and clear +0x84 and the
   motion value +0x08.
   regargs: act=EAX obj=ESI. */
void r3d_Spin18CA90(R3cObj *act, R3cObj *obj)
{
    R3dBlk74 *m = (R3dBlk74 *)act->p74;

    m->f04 = r3c_frameSeconds * 3.1415927f;
    m->flags |= 0xC;
    obj->flags10 &= ~0x20u;
    obj->f54 += 3.1415927f;
    if (obj->f54 > 3.1415927f)
        obj->f54 -= 6.2831855f;
    sub_001ADBA0(&obj->f80, &obj->f80, -2.0f);
    obj->f84 = 0.0f;
    m->f08 = 0.0f;
}

/* 0x001842F0: run condition 1, pick light 0x325 (work flag 2) / 0x326 (work flag 1, each
   consumed) / 0x324 and store its handle at act+0x6C. */
void r3d_Light1842F0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;
    uint32_t f;
    int id;

    sub_001456E0(obj, act, 1, 0);
    f = w->flags04;
    if (f & 2) {
        w->flags04 = f & ~2u;
        id = 0x325;
    } else if (f & 1) {
        w->flags04 = f & ~1u;
        id = 0x326;
    } else {
        id = 0x324;
    }
    ((R3dAct *)act)->h6C = sub_00049700(id, 0x80, 0x80, 0x80, obj->pos60, 0, 500.0f, 0);
}

/* 0x00181E00: detach a live object listed second in a 0x003FE2D8 pair (0 when not listed). */
int r3d_Detach181E00(R3cObj *o, R3cObj *act)
{
    int i;

    if (!(o->flags0C & 1))
        return 0;
    sub_00033B30(o);
    for (i = 0; i < 4; i++)
        if (b7c_idRecs3FE2D8[i].b == o)
            break;
    if (i >= 4)
        return 0;
    o->flags10 |= 0xD;
    o->flags0C &= ~1u;
    b7c_idRecs3FE2D8[i].b = 0;
    act->work278 = 0;
    sub_0001EB80(o);
    return 1;
}

/* 0x00188C00: start a pending hold (state 1 -> 2): snap its object to pos, reset its timer and
   collapse its matrix (identity rows scaled by the hold's factors times the reset timer). */
void r3d_Hold188C00(R3dHold *h, const float *pos)
{
    R3dHold2 *s;
    float *m;
    int i;

    if (!h || h->state != 1)
        return;
    s = h->pC;
    if (!s)
        return;
    m = s->m44;
    h->state = 2;
    s->f14 = 0.0f;
    sub_000F5D40(s->obj->pos60, pos);
    h->f4 = 0.0f;
    sub_001AD940(m);
    for (i = 0; i < 3; i++, m += 4)
        sub_001ADBA0(m, m, s->f24[i] * s->f14);
}

/* 0x00188EB0: advance the work blend (+0x14 by +0x1C, which grows by +0x18) up to 1; when the
   counter +0x0C reaches +0x20 enter state 0 with the blend at 1, else count up. */
void r3d_Blend188EB0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    w->f14 += w->f1C;
    w->f1C = w->f18 + w->f1C;
    if (w->f14 > 1.0f)
        w->f14 = 1.0f;
    if (w->u0C.f >= w->f20) {
        sub_00113040(obj, act, 0);
        w->f14 = 1.0f;
        return;
    }
    w->u0C.f += 1.0f;
}
