/* Area b4c, group 6: enemy range tests and motion helpers 0x00154D00-0x0015A270.
 * Names inferred. */
#include "b4c.h"

/* 0x00154D00: test the work range pair (+0x78, +0x80) and apply it. */
void b4c_Range154D00(B4cOwner *o, B4cEnemy *e, const B4cArgs *c)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    if (sub_00145940(o, w->i78, w->i80, c->p10, c->p14))
        sub_00155FB0(o, w->i78, w->i80, c->p18);
}

/* 0x001560B0: add gravity to the vertical speed unless a skip flag is pending. */
void b4c_Gravity1560B0(const B4cBody *b, void *unused, B4cMotion *m)
{
    float d, v;
    if (!(m->flags & 4)) return;
    if (m->flags & 8) {
        m->flags &= ~8u;
        return;
    }
    d = a50_frameSeconds;
    v = d * d * 294.0f;
    if (!(b->b128 & 0x18)) v += m->f28;
    m->f28 = v;
}

/* 0x00156180: set the motion parameters. */
void b4c_MotionSet156180(B4cMotion *m, float a, float b, float c, float t)
{
    m->f2C = 0.0f - a;
    m->f28 = b;
    m->f24 = c;
    m->f10 = 0.0f;
    m->f30 = 1.0f;
    m->fC = t;
}

/* 0x0015A220: test the work range pair (+0x64, +0x6C) and apply it. */
void b4c_Range15A220(B4cOwner *o, B4cEnemy *e, const B4cArgs *c)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    if (sub_00145940(o, w->i64, w->i6C, c->p10, c->p14))
        sub_00155FB0(o, w->i64, w->i6C, c->p18);
}
