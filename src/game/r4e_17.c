/* Area r4e: vector and matrix helpers around 0x001AD7E0-0x001AE055 (r4e_17). Names inferred. */
#include "r4e.h"

/* 0x001AD7E0: normalise the 3-vector in (w=0) into out; if the result is all zero,
   replace zero components by 1 and normalise again. Stack args (out in). */
void r4e_VecNormalize3(float *out, const float *in)
{
    float t[4];
    t[0] = in[0];
    t[1] = in[1];
    t[2] = in[2];
    t[3] = 0.0f;
    sub_001E51AB(out, t);
    if (out[0] != 0.0f || out[1] != 0.0f || out[2] != 0.0f || out[3] != 0.0f)
        return;
    if (t[0] == 0.0f)
        t[0] = 1.0f;
    if (t[1] == 0.0f)
        t[1] = 1.0f;
    if (t[2] == 0.0f)
        t[2] = 1.0f;
    sub_001E51AB(out, t);
}

/* 0x001AD940: set a 4x4 matrix to identity. Stack arg (m). */
void r4e_MatIdentity(float *m)
{
    m[14] = 0.0f;
    m[13] = 0.0f;
    m[12] = 0.0f;
    m[11] = 0.0f;
    m[9] = 0.0f;
    m[8] = 0.0f;
    m[7] = 0.0f;
    m[6] = 0.0f;
    m[4] = 0.0f;
    m[3] = 0.0f;
    m[2] = 0.0f;
    m[1] = 0.0f;
    m[15] = 1.0f;
    m[10] = 1.0f;
    m[5] = 1.0f;
    m[0] = 1.0f;
}

/* 0x001AD9F0: d = a - b (4 components). Stack args (d a b). */
void r4e_VecSub4(float *d, const float *a, const float *b)
{
    d[0] = a[0] - b[0];
    d[1] = a[1] - b[1];
    d[2] = a[2] - b[2];
    d[3] = a[3] - b[3];
}

/* 0x001ADA60: d = a x b with w = 0. Stack args (d a b). */
void r4e_VecCross3(R4eVec4 *d, const float *a, const float *b)
{
    R4eVec4 t;
    t.x = b[2] * a[1] - a[2] * b[1];
    t.y = a[2] * b[0] - b[2] * a[0];
    t.z = a[0] * b[1] - b[0] * a[1];
    t.w = 0.0f;
    *d = t;
}

/* 0x001ADAF0: d = a + b (4 components). Stack args (d a b). */
void r4e_VecAdd4(float *d, const float *a, const float *b)
{
    d[0] = a[0] + b[0];
    d[1] = a[1] + b[1];
    d[2] = a[2] + b[2];
    d[3] = a[3] + b[3];
}

/* 0x001ADBA0: d = s * k (4 components). Stack args (d s k). */
void r4e_VecScale4(float *d, const float *s, float k)
{
    d[0] = s[0] * k;
    d[1] = s[1] * k;
    d[2] = s[2] * k;
    d[3] = s[3] * k;
}

/* 0x001ADC60: d = b + (a - b) * t (4 components). Stack args (d a b t). */
void r4e_VecLerp4(float *d, const float *a, const float *b, float t)
{
    d[0] = (a[0] - b[0]) * t + b[0];
    d[1] = (a[1] - b[1]) * t + b[1];
    d[2] = (a[2] - b[2]) * t + b[2];
    d[3] = (a[3] - b[3]) * t + b[3];
}

/* 0x001ADCD0: d = b + (a - b) * t (3 components). Stack args (d a b t). */
void r4e_VecLerp3(float *d, const float *a, const float *b, float t)
{
    d[0] = (a[0] - b[0]) * t + b[0];
    d[1] = (a[1] - b[1]) * t + b[1];
    d[2] = (a[2] - b[2]) * t + b[2];
}

/* 0x001ADD30: clamp each component of v to [lo, hi]. Stack args (d v lo hi). */
void r4e_VecClamp4(R4eVec4 *d, const float *v, float lo, float hi)
{
    R4eVec4 t;
    t.x = (lo > v[0]) ? lo : (v[0] > hi) ? hi : v[0];
    t.y = (lo > v[1]) ? lo : (v[1] > hi) ? hi : v[1];
    t.z = (lo > v[2]) ? lo : (v[2] > hi) ? hi : v[2];
    t.w = (lo > v[3]) ? lo : (v[3] > hi) ? hi : v[3];
    *d = t;
}

/* 0x001ADE90: d = a * b componentwise (4 components). Stack args (d a b). */
void r4e_VecMul4(float *d, const float *a, const float *b)
{
    d[0] = a[0] * b[0];
    d[1] = a[1] * b[1];
    d[2] = a[2] * b[2];
    d[3] = a[3] * b[3];
}

/* 0x001AE010: d = s with t added to the translation row. Stack args (d s t). */
void r4e_MatCopyTranslate(R4dMat *d, const R4dMat *s, const float *t)
{
    *d = *s;
    d->m[3][0] += t[0];
    d->m[3][1] = t[1] + d->m[3][1];
    d->m[3][2] = t[2] + d->m[3][2];
}
