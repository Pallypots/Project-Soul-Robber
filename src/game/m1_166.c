/* Area m1, file 166: riding helpers (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Sub166 { uint8_t unk00[0x50]; int32_t n50; } M1Sub166;
typedef struct M1Rg166 { uint8_t unk00[8]; M1Sub166 *x8; uint8_t unk0C[0xC]; float t18; float t1C; float t20; } M1Rg166;
typedef struct M1Ob166 { uint8_t unk00[0xC]; uint32_t fC; uint8_t unk10[0x10]; uint8_t *m20; uint8_t unk24[0x3C]; float pos60[4]; } M1Ob166;
typedef struct M1Ai166 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x278 - 0x50]; M1Rg166 *rig278; } M1Ai166;
extern float m1_frameRate42C85C;
extern const float m1_offA27A904[4];
extern const float m1_offB27A918[4];
int   m1_CamMode0F40B0(void);
void  sub_000F3FD0(M1Ob166 *o);
uint8_t *sub_0001D0F0(void *o, int b);
void  sub_000F5D40(float *d, const void *s);
void  m1_VecXform1AD9B0(float *d, const void *m, const float *s);
void  sub_001ADAF0(float *d, const float *a, const float *b);
void  sub_0001EF00(M1Ob166 *o, float *v);
int   sub_0001EEC0(M1Ob166 *o, float t);

/* 0x181EF0: ride step: tick the three timers, place the rider at the mount's seat and tilt by the seat height. */
void m1_RideStep181EF0(M1Ob166 *o, M1Ai166 *e) {
    M1Rg166 *r = e->rig278; float a[4]; float *p; uint8_t *m; int volatile v;
    if (r->t18 > 0.0f) r->t18 -= m1_frameRate42C85C;
    if (r->t1C > 0.0f) r->t1C -= m1_frameRate42C85C;
    if (r->t20 > 0.0f) r->t20 -= m1_frameRate42C85C;
    if (r->x8->n50 == 1) o->fC |= 0x20; else o->fC &= ~0x20u;
    if (m1_CamMode0F40B0() == 2) e->flags4C &= ~0x1000000u;
    sub_000F3FD0(o);
    { float *volatile pp = (float *)(o->m20 + 0x30); p = pp; }
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    m = sub_0001D0F0(o, 1) + 0x40;
    sub_000F5D40(a, m1_offA27A904);
    m1_VecXform1AD9B0(a, m, a);
    sub_001ADAF0(o->pos60, a, (float *)(o->m20 + 0x70));
    sub_000F5D40(a, m1_offB27A918);
    m1_VecXform1AD9B0(a, m, a);
    sub_001ADAF0(a, a, (float *)(o->m20 + 0x70));
    sub_0001EF00(o, a);
    if (a[1] > -40.0f) v = sub_0001EEC0(o, 2.5f);
    else v = sub_0001EEC0(*(M1Ob166 *volatile *)&o, 0.0f);
}

typedef struct M1Ai166b { uint8_t unk00[0x5C]; float t5C; } M1Ai166b;
extern int32_t m1_spinDir3FE378;
extern float m1_spinAng3FE380;
extern float m1_spinSpd3FE384;
extern int32_t m1_spinRev3FE388;
extern float m1_spinTA27A994[3];
extern float m1_spinTB27A9A0[3];
extern uint32_t m1_level413178;
extern float m1_frameTime42C858;
void m1_CamSync0F3F80(void);
void m1_AngWrap0F5ED0(float *a);
int  m1_AiGoto113040(void *o, void *e, int st);

/* 0x182C00: spin the arena: accelerate the rotation toward the level's top speed (either direction). */
void m1_ArenaSpin182C00(void *o, M1Ai166b *e) {
    uint32_t n; float t, sp, acc, neg; int volatile v;
    m1_CamSync0F3F80();
    m1_spinAng3FE380 = m1_spinAng3FE380 + m1_spinSpd3FE384;
    m1_AngWrap0F5ED0(&m1_spinAng3FE380);
    n = m1_level413178;
    if (n > 2) n = 2;
    t = m1_spinDir3FE378 == 0 ? m1_spinTA27A994[n] : m1_spinTB27A9A0[n];
    sp = 3.14159274f / (t / m1_frameTime42C858);
    acc = sp * 0.00999999978f;
    if (m1_spinRev3FE388 == 0) {
        if (sp > m1_spinSpd3FE384) {
            m1_spinSpd3FE384 = m1_spinSpd3FE384 + acc;
            if (m1_spinSpd3FE384 > sp) m1_spinSpd3FE384 = sp;
        }
    } else {
        neg = 0.0f - sp;
        if (m1_spinSpd3FE384 > neg) {
            m1_spinSpd3FE384 = m1_spinSpd3FE384 - acc;
            if (neg > m1_spinSpd3FE384) m1_spinSpd3FE384 = neg;
        }
    }
    if (m1_CamMode0F40B0() == 2) { v = m1_AiGoto113040(o, e, 5); return; }
    if (e->t5C > 4.0f) v = m1_AiGoto113040(*(void *volatile *)&o, e, 5);
}

typedef struct M1Ob166c { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; void *anim30; } M1Ob166c;
typedef struct M1Ai166c {
    uint8_t unk00[0x20]; uint8_t b20; uint8_t b21; uint8_t b22; uint8_t unk23[0x35];
    int32_t n58; uint8_t unk5C[0x10]; int32_t snd6C; void *fx70; float t74;
} M1Ai166c;
typedef int (*M1Check166)(M1Ob166c *o, M1Ai166c *e, const uint8_t *tbl);
extern M1Check166 m1_chkFn31CDFC, m1_chkFn31CE00, m1_chkFn31CE04, m1_chkFn31CE08;
extern const uint8_t m1_chkT279728[], m1_chkT279738[], m1_chkT279748[], m1_chkT279758[];
int  sub_000833E0(void *a);
void sub_00033A70(void *p);
void m1_SndStop048250(int h);
void sub_00113090(void *o, void *e, int st);

/* 0x13CB80: get-up step, then pick a combo follow-up from the four check tables (strong or weak set). */
void m1_AiComboUp13CB80(M1Ob166c *o, M1Ai166c *e) {
    int volatile v;
    switch (e->n58) {
    case 0:
        if (e->t74 >= 0.0f) return;
        sub_00033A70(e->fx70);
        e->fx70 = 0;
        sub_00113090(o, e, (e->b22 & 1) + 0x18);
        m1_SndStop048250(e->snd6C);
        e->snd6C = -1;
        o->f10 &= ~0x10u;
        e->n58++;
    case 1:
        if (sub_000833E0(o->anim30) == 0) return;
        if (e->b20 & 1) {
            if (m1_chkFn31CE04(o, e, m1_chkT279748)) { v = m1_AiGoto113040(o, e, 0x13); return; }
            { volatile int k; k = -(m1_chkFn31CE08(o, e, m1_chkT279758) != 0) & 7;
            v = m1_AiGoto113040(*(M1Ob166c *volatile *)&o, e, k + 0xD); }
            return;
        }
        if (m1_chkFn31CDFC(o, e, m1_chkT279728)) { v = m1_AiGoto113040(o, e, 0x11); return; }
        { volatile int k2; k2 = -(m1_chkFn31CE00(o, e, m1_chkT279738) != 0) & 5;
        v = m1_AiGoto113040(o, e, k2 + 0xD); }
        return;
    }
}
