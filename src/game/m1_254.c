/* Area m1, file 254: small AI state machines. Names inferred. */
#include <stdint.h>

typedef struct M1S254 { uint8_t unk00[8]; float t8; int32_t stateC; int32_t f10; } M1S254;
typedef struct M1O254 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x1C]; int32_t h30; } M1O254;
typedef struct M1A254 { uint8_t unk00[0x278]; M1S254 *s278; } M1A254;
int32_t sub_000F5D00(M1O254 *o);
void sub_0001D610(M1O254 *o);
void sub_000832D0(int32_t h, int32_t mode);
void m1_AiGoto113040(M1O254 *o, M1A254 *a, int32_t st);
extern float m1_frameRate42C85C;

/* 0x00179460: four-step sequence: wait for o's animation, then show it, then wait again, then count a timer up
   and hand over to AI state 2 when it passes the limit. */
void m1_Seq179460(M1O254 *o, M1A254 *a)
{
    M1S254 *s = a->s278;
    switch (s->stateC) {
    case 0:
        if (sub_000F5D00(o) == 0) return;
        sub_0001D610(o);
        sub_000832D0(o->h30, 4);
        s->stateC++;
        return;
    case 1:
        if (sub_000F5D00(o) == 0) return;
        o->flags10 &= ~0xDu;
        sub_000832D0(o->h30, 1);
        s->stateC++;
        s->f10 = 1;
        return;
    case 2:
        if (sub_000F5D00(o) == 0) return;
        s->stateC++;
        s->t8 = 0.0f;
        return;
    case 3:
        if (s->t8 > 0.2f) {
            m1_AiGoto113040(o, a, 2);
            s->t8 = 0.0f;
            return;
        }
        s->t8 = m1_frameRate42C85C + s->t8;
        return;
    }
}

extern int32_t m1_worldB413170;
extern uint8_t m1_tbl2E5100[], m1_tbl2E5150[], m1_tbl2E5170[], m1_tbl2E51A0[], m1_tbl2E51C0[], m1_tbl2E51E0[],
    m1_tbl2E5250[], m1_tbl2E5320[], m1_tbl2E5350[];

/* 0x000B0A60: pick the table for the current world (worlds 0-7 and 8-15 share tables, 16 has its own). */
void *m1_WorldTableB0A60(void)
{
    void *r;
    switch (m1_worldB413170) {
    case 0: case 8: r = m1_tbl2E5100; break;
    case 1: case 9: r = m1_tbl2E5150; break;
    case 2: case 10: r = m1_tbl2E5170; break;
    case 3: case 11: r = m1_tbl2E51A0; break;
    case 4: case 12: r = m1_tbl2E51C0; break;
    case 5: case 13: r = m1_tbl2E51E0; break;
    case 6: case 14: r = m1_tbl2E5250; break;
    case 7: case 15: r = m1_tbl2E5320; break;
    case 16: r = m1_tbl2E5350; break;
    }
    return r;
}

typedef struct M1K254 { uint8_t unk00[4]; int32_t kind4; } M1K254;
typedef struct M1L254 { uint8_t unk00[0x20]; uint8_t b20; } M1L254;
typedef struct M1C254 { int32_t who0; int32_t unk4; int32_t neg8; } M1C254;
typedef struct M1B254 { uint8_t unk00[0x278]; struct { int32_t unk0; M1K254 *k4; } *p278; } M1B254;
extern M1K254 *g_playerObj;
int32_t m1_KindMapEE5F0(M1K254 *k);
M1L254 *sub_0001D960(M1K254 *k, int32_t kind);

/* 0x00186310: condition: is bit 0 of the chosen object's link flags set (or clear when c->neg8 is 0)? The object is
   the player, a's target or self, picked by c->who0. Kinds other than 2 and 4 just test c->neg8. */
int32_t m1_CondLink186310(M1K254 *self, M1B254 *a, M1C254 *c)
{
    M1K254 *k;
    M1L254 *l;
    switch (c->who0) {
    case 1: k = g_playerObj; break;
    case 3: k = a->p278->k4; break;
    case 4: k = self; break;
    case 2: case 5: k = 0; break;
    default: for (;;) ;
    }
    if (k->kind4 != 2 && k->kind4 != 4)
        return c->neg8 == 0;
    l = sub_0001D960(k, m1_KindMapEE5F0(k));
    if (c->neg8 == 0)
        return ~l->b20 & 1;
    return l->b20 & 1;
}


typedef struct M1Sn254 { uint8_t unk00[0x1E8]; void *p1E8; } M1Sn254;
extern M1Sn254 *m1_scene42C8E4;
void *sub_0001D080(void *list, int32_t a, int32_t b);
void *sub_0001D080a(void *list, int32_t a, int32_t b);   /* aliases of the same function stop cl merging calls */
void *sub_0001D080c(void *list, int32_t a, int32_t b);
void *sub_0001D080d(void *list, int32_t a, int32_t b);
void *sub_0001D080e(void *list, int32_t a, int32_t b);
void *sub_0001D080f(void *list, int32_t a, int32_t b);
void *sub_0001D080g(void *list, int32_t a, int32_t b);

/* 0x000E3DA0: look up a stage object by id: id 2 is the player, ids 3-11 are entries in the scene's object list. */
void *m1_ObjById_E3DA0(int32_t unused, int32_t id)
{
    switch (id) {
    case 2: return g_playerObj;
    case 3: return sub_0001D080a(m1_scene42C8E4->p1E8, 3, 0);
    case 4: return sub_0001D080c(m1_scene42C8E4->p1E8, 4, 3);
    case 5: return sub_0001D080(m1_scene42C8E4->p1E8, 3, 3);
    case 6: return sub_0001D080d(m1_scene42C8E4->p1E8, 3, 4);
    case 7: return sub_0001D080e(m1_scene42C8E4->p1E8, 3, 5);
    case 8: return sub_0001D080(m1_scene42C8E4->p1E8, 3, 6);
    case 9: return sub_0001D080f(m1_scene42C8E4->p1E8, 3, 7);
    case 10: return sub_0001D080g(m1_scene42C8E4->p1E8, 3, 8);
    case 11: return sub_0001D080(m1_scene42C8E4->p1E8, 3, 9);
    }
    return 0;
}

typedef struct M1G254 { uint8_t unk00[4]; int32_t kind4; int32_t f8; } M1G254;
typedef struct M1H254 { uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x2F]; int32_t st50; uint8_t unk54[8]; float t5C; } M1H254;
M1H254 *sub_0001D960b(M1G254 *o, int32_t kind);
void sub_00113040b(M1G254 *o, M1H254 *l, int32_t st);
void sub_00113480(M1H254 *l, int32_t st);

/* 0x00137F50: hit reaction for a kind-2 object: pick the next AI state from the hit type n (0-3) and the
   object's current state. */
void m1_HitReact137F50(M1G254 *o, int32_t n)
{
    M1H254 *l;
    int32_t st, zero = 0;
    if (o == 0 || o->kind4 != 2 || o->f8 != 0) return;
    l = sub_0001D960b(o, 4);
    if (l == 0) return;
    if (n != 3 && l->st50 != 0xC && l->st50 != 0xD) return;
    switch (n) {
    case 0: case 1:
        sub_00113040b(o, l, 0x10);
        return;
    case 2:
        st = (int8_t)~l->b20;
        st = (st & 1) << 2 | 0xB;
        sub_00113480(l, 3);
        if (st >= *(volatile int32_t *)&zero) sub_00113040b(o, l, st);
        return;
    case 3:
        if (l->b20 & 1) return;
        if (l->st50 == 0xF) {
            l->t5C = 0.0f;
            sub_00113480(l, 9);
            sub_00113040b(o, l, 0x1A);
        } else if (l->st50 == 0x1C) {
            sub_00113040b(o, l, 0x1D);
        }
        return;
    }
}

typedef struct M1Q254 { uint8_t unk00[0x64]; float f64; uint8_t unk68[0xC0]; uint8_t b128; } M1Q254;
typedef struct M1R254 { uint8_t unk00[0x9C]; int32_t st9C; uint8_t unkA0[0x1C]; uint16_t wBC; uint8_t unkBE[0xBA];
    float f178; } M1R254;
M1R254 *sub_000F5F80(M1Q254 *o);
int32_t sub_000F5D00b(M1Q254 *o);
void sub_000F62F0(M1R254 *s, int32_t anim);
void sub_000F63D0(float *v);
extern float m1_fps42C964;

/* 0x000FB160: fall sequence: start falling (anim 0x39), then speed the fall up each frame until o lands
   (flag 0x18: anim 0x3A), then wait out the landing (anim 0x3B), then mark the sequence finished. */
void m1_Fall_FB160(M1Q254 *o)
{
    M1R254 *s = sub_000F5F80(o);
    switch (s->st9C) {
    case 0:
        if (sub_000F5D00b(o)) {
            sub_000F62F0(s, 0x39);
            s->st9C++;
        }
        /* fall through */
    case 1:
        o->f64 += s->f178;
        s->f178 += 3.0f / m1_fps42C964;
        sub_000F63D0(&s->f178);
        if (o->b128 & 0x18) {
            sub_000F62F0(s, 0x3A);
            s->st9C = 2;
        }
        return;
    case 2:
        if (sub_000F5D00b(o)) {
            sub_000F62F0(s, 0x3B);
            s->st9C++;
        }
        return;
    case 3:
        if (sub_000F5D00b(o) == 0) return;
        /* fall through */
    default:
        s->wBC = 1;
        return;
    }
}

typedef struct M1Pr254 { int32_t f0; uint8_t unk04[0xD4]; int32_t fD8, fDC, fE0; uint8_t unkE4[0xC]; } M1Pr254;   /* 0xF0 */
typedef struct M1Pe254 { uint8_t unk00[0xB0]; int32_t fB0; uint8_t unkB4[0x64]; M1Pr254 *r118; int32_t f11C, f120, f124;
    uint8_t unk128[4]; } M1Pe254;                                                                       /* 0x12C */
typedef struct M1Pm254 { uint8_t unk00[0xB0]; uint32_t nB0; M1Pe254 *eB4; uint8_t unkB8[4]; int32_t fBC, fC0, fC4, fC8;
    uint8_t unkCC[8]; int32_t fD4; } M1Pm254;
typedef struct M1Pd254 { int32_t n0; M1Pr254 *r4; } M1Pd254;
void sub_001B6310(M1Pm254 *m, int32_t a, int32_t b, int32_t c, int32_t d);
void sub_001B6670(M1Pm254 *m, int32_t s);

/* 0x001B6C80: bind m's emitters to the descriptor's records (as many as both have), clear the rest, then
   reapply m's settings and scale. */
void m1_EmitBind1B6C80(M1Pm254 *m, M1Pd254 *d)
{
    uint32_t i = 0, z = 0;
    M1Pe254 *e;
    M1Pr254 *r;
    if (m->nB0 > *(volatile uint32_t *)&z) {
        do {
            if ((int32_t)i >= d->n0) break;
            r = &d->r4[i];
            e = &m->eB4[i];
            e->r118 = r;
            e->fB0 = r->f0;
            e->f120 = r->fDC;
            e->f124 = r->fE0;
            e->f11C = r->fD8;
            i++;
        } while (i < m->nB0);
    }
    for (; i < m->nB0; i++)
        m->eB4[i].fB0 = 0;
    sub_001B6310(m, m->fBC, m->fC0, m->fC4, m->fC8);
    sub_001B6670(m, m->fD4);
}

typedef struct M1Mg254 { int32_t id0; uint8_t unk04[8]; int32_t fC; float pos10[4]; } M1Mg254;
typedef struct M1Ml254 { uint8_t unk00[0x5C]; float f5C; uint8_t unk60[0x2C]; int32_t f8C; uint8_t unk90[0x4C];
    int32_t fDC; } M1Ml254;
M1Ml254 *sub_0001D960B(void *o, int32_t kind);
int32_t sub_0019BE60(int32_t mask);
void sub_000F3BF0(void *o, int32_t v, int32_t a);
void sub_00025D50(int32_t a, int32_t b);
void sub_000F3BF0b(void *o, int32_t v, int32_t a);   /* aliases stop cl merging the two accept tails */
void sub_00025D50b(int32_t a, int32_t b);
void *sub_00035D80(void *o, int32_t a, int32_t b);
void sub_00034DD0(void *h, const float *pos, const void *m, const void *col);
void sub_000C75E0(void *o);
extern uint8_t m1_fx378188[], m1_fx378198[];

/* 0x000EEE10: message handler: ignored while input is blocked or o is busy. Message 10 is always taken;
   others are taken unless o is in state 1. Messages 1-3 also spawn a hit effect; 32 also calls c75e0;
   34 is refused while o's timer is still running. Returns 1 when the message was taken. */
int32_t m1_OnMsgEEE10(void *o, M1Mg254 *msg)
{
    M1Ml254 *l = sub_0001D960B(o, 5);
    int32_t r;
    if (sub_0019BE60(0x10000) || l->f8C != 0) return 0;
    if (msg->id0 == 10) {
        sub_000F3BF0(o, msg->fC, 1);
        sub_00025D50(1, 1);
        return 1;
    }
    if (l->fDC == 1) return 0;
    r = 0;
    switch (msg->id0) {
    case 1: case 2: case 3:
        sub_00034DD0(sub_00035D80(o, 2, 3), msg->pos10, m1_fx378198, m1_fx378188);
        /* fall through */
    case 5: case 6: case 7: case 8: case 9: case 11: case 32: case 34: case 35:
        if (msg->id0 == 32) sub_000C75E0(o);
        if (msg->id0 == 34 && l->f5C > 0.0f) return r;
        sub_000F3BF0b(o, msg->fC, 1);
        sub_00025D50b(1, 1);
        r = 1;
        return r;
    }
    return 0;
}
