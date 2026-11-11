/* Area r4e: game initialisation and the main frame around 0x0019BA70-0x0019C5C6 (r4e_3). Names inferred. */
#include "r4e.h"

/* 0x0019BA70: one-time game initialisation: subsystems, memory heaps, render targets,
   then the frame flags; ends in 0x000D9BF0. No inputs. */
void r4e_GameInit(void)
{
    r4e_g402FA0 = 0x3C;
    r4e_g402FA8 = 0;
    r4e_g402FC0 = 0;
    sub_001A11F0();
    sub_00053C40();
    sub_00053710(8);
    sub_0004EAE0();
    sub_00036BC0();
    sub_000527B0();
    sub_00012F90();
    sub_001BBD90();
    sub_00012000();
    sub_00052970(1.0f);
    r4e_g402F88 = sub_00053820(8, 0xB020, 0, 0);
    r4e_g402F8C = sub_00053820(8, 0xFFC, 0, 0);
    r4e_g402F90 = sub_00053820(8, 0x1FF0, 0, 0);
    sub_001BB2A0(r4e_g402F8C, 0xFFC);
    sub_001BB2E0(0x1800, 0x800, 0);
    sub_001BB2E0(0x1000, 0x800, 0x1B);
    sub_001BB780(r4e_g402F90, 0x1FF0, 0x2000, 0x2000, 0);
    sub_001BB1D0(0x200, 0xE0, 0);
    sub_001BB1F0(0x200, 0xE0, 0x31);
    sub_001BB210(0x200, 0x1C0, 0);
    sub_001BA650(r4e_g402F88, 0xB020);
    sub_001B9720();
    sub_001B9730();
    sub_001B16E0();
    sub_00037AE0();
    sub_00038FA0();
    sub_000390B0();
    sub_00052840(r4e_g402788);
    sub_00037F10();
    sub_00075EF0();
    sub_00102FA0();
    sub_000186C0();
    sub_000792F0();
    sub_0005EDE0();
    sub_0005EB40((int8_t)r4c_opt413142);
    sub_001A1A70();
    sub_000E6CE0(-1);
    sub_0008CD50();
    sub_0003DC90();
    r4e_g402F94 = 0;
    r4e_g402F98 = 0;
    r4e_g402FB0 = 0;
    r4e_g402FB4 = 0;
    r4e_g402FB8 = 0;
    r4e_g402FBC = 0;
    sub_00053740();
    r4e_g413160 = 0;
    r4e_g41316C = 0;
    r4e_g413170 = 0;
    r4e_g413174 = 0;
    r4e_g413164 = 1;
    r4e_g413168 = 1;
    sub_000D9BF0();
}

/* 0x0019BC60: start-up waits: pump 0x00048590/0x000580D0 until 0x00047950 is ready,
   optionally wait for 0x000E3050, then bring up the game systems. No inputs. */
void r4e_GameStart(void)
{
    if (sub_001A1CD0())
        sub_001A1B90();
    sub_00048590();
    while (!sub_00047950()) {
        sub_00048590();
        sub_000580D0();
    }
    sub_00034B70();
    if (sub_000E3370()) {
        sub_000E4F70();
        while (!sub_000E3050())
            sub_000580D0();
    }
    sub_00022920();
    sub_000E7630();
    sub_00031A10();
    sub_0005FFA0();
    sub_0006C1C0(0, 0);
    sub_0004F4E0();
    sub_0004F660();
}

/* 0x0019C4D0: one main-loop frame: update, timers, then either the pause/menu path
   or the current state handler (r4e_g402F94); advances the 64-bit frame counter.
   No inputs; returns 0. */
int r4e_GameFrame(void)
{
    sub_00079370();
    sub_001A0DB0();
    if (r4e_g402FC0 > 0) {
        r4e_g402FC0--;
        r4e_g42CA3C = 0;
        r4e_g42CA38 = 0;
        r4e_g42CA34 = 0;
    }
    sub_000583C0();
    sub_0019C3B0();
    if (r4e_g402FA0 > 0)
        r4e_g402FA0--;
    sub_0019C2D0();
    if (r4e_g402F9C) {
        if (sub_0019FEE0())
            sub_001A0660(0.1f, 0, 0, 0, 0, 0);
        while (sub_00057E90())
            sub_001AD6A0();
        sub_0019BCF0();
        sub_0019C200();
        return 0;
    }
    if (!r4e_g402F98) {
        if (r4e_g402F94) {
            r4e_g402F94();
        } else {
            sub_0004EB50();
            sub_0004ECE0(1);
            sub_0004EC40();
        }
    } else {
        sub_0004EC60();
        r4e_g402F98 = 0;
    }
    r4e_frame42C918++;
    r4e_g42CB00 = (int32_t)r4e_frame42C918;
    sub_001BA640((int32_t)r4e_frame42C918);
    return 0;
}
