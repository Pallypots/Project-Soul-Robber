/* Area r4f: music players at 0x001ABC10-0x001AC078 (r4f_18). Names inferred. */
#include "r4f.h"

/* 0x001ABC10: stop the music player with id: query its cue (engine 1 or 2; mode 0 resets
   0x00365164), stop the voice, stop its cue pair and clear the player. Returns the
   player index or -1. Stack args (a id). XACT callees are stdcall. */
int r4f_MusStop(int a, int id)
{
    R4fMusTrack *t;
    int i, x;
    for (i = 0, t = r4f_mus40E358; i < 4; i++, t++)
        if (t->id24 == id)
            break;
    if (i == 4)
        return -1;
    if (t->mode04 == 0) {
        x = a;
        r4f_g365164 = -1;
    }
    if (t->mode04 == 1)
        sub_0022268D(r4f_engines40C868[1], &r4f_cues338858[t->cue00], &x);
    if (t->mode04 == 2)
        sub_0022268D(r4f_engines40C868[2], &r4f_cues33AE40[t->cue00], &x);
    sub_00222538(r4d_drvDev40E690, &t->w2C);
    sub_002225B2(r4d_drvDev40E690, &t->w2C);
    sub_00222726(r4f_engines40C868[t->mode04], -1, 2, r4f_musPlay40E300[i]);
    r4f_MusicCueCmd(1, t->cue00);
    t->b28 = 0;
    t->paused29 = 0;
    t->f0C = 0;
    t->cue00 = -1;
    t->f14 = 0;
    t->f18 = 0;
    t->f1C = 0;
    t->id24 = -1;
    return i;
}

/* 0x001ABF20: start the music player with id (or the first free one): play its cue pair,
   start the cue on the current engine and queue the voice status. Stack args (unused id).
   XACT callees are stdcall. */
void r4f_MusPlay(int unused, int id)
{
    R4dDrvMsg m;
    R4fMusTrack *t;
    int i;
    (void)unused;
    for (i = 0, t = r4f_mus40E358; i < 4; i++, t++)
        if (t->id24 == id || t->cue00 == -1)
            break;
    if (i == 4)
        return;
    m.kind = 4;
    m.x = t->cue00;
    m.f0C = 0;
    m.f08 = 0;
    r4f_MusicCueCmd(0, t->cue00);
    sub_002226F3(r4f_engines40C868[r4d_drvMode40E348], &m, &r4f_musPlay40E300[i]);
    t->w2E = 4;
    t->f30 = r4f_engines40C868[r4d_drvMode40E348];
    t->h38 = r4f_musPlay40E300[i];
    t->w2C = 1;
    sub_002225B2(r4d_drvDev40E690, &t->w2C);
    sub_002224FD(r4d_drvDev40E690, &t->w2C);
    sub_00223F9C();
    r4f_g365164 = aac_g365158;
}

/* 0x001ABFE0: pause (pause != 0) or resume the music player with id, with its cue pair.
   Stack args (id pause). XACT callees are stdcall. */
void r4f_MusPause(int id, int pause)
{
    R4fMusTrack *t;
    int i;
    for (i = 0, t = r4f_mus40E358; i < 4; i++, t++)
        if (t->id24 == id)
            break;
    if (i == 4 || t->cue00 == -1)
        return;
    if (!t->paused29 && pause) {
        sub_0022275D(r4f_engines40C868[t->mode04], r4f_musPlay40E300[i], 1);
        r4f_MusicCueCmd(2, t->cue00);
        t->paused29 = 1;
    } else if (t->paused29 == 1 && !pause) {
        sub_0022275D(r4f_engines40C868[t->mode04], r4f_musPlay40E300[i], 0);
        r4f_MusicCueCmd(3, t->cue00);
        t->paused29 = 0;
    }
}
