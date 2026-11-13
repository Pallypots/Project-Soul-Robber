/* Area m1, file 48: scripted-actor steps and screen timers. Names inferred. */
#include <stdint.h>

typedef struct M1Cam10 { uint8_t unk00[0x10]; uint32_t flags10; } M1Cam10;
typedef struct M1Scr1A8 {
    uint8_t unk000[0x8C];
    M1Cam10 *cam8C;            /* +0x8C */
    uint8_t unk090[0x98 - 0x90];
    int32_t f98;               /* +0x98 */
    uint8_t unk09C[0x138 - 0x9C];
    int32_t f138, f13C;        /* +0x138 */
    uint8_t unk140[0x18C - 0x140];
    int32_t f18C, f190;        /* +0x18C */
    uint8_t unk194[0x1A8 - 0x194];
    int16_t w1A8;              /* +0x1A8 */
    uint8_t unk1AA[2];
    float   f1AC;              /* +0x1AC */
    float   f1B0;              /* +0x1B0 */
    uint8_t unk1B4[0x1C8 - 0x1B4];
    int32_t f1C8;              /* +0x1C8 */
    uint8_t unk1CC[0x1E4 - 0x1CC];
    float   f1E4;              /* +0x1E4 */
    uint8_t unk1E8[0x210 - 0x1E8];
    int32_t f210;              /* +0x210 */
} M1Scr1A8;
extern M1Scr1A8 *m1_scr3F6130;
int  aab_Rand(void);
void sub_00101280(int v);

/* 0x001032A0: screen state reset: +0x1E4 = 0, +0x1A8 = 0, +0x1AC = 2.0 + (rand % 51) * 0.1,
 * 0x101280(3), +0x1C8 = 0. */
void m1_ScrReset1032A0(void)
{
    M1Scr1A8 *s = m1_scr3F6130;
    s->f1E4 = 0.0f;
    s->w1A8 = 0;
    s->f1AC = (float)(aab_Rand() % 51) * 0.1f + 2.0f;
    sub_00101280(3);
    s->f1C8 = 0;
}

typedef struct M1Act30 { uint8_t unk00[0x30]; int32_t f30; uint8_t unk34[0x60 - 0x34]; float pos60[3]; } M1Act30;
typedef struct M1Step58 {
    uint8_t unk00[0x58];
    int32_t state58;           /* +0x58 */
    uint8_t unk5C[0x6C - 0x5C];
    int32_t snd6C;             /* +0x6C */
    int32_t f70;               /* +0x70 */
} M1Step58;
int  sub_000833E0(int v);
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_0001D4E0(void *o);
int  sub_000494D0(int id, const void *pos, int c);
int  sub_00036750(void *o, int v);

/* 0x001173F0: two-step script: state 0 waits for 0x833E0(o +0x30); state 1 runs
 * 0x1456E0(0x14), on 1 calls 0x1D4E0, then starts sound 0x174 and 0x36750(2), state 0x63. */
void m1_Step1173F0(M1Act30 *o, M1Step58 *s)
{
    switch (s->state58) {
    case 0:
        if (sub_000833E0(o->f30) != 0)
            s->state58++;
        break;
    case 1:
        if (sub_001456E0(o, s, 0x14, 0) == 1)
            sub_0001D4E0(o);
        s->snd6C = sub_000494D0(0x174, o->pos60, 0);
        s->f70 = sub_00036750(o, 2);
        s->state58 = 0x63;
        break;
    }
}

void sub_0001EEC0(void *cam, float v);
void sub_0001EF00(void *cam, const float *v);

/* 0x00102310: camera hold on: +0x98 = 0, camera flag 4, +0x1B0 = 4.2, camera speed 4.2,
 * camera offset zero, then copy +0x13C -> +0x138 and +0x190 -> +0x18C. */
void m1_CamHold102310(void)
{
    M1Scr1A8 *s = m1_scr3F6130;
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    s->f98 = 0;
    s->cam8C->flags10 |= 4;
    s->f1B0 = 4.2f;
    sub_0001EEC0(s->cam8C, 4.2f);
    sub_0001EF00(s->cam8C, v);
    s->f138 = s->f13C;
    s->f18C = s->f190;
}

/* 0x001036E0: camera hold off: +0x210 = 0, +0x1A8 = 0, +0x1B0 = 4.2, speed 4.2 on cam,
 * camera offset zero, +0x98 = 1, clear camera flag 4. */
void m1_CamRelease1036E0(void *cam)
{
    M1Scr1A8 *s = m1_scr3F6130;
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    s->f210 = 0;
    s->w1A8 = 0;
    s->f1B0 = 4.2f;
    sub_0001EEC0(cam, 4.2f);
    sub_0001EF00(s->cam8C, v);
    m1_scr3F6130->f98 = 1;
    s->cam8C->flags10 &= ~4u;
}

typedef struct M1Ctl9C { uint8_t unk00[0x94]; int32_t f94; uint8_t unk98[4]; int32_t step9C; float tA0; } M1Ctl9C;
extern M1Ctl9C *m1_ctl3F6128;
extern float m1_frameRate42C85C;
int  sub_000F5D00(void *o);
void sub_0001D700(int v);
void sub_000F3D10(void *o, void *c, int mode);

/* 0x001009E0: controller step: at step 0 waits for 0xF5D00(o), then 0x1D700(+0x94),
 * timer 0 and step 1; later counts the timer up by the frame rate and switches c to
 * mode 9 once it passes 0.2. */
void m1_CtlStep1009E0(void *o, void *c)
{
    M1Ctl9C *g = m1_ctl3F6128;
    if (g->step9C == 0) {
        if (sub_000F5D00(o) != 0) {
            sub_0001D700(g->f94);
            g->tA0 = 0.0f;
            g->step9C++;
        }
        return;
    }
    if (g->tA0 > 0.2f)
        sub_000F3D10(o, c, 9);
    else
        g->tA0 += m1_frameRate42C85C;
}
