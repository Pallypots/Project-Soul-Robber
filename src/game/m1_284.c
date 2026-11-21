/* Area m1, file 284: action events. Names inferred. */
#include <stdint.h>

typedef struct M1Ev284 { int32_t kind0; int32_t r4; uint32_t flags8; float vC; float v10[4]; float v20[4]; } M1Ev284;
typedef struct M1Ed284 { uint8_t unk00[8]; int32_t k8; int32_t vC; uint8_t unk10[0xC0]; } M1Ed284;
typedef struct M1Hd284 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[8]; uint8_t b10; } M1Hd284;
typedef struct M1Ac284 { uint8_t unk00[0xEC]; uint32_t flagsEC; uint8_t unkF0[0xC8]; uint8_t *p1B8; uint8_t unk1BC[0xD40];
    M1Hd284 *hEFC; } M1Ac284;
void sub_000BD570(M1Ac284 *a, int32_t k);                    /* regargs: a=ESI k=EDI */
void sub_000C4B70(M1Ed284 *d);
int32_t sub_000C5D20(M1Ac284 *a, M1Hd284 *h, M1Ed284 *d, float *p, float *q);
void sub_000A95E0(M1Hd284 *h, float *p, int32_t v);
int32_t sub_000CF790(M1Ac284 *a, uint8_t *p);
void sub_000F5D40(float *d, const float *s);
void sub_000EE010(M1Hd284 *h, M1Ev284 *e);

/* 0x000C2AA0: send action k with value v from actor a to its handler. Kind-12 handlers take the plain
   0x000BD570 path; handlers with flag 8 ignore it. Action 14 sends a direct event carrying v; others go through
   0x000C5D20 and, if accepted, 0x000A95E0. regargs: k=EAX, a=ECX; stack arg (v). */
void m1_SendActionC2AA0(int32_t k, M1Ac284 *a, int32_t v)
{
    float z[4], s[4];
    M1Hd284 *h;
    M1Ed284 d;
    M1Ev284 e;
    z[0] = 0.0f;
    z[1] = 0.0f;
    z[2] = 0.0f;
    z[3] = 1.0f;
    h = a->hEFC;
    if (!h) return;
    if (h->kind4 == 0xC) {
        sub_000BD570(a, k);
        return;
    }
    if (h->b10 & 8) return;
    if (k != 14) {
        sub_000C4B70(&d);
        d.k8 = k;
        d.vC = v;
        if (sub_000C5D20(a, h, &d, z, z) > 0)
            sub_000A95E0(h, z, v);
        return;
    }
    s[0] = 0.0f;
    s[1] = 0.0f;
    s[2] = 0.0f;
    e.vC = (float)v;
    s[3] = 1.0f;
    e.kind0 = 14;
    e.r4 = sub_000CF790(a, a->p1B8 + 4);
    e.flags8 = a->flagsEC & 0x40;
    sub_000F5D40(e.v10, s);
    sub_000F5D40(e.v20, s);
    sub_000EE010(h, &e);
}

typedef struct M1Hs284 { uint8_t unk00[4]; uint32_t flags4; } M1Hs284;
typedef struct M1Ho284 { uint8_t unk00[0xC]; uint32_t flagsC, flags10; } M1Ho284;
typedef struct M1Ha284 { uint8_t unk00[0x22]; uint8_t b22; uint8_t unk23[0x29]; uint32_t flags4C; uint8_t unk50[8];
    int32_t mode58; uint8_t unk5C[0x18]; float speed74; uint8_t unk78[0x200]; M1Hs284 *s278; } M1Ha284;
typedef struct M1Hx284 { uint8_t unk00[0x10]; float a10, a14, a18, a1C; } M1Hx284;
extern float m1_frameTime42C858, m1_frameRate42C85C;
void sub_0013D4B0(M1Ha284 *a, int32_t st);                   /* regargs: a=EAX st=EBX */
void sub_00113090(M1Ho284 *o, M1Ha284 *a, int32_t st);
M1Hx284 *sub_00113430(M1Ha284 *a, int32_t k);

/* 0x0013E250: pick a's hit reaction. A pending knock-back (0x800000) sends it flying (state 0x1E, mode 2) at a
   speed scaled to the frame time; a pending spin (8) starts a +-160 degree spin (state 0xD, mode 1); otherwise
   a plain flinch (state 8 or 9 by a's side bit, mode 0). */
void m1_HitPick13E250(M1Ho284 *o, M1Ha284 *a)
{
    M1Hs284 *s = a->s278;
    M1Hx284 *x;
    uint32_t fl;
    int32_t st;
    fl = o->flags10 & ~0x20u;
    o->flags10 = fl;
    if (s->flags4 & 0x800000) {
        o->flagsC &= ~0x20u;
        o->flags10 = fl | 6;
        a->flags4C &= 0xFEFFFF87u;
        s->flags4 &= ~0x800000u;
        a->speed74 = 90.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        sub_0013D4B0(a, 0x1E);
        a->mode58 = 2;
        sub_00113090(o, a, 0x1E);
        return;
    }
    if (s->flags4 & 8) {
        o->flags10 = fl | 0x20;
        a->flags4C &= ~0x10u;
        s->flags4 &= ~8u;
        x = sub_00113430(a, 9);
        x->a10 = m1_frameTime42C858 * 0.034906585f;
        x->a14 = 0.0f - x->a10;
        x->a18 = -2.792527f;
        x->a1C = 2.792527f;
        a->mode58 = 1;
        sub_00113090(o, a, 0xD);
        return;
    }
    o->flags10 = fl | 5;
    o->flagsC &= ~0x20u;
    a->flags4C &= 0xFEFFFF87u;
    st = (a->b22 & 1) + 8;
    sub_0013D4B0(a, st);
    a->mode58 = 0;
    sub_00113090(o, a, st);
}
