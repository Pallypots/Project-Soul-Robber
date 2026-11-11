/* Area r6d: faded text box drawing at 0x00077110 (r6d_2). Names inferred. */
#include "r6d.h"

/* 0x00077110: draw a text box faded to an alpha level.
   calls 0x00076E30 with EAX=t ESI=alpha/2 EBX=ctx; 0x00076FA0 with EAX=t ESI=alpha/2 */
void *r6d_TextDrawAlpha(void *ctx, R6cText *t, uint32_t alpha)
{
    r6c_TextReset(t);
    if (t) {
        if (t->u00.flags0 < 0)
            sub_00076E30(t, (alpha >> 1) & 0x7F, ctx, 2);
        if (t->u00.flags & 0x100)
            sub_00076FA0(t, (alpha >> 1) & 0x7F, ctx, 2);
    }
    sub_00038060(alpha | 0xFFFFFF00);
    r6d_TextDraw(ctx, t);
    sub_00038060(-1);
    return ctx;
}

