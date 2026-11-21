/* Area m1, file 283: direction classing. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Dc283 { uint8_t unk00[0xFC]; void *tFC; uint8_t unk100[0xE0]; float dir1E0[4]; } M1Dc283;
float sub_000CCA40(M1Dc283 *o, void *t);                      /* bearing to the target */
void sub_00082A30(float *d, const float *a, const float *v);   /* rotate v by angle *a about Y */
void sub_000F5D40(float *d, const float *s);

/* 0x000CD300: class the bearing from o to its target (negated, wrapped into -pi..pi) as 0 front (within 30
   degrees), 1 behind (beyond 150), 2 or 3 for the two sides; also store the matching facing vector at 0x1E0.
   regargs: o=EAX. */
int32_t m1_BearingClassCD300(M1Dc283 *o)
{
    float a, fwd[4], z[4];
    z[0] = 0.0f;
    z[1] = 0.0f;
    z[2] = 0.0f;
    z[3] = 1.0f;
    fwd[2] = -1.0f;
    fwd[0] = 0.0f;
    fwd[1] = 0.0f;
    fwd[3] = 1.0f;
    (void)z;
    a = sub_000CCA40(o, o->tFC) * -1.0f;
    if (a > 3.1415927f) a -= 6.2831855f;
    if (-3.1415927f > a) a += 6.2831855f;
    sub_00082A30(fwd, &a, fwd);
    sub_000F5D40(o->dir1E0, fwd);
    if (a >= 0.0f) {
        if (0.5235988f > a) return 0;
        if (2.6179938f > a) return 2;
        return 1;
    }
    if (a > -0.5235988f) return 0;
    if (a > -2.6179938f) return 3;
    return 1;
}

typedef struct M1Ez283 { uint8_t unk00[0x3F0]; float on3F0, t3F4; float to3F8[4]; } M1Ez283;
extern float m1_frameRate42C85C;
void sub_000390A0(void);                                      /* uses the caller's registers */

/* 0x000E1CD0: ease value v toward s's target over the remaining time: each step moves it by the remaining
   fraction; when time runs out it snaps to the target and the ease is switched off (-1). Inactive while
   s->on3F0 is negative. regargs: s=ESI, v=EAX. */
void m1_EaseToE1CD0(M1Ez283 *s, float *v)
{
    float t, n, k;
    sub_000390A0();
    t = s->t3F4;
    n = t - m1_frameRate42C85C;
    if (!(s->on3F0 >= 0.0f)) return;
    if (t > 0.0f && n > 0.0f) {
        k = 1.0f / t;
        v[0] = (v[0] - s->to3F8[0]) * k * n + s->to3F8[0];
        v[1] = (v[1] - s->to3F8[1]) * k * n + s->to3F8[1];
        v[2] = (v[2] - s->to3F8[2]) * k * n + s->to3F8[2];
        v[3] = (v[3] - s->to3F8[3]) * k * n + s->to3F8[3];
        s->t3F4 = s->t3F4 - m1_frameRate42C85C;
        return;
    }
    ((int32_t *)v)[0] = ((int32_t *)s->to3F8)[0];
    ((int32_t *)v)[1] = ((int32_t *)s->to3F8)[1];
    ((int32_t *)v)[2] = ((int32_t *)s->to3F8)[2];
    ((int32_t *)v)[3] = ((int32_t *)s->to3F8)[3];
    s->on3F0 = -1.0f;
    s->t3F4 = -1.0f;
}
