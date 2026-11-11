/* Area r2b, group 9: target selection (0x0011EE30). Names inferred. */
#include "r2b.h"

/* 0x0011EE30: pick the target named by condition c: 1 the player, 2 the linked
   kind-0xD actor when ctx is in mode 1 and it is flagged, 3 self, 4 the linked
   object, 5 none.  regargs: c=EAX ctx=ECX; self is the stack arg */
void *r2b_PickTargetB(const R2Cond *c, R2Ctx *ctx, void *self)
{
    switch (c->kind) {
    case 1:
        return r2_player;
    case 2:
        if (ctx->mode0F8 == 1 && (ctx->link104->flags0C & 1) && ctx->link104->kind04 == 0xD)
            return ctx->link104;
        return 0;
    case 3:
        return self;
    case 4:
        return ctx->link104;
    case 5:
        return 0;
    default:
        for (;;) ;
    }
}
