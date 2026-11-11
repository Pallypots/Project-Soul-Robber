/* Area r6h: three-key curves (r6h_15). Names inferred. */
#include "r6h.h"

/* 0x000A32A0: set up the three curves of c (one per axis) with three keys
   each: key values a[i], b[i], c[i] for curve i at key times 0, 30 and 60,
   then prepare each curve (0x00061C50). */
void r6h_CurvesSet3(R6hCurves *cv, const float *a, const float *b, const float *c)
{
    sub_00062050(&cv->sl[0], cv->buf[0], 3);
    cv->sl[0].s[1][0] = a[0];
    cv->sl[0].s[1][1] = b[0];
    cv->sl[0].s[1][2] = c[0];
    cv->sl[0].s[0][0] = 0.0f;
    cv->sl[0].s[0][1] = 30.0f;
    cv->sl[0].s[0][2] = 60.0f;
    sub_00061C50(&cv->sl[0], 3);
    sub_00062050(&cv->sl[1], cv->buf[1], 3);
    cv->sl[1].s[1][0] = a[1];
    cv->sl[1].s[1][1] = b[1];
    cv->sl[1].s[1][2] = c[1];
    cv->sl[1].s[0][0] = 0.0f;
    cv->sl[1].s[0][1] = 30.0f;
    cv->sl[1].s[0][2] = 60.0f;
    sub_00061C50(&cv->sl[1], 3);
    sub_00062050(&cv->sl[2], cv->buf[2], 3);
    cv->sl[2].s[1][0] = a[2];
    cv->sl[2].s[1][1] = b[2];
    cv->sl[2].s[1][2] = c[2];
    cv->sl[2].s[0][0] = 0.0f;
    cv->sl[2].s[0][1] = 30.0f;
    cv->sl[2].s[0][2] = 60.0f;
    sub_00061C50(&cv->sl[2], 3);
}
