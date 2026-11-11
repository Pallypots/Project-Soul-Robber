/* Area ac0, group 5: callers kept apart from their callees (so cl does not inline them). Names inferred. */
#include "ac0.h"

/* 0x000C5CC0: play the level-adjusted sound of entry i (alternate column when powered). */
void ac0_PlayLevelSound(Ac0Actor *a, int i, void *b)
{
    const Ac0SndEntry *e = &g_ac0_sndEntries[i];
    int id;
    if (!(a->flagsEC & 0x40) && !(a->flagsD60 & 2))
        id = e->a;
    else
        id = e->b;
    if (id < 0) return;
    if (e->level >= 0)
        id += a->levD6C[e->level];
    ac0_Handle_Start(id, b);
}
/* 0x000C9830: init via 0x000C72C0 then reset the transforms. */
void ac0_Init_C9830(void)
{
    sub_000C72C0();
    ac0_Xforms_Reset();
}
/* 0x000C9970: init via 0x000C7B00 then 0x000C93D0. */
void ac0_Init_C9970(void)
{
    sub_000C7B00();
    sub_000C93D0();
}
/* 0x000CC230: set a target unless busy, in states 1/2/4/5, or blocked by 0x4101. */
void ac0_TrySetTarget(Ac0Actor *a, int v, const float *p, const float *q)
{
    int k;
    if (!(a->flags150 & 0x82006)) {
        k = a->kindD4;
        if (k != 1 && k != 2 && k != 4 && k != 5 && !sub_0019BE60(0x4101)) {
            ac0_SetTarget(a, v, p, q);
            return;
        }
    }
    a->flags5A8 = 0;
}
/* 0x000CC920: promote the current companion when its button is pressed. */
void ac0_TryPromote(Ac0Actor *a)
{
    int k;
    if (a->flags150 & 0x80006) return;
    k = a->kindD4;
    if (k == 2 || k == 4 || k == 5) return;
    if (sub_0019BE60(0x4101)) return;
    if (g_ac0_42CA38 & g_ac0_41CD28)
        ac0_Slots_Promote(a);
}
/* 0x000CC970: 1 if a companion can be summoned, else -1 (with error sound 4). */
int ac0_CanSummon(Ac0Actor *a)
{
    int r = 1;
    int k;
    if (ac0_Slots_CountActive(a) >= 3) r = -1;
    k = a->stat3;
    if (a->slotD7C[k] < 0) r = -1;
    if (k == 3 && Stats_TestFlags((PlayerStats *)a, 1)) {
        r = -1;
        sub_00048AF0(4);
        return r;
    }
    if (r < 0) sub_00048AF0(4);
    return r;
}
