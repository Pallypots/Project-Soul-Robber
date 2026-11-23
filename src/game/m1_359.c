/* Area m1, file 359: enemy idle entry. Names inferred. Types come from m1_enemy.h. */
#include "m1_enemy.h"

void sub_0011DD70(M1Actor *o, M1EnemyAi *e);       /* regargs: o=ESI e=EDI */
void sub_001130F0(M1Actor *o, M1EnemyAi *e, int k);
void sub_00119FF0(M1Actor *o, M1EnemyAi *e, int k);

/* 0x11DF80: enter the idle / alert state: mode 0 or 1 go to state 1 (mode 1 awake), mode 2
   to state 5 with flag 0x400; other modes return 0. Kind-2 enemies of type 3 or 4 also
   refresh their wake flag. Returns 1 when handled. */
int m1_AiEnterIdle11DF80(M1Actor *o, M1EnemyAi *e, int mode) {
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
        e->ctlFlags |= 0x400;
        f = 0;
        k = 5;
        break;
    default:
        return 0;
    }
    if (o && o->kind == 2 && (o->subKind == 3 || o->subKind == 4)) {
        sub_001130F0(o, e, f);
        sub_00119FF0(o, e, f);
    }
    m1_AiGoto113040(o, e, k);
    return 1;
}
