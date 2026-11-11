/* Area r6h: event script step (r6h_12). Names inferred. */
#include "r6h.h"

/* 0x000B3C80: run one step of a two-stage event script s. Mode 0 resets it
   (returns 1), mode 1 arms it at state 10 (returns 1), mode 3 resets it and
   returns 0. Otherwise the id is the mode, or (flag bit 0) read from the
   script reader, which must succeed with id 11 (assert-style hang). State 10
   asks a question: answer 2 runs the accept sequence (0x0019BE90(3), model events,
   player refresh 0x000D1D00) and goes to state 11, any other answer closes with id
   result 0 and state 0x63. State 11 waits for id to finish, then clears the
   player flags, calls 0x0019BEB0(3) and closes with state 0x63. State 0x63
   resets the script and returns 0. */
int r6h_ScriptStep(int mode, R6hScr *s)
{
    int err, answer, id;

    if (mode == 0) {
        s->flags = 0;
        s->state = 0;
        return 1;
    }
    if (mode == 1) {
        s->flags |= 1;
        s->state = 10;
        return 1;
    }
    if (mode == 3) {
        s->flags = 0;
        s->state = 0;
        return 0;
    }
    if (s->flags & 1) {
        sub_000DFD40(&err, &mode);
        if (err)
            for (;;) ;
        if (mode != 11)
            for (;;) ;
        id = 0;
    } else {
        id = mode;
    }
    switch (s->state) {
    case 10:
        sub_000DDF20(&mode, &answer);
        if (answer == 2) {
            sub_0019BE90(3);
            sub_00019000(ae0_obj3E1270, 3);
            sub_0001AB00(ae0_obj3E1270, 3, 2, 1, 0);
            sub_000D1D00(&g_stats);
            sub_000A4340(id, 3);
            s->state++;
            return 1;
        }
        sub_000A4340(id, 0);
        s->state = 0x63;
        break;
    case 11:
        if (sub_000A4370(id)) {
            sub_000CF4E0(&g_stats);
            sub_0019BEB0(3);
            sub_00019000(ae0_obj3E1270, 1);
            sub_000A4340(id, 0);
            s->state = 0x63;
            return 1;
        }
        break;
    case 0x63:
        s->flags = 0;
        s->state = 0;
        return 0;
    }
    return 1;
}
