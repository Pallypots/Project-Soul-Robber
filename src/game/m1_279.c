/* Area m1, file 279: HUD sprites. Names inferred. */
#include <stdint.h>

typedef struct M1Spr279 { float x, y; uint8_t unk08[0x14]; float f1C, f20; uint8_t unk24[0x68]; uint32_t col8C;
    uint8_t unk90[0xC]; } M1Spr279;                                     /* 0x9C */
extern M1Spr279 m1_hudSpr37DAE4[2];
extern int16_t m1_hudOfs37DA9C[2];
void *sub_00017C00(void *dl, M1Spr279 *s);
void sub_00014E80(M1Spr279 *s);
void sub_00026910(void *dl, float x, float y, int32_t d, int32_t e, int32_t f, uint32_t col, float sx, float sy, int32_t j);

/* 0x00027A70: same as 0x00027B80 but draws the label in style 5: the two-layer HUD sprite at (x, y), size z,
   alpha from col, then label e offset by the anchor at 0.8 scale. */
void m1_HudSprite27A70(void *dl, float x, float y, float z, uint32_t col, int32_t e)
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
    sub_00026910(dl, (float)m1_hudOfs37DA9C[0] * s + x, (float)m1_hudOfs37DA9C[1] * s + y, 0, e, 5, col, s, s, 1);
}

typedef struct M1Sn279 { uint8_t unk00[0x44]; void *p44; } M1Sn279;
typedef struct M1Cam279 { uint8_t unk00[0x1F0]; float proj1F0[16]; float view230[16]; } M1Cam279;
typedef struct M1Pl279 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl279;
extern uint8_t m1_seqFlags37FB3C, m1_alpha37FB68;
extern int32_t m1_count37FB6C;
extern M1Sn279 *m1_scene42C8E4;
extern M1Pl279 *g_playerObj;
M1Cam279 *sub_000847F0(void *list, int32_t id);
void sub_000F5D40(float *d, const float *s);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001AE140(int32_t *scr, const float *m, const float *v, int32_t z);

/* 0x00028460: when sequence flag bit 0 is set, draw the counter 0x0037FB6C over the player's head: project a
   point 22 units above the player to the screen, centre the backing sprite on the digit count and draw the
   number at 0.64 scale with alpha 0x0037FB68. regargs: dl=EDI. */
void *m1_HeadCounter28460(void *dl)
{
    M1Cam279 *c;
    float v[4], t[4], x, y;
    int32_t scr[4], n, digits;
    if (!(m1_seqFlags37FB3C & 1)) return dl;
    c = sub_000847F0(m1_scene42C8E4->p44, 9);
    sub_000F5D40(v, g_playerObj->pos60);
    v[1] = v[1] - 22.0f;
    sub_001AD9B0(t, c->view230, v);
    sub_001AE140(scr, c->proj1F0, v, 0);
    y = (float)((scr[1] - 0x8000) >> 3) - 8.0f;
    x = (float)((scr[0] - 0x8000) >> 4);
    n = m1_count37FB6C;
    if (n != 0) {
        digits = 0;
        for (; n > 0; n = *(volatile int32_t *)&n / 10)
            digits++;
    } else {
        digits = 1;
    }
    x -= ((float)digits * 12.0f - 6.0f) * 0.8f;
    m1_hudSpr37DAE4[0].x = x;
    m1_hudSpr37DAE4[0].y = y;
    m1_hudSpr37DAE4[0].f20 = 0.8f;
    m1_hudSpr37DAE4[0].f1C = 0.8f;
    m1_hudSpr37DAE4[0].col8C = ((uint32_t)m1_alpha37FB68 << 24) + 0x808080;
    dl = sub_00017C00(dl, &m1_hudSpr37DAE4[0]);
    sub_00026910(dl, (float)m1_hudOfs37DA9C[0] * 0.8f + x, (float)m1_hudOfs37DA9C[1] * 0.8f + y, 0, m1_count37FB6C,
                 digits, ((uint32_t)m1_alpha37FB68 << 24) + 0x153F4A, 0.64f, 0.64f, 0);
    return dl;
}
