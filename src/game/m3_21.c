/* Area m3, file 21: boss hit by a close-range record. Names inferred. */
#include <stdint.h>

typedef struct M3HTgt21 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[4]; uint32_t fC; uint32_t f10; uint8_t unk14[0x4C]; float pos60[4]; } M3HTgt21;
typedef struct M3HRec21 { uint8_t unk00[0x10]; int32_t kind10; uint8_t unk14[0x10]; float src24[4]; } M3HRec21;
typedef struct M3HPos21 { uint8_t unk00[0x60]; float pos60[4]; } M3HPos21;
typedef struct M3HBoss21 { uint8_t unk00[0x6A8]; int32_t n6A8; uint8_t unk6AC[0x850]; void *tgtEFC; uint8_t unkF00[0xD8]; M3HPos21 *holdFD8; } M3HBoss21;
void sub_0009F710(M3HTgt21 *t, float *out);
void r2d_ObjTarget(void *o, float *out);
void a3c_VecCopy(float *dst, const float *src);
int  sub_000C4190(int kind, float *src, float *dir, float *at);
float sub_000CF200(M3HBoss21 *b, float *pos);
int  sub_000C4590(M3HBoss21 *b, M3HTgt21 *t);
void sub_000C4560(M3HBoss21 *b, M3HTgt21 *t);
void sub_000C44B0(M3HBoss21 *b, M3HTgt21 *t);
void sub_000C45D0(M3HRec21 *r, M3HTgt21 *t);
void sub_000C48A0(float *at, float k, float *src, float *a, float *b);
void m1_ActReact0CA540(M3HBoss21 *b, M3HTgt21 *t, int a);
void aab_Effect494D0(int id, void *pos, int a);

/* 0xC5060: close-range hit on the boss: like 0xC4EC0 (excluded flags 0x48 or 0x4C by target type), and only when the target is farther than the minimum and the boss has no current target; then also knock it back and play effect 0x22 at the boss. */
void m3_BossHit3C5060(M3HBoss21 *b, M3HRec21 *r, M3HTgt21 *t) {
    float at[4], dir[4], src[4], m[6]; uint8_t *e; volatile uint32_t mask;
    at[0] = 0.0f; at[1] = 0.0f; at[2] = 0.0f; at[3] = 1.0f;
    dir[0] = 0.0f; dir[1] = 0.0f; dir[2] = 0.0f; dir[3] = 1.0f;
    src[0] = 0.0f; src[1] = 0.0f; src[2] = 0.0f; src[3] = 1.0f;
    mask = 0x4C;
    if (t->f10 & 0x10) mask = 0x48;
    { volatile uint32_t f = t->fC; if (!(f & 1) || (f & 0x10000) || (t->f10 & mask)) return; }
    if (t->kind4 != 0xC) r2d_ObjTarget(t, m);
    else sub_0009F710(t, m);
    a3c_VecCopy(at, m);
    dir[0] = m[4];
    dir[1] = m[5] * -1.0f;
    a3c_VecCopy(src, r->src24);
    if (sub_000C4190(r->kind10, src, dir, at) < 0) return;
    if (!(sub_000CF200(b, t->pos60) > 0.7f)) return;
    if (b->tgtEFC) return;
    if (sub_000C4590(b, t) >= 0) return;
    sub_000C4560(b, t);
    sub_000C44B0(b, t);
    sub_000C45D0(r, t);
    { uint8_t *volatile ev = (uint8_t *)b + b->n6A8 * 16 + 0x6A8; e = ev; }
    sub_000C48A0(at, m[4], src, (float *)(e + 0x204), (float *)(e + 0x404));
    a3c_VecCopy((float *)((uint8_t *)b + b->n6A8 * 16 + 0x6AC), at);
    m1_ActReact0CA540(b, t, 1);
    aab_Effect494D0(0x22, b->holdFD8->pos60, 1);
}

typedef struct M3CMdl21 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M3CMdl21;
typedef struct M3CHold21 { uint8_t unk00[0x20]; M3CMdl21 *mdl20; } M3CHold21;
typedef struct M3CBoss21 { uint8_t unk00[0xFC]; float yawFC; uint8_t unk100[0xED8]; M3CHold21 *holdFD8; } M3CBoss21;
typedef struct M3FxRec21 { uint32_t f0; uint8_t unk04[0x10]; float f14, f18; uint8_t unk1C[0xC4]; } M3FxRec21;
extern M3FxRec21 m1_entsE41E2A0[];
void rbi_VecNorm(float *d, const float *s);
void rbi_VecScale(float *d, const float *s, float k);
float b16_TabFloat74(void *b, int i);
int  b16_TabInt74(void *b, int i);
int  m1_FxStart0C4C90(int id, float a, float b, int c, float *pos, float *dir, float *up);

/* 0xC57C0: start the boss's charge effect 0x22 at its hand bone, pointing back along the arm (scaled -0.8), facing the boss yaw, with strength from table 0x74 (times 12.5) and type from the int table; mark the effect (flag 0x8000000, 0.12, 6.0). */
void m3_BossChargeFxC57C0(M3CBoss21 *b) {
    float d[4], r[4], p[4], k; uint8_t *bones = b->holdFD8->mdl20->bonesC4; int n;
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    r[0] = 0.0f; r[1] = 0.0f; r[2] = 0.0f; r[3] = 1.0f;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    a3c_VecCopy(p, (float *)(bones + 0x1B70));
    p[3] = 1.0f;
    a3c_VecCopy(d, (float *)(b->holdFD8->mdl20->bonesC4 + 0x1B60));
    rbi_VecNorm(d, d);
    rbi_VecScale(d, d, -0.8f);
    r[2] = 0.0f; r[0] = 0.0f;
    r[1] = b->yawFC;
    d[3] = 1.0f; r[3] = 1.0f;
    k = b16_TabFloat74(b, 0) * 10.0f * 1.25f;
    n = m1_FxStart0C4C90(0x22, k, 0.2f, b16_TabInt74(b, 0), p, r, d);
    if (n < 0) return;
    {
        M3FxRec21 *e = &m1_entsE41E2A0[n];
        e->f0 |= 0x8000000;
        e->f18 = 0.12f;
        e->f14 = 6.0f;
    }
}

typedef struct M3Jmp21 { uint8_t unk00[0x94]; void *fx94; uint8_t unk98[0x10]; int32_t iA8; uint8_t unkAC[8]; float fB4, fB8, fBC, fC0, fC4, fC8, fCC, fD0; } M3Jmp21;
extern float b10_frameDelta;
extern float a50_framesPerSecond;
int  aab_Rand(void);
void *r2c_PushEffect(void *o, int a);
void Grade_AddExclamations(int n);
void sub_000F3B30(void *o, int a);
void sub_000F3F00(void *o, int a);

/* 0x10C2B0: start a random leap: pick an air time of 0.4..0.8 seconds, a sideways speed of -12..-8 and a height offset of -12..-10, derive the gravity, rise and sideways velocities and the spin (-pi over the leap), attach the push effect once (and grade it), then switch the object to state 0x20. */
void m3_RandomLeap10C2B0(void *o, M3Jmp21 *e) {
    float t, s, h, inv;
    e->fB4 = b10_frameDelta * 98.0f;
    e->fC0 = 0.0f; e->fBC = 0.0f; e->fB8 = 0.0f;
    e->fD0 = 0.0f; e->fCC = 0.0f; e->fC8 = 0.0f; e->fC4 = 0.0f;
    t = (((float)aab_Rand() * 6.1037019e-05f - 1.0f) * 0.2f + 0.6f) * a50_framesPerSecond;
    { volatile float two = 2.0f; s = ((float)aab_Rand() * 6.1037019e-05f - 1.0f) * two - 10.0f; }
    h = (float)aab_Rand() * 6.1037019e-05f - 1.0f - 11.0f;
    inv = 1.0f / t;
    e->fB4 = h * -8.0f / (t * t);
    e->fB8 = b10_frameDelta * 0.0f;
    e->fBC = inv * h * 4.0f;
    e->fC0 = inv * s;
    e->fCC = inv * -3.1415927f;
    if (e->fx94 == 0) {
        e->fx94 = r2c_PushEffect(o, 0);
        Grade_AddExclamations(1);
    }
    e->iA8 = 0;
    sub_000F3B30(o, 0x20);
    sub_000F3F00(o, 0);
}

typedef struct M3HlpT21 { uint8_t unk00[0x54]; float yaw54; uint8_t unk58[8]; float pos60[4]; } M3HlpT21;
typedef struct M3Hlp21 { uint8_t unk00[0x8C]; M3HlpT21 *tgt8C; uint8_t unk90[0x18]; float spdA8; uint8_t unkAC[0x18]; float angC4; float stepC8; uint8_t unkCC[0x28]; float distF4; uint8_t unkF8[8]; int32_t dir100; } M3Hlp21;
typedef struct M3Circ21 { uint8_t unk00[0x60]; float pos60[3]; } M3Circ21;
typedef struct M3PlC21 { uint8_t unk00[0x60]; float pos60[4]; } M3PlC21;
extern M3Hlp21 *m1_helper3F611C;
extern M3PlC21 *g_playerObj;
extern float m3_circRFar319178;
extern float m3_circRNear31917C;
float sub_000FB4A0(const float *p);
void m1_AngWrap0F5ED0(float *a);
float sub_001A3EE0(float a);
float sub_001A3ED0(float a);
float rbj_Distance(const float *a, const float *b);
void sub_000F3D10(void *t, void *h, int st);

/* 0xFCA70: run the helper's target around o at 85 units per second on the near or far radius (by the target's measure against 90), face along the tangent and add to the distance run; switch the helper to state 8 when o is farther than 80 from the player, or to state 2 after 350 units. */
void m3_HelperOrbitFCA70(M3Circ21 *o) {
    M3Hlp21 *h = m1_helper3F611C; float x, r, spd, *a, t;
    x = sub_000FB4A0(h->tgt8C->pos60);
    spd = 85.0f / a50_framesPerSecond;
    r = m3_circRFar319178;
    m1_helper3F611C->spdA8 = spd;
    if (x > 90.0f) r = m3_circRNear31917C;
    m1_helper3F611C->stepC8 = spd / (r * 6.2831855f) * 6.2831855f;
    if (h->dir100 == 0) h->angC4 = h->stepC8 + h->angC4;
    else if (h->dir100 == 1) h->angC4 = h->angC4 - h->stepC8;
    a = &h->angC4;
    m1_AngWrap0F5ED0(a);
    o->pos60[0] = sub_001A3EE0(*a) * h->spdA8 + o->pos60[0];
    o->pos60[2] = sub_001A3ED0(*a) * h->spdA8 + o->pos60[2];
    t = 0.0f - m1_helper3F611C->angC4 - 1.5707964f;
    m1_helper3F611C->tgt8C->yaw54 = t;
    if (-3.1415927f > t) m1_helper3F611C->tgt8C->yaw54 = t + 6.2831855f;
    h->distF4 = h->distF4 + h->spdA8;
    if (rbj_Distance(o->pos60, g_playerObj->pos60) > 80.0f) {
        volatile int z;
        sub_000F3D10(m1_helper3F611C->tgt8C, m1_helper3F611C, 8);
        z = 0;
        return;
    }
    if (h->distF4 > 350.0f) sub_000F3D10(m1_helper3F611C->tgt8C, m1_helper3F611C, 2);
}
