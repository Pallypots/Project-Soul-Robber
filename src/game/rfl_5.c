/* Area rfl, group 5: player-relative angles (0x000DE1B0). Names inferred. */
#include "rfl.h"

/* 0x000DE1B0: signed angle on the ground plane between the player's facing
   (-Z rotated by the player yaw) and the direction from the player to pos. */
float rfl_PlayerAngleTo(const float *pos)
{
    float fwd[4], to[4], c[4], m[16];
    float d;
    fwd[0] = 0.0f;
    fwd[1] = 0.0f;
    fwd[2] = -1.0f;
    fwd[3] = 0.0f;
    sub_001AD9F0(to, pos, rfl_playerObj->pos60);
    to[1] = 0.0f;
    sub_001AD7E0(to, to);
    to[3] = 1.0f;
    sub_001AD940(m);
    sub_001AD8E0(m, m, rfl_player.yaw108);
    sub_001AD9B0(fwd, m, fwd);
    fwd[1] = 0.0f;
    sub_001AD7E0(fwd, fwd);
    fwd[3] = 1.0f;
    d = sub_001AD9D0(to, fwd);
    if (d > 1.0f)
        d = 1.0f;
    else if (-1.0f > d)
        d = -1.0f;
    d = sub_001A3F20(d);
    sub_001ADA60(c, fwd, to);
    if (0.0f > c[1])
        d = 0.0f - d;
    return d;
}
