/* Area ac0, group 3: actor target/record helpers 0x000CB990-0x000CC030. Names inferred. */
#include "ac0.h"

/* 0x000CB990: forward (obj, obj + 0x24, b) to 0x000CF330. */
void ac0_Call_CF330(uint8_t *obj, float b)
{
    sub_000CF330(obj, obj + 0x24, b);
}
/* 0x000CB9B0: value of the current selection, 0 if none or of kind 1. */
int ac0_CurSelValue(void)
{
    if (!g_ac0_4201D8 || g_ac0_420268[g_ac0_4203E8[g_ac0_4201DC]] == 1)
        return 0;
    return g_ac0_4202E8[g_ac0_4203E8[g_ac0_4201DC]];
}
/* 0x000CB9F0: copy the selection position to `out`; returns its kind or -1. */
int ac0_CurSelPos(float *out)
{
    if (!g_ac0_4201D8) return -1;
    ac0_VecCopy(out, g_ac0_41FEE4);
    return g_ac0_420268[g_ac0_4203E8[g_ac0_4201DC]];
}
/* 0x000CBD10: clear the actor's target flags. */
void ac0_ClearTarget(Ac0Actor *a) { a->flags5A8 = 0; }

/* 0x000CBD20: set a target (value and two vectors). */
void ac0_SetTarget(Ac0Actor *a, int v, const float *p, const float *q)
{
    a->flags5A8 |= 1;
    a->v5AC = v;
    ac0_VecCopy(a->vec5B0, p);
    ac0_VecCopy(a->vec5C0, q);
}
/* 0x000CBFF0: apply 0x000CB390 to every entry of the 0x000EDB10 list. */
void ac0_ApplyToList(Ac0Actor *a)
{
    void *e;
    if (a->flags150 & 0x10000000) return;
    for (e = sub_000EDB10(0); e; e = sub_000EDB90())
        sub_000CB390(a, e);
}

/* 0x000CB340: clear the actor's cycle table. */
void ac0_Cycle_Clear(Ac0Actor *a)
{
    int i;
    if (a->flags150 & 0x10000000) return;
    a->cycCount = 0;
    for (i = 0; i < 32; i++) {
        a->cycF[i] = 0.0f;
        a->cycKind[i] = 0;
        a->cyc4A8[i] = 0;
        a->cycOrder[i] = 0;
        a->cycVal[i] = 0;
    }
}
/* 0x000CBAF0: on button 7, advance the cycle and pick up its value. */
void ac0_Cycle_Next(Ac0Actor *a)
{
    int k;
    if (g_ac0_413144) return;
    if (a->cycCount == 0) return;
    if (!sub_000CCD60(0, 7, 0)) return;
    a->cycPrev = a->cycIndex;
    if (++a->cycIndex >= a->cycCount)
        a->cycIndex = 0;
    k = a->cycOrder[a->cycIndex];
    if (a->cycKind[k] != 1)
        a->cycValue = a->cycVal[k];
}
