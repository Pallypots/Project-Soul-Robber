/* Area m3, batch 33. Names inferred. */
#include <stdint.h>

typedef struct M3TMx33 { float r0[4]; float r1[4]; float r2[4]; } M3TMx33;
typedef struct M3TAi33 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0xC]; M3TMx33 *m20; uint8_t unk24[0x3C]; float pos60[4]; } M3TAi33;
typedef struct M3TCmd33 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M3TCmd33;
typedef struct M3TSb33 { uint8_t unk00[0xC]; uint32_t fC; uint8_t unk10[0x154]; float v164[3]; float w170; } M3TSb33;
typedef struct M3TEb33 { uint8_t unk00[0x278]; M3TSb33 *st278; } M3TEb33;
extern uint8_t *g_playerObj;
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
void sub_001AD7E0(float *d, const float *s);
void sub_001ADBA0(float *d, const float *a, int s);
float sub_001AD9D0(const float *a, const float *b);
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
void sub_0001D4E0(void *a);
void a3c_VecCopy(float *dst, const float *src);
void sub_001ADA60(float *d, const float *a, const float *b);
M3TCmd33 *sub_00113400(void *o, int v);
int  aab_Effect494D0(int id, const void *pos, int c);

/* 0x130450: hard stagger for the second AI kind: face away (state 0x38) or toward the player (state 0x34), rebuild the basis, set flags 0x10008 and clear the knock flag 0x80000 (command 6 timer 1/12 s). */
void m3_AiStagger130450(M3TAi33 *a, M3TEb33 *o) {
    float d[4], f[4], c;
    M3TSb33 *st = o->st278;
    M3TCmd33 *k;
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
    a->f10 |= 0x10;
    st->fC = (st->fC & ~0x1000000u) | 0x10008;
    if (st->fC & 0x80000) {
        st->fC &= ~0x80000u;
        a->f10 |= 4;
        k = sub_00113400(o, 6);
        k->f10 = 0.083333336f;
        k->f14 = 0.0f; k->f18 = 0.0f; k->f1C = 0.0f;
    }
    if (st->fC & 0x20) a->f10 |= 0xD;
}

extern float a50_frameSeconds;

/* 0x130680: launch turn for the second AI kind: face away (state 0x38) or toward the player (state 0x34) with an up and back push (-120, -60 per second), set flags 0x10008, play effect 0x16E and turn flag 0x10 into command 4 (timer 0.1 s). */
void m3_AiLaunch130680(M3TAi33 *a, M3TEb33 *o) {
    float d[4], f[4], c;
    M3TSb33 *st = o->st278;
    M3TSb33 *s2;
    M3TCmd33 *k;
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
        s2->v164[2] = 0.0f - a50_frameSeconds * 60.0f;
        s2->v164[1] = a50_frameSeconds * -120.0f;
        s2->v164[0] = 0.0f;
        s2->w170 = 1.0f;
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        s2 = o->st278;
        s2->v164[2] = 0.0f - a50_frameSeconds * 60.0f;
        s2->v164[1] = a50_frameSeconds * -120.0f;
        s2->v164[0] = 0.0f;
        s2->w170 = 1.0f;
        a3c_VecCopy(a->m20->r2, d);
    }
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    st->fC = (st->fC & ~0x1000000u) | 0x10008;
    aab_Effect494D0(0x16E, a->pos60, 0);
    if (st->fC & 0x10) {
        st->fC &= ~0x10u;
        k = sub_00113400(o, 4);
        k->f10 = 0.1f;
        k->f14 = 0.0f; k->f18 = 0.0f;
    }
    if (st->fC & 0x20) a->f10 |= 0xD;
}

/* 0x130DB0: light launch turn for the second AI kind: face away (state 0x38) or toward the player (state 0x34) with an up and back push (-60, -30 per second), set flag 8, play effect 0x16E and set AI flags 0xD. */
void m3_AiLaunch130DB0(M3TAi33 *a, M3TEb33 *o) {
    float d[4], f[4], c;
    M3TSb33 *st = o->st278;
    M3TSb33 *s2;
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
        s2->v164[2] = 0.0f - a50_frameSeconds * 30.0f;
        s2->v164[1] = a50_frameSeconds * -60.0f;
        s2->v164[0] = 0.0f;
        s2->w170 = 1.0f;
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        s2 = o->st278;
        s2->v164[2] = 0.0f - a50_frameSeconds * 30.0f;
        s2->v164[1] = a50_frameSeconds * -60.0f;
        s2->v164[0] = 0.0f;
        s2->w170 = 1.0f;
        a3c_VecCopy(a->m20->r2, d);
    }
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    st->fC |= 8;
    aab_Effect494D0(0x16E, a->pos60, 0);
    a->f10 |= 0xD;
}

typedef struct M3TSa33 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x24]; float v2C[3]; float w38; } M3TSa33;
typedef struct M3TEa33 { uint8_t unk00[0x278]; M3TSa33 *st278; } M3TEa33;

/* 0x116A30: hard stagger for the first AI kind: face away (state 0x38) or toward the player (state 0x34), rebuild the basis, set flags 0x4002 (clearing 0x80000), play effect 0x16C and clear the knock flag 0x100000 (command 4 timer 1/12 s). */
void m3_AiStagger116A30(M3TAi33 *a, M3TEa33 *o) {
    float d[4], f[4], c;
    M3TSa33 *st = o->st278;
    M3TCmd33 *k;
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
    a->f10 |= 0x10;
    st->f4 = (st->f4 & ~0x80000u) | 0x4002;
    aab_Effect494D0(0x16C, a->pos60, 0);
    if (st->f4 & 0x100000) {
        st->f4 &= ~0x100000u;
        a->f10 |= 4;
        k = sub_00113400(o, 4);
        k->f10 = 0.083333336f;
        k->f14 = 0.0f; k->f18 = 0.0f; k->f1C = 0.0f;
    }
    if (st->f4 & 0x10) a->f10 |= 0xD;
}

/* 0x1170D0: light launch turn for the first AI kind: face away (state 0x38) or toward the player (state 0x34) with an up and back push (-60, -30 per second; the toward case is offset by 1), set flag 2, play effect 0x16C and set AI flags 0xD. */
void m3_AiLaunch1170D0(M3TAi33 *a, M3TEa33 *o) {
    float d[4], f[4], c;
    M3TSa33 *st = o->st278;
    M3TSa33 *s2;
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
        s2->v2C[2] = 0.0f - a50_frameSeconds * 30.0f;
        s2->v2C[1] = a50_frameSeconds * -60.0f;
        s2->v2C[0] = 0.0f;
        s2->w38 = 1.0f;
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        s2 = o->st278;
        s2->v2C[2] = 0.0f - (0.0f - a50_frameSeconds * 30.0f - 1.0f);
        s2->v2C[1] = a50_frameSeconds * -60.0f;
        s2->v2C[0] = 0.0f;
        s2->w38 = 1.0f;
        a3c_VecCopy(a->m20->r2, d);
    }
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    st->f4 |= 2;
    aab_Effect494D0(0x16C, a->pos60, 0);
    a->f10 |= 0xD;
}
