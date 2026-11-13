/* Area m1, file 64: timed rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Phase {
    int32_t state00;           /* +0x00 */
    uint8_t unk04[4];
    float   t08;               /* +0x08 */
    int32_t phase0C;           /* +0x0C */
    float   start10, len14;    /* +0x10 */
    int32_t anim18;            /* +0x18 */
    float   show1C;            /* +0x1C */
} M1Phase;
int  sub_00145780(void *o, int anim);
void sub_001130F0(void *o, void *h, int on);
void sub_00113370(void *h, M1Phase *s);

/* 0x00155780: phased step: phase 0 waits for 0x145780(anim) (spins unless start and
 * length are positive); phase 1 shows the chain ((int)+0x1C, 0x1130F0) once the timer
 * passes the start; phase 2 finishes (done 1, 0x113370) once it passes start + length.
 * While waiting the step is marked running (2). */
void m1_Phased155780(void *o, void *h, M1Phase *s)
{
    switch (s->phase0C) {
    case 0:
        if (sub_00145780(o, s->anim18) == 0)
            break;
        if (!(s->start10 > 0.0f) || !(s->len14 > 0.0f))
            for (;;) ;
        s->phase0C++;
        break;
    case 1:
        if (s->t08 > s->start10) {
            sub_001130F0(o, h, (int)s->show1C);
            s->phase0C++;
        }
        break;
    case 2:
        if (s->t08 - s->start10 > s->len14) {
            if (s->state00 != 0)
                s->state00 = 1;
            sub_00113370(h, s);
            return;
        }
        break;
    }
    if (s->state00 != 0)
        s->state00 = 2;
}

typedef struct M1RigM { uint8_t unk00[4]; uint32_t flags04; uint8_t unk08[0x2C - 8]; float q2C[4]; uint8_t unk3C[0x4C - 0x3C]; float f4C; uint8_t unk50[0x60 - 0x50]; int32_t mode60; } M1RigM;
typedef struct M1StepM { uint8_t unk000[0x74]; float t74; uint8_t unk078[0x278 - 0x78]; M1RigM *rig278; } M1StepM;
typedef struct M1ObjM { uint8_t unk00[0x10]; uint32_t flags10; } M1ObjM;
void sub_00113A40(void *o, void *h);

/* 0x00116980: rig quaternion +0x2C = (0, 0, 0, 1), 0x113A40, rig flag 0x400; timer +0x74 =
 * 2 / 3 / 4 for rig mode 0 / 1 / 2 (spins otherwise); rig flag 0x80000, rig +0x4C = 3;
 * o flags |= 0xD with rig flag 0x10. */
void m1_RigStep116980(M1ObjM *o, M1StepM *h)
{
    M1RigM *r = h->rig278;
    int m;
    r->q2C[2] = 0.0f;
    r->q2C[1] = 0.0f;
    r->q2C[0] = 0.0f;
    r->q2C[3] = 1.0f;
    sub_00113A40(o, h);
    r->flags04 |= 0x400;
    m = r->mode60;
    if (m == 0)
        h->t74 = 2.0f;
    else if (m == 1)
        h->t74 = 3.0f;
    else if (m == 2)
        h->t74 = 4.0f;
    else
        for (;;) ;
    r->flags04 |= 0x80000;
    r->f4C = 3.0f;
    if (*(uint8_t *)&r->flags04 & 0x10)
        o->flags10 |= 0xD;
}

typedef struct M1PlP { uint8_t unk00[0x60]; float pos60[4]; } M1PlP;
extern M1PlP *g_playerObj;
void  sub_001AD9F0(float *out, const float *a, const float *b);
float sub_000F5F50(const float *v);
void  sub_001AD7E0(float *out, const float *v);

/* 0x001809B0: moves point v towards the player on the x/z plane by up to step; snaps to
 * the player's x/z when closer than that. */
void m1_StepToPlayer1809B0(float *v, float step)
{
    float d[4];
    sub_001AD9F0(d, g_playerObj->pos60, v);
    if (sub_000F5F50(d) > step) {
        d[3] = 0.0f;
        d[1] = 0.0f;
        sub_001AD7E0(d, d);
        v[0] += d[0] * step;
        v[2] += d[2] * step;
    } else {
        v[0] = g_playerObj->pos60[0];
        v[2] = g_playerObj->pos60[2];
    }
}

typedef struct M1RigN { uint8_t unk00[0x20]; float q20[4]; uint8_t unk30[0x8C - 0x30]; float f8C, f90; } M1RigN;
typedef struct M1StepN { uint8_t unk000[0x278]; M1RigN *rig278; } M1StepN;
typedef struct M1CmdN { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1CmdN;
extern float m1_frameRate42C85C;
int     sub_001456E0(void *o, void *s, int a, int b);
int     sub_00036750(void *o, int v);
M1CmdN *sub_00113400(void *h, int v);

/* 0x00187380: 0x1456E0(0x11), rig quaternion +0x20 = (0, 0, 0, 1), 0x36750(0), rig +0x8C = 0,
 * rig +0x90 = frame rate * 50, command 3 = (0.3, 0.3, 10, 0). */
void m1_RigStep187380(void *o, M1StepN *h)
{
    M1RigN *r = h->rig278;
    M1RigN *p;
    M1CmdN *c;
    sub_001456E0(o, h, 0x11, 0);
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    sub_00036750(o, 0);
    r->f8C = 0.0f;
    r->f90 = m1_frameRate42C85C * 50.0f;
    c = sub_00113400(h, 3);
    c->f10 = 0.3f;
    c->f14 = 0.3f;
    c->f18 = 10.0f;
    c->f1C = 0.0f;
}

typedef struct M1RigL { uint8_t unk00[0x20]; void *fx20; } M1RigL;
typedef struct M1StepL { uint8_t unk000[0x278]; M1RigL *rig278; } M1StepL;
typedef struct M1ObjL { uint8_t unk00[0x54]; float yaw54; } M1ObjL;
void sub_001AD940(float *m);
void sub_001AD8E0(float *out, const float *m, float a);
void sub_001AD9B0(float *out, const float *m, const float *v);
void sub_001ADBA0(float *out, const float *v, float k);
void sub_0018B260(void *fx, const float *v);
void sub_00113190(void *o, void *h, int v);

/* 0x00142330: launches the rig effect (+0x20, spins when null) along o's facing: (0, 0, -1)
 * rotated by yaw +0x54 (0x1AD940, 0x1AD8E0, 0x1AD9B0) scaled by 20 (0x1ADBA0) goes to
 * 0x18B260; then 0x113190(0) and the rig lets go of the effect. */
void m1_RigLaunch142330(M1ObjL *o, M1StepL *h)
{
    M1RigL *r = h->rig278;
    float v[4];
    float m[16];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = -1.0f;
    v[3] = 0.0f;
    if (r->fx20 == 0)
        for (;;) ;
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->yaw54);
    sub_001AD9B0(v, m, v);
    sub_001ADBA0(v, v, 20.0f);
    sub_0018B260(r->fx20, v);
    sub_00113190(o, h, 0);
    r->fx20 = 0;
}
