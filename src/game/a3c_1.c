/* Area a3c, group 1: globals and tables near 0x00037B70..0x000390B0. Names inferred. */
#include "a3c.h"

/* 0x00037B70: reset and clear the five slots at 0x003DA2D8. */
void a3c_SlotsReset(void)
{
    sub_00037AE0();
    a3c_tbl3DA2D8[0] = 0;
    a3c_tbl3DA2D8[1] = 0;
    a3c_tbl3DA2D8[2] = 0;
    a3c_tbl3DA2D8[3] = 0;
    a3c_tbl3DA2D8[4] = 0;
}

/* 0x00037BB0: set slot i. */
void a3c_SlotSet(int i, int v) { a3c_tbl3DA2D8[i] = v; }

/* 0x00037FC0: read the current mode word. */
int a3c_ModeGet(void) { return a3c_g2C4460; }

/* 0x00037FD0: replace the mode word, returning the old one. */
int a3c_ModeSwap(int v)
{
    int old = a3c_g2C4460;
    a3c_g2C4460 = v;
    return old;
}

/* 0x00037FE0: true when nothing is busy. */
int a3c_IsIdle(void) { return a3c_busy3DA310 == 0; }

/* 0x00038030: attach the default object and set flag 0x40. */
void a3c_AttachDefault(A3cFlags24 *p)
{
    sub_00014D00(p, a3c_obj2C4090, a3c_g3DA2FC);
    p->flags |= 0x40;
}

/* 0x00038060: set the secondary mode word. */
void a3c_Mode2Set(int v) { a3c_g2C4464 = v; }

/* 0x00038070: wait until idle, then swap the mode word. */
int a3c_ModeSwapWhenIdle(int v)
{
    int old;
    while (a3c_busy3DA310) sub_000580D0();
    old = a3c_g2C4460;
    a3c_g2C4460 = v;
    return old;
}

/* 0x00038960: clear the mask, queue count and 0x003DA390. */
void a3c_QueueReset(void)
{
    a3c_mask3DA330 = 0;
    a3c_n3DA334 = 0;
    a3c_g3DA390 = 0;
}

/* 0x00038980: clear the mask. */
void a3c_MaskClear(void) { a3c_mask3DA330 = 0; }

/* 0x00038990: set bit `bit` of the mask to v. */
void a3c_MaskSetBit(int bit, uint32_t v)
{
    a3c_mask3DA330 = (a3c_mask3DA330 & ~(1u << bit)) | (v << bit);
}

/* 0x00038AA0: empty the queue. */
void a3c_QueueClear(void) { a3c_n3DA334 = 0; }

/* 0x00038AB0: append to the 16-entry queue (hang when full). */
void a3c_QueuePush(int v)
{
    int n = a3c_n3DA334;
    if (n >= 16) for (;;) ;
    a3c_tbl3DA338[n] = v;
    a3c_n3DA334++;
}

/* 0x00038F80: process the object at 0x003DCDA8 and pass the argument through. */
int a3c_ProcessPass(int v)
{
    sub_001A4FB0(a3c_obj3DCDA8);
    return v;
}

/* 0x000390A0: address of the object at 0x003DCDA8. */
void *a3c_ObjGet(void) { return a3c_obj3DCDA8; }

/* 0x000390B0: set the default 512x224 sizes. */
void a3c_SizeDefaults(void)
{
    a3c_w3DCE58 = 0x200;
    a3c_h3DCE5C = 0xE0;
    a3c_w3DA4A0 = 0x200;
    a3c_h3DCDA4 = 0xE0;
}
