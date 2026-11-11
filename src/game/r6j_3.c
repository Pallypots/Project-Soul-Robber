/* Area r6j: switch room scripts (r6j_3). Names inferred. */
#include "r6j.h"

/* 0x000B95C0: room script for the floor switch (actor 4) tied to event
   flag 0x2C5. Mode 0 resets, mode 1 arms phase 10, mode 3 forces phase
   0x14. Phase 10 sets the switch pose (1 when the flag is set, else 3);
   phase 11 shows lamps 0x14..0x17 for the flag state, flips the switch
   when its state no longer matches, and on hit bit 0x1000 shakes the
   player (-10000) and clears the bit. Phase 0x14 clears the state and
   returns 0. While the flag is clear and slot 0 value is 2 the lamps
   blink with bit 3 of the frame counter. Returns 1. */
int r6j_RoomScriptSwitch2C5(int mode, R6jStep *st)
{
    R6jActor *a;
    int state;

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
    case 10:
        if (sub_000D9A70(0x2C5) != 0)
            sub_000A42F0(4, 1);
        else
            sub_000A42F0(4, 3);
        st->phase++;
        /* fall through */
    case 11:
        a = sub_000A4290(4);
        if (sub_000D9A70(0x2C5) != 0) {
            sub_000A4410(0x14, 1);
            sub_000A4410(0x15, 0);
            sub_000A4410(0x16, 0);
            sub_000A4410(0x17, 1);
            state = a->state48;
            if (state == 1 || state == 2)
                break;
            sub_000A42F0(4, 1);
        } else {
            sub_000A4410(0x14, 0);
            sub_000A4410(0x15, 1);
            sub_000A4410(0x16, 1);
            sub_000A4410(0x17, 0);
            state = a->state48;
            if (state == 0 || state == 3)
                break;
            sub_000A42F0(4, 3);
        }
        if (sub_000A2CE0(4, 0x1000) != 0) {
            sub_000CAE20(&g_stats, -10000.0f);
            sub_000A2CC0(4, 0x1000);
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    if (sub_000D9A70(0x2C5) == 0 && r6b_Slot0Value110() == 2) {
        if ((a50_frameCounter0 & 8) != 0) {
            sub_000A4410(0x14, 0);
            sub_000A4410(0x15, 1);
            sub_000A4410(0x16, 1);
            sub_000A4410(0x17, 0);
        } else {
            sub_000A4410(0x14, 0);
            sub_000A4410(0x15, 0);
            sub_000A4410(0x16, 1);
            sub_000A4410(0x17, 1);
        }
    }
    return 1;
}

/* 0x000B97A0: room script for floor switch actor 5 and event flag
   0x2C6 (lamps 0xC..0xF), same shape as 0x000B95C0. Phase 10 sets
   the pose (1 when the flag is set, else 3); phase 11 shows the
   lamps for the flag state and flips the switch when its state disagrees;
   while the flag is clear and slot 0 value is 0 the lamps blink with bit 3
   of the frame counter. Phase 0x14 clears and returns 0. Returns 1. */
int r6j_RoomScriptSwitch2C6(int mode, R6jStep *st)
{
    R6jActor *a;
    int state;

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
    case 10:
        if (sub_000D9A70(0x2C6) != 0)
            sub_000A42F0(5, 1);
        else
            sub_000A42F0(5, 3);
        st->phase++;
        /* fall through */
    case 11:
        a = sub_000A4290(5);
        if (sub_000D9A70(0x2C6) != 0) {
            sub_000A4410(0xC, 0);
            sub_000A4410(0xD, 1);
            sub_000A4410(0xE, 1);
            sub_000A4410(0xF, 0);
            state = a->state48;
            if (state == 1 || state == 2)
                break;
            sub_000A42F0(5, 1);
        } else {
            sub_000A4410(0xC, 1);
            sub_000A4410(0xD, 0);
            sub_000A4410(0xE, 0);
            sub_000A4410(0xF, 1);
            state = a->state48;
            if (state == 0 || state == 3)
                break;
            sub_000A42F0(5, 3);
        }
        if (sub_000A2CE0(5, 0x1000) != 0) {
            sub_000CAE20(&g_stats, -10000.0f);
            sub_000A2CC0(5, 0x1000);
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    if (sub_000D9A70(0x2C6) == 0 && r6b_Slot0Value110() == 0) {
        if ((a50_frameCounter0 & 8) != 0) {
            sub_000A4410(0xC, 1);
            sub_000A4410(0xD, 0);
            sub_000A4410(0xE, 0);
            sub_000A4410(0xF, 1);
        } else {
            sub_000A4410(0xC, 0);
            sub_000A4410(0xD, 0);
            sub_000A4410(0xE, 1);
            sub_000A4410(0xF, 1);
        }
    }
    return 1;
}

/* 0x000B9970: room script for floor switch actor 6 and event flag
   0x2C7 (lamps 0x10..0x13), same shape as 0x000B95C0. Phase 10 sets
   the pose (3 when the flag is set, else 1); phase 11 shows the
   lamps for the flag state and flips the switch when its state disagrees;
   while the flag is clear and slot 0 value is 3 the lamps blink with bit 3
   of the frame counter. Phase 0x14 clears and returns 0. Returns 1. */
int r6j_RoomScriptSwitch2C7(int mode, R6jStep *st)
{
    R6jActor *a;
    int state;

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
    case 10:
        if (sub_000D9A70(0x2C7) != 0)
            sub_000A42F0(6, 3);
        else
            sub_000A42F0(6, 1);
        st->phase++;
        /* fall through */
    case 11:
        a = sub_000A4290(6);
        if (sub_000D9A70(0x2C7) != 0) {
            sub_000A4410(0x10, 0);
            sub_000A4410(0x11, 1);
            sub_000A4410(0x12, 1);
            sub_000A4410(0x13, 0);
            state = a->state48;
            if (state == 0 || state == 3)
                break;
            sub_000A42F0(6, 3);
        } else {
            sub_000A4410(0x10, 1);
            sub_000A4410(0x11, 0);
            sub_000A4410(0x12, 0);
            sub_000A4410(0x13, 1);
            state = a->state48;
            if (state == 1 || state == 2)
                break;
            sub_000A42F0(6, 1);
        }
        if (sub_000A2CE0(6, 0x1000) != 0) {
            sub_000CAE20(&g_stats, -10000.0f);
            sub_000A2CC0(6, 0x1000);
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    if (sub_000D9A70(0x2C7) == 0 && r6b_Slot0Value110() == 3) {
        if ((a50_frameCounter0 & 8) != 0) {
            sub_000A4410(0x10, 1);
            sub_000A4410(0x11, 0);
            sub_000A4410(0x12, 0);
            sub_000A4410(0x13, 1);
        } else {
            sub_000A4410(0x10, 0);
            sub_000A4410(0x11, 0);
            sub_000A4410(0x12, 1);
            sub_000A4410(0x13, 1);
        }
    }
    return 1;
}

/* 0x000B9B40: room script for floor switch actor 7 and event flag
   0x2C8 (lamps 0x8..0xB), same shape as 0x000B95C0. Phase 10 sets
   the pose (3 when the flag is set, else 1); phase 11 shows the
   lamps for the flag state and flips the switch when its state disagrees;
   while the flag is clear and slot 0 value is 1 the lamps blink with bit 3
   of the frame counter. Phase 0x14 clears and returns 0. Returns 1. */
int r6j_RoomScriptSwitch2C8(int mode, R6jStep *st)
{
    R6jActor *a;
    int state;

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
    case 10:
        if (sub_000D9A70(0x2C8) != 0)
            sub_000A42F0(7, 3);
        else
            sub_000A42F0(7, 1);
        st->phase++;
        /* fall through */
    case 11:
        a = sub_000A4290(7);
        if (sub_000D9A70(0x2C8) != 0) {
            sub_000A4410(0x8, 1);
            sub_000A4410(0x9, 0);
            sub_000A4410(0xA, 0);
            sub_000A4410(0xB, 1);
            state = a->state48;
            if (state == 0 || state == 3)
                break;
            sub_000A42F0(7, 3);
        } else {
            sub_000A4410(0x8, 0);
            sub_000A4410(0x9, 1);
            sub_000A4410(0xA, 1);
            sub_000A4410(0xB, 0);
            state = a->state48;
            if (state == 1 || state == 2)
                break;
            sub_000A42F0(7, 1);
        }
        if (sub_000A2CE0(7, 0x1000) != 0) {
            sub_000CAE20(&g_stats, -10000.0f);
            sub_000A2CC0(7, 0x1000);
        }
        break;
    case 0x14:
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    if (sub_000D9A70(0x2C8) == 0 && r6b_Slot0Value110() == 1) {
        if ((a50_frameCounter0 & 8) != 0) {
            sub_000A4410(0x8, 0);
            sub_000A4410(0x9, 1);
            sub_000A4410(0xA, 1);
            sub_000A4410(0xB, 0);
        } else {
            sub_000A4410(0x8, 0);
            sub_000A4410(0x9, 0);
            sub_000A4410(0xA, 1);
            sub_000A4410(0xB, 1);
        }
    }
    return 1;
}
