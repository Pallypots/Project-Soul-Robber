/* Area r1f, group 6: sound channel settings 0x000397A0..0x000398D0. Names inferred. */
#include "r1f.h"

/* 0x000397A0: load the default settings of channel 0 or 1.
   regargs: i=ECX */
void r1f_ChanDefaults(int i)
{
    R1fChan *c = &r1e_chan3DA4A8[i];
    switch (i) {
    case 0:
        c->d04 = 4;
        c->d14 = 0x18;
        break;
    case 1:
        c->d04 = 0;
        c->d14 = 0x30;
        break;
    default:
        return;
    }
    c->kind = 0;
    c->d08 = 0xFF;
    c->d0C = 0x80;
    c->level = 0x40;
    c->d18 = 1;
    c->d1C = 0x80;
    c->d20 = 0x80;
    c->d24 = 0x40;
    c->d28 = 0x40;
}

