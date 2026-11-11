/* Area r2b, group 3: mode helpers and the block at 0x003EDC00 and the script flag bits (0x000D8FF0..0x000D9BA5).
   Names inferred. */
#include "r2b.h"

/* 0x000D8FF0: first word of pair i at 0x3EDC14. */
int r2b_PairA(int i)
{
    return r2b_pairs3EDC14[i].a;
}

/* 0x000D9000: second word of pair i at 0x3EDC14. */
int r2b_PairB(int i)
{
    return r2b_pairs3EDC14[i].b;
}

/* 0x000D9010: word +0x10 of the block at 0x3EDC00. */
int r2b_GetBlkI10(void)
{
    return r2_blk3EDC00.i10;
}

/* 0x000D9020: copy Jack's position into the block at 0x3EDC00 and clear its index. */
void r2b_BlkFromPlayer(void)
{
    sub_000F5D40(&r2_blk3EDC00, (uint8_t *)g_playerObj + 0x60);
    r2_blk3EDC00.i10 = -1;
}

/* 0x000D9A30: run both passes of 0x0D9180 and 0x0D97B0 on a, then store a in the
   block at 0x3EDC00.  calls 0x000D9180 with ECX=pass (a, b on the stack) and
   0x000D97B0 with ECX=a */
void r2b_BlkSetup(void *a, float b)
{
    sub_000D9180(0, a, b);
    sub_000D9180(1, a, b);
    sub_000D97B0(a);
    sub_000F5D40(&r2_blk3EDC00, a);
}

/* 0x000D9A70: bit i (0..0x3FF) of the script flag block 0x3EDC38. */
int r2b_TestBit(int i)
{
    if (i < 0 || i >= 0x400)
        return 0;
    return r2b_bits3EDC38[i / 32] & (1 << (i % 32));
}

/* 0x000D9AB0: set bit i of the script flag block and notify both listeners when it
   was clear. */
void r2b_SetBit(int i)
{
    uint32_t m, w;
    if (i < 0 || i >= 0x400)
        return;
    m = 1u << (i % 32);
    w = r2b_bits3EDC38[i / 32];
    if (w & m)
        return;
    r2b_bits3EDC38[i / 32] = w | m;
    if (r2b_ctx42C8E4) {
        sub_00035A10(r2b_ctx42C8E4->p1EC, i, 1);
        sub_0005C580(r2b_ctx42C8E4->p1F0, i, 1);
    }
}

/* 0x000D9B30: clear bit i of the script flag block and notify both listeners. */
void r2b_ClearBit(int i)
{
    if (i < 0 || i >= 0x400)
        return;
    r2b_bits3EDC38[i / 32] &= ~(1u << (i % 32));
    if (r2b_ctx42C8E4) {
        sub_00035A10(r2b_ctx42C8E4->p1EC, i, 0);
        sub_0005C580(r2b_ctx42C8E4->p1F0, i, 0);
    }
}
