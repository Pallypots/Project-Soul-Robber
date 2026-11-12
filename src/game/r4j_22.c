/* Area r4j: fade job of the game-logic thread (0x0019D120). Names inferred. */
#include "r4j.h"

/* 0x0019D120: job that runs a screen transition: start fade (1, 2, 0),
   wait half a second, wait while channel 0 is busy (0x00032450 and
   0x00032470), wait for flag 0x00402FDC, wait 0.1 s more, start fade
   (1, 1, 0) unless state 0x0041316C is 10 with 0x00413170 clear, run
   0x0003DD10, wait while channel 1 is busy, clear 0x00402FDC, wait for
   flag 0x00402FE0, clear 0x0040B0EC and finish the job (tail call
   0x00058190). Each wait step yields with 0x000580D0, most after the
   per-frame update 0x00033250. No inputs. */
void r4j_FadeJob(void)
{
    float t1 = 0.0f;
    float t2 = 0.0f;

    sub_00032140(1, 2, 0);
    do {
        t1 = r4c_frameSeconds + t1;
        sub_000580D0();
    } while (0.5f > t1);
    if (sub_00032450(0)) {
        do {
            if (!sub_00032470(0))
                break;
            sub_00033250();
            sub_000580D0();
        } while (sub_00032450(0));
    }
    while (r4e_g402FDC != 1) {
        sub_00033250();
        sub_000580D0();
    }
    do {
        t2 = r4c_frameSeconds + t2;
        sub_00033250();
        sub_000580D0();
    } while (0.1f > t2);
    if (a30_g41316C != 10 || a30_g413170 != 0)
        sub_00032140(1, 1, 0);
    sub_0003DD10();
    if (sub_00032450(1)) {
        do {
            if (!sub_00032470(1))
                break;
            sub_00033250();
            sub_000580D0();
        } while (sub_00032450(1));
    }
    sub_00033250();
    r4e_g402FDC = 0;
    while (r4e_g402FE0 != 1) {
        sub_00033250();
        sub_000580D0();
    }
    sub_001A5380(0);
    sub_00058190();
}
