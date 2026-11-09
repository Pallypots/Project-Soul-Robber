/* Video rate mode accessor. Reference build OOGIE-XBOX-US-RETAIL. Names
 * inferred. Kept in its own file: the original is far from its callers
 * (0x000529E0 vs 0x0019C030), so it was a separate translation unit and was
 * not inlined. */
#include "oogie.h"

/* 0x000529E0 */
int Video_GetRateMode(void)
{
    return g_videoRateMode;
}
