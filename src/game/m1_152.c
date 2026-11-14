/* Area m1, file 152: more minion movement. Names inferred. */
#include <stdint.h>

typedef struct M1Min152 {
    uint8_t unk00[0x9C]; int32_t i9C; uint8_t unkA0[0xEC - 0xA0]; int16_t wEC;
    uint8_t unkEE[0x158 - 0xEE]; float v158[4]; float f168; float f16C; float f170; float f174; float f178;
    float f17C; float f180; float v184[4]; float v194[4]; volatile int16_t w1A4; volatile int16_t w1A6;
} M1Min152;
M1Min152 *sub_000F5F80(uint8_t *t);
void sub_000F62F0(M1Min152 *p, int anim);
void sub_000F5D40(float *d, const void *s);
void sub_001ADB60(float *d, const float *s, float k);

/* 0xF9620: send the target's minion on a hop using its own speed settings. */
void m1_MinionHop20F9620(uint8_t *tgt) {
    M1Min152 *p = sub_000F5F80(tgt); float l[4], b, x; volatile float k = 2.0f;
    if (p->wEC != 0) { sub_000F62F0(p, 0x11); *(volatile int32_t *)&p->i9C = 1; }
    else { sub_000F62F0(p, 0x10); *(volatile int32_t *)&p->i9C = 0; }
    sub_000F5D40(p->v194, tgt + 0x60);
    l[0] = p->f168;
    b = p->f16C;
    sub_001ADB60(l, p->v158, p->f170 / p->f168);
    p->f17C = l[1];
    p->f180 = l[3];
    p->v184[3] = 0.0f; p->v184[2] = 0.0f; p->v184[1] = 0.0f; p->v184[0] = 0.0f;
    x = b / l[0] * k * k;
    p->f174 = (b - x * l[0] * 0.5f) * 8.0f / (l[0] * l[0]);
    p->f178 = x;
    p->w1A4 = 0;
    p->w1A6 = 1;
}

typedef struct M1Ob152 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0xC]; uint8_t *mdl20; uint8_t unk24[0x4C]; float f70; uint8_t unk74[0x130 - 0x74]; int32_t x130; } M1Ob152;
typedef struct M1St152 { int16_t w0; int16_t w2; void *p4; void *p8; float v0C[4]; float v1C[4]; float v2C[4]; } M1St152;
typedef struct M1Ai152 { uint8_t unk00[0x20]; uint32_t f20; uint8_t unk24[0x50]; M1St152 *st74; } M1Ai152;
void *sub_00035DD0(M1Ob152 *o, int a, int b, int c);
void  m1_FxScale034DA0(void *fx, float s);
void  m1_SndStop048250(int h);
void  sub_000494D0(int id, void *pos, int k);
void  sub_00033A70(void *p);
void  m1_HoldDrop13D4E0(void *h, M1Ob152 *o, int k);

/* 0x18EA90: enemy death: switch to the death effect, stop its sound, puff, drop anything held. */
void m1_AiDeath18EA90(M1Ob152 *o, M1Ai152 *e) {
    M1St152 *s = e->st74; void *fx; float f;
    o->f10 |= 0xD;
    fx = sub_00035DD0(o, o->x130, 5 - (e->f20 & 1), 1);
    f = o->f70;
    if (f > 1.5f) f = 1.5f;
    m1_FxScale034DA0(fx, f);
    if (s->w2 >= 0) { m1_SndStop048250(s->w2); s->w2 = -1; }
    sub_000494D0(0x97, o->mdl20 + 0x70, 0);
    sub_00033A70(s->p8);
    s->p8 = 0;
    if (s->p4 != 0) { m1_HoldDrop13D4E0(s->p4, o, 1); s->p4 = 0; }
}

/* 0x18E040: free an enemy's hold state (effect, sound, transforms); 0 when it is still holding. */
int m1_AiHoldFree18E040(void *unused, M1Ai152 *e) {
    M1St152 *s = e->st74;
    if (s == 0 || s->p4 != 0) return 0;
    if (s->p8 != 0) { sub_00033A70(s->p8); s->p8 = 0; }
    if (s->w2 >= 0) { m1_SndStop048250(s->w2); s->w2 = -1; }
    s->w0 = 0; s->p4 = 0; s->p8 = 0; s->w2 = -1;
    s->v0C[0] = 0.0f; s->v0C[1] = 0.0f; *(volatile float *)&s->v0C[2] = 0.0f; s->v0C[3] = 1.0f;
    s->v0C[2] = -70.0f;
    s->v1C[0] = 0.0f; s->v1C[1] = 0.0f; s->v1C[2] = 0.0f; s->v1C[3] = 1.0f;
    s->v2C[0] = 0.0f; s->v2C[1] = 0.0f; s->v2C[2] = 0.0f; s->v2C[3] = 1.0f;
    e->st74 = 0;
    return 1;
}

typedef struct M1Rg152 { uint8_t unk00[4]; uint32_t f4; } M1Rg152;
typedef struct M1Ob152b { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; void *anim30; } M1Ob152b;
typedef struct M1Ai152b {
    uint8_t unk00[0x20]; uint32_t f20; uint8_t unk24[0x28]; uint32_t flags4C; uint8_t unk50[0x24]; float t74;
    uint8_t unk78[0x278 - 0x78]; M1Rg152 *rig278;
} M1Ai152b;
typedef int (*M1Check152)(M1Ob152b *o, M1Ai152b *e, const uint8_t *tbl);
extern M1Check152 m1_chkFn31D0B8, m1_chkFn31D0BC;
extern const uint8_t m1_chkTbl2797C8[], m1_chkTbl2797D8[];
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
void m1_AiGoto113040(M1Ob152b *o, M1Ai152b *e, int st);

/* 0x141760: pick the enemy's next state when its current animation ends. */
void m1_AiNext141760(M1Ob152b *o, M1Ai152b *e) {
    M1Rg152 *r = e->rig278; int st;
    if (sub_000833E0(o->anim30) == 0) return;
    if (m1_chkFn31D0B8(o, e, m1_chkTbl2797C8)) st = 0xA;
    else if (!(e->f20 & 0x10000)) st = 0x28;
    else if (e->f20 & 1) st = (-(m1_chkFn31D0BC(o, e, m1_chkTbl2797D8) != 0) & -2) + 0x29;
    else { e->t74 = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C; st = 0xC; }
    o->f10 &= ~6u;
    e->flags4C |= 0x18;
    r->f4 &= ~0x800000u;
    m1_AiGoto113040(o, e, st);
}
