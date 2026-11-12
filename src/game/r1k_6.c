/* Area r1k, group 6: loading-screen star field draw 0x000592E0.
   Names inferred. */
#include "r1k.h"

/* 0x000592E0: move and draw every field star with the shared sprite:
   it grows as its life runs out and fades in and out along a sine of
   the remaining life; a star whose life reaches zero respawns. Returns
   the advanced command pointer. regargs: cmd=EDI */
void *r1k_FieldStarsDraw(void *cmd)
{
    int i;
    float v;
    R1K_FSPR()->mode = r1k_starDef2DD1B8.mode;
    for (i = 0; i < r1k_starDef2DD1B8.count; i++) {
        R1K_FSPR()->x = R1K_FSTAR(i)->x = R1K_FSTAR(i)->vx + R1K_FSTAR(i)->x;
        R1K_FSPR()->y = R1K_FSTAR(i)->y = R1K_FSTAR(i)->vy + R1K_FSTAR(i)->y;
        v = (480.0f - R1K_FSTAR(i)->life) / r1k_starDef2DD1B8.life
            * r1k_starDef2DD1B8.grow + 1.0f;
        R1K_FSPR()->sx = v;
        R1K_FSPR()->sy = v;
        R1K_FSPR()->color = ((uint32_t)(int)(sub_001A3ED0(180.0f / r1k_starDef2DD1B8.life
                                 * R1K_FSTAR(i)->life * 0.017453292f)
                             * r1k_starDef2DD1B8.alpha) << 24) | r1k_starDef2DD1B8.color;
        cmd = sub_00017C00(cmd, R1K_FSPR());
        a60_StepByFrame(&R1K_FSTAR(i)->life, 0);
        if (0.0f >= R1K_FSTAR(i)->life)
            r1k_FieldStarSpawn(i);
    }
    return cmd;
}
