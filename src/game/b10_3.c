/* Area b10, group 3: enemy component helpers 0x00112A80-0x00113E60. Names inferred. */
#include "b10.h"

/* 0x00112A80: count a global timer down by the frame time. */
void b10_TickTimer(void) { b10_f3F7504 -= b10_frameDelta; }

/* 0x00112B00: 1 if command i (0..16) passes 0x0004F6D0. */
int b10_CmdTest(int i)
{
    if (i < 0 || i >= 17)
        return 0;
    return sub_0004F6D0(b10_cmdTable[i].id) != 0;
}

/* 0x00113040: switch the enemy to a new state and run its handler. */
int b10_EnemySetState(void *owner, B10Enemy *e, int state)
{
    B10StateFn * volatile fns;
    do { fns = e->stateFns; } while (state < 0 || fns[state] == 0);
    e->prevState = e->state;
    e->state = state;
    e->stateTicks = 0;
    e->stateTime = 0.0f;
    return e->stateFns[state](owner, e);
}

/* 0x00113190: enable or disable via 0x0001D470/0x0001D4B0 and mirror flag 0x10000. */
void b10_EnemySetFlag(void *a, B10Enemy *e, int on)
{
    if (on) {
        sub_0001D470(a, 0);
        e->flags20 |= 0x10000;
    } else {
        sub_0001D4B0(a, 0);
        e->flags20 &= ~0x10000;
    }
}

/* 0x001131E0: subtract damage from the enemy's health. */
void b10_EnemyDamage(B10Enemy *e, float dmg) { e->health -= dmg; }

/* 0x001133E0: find the node with an id. */
B10Node *b10_NodeFind(B10Enemy *e, int id)
{
    B10Node *n;
    for (n = e->nodes; n != 0; n = n->next)
        if (n->id == id)
            return n;
    return 0;
}

/* 0x00113400: find the node with an id, allocating one if absent. */
B10Node *b10_NodeGet(B10Enemy *e, int id)
{
    B10Node *n;
    for (n = e->nodes; n != 0; n = n->next)
        if (n->id == id)
            return n;
    n = sub_00113300(e);
    if (n != 0)
        n->id = id;
    return n;
}

/* 0x00113480: release the node with an id unless it is locked (kind 2). */
B10Node *b10_NodeRelease(B10Enemy *e, int id)
{
    B10Node *n;
    for (n = e->nodes; n != 0; n = n->next) {
        if (n->id == id) {
            if (n->kind == 2)
                return n;
            sub_00113370(e, n);
            return 0;
        }
    }
    return 0;
}

/* 0x00113C40: add with an upper clamp. */
void b10_AddClampI(int *v, int d, int max)
{
    *v += d;
    if (*v > max)
        *v = max;
}

/* 0x00113C60: float add with an upper clamp. */
void b10_AddClampF(float *v, float d, float max)
{
    *v += d;
    if (*v > max)
        *v = max;
}

/* 0x00113C90: subtract with a lower clamp. */
void b10_SubClampI(int *v, int d, int min)
{
    *v -= d;
    if (*v < min)
        *v = min;
}

/* 0x00113CB0: float subtract with a lower clamp. */
void b10_SubClampF(float *v, float d, float min)
{
    *v -= d;
    if (*v < min)
        *v = min;
}

/* 0x00113E60: base init, then install the enemy's callbacks. */
void b10_EnemyInitCallbacks(B10Enemy *e)
{
    sub_000EE270(e);
    e->fn24 = (void *)sub_00113E00;
    e->fn28 = (void *)sub_00112970;
    e->fn2C = (void *)b10_SkelHit;
}

