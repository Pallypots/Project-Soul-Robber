/* Area r6j: two-gate room scripts (r6j_11). Names inferred. */
#include "r6j.h"

#define HIT_BIT 0x10000000u

/* 0x000B0B00: room script for two pairs of gates (actors 0/1 and 2/3)
   with event flags 0x2C9/0x2CA. Phase 10: when flag 0x2C9 is set the first
   pair is shut (pose 0) and the script ends (0x14); otherwise it is opened
   (pose 2). Phase 11 needs flags 0x2BE and 0x2BF (else it ends): it stops
   the player and starts camera event 3 with a camera move. Phases 12..15
   then, a second or four seconds apart, swing and shut the first pair
   (setting flag 0x2C9) and the second pair (setting flag 0x2CA), restore
   the camera and player and end. Phase 0x14 clears the state and returns
   0 (mode 3 forces it). Returns 1. */
int r6j_RoomScriptGatePairs(int mode, R6jStep *st)
{
    int count;

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
        st->phase = 0x14;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0x2C9) != 0) {
            sub_000A2D40(0, 0x20);
            sub_000A2D40(1, 0x20);
            sub_000A2CC0(0, HIT_BIT);
            sub_000A2CC0(1, HIT_BIT);
            sub_000A42F0(0, 0);
            sub_000A42F0(1, 0);
            st->phase = 0x14;
            return 1;
        }
        sub_000A2D10(0, 0x20);
        sub_000A2D40(1, 0x20);
        sub_000A2CA0(0, HIT_BIT);
        sub_000A2CC0(1, HIT_BIT);
        sub_000A42F0(0, 2);
        sub_000A42F0(1, 2);
        st->phase++;
        return 1;
    case 11:
        if (sub_000D9A70(0x2BE) == 0 || sub_000D9A70(0x2BF) == 0) {
            st->phase = 0x14;
            return 1;
        }
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 2, 1);
        st->phase++;
        st->count = 0;
        break;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(0, 3);
        sub_000A42F0(1, 5);
        st->phase++;
        st->count = 0;
        return 1;
    case 13:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(0, 0x20);
        sub_000A2D40(1, 0x20);
        sub_000A2CC0(0, HIT_BIT);
        sub_000A2CC0(1, HIT_BIT);
        sub_000A42F0(0, 0);
        sub_000A42F0(1, 0);
        sub_000D9AB0(0x2C9);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 1, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 14:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(2, 3);
        st->phase++;   /* before the second call (0x000A42F0 only touches actor records) */
        st->count = 0;
        sub_000A42F0(3, 5);
        return 1;
    case 15:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(2, 0x20);
        sub_000A2D40(3, 0x20);
        sub_000A2CC0(2, HIT_BIT);
        sub_000A2CC0(3, HIT_BIT);
        sub_000A42F0(2, 0);
        sub_000A42F0(3, 0);
        sub_00019000(ae0_obj3E1270, 1);
        sub_000D9AB0(0x2CA);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B0F70: the room script of 0x000B0B00 for event flags 0x2CB/0x2CC
   (camera move 3 2 0 1 in phase 11). Room script for two pairs of gates
   (actors 0/1 and 2/3). Phase 10: when flag 0x2CB is set the first
   pair is shut (pose 0) and the script ends (0x14); otherwise it is opened
   (pose 2). Phase 11 needs flags 0x2BE and 0x2BF (else it ends): it stops
   the player and starts camera event 3 with a camera move. Phases 12..15
   then, a second or four seconds apart, swing and shut the first pair
   (setting flag 0x2CB) and the second pair (setting flag 0x2CC), restore
   the camera and player and end. Phase 0x14 clears the state and returns
   0 (mode 3 forces it). Returns 1. */
int r6j_RoomScriptGatePairs2(int mode, R6jStep *st)
{
    int count;

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
        st->phase = 0x14;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0x2CB) != 0) {
            sub_000A2D40(0, 0x20);
            sub_000A2D40(1, 0x20);
            sub_000A2CC0(0, HIT_BIT);
            sub_000A2CC0(1, HIT_BIT);
            sub_000A42F0(0, 0);
            sub_000A42F0(1, 0);
            st->phase = 0x14;
            return 1;
        }
        sub_000A2D10(0, 0x20);
        sub_000A2D40(1, 0x20);
        sub_000A2CA0(0, HIT_BIT);
        sub_000A2CC0(1, HIT_BIT);
        sub_000A42F0(0, 2);
        sub_000A42F0(1, 2);
        st->phase++;
        return 1;
    case 11:
        if (sub_000D9A70(0x2BE) == 0 || sub_000D9A70(0x2BF) == 0) {
            st->phase = 0x14;
            return 1;
        }
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 0, 1);
        st->phase++;
        st->count = 0;
        break;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(0, 3);
        sub_000A42F0(1, 5);
        st->phase++;
        st->count = 0;
        return 1;
    case 13:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(0, 0x20);
        sub_000A2D40(1, 0x20);
        sub_000A2CC0(0, HIT_BIT);
        sub_000A2CC0(1, HIT_BIT);
        sub_000A42F0(0, 0);
        sub_000A42F0(1, 0);
        sub_000D9AB0(0x2CB);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 1, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 14:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(2, 3);
        st->phase++;   /* before the second call (0x000A42F0 only touches actor records) */
        st->count = 0;
        sub_000A42F0(3, 5);
        return 1;
    case 15:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(2, 0x20);
        sub_000A2D40(3, 0x20);
        sub_000A2CC0(2, HIT_BIT);
        sub_000A2CC0(3, HIT_BIT);
        sub_000A42F0(2, 0);
        sub_000A42F0(3, 0);
        sub_00019000(ae0_obj3E1270, 1);
        sub_000D9AB0(0x2CC);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
