/* Area m1, file 286: overlap tests. Names inferred. */
#include <stdint.h>

typedef struct M1Bd286 { uint8_t unk00[0x60]; float pos60[4]; uint8_t unk70[0x30]; float offA0[3]; uint8_t unkAC[4];
    float rB0, hB4; } M1Bd286;
void sub_000F5D40(float *d, const float *s);
void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
float sub_00082D70(const float *v);                           /* length */

/* 0x0001BDC0: gap between bodies a and b: -1 when their height ranges do not overlap; otherwise store both
   centres (pos + offset) and the flat direction from a to b, and return the sum of radii minus the flat
   distance (positive when they overlap). regargs: a=EDI, b=ESI, ca=ECX, dir=EBX; stack arg (cb). */
float m1_BodyGap1BDC0(M1Bd286 *a, M1Bd286 *b, float *ca, float *dir, float *cb)
{
    float pa[4], pb[4];
    pa[0] = a->pos60[0] + a->offA0[0];
    pa[2] = a->pos60[2] + a->offA0[2];
    pa[3] = a->pos60[3];
    pb[0] = b->offA0[0] + b->pos60[0];
    pb[2] = b->pos60[2] + b->offA0[2];
    pb[3] = b->pos60[3];
    pb[1] = b->pos60[1] + b->offA0[1];
    pa[1] = a->pos60[1] + a->offA0[1];
    if (b->hB4 + pb[1] > pa[1]) return -1.0f;
    if (a->hB4 + pa[1] > pb[1]) return -1.0f;
    sub_000F5D40(ca, pa);
    sub_000F5D40(cb, pb);
    pa[1] = 0.0f;
    pb[1] = 0.0f;
    sub_001AD9F0(dir, pb, pa);
    return (a->rB0 + b->rB0) - sub_00082D70(dir);
}

typedef struct M1Sv286 { uint8_t unk00[4]; int32_t ver4; uint32_t n8; uint8_t unkC[4]; uint8_t data10[1]; } M1Sv286;
void *sub_00053AB0(uint32_t size, int32_t a, int32_t tag);    /* allocate */
void sub_00053880(void *p);                                   /* free */
void sub_000187E0(uint8_t *d, const uint8_t *s);              /* regargs: d=EBX; convert a v1 record (0x540 bytes) */
void sub_00018840(uint8_t *d, const uint8_t *s);              /* regargs: d=EBX; convert a v2 record (0x550 bytes) */
void m1_RecCopy188E0(uint8_t *d, const uint8_t *s);           /* regargs: d=EBX; copy a v3 record (0x560 bytes) */
void sub_000195F0(uint8_t *d);                               /* reset a record */

/* 0x000189C0: load h's record array into a new buffer of max(n, 64) 0x560-byte records, converting from
   format versions 1-3 (record sizes 0x540, 0x550, 0x560); an unknown version frees the buffer and gives 0.
   Unused records are reset. Returns the buffer. */
uint8_t *m1_LoadRecords189C0(M1Sv286 *h)
{
    int32_t ver = h->ver4;
    uint32_t n = h->n8, cap = 0x40, k, z = 0;
    uint8_t *buf, *d;
    const uint8_t *s;
    if (n >= 0x40) cap = n;
    buf = sub_00053AB0(cap * 0x560, 0, 0x9B);
    switch (ver) {
    case 1:
        s = h->data10;
        d = buf;
        if (n > *(volatile uint32_t *)&z) {
            k = n;
            do {
                sub_000187E0(d, s);
                d += 0x560;
                s += 0x540;
            } while (--k);
        }
        break;
    case 2:
        s = h->data10;
        d = buf;
        if (n > *(volatile uint32_t *)&z) {
            k = n;
            do {
                sub_00018840(d, s);
                d += 0x560;
                s += 0x550;
            } while (--k);
        }
        break;
    case 3:
        d = buf;
        if (n > *(volatile uint32_t *)&z) {
            k = n;
            do {
                m1_RecCopy188E0(d, d + (h->data10 - buf));
                d += 0x560;
            } while (--k);
        }
        break;
    default:
        sub_00053880(buf);
        buf = 0;
        break;
    }
    if (n < cap) {
        d = buf + n * 0x560;
        k = cap - n;
        do {
            sub_000195F0(d);
            d += 0x560;
        } while (--k);
    }
    return buf;
}
