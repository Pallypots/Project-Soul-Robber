/* Area r4: worker-thread exit stub (r4_8), kept apart from its register-argument callee. Names inferred. */
#include "r4.h"

/* 0x001AD540: mark the current worker thread finished (state 1) and exit it.
   Calls 0x001AD340 with EAX=current thread id and state=1 on the stack. */
void r4_ThreadExit(void)
{
    r4_ThreadSetState(sub_001BD50A(), 1);
    sub_001BD345(0);
}
