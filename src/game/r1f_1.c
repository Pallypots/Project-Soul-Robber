/* Area r1f, group 1: actor kind dispatchers 0x0001C400..0x0001C490. Names inferred. */
#include "r1f.h"

typedef void (*R1fActorFn)(void *ctx, A12Actor *a);

/* 0x0001C400: pick an actor's handler by kind (4..13) and forward to it. */
void r1f_ActorDispatchA(void *ctx, A12Actor *a)
{
    R1fActorFn fn;
    switch (a->kind) {
    case 4: case 9: case 10: case 12:
        fn = sub_0001C160;
        break;
    case 5:
        fn = sub_0001BEE0;
        break;
    case 6: case 7: case 8: case 11: case 13:
        fn = (R1fActorFn)a1b_Swap_1C260;
        break;
    default:
        return;
    }
    fn(ctx, a);
}

/* 0x0001C460: pick the handler of an actor of kind 4 or 5..7 and forward. */
void r1f_ActorDispatchB(void *ctx, A12Actor *a)
{
    R1fActorFn fn;
    int k = a->kind;
    if (k == 4) {
        fn = sub_0001BEE0;
    } else {
        if (k < 4)
            return;
        if (k > 7)
            return;
        fn = (R1fActorFn)a1b_Swap_1C260;
    }
    fn(ctx, a);
}

/* 0x0001C490: pick the handler of an actor of kind 5, 7 or 10 (sub-kind 5)
   and forward. */
void r1f_ActorDispatchC(void *ctx, R1fActorB *a)
{
    R1fActorFn fn;
    switch (a->kind) {
    case 10:
        if (a->sub != 5)
            return;
        /* fall through */
    case 5:
        fn = sub_0001BEE0;
        break;
    case 7:
        fn = (R1fActorFn)a1b_Swap_1C260;
        break;
    default:
        return;
    }
    fn(ctx, (A12Actor *)a);
}
