/* Area r6i: key door step (r6i_13). Names inferred. */
#include "r6i.h"

/* 0x000B34F0: one step of a key door (actor idx 0..3, each with its event
   flag 0x17/0x19/0x1A/0x18 and sound flag 0x1F4..0x1F7). Mode 0 clears the
   state, mode 1 arms it (phase 10), mode 3 forces phase 0x14. In phase 10
   the door opens when its flag is set (motion 2, flags, motion 0x201, sets
   the sound flag) or stays shut unless flag 0x108 is set; when the flag is
   clear the door is reset and the sound flag cleared once 0x108 is set; the
   phase then becomes 0x14. Phase 0x14 clears the state and returns 0;
   otherwise returns 1.
   regargs: mode=EAX st=ESI idx=EDI. */
int r6i_KeyDoorStep(int mode, R6iKeyStep *st, int idx)
{
    R6iActor *actor = sub_000A4290(idx);
    int flag, snd;

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
    switch (idx) {
    case 0: flag = 0x17; snd = 0x1F4; break;
    case 1: flag = 0x19; snd = 0x1F5; break;
    case 2: flag = 0x1A; snd = 0x1F6; break;
    case 3: flag = 0x18; snd = 0x1F7; break;
    default: return 1;
    }
    st->count++;
    if (st->phase == 10) {
        if (sub_000D9A70(flag) != 0) {
            sub_000A42F0(idx, 2);
            sub_000A2D70(idx, 1);
            sub_000A2CC0(idx, 0x80);
            sub_000A1940(actor, 0x201);
            sub_000D9B30(snd);
        } else if (sub_000D9A70(0x108) == 0) {
            sub_000A2D70(idx, 1);
            sub_000A2CC0(idx, 0x80);
        }
        if (sub_000D9A70(flag) == 0) {
            sub_000A2DD0(idx, 1, 0);
            if (sub_000D9A70(0x108) != 0)
                sub_000D9AB0(snd);
        }
        st->phase = 0x14;
    } else if (st->phase == 0x14) {
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}

/* 0x000BB1C0: the same key door step for the second set of doors (actor idx
   0..3 with event flags 0x13..0x16 and sound flags 0x1F0..0x1F3); see
   0x000B34F0.
   regargs: mode=EAX st=ESI idx=EDI. */
int r6i_KeyDoorStep2(int mode, R6iKeyStep *st, int idx)
{
    R6iActor *actor = sub_000A4290(idx);
    int flag, snd;

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
    switch (idx) {
    case 0: flag = 0x13; snd = 0x1F0; break;
    case 1: flag = 0x14; snd = 0x1F1; break;
    case 2: flag = 0x15; snd = 0x1F2; break;
    case 3: flag = 0x16; snd = 0x1F3; break;
    default: return 1;
    }
    st->count++;
    if (st->phase == 10) {
        if (sub_000D9A70(flag) != 0) {
            sub_000A42F0(idx, 2);
            sub_000A2D70(idx, 1);
            sub_000A2CC0(idx, 0x80);
            sub_000A1940(actor, 0x201);
            sub_000D9B30(snd);
        } else if (sub_000D9A70(0x108) == 0) {
            sub_000A2D70(idx, 1);
            sub_000A2CC0(idx, 0x80);
        }
        if (sub_000D9A70(flag) == 0) {
            sub_000A2DD0(idx, 1, 0);
            if (sub_000D9A70(0x108) != 0)
                sub_000D9AB0(snd);
        }
        st->phase = 0x14;
    } else if (st->phase == 0x14) {
        st->flags = 0;
        st->phase = 0;
        return 0;
    }
    return 1;
}
