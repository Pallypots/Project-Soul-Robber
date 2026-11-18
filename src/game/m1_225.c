/* Area m1, file 225: event handler by kind (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Ev225 { uint8_t unk00[0x54]; int32_t f54; uint8_t unk58[4]; float v5C[3]; } M1Ev225;
typedef struct M1Ob225 { uint8_t unk00[0xC]; uint32_t flagsC; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; uint8_t pos60[0xC8];
                         uint32_t flags128; } M1Ob225;
void sub_00036750(M1Ob225 *o, int a);
void sub_000494D0(int id, void *pos, int a);
void sub_001ADB60(float *dst, float *src, float s);

/* 0x00170D80: react to event kind k on object o (regargs: k=EAX e=ECX o=EDX). */
void m1_EvReact170D80(int k, M1Ev225 *e, M1Ob225 *o)
{
    switch (k) {
    case 0x0E: o->flagsC &= ~0x20u; break;
    case 0x1A: case 0x1C: o->flagsC |= 0x20; break;
    case 0x0D:
        sub_00036750(o, 0);
        sub_000494D0(0x77, o->pos60, 0);
        break;
    case 0x2A:
        sub_001ADB60(e->v5C, e->v5C, 60.0f);
        o->flagsC &= ~0x20u;
        o->flags10 |= 4;
        o->flags128 |= 0x18;
        break;
    case 0x22:
        o->flags10 |= 4;
        e->f54 = 1;
        break;
    }
}

typedef struct M1Pa225 { float v[3]; float pC; float r10; } M1Pa225;            /* 0x14 */
typedef struct M1Pb225 { float f[5]; float s14; } M1Pb225;                        /* 0x18 */
typedef struct M1Src225 { uint8_t unk00[4]; void *h4; } M1Src225;
typedef struct M1A225 { uint8_t unk00[0x74]; M1Src225 *src74; } M1A225;
typedef struct M1B225 { uint8_t unk00[0x60]; float pos60[3]; uint8_t unk6C[0xE8 - 0x6C]; float fE8; } M1B225;
void sub_000F5D40(float *dst, const float *src);
void sub_000EDEC0(void *h, M1Pb225 *out);
int  sub_000EE2B0(M1Pa225 *a, M1Pb225 *b, int c);

/* 0x0018ECD0: when a's source has a handle, build b's position/radius and the source's shape (scale +0x14 negated)
   and test them with 0xEE2B0; 0 when there is no handle (regargs: a=ESI b=EDI). */
int m1_ShapeTest18ECD0(M1A225 *a, M1B225 *b)
{
    M1Pa225 pa;
    M1Pb225 pb;
    if (!a->src74->h4) return 0;
    sub_000F5D40(pa.v, b->pos60);
    pa.r10 = b->fE8;
    sub_000EDEC0(a->src74->h4, &pb);
    pb.s14 = pb.s14 * -1.0f;
    return sub_000EE2B0(&pa, &pb, 0);
}
