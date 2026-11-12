/* Area m1, file 15: small state helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Clamp {
    uint8_t unk00[8];
    volatile int32_t state08;  /* +0x08 busy marker read by another thread (Hypothesis) */
    uint8_t unk0C[4];
    int32_t value10;           /* +0x10 */
    int32_t min14;             /* +0x14 */
    int32_t max18;             /* +0x18 */
} M1Clamp;

/* 0x0003EA40: sets value to v clamped to [min, max] and marks state 3. */
void m1_SetClamped3EA40(M1Clamp *c, int v)
{
    int lim;
    if (c == 0)
        return;
    c->state08 = 2;
    lim = c->min14;
    if (lim <= v) {
        lim = c->max18;
        if (lim >= v) {
            c->value10 = v;
            c->state08 = 3;
            return;
        }
    }
    c->value10 = lim;
    c->state08 = 3;
}

typedef struct M1Part80 {
    uint8_t unk00[0x80];
    float   vec80[4];          /* +0x80 */
} M1Part80;
typedef struct M1PartSet {
    uint8_t   unk000[8];
    int32_t   active08;        /* +0x08 */
    uint8_t   unk00C[0x12C - 0xC];
    M1Part80 *parts[8];        /* +0x12C */
} M1PartSet;
void sub_001ADAF0(float *out, const float *a, const float *b);

/* 0x000A23A0: when active, adds offset m to the vector at +0x80 of each of the 8 parts. */
void m1_OffsetParts_A23A0(M1PartSet *s, const float *m)
{
    int i;
    if (s->active08 != 1)
        return;
    for (i = 0; i < 8; i++) {
        if (s->parts[i] != 0)
            sub_001ADAF0(s->parts[i]->vec80, s->parts[i]->vec80, m);
    }
}
