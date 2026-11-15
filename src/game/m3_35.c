/* Area m3, batch 35. Names inferred. */
#include <stdint.h>

typedef struct M3PObj35 { uint8_t unk00[0xC]; uint32_t fC; } M3PObj35;
typedef struct M3PA35 { uint32_t f0; int f4; int f8; float fC, f10, f14, f18, f1C; int f20, f24, f28, f2C; float f30; float m34[3][4]; M3PObj35 *p64; } M3PA35;
typedef struct M3PB35 { uint32_t f0; float f4, f8, fC; int f10; float m14[2][4]; uint8_t unk34[0xB4]; M3PObj35 *pE8; } M3PB35;
typedef struct M3PC35 { uint32_t f0; float f4, f8; int fC, f10; float f14; float v18[4]; float v28[4]; float s38[4]; float z48[4]; M3PObj35 *p58; } M3PC35;
extern M3PA35 g_ac0_slots[3];
extern M3PB35 g_ac0_xforms[20];
extern M3PC35 m3_fxPool41CD40[4];
void sub_0001EB80(void *o);

/* 0xC85C0: release every live record in the three effect pools (3 slots, 20 transforms, 4 effects): unflag and free the owner object, then reset the record to its defaults. */
void m3_PoolsResetC85C0(void) {
    uint8_t *q;
    for (q = (uint8_t *)&g_ac0_slots[0] + 8; (int32_t)q < (int32_t)((uint8_t *)&g_ac0_slots[3] + 8); q += sizeof(M3PA35)) {
        uint8_t *volatile vq = q; M3PA35 *e = (M3PA35 *)(vq - 8);
        if (!(e->f0 & 1)) continue;
        e->p64->fC &= ~1u;
        sub_0001EB80(e->p64);
        e->f0 = 0; e->f4 = 1; e->f8 = 0;
        e->fC = 0.0f; e->f10 = 0.0f; e->f14 = 1.0f;
        e->f20 = 0; e->f24 = 0;
        e->f18 = 0.5f; e->f1C = 0.0f;
        e->f28 = 0; e->f2C = 0;
        e->f30 = 0.0f;
        e->m34[0][2] = 0.0f; e->m34[0][1] = 0.0f; e->m34[0][0] = 0.0f;
        e->m34[1][2] = 0.0f; e->m34[1][1] = 0.0f; e->m34[1][0] = 0.0f;
        e->m34[2][2] = 0.0f; e->m34[2][1] = 0.0f; e->m34[2][0] = 0.0f;
        e->m34[2][3] = 1.0f; e->m34[1][3] = 1.0f; e->m34[0][3] = 1.0f;
        e->p64 = 0;
    }
    for (q = (uint8_t *)&g_ac0_xforms[0] + 8; (int32_t)q < (int32_t)((uint8_t *)&g_ac0_xforms[20] + 8); q += sizeof(M3PB35)) {
        uint8_t *volatile vq = q; M3PB35 *e = (M3PB35 *)(vq - 8);
        if (!(e->f0 & 1)) continue;
        e->pE8->fC &= ~1u;
        sub_0001EB80(e->pE8);
        e->f0 = 0;
        e->f4 = 0.0f; e->f8 = 1.0f; e->fC = 0.0f;
        e->f10 = 0;
        e->m14[0][2] = 0.0f; e->m14[0][1] = 0.0f; e->m14[0][0] = 0.0f;
        e->m14[1][2] = 0.0f; e->m14[1][1] = 0.0f; e->m14[1][0] = 0.0f;
        e->m14[1][3] = 1.0f; e->m14[0][3] = 1.0f;
        e->pE8 = 0;
    }
    for (q = (uint8_t *)&m3_fxPool41CD40[0] + 8; (int32_t)q < (int32_t)((uint8_t *)&m3_fxPool41CD40[4] + 8); q += sizeof(M3PC35)) {
        uint8_t *volatile vq = q; M3PC35 *e = (M3PC35 *)(vq - 8);
        if (!(e->f0 & 1)) continue;
        e->p58->fC &= ~1u;
        sub_0001EB80(e->p58);
        e->f4 = 0.0f; e->f8 = 0.0f;
        e->v18[2] = 0.0f; e->v18[1] = 0.0f; e->v18[0] = 0.0f;
        e->v28[2] = 0.0f; e->v28[1] = 0.0f; e->v28[0] = 0.0f;
        e->z48[3] = 0.0f; e->z48[2] = 0.0f; e->z48[1] = 0.0f; e->z48[0] = 0.0f;
        e->f0 = 0; e->fC = 0; e->f10 = 0;
        e->s38[3] = 0.01f; e->s38[2] = 0.01f; e->s38[1] = 0.01f; e->s38[0] = 0.01f;
        e->v28[3] = 1.0f; e->v18[3] = 1.0f;
        e->p58 = 0;
    }
}

#include <xmmintrin.h>
typedef struct M3HtTg35 { uint8_t unk00[4]; int kind4; uint8_t unk08[4]; uint32_t fC; uint8_t unk10[0x50]; float pos60[4]; } M3HtTg35;
typedef struct M3HtB35 { uint8_t unk00[0x20]; int8_t c20; uint8_t unk21[0x2B]; uint32_t f4C; uint8_t unk50[0xA8]; int fF8; uint8_t unkFC[8]; M3HtTg35 *p104; } M3HtB35;
typedef struct M3HtMx35 { float r0[4]; float r1[4]; float r2[4]; } M3HtMx35;
typedef struct M3HtA35 { uint8_t unk00[0x20]; M3HtMx35 *m20; uint8_t unk24[0x3C]; float pos60[4]; } M3HtA35;
typedef struct M3HtK35 { uint8_t unk00[0x10]; float id10; uint8_t unk14[4]; float hit18; float hit1C; } M3HtK35;
#define M3I35(f) _mm_cvtt_ss2si(_mm_load_ss(&(f)))
extern uint8_t *g_playerObj;
extern int g_stats;
int  sub_00113870(void *a, void *o, void *t, int id, void *k);
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
void sub_001AD7E0(float *d, const float *s);
int  sub_000D3BF0(void *s, void *o, int k, float *pos, float *dir);
int  aab_Effect494D0(int id, const void *pos, int c);
void *sub_00035D80(void *a, int fx, int k);
void sub_00034DD0(void *h, const float *pos, const float *dir, const float *up);
void m1_FireOwnedC6CD0(void *o);
void sub_00113370(void *b, void *atk);

/* 0x11E510: hit pass for an attack whose flags are floats: for the player and the attacker's held type-13 body, each still armed, test the hit set; on a confirmed hit play effect 0xF6 (kinds 1, 3, 4) and a spark along the attacker's axes, flag the attacker and disarm the target; finish when both are disarmed. */
void m3_AttackHits11E510(M3HtA35 *a, M3HtB35 *b, M3HtK35 *k) {
    int i;
    float d[4], p[4], n2[4], n1[4];
    M3HtTg35 *t;
    void *h;
    int kd;
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            if (!M3I35(k->hit18)) continue;
            t = (M3HtTg35 *)g_playerObj;
        } else {
            if (i == 1 && !M3I35(k->hit1C)) continue;
            if (b->fF8 != 1) continue;
            t = b->p104;
            if (!(t->fC & 1)) continue;
            if (t->kind4 != 0xD) continue;
        }
        if (!t) continue;
        if (sub_00113870(a, b, t, M3I35(k->id10), p) < 0) continue;
        if (i == 0) {
            aab_Vec1AD9F0(d, ((M3HtTg35 *)g_playerObj)->pos60, a->pos60);
            d[1] = 0.0f;
            d[3] = 1.0f;
            sub_001AD7E0(d, d);
            if (sub_000D3BF0(&g_stats, a, M3I35(k->id10), p, d) == -1) {
                k->hit18 = 0.0f;
                continue;
            }
        }
        kd = M3I35(k->id10);
        if (kd == 1 || kd == 3 || kd == 4) aab_Effect494D0(0xF6, a->pos60, 0);
        h = sub_00035D80(a, (b->c20 & 1) | 0xC, 1);
        if (h) {
            sub_001AD7E0(n1, a->m20->r2);
            sub_001AD7E0(n2, a->m20->r1);
            sub_00034DD0(h, p, n1, n2);
        }
        b->f4C |= 0x100;
        if (i == 0) {
            k->hit18 = 0.0f;
        } else {
            m1_FireOwnedC6CD0(t);
            k->hit1C = 0.0f;
        }
    }
    if (!M3I35(k->hit18) && !M3I35(k->hit1C)) sub_00113370(b, k);
}

typedef struct M3FxO35 { uint8_t unk00[0xC]; uint32_t fC; } M3FxO35;
typedef struct M3Fx35 { uint32_t f0; uint8_t unk04[8]; float tC; uint8_t unk10[0xC]; int f1C; int f20; uint8_t unk24[8]; float f2C;
                        uint8_t unk30[0x10]; float pos40[3]; float f4C; float f50[4]; float v60[4]; float v70[4]; uint8_t unk80[0x54];
                        void *pD4; M3FxO35 *pD8; } M3Fx35;
extern M3Fx35 aab_recDC[56];
extern float m1_sndPos423F40[4];
extern float a50_frameUnits;
void sub_000A58B0(M3Fx35 *r);
void sub_001ADBA0(float *d, const float *a, float s);
void sub_001ADAF0(float *d, const float *a, const float *b);
int  m1_HandsNearA8BF0(void *r, void *s);
int  m1_AnyNearA8C90(void *r);
void sub_000A7830(M3Fx35 *r);
void sub_000A79E0(M3Fx35 *r);
void sub_0001EB80(void *o);
void sub_00033A40(void *h);
void sub_000A7700(void *r);

/* 0xA9710: per-frame update of the 56 drop records: move falling ones (with spin), flag them when near the hands or any picker, run their two step hooks, expire timed ones (state 15) and free finished ones; then age the four sound timers (reset to -1 after 30). */
void m3_DropsTickA9710(void) {
    float t[4];
    uint8_t *q;
    int i;
    for (q = (uint8_t *)aab_recDC[0].v60; (int32_t)q < (int32_t)aab_recDC[56].v60; q += sizeof(M3Fx35)) {
        uint8_t *volatile vq = q;
        uint8_t *b = vq;
        uint32_t f;
#define R35(off, T) (*(T *)(b + (off) - 0x60))
        if (!(R35(0, uint32_t) & 1)) continue;
        sub_000A58B0((M3Fx35 *)(b - 0x60));
        f = R35(0, uint32_t);
        if (f & 0x10) {
            sub_001ADBA0(t, (float *)b, a50_frameUnits);
            {
                float *pp = &R35(0x40, float);
                sub_001ADAF0(pp, pp, t);
                sub_001ADAF0((float *)b, (float *)b, pp + 12);
            }
            f = R35(0, uint32_t);
            if (!(f & 0x20)) {
                R35(0x44, float) += R35(0x2C, float) * a50_frameUnits;
                R35(0x2C, float) += 0.06f;
            }
        }
        if ((f & 0x100) && m1_HandsNearA8BF0(b - 0x60, &g_stats) > 0) goto near;
        if ((R35(0, uint32_t) & 0x200) && m1_AnyNearA8C90(b - 0x60) > 0) {
near:
            R35(0, uint32_t) |= 0x400;
        }
        sub_000A7830((M3Fx35 *)(b - 0x60));
        sub_000A79E0((M3Fx35 *)(b - 0x60));
        f = R35(0, uint32_t);
        if (f & 0x40) {
            R35(0xC, float) -= a50_frameUnits;
            if (0.0f > R35(0xC, float)) {
                R35(0, uint32_t) = f | 0x20000000;
                if (R35(0x1C, int) != 15) {
                    R35(0x1C, int) = 15;
                    R35(0x20, int) = 0;
                }
            }
        }
        if (R35(0, uint32_t) & 0x40000000) {
            R35(0xD8, M3FxO35 *)->fC &= ~1u;
            sub_0001EB80(R35(0xD8, M3FxO35 *));
            if (R35(0xD4, void *)) sub_00033A40(R35(0xD4, void *));
            sub_000A7700(b - 0x60);
        }
#undef R35
    }
    for (i = 0; i < 4; i++) {
        if (m1_sndPos423F40[i] >= 0.0f) {
            m1_sndPos423F40[i] += a50_frameUnits;
            if (m1_sndPos423F40[i] > 30.0f) m1_sndPos423F40[i] = -1.0f;
        }
    }
}
