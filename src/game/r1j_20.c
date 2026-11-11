/* Area r1j, group 20: HUD sequence dispatcher 0x0002C5E0.
   Names inferred. */
#include "r1j.h"

/* 0x0002C5E0: per-frame step of five HUD sequence blocks. Each block is
   prepared by its own update (0x0002C150/0x0002C1B0, 0x0002C230,
   0x0002C2A0, 0x0002C300, 0x0002C370) and then runs the handler of its
   current state; state 0 clears its active flag (bit 0). The last
   block's handlers are tail calls. */
void r1j_HudSeqStep(void)
{
    sub_0002C150();
    sub_0002C1B0();
    switch (r1j_seqStateC37DAA4) {
    case 0: r1j_seqFlagsC37DAA0 &= ~1u; break;
    case 1: sub_00029680(); break;
    case 2: sub_00029770(); break;
    case 3: sub_00029850(); break;
    case 4: sub_000298C0(); break;
    }
    sub_0002C230();
    switch (r1j_seqState37DCFC) {
    case 0: r1j_seqFlags37DCF8 &= ~1u; break;
    case 1: sub_00029DC0(); break;
    case 2: sub_00029EF0(); break;
    case 3: sub_0002A000(); break;
    }
    sub_0002C2A0();
    switch (r1j_seqState37E094) {
    case 0: r1j_seqFlags37E090 &= ~1u; break;
    case 1: sub_0002A570(); break;
    case 2: sub_0002A6C0(); break;
    case 3: sub_0002A7A0(); break;
    case 4: sub_0002A830(); break;
    }
    sub_0002C300();
    switch (r1j_seqStateE37F484) {
    case 0: r1j_seqFlagsE37F480 &= ~1u; break;
    case 1: sub_0002B140(); break;
    case 2: sub_0002B230(); break;
    case 3: sub_0002B310(); break;
    }
    sub_0002C370();
    switch (r1j_seqState37FB40) {
    case 0: r1j_seqFlags37FB3C &= ~1u; break;
    case 1: sub_0002B5A0(); break;
    case 2: sub_0002B690(); break;
    case 3: sub_0002B770(); break;
    }
}
