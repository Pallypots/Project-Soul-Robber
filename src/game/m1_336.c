/* Area m1, file 336: enemy target selection (two variants). Names inferred. */
#include <stdint.h>

typedef struct M1Tg336 { uint8_t unk00[4]; int32_t i04; uint8_t unk08[4]; uint8_t b0C; uint8_t unk0D[0x60 - 0x0D]; float x60; float y64; float z68; } M1Tg336;
typedef struct M1St336 { uint8_t unk00[0x38]; M1Tg336 *p38; uint8_t unk3C[4]; uint32_t f40; uint8_t unk44[0x50 - 0x44]; uint32_t f50; } M1St336;
typedef struct M1Ai336 {
    uint8_t unk000[0x50]; int32_t n50; uint8_t unk054[0xF8 - 0x54]; int32_t iF8; uint8_t unk0FC[0x104 - 0xFC]; M1Tg336 *p104;
    uint8_t unk108[0x278 - 0x108]; M1St336 *s278;
} M1Ai336;
extern M1Tg336 *g_playerObj;
M1Tg336 *sub_000C7130(void *o);
int      sub_00145940(void *o, float x, float z, float lo, float hi);
M1Tg336 *sub_000EDBE0(int a, int b);
float    sub_001B2770(const void *a, const void *b);   /* distance */

/* 0x155330: pick the target. With state bit 0x80 set keep a grabbed kind-0xD target (or
   switch to the nearest entity in the +-120 degree cone, flagging 0x100) and remember the
   kind-7 helper (clearing 0x1000 when there is none). Otherwise choose between the player
   and the nearest entity in the cone (the entity when it is within 80 and no farther than
   the player), note the kind-7 helper, and flag 0x100 when the target changes. */
void m1_AiPickTarget155330(uint8_t *o, M1Ai336 *e) {
    M1St336 *s = e->s278;
    M1Tg336 *best, *t, *h;
    float dp, dt;
    s->f40 &= ~0x100u;
    if ((int8_t)s->f40 < 0) {
        if (e->iF8 == 1 && (!e->p104 || !(e->p104->b0C & 1))) {
            e->p104 = g_playerObj;
            e->iF8 = 1;
        }
        if (e->iF8 == 1 && (e->p104->b0C & 1) && e->p104->i04 == 0xD) {
            t = sub_000C7130(o);
            if (t && t != e->p104 && sub_00145940(o, t->x60, t->z68, -2.0943952f, 2.0943952f)) {
                s->f40 |= 0x100;
                e->p104 = t;
                e->iF8 = 1;
            }
        }
        h = sub_000EDBE0(2, 7);
        if (h) {
            s->p38 = h;
            return;
        }
        s->f40 &= ~0x1000u;
        s->p38 = 0;
        return;
    }
    best = g_playerObj;
    t = sub_000C7130(o);
    h = sub_000EDBE0(2, 7);
    if (best)
        dp = sub_001B2770(o + 0x60, (uint8_t *)best + 0x60);
    else
        dp = 3.4028235e38f;
    if (t && sub_00145940(o, t->x60, t->z68, -2.0943952f, 2.0943952f) == 1)
        dt = sub_001B2770(o + 0x60, (uint8_t *)t + 0x60);
    else
        dt = 3.4028235e38f;
    if (h) {
        sub_001B2770(o + 0x60, (uint8_t *)h + 0x60);
        s->p38 = h;
    } else {
        s->f40 &= ~0x1000u;
        s->p38 = 0;
    }
    if (!(80.0f >= dt) || !(dp >= dt))
        t = best;
    if (e->p104 != t || e->iF8 != 1) {
        e->p104 = t;
        e->iF8 = 1;
        s->f40 |= 0x100;
    }
}

/* 0x146390: the same choice on the +0x50 state word (bit 0x40 instead of 0x80, flag 0x80,
   helper kind 6 clearing 0x400); the grab check also skips enemies in step 0x14 and
   flags 0x80 when it falls back to the player. */
void m1_AiPickTarget146390(uint8_t *o, M1Ai336 *e) {
    M1St336 *s = e->s278;
    M1Tg336 *best, *t, *h;
    float dp, dt;
    uint32_t f;
    s->f50 &= ~0x80u;
    f = s->f50;
    if (f & 0x40) {
        if (e->iF8 == 1 && (!e->p104 || !(e->p104->b0C & 1))) {
            s->f50 = f | 0x80;
            e->p104 = g_playerObj;
            e->iF8 = 1;
        }
        if (e->iF8 == 1 && (e->p104->b0C & 1) && e->p104->i04 == 0xD && e->n50 != 0x14) {
            t = sub_000C7130(o);
            if (t && t != e->p104 && sub_00145940(o, t->x60, t->z68, -2.0943952f, 2.0943952f)) {
                s->f50 |= 0x80;
                e->p104 = t;
                e->iF8 = 1;
            }
        }
        h = sub_000EDBE0(2, 6);
        if (h) {
            s->p38 = h;
            return;
        }
        s->f50 &= ~0x400u;
        s->p38 = 0;
        return;
    }
    best = g_playerObj;
    t = sub_000C7130(o);
    h = sub_000EDBE0(2, 6);
    if (best)
        dp = sub_001B2770(o + 0x60, (uint8_t *)best + 0x60);
    else
        dp = 3.4028235e38f;
    if (t && sub_00145940(o, t->x60, t->z68, -2.0943952f, 2.0943952f) == 1)
        dt = sub_001B2770(o + 0x60, (uint8_t *)t + 0x60);
    else
        dt = 3.4028235e38f;
    if (h) {
        sub_001B2770(o + 0x60, (uint8_t *)h + 0x60);
        s->p38 = h;
    } else {
        s->f50 &= ~0x400u;
        s->p38 = 0;
    }
    if (!(80.0f >= dt) || !(dp >= dt))
        t = best;
    if (e->p104 != t || e->iF8 != 1) {
        e->p104 = t;
        e->iF8 = 1;
        s->f50 |= 0x80;
    }
}
