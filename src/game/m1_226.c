/* Area m1, file 226: node attach setup and transform build (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Node226 { uint8_t unk00[0x180]; } M1Node226;
typedef struct M1Mdl226 { uint8_t unk00[0xC4]; M1Node226 *nodesC4; } M1Mdl226;
typedef struct M1B226 { uint8_t unk00[0x20]; M1Mdl226 *mdl20; } M1B226;
typedef struct M1Att226 { int32_t a0; void (*cb4)(void); uint8_t unk08[8]; M1B226 *b10; int32_t n14; float f18, f1C, f20, f24, f28, f2C; } M1Att226;
typedef struct M1O226 { uint8_t unk00[0x278]; uint8_t *ext278; } M1O226;
void sub_001B2150(M1Att226 *a);
void sub_001B2160(M1Node226 *n, M1Att226 *a);
void sub_00186500(void);

/* 0x00188740: reset the attach record at o's extension +0x70, point it at b with callback 0x186500, and attach it
   to b's model nodes 3, 4, 5 and 6 (regargs: o=EAX b=ECX). */
void m1_AttachNodes188740(M1O226 *o, M1B226 *b)
{
    int ids[4];
    M1Mdl226 *m = b->mdl20;
    M1Att226 *a = (M1Att226 *)(o->ext278 + 0x70);
    int i;
    ids[0] = 3; ids[1] = 4; ids[2] = 5; ids[3] = 6;
    sub_001B2150(a);
    a->b10 = b;
    a->cb4 = sub_00186500;
    a->f18 = 0.0f; a->f1C = 0.0f; a->f20 = 0.0f; a->f24 = 0.0f; a->f28 = 0.0f; a->f2C = 0.0f;
    a->n14 = 0;
    for (i = 0; i < 4; i++)
        sub_001B2160(&m->nodesC4[ids[i]], a);
}

typedef struct M1Pv226 { uint8_t unk00[0x20]; void *xf20; uint8_t unk24[0x3C]; float pos60[3]; float f6C; } M1Pv226;
typedef struct M1S226 { uint8_t unk00[8]; float scale8; uint8_t unkC[8]; float pos14[3]; float f20; uint8_t unk24[4];
                        float ang28; uint8_t unk2C[0xBC]; M1Pv226 *pvE8; } M1S226;
void sub_000F5D40(float *dst, const float *src);
void sub_001AD940(float *m);
void sub_001AD8E0(float *dst, const float *src, float ang);
void sub_001ADBA0(float *dst, const float *src, float s);
void sub_001ADA40(void *xf, const float *m);

/* 0x000C7700: copy s's position to its pivot, reset both weights to 1, build identity -> rotate by +0x28 -> scale
   rows 0..2 by +8 -> translate to the pivot, and load it into the pivot's transform (regargs: s=ESI). */
void m1_BuildXform0C7700(M1S226 *s)
{
    float m[16];
    void *xf = s->pvE8->xf20;
    sub_000F5D40(s->pvE8->pos60, s->pos14);
    s->f20 = 1.0f;
    s->pvE8->f6C = 1.0f;
    sub_001AD940(m);
    sub_001AD8E0(m, m, s->ang28);
    sub_001ADBA0(m, m, s->scale8);
    sub_001ADBA0(m + 4, m + 4, s->scale8);
    sub_001ADBA0(m + 8, m + 8, s->scale8);
    sub_000F5D40(m + 12, s->pvE8->pos60);
    sub_001ADA40(xf, m);
}

typedef void (*M1Fn226)(void);
typedef struct M1Ctl226 {
    uint8_t unk00[0x10]; uint8_t blk10[0x24];
    M1Fn226 fn34, fn38, fn3C; uint8_t unk40[0xC];
    int32_t a4C, a50; float f54, f58; int32_t a5C, i60; float f64; int32_t i68; M1Fn226 fn6C;
    float q70[5], q84[4], q94[4];
} M1Ctl226;
void sub_000EE270(void *blk);
void sub_00172340(void); void sub_001723A0(void); void sub_001740F0(void); void sub_001724E0(void);

/* 0x001745D0: initialise a controller: reset its +0x10 block, install its four handlers, clear counters, set the
   two ids to -1 and the three orientation blocks to identity (w = 1.0) (regargs: c=ESI). */
void m1_CtlInit1745D0(M1Ctl226 *c)
{
    sub_000EE270(c->blk10);
    c->fn34 = sub_00172340;
    c->fn38 = sub_001723A0;
    c->fn3C = sub_001740F0;
    c->f54 = 0.0f; c->f58 = 0.0f; c->f64 = 0.0f;
    c->fn6C = sub_001724E0;
    c->a4C = 0; c->a50 = 0; c->a5C = 0;
    c->i60 = -1; c->i68 = -1;
    c->q94[0] = 0.0f; c->q94[1] = 0.0f; c->q94[2] = 0.0f; c->q94[3] = 1.0f;
    c->q70[0] = 0.0f; c->q70[1] = 0.0f; c->q70[2] = 0.0f; c->q70[3] = 0.0f; c->q70[4] = 1.0f;
    c->q84[0] = 0.0f; c->q84[1] = 0.0f; c->q84[2] = 0.0f; c->q84[3] = 1.0f;
}

