/* Area m2, file 21: collision gather. Names inferred. */
#include <stdint.h>

typedef struct M2Item21 { uint8_t unk00[0x50]; void *grp50; uint8_t unk54[0xC]; } M2Item21;
typedef struct M2Out21 { uint8_t unk00[4]; uint32_t n4; uint8_t unk08[4]; M2Item21 *itemsC; } M2Out21;
typedef struct M2Box21 { int32_t n0; uint8_t unk04[0x2C]; uint8_t grp30[1]; } M2Box21;
typedef struct M2Grp21 { int32_t n0; } M2Grp21;
typedef struct M2Coll21 { uint8_t *w0; uint8_t unk04[8]; uint8_t *nodeC; } M2Coll21;
typedef struct M2Hit21 { uint8_t unk00[8]; M2Coll21 *owner8; int32_t idxC; } M2Hit21;
typedef struct M2Flt21 { uint32_t a, b; } M2Flt21;
extern M2Hit21 *a8c_buf3EC448[];
int   r6c_CollectBetween(void *ctx, const float *hi, const float *lo, M2Hit21 **out);
void  a80_PairInvalidate(M2Flt21 *f);
int   r6c_BoxBehind(const float *hi, const float *lo, const float *bhi, const float *blo);
int   sub_00080D40(M2Flt21 *f, M2Grp21 *g);
M2Grp21 *sub_00083CA0(M2Grp21 *g);
uint32_t sub_00083D20(M2Out21 *out, void *tri, const float *pos, float r);
void *sub_00083CF0(M2Grp21 *g, void *tri);

/* 0x822D0: gather the collision triangles near a sphere (pos, r) into out: take the hit list (or collect the hits inside the sphere box), and for every hit whose box overlaps walk its groups; groups the filter rejects (unless the world allows all) are skipped, others add their touching triangles, each tagged with its group. */
void m2_CollGather822D0(void *ctx, M2Out21 *out, float *pos, float r, M2Hit21 **lst, M2Flt21 *flt) {
    float lo[4], hi[4];
    M2Flt21 lf;
    M2Hit21 **pp;
    lo[0] = pos[0] - r; lo[1] = pos[1] - r;
    hi[0] = pos[0] + r + 0.01f; hi[1] = pos[1] + r + 0.01f; hi[2] = pos[2] + r + 0.01f;
    lo[2] = pos[2] - r;
    pos[3] = 1.0f; hi[3] = 1.0f; lo[3] = 1.0f;
    if (lst == 0) {
        r6c_CollectBetween(ctx, hi, lo, a8c_buf3EC448);
        lst = a8c_buf3EC448;
    }
    if (flt == 0) {
        flt = &lf;
        a80_PairInvalidate(&lf);
    }
    for (pp = lst; *pp != 0; pp++) {
        M2Hit21 *h = *pp;
        uint32_t wflags = *(uint32_t *)(h->owner8->w0 + 0x30);
        M2Box21 *b = (M2Box21 *)(h->owner8->nodeC + *(int32_t *)(h->owner8->nodeC + h->idxC * 0x50 + 0x28));
        int j;
        M2Grp21 *g;
        if (r6c_BoxBehind(hi, lo, (float *)((uint8_t *)b + 0x20), (float *)((uint8_t *)b + 0x10)) == 0) continue;
        g = (M2Grp21 *)b->grp30;
        for (j = 0; j < b->n0; j++) {
            if (sub_00080D40(flt, g) == 0 && !(wflags & 1)) {
                g = sub_00083CA0(g);
            } else {
                void *t = (uint8_t *)g + 0x60;
                int k;
                for (k = 0; k < g->n0; k++) {
                    uint32_t c = sub_00083D20(out, t, pos, r), m;
                    uint32_t volatile z = 0;
                    if (c > z) {
                        m = 0;
                        do { out->itemsC[out->n4 + m].grp50 = g; } while (++m < c);
                    }
                    out->n4 += c;
                    t = sub_00083CF0(g, t);
                }
                g = (M2Grp21 *)t;
            }
        }
    }
}

void a3c_VecCopy(float *d, const float *s);
void sub_00082750(float *hi, float *lo);
int  sub_000807C0(const float *bhi, const float *blo, const float *p0, const float *p1);
uint32_t sub_000845D0(M2Out21 *out, void *tri, const float *p0, const float *p1);

/* 0x824F0: same as 0x822D0 for a segment p0..p1: the search box is the segment's bounds (+0.01), boxes are tested against the segment (0x807C0) and triangles gathered by 0x845D0. */
void m2_CollGatherSeg824F0(void *ctx, M2Out21 *out, float *p0, float *p1, M2Hit21 **lst, M2Flt21 *flt) {
    float hi[4], lo[4];
    M2Flt21 lf;
    M2Hit21 **pp;
    p0[3] = 1.0f;
    p1[3] = 1.0f;
    a3c_VecCopy(hi, p0);
    a3c_VecCopy(lo, p1);
    sub_00082750(hi, lo);
    hi[0] += 0.01f; hi[1] += 0.01f; hi[2] += 0.01f;
    if (lst == 0) {
        r6c_CollectBetween(ctx, hi, lo, a8c_buf3EC448);
        lst = a8c_buf3EC448;
    }
    if (flt == 0) {
        flt = &lf;
        a80_PairInvalidate(&lf);
    }
    for (pp = lst; *pp != 0; pp++) {
        M2Hit21 *h = *pp;
        uint32_t wflags = *(uint32_t *)(h->owner8->w0 + 0x30);
        M2Box21 *b = (M2Box21 *)(h->owner8->nodeC + *(int32_t *)(h->owner8->nodeC + h->idxC * 0x50 + 0x28));
        int j;
        M2Grp21 *g;
        if (sub_000807C0((float *)((uint8_t *)b + 0x20), (float *)((uint8_t *)b + 0x10), p0, p1) == 0) continue;
        g = (M2Grp21 *)b->grp30;
        for (j = 0; j < b->n0; j++) {
            if (sub_00080D40(flt, g) == 0 && !(wflags & 1)) {
                g = sub_00083CA0(g);
            } else {
                void *t = (uint8_t *)g + 0x60;
                int k;
                for (k = 0; k < g->n0; k++) {
                    uint32_t c = sub_000845D0(out, t, p0, p1), m;
                    uint32_t volatile z = 0;
                    if (c > z) {
                        m = 0;
                        do { out->itemsC[out->n4 + m].grp50 = g; } while (++m < c);
                    }
                    out->n4 += c;
                    t = sub_00083CF0(g, t);
                }
                g = (M2Grp21 *)t;
            }
        }
    }
}
