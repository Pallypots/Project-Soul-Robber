/* Area m1, file 101: recover variants. Names inferred. */
#include <stdint.h>

typedef struct M1Rig101 { uint32_t flags00; float f04; float f08; uint8_t unk0C[0x40 - 0xC]; uint32_t flags40; } M1Rig101;
typedef struct M1Step101 {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x6C - 0x50];
    int32_t snd6C;             /* +0x6C */
    void   *fx70;              /* +0x70 */
    uint8_t unk074[0x278 - 0x74];
    M1Rig101 *rig278;          /* +0x278 */
} M1Step101;
typedef struct M1Obj101 { uint8_t unk000[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk014[0x30 - 0x14]; void *anim30; uint8_t unk034[0x60 - 0x34]; float pos60[4]; uint8_t unk070[0x13C - 0x70]; int32_t i13C; } M1Obj101;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
void sub_001134B0(void *h);
void sub_00113AA0(void *o, void *h);
int  sub_000494D0(int id, const void *pos, int c);
void sub_0005BE30(int v);
void sub_00033A70(void *r);
void sub_00113040(void *o, void *h, int state);

/* 0x00165560: recover (as 0x165480) once the clip ends, but starting looping sound 0x10F when
 * none is playing and going to state 0x20. */
void m1_Recover165560(M1Obj101 *o, M1Step101 *h)
{
    M1Rig101 *r;
    uint32_t f;
    if (!sub_000833E0(o->anim30))
        return;
    r = h->rig278;
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
    if (h->snd6C == -1)
        h->snd6C = sub_000494D0(0x10F, o->pos60, 1);
    sub_0005BE30(o->i13C);
    if (h->fx70 != 0) {
        sub_00033A70(h->fx70);
        h->fx70 = 0;
    }
    sub_00113040(o, h, 0x20);
}

typedef struct M1Rig101S { uint8_t unk00[0x20]; float q20[4]; uint8_t unk30[0x8C - 0x30]; float f8C; float f90; } M1Rig101S;
typedef struct M1Step101S { uint8_t unk000[0x278]; M1Rig101S *rig278; } M1Step101S;
typedef struct M1Cmd101 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Cmd101;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);
M1Cmd101 *sub_00113400(void *h, int v);

/* 0x00186D20: as 0x1868A0 with state 2, rig +0x8C = 10, +0x90 = 15 * frameRate, a +-5 degree
 * sway at 4 degrees/frame and command 2 = (2, 0, 1, 0). */
void m1_RigSway186D20(void *o, M1Step101S *h)
{
    M1Rig101S *r = h->rig278;
    M1Rig101S *p;
    M1Cmd101 *c;
    float t;
    sub_001456E0(o, h, 2, 0);
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    r->f8C = 10.0f;
    r->f90 = m1_frameRate42C85C * 15.0f;
    t = m1_frameTime42C858 * 0.06981317f;
    c = sub_00113400(h, 1);
    c->f10 = 0.087266468f;
    c->f14 = -0.087266468f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
    c = sub_00113400(h, 2);
    c->f10 = 2.0f;
    c->f14 = 0.0f;
    c->f18 = 1.0f;
    c->f1C = 0.0f;
}

typedef struct M1Sub101 { uint32_t flags00; uint8_t unk04[0x18 - 4]; float range18; uint8_t unk1C[0x2C - 0x1C]; float home2C[4]; uint8_t unk3C[0x5C - 0x3C]; void *res5C; } M1Sub101;
typedef struct M1Step101W { uint8_t unk00[0x50]; uint32_t state50; uint8_t unk54[0x74 - 0x54]; M1Sub101 *sub74; } M1Step101W;
typedef struct M1Pl101 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl101;
extern M1Pl101 *g_playerObj;
float sub_001B2770(const float *a, const float *b);
void  sub_000D9AB0(int id);
void  sub_000D9B30(int id);
int   sub_000C71C0(void *o, float r);
void  sub_001671D0(void *o, void *h, int v);
int   sub_00033AD0(void *r);
void  sub_00033560(void *r);

/* 0x001677F0: watch: with sub flag 0x200000 toggle flag 0x3FF by player distance (under 45);
 * in states other than 7 (below 8) without flag 0x20000000 react to 0xC71C0(30) (flag
 * 0x8000000, 0x1671D0(7)); in states other than 5 (below 8) without the sign flag, leaving the
 * +0x18 range around home sets it and runs 0x1671D0(5); drop the +0x5C resource when done. */
void m1_Watch1677F0(M1Obj101 *o, M1Step101W *h)
{
    M1Sub101 *s = h->sub74;
    if (s->flags00 & 0x200000) {
        if (45.0f > sub_001B2770(o->pos60, g_playerObj->pos60))
            sub_000D9AB0(0x3FF);
        else
            sub_000D9B30(0x3FF);
    }
    if (h->state50 != 7 && h->state50 < 8 && !(s->flags00 & 0x20000000) && sub_000C71C0(o, 30.0f)) {
        s->flags00 |= 0x8000000;
        sub_001671D0(o, h, 7);
    }
    if (h->state50 != 5 && h->state50 < 8 && (int32_t)s->flags00 >= 0 &&
        sub_001B2770(o->pos60, s->home2C) > s->range18) {
        s->flags00 |= 0x80000000;
        sub_001671D0(o, h, 5);
    }
    if (s->res5C != 0 && !sub_00033AD0(s->res5C)) {
        sub_00033560(s->res5C);
        s->res5C = 0;
    }
}

typedef struct M1Rig101T { uint8_t unk00[0xC]; uint16_t step0C; uint8_t unk0E[2]; float t10; } M1Rig101T;
typedef struct M1Step101T { uint8_t unk000[0x278]; M1Rig101T *rig278; } M1Step101T;
typedef struct M1Obj101T { uint8_t unk00[0x30]; void *anim30; uint8_t unk34[0x54 - 0x34]; float yaw54; } M1Obj101T;
int  sub_000F5D00(void *o);
void sub_000832D0(void *a, int v);

/* 0x00181770: step 0 plays clip 6 once 0xF5D00 holds, step 1 plays clip 7 after 6 s,
 * step 2 turns the yaw back to 0 at frameTime * 0.00646 per frame and then (0xF5D00) goes to
 * state 0. */
void m1_TurnBack181770(M1Obj101T *o, M1Step101T *h)
{
    M1Rig101T *r = h->rig278;
    float k;
    switch (r->step0C) {
    case 0:
        if (sub_000F5D00(o)) {
            sub_000832D0(o->anim30, 6);
            r->step0C++;
            r->t10 = 0.0f;
        }
        break;
    case 1:
        if (r->t10 > 6.0f) {
            sub_000832D0(o->anim30, 7);
            r->step0C++;
        } else {
            r->t10 += m1_frameRate42C85C;
        }
        break;
    case 2:
        k = m1_frameTime42C858 * 0.00645771855f;
        if (o->yaw54 > k) {
            o->yaw54 -= k;
            return;
        }
        if (0.0f - k > o->yaw54) {
            o->yaw54 += k;
            return;
        }
        o->yaw54 = 0.0f;
        if (sub_000F5D00(o))
            sub_00113040(o, h, 0);
        break;
    }
}
