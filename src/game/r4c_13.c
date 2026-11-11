/* Area r4c: stage flow, job loops and group set-up 0x0019E6E0-0x001A1672 (r4c_13). Names inferred. */
#include "r4c.h"

/* 0x0019E6E0: resume the stage: pause handling, sound restart and flag 0x00403130. Stack args (force). */
void r4c_StageResume(int force)
{
    sub_0019B9E0();
    sub_0005C510();
    if (sub_000E3370())
        sub_000E51A0(sub_000E0770());
    else if (force || sub_000D9A70(0xF0))
        sub_00048A60();
    sub_00048110(10);
    sub_00048370();
    r4c_g403130 = 1;
    sub_000DF970();
    sub_0019B9F0();
}

/* 0x0019FE60: shut the stage down: free its heap block, stop the worker and release group g's entries 0x100/0x102. Stack args. */
void r4c_StageShutdown(void *g)
{
    r4c_g404318 = 0;
    r4c_g403988 = 0;
    r4c_g40398C = 0;
    if (r4c_g40431C) {
        sub_00053880(r4c_g40431C);
        r4c_g40431C = 0;
    }
    sub_0019BE50(0);
    sub_00058540(0, 0);
    sub_001A1090(g, 0x100);
    sub_001A1090(g, 0x102);
    sub_001A10C0(g, 0x100);
    sub_001A10C0(g, 0x102);
    r4c_g40396C = 0;
}

/* 0x001A01A0: play every controller-shock entry of the current table whose id matches. Stack args. */
void r4c_ShockById(int id)
{
    R4cShockTab *t = r4c_g40398C;
    int i;
    if (t && r4c_g403984)
        for (i = 0; i < t->n; i++)
            if (t->e[i].id == id)
                sub_0005EB10(0, t->e[i].val);
}

/* 0x001A0B30: reset both session slots (flags cleared, scale 1.0) after 0x001A1130. Stack args. */
void r4c_SessionSlotsReset(void *a)
{
    int i;
    sub_001A1130(a);
    for (i = 0; i < 2; i++) {
        g_sessionSlots[i].b[0] = 0;
        g_sessionSlots[i].b[1] = 0;
        g_sessionSlots[i].b[2] = 0;
        g_sessionSlots[i].b[3] = 0;
        g_sessionSlots[i].scale = 1.0f;
    }
}

/* 0x001A0B80: job: wait for the movie to finish, allowing a skip after 30 frames, then finish. Stack args. */
void r4c_MovieWaitJob(R4cJob *job)
{
    int n = 0;
    job->skip08 = 0;
    while (sub_00079460()) {
        if (n < 30)
            n++;
        else
            job->skip08 = 1;
        sub_000580D0();
    }
    job->skip08 = 0;
    sub_001A0D70();
    sub_00058190();
}

/* 0x001A0BD0: job: build each frame's command buffer (with the skip prompt when requested), forever. Stack args.
   Calls 0x0019C800 with EAX=buffer. */
void r4c_RenderJob(R4cJob *job)
{
    uint32_t *p;
    for (;;) {
        p = sub_0019C800(r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd);
        if (job->skip08)
            p = sub_00079480(p);
        sub_001B96D0();
        sub_000AD090(0, 0);
        sub_000AD090(0x80);
        r4c_bufs42CAC8[r4c_bufIndex42CAC0].cmd = p;
        sub_000580D0();
    }
}

/* 0x001A1610: register the three 0x2800-byte entries of group g and release the old ones. Stack args. */
void r4c_GroupSetup2800(R4cJob *g)
{
    sub_001A8A70(0);
    g->skip08 = 0;
    sub_001A1030(g, 0, 1, sub_001A13E0, 8, 0x2800);
    sub_001A1030(g, 1, 2, sub_001A1280, 8, 0x2800);
    sub_001A1030(g, -1, 4, sub_001A1320, 8, 0x2800);
    sub_001A10F0(g);
}
