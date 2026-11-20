/* Area m1, file 270: facing checks. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Pl270 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl270;
typedef struct M1Q270 { uint8_t unk00[8]; int32_t quad8; int16_t hitC; uint8_t unkE[0x16]; float f24[4]; } M1Q270;
extern uint32_t m1_level413178;
extern const float m1_spinTbl27A88C[3];      /* 2.0, 3.2, 4.1 */
extern float m1_fps42C964;
extern M1Pl270 *g_playerObj;
void sub_001809B0(float *v, float speed);
void sub_000F5D40(float *d, const float *s);
float sub_001A3EC0(float y, float x);                          /* atan2 */

/* 0x00180E00: spin q at the difficulty's speed, then flag a hit (hitC = 1) when the player's bearing
   (0..2pi) is outside q's quarter (quarter 1 only flags when the bearing is below 3pi/2). regargs: q=EDI. */
void m1_QuarterCheck180E00(M1Q270 *q)
{
    uint32_t lv = m1_level413178;
    int32_t k;
    float v[4], a, hi;
    if (lv > 2) lv = 2;
    sub_001809B0(q->f24, m1_spinTbl27A88C[lv] * 10.0f / m1_fps42C964);
    k = q->quad8;
    sub_000F5D40(v, g_playerObj->pos60);
    a = sub_001A3EC0(v[2], v[0]);
    if (0.0f > a) a += 6.2831855f;
    if (k == 0) {
        if (a < 0.0f) goto hit;
        hi = 1.5707964f;
    } else if (k == 1) {
        if (a >= 4.712389f) return;
        q->hitC = (int16_t)k;
        return;
    } else if (k == 2) {
        if (a < 3.1415927f) goto hit;
        hi = 4.712389f;
    } else if (k == 3) {
        if (a < 1.5707964f) goto hit;
        hi = 3.1415927f;
    } else {
        return;
    }
    if (hi > a) return;
hit:
    q->hitC = 1;
}

typedef struct M1Sb270 { uint8_t unk00[0x10]; uint32_t flags10; } M1Sb270;
typedef struct M1Sa270 { uint8_t unk00[0x4C]; uint8_t b4C; uint8_t unk4D[3]; int32_t st50; int32_t k54; float t58;
    uint8_t unk5C[0x14]; float t70; } M1Sa270;
void sub_00170E40(M1Sa270 *s, M1Sb270 *o);                  /* regargs: s=EAX o=EDI */
void sub_000EE850(M1Sb270 *o, float scale);

/* 0x00171070: grow-in / pop sequence. A flagged actor whose timer has run out restarts at state 2. Each step
   grows o's scale from 1 by 20x the step time until 0.05 s: step 0 then finishes, step 1 advances, and step 2
   (after 0.53 s) clears o's flag 4 and finishes. Finishing sets state 1. */
void m1_GrowPop171070(M1Sb270 *o, M1Sa270 *s)
{
    if ((s->b4C & 1) && _mm_comige_ss(_mm_set_ss(0.0f), _mm_load_ss(&s->t70))) {
        s->st50 = 2;
        s->k54 = 0;
        s->t58 = 0.0f;
    }
    sub_00170E40(s, o);
    switch (s->k54) {
    case 0:
        if (!_mm_comige_ss(_mm_load_ss(&s->t58), _mm_set_ss(0.05f))) goto grow;
        sub_000EE850(o, 1.0f);
        goto finish;
    case 1:
        if (!_mm_comige_ss(_mm_load_ss(&s->t58), _mm_set_ss(0.05f))) goto grow;
        sub_000EE850(o, 1.0f);
        s->k54++;
        return;
    case 2:
        if (!_mm_comige_ss(_mm_load_ss(&s->t58), _mm_set_ss(0.53333336f))) return;
        o->flags10 &= ~4u;
        goto finish;
    }
    return;
grow:
    sub_000EE850(o, s->t58 * 20.0f + 1.0f);
    return;
finish:
    s->st50 = 1;
    s->k54 = 0;
    s->t58 = 0.0f;
}
