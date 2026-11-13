/* Area m1, file 46: radius test (kept apart so cl does not inline it). Names inferred. */
#include <stdint.h>
void sub_000F5D40(void *dst, const void *src);

typedef struct M1Rad14 {
    uint8_t  unk00[0x14];
    float    radius14;         /* +0x14 */
    uint8_t  unk18[0xD8 - 0x18];
    uint8_t *node0D8;          /* +0xD8 (+0x60 position) */
} M1Rad14;
float sub_00082D70(float *v);   /* length */
void  sub_001AD9F0(float *d, const float *a, const void *b);   /* d = a - b */

/* 0x000A8090: 1 if pos is within t's radius of t's node position, else -1. */
int m1_WithinRadiusA8090(void *tv, const float *pos)
{
    M1Rad14 *t = tv;
    float a[4], b[4], d[4];
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    a[0] = 0.0f; a[1] = 0.0f; a[2] = 0.0f; a[3] = 1.0f;
    b[0] = 0.0f; b[1] = 0.0f; b[2] = 0.0f; b[3] = 1.0f;
    sub_000F5D40(a, pos);
    sub_000F5D40(b, t->node0D8 + 0x60);
    sub_001AD9F0(d, a, b);
    if (t->radius14 > sub_00082D70(d))
        return 1;
    return -1;
}
