/* Area r1j, group 7: positional sound voices 0x00049000.
   Names inferred. */
#include "r1j.h"

/* 0x00049000: per-frame update of the 45 positional sound voices. A voice
   whose channel no longer holds its handle is left alone; one whose
   channel stopped is released. Otherwise volume and pan angle are
   computed from the voice position (0x00048B70); the stored pan moves a
   tenth of the way towards the new angle (whole way within 10 degrees,
   wrapping through 360), is kept in 0..359, and both go to the channel
   (0x0019A390) together with the listener vector r1j_sndListener. */
void r1j_SndVoicesUpdate(void)
{
    R1jSndVoice *v;
    int i, d, a3, a4;
    int pan, vol;
    for (i = 0; i < 45; i++) {
        v = &r1j_sndVoices[i];
        if (v->active == 0)
            continue;
        if (v->handle != sub_0019A540(i))
            continue;
        if (sub_00199E70(i) == 0) {
            v->active = 0;
            continue;
        }
        a4 = sub_0019A590(sub_0019A540(i));
        a3 = sub_0019A580(sub_0019A540(i));
        sub_00048B70(v->pos, &vol, &pan, v->mode, v->range, a3, a4);
        d = pan - v->pan;
        if (d > 180) {
            if (d <= 360) {
                if (d < 350)
                    d /= 10;
                v->pan = (int16_t)(v->pan + d - 360);
            }
        } else if (d >= -180) {
            if (d <= -10 || d >= 10)
                d /= 10;
            v->pan = (int16_t)(v->pan + d);
        } else if (d > -360) {
            if (d > -350)
                d /= 10;
            v->pan = (int16_t)(v->pan + d + 360);
        }
        v->vol = (int16_t)vol;
        v->pan = (int16_t)((v->pan + 360) % 360);
        sub_0019A390(i, v->id, v->pan, v->vol, v->range, r1j_sndListener);
    }
}
