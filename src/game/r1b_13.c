/* Area r1b, group 13: fade sequence 0x00032A50 driving the queue at 0x00381834. Names inferred. */
#include "r1b.h"

extern float r1b_qtime381848;

/* 0x00032A50: four-step fade (arm with both bytes full, raise the level to
   192, fade A out over 20 units, fade B out over 60), then pop the queue. */
void r1b_FadeSeq32A50(void)
{
    float t;
    switch (r1b_qbusy381844) {
    case 0:
        r1b_qtime381848 = 40.0f;
        r1b_qbusy381844++;
        r1b_fadeB381875 = 0x80;
        r1b_fadeA381874 = 0x80;
        r1b_fade381878 = 0.0f;
        return;
    case 1:
        sub_000720A0(&r1b_qtime381848, 0);
        t = r1b_qtime381848;
        r1b_fade381878 = (20.0f - t) * 0.05f * 192.0f;
        if (!(0.0f >= t)) return;
        r1b_qbusy381844++;
        r1b_fade381878 = 192.0f;
        r1b_qtime381848 = t + 20.0f;
        return;
    case 2:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fadeA381874 = (uint8_t)(int32_t)((double)r1b_qtime381848 * 0.05f * 128.0f);
        t = r1b_qtime381848;
        if (!(0.0f >= t)) return;
        r1b_qtime381848 = t + 60.0f;
        r1b_qbusy381844++;
        r1b_fadeA381874 = 0;
        return;
    case 3:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fadeB381875 = (uint8_t)(int32_t)((double)r1b_qtime381848 * (1.0f / 60.0f) * 128.0f);
        if (!(0.0f >= r1b_qtime381848)) return;
        r1b_fadeB381875 = 0;
        r1b_queue381834[0] = r1b_queue381834[1];
        r1b_queue381834[1] = r1b_queue381834[2];
        r1b_queue381834[2] = r1b_queue381834[3];
        r1b_queue381834[3] = 0;
        r1b_qbusy381844 = 0;
        return;
    }
}
