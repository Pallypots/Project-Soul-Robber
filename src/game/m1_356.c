/* Area m1, file 356: enemy aim tick (track the target point). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1St356 { uint8_t unk00[0x10]; float v10[4]; uint8_t unk20[0x90 - 0x20]; float f90; } M1St356;
typedef struct M1Ai356 { uint8_t unk000[0xF8]; int32_t iF8; uint8_t unk0FC[0x104 - 0xFC]; uint8_t *p104; uint8_t unk108[0x278 - 0x108]; M1St356 *s278; } M1Ai356;
typedef struct M1Ob356 { uint8_t unk00[0x20]; int32_t i20; } M1Ob356;
extern float m1_frameRate42C85C;
void sub_00145F70(int a, int b);
void sub_000F5D40(void *d, const void *s);
void sub_0011F0C0(M1Ai356 *e);                 /* regargs: e=EAX */

/* 0x120BF0: aim tick: refresh the model, copy the aim point (the target's position, or the
   stored point for kind 2), update the aim and count the +0x90 timer down to zero. */
void m1_AimTick120BF0(M1Ob356 *o, M1Ai356 *e) {
    M1St356 *s = e->s278;
    float v;
    sub_00145F70(o->i20, o->i20);
    if (e->iF8 == 1)
        sub_000F5D40(s->v10, e->p104 + 0x60);
    else if (e->iF8 == 2)
        sub_000F5D40(s->v10, &e->p104);
    sub_0011F0C0(e);
    v = s->f90 - m1_frameRate42C85C;
    s->f90 = v;
    if (0.0f > v)
        s->f90 = 0.0f;
}

typedef struct M1Ob356b { uint8_t unk00[0x30]; void *anim30; uint8_t unk34[0x60 - 0x34]; float p60[3]; } M1Ob356b;
extern uint8_t *g_playerObj;
float sub_001B2770(const void *a, const void *b);   /* distance */
void  sub_00131310(int next);                       /* regargs: o=EBX e=EDI */
void  sub_00131310b(int next);                      /* aliases of 0x131310: keep the four calls apart */
void  sub_00131310c(int next);
void  sub_00131310d(int next);

/* 0x132080: pick the attack by height and player distance: high up 0x15, within 60 -> 9,
   within 100 -> 0xA, else 0xB. */
void m1_AiPickByRange132080(M1Ob356b *o, void *e) {
    float d;
    if (o->p60[1] >= 50.0f) {
        sub_00131310(0x15);
        return;
    }
    d = sub_001B2770(o->p60, g_playerObj + 0x60);
    if (60.0f >= d) {
        sub_00131310b(9);
        return;
    }
    if (100.0f >= d) {
        sub_00131310c(0xA);
        return;
    }
    sub_00131310d(0xB);
}

typedef struct M1St356c { uint32_t f00; uint8_t unk04[0x2C - 4]; void *p2C; } M1St356c;
typedef struct M1Ai356c { uint8_t unk000[0x58]; int32_t n58; uint8_t unk05C[0x68 - 0x5C]; float f68; uint8_t unk06C[0x278 - 0x6C]; M1St356c *s278; } M1Ai356c;
extern float m1_frameTime42C858;
int  sub_000833E0(void *a);
int  m1_AiGoto113040(void *o, void *e, int st);
int  sub_0018C6B0(M1St356c *s);                /* regargs: s=ESI */
void sub_0018C540(void *p);

/* 0x176BB0: when the animation ends go to state 2 and advance; otherwise after 10 units
   (once) release the held effect if 0x18C6B0 allows and mark it done. */
void m1_AiRelease176BB0(M1Ob356b *o, M1Ai356c *e) {
    M1St356c *s = e->s278;
    M1St356c *t;
    if (sub_000833E0(o->anim30)) {
        m1_AiGoto113040(o, e, 2);
        e->n58++;
        return;
    }
    if (e->f68 > 10.0f / m1_frameTime42C858 * m1_frameRate42C85C && !(s->f00 & 8)) {
        t = e->s278;
        if (sub_0018C6B0(t) && t->p2C) {
            sub_0018C540(t->p2C);
            t->p2C = 0;
        }
        s->f00 |= 8;
    }
}

typedef struct M1St356d { uint8_t unk00[0x0C]; float f0C; } M1St356d;
typedef struct M1Ai356d { uint8_t unk000[0x278]; M1St356d *s278; } M1Ai356d;
float sub_00176970(void *o);                    /* regargs: o=ESI; turn angle to the target */

/* 0x176E00: approach step: within 70 of the player go to state 6; otherwise set the turn
   rate towards the target (2 degrees a frame either way beyond 10 degrees, else none). */
void m1_AiApproach176E00(M1Ob356b *o, M1Ai356d *e) {
    float d, a;
    d = sub_001B2770(o->p60, g_playerObj + 0x60);
    a = sub_00176970(o);
    if (70.0f > d) {
        m1_AiGoto113040(o, e, 6);
        return;
    }
    if (a > 0.174532935f)
        e->s278->f0C = m1_frameTime42C858 * 0.0349065848f;
    else if (-0.174532935f > a)
        e->s278->f0C = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(m1_frameTime42C858), _mm_set_ss(-0.0349065848f)));
    else
        e->s278->f0C = 0.0f;
}

typedef struct M1Ctl356 { uint8_t unk000[0x94]; int32_t i94; uint8_t unk098[0x1C4 - 0x98]; uint8_t *p1C4; uint8_t unk1C8[0x1D0 - 0x1C8]; int16_t w1D0; } M1Ctl356;
extern M1Ctl356 *b10_ctl;
int   sub_0018F650(uint8_t **slot);             /* regargs: slot=ESI */
float sub_000F7C40(void *o, void *target, float rate);
void  sub_000F3D10(void *o, void *e, int st);
float afc_VecLengthXZ(const float *v);
void  sub_001AD9F0(float *d, const void *a, const void *b);   /* d = a - b */
void  sub_0001D700(int v);

/* 0x100C50: minion follow: without a live leader drop it (state 0x24) and release the
   group; while the leader is idle steer towards the player; otherwise switch to state 0x23
   once within 35 of the leader and steer towards it. */
void m1_MinionFollow100C50(M1Ob356b *o, void *e) {
    float rate = m1_frameTime42C858 * 0.0785398185f;
    M1Ctl356 *c = b10_ctl;
    uint8_t **slot = &c->p1C4;
    float v[4];
    if (!c->p1C4 || !sub_0018F650(slot)) {
        sub_000F3D10(o, e, 0x24);
        sub_0001D700(c->i94);
        *slot = 0;
        return;
    }
    if (c->w1D0 == 0) {
        sub_000F7C40(o, g_playerObj, rate);
        return;
    }
    sub_001AD9F0(v, *slot + 0x60, o->p60);
    if (35.0f > afc_VecLengthXZ(v))
        sub_000F3D10(o, e, 0x23);
    sub_000F7C40(o, *slot, rate);
}

typedef struct M1Ctl356b {
    uint8_t unk000[0x94]; int32_t i94; uint8_t unk098[4]; int32_t i9C; float fA0; uint8_t unk0A4[0xBC - 0xA4];
    int16_t wBC; uint8_t unk0BE[0x134 - 0xBE]; int32_t snd134; uint8_t unk138[0x1C4 - 0x138]; uint8_t *p1C4;
} M1Ctl356b;
extern float m1_frameRate42C85C;
int  sub_000F5D00(void *o);
void m1_SndStop048250(int h);
void sub_000ED780(void *o);

/* 0x100DB0: minion leave sequence. Step 0: without a live leader drop it (state 0x24),
   release the group and stop the sound; with one, after a third of a unit stop the sound,
   remove the leader and advance. Step 1 waits for the minion, releases the group and resets
   the timer; step 2 finishes after 0.2 units. */
void m1_MinionLeave100DB0(void *o, void *e) {
    M1Ctl356b *c = (M1Ctl356b *)b10_ctl;
    int32_t *st = &c->i9C;
    uint8_t **slot;
    switch (c->i9C) {
    case 0:
        slot = &c->p1C4;
        if (c->p1C4 && sub_0018F650(slot)) {
            if (c->fA0 > 0.333299994f) {
                if (c->snd134 != -1) {
                    m1_SndStop048250(c->snd134);
                    c->snd134 = -1;
                }
                sub_000ED780(*slot);
                (*st)++;
                *slot = 0;
                return;
            }
            c->fA0 = c->fA0 + m1_frameRate42C85C;
            return;
        }
        sub_000F3D10(o, e, 0x24);
        sub_0001D700(c->i94);
        if (c->snd134 != -1) {
            m1_SndStop048250(c->snd134);
            c->snd134 = -1;
        }
        *slot = 0;
        return;
    case 1:
        if (!sub_000F5D00(o))
            return;
        sub_0001D700(c->i94);
        (*st)++;
        c->fA0 = 0.0f;
        return;
    case 2:
        if (c->fA0 > 0.2f) {
            c->wBC = 1;
            return;
        }
        c->fA0 = c->fA0 + m1_frameRate42C85C;
        return;
    }
}
