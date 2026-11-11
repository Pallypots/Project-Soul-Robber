/* Area r4d: stage flow and job helpers around 0x0019E750-0x001A1716 (r4d_11). Names inferred. */
#include "r4d.h"

/* 0x0019E750: end the current stage: optionally record the result, run the wrap-up loop until
   the script says it is done (or wait 1000 ms when no script), then fade out. Stack arg (a). */
void r4d_StageEnd(int a)
{
    int out;
    sub_0019B9E0();
    if (a)
        sub_000DFD40(&out, &a);
    if (sub_000E3370()) {
        while (!sub_000E6840(sub_000E0770())) {
            sub_0004F0B0();
            sub_0005E9B0();
            sub_0004F4C0();
            sub_00049470();
            sub_000586E0(0);
        }
    } else {
        sub_00048EE0(1000);
    }
    sub_000481B0(100);
    sub_000483A0(100);
    sub_0005CCD0(((R4dCtx1F0 *)r4c_ctx42C8E4)->f1F0, 1);
    r4c_g403130 = 0;
    sub_000DF990();
    sub_0019B9F0();
}

/* 0x0019FD60: tear down the stage: stop the movie, reset jobs and state, free the stage buffers
   and clear the three render groups of g. Stack arg (g). */
void r4d_StageUnload(void *g)
{
    sub_000226B0();
    sub_0005EB50();
    sub_0005EE40();
    sub_001A7F90(r4d_g403960);
    while (sub_001A7DC0())
        sub_000580D0();
    sub_001BB6E0();
    sub_0019BE50(0);
    sub_00058540(0, 0);
    r4c_g404318 = 0;
    r4c_g403988 = 0;
    r4c_g40398C = 0;
    if (sub_0004F6D0(0xE6))
        sub_0004F5D0(0xE6);
    if (r4d_g403964) {
        sub_00053880(r4d_g403964);
        r4d_g403964 = 0;
    }
    if (r4c_g40431C) {
        sub_00053880(r4c_g40431C);
        r4c_g40431C = 0;
    }
    sub_001A1090(g, 0x100);
    sub_001A1090(g, 0x101);
    sub_001A1090(g, 0x102);
    sub_001A10C0(g, 0x100);
    sub_001A10C0(g, 0x101);
    sub_001A10C0(g, 0x102);
    r4d_g40396C = 0;
}

/* 0x001A0020: fire the screen shakes whose time lies in (lo, hi]. Stack args (hi lo). */
void r4d_StageShocks(int hi, int lo)
{
    R4cShockTab *t;
    R4cShockEnt *e;
    int k;
    if (!r4d_g403978 || !(t = r4d_shocks403988) || !r4c_g404318)
        return;
    for (k = 0, e = t->e; k < t->n; k++, e++) {
        if (e->id <= hi && e->id > lo) {
            sub_0003FC10(r4d_shake4042F8);
            sub_0003FCB0(r4d_shake4042F8, sub_0003FA70(r4c_g404318, e->val), 0, 20.0f, -1.0f);
        }
    }
    sub_0003FCE0(r4d_shake4042F8);
}

/* 0x001A11F0: build the job free list from the 16 nodes, take the first node as the running job
   and kick the scheduler when no job id is set. No inputs; assert-style hang when the list is empty. */
void r4d_JobsInit(void)
{
    R4dJobNode *n, *q;
    void *p;
    sub_0003D860(r4d_jobQueue4044A8);
    sub_0003D860(r4d_jobQueue404410);
    for (n = r4d_jobNodes4044B8; n < r4d_jobNodes4044B8 + 16; n++) {
        sub_0003D880(r4d_jobQueue404410, n);
        n->self0C = n;
    }
    r4d_g4044A0 = -1;
    r4d_g4044A4 = -1;
    p = sub_0003DC70(r4d_jobQueue404410);
    if (!p)
        for (;;)
            ;
    q = ((R4dJobNode *)p)->self0C;
    q->f10 = 0;
    q->f14 = 0;
    q->f18 = 0;
    sub_0003D880(r4d_jobQueue4044A8, p);
    if (sub_0019B9D0() == -1)
        sub_000774C0();
}

/* 0x001A1680: load the common stage file 0xBC, then create the three shared objects. No inputs. */
void r4d_StageLoadCommon(void)
{
    int k;
    void *h;
    sub_0004FA70(0xBC, sub_00053AB0(sub_0004F680(0xBC), 0, 0xA8));
    while (sub_0004F4D0())
        sub_000580D0();
    for (k = 0; k < 3; k++) {
        h = sub_00037570(r4d_names337748[k], 0x40);
        r4d_objs4046A4[k] = h;
        if (h)
            r4d_ids404688[k] = sub_00084C00(h, 0);
        else
            r4d_ids404688[k] = -1;
    }
    sub_000588D0(r4d_g40467C);
    sub_00058170();
}
