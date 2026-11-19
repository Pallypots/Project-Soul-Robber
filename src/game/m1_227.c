/* Area m1, file 227: draw-state helpers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Col227 { int32_t r, g, b, a; uint8_t unk10[0x18]; int32_t blend28; } M1Col227;
typedef struct M1Quad227 { uint8_t f0, r, g, b, a; uint8_t pad5[7]; int32_t zC; volatile int16_t x10, y12, w14, h16; } M1Quad227;
extern int32_t m1_blendTab2836E0[];
void sub_001A69C0(int32_t a, int32_t b);
void sub_001A6E40(int32_t v);
void sub_001A6E80(int32_t v);
void r4d_Call1A5F50(M1Quad227 *q);

typedef struct M1Pl227 { uint8_t unk00[0x150]; uint32_t flags150; uint8_t unk154[0x5F0 - 0x154]; int32_t snd5F0;
    uint8_t unk5F4[0xC]; int32_t h600; } M1Pl227;
extern int32_t g_42C8EC;
extern uint8_t r6e_obj420EC0[];
void sub_00048250(int32_t h);
int32_t Player_D00A0(M1Pl227 *o, int32_t h);
void sub_000BC5D0(void);
void m1_SceneFade0D4C10(int32_t rig);
void sub_000D45B0(int32_t rig, int32_t a, float b, float c);
void sub_000CA400(M1Pl227 *o);
void m1_ClearWordsC44E0(M1Pl227 *o);
void sub_000BC5F0(void *p);
int32_t PlayerObj_IsActive(M1Pl227 *o);
void abc_SetState(M1Pl227 *o, int32_t st);

/* 0x00037790: draw a full-screen 512x448 quad in colour c with c's blend mode, then restore state; returns arg
   unchanged (regargs: c=ESI). */
int32_t m1_FadeQuad037790(M1Col227 *c, int32_t arg)
{
    M1Quad227 q;
    sub_001A69C0(m1_blendTab2836E0[c->blend28], 0);
    q.r = (uint8_t)c->r;
    q.g = (uint8_t)c->g;
    q.b = (uint8_t)c->b;
    q.a = (uint8_t)c->a;
    q.x10 = 0;
    q.y12 = 0;
    q.w14 = 0x200;
    q.h16 = 0x1C0;
    q.zC = 0x7FFFFF00;
    sub_001A6E40(0);
    sub_001A6E80(0);
    if (q.a)
        r4d_Call1A5F50(&q);
    sub_001A69C0(0x44, 0);
    sub_001A6E40(1);
    sub_001A6E80(1);
    return arg;
}

/* 0x000BF740: shut the player down unless flags 0x80/0x400000 are set (returns 1): clear its flags, stop its sound,
   release h600, reset the scene and set state 6 if still active else 1; returns -1 (regargs: o=ESI). */
int32_t m1_PlayerStop0BF740(M1Pl227 *o)
{
    if (o->flags150 & 0x400080)
        return 1;
    o->flags150 &= 0xEEFFFFBF;
    if (o->snd5F0 >= 0) {
        sub_00048250(o->snd5F0);
        o->snd5F0 = -1;
    }
    if (o->h600)
        o->h600 = Player_D00A0(o, o->h600);
    sub_000BC5D0();
    m1_SceneFade0D4C10(g_42C8EC);
    sub_000D45B0(g_42C8EC, 0, -1.0f, -1.0f);
    sub_000CA400(o);
    m1_ClearWordsC44E0(o);
    sub_000BC5F0(r6e_obj420EC0);
    if (PlayerObj_IsActive(o) > 0) {
        abc_SetState(o, 6);
        return -1;
    }
    abc_SetState(o, 1);
    return -1;
}
