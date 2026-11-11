/* Area r4d: music track control around 0x0019AA00-0x0019AE82 (r4d_5). Names inferred. */
#include "r4d.h"

/* 0x0019AA00: restart a playing or paused track: reload its sound and re-issue every part.
   Stack args (i x). */
void r4d_TrackRestart(int i, int x)
{
    R4dTrack *t;
    int k, n;
    if (i < 0 || i >= 3)
        return;
    t = &r4d_tracks4019D8[i];
    if (!t->used00)
        return;
    switch (sub_0019A900(i)) {
    case 5: case 7:
        break;
    default:
        return;
    }
    if (t->snd0C < 0x30)
        sub_001AB4A0(t->snd0C, 0);
    else if (t->snd0C < 0x215)
        sub_001AB4A0(t->snd0C, 1);
    else
        sub_001AB4A0(t->snd0C, 2);
    n = t->parts18;
    t->state08 = 3;
    for (k = 0; k < n; k++)
        sub_001AC9C0(t->snd0C, i, k, t->parts18, 0, x, 1);
}

/* 0x0019AAC0: start a track unless it is paused (state 5) or not active. Stack args (i x). */
void r4d_TrackPlay(int i, int x)
{
    R4dTrack *t;
    if (i < 0 || i >= 3)
        return;
    t = &r4d_tracks4019D8[i];
    if (!t->used00)
        return;
    switch (sub_0019A900(i)) {
    case 2: case 3: case 4: case 6: case 7:
        r4d_g402748 = sub_001AAA20(i, x);
        t->n5C = 0;
        r4d_g401B28 = 1;
        t->state08 = 5;
        break;
    }
}

/* 0x0019AB40: pause a track (state 7) and count the pause depth. Stack arg (i). */
void r4d_TrackPause(int i)
{
    R4dTrack *t;
    if (i < 0 || i >= 3)
        return;
    t = &r4d_tracks4019D8[i];
    if (!t->used00)
        return;
    switch (sub_0019A900(i)) {
    case -1: case 0: case 1: case 3: case 5:
        sub_001ABFE0(i, 1);
        t->state08 = 7;
        /* fall through */
    case 7:
        t->n5C++;
        break;
    }
}

/* 0x0019AC20: set the volume of one part (0x80 = the sound's default). Stack args (i k vol);
   calls 0x0019ABB0 with EAX=t ESI=k EDX=vol. */
void r4d_TrackSetPartVolume(int i, int k, int vol)
{
    R4dTrack *t;
    if (i < 0 || i >= 3)
        return;
    t = &r4d_tracks4019D8[i];
    if (!t->used00)
        return;
    if (vol == 0x80)
        vol = ((R4dSndPart *)&r4d_snd3317C0[t->snd0C])[k].vol6;
    r4d_TrackApplyPart(t, k, vol, i);
}

/* 0x0019AC70: set the volume and the two mix values of one part. Stack args (i k vol a b);
   calls 0x0019ABB0 with EAX=t ESI=k EDX=vol. */
void r4d_TrackSetPart(int i, int k, int vol, int a, int b)
{
    R4dTrack *t;
    if (i < 0 || i >= 3)
        return;
    t = &r4d_tracks4019D8[i];
    if (!t->used00)
        return;
    if (vol == 0x80)
        vol = ((R4dSndPart *)&r4d_snd3317C0[t->snd0C])[k].vol6;
    t->part[k].a = a;
    t->part[k].b = b;
    r4d_TrackApplyPart(t, k, vol, i);
}

/* 0x0019AD50: like 0x0019AC20 but only while the track is playing or paused. Stack args (i k vol);
   calls 0x0019ABB0 with EAX=t ESI=k EDX=vol. */
void r4d_TrackSetPartVolumeIfPlaying(int i, int k, int vol)
{
    R4dTrack *t;
    if (i < 0 || i >= 3)
        return;
    t = &r4d_tracks4019D8[i];
    if (!t->used00)
        return;
    switch (sub_0019A900(i)) {
    case 5: case 7:
        break;
    default:
        return;
    }
    if (vol == 0x80)
        vol = ((R4dSndPart *)&r4d_snd3317C0[t->snd0C])[k].vol6;
    r4d_TrackApplyPart(t, k, vol, i);
}

/* 0x0019AE00: per-frame update of the three tracks: finish playback, free stopped tracks. No inputs. */
void r4d_TrackUpdateAll(void)
{
    R4dTrack *t;
    int i;
    for (i = 0; i < 3; i++) {
        t = &r4d_tracks4019D8[i];
        if (!t->used00)
            continue;
        if (t->busy04 && !sub_001ACCE0(i)) {
            t->state08 = 0;
            t->busy04 = 0;
        }
        if (i < 0 || i >= 3 || !t->used00 || t->state08 < 0)
            continue;
        if (t->state08 == 0) {
            t->used00 = 0;
            t->state08 = -1;
            t->snd0C = -1;
            t->n5C = 0;
        } else if (t->state08 == 2 && t->busy04) {
            t->busy04 = 0;
        }
    }
    sub_001AB850();
}
