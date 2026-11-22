/* Area m1, file 341: enter-attack state (charge or close swipe). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78, f7c;
    uint8_t _80[0xB8 - 0x80]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180;
} M1As341;
typedef struct M1Tg341 { uint8_t unk00[4]; int32_t i04; int32_t i08; uint8_t b0C; } M1Tg341;
typedef struct {
    uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0xF8 - 0x5C]; int32_t iF8;
    uint8_t _fc[0x104 - 0xFC]; M1Tg341 *p104; uint8_t _108[0x278 - 0x108]; M1As341 *s278;
} M1Aa341;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10]; } M1Ao341;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Kc341;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
extern uint8_t *g_playerObj;
int      m1_AiSetState1456E0(void *o, void *a, int st, int f);
void     sub_000F5D40(float *d, const float *s);
void     sub_001ADA40(float *d, const float *m);
void     sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
float    sub_001B2770(const void *a, const void *b);            /* distance */
M1Kc341 *m1_Quest113400(void *a, int v);
void     sub_00147710(void *e, int k, float a, int b, float c, int d);   /* regargs: e=ECX k=EAX */

/* 0x124940: far from the player (beyond 40) and not holding a grabbed kind-0xD target:
   enter the charge (pose 0x27: rise at 10/s, gravity -10, slow spin, blend 0x10, +30 to
   the 0..200 rage meter, the 4-unit lunge effect). Otherwise the close swipe (pose 0x26,
   blend 0xF, +50 rage); when holding a grabbed kind-1 target with fewer than 3 hits use the
   throw follow-up, else a heavier rise with the lunge effect; step 0xA. Both flag the
   model and start the timed sway effect. */
void m1_EnterCharge124940(M1Ao341 *o, M1Aa341 *a)
{
    M1As341 *s0 = a->s278;
    M1As341 *s;
    M1Kc341 *c;
    float x, q, y, v, z;

    if (!(40.0f >= sub_001B2770(o->pos60, g_playerObj + 0x60)) &&
        !(a->iF8 == 1 && (a->p104->b0C & 1) && a->p104->i04 == 0xD)) {
        m1_AiSetState1456E0(o, a, 0x27, 0);
        s = a->s278;
        x = m1_frameTime42C858 * 0.125f;
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
        s->f5c = 1.0f;
        s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
        s->f64 = x;
        s = a->s278;
        s->f6c = m1_frameRate42C85C * 10.0f;
        s->f4 |= 1;
        s->f68 = -10.0f;
        s = a->s278;
        q = 6.28318548f / (m1_fps42C964 * 4.0f);
        if (!(6.28318548f >= q)) for (;;) ;
        s->f78 = q;
        s->f74 = 2.5f;
        s->f4 |= 2;
        s = a->s278;
        s->f4 |= 4;
        y = m1_frameTime42C858 * 0.125f;
        sub_001ADA40(s->mf8, s->mb8);
        sub_0011F640(0x10, s->b138);
        s->f180 = y;
        s->f178 = 0x10;
        s->f17c = 0.0f;
        s = a->s278;
        v = s->f7c + 30.0f;
        s->f7c = v;
        if (0.0f > v)
            s->f7c = 0.0f;
        else if (v > 200.0f)
            s->f7c = 200.0f;
        c = m1_Quest113400(a, 2);
        c->f10 = 4.0f;
        c->f14 = 0.0f;
        c->f18 = 1.0f;
        c->f1c = 0.0f;
    } else {
        m1_AiSetState1456E0(o, a, 0x26, 0);
        s = a->s278;
        x = m1_frameTime42C858 * (1.0f / 30.0f);
        sub_000F5D40(s->v40, s->v30);
        s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
        s->f5c = 1.0f;
        s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
        s->f64 = x;
        s = a->s278;
        q = 6.28318548f / (m1_fps42C964 * 4.0f);
        if (!(6.28318548f >= q)) for (;;) ;
        s->f78 = q;
        s->f74 = 2.5f;
        s->f4 |= 2;
        s = a->s278;
        s->f4 |= 4;
        y = m1_frameTime42C858 * 0.03125f;
        sub_001ADA40(s->mf8, s->mb8);
        sub_0011F640(0xF, s->b138);
        s->f180 = y;
        s->f178 = 0xF;
        s->f17c = 0.0f;
        s = a->s278;
        v = s->f7c + 50.0f;
        s->f7c = v;
        if (0.0f > v)
            s->f7c = 0.0f;
        else if (v > 200.0f)
            s->f7c = 200.0f;
        if (a->iF8 == 1 && (a->p104->b0C & 1) && a->p104->i04 == 1 && a->p104->i08 < 3) {
            s = a->s278;
            s->f4 |= 1;
            s->f68 = -10.0f;
            s->f6c = m1_frameRate42C85C * 10.0f;
            sub_00147710(a, 2, 3.0f, 0, 1.0f, 0);
        } else {
            s = a->s278;
            s->f4 |= 1;
            s->f68 = -4.0f;
            s->f6c = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(m1_frameRate42C85C * 10.0f), _mm_set_ss(2.0f)));
            c = m1_Quest113400(a, 2);
            c->f10 = 4.0f;
            c->f14 = 0.0f;
            c->f18 = 1.0f;
            c->f1c = 1.0f;
        }
        a->st58 = 0xA;
    }
    o->f10 |= 0x20;
    s0->f4 |= 0x10800;
    z = m1_frameTime42C858 * 0.0523598790f;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.174532935f;
    c->f14 = -0.174532935f;
    if (z != -1.0f) c->f18 = z;
    c->f1c = 0.0f;
}
