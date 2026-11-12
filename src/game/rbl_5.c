/* Area rbl: effect slot pools. Names inferred. */
#include "rbl.h"

/* 0x00181870: clear the 4 slots of the table at 0x003FE1C8 (objects, counters, timer and
   vectors). The original's loop is fully unrolled, as modern cl does. No inputs. */
void rbl_SlotsReset181870(void)
{
    int i;

    for (i = 0; i < 4; i++) {
        RblSlot44 *s = &r3c_slots3FE1C8[i];
        s->obj00 = 0;
        s->act04 = 0;
        s->i34 = 0;
        s->i08 = 0;
        s->s0C = 0;
        s->f10 = 0.0f;
        s->v18[0] = 0.0f;
        s->v18[1] = 0.0f;
        s->v18[2] = 0.0f;
        s->v38[0] = 0.0f;
        s->v38[1] = 0.0f;
        s->v38[2] = 0.0f;
        s->v24[0] = 0.0f;
        s->v24[1] = 0.0f;
        s->v24[2] = 0.0f;
        s->v24[3] = 0.0f;
    }
}
