/* Area r2d, group 2: light set refresh (0x000D1750). Names inferred. */
#include "r2d.h"

/* 0x000D1750: reset the camera rig and switch on the light set for the
   current player mode (mode 0: rig reset plus lights 16..19 in area 4;
   mode 1: lights 0..3 and 8..12). */
void r2d_LightsRefresh(void)
{
    if (r2d_player.mode1B8 == 0) {
        r2d_RigClear((R2dRig *)g_42C8EC);
        r2d_RigSetAim((R2dRig *)g_42C8EC, 0, 0, -1.0f);
        ((R2dRig *)g_42C8EC)->flags |= 1;
        sub_000D51E0((R2dRig *)g_42C8EC);
        sub_001BA8F0(&r2d_lightSet);
        r2d_lightSet.flagsC0 |= 1;
        sub_000D5650();
        if (r2d_player.v140 == 4) {
            r2d_lights417938[16].flags |= 8;
            r2d_lights417938[17].flags |= 8;
            r2d_lights417938[18].flags |= 8;
            r2d_lights417938[19].flags |= 8;
        }
    } else if (r2d_player.mode1B8 == 1) {
        r2d_lights417938[0].flags |= 8;
        r2d_lights417938[1].flags |= 8;
        r2d_lights417938[2].flags |= 8;
        r2d_lights417938[3].flags |= 8;
        r2d_lights417938[8].flags |= 8;
        r2d_lights417938[9].flags |= 8;
        r2d_lights417938[10].flags |= 8;
        r2d_lights417938[11].flags |= 8;
        r2d_lights417938[12].flags |= 8;
    }
}
