/* Area r4d: thread exit 0x001AD520 (r4d_17, apart from its callee so it is not inlined). Names inferred. */
#include "r4d.h"

/* 0x001AD520: free the calling thread's table entry and exit the thread with code 1. No inputs. */
void r4d_ThreadExitSelf(void)
{
    r4d_ThreadClose(sub_001BD50A());
    sub_001BD345(1);
}
