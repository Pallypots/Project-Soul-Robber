/* Area m1, file 19: record clears. Names inferred. */
#include <stdint.h>

typedef struct M1Fx {
    uint8_t unk00[0x14];
    int32_t f14;               /* +0x14 */
    int32_t f18;               /* +0x18 */
    int32_t slots1C[16];       /* +0x1C */
} M1Fx;
void sub_0005A400(M1Fx *f);

/* 0x00033710: resets an effect record: +0x14 = 0, +0x18 = -1, 0x5A400, then clears 16 slots. */
void m1_FxReset33710(M1Fx *f)
{
    int i;
    f->f14 = 0;
    f->f18 = -1;
    sub_0005A400(f);
    for (i = 0; i < 16; i++)
        f->slots1C[i] = 0;
}

typedef struct M1Big {
    uint8_t unk000[0x624];
    int32_t f624;              /* +0x624 */
    int32_t words628[32];      /* +0x628 */
} M1Big;

/* 0x000C44E0: clears +0x624 and the 32 words at +0x628. */
void m1_ClearWordsC44E0(M1Big *b)
{
    int i;
    b->f624 = 0;
    for (i = 0; i < 32; i++)
        b->words628[i] = 0;
}
