/* Area r4e: stage entry and loader flow around 0x0019D460-0x0019E5EA (r4e_4). Names inferred. */
#include "r4e.h"

/* 0x0019D460: enter the current stage: wait for pending jobs, pick the stage's two
   setup values (overridden for chapter 31 part 0), run the load jobs, then start
   play with or without the intro. Stack arg (t). */
void r4e_StageEnter(R4eTask *t)
{
    R4eStageCfg *cfg;
    int a, b;
    int chapter, part;
    r4e_g402FE0 = 0;
    sub_000580D0();
    sub_000580D0();
    while (sub_00057E90())
        sub_000580D0();
    r4e_g402FDC = 0;
    sub_00032140(1, 2, 0);
    cfg = &r4e_stageCfg336DD8[r4e_g41316C][r4e_g413170];
    b = cfg->b04;
    a = cfg->a00;
    sub_000DDF20(&chapter, &part);
    if (chapter == 0x1F && part == 0) {
        a = 0xC;
        b = 0x20;
    }
    sub_00031B60(b);
    r4e_g402FDC = 1;
    sub_00058540(sub_0019D360, t);
    while (sub_00057E90())
        sub_000580D0();
    t->f04 = 0;
    sub_00058540(sub_0019D2A0, t);
    while (sub_00057E90())
        sub_000580D0();
    sub_00086EF0();
    sub_00085DE0();
    while (r4e_g402FDC)
        sub_000580D0();
    sub_000AA4C0();
    sub_00031AC0(a);
    sub_00032140(0, 0, 0);
    r4e_g402FE0 = 1;
    if (a19_g337498) {
        sub_00032140(0, 1, 0);
        sub_00032140(1, 1, 0x12C);
        sub_000DE330(0);
    } else {
        /* The original pushes no argument here although 0x00047BF0 reads one
           (call 0x47BF0 with nothing pushed); called through a no-argument type. */
        ((void (*)(void))sub_00047BF0)();
        sub_00036FD0(128.0f);
        sub_00032140(0, 8, 0);
        sub_00032140(1, 1, 0x1E);
    }
    PlayerObj_ClearFlags22((PlayerObj *)&g_stats);
    sub_001A0D70();
    sub_00058190();
}

/* 0x0019DF20: create the loader semaphore and start the loader thread (entry
   0x0019D8E0, priority 5). No inputs; 0x001AD3D0 is called with an extra 0 argument. */
void r4e_LoaderInit(void)
{
    R4dSemDesc sd;
    R4eThreadDesc td;
    r4e_g402FE4 = 1;
    sd.max = 1;
    r4e_g402FE8 = 0;
    sd.init = 0;
    sd.f14 = 0;
    r4e_g402FF4 = r4d_SemCreate(&sd);
    r4e_g402FFC = 0;
    r4e_g402FF8 = 0;
    td.entry04 = (void *)sub_0019D8E0;
    td.f08 = 0;
    td.f0C = 0;
    td.prio14 = 5;
    td.arg10 = r4e_g40B860;
    r4e_g402FF0 = sub_001AD720(&td, 0);
    r4d_ThreadStart(r4e_g402FF0);
}

/* 0x0019E530: title/menu job: clear the task's busy flag, run the 0x0019DFD0 job,
   then set up the next mode from the 0x00413160 flags (bit 0, bit 1, or neither).
   Stack arg (t). */
void r4e_TitleTask(R4eTask *t)
{
    int sel;
    t->f04 = 0;
    if (r4e_g413160 & 1)
        sel = 0;
    else
        sel = (r4e_g413160 & 2) ? 1 : 2;
    sub_00058540(sub_0019DFD0, 0);
    while (sub_00057E90())
        sub_000580D0();
    switch (sel) {
    case 0:
        sub_001A0CF0(4, 0);
        sub_001A0D30(3, 0);
        sub_000408B0(r4e_g413164);
        sub_000408C0(0);
        sub_001A0D30(8, 0);
        break;
    case 1:
        sub_0019D870(1);
        break;
    case 2:
        sub_001A0CF0(4, 0);
        sub_001A0D30(3, 0);
        break;
    }
    sub_00058190();
}
