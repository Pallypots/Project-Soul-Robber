/* Event-script opcode handlers 0x000DD160-0x000DD982. Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "adc.h"

/* 0x000DD160: wait until mode 0xD71E0 is not 1 and var 0x3EE6AC is 5. */
int adc_OpWaitMode5(ScriptCtx *c)
{
    if (sub_000D71E0() != 1 && sub_000DFDF0() == 5)
        return SCR_NEXT(0);
    return SCR_WAIT;
}

/* 0x000DD180: while the wait timer runs, jump by s16 and restart. */
int adc_OpLoopWhileWaiting(ScriptCtx *c)
{
    uint8_t *p;
    if (c->wait <= 0.0f)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_RESTART;
}

/* 0x000DD1B0: set flag 0x3ED238. */
int adc_OpSet3ED238(ScriptCtx *c)
{
    a80_Set3ED238();
    return SCR_NEXT(0);
}

/* 0x000DD1C0: wait until test(id) matches the expected byte. */
int adc_OpWaitTest(ScriptCtx *c)
{
    if (sub_000D9A70(OP_S16(c->pc))) {
        if (c->pc[2] == 0)
            return SCR_WAIT;
    } else {
        if (c->pc[2] != 0)
            return SCR_WAIT;
    }
    return SCR_NEXT(3);
}

/* 0x000DD210: event 4 then stat 0 adjust by 2. */
int adc_OpStat0Plus2(ScriptCtx *c)
{
    sub_00023D80(4, 0);
    sub_000D1E10(&g_stats, 0, 2);
    return SCR_NEXT(0);
}

/* 0x000DD230: set 0x3ED23C from a byte operand. */
int adc_OpSet3ED23C(ScriptCtx *c)
{
    a80_Set3ED23C(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DD3C0: call 0xDE970 and yield. */
int adc_OpCallDE970(ScriptCtx *c)
{
    sub_000DE970();
    return SCR_NEXTYIELD(0);
}

/* 0x000DD3D0: run 0xD9B30 over ids 0x38D..0x3AF. */
int adc_OpClearRange(ScriptCtx *c)
{
    int i;
    for (i = 0x38D; i < 0x3B0; i++)
        sub_000D9B30(i);
    return SCR_NEXT(0);
}

/* 0x000DD440: three byte operands to 0xDE6D0. */
int adc_OpDE6D0(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    sub_000DE6D0(p[0], p[1], p[2]);
    return SCR_NEXT(3);
}

/* 0x000DD470: wait for state 3, then 0x36F40(0,0,0,128). */
int adc_OpWaitState3(ScriptCtx *c)
{
    sub_0002E410();
    sub_000A96D0();
    if (af0_GetVar3EDCF8() != 3)
        return SCR_WAIT;
    sub_00036F40(0, 0, 0, 128.0f);
    return SCR_NEXTYIELD(0);
}

/* 0x000DD540: start sequence: state 1, clear 0x3EDCFC. */
int adc_OpStartState1(ScriptCtx *c)
{
    sub_0002C790();
    sub_000A86A0();
    af0_SetVar3EDCF8(1);
    af0_SetVar3EDCFC(0);
    return SCR_NEXT(0);
}

/* 0x000DD570: wait while 0x2CC20 is busy. */
int adc_OpTest2CC20(ScriptCtx *c)
{
    return sub_0002CC20() ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000DD590: byte operand to 0xDE8E0. */
int adc_OpDE8E0(ScriptCtx *c)
{
    sub_000DE8E0(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DD5B0: wait until 0x37FE0 is nonzero. */
int adc_OpWait37FE0(ScriptCtx *c)
{
    return sub_00037FE0() ? SCR_NEXT(0) : SCR_WAIT;
}

/* 0x000DD5D0: byte operand to 0x19C5E0. */
int adc_Op19C5E0(ScriptCtx *c)
{
    sub_0019C5E0(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DD5F0: three 32-bit operands to 0x19C5F0. */
int adc_Op19C5F0(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    sub_0019C5F0(OP_U32(p), OP_U32(p + 4), OP_U32(p + 8));
    return SCR_NEXT(12);
}

/* 0x000DD660: jump by s16 when var 0x3EDCFC is zero. */
int adc_OpJumpIfVarZero(ScriptCtx *c)
{
    uint8_t *p;
    if (af0_GetVar3EDCFC() != 0)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DD690: call 0xA86C0. */
int adc_OpA86C0(ScriptCtx *c)
{
    sub_000A86C0();
    return SCR_NEXT(0);
}

/* 0x000DD6A0: s16 operand to 0xDFCC0. */
int adc_OpDFCC0(ScriptCtx *c)
{
    sub_000DFCC0(OP_S16(c->pc));
    return SCR_NEXT(2);
}

/* 0x000DD6D0: stat 0 adjust by 2 and report stats 0 and 1. */
int adc_OpStatReport(ScriptCtx *c)
{
    int a;
    sub_000D1E10(&g_stats, 0, 2);
    a = Stats_Get(&g_stats, 0);
    sub_00026280(a, Stats_Get(&g_stats, 1));
    return SCR_NEXT(0);
}

/* 0x000DD710: wait for var 5 or timer expiry, then release. */
int adc_OpWaitRelease(ScriptCtx *c)
{
    if (sub_000DFDF0() == 5 || c->wait <= 0.0f) {
        af0_Release3EE6A8();
        return SCR_NEXT(0);
    }
    return SCR_WAIT;
}

/* 0x000DD7A0: byte operand; in mode 5 run AA490 and release, else wait on A9D80. */
int adc_OpModeA9D80(ScriptCtx *c)
{
    int v = c->pc[0];
    if (sub_000DFDF0() == 5) {
        sub_000AA490(v);
        af0_Release3EE6A8();
        return SCR_NEXT(1);
    }
    return sub_000A9D80(v) ? SCR_WAIT : SCR_NEXT(1);
}

/* 0x000DD7F0: s16 operand to 0x48160. */
int adc_Op48160(ScriptCtx *c)
{
    sub_00048160(OP_S16(c->pc));
    return SCR_NEXT(2);
}

/* 0x000DD820: s16 operand to 0x48200. */
int adc_Op48200(ScriptCtx *c)
{
    sub_00048200(OP_S16(c->pc));
    return SCR_NEXT(2);
}

/* 0x000DD850: call 0x5CA80. */
int adc_Op5CA80(ScriptCtx *c)
{
    sub_0005CA80();
    return SCR_NEXT(0);
}

/* 0x000DD860: pass ctx->+0x1F0 to 0x5C430. */
int adc_Op5C430(ScriptCtx *c)
{
    sub_0005C430(*(void **)(adc_ctx42C8E4 + 0x1F0));
    return SCR_NEXT(0);
}

/* 0x000DD8B0: byte operand as float to 0x36FD0. */
int adc_Op36FD0(ScriptCtx *c)
{
    sub_00036FD0((float)c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DD8E0: rumble with a byte operand when enabled. */
int adc_OpShock(ScriptCtx *c)
{
    if (adc_enabled413142)
        sub_0005EB10(0, c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DD910: byte operand to 0x49AA0. */
int adc_Op49AA0(ScriptCtx *c)
{
    sub_00049AA0(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000DD930: byte flag selects 0x19B9E0 or 0x19B9F0. */
int adc_Op19B9E0(ScriptCtx *c)
{
    if (c->pc[0] != 0)
        sub_0019B9E0();
    else
        sub_0019B9F0();
    return SCR_NEXT(1);
}

/* 0x000DD960: byte flag selects 0x169790 or 0x169730. */
int adc_Op169730(ScriptCtx *c)
{
    if (c->pc[0] == 0)
        sub_00169730();
    else
        sub_00169790();
    return SCR_NEXT(1);
}
