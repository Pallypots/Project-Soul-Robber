/* Area r1e, group 5: script object hook, voice sweep, collection checks 0x0003F800..0x0004BE80. Names inferred. */
#include "r1e.h"

/* 0x0003F800: run 0x0003F780, then for op 0 clear the last entry's link
   and for op 1 notify the object if its kind matches the mask. */
void *r1e_SObjOpEx(void *a, R1eSObj *o, int op)
{
    void *r = r1e_SObjOp(a, o, op);
    switch (op) {
    case 0:
        if (o->y->n > 0)
            o->y->ents[o->y->n - 1].d14 = -1;
        break;
    case 1:
        if (sub_0004ECE0(o->d28) & r1e_mask2C4B1C)
            sub_0003E410(o, o->d04);
        break;
    }
    return r;
}

/* 0x000483D0: free the voice pairs whose handle has finished; if none is
   still playing, fade the music back to 0x80. */
void r1e_VoiceSweep(void)
{
    int any = -1;
    int i;
    R1ePair *p;
    for (i = 0; i < 4; i++) {
        p = &r1e_pairs3DFEA0[i];
        if (p->h >= 0) {
            if (sub_0019A930(p->h) != 0) {
                any = 1;
            } else {
                p->a = -1;
                p->h = -1;
                if (any < 0)
                    any = 0;
            }
        }
    }
    if (any <= 0 && r1e_g3DFED4 != 0x80)
        sub_00047DA0(0x80, 100);
}

/* 0x00049B70: 2 if item 0xF8 is owned, else 1 when every one of the 0x38
   listed flags is set, else 0. */
int r1e_AllCollected(void)
{
    unsigned i, n;
    if (sub_000D9A70(0xF8) != 0)
        return 2;
    for (i = 0; i < 0x38; i++) {
        n = r1e_ids2C7E08[i] + 0x10;
        if (n < 0x10 || n > 0x4F)
            for (;;) ;
        if (!(r1e_bits4133FC[n >> 5] & (1u << (n & 31))))
            return 0;
    }
    return 1;
}

/* 0x0004BE80: grant the first not yet owned reward (0xF9..0xFC) the
   collection rank allows; returns its index or -1. */
int r1e_RankReward(void)
{
    int r = r1e_CollectRank();
    if (r >= 1 && sub_000D9A70(0xF9) == 0)
        return 0;
    if (r >= 2 && sub_000D9A70(0xFA) == 0)
        return 1;
    if (r >= 3 && sub_000D9A70(0xFB) == 0)
        return 2;
    if (r >= 4 && sub_000D9A70(0xFC) == 0)
        return 3;
    return -1;
}
