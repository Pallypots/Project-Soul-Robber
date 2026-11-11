/* Area r6j: chest room script (r6j_9). Names inferred. */
#include "r6j.h"

/* 0x000BBCD0: room script for three switches (actors 0, 2, 4) that open
   actor 6. Phase 10 turns lamps 1/3/5 off, gives the switches motion 0x21,
   resets actor 6 (motion 0, HIT_BIT 0x10000000 set) and sets event flag
   0x1F9; phase 11 waits until all three switches report bit 0x800, then
   sets flag 0xE6, clears 0x1F9 and goes to 0x14; 0x14 gives actor 6
   motion 1; 0x15 waits 60 frames of its animation, detaches its model,
   sets actor flag 0x40 and clears HIT_BIT; 0x16 waits for the motion;
   0x17 gives motion 2 and ends (0x63); 0x63 clears the state and returns 0
   (mode 3 forces it). Returns 1. */
int r6j_RoomScriptChest(int mode, R6jStep *st)
{
    R6jActor *a;

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
        sub_000A4410(1, 0);
        sub_000A4410(3, 0);
        sub_000A4410(5, 0);
        sub_000A43C0(0, 0x21);
        sub_000A43C0(2, 0x21);
        sub_000A43C0(4, 0x21);
        sub_000A42F0(6, 0);
        sub_000A2CA0(6, 0x10000000);
        sub_000D9AB0(0x1F9);
        st->phase++;
        break;
    case 11:
        if ((sub_000A4290(0)->flags & 0x800) == 0)
            break;
        if ((sub_000A4290(2)->flags & 0x800) == 0)
            break;
        if ((sub_000A4290(4)->flags & 0x800) == 0)
            break;
        sub_000D9AB0(0xE6);
        sub_000D9B30(0x1F9);
        st->phase = 0x14;
        return 1;
    case 0x14:
        sub_000A42F0(6, 1);
        st->phase++;
        return 1;
    case 0x15:
        if (sub_00145780(sub_000A42A0(6), 60.0f) == 0)
            break;
        a = sub_000A4290(6);
        sub_0001B3F0(a->model120);
        a->flags |= 0x40;
        sub_000A2CC0(6, 0x10000000);
        st->phase++;
        return 1;
    case 0x16:
        if (sub_000A4370(6) == 0)
            break;
        st->phase++;
        return 1;
    case 0x17:
        sub_000A42F0(6, 2);
        st->phase = 0x63;
        return 1;
    case 0x63:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5830: fade cutscene for chapter 2 stages 7, 8 and 11 (any other
   chapter or stage hangs, assert style). Phase 10 fades out (0.5 s); 11
   waits; 12 sets the actor's flags 0x300000, stops the player (flags
   0x3800008) and fades in; 13 waits and goes to 0x14; 0x14 gives the actor
   motion 2 and restarts the frame count; 0x15 waits 1.5 seconds then clears
   the actor flags, releases the player and ends (0x63); 0x63 clears the
   state and returns 0 (mode 3 forces it). The actor is 0 while flag bit 0
   is set; otherwise the original leaves the index uninitialised and the
   compiler reads the mode argument slot, so it is written as actor = mode
   to keep that behaviour defined. Returns 1. */
int r6j_RoomScriptFadeC2(int mode, R6jStep *st)
{
    int32_t chapter, stage;
    int actor;

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
    actor = mode;
    if (st->flags & 1) {
        sub_000DFD40(&chapter, &stage);
        if (chapter != 2)
            for (;;) ;
        if (stage != 7 && stage != 11 && stage != 8)
            for (;;) ;
        actor = 0;
    }
    st->count++;
    switch (st->phase) {
    case 10:
        sub_00036C00(1, 0, 0.5f);
        st->phase++;
        return 1;
    case 11:
        if (sub_00036D40() != 0)
            break;
        st->phase++;
        return 1;
    case 12:
        sub_000A2CA0(actor, 0x300000);
        PlayerObj_SetFlags(&g_stats, 0x3800008, 0);
        st->phase++;   /* before the fade (0x00036C00 only touches the fade globals) */
        sub_00036C00(0, 0, 0.5f);
        return 1;
    case 13:
        if (sub_00036D40() != 0)
            break;
        st->phase = 0x14;
        return 1;
    case 0x14:
        sub_000A42F0(actor, 2);
        st->phase++;
        st->count = 0;
        return 1;
    case 0x15:
        if (st->count < R6J_FTOI(a50_framesPerSecond * 1.5f))
            break;
        sub_000A2CC0(actor, 0x300000);
        sub_000D1930(&g_stats);
        st->phase = 0x63;
        return 1;
    case 0x63:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
