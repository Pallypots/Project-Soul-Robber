/* Area r1f, group 14: title state dispatcher 0x0004E970. Names inferred. */
#include "r1f.h"

/* 0x0004E970: mirror the movie state into flag bit 0 of 0x00428F45, then
   run the handler of the current title state (0..4). */
void r1f_TitleStep(void)
{
    if (sub_00079460() != 0) {
        if (!(a60_b428F45 & 1))
            a60_b428F45 |= 1;
    } else if (a60_b428F45 & 1) {
        a60_b428F45 &= ~1;
    }
    switch (a4c_state3E0000) {
    case 0:
        sub_0004B090();
        break;
    case 1:
        sub_0004D9E0();
        break;
    case 2:
        sub_0004E830();
        break;
    case 3:
        sub_0004E1C0();
        break;
    case 4:
        sub_0004E3A0();
        break;
    }
}

/* 0x0004E830: unless a movie is playing, run the handler of the title
   sub-state (0, 1, 16 or 17). */
void r1f_TitleSubStep(void)
{
    if (sub_00079460() != 0)
        return;
    switch (r1f_sub3E0004) {
    case 0:
        sub_0004B320();
        break;
    case 1:
        sub_0004B7A0();
        break;
    case 16:
        sub_0004E030();
        break;
    case 17:
        sub_0004BA20();
        break;
    }
}
