/* Area r4g: boot loading thread at 0x001A13E0 (r4g_6). Names inferred. */
#include "r4g.h"

/* 0x001A13E0: boot loading sequence run as a thread: reset the two session
   slots, wait for the pending jobs, load the startup archives (0x1F4
   requests), wait until c->go08 is set, then step c->state04 through 1 and
   2 while the title data loads, install the 0x001A13D0 callback and finish
   the remaining loads. Each wait yields with 0x000580D0. Stack arg (c). */
void r4g_BootLoadThread(R4gLoadCtx *c)
{
    int a, b;
    int i;

    for (i = 0; i < 2; i++) {
        g_sessionSlots[i].b[0] = 0;
        g_sessionSlots[i].b[1] = 0;
        g_sessionSlots[i].b[2] = 0;
        g_sessionSlots[i].b[3] = 0;
        g_sessionSlots[i].scale = 1.0f;
    }
    c->state04 = 0;
    while (sub_00057E90())
        sub_000580D0();
    sub_000580D0();
    sub_000580D0();
    sub_000580D0();
    sub_001A1AC0();
    sub_0019B9E0();
    sub_000DFD40(&a, &b);
    sub_000487F0(0x1F4, 0, 0);
    while (sub_00048820(0x1F4, 0, 0) != 2)
        sub_000580D0();
    sub_00048860(0x1F4, 0, 0);
    while (sub_00048890(0x1F4, 0, 0))
        sub_000580D0();
    sub_0019B9F0();
    sub_0019BEB0(0x8000);
    sub_0006C030();
    while (sub_0006D350())
        sub_000580D0();
    while (!c->go08)
        sub_000580D0();
    c->state04 = 1;
    sub_000325A0(0);
    sub_00036F40(0, 0, 0, 0);
    while (sub_0006DA80())
        sub_000580D0();
    c->state04 = 2;
    sub_000325A0(1);
    sub_0006C070();
    sub_00032140(1, 2, 0);
    sub_00058670();
    sub_00058540(sub_001A13D0, 0);
    sub_00058670();
    sub_0019B9E0();
    sub_000488C0(0x1F4, 0, 0);
    while (sub_000AD090(0x1F4, 0, 0))
        sub_000580D0();
    sub_0019B9F0();
    sub_0019B9E0();
    sub_000DFD40(&a, &b);
    sub_0019B9F0();
    sub_000325A0(0);
    sub_00079340();
    sub_001A0D70();
    sub_00058190();
}

/* 0x0019BCF0: game main: reset the two session slots, step the frame
   counter through three startup frames, reset the job and sound systems,
   start the game task (0x0019BC60) and run the frame loop while jobs are
   pending; then free the textures and memory and leave. No inputs. */
void r4g_GameMain(void)
{
    int i;

    for (i = 0; i < 2; i++) {
        g_sessionSlots[i].b[0] = 0;
        g_sessionSlots[i].b[1] = 0;
        g_sessionSlots[i].b[2] = 0;
        g_sessionSlots[i].b[3] = 0;
        g_sessionSlots[i].scale = 1.0f;
    }
    sub_001A5500();
    sub_0004EC40();
    a50_frameCounter0++;
    sub_0004EB50();
    sub_0004EC40();
    a50_frameCounter0++;
    sub_0004EB50();
    sub_0004EC40();
    a50_frameCounter0++;
    sub_000AD090(0, 0);
    sub_000AD090(0, 0);
    sub_000AD090(0, 0);
    sub_0004F4E0();
    sub_00057E90();
    sub_00058540(0, 0);
    sub_00058780();
    sub_0019D680();
    sub_000583C0();
    sub_001A5500();
    sub_0005EB50();
    sub_0005E9B0();
    sub_0005E930();
    sub_00058540(sub_0019BC60, 0);
    while (sub_00057E90()) {
        sub_0004F0B0();
        sub_0005E9B0();
        sub_0004F4C0();
        sub_00049470();
        sub_001A53F0();
    }
    sub_001BA6B0();
    ((void (*)(void))sub_00102FA0)();   /* empty stub called without an argument */
    sub_00053C40();
    sub_00058780();
}
