/* Area b4c, group 5: state entries of the 0x00146xxx enemy. Names inferred.
 * Kept apart from b4c_4.c so 0x001456E0 is not inlined. */
#include "b4c.h"

/* 0x00146860: enter state 0x14 with effect 0x12E and sound 5. */
void b4c_Enter146860(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    b4c_Enter1456E0(o, e, 0x14, 0);
    b4c_MotionSet156180((B4cMotion *)w, 0.0f, 0.0f, 0.0f, a50_frameUnits * 0.003f);
    e->flags4C &= ~0x70u;
    o->flags10 |= 0x30;
    w->flags50 &= ~4u;
    w->i58 = 0;
    e->fx6C = aab_Effect494D0(0x12E, (uint8_t *)o + 0x60, 0);
    e->i70 = sub_00036750(o, 5);
}

/* 0x001468E0: enter state 0x16. */
void b4c_Enter1468E0(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    b4c_Enter1456E0(o, e, 0x16, 0);
    b4c_MotionSet156180((B4cMotion *)w, 0.0f, 0.0f, 0.0f, a50_frameUnits * 0.003f);
    o->flags10 |= 0x20;
    e->flags4C &= ~0x70u;
}

/* 0x001469E0: enter state 0x13 and score 1. */
void b4c_Enter1469E0(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    b4c_Enter1456E0(o, e, 0x13, 0);
    b4c_MotionSet156180((B4cMotion *)w, 0.0f, 0.0f, 0.0f, a50_frameUnits * 0.003f);
    e->flags4C &= ~0x70u;
    sub_000414A0(1);
}

/* 0x00146A40: enter state 0x13 with owner flag 0x20 and score 1. */
void b4c_Enter146A40(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    b4c_Enter1456E0(o, e, 0x13, 0);
    b4c_MotionSet156180((B4cMotion *)w, 0.0f, 0.0f, 0.0f, a50_frameUnits * 0.003f);
    o->flags10 |= 0x20;
    e->flags4C &= ~0x70u;
    sub_000414A0(1);
}

/* 0x00146CA0: reset and remember the owner position. */
void b4c_Reset146CA0(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    b4c_MotionSet156180((B4cMotion *)w, 0.0f, 0.0f, 0.0f, a50_frameUnits * 0.003f);
    e->flags4C &= ~0x70u;
    o->flagsC &= ~0x20u;
    w->flags |= 2;
    b4c_VecCopy(w->v40, (uint8_t *)o + 0x60);
}

/* 0x00146D00: enter state 0x46. */
void b4c_Enter146D00(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    b4c_Enter1456E0(o, e, 0x46, 0);
    b4c_MotionSet156180((B4cMotion *)w, 0.0f, 0.0f, 0.0f, a50_frameUnits * 0.003f);
    e->flags4C &= ~0x70u;
    o->flagsC &= ~0x20u;
    w->flags |= 2;
}

/* 0x00146D60: once, after the animation, enter state 0x42. */
void b4c_Once146D60(B4cOwner *o, B4cEnemy *e)
{
    if (e->i58 == 0 && sub_000833E0(o->anim30)) {
        b4c_Enter1456E0(o, e, 0x42, 0);
        e->i58++;
    }
}

/* 0x00146EF0: test and apply the work range pair. */
void b4c_Range146EF0(B4cOwner *o, B4cEnemy *e, const B4cArgs *c)
{
    B4cEWork2 *w = (B4cEWork2 *)e->work;
    if (sub_00145940(o, w->i78, w->i80, c->p10, c->p14))
        sub_001459D0(o, w->i78, w->i80, c->p18);
}
