/* Event-script opcode handlers 0x000DDA70-0x000DDDDF. Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "adc.h"

/* 0x000DDA70: jump by s16+1 when the low-flag test matches the byte flag. */
int adc_OpJumpIfLowFlags(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int want = p[0];
    int off = ADC_S16(p + 1) + 1;
    if (sub_00087AF0()) {
        if (want == 0)
            return SCR_NEXT(3);
    } else {
        if (want != 0)
            return SCR_NEXT(3);
    }
    c->pc += off;
    return SCR_JUMPED;
}

/* 0x000DDB10: while 0x32450(1) is set, poke 0x32140 and wait. */
int adc_OpWait32450(ScriptCtx *c)
{
    if (sub_00032450(1)) {
        sub_00032140(1, 0, 0);
        return SCR_WAIT;
    }
    return SCR_NEXT(0);
}

/* 0x000DDB40: if 0x49B70 reports 1, pass it to 0x19E900; yield. */
int adc_Op19E900(ScriptCtx *c)
{
    if (sub_00049B70() == 1)
        sub_0019E900(1);
    return SCR_NEXTYIELD(0);
}

/* 0x000DDB60: set wait timer from the float operand selected by 0x413178. */
int adc_OpSetWaitIndexed(ScriptCtx *c)
{
    c->wait = g_ad0_waitScale * adc_ReadF32(c->pc + adc_413178 * 4);
    return SCR_NEXT(12);
}

/* 0x000DDBB0: wait until 0x47F60 is nonzero. */
int adc_OpWait47F60(ScriptCtx *c)
{
    return sub_00047F60() ? SCR_NEXT(0) : SCR_WAIT;
}

/* 0x000DDBD0: wait until 0xE03C0 reports 5. */
int adc_OpWaitE03C0(ScriptCtx *c)
{
    return sub_000E03C0() == 5 ? SCR_NEXT(0) : SCR_WAIT;
}

/* 0x000DDBF0: call 0xDF830. */
int adc_OpDF830(ScriptCtx *c)
{
    sub_000DF830();
    return SCR_NEXT(0);
}

/* 0x000DDC00: jump by s16 when 0xDF8E0 is zero. */
int adc_OpJumpIfDF8E0Zero(ScriptCtx *c)
{
    uint8_t *p;
    if (sub_000DF8E0() != 0)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DDC30: call 0xA9D00 and yield. */
int adc_OpA9D00(ScriptCtx *c)
{
    sub_000A9D00();
    return SCR_NEXTYIELD(0);
}

/* 0x000DDC40: start sound sequence and set 0x3EDD1C. */
int adc_OpSndStart(ScriptCtx *c)
{
    a5b_SndStart(0);
    a5b_SndBegin();
    af0_SetVar3EDD1C(1);
    return SCR_NEXT(0);
}

/* 0x000DDCD0: when event 0x4001 is clear and the byte is 7, call 0x264C0. */
int adc_Op264C0(ScriptCtx *c)
{
    int v = c->pc[1];
    if (sub_0019BE60(0x4001) == 0 && v == 7)
        sub_000264C0();
    return SCR_NEXT(2);
}

/* 0x000DDD90: two byte operands to 0x3AEB0. */
int adc_Op3AEB0(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    sub_0003AEB0(p[0], p[1]);
    return SCR_NEXT(2);
}

/* 0x000DDDB0: byte and test(s16) to 0x3AEB0. */
int adc_Op3AEB0Test(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int a = p[0];
    sub_0003AEB0(a, sub_000D9A70(ADC_S16(p + 1)));
    return SCR_NEXT(3);
}
