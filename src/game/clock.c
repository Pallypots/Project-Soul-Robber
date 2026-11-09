/* Chapter clock. Reference build OOGIE-XBOX-US-RETAIL. Names inferred.
 * The clock counts 300 ticks per second. When the video rate mode is 0 the
 * game scales by 1.001001 / 0.999, which fits 59.94 Hz NTSC timing
 * (Hypothesis). Records: docs/functions/clock.md */
#include "oogie.h"

/* 0x0019C030 */
float Clock_GetChapterTime(void)
{
    float t = (float)g_chapterTicks;
    if (Video_GetRateMode() == 0)
        t *= 1.001001f;
    return t * (1.0f / 300.0f);
}

/* 0x0019C0B0 */
void Clock_SetChapterTime(float seconds)
{
    seconds *= 300.0f;
    if (Video_GetRateMode() == 0)
        seconds *= 0.999f;
    g_chapterTicks = (int64_t)seconds;
}
