/* Area r4e: matrix inverse and screen projection helpers at 0x001AE060-0x001AE207 (r4e_24). Names inferred. */
#include "r4e.h"
#include <xmmintrin.h>

/* 0x001AE060: d = inverse of the rigid transform s (transpose the rotation, then move the
   translation back through it). Stack args (d s). */
void r4e_MatInverseRigid(R4dMat *d, const R4dMat *s)
{
    R4dMat m;
    float v[4];
    m = *s;
    m.m[3][2] = 0.0f;
    m.m[3][1] = 0.0f;
    m.m[3][0] = 0.0f;
    sub_001E4BC6(&m, &m);
    v[0] = s->m[3][0];
    v[1] = s->m[3][1];
    v[2] = s->m[3][2];
    v[3] = s->m[3][3];
    sub_001E4B2D(v, v, &m);
    {
        float x = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(v[0]), _mm_set_ss(-1.0f)));
        float y = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(v[1]), _mm_set_ss(-1.0f)));
        float z = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(v[2]), _mm_set_ss(-1.0f)));
        *d = m;
        d->m[3][0] += x;
        d->m[3][1] += y;
        d->m[3][2] += z;
    }
}

#define MM(a, b) _mm_mul_ss((a), _mm_set_ss(b))
#define T(x) _mm_cvttss_si32(x)

/* 0x001AE140: project the point p through the current view-projection matrix into
   fixed-point screen coordinates out[0..3]. Stack args (out p). */
void r4e_ProjectToScreen(int32_t *out, const float *p)
{
    float v[4];
    R4dMat m;
    float w;
    __m128 iv;
    sub_001A73F0(&m);
    sub_001E4B2D(v, p, &m);
    w = v[3];
    iv = _mm_set_ss(1.0f / w);
    out[0] = 0x8000 - T(MM(_mm_mul_ss(MM(_mm_set_ss(v[0]), 320.0f), iv), -12.8f));
    out[1] = 0x8000 - T(MM(_mm_mul_ss(MM(_mm_set_ss(v[1]), -240.0f), iv), -6.4f));
    out[2] = T(MM(_mm_mul_ss(MM(_mm_set_ss(v[2]), 16770000.0f), iv), 16.0f));
    out[3] = T(MM(_mm_mul_ss(MM(_mm_set_ss(w), 0.0f), iv), 16.0f));
}
