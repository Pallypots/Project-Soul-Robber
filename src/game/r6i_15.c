/* Area r6i: room cutscene script for event flag 0x2E2 (r6i_15). Names inferred. */
#include "r6i.h"

/* 0x000B89B0: room script for event flag 0x2E2 (modes as the other room
   scripts; mode 3 forces phase 0x14). Phase 10: when the flag is already
   set finish at once (0x000A5450(2)), else open actor 2 and go on; actor 3
   gets motion 0 either way. 11 waits until the player is free; 12 after 3 s
   starts camera event 3; 13 waits for an idle player motion (0, 0x200 or
   0x313), stops the player and moves the camera; 14 after 3 s gives actor 3
   motion 1; 15 after 1 s restores the camera and player and ends camera
   event 3; 16 waits for pair 0 to reach 3 and sets 0x003ED23C; 17 after 5 s
   sets flag 0x2E2 and goes to 0x14; 0x14 clears the state and returns 0.
   Otherwise returns 1. */
int r6i_RoomScript2E2(int mode, R6iKeyStep *st)
{
    int n;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->phase = 10;
        st->count = 0;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    n = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0x2E2) != 0) {
            sub_000A5450(2);
            st->phase = 0x14;
            sub_000A4410(3, 0);
            break;
        }
        sub_000A4410(2, 1);
        sub_000A2D10(2, 0x20);
        sub_000A42F0(2, 0);
        st->phase++;
        sub_000A4410(3, 0);
        break;
    case 11:
        if (a80_AnyLowFlags() == 0 && a80_ModeFlag1() == 0) {
            st->count = 0;
            st->phase++;
        }
        break;
    case 12:
        if (!(r1e_fps42C964 * 3.0f > (float)n)) {
            sub_0019BE90(3);
            st->phase++;
        }
        break;
    case 13:
        if (g_stats.anim128 == 0 || g_stats.anim128 == 0x200 || g_stats.anim128 == 0x313) {
            sub_000D1D00(&g_stats);
            sub_00019000(ae0_obj3E1270, 3);
            sub_0001AB00(ae0_obj3E1270, 3, 2, 0, 1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 14:
        if (!(r1e_fps42C964 * 3.0f > (float)n)) {
            sub_000A43C0(3, 1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 15:
        if (!(r1e_fps42C964 > (float)n)) {
            sub_00019000(ae0_obj3E1270, 1);
            PlayerObj_ClearFlags22(&g_stats);
            sub_0019BEB0(3);
            st->phase++;
        }
        break;
    case 16:
        if (r2b_PairB(0) == 3) {
            a80_Set3ED23C(1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 17:
        if (!(r1e_fps42C964 * 5.0f > (float)n)) {
            sub_000D9AB0(0x2E2);
            st->phase = 0x14;
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B8C60: the follow-up room script for event flag 0x2E3, like
   0x000B89B0 for actors 4 and 5: phase 11 also waits for flag 0x2E2; the
   camera move uses 0x0001AB00(3, 2, 1, 1); phase 16 waits for pair 0 to
   reach 4 and sets 0x003ED23C to 2. */
int r6i_RoomScript2E3(int mode, R6iKeyStep *st)
{
    int n;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->phase = 10;
        st->count = 0;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    n = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0x2E3) != 0) {
            sub_000A5450(4);
            st->phase = 0x14;
            sub_000A4410(5, 0);
            break;
        }
        sub_000A4410(4, 1);
        sub_000A2D10(4, 0x20);
        sub_000A42F0(4, 0);
        st->phase++;
        sub_000A4410(5, 0);
        break;
    case 11:
        if (a80_AnyLowFlags() == 0 && a80_ModeFlag1() == 0 && sub_000D9A70(0x2E2) != 0) {
            st->count = 0;
            st->phase++;
        }
        break;
    case 12:
        if (!(r1e_fps42C964 * 3.0f > (float)n)) {
            sub_0019BE90(3);
            st->phase++;
        }
        break;
    case 13:
        if (g_stats.anim128 == 0 || g_stats.anim128 == 0x200 || g_stats.anim128 == 0x313) {
            sub_000D1D00(&g_stats);
            sub_00019000(ae0_obj3E1270, 3);
            sub_0001AB00(ae0_obj3E1270, 3, 2, 1, 1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 14:
        if (!(r1e_fps42C964 * 3.0f > (float)n)) {
            sub_000A43C0(5, 1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 15:
        if (!(r1e_fps42C964 > (float)n)) {
            sub_00019000(ae0_obj3E1270, 1);
            PlayerObj_ClearFlags22(&g_stats);
            sub_0019BEB0(3);
            st->phase++;
        }
        break;
    case 16:
        if (r2b_PairB(0) == 4) {
            a80_Set3ED23C(2);
            st->count = 0;
            st->phase++;
        }
        break;
    case 17:
        if (!(r1e_fps42C964 * 5.0f > (float)n)) {
            sub_000D9AB0(0x2E3);
            st->phase = 0x14;
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B8F20: the last room script of the set, for event flag 0x2E4, like
   0x000B8C60 for actors 6 and 7 (phase 11 waits for flag 0x2E3; camera move
   0x0001AB00(3, 2, 2, 1)); phase 15 restores the camera and player, ends
   camera event 3, sets flag 0x2E4 and goes straight to 0x14. */
int r6i_RoomScript2E4(int mode, R6iKeyStep *st)
{
    int n;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
        st->count = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->phase = 10;
        st->count = 0;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0x14;
    }
    n = ++st->count;
    switch (st->phase) {
    case 10:
        if (sub_000D9A70(0x2E4) != 0) {
            sub_000A5450(6);
            st->phase = 0x14;
            sub_000A4410(7, 0);
            break;
        }
        sub_000A4410(6, 1);
        sub_000A2D10(6, 0x20);
        sub_000A42F0(6, 0);
        st->phase++;
        sub_000A4410(7, 0);
        break;
    case 11:
        if (a80_AnyLowFlags() == 0 && a80_ModeFlag1() == 0 && sub_000D9A70(0x2E3) != 0) {
            st->count = 0;
            st->phase++;
        }
        break;
    case 12:
        if (!(r1e_fps42C964 * 3.0f > (float)n)) {
            sub_0019BE90(3);
            st->phase++;
        }
        break;
    case 13:
        if (g_stats.anim128 == 0 || g_stats.anim128 == 0x200 || g_stats.anim128 == 0x313) {
            sub_000D1D00(&g_stats);
            sub_00019000(ae0_obj3E1270, 3);
            sub_0001AB00(ae0_obj3E1270, 3, 2, 2, 1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 14:
        if (!(r1e_fps42C964 * 3.0f > (float)n)) {
            sub_000A43C0(7, 1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 15:
        if (!(r1e_fps42C964 > (float)n)) {
            sub_00019000(ae0_obj3E1270, 1);
            PlayerObj_ClearFlags22(&g_stats);
            sub_0019BEB0(3);
            sub_000D9AB0(0x2E4);
            st->phase = 0x14;
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5A60: room script for chapter 2 stages 7, 8 and 11 (mode 0 sets
   flags 2, mode 1 arms phase 10, mode 3 clears and returns 0). Phase 0
   checks the chapter and stage (assert-style hang when not chapter 2 or
   not stage 7/8/11); on stage 8 it clears flag bit 1 and gives actor 1
   motion 2 when event flag 0xF is set (returning at once) or resets it.
   Phase 8 starts camera event 3 and actor 1's motion 1; phase 9 waits for
   the motion, gives motion 2, ends the camera event and goes to 0x14; phase
   0x14 clears the flags, sets phase 0x63 and returns 0. Returns 1. */
int r6i_RoomScriptC2(int mode, R6iKeyStep *st)
{
    int32_t chapter, stage;

    if (mode == 0) {
        st->flags = 2;
        st->phase = 0;
        return 1;
    }
    if (mode == 1) {
        st->flags |= 1;
        st->phase = 10;
        return 1;
    }
    if (mode == 3) {
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    switch (st->phase) {
    case 0:
        sub_000DFD40(&chapter, &stage);
        if (chapter != 2)
            for (;;) ;
        if (stage != 7 && stage != 8 && stage != 11)
            for (;;) ;
        if (stage == 8) {
            st->flags &= ~2u;
            if (sub_000D9A70(0xF) != 0) {
                sub_000A4340(1, 2);
                st->phase++;
                return 1;
            }
            sub_000A4340(1, 0);
            sub_000A2DD0(1, 0, 0);
        }
        st->phase++;
        break;
    case 8:
        sub_0019BE90(3);
        sub_000A4340(1, 1);
        sub_000A2E10(1, 0);
        st->phase++;
        break;
    case 9:
        if (sub_000A4370(1) != 0) {
            sub_000A4340(1, 2);
            sub_0019BEB0(3);
            st->phase = 0x14;
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0x63;
        return 0;
    }
    return 1;
}
