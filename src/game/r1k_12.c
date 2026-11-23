/* Area r1k: title background star setup 0x00045C60. Names inferred. */
#include "r1k.h"

/* 0x00045C60: spawn all 32 title stars and stagger their lives evenly over the
   current stage's star life (stage 0x1B in mode 2), so they do not all fade at once.
   r1k_StarSpawn takes i in EBX; written as an ordinary parameter. */
void r1k_StarsInit(void)
{
    int kind = a30_g3DF9BC;
    int i;
    if (a30_g3DF9B8 == 2)
        kind = 0x1B;
    for (i = 0; i < 32; i++) {
        r1k_StarSpawn(i);
        R1K_STAR(i)->life = r1k_starDefs2C58E0[kind].life
                            / (float)r1k_starDefs2C58E0[kind].count * (float)i;
    }
}
