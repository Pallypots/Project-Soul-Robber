/* Area r4c: camera-attached effect and sound voice helpers 0x00199500-0x00199C9F (r4c_9). Names inferred. */
#include "r4c.h"

/* 0x00199500: stop a timed effect, set the actor's +0x70 from 0x0032C91C and attach it at the camera point.
   Stack args (o a). Calls 0x00198DA0 with ESI=point EDI=o. */
void r4c_TimedAttachCam0(R4cNode *o, R4cActor *a)
{
    R4cTimedV *w = (R4cTimedV *)a->work;
    float v[4];
    w->v08[0] = r4c_frameSeconds * 0.0f;
    w->v08[1] = r4c_frameSeconds * 0.0f;
    w->v08[2] = r4c_frameSeconds * 0.0f;
    w->v08[3] = r4c_frameSeconds * 0.0f;
    a->f70 = r4c_g32C91C;
    r4c_CamPoint(v, o);
    sub_00034CF0((void *)sub_00036750(o, 0), v[0], v[1], v[2], v[3]);
}

/* 0x001998C0: start a free voice of bank 0 on channel ch (0 or 1); returns its voice index or -1.
   Hangs on a bad channel. Stack args. */
int r4c_VoiceAlloc(int ch)
{
    R4cVoice *v;
    int n, i;
    if (ch <= -1 || ch >= 2)
        for (;;)
            ;
    v = &r4c_voices401B30[r4c_banks3316A0[0].first10];
    n = r4c_banks3316A0[0].count11;
    for (i = 0; i < n; i++, v++)
        if (v->f00 && !v->busy04)
            goto found;
    return -1;
found:
    v->busy04 = 1;
    v->ch14 = ch;
    v->vol1C = r4c_banks3316A0[0].vol14;
    v->f18 = 0x100;
    v->state10 = 5;
    v->n20 = 0;
    sub_001AA950(ch);
    sub_001ABC00(v->vol1C * r4c_g402764 / 16383);
    sub_001AA970(v->ch14);
    return r4c_banks3316A0[0].first10 + i;
}
