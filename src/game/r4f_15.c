/* Area r4f: driver slot reset at 0x001AD150 (r4f_15). Names inferred. */
#include "r4f.h"

/* 0x001AD150: reset a driver slot: release its two driver objects, close both stream
   files and mark it free. regargs: s=ECX (member function without stack arguments).
   Calls 0x001A3A80 with ECX=file; XACT callees are stdcall. */
void R4D_FASTCALL r4f_SlotReset(R4fSlot *s)
{
    if (s->h58) {
        sub_00222662(s->h58);
        s->h58 = 0;
    }
    r4f_FileClose(&s->file5C);
    if (s->h04) {
        sub_002224A2(r4d_drvDev40E690, s->h04);
        s->h04 = 0;
    }
    r4f_FileClose(&s->file08);
    s->fAC = 0;
    s->fB0 = 0;
    s->id00 = -1;
}
