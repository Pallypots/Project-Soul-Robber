/* Area m1, file 365: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_enemy.h"
#include "m1_enemy1.h"

int  sub_00145780(M1Actor *o, float range);
void sub_00113480(M1EnemyAi *e, int k);
int  sub_000833E0(void *anim);
/* 0x135A70 takes the body in esi and the AI in edi plus the next state; written as ordinary parameters. */
void r3_SetStateB2(M1Actor *o, M1EnemyAi *e, int next);

/* 0x137170: first-type recover: within 24 units cue the AI; when the anim ends go to the counter state (3 from the left, 5 otherwise) if countering is allowed, else to state 1. */
void m1_E1Recover137170(M1Actor *o, M1EnemyAi *e) {
    M1Enemy1State *st = (M1Enemy1State *)e->st;
    if (sub_00145780(o, 24.0f)) sub_00113480(e, 1);
    if (!sub_000833E0(o->anim)) return;
    if (st->reactFlags & 1) {
        if (st->reactByte < 0) { r3_SetStateB2(o, e, 3); return; }
        r3_SetStateB2(o, e, 5);
        return;
    }
    r3_SetStateB2(o, e, 1);
}
