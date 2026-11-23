/* Area m1, file 362: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_enemy.h"

/* 0x186470 takes the body in ebx and the AI in edi plus one stack argument; written here as ordinary parameters. */
void sub_00186470(M1Actor *o, M1EnemyAi *e, int variant);

/* 0x188360: enter the get-up state, variant 2 when the AI's reaction bit is set, else variant 1. */
void m1_AiGetUpPick188360(M1Actor *o, M1EnemyAi *e) {
    if (e->aiFlags & 1) { int volatile v1 = 2; sub_00186470(o, e, v1); return; }
    { int volatile v2 = 1; sub_00186470(o, e, v2); }
}
