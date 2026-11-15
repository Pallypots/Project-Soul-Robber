/* Area m3, batch 32. Names inferred. */
#include <stdint.h>

typedef struct M3TSt32 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x24]; float v2C[3]; float w38; } M3TSt32;
typedef struct M3TEn32 { uint8_t unk00[0x278]; M3TSt32 *st278; } M3TEn32;
typedef struct M3TMx32 { float r0[4]; float r1[4]; float r2[4]; } M3TMx32;
typedef struct M3TAi32 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0xC]; M3TMx32 *m20; uint8_t unk24[0x3C]; float pos60[4]; } M3TAi32;
typedef struct M3TCmd32 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M3TCmd32;
extern uint8_t *g_playerObj;
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
void sub_001AD7E0(float *d, const float *s);
void sub_001ADBA0(float *d, const float *a, int s);
float sub_001AD9D0(const float *a, const float *b);
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
void sub_0001D4E0(void *a);
void a3c_VecCopy(float *dst, const float *src);
void sub_001ADA60(float *d, const float *a, const float *b);
M3TCmd32 *sub_00113400(void *o, int v);

/* 0x1160A0: turn an AI on the ground plane: if its back faces the player it turns to face away (state 0x32), else it faces the player (state 0x31); rebuilds the basis, and clears the knock flag (command 4 timer 1/12 s) and heavy flag bits. */
void m3_AiTurn1160A0(M3TAi32 *a, M3TEn32 *o) {
    float d[4], f[4], c;
    M3TSt32 *st = o->st278;
    M3TCmd32 *k;
    aab_Vec1AD9F0(d, a->pos60, (float *)(g_playerObj + 0x60));
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(f, a->m20->r2, 0xBF800000);
    f[1] = 0.0f;
    sub_001AD7E0(f, f);
    c = sub_001AD9D0(f, d);
    if (c == 0.0) sub_001ADBA0(d, f, 0xBF800000);
    if (c > 0.0f) {
        if (m1_AiSetState1456E0(a, o, 0x32, 0) == 1) sub_0001D4E0(a);
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x31, 0) == 1) sub_0001D4E0(a);
        a3c_VecCopy(a->m20->r2, d);
    }
    o->st278->v2C[2] = 0.0f; o->st278->v2C[1] = 0.0f; o->st278->v2C[0] = 0.0f;
    o->st278->w38 = 1.0f;
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    if (st->f4 & 0x100000) {
        st->f4 &= ~0x100000u;
        a->f10 |= 4;
        k = sub_00113400(o, 4);
        k->f10 = 0.083333336f;
        k->f14 = 0.0f; k->f18 = 0.0f; k->f1C = 0.0f;
    }
    if (st->f4 & 0x10) a->f10 |= 0xD;
}

int  aab_Effect494D0(int id, const void *pos, int c);

/* 0x116C60: like 0x1160A0 for the stagger turn: face away (state 0x38) or toward the player (state 0x34), rebuild the basis, set flag 2 (clearing 0x80000) and play effect 0x16C at the AI. */
void m3_AiStagger116C60(M3TAi32 *a, M3TEn32 *o) {
    float d[4], f[4], c;
    M3TSt32 *st = o->st278;
    aab_Vec1AD9F0(d, a->pos60, (float *)(g_playerObj + 0x60));
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(f, a->m20->r2, 0xBF800000);
    f[1] = 0.0f;
    sub_001AD7E0(f, f);
    c = sub_001AD9D0(f, d);
    if (c == 0.0) sub_001ADBA0(d, f, 0xBF800000);
    if (c > 0.0f) {
        if (m1_AiSetState1456E0(a, o, 0x38, 0) == 1) sub_0001D4E0(a);
        o->st278->v2C[2] = 0.0f; o->st278->v2C[1] = 0.0f; o->st278->v2C[0] = 0.0f;
        o->st278->w38 = 1.0f;
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        o->st278->v2C[2] = 0.0f; o->st278->v2C[1] = 0.0f; o->st278->v2C[0] = 0.0f;
        o->st278->w38 = 1.0f;
        a3c_VecCopy(a->m20->r2, d);
    }
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    st->f4 = (st->f4 & ~0x80000u) | 2;
    aab_Effect494D0(0x16C, a->pos60, 0);
    if (st->f4 & 0x10) a->f10 |= 0xD;
}

typedef struct M3TSb32 { uint8_t unk00[0xC]; uint32_t fC; uint8_t unk10[0x154]; float v164[3]; float w170; } M3TSb32;
typedef struct M3TEb32 { uint8_t unk00[0x278]; M3TSb32 *st278; } M3TEb32;

/* 0x12FA50: turn for a second AI kind (block at +0x164, flags at +0xC): face away (state 0x32) or toward the player (state 0x31), rebuild the basis, clear knock flag 0x80000 (command 6 timer 1/12 s) and apply flag 0x20. */
void m3_AiTurn12FA50(M3TAi32 *a, M3TEb32 *o) {
    float d[4], f[4], c;
    M3TSb32 *st = o->st278;
    M3TCmd32 *k;
    aab_Vec1AD9F0(d, a->pos60, (float *)(g_playerObj + 0x60));
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(f, a->m20->r2, 0xBF800000);
    f[1] = 0.0f;
    sub_001AD7E0(f, f);
    c = sub_001AD9D0(f, d);
    if (c == 0.0) sub_001ADBA0(d, f, 0xBF800000);
    if (c > 0.0f) {
        if (m1_AiSetState1456E0(a, o, 0x32, 0) == 1) sub_0001D4E0(a);
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x31, 0) == 1) sub_0001D4E0(a);
        a3c_VecCopy(a->m20->r2, d);
    }
    o->st278->v164[2] = 0.0f; o->st278->v164[1] = 0.0f; o->st278->v164[0] = 0.0f;
    o->st278->w170 = 1.0f;
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    if (st->fC & 0x80000) {
        st->fC &= ~0x80000u;
        a->f10 |= 4;
        k = sub_00113400(o, 6);
        k->f10 = 0.083333336f;
        k->f14 = 0.0f; k->f18 = 0.0f; k->f1C = 0.0f;
    }
    if (st->fC & 0x20) a->f10 |= 0xD;
}

/* 0x130900: stagger turn for the second AI kind: face away (state 0x38) or toward the player (state 0x34), rebuild the basis, then set flag 8 (clearing 0x1000000). */
void m3_AiStagger130900(M3TAi32 *a, M3TEb32 *o) {
    float d[4], f[4], c;
    M3TSb32 *st = o->st278;
    aab_Vec1AD9F0(d, a->pos60, (float *)(g_playerObj + 0x60));
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(f, a->m20->r2, 0xBF800000);
    f[1] = 0.0f;
    sub_001AD7E0(f, f);
    c = sub_001AD9D0(f, d);
    if (c == 0.0) sub_001ADBA0(d, f, 0xBF800000);
    if (c > 0.0f) {
        if (m1_AiSetState1456E0(a, o, 0x38, 0) == 1) sub_0001D4E0(a);
        o->st278->v164[2] = 0.0f; o->st278->v164[1] = 0.0f; o->st278->v164[0] = 0.0f;
        o->st278->w170 = 1.0f;
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        o->st278->v164[2] = 0.0f; o->st278->v164[1] = 0.0f; o->st278->v164[0] = 0.0f;
        o->st278->w170 = 1.0f;
        a3c_VecCopy(a->m20->r2, d);
    }
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    a->f10 |= 4;
    st->fC = (st->fC & ~0x1000000u) | 8;
    if (st->fC & 0x20) a->f10 |= 0xD;
}

extern float a50_frameSeconds;

/* 0x12FD50: knock-down turn for the second AI kind: face away (state 0x38) or toward the player (state 0x34) with a downward push of 100 per second, rebuild the basis, set flags 0x10004 and play effect 0x16E. */
void m3_AiKnockDown12FD50(M3TAi32 *a, M3TEb32 *o) {
    float d[4], f[4], c;
    M3TSb32 *st = o->st278;
    M3TSb32 *s2;
    aab_Vec1AD9F0(d, a->pos60, (float *)(g_playerObj + 0x60));
    d[1] = 0.0f;
    sub_001AD7E0(d, d);
    sub_001ADBA0(f, a->m20->r2, 0xBF800000);
    f[1] = 0.0f;
    sub_001AD7E0(f, f);
    c = sub_001AD9D0(f, d);
    if (c == 0.0) sub_001ADBA0(d, f, 0xBF800000);
    if (c > 0.0f) {
        if (m1_AiSetState1456E0(a, o, 0x38, 0) == 1) sub_0001D4E0(a);
        s2 = o->st278;
        s2->v164[1] = 0.0f - a50_frameSeconds * 100.0f;
        s2->v164[2] = 0.0f; s2->v164[0] = 0.0f;
        s2->w170 = 1.0f;
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        s2 = o->st278;
        s2->v164[1] = 0.0f - a50_frameSeconds * 100.0f;
        s2->v164[2] = 0.0f; s2->v164[0] = 0.0f;
        s2->w170 = 1.0f;
        a3c_VecCopy(a->m20->r2, d);
    }
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    a->f10 |= 0x10;
    st->fC = (st->fC & ~0x1000000u) | 0x10004;
    aab_Effect494D0(0x16E, a->pos60, 0);
    if (st->fC & 0x20) a->f10 |= 0xD;
}
