/* Area r1k, group 4: message queue B with glyph pop-in 0x0002A570.
   Names inferred. */
#include "r1k.h"

/* 0x0002A570: step queue B. State 0 sets flag bit 0, clears the timer and
   moves to state 1. State 1 advances the timer and scales each glyph
   sprite in turn (glyph i grows from 0 to 1 over 6 time units starting
   at 6*i); at 126 the queue shifts by one entry and returns to state 0. */
void r1k_QueueStepBPop(void)
{
    int i;
    R1kSprite *s;
    switch (r1e_qStateB37E0B4) {
    case 0:
        r1j_seqFlags37E090 |= 1;
        r1e_qWaitB37E0B8 = 0.0f;
        r1e_qStateB37E0B4 = 1;
        return;
    case 1:
        r1k_b37E0BC = 0x80;
        a60_StepByFrame(&r1e_qWaitB37E0B8, 1);
        s = r1k_qSpr37E0C4;
        for (i = 0; i < r1e_qLeftB37E0BE; i++, s++) {
            float t = (float)i * 6.0f;
            if (t > r1e_qWaitB37E0B8) {
                s->sy = 0.0f;
                s->sx = 0.0f;
            } else {
                float v;
                if (r1e_qWaitB37E0B8 > t + 6.0f)
                    v = 1.0f;
                else
                    v = (r1e_qWaitB37E0B8 - t) * 0.16666667f;
                s->sy = v;
                s->sx = v;
            }
        }
        if (!(r1e_qWaitB37E0B8 >= 126.0f))
            return;
        r1e_qB37E094[0] = r1e_qB37E094[1];
        r1e_qB37E094[1] = r1e_qB37E094[2];
        r1e_qB37E094[2] = r1e_qB37E094[3];
        r1e_qB37E094[3] = r1e_qB37E094[4];
        r1e_qB37E094[4] = r1e_qB37E094[5];
        r1e_qB37E094[5] = r1e_qB37E094[6];
        r1e_qB37E094[6] = r1e_qB37E094[7];
        r1e_qB37E094[7] = 0;
        r1e_qStateB37E0B4 = 0;
        return;
    }
}
