/* Area r1j, group 9: combo display state 0x0002ACF0.
   Names inferred. */
#include "r1j.h"

/* 0x0002ACF0: step the combo display. Phase 0 starts it (sequence flag
   bit 0, a 160-frame timer). Phase 1 counts the timer down; a combo of 5
   or more ends it at once and pops the command queue. Otherwise, once the
   timer has run out (and, while 0x0037EE18 is set, only on a pending
   reset) the shown values are cleared, the combo itself too unless a
   reset was pending, and command 1 is finished or command 3 turns into
   command 2. */
void r1j_ComboStep(void)
{
    int16_t combo, reset;
    int cmd;
    switch (r1j_comboPhase) {
    case 0:
        r1j_seqFlags37EDEC |= 1;
        r1j_comboLast = 0;
        r1j_comboTimer = 160.0f;
        r1j_comboByte = 0;
        r1j_comboPhase = 1;
        return;
    case 1:
        sub_000720A0(&r1j_comboTimer, 0);
        combo = r1j_combo37EEBE;
        if (combo >= 5) {
            r1j_cmdQueue37EECC[0] = r1j_cmdQueue37EECC[1];
            r1j_cmdQueue37EECC[1] = r1j_cmdQueue37EECC[2];
            r1j_cmdQueue37EECC[2] = r1j_cmdQueue37EECC[3];
            r1j_cmdQueue37EECC[3] = r1j_cmdQueue37EECC[4];
            r1j_cmdQueue37EECC[4] = r1j_cmdQueue37EECC[5];
            r1j_cmdQueue37EECC[5] = r1j_cmdQueue37EECC[6];
            r1j_cmdQueue37EECC[6] = r1j_cmdQueue37EECC[7];
            r1j_cmdQueue37EECC[7] = 0;
            r1j_comboPhase = 0;
            return;
        }
        reset = r1j_comboReset37EEC4;
        if (r1j_g37EE18 != 0 && reset != 1)
            return;
        if (!(0.0f >= r1j_comboTimer))
            return;
        r1j_comboLast = combo;
        r1j_comboPhase = 0;
        if (reset != 1) {
            r1j_combo37EEBE = 0;
            r1j_comboRank37EEBC = 0;
        }
        cmd = r1j_cmdQueue37EECC[0];
        r1j_comboByte = 0;
        r1j_comboReset37EEC4 = 0;
        r1j_comboShown37EEC2 = 0;
        r1j_comboRankShown37EEC0 = 0;
        switch (cmd) {
        case 1:
            r1j_cmdQueue37EECC[0] = 0;
            r1j_seqState37EDF0 = 0;
            r1j_comboPhase = 0;
            return;
        case 3:
            r1j_cmdQueue37EECC[1] = 0;
            r1j_seqState37EDF4 = 0;
            r1j_comboPhase = 0;
            r1j_cmdQueue37EECC[0] = 2;
            r1j_seqState37EDF0 = 2;
            return;
        }
        return;
    }
}
