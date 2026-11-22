/* Area r4f: driver voice fade/release tick (r4f_20). Names inferred. */
#include "r4f.h"

extern uint8_t r4f_tick40E6AA;      /* 0x0040E6AA nonzero while a tick is pending */
extern int32_t r4f_step40E6B0;      /* 0x0040E6B0 current step */
extern int32_t r4f_steps40E6AC;     /* 0x0040E6AC step count */
extern void   *r4f_voiceG40E518[];  /* 0x0040E518 per-voice group objects */
extern uint8_t r4f_slotTab40E604[]; /* 0x0040E604 0xB4-byte driver slots */
int  __fastcall m1_PeerCall1AA690(void *p, int unusedEdx, void *a, int b); /* thiscall, ECX=p */
void r4f_VoiceVolume1AB4E0(int v, int vol);  /* 0x001AB4E0 */

#define VI10(d) (*(int32_t *)((d)->unk08 + 0x08))   /* +0x10 */
#define VI0C(d) (*(int32_t *)((d)->unk08 + 0x04))   /* +0x0C */

/* 0x001AC080: while steps remain, ramp the volume of every live voice (ids above 0xD,
   outside 0x24E..0x258, not 0x5A) and advance by 2; on the last step release them, or
   for voices with +0x10 == -1 restart their group object, then clear the tick. */
void r4f_DrvVoiceTick(void)
{
    R4fDrvVoice *d;
    int n;
    volatile int id;
    if (!r4f_tick40E6AA)
        return;
    if (r4f_step40E6B0 >= r4f_steps40E6AC) {
        d = r4f_voices40CF50;
        for (n = 45; n != 0; n--, d++) {
            if (VI10(d) == -1) {
                int v = d->f24;
                volatile int vv = v;
                void *h = r4f_voiceH40E5D8[v];
                int g = d->f04;
                if (h && r4f_voiceG40E518[v] && g >= 1 && vv >= 0 && vv <= 0x2D) {
                    m1_PeerCall1AA690(r4f_slotTab40E604 + g * 0xB4, 0, h, 1);
                    r4f_voices40CF50[v].b29 = 1;
                }
            } else if (d->b28 == 1) {
                id = d->id00;
                if (id > 0xD && (id <= 0x24D || id >= 0x25A) && id != 0x5A && d->b2A == 1)
                    sub_001AAD40(0, id, d->f04, d->f24);
            }
        }
        r4f_tick40E6AA = 0;
        r4f_step40E6B0 = 0;
        return;
    }
    {
    R4fDrvVoice *volatile w = r4f_voices40CF50;
    for (n = 45; n != 0; n--, w++) {
        if (w->b28 == 1) {
            id = w->id00;
            if (id > 0xD && (id <= 0x24D || id >= 0x259) && id != 0x5A && w->b2A == 1)
                r4f_VoiceVolume1AB4E0(w->f24, (int)((double)(r4f_steps40E6AC - r4f_step40E6B0) * VI0C(w) * 0.01));
        }
    }
    }
    r4f_step40E6B0 += 2;
}
