/* Area m1, file 92: effect launches. Names inferred. */
#include <stdint.h>

typedef struct M1Pl92 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl92;
typedef struct M1Obj92 { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[4]; } M1Obj92;
typedef struct M1Step92 { uint8_t unk00[0x4C]; uint32_t flags4C; } M1Step92;
extern M1Pl92 *g_playerObj;
void  sub_0013A120(void *o, int a, int *out);
void  sub_001AD9F0(float *out, const float *a, const float *b);
void  sub_001AD7E0(float *out, const float *v);
void  sub_001ADBA0(float *d, const float *s, float k);
void *sub_00035D80(void *o, int a, int b);
void  sub_001ADAF0(float *d, const float *a, const float *b);
void  sub_00034E00(void *fx, const float *pos, const float *dir, const float *up);
int   sub_000494D0(int id, const void *pos, int c);

/* 0x00178080: blast: o flags (+0xC clear 0x20, +0x10 clear 0x20 set 0xD), clear h +0x4C bit
 * 0x1000000, 0x13A120(1), effect 3/3 placed 10 out from the object away from the player
 * facing that way (up (0,1,0,1)), sound 0x1A. */
void m1_Blast178080(M1Obj92 *o, M1Step92 *h)
{
    int id;
    float up[4];
    float d[4];
    float p[4];
    void *fx;
    o->flags0C &= ~0x20u;
    o->flags10 = (o->flags10 & ~0x20u) | 0xD;
    h->flags4C &= ~0x1000000u;
    id = -1;
    sub_0013A120(o, 1, &id);
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 1.0f;
    sub_001AD9F0(d, o->pos60, g_playerObj->pos60);
    sub_001AD7E0(d, d);
    sub_001ADBA0(p, d, 10.0f);
    fx = sub_00035D80(o, 3, 3);
    sub_001ADAF0(p, p, o->pos60);
    sub_00034E00(fx, p, d, up);
    sub_000494D0(0x1A, o->pos60, 0);
}

int   sub_001456E0(void *o, void *h, int a, int b);
void  sub_0001D4E0(void *o);

typedef struct M1Rig92S { uint8_t unk000[8]; uint32_t flags08; uint8_t unk00C[0x160 - 0xC]; float q160[4]; } M1Rig92S;
typedef struct M1Step92S { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig92S *rig278; } M1Step92S;
typedef struct M1Cmd92 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd92;
extern float m1_frameTime42C858;
M1Cmd92 *sub_00113400(void *h, int v);

/* 0x00136B90: sway (rig quaternion +0x160), state 0x16, o +0xC clears 0xE0, o +0x10 |= 5,
 * h +0x4C |= 0x70, rig +8 |= 6, +-5 degrees at frameTime * pi/32. */
void m1_Sway136B90(M1Obj92 *o, M1Step92S *h)
{
    M1Rig92S *r = h->rig278;
    M1Rig92S *p;
    M1Cmd92 *c;
    float t;
    if (sub_001456E0(o, h, 0x16, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q160[2] = 0.0f;
    p->q160[1] = 0.0f;
    p->q160[0] = 0.0f;
    p->q160[3] = 1.0f;
    o->flags0C &= ~0xE0u;
    o->flags10 |= 5;
    h->flags4C |= 0x70;
    r->flags08 |= 6;
    t = m1_frameTime42C858 * 0.098174773f;
    c = sub_00113400(h, 1);
    c->f10 = 0.087266468f;
    c->f14 = -0.087266468f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}
