/* Area m1, file 189: counters and camera helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Ctr189 { uint8_t unk00[4]; int32_t n4; uint8_t unk08[0x84]; } M1Ctr189;
typedef struct M1Own189 { uint8_t unk00[0x18C]; int32_t live18C; uint8_t unk190[0x70]; M1Ctr189 ctr200[1]; } M1Own189;
extern uint32_t aa0_flags420010;
extern int32_t  m1_gameMode41FF94;
extern uint32_t m1_btnB41CD04;
extern uint32_t g_ac0_42CA38;
int sub_000CD180(M1Own189 *o, int i);
int sub_0019BE60(int k);

/* 0xCD970: bump counter i: in replay mode add the recorded amount; live, add one only when the button is held and no menu/pause state blocks it. */
void m1_CounterBump0CD970(M1Own189 *o, int i) {
    M1Ctr189 *c;
    int m;
    if (o->live18C == 0) {
        c = &o->ctr200[i];
        c->n4 += sub_000CD180(o, i);
        return;
    }
    c = &o->ctr200[i];
    if (aa0_flags420010 & 0x82006) return;
    m = m1_gameMode41FF94;
    if (m == 2 || m == 4 || m == 5) return;
    if (sub_0019BE60(0x4101)) return;
    if (m1_btnB41CD04 & g_ac0_42CA38) c->n4++;
}

typedef struct M1Face189 { uint8_t unk00[0x54]; float ang54; uint8_t unk58[8]; float pos60[4]; } M1Face189;
void  rbj_VecSub(float *dst, const float *a, const float *b);
void  r4e_MatIdentity(float *m);
void  rbj_MatRotY(float *dst, const float *src, float a);
void  rbj_VecTransform(float *dst, const float *m, const float *v);
float sub_001B27C0(const float *a, const float *b);

/* 0x113200: angle between an object's facing (-Z turned by its yaw) and the direction to target. */
float m1_FaceAngle113200(M1Face189 *o, const float *target) {
    float a[4], d[4], m[16];
    a[0] = 0.0f; a[1] = 0.0f; a[2] = -1.0f; a[3] = 0.0f;
    rbj_VecSub(d, target, o->pos60);
    r4e_MatIdentity(m);
    rbj_MatRotY(m, m, o->ang54);
    rbj_VecTransform(a, m, a);
    return sub_001B27C0(a, d);
}

typedef struct M1AiS189 {
    uint8_t unk00[0xC]; float fC, f10; uint8_t unk14[0x10]; float f24, f28, f2C, f30; uint8_t unk34[4];
    int32_t i38; uint8_t unk3C[4]; uint32_t i40; uint8_t unk44[0xC]; float f50;
} M1AiS189;
typedef struct M1AiE189 { uint8_t unk00[0x4C]; uint32_t i4C; uint8_t unk50[0x228]; M1AiS189 *st278; } M1AiE189;
typedef struct M1AiO189 { uint8_t unk00[0x10]; uint32_t i10; } M1AiO189;
extern float m1_frameTime42C858;
void m1_AiSetState1456E0(M1AiO189 *a, M1AiE189 *e, int s, int t);

/* 0x1568A0: enter the idle-wait state: reset the timer and turn rates, pick the wait length (300, or 210 when unarmed) and set the waiting flags. */
void m1_AiIdleEnter1568A0(M1AiO189 *a, M1AiE189 *e) {
    M1AiS189 *s = e->st278;
    m1_AiSetState1456E0(a, e, 0, 0);
    s->fC = m1_frameTime42C858 * 0.005f;
    s->f2C = 0.0f; s->f28 = 0.0f; s->f24 = 0.0f; s->f30 = 1.0f; s->f10 = 0.0f;
    s->f50 = s->i38 ? 300.0f : 210.0f;
    a->i10 |= 0x20;
    e->i4C |= 0x70;
    s->i40 |= 0x200;
}

typedef struct M1AiT189 { uint8_t unk00[4]; uint32_t i4; uint8_t unk08[0x10]; float f18; } M1AiT189;
typedef struct M1AiF189 { uint8_t unk00[0x10]; uint32_t i10; } M1AiF189;
typedef struct M1AiG189 { uint8_t unk00[0x22]; uint8_t b22; uint8_t unk23[0x29]; uint32_t i4C; uint8_t unk50[8]; int32_t i58; uint8_t unk5C[0x21C]; M1AiT189 *st278; } M1AiG189;
typedef struct M1Tm189 { uint8_t unk00[0x10]; float f10, f14; int32_t i18; void *cb1C; } M1Tm189;
void sub_00113090(M1AiF189 *a, M1AiG189 *e, int anim);
void aab_Attach36750(M1AiF189 *a, int k);
M1Tm189 *m1_Quest113430(M1AiG189 *e, int k);
void sub_00142480(void);

/* 0x142780: enter the knocked-back state: play the knockback (or the airborne one when flagged), detach, and start a timer that calls 0x142480. */
void m1_AiKnockEnter142780(M1AiF189 *a, M1AiG189 *e) {
    M1AiT189 *s = e->st278; M1Tm189 *t;
    a->i10 |= 2;
    e->i4C &= ~0x10u;
    s->f18 = 0.0f;
    s->i4 &= ~4u;
    if (e->b22 & 1) { sub_00113090(a, e, 0x15); e->i58 = 1; }
    else sub_00113090(a, e, 4);
    aab_Attach36750(a, 0);
    t = m1_Quest113430(e, 1);
    t->f10 = 0.3f; t->f14 = 0.25f; t->i18 = 1; t->cb1C = (void *)sub_00142480;
}

typedef struct M1AiU189 { uint32_t i0; uint8_t unk04[8]; float fC, f10; uint8_t unk14[0x10]; float f24, f28, f2C, f30; uint8_t unk34[0x10]; int32_t i44; } M1AiU189;
typedef struct M1AiH189 { uint8_t unk00[0x4C]; uint32_t i4C; uint8_t unk50[0x228]; M1AiU189 *st278; } M1AiH189;
extern float m1_frameRate42C85C;

/* 0x159860: enter the leap state (anim 0x37): launch velocity back 40 and up -50 per tick, clear the move flags and count the leap. */
void m1_AiLeapEnter159860(void *a, M1AiH189 *e) {
    M1AiU189 *s = e->st278;
    m1_AiSetState1456E0((M1AiO189 *)a, (M1AiE189 *)e, 0x37, 0);
    s->f2C = 0.0f - m1_frameRate42C85C * 40.0f;
    s->f28 = m1_frameRate42C85C * -50.0f;
    s->f24 = 0.0f; s->f30 = 1.0f; s->f10 = 0.0f;
    s->fC = m1_frameTime42C858 * 0.005f;
    e->i4C &= ~0x70u;
    s->i0 |= 7;
    s->i44++;
}

typedef struct M1AiV189 { uint8_t unk00[8]; float f8; int32_t iC; } M1AiV189;
typedef struct M1AiI189 { uint8_t unk00[0x278]; M1AiV189 *st278; } M1AiI189;
typedef struct M1AiA189 { uint8_t unk00[0x30]; void *h30; } M1AiA189;
int  afc_NodeActive(M1AiA189 *a);
void aab_SetAnim832D0(void *h, int anim);
void m1_AiGoto113040(M1AiA189 *a, M1AiI189 *e, int st);

/* 0x179770: wake-up state: play anim 1 once the node is active, then go to state 2; give up to state 4 after a time limit. */
void m1_AiWake179770(M1AiA189 *a, M1AiI189 *e) {
    M1AiV189 *s = e->st278;
    switch (s->iC) {
    case 0:
        if (afc_NodeActive(a)) { aab_SetAnim832D0(a->h30, 1); s->iC++; }
        break;
    case 1:
        if (afc_NodeActive(a)) { m1_AiGoto113040(a, e, 2); return; }
        break;
    }
    if (s->f8 > 6.0f) { m1_AiGoto113040(a, e, 4); return; }
    s->f8 += m1_frameRate42C85C;
}
