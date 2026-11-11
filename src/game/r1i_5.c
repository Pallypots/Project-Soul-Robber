/* Area r1i, group 5: key curve set 0x00019030. Names inferred. */
#include "r1i.h"

/* 0x00019030: fill the ten curves of s from the keys of src (key times
   accumulate the following key's duration) and build each curve.
   Returns 0. */
int r1i_CurveSetBuild(R1iCurveSet *s, const R1iCurveSrc *src)
{
    const R1iCurveKey *k;
    float t = 0.0f;
    int i;
    s->count = src->count;
    for (i = 0; i < s->count; i++) {
        k = &src->key[i];
        s->ch[0].t[i] = t;
        s->ch[0].v[i] = k->a[0];
        s->ch[1].t[i] = t;
        s->ch[1].v[i] = k->a[1];
        s->ch[2].t[i] = t;
        s->ch[2].v[i] = k->a[2];
        s->ch[3].t[i] = t;
        s->ch[3].v[i] = k->b[0];
        s->ch[4].t[i] = t;
        s->ch[4].v[i] = k->b[1];
        s->ch[5].t[i] = t;
        s->ch[5].v[i] = k->b[2];
        s->ch[6].t[i] = t;
        s->ch[6].v[i] = k->c[0];
        s->ch[7].t[i] = t;
        s->ch[7].v[i] = k->c[1];
        s->ch[8].t[i] = t;
        s->ch[8].v[i] = k->c[2];
        s->ch[9].t[i] = t;
        s->ch[9].v[i] = k->d;
        t = k[1].dur + t;
    }
    sub_00061C50(&s->ch[0], s->count);
    sub_00061C50(&s->ch[1], s->count);
    sub_00061C50(&s->ch[2], s->count);
    sub_00061C50(&s->ch[3], s->count);
    sub_00061C50(&s->ch[4], s->count);
    sub_00061C50(&s->ch[5], s->count);
    sub_00061C50(&s->ch[6], s->count);
    sub_00061C50(&s->ch[7], s->count);
    sub_00061C50(&s->ch[8], s->count);
    sub_00061C50(&s->ch[9], s->count);
    return 0;
}
