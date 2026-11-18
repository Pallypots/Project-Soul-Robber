/* Area m1, file 222: per-phase dispatchers on the byte at 0x428F81. Names inferred. */
#include <stdint.h>

extern uint8_t a60_phase428F81;
void sub_00064FC0(void);
void sub_000639A0(void);
void sub_00063E00(void);
void sub_000642A0(void);
void sub_00068E50(void);
void sub_00068740(void);
void sub_00068A60(void);
void sub_00069D90(void);

/* 0x00065310: run the phase-0..3 handler (tail calls). */
void m1_PhaseRunA65310(void)
{
    switch (a60_phase428F81) {
    case 0: sub_00064FC0(); break;
    case 1: sub_000639A0(); break;
    case 2: sub_00063E00(); break;
    case 3: sub_000642A0(); break;
    }
}

/* 0x0006A2E0: run the phase handler for phases 0, 1, 3, 4 (phase 2 does nothing; tail calls). */
void m1_PhaseRunB6A2E0(void)
{
    switch (a60_phase428F81) {
    case 0: sub_00068E50(); break;
    case 1: sub_00068740(); break;
    case 3: sub_00068A60(); break;
    case 4: sub_00069D90(); break;
    }
}

/* 0x00146030: true for kinds 1-3, 5-11, 13, 32, 34, 35; false otherwise. */
int m1_KindFlag146030(int k)
{
    switch (k) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
    case 13: case 32: case 34: case 35:
        return 1;
    case 4: case 37: case 38: case 44:
        return 0;
    case 12: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: case 22:
    case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31: case 33:
    case 36: case 39: case 40: case 41: case 42: case 43: case 45:
        return 0;
    }
    return 0;
}

typedef struct M1K222 { int32_t a0; int32_t kind4; } M1K222;

/* 0x000EE5F0: map kind 2..9 to 4..11 (hang on any other kind). */
int m1_KindMapEE5F0(M1K222 *o)
{
    switch (o->kind4) {
    case 2: return 4;
    case 3: return 5;
    case 4: return 6;
    case 5: return 7;
    case 6: return 8;
    case 7: return 9;
    case 8: return 10;
    case 9: return 11;
    }
    for (;;) ;
}
