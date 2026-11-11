/* Area r4c: render target selection 0x001A1EE0 (r4c_11, apart from its callee). Names inferred. */
#include "r4c.h"

/* 0x001A1EE0: make target i (0..13) current at offset 0; returns 0, -1 if already current, 2 on failure. Stack args. */
int r4c_TargetSelect(int i)
{
    void *cur;
    if (i >= 14)
        return 2;
    sub_001D2470(&cur);
    if (r4c_targets404734[i] == cur)
        return -1;
    r4c_offsets4046FC[i] = 0;
    if (!r4c_TargetSetOffset(i, 0))
        return 2;
    sub_001D27B0(r4c_targets404734[i], r4c_offsets4046FC[i]);
    r4c_curTarget40476C = i;
    return 0;
}
