/* Area ac0, group 1: actor list/velocity helpers 0x000C2270-0x000C5B10. Names inferred. */
#include "ac0.h"

/* 0x000C2270: stop the actor and play reaction 2. */
void ac0_StopAnim2(Ac0Actor *a)
{
    a->vel[2] = 0.0f; a->vel[1] = 0.0f; a->vel[0] = 0.0f;
    sub_000BD4D0(a, 2);
}
/* 0x000C22A0: stop the actor and play reaction 1. */
void ac0_StopAnim1(Ac0Actor *a)
{
    a->vel[2] = 0.0f; a->vel[1] = 0.0f; a->vel[0] = 0.0f;
    sub_000BD4D0(a, 1);
}
/* 0x000C44B0: append to list C (max 32); returns new count or -1. */
int ac0_ListC_Add(Ac0Actor *a, int v)
{
    if (a->listCCount >= 32) return -1;
    a->listC[a->listCCount] = v;
    return ++a->listCCount;
}
/* 0x000C4560: append to list B (max 32); returns new count or -1. */
int ac0_ListB_Add(Ac0Actor *a, int v)
{
    if (a->listBCount >= 32) return -1;
    a->listB[a->listBCount] = v;
    return ++a->listBCount;
}
/* 0x000C4590: index of v in list B, or -1. */
int ac0_ListB_Find(Ac0Actor *a, int v)
{
    int i;
    if (a->listBCount == 0) return -1;
    for (i = 0; i < a->listBCount; i++)
        if (a->listB[i] == v) return i;
    return -1;
}
/* 0x000C45D0: append to list A (max 32); returns new count or -1. */
int ac0_ListA_Add(Ac0ListObj *a, int v)
{
    if (a->count >= 32) return -1;
    a->items[a->count] = v;
    return ++a->count;
}
/* 0x000C46A0: constant 0x50. */
int ac0_Const50(void) { return 0x50; }

/* 0x000C5250: play table sound `i` at the actor's position (third stack slot reused for the tail call). */
int ac0_PlaySound(Ac0Actor *a, int i, int unused)
{
    int id = g_ac0_soundTable[i];
    if (id < 0) return id;
    return sub_000494D0(id, a->subFD8 + 0x60, 0);
}
/* 0x000C5290: trigger table effect `i`. */
void ac0_PlayEffect(Ac0Actor *a, int i)
{
    int id = g_ac0_effectTable[i];
    if (id >= 0) sub_000AA2E0(id);
}
/* 0x000C52B0: clear the eight handles. */
void ac0_Handles_Clear(void)
{
    g_ac0_handles[0] = 0; g_ac0_handles[1] = 0; g_ac0_handles[2] = 0; g_ac0_handles[3] = 0;
    g_ac0_handles[4] = 0; g_ac0_handles[5] = 0; g_ac0_handles[6] = 0; g_ac0_handles[7] = 0;
}
/* 0x000C5340: release handles that have finished. */
void ac0_Handles_Reap(void)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (g_ac0_handles[i] && !sub_00033AD0(g_ac0_handles[i])) {
            sub_00033AC0(g_ac0_handles[i]);
            g_ac0_handles[i] = 0;
        }
    }
}
/* 0x000C5380: stop and free every handle. */
void ac0_Handles_FreeAll(void)
{
    int i;
    for (i = 0; i < 8; i++) {
        if (g_ac0_handles[i]) {
            sub_00033AC0(g_ac0_handles[i]);
            sub_00033A70(g_ac0_handles[i]);
            g_ac0_handles[i] = 0;
        }
    }
}
/* 0x000C5B10: run the per-record update over the 32 records at 0x0041E2A0. */
void ac0_Recs_UpdateAll(void)
{
    int i;
    for (i = 0; i < 32; i++)
        sub_000C4B70(&g_ac0_41E2A0[i]);
}

/* 0x000C17B0: two-step reaction: arm anim 0x30A, then play reaction 1 when the timer ends. */
void ac0_React_C17B0(Ac0Actor *a)
{
    a->vel[2] = 0.0f; a->vel[1] = 0.0f; a->vel[0] = 0.0f;
    switch (a->stateE0) {
    case 0:
        a->flags150 = (a->flags150 & ~1u) | 0x28000000;
        a->anim12C = 0x30A;
        a->stateE0 = 1;
        break;
    case 1:
        if (PlayerObj_TimerDone((PlayerObj *)a))
            sub_000BD4D0(a, 1);
        break;
    }
}
/* 0x000C1830: as 0x000C17B0 with anim 0x309. */
void ac0_React_C1830(Ac0Actor *a)
{
    a->vel[2] = 0.0f; a->vel[1] = 0.0f; a->vel[0] = 0.0f;
    switch (a->stateE0) {
    case 0:
        a->flags150 = (a->flags150 & ~1u) | 0x28000000;
        a->anim12C = 0x309;
        a->stateE0 = 1;
        break;
    case 1:
        if (PlayerObj_TimerDone((PlayerObj *)a))
            sub_000BD4D0(a, 1);
        break;
    }
}
/* 0x000C18B0: as 0x000C17B0 but ends with reaction 2. */
void ac0_React_C18B0(Ac0Actor *a)
{
    a->vel[2] = 0.0f; a->vel[1] = 0.0f; a->vel[0] = 0.0f;
    switch (a->stateE0) {
    case 0:
        a->flags150 = (a->flags150 & ~1u) | 0x28000000;
        a->anim12C = 0x30A;
        a->stateE0 = 1;
        break;
    case 1:
        if (PlayerObj_TimerDone((PlayerObj *)a))
            sub_000BD4D0(a, 2);
        break;
    }
}
/* 0x000C21A0: enter state 1 with anim 0x203. */
void ac0_Enter_C21A0(Ac0Actor *a)
{
    if (a->stateE0 != 0) return;
    a->f10C = 10.0f;
    a->flags150 &= 0x83FFF4FE;
    a->anim12C = 0x203;
    a->vel[2] = 0.2f;
    a->stateE0 = 1;
}
/* 0x000C2200: enter state 1 with anim 5. */
void ac0_Enter_C2200(Ac0Actor *a)
{
    if (a->stateE0 != 0) return;
    a->fE8 = 0.0f;
    a->fE4 = 0.0f;
    a->f10C = 10.0f;
    a->flags150 &= 0x83FFF4FE;
    a->vel[2] = 0.5f;
    a->anim12C = 5;
    a->stateE0 = 1;
}
/* 0x000C4250: read the actor's anchor: position into p, pair into q. */
void ac0_GetAnchor(Ac0Actor *a, float *p, int32_t *q)
{
    p[3] = 0.0f; p[2] = 0.0f; p[1] = 0.0f; p[0] = 0.0f;
    ((float *)q)[3] = 0.0f; ((float *)q)[2] = 0.0f; ((float *)q)[1] = 0.0f; ((float *)q)[0] = 0.0f;
    ac0_VecCopy(p, a->vec198);
    q[1] = a->v190;
    q[0] = a->v194;
}
/* 0x000C52E0: start sound a in the first free handle slot. */
void ac0_Handle_Start(int a, int b)
{
    void *p = g_playerObj;
    int i;
    for (i = 0; i < 8; i++) {
        if (g_ac0_handles[i] == 0) {
            g_ac0_handles[i] = sub_00035D80(p, a, 3);
            sub_00034E00(g_ac0_handles[i], b, g_378198, g_378188);
            sub_00033AB0(g_ac0_handles[i]);
            return;
        }
    }
}
