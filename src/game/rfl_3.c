/* Area rfl, group 3: facing angles and picks (0x00145820..0x00145E08). Names inferred. */
#include "rfl.h"

/* 0x00145820: signed angle on the ground plane between the actor's facing
   (its matrix row at part+0x20, scaled by -1) and the point (x, z). */
float rfl_FacingAngleXZ(RflActor *a, float x, float z)
{
    float to[4], fwd[4], c[4];
    float d;
    sub_001ADBA0(fwd, (const float *)(a->part20 + 0x20), -1.0f);
    fwd[3] = 0.0f;
    fwd[1] = 0.0f;
    sub_001AD7E0(fwd, fwd);
    to[0] = x - a->pos60[0];
    to[2] = z - a->pos60[2];
    to[3] = 0.0f;
    to[1] = 0.0f;
    sub_001AD7E0(to, to);
    d = sub_001AD9D0(fwd, to);
    if (!(-1.0f < d))
        return 3.14159274f;
    if (d >= 1.0f)
        return 0.0f;
    d = sub_001A3F20(d);
    sub_001ADA60(c, fwd, to);
    if (0.0f > c[1])
        d = 0.0f - d;
    return d;
}

/* 0x00145B60: signed angle on the ground plane between +Z and dir. */
float rfl_AngleFromZ(const float *dir)
{
    float v[4], z[4];
    float d;
    z[0] = 0.0f;
    z[1] = 0.0f;
    z[2] = 1.0f;
    z[3] = 0.0f;
    sub_000F5D40(v, dir);
    v[3] = 0.0f;
    v[1] = 0.0f;
    sub_001AD7E0(v, v);
    d = sub_001AD9D0(z, v);
    if (!(-1.0f < d))
        return 3.14159274f;
    if (d >= 1.0f)
        return 0.0f;
    d = sub_001A3F20(d);
    sub_001ADA60(v, z, v);
    if (0.0f > v[1])
        d = 0.0f - d;
    return d;
}

/* 0x00145DA0: run the pick query at pos and return the distance to the hit
   (copying the 0x60-byte hit record to out when given); -1 when nothing was
   hit. */
float rfl_PickDistance(const float *pos, int b, int c, int d, void *out)
{
    void *pool = r1b_Pool80970();
    uint8_t *hit;
    sub_000824F0(rfl_ctx->v54, pool, pos, b, c, d);
    hit = sub_00080CB0(pool, pos, b);
    if (!hit)
        return -1.0f;
    if (out)
        memcpy(out, hit, 0x60);
    return r4_Distance(pos, (const float *)(hit + 0x40));
}

/* 0x00145AA0: rotate matrix m by angle about axis (through a quaternion),
   keeping its translation; the result goes to dst. */
void rfl_MtxRotateAxis(float *dst, float *m, const float *axis, float angle)
{
    float q[4], t[4], r[16];
    float s, c;
    angle *= 0.5f;
    s = sub_001A3ED0(angle);
    c = sub_001A3EE0(angle);
    sub_001ADBA0(q, axis, s);
    q[3] = c;
    sub_001A8830(r, q);
    sub_000F5D40(t, &m[12]);
    m[14] = 0.0f;
    m[13] = 0.0f;
    m[12] = 0.0f;
    sub_001AD7C0(dst, r, m);
    sub_000F5D40(&m[12], t);
    sub_000F5D40(&dst[12], t);
}

/* 0x00145CD0: dst = normalised v scaled by k when v is not (almost) zero
   and its dot with the normalised copy exceeds k; (0, 0, 0, 1) for a zero
   vector. Sets v[3] to 1. */
void rfl_VecScaledDir(float *dst, float *v, float k)
{
    float n[4];
    if (sub_001A3F30(v[0]) < 0.0001f && sub_001A3F30(v[1]) < 0.0001f &&
        sub_001A3F30(v[2]) < 0.0001f) {
        dst[0] = 0.0f;
        dst[1] = 0.0f;
        dst[2] = 0.0f;
        dst[3] = 1.0f;
        return;
    }
    v[3] = 1.0f;
    sub_001AD7E0(n, v);
    if (!(k >= sub_001AD9D0(n, v)))
        sub_001ADBA0(dst, n, k);
}
