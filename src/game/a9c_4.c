/* Area a9c, 0x0019D000-0x0019EFFF (task/session setup). Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9c.h"

/* 0x0019D620: add the three standard tasks to group g and release the group's pending list. */
void a9c_GroupAddStdTasks(void *g)
{
    a1a_GroupAdd(g, 0, 1, (void (*)(void))sub_0019D460, 8, 0xC800);
    a1a_GroupAdd(g, 1, 2, sub_0019D120, 8, 0x2800);
    a1a_GroupAdd(g, -1, 4, sub_0019D390, 8, 0x2800);
    a1a_GroupReleaseAll(g);
}

/* 0x0019D7A0: store the two parameters, force modes 4 and 3 and refresh the stats. */
void a9c_EnterMode3(int a, int b)
{
    a30_g41316C = a;
    a30_g413170 = b;
    if (sub_001A0CC0() != 4)
        sub_001A0D30(4, 0);
    sub_001A0D30(3, 0);
    sub_000D1D00(&g_stats);
    sub_000D1930(&g_stats);
}

/* 0x0019E630: start with a, reset both session slots and clear the controller block pointer. */
void a9c_SessionStart(void *a)
{
    int i;
    sub_001A1130(a);
    for (i = 0; i < 2; i++) {
        g_sessionSlots[i].b[0] = 0;
        g_sessionSlots[i].b[1] = 0;
        g_sessionSlots[i].b[2] = 0;
        g_sessionSlots[i].b[3] = 0;
        g_sessionSlots[i].scale = 1.0f;
    }
    a19_g403128 = 0;
}

/* 0x0019E690: stop the movie, apply both 0x003DE5B0 settings, reset the 0x00403124 scale and continue. */
int a9c_SessionSetup(void *g)
{
    sub_001A8A70(0);
    sub_00079340();
    sub_00079F50(a80_ctx42C8E4, a9c_g3DE5B0, 0);
    sub_00079F50(a80_ctx42C8E4, a9c_g3DE5B0, 1);
    a9c_g403124 = 1.0f;
    return sub_001A11B0(g);
}

/* 0x0019E8B0: apply a, clear 0x0040312C and store flag b; in state 1 the controller block moves to 0xD (set) or 0xE. */
void a9c_CtrlApplyFlag(int a, int b)
{
    int32_t *p = a19_g403128;
    if (!p) for (;;) ;
    sub_00049860(a);
    a9b_g40312C = 0;
    if (p[1] == 1) {
        p[1] = b ? 0xD : 0xE;
        a19_g3374A0 = b;
    } else {
        a19_g3374A0 = b;
    }
}
