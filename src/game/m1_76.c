/* Area m1, file 76: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Act76 { uint8_t unk00[0x10]; uint32_t flags10; } M1Act76;
typedef struct M1Rig76 { uint32_t unk00; uint32_t flags04; uint8_t unk08[0x18 - 8]; uint8_t fade18[0x1C]; } M1Rig76;
typedef struct M1Step76 {
    uint8_t unk000[0x20];
    int8_t  b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1Rig76 *rig278;           /* +0x278 */
} M1Step76;
typedef struct M1Cmd76 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd76;
typedef struct M1Cmd76I { uint8_t unk00[0x10]; int32_t i10, i14; } M1Cmd76I;
extern float m1_frameTime42C858;
void sub_00113090(void *o, void *h, int state);
void sub_00113C60(void *fade, float a, float b);
void *sub_00113430(void *h, int v);
void *sub_00113400(void *h, int v);

/* 0x0013E6B0: next state 0x21, clear o flag 0x20 and h +0x4C bits 0x130, rig flags 0x400004,
 * rig fade 20 (40 if h +0x20 bit 0) -> 255, command 3 = (frameTime * 2 deg, 0, 5 deg,
 * 60 deg), command 2 = (0, 4 or 6). */
void m1_RigStep13E6B0(M1Act76 *o, M1Step76 *h)
{
    M1Rig76 *r = h->rig278;
    M1Cmd76 *c;
    M1Cmd76I *d;
    sub_00113090(o, h, 0x21);
    o->flags10 &= ~0x20u;
    h->flags4C &= ~0x130u;
    r->flags04 |= 0x400004;
    sub_00113C60(r->fade18, (h->b20 & 1) ? 40.0f : 20.0f, 255.0f);
    c = (M1Cmd76 *)sub_00113430(h, 3);
    c->f10 = m1_frameTime42C858 * 0.034906585f;
    c->f14 = 0.0f;
    c->f18 = 0.087266468f;
    c->f1C = 1.0471976f;
    d = (M1Cmd76I *)sub_00113430(h, 2);
    d->i10 = 0;
    d->i14 = ((~h->b20 & 1) | 2) << 1;
}

typedef struct M1Pos76 { uint8_t unk00[0x60]; float pos60[4]; } M1Pos76;
typedef struct M1Obj128 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0x128 - 0x70]; uint8_t b128; } M1Obj128;
typedef struct M1StepL {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    int32_t state50;           /* +0x50 */
} M1StepL;
typedef struct M1DataL { uint8_t unk00[0x10]; float t10; } M1DataL;
extern float m1_frameRate42C85C;
extern M1Pos76 *g_playerObj;
float sub_001B2770(const float *a, const float *b);
int   sub_00087500(void);
float sub_001A3F30(float x);
void  sub_00113040(void *o, void *h, int state);

/* 0x0017C1F0: leash: timer +0x10 runs while o +0x128 bits 6; in states 3, 4 and 6 go to state 2
 * when 0x87500 is set, or (h +0x4C bit 0x400 clear) the player is 200+ away, 100+ apart in
 * height, or the timer reached 3 s. */
void m1_Leash17C1F0(M1Obj128 *o, M1StepL *h, M1DataL *d)
{
    if (o->b128 & 6)
        d->t10 += m1_frameRate42C85C;
    if (h->state50 >= 3 && (h->state50 <= 4 || h->state50 == 6)) {
        M1Pos76 *p = g_playerObj;
        if (sub_00087500() == 0) {
            if (h->flags4C & 0x400)
                return;
            if (!(sub_001B2770(o->pos60, p->pos60) >= 200.0f) &&
                !(sub_001A3F30(o->pos60[1] - p->pos60[1]) >= 100.0f) &&
                !(d->t10 >= 3.0f))
                return;
        }
        sub_00113040(o, h, 2);
    }
}

typedef struct M1StepB {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021;
    uint8_t b22;               /* +0x22 */
    uint8_t unk023[0x4C - 0x23];
    uint32_t flags4C;          /* +0x4C */
} M1StepB;
int sub_00139DB0(void *h);

/* 0x0013E4A0: spins unless h +0x22 bit 0; if 0x139DB0 holds, command 8 = (0x50 + bit, 13) and
 * state 0; otherwise o flag 0x20, clear h +0x4C bit 0x20, next state 3 or 5 (h +0x20 bit 0),
 * command 3 = (+-frameTime*2 deg, +-10 deg). */
void m1_RigStep13E4A0(M1Act76 *o, M1StepB *h)
{
    M1Cmd76 *c;
    float t;
    if (!(h->b22 & 1))
        for (;;) ;
    if (sub_00139DB0(h)) {
        M1Cmd76I *d = (M1Cmd76I *)sub_00113430(h, 8);
        d->i14 = 0xD;
        d->i10 = (h->b22 & 1) + 0x50;
        sub_00113040(o, h, 0);
        return;
    }
    o->flags10 |= 0x20;
    h->flags4C &= ~0x20u;
    sub_00113090(o, h, (-((h->b20 & 1) != 0) & 2) + 3);  /* 5 or 3 */
    c = (M1Cmd76 *)sub_00113400(h, 3);
    t = m1_frameTime42C858 * 0.034906585f;
    c->f10 = t;
    c->f18 = 0.17453294f;
    c->f14 = 0.0f - t;
    c->f1C = -0.17453294f;
}
