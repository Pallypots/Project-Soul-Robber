/* Area r4e: frame timer at 0x001AE430 and 0x001AE710 (r4e_14). Names inferred. */
#include "r4e.h"

/* 0x001AE430: read the performance counter frequency and start the frame timer.
   No inputs. */
void r4e_TimerInit(void)
{
    int64_t freq;
    sub_001BD59E(&freq);
    r4e_tick40F0E8 = 1.0f / (float)freq;
    sub_001BD58D(&r4e_now40F0E0);
    r4e_last40F118 = r4e_now40F0E0;
    r4e_total40F0F0 = 0;
    r4e_delta40F108 = 0;
    r4e_delta40F110 = 0;
}

/* 0x001AE710: advance the frame timer: current time, frame delta and running total,
   in ticks and in seconds. No inputs. */
void r4e_TimerTick(void)
{
    sub_001BD58D(&r4e_now40F0E0);
    r4e_nowSec40F0F8 = (float)r4e_now40F0E0 * r4e_tick40F0E8;
    r4e_delta40F108 = r4e_now40F0E0 - r4e_last40F118;
    r4e_last40F118 = r4e_now40F0E0;
    r4e_delta40F110 = r4e_delta40F108;
    r4e_total40F0F0 += r4e_delta40F108;
    r4e_dt40F0FC = r4e_dt40F0EC = (float)r4e_delta40F108 * r4e_tick40F0E8;
    r4e_totalSec40F100 = (float)r4e_total40F0F0 * r4e_tick40F0E8;
}
