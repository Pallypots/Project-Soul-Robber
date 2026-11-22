/* Area m1, file 338: enter-attack state (side dash, two strengths). Names inferred. */
#include <stdint.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78;
    uint8_t _7c[0x90 - 0x7C]; float f90; uint8_t _94[0xB8 - 0x94]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180;
} M1As338;
typedef struct M1Tg338 { uint8_t unk00[4]; int32_t i04; uint8_t unk08[4]; uint8_t b0C; } M1Tg338;
typedef struct {
    uint8_t _0[0x20]; uint8_t b20; uint8_t _21[0x58 - 0x21]; int32_t st58; uint8_t _5c[0xF8 - 0x5C]; int32_t iF8;
    uint8_t _fc[0x104 - 0xFC]; M1Tg338 *p104; uint8_t _108[0x278 - 0x108]; M1As338 *s278;
} M1Aa338;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x60 - 0x14]; uint8_t pos60[0x10]; } M1Ao338;
typedef struct { uint8_t _0[0x10]; float f10, f14, f18, f1c; } M1Kc338;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
extern uint8_t *g_playerObj;
int      m1_AiSetState1456E0(void *o, void *a, int st, int f);
void     sub_000F5D40(float *d, const float *s);
void     sub_001ADA40(float *d, const float *m);
void     sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
int      sub_001C7EE1(void);                                    /* rand */
float    sub_001B2770(const void *a, const void *b);            /* distance */
M1Kc338 *m1_Quest113400(void *a, int v);

/* 0x1228F0: enter the side dash: reset the move blend, spin once in 1/6 s (hangs if the
   frame rate makes that impossible), pick the dash side at random (state bit 0x100) and the
   strong (guard bit, pose 2, blend 0xC) or weak (pose 1, blend 0xA) set; when holding a
   grabbed kind-0xD target go to step 0xA, otherwise step 0 with a 70 reach close to the
   player (clearing 0x200) or 15 (setting it). Rise at 10/s with gravity -15, start the
   pose blend and the two timed effects. */
void m1_EnterDash1228F0(M1Ao338 *o, M1Aa338 *a)
{
    M1As338 *s, *t;
    M1Kc338 *c;
    float x, q, y;
    float side, fwd, turn, reach;
    int n;
    uint32_t f;

    x = m1_frameTime42C858 * (1.0f / 30.0f);
    s = a->s278;
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    t = a->s278;
    q = 6.28318548f / (m1_fps42C964 * 6.0f);
    if (!(6.28318548f >= q)) for (;;) ;
    t->f74 = 5.0f;
    t->f78 = q;
    t->f4 |= 2;
    o->f10 |= 0x20;
    s->f4 |= 0x4000;
    if (sub_001C7EE1() & 1)
        s->f4 |= 0x100;
    else
        s->f4 &= ~0x100u;
    if (a->b20 & 1) {
        m1_AiSetState1456E0(o, a, 2, 0);
        side = m1_frameRate42C85C * 20.0f;
        fwd = m1_frameRate42C85C * 12.0f;
        turn = m1_frameTime42C858 * 0.0436332338f;
        n = 0xC;
    } else {
        m1_AiSetState1456E0(o, a, 1, 0);
        fwd = m1_frameRate42C85C * 8.0f;
        side = m1_frameRate42C85C * 15.0f;
        turn = m1_frameTime42C858 * 0.0349065848f;
        n = 0xA;
    }
    if (s->f4 & 0x100)
        n++;
    else
        side = 0.0f - side;
    if (a->iF8 == 1 && (a->p104->b0C & 1) && a->p104->i04 == 0xD) {
        reach = 15.0f;
        a->st58 = 0xA;
    } else {
        f = s->f4;
        if ((a->b20 & 1) && 35.0f > sub_001B2770(o->pos60, g_playerObj + 0x60)) {
            reach = 70.0f;
            f &= ~0x200u;
        } else {
            reach = 15.0f;
            f |= 0x200;
        }
        s->f4 = f;
        a->st58 = 0;
    }
    t = a->s278;
    t->f6c = m1_frameRate42C85C * 10.0f;
    t->f68 = -15.0f;
    t->f4 |= 1;
    t = a->s278;
    t->f4 |= 4;
    y = m1_frameTime42C858 * 0.008f;
    sub_001ADA40(t->mf8, t->mb8);
    sub_0011F640(n, t->b138);
    t->f17c = 0.0f;
    t->f178 = n;
    t->f180 = y;
    c = m1_Quest113400(a, 1);
    c->f10 = 0.0872664675f;
    c->f14 = -0.0872664675f;
    if (turn != -1.0f) c->f18 = turn;
    c->f1c = 0.0f;
    c = m1_Quest113400(a, 4);
    if (reach != -1.0f) c->f10 = reach;
    if (fwd != -1.0f) c->f14 = fwd;
    if (side != -1.0f) c->f18 = side;
    c->f1c = 0.0f;
    s->f90 = 0.0f;
}
