/* Area r3b: callers of other r3b helpers (r3b_4, kept apart so cl does not inline the callees). Names inferred. */
#include "r3b.h"

/* 0x001357C0: 1 when any type-5 or type-15 object is flagged (0x00135780).
   calls 0x00135780 with EAX=kind. */
int r3b_AnyFlagged1357C0(void)
{
    if (r3b_Any135780(5))
        return 1;
    return r3b_Any135780(0xF) != 0;
}
