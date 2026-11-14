/* Area m1, file 176: grade and misc (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Rec176 { int32_t n; uint8_t rest[0x14]; } M1Rec176;
extern M1Rec176 m1_scores4131C4[24];
extern uint8_t m1_bonus413430;

/* 0x4BE20: overall grade 0..4 from the 24 stage scores plus two bonus flags (0 if any stage is unplayed). */
int m1_Grade04BE20(void) {
    int n = 0; M1Rec176 *p; uint8_t f; volatile int k;
    for (p = m1_scores4131C4; (int32_t)p <= (int32_t)&m1_scores4131C4[23]; p++) {
        if (p->n < 0) return 0;
        n += p->n;
    }
    f = m1_bonus413430;
    if (f & 1) n++;
    if (f & 2) n++;
    k = n;
    if (k == 0x62) return 4;
    if (k >= 0x4A) return 3;
    if (k >= 0x30) return 2;
    return k >= 0x18;
}

typedef struct M1Pl176 { uint8_t unk00[0x64]; float y64; } M1Pl176;
typedef struct M1Cam176 { uint8_t unk00[0x8C]; M1Pl176 *o8C; uint8_t unk90[0x120]; float f1B0; } M1Cam176;
extern M1Cam176 *m1_scr3F6130;

/* 0x102950: camera height offset from the player's height (fixed near the ground). */
void m1_CamHeight102950(void) {
    M1Cam176 *s = m1_scr3F6130; M1Pl176 *a = s->o8C; volatile float k = 2.0f; volatile float m = -0.015625f;
    if (-64.0f > a->y64) { s->f1B0 = 6.19999981f; return; }
    s->f1B0 = a->y64 * m * k + 4.19999981f;
}
