/* Area m1, file 268: texture scroll. Names inferred. */
#include <stdint.h>

typedef struct M1Uv268 { uint8_t unk00[0x10]; float du10, dv14; uint8_t unk18[0x18]; int32_t kind30; uint32_t period34;
    float u38, v3C, phase40; } M1Uv268;

/* 0x00037830: scrolling-texture step for kind-2 layers: add the per-frame speeds to u and v and wrap both into
   0..1; with a period set, also advance the phase by 100 / period / 60 (skipped when that exceeds 1) and wrap it.
   regargs: s=EAX. */
void m1_UvScroll37830(M1Uv268 *s)
{
    float u, v, t, r;
    if (s->kind30 != 2) return;
    u = s->du10 + s->u38;
    v = s->dv14 + s->v3C;
    s->u38 = u;
    s->v3C = v;
    if (0.0f > u) s->u38 = u + 1.0f;
    if (0.0f > v) s->v3C = v + 1.0f;
    if (s->u38 > 1.0f) s->u38 = s->u38 - 1.0f;
    if (s->v3C > 1.0f) s->v3C = s->v3C - 1.0f;
    if (s->period34) {
        r = 0.0f;
        t = 100.0f / (float)s->period34 * 0.016666668f;
        if (!(t > 1.0f)) r = t;
        s->phase40 += r;
        if (s->phase40 > 1.0f) s->phase40 = s->phase40 - 1.0f;
    }
}
