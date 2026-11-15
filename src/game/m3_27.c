/* Area m3, file 27: menu steps and revisits. Names inferred. */
#include <stdint.h>

typedef struct M3MS27 { uint8_t unk00[0x48]; int32_t i48; } M3MS27;
extern uint8_t g_stats[];
extern float a50_framesPerSecond;
M3MS27 *m1_SlotGet0A4290(int i);
int  r2b_TestBit(int bit);
void sub_000A42F0(int i, int v);
void sub_000A4410(int slot, int v);
int  sub_000A2CE0(int slot, int f);
void sub_000A2CC0(int slot, int v);
/* float argument passed as its bit pattern (-10000.0f) so cl pushes the immediate like the original */
void m1_PowerAdd0CAE20(void *s, int vbits);
int  sub_000A3510(int slot, int a);
void sub_000A34B0(int slot, int v, int a);
void sub_000D9B30(int bit);

/* 0xAEC00: menu step for slot 4 (bit 0x2C3 picks the look): 10 opens it, 11 shows buttons 5..8 by the bit, moves slot 4 to its follow-up state (charging -10000 power on a buy press), counts presses and clears the bit after fps*10 presses or on cancel; 20 clears and returns 0. */
int m3_MenuStepAEC00(int k, int *s) {
    M3MS27 *o; int n; volatile int z;
    if (k == 0) { s[0] = 0; s[1] = 0; s[2] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[2] = 0; s[1] = 10; return 1; }
    if (k == 3) { s[0] = 0; s[1] = 0x14; }
    s[2]++;
    switch (s[1]) {
    case 0x14:
        s[0] = 0; s[1] = 0;
        return 0;
    case 0xA:
        sub_000A42F0(4, -(int)(r2b_TestBit(0x2C3) == 0) & 2);
        s[1]++;
        /* fall through */
    case 0xB:
        o = m1_SlotGet0A4290(4);
        if (r2b_TestBit(0x2C3)) {
            sub_000A4410(5, 0); sub_000A4410(6, 1); sub_000A4410(7, 1); sub_000A4410(8, 0);
            if (o->i48 != 0 && o->i48 != 3) {
                sub_000A42F0(4, 3);
                if (sub_000A2CE0(4, 0x1000)) {
                    m1_PowerAdd0CAE20(g_stats, (int)0xC61C3C00);
                    sub_000A2CC0(4, 0x1000);
                    z = 0;
                }
            }
            n = sub_000A3510(4, 2) + 1;
            sub_000A34B0(4, n, 2);
            if ((float)n >= a50_framesPerSecond * 10.0) { sub_000D9B30(0x2C3); z = -1; }
            else if (sub_000A2CE0(4, 0x2000)) sub_000D9B30(0x2C3);
        } else {
            sub_000A4410(5, 1); sub_000A4410(6, 0); sub_000A4410(7, 0); sub_000A4410(8, 1);
            if (o->i48 != 1 && o->i48 != 2) {
                sub_000A42F0(4, 1);
                if (sub_000A2CE0(4, 0x1000)) {
                    m1_PowerAdd0CAE20(g_stats, (int)0xC61C3C00);
                    sub_000A2CC0(4, 0x1000);
                    z = 1;
                }
            }
        }
        if (sub_000A2CE0(4, 0x2000)) sub_000A2CC0(4, 0x2000);
        return 1;
    }
    return 1;
}

typedef struct M3St27 { uint8_t unk00[4]; uint8_t b4; uint8_t unk05[0x27]; float v2C[3]; float w38; } M3St27;
typedef struct M3En27 { uint8_t unk00[0x278]; M3St27 *st278; } M3En27;
typedef struct M3Ob27 { uint8_t unk00[0x60]; float pos60[4]; } M3Ob27;
extern M3Ob27 *g_playerObj;
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
void sub_0001D4E0(void *a);
void a3c_VecCopy(float *dst, const float *src);
void r4c_VecSub(float *dst, const float *a, const float *b);
float rfl_AngleFromZ(const float *v);
void sub_0001F100(void *a, float ang, int b);

/* 0x117470: warp the AI to its fixed spot (-0.029, 205.948, -2.273) in state 0x14 or 0x18, stop it, and turn it to face away from the player horizontally. */
void m3_AiWarp117470(M3Ob27 *a, M3En27 *o) {
    float d[4], t[4]; volatile int k;
    t[0] = -0.029f; t[1] = 205.948f; t[2] = -2.273f; t[3] = 1.0f;
    k = 0x18;
    if (o->st278->b4 & 0x10) k = 0x14;
    if (m1_AiSetState1456E0(a, o, k, 0) == 1) sub_0001D4E0(a);
    o->st278->v2C[2] = 0.0f; o->st278->v2C[1] = 0.0f; o->st278->v2C[0] = 0.0f;
    o->st278->w38 = 1.0f;
    a3c_VecCopy(a->pos60, t);
    r4c_VecSub(d, a->pos60, g_playerObj->pos60);
    if (0.001f > d[0] && 0.001f > d[2]) d[0] = 1.0f;
    d[1] = 0.0f;
    sub_0001F100(a, rfl_AngleFromZ(d), 0);
}

typedef struct M3Btn27 { uint8_t unk00[0xC]; uint32_t fC; } M3Btn27;
typedef struct M3Slot27 { uint32_t f0; uint8_t unk04[0x11C]; M3Btn27 *btn120; } M3Slot27;
int  sub_000A4370(int slot);

/* 0xB86E0: menu step for a 3-int setting (third = frame counter): 0 clears, 1 sets bit 0 and 10, 3 forces the close state 0x63; 10 opens slot 0 (look 2 or 3 by story bit 0xE2), 11 waits for it and then shows or hides its button by that bit, 0x63 clears and returns 0. */
int m3_MenuStepB86E0(int k, int *s) {
    M3Slot27 *o;
    if (k == 0) { s[0] = 0; s[1] = 0; s[2] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[2] = 0; s[1] = 10; return 1; }
    if (k == 3) { s[0] = 0; s[1] = 0x63; }
    s[2]++;
    switch (s[1]) {
    case 0x63:
        s[0] = 0; s[1] = 0;
        return 0;
    case 0xB:
        if (!sub_000A4370(0)) return 1;
        o = (M3Slot27 *)m1_SlotGet0A4290(0);
        if (r2b_TestBit(0xE2)) {
            o->f0 &= ~0x40u;
            o->btn120->fC &= ~0x20u;
            s[1] = 0x63;
            return 1;
        }
        sub_000A42F0(0, 4);
        o->f0 |= 0x40;
        o->btn120->fC |= 0x20;
        s[1] = 0x63;
        return 1;
    case 0xA:
        {
            volatile int v = 3;
            if (r2b_TestBit(0xE2)) v = 2;
            sub_000A42F0(0, v);
        }
        s[1]++;
        return 1;
    }
    return 1;
}

typedef struct M3Pt28 { float m00[16]; float m40[12]; float v70[3]; float w7C; struct M3Pt28 *par80; } M3Pt28;
void   r1e_PartValues(int *n, int k, void *o);
M3Pt28 *sub_0001D0F0(void *o, int part);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_001ADAF0(float *d, const float *a, const float *b);
extern float a50_frameUnits;

/* 0x13A380: rebuild part matrices from first..last; parts not in the skip list (ends with a negative) get their 3x4 rows applied as a local transform plus drift, listed parts follow their parent. */
void m3_PartMats13A380(void *o, int n, int *skip) {
    float m[16];
    int i = n, k;
    M3Pt28 *p;
    r1e_PartValues(&n, 0, o);
    for (; i < n; i++) {
        p = sub_0001D0F0(o, i);
        for (k = 0; skip[k] >= 0 && i != skip[k]; k++) ;
        if (skip[k] < 0) {
            a3c_VecCopy(&m[0], p->m00);
            a3c_VecCopy(&m[4], p->m00 + 4);
            a3c_VecCopy(&m[8], p->m00 + 8);
            m[12] = 0.0f; m[13] = 0.0f; m[14] = 0.0f; m[15] = 1.0f;
            sub_001AD7C0(p->m40, p->m40, m);
            sub_001ADAF0(p->v70, p->v70, p->m00 + 12);
            p->w7C = 1.0f;
            p->m00[13] += a50_frameUnits * 0.1f;
        } else {
            sub_001AD7C0(p->m40, p->par80->m40, p->m00);
        }
    }
}
