/* Area r1j, group 6: save slot time stamps 0x00054860.
   Names inferred. */
#include "r1j.h"

/* jump to `later` when time stamp a (six words, most significant first)
   is later than b, else to `notLater` (the original has this compare
   inline at every use) */
#define R1J_STAMP_CMP(a, b, later, notLater) do { \
    if ((a)[0] > (b)[0]) goto later; \
    if ((a)[0] != (b)[0]) goto notLater; \
    if ((a)[1] > (b)[1]) goto later; \
    if ((a)[1] != (b)[1]) goto notLater; \
    if ((a)[2] > (b)[2]) goto later; \
    if ((a)[2] != (b)[2]) goto notLater; \
    if ((a)[3] > (b)[3]) goto later; \
    if ((a)[3] != (b)[3]) goto notLater; \
    if ((a)[4] > (b)[4]) goto later; \
    if ((a)[4] != (b)[4]) goto notLater; \
    if ((a)[5] <= (b)[5]) goto notLater; \
} while (0)

/* 0x00054860: index (0..4) of the save slot with the latest time stamp
   (the first one wins on a tie). */
int r1j_LatestSaveSlot(void)
{
    R1jSave *s = r1j_save3E3934;
    const uint16_t *best = s->slot[0].stamp;
    const uint16_t *c;
    int idx = 0;
    c = s->slot[1].stamp;
    R1J_STAMP_CMP(c, best, later1, done1);
later1:
    best = c;
    idx = 1;
done1:
    c = s->slot[2].stamp;
    R1J_STAMP_CMP(c, best, later2, done2);
later2:
    best = c;
    idx = 2;
done2:
    c = s->slot[3].stamp;
    R1J_STAMP_CMP(c, best, later3, done3);
later3:
    best = c;
    idx = 3;
done3:
    c = s->slot[4].stamp;
    R1J_STAMP_CMP(c, best, later4, done4);
later4:
    idx = 4;
done4:
    return idx;
}
