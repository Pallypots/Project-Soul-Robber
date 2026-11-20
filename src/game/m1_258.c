/* Area m1, file 258: particle quad setup. Names inferred. */
#include <stdint.h>

typedef struct M1V258 { float v[4]; } M1V258;
void sub_000F5D40(M1V258 *d, const M1V258 *s);   /* copy a 4-float vector */

/* 0x001B52D0: write four 8-vector quad records to out from template src, one per corner: each record copies
   src[0..4] and src[5], with the corner's UV offset (+-0.5, corner order 0 1 3 2) and the corner's own
   position src[6 + corner]. Returns the end of the written block. regargs: out=EAX, src=EDI. */
M1V258 *m1_QuadCorners1B52D0(M1V258 *out, const M1V258 *src)
{
    M1V258 uv[4];
    int32_t order[4];
    int32_t i, k;
    uv[0].v[0] = -0.5f; uv[0].v[1] = 0.0f; uv[0].v[2] = -0.5f; uv[0].v[3] = 0.0f;
    uv[1].v[0] = 0.5f;  uv[1].v[1] = 0.0f; uv[1].v[2] = -0.5f; uv[1].v[3] = 0.0f;
    uv[2].v[0] = -0.5f; uv[2].v[1] = 0.0f; uv[2].v[2] = 0.5f;  uv[2].v[3] = 0.0f;
    uv[3].v[0] = 0.5f;  uv[3].v[1] = 0.0f; uv[3].v[2] = 0.5f;  uv[3].v[3] = 0.0f;
    order[0] = 0;
    order[1] = 1;
    order[2] = 3;
    order[3] = 2;
    for (i = 0; i < 4; i++) {
        sub_000F5D40(&out[0], &src[0]);
        sub_000F5D40(&out[1], &src[1]);
        sub_000F5D40(&out[2], &src[2]);
        sub_000F5D40(&out[3], &src[3]);
        sub_000F5D40(&out[4], &src[4]);
        k = order[i];
        sub_000F5D40(&out[5], &uv[k]);
        sub_000F5D40(&out[6], &src[5]);
        sub_000F5D40(&out[7], &src[*(volatile int32_t *)&order[i] + 6]);
        out += 8;
    }
    return out;
}

void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
float sub_001AD9D0(const float *a, const float *b);           /* dot */
void sub_001AD7E0(float *d, const float *s);                  /* normalise */
void sub_001ADBA0(float *d, const float *s, float k);          /* d = s * k */
void sub_001ADAF0(float *d, const float *a, const float *b);   /* d = a + b */
float sub_00082D70(const float *v);                           /* length */

/* 0x000D4F20: push-out vector. out = 0; take the direction from b to a and step from b along it by r (or by
   gap + 0.05 when r is within 0.05 of gap); if that point is further than gap from p, out is the direction
   from p to it scaled by the excess. regargs: a=EAX, out=ESI, b=EDI; stack args (p r gap). */
void m1_PushOutD4F20(const float *a, float *out, const float *b, const float *p, float r, float gap)
{
    float s;
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    out[2] = 0.0f;
    out[1] = 0.0f;
    out[0] = 0.0f;
    out[3] = 1.0f;
    sub_001AD9F0(v, a, b);
    if (sub_001AD9D0(v, v) > 0.0f) {
        if (r - gap > 0.05f)
            s = r;
        else
            s = gap + 0.05f;
        sub_001AD7E0(v, v);
        sub_001ADBA0(v, v, s);
        sub_001ADAF0(v, b, v);
        sub_001AD9F0(v, v, p);
        s = sub_00082D70(v) - gap;
        if (s > 0.0f) {
            sub_001AD7E0(v, v);
            sub_001ADBA0(out, v, s);
            out[3] = 1.0f;
        }
    }
}

/* 0x001ADEE0: build rotation matrix m from three axis vectors: each row is the negated, normalised axis
   (x, y, z), and the translation row is (0, 0, 0, 1). */
void m1_MatFromAxes1ADEE0(float *m, const float *ax, const float *ay, const float *az)
{
    float t[4];
    t[0] = ax[0] * -1.0f;
    t[1] = ax[1] * -1.0f;
    t[2] = ax[2] * -1.0f;
    t[3] = ax[3] * -1.0f;
    sub_001AD7E0(m, t);
    t[0] = ay[0] * -1.0f;
    t[1] = ay[1] * -1.0f;
    t[2] = ay[2] * -1.0f;
    t[3] = ay[3] * -1.0f;
    sub_001AD7E0(m + 4, t);
    t[0] = az[0] * -1.0f;
    t[1] = az[1] * -1.0f;
    t[2] = az[2] * -1.0f;
    t[3] = az[3] * -1.0f;
    sub_001AD7E0(m + 8, t);
    m[14] = 0.0f;
    m[13] = 0.0f;
    m[12] = 0.0f;
    m[15] = 1.0f;
}

typedef struct M1Spr258 { float x, y; uint8_t unk08[0x14]; float f1C, f20; uint8_t unk24[0x68]; uint32_t col8C;
    uint8_t unk90[0xC]; } M1Spr258;                                     /* 0x9C */
extern uint8_t m1_caption3F4870, m1_alpha3F488C;
extern int32_t m1_count3F4894;
extern M1Spr258 m1_cntSpr3F4898, m1_cntSpr3F4934;
extern const int32_t m1_cntCol317E60[4];
void sub_000150B0(M1Spr258 *s, int32_t frame);
void *sub_00017C00(void *dl, M1Spr258 *s);
void *sub_00017AE0(void *dl, M1Spr258 *s);
void sub_00014E80(M1Spr258 *s);
void *r1d_Fwd26910(void *dl, float x, float y, int32_t d, int32_t n, int32_t digits, int32_t col, float sx, float sy,
                   int32_t j);

/* 0x000E7F50: draw the held-item counter when caption bit 0 is set. Counts 0-3 show icon frame 7+n, growing as
   it fades in; larger counts show the icon and the number, colored by tier (90+, 60+, 30+, below 30).
   regargs: dl=EAX. */
void *m1_ItemCounterE7F50(void *dl)
{
    int32_t n, a, digits, tier;
    float s;
    if (!(m1_caption3F4870 & 1)) return dl;
    n = m1_count3F4894;
    if (n <= 3) {
        a = m1_alpha3F488C;
        m1_cntSpr3F4898.x = 0.0f;
        m1_cntSpr3F4898.y = 0.0f;
        s = (float)(0x80 - a) * 0.015625f + 2.0f;
        m1_cntSpr3F4898.f20 = s;
        m1_cntSpr3F4898.f1C = s;
        m1_cntSpr3F4898.col8C = ((uint32_t)a << 24) | 0x808080;
        sub_000150B0(&m1_cntSpr3F4898, n + 7);
        return sub_00017C00(dl, &m1_cntSpr3F4898);
    }
    m1_cntSpr3F4934.x = -80.0f;
    m1_cntSpr3F4934.y = -133.0f;
    dl = sub_00017AE0(dl, &m1_cntSpr3F4934);
    sub_00014E80(&m1_cntSpr3F4934);
    n = m1_count3F4894;
    if (n < 10)
        digits = 1;
    else
        digits = (n >= 100) + 2;
    if (n >= 90)
        tier = 0;
    else if (n >= 60)
        tier = 1;
    else
        tier = (n < 30) + 2;
    return r1d_Fwd26910(dl, -80.0f, -133.0f, 0, n, digits, m1_cntCol317E60[tier], 0.75f, 0.75f, 8);
}
