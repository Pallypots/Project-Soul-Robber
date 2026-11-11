/* Area r6j: actor 6 room cutscene (r6j_7). Names inferred. */
#include "r6j.h"

/* 0x000BA4C0: room cutscene for actor 6. Phase 10 reads the scene state
   (0x000DDF20); when its second value is 0 it starts camera event 3 with a
   camera move, sets actor 6 flags 0x300000, stops the player (flags
   0x3800008) and gives actor 6 motion 2, else it gives motion 3 and ends
   (phase 0x63). Phase 11 waits for actor 6 (0x000A4370), then restores the
   camera, ends camera event 3, clears the actor flags, gives motion 3,
   releases the player (0x000D1930) and ends. Phase 0x63 clears the state
   and returns 0; mode 3 forces it. Returns 1. */
int r6j_RoomScriptActor6(int mode, R6jStep *st)
{
    int32_t a, b;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->count = 0;
        st->phase = 10;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x63;
    }
    st->count++;
    switch (st->phase) {
    case 10:
        sub_000DDF20(&a, &b);
        if (b == 0) {
            sub_00019000(ae0_obj3E1270, 3);
            sub_0001AB00(ae0_obj3E1270, 3, 2, 0, 1);
            sub_0019BE90(3);
            sub_000A2CA0(6, 0x300000);
            PlayerObj_SetFlags(&g_stats, 0x3800008, 0);
            sub_000A42F0(6, 2);
            st->phase++;
            return 1;
        }
        sub_000A42F0(6, 3);
        st->phase = 0x63;
        break;
    case 11:
        if (sub_000A4370(6) != 0) {
            sub_00019000(ae0_obj3E1270, 1);
            sub_0019BEB0(3);
            sub_000A2CC0(6, 0x300000);
            sub_000A42F0(6, 3);
            sub_000D1930(&g_stats);
            st->phase = 0x63;
            return 1;
        }
        break;
    case 0x63:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
