/* Area r1f, group 15: stage background loader 0x00031B60. Names inferred. */
#include "r1f.h"

/* 0x00031B60: select stage background `id` (0..0x38, else 0), build its
   file name and, for a real stage, load it, wait for the load, replace the
   texture and set up the background sprite. */
void r1f_StageBgLoad(unsigned id)
{
    if (id >= 0x39)
        id = 0;
    r1f_stage381830 = id;
    a6b_Printf2(r1f_name3817E8, r1f_fmt283614, sub_00052A10(id));
    if (r1f_stage381830 == 0)
        return;
    sub_0004F700(0xB0);
    sub_00053E20(r1f_name3817E8, r1d_heap381A5C + 0x4080);
    while (sub_00053CA0(1) != 0)
        sub_000580D0();
    sub_0004F720();
    if (r1d_tex381AB0 >= 0)
        sub_001B9FC0(r1d_tex381AB0);
    r1d_tex381AB0 = sub_00084C00(r1d_heap381A5C + 0x4080, 0);
    sub_00014DA0(r1d_heap381A5C + 0x14100);
    sub_00014D00(r1f_spr381888, r1d_heap381A5C + 0x14100, r1d_tex381AB0);
    sub_00014E30(r1f_spr381888, 0, 0, 0, 0);
}
