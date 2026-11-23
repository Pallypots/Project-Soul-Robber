/* Area m1, file 366: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_enemy.h"
#include "m1_enemy1.h"

/* 0x11F4F0: aim a first-type enemy (the AI arrives in eax and the angle in xmm0; written as ordinary parameters): hangs on an angle over 2*pi, then sets the aim flag, the aim distance and the angle. */
void m1_E1Aim11F4F0(M1EnemyAi *e, float angle, float dist) {
    M1Enemy1State *st = (M1Enemy1State *)e->st;
    if (!(6.28318548f >= angle)) for (;;) ;
    st->aiFlags |= 2;
    st->aimDist = dist;
    st->aimAngle = angle;
}

/* 0xE0CF0: voice bank for a costume slot: 0x27 for slot 4, 0x25 for every other slot. */
int m1_CostumeVoiceBank0E0CF0(int slot) {
    int volatile r = 0x25;
    switch (slot) {
    case 0: r = 0x25; break;
    case 1: r = 0x25; break;
    case 2: r = 0x25; break;
    case 3: r = 0x25; break;
    case 4: r = 0x27; break;
    case 5: r = 0x25; break;
    case 6: r = 0x25; break;
    }
    return r;
}
