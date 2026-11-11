/* Area b4c, group 3: enemy predicates and state entries 0x00140060-0x001430A0.
 * Names inferred. The predicate record c[] holds floats. */
#include "b4c.h"

/* 0x00140060: in range, close enough, work float low enough, random 1-in-c[3]. */
int b4c_PredAttack140060(B4cOwner *o, B4cEnemy *e, const float *c)
{
    if (e->f100 > c[0]) return 0;
    if (sub_001A3F30(e->distFC) > c[1]) return 0;
    if (c[2] > e->work->f18) return 0;
    return sub_001C7EE1() % (int)c[3] < 1;
}

/* 0x001400C0: global timer not running and target within both limits. */
int b4c_PredNear1400C0(B4cOwner *o, B4cEnemy *e, const float *c)
{
    if (b10_f3F7504 > 0.0f) return 0;
    if (e->f100 > c[0]) return 0;
    if (sub_001A3F30(e->distFC) > c[1]) return 0;
    return 1;
}

/* 0x00140110: animation done, within distance, random 1-in-c[1]. */
int b4c_PredAnim140110(B4cOwner *o, B4cEnemy *e, const float *c)
{
    float d = sub_001A3F30(e->distFC);
    int n = (int)c[1];
    if (sub_000833E0(o->anim30) && c[0] >= d && sub_001C7EE1() % n < 1) return 1;
    return 0;
}

/* 0x001420E0: animation done, close, fewer than 6 attackers, no global timer, random. */
int b4c_PredJoin1420E0(B4cOwner *o, B4cEnemy *e, const float *c)
{
    if (sub_000833E0(o->anim30) && c[0] >= sub_001A3F30(e->distFC) &&
        sub_001401C0() < 6 && 0.0f >= b10_f3F7504 &&
        sub_001C7EE1() % (int)c[1] < 1)
        return 1;
    return 0;
}

/* 0x00142150: work float +0x1C >= 1, close, fewer than 6 attackers, no global timer. */
int b4c_PredJoin142150(B4cOwner *o, B4cEnemy *e, const float *c)
{
    if (e->work->f1C >= 1.0f && c[0] >= sub_001A3F30(e->distFC) &&
        sub_001401C0() < 6 && 0.0f >= b10_f3F7504)
        return 1;
    return 0;
}

/* 0x001423E0: target the player and refresh distance and angle. */
void b4c_Target1423E0(B4cOwner *o, B4cEnemy *e)
{
    PlayerObj *p = g_playerObj;
    if (e->iF8 != 1 || e->target104 != p) {
        e->iF8 = 1;
        e->target104 = p;
    }
    e->distFC = sub_001135C0(o, e);
    e->f100 = sub_00113570(o, e);
}

/* 0x00142840: enter state 2/3 by side and set timer slot 3 angles to +-10 degrees. */
void b4c_Enter142840(B4cOwner *o, B4cEnemy *e)
{
    B4cTimer *t;
    sub_00113090(o, e, (e->w20 & 1) + 2);
    e->flags4C |= 0x10;
    t = sub_00113430(e, 3);
    t->f18 = 0.17453294f;
    t->f1C = -0.17453294f;
}

/* 0x00142A90: pick the hit-reaction state from work flags and enter it. */
void b4c_Hit142A90(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork *w = e->work;
    uint32_t f = w->flags04;
    int s;
    if (f & 0x8000000) s = 0x30;
    else s = (~(f >> 25) & 2) | 0x64;
    w->flags04 = f & 0xF1FFFFFFu;
    sub_00113090(o, e, B4C_SIDE(e) + s);
    o->flags10 |= 4;
}

/* 0x00142B80: enter state 0x14 with effect 0xCD and sound 6. */
void b4c_Enter142B80(B4cOwner *o, B4cEnemy *e)
{
    sub_00113090(o, e, 0x14);
    e->fx6C = aab_Effect494D0(0xCD, o->model20 + 0x30, 0);
    o->flags10 |= 0x10;
    e->flags4C &= ~0x10u;
    e->work->flags04 |= 0x10;
    e->i70 = sub_00036750(o, 6);
}

/* 0x00142BE0: random 0-8 frame delay; consume the pending flag. */
void b4c_Delay142BE0(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork *w;
    int r = sub_001C7EE1() % 9;
    e->flags4C &= ~8u;
    e->f74 = (float)r / a50_frameUnits * a50_frameSeconds;
    w = e->work;
    if ((int32_t)w->flags04 < 0) {
        e->i58 = 1;
        w->flags04 &= 0x7FFFFFFFu;
    }
}

/* 0x00142C80: enter state 0x34/0x35 by side. */
void b4c_Enter142C80(B4cOwner *o, B4cEnemy *e)
{
    sub_00113090(o, e, B4C_SIDE(e) + 0x34);
    o->flagsC |= 0x20;
    o->flags10 |= 4;
    e->work->flags04 &= ~0x10u;
}

/* 0x00142CD0: effect 0xBD, sound 8, enter state 0x45. */
void b4c_Enter142CD0(B4cOwner *o, B4cEnemy *e)
{
    sub_0013B960(o, e);
    aab_Effect494D0(0xBD, o->model20 + 0x30, 0);
    sub_00036750(o, 8);
    sub_00113090(o, e, 0x45);
    e->i58 = 2;
}

/* 0x00143050: after the animation, switch to state 0x11 recording whether state was 0x3B. */
void b4c_Done143050(B4cOwner *o, B4cEnemy *e)
{
    B4cEWork *w;
    if (sub_000833E0(o->anim30) == 0) return;
    w = e->work;
    if (e->i64 == 0x3B) {
        w->flags04 |= 0x80000000u;
        sub_00113040(o, e, 0x11);
        return;
    }
    w->flags04 &= 0x7FFFFFFFu;
    sub_00113040(o, e, 0x11);
}
