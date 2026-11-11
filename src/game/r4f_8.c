/* Area r4f: pad selection at 0x001A8980 (r4f_8). Names inferred. */
#include "r4f.h"

/* 0x001A8980: the selected pad, choosing one if none is: in mode 1 the previous pad or
   any open pad holding button 0x10, in mode 2 the previous pad if still open, otherwise
   any open pad holding the button. Returns the pad or -1. No inputs. */
int r4f_PadPickActive(void)
{
    int i;
    if (r4d_padSel3650C8 != -1)
        return r4d_padSel3650C8;
    switch (r4f_padMode40BE18) {
    case 1:
        for (i = 0; i < 4; i++) {
            if (r4f_padView40B9A8[i].hD0 &&
                (i == aac_g3650CC || (r4f_padView40B9A8[i].flags48 & 0x10)))
                goto found;
        }
        return -1;
    case 2:
        for (i = 0; i < 4; i++) {
            if (r4f_padView40B9A8[i].hD0 && i == aac_g3650CC)
                goto found;
        }
        return -1;
    default:
        for (i = 0; i < 4; i++) {
            if (r4f_padView40B9A8[i].hD0 && (r4f_padView40B9A8[i].flags48 & 0x10))
                goto found;
        }
        return -1;
    }
found:
    aac_g3650CC = -1;
    r4d_padSel3650C8 = i;
    return i;
}


