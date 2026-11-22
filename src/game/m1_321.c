/* Area m1, group 321. Names inferred. */
#include <stdint.h>

typedef struct { uint32_t f0; uint8_t _4[0x1C]; } M1Fp321;
typedef struct {
    uint8_t _0[0x24]; int32_t f24; float f28, f2c; uint8_t _30[0x44]; M1Fp321 *flags74;
    uint8_t _78[0xB4 - 0x78]; const void *cbb4; uint8_t _b8[4]; const void *cbbc, *cbc0, *cbc4,
    *cbc8, *cbcc, *cbd0;
} M1Fa321;
typedef struct {
    uint8_t _0[0xC]; uint32_t fc, f10; uint8_t _14[0x70 - 0x14]; float f70, f74, f78, f7c;
    uint8_t _80[0xA4 - 0x80]; float fa4; uint8_t _a8[8]; float fb0, fb4; uint8_t _b8[0xD0 - 0xB8];
    int32_t fd0; uint8_t _d4[8]; float fdc; uint8_t _e0[8]; float fe8; int32_t fec, ff0, ff4;
    uint8_t _f8[4]; float ffc; uint8_t _100[0xC]; float f10c; uint8_t _110[8]; int32_t f118, f11c,
    f120, f124;
} M1Fo321;

extern M1Fp321 m1_flyPool3F8A18[16];
extern const uint8_t m1_flyTabA31F218[], m1_flyTabB31F1D0[];
int32_t m1_FlyerFree169A00();
int32_t m1_FlyerHit169800();
void m1_FlyerThink16B320();
void m1_FlyerMove169A50();
void b16_To12(void);
int  sub_000D9A70(int k);
int32_t sub_0001BC40(M1Fo321 *o);
void sub_001671D0(M1Fo321 *o, M1Fa321 *a, int st);
void sub_001671D0b(M1Fo321 *o, M1Fa321 *a, int st);

/* 0x0016B5F0: spawn a flyer of kind k (negative: low byte, marked as a
   summoned copy) in mode 0/1/2: take a free slot from the 16-entry pool
   (kind 0 also needs spawn slot 0x48), install its handlers, scale it
   (2x, or 1x for kind 2), set its body and motion limits and start it in
   state 0 (mode 0 also flags it grounded) or, in mode 2, dropping in
   (state 0xE; a summoned copy gives up instead). Returns 1 when spawned. */
int32_t m1_FlyerSpawn16B5F0(M1Fo321 *o, M1Fa321 *a, int32_t k, int32_t mode)
{
    M1Fp321 *p;
    int32_t neg = 0, i;
    float sc;
    uint32_t f;

    if (k < 0) {
        k &= 0xFF;
        neg = 1;
    }
    for (i = 0, p = m1_flyPool3F8A18; (intptr_t)p < (intptr_t)(m1_flyPool3F8A18 + 16); p++, i++)
        if (!(p->f0 & 1))
            goto found;
    return 0;
found:
    p = &m1_flyPool3F8A18[i];
    p->f0 |= 1;
    if (p == 0) return 0;
    a->flags74 = p;
    if (k == 0 && sub_000D9A70(0x48)) {
        p->f0 &= ~1u;
        return 0;
    }
    if (neg) p->f0 |= 0x800;
    a->cbb4 = (const void *)m1_FlyerFree169A00;
    a->cbbc = (const void *)m1_FlyerHit169800;
    a->cbc0 = (const void *)m1_FlyerThink16B320;
    a->cbc4 = (const void *)m1_FlyerMove169A50;
    a->cbc8 = m1_flyTabA31F218;
    a->cbcc = m1_flyTabB31F1D0;
    a->cbd0 = (const void *)b16_To12;
    sc = 1.0f;
    if (k != 2) sc = 2.0f;
    o->f78 = sc; o->f74 = sc; o->f70 = sc;
    o->f7c = 1.0f;
    i = sub_0001BC40(o);
    o->fb0 = o->f70 * 3.5f;
    o->fb4 = o->f70 * -3.0f;
    o->fa4 = o->f70 * 0.0f;
    o->fe8 = o->f70 * 2.7f;
    o->fdc = o->f70 * -2.7f;
    o->ffc = o->f70 * -5.0f;
    o->fd0 = i;
    o->f10c = o->f70 * 0.5f;
    o->f124 = 1;
    o->fec = 0;
    o->f118 = 0;
    a->f24 = 2;
    o->ff0 = 2;
    o->ff4 = 2;
    o->f11c = 1;
    o->f120 = 2;
    a->f28 = o->f70 * -4.0f;
    a->f2c = o->f70 * -7.0f;
    o->fc = (o->fc & ~0x20u) | 0xC0;
    o->f10 |= 0x80;
    switch (mode) {
    case 0:
        p->f0 |= 2;
    case 1:
        p->f0 |= 4;
        sub_001671D0(o, a, 0);
        return 1;
    case 2:
        f = p->f0;
        if (f & 0x800) {
            p->f0 = f & 0xFFFFF7FEu;
            return 0;
        }
        p->f0 = f | 0x1004;
        o->fc &= ~0x20u;
        o->f10 = (o->f10 & 0xFFFFFEBFu) | 1;
        sub_001671D0b(o, a, 0xE);
        return 1;
    }
    p->f0 &= ~1u;
    return 0;
}

typedef struct { uint32_t f0; float f4, f8, fc, f10, f14; uint8_t _18[4]; int32_t f1c; } M1Ft321;
typedef struct { uint8_t _0[0x50]; int32_t f50; uint8_t _54[0x20]; M1Ft321 *flags74; } M1Ta321;
typedef struct { uint8_t _0[0x60]; float pos60[4]; } M1To321;

extern float m1_frameTime42C858, m1_frameRate42C85C;
extern float m1_flyTimer3F8C18;
extern M1To321 *g_playerObj;
int  Stats_GetD8(void);
int  sub_000D9A70b(int k);
float r4_DistanceXZ(float *a, float *b);
float r4_DistanceXZb(float *a, float *b);
int32_t m1_NthNearest169BA0(M1To321 *o, int32_t n);        /* regargs: o=ECX */
int32_t m1_NthNearest169BA0b(M1To321 *o, int32_t n);
int  sub_001C7EE1(void);                                    /* rand */
void sub_001671D0c(M1To321 *o, M1Ta321 *a, int st);
void sub_001671D0d(M1To321 *o, M1Ta321 *a, int st);
void sub_001671D0e(M1To321 *o, M1Ta321 *a, int st);

/* 0x0016B320: flyer think: count down the recovery timer; when idle, start
   pending attacks (state 3) or drops (state 1). In the active states (1-7)
   track how long the player stays within 100 units (in stage 3, or always
   in stages 0x13-0x16) and after 120 units go alert; a heavy hit staggers
   it (state 6) unless already reacting; when alert aim at the extra point,
   while the guard timer runs keep the current point, the shared swoop
   timer (flag 2) re-arms every 180-300 units (target 0xD while running),
   and otherwise pick one of the three nearest points at random. */
void m1_FlyerThink16B320(M1To321 *o, M1Ta321 *a)
{
    M1To321 *pl = g_playerObj;
    M1Ft321 *t = a->flags74;
    int32_t m = Stats_GetD8();
    uint32_t f = t->f0;
    int32_t st, r, i;
    volatile int32_t vm;
    float g;

    if (f & 0x1000) return;
    if (t->f14 > 0.0f)
        t->f14 = t->f14 - m1_frameRate42C85C;
    st = a->f50;
    if (st == 0) {
        if (f & 0x10) {
            t->f0 = f & ~0x14u;
            sub_001671D0c(o, a, 3);
            return;
        }
        if (f & 0x400) {
            t->f0 = f & 0xFFFFFBFBu;
            sub_001671D0d(o, a, 1);
        }
        return;
    }
    if ((uint32_t)st >= 8) return;
    if (0.0f > t->f4)
        t->f8 = t->f8 - m1_frameRate42C85C;
    if (sub_000D9A70b(0xC4)) {
        t->f0 &= ~0x8000u;
        if (m == 3) {
            if (!(100.0f > r4_DistanceXZ(o->pos60, pl->pos60))) goto act;
            f = t->f0;
            t->fc = t->fc + m1_frameRate42C85C;
            t->f0 = f | 0x8000;
            if (!(t->fc > 120.0f / m1_frameTime42C858 * m1_frameRate42C85C)) goto act;
        } else {
            vm = m;
            if (vm <= 0x12 || vm > 0x16)
                goto act;
        }
        if (r4_DistanceXZb(o->pos60, pl->pos60) < 100.0f && !((f = t->f0) & 0x40)) {
            t->f0 = f | 0x20;
            t->f4 = 0.0f;
        }
    }
act:
    f = t->f0;
    if ((int8_t)(f >> 8) < 0) {
        st = a->f50;
        if (st != 6 && st != 5 && st != 7 && !(st == 4 && (f & 0x40))) {
            sub_001671D0e(o, a, 6);
            return;
        }
    }
    st = a->f50;
    if (st == 5 || st == 7) return;
    if (f & 0x40) {
        t->f1c = m1_NthNearest169BA0(o, -1);
        return;
    }
    if (t->f4 >= 0.0f) {
        t->f4 = t->f4 - m1_frameRate42C85C;
        t->f0 = f | 8;
        t->f1c = -1;
        return;
    }
    g = m1_flyTimer3F8C18;
    if (f & 2) {
        g = g - m1_frameRate42C85C;
        m1_flyTimer3F8C18 = g;
        if (0.0f - 5400.0f / m1_frameTime42C858 * m1_frameRate42C85C > g) {
            g = ((float)(sub_001C7EE1() % 0x78) + 180.0f) / m1_frameTime42C858 * m1_frameRate42C85C;
            m1_flyTimer3F8C18 = g;
        }
    }
    if (g >= 0.0f) {
        t->f1c = 0xD;
        return;
    }
    if (!(t->f0 & 8)) return;
    r = sub_001C7EE1() % 0x63;
    t->f0 &= ~8u;
    for (i = 0; i < 3; i++) {
        r -= 0x21;
        if (r < 0) {
            t->f1c = m1_NthNearest169BA0b(o, i + 3);
            return;
        }
    }
}
