/* Event-script opcode handlers 0x000DA3B0-0x000DA9D8. Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "ad0.h"

/* 0x000DA4A0: if operand is 0 or 0x0019FEE0 is false, call
 * 0x00032140(1, 2, 0) and continue; otherwise yield. */
int Op_DA4A0(ScriptCtx *c)
{
    if (c->pc[0] != 0 && sub_0019FEE0() != 0)
        return SCR_WAIT;
    sub_00032140(1, 2, 0);
    return SCR_NEXT(1);
}

/* 0x000DA4D0 */
int Op_A9D40(ScriptCtx *c)
{
    sub_000A9D40(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DA4F0: yield while 0x000A9D80(operand) is true. */
int Op_WaitA9D80(ScriptCtx *c)
{
    return sub_000A9D80(c->pc[0]) ? SCR_WAIT : SCR_NEXT(1);
}

/* 0x000DA520: add 1 to player stat (13 + operand). */
int Op_StatInc(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    sub_000D1E10(&g_stats, OP_S16(p) + 13, 1);
    return SCR_NEXT(2);
}

/* 0x000DA550: subtract 1 from player stat (13 + operand). */
int Op_StatDec(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    sub_000D1E10(&g_stats, OP_S16(p) + 13, -1);
    return SCR_NEXT(2);
}

/* 0x000DA760 */
int Op_DA760(ScriptCtx *c)
{
    sub_000408B0(c->pc[0]);
    sub_000408C0(0);
    sub_001A0D30(8, 0);
    return SCR_NEXTYIELD(2);
}

/* 0x000DA940: opcode that skips two operand bytes. */
int Op_Skip2(void)
{
    return SCR_NEXT(2);
}

/* 0x000DA9C0 */
int Op_DE330(ScriptCtx *c)
{
    sub_000DE330(c->pc[0]);
    return SCR_NEXT(1);
}
