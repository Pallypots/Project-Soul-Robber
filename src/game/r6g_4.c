/* Area r6g: return-to-title flow and 3D object model setup (r6g_4). Names inferred. */
#include "r6g.h"

/* 0x0006D780: leave the current game and go back to the title: release the pause
   screen, reset the game state, shut down the two optional subsystems that are
   running (each waited out later), switch the video mode for the language, make
   sure the title movie of the mode is loaded, wait for loading, clear the menu
   state and run the title page until it ends; then start the title object. */
void r6g_ReturnToTitle(void)
{
    int running = 0;
    int mode, movie;

    sub_0006C070();
    sub_00022920();
    if (sub_00060BD0() != -1) {
        sub_0005FE00();
        running = 1;
    }
    if (sub_000774E0() != -1) {
        sub_00077410();
        running |= 2;
    }
    mode = sub_00052A00(a60_lang413145);
    a60_cmd3E6610 = 5;
    a60_arg3E661C = 1;
    sub_0019BF80(mode, a60_lang413145);
    movie = sub_000529F0() + 0xA8;
    if (!sub_0004F6D0(movie))
        sub_0004FA70(movie, sub_00053820(5, sub_0004F680(movie), 0, 0));
    while (sub_0004F4D0())
        sub_000580D0();
    sub_0002BAB0();
    sub_0006EA20(0);
    a60_v3E6620 = 0;
    a60_flag428F78 = 0;
    a60_v42C5EC = -1;
    a60_v428F74 = -1;
    a60_v3E6614 = -1;
    a60_v3E68A8 = -1;
    if (running & 1) {
        while (sub_0005F860())
            sub_000580D0();
    }
    if (running & 2) {
        while (sub_00077500())
            sub_000580D0();
        sub_00077A30();
        sub_0006EA20(1);
    }
    while (sub_0006D350())
        sub_000580D0();
    r6g_g42AC78 = 5;
    sub_00072EE0(a4c_obj428F40, 0, 8.0f, 0);
    r6g_g428F20 = 1;
    r6g_b428F80[0] = 4;
    r6g_b428F80[1] = 1;
    r6g_b428F80[2] = 0;
    r6g_b428F80[3] = 0;
}

/* 0x00079A00: create the model list of a 3D object (18 entries), chain it with v,
   apply the object's light, set the slot sizes and install the per-slot draw
   hooks. Returns the result of the chain call. */
int r6g_ObjModelsCreate(R6gObj7 *o, int v)
{
    int r;
    o->mdl = sub_000846D0(0x12);
    r = sub_00084730(o->mdl, v);
    sub_00079980(o->mdl, o->light);
    sub_000847D0(o->mdl, 0, 4);
    sub_000847D0(o->mdl, 2, 4);
    sub_000847D0(o->mdl, 4, 4);
    sub_000847D0(o->mdl, 8, 4);
    sub_000847D0(o->mdl, 6, 4);
    sub_000847D0(o->mdl, 0xA, 4);
    sub_000847D0(o->mdl, 0xB, 4);
    sub_000847D0(o->mdl, 0xD, 4);
    sub_000847D0(o->mdl, 0xF, 4);
    sub_000847D0(o->mdl, 0x11, 3);
    sub_00084810(o->mdl, 5, sub_001B7E90);
    sub_00084830(o->mdl, 5, sub_000796D0);
    sub_00084810(o->mdl, 6, sub_00079810);
    sub_00084830(o->mdl, 7, sub_00079830);
    sub_00084810(o->mdl, 0xA, sub_00079780);
    sub_00084830(o->mdl, 0xC, sub_00079790);
    sub_00084810(o->mdl, 0xF, sub_000799F0);
    return r;
}
