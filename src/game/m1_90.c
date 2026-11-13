/* Area m1, file 90: rig resets. Names inferred. */
#include <stdint.h>

typedef struct M1Rig90 { uint32_t flags00; float f04; float f08; uint8_t unk0C[0x40 - 0xC]; uint32_t flags40; } M1Rig90;
typedef struct M1Step90 {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x6C - 0x50];
    int32_t snd6C;             /* +0x6C */
    void   *fx70;              /* +0x70 */
    uint8_t unk074[0x278 - 0x74];
    M1Rig90 *rig278;           /* +0x278 */
} M1Step90;
typedef struct M1Obj90 { uint8_t unk000[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk014[0x13C - 0x14]; int32_t i13C; } M1Obj90;
extern float m1_frameRate42C85C;
void sub_001134B0(void *h);
void sub_00113AA0(void *o, void *h);
void sub_00048250(int snd);
void sub_0005BE30(int v);
void sub_00033A70(void *r);
void sub_00113040(void *o, void *h, int state);

/* 0x00165480: recover: 0x1134B0, o +0xC |= 0xE0, o +0x10 clears 0x135, h +0x4C clears 0x100,
 * rig +0x40 clears 0x40A86 and +0 clears 0x17, rig +4 = -10, +8 = 10 * frameRate; rig flag
 * 0x4000 runs 0x113AA0 (h +0x4C |= 0x200) and is cleared; stop sound +0x6C, 0x5BE30(o +0x13C),
 * free +0x70, state 0. */
void m1_Recover165480(M1Obj90 *o, M1Step90 *h)
{
    M1Rig90 *r = h->rig278;
    uint32_t f;
    sub_001134B0(h);
    o->flags0C |= 0xE0;
    o->flags10 &= ~0x135u;
    h->flags4C &= ~0x100u;
    f = r->flags40 & ~0x40A86u;
    r->flags40 = f;
    r->flags00 &= ~0x17u;
    r->f04 = -10.0f;
    r->f08 = m1_frameRate42C85C * 10.0f;
    if (f & 0x4000) {
        sub_00113AA0(o, h);
        h->flags4C |= 0x200;
        r->flags40 &= ~0x4000u;
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

typedef struct M1Rig90S {
    uint8_t unk00[0xC];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
} M1Rig90S;
typedef struct M1Step90S { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig90S *rig278; } M1Step90S;
typedef struct M1Cmd90 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd90;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
M1Cmd90 *sub_00113400(void *h, int v);

/* 0x00156A30: enter state 1, rig quaternion z = -35 * frameRate, rig +0xC = frameTime *
 * 0.005, o flag 0x20, h +0x4C |= 0x70, rig flag 0x200, +-5 degree sway at 2 degrees/frame. */
void m1_Sway156A30(M1Obj90 *o, M1Step90S *h)
{
    M1Rig90S *r = h->rig278;
    M1Cmd90 *c;
    float t;
    sub_001456E0(o, h, 1, 0);
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    r->q24[2] = 0.0f - m1_frameRate42C85C * 35.0f;
    r->q24[3] = 1.0f;
    o->flags10 |= 0x20;
    h->flags4C |= 0x70;
    r->flags40 |= 0x200;
    t = m1_frameTime42C858 * 0.034906585f;
    c = sub_00113400(h, 1);
    c->f10 = 0.087266468f;
    c->f14 = -0.087266468f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1Obj90M { uint8_t unk00[0x80]; float vel80[4]; } M1Obj90M;
typedef struct M1Step90M { uint8_t unk000[0x100]; float speed100; } M1Step90M;
typedef struct M1Data90 { uint8_t unk00[8]; float t08; uint8_t unk0C[0x10 - 0xC]; float max10; uint8_t unk14[0x1C - 0x14]; float end1C; } M1Data90;
void  sub_00113600(void *o, void *h, float *dir);
float sub_001A3F50(float x);
void  sub_001ADBA0(float *d, const float *s, float k);
void  sub_001ADAF0(float *d, const float *a, const float *b);
void  sub_00113370(void *h, void *d);

/* 0x001395C0: move: velocity += the flat unit direction from 0x113600 times the speed
 * (+0x100 capped at max +0x10); when the timer +8 reaches +0x1C run 0x113370. */
void m1_Move1395C0(M1Obj90M *o, M1Step90M *h, M1Data90 *d)
{
    float spd = h->speed100;
    float v[4];
    float inv;
    if (spd > d->max10)
        spd = d->max10;
    sub_00113600(o, h, v);
    inv = 1.0f / sub_001A3F50(v[0] * v[0] + v[2] * v[2]);
    v[0] = inv * v[0];
    v[1] = 0.0f;
    v[2] = inv * v[2];
    v[3] = 0.0f;
    sub_001ADBA0(v, v, spd);
    sub_001ADAF0(o->vel80, o->vel80, v);
    if (d->t08 >= d->end1C)
        sub_00113370(h, d);
}
