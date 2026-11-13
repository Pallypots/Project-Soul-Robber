/* Area m1, file 38: GPU command block builder. Names inferred. */
#include <stdint.h>

extern uint32_t m1_colour2C453C[4];      /* 0x002C453C */
void sub_001ADA40(uint32_t *dst, const void *m);
void sub_001B1F70(uint32_t *dst, const void *m);

/* 0x0003A020: writes a fixed command block (two matrices from m, state words and the
 * colour at 0x2C453C) at p; returns the next free word. regargs: p=EAX m=EBX */
uint32_t *m1_EmitBlock3A020(uint32_t *p, const void *m)
{
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x11000000;
    p[4] = 0x10000008;
    p[5] = 0;
    p[6] = 0x1000101;
    p[7] = 0x6C08001B;
    sub_001ADA40(&p[8], m);
    sub_001B1F70(&p[0x18], m);
    p[0x29] = 0;
    p[0x28] = 0x10000000;
    p[0x2A] = 0x14000000;
    p[0x2B] = 0x11000000;
    p[0x2D] = 0;
    p[0x2C] = 0x10000001;
    p[0x2E] = 0x1000101;
    p[0x2F] = 0x30000000;
    p[0x33] = m1_colour2C453C[3];
    p[0x32] = m1_colour2C453C[2];
    p[0x31] = m1_colour2C453C[1];
    p[0x30] = m1_colour2C453C[0];
    return &p[0x34];
}

typedef struct M1Def34 { uint32_t w[0xD]; } M1Def34;
extern const M1Def34 m1_defaults2E4720[10];   /* 0x002E4720 */
extern M1Def34 m1_live3ED540[10];             /* 0x003ED540 */

/* 0x000A9EF0: restores the ten 0x34-byte records from their defaults. */
void m1_RestoreDefaultsA9EF0(void)
{
    m1_live3ED540[0] = m1_defaults2E4720[0];
    m1_live3ED540[1] = m1_defaults2E4720[1];
    m1_live3ED540[2] = m1_defaults2E4720[2];
    m1_live3ED540[3] = m1_defaults2E4720[3];
    m1_live3ED540[4] = m1_defaults2E4720[4];
    m1_live3ED540[5] = m1_defaults2E4720[5];
    m1_live3ED540[6] = m1_defaults2E4720[6];
    m1_live3ED540[7] = m1_defaults2E4720[7];
    m1_live3ED540[8] = m1_defaults2E4720[8];
    m1_live3ED540[9] = m1_defaults2E4720[9];
}
