/* Area r3c: game functions in 0x00180000..0x0018FFFF (r3c_3). Names inferred. */
#include <string.h>
#include "r3c.h"

/* 0x00181730: start animation 5 and reset the work block. */
void r3c_Start181730(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    sub_000832D0(obj->pa30, 5);
    w->u0C.s = 0;
    w->p34->flags90 &= ~0x40u;
    obj->flags10 |= 0xD;
    w->i14 = 0;
}

/* 0x001827A0: put the saved object back to state 0 at the origin. */
void r3c_Reset1827A0(void)
{
    sub_00113040(r3c_obj3FE368, r3c_act3FE36C, 0);
    sub_000832D0(r3c_obj3FE368->pa30, 0);
    sub_000F5D40(r3c_obj3FE368->pos60, r3c_vec27A95C);
}

/* 0x00182FE0: clear the saved object block. */
void r3c_Clear182FE0(void)
{
    r3c_obj3FE368 = 0;
    r3c_act3FE36C = 0;
    r3c_i3FE37C = 0;
    r3c_i3FE378 = 0;
    r3c_f3FE380 = 0.0f;
    r3c_f3FE384 = 0.0f;
}

/* 0x001831D0: advance the angle obj->f54 by half a degree, wrapping at pi. */
void r3c_Spin1831D0(R3cObj *obj)
{
    obj->f54 += r3c_halfDegree32B8E8;
    if (obj->f54 >= 3.1415927f)
        obj->f54 -= 6.2831855f;
}

/* 0x00183B40: run 0x001456E0 mode 0 on obj and on its linked object. */
void r3c_Both183B40(R3cObj *obj, void *act)
{
    R3cObj *link = obj->p3C;

    sub_001456E0(obj, act, 0, 0);
    sub_001456E0(link, act, 0, 0);
}

/* 0x00183B70: run 0x001456E0 mode 1 on obj and on its linked object. */
void r3c_Both183B70(R3cObj *obj, void *act)
{
    R3cObj *link = obj->p3C;

    sub_001456E0(obj, act, 1, 0);
    sub_001456E0(link, act, 1, 0);
}

/* 0x00183BA0: run 0x001456E0 mode 2 on obj and on its linked object. */
void r3c_Both183BA0(R3cObj *obj, void *act)
{
    R3cObj *link = obj->p3C;

    sub_001456E0(obj, act, 2, 0);
    sub_001456E0(link, act, 2, 0);
}

/* 0x00183BD0: run 0x001456E0 mode 1 on obj and its linked object, then set obj->f54. */
void r3c_Both183BD0(R3cObj *obj, void *act)
{
    R3cObj *link = obj->p3C;

    sub_001456E0(obj, act, 1, 0);
    sub_001456E0(link, act, 1, 0);
    obj->f54 = r3c_f32BCA4;
}

/* 0x00184490: leave to state 2 when work flag 4 is clear and act->f74 has run out. */
void r3c_Timeout184490(void *obj, R3cObj *act)
{
    if (!(act->work278->flags04 & 4) && act->f74 <= 0.0f) {
        sub_001134B0(act);
        sub_00113040(obj, act, 2);
    }
}

/* 0x001844D0: leave to state 1 when work flag 4 is set or the animation finished. */
void r3c_Done1844D0(R3cObj *obj, R3cObj *act)
{
    if ((act->work278->flags04 & 4) || sub_000833E0(obj->anim30)) {
        sub_001134B0(act);
        sub_00113040(obj, act, 1);
    }
}

/* 0x00185500: point component 6 of o at target t. */
void r3c_SetTarget185500(void *o, R3cObj *t)
{
    R3cObj *c = sub_0001D960(o, 6);

    if (c->kind00 != 6)
        for (;;)
            ;
    c->p104 = t;
    c->iF8 = 1;
    c->work278->flags18 |= 0x4000;
}

/* 0x001861C0: is the work timer inside [c->f10, c->f14]? */
int r3c_InRange1861C0(void *obj, R3cObj *act, const R3cRange *c)
{
    R3cWork *w = act->work278;

    return w->f1C >= c->lo && c->hi >= w->f1C;
}

/* 0x001863B0: test work flag bit 0 against the wanted state c->i08. */
int r3c_Flag1863B0(void *obj, R3cObj *act, const R3cRange *c)
{
    R3cWork *w = act->work278;

    if (c->i08 == 0)
        return ~w->flags18 & 1;
    return w->flags18 & 1;
}

/* 0x00186430: true unless the player state is 4, 5, 6 or 8. */
int r3c_StateOk186430(void)
{
    int st = PlayerObj_GetState((PlayerObj *)&g_stats);

    if (st == 4 || st == 5 || st == 6 || st == 8)
        return 0;
    return 1;
}

/* 0x001867C0: run 0x001456E0 mode 0 and reset the work vector to (0,0,0,1). */
void r3c_Reset1867C0(void *obj, R3cObj *act)
{
    R3cWork *w;

    sub_001456E0(obj, act, 0, 0);
    w = act->work278;
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f20 = 0.0f;
    w->f2C = 1.0f;
}

/* 0x00188F90: reset the block at 0x003FEAB8. */
void r3c_Reset188F90(void)
{
    r3c_s3FEAB8 = 5;
    r3c_f3FEAC0 = 0.0f;
    r3c_f3FEAC4 = 0.0f;
    r3c_f3FEAC8 = sub_001065B0();
    r3c_f3FEABC = 0.0f;
}

/* 0x00189A00: create the object kind 0xB once and remember it. */
void r3c_Create189A00(void)
{
    R3cObj *o;

    if (r3c_i3FF584 == 0) {
        o = sub_0001F210(0xB, 0);
        r3c_obj3FF57C = o;
        r3c_i3FF584 = o->i08;
        sub_0001DA40(o);
    }
}

/* 0x00189A30: destroy the object made by 0x00189A00. */
void r3c_Destroy189A30(void)
{
    if (r3c_i3FF584 != 0) {
        sub_000ED560(5);
        sub_00020170(r3c_obj3FF57C);
        r3c_obj3FF57C = 0;
        r3c_i3FF584 = 0;
    }
}

/* 0x00189CF0: ask component 7 whether o may go; if so deactivate o. */
int r3c_TryEnd189CF0(R3cObj *o)
{
    R3cObj *c = sub_0001D960(o, 7);

    if (c->fn78(o, c)) {
        o->flags0C &= ~1u;
        sub_0001EB80(o);
        return 1;
    }
    return 0;
}

/* 0x00189E50: run 0x0001B450 with o's timer when it is positive. */
int r3c_Run189E50(R3cObj *o, void *a, void *b)
{
    if (0.0f >= o->fE8)
        return 0;
    return sub_0001B450(a, o->fE8, b, &o->fF0) != 0;
}

/* 0x00189E90: call the +0x80 callback of o's own component. */
int r3c_Call189E90(R3cObj *o, void *arg)
{
    R3cObj *c;

    if (o == 0)
        for (;;)
            ;
    c = sub_0001D960(o, sub_000EE5F0(o));
    if (c == 0)
        for (;;)
            ;
    return c->fn80(o, c, arg);
}

/* 0x0018A2D0: drop b's +0x74 block when it is idle. */
int r3c_Drop18A2D0(void *a, R3cObj *b)
{
    R3cBlk74 *m = b->p74;

    if (m != 0 && m->i04 == 0) {
        m->flags = 0;
        m->i04 = 0;
        m->i08 = 0;
        m->f0C = 0.0f;
        b->p74 = 0;
        return 1;
    }
    return 0;
}

/* 0x0018D150: grow a->f84 when block flag 0x10 is set; notify 0x00189DA0 when a has flags 0x18. */
void r3c_Grow18D150(R3cObj *a, R3cObj *b)
{
    if (b->p74->flags & 0x10)
        a->f84 += 0.02f;
    if (a->flags128 & 0x18)
        sub_00189DA0(a, b, 2);
}

/* 0x0018D3C0: take the first free 0x18-byte record at 0x003FFC78 (bit 0 = used). */
R3cRec18 *r3c_Alloc18D3C0(void)
{
    int i;
    R3cRec18 *r;

    for (i = 0; i < 15; i++) {
        if (!(r3c_recs3FFC78[i].w[0] & 1)) {
            r = &r3c_recs3FFC78[i];
            r->w[0] = 0;
            r->w[1] = 0;
            r->w[2] = 0;
            r->w[3] = 0;
            r->w[4] = 0;
            r->w[5] = 0;
            r->w[0] |= 1;
            return r;
        }
    }
    return 0;
}

/* 0x0018DEA0: update through 0x0018DA80, then notify 0x00189DA0 when block flag 4 is set. */
void r3c_Update18DEA0(void *a, R3cObj *b)
{
    R3cBlk74 *m = b->p74;

    sub_0018DA80(a, b);
    if ((uint8_t)m->flags & 4)
        sub_00189DA0(a, b, 1);
}

/* 0x0018E640: if component 7 of o holds key k, clear it and release o. */
int r3c_Release18E640(void *o, int k)
{
    R3cObj *c;

    if (o == 0 || (c = sub_0001D960(o, 7)) == 0 || c->p74->i04 != k)
        return 0;
    c->p74->i04 = 0;
    return sub_000ED780(o);
}

/* 0x0018E680: is o an idle type-5 object whose component 7 is of kind 2? */
int r3c_IsKind18E680(R3cObj *o)
{
    R3cObj *c;

    if (o == 0 || o->type04 != 5 || o->i08 != 0)
        return 0;
    c = sub_0001D960(o, 7);
    if (c == 0)
        for (;;)
            ;
    return *(int16_t *)&c->p74->flags == 2;
}

/* 0x0018E7C0: clear component 7's key and notify 0x00189DA0. */
void r3c_Clear18E7C0(void *o)
{
    R3cObj *c;

    if (o != 0 && (c = sub_0001D960(o, 7)) != 0) {
        c->p74->i04 = 0;
        sub_00189DA0(o, c, 7);
    }
}

/* 0x0018F650: is the current object's component 7 in mode 1 or 2? */
int r3c_Mode18F650(void)
{
    R3cObj *o = sub_00100110()->p1C4;
    int m;

    if (o != 0 && (o->flags0C & 1)) {
        m = sub_0001D960(o, 7)->i60;
        if (m == 1 || m == 2)
            return 1;
    }
    return 0;
}

/* 0x001811A0: start animation 1, copy act->i270 to +0x274 and reset the work block. */
void r3c_Start1811A0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    sub_000832D0(obj->pa30, 1);
    act->i274 = act->i270;
    w->p34->flags90 &= ~0x40u;
    w->u0C.s = 0;
}

/* 0x00181610: start animation 2 and reset the work block. */
void r3c_Start181610(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    w->u0C.s = 0;
    w->f10 = 0.0f;
    sub_000832D0(obj->pa30, 2);
    obj->flags10 |= 0xD;
    w->i14 = 0;
}

/* 0x00183320: move the saved actor at 0x003FE390 out of state 0 (k=0: state 1, k=1: state 2). */
void r3c_Wake183320(int k)
{
    R3cObj *act = r3c_act3FE390;

    if (act->state50 != 0)
        return;
    if (k == 0)
        sub_00113040(r3c_obj3FE38C, act, 1);
    else if (k == 1)
        sub_00113040(r3c_obj3FE38C, act, 2);
}

/* 0x00184260: renormalise the object's matrix rows and rebuild them by cross products. */
void r3c_Ortho184260(R3cObj *o)
{
    float *m;

    sub_001AD7E0(o->m20, o->m20);
    sub_001AD7E0(o->m20 + 4, o->m20 + 4);
    m = o->m20;
    sub_001ADA60(m + 8, m, m + 4);
    m = o->m20;
    sub_001ADA60(m, m + 4, m + 8);
}

/* 0x001842B0: run 0x001456E0 mode 0 and set a random wait of 7..10 frames. */
void r3c_Wait1842B0(void *obj, R3cObj *act)
{
    sub_001456E0(obj, act, 0, 0);
    act->f74 = (float)sub_001C7EE1() * 3.0518509e-05f * 3.0f + 7.0f;
}

/* 0x00189560: reset the block at 0x003FEAB8 including the two words at 0x003FEB10. */
void r3c_Reset189560(void)
{
    r3c_s3FEAB8 = 5;
    r3c_f3FEAC0 = 0.0f;
    r3c_f3FEAC4 = 0.0f;
    r3c_f3FEAC8 = sub_001065B0();
    r3c_f3FEABC = 0.0f;
    r3c_i3FEB10 = 0;
    r3c_i3FEB14 = 0;
}

/* 0x00189DA0: switch component c to mode k and run that mode's entry callback. */
int r3c_SetMode189DA0(void *o, R3cObj *c, int k)
{
    R3cCompFn fn;

    c->i64 = c->i60;
    c->i60 = k;
    c->i68 = 0;
    c->f6C = 0.0f;
    fn = c->fns84[k];
    if (fn == 0)
        for (;;)
            ;
    return fn(o, c);
}

/* 0x0018C400: take the first free 0x20-byte record at 0x003FFB38 (bit 0 = used). */
R3cRec20 *r3c_Alloc18C400(void)
{
    int i;
    R3cRec20 *r;

    for (i = 0; i < 10; i++) {
        if (!(r3c_recs3FFB38[i].w[0] & 1)) {
            r = &r3c_recs3FFB38[i];
            r->w[0] = 0;
            r->w[1] = 0;
            r->w[2] = 0;
            r->w[3] = 0;
            r->w[4] = 0;
            r->w[5] = 0;
            r->w[6] = 0;
            r->w[7] = 0;
            r->w[0] |= 1;
            return r;
        }
    }
    return 0;
}

/* 0x0018DE10: notify 0x00189DA0 when a has flags 6; grow a->f84 when block flag 0x10 is set. */
void r3c_Grow18DE10(R3cObj *a, R3cObj *b)
{
    if (a->flags128 & 6)
        sub_00189DA0(a, b, 1);
    if (b->p74->flags & 0x10)
        a->f84 += 0.02f;
}

/* 0x0018E6C0: set o's uniform scale to v and component 7's +0x2C to -4v. */
void r3c_Scale18E6C0(R3cObj *o, float v)
{
    R3cComp2C *c = (R3cComp2C *)sub_0001D960(o, 7);

    if (c == 0)
        for (;;)
            ;
    o->f70 = v;
    o->f74 = v;
    o->f78 = v;
    o->f7C = 0.0f;
    c->f2C = v * -4.0f;
}

/* 0x0018E8B0: set c's rate to one second and start effect 0x8A at obj. */
void r3c_Start18E8B0(R3cObj *obj, R3cObj *c)
{
    c->f70 = 60.0f / r3c_frameUnits * r3c_frameSeconds;
    obj->flags10 &= ~5u;
    *((int16_t *)&c->p74->flags + 1) = (int16_t)sub_000494D0(0x8A, obj->pos60, 1);
}

/* 0x0018E980: mark obj, set block kind 2 and start effect 0x8A/0x8B once. */
void r3c_Start18E980(R3cObj *obj, R3cObj *c)
{
    int16_t *blk;

    obj->flags0C |= 0x40;
    obj->flags10 &= ~5u;
    blk = (int16_t *)c->p74;
    if (blk[1] < 0) {
        blk[0] = 2;
        blk[1] = (int16_t)sub_000494D0((c->b20 & 1) + 0x8A, obj->pos60, 1);
    } else {
        blk[0] = 2;
    }
}

/* 0x0018F760: set or clear o's flag 1 by 0x000CF6C0 in modes 1 and 2, then run 0x000FB4D0. */
void r3c_Update18F760(R3cObj *o, R3cObj *c)
{
    int m = c->i60;

    if (m == 1 || m == 2) {
        if (Stats_HasEFC() > 0) {
            o->flags10 |= 1;
            sub_000FB4D0(o);
            return;
        }
        o->flags10 &= ~1u;
    }
    sub_000FB4D0(o);
}

/* 0x00183360: detach the saved pair 0x003FE38C/0x003FE390 and deactivate o. */
int r3c_Detach183360(R3cObj *o, R3cObj *act)
{
    if (!(o->flags0C & 1))
        return 0;
    r3c_obj3FE38C = 0;
    r3c_act3FE390 = 0;
    act->work278 = 0;
    sub_0001EB80(o);
    o->flags0C &= ~1u;
    o->flags10 |= 0x44D;
    return 1;
}

/* 0x00185DC0: when 0x00145940 accepts c's range, apply c's value through 0x001459D0. */
void r3c_Apply185DC0(void *obj, R3cObj *act, const R3cRange *c)
{
    R3cWork *w = act->work278;

    if (sub_00145940(obj, w->f30, w->f38, c->lo, c->hi))
        sub_001459D0(obj, w->f30, w->f38, c->val);
}

/* Holder released by 0x00189510. */
typedef struct R3cHold { R3cObj *obj; float f4; int32_t i8; struct R3cHold2 *pC; } R3cHold;
typedef struct R3cHold2 { R3cObj *obj; int32_t i4; uint8_t unk08[0x44 - 8]; int32_t i44, i48; } R3cHold2;

/* 0x00189510: release the object of h's sub-holder and clear both. */
void r3c_Release189510(R3cHold *h)
{
    if (h == 0 || h->obj == 0)
        return;
    if (h->pC != 0) {
        if (h->pC->obj != 0)
            sub_000ED780(h->pC->obj);
        if (h->pC != 0) {
            h->pC->obj = 0;
            h->pC->i4 = 0;
            h->pC->i44 = 0;
            h->pC->i48 = 0;
        }
    }
    h->obj = 0;
    h->f4 = 0.0f;
    h->i8 = 0;
    h->pC = 0;
}

/* 0x0018AB00: reset o's display state (flags, colour 0,0,0,1, mode 2). */
void r3c_Reset18AB00(R3cObj *o)
{
    o->flags0C = (o->flags0C & ~0xA0u) | 0x40;
    o->fD8 = 0.0f;
    o->fDC = 0.0f;
    o->fE0 = 0.0f;
    o->fE4 = 1.0f;
    o->iF0 = 2;
}

/* 0x0018B660: aim component 7 of o at target x from point v with speed -k. */
void r3c_Aim18B660(void *o, R3cObj *x, const float *v, float k)
{
    R3cBlk74 *b = sub_0001D960(o, 7)->p74;

    b->obj04 = x;
    b->i08 = x->i130;
    sub_000F5D40(b->v24, v);
    sub_000F5D40(b->v34, v);
    b->f10 = 0.0f - k;
}

/* 0x00183620: reset o's rotation to identity, clear the saved timers and restart animation 1. */
void r3c_Reset183620(R3cObj *o)
{
    o->f50 = 0.0f;
    o->f54 = 0.0f;
    o->f58 = 0.0f;
    o->f5C = 1.0f;
    r3c_f3FE394 = 0.0f;
    r3c_f3FE3A0 = 0.0f;
    r3c_i3FE398 = 0;
    sub_000832D0(o->pa30, 1);
    sub_0001D610(o);
}

/* 0x001848A0: set the current object's +0x1E8 to 45 and reset the work timer (15 per second). */
void r3c_Reset1848A0(void *obj, R3cObj *act)
{
    R3cObj *p = sub_00100110();
    R3cWork *w = act->work278;

    p->f1E8 = 45.0f;
    w->f18 = 15.0f / r3c_framesPerSecond;
    w->f10 = 0.0f;
    p->s1FC = 0;
    w->s32 = 0;
}

/* 0x00185130: clear the four 0x34-byte records at 0x003FE3B0 and the word after them. */
void r3c_Clear185130(void)
{
    r3c_recs3FE3B0[0].i0 = 0;
    r3c_recs3FE3B0[0].i4 = 0;
    r3c_recs3FE3B0[0].i8 = 0;
    r3c_recs3FE3B0[0].iC = 0;
    r3c_recs3FE3B0[1].i0 = 0;
    r3c_recs3FE3B0[1].i4 = 0;
    r3c_recs3FE3B0[1].i8 = 0;
    r3c_recs3FE3B0[1].iC = 0;
    r3c_recs3FE3B0[2].i0 = 0;
    r3c_recs3FE3B0[2].i4 = 0;
    r3c_recs3FE3B0[2].i8 = 0;
    r3c_recs3FE3B0[2].iC = 0;
    r3c_recs3FE3B0[3].i0 = 0;
    r3c_recs3FE3B0[3].i4 = 0;
    r3c_recs3FE3B0[3].i8 = 0;
    r3c_recs3FE3B0[3].iC = 0;
    r3c_i3FE480 = 0;
}

/* 0x00188CA0: deactivate o, clear and detach act's work block. */
int r3c_Detach188CA0(R3cObj *o, R3cObj *act)
{
    R3cWork *w = act->work278;

    if (!(o->flags0C & 1))
        return 0;
    if (w != 0) {
        w->flags00 = 0;
        w->flags04 = 0;
        w->f44 = 0.0f;
        w->f48 = 0.0f;
    }
    sub_0001EB80(o);
    act->work278 = 0;
    o->flags0C &= ~1u;
    o->flags10 |= 0xD;
    return 1;
}

/* 0x0018D230: copy b's vector into a, update, and switch b to mode 2 when the player is beyond 80. */
void r3c_Follow18D230(R3cObj *a, R3cObj *b)
{
    sub_000F5D40(&a->f80, &b->flags4C);
    sub_0018CB60(a, b);
    if (sub_001B2770(a->pos60, ((R3cObj *)g_playerObj)->pos60) > 80.0f)
        sub_00189DA0(a, b, 2);
}

/* 0x0018DD70: update; when block flag 4 is set either grow a->f84 (flag 8) or switch to mode 1. */
void r3c_Update18DD70(R3cObj *a, R3cObj *b)
{
    R3cBlk74 *m = b->p74;
    uint32_t f;

    sub_0018DA80(a, b);
    f = m->flags;
    if (f & 4) {
        if (f & 8)
            a->f84 += 0.02f;
        else
            sub_00189DA0(a, b, 1);
    }
}

/* 0x001828F0: rise by 20/(2*fps) per frame (capped at -40) and stop (state 0) after 2 seconds. */
void r3c_Rise1828F0(R3cObj *o, R3cObj *act)
{
    o->pos60[1] += 20.0f / (r3c_framesPerSecond * 2.0f);
    if (o->pos60[1] > -40.0f)
        o->pos60[1] = -40.0f;
    if (act->f5C > 2.0f)
        sub_00113040(o, act, 0);
}

/* 0x00183FC0: when animation 1 reports bit 2, run 0x001456E0 mode 1 on obj and its link; leave to state 2 unless the stage is in mode 4. */
void r3c_Step183FC0(R3cObj *obj, void *act)
{
    R3cAnim *a = obj->pa30;
    R3cObj *link = obj->p3C;

    if (a->i08 == 1 && (sub_001AEE90(a->inst14, 0) & 2)) {
        sub_001456E0(obj, act, 1, 0);
        sub_001456E0(link, act, 1, 0);
    }
    if (sub_000E3380() != 4)
        sub_00113040(obj, act, 2);
}

/* 0x00188F30: count the work timer up to its limit (progress in +0x14), then leave to state 0. */
void r3c_Count188F30(void *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    w->f14 = 1.0f - w->u0C.f / w->f20;
    if (w->u0C.f >= w->f20) {
        sub_00113040(obj, act, 0);
        w->f14 = 0.0f;
        return;
    }
    w->u0C.f += 1.0f;
}

/* 0x0018E9D0: hide obj, drop c's attachment and set block kind 2 (starting effect 0x8A/0x8B once). */
void r3c_Hide18E9D0(R3cObj *obj, R3cObj *c)
{
    R3cBlk74 *b = c->p74;
    int16_t *s = (int16_t *)b;

    obj->flags10 |= 5;
    if (b->i04 != 0) {
        sub_0013D4E0(b->i04, obj, 1);
        b->i04 = 0;
    }
    if (s[1] < 0)
        s[1] = (int16_t)sub_000494D0((c->b20 & 1) + 0x8A, obj->pos60, 1);
    s[0] = 2;
}

/* 0x0018EA30: show obj, drop c's attachment and sound, and set block kind 1. */
void r3c_Show18EA30(R3cObj *obj, R3cObj *c)
{
    R3cBlk74 *b = c->p74;
    int16_t *s = (int16_t *)b;

    obj->flags0C &= ~0xC0u;
    obj->flags10 |= 1;
    if (b->i04 != 0) {
        sub_0013D4E0(b->i04, obj, 1);
        b->i04 = 0;
    }
    if (s[1] >= 0) {
        sub_00048250(s[1]);
        s[1] = -1;
    }
    s[0] = 1;
}

/* 0x0018F690: drop the current object's sound and target and release the three objects at 0x004000B0. */
void r3c_Release18F690(void)
{
    R3cObj *p = sub_00100110();
    int i;

    if (p->i134 != -1) {
        sub_00048250(p->i134);
        p->i134 = -1;
    }
    if (p->p1C4 != 0)
        p->p1C4 = 0;
    for (i = 0; i < 3; i++) {
        if (r3c_recs4000B0[i].obj != 0)
            sub_000ED780(r3c_recs4000B0[i].obj);
    }
}

/* 0x00182890: sink by 20/(2*fps) per frame (floored at -60) and stop (state 0) after 2 seconds. */
void r3c_Sink182890(R3cObj *o, R3cObj *act)
{
    o->pos60[1] -= 20.0f / (r3c_framesPerSecond * 2.0f);
    if (-60.0f > o->pos60[1])
        o->pos60[1] = -60.0f;
    if (act->f5C > 2.0f)
        sub_00113040(o, act, 0);
}

/* 0x0018E850: hide obj, notify 0x0018E270 (obj in ESI, c in EAX) and replace c's looping sound by effect 0x8C. */
void r3c_Hide18E850(R3cObj *obj, R3cObj *c)
{
    int16_t *s = (int16_t *)c->p74;

    obj->flags0C &= ~0x40u;
    obj->flags10 |= 5;
    sub_0018E270(obj, c, 1);
    if (s[1] >= 0) {
        sub_00048250(s[1]);
        s[1] = -1;
        sub_000494D0(0x8C, obj->pos60, 0);
    }
}

/* 0x00189DE0: switch o's component 7 on (flag, mode 3) or off (mode 1). */
void r3c_Enable189DE0(void *o, int on)
{
    R3cObj *c = sub_0001D960(o, 7);

    if (c == 0)
        for (;;)
            ;
    if (o == 0)
        return;
    if (on) {
        sub_0001F070(o, 1);
        *(uint32_t *)&c->b20 |= 1;
        sub_0001EBF0(o, 3);
    } else {
        sub_0001F070(o, 0);
        *(uint32_t *)&c->b20 &= ~1u;
        sub_0001EBF0(o, 1);
    }
}
