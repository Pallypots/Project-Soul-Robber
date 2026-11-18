/* Area m1, file 219: memory-unit/pad enumeration. Names inferred. */
#include <intrin.h>
#include "r4e.h"

/* 0x001A8AA0: clear the four pad records, open each connected device and read its capabilities; when exactly one is
   present make it the selected pad (old selection saved). Optionally returns the record array. */
int m1_PadScan1A8AA0(R4ePad **out)
{
    uint32_t mask = sub_00259432(r4e_padType257FEC);
    int count = 0, first = -1, i = 0;
    unsigned off;
    for (off = 0; off < sizeof r4e_pads40B9A8; off += sizeof(R4ePad), i++) {
        R4ePad *p = (R4ePad *)((uint8_t *)r4e_pads40B9A8 + off);
        __stosd((unsigned long *)p, 0, 0x47);
        if (mask & (1u << i)) {
            void *h = sub_0025912B(r4e_padType257FEC, i, 0, 0);
            p->hD0 = h;
            if (h) {
                sub_0025918D(h, p->capsB6);
                count++;
                if (first == -1) first = i;
            }
        }
    }
    if (count == 1) {
        aac_g3650CC = r4d_padSel3650C8;
        r4d_padSel3650C8 = first;
    }
    if (out) *out = r4e_pads40B9A8;
    return 0;
}
