/* Area rbh: game functions in 0x000D0000..0x000DFFFF (rbh_9). Names inferred. */
#include "rbh.h"

/* 0x000DDF40: apply a pending room entry. Locked (-2) values clear the request. A negative
   room or entry is looked up from the current chapter and stage in the warp map (entry 0).
   Every room record with the pending id places Jack at its matching entry point, facing its
   yaw, with zero velocity and the idle animation. The request is cleared afterwards. */
void rbh_EnterRoom0DDF40(void)
{
    int32_t chapter, stage;
    const RbhWarpMap *m;
    int entry, i, j;

    if (adc_var3EDCCC == -2 || adc_var3EDCD0 == -2) {
        adc_var3EDCCC = -1;
        adc_var3EDCD0 = -1;
        return;
    }
    entry = adc_var3EDCD0;
    if (adc_var3EDCCC < 0 || entry < 0) {
        sub_000DFD40(&chapter, &stage);
        for (m = rbh_warpMap301038, i = 0; m->chapter > -1; m++, i++) {
            if (m->chapter == chapter && m->stage == stage) {
                adc_var3EDCCC = rbh_warpMap301038[i].room;
                adc_var3EDCD0 = 0;
                break;
            }
        }
        entry = adc_var3EDCD0;
    }
    if (adc_var3EDCCC == -1 || entry == -1)
        return;
    for (i = 0; rbh_rooms301428[i].id > -1; i++) {
        if (rbh_rooms301428[i].id != adc_var3EDCCC)
            continue;
        for (j = 0; rbh_rooms301428[i].entries[j].id > -1; j++) {
            if (rbh_rooms301428[i].entries[j].id == entry) {
                r2d_PlayerPlace(&g_stats, rbh_rooms301428[i].entries[j].pos);
                RBH_PLAYER->angle108 = r6c_AngleAdd(0.0f, rbh_rooms301428[i].entries[j].yaw14);
                RBH_PLAYER->angleFC = RBH_PLAYER->angle108;
                RBH_PLAYER->v110[2] = 0.0f;
                RBH_PLAYER->v110[1] = 0.0f;
                RBH_PLAYER->v110[0] = 0.0f;
                RBH_PLAYER->v110[3] = 1.0f;
                RBH_PLAYER->f14C = 0.0f;
                RBH_PLAYER->f148 = 0.0f;
                PlayerObj_SetAnim(&g_stats, 0);
                entry = adc_var3EDCD0;
                rbh_g3E14EC = -1;
                rbh_g3E14F4 = -1;
                break;
            }
        }
    }
    adc_var3EDCCC = -1;
}
