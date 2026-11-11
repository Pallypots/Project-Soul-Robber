/* Area r4g: music track start and resume at 0x0019B6A0-0x0019B99C (r4g_4). Names inferred. */
#include "r4g.h"

/* 0x0019B6A0: start sequence snd (0..611) on a free track: load its bank
   (kind 0, 1 or 2 by range), open the stream, set every part's volume and
   play. Returns the track index or -1 when all three are busy; hangs on a
   bad sequence number. Stack arg (snd); calls 0x0019ABB0 with EAX=track
   ESI=part EDX=volume. */
int r4g_TrackStart(int snd)
{
    R4gSeq *s;
    R4gTrack *t;
    int i, k;

    if (snd <= -1 || snd >= 0x264)
        for (;;)
            ;
    s = &r4d_snd3317C0[snd];
    t = r4d_tracks4019D8;
    for (i = 0; t->used00; t++)
        if (++i >= 3)
            return -1;
    t->busy04 = 1;
    t->state08 = 3;
    t->snd0C = snd;
    t->chan10 = s->u.h.chan;
    t->parts18 = s->u.bits >> 28;
    t->used00 = 1;
    if (snd < 0x30)
        sub_001AB4A0(s->u.h.bank, 0);
    else if (snd < 0x215)
        sub_001AB4A0(s->u.h.bank, 1);
    else
        sub_001AB4A0(s->u.h.bank, 2);
    sub_001ABD10(0, i);
    sub_00102FA0(s->u.h.chan);
    t->state08 = 5;
    for (k = 0; k < t->parts18; k++) {
        t->part[k].id = s->parts[k].id;
        t->part[k].a = s->parts[k].a;
        t->part[k].b = s->parts[k].b;
        if (i >= 0 && i < 3 && r4d_tracks4019D8[i].used00)
            sub_0019ABB0(&r4d_tracks4019D8[i], k,
                         r4d_snd3317C0[r4d_tracks4019D8[i].snd0C].parts[k].vol, i);
    }
    sub_001ABF20(0, i);
    return i;
}

/* 0x0019B800: resume track i: when stopped (state 2 or 5) reload its bank
   (or the pending bank 0x00402748 once) and restart the stream, when
   paused (state 7) undo one pause level and unpause; then reapply every
   part's volume. Stack arg (i); calls 0x0019ABB0 with EAX=track ESI=part
   EDX=volume. */
void r4g_TrackResume(int i)
{
    R4gTrack *t;
    R4gSeq *s;
    int k;

    if (i < 0 || i >= 3)
        return;
    t = &r4d_tracks4019D8[i];
    s = &r4d_snd3317C0[t->snd0C];
    if (!t->used00)
        return;
    switch (sub_0019A900(i)) {
    case 2:
    case 5:
        if (t->busy04 && !r4d_g401B28)
            return;
        if (t->snd0C < 0x30) {
            if (r4d_g401B28 == 1) {
                sub_001AB4A0(r4d_g402748, 0);
                r4d_g401B28 = 0;
            } else {
                sub_001AB4A0(s->u.h.bank, 0);
            }
        } else if (t->snd0C < 0x215) {
            sub_001AB4A0(s->u.h.bank, 1);
        } else {
            sub_001AB4A0(s->u.h.bank, 2);
        }
        t->state08 = 3;
        break;
    case 7:
        break;
    default:
        return;
    }
    if (t->n5C && --t->n5C)
        return;
    t->busy04 = 1;
    t->chan10 = s->u.h.chan;
    if (t->state08 == 7)
        sub_001ABFE0(i, 0);
    else
        sub_001ABD10(0, i);
    sub_00102FA0(s->u.h.chan);
    for (k = 0; k < t->parts18; k++) {
        t->part[k].id = s->parts[k].id;
        t->part[k].a = s->parts[k].a;
        t->part[k].b = s->parts[k].b;
        if (t->used00)
            sub_0019ABB0(t, k, r4d_snd3317C0[t->snd0C].parts[k].vol, i);
    }
    if (t->state08 != 7)
        sub_001ABF20(0, i);
    t->state08 = 5;
}
