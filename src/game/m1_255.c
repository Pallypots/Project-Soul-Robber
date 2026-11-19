/* Area m1, file 255: model node setup helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Blk255 { uint32_t w[0x3C]; } M1Blk255;                     /* 0xF0-byte node block */
typedef struct M1Nd255 { int32_t kind0; int32_t unk4; struct M1Nd255 *next8; uint8_t unkC[0x28]; int32_t f34; } M1Nd255;
typedef struct M1Mb255 { uint8_t unk00[0xBC]; int32_t fBC; } M1Mb255;
typedef struct M1Ow255 { uint8_t unk00[0xC]; uint8_t bC; uint8_t unkD[0x13]; int32_t f20; uint8_t unk24[4]; M1Mb255 *m28;
    uint8_t unk2C[0x14]; M1Nd255 *list40; } M1Ow255;
typedef struct M1Pt255 { uint8_t unk00[0x20]; int32_t f20; uint8_t unk24[4]; void *h28; int32_t f2C; } M1Pt255;
void sub_001B2080(void *h);
int32_t sub_000AD090(void);
void sub_001B8240(void *h);
void sub_001B8240b(void *h);
void sub_001B2FE0(void *h);
void sub_001B85B0(int32_t a, void *h);
void sub_001B87F0(void *h, int32_t a);
void sub_0001FE70(M1Pt255 *p, int32_t a, void *h, int32_t b, int32_t c);

/* 0x00022280: attach p's node to owner o. Needs a kind-1 entry in o's list. Detaches p's old node, re-inits it
   (type 1 or type 12 by o's flag 0x10), then for type 12 copies o's 0xF0-byte block into it and sets it up;
   type 1 goes through 1fe70 instead. regargs: o=EAX. */
void m1_NodeAttach22280(M1Ow255 *o, M1Pt255 *p)
{
    M1Nd255 *n;
    for (n = o->list40; n; n = n->next8)
        if (n->kind0 == 1) break;
    if (!n) return;
    if (p->h28) {
        sub_001B2080(p->h28);
        if (!(o->bC & 0x10)) {
            sub_000AD090();
            sub_001B8240(p->h28);
        } else {
            sub_000AD090();
            sub_001B2FE0(p->h28);
        }
        sub_000AD090();
    }
    if (!p->f20 || !o->f20 || !p->h28 || !o->m28) return;
    if (!(o->bC & 0x10)) {
        sub_000AD090();
        sub_001B8240b(p->h28);
        sub_000AD090();
        *(M1Blk255 *)p->h28 = *(M1Blk255 *)o->m28;
        sub_000AD090();
        sub_001B85B0(p->f2C, p->h28);
        sub_000AD090();
        sub_001B87F0(p->h28, p->f20);
        return;
    }
    sub_0001FE70(p, o->m28->fBC, p->h28, p->f2C, n->f34);
}

void sub_001AD940(float *m);
void sub_001AD8B0(float *out, const float *in, float a);
void sub_001AD8E0(float *out, const float *in, float a);
void sub_001AD910(float *out, const float *in, float a);
void sub_001ADBF0(float *out, const float *in, const float *v);
void sub_001AD8B0b(float *out, const float *in, float a);   /* aliases stop cl merging the shared tails */
void sub_001AD8E0b(float *out, const float *in, float a);
void sub_001AD910b(float *out, const float *in, float a);
void sub_001AD8B0c(float *out, const float *in, float a);
void sub_001AD8E0c(float *out, const float *in, float a);
void sub_001AD910c(float *out, const float *in, float a);

/* 0x001AEAF0: build rotation matrix m from angles v (x, y, z) in the given axis order (0 = combined call,
   0x10000-0x50000 = YZX, XZY, ZXY, YXZ, XYZ). regargs: m=ESI, order=EBX, v=EDI. */
void m1_RotOrder1AEAF0(float *m, uint32_t order, const float *v)
{
    sub_001AD940(m);
    switch (order) {
    case 0x20000:
        sub_001AD8B0(m, m, v[0]);
        sub_001AD910(m, m, v[2]);
        sub_001AD8E0(m, m, v[1]);
        return;
    case 0x10000:
        sub_001AD8E0(m, m, v[1]);
        sub_001AD910(m, m, v[2]);
        sub_001AD8B0(m, m, v[0]);
        return;
    case 0:
        sub_001ADBF0(m, m, v);
        return;
    case 0x30000:
        sub_001AD910b(m, m, v[2]);
        sub_001AD8B0b(m, m, v[0]);
        sub_001AD8E0b(m, m, v[1]);
        return;
    case 0x50000:
        sub_001AD8B0c(m, m, v[0]);
        sub_001AD8E0c(m, m, v[1]);
        sub_001AD910c(m, m, v[2]);
        return;
    case 0x40000:
        sub_001AD8E0(m, m, v[1]);
        sub_001AD8B0(m, m, v[0]);
        sub_001AD910(m, m, v[2]);
        return;
    }
}

