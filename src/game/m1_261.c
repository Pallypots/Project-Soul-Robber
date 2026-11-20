/* Area m1, file 261: search helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Pl261 { uint8_t unk00[0x30]; float normal30[4]; float pos40[4]; uint8_t unk50[0x10]; } M1Pl261;  /* 0x60 */
typedef struct M1Pls261 { uint8_t unk00[4]; uint32_t n4; uint8_t unk08[4]; M1Pl261 *items0C; } M1Pls261;
void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
float sub_001AD9D0(const float *a, const float *b);           /* dot */
float sub_00082D70(const float *v);                           /* length */

/* 0x00080B40: of the planes in l that face away from p (p is behind them), return the nearest one, or 0.
   regargs: l=EBX; stack arg (p). */
M1Pl261 *m1_NearestPlane80B40(M1Pls261 *l, const float *p)
{
    M1Pl261 *it = l->items0C, *found = 0;
    float best, len;
    float v[4];
    uint32_t i;
    best = 10000000.0f;
    for (i = 0; i < l->n4; i++, it++) {
        sub_001AD9F0(v, it->pos40, p);
        if (0.0f > sub_001AD9D0(v, it->normal30)) {
            len = sub_00082D70(v);
            if (best > len) {
                best = len;
                found = it;
            }
        }
    }
    return found;
}

typedef struct M1Fo261 { uint8_t unk00[0x10]; uint8_t b10; } M1Fo261;
typedef struct M1Fe261 { uint8_t unk00[0xC]; uint32_t flagsC; } M1Fe261;
typedef struct M1Fa261 { uint8_t unk00[0x74]; M1Fe261 *e74; } M1Fa261;
typedef struct M1Fm261 { int32_t id0; } M1Fm261;
void sub_00189DA0(M1Fo261 *o, M1Fa261 *a, int32_t next);
void sub_00189DA0b(M1Fo261 *o, M1Fa261 *a, int32_t next);   /* same function (alias stops cl merging calls) */

/* 0x0018B830: hit message handler. Ignored while o has flag 8. Message 5 marks the hit and moves to state 2
   or 3 (by flag bit 1); messages 1-3, 6-11, 14, 32, 34, 35 mark it and move to state 2. Returns -1 when
   handled, 0 otherwise. */
int32_t m1_OnHit18B830(M1Fo261 *o, M1Fa261 *a, M1Fm261 *m)
{
    M1Fe261 *e;
    uint32_t f, k;
    if (o->b10 & 8) return 0;
    e = a->e74;
    switch (m->id0) {
    case 5:
        f = e->flagsC;
        k = ((~f & 2) | 4) >> 1;
        e->flagsC = f | 8;
        if (k) sub_00189DA0(o, a, k);
        return -1;
    case 1: case 2: case 3: case 6: case 7: case 8: case 9: case 10: case 11: case 14: case 32: case 34: case 35:
        e->flagsC |= 8;
        sub_00189DA0b(o, a, 2);
        return -1;
    }
    return 0;
}

extern int32_t m1_capMode3F47B8, m1_capMode3F4874, m1_capReady3F4884;
extern uint32_t m1_capFlags3F47B4, m1_capFlags3F4870;
void sub_000E99F0(void);
void sub_000E9A60(void);
void sub_000E9180(void);
void sub_000E9240(void);
void sub_000E9300(void);
void sub_000E9380(void);
void sub_000E95F0(void);
void sub_000E9AB0(void);

/* 0x000E9B00: per-frame caption update: run both caption layers' common steps, then each layer's mode
   (0 hides it, 1-3 run its stages; mode 3 of the second layer just marks it ready), then finish. */
void m1_CaptionTickE9B00(void)
{
    sub_000E99F0();
    sub_000E9A60();
    switch (m1_capMode3F47B8) {
    case 0: m1_capFlags3F47B4 &= ~1u; break;
    case 1: sub_000E9180(); break;
    case 2: sub_000E9240(); break;
    case 3: sub_000E9300(); break;
    }
    switch (m1_capMode3F4874) {
    case 0: m1_capFlags3F4870 &= ~1u; break;
    case 1: sub_000E9380(); break;
    case 2: sub_000E95F0(); break;
    case 3:
        if (m1_capReady3F4884 == 0)
            m1_capReady3F4884 = 1;
        break;
    }
    sub_000E9AB0();
}

typedef struct M1Pkt261 { uint32_t *cur; uint32_t unk4[3]; } M1Pkt261;   /* 16-byte packet slot */
typedef struct M1Q261 { uint32_t w[4]; } M1Q261;
extern int32_t m1_pktIdx37B4A0, m1_dma37B390;
extern M1Pkt261 m1_pkts37B4AC[2];
extern const M1Q261 m1_tag280480, m1_tag280490;
int32_t sub_00102FA0(void *p, ...);                      /* debug trace (does nothing in retail) */
int32_t sub_00102FA0b(void *p, ...);                     /* same function (alias keeps both branch calls) */
int32_t sub_00102FA0c(void *p, ...);
int32_t sub_000AD090(void *p, ...);                      /* stub */

/* 0x000138F0: flip to the other packet slot, trace it, and write a 0x4E header word (8 quadwords follow).
   Returns the header's address. */
uint32_t *m1_PktOpen138F0(void)
{
    M1Pkt261 *p;
    uint32_t *d;
    m1_pktIdx37B4A0 ^= 1;
    sub_00102FA0(&m1_pkts37B4AC[m1_pktIdx37B4A0]);
    p = &m1_pkts37B4AC[m1_pktIdx37B4A0];
    if (m1_dma37B390)
        sub_00102FA0b(p, 0, 0, 0);
    else
        sub_00102FA0c(p, 0, 0, 0);
    sub_00102FA0(p, m1_tag280480);
    d = p->cur;
    d[0] = 0x4E;
    d[1] = 0;
    sub_000AD090(p, 8);
    sub_00102FA0(p);
    sub_000AD090(p);
    return d;
}

/* 0x00013990: same as 0x000138F0 with header 0x15C and 0x1C quadwords. */
uint32_t *m1_PktOpen13990(void)
{
    M1Pkt261 *p;
    uint32_t *d;
    m1_pktIdx37B4A0 ^= 1;
    sub_00102FA0(&m1_pkts37B4AC[m1_pktIdx37B4A0]);
    p = &m1_pkts37B4AC[m1_pktIdx37B4A0];
    if (m1_dma37B390)
        sub_00102FA0b(p, 0, 0, 0);
    else
        sub_00102FA0c(p, 0, 0, 0);
    sub_00102FA0(p, m1_tag280490);
    d = p->cur;
    d[0] = 0x15C;
    d[1] = 0;
    sub_000AD090(p, 0x1C);
    sub_00102FA0(p);
    sub_000AD090(p);
    return d;
}

extern const M1Q261 m1_tag280430;
uint32_t *sub_00013AA0(void);

/* 0x00013C00: flip to the other packet slot and trace it with header tag 0x00280430 and values (a b c), then
   continue in 0x00013AA0. */
uint32_t *m1_PktOpen13C00(int32_t a, int32_t b, int32_t c)
{
    M1Pkt261 *p;
    m1_pktIdx37B4A0 ^= 1;
    sub_00102FA0(&m1_pkts37B4AC[m1_pktIdx37B4A0]);
    p = &m1_pkts37B4AC[m1_pktIdx37B4A0];
    if (m1_dma37B390)
        sub_00102FA0b(p, 0, 0, 0);
    else
        sub_00102FA0c(p, 0, 0, 0);
    sub_00102FA0(p, m1_tag280430);
    sub_00102FA0(p, a, b, c);
    sub_00102FA0(p);
    sub_000AD090(p);
    return sub_00013AA0();
}
