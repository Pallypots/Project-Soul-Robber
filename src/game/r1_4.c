/* Area r1, group 4: queue, timer and HUD helpers 0x000268D0..0x00033330. Names inferred. */
#include "r1.h"

/* 0x000268D0: drop the first of eight queued values and clear the last.
   regargs: q=EAX */
void r1_QueuePop8(int32_t *q)
{
    int i;
    for (i = 0; i < 7; i++) q[i] = q[i + 1];
    q[7] = 0;
}

/* 0x0002B520: two-state countdown; when it expires the queue advances.
   regargs: t=ESI */
void r1_TimerStep(R1Timer *t)
{
    int i;
    switch (t->state) {
    case 0:
        t->t = 120.0f;
        t->state = 1;
        break;
    case 1:
        sub_000720A0(&t->t, 0);
        if (t->t <= 0.0f) {
            for (i = 0; i < 7; i++) t->q[i] = t->q[i + 1];
            t->q[7] = 0;
            t->state = 0;
        }
        break;
    }
}

/* 0x0002C8C0: switch the HUD to another entry when it changed.
   regargs: id=ESI */
void r1_HudSelect(int32_t id)
{
    if (r1_curHudId == id) return;
    sub_00076060(r1_hud->h970);
    sub_0003FCB0(r1_hud->slot968, sub_0003FA70(r1_hud->tbl988, id), 0, 0, -1.0f);
    r1_curHudId = id;
}

/* 0x00033330: initialise a sound bank and its two channels.
   regargs: b=EAX */
void r1_BankInit(R1Bank *b)
{
    int i;
    sub_00036A90(b, 0xB40, 0x79);
    sub_00036A90(b->sub55140, 0x6C, 0x79);
    sub_0003D860(b->sub5844C);
    for (i = 0; i < 2; i++) {
        b->chans[i].busy = 0;
        sub_001B25B0(&b->chans[i]);
    }
}
