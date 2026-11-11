/* Area r1d, group 16: packet entries and fade channels 0x00038D90..0x00039820. Names inferred. */
#include "r1d.h"

/* 0x00038D90: append a texture transfer entry to the packet stream,
   growing it first when full.  calls 0x00038BF0 with EBX=&stream */
void r1d_PkAddTex(int a, int b, int c)
{
    if (r1d_pkRoom3DA328 == 0)
        sub_00038BF0(&r1_pk3DA320);
    r1d_pkEnd3DA324[3] = c << 15;
    r1d_pkEnd3DA324[2] = 0xFFFFFFFF;
    r1d_pkEnd3DA324[1] = b * 8 + 0x7900;
    r1d_pkEnd3DA324[0] = (a + 0x700) << 4;
    r1d_pkEnd3DA324 += 4;
    r1d_pkRoom3DA328--;
}

/* 0x00038E10: append a two-word entry (a, b, 0, 0) to the packet stream.
   calls 0x00038BF0 with EBX=&stream */
void r1d_PkAdd4(int a, int b)
{
    if (r1d_pkRoom3DA328 == 0)
        sub_00038BF0(&r1_pk3DA320);
    r1d_pkEnd3DA324[3] = 0;
    r1d_pkEnd3DA324[2] = 0;
    r1d_pkEnd3DA324[1] = b;
    r1d_pkEnd3DA324[0] = a;
    r1d_pkEnd3DA324 += 4;
    r1d_pkRoom3DA328--;
}

/* 0x00039820: set the mode, level and speed of fade channel 1. */
void r1d_Fade1Mode(int m)
{
    switch (m) {
    case 0:
        r1c_chan3DA4A8[1].mode = 0;
        r1c_chan3DA4A8[1].speed = 0x30;
        r1c_chan3DA4A8[1].level = 0x80;
        break;
    case 1:
        r1c_chan3DA4A8[1].mode = 2;
        r1c_chan3DA4A8[1].level = 0xFF;
        r1c_chan3DA4A8[1].speed = 0x30;
        break;
    case 2:
        r1c_chan3DA4A8[1].mode = 3;
        r1c_chan3DA4A8[1].level = 0xFF;
        r1c_chan3DA4A8[1].speed = 0xA;
        break;
    case 3:
        r1c_chan3DA4A8[1].mode = 2;
        r1c_chan3DA4A8[1].speed = 0xFF;
        r1c_chan3DA4A8[1].level = 0x80;
        break;
    }
}
