/* Area rbi: three-key curve set-up shared by several enemy families (rbi_4). Names inferred. */
#include "rbi.h"

/* 0x0011FD80: set the three curves at work+0x184 of an enemy family from
   the start, middle and end vectors a, b and c (curve i animates component i).
   regargs: act=EAX b=EBX c=EDI, a on the stack */
void rbi_Curves11FD80(RbhComp *act, const float *a, const float *b, const float *c)
{
    RbiCurves *cv = &((RbiWorkCv184 *)act->work278)->cv;

    rbi_SetSlices62050(&cv->rec[0], cv->buf5C[0], 3);
    cv->rec[0].s[1][0] = a[0];
    cv->rec[0].s[1][1] = b[0];
    cv->rec[0].s[1][2] = c[0];
    cv->rec[0].s[0][0] = 0.0f;
    cv->rec[0].s[0][1] = 0.5f;
    cv->rec[0].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[0], 3);
    rbi_SetSlices62050(&cv->rec[1], cv->buf5C[1], 3);
    cv->rec[1].s[1][0] = a[1];
    cv->rec[1].s[1][1] = b[1];
    cv->rec[1].s[1][2] = c[1];
    cv->rec[1].s[0][0] = 0.0f;
    cv->rec[1].s[0][1] = 0.5f;
    cv->rec[1].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[1], 3);
    rbi_SetSlices62050(&cv->rec[2], cv->buf5C[2], 3);
    cv->rec[2].s[1][0] = a[2];
    cv->rec[2].s[1][1] = b[2];
    cv->rec[2].s[1][2] = c[2];
    cv->rec[2].s[0][0] = 0.0f;
    cv->rec[2].s[0][1] = 0.5f;
    cv->rec[2].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[2], 3);
}

/* 0x00147E90: set the three curves at work+0x88 of an enemy family from
   the start, middle and end vectors a, b and c (curve i animates component i).
   regargs: act=EAX b=EBX c=EDI, a on the stack */
void rbi_Curves147E90(RbhComp *act, const float *a, const float *b, const float *c)
{
    RbiCurvesS *cv = &((RbiWorkCv88 *)act->work278)->cv;

    rbi_SetSlices62050(&cv->rec[0], cv->buf5C[0], 3);
    cv->rec[0].s[1][0] = a[0];
    cv->rec[0].s[1][1] = b[0];
    cv->rec[0].s[1][2] = c[0];
    cv->rec[0].s[0][0] = 0.0f;
    cv->rec[0].s[0][1] = 0.5f;
    cv->rec[0].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[0], 3);
    rbi_SetSlices62050(&cv->rec[1], cv->buf5C[1], 3);
    cv->rec[1].s[1][0] = a[1];
    cv->rec[1].s[1][1] = b[1];
    cv->rec[1].s[1][2] = c[1];
    cv->rec[1].s[0][0] = 0.0f;
    cv->rec[1].s[0][1] = 0.5f;
    cv->rec[1].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[1], 3);
    rbi_SetSlices62050(&cv->rec[2], cv->buf5C[2], 3);
    cv->rec[2].s[1][0] = a[2];
    cv->rec[2].s[1][1] = b[2];
    cv->rec[2].s[1][2] = c[2];
    cv->rec[2].s[0][0] = 0.0f;
    cv->rec[2].s[0][1] = 0.5f;
    cv->rec[2].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[2], 3);
}

/* 0x00155E70: set the three curves at work+0x84 of an enemy family from
   the start, middle and end vectors a, b and c (curve i animates component i).
   regargs: act=EAX b=EBX c=EDI, a on the stack */
void rbi_Curves155E70(RbhComp *act, const float *a, const float *b, const float *c)
{
    RbiCurvesS *cv = &((RbiWorkCv84 *)act->work278)->cv;

    rbi_SetSlices62050(&cv->rec[0], cv->buf5C[0], 3);
    cv->rec[0].s[1][0] = a[0];
    cv->rec[0].s[1][1] = b[0];
    cv->rec[0].s[1][2] = c[0];
    cv->rec[0].s[0][0] = 0.0f;
    cv->rec[0].s[0][1] = 0.5f;
    cv->rec[0].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[0], 3);
    rbi_SetSlices62050(&cv->rec[1], cv->buf5C[1], 3);
    cv->rec[1].s[1][0] = a[1];
    cv->rec[1].s[1][1] = b[1];
    cv->rec[1].s[1][2] = c[1];
    cv->rec[1].s[0][0] = 0.0f;
    cv->rec[1].s[0][1] = 0.5f;
    cv->rec[1].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[1], 3);
    rbi_SetSlices62050(&cv->rec[2], cv->buf5C[2], 3);
    cv->rec[2].s[1][0] = a[2];
    cv->rec[2].s[1][1] = b[2];
    cv->rec[2].s[1][2] = c[2];
    cv->rec[2].s[0][0] = 0.0f;
    cv->rec[2].s[0][1] = 0.5f;
    cv->rec[2].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[2], 3);
}

/* 0x0012E390: set the three curves at work+0x10 of an enemy from a through b to c and pick
   the curve speed from the distance a..c: 1/30 per frame unit below 30 units, 1/35 below 50,
   else 1/40.
   regargs: act=EAX a=EBX c=EDI, b on the stack */
void rbi_Curves12E390(RbhComp *act, const float *a, const float *b, const float *c)
{
    RbiCurvesS *cv = &((RbiWorkCv10 *)act->work278)->cv;
    float d;

    rbi_SetSlices62050(&cv->rec[0], cv->buf5C[0], 3);
    cv->rec[0].s[1][0] = a[0];
    cv->rec[0].s[1][1] = b[0];
    cv->rec[0].s[1][2] = c[0];
    cv->rec[0].s[0][0] = 0.0f;
    cv->rec[0].s[0][1] = 0.5f;
    cv->rec[0].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[0], 3);
    rbi_SetSlices62050(&cv->rec[1], cv->buf5C[1], 3);
    cv->rec[1].s[1][0] = a[1];
    cv->rec[1].s[1][1] = b[1];
    cv->rec[1].s[1][2] = c[1];
    cv->rec[1].s[0][0] = 0.0f;
    cv->rec[1].s[0][1] = 0.5f;
    cv->rec[1].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[1], 3);
    rbi_SetSlices62050(&cv->rec[2], cv->buf5C[2], 3);
    cv->rec[2].s[1][0] = a[2];
    cv->rec[2].s[1][1] = b[2];
    cv->rec[2].s[1][2] = c[2];
    cv->rec[2].s[0][0] = 0.0f;
    cv->rec[2].s[0][1] = 0.5f;
    cv->rec[2].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[2], 3);
    cv->t54 = 0.0f;
    d = r4_Distance(a, c);
    if (30.0f > d)
        cv->rate58 = a50_frameUnits * 0.0333333351f;
    else if (50.0f > d)
        cv->rate58 = a50_frameUnits * 0.0285714287f;
    else
        cv->rate58 = a50_frameUnits * 0.025f;
}

/* 0x00135C60: set the three curves at work+0xC of an enemy from a through b to c and pick
   the curve speed from the distance a..c: 1/30 per frame unit below 30 units, 1/35 below 50,
   else 1/40.
   regargs: act=EAX a=EBX c=EDI, b on the stack */
void rbi_Curves135C60(RbhComp *act, const float *a, const float *b, const float *c)
{
    RbiCurvesS *cv = &((RbiWorkCvC *)act->work278)->cv;
    float d;

    rbi_SetSlices62050(&cv->rec[0], cv->buf5C[0], 3);
    cv->rec[0].s[1][0] = a[0];
    cv->rec[0].s[1][1] = b[0];
    cv->rec[0].s[1][2] = c[0];
    cv->rec[0].s[0][0] = 0.0f;
    cv->rec[0].s[0][1] = 0.5f;
    cv->rec[0].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[0], 3);
    rbi_SetSlices62050(&cv->rec[1], cv->buf5C[1], 3);
    cv->rec[1].s[1][0] = a[1];
    cv->rec[1].s[1][1] = b[1];
    cv->rec[1].s[1][2] = c[1];
    cv->rec[1].s[0][0] = 0.0f;
    cv->rec[1].s[0][1] = 0.5f;
    cv->rec[1].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[1], 3);
    rbi_SetSlices62050(&cv->rec[2], cv->buf5C[2], 3);
    cv->rec[2].s[1][0] = a[2];
    cv->rec[2].s[1][1] = b[2];
    cv->rec[2].s[1][2] = c[2];
    cv->rec[2].s[0][0] = 0.0f;
    cv->rec[2].s[0][1] = 0.5f;
    cv->rec[2].s[0][2] = 1.0f;
    rbi_Curve61C50(&cv->rec[2], 3);
    cv->t54 = 0.0f;
    d = r4_Distance(a, c);
    if (30.0f > d)
        cv->rate58 = a50_frameUnits * 0.0333333351f;
    else if (50.0f > d)
        cv->rate58 = a50_frameUnits * 0.0285714287f;
    else
        cv->rate58 = a50_frameUnits * 0.025f;
}
