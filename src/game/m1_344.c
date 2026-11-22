/* Area m1, file 344: enemy spin-swipe sequence. Names inferred. */
#include <stdint.h>

typedef struct M1St344 { uint8_t unk00[4]; uint32_t f04; uint8_t unk08[0x1C - 8]; float f1C; uint8_t unk20[0x34 - 0x20]; void *p34[2]; void *p3C; } M1St344;
typedef struct M1Ai344 {
    uint8_t unk000[0x20]; uint8_t b20; uint8_t unk021[0x58 - 0x21]; int32_t n58; float f5C;
    uint8_t unk060[0x68 - 0x60]; float f68; uint8_t unk06C[0x278 - 0x6C]; M1St344 *s278;
} M1Ai344;
typedef struct M1Ob344 { uint8_t unk00[0x30]; void *anim30; uint8_t unk34[0x70 - 0x34]; float f70; } M1Ob344;
typedef struct M1Tm344 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1Tm344;
extern float m1_frameTime42C858, m1_frameRate42C85C;
extern float m1_g3F7504;
M1Tm344 *sub_001133E0(void *e, int k);
void     sub_00113480(void *e, int k);
int      sub_000833E0(void *a);
int      sub_0013D3F0(void *e);                        /* regargs: o=EBX */
void     sub_0018E6C0(void *fx, float k);
int      sub_00140040(int a, void *e, void *o);        /* regargs: a=EAX e=EDX, o on stack */
int      sub_001401C0(void);                           /* regargs */
int      sub_0013D380(void);                           /* regargs */
void     sub_00113090(void *o, void *e, int st);
int      sub_001C7EE1(void);                           /* rand */
int      m1_AiGoto113040(void *o, void *e, int st);

/* 0x141270: spin swipe. Step 0 waits 30 units and starts the wind-up turn (clearing the
   charge without the guard bit); step 1 waits 42 units and ends it; step 2 scales the
   swipe effect up over 30..48 units and then fires the chosen one; step 3 on the animation
   end goes to 0xA (hit check), retries the swipe (pose 6, guard bit, a free effect slot,
   fewer than 6 hits, cooldown over, half the time) or 0x2E; step 4 after 30 units continues
   or (half the time) goes to 0x1B; step 5 after 55 units ends in 0xA (no effect) or 0x14. */
void m1_AiSpinSwipe141270(M1Ob344 *o, M1Ai344 *e) {
    M1St344 *s = e->s278;
    M1Tm344 *t;
    float u;
    int k;
    switch (e->n58) {
    case 0:
        if (!(e->f5C >= 30.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        t = sub_001133E0(e, 3);
        t->f10 = 0.0f;
        t->f18 = -1.04719758f;
        t->f14 = 0.0f - m1_frameTime42C858 * 0.0349065848f;
        t->f1C = -0.0872664675f;
        if (!(e->b20 & 1))
            s->f1C = 0.0f;
        e->n58++;
        return;
    case 1:
        if (e->f5C >= 42.0f / m1_frameTime42C858 * m1_frameRate42C85C) {
            sub_00113480(e, 3);
            e->n58++;
        }
    case 2:
        u = 1.0f / m1_frameTime42C858;
        if (e->f5C >= u * 48.0f * m1_frameRate42C85C) {
            k = sub_0013D3F0(e);
            sub_0018E6C0(s->p34[k], (s->f1C + 1.0f) * o->f70);
            s->f1C = 0.0f;
            e->n58++;
            return;
        }
        sub_0018E6C0(s->p34[0], (e->f5C - u * 30.0f * m1_frameRate42C85C) / (u * 18.0f * m1_frameRate42C85C) * s->f1C + 1.0f);
        return;
    case 3:
        if (!sub_000833E0(o->anim30))
            return;
        if (sub_00140040(0, e, o)) {
            k = 0xA;
            goto go;
        }
        if ((e->b20 & 1) && (!s->p34[1] || !s->p3C) && sub_001401C0() < 6 && 0.0f >= m1_g3F7504
            && sub_001C7EE1() % 2 < 1) {
            sub_00113090(o, e, 6);
            e->n58++;
            return;
        }
        k = 0x2E;
        goto go;
    case 4:
        if (!(e->f68 >= 30.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        if (sub_0013D380() || sub_001C7EE1() % 2 >= 1) {
            e->n58++;
            return;
        }
        k = 0x1B;
        goto go;
    case 5:
        if (!(e->f68 >= 55.0f / m1_frameTime42C858 * m1_frameRate42C85C))
            return;
        if (!s->p34[0]) {
            s->f04 |= 8;
            k = 0xA;
        } else {
            k = 0x14;
        }
    go:
        s->f04 &= ~0x400000u;
        m1_AiGoto113040(o, e, k);
        return;
    }
}
