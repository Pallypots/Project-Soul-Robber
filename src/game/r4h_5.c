/* Area r4h: effect record reset of the 0x00400390 family (r4h_5). Names inferred. */
#include "r4h.h"

/* 0x00191B30: clear the ten 0x4C-byte effect records at 0x00400390
   (no node, no actor, mode 3). No inputs. */
void r4h_FxResetB(void)
{
    int i;
    for (i = 0; i < 10; i++) {
        r4c_recs400390[i].obj = 0;
        r4c_recs400390[i].actor = 0;
        r4c_recs400390[i].f0C = 0.0f;
        r4c_recs400390[i].mode10 = 3;
        r4c_recs400390[i].h40 = 0;
    }
}
