/* Area m1, file 210: AI state entries. Names inferred. */
#include <stdint.h>

typedef struct M1LgS210 { uint8_t unk00[4]; float f4, f8, fC, f10; uint8_t unk14[0x10]; float f24, f28, f2C, f30; } M1LgS210;
typedef struct M1LgE210 { uint8_t unk00[0x4C]; uint32_t i4C; uint8_t unk50[0x228]; M1LgS210 *st278; } M1LgE210;
typedef struct M1LgA210 { uint8_t unk00[0x20]; float *mtx20; uint8_t unk24[0x3C]; float pos60[4]; } M1LgA210;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
extern uint8_t *g_playerObj;
int  m1_AiSetState1456E0(void *a, void *e, int s, int t);
void rbj_VecSub(float *dst, const float *a, const float *b);
void rbi_VecNorm(float *dst, const float *src);
void sub_001ADBA0(float *dst, const float *src, float s);
void r4e_VecCross3(float *dst, const float *a, const float *b);

/* 0x1596C0: enter the lunge state (anim 0x41): set the lunge speeds, face away from the player horizontally (forward = -dir), keep the object upright and rebuild its side axis. */
void m1_AiLunge1596C0(M1LgA210 *a, M1LgE210 *e) {
    M1LgS210 *s = e->st278; float d[4]; float *m;
    m1_AiSetState1456E0(a, e, 0x41, 0);
    s->f2C = 0.0f; s->f28 = 0.0f; s->f24 = 0.0f; s->f10 = 0.0f;
    s->fC = m1_frameTime42C858 * 0.005f;
    s->f30 = 1.0f;
    s->f4 = -12.0f;
    s->f8 = m1_frameRate42C85C * 10.0f;
    e->i4C &= ~0x70u;
    rbj_VecSub(d, a->pos60, (float *)(g_playerObj + 0x60));
    d[1] = 0.0f;
    rbi_VecNorm(d, d);
    sub_001ADBA0(a->mtx20 + 8, d, -1.0f);
    a->mtx20[7] = 0.0f; a->mtx20[6] = 0.0f; a->mtx20[4] = 0.0f; a->mtx20[5] = 1.0f;
    m = a->mtx20;
    r4e_VecCross3(m, m + 4, m + 8);
}

typedef struct M1BpS210 { void *o0; void *e4; uint8_t unk08[0xC]; int32_t idx14; uint8_t unk18[0xA4]; } M1BpS210;
typedef struct M1BpE210 { uint8_t unk00[0x278]; M1BpS210 *st278; void *cb27C; uint8_t unk280[8]; void *cb288; void *p28C; void *p290; uint8_t unk294[8]; void *cb29C; } M1BpE210;
typedef struct M1BpO210 { uint8_t unk00[0xC]; uint32_t iC; uint32_t i10; uint8_t unk14[0x40]; float yaw54; uint8_t unk58[8]; float pos60[4]; float s70, s74, s78; uint8_t unk7C[0xA8]; int32_t i124; } M1BpO210;
extern M1BpS210 r3_recs3FDED8[2];
extern uint8_t m1_bpTblA32B7A8[];
extern uint8_t m1_bpTblB32B7B8[];
extern float m1_bpBox27A6F4[2][4];
extern float m1_bpPos27A714[2][4];
extern float m1_bpYaw27A734[2];
void sub_0017E5D0(void);
void sub_0017E690(void);
void sub_0017E6E0(void);
void sub_000F5D60(void *o, float a, float b, float c, const float *box);
void a3c_VecCopy(float *dst, const float *src);
void m1_AiGoto113040(void *a, void *e, int st);

/* 0x17EAE0: set up boss hand idx (0 or 1): bind its state record and handlers, set its flags and collision box, place it at its start position and yaw, and start state 1. */
int m1_BossHandInit17EAE0(M1BpO210 *o, M1BpE210 *e, int idx) {
    M1BpS210 *s;
    if (o == 0) return 0;
    { int volatile vi = idx; if (vi < 0 || vi >= 2) return 0; }
    s = &r3_recs3FDED8[idx];
    e->st278 = s;
    s->o0 = o; s->e4 = e; s->idx14 = idx;
    e->p28C = m1_bpTblA32B7A8;
    e->p290 = m1_bpTblB32B7B8;
    e->cb27C = (void *)sub_0017E5D0;
    e->cb288 = (void *)sub_0017E690;
    e->cb29C = (void *)sub_0017E6E0;
    o->i10 |= 0x441;
    o->iC = (o->iC & ~0xE0u) | 3;
    o->i124 = 0;
    sub_000F5D60(o, 1.0f, -40.0f, 28.5f, m1_bpBox27A6F4[idx]);
    o->s78 = 1.0f; o->s74 = 1.0f; o->s70 = 1.0f;
    a3c_VecCopy(o->pos60, m1_bpPos27A714[idx]);
    o->yaw54 = m1_bpYaw27A734[idx];
    m1_AiGoto113040(o, e, 1);
    return 1;
}

typedef struct M1Vo210 { uint8_t unk00[0x2E8]; int32_t snd2E8; int32_t ch2EC; uint8_t unk2F0[0x10]; int32_t st300[4]; } M1Vo210;
int      sub_0019AD10(int snd, int part);
void     r4d_TrackSetPartVolume(int t, int p, int v);
uint8_t *sub_000E3DA0(void *o, int st);
void     sub_000497E0(int ch, int part, int r, void *pos, int a, float b, int c);
void     sub_00048450(int ch, int part);
void     r1c_SetRecThunk(int ch, int part, int v);

/* 0xE51F0: refresh a voice's parts: set the volume of parts 0 and 1, then re-apply each remaining part's remembered state (stop, plain, or positioned at its emitter). */
void m1_VoiceRefresh0E51F0(M1Vo210 *c) {
    int i; int32_t *st; uint8_t *p;
    if (c->ch2EC < 0) return;
    r4d_TrackSetPartVolume(c->ch2EC, 0, sub_0019AD10(c->snd2E8, 0));
    r4d_TrackSetPartVolume(c->ch2EC, 1, sub_0019AD10(c->snd2E8, 1));
    for (i = 2, st = &c->st300[2]; i < 4; i++, st++) {
        switch (*st) {
        case 0:
            sub_00048450(c->ch2EC, i);
            r1c_SetRecThunk(c->ch2EC, i, 0);
            break;
        case 1:
            sub_00048450(c->ch2EC, i);
            r1c_SetRecThunk(c->ch2EC, i, sub_0019AD10(c->snd2E8, i));
            break;
        default:
            p = sub_000E3DA0(c, *st);
            if (p != 0) sub_000497E0(c->ch2EC, i, sub_0019AD10(c->snd2E8, i), p + 0x60, 0, 1000.0f, 1);
            break;
        }
    }
}

typedef struct M1EnS210 { uint8_t unk00[0xC]; void *srcC; } M1EnS210;
typedef struct M1EnSrc210 { uint8_t unk00[0x130]; int32_t i130; } M1EnSrc210;
typedef struct M1EnE210 { uint8_t unk00[0x28]; float f28, f2C; uint8_t unk30[0x44]; M1EnS210 *st74; void *cb78; void *cb7C; void *cb80; void *p84; void *p88; } M1EnE210;
typedef struct M1EnO210 {
    uint8_t unk00[0xC]; uint32_t iC; uint32_t i10; uint8_t unk14[0x90]; float fA4; uint8_t unkA8[8]; float fB0, fB4;
    uint8_t unkB8[0x30]; float fE8; int32_t iEC, iF0; uint32_t iF4; uint8_t unkF8[0x14]; float f10C; uint8_t unk110[8];
    int32_t i118, i11C; uint32_t i120; uint8_t unk124[0xC]; int32_t i130;
} M1EnO210;
extern uint8_t m1_enTblA32C53C[];
extern uint8_t m1_enTblB32C554[];
M1EnS210 *sub_0018C400(void);
void r3b_Stop18C790(void);
void sub_0018C950(void);
void sub_0018C7A0(void);
void rbj_SetState(void *o, void *e, int st);

/* 0x18D290: set up a small enemy: take a free state slot bound to its spawn record, copy its group, hook its handlers, set its collision sizes, stats and drift, then enter state 0. 0 when no slot is free. */
int m1_EnemyInit18D290(M1EnO210 *o, M1EnE210 *e, M1EnSrc210 *src) {
    M1EnS210 *s = sub_0018C400();
    if (s == 0) return 0;
    e->st74 = s;
    s->srcC = src;
    o->i130 = src->i130;
    e->p84 = m1_enTblA32C53C;
    e->p88 = m1_enTblB32C554;
    e->cb78 = (void *)r3b_Stop18C790;
    e->cb7C = (void *)sub_0018C950;
    e->cb80 = (void *)sub_0018C7A0;
    o->iC |= 0x1C0;
    o->fB0 = 3.0f; o->fB4 = 3.0f;
    o->fA4 = -1.5f;
    o->f10C = 3.0f;
    o->iF4 = 0x80000000; o->i120 = 0x80000000;
    o->fE8 = 2.5f;
    o->iEC = 1; o->i118 = 0; o->iF0 = 2; o->i11C = 1;
    e->f28 = 0.0f; e->f2C = -7.0f;
    o->i10 |= 0x200;
    rbj_SetState(o, e, 0);
    return 1;
}
