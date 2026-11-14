/* Area m1, file 102: sway variants. Names inferred. */
#include <stdint.h>

typedef struct M1Rig102 {
    uint8_t unk00[0xC];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
    uint8_t unk44[0x54 - 0x44];
    float   f54;               /* +0x54 */
} M1Rig102;
typedef struct M1Step102 { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig102 *rig278; } M1Step102;
typedef struct M1Cmd102 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd102;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int  sub_001456E0(void *o, void *h, int a, int b);
M1Cmd102 *sub_00113400(void *h, int v);
void sub_00185540(void *o);

/* 0x00157E80: enter state 0x15, rig +0xC = frameTime * 0.005, reset the rig quaternion, raise
 * rig +0x54 by 20 clamped to 0..200, clear h +0x4C bits 0x70, rig flags 0x40080, +-10 degree
 * sway at 2 degrees/frame, then 0x185540(o). */
void m1_Sway157E80(void *o, M1Step102 *h)
{
    M1Rig102 *r = h->rig278;
    M1Rig102 *p;
    M1Cmd102 *c;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    r->rate0C = m1_frameTime42C858 * 0.005f;
    r->q24[2] = 0.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    p = h->rig278;
    p->f54 = p->f54 + 20.0f;
    if (0.0f > p->f54)
        p->f54 = 0.0f;
    else if (p->f54 > 200.0f)
        p->f54 = 200.0f;
    h->flags4C &= ~0x70u;
    r->flags40 |= 0x40080;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.17453294f;
    c->f14 = -0.17453294f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    sub_00185540(o);
}

/* 0x00157480: as 0x157E80 but with quaternion z = -3 * frameRate, rig flag 0x80 only and no
 * 0x185540 call. */
void m1_Sway157480(void *o, M1Step102 *h)
{
    M1Rig102 *r = h->rig278;
    M1Rig102 *p;
    M1Cmd102 *c;
    float t;
    sub_001456E0(o, h, 0x15, 0);
    r->rate0C = m1_frameTime42C858 * 0.005f;
    r->q24[2] = 0.0f - m1_frameRate42C85C * 3.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    p = h->rig278;
    p->f54 = p->f54 + 20.0f;
    if (0.0f > p->f54)
        p->f54 = 0.0f;
    else if (p->f54 > 200.0f)
        p->f54 = 200.0f;
    h->flags4C &= ~0x70u;
    r->flags40 |= 0x80;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.17453294f;
    c->f14 = -0.17453294f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1Scene102 { uint8_t unk000[0x324]; int32_t mode324; } M1Scene102;
typedef struct M1Rig102T { uint8_t unk00[0x10]; float t10; int32_t i14; uint8_t unk18[0x54 - 0x18]; int16_t w54; } M1Rig102T;
typedef struct M1Step102T { uint8_t unk000[0x278]; M1Rig102T *rig278; } M1Step102T;
typedef struct M1Obj102T { uint8_t unk00[0x30]; void *anim30; } M1Obj102T;
extern float m1_stageTime3FE098;
M1Scene102 *sub_000E0770(void);
void *sub_000E23F0(int a, int b);
void sub_000F3BF0(void *o, float t, int v);
int  sub_000F5D00(void *o);
void sub_000832D0(void *a, int v);
void sub_00113040(void *o, void *h, int state);

/* 0x0017FD80: pulse: while the stage time is under 4.08, fire 0xF3BF0 on object 3/7 once after
 * 0.85 s and then every 0.225 s while the +0x54 count lasts; go to state 0 when 0xF5D00 holds,
 * or (scene mode 2 or 6) after playing clip 3. */
void m1_Pulse17FD80(M1Obj102T *o, M1Step102T *h)
{
    M1Rig102T *r = h->rig278;
    int k = sub_000E0770()->mode324;
    if (4.0799999f > m1_stageTime3FE098) {
        if (r->i14 == 0) {
            if (r->t10 > 0.85000002f) {
                sub_000F3BF0(sub_000E23F0(3, 7), 9.5238094f, 4);
                r->i14 = 1;
                r->t10 = 0.0f;
            } else {
                r->t10 += m1_frameRate42C85C;
            }
        } else if (r->w54 != 0) {
            if (r->t10 > 0.225f) {
                sub_000F3BF0(sub_000E23F0(3, 7), 9.5238094f, 4);
                r->w54--;
                r->t10 = 0.0f;
            } else {
                r->t10 += m1_frameRate42C85C;
            }
        }
    }
    if (sub_000F5D00(o)) {
        sub_00113040(o, h, 0);
        return;
    }
    if (k == 2 || k == 6) {
        sub_000832D0(o->anim30, 3);
        sub_00113040(o, h, 0);
    }
}

typedef struct M1Rig102R { uint32_t flags00; uint8_t unk04[0x50 - 4]; uint32_t flags50; } M1Rig102R;
typedef struct M1Step102R {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x6C - 0x50];
    int32_t snd6C;             /* +0x6C */
    void   *fx70;              /* +0x70 */
    uint8_t unk074[0x278 - 0x74];
    M1Rig102R *rig278;         /* +0x278 */
} M1Step102R;
typedef struct M1Obj102R { uint8_t unk000[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk014[0x13C - 0x14]; int32_t i13C; } M1Obj102R;
void sub_001134B0(void *h);
void sub_001561D0(void *rig, float a, float b);
void sub_00113AA0(void *o, void *h);
void sub_00113190(void *o, void *h, int v);
void sub_00048250(int snd);
void sub_0005BE30(int v);
void sub_00033A70(void *r);

/* 0x00154150: recover (rig flags at +0x50): 0x1134B0, o +0xC |= 0xE0, o +0x10 clears 0x137,
 * h +0x4C clears 0x100, rig +0 clears 0x17 and +0x50 clears 0x241140, tilt (-10, 10 *
 * frameRate); flag 0x10000 runs 0x113AA0, flag 0x100000 runs 0x113190(1); stop the sound,
 * 0x5BE30, free +0x70, state 0. */
void m1_Recover154150(M1Obj102R *o, M1Step102R *h)
{
    M1Rig102R *r = h->rig278;
    uint32_t f;
    sub_001134B0(h);
    o->flags0C |= 0xE0;
    o->flags10 &= ~0x137u;
    h->flags4C &= ~0x100u;
    r->flags00 &= ~0x17u;
    r->flags50 &= ~0x241140u;
    sub_001561D0(r, -10.0f, m1_frameRate42C85C * 10.0f);
    if (r->flags50 & 0x10000) {
        sub_00113AA0(o, h);
        h->flags4C |= 0x200;
        r->flags50 &= ~0x10000u;
    }
    f = r->flags50;
    if (f & 0x100000) {
        r->flags50 = f & ~0x100000u;
        sub_00113190(o, h, 1);
    }
    if (h->snd6C != -1) {
        sub_00048250(h->snd6C);
        h->snd6C = -1;
    }
    sub_0005BE30(o->i13C);
    if (h->fx70 != 0) {
        sub_00033A70(h->fx70);
        h->fx70 = 0;
    }
    sub_00113040(o, h, 0);
}

typedef struct M1Obj102C { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x20 - 0x14]; uint8_t *mdl20; } M1Obj102C;
typedef struct M1Step102C {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
} M1Step102C;
int  sub_00139FE0(void *o, void *h);
int  sub_000494D0(int id, const void *pos, int c);
int  aab_Rand(void);

/* 0x0013F040: while 0x139FE0 holds: phase 0 plays sound 0xA5 at the model and waits 22
 * frames, phase 1 goes to 2, phase 2 clears o flags 5, sets h +0x4C bits 0x18 and picks state
 * 0x29 (bit 0, 1 in 4), 0x12 (no bit, 1 in 8) or 0xC with the wait cleared. */
void m1_RigStep13F040(M1Obj102C *o, M1Step102C *h)
{
    if (!sub_00139FE0(o, h))
        return;
    switch (h->phase58) {
    case 0:
        sub_000494D0(0xA5, o->mdl20 + 0x30, 0);
        h->wait74 = 22.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        h->phase58++;
        break;
    case 1:
        h->phase58 = 2;
        break;
    case 2:
        o->flags10 &= ~5u;
        h->flags4C |= 0x18;
        if (h->b20 & 1) {
            if (aab_Rand() % 4 < 1) {
                sub_00113040(o, h, 0x29);
                return;
            }
        } else {
            if (aab_Rand() % 8 < 1) {
                sub_00113040(o, h, 0x12);
                return;
            }
        }
        h->wait74 = 0.0f;
        sub_00113040(o, h, 0xC);
        break;
    }
}
