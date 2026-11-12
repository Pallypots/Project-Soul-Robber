/* Area r1k, group 3: title background star respawn 0x00040D20.
   Names inferred. */
#include "r1k.h"

/* 0x00040D20: respawn star i at a random position outside the central
   100x100 square, with a random velocity (sign chosen by a coin flip,
   vertical speed a quarter of horizontal) and the life of the current
   stage's star parameters (stage 0x1B in mode 2). regargs: i=EBX */
void r1k_StarSpawn(int i)
{
    int kind = a30_g3DF9BC;
    float sign;
    if (a30_g3DF9B8 == 2)
        kind = 0x1B;
    do {
        R1K_STAR(i)->x = (float)(sub_001C7EE1() % 512 - 256);
        R1K_STAR(i)->y = (float)(sub_001C7EE1() % 448 - 224);
    } while (R1K_STAR(i)->x >= -50.0f && R1K_STAR(i)->x <= 50.0f &&
             R1K_STAR(i)->y >= -50.0f && R1K_STAR(i)->y <= 50.0f);
    sign = (sub_001C7EE1() & 1) ? -1.0f : 1.0f;
    R1K_STAR(i)->vx = (float)(sub_001C7EE1() % r1k_starDefs2C58E0[0].speed)
                      * 0.00390625f * sign;
    sign = (sub_001C7EE1() & 1) ? -1.0f : 1.0f;
    R1K_STAR(i)->vy = (float)(sub_001C7EE1() % r1k_starDefs2C58E0[0].speed)
                      * 0.00390625f * sign * 0.25f;
    R1K_STAR(i)->life = r1k_starDefs2C58E0[kind].life;
}
