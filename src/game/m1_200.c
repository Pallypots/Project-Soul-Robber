/* Area m1, file 200: object scale helpers. Names inferred. */
#include <stdint.h>

typedef struct M1ScB200 { uint8_t unk00[0x70]; float s70, s74, s78, s7C; uint8_t unk80[0x20]; float fA0; uint8_t unkA4[4]; float fA8; uint8_t unkAC[4]; float fB0; uint8_t unkB4[4]; float fB8; uint8_t unkBC[0x14]; int32_t iD0; uint8_t unkD4[0x14]; float fE8; } M1ScB200;
typedef struct M1Sc200 { uint32_t flags0; uint8_t unk04[0xC]; float f10; uint8_t unk14[0xC]; float f20; uint8_t unk24[4]; float f28, f2C; uint8_t unk30[4]; float f34; uint8_t unk38[0xE8]; M1ScB200 *b120; } M1Sc200;

/* 0xA4870: set an active object's scale: uniform scale on its body, and the collision sizes scaled to match (all four for kind 1, otherwise just the radius). */
void m1_ObjScale0A4870(M1Sc200 *o, float s) {
    M1ScB200 *b;
    if (!(o->flags0 & 1)) return;
    o->f10 = s;
    o->b120->s78 = s;
    o->b120->s74 = s;
    o->b120->s70 = s;
    o->b120->s7C = 0.0f;
    b = o->b120;
    if (b->iD0 == 1) {
        b->fA0 = o->f20 * s;
        o->b120->fA8 = o->f28 * s;
        o->b120->fB0 = o->f2C * s;
        o->b120->fB8 = o->f34 * s;
    } else b->fB0 = o->f2C * s;
    o->b120->fE8 = o->f2C * s;
}

typedef struct M1Scn200 { uint8_t unk00[0x3B0]; void *model3B0; } M1Scn200;
extern void *m1_plFx4204C0[8];
extern void *r2b_h4204DC;
extern void *r2b_h4204D8;
extern uint32_t m1_plFlags420C20;
extern int32_t m1_plMode420078;
extern int32_t r2b_g41FFEC;
extern uint8_t *g_playerObj;
extern M1Scn200 *m1_scene2_42C8EC;
extern uint8_t abc_player[];
void r1c_NodeFreeChain(void *c);
void aab_Hide1D700(void *o);
void sub_000D1930(void *p);
void sub_00033A40(void *h);
void abc_SetState(void *p, int st);
void sub_000CE970(void);
void sub_000CEF60(void);

/* 0xD3540: reset the player: free its eight effect chains, hide the player and the scene model, drop the two held handles, return to state 1 and, in modes 0/1, restart the HUD. */
void m1_PlReset0D3540(void) {
    void **p; int m;
    for (p = m1_plFx4204C0; (int32_t)p < (int32_t)&m1_plFx4204C0[8]; p++)
        if (*p) { r1c_NodeFreeChain(*p); *p = 0; }
    aab_Hide1D700(g_playerObj);
    aab_Hide1D700(m1_scene2_42C8EC->model3B0);
    sub_000D1930(abc_player);
    m1_plFlags420C20 &= ~2u;
    if (r2b_h4204DC) { sub_00033A40(r2b_h4204DC); r2b_h4204DC = 0; }
    m1_plFlags420C20 &= ~1u;
    if (r2b_h4204D8) { sub_00033A40(r2b_h4204D8); r2b_h4204D8 = 0; }
    abc_SetState(abc_player, 1);
    r2b_g41FFEC = 0;
    m = m1_plMode420078;
    if (m == 0 || m == 1) { sub_000CE970(); sub_000CEF60(); }
}

typedef struct M1Tg200 { uint8_t unk00[0x60]; float pos60[4]; } M1Tg200;
typedef struct M1Pb200 { uint8_t unk00[0x5C0]; float pos5C0[4]; float fwd5D0[4]; uint8_t unk5E0[0x9F8]; M1Tg200 *tgtFD8; } M1Pb200;
void  rbj_VecSub(float *dst, const float *a, const float *b);
float sub_00082D70(const float *v);
void  rbi_VecNorm(float *dst, const float *src);
float sub_001AD9D0(const float *a, const float *b);

/* 0xCBF10: is the target behind the player? 1 when it is within 2 units horizontally or the facing points away from it, else -1. */
int m1_TargetBehind0CBF10(M1Pb200 *p) {
    float a[4], b[4];
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f; b[3] = 1.0f;
    rbj_VecSub(a, p->pos5C0, p->tgtFD8->pos60);
    a[1] = 0.0f; a[3] = 1.0f;
    if (2.0f >= sub_00082D70(a)) return 1;
    rbi_VecNorm(a, a);
    rbi_VecNorm(b, p->fwd5D0);
    if (0.0f > sub_001AD9D0(a, b)) return 1;
    return -1;
}
