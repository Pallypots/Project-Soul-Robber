/* Area r6d: resource table search at 0x0007E680 (r6d_14). Names inferred. */
#include "r6d.h"

/* 0x0007E680: first table entry whose bit 0 at +0x0C is clear; stores it in *out and
   returns 0, or returns -1.
   regargs: t=EDI */
int r6d_TableFirstFree(void *t, void **out)
{
    int i = 0;
    uint8_t *e;
    while (i < *(int32_t *)t && (e = (uint8_t *)a12_Table_Get(t, i)) != 0) {
        if (!(e[0x0C] & 1)) {
            if (out)
                *out = e;
            return 0;
        }
        i++;
    }
    return -1;
}
