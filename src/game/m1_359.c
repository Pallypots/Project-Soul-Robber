/* Area m1, file 359: enemy idle entry. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Tm359 { uint8_t unk00[0x10]; int32_t i10; } M1Tm359;
M1Tm359 *sub_001133E0(void *e, int k);
int      sub_000A82C0(int a);


typedef struct M1Ob359 { uint8_t unk00[4]; int32_t i04; int32_t i08; } M1Ob359;
typedef struct M1Ai359 { uint8_t unk00[0x4C]; uint32_t f4C; } M1Ai359;
void sub_0011DD70(M1Ob359 *o, M1Ai359 *e);       /* regargs: o=ESI e=EDI */
void sub_001130F0(void *o, void *e, int k);
void sub_00119FF0(void *o, void *e, int k);
int  m1_AiGoto113040(void *o, void *e, int st);

/* 0x11DF80: enter the idle / alert state: mode 0 or 1 go to state 1 (mode 1 awake), mode 2
   to state 5 with flag 0x400; other modes return 0. Kind-2 enemies of type 3 or 4 also
   refresh their wake flag. Returns 1 when handled. */
int m1_AiEnterIdle11DF80(M1Ob359 *o, M1Ai359 *e, int mode) {
    int f, k;
    sub_0011DD70(o, e);
    switch (mode) {
    case 0:
        f = 0;
        k = 1;
        break;
    case 1:
        f = 1;
        k = 1;
        break;
    case 2:
        e->f4C |= 0x400;
        f = 0;
        k = 5;
        break;
    default:
        return 0;
    }
    if (o && o->i04 == 2 && (o->i08 == 3 || o->i08 == 4)) {
        sub_001130F0(o, e, f);
        sub_00119FF0(o, e, f);
    }
    m1_AiGoto113040(o, e, k);
    return 1;
}
