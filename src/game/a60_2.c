/* Area a60, group 2: 0x00065000..0x0006EFFF. Names inferred. */
#include "a60.h"

/* 0x000659A0: release every loaded handle of this screen. */
void a60_Release659A0(void)
{
    int i;
    for (i = 0; i < 5; i++)
        if (a60_h3E64FC[i] != -1) { sub_001B9FC0(a60_h3E64FC[i]); a60_h3E64FC[i] = -1; }
    if (a60_flag428F78 == 0) {
        for (i = 0; i < 4; i++)
            if (a60_h3E6510[i] != -1) { sub_001B9FC0(a60_h3E6510[i]); a60_h3E6510[i] = -1; }
        for (i = 0; i < 2; i++)
            if (a60_h3E6520[i] != -1) { sub_001B9FC0(a60_h3E6520[i]); a60_h3E6520[i] = -1; }
    }
    if (a60_h3E653C != -1)
        sub_00048250(a60_h3E653C);
}

/* 0x00065AA0: create the resource in the work area at +0x40080. */
void a60_InitRes65AA0(void)
{
    sub_001B9720();
    a60_res3E6540 = sub_00084C00(a60_work42C5E8 + 0x40080, 0);
}

/* 0x0006A320: clear three handles. */
void a60_Clear6A320(void)
{
    a60_h3E660C = a60_h3E6608 = a60_h42C6F0 = -1;
}

/* 0x0006A340: release three handles. */
void a60_Release6A340(void)
{
    if (a60_h42C6F0 != -1) { sub_001B9FC0(a60_h42C6F0); a60_h42C6F0 = -1; }
    if (a60_h3E6608 != -1) { sub_001B9FC0(a60_h3E6608); a60_h3E6608 = -1; }
    if (a60_h3E660C != -1) { sub_001B9FC0(a60_h3E660C); a60_h3E660C = -1; }
}

/* 0x0006B5D0: setter. */
void a60_Set3E65FC(int v) { a60_val3E65FC = v; }

/* 0x0006BF80: per-frame update of three parts (first only in phase 0). */
void a60_Update6BF80(void)
{
    if (a60_phase428F81 == 0)
        sub_0006A970();
    sub_0006AB70();
    sub_0006AD80();
}

/* 0x0006C030: reset the menu state. */
void a60_Reset6C030(void)
{
    sub_0006EA20(0);
    a60_v3E6620 = 0;
    a60_flag428F78 = 0;
    a60_v42C5EC = a60_v428F74 = a60_v3E6614 = a60_v3E68A8 = -1;
}

/* 0x0006C1C0: post a command (0..5) with an argument. */
void a60_PostCommand(int cmd, int arg)
{
    switch (cmd) {
    case 0: a60_cmd3E6610 = 0; a60_arg3E661C = 0; break;
    case 1: a60_cmd3E6610 = 1; a60_arg3E661C = arg; break;
    case 2: a60_cmd3E6610 = 2; a60_arg3E661C = 0; break;
    case 3: a60_cmd3E6610 = 3; a60_arg3E661C = arg; break;
    case 4: a60_cmd3E6610 = 4; a60_arg3E661C = arg; break;
    case 5: a60_cmd3E6610 = 5; a60_arg3E661C = arg; break;
    }
}

/* 0x0006C260: current command. */
int a60_GetCommand(void) { return a60_cmd3E6610; }

/* 0x0006EA20: setter. */
void a60_Set3E6938(int v) { a60_val3E6938 = v; }

/* 0x00068E20: queue task 0x00065F00 and pump until the queue is empty. */
void a60_RunTask68E20(void)
{
    sub_001B9720();
    sub_00058540(sub_00065F00, 0);
    while (sub_00057E90())
        sub_000580D0();
}

/* 0x0006DA80: per-frame movie/menu check; returns whether the top state is not 5. */
int a60_Update6DA80(void)
{
    if (a60_v3E6620 == 10000) {
        if (sub_00079460() == 0) {
            if (a60_b428F45 & 1)
                a60_b428F45 &= ~1;
            sub_0006D910();
        } else if (!(a60_b428F45 & 1)) {
            a60_b428F45 |= 1;
        }
        sub_00053CA0(1);
        return a60_b428F80 != 5;
    }
    sub_00079340();
    return a60_b428F80 != 5;
}

/* 0x0006DBB0: release 32 handles, then reload the language resource if needed. */
void a60_Release6DBB0(void)
{
    int i;
    for (i = 0; i < 32; i++)
        if (a60_h3E68B8[i] != -1) { sub_001B9FC0(a60_h3E68B8[i]); a60_h3E68B8[i] = -1; }
    if (sub_000E3370())
        sub_000E3A20(sub_000E0770(a60_lang413145));
}
