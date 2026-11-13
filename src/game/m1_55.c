/* Area m1, file 55: player state checks. Names inferred. */
#include <stdint.h>

typedef struct M1Act0C { uint8_t unk00[0xC]; uint32_t flags0C; uint8_t b10; } M1Act0C;
typedef struct M1PlEFC {
    uint8_t unk000[0xEFC];
    M1Act0C *actEFC;           /* +0xEFC */
    uint8_t unkF00[0xFAC - 0xF00];
    float   fFAC;              /* +0xFAC */
} M1PlEFC;

/* 0x000C9CE0: 1 when the current action (+0xEFC) is active (flag 1), not locked (flag
 * 0x10000, byte +0x10 bits 0x48) and +0xFAC is positive; else -1. */
int m1_ActionReady0C9CE0(M1PlEFC *p)
{
    M1Act0C *a = p->actEFC;
    if (a != 0 && (a->flags0C & 1) && !(a->flags0C & 0x10000) && !(a->b10 & 0x48) &&
        !(p->fFAC <= 0.0f))
        return 1;
    return -1;
}
