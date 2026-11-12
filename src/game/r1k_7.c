/* Area r1k, group 7: loading-screen star respawn 0x00058ED0 (separate
   file so cl does not inline it into the draw loop). Names inferred. */
#include "r1k.h"

/* 0x00058ED0: respawn field star i at a random position outside the
   central 100x100 square with a random velocity (vertical a quarter of
   horizontal) and the full life of the star parameters. regargs: i=EAX */
void r1k_FieldStarSpawn(int i)
{
    float sign;
    do {
        R1K_FSTAR(i)->x = (float)(sub_001C7EE1() % 512 - 256);
        R1K_FSTAR(i)->y = (float)(sub_001C7EE1() % 448 - 224);
    } while (R1K_FSTAR(i)->x >= -50.0f && R1K_FSTAR(i)->x <= 50.0f &&
             R1K_FSTAR(i)->y >= -50.0f && R1K_FSTAR(i)->y <= 50.0f);
    sign = (sub_001C7EE1() & 1) ? -1.0f : 1.0f;
    R1K_FSTAR(i)->vx = (float)(sub_001C7EE1() % r1k_starDef2DD1B8.speed)
                       * 0.00390625f * sign;
    sign = (sub_001C7EE1() & 1) ? -1.0f : 1.0f;
    R1K_FSTAR(i)->vy = (float)(sub_001C7EE1() % r1k_starDef2DD1B8.speed)
                       * 0.00390625f * sign * 0.25f;
    R1K_FSTAR(i)->life = r1k_starDef2DD1B8.life;
}
