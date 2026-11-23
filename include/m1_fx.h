/* Shared types for area m1 effect/prop controllers (the second argument of prop state routines). */
#ifndef M1_FX_H
#define M1_FX_H
#include <stdint.h>

/* Prop / effect controller: a small state machine with a phase, a timer and a per-object state block. */
typedef struct M1PropCtl {
    uint8_t  unk00[0x54];
    int32_t  phase;         /* +0x54 */
    float    timer;         /* +0x58 */
    float    timer2;        /* +0x5C */
    uint8_t  unk60[0x6C - 0x60];
    int32_t  variant;       /* +0x6C */
    uint8_t  unk70[0x74 - 0x70];
    void    *st;            /* +0x74  per-prop state block */
} M1PropCtl;

#endif
