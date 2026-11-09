/* Event-script opcode handlers 0x000DB2B0-0x000DBE90. Reference build
 * OOGIE-XBOX-US-RETAIL. Names inferred (Hypothesis). */
#include "ae0.h"

/* 0x000DB2B0: set or clear player flag bit 1 (operand 1 = set). */
int ae0_Op_PlayerFlag2(Ae0Script *c)
{
    if (c->pc[0] == 1)
        PlayerObj_SetFlags((PlayerObj *)&g_stats, 2, 0);
    else
        PlayerObj_ClearFlags((PlayerObj *)&g_stats, 2, 0);
    return AE0_NEXT(1);
}

/* 0x000DB2F0: conditional relative jump on flag bit 1 of 0x00420010. */
int ae0_Op_JumpOnFlag(Ae0Script *c)
{
    uint8_t *p = c->pc;
    if (p[0] != 0) {
        if (!(ae0_flags420010 & 2))
            return AE0_NEXT(3);
    } else {
        if (ae0_flags420010 & 2)
            return AE0_NEXT(3);
    }
    c->pc = p + ae0_ReadS16(p + 1) + 1;
    return AE0_JUMPED;
}

/* 0x000DB330: run three reset helpers and yield. */
int ae0_Op_DB330(void)
{
    sub_000DDF40();
    sub_00087450();
    sub_000D9020();
    return AE0_NEXTYIELD(0);
}

/* 0x000DB350: look up an object and pass its +0x60 block to 0x000CF330. */
int ae0_Op_DB350(Ae0Script *c)
{
    uint8_t *p = c->pc;
    uint8_t *o = (uint8_t *)sub_000DE170(p[0], p[1]);
    if (o)
        sub_000CF330(&g_stats, o + 0x60, 8.0f);
    return AE0_NEXT(2);
}

/* 0x000DB390: book a spawn point. */
int ae0_Op_BookSpawn(Ae0Script *c)
{
    uint8_t *p = c->pc;
    sub_000DDEF0(p[0], p[1]);
    return AE0_NEXT(2);
}

/* 0x000DB430: operand 1 calls 0x000D1D00, otherwise clears player flags. */
int ae0_Op_DB430(Ae0Script *c)
{
    if (c->pc[0] == 1)
        sub_000D1D00(&g_stats);
    else
        PlayerObj_ClearFlags22((PlayerObj *)&g_stats);
    return AE0_NEXT(1);
}

/* 0x000DB4F0: operand 1 calls 0x0001D610 on the player object, else 0x0001D700. */
int ae0_Op_DB4F0(Ae0Script *c)
{
    if (c->pc[0] == 1)
        sub_0001D610(g_playerObj);
    else
        sub_0001D700(g_playerObj);
    return AE0_NEXT(1);
}

/* 0x000DB530 */
int ae0_Op_DB530(Ae0Script *c)
{
    sub_000DE530(c->pc[0]);
    sub_00087450();
    sub_000D9020();
    return AE0_NEXT(1);
}

/* 0x000DB560: set or clear player flag bit 4 (operand nonzero = set). */
int ae0_Op_PlayerFlag10(Ae0Script *c)
{
    if (c->pc[0] != 0)
        PlayerObj_SetFlags((PlayerObj *)&g_stats, 0x10, 0);
    else
        PlayerObj_ClearFlags((PlayerObj *)&g_stats, 0x10, 0);
    return AE0_NEXT(1);
}

/* 0x000DB5A0: wait until the player is idle, not in state 2 and stat 1 is nonzero. */
int ae0_Op_WaitPlayerReady(void)
{
    if (PlayerObj_IsIdle((PlayerObj *)&g_stats) != 1)
        return AE0_WAIT;
    if (PlayerObj_GetState((PlayerObj *)&g_stats) == 2)
        return AE0_WAIT;
    return Stats_Get(&g_stats, 1) ? AE0_NEXT(0) : AE0_WAIT;
}

/* 0x000DB5F0: set player flag 0x200000 and call 0x000BD4D0(stats, 0x1F). */
int ae0_Op_DB5F0(void)
{
    PlayerObj_SetFlags((PlayerObj *)&g_stats, 0x200000, 0);
    sub_000BD4D0(&g_stats, 0x1F);
    return AE0_NEXT(0);
}

/* 0x000DB620 */
int ae0_Op_DB620(Ae0Script *c)
{
    sub_000E6CE0(c->pc[0]);
    return AE0_NEXT(1);
}

/* 0x000DB640: wait for 0x000E5CF0 with 0x000325A0 toggled on meanwhile. */
int ae0_Op_DB640(void)
{
    sub_000325A0(1);
    if (sub_000E5CF0() != 1)
        return AE0_WAIT;
    sub_000325A0(0);
    return AE0_NEXT(0);
}

/* 0x000DB670 */
int ae0_Op_DB670(void)
{
    sub_000E5D50();
    return AE0_NEXT(0);
}

/* 0x000DB680: wait until 0x000E3370 returns 1. */
int ae0_Op_DB680(void)
{
    return sub_000E3370() == 1 ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DB6A0 */
int ae0_Op_DB6A0(void)
{
    sub_000E4F70();
    return AE0_NEXT(0);
}

/* 0x000DB6B0: wait while 0x000E3050 is not 1. */
int ae0_Op_DB6B0(void)
{
    return sub_000E3050() != 1 ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DB6D0: wait while 0x00087AF0 is true. */
int ae0_Op_DB6D0(void)
{
    return sub_00087AF0() ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DB6F0 */
int ae0_Op_DB6F0(void)
{
    sub_00087B00();
    return sub_00089040() ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DB710 */
int ae0_Op_DB710(Ae0Script *c)
{
    if (c->pc[0] != 7)
        sub_000325A0(1);
    if (sub_00089010(c->pc[0]))
        return AE0_WAIT;
    sub_000325A0(0);
    return AE0_NEXT(1);
}

/* 0x000DB760: wait until 0x00088150 is true. */
int ae0_Op_DB760(void)
{
    return sub_00088150() ? AE0_NEXT(0) : AE0_WAIT;
}

/* 0x000DB780: wait while 0x00089040 is true. */
int ae0_Op_DB780(void)
{
    return sub_00089040() ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DB7A0 */
int ae0_Op_DB7A0(Ae0Script *c)
{
    sub_00087B60(c->pc[0]);
    return AE0_NEXT(1);
}

/* 0x000DB7C0 */
int ae0_Op_DB7C0(void)
{
    sub_00087B90();
    return AE0_NEXT(0);
}

/* 0x000DB7D0 */
int ae0_Op_DB7D0(void)
{
    sub_00087BA0();
    return AE0_NEXT(0);
}

/* 0x000DB7E0 */
int ae0_Op_DB7E0(void)
{
    if (sub_00086290())
        return AE0_WAIT;
    sub_00048590();
    return AE0_NEXT(0);
}

/* 0x000DB800: wait until 0x00047950 is true. */
int ae0_Op_DB800(void)
{
    return sub_00047950() ? AE0_NEXT(0) : AE0_WAIT;
}

/* 0x000DB820: fetch a pair and call 0x000487F0 for both sides. */
int ae0_Op_DB820(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    sub_000487F0(a, b, 0);
    sub_000487F0(a, b, 1);
    return AE0_NEXT(0);
}

/* 0x000DB8C0 */
int ae0_Op_DB8C0(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    sub_000488F0(a, b);
    return AE0_NEXT(0);
}

/* 0x000DB8F0: wait until 0x00048910(pair) returns 2. */
int ae0_Op_DB8F0(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    return sub_00048910(a, b) != 2 ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DB930 */
int ae0_Op_DB930(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    sub_00048860(a, b, 0);
    sub_00048860(a, b, 1);
    return AE0_NEXT(0);
}

/* 0x000DB970: no-op opcode. */
int ae0_Op_Nop(void)
{
    return AE0_NEXT(0);
}

/* 0x000DB980 */
int ae0_Op_DB980(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    sub_00048940(a, b);
    return AE0_NEXT(0);
}

/* 0x000DB9B0 */
int ae0_Op_DB9B0(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    sub_000488C0(a, b, 0);
    sub_000488C0(a, b, 1);
    return AE0_NEXT(0);
}

/* 0x000DBA50 */
int ae0_Op_DBA50(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    sub_000489A0(a, b);
    return AE0_NEXT(0);
}

/* 0x000DBA80: wait while 0x000489D0(pair) is true. */
int ae0_Op_DBA80(void)
{
    int a, b;
    sub_000DFD40(&a, &b);
    return sub_000489D0(a, b) ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DBAC0 */
int ae0_Op_DBAC0(Ae0Script *c)
{
    sub_00048110(ae0_ReadS16(c->pc));
    return AE0_NEXT(2);
}

/* 0x000DBAF0 */
int ae0_Op_DBAF0(Ae0Script *c)
{
    sub_000481B0(ae0_ReadS16(c->pc));
    return AE0_NEXT(2);
}

/* 0x000DBB20 */
int ae0_Op_DBB20(void)
{
    sub_00048270();
    return AE0_NEXT(0);
}

/* 0x000DBB30 */
int ae0_Op_DBB30(void)
{
    if (sub_00047F40())
        return AE0_WAIT;
    return sub_00047EE0() != 5 ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DBB60 */
int ae0_Op_DBB60(Ae0Script *c)
{
    sub_00022750(c->pc[0]);
    return AE0_NEXT(1);
}

/* 0x000DBB80: wait until 0x00022770 returns 3. */
int ae0_Op_DBB80(void)
{
    return sub_00022770() != 3 ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DBBA0 */
int ae0_Op_DBBA0(Ae0Script *c)
{
    uint8_t *p;
    sub_00019000(ae0_obj3E1270, c->pc[0]);
    p = c->pc;
    sub_0001AB00(ae0_obj3E1270, p[0], p[1], p[2], 1);
    return AE0_NEXT(3);
}

/* 0x000DBBE0 */
int ae0_Op_DBBE0(Ae0Script *c)
{
    sub_00019000(ae0_obj3E1270, c->pc[0]);
    return AE0_NEXT(1);
}

/* 0x000DBC00 */
int ae0_Op_DBC00(Ae0Script *c)
{
    uint8_t *p = c->pc;
    sub_00036C00(p[0], p[1], AE0_U32(p + 2));
    return AE0_NEXT(6);
}

/* 0x000DBC40 */
int ae0_Op_DBC40(void)
{
    return sub_00036D40() ? AE0_WAIT : AE0_NEXT(0);
}

/* 0x000DBC60 */
int ae0_Op_DBC60(void)
{
    sub_00036BC0();
    return AE0_NEXT(0);
}

/* 0x000DBC70 */
int ae0_Op_DBC70(Ae0Script *c)
{
    uint8_t *p = c->pc;
    void *o = sub_000DE170(p[0], p[1]);
    if (o)
        sub_00174410(o);
    return AE0_NEXT(2);
}

/* 0x000DBCA0 */
int ae0_Op_DBCA0(void)
{
    return sub_001729D0() ? AE0_NEXT(0) : AE0_WAIT;
}

/* 0x000DBCC0 */
int ae0_Op_DBCC0(Ae0Script *c)
{
    sub_00174470(c->pc[0]);
    return AE0_NEXT(1);
}

/* 0x000DBCE0 */
int ae0_Op_DBCE0(void)
{
    sub_001744C0();
    return AE0_NEXT(0);
}

/* 0x000DBCF0 */
int ae0_Op_DBCF0(Ae0Script *c)
{
    uint8_t *p = c->pc;
    void *o = sub_000DE170(p[0], p[1]);
    if (o)
        sub_00172A00(o, c->pc[2]);
    return AE0_NEXT(3);
}

/* 0x000DBD30 */
int ae0_Op_DBD30(Ae0Script *c)
{
    uint8_t *p = c->pc;
    void *o = sub_000DE170(p[0], p[1]);
    if (o) {
        if (c->pc[2])
            sub_000CEDF0(o);
        else
            sub_000CEDA0(o);
    }
    return AE0_NEXT(3);
}

/* 0x000DBD80 */
int ae0_Op_DBD80(Ae0Script *c)
{
    uint8_t *p = c->pc;
    if (p[1])
        sub_000DE9E0(p[0]);
    else
        sub_000DEA00(p[0]);
    return AE0_NEXT(2);
}

/* 0x000DBE20 */
int ae0_Op_DBE20(Ae0Script *c)
{
    uint8_t *p = c->pc;
    sub_000DDEE0(p[0], AE0_U32(p + 1));
    return AE0_NEXT(5);
}

/* 0x000DBE60 */
int ae0_Op_DBE60(Ae0Script *c)
{
    if (ae0_ptr3F6100)
        sub_000F3B70(ae0_ptr3F6100, c->pc[0]);
    return AE0_NEXT(1);
}

/* 0x000DBE90: opcode that skips three operand bytes. */
int ae0_Op_Skip3(void)
{
    return AE0_NEXT(3);
}
