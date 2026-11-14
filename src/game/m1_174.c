/* Area m1, file 174: one-slot play start (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Cue174 { uint8_t unk00[0xC]; int8_t bC; uint8_t bD; uint8_t unk0E[2]; uint16_t w10; uint16_t w12; uint16_t w14; uint8_t unk16[2]; } M1Cue174;
typedef struct M1Sl174 { int32_t on0; int32_t a4; int32_t a8; int32_t idC; int32_t i10; uint8_t b14; uint8_t unk15[0xB]; int32_t w20; int32_t w24; int32_t w28; int32_t z2C; } M1Sl174;
extern M1Cue174 m1_cues3317A8[1];
extern M1Sl174 m1_cueSlots401AF8[1];

/* 0x19A830: start cue id (only 0 is valid; hangs otherwise) in the single play slot; -1 when the slot is busy. */
int m1_CueStart19A830(int id) {
    volatile int k = id; M1Cue174 *e; M1Sl174 *s; int i;
    if (k <= -1 || k >= 1) for (;;) ;
    { M1Cue174 *volatile pe = &m1_cues3317A8[id]; e = pe; }
    for (i = 0, s = m1_cueSlots401AF8; i < 1; i++, s++)
        if (s->on0 == 0) break;
    if (i >= 1) return -1;
    s->idC = id;
    s->b14 = e->bD;
    s->i10 = e->bC;
    s->w20 = e->w10;
    s->w24 = e->w12;
    s->on0 = 1;
    s->a4 = 1;
    s->a8 = -1;
    s->w28 = e->w14;
    s->z2C = 0;
    return i;
}

typedef struct M1Eh174 { int32_t x0; int32_t x4; int32_t x8; int16_t k0C; int16_t s0E; } M1Eh174;
typedef struct M1Ev174 { uint8_t unk00[0xC]; M1Eh174 h; } M1Ev174;
void m1_HitWarp0F6E20(M1Eh174 *h);
void m1_EvAnimA0F41C0(M1Eh174 *h);
void m1_EvWarp0F0430(int x, int y, int z);
void m1_EvLog0E3FF0(int k, int s);
void m1_EvRun0E4050(int k, int s, int x, int y, int z);

/* 0xEA170: dispatch a script event: kind 3 with sub 3..7 has special handlers, everything else is logged and run. */
void m1_EvDispatch0EA170(void *unused, M1Ev174 *ev) {
    M1Eh174 *h; volatile int k;
    if (ev == 0) return;
    h = &ev->h;
    k = h->k0C;
    if (k == 3 && h->s0E == 3) { warp: m1_HitWarp0F6E20(h); return; }
    if (k == 3 && h->s0E == 4) goto warp;
    if (k == 3 && h->s0E == 5) goto warp;
    if (k == 3 && h->s0E == 6) { m1_EvAnimA0F41C0(h); return; }
    if (k == 3 && h->s0E == 7) { m1_EvWarp0F0430(h->x0, h->x4, h->x8); return; }
    m1_EvLog0E3FF0(h->k0C, h->s0E);
    m1_EvRun0E4050(h->k0C, h->s0E, h->x0, h->x4, h->x8);
}

typedef struct M1Rg174 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0xC]; uint8_t t14[0x18]; float t2C; } M1Rg174;
typedef struct M1Ai174 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x278 - 0x50]; M1Rg174 *rig278; } M1Ai174;
int  sub_001C7EE1(void);
void sub_00113090(void *o, M1Ai174 *e, int st);
void sub_00113CB0(void *t, float v, int z);

/* 0x11A660: enemy flinch: toggle the stagger flag (20-frame lockout), enter state 0x15, random 70..110 frame wait. */
void m1_AiFlinch11A660(void *o, M1Ai174 *e) {
    M1Rg174 *r = e->rig278; uint32_t f;
    f = r->f4 & ~0x10u;
    *(volatile uint32_t *)&r->f4 = f;
    if ((f & 8) && 0.0f >= r->t2C) f &= ~8u;
    else { f |= 8; r->t2C = 20.0f; }
    r->f4 = f;
    e->flags4C &= ~0x10u;
    sub_00113090(o, e, 0x15);
    sub_00113CB0(r->t14, (float)(sub_001C7EE1() % 4001) * 0.00999999978f + 70.0f, 0);
}
