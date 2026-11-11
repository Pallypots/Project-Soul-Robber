/* Area r1, group 2: callers of register-argument helpers near 0x0001A390. Names inferred. */
#include "r1.h"
#include <string.h>

/* 0x0001A390: copy set B (when a selection exists) or set A into the current set.
   regargs: o=EAX; calls 0x000192C0 with EDI=o */
void r1_LoadCurSet(R1SelOwner *o)
{
    if (r1_PickSel(o)) memcpy(o->cur, o->setB, sizeof o->cur);
    else memcpy(o->cur, o->setA, sizeof o->cur);
}
