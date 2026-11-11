/* Area r1c, group 1: one-jump forwarding thunks in 0x00012000..0x00054000.
   Each original is a single jmp to the real routine. Names inferred. */
#include "r1c.h"

/* 0x00012000: forwards to the packet buffer initialiser 0x00014B60. */
void r1c_PktInitThunk(void)
{
    sub_00014B60();
}

/* 0x000122F0: forwards to the packet flush routine 0x00014BE0. */
void r1c_PktFlushThunk(int which)
{
    sub_00014BE0(which);
}

/* 0x0002C750: forwards to the per-frame state update 0x0002C5E0. */
void r1c_StateUpdateThunk(void)
{
    sub_0002C5E0();
}

/* 0x0002C780: forwards to the sound group resume routine 0x001A11B0. */
int r1c_GroupResumeThunk(void *group)
{
    return sub_001A11B0(group);
}

/* 0x00037590: forwards to the resource loader 0x000373A0. */
void r1c_LoadThunk(int a, int b, int c, int d)
{
    sub_000373A0(a, b, c, d);
}

/* 0x00037AE0: forwards to the record table reset 0x000375A0. */
void r1c_TableResetThunk(void)
{
    sub_000375A0();
}

/* 0x00037BA0: forwards to the record table pass 0x00037B20. */
void r1c_TablePassThunk(int arg)
{
    sub_00037B20(arg);
}

/* 0x000479E0: forwards to 0x001997D0 (store a block at 0x00402760). */
void r1c_Store402760Thunk(void)
{
    sub_001997D0();
}

/* 0x000480F0: forwards to 0x00199D90 (is entity i linked). */
int r1c_EntIsLinkedThunk(int i)
{
    return sub_00199D90(i);
}

/* 0x00048100: forwards to 0x00199E70 (slot i has flag 4). */
int r1c_SlotHas4Thunk(int i)
{
    return sub_00199E70(i);
}

/* 0x000482B0: forwards to 0x0019A930 (record i of the table at 0x004019D8). */
int r1c_GetRecThunk(int i)
{
    return sub_0019A930(i);
}

/* 0x00048440: forwards to 0x0019AC20 (set a value in a 0x004019D8 record). */
void r1c_SetRecThunk(int h, int i, int v)
{
    sub_0019AC20(h, i, v);
}

/* 0x0004BD70: forwards to the subsystem shutdown sequence 0x00057C70. */
void r1c_ShutdownThunk(void)
{
    sub_00057C70();
}

/* 0x00053F60: forwards to 0x001A8680. */
int r1c_Poll1A8680Thunk(void)
{
    return sub_001A8680();
}
