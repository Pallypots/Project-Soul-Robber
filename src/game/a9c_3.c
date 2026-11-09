/* Area a9c, 0x0019A000-0x0019FFFF. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9c.h"

/* 0x0019A180: whether any 0x00401D70 slot in the range linked from entry i of 0x003316A0 is active. */
int a9c_LinkAnyActive(int i)
{
    a9c_Link24 *l = &a9c_g3316A0[i];
    a9c_Slot38 *s = &a9c_g401D70[l->b10];
    int n, r = 0;
    for (n = l->b11; n > 0; n--, s++)
        if (s->f0)
            r = 1;
    return r;
}

/* 0x0019A540: +0x14 of active slot i (0..44) of 0x00401D70 whose state is at least 1, or -1. */
int a9c_Slot401D70Get14(int i)
{
    a9c_Slot38 *s;
    if (i < 0 || i >= 45)
        return -1;
    s = &a9c_g401D70[i];
    if (s->f0 && sub_00199E20(i) >= 1)
        return s->f14;
    return -1;
}

/* 0x0019E810: when the controller block is in state 1, pick next state 0x18/0x16/0x19 for mode 0/1/2. */
void a9c_CtrlSelectMode(int mode)
{
    int32_t *p = a19_g403128;
    if (!p) for (;;) ;
    if (p[1] != 1)
        return;
    switch (mode) {
    case 0: p[1] = 0x18; break;
    case 1: p[1] = 0x16; break;
    case 2: p[1] = 0x19; break;
    }
}

/* 0x0019E870: store the flag at 0x003374A0; in state 1 the controller block moves to 3 (set) or 5 (clear). */
void a9c_CtrlSetFlag(int v)
{
    int32_t *p = a19_g403128;
    if (!p) for (;;) ;
    if (p[1] == 1) {
        a19_g3374A0 = v;
        p[1] = v ? 3 : 5;
    } else {
        a19_g3374A0 = v;
    }
}

/* 0x0019FFE0: per-frame tail: updates, frame-rate bookkeeping and present. */
void a9c_FrameEnd(void)
{
    sub_0004EB50();
    sub_0004EC40();
    if (sub_001A7E30()) {
        Video_GetRateMode();
        a9c_g403968++;
    }
    sub_001BA640(a50_frameCounter0);
    sub_001B96D0();
}

/* 0x0019A1D0: whether any 0x00401D70 slot linked from entry i (0..10) of 0x003316A0 is active or has +0x10 > 0. */
int a9c_LinkAnyBusy(int i)
{
    a9c_Link24 *l;
    a9c_Slot38 *s;
    int n, r;
    if (i == -1)
        return 0;
    if (i <= -1 || i >= 11) for (;;) ;
    l = &a9c_g3316A0[i];
    s = &a9c_g401D70[l->b10];
    r = 0;
    for (n = l->b11; n > 0; n--, s++)
        if (s->f0 || s->f10 > 0)
            r = 1;
    return r;
}

/* 0x0019A640: apply b to every 0x00401D70 slot linked from entry i (0..10) of 0x003316A0. */
void a9c_LinkApplyAll(int i, int b)
{
    a9c_Link24 *l;
    int k;
    if (i == -1)
        return;
    if (i <= -1 || i >= 11) for (;;) ;
    l = &a9c_g3316A0[i];
    for (k = 0; k < l->b11; k++)
        sub_0019A230(l->b10 + k, b);
}

/* 0x0019A6A0: run 0x0019A4B0 on every 0x00401D70 slot linked from entry i (0..10) of 0x003316A0. */
void a9c_LinkRunAll(int i)
{
    a9c_Link24 *l;
    int k;
    if (i == -1)
        return;
    if (i <= -1 || i >= 11) for (;;) ;
    l = &a9c_g3316A0[i];
    for (k = 0; k < l->b11; k++)
        sub_0019A4B0(l->b10 + k);
}

/* 0x0019A950: claim a free record of 0x004019D8 for entry e (0..0x263) of 0x003317C0; its index or -1. */
int a9c_Rec4019D8Claim(int e)
{
    int i;
    a9c_Rec36 *src;
    a9c_Rec60 *r = a9c_g4019D8;
    if (e <= -1 || e >= 0x264) for (;;) ;
    src = &a9c_g3317C0[e];
    for (i = 0; i < 3; i++, r++) {
        if (!r->f0) {
            r->fC = e;
            r->f8 = 2;
            r->f18 = src->f0 >> 28;
            r->f0 = 1;
            r->f5C = 0;
            return i;
        }
    }
    return -1;
}
