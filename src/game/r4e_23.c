/* Area r4e: fade jobs at 0x0019C6F0 and 0x001A1280 (r4e_23). Names inferred. */
#include "r4e.h"

/* 0x0019C6F0: job: if 0x00336DD0 is set, mark the job busy, wait for 0x00036D40,
   apply the stored offsets and ramp the level from 0 to 128 over one second's worth
   of frames; then finish the transition. Stack arg (job). */
void r4e_FadeInJob(int *job)
{
    float t = 0.0f;
    float step = 128.0f / (1.0f / r4c_frameSeconds);
    r4e_g402FD4 = 0;
    if (a19_g336DD0) {
        job[2] |= 1;
        while (sub_00036D40()) {
            sub_00036C90();
            sub_000580D0();
        }
        sub_00036F90(a9b_g402FC8, a9b_g402FCC, a9b_g402FD0);
        do {
            sub_00036FD0(t);
            t += step;
            sub_000580D0();
        } while (128.0f > t);
        sub_00036FD0(128.0f);
        sub_000580D0();
    }
    job[2] &= ~1;
    sub_0003DD10();
    sub_000325A0(1);
    r4e_g402FD4 = 1;
    sub_00058190();
}

/* 0x001A1280: job: ramp the shake/fade level from 0 to 128 at 0.7 s per full ramp
   while no movie is playing, then finish and mark the job done. Stack arg (job). */
void r4e_ShakeFadeJob(int *job)
{
    float t = 0.0f;
    float step = 128.0f / (0.7f / r4c_frameSeconds);
    do {
        if (!sub_00079460()) {
            sub_00036F40(0, 0, 0, t);
            t += step;
        }
        sub_000580D0();
    } while (128.0f > t);
    sub_00036FD0(128.0f);
    sub_000580D0();
    sub_0003DD10();
    sub_000325A0(1);
    job[2] = 1;
    sub_00058190();
}
