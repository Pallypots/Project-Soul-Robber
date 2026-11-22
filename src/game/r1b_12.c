/* Area r1b, group 12: fade sequence 0x00032C40 driving the queue at 0x00381834. Names inferred. */
#include "r1b.h"

extern float r1b_qtime381848;

/* 0x00032C40: four-step fade (arm, fade B in, fade A in, fade level out),
   then pop the state queue. */
void r1b_FadeSeq32C40(void)
{
    float t;
    switch (r1b_qbusy381844) {
    case 0:
        r1b_qbusy381844++;
        r1b_qtime381848 = 40.0f;
        r1b_fadeB381875 = 0;
        r1b_fadeA381874 = 0;
        r1b_fade381878 = 192.0f;
        return;
    case 1:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fadeB381875 = (uint8_t)(int32_t)((double)(40.0f - r1b_qtime381848) * 0.025f * 128.0f);
        t = r1b_qtime381848;
        if (!(0.0f >= t)) return;
        r1b_fadeB381875 = 0x80;
        r1b_fadeA381874 = 0x80;
        break;
    case 2:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fadeA381874 = (uint8_t)(int32_t)((double)(20.0f - r1b_qtime381848) * 0.05f * 128.0f);
        t = r1b_qtime381848;
        if (!(0.0f >= t)) return;
        break;
    case 3:
        sub_000720A0(&r1b_qtime381848, 0);
        t = r1b_qtime381848;
        r1b_fade381878 = t * 0.05f * 192.0f;
        if (!(0.0f >= t)) return;
        r1b_fade381878 = 0.0f;
        r1b_queue381834[0] = r1b_queue381834[1];
        r1b_queue381834[1] = r1b_queue381834[2];
        r1b_queue381834[2] = r1b_queue381834[3];
        r1b_queue381834[3] = 0;
        r1b_qbusy381844 = 0;
        return;
    default:
        return;
    }
    r1b_qtime381848 = t + 20.0f;
    r1b_qbusy381844++;
}

/* 0x000328A0: three-step fade (arm, fade B in over 60 units while the level
   drops, fade A in over the last 60), then pop the state queue. */
void r1b_FadeSeq328A0(void)
{
    switch (r1b_qbusy381844) {
    case 0:
        r1b_qtime381848 = 120.0f;
        r1b_qbusy381844++;
        r1b_fadeB381875 = 0;
        r1b_fadeA381874 = 0;
        r1b_fade381878 = 768.0f;
        return;
    case 1:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fade381878 = r1b_qtime381848 * (1.0f / 120.0f) * 768.0f;
        r1b_fadeB381875 = (uint8_t)(int32_t)((double)(120.0f - r1b_qtime381848) * (1.0f / 60.0f) * 128.0f);
        if (!(60.0f >= r1b_qtime381848)) return;
        r1b_qbusy381844++;
        r1b_fadeB381875 = 0x80;
        return;
    case 2:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fade381878 = r1b_qtime381848 * (1.0f / 120.0f) * 768.0f;
        r1b_fadeA381874 = (uint8_t)(int32_t)((double)(60.0f - r1b_qtime381848) * (1.0f / 60.0f) * 128.0f);
        if (!(0.0f >= r1b_qtime381848)) return;
        r1b_queue381834[0] = r1b_queue381834[1];
        r1b_queue381834[1] = r1b_queue381834[2];
        r1b_queue381834[2] = r1b_queue381834[3];
        r1b_queue381834[3] = 0;
        r1b_qbusy381844 = 0;
        r1b_fade381878 = 0.0f;
        return;
    }
}

void sub_001A8A70(int m);
void sub_00079340(void);

/* 0x000326C0: reverse three-step fade (arm with both bytes full and stop the
   movie, fade A out over 30 units, fade B out), raising the level to 768,
   then pop the state queue. */
void r1b_FadeSeq326C0(void)
{
    switch (r1b_qbusy381844) {
    case 0:
        r1b_qtime381848 = 60.0f;
        r1b_qbusy381844++;
        r1b_fadeB381875 = 0x80;
        r1b_fadeA381874 = 0x80;
        r1b_fade381878 = 0.0f;
        sub_001A8A70(0);
        sub_00079340();
        return;
    case 1:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fade381878 = (60.0f - r1b_qtime381848) * (1.0f / 60.0f) * 768.0f;
        r1b_fadeA381874 = (uint8_t)(int32_t)((double)(r1b_qtime381848 - 30.0f) * (1.0f / 30.0f) * 128.0f);
        if (!(30.0f >= r1b_qtime381848)) return;
        r1b_qbusy381844++;
        r1b_fadeA381874 = 0;
        return;
    case 2:
        sub_000720A0(&r1b_qtime381848, 0);
        r1b_fade381878 = (60.0f - r1b_qtime381848) * (1.0f / 60.0f) * 768.0f;
        r1b_fadeB381875 = (uint8_t)(int32_t)((double)r1b_qtime381848 * (1.0f / 30.0f) * 128.0f);
        if (!(0.0f >= r1b_qtime381848)) return;
        r1b_fadeB381875 = 0;
        r1b_fade381878 = 768.0f;
        r1b_queue381834[0] = r1b_queue381834[1];
        r1b_queue381834[1] = r1b_queue381834[2];
        r1b_queue381834[2] = r1b_queue381834[3];
        r1b_queue381834[3] = 0;
        r1b_qbusy381844 = 0;
        return;
    }
}
