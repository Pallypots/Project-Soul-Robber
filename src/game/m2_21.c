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

typedef struct M2Stream21 { uint8_t unk00[0x10]; int32_t size10; uint8_t unk14[0xC]; } M2Stream21;
extern M2Stream21 m1_streams2C8900[0x21E];

/* 0x4F6B0: size of stream entry i; the original bounds test (i < 0 && i >= 0x21E) can never be true, so it always reads the table. */
int m2_StreamSize4F6B0(int i) {
    int volatile v = i;
    if (v < 0 && v >= 0x21E) return 0;
    return m1_streams2C8900[i].size10;
}

typedef struct M2Face21 { uint8_t unk00[0x10]; float a10[4]; float b20[4]; float n30[4]; float c40[4]; uint8_t unk50[0x10]; } M2Face21;
typedef struct M2FaceSet21 { uint8_t unk00[4]; uint32_t n4; uint8_t unk08[4]; M2Face21 *fC; } M2FaceSet21;
float r4_Distance(const float *a, const float *b);
void  rbj_VecSub(float *d, const float *a, const float *b);
float rbj_VecDot(const float *a, const float *b);
void  rbj_VecScale(float *d, const float *a, float s);

/* 0x80BD0: find the face whose centre is nearest to pos; when pos lies on its front side, swap its two edge vectors and flip its normal. Returns the face (0 when the set is empty). */
M2Face21 *m2_FaceNearest80BD0(M2FaceSet21 *s, float *pos) {
    float best = 10000000.0f, d, t[4], tmp[4];
    M2Face21 *f = s->fC, *bf = 0;
    uint32_t i;
    for (i = 0; i < s->n4; i++, f++) {
        d = r4_Distance(pos, f->c40);
        if (best > d) { best = d; bf = f; }
    }
    if (bf == 0) return 0;
    rbj_VecSub(t, bf->c40, pos);
    if (rbj_VecDot(t, bf->n30) > 0.0f) {
        a3c_VecCopy(tmp, bf->a10);
        a3c_VecCopy(bf->a10, bf->b20);
        a3c_VecCopy(bf->b20, tmp);
        rbj_VecScale(bf->n30, bf->n30, -1.0f);
    }
    return bf;
}

void sub_00082840(float *hi, float *lo, const float *a, const float *b);
void rbj_VecNormalize(float *d, const float *s);
void r4e_VecMul4(float *d, const float *a, const float *b);

/* 0x807C0: 1 when segment p0..p1 touches box (bhi, blo): its bounding box must overlap, then the segment is clipped to the box's two planes across its dominant axis and that clipped box must overlap too. Near-zero direction gives 0. */
int m2_SegBox807C0(const float *bhi, const float *blo, const float *p0, const float *p1) {
    float n[4], d[4], lo[4], hi[4];
    int k, a, b;
    float inv, sa, sb, t;
    sub_00082840(hi, lo, p0, p1);
    if (r6c_BoxBehind(bhi, blo, hi, lo) == 0) return 0;
    rbj_VecSub(d, p1, p0);
    d[3] = 1.0f;
    rbj_VecNormalize(n, d);
    if (9.9999997e-07f > rbj_VecDot(n, d)) return 0;
    r4e_VecMul4(n, n, d);
    n[3] = 1.0f;
    k = 0;
    if (n[1] > n[0]) k = 1;
    if (n[2] > n[k]) k = 2;
    a = (k + 1) % 3;
    b = (a + 1) % 3;
    inv = 1.0f / d[k];
    hi[k] = bhi[k];
    t = bhi[k] - p0[k];
    sa = d[a] * inv;
    hi[a] = sa * t + p0[a];
    sb = d[b] * inv;
    hi[b] = sb * t + p0[b];
    lo[k] = blo[k];
    t = blo[k] - p0[k];
    lo[a] = sa * t + p0[a];
    lo[b] = sb * t + p0[b];
    sub_00082840(hi, lo, hi, lo);
    return r6c_BoxBehind(bhi, blo, hi, lo) != 0;
}

typedef struct M2Place21 { void *p0; int8_t gate4; int8_t kind5; int8_t mode6; int8_t var7; int32_t bit8; void *argC; float pos10[3]; float yaw1C; } M2Place21;
typedef struct M2PlSlot21 { M2Place21 *rec0; int32_t done4; void *obj8; uint8_t unkC[4]; } M2PlSlot21;
typedef struct M2PlHdr21 { uint8_t unk00[8]; int32_t n8; } M2PlHdr21;
extern M2PlHdr21 *a80_g3ED1D4;
extern uint8_t *a80_g3ED1D0;
int   r2b_TestBit(int bit);
void *m1_VoiceStartA93F0(void *p, int k, void *arg, float *pos, float *rot);
void *sub_000A9440(void *p, int k, void *arg, float *pos, float *rot, float v);
void *m2_SpawnA93F0(void *p, int k, void *arg, float *pos, float *rot);

/* 0x85DE0: spawn every placed object whose gate flag (when gated) is set: at its position with yaw -yaw1C, mode 0 by its own kind, modes 1-2 by kind 4 or 5 (low bit of its kind), using the variant call when it has a variant number. Each slot remembers it was handled and the spawned object (unknown modes keep the previous object). */
void m2_SpawnPlaced85DE0(void) {
    float rot[4], pos[4];
    void *o = 0;
    int i;
    int off;
    if (a80_g3ED1D4 == 0 || a80_g3ED1D0 == 0) return;
    for (i = 0, off = 0; i < a80_g3ED1D4->n8; i++, off += 0x10) {
        M2PlSlot21 *s = (M2PlSlot21 *)(a80_g3ED1D0 + off);
        M2Place21 *r = s->rec0;
        int k;
        if (r->gate4 == 1 && r2b_TestBit(r->bit8) == 0) continue;
        pos[0] = r->pos10[0]; pos[1] = r->pos10[1]; pos[2] = r->pos10[2]; pos[3] = 1.0f;
        rot[0] = 0.0f;
        rot[1] = 0.0f - r->yaw1C;
        rot[2] = 0.0f; rot[3] = 0.0f;
        if (r->mode6 == 0) {
            if (r->var7 == 0) { o = m1_VoiceStartA93F0(r->p0, r->kind5, r->argC, pos, rot); goto mark; }
            k = r->kind5;
        } else if (r->mode6 == 1 || r->mode6 == 2) {
            if (r->var7 == 0) { o = m2_SpawnA93F0(r->p0, ((uint8_t)r->kind5 & 1) + 4, r->argC, pos, rot); goto mark; }
            k = ((uint8_t)r->kind5 & 1) + 4;
        } else goto mark;
        o = sub_000A9440(r->p0, k, r->argC, pos, rot, (float)r->var7);
    mark:
        s->done4 = 1;
        s->obj8 = o;
    }
}
