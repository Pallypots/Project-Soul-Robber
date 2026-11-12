/* Area m1, file 1. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "m1.h"

/* 0x00072EE0: arm a timed fade record, then hand over to 0x00072DD0.
 * Hangs if the time is not positive (assert in the original). */
void m1_FadeStart72EE0(M1Fade *f, int mode, float time, int arg)
{
    if (!(time > 0.0f))
        for (;;) ;
    f->b4 = 0;
    f->b5 = 0;
    f->on = 1;
    f->mode = (uint16_t)mode;
    f->time = time;
    f->w6 = 1;
    sub_00072DD0(f, mode, time, arg);
}
