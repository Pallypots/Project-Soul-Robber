/* Area m1, file 97: refill and landing steps. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd97I { uint8_t unk00[0x10]; int32_t i10, i14; } M1Cmd97I;
typedef struct M1Cmd97 { uint8_t unk00[0x10]; float f10; } M1Cmd97;
typedef struct M1Step97 {
    uint8_t unk00[0x58];
    int32_t phase58;           /* +0x58 */
    uint8_t unk5C[0x64 - 0x5C];
    int32_t state64;           /* +0x64 */
    uint8_t unk68[0x74 - 0x68];
    float   wait74;            /* +0x74 */
    uint8_t unk78[0x7C - 0x78];
    float   t7C;               /* +0x7C */
} M1Step97;
typedef struct M1Anim97 { uint8_t unk00[0xB8]; uint32_t flagsB8; } M1Anim97;
typedef struct M1Clip97 { uint8_t unk00[0x14]; M1Anim97 *anim14; } M1Clip97;
typedef struct M1Obj97 { uint8_t unk00[0x30]; M1Clip97 *clip30; uint8_t unk34[0x60 - 0x34]; float pos60[4]; uint8_t unk70[0x128 - 0x70]; uint8_t b128; } M1Obj97;
void *sub_00113400(void *h, int v);
void *sub_001133E0(void *h, int v);
int  sub_0017AE00(void);
void *sub_00036750(void *o, int b);
int  sub_000494D0(int id, const void *pos, int c);
void sub_0005EB10(int a, int b);
void sub_00113040(void *o, void *h, int state);
void sub_00113090(void *o, void *h, int state);

/* 0x0017BA50: refill command 2 as 0x17B9A0; phase 0 goes to phase 1 once +0x7C >= 0; phase 1
 * on landing (o +0x128 bits 0x18) clears clip flag 2, re-enters the current state, then
 * state 6 (count left, command 3 = 0) or state 3 with a 2 s wait. */
void m1_RefillLand17BA50(M1Obj97 *o, M1Step97 *h)
{
    M1Cmd97I *c = (M1Cmd97I *)sub_00113400(h, 2);
    int n;
    if (c->i10 <= 0) {
        c->i14 = -1;
        n = sub_0017AE00();
        if (n > 0) {
            c->i10 = n;
            c->i14 = -1;
            sub_00036750(o, 0);
            sub_000494D0(0x59, o->pos60, 0);
            sub_0005EB10(0, 3);
        }
    }
    switch (h->phase58) {
    case 0:
        if (h->t7C >= 0.0f)
            h->phase58 = 1;
        break;
    case 1:
        if (o->b128 & 0x18) {
            o->clip30->anim14->flagsB8 &= ~2u;
            sub_00113090(o, h, h->state64);
            if (c->i10 > 0) {
                sub_00113040(o, h, 6);
                ((M1Cmd97 *)sub_001133E0(h, 3))->f10 = 0.0f;
            } else {
                sub_00113040(o, h, 3);
                h->wait74 = 2.0f;
            }
        }
        break;
    }
}


typedef struct M1Rig97S { uint8_t unk000[8]; int8_t b08; uint8_t unk009[3]; uint8_t unk00C[0x160 - 0xC]; float q160[4]; } M1Rig97S;
typedef struct M1Step97S { uint8_t unk000[0x4C]; uint32_t flags4C; uint8_t unk050[0x278 - 0x50]; M1Rig97S *rig278; } M1Step97S;
typedef struct M1Obj97S { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } M1Obj97S;
typedef struct M1Cmd97S { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd97S;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
void sub_000414A0(int v);

/* 0x001371F0: sway (rig quaternion +0x160), state 0x13, o flags 5, h +0x4C |= 0x70,
 * 0x414A0(1); rig byte +8 bit 7 clears o bits 0xE0 and sets rig bit 4; +-5 degrees at
 * frameTime * pi/24. */
void m1_Sway1371F0(M1Obj97S *o, M1Step97S *h)
{
    M1Rig97S *r = h->rig278;
    M1Rig97S *p;
    M1Cmd97S *c;
    float t;
    if (sub_001456E0(o, h, 0x13, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q160[2] = 0.0f;
    p->q160[1] = 0.0f;
    p->q160[0] = 0.0f;
    p->q160[3] = 1.0f;
    o->flags10 |= 5;
    h->flags4C |= 0x70;
    sub_000414A0(1);
    if (r->b08 < 0) {
        o->flags0C &= ~0xE0u;
        *(uint32_t *)&r->b08 |= 4;
    }
    t = m1_frameTime42C858 * 0.1308997f;
    c = (M1Cmd97S *)sub_00113400(h, 1);
    c->f10 = 0.087266468f;
    c->f14 = -0.087266468f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}

typedef struct M1Mov97 {
    uint8_t unk00[0xA8];
    int32_t iA8;               /* +0xA8 */
    uint8_t unkAC[0xB4 - 0xAC];
    float   fB4, fB8, fBC, fC0, fC4;   /* +0xB4..+0xC4 */
    uint8_t unkC8[0xCC - 0xC8];
    float   fCC;               /* +0xCC */
} M1Mov97;
typedef struct M1Obj97B { uint8_t unk00[0x50]; float f50; } M1Obj97B;
extern float m1_fps42C964;
extern float m1_frameRate42C85C;
void sub_000F3B00(void *o, int v);
void sub_000F3B30(void *o, int v);
void sub_000F3F00(void *o, int v);

/* 0x00109B10: bounce off: reverse and damp +0xBC (-0.4) and +0xC0 (0.4), clear +0xA8, rise
 * +0xB4 = -BC / (fps * 0.3), clear +0xB8/+0xC4, spin +0xCC = (5 pi - o +0x50) * frameRate with
 * its sign flipped unless it was positive, then 0xF3B00(0x44), 0xF3B30(0x20), 0xF3F00(0). */
void m1_BounceOff109B10(M1Obj97B *o, M1Mov97 *s)
{
    float a;
    s->fBC = s->fBC * -0.40000001f;
    s->fC0 = s->fC0 * 0.40000001f;
    s->iA8 = 0;
    a = s->fBC;
    s->fB4 = a * -1.0f / (m1_fps42C964 * 0.30000001f);
    s->fB8 = 0.0f;
    if (s->fCC > 0.0f)
        s->fCC = (15.707964f - o->f50) * m1_frameRate42C85C;
    else
        s->fCC = (15.707964f - o->f50) * m1_frameRate42C85C * -1.0f;
    s->fC4 = 0.0f;
    sub_000F3B00(o, 0x44);
    sub_000F3B30(o, 0x20);
    sub_000F3F00(o, 0);
}

typedef struct M1Rig97N { uint32_t unk00; uint32_t flags04; uint8_t unk08[0x24 - 8]; int32_t hits24; uint8_t unk28[0x38 - 0x28]; void *res38; } M1Rig97N;
typedef struct M1Step97N {
    uint8_t unk000[0x22];
    uint8_t b22;               /* +0x22 */
    uint8_t unk023[0x58 - 0x23];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x68 - 0x5C];
    float   t68;               /* +0x68 */
    uint8_t unk06C[0x74 - 0x6C];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1Rig97N *rig278;          /* +0x278 */
} M1Step97N;
typedef struct M1Obj97N { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; void *anim30; } M1Obj97N;
int  sub_000833E0(void *a);
void sub_00033560(void *r);

/* 0x0011DA40: command 5 = 0.008; phase 0 waits 95 frames; phase 1 on clip end picks state 5
 * (rig flag 0x10, no wait), 4 (flag 0x40), 0xE (3+ hits) or 8/12 (h +0x22 bit), frees the
 * rig +0x38 resource and clears o flag 4. */
void m1_RigNext11DA40(M1Obj97N *o, M1Step97N *h)
{
    M1Rig97N *r;
    uint32_t f;
    int s;
    ((M1Cmd97S *)sub_00113400(h, 5))->f10 = 0.0080000004f;
    switch (h->phase58) {
    case 0:
        if (h->t68 >= 95.0f / m1_frameTime42C858 * m1_frameRate42C85C)
            h->phase58 = 1;
        break;
    case 1:
        if (sub_000833E0(o->anim30)) {
            r = h->rig278;
            f = r->flags04;
            if (f & 0x10) {
                h->wait74 = 0.0f;
                s = 5;
            } else if (f & 0x40) {
                s = 4;
            } else if (r->hits24 >= 3) {
                s = 0xE;
            } else {
                s = ((~h->b22 & 1) | 2) << 2;
            }
            if (r->res38 != 0) {
                sub_00033560(r->res38);
                h->rig278->res38 = 0;
            }
            o->flags10 &= ~4u;
            sub_00113040(o, h, s);
        }
        break;
    }
}
