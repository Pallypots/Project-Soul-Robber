/* Area afc, group 3: random actor events 0x000F6C50. Names inferred. */
#include "afc.h"

/* 0x000F6C50: rarely (1 in 3000) switch an active actor to sub-state 11. */
void afc_RandomTaunt(AfcActor *o)
{
    if (o == 0)
        return;
    if (sub_001C7EE1() % 3000 == 0 && o->state >= 7 && o->state <= 10)
        sub_000F62C0(o, 11);
}
