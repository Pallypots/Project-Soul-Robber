/* Area r2b, group 4: flag reset and event-script opcode handlers
   (0x000D9BF0..0x000DAFFF). Names inferred. */
#include "r2b.h"

/* 0x000D9BF0: clear the script flag block and set the bits listed at 0x300F38. */
void r2b_ResetBits(void)
{
    const int32_t *p;
    r2b_bits3EDC38[0] = 0;
    r2b_bits3EDC38[1] = 0;
    r2b_bits3EDC38[2] = 0;
    r2b_bits3EDC38[3] = 0;
    r2b_bits3EDC38[4] = 0;
    r2b_bits3EDC38[5] = 0;
    r2b_bits3EDC38[6] = 0;
    r2b_bits3EDC38[7] = 0;
    r2b_bits3EDC38[8] = 0;
    r2b_bits3EDC38[9] = 0;
    r2b_bits3EDC38[10] = 0;
    r2b_bits3EDC38[11] = 0;
    r2b_bits3EDC38[12] = 0;
    r2b_bits3EDC38[13] = 0;
    r2b_bits3EDC38[14] = 0;
    r2b_bits3EDC38[15] = 0;
    r2b_bits3EDC38[16] = 0;
    r2b_bits3EDC38[17] = 0;
    r2b_bits3EDC38[18] = 0;
    r2b_bits3EDC38[19] = 0;
    r2b_bits3EDC38[20] = 0;
    r2b_bits3EDC38[21] = 0;
    r2b_bits3EDC38[22] = 0;
    r2b_bits3EDC38[23] = 0;
    r2b_bits3EDC38[24] = 0;
    r2b_bits3EDC38[25] = 0;
    r2b_bits3EDC38[26] = 0;
    r2b_bits3EDC38[27] = 0;
    r2b_bits3EDC38[28] = 0;
    r2b_bits3EDC38[29] = 0;
    r2b_bits3EDC38[30] = 0;
    r2b_bits3EDC38[31] = 0;
    for (p = r2b_bits300F38; *p != -1; p++)
        r2b_SetBit(*p);
}

/* 0x000D9F40: jump by the second operand unless flag bit S16 equals operand byte 2
   (set / clear); otherwise skip 5 operand bytes. */
int r2b_OpJumpIfBit(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (p[2]) {
        if (!r2b_TestBit(OP_S16(p)))
            return SCR_NEXT(5);
    } else if (r2b_TestBit(OP_S16(p)))
        return SCR_NEXT(5);
    p = c->pc;
    c->pc = p + 3 + OP_S16(p + 3);
    return SCR_JUMPED;
}

/* 0x000D9FA0: set (byte 2 == 1) or clear flag bit S16. */
int r2b_OpSetBit(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (p[2] == 1)
        r2b_SetBit(OP_S16(p));
    else
        r2b_ClearBit(OP_S16(p));
    return SCR_NEXT(3);
}

/* 0x000DA3B0: wait until variable 0x3EE6AC is 5. */
int r2b_OpWaitVar5(void)
{
    return af0_GetVar3EE6AC() != 5 ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000DA580: decrement stat S16+13 and increment stat S16(+2)+13. */
int r2b_OpStatMove(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int b = OP_S16(p + 2) + 13;
    sub_000D1E10(&g_stats, OP_S16(p) + 13, -1);
    sub_000D1E10(&g_stats, b, 1);
    return SCR_NEXT(4);
}

/* 0x000DA5D0: jump by the second operand unless stat S16+13 being nonzero matches
   operand byte 2; otherwise skip 5 operand bytes. */
int r2b_OpJumpIfStat(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (p[2]) {
        if (!Stats_Get(&g_stats, OP_S16(p) + 13))
            return SCR_NEXT(5);
    } else if (Stats_Get(&g_stats, OP_S16(p) + 13))
        return SCR_NEXT(5);
    p = c->pc;
    c->pc = p + 3 + OP_S16(p + 3);
    return SCR_JUMPED;
}

/* 0x000DA420: operand byte 1 == 0: start track n (with 0x0C extra for track 0x2C);
   otherwise switch to the n-th music setting.  Advances 2 bytes and yields. */
int r2b_OpMusic(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int n = p[0];
    if (!p[1]) {
        sub_0003DD00();
        sub_001A0D30(0xB, n);
        sub_00049A40(1, n);
        if (n == 0x2C)
            sub_00049B00(0xC);
    } else {
        sub_0019FCF0(n, 0, 9, 1, 1, 1);
        sub_001A0D30(6, 0);
        sub_001A8A70(1);
        sub_00049A40(0, n);
    }
    return SCR_NEXTYIELD(2);
}

/* 0x000DA640: set the two channel levels for preset p[0] (0..3). */
int r2b_OpSetLevels(ScriptCtx *c)
{
    switch (c->pc[0]) {
    case 0:
        sub_00032140(0, 1, 0);
        sub_00032140(1, 1, 0x12C);
        break;
    case 2:
        sub_00032140(0, 2, 0);
        sub_00032140(1, 1, 0);
        break;
    case 1:
    case 3:
        sub_00032140(0, 3, 0);
        sub_00032140(1, 0, 0);
        break;
    }
    return SCR_NEXT(1);
}

/* 0x000DA6D0: chapter change: ids above 0x18 go to 0x0408B0, else enter chapter p[0]
   (or the current one when p[1] is 0).  Advances 2 bytes and yields. */
int r2b_OpChapter(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (p[0] <= 0x18) {
        if (!p[1]) {
            sub_000408D0(1);
            sub_0019D830(a9b_g413164);
        } else {
            sub_000408D0(0);
            sub_0019D7F0(c->pc[0]);
        }
        af0_SetVar3EDCC0(1);
        return SCR_NEXTYIELD(2);
    }
    sub_000408B0(p[0]);
    sub_000408C0(1);
    sub_001A0D30(8, 0);
    return SCR_NEXTYIELD(2);
}

/* 0x000DA950: play voice S16(p+1) + variant (0, 2 or 3 by p[0]) unless one is playing
   or mode 0x1F is active. */
int r2b_OpVoice(ScriptCtx *c)
{
    int k;
    if (sub_00047BB0() <= 0 && b3b_mode42CAFC != 0x1F) {
        switch (c->pc[0]) {
        case 0:
            k = 0;
            break;
        case 1:
            k = 2;
            break;
        case 2:
            k = 3;
            break;
        }
        sub_00048A00(OP_S16(c->pc + 1) + k, 1000);
    }
    return SCR_NEXT(3);
}

/* 0x000DAB20: jump by S16(p+2) unless 0x0EDA20(p[0], p[1]) holds. */
int r2b_OpJumpIfNotEDA20(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (sub_000EDA20(p[0], p[1]))
        return SCR_NEXT(4);
    p = c->pc;
    c->pc = p + 2 + OP_S16(p + 2);
    return SCR_JUMPED;
}

/* 0x000DADC0: jump by S16 when 0x060BD0() holds. */
int r2b_OpJumpIf60BD0(ScriptCtx *c)
{
    uint8_t *p;
    if (!sub_00060BD0())
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DAF40: start the 0x0869C0 sequence once and wait until it ends, then restore
   the block at 0x3EDC00 from Jack. */
int r2b_OpWait869C0(void)
{
    if (!r2b_g3EDCB8) {
        sub_0019B9E0();
        sub_000325A0(1);
        r2b_g3EDCB8 = 1;
    }
    if (sub_000869C0())
        return SCR_WAIT;
    sub_000325A0(0);
    sub_00087450();
    r2b_BlkFromPlayer();
    r2b_g3EDCB8 = 0;
    sub_0019B9F0();
    return SCR_NEXT(0);
}

/* 0x000DB3B0: jump by S16(p+1) unless Jack passes test p[0] (0: idle, 1: state not 2,
   2: stat 1 nonzero; the tests chain downwards). */
int r2b_OpJumpIfPlayer(ScriptCtx *c)
{
    uint8_t *p;
    switch (c->pc[0]) {
    case 0:
        if (PlayerObj_IsIdle((PlayerObj *)&g_stats) != 1)
            break;
    case 1:
        if (PlayerObj_GetState((PlayerObj *)&g_stats) == 2)
            break;
    case 2:
        if (!Stats_Get(&g_stats, 1))
            break;
    default:
        return SCR_NEXT(3);
    }
    p = c->pc;
    c->pc = p + 1 + OP_S16(p + 1);
    return SCR_JUMPED;
}

/* 0x000DB460: when Jack is alive, look up entry (p[0], p[1]) and apply its two vectors
   through 0x0CC230 (not in stats modes 0x22 / 0x23). */
int r2b_OpStatCC230(ScriptCtx *c)
{
    float a[4], b[4];
    int i;
    if (Stats_Get(&g_stats, 1)) {
        i = sub_000DE100(c->pc[0], c->pc[1]);
        if (i != -1 && sub_000E0640(c->pc[1], b, a) &&
            g_stats.unkD8 != 0x22 && g_stats.unkD8 != 0x23)
            sub_000CC230(&g_stats, i, b, a);
    }
    return SCR_NEXT(2);
}

/* 0x000DB860: wait until key (x, y) from 0x0DFD40 reaches state 2 in both modes. */
int r2b_OpWaitKey(void)
{
    int y, x;
    sub_000DFD40(&x, &y);
    if (r1_KeyStateW(x, y, 0) != 2)
        return SCR_WAIT;
    return r1_KeyStateW(x, y, 1) != 2 ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000DB9F0: wait until 0x0AD090(x, y, mode) clears for both modes. */
int r2b_OpWaitAD090(void)
{
    int y, x;
    sub_000DFD40(&x, &y);
    if (r2b_AD090(x, y, 0))
        return SCR_WAIT;
    return r2b_AD090(x, y, 1) ? SCR_WAIT : SCR_NEXT(0);
}

/* 0x000DBDC0: jump by S16(p+2) unless 0x0DEA20(p[0]) being set matches p[1]. */
int r2b_OpJumpIfDEA20(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (p[1]) {
        if (!sub_000DEA20(p[0]))
            return SCR_NEXT(4);
    } else if (sub_000DEA20(p[0]))
        return SCR_NEXT(4);
    p = c->pc;
    c->pc = p + 2 + OP_S16(p + 2);
    return SCR_JUMPED;
}

/* 0x000DC0D0: wait until level query p[0] (0..9) returns p[1]. */
int r2b_OpWaitLevel(ScriptCtx *c)
{
    int r;
    switch (c->pc[0]) {
    case 0: r = a12_Level_37C544(); break;
    case 1: r = a12_Level_37D434(); break;
    case 2: r = a12_Level_37DAA4(); break;
    case 3: r = a12_Level_37DC28(); break;
    case 4: r = a12_Level_37DCFC(); break;
    case 5: r = a12_Level_37ED04(); break;
    case 6: r = a12_Level_37E094(); break;
    case 7: r = a12_Level_37EECC(); break;
    case 8: r = a12_FlagBit0(); break;
    case 9: r = a12_FlagBit1(); break;
    default:
        return SCR_NEXT(2);
    }
    return r == c->pc[1] ? SCR_NEXT(2) : SCR_WAIT;
}

/* 0x000DC3C0: jump by S16(p+2) when the current chapter compares to p[1] by test p[0]
   (0 ==, 1 !=, 2 >=, 3 <=, 4 >, 5 <). */
int r2b_OpJumpIfChapter(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int v = p[1];
    switch (p[0]) {
    case 0:
        if (a9b_g413164 != v)
            return SCR_NEXT(4);
        break;
    case 1:
        if (a9b_g413164 == v)
            return SCR_NEXT(4);
        break;
    case 2:
        if (a9b_g413164 < v)
            return SCR_NEXT(4);
        break;
    case 3:
        if (a9b_g413164 > v)
            return SCR_NEXT(4);
        break;
    case 4:
        if (a9b_g413164 <= v)
            return SCR_NEXT(4);
        break;
    case 5:
        if (a9b_g413164 >= v)
            return SCR_NEXT(4);
        break;
    default:
        return SCR_NEXT(4);
    }
    c->pc = p + 2 + OP_S16(p + 2);
    return SCR_JUMPED;
}

/* 0x000DC500: jump by S16(p+2) unless 0x19BE60(S16) holds. */
int r2b_OpJumpIfNot19BE60(ScriptCtx *c)
{
    uint8_t *p;
    if (sub_0019BE60(OP_S16(c->pc)))
        return SCR_NEXT(4);
    p = c->pc;
    c->pc = p + 2 + OP_S16(p + 2);
    return SCR_JUMPED;
}

/* 0x000DC550: jump by S16(p+2) unless 0x19BE70(S16) holds. */
int r2b_OpJumpIfNot19BE70(ScriptCtx *c)
{
    uint8_t *p;
    if (sub_0019BE70(OP_S16(c->pc)))
        return SCR_NEXT(4);
    p = c->pc;
    c->pc = p + 2 + OP_S16(p + 2);
    return SCR_JUMPED;
}

/* 0x000DC5A0: pass the 32-bit operand to 0x19BE90 (p[4] set) or 0x19BEB0. */
int r2b_OpSet19BE90(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (p[4])
        sub_0019BE90(OP_U32(p));
    else
        sub_0019BEB0(OP_U32(p));
    return SCR_NEXT(5);
}

/* 0x000DCD20: stop the four cue channels when a cue is active and forget it. */
int r2b_OpStopCues(R2bScriptCtx *s)
{
    int i;
    if (s->snd58 != -1) {
        for (i = 0; i < 4; i++)
            sub_00048330(i, 0);
        s->snd58 = -1;
    }
    return SCR_NEXTYIELD(0);
}

/* 0x000DCD50: jump by S16 when no cue is active or the active one has finished. */
int r2b_OpJumpIfCueDone(R2bScriptCtx *s)
{
    uint8_t *p;
    if (s->snd58 != -1 && sub_000482B0(s->snd58))
        return SCR_NEXT(2);
    p = s->c.pc;
    s->c.pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DCDB0: post command (1, p[0]) and pass p[1] to 0x19E870. */
int r2b_OpPostCmd(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int b = p[1];
    a60_PostCommand(1, p[0]);
    sub_0019E870(b);
    return SCR_NEXTYIELD(2);
}

/* 0x000DCDE0: jump by S16(p+3) unless 0x0DE4D0(p[0], p[1]) being set matches p[2]. */
int r2b_OpJumpIfDE4D0(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    if (p[2]) {
        if (!sub_000DE4D0(p[0], p[1]))
            return SCR_NEXT(5);
    } else if (sub_000DE4D0(p[0], p[1]))
        return SCR_NEXT(5);
    p = c->pc;
    c->pc = p + 3 + OP_S16(p + 3);
    return SCR_JUMPED;
}

/* 0x000DD120: jump by S16 unless mode 0 is not 1 and variable 0x3EE6AC is 5. */
int r2b_OpJumpUnlessVar5(ScriptCtx *c)
{
    uint8_t *p;
    if (r2b_GetMode0() != 1 && af0_GetVar3EE6AC() == 5)
        return SCR_NEXT(2);
    p = c->pc;
    c->pc = p + OP_S16(p);
    return SCR_JUMPED;
}

/* 0x000DD3F0: jump by S16(p+1) unless the current area is p[0] (area 4 also accepts
   0x02C810()). */
int r2b_OpJumpUnlessArea(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int n = p[0];
    if ((n == 4 && sub_0002C810() == n) || af0_GetVar3EDCF8() == n)
        return SCR_NEXT(3);
    p = c->pc;
    c->pc = p + 1 + OP_S16(p + 1);
    return SCR_JUMPED;
}

/* 0x000DDAC0: jump by S16(p+1)+1 unless 0x088150() being set matches p[0]. */
int r2b_OpJumpIf88150(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int n = p[0];
    int off = OP_S16(p + 1) + 1;
    if (sub_00088150()) {
        if (n)
            return SCR_NEXT(3);
    } else if (!n)
        return SCR_NEXT(3);
    c->pc += off;
    return SCR_JUMPED;
}

/* 0x000DD250: jump by S16(p+5) when stat S16+13 compares to stat S16(p+2)+13 by test
   p[4] (0 ==, 1 !=, 2 >=, 3 <=, 4 >, 5 <). */
int r2b_OpJumpIfStatCmp(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int ib = OP_S16(p + 2);
    int a = Stats_Get(&g_stats, OP_S16(p) + 13);
    int b = Stats_Get(&g_stats, ib + 13);
    p = c->pc;
    switch (p[4]) {
    case 0:
        if (a != b)
            return SCR_NEXT(7);
        break;
    case 1:
        if (a == b)
            return SCR_NEXT(7);
        break;
    case 2:
        if (a < b)
            return SCR_NEXT(7);
        break;
    case 3:
        if (a > b)
            return SCR_NEXT(7);
        break;
    case 4:
        if (a <= b)
            return SCR_NEXT(7);
        break;
    case 5:
        if (a >= b)
            return SCR_NEXT(7);
        break;
    default:
        return SCR_NEXT(7);
    }
    c->pc = p + 5 + OP_S16(p + 5);
    return SCR_JUMPED;
}

/* 0x000DD310: jump by S16(p+5) when stat S16+13 compares to the constant S16(p+2) by
   test p[4] (as 0x0DD250). */
int r2b_OpJumpIfStatK(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int b = OP_S16(p + 2);
    int a = Stats_Get(&g_stats, OP_S16(p) + 13);
    p = c->pc;
    switch (p[4]) {
    case 0:
        if (a != b)
            return SCR_NEXT(7);
        break;
    case 1:
        if (a == b)
            return SCR_NEXT(7);
        break;
    case 2:
        if (a < b)
            return SCR_NEXT(7);
        break;
    case 3:
        if (a > b)
            return SCR_NEXT(7);
        break;
    case 4:
        if (a <= b)
            return SCR_NEXT(7);
        break;
    case 5:
        if (a >= b)
            return SCR_NEXT(7);
        break;
    default:
        return SCR_NEXT(7);
    }
    c->pc = p + 5 + OP_S16(p + 5);
    return SCR_JUMPED;
}

/* 0x000DD4B0: interface command p[0]: 0 reset, 1 post (1, p[1]) and show p[2], 2 close,
   3 show (p[1], p[2]).  Advances 3 bytes and yields. */
int r2b_OpUi(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int a = p[1], b = p[2];
    switch (p[0]) {
    case 0:
        sub_00054160(0);
        sub_00054170(0);
        sub_0019E850();
        break;
    case 1:
        a60_PostCommand(1, a);
        sub_0019E870(b);
        break;
    case 2:
        sub_000DE910();
        break;
    case 3:
        sub_0019E8B0(a, b);
        break;
    }
    return SCR_NEXTYIELD(3);
}

/* 0x000DDA00: set (p[3] != 0) or clear flag bits S16 .. S16 + p[2]. */
int r2b_OpSetBitRange(ScriptCtx *c)
{
    uint8_t *p = c->pc;
    int i = OP_S16(p);
    int end = p[2] + i;
    if (!p[3]) {
        for (; i <= end; i++)
            r2b_ClearBit(i);
    } else {
        for (; i <= end; i++)
            r2b_SetBit(i);
    }
    return SCR_NEXT(4);
}

/* 0x000DDD00: when Jack is alive, look up entry (p[0], p[1]) and aim at its two
   vectors through 0x0CBD20 (not in stats modes 0x22 / 0x23). */
int r2b_OpSetTarget(ScriptCtx *c)
{
    float a[4], b[4];
    int i;
    if (Stats_Get(&g_stats, 1)) {
        i = sub_000DE100(c->pc[0], c->pc[1]);
        if (i != -1 && sub_000E0640(c->pc[1], b, a) &&
            g_stats.unkD8 != 0x22 && g_stats.unkD8 != 0x23)
            ac0_SetTarget(&g_stats, i, b, a);
    }
    return SCR_NEXT(2);
}
