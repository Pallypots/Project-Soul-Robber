/* Area r6j: door room scripts (r6j_12). Names inferred. */
#include "r6j.h"

#define HIT_BIT 0x10000000u

/* 0x000B28D0: room script for door actor 4 with event flags 0x2D5
   (door unlocked) and 0x2D9 (opened), plus flag 0x12A. Phase 10: with
   0x2D5 clear the door is shut and the script ends (0x14); once both
   0x2D9 is clear and 0x12A is set the door is armed (bit 0x20 and
   HIT_BIT set) and the script goes on; otherwise the door follows 0x12A
   (opened through 0x000A2DD0 while it is clear). Phase 11 stops the player
   and starts camera event 3 with camera move (3 2 1 1), then jumps to
   13. Phase 12 (not reached from 11) calls 0x000A2E10 after a second.
   Phase 13 opens the door (0x000A2DD0 mode 1); 14 after four seconds shuts
   it, restores camera and player, clears 0x2D5 and sets 0x2D9. Phase 0x14
   clears the state and returns 0 (mode 3 forces it). Returns 1. */
int r6j_RoomScriptDoor2D5(int mode, R6jStep *st)
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
        if (sub_000D9A70(0x2D5) != 0) {
            if (sub_000D9A70(0x2D9) == 0 && sub_000D9A70(0x12A) != 0) {
                sub_000A2D10(4, 0x20);
                sub_000A2CA0(4, HIT_BIT);
                st->phase++;
                return 1;
            }
            if (sub_000D9A70(0x12A) == 0) {
                sub_000A2D10(4, 0x20);
                sub_000A2DD0(4, 0, 0);
                sub_000A2CA0(4, HIT_BIT);
                return 1;
            }
            sub_000A2D40(4, 0x20);
            sub_000A2CC0(4, HIT_BIT);
            return 1;
        }
        sub_000A2D40(4, 0x20);
        sub_000A2CC0(4, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 11:
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 1, 1);
        st->count = 0;
        st->phase = 13;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A2E10(4, 0);
        st->phase++;
        st->count = 0;
        break;
    case 13:
        sub_000A2DD0(4, 1, 0);
        st->phase++;
        st->count = 0;
        return 1;
    case 14:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(4, 0x20);
        sub_000A2CC0(4, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        sub_000D9B30(0x2D5);
        sub_000D9AB0(0x2D9);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B2B70: room script for door actor 0 with event flags 0x2D6
   (door unlocked) and 0x2DA (opened), plus flag 0x12A. Phase 10: with
   0x2D6 clear the door is shut and the script ends (0x14); once both
   0x2DA is clear and 0x12A is set the door is armed (bit 0x20 and
   HIT_BIT set) and the script goes on; otherwise the door follows 0x12A
   (opened through 0x000A2DD0 while it is clear). Phase 11 stops the player
   and starts camera event 3 with camera move (3 2 0 1), then jumps to
   13. Phase 12 (not reached from 11) calls 0x000A2E10 after a second.
   Phase 13 opens the door (0x000A2DD0 mode 1); 14 after four seconds shuts
   it, restores camera and player, clears 0x2D6 and sets 0x2DA. Phase 0x14
   clears the state and returns 0 (mode 3 forces it). Returns 1. */
int r6j_RoomScriptDoor2D6(int mode, R6jStep *st)
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
        if (sub_000D9A70(0x2D6) != 0) {
            if (sub_000D9A70(0x2DA) == 0 && sub_000D9A70(0x12A) != 0) {
                sub_000A2D10(0, 0x20);
                sub_000A2CA0(0, HIT_BIT);
                st->phase++;
                return 1;
            }
            if (sub_000D9A70(0x12A) == 0) {
                sub_000A2D10(0, 0x20);
                sub_000A2DD0(0, 0, 0);
                sub_000A2CA0(0, HIT_BIT);
                return 1;
            }
            sub_000A2D40(0, 0x20);
            sub_000A2CC0(0, HIT_BIT);
            return 1;
        }
        sub_000A2D40(0, 0x20);
        sub_000A2CC0(0, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 11:
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 0, 1);
        st->count = 0;
        st->phase = 13;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A2E10(0, 0);
        st->phase++;
        st->count = 0;
        break;
    case 13:
        sub_000A2DD0(0, 1, 0);
        st->phase++;
        st->count = 0;
        return 1;
    case 14:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(0, 0x20);
        sub_000A2CC0(0, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        sub_000D9B30(0x2D6);
        sub_000D9AB0(0x2DA);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B2E10: room script for door actor 6 with event flags 0x2D8
   (door unlocked) and 0x2DC (opened), plus flag 0x12A. Phase 10: with
   0x2D8 clear the door is shut and the script ends (0x14); once both
   0x2DC is clear and 0x12A is set the door is armed (bit 0x20 and
   HIT_BIT set) and the script goes on; otherwise the door follows 0x12A
   (opened through 0x000A2DD0 while it is clear). Phase 11 stops the player
   and starts camera event 3 with camera move (3 2 0 1), then jumps to
   13. Phase 12 (not reached from 11) calls 0x000A2E10 after a second.
   Phase 13 opens the door (0x000A2DD0 mode 1); 14 after four seconds shuts
   it, restores camera and player, clears 0x2D8 and sets 0x2DC. Phase 0x14
   clears the state and returns 0 (mode 3 forces it). Returns 1. */
int r6j_RoomScriptDoor2D8(int mode, R6jStep *st)
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
        if (sub_000D9A70(0x2D8) != 0) {
            if (sub_000D9A70(0x2DC) == 0 && sub_000D9A70(0x12A) != 0) {
                sub_000A2D10(6, 0x20);
                sub_000A2CA0(6, HIT_BIT);
                st->phase++;
                return 1;
            }
            if (sub_000D9A70(0x12A) == 0) {
                sub_000A2D10(6, 0x20);
                sub_000A2DD0(6, 0, 0);
                sub_000A2CA0(6, HIT_BIT);
                return 1;
            }
            sub_000A2D40(6, 0x20);
            sub_000A2CC0(6, HIT_BIT);
            return 1;
        }
        sub_000A2D40(6, 0x20);
        sub_000A2CC0(6, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 11:
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 0, 1);
        st->count = 0;
        st->phase = 13;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A2E10(6, 0);
        st->phase++;
        st->count = 0;
        break;
    case 13:
        sub_000A2DD0(6, 1, 0);
        st->phase++;
        st->count = 0;
        return 1;
    case 14:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(6, 0x20);
        sub_000A2CC0(6, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        sub_000D9B30(0x2D8);
        sub_000D9AB0(0x2DC);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B30B0: room script for door actor 7 with event flags 0x2D7
   (door unlocked) and 0x2DB (opened), plus flag 0x12A. Phase 10: with
   0x2D7 clear the door is shut and the script ends (0x14); once both
   0x2DB is clear and 0x12A is set the door is armed (bit 0x20 and
   HIT_BIT set) and the script goes on; otherwise the door follows 0x12A
   (opened through 0x000A2DD0 while it is clear). Phase 11 stops the player
   and starts camera event 3 with camera move (3 2 3 1), then jumps to
   13. Phase 12 (not reached from 11) calls 0x000A2E10 after a second.
   Phase 13 opens the door (0x000A2DD0 mode 1); 14 after four seconds shuts
   it, restores camera and player, clears 0x2D7 and sets 0x2DB. Phase 0x14
   clears the state and returns 0 (mode 3 forces it). Returns 1. */
int r6j_RoomScriptDoor2D7(int mode, R6jStep *st)
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
        if (sub_000D9A70(0x2D7) != 0) {
            if (sub_000D9A70(0x2DB) == 0 && sub_000D9A70(0x12A) != 0) {
                sub_000A2D10(7, 0x20);
                sub_000A2CA0(7, HIT_BIT);
                st->phase++;
                return 1;
            }
            if (sub_000D9A70(0x12A) == 0) {
                sub_000A2D10(7, 0x20);
                sub_000A2DD0(7, 0, 0);
                sub_000A2CA0(7, HIT_BIT);
                return 1;
            }
            sub_000A2D40(7, 0x20);
            sub_000A2CC0(7, HIT_BIT);
            return 1;
        }
        sub_000A2D40(7, 0x20);
        sub_000A2CC0(7, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 11:
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 3, 1);
        st->count = 0;
        st->phase = 13;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A2E10(7, 0);
        st->phase++;
        st->count = 0;
        break;
    case 13:
        sub_000A2DD0(7, 1, 0);
        st->phase++;
        st->count = 0;
        return 1;
    case 14:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_000A2D40(7, 0x20);
        sub_000A2CC0(7, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        sub_000D9B30(0x2D7);
        sub_000D9AB0(0x2DB);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
