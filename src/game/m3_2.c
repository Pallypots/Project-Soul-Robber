/* Area m3, file 2: record resets, list broadcast, AI state entry. Names inferred. */
#include <stdint.h>

typedef struct M3Node2 { uint8_t unk00[0x3C]; struct M3Node2 *next3C; uint8_t unk40[0x110]; } M3Node2;
typedef struct M3Ctx2 { uint8_t unk00[0x1E8]; void *recs1E8; } M3Ctx2;
extern M3Ctx2 *m1_scene42C8E4;
extern M3Node2 *g_playerObj;
int sub_000F3140(int key);
M3Node2 *r1b_RecFind(void *recs, int kind, int key);
void sub_000E1060(M3Node2 *n, int a, int b, int c);

/* 0xE4050: send (a, b, c) to every node of the target set: kind 1 is the player, kind 3 is a group of n consecutive 0x150-byte lists; each list is walked through +0x3C. */
void m3_BroadcastE4050(int kind, int key, int a, int b, int c) {
    int n = 1; M3Node2 *list, *p;
    if (kind == 3) n = sub_000F3140(key);
    else if (kind == 1) { list = g_playerObj; goto run; }
    list = r1b_RecFind(m1_scene42C8E4->recs1E8, kind, key);
run:
    for (; n > 0; n--, list++)
        for (p = list; p; p = p->next3C) sub_000E1060(p, a, b, c);
}

typedef struct M3St2 { uint8_t unk00[4]; uint32_t f4; } M3St2;
typedef struct M3Obj2 { uint8_t unk00[0x20]; uint32_t f20; uint8_t unk24[0x28]; uint32_t f4C; uint8_t unk50[0x228]; M3St2 *st278; } M3Obj2;
typedef struct M3Spin2 { uint8_t unk00[0x10]; float f10, f14; } M3Spin2;
extern float m1_frameTime42C858;
void sub_00113090(void *a, M3Obj2 *o, int st);
M3Spin2 *m1_Quest113430(M3Obj2 *o, int k);
void aab_Attach36750(void *o, int mode);

/* 0x138270: AI entry: pick the state from flag bits (bit0 clear adds 8, bit16 adds 1, base 4), set the spin rate (1.5 or 2 degrees per frame unit) and its negative, mark flags 0x20 / 0x400000, attach mode 10. */
void m3_AiSpin138270(void *a, M3Obj2 *o) {
    uint32_t f = o->f20; M3Spin2 *s;
    sub_00113090(a, o, (int)((~(f << 3) & 8 | 4) + (f >> 16 & 1)));
    s = m1_Quest113430(o, 3);
    if (*(uint8_t *)&o->f20 & 1) s->f10 = m1_frameTime42C858 * 0.02617994f;
    else s->f10 = m1_frameTime42C858 * 0.034906585f;
    s->f14 = 0.0f - s->f10;
    o->f4C = (o->f4C & ~0x10u) | 0x20;
    o->st278->f4 |= 0x400000;
    aab_Attach36750(a, 10);
}

typedef struct M3Light2 { uint8_t unk00[0xC]; int32_t iC; uint8_t r10, g11, b12, a13; float x14, y18, z1C; } M3Light2;
void sub_000E43D0(void *o, int id, float *pos, float *col);

/* 0xEAD50: apply a light record to o: position (w = 1) and its byte colour converted to floats, passed with the record id to 0xE43D0. */
void m3_ApplyLightEAD50(void *o, M3Light2 *l) {
    float col[4], pos[4];
    if (o == 0 || l == 0) return;
    pos[0] = l->x14; pos[1] = l->y18; pos[2] = l->z1C; pos[3] = 1.0f;
    col[0] = (float)l->r10; col[1] = (float)l->g11; col[2] = (float)l->b12; col[3] = (float)l->a13;
    sub_000E43D0(o, l->iC, pos, col);
}

void r4c_VecSub(float *dst, const float *a, const float *b);
float m1_VecLen082D70(const float *v);

/* 0xA2890: cylinder overlap test of A (radius/height ra at pa) and B (rb at pb): 0 when the horizontal distance reaches ra[0]+rb[0] or the height spans do not overlap, else 1. */
int m3_CylOverlapA2890(const float *ra, const float *pa, const float *rb, const float *pb) {
    float d[4];
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    r4c_VecSub(d, pa, pb);
    d[1] = 0.0f;
    if (m1_VecLen082D70(d) >= ra[0] + rb[0]) return 0;
    if (rb[1] + pb[1] > pa[1]) return 0;
    if (ra[1] + pa[1] > pb[1]) return 0;
    return 1;
}

typedef struct M3Node3 { uint8_t unk00[0xC]; uint32_t fC; } M3Node3;
typedef struct M3Anim2 {
    int32_t i0, i4, i8; float fC, f10, f14, f18, f1C; int32_t i20, i24, i28, i2C;
    float f30, f34, f38, f3C, f40, f44, f48, f4C, f50, f54, f58, f5C, f60;
    M3Node3 *node64;
} M3Anim2;
void r1b_RecDetachNodes(M3Node3 *n);

/* 0xC6AA0: release the attached node (clear its bit 0 and detach it) and reset the record: counters 0/1/0, scale 1, half speed, zero vectors with unit w at +0x40/+0x50/+0x60. */
void m3_AnimResetC6AA0(M3Anim2 *a) {
    a->node64->fC &= ~1u;
    r1b_RecDetachNodes(a->node64);
    a->i0 = 0; a->i4 = 1; a->i8 = 0;
    a->fC = 0.0f; a->f10 = 0.0f; a->f14 = 1.0f;
    a->i20 = 0; a->i24 = 0;
    a->f18 = 0.5f; a->f1C = 0.0f;
    a->i28 = 0; a->i2C = 0;
    a->f30 = 0.0f; a->f3C = 0.0f; a->f38 = 0.0f; a->f34 = 0.0f;
    a->f4C = 0.0f; a->f48 = 0.0f; a->f44 = 0.0f;
    a->f5C = 0.0f; a->f58 = 0.0f; a->f54 = 0.0f;
    a->f60 = 1.0f; a->f50 = 1.0f; a->f40 = 1.0f;
    a->node64 = 0;
}
