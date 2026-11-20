/* Area m1, file 269: menu sequences. Names inferred. */
#include <stdint.h>

typedef struct M1Ms269 { uint32_t flags0; int32_t step4; int32_t ticks8; } M1Ms269;
void sub_000DFD40(int32_t *a, int32_t *b);
void sub_000A43C0(int32_t slot, int32_t v);
void sub_000A5450(int32_t k);

/* 0x000AF920: menu sequence handler. Command 0 resets, 1 starts (step 10), 3 forces the end (step 20); then
   each call counts a tick: step 10 reads the menu state (asserting stage 3), and in modes 0-1 sets slots 3 and
   4 to 0x30 and shows panel 5 before advancing; step 20 resets and returns 0. */
int32_t m1_MenuSeqAF920(int32_t cmd, int32_t unused, M1Ms269 *s)
{
    int32_t stage, mode;
    if (cmd == 0) {
        s->flags0 = 0;
        s->step4 = 0;
        s->ticks8 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags0 |= 1;
        s->ticks8 = 0;
        s->step4 = 10;
        return 1;
    }
    if (cmd == 3) {
        s->flags0 = 0;
        s->step4 = 0x14;
    }
    s->ticks8++;
    if (s->step4 == 10) {
        sub_000DFD40(&stage, &mode);
        if (stage != 3) for (;;) ;
        for (;;) {
            if (mode == 0 || mode == 1) break;
            if (mode == 5 || mode == 6) goto skip;
        }
        sub_000A43C0(3, 0x30);
        sub_000A43C0(4, 0x30);
        sub_000A5450(5);
skip:
        s->step4++;
        return 1;
    }
    if (s->step4 == 0x14) {
        s->flags0 = 0;
        s->step4 = 0;
        return 0;
    }
    return 1;
}

extern const float m1_vec3DA088[4];
extern const uint32_t m1_q28369C[4];
void sub_001ADA40(uint32_t *d, const float *m);       /* copy a 4x4 matrix */
void sub_001B1F70(uint32_t *d, const float *m);
void sub_000F5D40(uint32_t *d, const float *v);

/* 0x00034430: build the matrix upload packet at p for matrix m: VIF/GIF headers, m, its derived matrix, a
   vector, then two closing tags and the fixed quadword 0x0028369C. Returns the end of the packet.
   regargs: p=EAX, m=EBX. */
uint32_t *m1_MatPacket34430(uint32_t *p, const float *m)
{
    uint32_t *q = p + 4;
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x11000000;
    q[0] = 0x10000008;
    q[1] = 0;
    q[2] = 0x1000101;
    q[3] = 0x6C08001B;
    q += 4;
    sub_001ADA40(q, m);
    q += 16;
    sub_001B1F70(q, m);
    q += 16;
    q[0] = 0x10000001;
    q[1] = 0;
    q[2] = 0x1000101;
    q[3] = 0x6C01001A;
    q += 4;
    sub_000F5D40(q, m1_vec3DA088);
    q[5] = 0;
    q[4] = 0x10000000;
    q[6] = 0x14000000;
    q[7] = 0x11000000;
    q += 4;
    q[5] = 0;
    q[4] = 0x10000001;
    q[6] = 0x1000101;
    q[7] = 0x30000000;
    q += 4;
    q += 4;
    q[3] = m1_q28369C[3];
    q[2] = m1_q28369C[2];
    q[1] = m1_q28369C[1];
    q[0] = m1_q28369C[0];
    return q + 4;
}

extern const char m1_fmtSe26CB24[], m1_fmtSe26CAF8[], m1_fmtSe26CAC8[], m1_fmtSe26CA90[], m1_fmtSe26CA6C[], m1_fmtSe26CA4C[];
extern int32_t m1_worldA41316C, m1_worldB413170;
int32_t sub_0007E070(char *buf, int32_t n, const char *fmt, ...);   /* snprintf */

/* 0x0005BF00: build the debug host path of sound bank c for owner kind k (character, character pair, world
   object or common bank) into buf. With mode set only the common-bank forms are used.
   regargs: k=EAX, c=ECX, buf=EDX, s=ESI; stack arg (mode). */
void m1_SeBankPath5BF00(int32_t k, int32_t c, char *buf, int32_t s, int32_t mode)
{
    if (mode == 0) {
        switch (k) {
        case 1:
            sub_0007E070(buf, 0x7F, m1_fmtSe26CB24, k, k, c);
            return;
        case 8: case 9: case 11: case 13: case 15:
            sub_0007E070(buf, 0x7F, m1_fmtSe26CAF8, k, k, s, c);
            return;
        case 2: case 3: case 4: case 5: case 6: case 7:
            sub_0007E070(buf, 0x7F, m1_fmtSe26CAC8, k, s, k, s, c);
            return;
        case 12:
            sub_0007E070(buf, 0x7F, m1_fmtSe26CA90, m1_worldA41316C, m1_worldB413170, k, s, c);
            return;
        }
    } else {
        if (k == 1) {
            sub_0007E070(buf, 0x7F, m1_fmtSe26CA4C, 1, c);
            return;
        }
        if (k == 3) {
            sub_0007E070(buf, 0x7F, m1_fmtSe26CA6C, 3, s, c);
            return;
        }
    }
    sub_0007E070(buf, 0x7F, m1_fmtSe26CA6C, k, s, c);
}

typedef struct M1Tg269 { uint8_t unk00[0x60]; float pos60[4]; } M1Tg269;
typedef struct M1Th269 { int32_t id0; M1Tg269 *t4; uint8_t unk08[0x58]; float pos60[4]; } M1Th269;
typedef struct M1Seg269 { float unk0[2]; float b[2]; float from[4]; float to[4]; } M1Seg269;
extern uint8_t m1_stats41FEC0[];
extern M1Tg269 *g_playerObj;
void sub_000C4250(void *stats, float *a, float *b);
int32_t sub_00194F00(float *a, M1Seg269 *seg, float *b);
void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
void sub_001AD7E0(float *d, const float *s);                  /* normalise */
int32_t sub_000D3BF0(void *stats, int32_t id, int32_t k, float *b, float *dir);

/* 0x001954C0: throw o at its target: if the path from o to its target is clear, aim along the flat direction
   from the target to the player and launch (0xD3BF0); on success move the target to the landing point.
   Returns the launch id or -1. regargs: o=EAX; stack arg (k). */
int32_t m1_ThrowAt1954C0(M1Th269 *o, int32_t k)
{
    M1Tg269 *t = o->t4;
    float a[4], b[4], d[4];
    M1Seg269 seg;
    int32_t r;
    sub_000C4250(m1_stats41FEC0, a, b);
    seg.b[0] = b[0];
    seg.b[1] = b[1];
    sub_000F5D40((uint32_t *)seg.from, o->pos60);
    sub_000F5D40((uint32_t *)seg.to, t->pos60);
    if (sub_00194F00(a, &seg, b)) {
        sub_001AD9F0(d, g_playerObj->pos60, t->pos60);
        d[3] = 0.0f;
        d[1] = 0.0f;
        sub_001AD7E0(d, d);
        r = sub_000D3BF0(m1_stats41FEC0, o->id0, k, b, d);
        if (r != -1) {
            sub_000F5D40((uint32_t *)t->pos60, b);
            return r;
        }
    }
    return -1;
}
