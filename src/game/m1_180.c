/* Area m1, file 180: curve helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Crv180 { int32_t unk0; int32_t kind4; float *v8; } M1Crv180;
extern int32_t m1_curveTbl2E020C[];

/* 0x7F0A0: negate every key's values after the first, key by key, stopping after the first key whose lead value is negative. */
int m1_CurveFlip07F0A0(M1Crv180 *c) {
    float *v; int i;
    if (c == 0 || (v = c->v8) == 0) return -1;
    for (;;) {
        for (i = 1; i < m1_curveTbl2E020C[c->kind4 * 5]; i++) v[i] *= -1.0f;
        if (0.0f > v[0]) break;
        v += m1_curveTbl2E020C[c->kind4 * 5];
    }
    return 0;
}
