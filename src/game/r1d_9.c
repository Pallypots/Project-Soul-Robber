/* Area r1d, group 9: range records 0x00033D10..0x00035B20. Names inferred. */
#include "r1d.h"

/* take a range record from the bank's range pool and reset it */
static R1dRange *r1d_RangeAlloc(void)
{
    R1dRangeEnt *e = r1c_PoolTake(r1c_bank283698 + 0x55140, 0x6C);
    if (e != 0) {
        sub_00033710(&e->range);
        return &e->range;
    }
    return 0;
}

/* 0x00033D10: replace the host's range record by a new one set from s. */
void r1d_HostRangeNew(R1dRangeHost *h, R1dRangeSpec *s)
{
    if (h == 0) return;
    if (h->range != 0) {
        sub_00033C20(h->range);
        h->range = 0;
    }
    h->range = r1d_RangeAlloc();
    if (h->range == 0) return;
    h->range->owner = h;
    s->d0C = s->d50;
    a5b_PairSet(h->range, s);
    h->range->flags |= 1;
}

/* 0x000341E0: create a range record for every spawn entry whose event
   flag is set (or -1). Returns 0. */
int r1d_SpawnRanges(R1dSpawnList *l)
{
    R1dSpawn *s;
    R1dRange *r;
    if (l == 0) return 0;
    for (s = l->head; s != 0; s = s->next) {
        if (s->flag != -1 && sub_000D9A70(s->flag) == 0) continue;
        r = r1d_RangeAlloc();
        if (r == 0) continue;
        s->spec.d0C = s->spec.d50;
        a5b_PairSet(r, &s->spec);
        r->flags |= 1;
        r->d14 |= 2;
        r->d18 = s->flag;
    }
    return 0;
}

/* 0x00035B20: run the three reset passes over the range and node pools,
   then create a range record for every always-on spawn entry (flag -1). */
void r1d_SpawnReset(R1dSpawnList *l)
{
    R1dSpawn *s;
    R1dRange *r;
    if (l == 0) return;
    r1c_PoolForEach(r1c_bank283698 + 0x55140, 0x6C, sub_00034270, 0);
    r1c_PoolForEach(r1c_bank283698, 0xB40, sub_000335D0, 0);
    r1c_PoolForEach(r1c_bank283698 + 0x55140, 0x6C, sub_00034B50, 0);
    for (s = l->head; s != 0; s = s->next) {
        if (s->flag != -1) continue;
        r = r1d_RangeAlloc();
        if (r == 0) continue;
        s->spec.d0C = s->spec.d50;
        a5b_PairSet(r, &s->spec);
        r->flags |= 1;
        r->d14 |= 2;
        r->d18 = s->flag;
    }
}
