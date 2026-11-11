/* Area r6d: area-select screen helpers around 0x0006BFA0-0x0006C1A4 (r6d_7). Names inferred. */
#include "r6d.h"

/* 0x0006BFA0: pick the area picture for the current chapter/stage and load the four images.
   calls 0x0006B5E0 with ECX=chapter EAX=stage ESI=&r6d_pos3E65E8 */
void r6d_AreaLoadImages(void)
{
    sub_000DFD40(&r6d_chapter4297F0, &r6d_stage4297F4);
    r6d_area4297F8 = sub_0006B5E0(r6d_chapter4297F0, r6d_stage4297F4, r6d_pos3E65E8);
    sub_00053E20(r6d_areaImages2DE3D8[r6d_area4297F8], a60_work42C5E8);
    sub_00053E20(r6d_img2DE458, a60_work42C5E8 + 0x40080);
    sub_00053E20(r6d_img2DE45C, a60_work42C5E8 + 0x44100);
    sub_00053E20(r6d_img2DE460, a60_work42C5E8 + 0x44980);
}

/* 0x0006C070: leave the pause screens: stop their sounds, release every page and the work block. */
void r6d_PauseRelease(void)
{
    a60_cmd3E6610 = 0;
    a60_arg3E661C = 0;
    a60_v3E6620 = 0;
    sub_00026850();
    sub_00038070(r6d_g3E6618);
    if (a60_v428F74 != -1) {
        sub_001B9FC0(a60_v428F74);
        a60_v428F74 = -1;
    }
    if (a60_v42C5EC != -1) {
        sub_001B9FC0(a60_v42C5EC);
        a60_v42C5EC = -1;
    }
    if (a60_v3E68A8 != -1) {
        sub_001B9FC0(a60_v3E68A8);
        a60_v3E68A8 = -1;
    }
    if (a60_v3E6614 != -1) {
        sub_001B9FC0(a60_v3E6614);
        a60_v3E6614 = -1;
    }
    a60_Release659A0();
    a60_Release6A340();
    a60_ScreenRelease62200();
    a60_Release72FD0();
    a60_Release6DBB0();
    sub_0004F5D0(a5b_GetVideoMode() + 0xA0);
    sub_0004F5D0(0xA7);
    if (a60_flag428F78 == 0)
        sub_0004F5D0(0xAF);
    sub_00053880(a60_work42C5E8);
    a60_work42C5E8 = 0;
}

/* 0x0006C160: pass a menu value to the handler of the current pause page.
   regargs: v=EAX */
int r6d_PausePageValue(int v)
{
    switch (a60_b428F80) {
    case 0:
        return sub_00066050(v);
    case 1:
        return sub_0006A3A0(v);
    case 2:
        return sub_000622A0(v);
    case 3:
        return a60_Dispatch74700(v);
    case 4:
        return sub_0006EA30(v);
    }
    return v;
}
