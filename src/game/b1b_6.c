/* Area b1b, group 6: actor condition checks 0x0012D970-0x0012DDB0. Names inferred. */
#include "b1b.h"

/* 0x0012D970: target the player unless info flag 2 is set. */
void b1b_TargetPlayer(void *unused, B1bCAct *a)
{
    if (!(a->info->flags0C & 2)) {
        a->target = (void *)g_playerObj;
        a->targetMode = 1;
    }
}

/* 0x0012DD70: 1 if info value +0x180 lies within [lo, hi]. */
int b1b_InRange180(void *unused, B1bCAct *a, B1bRange *r)
{
    B1bCInfo *i = a->info;
    return i->f180 >= r->lo && r->hi >= i->f180;
}

/* 0x0012DDB0: test info flags against a mask: want 0 = none set, else any set. */
int b1b_MaskTest(void *unused, B1bCAct *a, B1bMask *m)
{
    uint32_t f = a->info->flags0C;
    if (m->want == 0)
        return (f & m->mask) == 0;
    return (f & m->mask) != 0;
}
