/* Area m1, file 256: math and HUD helpers. Names inferred. */
#include <stdint.h>

float sub_001A3F50(float x);                                   /* sqrtf */
void sub_001ADBA0(float *d, const float *s, float k);          /* d = s * k */
void sub_001ADE90(float *d, const float *a, const float *b);   /* d = a * b per component */
extern const float m1_atanLo367E74[4], m1_atanHi367E84[4];      /* odd-power series coefficients 1..15 */

/* 0x001AF2A0: arc cosine of x by an 8-term arctangent series: with r = sqrt(1 - x*x) and
   t = (x - r) / (x + r), acos(x) = pi/2 - (atan(t) + pi/4). */
float m1_Acos1AF2A0(float x)
{
    float r, t, t2, k, sum;
    float lo[4], hi[4], p[4];
    r = sub_001A3F50(1.0f - x * x);
    t = (x - r) / (x + r);
    t2 = t * t;
    lo[1] = t2 * t;
    lo[2] = lo[1] * t2;
    lo[3] = lo[2] * t2;
    k = lo[3] * t;
    lo[0] = t;
    sub_001ADBA0(hi, lo, k);
    sub_001ADE90(p, lo, m1_atanLo367E74);
    sum = p[3] + p[2] + p[1] + p[0];
    sub_001ADE90(p, hi, m1_atanHi367E84);
    return 1.5707964f - (p[3] + p[2] + p[1] + p[0] + sum + 0.78539819f);
}

typedef struct M1Spr256 { float x, y; uint8_t unk08[0x14]; float f1C, f20; uint8_t unk24[0x68]; uint32_t col8C;
    uint8_t unk90[0xC]; } M1Spr256;                                     /* 0x9C */
extern M1Spr256 m1_hudSpr37DAE4[2];
extern int16_t m1_hudOfs37DA9C[2];
void *sub_00017C00(void *dl, M1Spr256 *s);
void sub_00014E80(M1Spr256 *s);
void sub_00026910(void *dl, float x, float y, int32_t d, int32_t e, int32_t f, uint32_t col, float sx, float sy, int32_t j);

/* 0x00027B80: draw the two-layer HUD sprite at (x, y) with size z and color col (alpha kept, RGB set to grey),
   then draw label e over it, offset by the sprite's anchor and scaled to 0.8 of z. */
void m1_HudSprite27B80(void *dl, float x, float y, float z, uint32_t col, int32_t e)
{
    uint32_t c = (col & 0xFF000000u) + 0x808080;
    float s;
    m1_hudSpr37DAE4[0].x = x;
    m1_hudSpr37DAE4[1].x = x;
    m1_hudSpr37DAE4[0].col8C = c;
    m1_hudSpr37DAE4[1].col8C = c;
    m1_hudSpr37DAE4[0].y = y;
    m1_hudSpr37DAE4[1].y = y;
    m1_hudSpr37DAE4[0].f20 = z;
    m1_hudSpr37DAE4[1].f20 = z;
    m1_hudSpr37DAE4[0].f1C = z;
    m1_hudSpr37DAE4[1].f1C = z;
    dl = sub_00017C00(dl, &m1_hudSpr37DAE4[0]);
    dl = sub_00017C00(dl, &m1_hudSpr37DAE4[1]);
    sub_00014E80(&m1_hudSpr37DAE4[1]);
    s = z * 0.8f;
    sub_00026910(dl, (float)m1_hudOfs37DA9C[0] * s + x, (float)m1_hudOfs37DA9C[1] * s + y, 0, e, 7, col, s, s, 1);
}

extern uint8_t m1_seqE37F480, m1_alpha37F4B0;
extern int32_t m1_hud37FB70;
extern M1Spr256 m1_keySpr37F4B4;
extern int32_t m1_label41318C;

/* 0x00028360: when sequence flag bit 0 is set, draw the key prompt sprite (one of two screen spots chosen by
   0x0037FB70) with alpha 0x0037F4B0, then its label 8 left and 7 down from it at 0.8 scale. regargs: dl=EAX. */
void m1_KeyPrompt28360(void *dl)
{
    float x, y;
    if (!(m1_seqE37F480 & 1)) return;
    if (m1_hud37FB70 == 0) {
        x = 64.0f;
        y = -176.0f;
    } else {
        x = 28.0f;
        y = -180.0f;
    }
    m1_keySpr37F4B4.x = x;
    m1_keySpr37F4B4.y = y;
    m1_keySpr37F4B4.col8C = ((uint32_t)m1_alpha37F4B0 << 24) | 0x808080;
    dl = sub_00017C00(dl, &m1_keySpr37F4B4);
    sub_00026910(dl, x - 8.0f, y + 7.0f, 0, m1_label41318C, 3, ((uint32_t)m1_alpha37F4B0 << 24) | 0x1E285C,
                 0.8f, 0.8f, 1);
}

