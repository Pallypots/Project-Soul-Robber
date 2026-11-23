/* Area m1, file 361: register-argument revisits (written with normal parameters). Names inferred. */
#include <stdint.h>
#include "m1_enemy.h"

extern M1Actor *g_playerObj;
extern float m1_turnStepA318C24;
extern float m1_turnStepB318C28;
/* 0x10A140 reads its target point in eax; written here as an ordinary parameter. */
float sub_0010A140(const float *target);
void  sub_000F09E0(M1Actor *o);

/* Twin turn helpers: turn toward the player by the signed angle, clamped to +/- step. */
#define M1_TURN_TO_PLAYER361(o, step) \
    float a = sub_0010A140(g_playerObj->pos); \
    if (a > (step)) a = (step); \
    if (0.0f - (step) > a) a = 0.0f - (step); \
    (o)->yaw += a;

/* 0xF23C0: turn toward the player, at most 1.5 degrees per call. */
void m1_TurnToPlayer0F23C0(M1Actor *o) { float k = m1_turnStepA318C24; M1_TURN_TO_PLAYER361(o, k) }

#pragma optimize("s", on)
/* 0xF24B0: turn toward the player, at most 2.5 degrees per call, then run the move step (0xF09E0). */
void m1_TurnToPlayerB0F24B0(M1Actor *o) { float k = m1_turnStepB318C28; M1_TURN_TO_PLAYER361(o, k) sub_000F09E0(o); }
#pragma optimize("", on)
