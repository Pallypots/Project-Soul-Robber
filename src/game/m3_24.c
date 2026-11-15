/* Area m3, file 24: turn helpers. Names inferred. */
#include <stdint.h>

typedef struct M3Tn24 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[8]; float pos60[4]; } M3Tn24;
extern M3Tn24 *g_playerObj;
void rbi_VecNorm(float *d, const float *s);
float rbj_Acos(float x);

/* 0x1091C0: turn towards the player: horizontal direction to the player, its heading from acos of z (sign from x), minus the yaw, wrapped to -pi..pi; outside +-60 degrees turn by at most 2 degrees per call. */
void m3_TurnToPlayer1091C0(M3Tn24 *o) {
    float v[4], c, a;
    v[0] = g_playerObj->pos60[0] - o->pos60[0];
    v[1] = 0.0f;
    v[2] = g_playerObj->pos60[2] - o->pos60[2];
    v[3] = 1.0f;
    rbi_VecNorm(v, v);
    c = v[2];
    if (c > 1.0f) c = 1.0f;
    else if (-1.0f > c) c = -1.0f;
    if (v[0] > 0.0f) { volatile int z; a = rbj_Acos(c); z = 0; }
    else a = -rbj_Acos(c);
    a = a - o->yaw54;
    while (a > 3.1415927f) a -= 6.2831855f;
    while (-3.1415927f > a) a += 6.2831855f;
    if (-1.0471976f > a || a > 1.0471976f) {
        if (a > 0.034906585f) a = 0.034906585f;
        else if (-0.034906585f > a) a = -0.034906585f;
        o->yaw54 = o->yaw54 + a;
    }
}

typedef struct M3HH24 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0x40]; float radB0; } M3HH24;
typedef struct M3HS24 { uint8_t unk00[0x70]; int32_t mode70; uint8_t unk74[0x18]; M3HH24 *hero8C; uint8_t unk90[0x130]; int32_t i1C0; } M3HS24;
extern M3HS24 *m1_scr3F6130;
extern signed char m3_heroActA2790BC[], m3_heroActB2790CC[], m3_heroActC2790DC[], m3_heroActD2790EC[], m3_heroActE2790FC[], m3_heroActF27910C[];
int  aab_Rand(void);
float rbj_Distance(const float *a, const float *b);
void sub_000F3D10(void *t, void *h, int st);

/* 0x104E90: pick the hero's next state at random from tables by gap band (46, 80, farther) and by whether the player is above -30; -1 means state 2, and state 5 in mode 5 becomes 0x10 or 2 at random. */
void m3_HeroPick104E90(void) {
    M3HS24 *s = m1_scr3F6130; volatile int w; int r, k; float d; M3HH24 *h;
    if (((M3Tn24 *)g_playerObj)->pos60[1] > -30.0f) w = 0; else w = 1;
    r = aab_Rand() & 0xF;
    h = m1_scr3F6130->hero8C;
    d = rbj_Distance(h->pos60, g_playerObj->pos60) - h->radB0;
    if (0.0f > d || 46.0f > d) {
        if (w == 0) k = m3_heroActA2790BC[r];
        else if (w == 1) k = m3_heroActB2790CC[r];
        else goto two;
    } else if (80.0f > d) {
        if (w == 0) k = m3_heroActC2790DC[r];
        else if (w == 1) k = m3_heroActD2790EC[r];
        else goto two;
    } else {
        if (w == 0) k = m3_heroActE2790FC[r];
        else if (w == 1) k = m3_heroActF27910C[r];
        else goto two;
    }
    if (k == -1) {
two:
        k = 2;
    } else if (k == 5 && s->mode70 == 5) {
        k = (-(int)(aab_Rand() & 1) & 0xE) + 2;
    }
    h = m1_scr3F6130->hero8C;
    if (h == 0) for (;;) ;
    sub_000F3D10(h, m1_scr3F6130, k);
    m1_scr3F6130->i1C0 = 0;
}

typedef struct M3RH24 { uint8_t unk00[0x60]; float pos60[4]; } M3RH24;
typedef struct M3RB24 { uint8_t unk00[0x34]; float aim34[4]; uint8_t unk44[0xF94]; M3RH24 *holdFD8; } M3RB24;
extern void *g_42C8EC;
float sub_00171B90(M3RB24 *b);
float sub_00171BE0(M3RB24 *b);
float m1_VecLen082D70(const float *v);
void rbi_VecScale(float *d, const float *s, float k);
void r4e_VecAdd4(float *d, const float *a, const float *b);
void sub_000D45B0(void *s, float *p, float a, float b);
void a3c_VecCopy(float *dst, const float *src);
void r4c_VecSub(float *dst, const float *a, const float *b);

/* 0xC9B40: place the boss's reach point: from the held object (11.25 lower) towards the aim point; mode 0 always reaches table distance A*10, otherwise the aim point clamped to table distance B*10; hand the point to the scene. */
void m3_BossReachC9B40(M3RB24 *b, int mode) {
    float a[4], s[4], p[4], k, l; volatile int z;
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    s[0] = 0.0f; s[1] = 0.0f; s[2] = 0.0f; s[3] = 1.0f;
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    a3c_VecCopy(p, b->aim34);
    a3c_VecCopy(s, b->holdFD8->pos60);
    s[1] = s[1] - 11.25f;
    r4c_VecSub(a, p, s);
    if (mode == 0) {
        k = sub_00171B90(b) * 10.0f;
        rbi_VecNorm(a, a);
        rbi_VecScale(a, a, k);
        r4e_VecAdd4(p, s, a);
        z = 0;
    } else {
        l = m1_VecLen082D70(a);
        k = sub_00171BE0(b) * 10.0f;
        if (l > k) {
            rbi_VecNorm(a, a);
            rbi_VecScale(a, a, k);
            r4e_VecAdd4(p, s, a);
            z = 1;
        } else {
            r4e_VecAdd4(p, s, a);
            z = -1;
        }
    }
    sub_000D45B0(g_42C8EC, p, -1.0f, -1.0f);
}
