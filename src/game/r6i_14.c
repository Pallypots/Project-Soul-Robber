/* Area r6i: room event script with a camera fade (r6i_14). Names inferred. */
#include "r6i.h"

/* 0x000BACA0: room script (modes as the other room scripts; mode 3 forces
   phase 0x63). Phases: 10 fade out (0x00036C00(1, 0, 0.5)); 11 wait for the
   fade; 12 set actor 0's flags 0x300000, set player flags 0x3800008 and fade
   back in; 13 wait, then phase 20; 20 give actor 0 motion 1 and restart the
   counter; 21 after 1.5 seconds clear actor 0's flags 0x300000 and go to 0x63;
   0x63 clears the state and returns 0. Otherwise returns 1. */
int r6i_RoomScriptFade(int mode, R6iKeyStep *st)
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
        st->phase = 0x63;
    }
    n = ++st->count;
    switch (st->phase) {
    case 10:
        sub_00036C00(1, 0, 0.5f);
        st->phase++;
        break;
    case 11:
        if (sub_00036D40() == 0)
            st->phase++;
        break;
    case 12:
        sub_000A2CA0(0, 0x300000);
        PlayerObj_SetFlags(&g_stats, 0x3800008, 0);
        sub_00036C00(0, 0, 0.5f);
        st->phase++;
        break;
    case 13:
        if (sub_00036D40() == 0)
            st->phase = 0x14;
        break;
    case 20:
        sub_000A42F0(0, 1);
        st->count = 0;
        st->phase++;
        break;
    case 21:
        if (n >= R6I_FTOI(r1e_fps42C964 * 1.5f)) {
            sub_000A2CC0(0, 0x300000);
            st->phase = 0x63;
        }
        break;
    case 0x63:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000AE5F0: room script with timed steps (mode 0 clears flags and phase,
   mode 1 arms phase 10, mode 3 clears and returns 0). Phases: 10 reset actor
   0x18; 11 after 3 seconds give actor 0x1A motion 1; 12 after 0.5 seconds
   switch actor 0x18 on; 13 after 0.8 seconds give actor 0x1A motion 2; 14
   when actor 0x1A's motion ends give it motion 0 and go to phase 0x14; 0x14
   clears the state and returns 0. Otherwise returns 1. */
int r6i_RoomScriptTimed(int mode, R6iKeyStep *st)
{
    int n;

    if (mode == 0) {
        st->flags = 0;
        st->phase = 0;
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
        st->phase = 0;
        return 0;
    }
    n = ++st->count;
    switch (st->phase) {
    case 10:
        sub_000A2E10(0x18, 0);
        sub_000A2DD0(0x18, 0, 0);
        st->count = 0;
        st->phase++;
        break;
    case 11:
        if (!(r1e_fps42C964 * 3.0 > n)) {
            sub_000A4340(0x1A, 1);
            st->count = 0;
            st->phase++;
        }
        break;
    case 12:
        if (!(r1e_fps42C964 * 0.5 > n)) {
            sub_000A2E50(0x18, 0);
            sub_000A2DD0(0x18, 1, 0);
            st->phase++;
        }
        break;
    case 13:
        if (!(r1e_fps42C964 * 0.8 > n)) {
            sub_000A4340(0x1A, 2);
            st->phase++;
        }
        break;
    case 14:
        if (sub_000A4370(0x1A) != 0) {
            sub_000A4340(0x1A, 0);
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

/* 0x000B49E0: room script like 0x000BACA0 for actor 1: set player flags
   0x3800008 and fade out; wait; set actor 1's flags 0x300000 and fade back
   in; wait, then phase 20; give actor 1 motion 1 and restart the counter;
   after 6 seconds clear actor 1's flags 0x300000 and go to 0x63; 0x63 clears
   the state and returns 0. Otherwise returns 1. */
int r6i_RoomScriptFade2(int mode, R6iKeyStep *st)
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
        st->phase = 0x63;
    }
    n = ++st->count;
    switch (st->phase) {
    case 10:
        PlayerObj_SetFlags(&g_stats, 0x3800008, 0);
        sub_00036C00(1, 0, 0.5f);
        st->phase++;
        break;
    case 11:
        if (sub_00036D40() == 0)
            st->phase++;
        break;
    case 12:
        sub_000A2CA0(1, 0x300000);
        sub_00036C00(0, 0, 0.5f);
        st->phase++;
        break;
    case 13:
        if (sub_00036D40() == 0)
            st->phase = 0x14;
        break;
    case 20:
        sub_000A42F0(1, 1);
        st->count = 0;
        st->phase++;
        break;
    case 21:
        if (n >= R6I_FTOI(r1e_fps42C964 * 6.0f)) {
            sub_000A2CC0(1, 0x300000);
            st->phase = 0x63;
        }
        break;
    case 0x63:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
