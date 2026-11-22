/* Area r1e, group 14: fade sequence C (queue at 0x00381850). Names inferred. */
#include "r1e.h"

extern float   r1e_seqVal38186C;   /* 0x0038186C */
extern uint8_t r1e_fadeA381876;    /* 0x00381876 */
extern uint8_t r1e_fadeB381877;    /* 0x00381877 */
extern float   r1e_lvlA38187C;     /* 0x0038187C */
extern float   r1e_lvlB381880;     /* 0x00381880 */
float sub_001A3ED0(float a);       /* sine (Hypothesis) */

/* 0x00032DD0: two-step fade on sequence C: arm (120 units), then over the first 60 units
   fade byte A out and ease level A, over the last 60 fade byte B out and ease level B;
   pop the queue when the timer runs out. */
void r1e_FadeSeqC32DD0(void)
{
    float x;
    switch (r1e_seqStateC381860) {
    case 0:
        r1e_seqTimeC381864 = 120.0f;
        r1e_seqStateC381860++;
        r1e_seqVal38186C = 360.0f;
        r1e_timer381870 = 600.0f;
        return;
    case 1:
        sub_000720A0(&r1e_seqTimeC381864, 0);
        if (r1e_seqTimeC381864 >= 60.0f) {
            x = (r1e_seqTimeC381864 - 60.0f) * (1.0f / 60.0f);
            r1e_fadeA381876 = (uint8_t)(0x80 - (int32_t)((double)x * 128.0f));
            r1e_fadeB381877 = 0;
            x = sub_001A3ED0((x + 1.0f) * 90.0f * 0.017453292f);
            r1e_lvlB381880 = 512.0f;
            r1e_lvlA38187C = (1.0f - x) * 0.5f * 512.0f;
        } else {
            x = r1e_seqTimeC381864 * (1.0f / 60.0f);
            r1e_fadeA381876 = 0x80;
            r1e_fadeB381877 = (uint8_t)(0x80 - (int32_t)((double)x * 128.0f));
            x = sub_001A3ED0((x + 1.0f) * 90.0f * 0.017453292f);
            r1e_lvlA38187C = 0.0f;
            r1e_lvlB381880 = (1.0f - x) * 0.5f * 512.0f;
        }
        if (!(0.0f >= r1e_seqTimeC381864))
            return;
        r1e_seqQC381850[0] = r1e_seqQC381850[1];
        r1e_seqQC381850[1] = r1e_seqQC381850[2];
        r1e_seqQC381850[2] = r1e_seqQC381850[3];
        r1e_seqQC381850[3] = 0;
        r1e_seqStateC381860 = 0;
        return;
    }
}
