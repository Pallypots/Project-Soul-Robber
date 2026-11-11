/* Area r1f, group 9: job group setup and model animation restarts
   0x000575D0..0x0005AB70. Names inferred. */
#include "r1f.h"

/* 0x000575D0: register the three worker jobs of group g, release slots 0
   and -1 and clear the related state. */
void r1f_JobsInit(void *g)
{
    sub_001A8A70(2);
    sub_001A1030(g, 0, 1, sub_000550F0, 8, 0x2000);
    sub_001A1030(g, 1, 1, sub_000574F0, 8, 0x2000);
    sub_001A1030(g, -1, 4, sub_00057160, 8, 0x2000);
    sub_001A1060(g, 0);
    sub_001A1060(g, -1);
    r1f_g3E3940 = 0;
    a5b_g3E3910 = 0;
    r1f_g42C7A0 = 0;
}


/* 0x0005A200: save job: until the save state reaches 3, either wait for the
   cancel button while a movie plays or run the handler of the save state
   (0..2); then finish the job. */
void r1f_SaveJob(void)
{
    uint32_t pads;
    while (r1e_sndTab3E4750 != 3) {
        if (sub_00079460() != 0 && sub_00072FA0(a4c_obj428F40) == 0 && r1e_sndTab3E4750 != 2)
            r1f_busy3E4770 = 1;
        if (r1f_busy3E4770 == 0) {
            switch (r1e_sndTab3E4750) {
            case 0:
                sub_00059720();
                break;
            case 1:
                sub_000599D0();
                break;
            case 2:
                sub_00058D20();
                break;
            }
        } else {
            sub_0004ECD0(0);
            pads = sub_0004ECE0(0);
            sub_0004ECF0(0);
            sub_0004ED00(0);
            pads |= sub_0004ED20(0);
            sub_0004ED40(0);
            if (sub_00079460() == 0 && (pads & 0x800)) {
                r1f_busy3E4770 = 0;
                sub_00048AF0(1);
            }
        }
        sub_000580D0();
    }
    sub_001A0D70();
    sub_00058190();
}
