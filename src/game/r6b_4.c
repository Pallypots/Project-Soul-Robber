/* Area r6b: small helpers in 0x00061C40-0x00087030 (r6b_4). Names inferred. */
#include "r6b.h"

/* 0x00061C40: run the menu update 0x00061BC0 while the mode is 100. */
void r6b_MenuTick(void)
{
    if (a60_mode3E64C0 == 100)
        sub_00061BC0();
}

/* 0x00065A40: reset the object at 0x00429050 with 0x00015070. */
void r6b_Reset429050(void)
{
    sub_00015070(r6b_obj429050);
}

/* 0x00065AC0: release the resource handle at 0x003E6540 if one is held. */
void r6b_ReleaseRes3E6540(void)
{
    if (a60_res3E6540 != -1) {
        sub_001B9FC0(a60_res3E6540);
        a60_res3E6540 = -1;
    }
}

/* 0x000774B0: forwards to 0x001A1170. */
void r6b_Fwd1A1170(void *job)
{
    sub_001A1170(job);
}

/* 0x000774C0: set the state word at 0x003E7A48 to 2. */
void r6b_Set3E7A48(void)
{
    r6b_g3E7A48 = 2;
}

/* 0x00078150: clear the work buffer, stop job `job`, then shut down (0x00077410). */
void r6b_StopAndShutdown(void *job)
{
    sub_00017D30();
    sub_001A1130(job);
    a60_Shutdown77410();
}

/* 0x00079780: flush the renderer, then run 0x00034A90 with `a`. */
void r6b_FlushRun34A90(int a)
{
    sub_001A7230();
    sub_00034A90(a);
}

/* 0x00079790: call 0x000398D0 with (a, 0). */
int r6b_Call398D0(int a)
{
    return sub_000398D0(a, 0);
}

/* 0x00079810: set the clear colour to white, flush the renderer, return `a`. */
int r6b_ClearWhite(int a)
{
    sub_001A7620(0xFFFFFF);
    sub_001A7230();
    return a;
}

/* 0x00079880: allocate a zeroed 0x214-byte block. */
void *r6b_Alloc214(void)
{
    uint32_t *p = (uint32_t *)a5b_AllocCur(0x214, 0, 0xE5);
    int i;
    for (i = 0; i < 0x85; i++)
        p[i] = 0;
    return p;
}

/* 0x000799F0: returns its argument. */
void *r6b_Identity(void *p)
{
    return p;
}

/* 0x0007A9D0: run pass 0x11 of the object's +0x44 list (0x00084B10). */
void r6b_ObjPass11(R6bObj7A *o)
{
    sub_00084B10(o->i44, 0x11);
}

/* 0x0007AA30: reset the screen size and rebuild both layers (0x00039B50). */
void r6b_ScreenReset(void)
{
    sub_000390B0();
    sub_00039B50(0);
    sub_00039B50(1);
}

/* 0x0007AA50: field +0x1E8. */
int r6b_Obj1E8(R6bObj7A *o) { return o->i1E8; }

/* 0x0007AA60: address of the block at +0x144. */
void *r6b_Obj144(R6bObj7A *o) { return o->blk144; }

/* 0x0007AA70: first half of record i (of 3) at +0xE4; hangs on a bad index. */
void *r6b_ObjRecA(R6bObj7A *o, uint32_t i)
{
    if (i >= 3)
        for (;;) ;
    return o->recs[i].a;
}

/* 0x0007AA90: second half of record i (of 3) at +0xE4; hangs on a bad index. */
void *r6b_ObjRecB(R6bObj7A *o, uint32_t i)
{
    if (i >= 3)
        for (;;) ;
    return o->recs[i].b;
}

/* 0x0007AAB0: field +0x1EC. */
int r6b_Obj1EC(R6bObj7A *o) { return o->i1EC; }

/* 0x0007AB00: address of the block at +0x1B8. */
void *r6b_Obj1B8(R6bObj7A *o) { return o->blk1B8; }

/* 0x0007F510: look up `name` (optionally returning the handle in *out), then select it. */
void r6b_LookupSelect(void *name, int *out)
{
    if (out)
        *out = sub_000374C0(name);
    sub_00037550(name, 0);
}

/* 0x0007FD30: push hook `b` on record idx (0x130 bytes each) of the object's +0xB4 table. */
void r6b_ObjHookPush(R6bB4 *o, int b, int idx)
{
    if (o->recs)
        r4_HookPushA8(o->recs + idx * 0x130, b);
}

/* 0x00080CF0: dispatch on bit 0 of +0x08. calls 0x00080B40 with EBX=a (and b on the stack). */
int r6b_Dispatch80CF0(R6bFlag8 *a, int b)
{
    if (a->flags & 1)
        return sub_00080BD0(a, b);
    return sub_00080B40(a, b);
}

/* 0x00080D60: index at +0x08 of the +0x30 record of the +0x50 sub-object, -1 when outside 0..20. */
int r6b_Index0to20(R6bP50 *p)
{
    int v = p->p50->sub30.index;
    if (v < 0 || v > 0x14)
        return -1;
    return v;
}

/* 0x00081B80: forwards to the heap free 0x00053880. */
void r6b_Free81B80(void *p)
{
    sub_00053880(p);
}
