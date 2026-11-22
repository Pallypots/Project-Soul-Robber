/* Area m1, file 342: enemy charged attack sequence. Names inferred. */
#include <stdint.h>

typedef struct M1St342 { uint8_t unk00[4]; uint32_t f04; uint8_t unk08[0x18 - 8]; float f18; } M1St342;
typedef struct M1Ai342 {
    uint8_t unk000[0x20]; uint8_t b20; uint8_t unk021[0x4C - 0x21]; uint32_t f4C; uint8_t unk050[0x58 - 0x50];
    int32_t n58; float f5C; uint8_t unk060[0x74 - 0x60]; float f74; uint8_t unk078[0x278 - 0x78]; M1St342 *s278;
} M1Ai342;
typedef struct M1Ob342 { uint8_t unk00[0x30]; void *anim30; } M1Ob342;
typedef struct M1Tm342 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Tm342;
extern float m1_frameTime42C858, m1_frameRate42C85C;
extern float m1_g3F7504;
M1Tm342 *sub_001133E0(void *e, int k);
void     sub_00113480(void *e, int k);
void     sub_00113C60(float *v, float a, float b);
int      sub_000833E0(void *a);
int      sub_00140040(void *o, void *e);          /* regargs: e=EDX */
int      sub_00140170(void *o, void *e);          /* regargs: o=ESI e=EDI */
int      m1_AiGoto113040(void *o, void *e, int st);

/* 0x141050: charged attack. Step 0 waits 17 units and starts the wind-up turn; step 1 waits
   30 units and ends it, then (step 2) while flagged pulses the glow and after 112 units
   moves on; step 3, when the animation ends, picks the follow-up (a flagged hit gives 0x27,
   0xC with a 150 timer or 0x12; else 0x29 with the guard bit or 0xC with a 90 timer below
   120 on +0x18) and clears the charge flags. */
void m1_AiCharged141050(M1Ob342 *o, M1Ai342 *e) {
    M1St342 *s = e->s278;
    M1Tm342 *t;
    float x;
    int k;
    switch (e->n58) {
    case 0:
        if (!(e->f5C >= 17.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        t = sub_001133E0(e, 3);
        t->f10 = 0.0f;
        t->f14 = 0.0f - m1_frameTime42C858 * 0.0349065848f;
        t->f18 = -1.04719758f;
        t->f1C = -0.0872664675f;
        e->n58++;
        return;
    case 1:
        if (e->f5C >= 30.0f / m1_frameTime42C858 * m1_frameRate42C85C) {
            sub_00113480(e, 3);
            e->n58++;
        }
    case 2:
        if (e->f4C & 0x100)
            sub_00113C60(&s->f18, 30.0f, 255.0f);
        if (!(e->f5C >= 112.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        e->n58++;
        return;
    case 3:
        if (!sub_000833E0(o->anim30))
            return;
        if (e->f4C & 0x100) {
            e->f4C &= ~0x100u;
            m1_g3F7504 = 240.0f / m1_frameTime42C858 * m1_frameRate42C85C;
            if ((e->b20 & 1) && sub_00140040(o, e)) {
                k = 0x27;
                goto go;
            }
            if (sub_00140170(o, e)) {
                x = 150.0f;
                k = 0xC;
                goto timer;
            }
            k = 0x12;
            goto go;
        }
        if (e->b20 & 1) {
            k = 0x29;
            goto go;
        }
        k = 0xC;
        if (s->f18 >= 120.0f) {
            e->f74 = 0.0f;
            goto go;
        }
        x = 90.0f;
    timer:
        e->f74 = x / m1_frameTime42C858 * m1_frameRate42C85C;
    go:
        sub_00113480(e, 2);
        e->f4C |= 0x10;
        s->f04 &= 0xFFBFFFFBu;
        m1_AiGoto113040(o, e, k);
        return;
    }
}
