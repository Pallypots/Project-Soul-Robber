/* Area m1, file 134: small helpers. Names inferred. */
#include <stdint.h>

void sub_000F5D40(float *d, const float *s);

/* 0x00082750: sort two vectors component-wise: b becomes the minimum and a the maximum of
 * the pair. */
void m1_MinMax082750(float *a, float *b)
{
    float lo[4];
    float hi[4];
    sub_000F5D40(lo, b);
    if (lo[0] > a[0])
        lo[0] = a[0];
    if (lo[1] > a[1])
        lo[1] = a[1];
    if (lo[2] > a[2])
        lo[2] = a[2];
    if (lo[3] > a[3])
        lo[3] = a[3];
    sub_000F5D40(hi, a);
    if (b[0] > hi[0])
        hi[0] = b[0];
    if (b[1] > hi[1])
        hi[1] = b[1];
    if (b[2] > hi[2])
        hi[2] = b[2];
    if (b[3] > hi[3])
        hi[3] = b[3];
    sub_000F5D40(b, lo);
    sub_000F5D40(a, hi);
}

typedef struct M1Node134 { uint8_t unk00[0x40]; float m40[16]; uint8_t unk80[0x90 - 0x80]; uint32_t flags90; } M1Node134;
typedef struct M1CamO134 { uint8_t unk00[0x10]; uint32_t flags10; } M1CamO134;
typedef struct M1Cam134 {
    uint8_t unk000[0x8C];
    M1CamO134 *obj8C;          /* +0x8C */
    uint8_t unk090[0xB8 - 0x90];
    M1Node134 *a0B8;           /* +0xB8 */
    M1Node134 *b0BC;           /* +0xBC */
    float   mC0[16];           /* +0xC0 */
    int32_t i100;              /* +0x100 */
    uint8_t unk104[0x108 - 0x104];
    int32_t i108;              /* +0x108 */
    uint8_t unk10C[0x118 - 0x10C];
    float   ang118, spd11C;    /* +0x118 */
    uint8_t unk120[0x128 - 0x120];
    int32_t snd128;            /* +0x128 */
} M1Cam134;
extern M1Cam134 *m1_cam3F610C;
extern void *m1_camH3F6110;
extern float m1_fps42C964;
extern uint8_t m1_stats41FEC0[];
extern float m1_camPos2787D8[4];
extern float m1_camAt318DC8[4];
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *s, float a);
void sub_001AD7C0(float *d, const float *a, const float *b);
void sub_000F3D10(void *o, void *c, int mode);
void sub_000D1CA0(void *s, const float *v);
void sub_000CF330(void *s, const float *v, float k);
void sub_00033B30(void *o);
void sub_00180A60(void);
void sub_00181DA0(void);
void sub_001827A0(void);
void m1_SceneReset17D6A0(void);
void sub_00048250(int h);

/* 0x000F4730: camera swing: node B = node A times the rig matrix, pitched by the swing angle,
 * which accelerates by 0.42 per second until it passes 0; then hide node B's flag 0x40, mark
 * done and switch the camera to mode 0 (hangs without the camera object or controller). */
void m1_CamSwing0F4730(void)
{
    M1Cam134 *g = m1_cam3F610C;
    M1Node134 *a = g->a0B8;
    M1Node134 *b = g->b0BC;
    M1CamO134 *c;
    float m[16];
    sub_001AD940(m);
    sub_001AD8B0(m, m, g->ang118);
    sub_001AD7C0(b->m40, a->m40, g->mC0);
    sub_001AD7C0(b->m40, b->m40, m);
    g->ang118 += g->spd11C;
    g->spd11C = 0.418879032f / m1_fps42C964 + g->spd11C;
    if (!(g->ang118 >= 0.0f))
        return;
    g->b0BC->flags90 &= ~0x40u;
    g->i100 = 1;
    c = m1_cam3F610C->obj8C;
    if (c == 0)
        for (;;) ;
    if (m1_camH3F6110 == 0)
        for (;;) ;
    sub_000F3D10(c, m1_camH3F6110, 0);
}

/* 0x000F4CA0: leave the camera sequence: put the player at 0x2787D8 facing 0x318DC8, unhide
 * the rig, flag the camera object, switch the camera to mode 1 (hangs without the camera
 * object or controller), release it, reset the scene helpers and stop the camera sound. */
void m1_CamLeave0F4CA0(void)
{
    M1Cam134 *g = m1_cam3F610C;
    M1CamO134 *c;
    float p[4];
    sub_000F5D40(p, m1_camPos2787D8);
    sub_000D1CA0(m1_stats41FEC0, p);
    sub_000CF330(m1_stats41FEC0, m1_camAt318DC8, 1.0f);
    g->b0BC->flags90 &= ~0x40u;
    g->obj8C->flags10 |= 0x40;
    g->i108 = 0;
    g->i100 = 1;
    c = m1_cam3F610C->obj8C;
    if (c == 0)
        for (;;) ;
    if (m1_camH3F6110 == 0)
        for (;;) ;
    sub_000F3D10(c, m1_camH3F6110, 1);
    sub_00033B30(g->obj8C);
    g = m1_cam3F610C;
    sub_00180A60();
    sub_00181DA0();
    sub_001827A0();
    m1_SceneReset17D6A0();
    if (g->snd128 != -1) {
        sub_00048250(g->snd128);
        g->snd128 = -1;
    }
}
