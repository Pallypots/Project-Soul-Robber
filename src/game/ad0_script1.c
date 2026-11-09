/* Event-script opcode handlers 0x000D9BB0-0x000D9F3F. Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "ad0.h"
#include <string.h>

/* 0x000D9BB0: load the 128-byte script variable block from src. */
void Script_LoadVars(const void *src)
{
    memcpy(g_ad0_scriptVars, src, sizeof g_ad0_scriptVars);
}

/* 0x000D9BD0: save the 128-byte script variable block to dst. */
void Script_SaveVars(void *dst)
{
    memcpy(dst, g_ad0_scriptVars, sizeof g_ad0_scriptVars);
}

/* 0x000D9CC0: opcode with no effect: yield. */
int Op_Yield(ScriptCtx *c)
{
    return SCR_NEXTYIELD(0);
}

/* 0x000D9CD0: relative jump by signed 16-bit offset. */
int Op_Jump(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000D9D00: relative jump by 32-bit offset. */
int Op_JumpFar(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    c->pc = p + OP_U32(p);
    return SCR_JUMPED;
}

/* 0x000D9D30: call: push return address (past the operand), jump. */
int Op_Call(ScriptCtx *c)
{
    uint8_t *p;
    c->stack[c->depth] = c->pc + 4;
    c->depth++;
    p = c->pc;
    c->pc = p + OP_U32(p);
    return SCR_JUMPED;
}

/* 0x000D9D80: return from call. */
int Op_Return(ScriptCtx *c)
{
    c->depth--;
    c->pc = c->stack[c->depth];
    return SCR_JUMPED;
}

/* 0x000D9DA0: store the operand byte in 0x0042CAE0 and yield. */
int Op_Set42CAE0(ScriptCtx *c)
{
    g_ad0_42CAE0 = c->pc[0];
    return SCR_WAIT;
}

/* 0x000D9DC0: clear (mode 0) or set (mode 1) script flag bits. */
int Op_ScriptFlags(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    uint16_t bits;
    switch (p[0]) {
    case 0:
        memcpy(&bits, p + 1, sizeof bits);
        c->flags &= ~bits;
        break;
    case 1:
        memcpy(&bits, p + 1, sizeof bits);
        c->flags |= bits;
        return SCR_NEXT(3);
    }
    return SCR_NEXT(3);
}

/* 0x000D9E00: jump if 0x000DFD00 reports false. */
int Op_JumpIfNotDFD00(ScriptCtx *c)
{
    uint8_t *p;
    if (sub_000DFD00() != 0)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000D9E30: start a wait of (float operand * scale). */
int Op_SetWait(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    uint32_t bits = OP_U32(p);
    c->wait = g_ad0_waitScale * *(float *)&bits;
    return SCR_NEXT(4);
}

/* 0x000D9E70: yield while the wait timer is positive. */
int Op_WaitTimer(ScriptCtx *c)
{
    if (c->wait <= 0.0f)
        return SCR_NEXT(0);
    return SCR_WAIT;
}

/* 0x000D9E90 */
int Op_DFD10(ScriptCtx *c)
{
    sub_000DFD10(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000D9EB0 */
int Op_19D7A0(ScriptCtx *c)
{
    uint8_t *p;
    sub_0003DD00();
    p = c->pc;
    sub_0019D7A0(p[0], p[1]);
    return SCR_WAIT;
}

/* 0x000D9EE0 */
int Op_DFD30(ScriptCtx *c)
{
    sub_000DFD30(c->pc[0]);
    return SCR_NEXT(1);
}

/* 0x000D9F00: yield while 0x000DDE80 is true. */
int Op_WaitDDE80(void)
{
    return sub_000DDE80() ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000D9F20: opcode that skips one operand byte. */
int Op_Skip1(void)
{
    return SCR_NEXT(1);
}

/* 0x000D9F30: restart the script from the beginning. */
int Op_Restart(ScriptCtx *c)
{
    c->pc = c->start;
    return SCR_RESTART;
}
