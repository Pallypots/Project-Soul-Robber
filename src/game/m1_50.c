/* Area m1, file 50: gauges and rig timers. Names inferred. */
#include <stdint.h>

typedef struct M1RigG { uint8_t unk00[4]; uint32_t flags04; } M1RigG;
typedef struct M1StepG { uint8_t unk000[0x278]; M1RigG *rig278; } M1StepG;
typedef struct M1Gauge70 { uint8_t unk00[0x70]; float f70, f74, f78, f7C; } M1Gauge70;
typedef struct M1Drain { int32_t state00; uint8_t unk04[0xC]; float secs10; } M1Drain;
extern float m1_fps42C964;
void sub_00113370(void *h, M1Drain *d);

/* 0x0011E700: drains the gauge by 1 / (seconds * fps) per call (clamped at 0, copied to
 * +0x70..+0x78, +0x7C = 1.0); when empty sets rig flag 0x400, marks the drain done (1)
 * and calls 0x113370, otherwise marks it running (2). */
void m1_GaugeDrain11E700(M1Gauge70 *o, M1StepG *h, M1Drain *d)
{
    M1RigG *r;
    float t = d->secs10 * m1_fps42C964;
    float v;
    t = 1.0f / t;
    v = o->f70 - t;
    r = h->rig278;
    v = (v < 0.0f) ? 0.0f : v;
    o->f78 = v;
    o->f74 = v;
    o->f70 = v;
    o->f7C = 1.0f;
    if (v <= 0.0f) {
        r->flags04 |= 0x400;
        if (d->state00 != 0)
            d->state00 = 1;
        sub_00113370(h, d);
    } else {
        if (d->state00 != 0)
            d->state00 = 2;
    }
}

typedef struct M1RigQ {
    uint8_t unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint8_t unk010[0x164 - 0x10];
    float   q164[4];           /* +0x164 */
    uint8_t unk174[0x180 - 0x174];
    float   f180;              /* +0x180 */
} M1RigQ;
typedef struct M1StepQ {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1RigQ *rig278;            /* +0x278 */
} M1StepQ;
typedef struct M1ObjQ { uint8_t unk00[0xC]; uint32_t flags0C, flags10; } M1ObjQ;
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_0001D4E0(void *o);

/* 0x0012F2E0: 0x1456E0(0x1B) (0x1D4E0 on 1), rig quaternion +0x164 = (0, 0, 0, 1); with
 * rig flag 1 sets o flags 5, and with rig flag 0x200 as well clears o +0xC bits 0xE0,
 * sets o flag 0x100 and rig flag 4; always h +0x4C |= 0x70. */
void m1_RigIdle12F2E0(M1ObjQ *o, M1StepQ *h)
{
    M1RigQ *r = h->rig278;
    M1RigQ *p;
    if (sub_001456E0(o, h, 0x1B, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    if (r->flags0C & 1) {
        o->flags10 |= 5;
        if (r->flags0C & 0x200) {
            o->flags0C &= ~0xE0u;
            o->flags10 |= 0x100;
            r->flags0C |= 4;
        }
    }
    h->flags4C |= 0x70;
}

extern float m1_frameRate42C85C;

/* 0x0012F850: 0x1456E0(0x28) (0x1D4E0 on 1), rig spin quaternion +0x164 =
 * (0, frame rate * -100, 0 - frame rate * -70, 1), o flag 1, h +0x4C |= 0x70,
 * rig flag 0x10000. */
void m1_RigSpin12F850(M1ObjQ *o, M1StepQ *h)
{
    M1RigQ *r = h->rig278;
    M1RigQ *p;
    float fr;
    if (sub_001456E0(o, h, 0x28, 0) == 1)
        sub_0001D4E0(o);
    fr = m1_frameRate42C85C;
    p = h->rig278;
    p->q164[1] = fr * -100.0f;
    p->q164[0] = 0.0f;
    p->q164[2] = 0.0f - fr * -70.0f;
    p->q164[3] = 1.0f;
    o->flags10 |= 1;
    h->flags4C |= 0x70;
    r->flags0C |= 0x10000;
}

typedef struct M1Fade1C { int32_t state00; uint8_t unk04[0xC]; float step10; uint8_t unk14[8]; float amt1C; } M1Fade1C;
void sub_000EE760(void *o, float a);

/* 0x001399D0: fade step: +0x1C += +0x10 (capped at 0.5), step becomes -0.002, sets o's
 * alpha to 1 - amount (capped at 1.0); once the amount reaches 0 marks it done (1) and
 * calls 0x113370, otherwise marks it running (2). */
void m1_FadeStep1399D0(void *o, void *h, M1Fade1C *f)
{
    float v = f->step10 + f->amt1C;
    float a;
    f->amt1C = v;
    if (v > 0.5f)
        f->amt1C = 0.5f;
    a = 1.0f - f->amt1C;
    f->step10 = -0.002f;
    if (a > 1.0f)
        a = 1.0f;
    sub_000EE760(o, a);
    if (f->amt1C <= 0.0f) {
        if (f->state00 != 0)
            f->state00 = 1;
        sub_00113370(h, (M1Drain *)f);
    } else {
        if (f->state00 != 0)
            f->state00 = 2;
    }
}

typedef struct M1RigB {
    uint8_t unk00[0x50];
    uint32_t flags50;          /* +0x50 */
    uint8_t unk54[4];
    int32_t f58;               /* +0x58 */
    uint8_t unk5C[0x64 - 0x5C];
    float   f64, f68;          /* +0x64 */
} M1RigB;
typedef struct M1StepB {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t state58;           /* +0x58 */
    uint8_t unk05C[0x278 - 0x5C];
    M1RigB *rig278;            /* +0x278 */
} M1StepB;
typedef struct M1ObjB { uint8_t unk00[0x10]; uint32_t flags10; } M1ObjB;
extern float m1_frameTime42C858;
void sub_00156180(void *rig, int a, int b, int c, float t);
void sub_001561D0(void *rig, float a, float b);
void sub_00113190(void *o, void *h, int v);
void sub_000414A0(int v);

/* 0x00146940: 0x1456E0(0x22), rig blend 0x156180(0, 0, 0, frame time * 0.003), rig turn
 * 0x1561D0(-15, frame rate * 10), clear h +0x4C bits 0x70, rig flags 0x200040, rig +0x64 = 0,
 * 0x113190(0), then rig flag 0x100000. */
void m1_RigBlend146940(M1ObjB *o, M1StepB *h)
{
    M1RigB *r = h->rig278;
    sub_001456E0(o, h, 0x22, 0);
    sub_00156180(r, 0, 0, 0, m1_frameTime42C858 * 0.003f);
    sub_001561D0(r, -15.0f, m1_frameRate42C85C * 10.0f);
    h->flags4C &= ~0x70u;
    r->flags50 |= 0x200040;
    r->f64 = 0.0f;
    sub_00113190(o, h, 0);
    r->flags50 |= 0x100000;
}

/* 0x0014F360: 0x1456E0(0x13), rig blend 0x156180(0, 0, 0, frame time * 0.003), o flag 0x20,
 * clear h +0x4C bits 0x70, 0x414A0(1), rig +0x58 = 0, rig +0x68 += 40 clamped to 0..200,
 * state 10. */
void m1_RigBlend14F360(M1ObjB *o, M1StepB *h)
{
    M1RigB *r = h->rig278;
    M1RigB *p;
    float v;
    sub_001456E0(o, h, 0x13, 0);
    sub_00156180(r, 0, 0, 0, m1_frameTime42C858 * 0.003f);
    o->flags10 |= 0x20;
    h->flags4C &= ~0x70u;
    sub_000414A0(1);
    r->f58 = 0;
    p = h->rig278;
    v = p->f68 + 40.0f;
    p->f68 = v;
    if (v < 0.0f)
        p->f68 = 0.0f;
    else if (v > 200.0f)
        p->f68 = 200.0f;
    h->state58 = 10;
}

int aab_Rand(void);

/* 0x0012F380: 0x1456E0(0x38) (0x1D4E0 on 1), rig quaternion +0x164 = (0, 0, 0, 1),
 * o flags |= 0x105 with rig flag 1, clear h +0x4C bits 0x70, rig +0x180 =
 * (rand / 32767 + 1) * 10. */
void m1_RigIdle12F380(M1ObjQ *o, M1StepQ *h)
{
    M1RigQ *r = h->rig278;
    M1RigQ *p;
    if (sub_001456E0(o, h, 0x38, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    if (r->flags0C & 1)
        o->flags10 |= 0x105;
    h->flags4C &= ~0x70u;
    r->f180 = ((float)aab_Rand() * (1.0f / 32767.0f) + 1.0f) * 10.0f;
}

/* 0x0012F420: 0x1456E0(0x13) (0x1D4E0 on 1), rig quaternion +0x164 = (0, 0, 0, 1),
 * 0x414A0(1); with rig flag 1 sets o flags 5, and with rig flag 0x200 as well sets o flag
 * 0x100, clears o +0xC bits 0xE0 and sets rig flag 4. */
void m1_RigIdle12F420(M1ObjQ *o, M1StepQ *h)
{
    M1RigQ *r = h->rig278;
    M1RigQ *p;
    if (sub_001456E0(o, h, 0x13, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q164[2] = 0.0f;
    p->q164[1] = 0.0f;
    p->q164[0] = 0.0f;
    p->q164[3] = 1.0f;
    sub_000414A0(1);
    if (r->flags0C & 1) {
        o->flags10 |= 5;
        if (r->flags0C & 0x200) {
            o->flags10 |= 0x100;
            o->flags0C &= ~0xE0u;
            r->flags0C |= 4;
        }
    }
}
