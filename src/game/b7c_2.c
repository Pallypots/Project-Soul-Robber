/* Area b7c, group 2: enemy state handlers and pools 0x001763C0-0x0017CB90. Names inferred. */
#include "b7c.h"

/* 0x001763C0: go to state 4 when the work-block timer at +0x10 fires. */
void b7c_Timer1763C0(void *o, B7CEnemy *e)
{
    if (sub_00176070(o, e, (uint8_t *)e->work + 0x10))
        sub_00113040(o, e, 4);
}

/* 0x001764A0: take a free 0x34-byte record from pool 0x003FD8D0. */
B7CRec34 *b7c_Alloc1764A0(void)
{
    int i = 0;
    B7CRec34 *r;
    for (r = b7c_pool3FD8D0; r < b7c_pool3FD8D0 + 5; r++, i++)
        if (!(r->flags & 1))
            goto found;
    return 0;
found:
    r = &b7c_pool3FD8D0[i];
    B7C_ZERO(r, sizeof *r);
    r->flags |= 1;
    return r;
}

/* 0x00176B80: state 1, clearing work flags 0x08|0x40|0x80. */
void b7c_State1_176B80(void *o, B7CEnemy *e)
{
    sub_00113090(o, e, 1);
    *(uint32_t *)e->work &= 0xFFFFFF37;
}

/* 0x00176D90: state 3, setting work flag 0x20. */
void b7c_State3_176D90(void *o, B7CEnemy *e)
{
    sub_00113090(o, e, 3);
    *(uint32_t *)e->work |= 0x20;
}

/* 0x00176DC0: go to state 5 when the work-block timer at +0x18 fires. */
void b7c_Timer176DC0(void *o, B7CEnemy *e)
{
    if (sub_00176070(o, e, (uint8_t *)e->work + 0x18))
        sub_00113040(o, e, 5);
}

/* 0x00177760: take a free 0x34-byte record from pool 0x003FD9D8. */
B7CRec34 *b7c_Alloc177760(void)
{
    int i = 0;
    B7CRec34 *r;
    for (r = b7c_pool3FD9D8; r < b7c_pool3FD9D8 + 5; r++, i++)
        if (!(r->flags & 1))
            goto found;
    return 0;
found:
    r = &b7c_pool3FD9D8[i];
    B7C_ZERO(r, sizeof *r);
    r->flags |= 1;
    return r;
}

/* 0x00177800: release the three effects at +0x28 and clear the active bit. */
int b7c_Release177800(void *o, B7CEnemy *e)
{
    B7CWorkB *w = e->work;
    int i;
    for (i = 0; i < 3; i++)
        if (w->fx28[i])
            sub_001940A0(w->fx28[i]);
    w->flags &= ~1u;
    return 1;
}

/* 0x00177F30: state 3, setting work flag 2. */
void b7c_State3_177F30(void *o, B7CEnemy *e)
{
    sub_00113090(o, e, 3);
    *(uint32_t *)e->work |= 2;
}

/* 0x00177F60: go to state 4 when the work-block timer at +0x14 fires. */
void b7c_Timer177F60(void *o, B7CEnemy *e)
{
    if (sub_00176070(o, e, (uint8_t *)e->work + 0x14))
        sub_00113040(o, e, 4);
}

/* 0x001784D0: always true. */
int b7c_True1784D0(void) { return 1; }

/* 0x00178990: clear the movement vector and set w to 1. */
void b7c_MoveReset178990(void *o, B7CMove *m)
{
    m->f78 = 0.0f;
    m->f7C = 0.0f;
    m->f80 = 0.0f;
    m->f84 = 1.0f;
}

/* 0x00178C20: copy the source position into the movement vector, zero y, then update. */
void b7c_MoveFrom178C20(uint8_t *src, B7CMove *m)
{
    b7c_VecCopy(src + 0x80, &m->f78);
    m->f7C = 0.0f;
    sub_00178860(src, m);
}

/* 0x00178EA0: forwards to 0x00178D50. */
void b7c_Fwd178EA0(void *a, void *b) { sub_00178D50(a, b); }

/* 0x00179140: reset ten halfword counters to 1. */
void b7c_ResetCounters179140(void)
{
    int i;
    for (i = 0; i < 10; i++)
        b7c_w3FDAE0[i] = 1;
}

/* 0x00179160: release the object of every record in pool 0x003FDAF8. */
void b7c_ReleaseAll179160(void)
{
    B7CRec24 *r;
    for (r = b7c_pool3FDAF8; r < b7c_pool3FDAF8 + 9; r++)
        if (r->obj)
            sub_000ED780(r->obj);
}

/* 0x00179440: clear work counter +0x0C. */
void b7c_Clear179440(void *o, B7CEnemy *e) { ((B7CWorkC *)e->work)->i0C = 0; }

/* 0x00179560: play animation 6 and clear work halfword +0x16. */
void b7c_Anim6_179560(B7COwner *o, B7CEnemy *e)
{
    B7CWorkC *w = e->work;
    sub_000832D0(o->anim30, 6);
    w->s16 = 0;
}

/* 0x00179800: clear work counter +0x0C and timer +0x08. */
void b7c_Clear179800(void *o, B7CEnemy *e)
{
    B7CWorkC *w = e->work;
    w->i0C = 0;
    w->f08 = 0.0f;
}

/* 0x001798D0: play animation 2, set owner flags 0x0D, clear work +0x0C/+0x10. */
void b7c_Anim2_1798D0(B7COwner *o, B7CEnemy *e)
{
    B7CWorkC *w = e->work;
    sub_000832D0(o->anim30, 2);
    w->i0C = 0;
    o->flags10 |= 0xD;
    w->i10 = 0;
}

/* 0x0017A140: enemy goes to state 13. */
void b7c_State13_17A140(void *o, void *e) { sub_00113090(o, e, 13); }
/* 0x0017A160: enemy goes to state 8. */
void b7c_State8_17A160(void *o, void *e) { sub_00113090(o, e, 8); }

/* 0x0017B260: set owner flag 0x20 and give slot 0 a speed of -21 per second. */
void b7c_Speed17B260(B7COwner *o, void *e)
{
    o->flags10 |= 0x20;
    sub_001133E0(e, 0)->f10 = b16_frameDelta * -21.0f;
}

/* 0x0017C4D0: 1 if no record in pool 0x003FDC70 is in use. */
int b7c_AllFree17C4D0(void)
{
    B7CRec54 *r;
    for (r = b7c_pool3FDC70; r < b7c_pool3FDC70 + 6; r++)
        if (r->used != 0)
            return 0;
    return 1;
}

/* 0x0017CA20: work mode +0x26 = 2. */
void b7c_Mode2_17CA20(void *o, B7CEnemy *e) { ((B7CWorkD *)e->work)->mode26 = 2; }

/* 0x0017CA40: clear owner flag 0x200 and set work mode 2. */
void b7c_Mode2_17CA40(B7COwner *o, B7CEnemy *e)
{
    B7CWorkD *w = e->work;
    o->flags0C &= ~0x200u;
    w->mode26 = 2;
}

/* 0x0017CB60: clear owner flag 0x200, set work mode 1 and zero its timer. */
void b7c_Mode1_17CB60(B7COwner *o, B7CEnemy *e)
{
    B7CWorkD *w = e->work;
    o->flags0C &= ~0x200u;
    w->mode26 = 1;
    w->f44 = 0.0f;
}
