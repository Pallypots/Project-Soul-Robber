/* Area m1, file 280: facing checks. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Pl280 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl280;
typedef struct M1Qs280 { uint8_t unk00[8]; int32_t quad8; uint8_t unkC[4]; float t10; uint8_t unk14[0xC]; float limit20; } M1Qs280;
typedef struct M1Qa280 { uint8_t unk00[0x278]; M1Qs280 *s278; } M1Qa280;
typedef struct M1Gm280 { uint8_t unk00[0x324]; int32_t mode324; } M1Gm280;
extern M1Pl280 *g_playerObj;
extern float m1_frameRate42C85C;
void sub_000F5D40(float *d, const float *s);
float sub_001A3EC0(float y, float x);                          /* atan2 */
M1Gm280 *sub_000E0770(void);
void m1_AiGoto113040(void *o, M1Qa280 *a, int32_t st);
void sub_00180970(void);                                      /* uses the caller's registers */

/* 0x001812F0: guard step: when the player's bearing (0..2pi) lies outside a's quarter (quarter 1 only reacts
   at 3pi/2 and above) and the game is not in mode 4, switch to AI state 3. Then run the timer: past the limit
   hand over to 0x00180970, otherwise count up. */
void m1_GuardQuarter1812F0(void *o, M1Qa280 *a)
{
    M1Qs280 *s = a->s278;
    int32_t hit = 0, k;
    float v[4], b, hi;
    sub_000F5D40(v, g_playerObj->pos60);
    b = sub_001A3EC0(v[2], v[0]);
    if (0.0f > b) b += 6.2831855f;
    k = s->quad8;
    if (k == 0) {
        if (!_mm_comige_ss(_mm_set_ss(b), _mm_set_ss(0.0f))) goto done;
        hi = 1.5707964f;
    } else if (k == 1) {
        if (!_mm_comige_ss(_mm_set_ss(b), _mm_set_ss(4.712389f))) goto done;
        goto set;
    } else if (k == 2) {
        if (!_mm_comige_ss(_mm_set_ss(b), _mm_set_ss(3.1415927f))) goto done;
        hi = 4.712389f;
    } else if (k == 3) {
        if (!_mm_comige_ss(_mm_set_ss(b), _mm_set_ss(1.5707964f))) goto done;
        hi = 3.1415927f;
    } else {
        goto done;
    }
    if (!(hi > b)) goto done;
set:
    hit = 1;
done:
    if (sub_000E0770()->mode324 != 4 && hit)
        m1_AiGoto113040(o, a, 3);
    if (s->t10 > s->limit20) {
        sub_00180970();
        return;
    }
    s->t10 += m1_frameRate42C85C;
}

typedef struct M1Quad280 { float uv0[4]; float uv1[4]; uint32_t col[4]; int32_t tex30; int32_t z34; } M1Quad280;
typedef struct M1Spr280 { float x, y; uint8_t unk08[0x94]; } M1Spr280;
extern int32_t m1_bgTex3E4748;
extern float m1_timer3E4768;
extern M1Spr280 m1_timerSpr3E4A80;
void *sub_00072420(void *dl, M1Quad280 *q);
void sub_000150B0(M1Spr280 *s, int32_t frame);
void *sub_00017AE0(void *dl, M1Spr280 *s);

/* 0x00058C10: draw the 512x448 backdrop (texture 0x003E4748, mid grey), then the timer panel: frame 0 at
   (0, -28) and the digit frame for the seconds left (1 - (t + 59) / 60) at (0, 83). Returns the display list.
   regargs: dl=EDX. */
void *m1_TimerScreen58C10(void *dl)
{
    M1Quad280 q;
    q.tex30 = m1_bgTex3E4748;
    q.z34 = 0;
    q.uv0[0] = 0.0f;
    q.uv0[2] = 512.0f;
    q.uv0[1] = 0.0f;
    q.uv0[3] = 448.0f;
    q.uv1[0] = 0.0f;
    q.uv1[1] = 0.0f;
    q.uv1[2] = 512.0f;
    q.uv1[3] = 448.0f;
    q.col[3] = 0x80808080;
    q.col[2] = 0x80808080;
    q.col[1] = 0x80808080;
    q.col[0] = 0x80808080;
    dl = sub_00072420(dl, &q);
    m1_timerSpr3E4A80.x = 0.0f;
    m1_timerSpr3E4A80.y = -28.0f;
    sub_000150B0(&m1_timerSpr3E4A80, 0);
    dl = sub_00017AE0(dl, &m1_timerSpr3E4A80);
    m1_timerSpr3E4A80.x = 0.0f;
    m1_timerSpr3E4A80.y = 83.0f;
    sub_000150B0(&m1_timerSpr3E4A80, 1 - _mm_cvttss_si32(_mm_set_ss((m1_timer3E4768 + 59.0f) * -0.016666668f)));
    return sub_00017AE0(dl, &m1_timerSpr3E4A80);
}
