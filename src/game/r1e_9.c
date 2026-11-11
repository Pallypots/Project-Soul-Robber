/* Area r1e, group 9: sound groups, entry index, effect pool 0x0005A380..0x0005BBD0. Names inferred. */
#include "r1e.h"

/* 0x0005A380: register the three sound callbacks on dev, release two
   groups and clear the sound table. */
void r1e_SndHooksInit(void *dev)
{
    a1a_GroupAdd(dev, 0, 1, sub_0005A1C0, 8, 0x2000);
    a1a_GroupAdd(dev, 1, 1, sub_0005A200, 8, 0x2000);
    a1a_GroupAdd(dev, -1, 4, sub_0005A2F0, 8, 0x2000);
    a1a_GroupReleaseOne(dev, 0);
    a1a_GroupReleaseOne(dev, -1);
#if defined(_M_IX86)
    __stosd((unsigned long *)r1e_sndTab3E4750, 0, 0xF3);
#else
    memset(r1e_sndTab3E4750, 0, sizeof r1e_sndTab3E4750);
#endif
    r1e_g3E4B1C = 0;
}

/* first used entry at or after i, or -1 */
static int r1e_NextUsed(R1eUList *l, int i, int count)
{
    for (; i < count && l->ents[i].used == 0; i++)
        ;
    return i < count ? i : -1;
}

/* 0x0005A920: position of used entry `target` among the used entries of
   the list, or -1. */
int r1e_UsedIndexOf(R1eUList *l, int target)
{
    int count = l->count;
    int n = 0;
    int i = r1e_NextUsed(l, 0, count);
    while (i != target) {
        if (i < 0)
            return -1;
        n++;
        i = r1e_NextUsed(l, i + 1, count);
    }
    return n;
}

/* 0x0005BA60: set up the effect pool, its two lists and the 32 sound
   owner slots. */
int r1e_FxPoolInit(void)
{
    R1eSndSlot *s;
    sub_00036A90(r1e_fxPool3E4B70, 0x3C, 0x41);
    sub_0003D860(&r1e_fxListA3E4B60);
    sub_0003D860(&r1e_fxListB3E5AAC);
    for (s = r1e_sndSlots3E5AC0; s < r1e_sndSlots3E5AC0 + 32; s++) {
        s->d00 = 0;
        s->self = s;
        s->handle = -1;
        s->owner = 0;
    }
    a5b_g3E6040 = 0;
    a5b_g2DD4D8 = -1;
    return 0;
}

/* 0x0005BBD0: take an effect from the pool, reset it and put it on list
   A (which 0) or B (which 1). */
R1eFx *r1e_FxNew(int which)
{
    char *p = r1c_PoolTake(r1e_fxPool3E4B70, 0x3C);
    R1eFx *f;
    if (p == 0)
        return 0;
    f = (R1eFx *)(p + 0x10);
    if (f != 0) {
        sub_0003D860(&f->link);
        sub_0005A400(f);
        f->scale = 1.0f;
        f->d28 = -1;
    }
    f->self = f;
    switch (which) {
    case 0:
        sub_0003D880(&r1e_fxListA3E4B60, (R1eRes *)&f->link);
        break;
    case 1:
        sub_0003D880(&r1e_fxListB3E5AAC, (R1eRes *)&f->link);
        break;
    }
    return f;
}
