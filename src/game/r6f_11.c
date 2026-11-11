/* Area r6f: sound channels and small object helpers around 0x00077190-0x0007AB3F (r6f_11). Names inferred. */
#include "r6f.h"

/* 0x000771E0: set the volume and mode (bits 0..1) of a channel; bit 6 marks a
   nonzero volume. */
void r6f_ChannelSetVolume(int ch, int mode, uint16_t vol)
{
    a60_chVol[ch].vol = vol;
    a60_chFlags[ch] = (a60_chFlags[ch] & ~0x43) | (((vol != 0) & 1) << 6) | (mode & 3);
}

/* 0x0007AB10: store the 0x18-byte sound settings block of an object. */
void r6f_ObjSetSound(R6fSndObj *o, const R6fSndSet *s)
{
    o->snd = *s;
}
