/* Area r6d: status screen wrapper at 0x00065EE0 (r6d_6). Names inferred. */
#include "r6d.h"

/* 0x00065EE0: stack-argument wrapper of 0x00065E50.
   calls 0x00065E50 with ESI=i */
void r6d_StatusShowTextS(int i, int id)
{
    r6d_StatusShowText(i, id);
}
