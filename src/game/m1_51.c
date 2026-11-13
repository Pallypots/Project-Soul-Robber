/* Area m1, file 51: rig blends with turn speeds. Names inferred. */
#include <stdint.h>

typedef struct M1RigT { uint32_t flags00; } M1RigT;
typedef struct M1StepT {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1RigT *rig278;            /* +0x278 */
} M1StepT;
typedef struct M1ObjT { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[3]; } M1ObjT;
extern float m1_frameTime42C858, m1_frameRate42C85C;
int  sub_001456E0(void *o, void *s, int a, int b);
int  aab_Rand(void);
void sub_00156180(void *rig, float x, float y, float z, float t);
int  sub_00036750(void *o, int v);
int  sub_000494D0(int id, const void *pos, int c);

/* 0x00146E50: 0x1456E0(6), rig blend 0x156180(frame rate * 10, frame rate * -5, 0,
 * frame time * 0.003), o flags |= 5, h +0x4C: clear 0x70 set 0x1000000, rig flags |= 3,
 * 0x36750(0), sound 0x12F at o. */
void m1_RigBlend146E50(M1ObjT *o, M1StepT *h)
{
    M1RigT *r = h->rig278;
    sub_001456E0(o, h, 6, 0);
    sub_00156180(r, m1_frameRate42C85C * 10.0f, m1_frameRate42C85C * -5.0f, 0.0f,
                 m1_frameTime42C858 * 0.003f);
    o->flags10 |= 5;
    h->flags4C = (h->flags4C & ~0x70u) | 0x1000000;
    r->flags00 |= 3;
    sub_00036750(o, 0);
    sub_000494D0(0x12F, o->pos60, 0);
}

typedef struct M1RigW { uint8_t unk00[4]; uint32_t flags04; } M1RigW;
typedef struct M1StepW {
    uint8_t unk000[0x20];
    uint32_t flags20;          /* +0x20 */
    uint8_t unk024[0x270 - 0x24];
    float   f270, f274;        /* +0x270 */
    M1RigW *rig278;            /* +0x278 */
} M1StepW;
typedef struct M1ObjW { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; int32_t f30; } M1ObjW;
typedef struct M1CmdW { uint8_t unk00[0x10]; float f10; } M1CmdW;
M1CmdW *sub_00113400(void *h, int v);
int  sub_000833E0(int v);
void sub_00113040(void *o, void *h, int next);

/* 0x001430B0: command 5 speed = 0.008; once 0x833E0(o +0x30) is ready picks the next state:
 * 4 normally; when rig flag 4 is clear or h flag 1 is set, 7 without h flag 0x10000, else 8
 * (also setting rig flag 2 unless h flag 1 is set and +0x274 is above half of +0x270);
 * then clears o flag 4 and calls 0x113040. */
void m1_RigNext1430B0(M1ObjW *o, M1StepW *h)
{
    M1RigW *r = h->rig278;
    uint32_t f;
    int next;
    sub_00113400(h, 5)->f10 = 0.008f;
    if (sub_000833E0(o->f30) == 0)
        return;
    next = 4;
    f = h->flags20;
    if (!(h->rig278->flags04 & 4) || (f & 1)) {
        next = (f & 0x10000) ? 8 : 7;
        if (next == 8 && (!(f & 1) || h->f270 * 0.5f >= h->f274))
            r->flags04 |= 2;
    }
    o->flags10 &= ~4u;
    sub_00113040(o, h, next);
}

typedef struct M1Pos60 { uint8_t unk00[0x60]; float pos60[4]; } M1Pos60;
typedef struct M1StepA88 {
    uint8_t unk000[0x88];
    float   v88[4];            /* +0x88 */
    uint8_t unk098[0x278 - 0x98];
    M1RigW *rig278;            /* +0x278 */
} M1StepA88;
extern M1Pos60 *g_playerObj;
int  sub_00139E10(void *o, const float *v);
void sub_000F5D40(float *dst, const float *src);

/* 0x00139EF0: rig flag 0x80000000 follows 0x139E10(o, v); when asked, stores the aim
 * vector at h +0x88: a copy of v when given, else o's position minus the player's
 * (w copied from o). */
void m1_RigAim139EF0(M1Pos60 *o, M1StepA88 *h, const float *v, int store)
{
    M1RigW *r = h->rig278;
    float *pp;
    if (sub_00139E10(o, v) != 0)
        r->flags04 |= 0x80000000u;
    else
        r->flags04 &= 0x7FFFFFFFu;
    if (store == 0)
        return;
    if (v != 0) {
        sub_000F5D40(h->v88, v);
        return;
    }
    pp = g_playerObj->pos60;
    h->v88[0] = o->pos60[0] - pp[0];
    h->v88[1] = o->pos60[1] - pp[1];
    h->v88[2] = o->pos60[2] - pp[2];
    h->v88[3] = o->pos60[3];
}

typedef struct M1Rig7C { uint8_t unk00[4]; uint32_t flags04; uint8_t unk08[0x7C - 8]; float f7C; } M1Rig7C;
typedef struct M1Step7C { uint8_t unk000[0x278]; M1Rig7C *rig278; } M1Step7C;
typedef struct M1Cmd4 { uint8_t unk00[0x10]; float v10[4]; } M1Cmd4;

/* 0x00121DA0: 0x1456E0(2), o flag 0x20, rig flag 8, rig +0x7C += 90 clamped to 0..200,
 * then command 7 vector = (0, 0, 0, 0) or (1, 0, 0, 0) at random. */
void m1_RigStep121DA0(M1ObjW *o, M1Step7C *h)
{
    M1Rig7C *r = h->rig278;
    M1Rig7C *p;
    M1Cmd4 *c;
    float v;
    sub_001456E0(o, h, 2, 0);
    o->flags10 |= 0x20;
    r->flags04 |= 8;
    p = h->rig278;
    v = p->f7C + 90.0f;
    p->f7C = v;
    if (v < 0.0f)
        p->f7C = 0.0f;
    else if (v > 200.0f)
        p->f7C = 200.0f;
    if (aab_Rand() & 1) {
        c = (M1Cmd4 *)sub_00113400(h, 7);
        c->v10[0] = 0.0f;
    } else {
        c = (M1Cmd4 *)sub_00113400(h, 7);
        c->v10[0] = 1.0f;
    }
    c->v10[1] = 0.0f;
    c->v10[2] = 0.0f;
    c->v10[3] = 0.0f;
}

typedef struct M1Fx28 { uint8_t unk00[0x28]; void *res28; } M1Fx28;
typedef struct M1RigX { uint8_t unk00[0x20]; M1Fx28 *fx20; } M1RigX;
typedef struct M1StepX {
    uint8_t unk000[0x6C];
    int32_t snd6C;             /* +0x6C */
    void   *res70;             /* +0x70 */
    uint8_t unk074[0x278 - 0x74];
    M1RigX *rig278;            /* +0x278 */
} M1StepX;
void sub_0001D700(void *p);
void sub_0018B260(void *fx, const float *v);
int  sub_000ED780(void *o);
void sub_001B2080(void *r);
void sub_00048250(int snd);
void sub_00033A70(void *r);

/* 0x001421C0: cleanup: releases the rig effect (+0x20: 0x1D700, zero offset, frees its
 * +0x28 resource, 0xED780 must return 1 or it spins), stops the +0x6C sound and frees
 * the +0x70 resource; returns 1. */
int m1_RigCleanup1421C0(void *o, M1StepX *h)
{
    M1RigX *r = h->rig278;
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    if (r->fx20 != 0) {
        sub_0001D700(r->fx20);
        sub_0018B260(r->fx20, v);
        sub_001B2080(r->fx20->res28);
        if (sub_000ED780(r->fx20) != 1)
            for (;;) ;
        r->fx20 = 0;
    }
    if (h->snd6C >= 0) {
        sub_00048250(h->snd6C);
        h->snd6C = -1;
    }
    if (h->res70 != 0) {
        sub_00033A70(h->res70);
        h->res70 = 0;
    }
    return 1;
}
