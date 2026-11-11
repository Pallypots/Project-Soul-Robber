/* Area r1h, group 11: save slot cursor 0x00054E90. Names inferred. */
#include "r1h.h"

/* 0x00054E90: one frame of the five-slot selection cursor. Up/down wrap
   the cursor and start the move animation (state 1, finished by
   0x000544F0); accept returns 1, except when saving over a used slot,
   which plays sound 4 and returns 0; cancel returns 2. After a choice the
   input is ignored for three frames. Returns 0 while nothing is chosen. */
int r1h_SlotSelect(void)
{
    uint32_t pressed, rep;
    int ret = 0;
    if (r1h_wait3E3984 > 0) {
        r1h_wait3E3984--;
        return 0;
    }
    pressed = sub_0004ECE0(0) | sub_0004ED20(0);
    rep = sub_0004ECF0(0) | sub_0004ED40(0);
    switch (r1h_state3E3F44) {
    case 0:
        if (rep & 0x1000) {
            r1h_state3E3F44 = 1;
            if (--r1h_slot3E3960 < 0)
                r1h_slot3E3960 = 4;
            sub_00048AF0(0);
            return 0;
        }
        if (rep & 0x4000) {
            if (++r1h_slot3E3960 >= 5)
                r1h_slot3E3960 = 0;
            r1h_state3E3F44 = 1;
            sub_00048AF0(0);
            return 0;
        }
        if (r1h_keys2C4AE8[0] & pressed) {
            if (r1h_mode3E3950 == 1 && r1h_save3E3934->used[r1h_slot3E3960]) {
                r1h_wait3E3984 = 3;
                sub_00048AF0(4);
                return 0;
            }
            r1h_wait3E3984 = 3;
            sub_00048AF0(1);
            return 1;
        }
        if (r1h_keys2C4AE8[1] & pressed) {
            ret = 2;
            sub_00048AF0(2);
        }
        break;
    case 1:
        if (sub_000544F0()) {
            r1h_state3E3F44 = 0;
            return 0;
        }
        break;
    }
    return ret;
}
