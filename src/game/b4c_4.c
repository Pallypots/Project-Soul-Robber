/* Area b4c, group 4: enemy helpers 0x00143410-0x00146130. Names inferred. */
#include "b4c.h"

/* 0x00143410: after the animation, pick the next state (random 1-in-4 state 4). */
void b4c_Next143410(B4cOwner *o, B4cEnemy *e)
{
    if (sub_000833E0(o->anim30) == 0) return;
    o->flags10 &= ~4u;
    if (!(e->w20 & 1) && sub_001C7EE1() % 4 < 1) {
        sub_00113040(o, e, 4);
        return;
    }
    sub_00113040(o, e, B4C_SIDE(e) ? 10 : 7);
}

/* 0x00143760: predicate: no global timer, in range, distance within band, health below ratio. */
int b4c_PredWeak143760(B4cOwner *o, B4cEnemy *e, const float *c)
{
    float d;
    if (b10_f3F7504 > 0.0f) return 0;
    if (e->f100 > c[0]) return 0;
    d = sub_001A3F30(e->distFC);
    if (c[1] > d) return 0;
    if (d > c[2]) return 0;
    if (e->hp274 > e->maxHp270 * c[3]) return 0;
    return 1;
}

/* 0x001437E0: arm or release timer slot 8. */
void b4c_Timer1437E0(B4cOwner *o, B4cEnemy *e, int arm)
{
    B4cTimer *t = sub_001133E0(e, 8);
    if (arm) {
        if (t && t->on) t->on = 1;
        t = sub_00113430(e, 8);
        if (t) {
            t->f10 = 0.1f;
            t->f14 = 0.2f;
        }
    } else if (t) {
        if (t->on) t->on = 1;
        sub_00113370(e, t);
    }
}

/* 0x001456E0: enter state s unless already in it with the animation flag clear (callers pass a fourth 0). */
int b4c_Enter1456E0(B4cOwner *o, B4cEnemy *e, int s, int unused)
{
    if (e->i64 == s && !(sub_00083450(o->anim30, s) & 1)) return 0;
    sub_00113090(o, e, s);
    return 1;
}

/* 0x00145780: animation time is within one frame step after t. */
int b4c_AnimAt145780(B4cActor *a, float t)
{
    B4cAnimState *s = a->model30->anim14;
    if (s->timeD8 >= t && t + s->rateC4 * a50_frameUnits > s->timeD8) return 1;
    return 0;
}

/* 0x00145C50: build a rotation of angle a and apply it. */
void b4c_Rotate145C50(float *dst, const void *src, float a)
{
    float m[16];
    sub_001AD940(m);
    sub_001AD8E0(m, m, a);
    sub_001AD9B0(dst, m, src);
}

/* 0x00145C90: copy a matrix without its translation and apply it. */
void b4c_ApplyRot145C90(float *dst, const void *src, const void *v)
{
    float m[16];
    sub_001ADA40(m, src);
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    sub_001AD9B0(dst, m, v);
}

/* 0x001460E0: release effect, sound and attached object. */
int b4c_Release1460E0(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork *w = e->work;
    if (e->fx6C != -1) {
        sub_00048250(e->fx6C);
        e->fx6C = -1;
    }
    if (e->i70) {
        sub_00033A70((void *)e->i70);
        e->i70 = 0;
    }
    b16_ClearBit0(w->obj3C);
    w->obj3C = 0;
    return 1;
}
