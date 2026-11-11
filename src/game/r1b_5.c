/* Area r1b, group 5: callers kept apart from their callees 0x000184D0..0x000186C0. Names inferred. */
#include "r1b.h"

/* 0x000184D0: run a track's command list until it ends.
   calls 0x000181B0 and 0x00018340 with EDI=t, 0x00017DE0 and 0x00017E80 with
   ESI=t, 0x00017F40 with EAX=t */
int r1b_TrackRun(R1bTrack *t)
{
    t->cur = t->begin;
    t->v08 = 0;
    for (;;) {
        switch (*t->cur) {
        case 0: sub_000181B0(t); break;
        case 1: sub_00018340(t); break;
        case 2: sub_00017E80(t); return 0;
        case 3: sub_00017DE0(t); break;
        case 4: r1_ClearList((struct R1EntryList *)t); return 1;
        default: return 0;
        }
    }
}

/* 0x000186C0: reset the menu object at 0x0037B560 and clear its four slots. */
void r1b_MenuReset(void)
{
    sub_00075F00(r1b_menu37B580);
    sub_0003FAB0(&a1b_obj37B560, r1b_menu37B580);
    r1b_ApplyLayout(&a1b_obj37B560, 0);
    a1b_slots37BEE8[0] = 0;
    a1b_slots37BEE8[1] = 0;
    a1b_slots37BEE8[2] = 0;
    a1b_slots37BEE8[3] = 0;
}
