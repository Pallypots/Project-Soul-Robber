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

/* 0x0019C100 */
void Clock_ResetChapter(void)
{
    g_chapterTicks = 0;
}

/* 0x0019C110: same conversion as Clock_GetChapterTime for the second counter. */
float Clock_GetPlayTime(void)
{
    float t = (float)g_playTicks;
    if (Video_GetRateMode() == 0)
        t *= 1.001001f;
    return t * (1.0f / 300.0f);
}

/* 0x0019C190 */
void Clock_SetPlayTime(float seconds)
{
    seconds *= 300.0f;
    if (Video_GetRateMode() == 0)
        seconds *= 0.999f;
    g_playTicks = (int64_t)seconds;
}

/* 0x0019C1E0 */
void Clock_ResetPlayTime(void)
{
    g_playTicks = 0;
}

/* 0x0019C1F0 */
void Clock_Set402FC0(int v)
{
    g_402FC0 = v;
}

/* 0x0019C200 */
void Session_Reset(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        g_sessionSlots[i].b[0] = 0;
        g_sessionSlots[i].b[1] = 0;
        g_sessionSlots[i].b[2] = 0;
        g_sessionSlots[i].b[3] = 0;
        g_sessionSlots[i].scale = 1.0f;
    }
    sub_0019BA70();
    g_402F9C = 0;
    g_402FC4 = 0;
    g_402780 = 0;
}

/* 0x0019C270: accept a request (store `value`, raise 0x00402FA4) only when
 * nothing is loading or busy. Returns 0 accepted, -1 refused. */
int Session_Request(int value)
{
    sub_00102FA0();
    if ((sub_0019FEE0() != 0 || Job_IsRunning() == 0) &&
        sub_001A0CC0() != 7 && g_402FA0 <= 0 && g_402FA8 <= 0 &&
        sub_000479F0() != 0) {
        g_402F9C = value;
        g_402FA4 = 1;
        g_402780 = 0;
        return 0;
    }
    return -1;
}
