/* Area m1, file 136: scripted sequences. Names inferred. */
#include <stdint.h>

typedef struct M1Seq136 { uint32_t flags00; int32_t step04; int32_t n08; } M1Seq136;
void sub_000DFD40(int *a, int *b);
void sub_000A43C0(int a, int b);
void sub_000A5450(int a);

/* 0x000BA7C0: scripted sequence: mode 0 clears, mode 1 starts (flag 1, step 10), mode 3 jumps
 * to step 0x14; each call counts; step 10 polls 0xDFD40 (hangs unless area 4 room 0), plays cues
 * 9..0xB (0x2E) and 0xD..0xE (0x30) with effects 0xC and 0xF, then advances; step 0x14 ends
 * it (returns 0). */
int m1_Seq0BA7C0(int mode, M1Seq136 *s)
{
    int k;
    if (mode == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->n08 = 0;
        return 1;
    }
    if (mode == 1) {
        s->n08 = 0;
        s->flags00 |= 1;
        s->step04 = 10;
        return 1;
    }
    if (mode == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
    }
    s->n08++;
    if (s->step04 == 10) {
        sub_000DFD40(&k, &mode);
        if (mode != 4)
            for (;;) ;
        if (k != 0)
            for (;;) ;
        sub_000A43C0(9, 0x2E);
        sub_000A43C0(0xA, 0x2E);
        sub_000A43C0(0xB, 0x2E);
        sub_000A5450(0xC);
        sub_000A43C0(0xD, 0x30);
        sub_000A43C0(0xE, 0x30);
        sub_000A5450(0xF);
        s->step04++;
        return 1;
    }
    if (s->step04 == 0x14) {
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

void sub_001AD9F0(float *out, const float *a, const float *b);
void sub_001AD7E0(float *out, const float *v);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_00082A30(float *d, const float *q, const float *v);
void sub_001ADAF0(float *d, const float *a, const float *b);

/* 0x000CA200: side-step direction: the unit vector from b to a scaled by k1, turned 90 degrees
 * left (side > 0: right) about the vertical, added to a; out = the unit direction from b to
 * that point times k2. */
void m1_SideStep0CA200(const float *a, const float *b, float *out, float side, float k2, float k1)
{
    struct { float d[4]; float r[4]; } l;
    l.d[0] = 0.0f;
    l.d[1] = 0.0f;
    l.d[2] = 0.0f;
    l.d[3] = 1.0f;
    l.r[0] = 0.0f;
    l.r[1] = 0.0f;
    l.r[2] = 0.0f;
    l.r[3] = 1.0f;
    sub_001AD9F0(l.d, a, b);
    sub_001AD7E0(l.d, l.d);
    sub_001ADBA0(l.d, l.d, k1);
    l.r[1] = 1.57079637f;
    if (side > 0.0f)
        l.r[1] = -1.57079637f;
    sub_00082A30(l.d, l.r, l.d);
    sub_001ADAF0(l.d, a, l.d);
    sub_001AD9F0(l.d, l.d, b);
    sub_001AD7E0(l.d, l.d);
    sub_001ADBA0(out, l.d, k2);
}

typedef struct M1Job136 { uint8_t unk[0x10]; } M1Job136;
typedef struct M1Res136 { uint8_t unk00[0xC]; void *self0C; uint8_t unk10[0x38 - 0x10]; } M1Res136;
extern M1Job136 m1_jobs3E46E0[6];
extern uint8_t m1_free3E3F54[];
extern M1Res136 m1_res3E3F98[32];
extern void *m1_thr3E4698;
extern int32_t m1_ld3E3F90;
extern int32_t m1_ld3E3F64[4];
extern int32_t m1_ld3E46A0[16];
extern int32_t m1_ld3E3F74[4];
extern int32_t m1_ld3E3F50, m1_ld3E3F8C;
extern int32_t m1_ld3E46D8[2];
void sub_0003D860(void *list);
void sub_0003D880(void *list, void *node);
void *sub_001AD560(void);
void sub_001AD570(void *t, int pri);

/* 0x000582C0: loader init: empty the six job lists and the free list, put the 32 resource
 * records on the free list (each its own owner), start the loader thread at priority 0x40,
 * and reset the request slots (-1) and counters (0). */
void m1_LoaderInit0582C0(void)
{
    M1Job136 *j;
    M1Res136 *r;
    int n;
    for (j = m1_jobs3E46E0; (int)j < (int)(m1_jobs3E46E0 + 6); j++)
        sub_0003D860(j);
    sub_0003D860(m1_free3E3F54);
    r = m1_res3E3F98;
    n = 0x20;
    do {
        sub_0003D880(m1_free3E3F54, r);
        r->self0C = r;
        r++;
    } while (--n);
    m1_thr3E4698 = sub_001AD560();
    sub_001AD570(m1_thr3E4698, 0x40);
    m1_ld3E3F90 = -1;
    m1_ld3E3F64[0] = 0;
    m1_ld3E3F64[1] = -1;
    m1_ld3E3F64[2] = -1;
    m1_ld3E46A0[0] = -1;
    m1_ld3E46A0[1] = -1;
    m1_ld3E46A0[2] = -1;
    m1_ld3E46A0[3] = -1;
    m1_ld3E46A0[4] = -1;
    m1_ld3E46A0[5] = -1;
    m1_ld3E46A0[6] = -1;
    m1_ld3E46A0[7] = -1;
    m1_ld3E46A0[8] = -1;
    m1_ld3E46A0[9] = -1;
    m1_ld3E46A0[10] = -1;
    m1_ld3E46A0[11] = -1;
    m1_ld3E46A0[12] = -1;
    m1_ld3E3F74[0] = 0;
    m1_ld3E3F74[1] = 0;
    m1_ld3E46A0[13] = -1;
    m1_ld3E3F74[2] = 0;
    m1_ld3E3F50 = 0;
    m1_ld3E3F74[3] = 0;
    m1_ld3E3F8C = 0;
    m1_ld3E46D8[0] = -1;
    m1_ld3E46D8[1] = 0;
}
