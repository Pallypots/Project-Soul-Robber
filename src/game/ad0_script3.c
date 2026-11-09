/* Event-script opcode handlers 0x000DAA80-0x000DB083. Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "ad0.h"

/* 0x000DAA80: opcode that skips four operand bytes. */
int Op_Skip4(void)
{
    return SCR_NEXT(4);
}

/* 0x000DAA90: jump unless 0x003FD7BC is set. */
int Op_JumpIfNot3FD7BC(ScriptCtx *c)
{
    uint8_t *p;
    if (g_ad0_3FD7BC != 0)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DAAC0: jump if 0x000EDA50 reports false. */
int Op_JumpIfNotEDA50(ScriptCtx *c)
{
    uint8_t *p;
    if (sub_000EDA50() != 0)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DAAF0: jump if 0x000EDA90 reports false. */
int Op_JumpIfNotEDA90(ScriptCtx *c)
{
    uint8_t *p;
    if (sub_000EDA90() != 0)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DAEC0 */
int Op_60B70(ScriptCtx *c)
{
    sub_00060B70(c->pc[0]);
    return SCR_NEXTYIELD(1);
}

/* 0x000DAEE0: yield while 0x00060BD0 is true. */
int Op_Wait60BD0(void)
{
    return sub_00060BD0() ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000DAF00: yield while 0x0005F860 is true, then call 0x000E00D0. */
int Op_Wait5F860(void)
{
    if (sub_0005F860() != 0)
        return SCR_WAIT;
    sub_000E00D0();
    return SCR_NEXT(0);
}

/* 0x000DAF20 */
int Op_38070(ScriptCtx *c)
{
    sub_00038070(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DAFA0: yield while 0x00086B30 is true. */
int Op_Wait86B30(void)
{
    return sub_00086B30() ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000DAFC0: yield while 0x00087570(0x0041316C, 0x00413170) is true. */
int Op_Wait87570(void)
{
    return sub_00087570(g_ad0_41316C, g_ad0_413170) ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000DAFF0 */
int Op_EE0C0(void)
{
    sub_000EE0C0();
    return SCR_NEXTYIELD(0);
}

/* 0x000DB000 */
int Op_47BF0(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    sub_00047BF0(OP_S16(p));
    return SCR_NEXTYIELD(2);
}

/* 0x000DB030 */
int Op_DB030(void)
{
    sub_00054160(0);
    sub_00054170(0);
    sub_0019E850();
    return SCR_NEXTYIELD(0);
}

/* 0x000DB050 */
int Op_19D450(ScriptCtx *c)
{
    sub_0019D450(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DB070: yield while 0x000DEA40 is true. */
int Op_WaitDEA40(void)
{
    return sub_000DEA40() ? SCR_WAIT : SCR_NEXT(0);
}
