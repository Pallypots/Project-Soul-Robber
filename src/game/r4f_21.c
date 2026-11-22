/* Area r4f: start a driver voice for a sound cue (r4f_21). Names inferred. */
#include "r4f.h"

extern R4fCueRec r4f_cue340200;           /* 0x00340200 cue used by group 10 */
extern R4fCueRec r4f_cues33B458[];        /* 0x0033B458 per-sound cue records */
extern uint8_t   r4f_slotTab40E6B8[];     /* 0x0040E6B8 0xB4-byte driver slots, by group - 1 */
int  R4D_FASTCALL sub_001ACF00(void *slot);
int  __fastcall r4f_SlotQuery1AA5D0(void *slot, int unusedEdx, void *q, void **out);   /* thiscall, ECX=slot */

typedef struct R4fVoiceQ { int32_t kind; int32_t h; int32_t z0; int32_t z1; } R4fVoiceQ;

/* 0x001AAF10: start voice v (below 45) for sound snd in group grp: the cue is snd's record
   (group 10 uses a fixed one); a busy voice in an idle slot is left alone; the slot's engine
   resolves the cue (group 10 cue 0x2C may go ahead without it), the slot hands out a handle
   and the voice record is filled and queued on the device. Returns 1 when started.
   Stack args (unused snd grp unused v). */
int r4f_DrvVoiceStart(int unused1, int snd, int grp, int unused4, int v)
{
    R4fDrvVoice *d;
    uint8_t *slot;
    R4fCueRec *cue;
    R4fVoiceQ q;
    int g, tmp;
    if (v >= 0x2D)
        return 0;
    g = grp - 1;
    if (g == 9)
        cue = &r4f_cue340200;
    else {
        cue = &r4f_cues33B458[snd];
        if (!cue)
            return 0;
    }
    d = &r4f_voices40CF50[v];
    slot = r4f_slotTab40E6B8 + g * 0xB4;
    if (!sub_001ACF00(slot) && d->b28 == 1)
        return 0;
    if (sub_001ACF00(slot)) {
        if (sub_0022268D(*(void **)(slot + 0x58), cue, &tmp) == 0)
            goto query;
    }
    if (g != 9 || v != 0x2C)
        return 0;
    tmp = 0;
query:
    q.z1 = 0;
    q.z0 = 0;
    q.h = tmp;
    q.kind = 8;
    if (r4f_SlotQuery1AA5D0(slot, 0, &q, &r4f_voiceH40E5D8[v]))
        return 0;
    d->f24 = v;
    d->w2C = 1;
    d->id00 = snd;
    d->f04 = grp;
    *(R4fCueRec **)d->unk08 = cue;
    d->b28 = 1;
    *(volatile uint8_t *)&d->b29 = 0;   /* separate byte store */
    d->w2E = 4;
    d->f30 = *(void **)(slot + 0x58);
    d->h38 = r4f_voiceH40E5D8[v];
    sub_002224FD(r4d_drvDev40E690, &d->w2C);
    return 1;
}
