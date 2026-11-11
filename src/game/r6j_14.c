/* Area r6j: music change room script (r6j_14). Names inferred. */
#include "r6j.h"

/* 0x000B4520: room script that opens actor 2 and changes the music. It
   first reads actor record 0 (0x000A4290, result unused). Phase 0 turns
   lamp 0x12 off; phase 9 gives actor 2 pose 2, clears bit 0x20 of 0x12,
   turns lamp 0x12 off and sets event flag 0x2B0, then ends (0x14) when
   flag 0x128 is set and 0x12A clear, else gives actor 0 pose 4 and starts
   music 0x23 (0x00048A00); phase 10 waits until music 0x23 is current and
   sets its four channels (0x00049180) before ending. Mode 3 forces phase
   0x14, which clears the state and returns 0. Returns 1. */
int r6j_RoomScriptMusic23(int mode, R6jStep *st)
{
    void *snd;

    sub_000A4290(0);
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
    st->count++;
    switch (st->phase) {
    case 0:
        sub_000A4410(0x12, 0);
        st->phase++;
        break;
    case 9:
        sub_000A42F0(2, 2);
        sub_000A2D40(0x12, 0x20);
        sub_000A4410(0x12, 0);
        sub_000D9AB0(0x2B0);
        if (sub_000D9A70(0x128) != 0 && sub_000D9A70(0x12A) == 0) {
            st->phase = 0x14;
            return 1;
        }
        sub_000A42F0(0, 4);
        sub_00048A00(0x23, 0);
        st->phase++;
        return 1;
    case 10:
        if (sub_00047F20() != 0x23)
            break;
        snd = sub_00047F30();
        sub_00049180(snd, 0, 0x3FFF, 1.0f, 0, 1, 2000.0f);
        sub_00049180(snd, 1, 0x3FFF, 1.0f, 0, 1, 2000.0f);
        sub_00049180(snd, 2, 0x3FFF, 1.0f, 0, 1, 2000.0f);
        sub_00049180(snd, 3, 0x3FFF, 1.0f, 0, 1, 2000.0f);
        st->phase = 0x14;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000BB430: room script for the five pillars (actors 9..0xD). Phase 10
   ends at once (0x14) when event flag 0xF3 is set; otherwise every frame
   the pillars follow event flag 0xBE: lamps on, bit 0x20 and HIT_BIT set
   while it is set, lamps off and the bits cleared while it is clear. Mode 3
   forces phase 0x14, which clears the state and returns 0. Returns 1. */
int r6j_RoomScriptPillarsBE(int mode, R6jStep *st)
{
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
    st->count++;
    if (st->phase == 10) {
        if (sub_000D9A70(0xF3) != 0) {
            st->phase = 0x14;
            return 1;
        }
        if (sub_000D9A70(0xBE) != 0) {
            sub_000A4410(9, 1);
            sub_000A4410(0xA, 1);
            sub_000A4410(0xB, 1);
            sub_000A4410(0xC, 1);
            sub_000A4410(0xD, 1);
            sub_000A2D10(9, 0x20);
            sub_000A2D10(0xA, 0x20);
            sub_000A2D10(0xB, 0x20);
            sub_000A2D10(0xC, 0x20);
            sub_000A2D10(0xD, 0x20);
            sub_000A2CA0(9, 0x10000000);
            sub_000A2CA0(0xA, 0x10000000);
            sub_000A2CA0(0xB, 0x10000000);
            sub_000A2CA0(0xC, 0x10000000);
            sub_000A2CA0(0xD, 0x10000000);
            return 1;
        }
        sub_000A4410(9, 0);
        sub_000A4410(0xA, 0);
        sub_000A4410(0xB, 0);
        sub_000A4410(0xC, 0);
        sub_000A4410(0xD, 0);
        sub_000A2D40(9, 0x20);
        sub_000A2D40(0xA, 0x20);
        sub_000A2D40(0xB, 0x20);
        sub_000A2D40(0xC, 0x20);
        sub_000A2D40(0xD, 0x20);
        sub_000A2CC0(9, 0x10000000);
        sub_000A2CC0(0xA, 0x10000000);
        sub_000A2CC0(0xB, 0x10000000);
        sub_000A2CC0(0xC, 0x10000000);
        sub_000A2CC0(0xD, 0x10000000);
    } else if (st->phase == 0x14) {
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000AD8C0: looping script for a moving platform actor `idx` (used for
   several actors; actor 9 also gets an extra 0x000A2DD0(9, 1, 1) at 1.8
   seconds). Phase 10 and 13 wait exactly three seconds; 11 starts motion 1,
   opens the actor (0x000A2DD0) and sets event flag 0xDD; 12 at 2.4 seconds
   calls 0x000A2E10, then waits for the motion and starts motion 2; 14
   starts motion 3 and opens the actor; 15 like 12 (plus the actor 9 extra)
   and when the motion ends gives motion 0, clears event flag 0xDD and loops
   back to phase 10. Mode 3 and phase 0x14 clear the state and return 0.
   Returns 1. regargs: mode=EAX st=ESI idx=EDI. */
int r6j_PlatformLoop(int mode, R6jStep *st, int idx)
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
    case 13:
        if (count == R6J_FTOI(a50_framesPerSecond * 3.0f)) {
            st->phase++;
            return 1;
        }
        break;
    case 11:
        sub_000A42F0(idx, 1);
        st->count = 0;
        sub_000A2DD0(idx, 0, 0);
        sub_000D9AB0(0xDD);
        st->phase++;
        break;
    case 12:
        if (count == R6J_FTOI(a50_framesPerSecond * 2.4f))
            sub_000A2E10(idx, 0);
        if (sub_000A4370(idx) == 0)
            break;
        sub_000A42F0(idx, 2);
        st->count = 0;
        st->phase++;
        return 1;
    case 14:
        sub_000A42F0(idx, 3);
        st->count = 0;
        sub_000A2DD0(idx, 0, 0);
        st->phase++;
        return 1;
    case 15:
        if (count == R6J_FTOI(a50_framesPerSecond * 2.4f))
            sub_000A2E10(idx, 0);
        if (idx == 9 && st->count == R6J_FTOI(a50_framesPerSecond * 1.8f))
            sub_000A2DD0(idx, 1, 1);
        if (sub_000A4370(idx) == 0)
            break;
        sub_000A42F0(idx, 0);
        sub_000A2E10(idx, 0);
        st->count = 0;
        sub_000D9B30(0xDD);
        st->phase = 10;
        return 1;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
