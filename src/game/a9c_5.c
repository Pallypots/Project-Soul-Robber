/* Area a9c, 0x00196000-0x00197FFF. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9c.h"

/* 0x00196AE0: free the three heap blocks at 0x00401830, 0x00401828 and 0x0040182C. */
void a9c_FreeBlocks401828(void)
{
    if (a19_g401830) {
        sub_00053880(a19_g401830);
        a19_g401830 = 0;
    }
    if (a19_g401828) {
        sub_00053880(a19_g401828);
        a19_g401828 = 0;
    }
    if (a19_g40182C) {
        sub_00053880(a19_g40182C);
        a19_g40182C = 0;
    }
}
