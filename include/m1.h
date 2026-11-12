/* Area m1: functions recovered directly (no helper). Names inferred. */
#ifndef M1_H
#define M1_H
#include "oogie.h"
#include "shared_decls.h"

typedef struct M1Fade {
    uint16_t on;        /* +0 */
    uint16_t mode;      /* +2 */
    uint8_t  b4, b5;    /* +4, +5 */
    uint16_t w6;        /* +6 */
    uint8_t  unk08[4];
    float    time;      /* +0xC */
} M1Fade;

void sub_00072DD0(M1Fade *f, int mode, float time, int arg);
void m1_FadeStart72EE0(M1Fade *f, int mode, float time, int arg);   /* 0x00072EE0 */
int  sub_00052A10(void);
void m1_PathOp53D70(const char *name);                        /* 0x00053D70 */
#endif
