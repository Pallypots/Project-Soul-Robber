/* Area r4c: render target offset helper 0x001A1E90 (r4c_10). Names inferred. */
#include "r4c.h"

/* 0x001A1E90: set the offset of target i (0..13) to off (< 0x88) and return the resulting position, or 0. Stack args (i off). */
uint32_t r4c_TargetSetOffset(int i, uint32_t off)
{
    void *t;
    uint32_t base;
    if (i >= 14)
        return 0;
    if (off >= 0x88)
        return 0;
    t = r4c_targets404734[i];
    sub_001D2750(t, off);
    sub_001D2850(t, &base);
    off += base;
    return off < 0x88 ? off : 0;
}
