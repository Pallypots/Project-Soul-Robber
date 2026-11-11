/* Area r1f, group 13: screen worker job 0x0002E470. Names inferred. */
#include "r1f.h"

/* 0x0002E470: screen job: until the screen mode reaches 4, run the handler
   of the current mode (0..3) and the state update each frame while the
   state is 10000; then finish the job. */
void r1f_ScreenJob(void)
{
    while (r1c_mode381400 != 4) {
        if (r1c_state3816D0 == 10000) {
            switch (r1c_mode381400) {
            case 0:
                sub_0002D230();
                break;
            case 1:
                sub_0002D790();
                break;
            case 2:
                sub_0002DBC0();
                break;
            case 3:
                sub_0002C870();
                break;
            }
            sub_0002C750();
        }
        sub_000580D0();
    }
    sub_001A0D70();
    sub_00058190();
}

