/* Area m3, batch 39. Names inferred. */
#include <stdint.h>

typedef struct M3WkSt39 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[0x10]; float v18[2]; int f20; } M3WkSt39;
typedef struct M3WkO39 { uint8_t unk00[0x22]; uint8_t b22; uint8_t unk23[0x35]; int st58; uint8_t unk5C[0xC]; float f68; uint8_t unk6C[8]; float t74;
                         uint8_t unk78[0x200]; M3WkSt39 *st278; } M3WkO39;
typedef struct M3WkA39 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x1C]; void *p30; } M3WkA39;
extern float a50_frameUnits, a50_frameSeconds;
int  sub_000833E0(void *p);
void sub_00113040(void *o, void *h, int next);
void sub_00113090(void *a, void *o, int s);
void b10_AddClampF(float *v, int add, int max);

/* 0x13F880: AI wake step: state 0 waits for its timer to run out, then enters state 0x35/0x36 (by flag bit) and ramps its glow; state 1 waits 45 frames' worth of height while dazed (then sets the next timer to 216 or 288 frames and goes to 0x1A), or waits for its anim to end and goes to 0x28 (0xC with flag bit). */
void m3_AiWake13F880(M3WkA39 *a, M3WkO39 *o) {
    M3WkSt39 *st = o->st278;
    float lim, t;
    volatile int k;
    switch (o->st58) {
    case 0:
        if (0.0f >= o->t74) {
            sub_00113090(a, o, (o->b22 & 1) + 0x35);
            b10_AddClampF(st->v18, 0x40A00000, 0x437F0000);
            o->st58++;
        }
        return;
    case 1:
        if (st->f4 & 0x40000000) {
            lim = 45.0f / a50_frameUnits * a50_frameSeconds;
            if (!(o->f68 >= lim)) return;
            st->f4 &= ~0x40000000u;
            k = 0x1A;
            t = (st->f20 >= 7) ? 288.0f : 216.0f;
            o->t74 = t / a50_frameUnits * a50_frameSeconds;
        } else {
            if (!sub_000833E0(a->p30)) return;
            k = (-(int)(o->b22 & 1) & -0x1C) + 0x28;
        }
        a->f10 &= ~0x20u;
        sub_00113040(a, o, k);
        return;
    }
}

#include <math.h>
typedef struct M3Wk2B39 { uint8_t unk00[0x20]; uint16_t f20; uint8_t b22; uint8_t unk23[0x35]; int st58; uint8_t unk5C[0xC]; float f68; uint8_t unk6C[8]; float t74;
                          uint8_t unk78[0x84]; float fFC; uint8_t unk100[0x178]; M3WkSt39 *st278; } M3Wk2B39;
int  sub_001C7EE1(void);
void b10_SubClampF(float *v, int sub, int min);

/* 0x13F6D0: heavier AI wake step: state 0 waits out its timer, then enters state 0x31/0x32 (0x33/0x34 when the sign flag is set) and drops its glow by 10 (30); state 1 leaves the daze after 72 frames of height (or 56 without the sign flag) with a 144/216 frame timer, or when its anim ends goes to 0x28, 0xC (60 frame timer or none) or rarely 0x27 when facing within 40 degrees. */
void m3_AiWake13F6D0(M3WkA39 *a, M3Wk2B39 *o) {
    M3WkSt39 *st = o->st278;
    float t, tt;
    volatile int k;
    volatile int s;
    volatile int g;
    switch (o->st58) {
    case 0:
        if (0.0f >= o->t74) {
            s = (o->b22 & 1) + 0x31;
            g = 0x41200000;
            if ((int32_t)st->f4 < 0) {
                s += 2;
                g = 0x41F00000;
            }
            b10_SubClampF(st->v18, g, 0);
            sub_00113090(a, o, s);
            o->st58++;
        }
        return;
    case 1:
        if (st->f4 & 0x40000000) {
            t = 1.0f / a50_frameUnits;
            if (!(o->f68 >= t * 72.0f * a50_frameSeconds)) {
                if (!(o->f68 >= t * 56.0f * a50_frameSeconds)) return;
                if ((int32_t)st->f4 < 0) return;
            }
            st->f4 &= ~0x40000000u;
            k = 0x1A;
            tt = (st->f20 >= 8) ? 216.0f : 144.0f;
            goto timer;
        }
        if (!sub_000833E0(a->p30)) return;
        if (!(*(uint32_t *)&o->f20 & 0x10000)) {
            k = 0x28;
            goto call;
        }
        if (st->f4 & 0x10) goto zero;
        if (!(*(uint32_t *)&o->f20 & 1)) {
            tt = 60.0f;
            k = 0xC;
            goto timer;
        }
        if (!((double)0.69813172f >= fabs(o->fFC))) goto zero;
        if (sub_001C7EE1() % 4 >= 1) goto zero;
        k = 0x27;
        goto call;
zero:
        o->t74 = 0.0f;
        k = 0xC;
        goto call;
timer:
        o->t74 = tt / a50_frameUnits * a50_frameSeconds;
call:
        a->f10 &= ~0x20u;
        sub_00113040(a, o, k);
        return;
    }
}

typedef struct M3PC39 { uint32_t f0; float f4, f8; int fC, f10; float f14; float v18[4]; float v28[4]; float s38[4]; float z48[4]; void *p58; } M3PC39;
extern M3PC39 m3_fxPool41CD40[4];

/* 0xC93D0: reset all 4 records of the effect pool at 0x41CD40 to defaults (scale 0.01, w 1). */
void m3_FxPoolInitC93D0(void) {
    uint8_t *q;
    for (q = (uint8_t *)&m3_fxPool41CD40[0] + 8; (int32_t)q < (int32_t)((uint8_t *)&m3_fxPool41CD40[4] + 8); q += sizeof(M3PC39)) {
        uint8_t *volatile vq = q;
        M3PC39 *e = (M3PC39 *)(vq - 8);
        e->f0 = 0;
        e->f4 = 0.0f; e->f8 = 0.0f;
        e->fC = 0; e->f10 = 0;
        e->v18[2] = 0.0f; e->v18[1] = 0.0f; e->v18[0] = 0.0f;
        e->v28[2] = 0.0f; e->v28[1] = 0.0f; e->v28[0] = 0.0f;
        e->s38[3] = 0.01f; e->s38[2] = 0.01f; e->s38[1] = 0.01f; e->s38[0] = 0.01f;
        e->z48[3] = 0.0f; e->z48[2] = 0.0f; e->z48[1] = 0.0f; e->z48[0] = 0.0f;
        e->v28[3] = 1.0f; e->v18[3] = 1.0f;
        e->p58 = 0;
    }
}
