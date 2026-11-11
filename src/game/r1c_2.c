/* Area r1c, group 2: small helpers 0x00017D30..0x00037FF0. Names inferred. */
#include "r1c.h"

/* 0x00017D30: clear the 0x5800-byte work area at 0x0042CE80. */
void r1c_ClearWork42CE80(void)
{
    R1C_ZERO(r1c_work42CE80, sizeof(r1c_work42CE80));
}

/* 0x00025F50: set (1), clear (0) or toggle (2) bit 0 of the flag word. */
void r1c_SetFlagBit0(int mode)
{
    switch (mode) {
    case 0:
        r1c_flags37F0C8 &= ~1u;
        break;
    case 1:
        r1c_flags37F0C8 |= 1;
        break;
    case 2:
        if (r1c_flags37F0C8 & 1)
            r1c_flags37F0C8 &= ~1u;
        else
            r1c_flags37F0C8 |= 1;
        break;
    }
}

/* 0x00025F90: set (1), clear (0) or toggle (2) bit 1 of the flag word. */
void r1c_SetFlagBit1(int mode)
{
    switch (mode) {
    case 0:
        r1c_flags37F0C8 &= ~2u;
        break;
    case 1:
        r1c_flags37F0C8 |= 2;
        break;
    case 2:
        if (r1c_flags37F0C8 & 2)
            r1c_flags37F0C8 &= ~2u;
        else
            r1c_flags37F0C8 |= 2;
        break;
    }
}

/* 0x0002C760: run the state step 0x0002C4E0 when bit 0 of the flags is set.
   calls 0x0002C4E0 with EAX=arg */
void r1c_StepIfEnabled(int arg)
{
    if (r1c_flags37C4F8 & 1)
        sub_0002C4E0(arg);
}

/* 0x00033A70: free a node chain: release each idle node's block at +0x20,
   recurse into the next node, then free the node. */
void r1c_NodeFreeChain(R1cNode *n)
{
    if (n == 0) return;
    if (n->busy == 0) {
        sub_001B6270(&n->blk);
        sub_001B6130(&n->blk);
    }
    if (n->next != 0)
        r1c_NodeFreeChain(n->next);
    sub_00033560(n);
}

/* 0x00033AD0: 1 when any node in the chain is busy or its block reports
   not done, 0 when all are done; a null chain hangs (assert). */
int r1c_NodeChainBusy(R1cNode *n)
{
    for (;;) {
        if (n == 0) for (;;) ;
        if (n->busy != 0) return 1;
        if (sub_001B6140(&n->blk) == 0) return 1;
        n = n->next;
        if (n == 0) return 0;
    }
}

/* 0x00034CF0: pass four values to every idle node's block (0x001B6310). */
void r1c_NodeChainSet4(R1cNode *n, float a, float b, float c, float d)
{
    for (; n != 0; n = n->next)
        if (n->busy == 0)
            sub_001B6310(&n->blk, a, b, c, d);
}

/* 0x00034D30: pass four values to every idle node's block (0x001B6610). */
void r1c_NodeChainSet4b(R1cNode *n, float a, float b, float c, float d)
{
    for (; n != 0; n = n->next)
        if (n->busy == 0)
            sub_001B6610(&n->blk, a, b, c, d);
}

/* 0x00034EC0: start (on) or stop every idle node's block. */
void r1c_NodeChainRun(R1cNode *n, int on)
{
    for (; n != 0; n = n->next) {
        if (n->busy == 0) {
            if (on)
                sub_001B6060(&n->blk);
            else
                sub_001B6070(&n->blk);
        }
    }
}

/* 0x00036BC0: reset the camera shake block at 0x003DA098. */
void r1c_ShakeReset(void)
{
    r1c_shake3DA098.flags = 0;
    r1c_shake3DA098.d04 = 0;
    r1c_shake3DA098.f08 = 0.0f;
    r1c_shake3DA098.x = 0.0f;
    r1c_shake3DA098.y = 0.0f;
    r1c_shake3DA098.z = 0.0f;
    r1c_shake3DA098.f18 = 0.0f;
}

/* 0x00036F90: set the shake offset unless the block is locked (bit 0). */
void r1c_ShakeSetOffset(float x, float y, float z)
{
    if (!(r1c_shake3DA098.flags & 1)) {
        r1c_shake3DA098.x = x;
        r1c_shake3DA098.y = y;
        r1c_shake3DA098.z = z;
    }
}

/* 0x00037FF0: element i (10 bytes each) of the paged table: the first
   `count` live in the direct block, the rest in 256-element pages. */
void *r1c_PagedElem(int i)
{
    R1cPaged *t = r1c_paged3DA314;
    if (i < t->count)
        return t->direct + i * 10;
    return t->pages[(i >> 8) - t->count] + (i & 0xFF) * 10;
}
