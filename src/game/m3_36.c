/* Area m3, batch 36. Names inferred. */
#include <stdint.h>

typedef struct M3SwN36 { uint8_t unk00[0x40]; float m40[16]; uint8_t unk80[0x10]; uint32_t f90; } M3SwN36;
typedef struct M3SwX36 { uint8_t unk00[0x30]; void *p30; } M3SwX36;
typedef struct M3SwM36 { uint8_t unk00[0x8C]; M3SwX36 *p8C; uint8_t unk90[8]; int16_t st98; uint8_t unk9A[6]; int16_t hA0; uint8_t unkA2[2];
                         float fA4; int16_t hA8; uint8_t unkAA[0xE]; M3SwN36 *pB8; M3SwN36 *pBC; float mC0[16]; int f100; int f104;
                         uint8_t unk108[0x10]; float ang118; } M3SwM36;
typedef struct M3SwO36 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x4C]; float pos60[4]; } M3SwO36;
extern M3SwM36 *g_acb_bossMgr;
extern float a50_frameUnits;
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *m, float a);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_001ADA40(void *node, const float *m);
int  aab_Effect494D0(int id, const void *pos, int c);
void sub_000F3F90(int k);
void sub_00195110(void);
void sub_000F3B70(void *o, int v);
int  afc_NodeActive(void *n);
void sub_000832D0(void *p, int k);
void sub_00192380(int a, int b);

/* 0xF5490: boss gate swing: state 0 holds the gate at -90 degrees and, once the node is active, starts the swing (state 1, mode 2) and fades channels 0 and 1; state 1 swings 90 degrees per 25 units and, when it closes, applies the base pose, plays effect 0x1DB and either clears the node flag or ends the encounter (mode 2). */
void m3_GateSwingF5490(M3SwO36 *o) {
    M3SwN36 *b;
    int16_t *st;
    float m[16];
    float *a;
    M3SwM36 *g = g_acb_bossMgr;
    M3SwM36 *mm;
    M3SwN36 *n;
    st = &g->st98;
    b = g->pB8;
    n = g->pBC;
    switch (*st) {
    case 1:
        a = &g->ang118;
        *a = 1.5707964f / (25.0f / a50_frameUnits) + *a;
        if (0.0f > *a) {
            sub_001AD940(m);
            sub_001AD8B0(m, m, *a);
            sub_001AD7C0(n->m40, b->m40, g->mC0);
            sub_001AD7C0(n->m40, n->m40, m);
            return;
        }
        sub_001ADA40(n, g->mC0);
        g->pBC->f90 &= ~0x40u;
        aab_Effect494D0(0x1DB, o->pos60, 1);
        g->f100 = 1;
        *a = 0.0f;
        mm = g_acb_bossMgr;
        if (!mm) for (;;) ;
        if (mm->f104 != 2) {
            o->f10 &= ~0x40u;
            sub_000F3F90(0);
            return;
        }
        g->hA0 = 0;
        g->fA4 = 0.0f;
        sub_00195110();
        sub_000F3F90(0);
        sub_000F3B70(o, 3);
        return;
    case 0:
        sub_001AD940(m);
        ((void (*)(float *, const float *, int))sub_001AD8B0)(m, m, 0xBFC90FDB);
        sub_001AD7C0(n->m40, b->m40, g->mC0);
        sub_001AD7C0(n->m40, n->m40, m);
        if (afc_NodeActive(o)) {
            if (g->f104 != 2) {
                mm = g_acb_bossMgr;
                if (mm->hA8) {
                    M3SwX36 *x = mm->p8C;
                    if (!x) for (;;) ;
                    sub_000832D0(x->p30, 0x10);
                    sub_00192380(0, 0x10);
                    sub_00192380(1, 0x10);
                }
            }
            *st = 1;
            g->f100 = 2;
        }
        return;
    }
}

typedef struct M3SpR36 { uint32_t f0; uint8_t unk04[0xDC]; } M3SpR36;
typedef struct M3SpO36 { uint8_t unk00[0xEC]; uint8_t cEC; uint8_t unkED[0x77]; int lvl164; uint8_t unk168[0xBF8]; uint8_t bD60; } M3SpO36;
extern M3SpR36 g_ac0_41E2A0[32];
extern uint8_t *g_42C8EC;
int  sub_00171AA0(void *s, int k);
int  sub_000C4C90(int k, int a, float r, int m, float *pos, float *v0, float *v1);
int  Stats_Get(void *p, int k);
void a3c_VecCopy(float *dst, const float *src);
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
float aab_Use82D70(const float *v);
void sub_001AD7E0(float *d, const float *s);
void sub_001ADBA0(float *d, const float *a, float s);
void sub_001ADAF0(float *d, const float *a, const float *b);

/* 0xC5460: spawn the stage's 15 effect points from the level table (kind 4 on level 14, else 2, with the level's model below 14); on levels 1 and 3 add one more along the table's lead direction, its distance scaled by the boost flags and the stat-4 rank. */
void m3_StageFxC5460(M3SpO36 *o) {
    float s;
    uint8_t *g;
    float a[4], b[4], c[4];
    float d;
    int m = 0, n, idx;
    uint8_t *p;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f;
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f;
    g = g_42C8EC;
    c[3] = 1.0f; b[3] = 1.0f; a[3] = 1.0f;
    s = 2.0f;
    p = g + 0x294;
    n = 15;
    do {
        a3c_VecCopy(c, (float *)p);
        if (o->lvl164 < 14) m = sub_00171AA0(o, o->lvl164);
        idx = ((int (*)(int, int, int, int, float *, float *, float *))sub_000C4C90)(o->lvl164, 0, 0x40000000, m, c, b, b);
        if (idx >= 0) {
            if (o->lvl164 == 14) g_ac0_41E2A0[idx].f0 |= 4;
            else g_ac0_41E2A0[idx].f0 |= 2;
        }
        p += 0x10;
    } while (--n);
    if (o->lvl164 != 1 && o->lvl164 != 3) return;
    if ((o->cEC & 0x40) || (o->bD60 & 2)) s = 6.0f;
    p = g + 0x384;
    aab_Vec1AD9F0(a, (float *)p, (float *)(g + 0x374));
    d = aab_Use82D70(a);
    if (Stats_Get(o, 4) < 2) {
        if ((o->cEC & 0x40) || (o->bD60 & 2)) {
            if (Stats_Get(o, 4) < 1) d *= 8.0f;
            else d *= 4.0f;
            goto go;
        }
    } else if (!(o->cEC & 0x40) && !(o->bD60 & 2)) goto go;
    { volatile float two = 2.0f; d *= two; }
go:
    sub_001AD7E0(a, a);
    sub_001ADBA0(a, a, d);
    sub_001ADAF0(c, a, (float *)p);
    idx = sub_000C4C90(o->lvl164, 0, s, m, c, b, b);
    if (idx >= 0) g_ac0_41E2A0[idx].f0 |= 2;
}

typedef struct M3CsS36 { float st; float t; float ang[2]; float pos[4]; float tgt[4]; } M3CsS36;
typedef struct M3CsO36 { uint8_t unk000[0x6D4]; M3CsS36 sl6D4[4]; } M3CsO36;
extern float a50_frameSeconds;
void sub_0003D120(int a, int k, float *x, float *y);
void sub_0003D1A0(int a, int k, float *p);
void sub_0003D220(int a, int k, float *p);
void sub_0003D160(int a, int k, float x, float y);
void sub_0003D1E0(int a, int k, const float *p);
void sub_0003D260(int a, int k, const float *p);
float sub_001A3F30(float a);
void sub_001ADC60(float *d, const float *a, const float *b, float t);

/* 0xE17A0: blend the 4 camera slots toward their goals: while a slot's time remains, ease the two angles (wrapping at 180), the position and the target by the remaining fraction; when time runs out snap to the goals and disarm the slot. */
void m3_CamBlendE17A0(M3CsO36 *o) {
    float f, t2, t, k, a[2], p[4], q[4], d, v, nt;
    float *g;
    int i, j;
    uint8_t *w = (uint8_t *)o->sl6D4[0].ang;
    for (i = 0; i < 4; i++, w += sizeof(M3CsS36)) {
        uint8_t *volatile vw = w;
        uint8_t *b = vw;
#define CS(off) (*(float *)(b + (off)))
        t = CS(-4);
        t2 = t - a50_frameSeconds;
        if (CS(-8) >= 0.0f) {
            if (t > 0.0f && t2 > 0.0f) {
                sub_0003D120(0, i, &a[0], &a[1]);
                sub_0003D1A0(0, i, p);
                sub_0003D220(0, i, q);
                f = 1.0f / t;
                g = (float *)b;
                for (j = 0; j < 2; j++, g++) {
                    d = a[j] - *g;
                    if (180.0f > sub_001A3F30(a[j] - *g)) {
                        a[j] = d * f * t2 + *g;
                        continue;
                    }
                    if (d > 0.0f) v = a[j] - *g - 360.0f;
                    else v = 360.0f - (*g - a[j]);
                    a[j] = v * f * t2 + *g;
                    if (a[j] > 180.0f) a[j] -= 360.0f;
                    if (-180.0f > a[j]) a[j] += 360.0f;
                }
                k = f * t2;
                sub_001ADC60(p, p, &CS(8), k);
                sub_001ADC60(q, q, &CS(0x18), k);
                nt = CS(-4) - a50_frameSeconds;
            } else {
                a[0] = CS(0);
                a[1] = CS(4);
                a3c_VecCopy(p, &CS(8));
                a3c_VecCopy(q, &CS(0x18));
                CS(-8) = -1.0f;
                nt = -1.0f;
            }
            CS(-4) = nt;
            sub_0003D160(0, i, a[0], a[1]);
            sub_0003D1E0(0, i, p);
            sub_0003D260(0, i, q);
        }
#undef CS
    }
}

typedef struct M3PaP36 { float m[3][4]; float pos30[4]; uint8_t unk40[0x30]; float wp70[4]; uint8_t unk80[0x10]; uint32_t f90; uint8_t unk94[0x40];
                         int fD4; uint8_t unkD8[0xA4]; int f17C; } M3PaP36;
typedef struct M3PaM36 { uint8_t unk00[0x8C]; int kind8C; } M3PaM36;
typedef struct M3PaO36 { uint8_t unk00[0x20]; M3PaM36 *m20; uint8_t unk24[0x3C]; float pos60[4]; } M3PaO36;
extern uint8_t *g_playerObj;
void r1e_PartValues(int *n, int k, void *o);
M3PaP36 *sub_0001D0F0(void *o, int part);
float sub_001A3F50(float a);
void sub_001ADA60(float *d, const float *a, const float *b);
void sub_001B2890(float *m, const float *axis, float ang);

/* 0x13A120: tilt an object's parts toward the player: from the first part each part not in the skip list (ends with a negative) points along (its offset from the first part + flat direction to the player, y -2), rotated 6 degrees per unit about the cross with down; kinds 1 and 9 clear a part link first. */
void m3_PartsAim13A120(M3PaO36 *o, int i, int *skip) {
    float len, d[4];
    int n;
    float a[4];
    M3PaP36 *p0;
    float u[4], w[4], m[16];
    M3PaP36 *q;
    int k;
    u[0] = 0.0f; u[1] = -1.0f; u[2] = 0.0f; u[3] = 0.0f;
    r1e_PartValues(&n, 0, o);
    p0 = sub_0001D0F0(o, i);
    if (o->m20->kind8C == 9) p0->f90 |= 0x20;
    aab_Vec1AD9F0(d, o->pos60, (float *)(g_playerObj + 0x60));
    len = 1.0f / sub_001A3F50((float)((double)d[0] * d[0] + (double)d[2] * d[2]));
    d[0] = len * d[0];
    d[2] = len * d[2];
    d[3] = 0.0f;
    d[1] = -2.0f;
    for (; i < n; i++) {
        q = sub_0001D0F0(o, i);
        if (o->m20->kind8C == 1) { q->f90 |= 0x40; q->fD4 = 0; }
        else if (o->m20->kind8C == 9) { q->f90 |= 0x20; q->f17C = 0; }
        for (k = 0; skip[k] >= 0 && i != skip[k]; k++) ;
        if (skip[k] >= 0) continue;
        aab_Vec1AD9F0(a, q->wp70, p0->wp70);
        sub_001AD7E0(a, a);
        sub_001ADAF0(a, a, d);
        ((void (*)(float *, const float *, int))sub_001ADBA0)(a, a, 0x3F19999A);
        a[3] = 1.0f;
        sub_001ADA60(w, a, u);
        sub_001B2890(m, w, a50_frameUnits * 0.10471976f);
        a3c_VecCopy(q->m[0], m);
        a3c_VecCopy(q->m[1], m + 4);
        a3c_VecCopy(q->m[2], m + 8);
        a3c_VecCopy(q->pos30, a);
    }
}
