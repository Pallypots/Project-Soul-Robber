/* Area r4j: merge all pads (0x001A8EA0). Names inferred. */
#include "r4j.h"

/* 0x001A8EA0: poll the four pads (0x001A8B60), pick the active one
   (0x001A8980), then build the merged pad at 0x0040B888: buttons, analog
   bytes and the edge/hold masks of every connected pad ORed together,
   sticks and axes summed. fDC of every pad is cleared. No inputs; calls
   0x001A8B60 with EAX=pads. */
void r4j_PadMergeAll(void)
{
    R4jPad *p;
    unsigned int i, j;

    sub_001A8B60(r4j_pads40B9A4);
    r4f_PadPickActive();
    R4J_ZERO(&r4j_padAll40B888, sizeof(r4j_padAll40B888));
    for (i = 0; i < 4; i++) {
        p = &r4j_pads40B9A4[i];
        if (p->hD0 != 0) {
            r4j_padAll40B888.stick0A[0] += p->stick0A[0];
            r4j_padAll40B888.stick0A[1] += p->stick0A[1];
            r4j_padAll40B888.stick0A[2] += p->stick0A[2];
            r4j_padAll40B888.stick0A[3] += p->stick0A[3];
            r4j_padAll40B888.axis14[0] = p->axis14[0] + r4j_padAll40B888.axis14[0];
            r4j_padAll40B888.axis14[1] = p->axis14[1] + r4j_padAll40B888.axis14[1];
            r4j_padAll40B888.axis14[2] = p->axis14[2] + r4j_padAll40B888.axis14[2];
            r4j_padAll40B888.axis14[3] = p->axis14[3] + r4j_padAll40B888.axis14[3];
            r4j_padAll40B888.buttons00 |= p->buttons00;
            r4j_padAll40B888.w48 |= p->w48;
            r4j_padAll40B888.w24 |= p->w24;
            for (j = 0; j < 8; j++) {
                r4j_padAll40B888.analog02[j] |= p->analog02[j];
                r4j_padAll40B888.hold4C[j] |= p->hold4C[j];
                r4j_padAll40B888.edge28[j] |= p->edge28[j];
            }
        }
        p->fDC = 0;
    }
}
