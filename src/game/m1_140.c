/* Area m1, file 140: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Act140 {
    uint8_t unk00[0xE0]; int32_t step0E0; uint8_t unkE4[0x12C - 0xE4]; int32_t anim12C;
    uint8_t unk130[0x150 - 0x130]; uint32_t flags150;
} M1Act140;
int  m1_ActReady0CF070(M1Act140 *o);
int  m1_ActHp0CF1A0(M1Act140 *o);
void sub_000BD4D0(M1Act140 *o, int st);
void sub_000AA2E0(int id);

/* 0xBF280: three-step wake-up sequence for an actor. */
void m1_ActWake0BF280(M1Act140 *o) {
    switch (o->step0E0) {
    case 0:
        o->flags150 |= 0x28200001; o->anim12C = 0x53; o->step0E0 = 1;
        return;
    case 1:
        if (o->flags150 & 0x400080) {
            sub_000AA2E0(0x10);
            o->anim12C = 0x54; o->step0E0++;
        }
        return;
    case 2:
        if (m1_ActReady0CF070(o) != 0) {
            o->flags150 &= ~0x200000u; o->anim12C = 0;
            if (m1_ActHp0CF1A0(o) > 0) { sub_000BD4D0(o, 7); return; }
            sub_000BD4D0(o, 1);
        }
        return;
    }
}

typedef struct M1Ramp140 {
    uint8_t unk00[0x24]; uint32_t flags24; float lo28; float hi2C;
    uint8_t k30[0x18]; uint8_t k48[0x18]; uint8_t k60[0x18]; uint8_t k78[0x18];
} M1Ramp140;
typedef struct M1In140 { uint8_t unk00[0x10]; float v10; } M1In140;
float m1_CurveAt07F650(void *curve, float t);
void  sub_00036F40(float a, float b, float c, float d);

/* 0x8F7E0: map an input into a 0..1 ramp and drive four colour curves. */
int m1_RampEval08F7E0(M1Ramp140 *c, M1In140 *in) {
    float t, v, d, a, b, e, f;
    if (!(c->flags24 & 1)) return 0;
    v = in->v10;
    if (c->lo28 > v) t = 0.0f;
    else if (v > c->hi2C) t = 1.0f;
    else {
        d = c->hi2C - c->lo28;
        if (d > 0.0f) t = (v - c->lo28) / d; else t = 0.0f;
    }
    a = m1_CurveAt07F650(c->k30, t); b = m1_CurveAt07F650(c->k48, t);
    e = m1_CurveAt07F650(c->k60, t); f = m1_CurveAt07F650(c->k78, t);
    sub_00036F40(a, b, e, f);
    return 0;
}

typedef struct M1Ent140 { uint8_t unk00[0x64]; float y64; uint8_t unk68[0x128 - 0x68]; uint32_t f128; } M1Ent140;
typedef struct M1Room140 { uint8_t unk00[0x12C]; M1Ent140 *ents[8]; } M1Room140;
extern uint8_t m1_stats41FEC0[];
extern float m1_statF41FFD4;
extern float m1_statF420008;
extern float m1_statF42000C;
void sub_000A21C0(M1Room140 *r, void *out);
void sub_000F5D40(float *d, const void *s);
int  sub_000CF420(void *s, int id, int a);

/* 0xA23E0: drop room entities to the floor height of the room anchor. */
void m1_RoomFloor0A23E0(M1Room140 *r) {
    struct { uint8_t *p; float v[4]; } l;
    M1Ent140 **pe; M1Ent140 *e; int i;
    l.v[0] = 0.0f; l.v[1] = 0.0f; l.v[2] = 0.0f; l.p = 0; l.v[3] = 1.0f;
    sub_000A21C0(r, &l.p);
    sub_000F5D40(l.v, l.p + 0x70);
    pe = r->ents;
    for (i = 8; i != 0; i--, pe++) {
        e = *pe;
        if (e == 0 || (e->f128 & 8)) continue;
        if (sub_000CF420(m1_stats41FEC0, 0x300, 0) != 0) {
            if (e->y64 > l.v[1] && !(0.0f > m1_statF41FFD4)) {
                e->y64 = l.v[1]; m1_statF420008 = 0.0f; m1_statF42000C = 0.0f;
            }
        } else e->y64 = l.v[1];
    }
}
