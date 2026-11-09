/* Area af0, group 1: event-script opcode handlers 0x000DC180..0x000DC700. Names inferred. */
#include "af0.h"

/* 0x000DC180: no-op opcode, wait. */
int af0_Op_Wait(Af0Script *s) { return 0x3000; }

/* 0x000DC190: set variable 0x3EDCBC from a byte operand. */
int af0_Op_SetVarBC(Af0Script *s) { af0_SetVar3EDCBC(s->pc[0]); return 0x2001; }
/* 0x000DC270: set variable 0x3EDCC4 from a byte operand. */
int af0_Op_SetVarC4(Af0Script *s) { af0_SetVar3EDCC4(s->pc[0]); return 0x2001; }
/* 0x000DC2D0: set variable 0x3EDCC8 from a byte operand. */
int af0_Op_SetVarC8(Af0Script *s) { af0_SetVar3EDCC8(s->pc[0]); return 0x2001; }
/* 0x000DC450: pass a byte operand to 0x000E03E0. */
int af0_Op_E03E0(Af0Script *s) { sub_000E03E0(s->pc[0]); return 0x2001; }
/* 0x000DC640: pass a byte operand to 0x00172A30. */
int af0_Op_172A30(Af0Script *s) { sub_00172A30(s->pc[0]); return 0x2001; }
/* 0x000DC690: pass a byte operand to 0x000D7480. */
int af0_Op_D7480(Af0Script *s) { sub_000D7480(s->pc[0]); return 0x2001; }

/* 0x000DC290: if variable 0x3EDCC4 differs from the byte operand, jump. */
int af0_Op_IfNotC4(Af0Script *s)
{
    uint8_t *pc;
    int v = af0_GetVar3EDCC4();
    pc = s->pc;
    if (v == pc[0])
        return 0x2003;
    s->pc = pc + AF0_RD16(pc + 1) + 1;
    return 0x1000;
}

/* 0x000DC2F0: if variable 0x3EDCC8 differs from the byte operand, jump. */
int af0_Op_IfNotC8(Af0Script *s)
{
    uint8_t *pc;
    int v = af0_GetVar3EDCC8();
    pc = s->pc;
    if (v == pc[0])
        return 0x2003;
    s->pc = pc + AF0_RD16(pc + 1) + 1;
    return 0x1000;
}

/* 0x000DC330: wait until variable 0x3EE6AC equals the byte operand. */
int af0_Op_WaitAC(Af0Script *s)
{
    return af0_GetVar3EE6AC() != s->pc[0] ? 0x3000 : 0x2001;
}

/* 0x000DC350: start 0x000D7100 with a word operand; jump unless it reports 1. */
int af0_Op_D7100(Af0Script *s)
{
    uint8_t *pc;
    sub_000D7100(AF0_RD16(s->pc));
    if (sub_000D71E0() == 1)
        return 0x2004;
    pc = s->pc;
    s->pc = pc + AF0_RD16(pc + 2) + 2;
    return 0x1000;
}

/* 0x000DC3A0: wait while 0x000D71E0 reports less than 2. */
int af0_Op_WaitD71E0(void)
{
    return sub_000D71E0() < 2 ? 0x3000 : 0x2000;
}

/* 0x000DC470: call 0x000DFC90. */
int af0_Op_DFC90(void) { sub_000DFC90(); return 0x2000; }

/* 0x000DC480: pass a word operand to 0x000DE400. */
int af0_Op_DE400(Af0Script *s) { sub_000DE400(AF0_RD16(s->pc)); return 0x2002; }

/* 0x000DC4B0: continue if variable 0x3EDCE8 is set and equals the word operand, else jump. */
int af0_Op_IfE8(Af0Script *s)
{
    uint8_t *pc;
    int v = af0_GetVar3EDCE8();
    if (v != 0 && v == AF0_RD16(s->pc))
        return 0x2004;
    pc = s->pc;
    s->pc = pc + AF0_RD16(pc + 2) + 2;
    return 0x1000;
}

/* 0x000DC600: jump unless variable 0x3EDCEC is set. */
int af0_Op_IfEC(Af0Script *s)
{
    uint8_t *pc;
    if (af0_GetVar3EDCEC() != 0)
        return 0x2002;
    pc = s->pc;
    s->pc = pc + AF0_RD16(pc);
    return 0x1000;
}

/* 0x000DC630: clear variable 0x3EDCEC. */
int af0_Op_ClearEC(void) { af0_ClearVar3EDCEC(); return 0x2000; }

/* 0x000DC660: set variable 0x3EDCE8 from a word operand. */
int af0_Op_SetE8(Af0Script *s) { af0_SetVar3EDCE8(AF0_RD16(s->pc)); return 0x2002; }

/* 0x000DC6B0: wait until 0x000D74D0 reports 2. */
int af0_Op_WaitD74D0(void)
{
    return sub_000D74D0() != 2 ? 0x3000 : 0x2000;
}

/* 0x000DC6D0: jump unless 0x000D8750 reports nonzero. */
int af0_Op_IfD8750(Af0Script *s)
{
    uint8_t *pc;
    if (sub_000D8750() != 0)
        return 0x2002;
    pc = s->pc;
    s->pc = pc + AF0_RD16(pc);
    return 0x1000;
}
