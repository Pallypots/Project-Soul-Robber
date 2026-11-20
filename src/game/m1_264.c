/* Area m1, file 264: timed actions. Names inferred. */
#include <stdint.h>

typedef struct M1Ta264 { int32_t f0; uint8_t unk04[4]; float t8; int32_t stC; float delay10, dur14, f18, f1C; } M1Ta264;
typedef struct M1Tm264 { uint8_t unk00[0x18]; uint32_t flags18; } M1Tm264;
typedef struct M1Tb264 { uint8_t unk00[0x5C]; float f5C; uint8_t unk60[0x218]; M1Tm264 *m278; } M1Tb264;
int32_t sub_00145730(float t, int32_t n);
void sub_001130F0(void *o, M1Tb264 *a, int32_t k);
void sub_00113370(M1Tb264 *a, M1Ta264 *s);

/* 0x00185FE0: timed action variant. Step 0 waits for animation frame f18 (asserting both times are positive);
   step 1 waits for the delay, sets or clears the actor's flag bit 1 (on when action f1C is 1) and starts action
   f1C; step 2 waits out the duration and finishes. */
void m1_TimedAct185FE0(void *o, M1Tb264 *a, M1Ta264 *s)
{
    M1Tm264 *m = a->m278;
    switch (s->stC) {
    case 0:
        if (sub_00145730(a->f5C, (int32_t)(double)s->f18)) {
            if (!(s->delay10 > 0.0f)) for (;;) ;
            if (!(s->dur14 > 0.0f)) for (;;) ;
            s->stC++;
        }
        return;
    case 1:
        if (s->t8 > s->delay10) {
            if ((int32_t)(double)s->f1C == 1)
                m->flags18 |= 2;
            else
                m->flags18 &= ~2u;
            sub_001130F0(o, a, (int32_t)s->f1C);
            s->stC++;
        }
        return;
    case 2:
        if (s->t8 - s->delay10 > s->dur14)
            sub_00113370(a, s);
        return;
    }
}

typedef struct M1Hm264 { uint8_t unk00[0x54]; float yaw54; } M1Hm264;
typedef struct M1Hp264 { uint8_t unk00[0x8C]; M1Hm264 *m8C; uint8_t unk90[0x18]; float radA8; uint8_t unkAC[0x14];
    int32_t dirC0; float angC4, speedC8; } M1Hp264;
typedef struct M1Ho264 { uint8_t unk00[0x60]; float x60, y64, z68; } M1Ho264;
extern M1Hp264 *m1_helper3F611C;
void m1_AngWrap0F5ED0(float *a);
float sub_001A3EE0(float a);                                  /* sin */
float sub_001A3ED0(float a);                                  /* cos */
void sub_000FD5F0(void);

/* 0x000FD900: orbit step for the helper: turn its angle one step (direction 0 adds, 1 subtracts), wrap it,
   move o around the circle of radius radA8, face the model along the circle (yaw kept in -pi..pi), then
   continue in 0x000FD5F0. */
void m1_HelperOrbitFD900(M1Ho264 *o)
{
    M1Hp264 *h = m1_helper3F611C;
    M1Hm264 *m;
    float v;
    if (h->dirC0 == 0)
        h->angC4 = h->speedC8 + h->angC4;
    else if (h->dirC0 == 1)
        h->angC4 = h->angC4 - h->speedC8;
    m1_AngWrap0F5ED0(&h->angC4);
    o->x60 += sub_001A3EE0(h->angC4) * h->radA8;
    o->z68 += sub_001A3ED0(h->angC4) * h->radA8;
    v = 0.0f - m1_helper3F611C->angC4 - 1.5707964f;
    m = m1_helper3F611C->m8C;
    m->yaw54 = v;
    m->yaw54 = -3.1415927f > v ? v + 6.2831855f : v;   /* ternary stops cl duplicating the tail call */
    sub_000FD5F0();
}
