/* Area a9b, 0x0019B5C0-0x0019E940. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9b.h"

/* 0x0019B5C0: call 0x199C10 with entry i (0..0x76) and its table value at 0x00330F30. */
int a9b_CallWithEntry(int i)
{
    if (i <= -1 || i >= 0x77) for (;;) ;
    return sub_00199C10(i, a9b_g330F30[i].f0);
}

/* 0x0019BA40: reset the six state words at 0x00413160. */
void a9b_Reset413160(void)
{
    a9b_g413160 = 0;
    a9b_g413164 = 1;
    a9b_g413168 = 1;
    a30_g41316C = 0;
    a30_g413170 = 0;
    a19_g413174 = 0;
}

/* 0x0019C5F0: store a vector into 0x00402FC8..0x00402FD0. */
void a9b_SetVec402FC8(float x, float y, float z)
{
    a9b_g402FC8 = x;
    a9b_g402FCC = y;
    a9b_g402FD0 = z;
}

/* 0x0019D680: release both handles 0x00402FF0/0x00402FF4 and mark them -1. */
void a9b_ReleaseHandles(void)
{
    sub_001AD440(a19_g402FF0);
    sub_001AA310(a19_g402FF4);
    a19_g402FF0 = -1;
    a19_g402FF4 = -1;
}

/* 0x0019D6D0: poll handle 0x00402FF4; when finished release both and continue. */
void a9b_PollHandles(void)
{
    sub_001AA460(a19_g402FF4);
    if (sub_001AD3A0()) {
        sub_001AA310(a19_g402FF4);
        a19_g402FF4 = -1;
        a19_g402FF0 = -1;
        sub_001AD520();
    }
}

/* 0x0019D870: set mode 8/2, notify 0x408B0/0x408C0, then continue at 0x1A0D70. */
void a9b_EnterMode2(int a)
{
    a19_g402FE4 = 8;
    a19_g402FE8 = 2;
    sub_000408B0(a);
    sub_000408C0(2);
    sub_001A0D70();
}

/* 0x0019DFA0: worker loop: refresh current buffer through 0x324B0, then yield. */
void a9b_BufferWorker(void)
{
    for (;;) {
        a30_buf12[a30_bufIndex].f4 = sub_000324B0(a30_buf12[a30_bufIndex].f4);
        sub_000580D0();
    }
}

/* 0x0019E5F0: register the two workers in group g and start them. */
void a9b_StartWorkers(void *g)
{
    a1a_GroupAdd(g, 0, 1, sub_0019E530, 8, 0x10000);
    a1a_GroupAdd(g, -1, 4, a9b_BufferWorker, 8, 0x10000);
    a1a_GroupReleaseAll(g);
}

/* 0x0019E850: set the state object's mode to 8 and flag 0x003374A0. */
void a9b_StateMode8(void)
{
    int32_t *s = a19_g403128;
    if (s == 0) for (;;) ;
    s[1] = 8;
    a19_g3374A0 = 1;
}

/* 0x0019E900: set 0x0040312C; from mode 1 go to mode 0x10 (v) or 0x11 (!v). */
void a9b_StateSelect10(int v)
{
    int32_t *s = a19_g403128;
    if (s == 0) for (;;) ;
    a9b_g40312C = 1;
    if (s[1] == 1) {
        s[1] = v != 0 ? 0x10 : 0x11;
        a19_g3374A0 = v;
        return;
    }
    a19_g3374A0 = v;
}

/* 0x0019E940: 0 if key 0x4101 is set, else whether stats flags 0x80080006 are all clear. */
int a9b_CheckFlags(void)
{
    if (sub_0019BE60(0x4101))
        return 0;
    return PlayerObj_TestFlags((PlayerObj *)&g_stats, 0x80080006u, 0) == 0;
}
