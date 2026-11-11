/* Area r1b, group 11: state queues 0x0002A240, 0x0002E3D0, 0x00032600..0x00032BF0 (kept apart from callers/callees). Names inferred. */
#include "r1b.h"

/* 0x0002A240: advance the state queue at 0x0037ED04 once the current state
   has finished (state 0 arms it). */
void r1b_QueueStep37ED04(void)
{
    int i;
    switch (r1b_qstate37ED24) {
    case 0:
        r1b_qstate37ED24 = 1;
        return;
    case 1:
        if (r1b_busy37ED30 != 0) return;
        for (i = 0; i < 7; i++) r1b_queue37ED04[i] = r1b_queue37ED04[i + 1];
        r1b_queue37ED04[7] = 0;
        r1b_qstate37ED24 = 0;
        return;
    }
}

/* 0x00032600: count down the queue timer and pop the state queue at
   0x00381834 when it expires. */
void r1b_Queue381834Tick(void)
{
    if (r1b_qbusy381844 != 0) return;
    if (r1b_qtimer38184C == -1.0f) return;
    sub_000720A0(&r1b_qtimer38184C, 0);
    if (0.0f >= r1b_qtimer38184C) {
        r1b_queue381834[0] = r1b_queue381834[1];
        r1b_queue381834[1] = r1b_queue381834[2];
        r1b_queue381834[2] = r1b_queue381834[3];
        r1b_queue381834[3] = 0;
        r1b_qbusy381844 = 0;
    }
}

/* 0x00032670: pop the state queue and reset the fade (both bytes 0x80, level 0). */
void r1b_Queue381834PopA(void)
{
    if (r1b_qbusy381844 != 0) return;
    r1b_fadeB381875 = 0x80;
    r1b_fadeA381874 = 0x80;
    r1b_queue381834[0] = r1b_queue381834[1];
    r1b_fade381878 = 0.0f;
    r1b_queue381834[1] = r1b_queue381834[2];
    r1b_queue381834[2] = r1b_queue381834[3];
    r1b_queue381834[3] = 0;
    r1b_qbusy381844 = 0;
}

/* 0x00032840: pop the state queue and reset the fade (both bytes 0, level 768). */
void r1b_Queue381834PopB(void)
{
    if (r1b_qbusy381844 != 0) return;
    r1b_queue381834[0] = r1b_queue381834[1];
    r1b_fadeB381875 = 0;
    r1b_fadeA381874 = 0;
    r1b_fade381878 = 768.0f;
    r1b_queue381834[1] = r1b_queue381834[2];
    r1b_queue381834[2] = r1b_queue381834[3];
    r1b_queue381834[3] = 0;
    r1b_qbusy381844 = 0;
}

/* 0x00032A00: pop the state queue and reset the fade (byte B 0x80, level 0). */
void r1b_Queue381834PopC(void)
{
    if (r1b_qbusy381844 != 0) return;
    r1b_queue381834[0] = r1b_queue381834[1];
    r1b_fadeB381875 = 0x80;
    r1b_fade381878 = 0.0f;
    r1b_queue381834[1] = r1b_queue381834[2];
    r1b_queue381834[2] = r1b_queue381834[3];
    r1b_queue381834[3] = 0;
    r1b_qbusy381844 = 0;
}

/* 0x00032BF0: pop the state queue and reset the fade (byte B 0, level 192). */
void r1b_Queue381834PopD(void)
{
    if (r1b_qbusy381844 != 0) return;
    r1b_queue381834[0] = r1b_queue381834[1];
    r1b_fadeB381875 = 0;
    r1b_fade381878 = 192.0f;
    r1b_queue381834[1] = r1b_queue381834[2];
    r1b_queue381834[2] = r1b_queue381834[3];
    r1b_queue381834[3] = 0;
    r1b_qbusy381844 = 0;
}
