/* Area r6j: lever room scripts (r6j_13). Names inferred. */
#include "r6j.h"

#define HIT_BIT 0x10000000u

/* 0x000AAEC0: room script for lever actor 1 (event flag 0xC8) and gate
   actor 9. Phase 10: with the flag already set the lever is put in pose 2,
   its model detached (actor flag 0x40), HIT_BIT cleared, the gate posed and
   its bit 0x80 cleared, and the script ends (0x14); otherwise the lever gets
   HIT_BIT and the script goes on. Phase 11 waits for the flag, then
   0x00087510, stops the player and starts camera event 3 with camera move
   (3 2 0 1). Phase 12 after a second gives the lever motion 1; 13 after
   four seconds calls 0x00087BA0, detaches the lever model, clears HIT_BIT,
   restores camera and player and ends. Phase 15 (not reached) detaches the
   model after two seconds. Mode 3 and phase 0x14 clear the state and
   return 0. Returns 1. */
int r6j_RoomScriptLeverC8(int mode, R6jStep *st)
{
    int count;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
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
        st->phase = 0;
        return 0;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0xC8) != 0) {
            sub_000A42F0(1, 2);
            sub_0001B3F0(aa0_slots[1].model120);
            aa0_slots[1].flags |= 0x40;
            sub_000A2CC0(1, HIT_BIT);
            sub_000A42F0(9, 2);
            sub_000A2CC0(9, 0x80);
            st->phase = 0x14;
            break;
        }
        sub_000A2CA0(1, HIT_BIT);
        st->phase++;
        return 1;
    case 11:
        if (sub_000D9A70(0xC8) == 0)
            break;
        a80_Set3ED238();
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 0, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(1, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 13:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_00087BA0();
        sub_0001B3F0(aa0_slots[1].model120);
        aa0_slots[1].flags |= 0x40;
        sub_000A2CC0(1, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 0x14;
        return 1;
    case 15:
        if (a50_framesPerSecond + a50_framesPerSecond > count)
            break;
        sub_0001B3F0(aa0_slots[1].model120);
        aa0_slots[1].flags |= 0x40;
        sub_000A2CC0(1, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000AB160: room script for lever actor 2 (event flag 0xC9) and gate
   actor 8. Phase 10: with the flag already set the lever is put in pose 2,
   its model detached (actor flag 0x40), HIT_BIT cleared, the gate posed and
   its bit 0x80 cleared, and the script ends (0x14); otherwise the lever gets
   HIT_BIT and the script goes on. Phase 11 waits for the flag, then
   0x00087510, stops the player and starts camera event 3 with camera move
   (3 2 2 1). Phase 12 after a second gives the lever motion 1; 13 after
   four seconds calls 0x00087BA0, detaches the lever model, clears HIT_BIT,
   restores camera and player and ends. Phase 15 (not reached) detaches the
   model after two seconds. Mode 3 and phase 0x14 clear the state and
   return 0. Returns 1. */
int r6j_RoomScriptLeverC9(int mode, R6jStep *st)
{
    int count;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
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
        st->phase = 0;
        return 0;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0xC9) != 0) {
            sub_000A42F0(2, 2);
            sub_0001B3F0(aa0_slots[2].model120);
            aa0_slots[2].flags |= 0x40;
            sub_000A2CC0(2, HIT_BIT);
            sub_000A42F0(8, 2);
            sub_000A2CC0(8, 0x80);
            st->phase = 0x14;
            break;
        }
        sub_000A2CA0(2, HIT_BIT);
        st->phase++;
        return 1;
    case 11:
        if (sub_000D9A70(0xC9) == 0)
            break;
        a80_Set3ED238();
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 2, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(2, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 13:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_00087BA0();
        sub_0001B3F0(aa0_slots[2].model120);
        aa0_slots[2].flags |= 0x40;
        sub_000A2CC0(2, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 0x14;
        return 1;
    case 15:
        if (a50_framesPerSecond + a50_framesPerSecond > count)
            break;
        sub_0001B3F0(aa0_slots[2].model120);
        aa0_slots[2].flags |= 0x40;
        sub_000A2CC0(2, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000AB720: room script for lever actor 4 (event flag 0xCB) and gate
   actor 11. Phase 10: with the flag already set the lever is put in pose 2,
   its model detached (actor flag 0x40), HIT_BIT cleared, the gate posed and
   its bit 0x80 cleared, and the script ends (0x14); otherwise the lever gets
   HIT_BIT and the script goes on. Phase 11 waits for the flag, then
   0x00087510, stops the player and starts camera event 3 with camera move
   (3 2 1 1). Phase 12 after a second gives the lever motion 1; 13 after
   four seconds calls 0x00087BA0, detaches the lever model, clears HIT_BIT,
   restores camera and player and ends. Phase 15 (not reached) detaches the
   model after two seconds. Mode 3 and phase 0x14 clear the state and
   return 0. Returns 1. */
int r6j_RoomScriptLeverCB(int mode, R6jStep *st)
{
    int count;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
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
        st->phase = 0;
        return 0;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0xCB) != 0) {
            sub_000A42F0(4, 2);
            sub_0001B3F0(aa0_slots[4].model120);
            aa0_slots[4].flags |= 0x40;
            sub_000A2CC0(4, HIT_BIT);
            sub_000A42F0(11, 2);
            sub_000A2CC0(11, 0x80);
            st->phase = 0x14;
            break;
        }
        sub_000A2CA0(4, HIT_BIT);
        st->phase++;
        return 1;
    case 11:
        if (sub_000D9A70(0xCB) == 0)
            break;
        a80_Set3ED238();
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 1, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(4, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 13:
        if (a50_framesPerSecond * 4.0f > (float)count)
            break;
        sub_00087BA0();
        sub_0001B3F0(aa0_slots[4].model120);
        aa0_slots[4].flags |= 0x40;
        sub_000A2CC0(4, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 0x14;
        return 1;
    case 15:
        if (a50_framesPerSecond + a50_framesPerSecond > count)
            break;
        sub_0001B3F0(aa0_slots[4].model120);
        aa0_slots[4].flags |= 0x40;
        sub_000A2CC0(4, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000AB400: the lever room script of 0x000AAEC0 for lever actor 3 (event
   flag 0xCA) and gate actor 0xA with camera move (3 2 4 1). Phase 13 is
   longer: after two seconds it sets event flag 0x21D once (with
   0x00087520(5)); exactly at five seconds it shakes the screen for one
   second (0x00019350) and calls 0x000AA2E0(0xC); after seven seconds it
   detaches the lever model, restores camera and player and ends. The
   time sums are kept in float variables (single precision like the
   original SSE code). Returns 1. */
int r6j_RoomScriptLeverCA(int mode, R6jStep *st)
{
    int count;
    float fps;
    float t;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
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
        st->phase = 0;
        return 0;
    }
    count = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0xCA) != 0) {
            sub_000A42F0(3, 2);
            sub_0001B3F0(aa0_slots[3].model120);
            aa0_slots[3].flags |= 0x40;
            sub_000A2CC0(3, HIT_BIT);
            sub_000A42F0(0xA, 2);
            sub_000A2CC0(0xA, 0x80);
            st->phase = 0x14;
            break;
        }
        sub_000A2CA0(3, HIT_BIT);
        st->phase++;
        return 1;
    case 11:
        if (sub_000D9A70(0xCA) == 0)
            break;
        a80_Set3ED238();
        PlayerObj_SetFlags(&g_stats, 2, 0);
        sub_000D1D00(&g_stats);
        sub_0019BE90(3);
        sub_00019000(ae0_obj3E1270, 3);
        sub_0001AB00(ae0_obj3E1270, 3, 2, 4, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 12:
        if (a50_framesPerSecond > (float)count)
            break;
        sub_000A42F0(3, 1);
        st->phase++;
        st->count = 0;
        return 1;
    case 13:
        fps = a50_framesPerSecond;
        if ((float)count > fps * 2.0f) {
            if (sub_000D9A70(0x21D) == 0) {
                sub_000D9AB0(0x21D);
                a80_Set3ED23C(5);
            }
            fps = a50_framesPerSecond;
        }
        t = fps * 3.0f;
        t += fps * 2.0f;
        if ((float)st->count == t) {
            sub_00019350(R6J_FTOI(fps), 1.0f);
            sub_000AA2E0(0xC);
            fps = a50_framesPerSecond;
        }
        if (fps * 7.0f > (float)st->count)
            break;
        sub_0001B3F0(aa0_slots[3].model120);
        aa0_slots[3].flags |= 0x40;
        sub_000A2CC0(3, HIT_BIT);
        sub_00019000(ae0_obj3E1270, 1);
        PlayerObj_ClearFlags22(&g_stats);
        PlayerObj_ClearFlags(&g_stats, 2, 0);
        sub_0019BEB0(3);
        st->phase = 0x14;
        return 1;
    case 15:
        if (a50_framesPerSecond + a50_framesPerSecond > count)
            break;
        sub_0001B3F0(aa0_slots[3].model120);
        aa0_slots[3].flags |= 0x40;
        sub_000A2CC0(3, HIT_BIT);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
