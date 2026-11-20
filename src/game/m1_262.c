/* Area m1, file 262: draw record setup. Names inferred. */
#include <stdint.h>

typedef struct M1Src262 { uint8_t unk00[0x1C]; uint32_t n1C; uint32_t v20[4]; } M1Src262;
typedef struct M1Dr262 { uint32_t v0[4]; uint16_t w10, w12; M1Src262 *s14; int32_t f18; uint16_t w1C; uint8_t unk1E[0xA];
    int32_t f28, f2C; uint64_t q30; int32_t f38, f3C, f40, f44, f48, f4C; } M1Dr262;

/* 0x001B9460: initialise draw record d from source s: copy s's four header words, set the default counts and
   GS register values, and put s's context count (low 3 bits) into bits 2-4 of the 64-bit word at 0x30.
   regargs: d=EAX, s=ECX. */
void m1_DrawInit1B9460(M1Dr262 *d, M1Src262 *s)
{
    uint32_t z = 0;
    d->s14 = s;
    d->v0[0] = s->v20[0];
    d->v0[1] = s->v20[1];
    d->v0[2] = s->v20[2];
    d->v0[3] = s->v20[3];
    d->w1C = 0;
    d->f18 = 1;
    *(volatile uint16_t *)&d->w12 = 0;
    d->w10 = 1;
    d->f28 = 0x4000;
    d->f2C = 4;
    if (s->n1C < 1)
        d->q30 = 0x0000FFB800000060ull;
    else
        d->q30 = 0x0000FFB800000160ull;
    if (s->n1C > *(volatile uint32_t *)&z)
        d->q30 = (*(volatile uint64_t *)&d->q30 & ~0x1Cull) | ((uint64_t)(s->n1C & 7) << 2);
    d->f48 = 0;
    d->f4C = 0;
    d->f38 = 0x4000;
    d->f3C = 0x400004;
    d->f40 = 0x4000;
    d->f44 = 0x400004;
}

typedef struct M1Ta262 { int32_t f0; uint8_t unk04[4]; float t8; int32_t stC; float delay10, dur14, f18, f1C; } M1Ta262;
typedef struct M1Tb262 { uint8_t unk00[0x5C]; float f5C; } M1Tb262;
int32_t sub_00145730(float t, int32_t n);
void sub_0011FCC0(M1Tb262 *a, void *o, int32_t k);        /* regargs: a=EAX o=ECX k=EDI */
void sub_00113370(M1Tb262 *a, M1Ta262 *s);

/* 0x0012CF00: timed action. Step 0 waits for the actor's animation frame f18, then (asserting both times are
   positive) advances; step 1 waits for the delay, fires action f1C and advances; step 2 waits out the duration
   and finishes (marking s done). While running, s->f0 (if set) reads 2. */
void m1_TimedAct12CF00(void *o, M1Tb262 *a, M1Ta262 *s)
{
    switch (s->stC) {
    case 0:
        if (sub_00145730(a->f5C, (int32_t)(double)s->f18)) {
            if (!(s->delay10 > 0.0f)) for (;;) ;
            if (!(s->dur14 > 0.0f)) for (;;) ;
            s->stC++;
        }
        break;
    case 1:
        if (s->t8 > s->delay10) {
            sub_0011FCC0(a, o, (int32_t)s->f1C);
            s->stC++;
        }
        break;
    case 2:
        if (s->t8 - s->delay10 > s->dur14) {
            if (s->f0) s->f0 = 1;
            sub_00113370(a, s);
            return;
        }
        break;
    }
    if (s->f0) s->f0 = 2;
}
