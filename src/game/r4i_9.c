/* Area r4i: sound driver start-up (0x001AC680). Names inferred. */
#include "r4i.h"

/* 0x001AC680: start the sound driver: record the refresh rate (50 when
   0x001A88B0 reports mode 1, else 60), create the device, clear the
   voice/track/cue tables, reset the ten driver slots, register the
   VOICE and DEMO banks, set the device status, wait until the device
   reports state 3 for its id (counting retries), create the two voices
   with the seven-entry routing table, start sound 0x76 and load the
   effect bank. No inputs. XDK callees are stdcall, 0x001AD150 fastcall
   (ECX = slot). */
void r4i_SoundInit(void)
{
    R4iDevDesc dd;
    R4fDrvQuery q;
    R4iDrvStat st;
    R4iPair pairs[7];
    R4iPairList list;
    R4iBankDesc bank;
    R4iRec3C *r;
    R4eDrvSlot *s;
    R4fDrvVoice *v;
    R4iRec18 *c;
    int i;

    r4i_refreshHz365168 = sub_001A88B0() == 1 ? 50 : 60;
    sub_00203D52();
    dd.f04 = 0;
    dd.f08 = 0;
    dd.f0C = 0;
    dd.f10 = 0;
    dd.f00 = 0x80;
    dd.f04 = 0x40;
    dd.f08 = 0x40;
    dd.f0C = 0;
    sub_00223FCE(&dd, &r4i_dev40E690);
    for (r = r4i_recs40C880; (intptr_t)r < (intptr_t)(r4i_recs40C880 + 11); r++) {
        r->f00 = -1;
        r->f08 = -1;
    }
    v = r4f_voices40CF50;
    i = 45;
    do {
        v->id00 = -1;
        v++;
    } while (--i);
    for (i = 0; i < 4; i++)
        r4f_mus40E358[i].cue00 = -1;
    c = r4i_recs40CB20;
    i = 45;
    do {
        c->f00 = -1;
        c++;
    } while (--i);
    for (s = r4f_slots40E6B8; s != r4f_slots40E6B8 + 10; s++)
        sub_001AD150(s);
    sub_001AB9B0();
    sub_001AB880(1, r4i_strVoice27B968);
    sub_001AB880(2, r4i_strDemo27B960);
    q.f04 = 0;
    q.f08 = 0;
    q.h0C = 0;
    q.f10 = 0;
    q.f14 = 0;
    q.f08 = -1;
    q.kind00 = 3;
    q.f04 = (void *)(intptr_t)r4i_devId40E694;
    q.w02 = 1;
    q.f14 = 0;
    r4i_DrvStatus(r4i_dev40E690, &q);
    r4i_DrvStatus2(r4i_dev40E690, &q);
    while (r4i_DrvQuery(r4i_dev40E690, 0, &st) != 0 || st.f04 != r4i_devId40E694 || st.state00 != 3)
        r4i_retries40EDD0++;
    r4i_DrvVoice(r4i_dev40E690, 2, &r4i_voiceA40E310);
    r4i_DrvVoice(r4i_dev40E690, 2, &r4i_voiceB40E314);
    list.count = 7;
    list.pairs = pairs;
    pairs[0].a = 6;  pairs[0].b = 0;
    pairs[1].a = 8;  pairs[1].b = 0;
    pairs[2].a = 7;  pairs[2].b = 0;
    pairs[3].a = 9;  pairs[3].b = 0;
    pairs[4].a = 2;  pairs[4].b = 0;
    pairs[5].a = 10; pairs[5].b = 0;
    pairs[6].a = 3;  pairs[6].b = 0;
    sub_002227BE(r4i_voiceA40E310, &list);
    sub_002227BE(r4i_voiceB40E314, &list);
    r4f_DrvStartWait(0x76, 10);
    bank.a = 1;
    bank.b = 2;
    sub_0020578E(r4i_strEffectBin27B940, &bank, 0, 0);
}
