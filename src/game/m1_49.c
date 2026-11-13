/* Area m1, file 49: model show/hide chains and screen shuffles. Names inferred. */
#include <stdint.h>

typedef struct M1Node3C { uint8_t unk00[0x3C]; struct M1Node3C *next3C; } M1Node3C;
typedef struct M1Fade270 {
    uint8_t unk000[0x20];
    uint32_t flags20;          /* +0x20 */
    uint8_t unk024[0x270 - 0x24];
    float   max270;            /* +0x270 */
    float   cur274;            /* +0x274 */
} M1Fade270;
void sub_0001F070(M1Node3C *n, int on);
void sub_0001EBF0(M1Node3C *n, int mode);

/* 0x001130F0: show or hide every node in the chain (+0x3C); when shown sets flag 1,
 * draw mode 3 and grows +0x274 by half of +0x270 (capped at +0x270), else clears
 * flag 1 and draw mode 1. */
void m1_ChainShow1130F0(M1Node3C *n, M1Fade270 *h, int on)
{
    M1Node3C *p = n;
    float t;
    while (p != 0) {
        sub_0001F070(p, on ? 1 : 0);
        p = p->next3C;
    }
    if (on) {
        h->flags20 |= 1;
        sub_0001EBF0(n, 3);
        t = h->max270 * 0.5f + h->cur274;
        h->cur274 = t;
        if (t > h->max270)
            h->cur274 = h->max270;
    } else {
        h->flags20 &= ~1u;
        sub_0001EBF0(n, 1);
    }
}

typedef struct M1Mat108 { uint8_t unk00[0xE8]; float alphaE8; uint8_t unkEC[0x108 - 0xEC]; } M1Mat108;
typedef struct M1Mdl { uint8_t unk00[0xC0]; int32_t nC0; M1Mat108 *matC4; } M1Mdl;
typedef struct M1MdlNode { uint8_t unk00[0x20]; M1Mdl *mdl20; uint8_t unk24[0x3C - 0x24]; struct M1MdlNode *next3C; } M1MdlNode;
typedef struct M1H68b { uint8_t unk00[0x68]; float t68; } M1H68b;
typedef struct M1Comp6C { uint8_t unk00[0x6C]; int32_t mode6C; } M1Comp6C;
M1Comp6C *sub_0001D960(void *o, int kind);
void sub_000F3D10(void *o, void *c, int mode);
void sub_000F3B70(void *o, int v);

/* 0x0010A0A0: fade-out: while h +0x68 is under 0.6, every material of every model in
 * the chain gets alpha (0.6 - t) * 213.33; after that (spins on a null o) puts the
 * kind-5 component back to mode 0 and calls 0xF3B70(3). */
void m1_FadeOut10A0A0(M1MdlNode *o, M1H68b *h)
{
    M1MdlNode *p = o;
    M1Mdl *m;
    M1Comp6C *c;
    float a;
    int i, off;
    if (h->t68 < 0.6f) {
        a = (0.6f - h->t68) * 213.33333f;
        do {
            m = p->mdl20;
            for (i = 0, off = 0; i < m->nC0; i++, off += sizeof(M1Mat108))
                ((M1Mat108 *)((uint8_t *)m->matC4 + off))->alphaE8 = a;
            p = p->next3C;
        } while (p != 0);
        return;
    }
    if (o == 0)
        for (;;) ;
    c = sub_0001D960(o, 5);
    if (c->mode6C != 0)
        sub_000F3D10(o, c, 0);
    sub_000F3B70(o, 3);
}
