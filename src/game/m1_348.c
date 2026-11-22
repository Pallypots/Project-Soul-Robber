/* Area m1, file 348: enemy cast sequence. Names inferred. */
#include <stdint.h>

typedef struct M1St348 { uint8_t unk00[0x164]; float v164[4]; } M1St348;
typedef struct M1Ai348 {
    uint8_t unk000[0x4C]; uint32_t f4C; uint8_t unk050[0x58 - 0x50]; int32_t n58;
    uint8_t unk05C[0x74 - 0x5C]; float f74; uint8_t unk078[0x278 - 0x78]; M1St348 *s278;
} M1Ai348;
typedef struct M1Ob348 { uint8_t unk00[0x30]; void *anim30; } M1Ob348;
typedef struct M1Kc348 { uint8_t unk00[0x10]; float f10, f14, f18, f1c; } M1Kc348;
int      sub_000833E0(void *a);
int      sub_000833E0b(void *a);   /* alias: keeps the second wait apart */
int      m1_AiSetState1456E0(void *o, void *e, int st, int f);
void     sub_0001D4E0(void *o);
M1Kc348 *m1_Quest113400(void *e, int v);
void     sub_00131310(int next);                      /* regargs: o=EBX e=EDI */

/* 0x1337B0: cast: wait for the animation, enter pose 0x2C with a 4-unit wait, then step 3;
   pose 0x2D with a 2-unit effect timer; wait for it to end, then finish into 0xF (flag
   0x100) or 5. */
void m1_AiCast1337B0(M1Ob348 *o, M1Ai348 *e) {
    M1St348 *s;
    M1Kc348 *c;
    switch (e->n58) {
    case 0:
        if (!sub_000833E0(o->anim30))
            return;
        e->n58++;
        return;
    case 1:
        if (m1_AiSetState1456E0(o, e, 0x2C, 0) == 1)
            sub_0001D4E0(o);
        s = e->s278;
        s->v164[2] = 0.0f;
        s->v164[1] = 0.0f;
        s->v164[0] = 0.0f;
        s->v164[3] = 1.0f;
        e->f74 = 4.0f;
        e->n58++;
        return;
    case 2:
        if (!(0.0f >= e->f74))
            return;
        e->n58 = 3;
        return;
    case 3:
        if (m1_AiSetState1456E0(o, e, 0x2D, 0) == 1)
            sub_0001D4E0(o);
        s = e->s278;
        s->v164[2] = 0.0f;
        s->v164[1] = 0.0f;
        s->v164[0] = 0.0f;
        s->v164[3] = 1.0f;
        c = m1_Quest113400(e, 2);
        c->f10 = 2.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        e->n58++;
        return;
    case 4:
        if (!sub_000833E0b(o->anim30))
            return;
        e->n58++;
        return;
    case 5:
        if (e->f4C & 0x100)
            sub_00131310(0xF);
        else
            sub_00131310(5);
        return;
    }
}

typedef struct M1St348b { uint8_t unk00[0x10]; float c10[7]; float c2C[7]; float c48[7]; float t64; float dt68; } M1St348b;
typedef struct M1Ob348b { uint8_t unk00[0x30]; void *anim30; uint8_t unk34[0x60 - 0x34]; float p60[3]; } M1Ob348b;
void  sub_00113480(void *e, int k);
void  sub_00083420(void *a, int k, int f);
float sub_00062080(const float *c, float t);

/* 0x131B80: rise along a curve: wait for the animation (closing the move effect), enter pose
   0x11 and wait until the curve parameter reaches 1, enter pose 0x12 (holding its last
   frame), wait for the animation, then finish into state 3. In steps 1..4 the parameter
   advances (clamped to 1) and the position follows the three curves. */
void m1_AiRiseCurve131B80(M1Ob348b *o, M1Ai348 *e) {
    M1St348b *c = (M1St348b *)e->s278;
    M1St348 *s;
    volatile int n;
    float t;
    switch (e->n58) {
    case 0:
        if (sub_000833E0(o->anim30)) {
            sub_00113480(e, 1);
            e->n58++;
        }
        break;
    case 1:
        if (m1_AiSetState1456E0(o, e, 0x11, 0) == 1)
            sub_0001D4E0(o);
        s = e->s278;
        s->v164[2] = 0.0f;
        s->v164[1] = 0.0f;
        s->v164[0] = 0.0f;
        s->v164[3] = 1.0f;
        e->n58++;
    case 2:
        if (c->t64 >= 1.0f)
            e->n58++;
        break;
    case 3:
        if (m1_AiSetState1456E0(o, e, 0x12, 0) == 1)
            sub_0001D4E0(o);
        sub_00083420(o->anim30, 0x12, 0);
        s = e->s278;
        s->v164[2] = 0.0f;
        s->v164[1] = 0.0f;
        s->v164[0] = 0.0f;
        s->v164[3] = 1.0f;
        e->n58++;
        break;
    case 4:
        if (sub_000833E0(o->anim30))
            e->n58++;
        break;
    case 5:
        sub_00131310(3);
        break;
    }
    n = e->n58;
    if (n >= 1 && n <= 4) {
        t = c->dt68 + c->t64;
        c->t64 = t;
        if (t > 1.0f)
            c->t64 = 1.0f;
        o->p60[0] = sub_00062080(c->c10, c->t64);
        o->p60[1] = sub_00062080(c->c2C, c->t64);
        o->p60[2] = sub_00062080(c->c48, c->t64);
    }
}

typedef struct M1St348c { uint8_t unk00[0x0C]; float c0C[7]; float c28[7]; float c44[7]; float t60; float dt64; } M1St348c;
typedef struct M1St348d { uint8_t unk00[0x160]; float v160[4]; } M1St348d;
void sub_00135A70(int next);                      /* regargs */

/* 0x136400: twin of 0x131B80 for another enemy (curves at +0x0C/+0x28/+0x44, blend vector at
   +0x160) that finishes into state 5 through 0x135A70. */
void m1_AiRiseCurve136400(M1Ob348b *o, M1Ai348 *e) {
    M1St348c *c = (M1St348c *)e->s278;
    M1St348d *s;
    volatile int n;
    float t;
    switch (e->n58) {
    case 0:
        if (sub_000833E0(o->anim30)) {
            sub_00113480(e, 1);
            e->n58++;
        }
        break;
    case 1:
        if (m1_AiSetState1456E0(o, e, 0x11, 0) == 1)
            sub_0001D4E0(o);
        s = (M1St348d *)e->s278;
        s->v160[2] = 0.0f;
        s->v160[1] = 0.0f;
        s->v160[0] = 0.0f;
        s->v160[3] = 1.0f;
        e->n58++;
    case 2:
        if (c->t60 >= 1.0f)
            e->n58++;
        break;
    case 3:
        if (m1_AiSetState1456E0(o, e, 0x12, 0) == 1)
            sub_0001D4E0(o);
        sub_00083420(o->anim30, 0x12, 0);
        s = (M1St348d *)e->s278;
        s->v160[2] = 0.0f;
        s->v160[1] = 0.0f;
        s->v160[0] = 0.0f;
        s->v160[3] = 1.0f;
        e->n58++;
        break;
    case 4:
        if (sub_000833E0(o->anim30))
            e->n58++;
        break;
    case 5:
        sub_00135A70(5);
        break;
    }
    n = e->n58;
    if (n >= 1 && n <= 4) {
        t = c->dt64 + c->t60;
        c->t60 = t;
        if (t > 1.0f)
            c->t60 = 1.0f;
        o->p60[0] = sub_00062080(c->c0C, c->t60);
        o->p60[1] = sub_00062080(c->c28, c->t60);
        o->p60[2] = sub_00062080(c->c44, c->t60);
    }
}
