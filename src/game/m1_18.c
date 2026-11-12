/* Area m1, file 18: actor cleanup and list filter. Names inferred. */
#include <stdint.h>

typedef struct M1Work278 {
    uint8_t  unk00[8];
    void    *fx08;             /* +0x08 */
    uint32_t flags0C;          /* +0x0C */
} M1Work278;
typedef struct M1Actor278 {
    uint8_t    unk000[0x6C];
    int32_t    snd06C;         /* +0x06C, -1 = none */
    void      *res070;         /* +0x070 */
    uint8_t    unk074[0x278 - 0x74];
    M1Work278 *work278;        /* +0x278 */
} M1Actor278;
void  sub_00048250(int h);
void  sub_00033A70(void *r);
void  sub_001661B0(void *fx);
void *sub_0001D2B0(void *model, int part);
void  sub_0001EB80(void *o);

/* 0x0012D670: releases an actor's sound, resource and effect; with flag 0x100,
 * also resets part 2 of the model. Returns 1. */
int m1_ActorRelease12D670(void *model, M1Actor278 *a)
{
    M1Work278 *w = a->work278;
    if (a->snd06C != -1) {
        sub_00048250(a->snd06C);
        a->snd06C = -1;
    }
    if (a->res070 != 0) {
        sub_00033A70(a->res070);
        a->res070 = 0;
    }
    sub_001661B0(w->fx08);
    w->fx08 = 0;
    if (w->flags0C & 0x100)
        sub_0001EB80(sub_0001D2B0(model, 2));
    return 1;
}



typedef struct M1V4 { float v[4]; } M1V4;
typedef struct M1M4 { M1V4 r[4]; } M1M4;
/* 0x001ADE10: builds a matrix from four rows; returns it. */
M1M4 *m1_MatFromRows1ADE10(M1M4 *m, const M1V4 *a, const M1V4 *b, const M1V4 *c, const M1V4 *d)
{
    m->r[0] = *a;
    m->r[1] = *b;
    m->r[2] = *c;
    m->r[3] = *d;
    return m;
}
