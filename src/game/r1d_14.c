/* Area r1d, group 14: channel update entry 0x00037EF0 (kept apart from 0x00037AF0). Names inferred. */
#include "r1d.h"

/* 0x00037EF0: update the channels for ctx (0x00037C70) or with no context
   (0x00037DD0), then step them.  calls 0x00037C70 with EDI=ctx */
void r1d_ChanUpdate(void *ctx)
{
    if (ctx != 0)
        sub_00037C70(ctx);
    else
        sub_00037DD0();
    sub_00037AF0();
}
