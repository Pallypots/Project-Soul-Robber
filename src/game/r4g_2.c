/* Area r4g: sound pool layout at 0x001995A0 (r4g_2). Names inferred. */
#include "r4g.h"

/* 0x001995A0: once, size the eleven sound pools from the largest two waves
   (rounded to 2 KB) of every cue that uses them, let pool 3 share the
   space of pool 7 (pool 4 mirrors pool 3), allocate one block and turn
   each size into the address of its part. No inputs. */
void r4g_SndPoolLayout(void)
{
    R4gPool *p;
    uint32_t s0, s1, total, base;
    uint32_t a1, a2, a3, a4, a5, a6, b0, b1, b2, b3, b4, b5, b6;
    int i;

    if (r4g_poolBase402750)
        return;
    for (i = 0; i < 11; i++) {
        r4g_pools3316A4[i].size0 = 0;
        r4g_pools3316A4[i].size1 = 0;
    }
    for (i = 0; i < 119; i++) {
        p = &r4g_pools3316A4[r4c_cues330F30[i].pool];
        s0 = (r4g_waves41344C[r4c_cues330F30[i].wave0].size + 0x7FF) & ~0x7FFu;
        s1 = (r4g_waves41344C[r4c_cues330F30[i].wave1].size + 0x7FF) & ~0x7FFu;
        if (s0 > p->size0)
            p->size0 = s0;
        if (s1 > p->size1)
            p->size1 = s1;
    }
    if (r4g_pools3316A4[7].size0 > r4g_pools3316A4[3].size0 * 2)
        r4g_pools3316A4[3].size0 = r4g_pools3316A4[7].size0 >> 1;
    r4g_pools3316A4[4].size0 = r4g_pools3316A4[3].size0;
    if (r4g_pools3316A4[7].size1 > r4g_pools3316A4[3].size1 * 2)
        r4g_pools3316A4[3].size1 = r4g_pools3316A4[7].size1 >> 1;
    r4g_pools3316A4[4].size1 = r4g_pools3316A4[3].size1;

    total = r4g_pools3316A4[0].size0 + r4g_pools3316A4[0].size1
          + r4g_pools3316A4[1].size0 + r4g_pools3316A4[1].size1
          + r4g_pools3316A4[2].size0 + r4g_pools3316A4[2].size1
          + r4g_pools3316A4[3].size0 + r4g_pools3316A4[3].size1
          + r4g_pools3316A4[4].size0 + r4g_pools3316A4[4].size1
          + r4g_pools3316A4[5].size0 + r4g_pools3316A4[5].size1
          + r4g_pools3316A4[6].size0 + r4g_pools3316A4[6].size1;
    base = sub_000AD090(total);

    /* first parts of pools 0..6, then second parts, packed back to back */
    a1 = base + r4g_pools3316A4[0].size0;
    a2 = a1 + r4g_pools3316A4[1].size0;
    a3 = a2 + r4g_pools3316A4[2].size0;
    a4 = a3 + r4g_pools3316A4[3].size0;
    a5 = a4 + r4g_pools3316A4[4].size0;
    a6 = a5 + r4g_pools3316A4[5].size0;
    b0 = a6 + r4g_pools3316A4[6].size0;
    b1 = b0 + r4g_pools3316A4[0].size1;
    b2 = b1 + r4g_pools3316A4[1].size1;
    b3 = b2 + r4g_pools3316A4[2].size1;
    b4 = b3 + r4g_pools3316A4[3].size1;
    b5 = b4 + r4g_pools3316A4[4].size1;
    b6 = b5 + r4g_pools3316A4[5].size1;
    r4g_pools3316A4[1].size0 = a1;
    r4g_pools3316A4[2].size0 = a2;
    r4g_pools3316A4[3].size0 = a3;
    r4g_pools3316A4[4].size0 = a4;
    r4g_pools3316A4[5].size0 = a5;
    r4g_pools3316A4[6].size0 = a6;
    r4g_pools3316A4[7].size0 = a3;
    r4g_pools3316A4[0].size1 = b0;
    r4g_pools3316A4[1].size1 = b1;
    r4g_pools3316A4[2].size1 = b2;
    r4g_pools3316A4[3].size1 = b3;
    r4g_pools3316A4[4].size1 = b4;
    r4g_pools3316A4[5].size1 = b5;
    r4g_pools3316A4[6].size1 = b6;
    r4g_pools3316A4[7].size1 = b3;
    r4g_pools3316A4[0].size0 = base;
    r4g_poolBase402750 = base;
    r4g_poolTotal402754 = total;
}
