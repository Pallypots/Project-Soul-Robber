/* Area r6g: movie screen state step (r6g_15). Names inferred. */
#include "r6g.h"

/* Restart the movie screen with the given animation of each of its four sprites. */
#define R6G_MOVIE_RESTART(a, b, c, d)           \
    sub_00078050();                             \
    a60_v3E7508 = 0;                            \
    a60_v3E750C = 0xF2;                         \
    a60_v3E7510 = 0;                            \
    a60_v3E7514 = 0;                            \
    sub_000150B0(a60_buf3E75F4, a);             \
    sub_000150B0(a60_buf3E7690, b);             \
    sub_000150B0(a60_buf3E772C, c);             \
    sub_000150B0(a60_buf3E77C8, d)

/* 0x00078F50: one step of the movie screen. While a movie is playing
   (a60_v3E750C == 1) wait for it to end and restore the display; otherwise act
   on the selected entry (1..3 restart the screen with that entry's sprite
   animations, 1 leaves instead when 0x00054180 reports it; 0 and 4 close). */
void r6g_MovieScreenStep(void)
{
    if (a60_v3E750C == 1) {
        sub_0019B9E0();
        sub_00048590();
        while (sub_00047950() != 1)
            sub_000580D0();
        sub_0019B9F0();
        sub_0019D8A0(1);
        sub_00054160(1);
        sub_001A0D30(7, 0);
        a60_v3E750C = 0;
        return;
    }
    switch (a60_v3E7530) {
    case 1:
        sub_001A8A70(0);
        r6c_v3E7550 = 1;
        if (sub_00054180() == 1) {
            a60_v3E7514 = 0;
            a60_v3E7510 = 0;
            a60_v3E750C = 0;
            if (*r1f_g42C7A0 != 2) {
                a60_v3E7508 = 2;
                sub_0019D8A0(1);
            } else {
                a60_v3E7508 = 4;
                a60_v3E7530 = 0;
                sub_0019D8A0(1);
            }
        } else {
            R6G_MOVIE_RESTART(2, 0x18, 4, 5);
        }
        break;
    case 2:
        sub_001A8A70(0);
        r6c_v3E7550 = 1;
        R6G_MOVIE_RESTART(2, 3, 0x19, 5);
        break;
    case 3:
        sub_001A8A70(0);
        r6c_v3E7550 = 1;
        R6G_MOVIE_RESTART(2, 3, 4, 0x1A);
        break;
    case 0:
    case 4:
        r6c_v3E7550 = 0;
        a60_v3E7508 = 2;
        a60_v3E750C = 0;
        a60_v3E7510 = 0;
        a60_v3E7514 = 0;
        break;
    }
    a60_v3E74B8 = 0;
}
