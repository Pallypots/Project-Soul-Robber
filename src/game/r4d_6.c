/* Area r4d: music track part output 0x0019ABB0 (r4d_6, kept apart so its callers do not inline it). Names inferred. */
#include "r4d.h"

/* 0x0019ABB0: store a part volume and send it scaled by the music or effect master volume.
   regargs: t=EAX k=ESI vol=EDX, i on the stack. */
void r4d_TrackApplyPart(R4dTrack *t, int k, int vol, int i)
{
    int snd = t->snd0C;
    int master;
    t->part[k].vol = vol;
    if (snd < 0x30 || snd >= 0x215)
        master = r4d_g402770;
    else
        master = r4d_g402774;
    sub_001ACAD0(k, 0, master * vol / 16383, t->part[k].a, t->part[k].b, snd, i, t->parts18);
}
