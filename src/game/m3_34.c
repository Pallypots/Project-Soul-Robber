/* Area m3, batch 34. Names inferred. */
#include <stdint.h>

typedef struct M3TMx34 { float r0[4]; float r1[4]; float r2[4]; } M3TMx34;
typedef struct M3TAi34 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0xC]; M3TMx34 *m20; uint8_t unk24[0x3C]; float pos60[4]; } M3TAi34;
typedef struct M3TCmd34 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M3TCmd34;
typedef struct M3TSa34 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x24]; float v2C[3]; float w38; } M3TSa34;
typedef struct M3TEa34 { uint8_t unk00[0x278]; M3TSa34 *st278; } M3TEa34;
extern uint8_t *g_playerObj;
extern float a50_frameSeconds;
void aab_Vec1AD9F0(float *d, const float *a, const float *b);
void sub_001AD7E0(float *d, const float *s);
void sub_001ADBA0(float *d, const float *a, int s);
float sub_001AD9D0(const float *a, const float *b);
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
void sub_0001D4E0(void *a);
void a3c_VecCopy(float *dst, const float *src);
void sub_001ADA60(float *d, const float *a, const float *b);
M3TCmd34 *sub_00113400(void *o, int v);
int  aab_Effect494D0(int id, const void *pos, int c);

/* 0x1166E0: launch turn for the first AI kind: face away (state 0x38) or toward the player (state 0x34) with an up and back push (-120, -60 per second), set flags 0x4002, play effect 0x16C, and turn flags 0x100000 and 8 into commands 4 (1/12 s) and 2 (0.1 s). */
void m3_AiLaunch1166E0(M3TAi34 *a, M3TEa34 *o) {
    float d[4], f[4], c;
    M3TSa34 *st = o->st278;
    M3TSa34 *s2;
    M3TCmd34 *k;
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
        s2->v2C[2] = 0.0f - a50_frameSeconds * 60.0f;
        s2->v2C[1] = a50_frameSeconds * -120.0f;
        s2->v2C[0] = 0.0f;
        s2->w38 = 1.0f;
        sub_001ADBA0(a->m20->r2, d, 0xBF800000);
    } else {
        if (m1_AiSetState1456E0(a, o, 0x34, 0) == 1) sub_0001D4E0(a);
        s2 = o->st278;
        s2->v2C[2] = 0.0f - (0.0f - a50_frameSeconds * 60.0f);
        s2->v2C[1] = a50_frameSeconds * -120.0f;
        s2->v2C[0] = 0.0f;
        s2->w38 = 1.0f;
        a3c_VecCopy(a->m20->r2, d);
    }
    a->m20->r1[3] = 0.0f;
    a->m20->r1[2] = 0.0f;
    a->m20->r1[0] = 0.0f;
    a->m20->r1[1] = 1.0f;
    sub_001ADA60(a->m20->r0, a->m20->r1, a->m20->r2);
    st->f4 = (st->f4 & ~0x80000u) | 0x4002;
    aab_Effect494D0(0x16C, a->pos60, 0);
    if (st->f4 & 0x100000) {
        st->f4 &= ~0x100000u;
        a->f10 |= 4;
        k = sub_00113400(o, 4);
        k->f10 = 0.083333336f;
        k->f14 = 0.0f; k->f18 = 0.0f; k->f1C = 0.0f;
    }
    if (st->f4 & 8) {
        st->f4 &= ~8u;
        k = sub_00113400(o, 2);
        k->f10 = 0.1f;
        k->f14 = 0.0f; k->f18 = 0.0f;
    }
    if (st->f4 & 0x10) a->f10 |= 0xD;
}

typedef struct M3TSb34 { uint8_t unk00[0xC]; uint32_t fC; uint8_t unk10[0x154]; float v164[3]; float w170; } M3TSb34;
typedef struct M3TEb34 { uint8_t unk00[0x278]; M3TSb34 *st278; } M3TEb34;

/* 0x1300E0: launch turn for the second AI kind (twin of 0x1166E0): face away (state 0x38) or toward the player (state 0x34) with an up and back push, set flags 0x10008, play effect 0x16E, and turn flags 0x80000 and 0x10 into commands 6 (1/12 s) and 4 (0.1 s). */
void m3_AiLaunch1300E0(M3TAi34 *a, M3TEb34 *o) {
    float d[4], f[4], c;
    M3TSb34 *st = o->st278;
    M3TSb34 *s2;
    M3TCmd34 *k;
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
        s2->v164[2] = 0.0f - (0.0f - a50_frameSeconds * 60.0f);
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
    if (st->fC & 0x80000) {
        st->fC &= ~0x80000u;
        a->f10 |= 4;
        k = sub_00113400(o, 6);
        k->f10 = 0.083333336f;
        k->f14 = 0.0f; k->f18 = 0.0f; k->f1C = 0.0f;
    }
    if (st->fC & 0x10) {
        st->fC &= ~0x10u;
        k = sub_00113400(o, 4);
        k->f10 = 0.1f;
        k->f14 = 0.0f; k->f18 = 0.0f;
    }
    if (st->fC & 0x20) a->f10 |= 0xD;
}

typedef struct M3Em34 { int active; float t; float cd; int count; int id; int part; } M3Em34;
typedef struct M3EmOb34 { uint8_t unk000[0x934]; M3Em34 em934[4]; float t994; } M3EmOb34;
extern float m3_emitLift317DF4, m3_emitRate317DF0, a50_framesPerSecond;
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *m, float a);
void sub_001AD8E0(float *d, const float *m, float a);
void sub_001AD9B0(float *d, const float *m, const float *p);
uint8_t *sub_0001D0F0(void *o, int part);
void sub_001ADAF0(float *d, const float *a, const float *b);
void *sub_000E2540(void *o, int id);
void sub_000A92A0(float *pos, float *dir, float k);
int  sub_001C7EE1(void);

/* 0xE4A20: tick an object's 4 effect emitters: an armed emitter with time, count and id fires its count bursts spread over the time, each a random direction (lift 6) from the player's part 5 toward part `part` of the emitter's target; spent emitters are cleared. */
void m3_EmitTickE4A20(M3EmOb34 *o) {
    float v[4], m[16];
    float *q = &o->em934[0].cd;
    int n = 4;
#define EM ((M3Em34 *)(q - 2))
    do {
        if (EM->active) {
            if (EM->t > 0.0f && EM->id != -1 && EM->count != 0) {
                EM->cd -= a50_frameSeconds;
                if (0.0f >= EM->cd) {
                    v[3] = 1.0f;
                    v[0] = 0.0f;
                    v[2] = 0.0f;
                    v[1] = m3_emitLift317DF4;
                    sub_001AD940(m);
                    sub_001AD8B0(m, m, ((float)sub_001C7EE1() * 6.1037019e-05f - 1.0f) * 3.1415927f);
                    sub_001AD8E0(m, m, ((float)sub_001C7EE1() * 6.1037019e-05f - 1.0f) * 3.1415927f);
                    sub_001AD9B0(v, m, v);
                    sub_001ADAF0(v, v, (float *)(sub_0001D0F0(g_playerObj, 5) + 0x70));
                    sub_000A92A0((float *)(sub_0001D0F0(sub_000E2540(o, EM->id), EM->part) + 0x70), v,
                                 a50_framesPerSecond * m3_emitRate317DF0);
                    EM->count--;
                    EM->cd = EM->t / (float)EM->count;
                }
            } else {
                EM->active = 0;
                EM->t = 0.0f;
                EM->count = 0;
                EM->id = -1;
                EM->part = 0;
            }
            EM->t -= a50_frameSeconds;
        }
        q += 6;
    } while (--n);
#undef EM
    o->t994 -= a50_frameSeconds;
}

typedef struct M3BTg34 { uint8_t unk00[0x64]; float f64; } M3BTg34;
typedef struct M3BSl34 { M3BTg34 *tgt; uint8_t unk04[4]; float v8[3]; float f14; float f18; uint8_t unk1C[4]; float t20; int st24; } M3BSl34;
typedef struct M3BOb34 { uint8_t unk000[0x86C]; M3BSl34 sl86C[1]; } M3BOb34;
extern float r2e_cue317D80[4];
extern float m3_blendIn317DE0, m3_blendHold317DE4, m3_blendOut317DE8, m3_blendWait3F1B54;
extern int m1_flag3F1B20;
void sub_001892E0(int k);
void sub_001ADC60(float *d, const float *a, const float *b, float t);
void sub_000E1FD0(void *o, int k, const float *v);
void sub_000E1F60(void *o, int k, int v);
void a3c_VecCopy(float *dst, const float *src);

/* 0xE2050: step blend slot k: state 0 eases the target value in and, near the end, fades the cue alpha; state 1 waits; state 2 lerps the slot colour back to the cue and finishes. */
void m3_BlendStepE2050(M3BOb34 *o, int k) {
    float c[4];
    M3BSl34 *s;
    M3BTg34 *g = o->sl86C[k].tgt;
    if (!g) return;
    sub_001892E0(m1_flag3F1B20);
    s = &o->sl86C[k];
    switch (s->st24) {
    case 2:
        if (m3_blendOut317DE8 > s->t20) {
            sub_001ADC60(c, s->v8, r2e_cue317D80, s->t20 / m3_blendOut317DE8);
            c[3] = s->f14;
            sub_000E1FD0(o, k, c);
            return;
        }
        sub_000E1FD0(o, k, s->v8);
        g->f64 = s->f18;
        sub_000E1F60(o, k, 1);
        return;
    case 1:
        if (s->t20 >= m3_blendWait3F1B54) {
            s->st24 = 2;
            s->t20 = 0.0f;
        }
        return;
    case 0:
        if (m3_blendIn317DE0 > s->t20) {
            g->f64 = (g->f64 - s->f18) / m3_blendIn317DE0 * (m3_blendIn317DE0 - s->t20) + s->f18;
            if (s->t20 >= m3_blendIn317DE0 - m3_blendHold317DE4) {
                a3c_VecCopy(c, r2e_cue317D80);
                c[3] = (s->t20 - (m3_blendIn317DE0 - m3_blendHold317DE4)) * ((s->f14 - r2e_cue317D80[3]) / m3_blendHold317DE4) + r2e_cue317D80[3];
                sub_000E1FD0(o, k, c);
            }
            return;
        }
        g->f64 = s->f18;
        s->st24 = 1;
        s->t20 = 0.0f;
        return;
    }
}

typedef struct M3AtTg34 { uint8_t unk00[4]; int kind4; uint8_t unk08[4]; uint32_t fC; uint8_t unk10[0x50]; float pos60[4]; } M3AtTg34;
typedef struct M3AtB34 { uint8_t unk00[0x4C]; uint32_t f4C; uint8_t unk50[0xA8]; int fF8; uint8_t unkFC[8]; M3AtTg34 *p104; } M3AtB34;
typedef struct M3AtA34 { uint8_t unk00[0x60]; float pos60[4]; } M3AtA34;
typedef struct M3Atk34 { uint8_t unk00[0x10]; int id10; int fx14; int hit18[2]; } M3Atk34;
extern int g_stats;
int  sub_00113870(void *a, void *o, void *t, int id, void *k);
void m1_FireOwnedC6CD0(void *o);
int  sub_000D3BF0(void *s, void *o, int k, float *pos, float *dir);
void *sub_00035D80(void *a, int fx, int k);
void sub_00034E00(void *h, const float *pos, const float *dir, const float *up);
void sub_00113370(void *b, void *atk);

/* 0x1396A0: attack hit pass: for the player and the attacker's held type-13 body, each not yet hit, test the attack's hit set; on a confirmed hit flag the attacker (0x100), play effect 0x88 and a spark at the hit point, then mark the target; when both are marked finish the attack. */
void m3_AttackHits1396A0(M3AtA34 *a, M3AtB34 *b, M3Atk34 *atk) {
    int i, j;
    float d[4], e[4], p[4];
    M3AtTg34 *t;
    void *h;
    volatile int z;
    for (i = 0; i < 2; i++) {
        if (atk->hit18[i] == 1) continue;
        switch (i) {
        case 0:
            t = (M3AtTg34 *)g_playerObj;
            break;
        case 1:
            if (b->fF8 != 1) continue;
            t = b->p104;
            if (!(t->fC & 1)) continue;
            if (t->kind4 != 0xD) continue;
            break;
        default:
            continue;
        }
        if (!t) continue;
        if (sub_00113870(a, b, t, atk->id10, p) < 0) continue;
        switch (t->kind4) {
        case 1:
            d[0] = ((M3AtTg34 *)g_playerObj)->pos60[0] - a->pos60[0];
            d[1] = ((M3AtTg34 *)g_playerObj)->pos60[1] - a->pos60[1];
            d[2] = ((M3AtTg34 *)g_playerObj)->pos60[2] - a->pos60[2];
            d[3] = ((M3AtTg34 *)g_playerObj)->pos60[3];
            if (!(sub_000D3BF0(&g_stats, a, atk->id10, p, d) != -1)) goto mark;
            break;
        case 0xD:
            m1_FireOwnedC6CD0(b->p104);
            break;
        default:
            goto mark;
        }
        b->f4C |= 0x100;
        aab_Effect494D0(0x88, p, 0);
        e[0] = 0.0f; e[2] = 0.0f; e[1] = -1.0f; e[3] = 1.0f;
        h = sub_00035D80(a, atk->fx14, 3);
        sub_00034E00(h, p, d, e);
mark:
        atk->hit18[i] = 1;
    }
    j = 0;
    do {
        if (!atk->hit18[j]) goto chk;
    } while (++j < 2);
    sub_00113370(b, atk);
    return;
chk:
    z = j;
    if (z >= 2) sub_00113370(b, atk);
}
