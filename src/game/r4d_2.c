/* Area r4d: sound stream helpers around 0x00199EB0-0x0019A7DB (r4d_2). Names inferred. */
#include "r4d.h"

/* 0x00199EB0: once a cue's first stream is done, claim the bank's remaining free streams
   for it. Stack arg (cue); assert-style hang on a bad cue. */
void r4d_CueStartAll(int cue)
{
    R4cCue *c;
    R4cBank *b;
    R4dStream *s;
    int i;
    if (cue == -1)
        return;
    if (cue <= -1 || cue >= 0x77)
        for (;;)
            ;
    c = &r4c_cues330F30[cue];
    b = &r4c_banks3316A0[c->bank];
    if (r4d_CuePoll(cue) != 2)
        return;
    for (i = 1; i < b->count11; i++) {
        s = &r4d_streams401D70[b->first10 + i];
        if (!s->used00) {
            sub_001AA1E0(r4c_g402778);
            s->used00 = 1;
            s->state10 = 2;
            s->cue08 = cue;
            s->bank0C = c->bank;
            s->n34 = 0;
            sub_001AA1F0(r4c_g402778);
        }
    }
}

/* 0x0019A230: count down a paused stream's pause depth and restart it at zero. Stack arg (j). */
void r4d_StreamResume(int j)
{
    R4dStream *s;
    if (j < 0 || j >= 45)
        return;
    s = &r4d_streams401D70[j];
    if (!s->used00 || sub_00199E20(j) != 7)
        return;
    sub_001AA1E0(r4c_g402778);
    if (s->n34 && --s->n34) {
        sub_001AA1F0(r4c_g402778);
        return;
    }
    sub_001AB640(s->vol28 * r4d_g402768 / 16383, s->f2C, s->f30, j);
    sub_001AC1D0(s->snd14, s->bank0C, j);
    s->state10 = 5;
    sub_001AA1F0(r4c_g402778);
}

/* 0x0019A2F0: set a stream volume (0x80 = the sound's default) and apply it. Stack args (j vol). */
void r4d_StreamSetVolume(int j, int vol)
{
    R4dStream *s;
    int st;
    if ((unsigned)j >= 45)
        return;
    s = &r4d_streams401D70[j];
    if (vol == 0x80)
        vol = r4d_snd32C930[s->snd14].vol2;
    st = sub_00199E20(j);
    if (st < -1 || (st > 3 && st != 5))
        return;
    sub_001AA1E0(r4c_g402778);
    s->vol28 = vol;
    sub_001AB640(vol * r4d_g402768 / 16383, s->f2C, s->f30, j);
    sub_001AA1F0(r4c_g402778);
}

/* 0x0019A390: set a stream's volume, two mix parameters (b clamped to 255) and a float
   parameter, then apply them. Stack args (j vol a b c d). */
void r4d_StreamSetParams(int j, int vol, int a, unsigned b, float c, int d)
{
    R4dStream *s;
    int st;
    if ((unsigned)j >= 45)
        return;
    s = &r4d_streams401D70[j];
    if (vol == 0x80)
        vol = r4d_snd32C930[s->snd14].vol2;
    if (b > 0xFF)
        b = 0xFF;
    st = sub_00199E20(j);
    if (st < -1 || (st > 3 && st != 5))
        return;
    sub_001AA1E0(r4c_g402778);
    s->vol28 = vol;
    s->f2C = a;
    s->f30 = b;
    sub_001AB810(d, c, j);
    sub_001AB640(s->vol28 * r4d_g402768 / 16383, s->f2C, s->f30, j);
    sub_001AA1F0(r4c_g402778);
}

/* 0x0019A5A0: pause the playing streams of a bank (state 5 -> 7) and count pause depth.
   Stack args (bank x); assert-style hang on a bad bank. */
void r4d_BankPause(int bank, int x)
{
    R4cBank *b;
    R4dStream *s;
    int i, j;
    if (bank == -1)
        return;
    if (bank <= -1 || bank >= 11)
        for (;;)
            ;
    b = &r4c_banks3316A0[bank];
    for (i = 0; i < b->count11; i++) {
        j = b->first10 + i;
        if (j < 0 || j >= 45)
            continue;
        s = &r4d_streams401D70[j];
        if (!s->used00)
            continue;
        switch (sub_00199E20(j)) {
        case 5:
            sub_001AB050(s->f1C, j, x);
            s->state10 = 7;
            /* fall through */
        case 7:
            s->n34++;
            break;
        }
    }
}
