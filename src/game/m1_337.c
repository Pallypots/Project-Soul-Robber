/* Area m1, file 337: enter-attack state 0x41 (lunge facing away from the player). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct {
    uint8_t _0[4]; uint32_t f4; uint8_t _8[0x30 - 8]; float v30[4]; float v40[4];
    float f50, f54, f58, f5c, f60, f64, f68, f6c; uint8_t _70[4]; float f74, f78;
    float f7c; uint8_t _80[4]; float f84; uint8_t _88[0xB8 - 0x88]; float mb8[16]; float mf8[16]; uint8_t b138[0x40];
    int32_t f178; float f17c, f180;
} M1As337;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[0x278 - 0x50]; M1As337 *s278; } M1Aa337;
typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x20 - 0x14]; float *m20; uint8_t _24[0x60 - 0x24]; uint8_t pos60[0x10]; } M1Ao337;

extern float m1_frameTime42C858, m1_frameRate42C85C, m1_fps42C964;
extern uint8_t *g_playerObj;
int  m1_AiSetState1456E0(void *o, void *a, int st, int f);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA40(float *d, const float *m);
void sub_0011F640(int k, uint8_t *p);                       /* regargs: k=EAX p=ESI */
void sub_001AD9F0(float *d, const void *a, const void *b);  /* d = a - b */
void sub_001AD7E0(float *d, const float *s);                /* normalise */
void sub_001ADBA0(float *d, const float *s, float k);       /* d = s * k */
void sub_001ADA60(float *d, const float *a, const float *b);/* cross */

/* 0x12A400: enter state 0x41: reset the move blend, rise at 5/s with gravity -17.5, spin
   once a second (hangs if the frame rate makes that impossible), start the 0.05 s pose
   blend, then turn the model to face directly away from the player (flat) and, for models
   with flag 8, wait until the state block's 0x20 bit clears. */
void m1_EnterTurnAway12A400(M1Ao337 *o, M1Aa337 *a)
{
    M1As337 *s0 = a->s278;
    M1As337 *s;
    float x, q, y;
    float v[4];
    float *m;
    uint32_t f;

    m1_AiSetState1456E0(o, a, 0x41, 0);
    s = a->s278;
    x = m1_frameTime42C858 * (1.0f / 30.0f);
    sub_000F5D40(s->v40, s->v30);
    s->f58 = 0.0f; s->f54 = 0.0f; s->f50 = 0.0f;
    s->f5c = 1.0f;
    s->f60 = (x != 1.0f) ? 0.0f : 1.0f;
    s->f64 = x;
    s = a->s278;
    s->f68 = -17.5f;
    s->f6c = m1_frameRate42C85C * 10.0f * 0.5f;
    s->f4 |= 1;
    s = a->s278;
    q = 6.28318548f / m1_fps42C964;
    if (!(6.28318548f >= q)) for (;;) ;
    s->f78 = q;
    s->f74 = 2.5f;
    s->f4 |= 2;
    y = m1_frameTime42C858 * 0.05f;
    s = a->s278;
    s->f4 |= 4;
    sub_001ADA40(s->mf8, s->mb8);
    sub_0011F640(0x18, s->b138);
    s->f17c = 0.0f;
    s->f178 = 0x18;
    s->f180 = y;
    a->f4c &= ~0x70u;
    sub_001AD9F0(v, o->pos60, g_playerObj + 0x60);
    v[1] = 0.0f;
    sub_001AD7E0(v, v);
    sub_001ADBA0(o->m20 + 8, v, -1.0f);
    o->m20[7] = 0.0f;
    o->m20[6] = 0.0f;
    o->m20[4] = 0.0f;
    o->m20[5] = 1.0f;
    m = o->m20;
    sub_001ADA60(m, m + 4, m + 8);
    f = o->f10 & 8;
    while (f && (*(volatile uint32_t *)&s0->f4 & 0x20)) ;
}
