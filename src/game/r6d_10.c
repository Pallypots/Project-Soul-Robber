/* Area r6d: movie and title helpers around 0x00078050-0x000796CD (r6d_10). Names inferred. */
#include "r6d.h"

/* 0x00078050: block until the pad is idle and key 0x2BC has been pressed and released. */
void r6d_WaitForKey(void)
{
    sub_000325A0(1);
    sub_0019B9E0();
    sub_00048590();
    while (sub_00047950() != 1)
        sub_000580D0();
    sub_000487F0(0x2BC, 0, 0);
    while (sub_00048820(0x2BC, 0, 0) != 2)
        sub_000580D0();
    sub_00048860(0x2BC, 0, 0);
    while (sub_00048890(0x2BC, 0, 0))
        sub_000580D0();
    sub_0019B9F0();
    sub_000325A0(0);
}

/* 0x00078E70: ending sequence step: start the credits fade, then switch to chapter 0x18. */
void r6d_EndingStep(void)
{
    sub_0004ECD0(0);
    sub_0004ECE0(0);
    sub_0004ECF0(0);
    sub_0004ED00(0);
    sub_0004ED20(0);
    sub_0004ED40(0);
    switch (a60_v3E750C) {
    case 0:
        sub_0019FCF0(4, 0, 9, r6d_b413147 != 0, 1, 1);
        sub_001A0D30(6, 0);
        sub_001A8A70(1);
        a60_v3E750C++;
        break;
    case 1:
        if (a60_v3E74B8 == 1) {
            sub_00077EF0();
            a9b_g413168 = 0x18;
            a9b_g413164 = 0;
            sub_000D9AB0(0xF4);
            sub_000D9AB0(0xF5);
            a60_v3E7530 = 4;
            sub_000408E0(2);
            sub_0019D8A0(2);
        }
        a60_v3E750C = 0;
        a60_v3E7510 = 0;
        a60_v3E7514 = 0;
        a60_v3E7508 = 1;
        break;
    }
}

/* 0x00079600: draw message 3 centred on the 512-pixel screen with a four-way shadow.
   calls 0x00079590 with EAX=x ECX=ctx */
void *r6d_DrawCentredMessage(void *ctx)
{
    const uint8_t *s = r6d_MsgGet(r6d_msgTables26F32C[a5b_GetVideoMode()], 3);
    int n = r6c_TextCount(s);
    int w = 0;
    int i;
    int x;
    for (i = 0; i < n; i++) {
        R6dGlyph *g = (R6dGlyph *)r1c_PagedElem(r6c_TextCharAt(s, i));
        if (g)
            w += g->width;
    }
    x = (0x200 - w) / 2;
    ctx = r6d_DrawString(x - 2, ctx, 0xD2, 0x80, s);
    ctx = r6d_DrawString(x + 2, ctx, 0xD2, 0x80, s);
    ctx = r6d_DrawString(x - 2, ctx, 0xD6, 0x80, s);
    ctx = r6d_DrawString(x + 2, ctx, 0xD6, 0x80, s);
    return r6d_DrawString(x, ctx, 0xD4, -1, s);
}
