/* Area m3, file 17: AI knockback entry. Names inferred. */
#include <stdint.h>

typedef struct M3St17 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x14]; float tgt1C[4]; float v2C[3]; float w38; } M3St17;
typedef struct M3En17 { uint8_t unk00[0x88]; float hit88[4]; uint8_t unk98[0x1E0]; M3St17 *st278; } M3En17;
typedef struct M3Ob17 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; uint8_t unk14[0xC]; float *mtx20; } M3Ob17;
typedef struct M3Emit17 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M3Emit17;
typedef struct M3Pl17 { uint8_t unk00[0x60]; float pos60[4]; } M3Pl17;
extern M3Pl17 *g_playerObj;
extern float m1_frameTime42C858;
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
void sub_0001D4E0(void *a);
void rbi_VecScale(float *d, const float *s, float k);
void rbi_VecNorm(float *d, const float *s);
void rbi_VecCross(float *d, const float *a, const float *b);
float rbi_VecDot(const float *a, const float *b);
void a3c_VecCopy(float *dst, const float *src);
M3Emit17 *m1_Quest113400(M3En17 *e, int k);

/* 0x116F70: AI knockback entry (state 0x42): flag the state, face along the hit direction (upright axes rebuilt), set the slide speed from the hit strength, aim at the player and start emitter 4 at 1/12. */
void m3_AiKnock116F70(M3Ob17 *a, M3En17 *o) {
    M3St17 *st = o->st278; float d[4]; float *m; float k; M3Emit17 *e;
    if (m1_AiSetState1456E0(a, o, 0x42, 0) == 1) sub_0001D4E0(a);
    st->f4 |= 1;
    a->fC &= ~0x20u;
    st->f4 &= ~0x8000u;
    rbi_VecScale(d, o->hit88, -1.0f);
    d[1] = 0.0f;
    rbi_VecNorm(d, d);
    rbi_VecScale(a->mtx20 + 8, d, -1.0f);
    a->mtx20[7] = 0.0f; a->mtx20[6] = 0.0f; a->mtx20[4] = 0.0f; a->mtx20[5] = 1.0f;
    m = a->mtx20;
    rbi_VecCross(m, m + 4, m + 8);
    rbi_VecNorm(d, o->hit88);
    k = rbi_VecDot(d, o->hit88);
    o->st278->v2C[1] = 0.0f; o->st278->v2C[0] = 0.0f;
    o->st278->v2C[2] = m1_frameTime42C858 * k;
    o->st278->w38 = 1.0f;
    a3c_VecCopy(st->tgt1C, g_playerObj->pos60);
    a->f10 |= 4;
    e = m1_Quest113400(o, 4);
    e->f10 = 0.083333336f;
    e->f14 = 0.0f; e->f18 = 0.0f; e->f1C = 0.0f;
}

typedef struct M3Mot17 { uint8_t unk00[0xD8]; float curD8; } M3Mot17;
typedef struct M3Mdl17 { uint8_t unk00[0x14]; M3Mot17 *mot14; } M3Mdl17;
typedef struct M3ShA17 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; uint8_t unk14[0x1C]; M3Mdl17 *mdl30; uint8_t unk34[0x2C]; float pos60[4]; uint8_t unk70[0x80]; uint32_t iF0; uint8_t unkF4[0x34]; uint8_t b128; } M3ShA17;
typedef struct M3ShSt17 { uint8_t unk00[4]; uint32_t f4; } M3ShSt17;
typedef struct M3ShE17 { uint8_t unk00[0x24]; int32_t bone24; uint8_t unk28[0x30]; int32_t step58; uint8_t unk5C[0x1C]; float v78[4]; uint8_t unk88[0x1F0]; M3ShSt17 *st278; } M3ShE17;
int  sub_000833E0(M3Mdl17 *m);
float rbj_Distance(const float *a, const float *b);
void m1_LockMark0C56B0(M3ShA17 *a);
void sub_00113480(M3ShE17 *o, int k);
void m1_PlShot0C62A0(M3ShA17 *a);
uint8_t *sub_0001D0F0(M3ShA17 *a, int bone);
void aab_Effect494D0(int id, void *pos, int a);

/* 0x13A900: AI shoot state: step 0 locks on when the player is within 60 units and not grounded-blocked (returns 0), otherwise flags the shot, clears the push, fires (flag 0x200000 around it) and plays effect 0x77 at the muzzle bone (returns 1); step 1 returns 1 after motion frame 10; step 2 returns 1 when the animation ended. */
int m3_AiShoot13A900(M3ShA17 *a, M3ShE17 *o) {
    M3ShSt17 *st = o->st278;
    switch (o->step58) {
    case 2:
        if (!sub_000833E0(a->mdl30)) return 0;
        a->f10 &= ~4u;
        return 1;
    case 1:
        if (a->mdl30->mot14->curD8 >= 10.0f) return 1;
        return 0;
    case 0:
        if (!(a->b128 & 6) && !(rbj_Distance(a->pos60, g_playerObj->pos60) >= 60.0f) && !(st->f4 & 0x200000)) {
            m1_LockMark0C56B0(a);
            return 0;
        }
        a->fC |= 0xA0;
        a->iF0 &= ~1u;
        o->v78[0] = 0.0f; o->v78[1] = 0.0f; o->v78[2] = 0.0f; o->v78[3] = 1.0f;
        sub_00113480(o, 4);
        st->f4 |= 0x200000;
        m1_PlShot0C62A0(a);
        st->f4 &= ~0x200000u;
        aab_Effect494D0(0x77, sub_0001D0F0(a, o->bone24) + 0x70, 0);
        return 1;
    }
    return 0;
}

int  r2b_TestBit(int bit);
void sub_000A2D40(int slot, int v);
void sub_000A2CC0(int slot, int v);
void sub_000A2D10(int slot, int v);
void sub_000A2CA0(int slot, int v);
void sub_000A4410(int slot, int v);

/* 0xB3EB0: menu step for a 3-int setting: 0 clears, 1 sets bit 0 and 10, 3 forces 20; at 10 set up slots 4/6/8 (enabled look when story bit 0x2B3 is set, else the locked look with slot 8 and 4 variants), hide slots 5/7/9 and go to 20; 20 clears and returns 0. */
int m3_MenuStepB3EB0(int k, int *s) {
    if (k == 0) { s[0] = 0; s[1] = 0; s[2] = 0; return 1; }
    if (k == 1) { s[0] |= 1; s[2] = 0; s[1] = 10; return 1; }
    if (k == 3) { s[0] = 0; s[1] = 0x14; }
    s[2]++;
    if (s[1] != 10) {
        if (s[1] != 0x14) return 1;
        s[0] = 0; s[1] = 0;
        return 0;
    }
    {
        int v; volatile int z;
        if (r2b_TestBit(0x2B3)) {
            sub_000A2D40(4, 0x20); sub_000A2D40(6, 0x20); sub_000A2D40(8, 0x20);
            sub_000A2CC0(4, 0x80); sub_000A2CC0(6, 0x80); sub_000A2CC0(8, 0x80);
            sub_000A4410(4, 0); sub_000A4410(6, 0); z = 0;
            v = 0;
        } else {
            sub_000A2D40(4, 0x20); sub_000A2D40(6, 0x20); sub_000A2D10(8, 0x20);
            sub_000A2CA0(4, 0x80); sub_000A2CC0(6, 0x80); sub_000A2CC0(8, 0x80);
            sub_000A4410(4, 1); sub_000A4410(6, 1);
            v = 1;
        }
        sub_000A4410(8, v);
    }
    sub_000A4410(5, 0); sub_000A4410(7, 0); sub_000A4410(9, 0);
    s[1] = 0x14;
    return 1;
}

typedef struct M3PrT17 { uint8_t unk00[4]; int32_t i4, i8; uint8_t bC; uint8_t unkD[0x53]; float pos60[4]; uint8_t unk70[0x78]; float radE8; } M3PrT17;
typedef struct M3PrB17 { uint8_t unk00[0xEFC]; M3PrT17 *tgtEFC; } M3PrB17;
int r2b_PoolGetA(float *a, float r, float *c, float *d);
int r2b_PoolGetB(float *a, float *b, float *c, float *d);

/* 0xCACB0: probe around the boss's target like 0xCAB90: from the target position (10 units higher for kind-2 enemies of types 5, 6, 7 and 15), radius 6 or the target's larger radius; 1 on a hit, else the line probe up to radius + 2 above. */
int m3_TgtProbeCACB0(M3PrB17 *b) {
    float a[4], up[4], p[4], q[4], r; M3PrT17 *t = b->tgtEFC;
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    up[0] = 0.0f; up[1] = 0.0f; up[2] = 0.0f; up[3] = 1.0f;
    q[0] = 0.0f; q[1] = 0.0f; q[2] = 0.0f; q[3] = 1.0f;
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    a3c_VecCopy(a, t->pos60);
    if (t->i4 == 2 && (t->i8 == 5 || t->i8 == 6 || t->i8 == 7 || t->i8 == 0xF)) a[1] = a[1] + 10.0f;
    a3c_VecCopy(up, a);
    r = 6.0f;
    if (b->tgtEFC && (b->tgtEFC->bC & 0x40) && !(6.0f > b->tgtEFC->radE8)) r = b->tgtEFC->radE8;
    up[1] = up[1] + r + 2.0f;
    if (r2b_PoolGetA(a, r, q, p) > 0) return 1;
    return r2b_PoolGetB(a, up, q, p);
}
