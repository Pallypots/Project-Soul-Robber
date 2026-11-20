/* Area m1, file 266: record copies. Names inferred. */
#include <stdint.h>

typedef struct M1Blk266 { uint32_t w[0x144]; } M1Blk266;
typedef struct M1Rc266 { uint8_t unk00[4]; int32_t f4, f8; uint8_t unkC[4]; M1Blk266 b10; float v520[2][4];
    int32_t d540[6]; uint8_t c558[4]; } M1Rc266;
void sub_000195F0(M1Rc266 *d);
void sub_000F5D40(float *d, const float *s);

/* 0x000188E0: reset d, then copy s into it field by field: header words, the 0x510-byte body, two vectors,
   six words and four bytes. regargs: d=EBX; stack arg (s). */
void m1_RecCopy188E0(M1Rc266 *d, const M1Rc266 *s)
{
    float *p;
    int32_t n;
    sub_000195F0(d);
    d->f4 = s->f4;
    d->f8 = s->f8;
    d->b10 = s->b10;
    for (p = d->v520[0], n = 2; n; n--, p += 4)
        sub_000F5D40(p, (const float *)((const uint8_t *)p + ((const uint8_t *)s - (uint8_t *)d)));
    d->c558[0] = s->c558[0];
    d->c558[1] = s->c558[1];
    d->c558[2] = s->c558[2];
    d->c558[3] = s->c558[3];
    d->d540[0] = s->d540[0];
    d->d540[1] = s->d540[1];
    d->d540[2] = s->d540[2];
    d->d540[3] = s->d540[3];
    d->d540[4] = s->d540[4];
    d->d540[5] = s->d540[5];
}

typedef struct M1Pl266 { uint8_t unk00[0x10]; float e10[4]; float e20[4]; float normal30[4]; float pos40[4];
    uint8_t unk50[0x10]; } M1Pl266;                                    /* 0x60 */
typedef struct M1Pls266 { uint8_t unk00[4]; uint32_t n4; uint8_t unk08[4]; M1Pl266 *items0C; } M1Pls266;
void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
float sub_001B2730(const float *a, const float *b);           /* distance */
float sub_001AD9D0(const float *a, const float *b);           /* dot */
void sub_001ADB60(float *d, const float *s, float k);          /* d = s * k */

/* 0x00080A60: find the plane in l nearest to p; if a lies on its front side, flip it (swap its two edge points
   and negate the normal) so it faces away from a. Returns the plane or 0. regargs: a=ECX; stack args (l p). */
M1Pl266 *m1_NearestPlaneFlip80A60(M1Pls266 *l, const float *p, const float *a)
{
    M1Pl266 *it, *found = 0;
    float best = 10000000.0f, d;
    float v[4], t[4];
    uint32_t i;
    sub_001AD9F0(v, a, p);
    it = l->items0C;
    for (i = 0; i < l->n4; i++, it++) {
        d = sub_001B2730(p, it->pos40);
        if (best > d) {
            best = d;
            found = it;
        }
    }
    if (found && sub_001AD9D0(v, found->normal30) > 0.0f) {
        sub_000F5D40(t, found->e10);
        sub_000F5D40(found->e10, found->e20);
        sub_000F5D40(found->e20, t);
        sub_001ADB60(found->normal30, found->normal30, -1.0f);
    }
    return found;
}
