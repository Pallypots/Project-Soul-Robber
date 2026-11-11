/* Area r4d: sound voice and cue helpers around 0x00199980-0x00199D88 (r4d_1). Names inferred. */
#include "r4d.h"

/* 0x00199980: per-tick voice step: state 5 pauses the channel (state 7), state 7 counts. Stack arg. */
void r4d_VoiceTick(int i)
{
    R4cVoice *v;
    if (i < 0 || i >= 16)
        return;
    v = &r4c_voices401B30[i];
    if (!v->f00)
        return;
    switch (sub_00199850(i)) {
    case 5:
        sub_001AAA00(v->ch14, 1);
        v->state10 = 7;
        v->n20++;
        break;
    case 7:
        v->n20++;
        break;
    }
}

/* 0x00199A40: stop a busy voice and release it. Stack arg. */
void r4d_VoiceStop(int i)
{
    R4cVoice *v;
    if (i < 0 || i >= 16)
        return;
    v = &r4c_voices401B30[i];
    if (v->f00 && v->busy04) {
        sub_001AA9D0(v->ch14);
        v->state10 = -1;
        v->busy04 = 0;
        v->n20 = 0;
    }
}

/* 0x00199A90: set a voice volume and apply it scaled by the master volume. Stack args (i vol). */
void r4d_VoiceSetVolume(int i, int vol)
{
    R4cVoice *v;
    if (i < 0 || i >= 16)
        return;
    v = &r4c_voices401B30[i];
    if (v->f00) {
        v->vol1C = vol;
        sub_001ABC00(vol * r4c_g402764 / 16383);
    }
}

/* 0x00199B20: store a voice volume without applying it. Stack args (i vol). */
void r4d_VoiceStoreVolume(int i, int vol)
{
    R4cVoice *v;
    if (i < 0 || i >= 16)
        return;
    v = &r4c_voices401B30[i];
    if (v->f00)
        v->vol1C = vol;
}

/* 0x00199B50: per-frame update of all 16 voices: finish voice 0 playback, free idle voices. No inputs. */
void r4d_VoiceUpdateAll(void)
{
    R4cVoice *v;
    int i;
    for (i = 0; i < 16; i++) {
        v = &r4c_voices401B30[i];
        if (!v->f00)
            continue;
        if (v->ch14 == 0 && v->busy04) {
            if (!sub_001AB150(0x2C)) {
                v->busy04 = 0;
                v->state10 = 2;
            } else {
                sub_001AAE20(0x2C);
            }
        }
        if (i < 0 || i >= 16 || !v->f00 || v->state10 < 0)
            continue;
        if (v->state10 == 0) {
            if (r4c_banks3316A0[v->f0C].first10 == i)
                r4c_banks3316A0[v->f0C].used00 = 0;
            v->f00 = 0;
            v->state10 = -1;
            v->ch14 = -1;
            v->n20 = 0;
        } else if (v->state10 == 2 && v->busy04) {
            v->busy04 = 0;
        }
    }
}

/* 0x00199C10: start cue `cue` on bank `bank` if the bank's stream is free. Stack args (cue bank);
   assert-style hang on a bad cue. */
void r4d_CueStart(int cue, int bank)
{
    R4cStream *s;
    R4cBank *b;
    if (cue <= -1 || cue >= 0x77)
        for (;;)
            ;
    sub_001AA1E0(r4c_g402778);
    b = &r4c_banks3316A0[bank];
    s = &r4c_streams401D70[b->first10];
    if (!s->used00 && !b->used00) {
        r4c_cues330F30[cue].bank = bank;
        s->bank0C = bank;
        b->used00 = 1;
        s->used00 = 1;
        s->state10 = 1;
        s->cue08 = cue;
        s->f34 = 0;
        sub_001AB1D0((uint16_t)cue, bank);
    }
    sub_001AA1F0(r4c_g402778);
}

/* 0x00199CA0: poll a cue's stream; returns 2 when it has finished or stopped, else -1. Stack arg;
   assert-style hang on a bad cue. */
int r4d_CuePoll(int cue)
{
    R4cStream *s;
    int result = -1;
    if (cue <= -1 || cue >= 0x77)
        for (;;)
            ;
    sub_001AA1E0(r4c_g402778);
    s = &r4c_streams401D70[r4c_banks3316A0[r4c_cues330F30[cue].bank].first10];
    if (s->used00 && s->state10 >= 0) {
        if (sub_001AB210((uint16_t)s->cue08, s->bank0C)) {
            result = 2;
            if (s->state10 == 1) {
                sub_001AC2E0((uint16_t)s->cue08, s->bank0C);
                s->state10 = 2;
            }
        } else if (!sub_001AB1F0((uint16_t)s->cue08, s->bank0C) ||
                   sub_001AB280((uint16_t)s->cue08, s->bank0C)) {
            result = 2;
        }
    }
    sub_001AA1F0(r4c_g402778);
    return result;
}
