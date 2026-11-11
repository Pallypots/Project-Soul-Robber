/* Area r1i, group 3: sprite track key interpolation 0x00017F70. Names inferred. */
#include "r1i.h"

/* 0x00017F70: take the interpolated key record at t->cur (advancing past
   it) and set the current key values to from + (to - from) * u, where
   u = (time - t0) / len; sx and sy are scaled by 1/1024 and the colour is
   interpolated per byte. regargs: t=EAX */
void r1i_TrackLerp(R1iTrack *t)
{
    R1iTrkLerp *k = (R1iTrkLerp *)t->cur;
    float u;
    int a, r, g, b, c;
    uint32_t to;
    t->cur = (uint8_t *)k + sizeof(R1iTrkLerp);
    u = (t->time - (float)k->t0) / (float)k->len;
    r1i_trkVal42CE60.x = (float)(k->to[0] - k->from[0]) * u + (float)k->from[0];
    r1i_trkVal42CE60.y = (float)(k->to[1] - k->from[1]) * u + (float)k->from[1];
    r1i_trkVal42CE60.z = (float)(k->to[2] - k->from[2]) * u + (float)k->from[2];
    r1i_trkVal42CE60.sx = ((float)(k->to[3] - k->from[3]) * u + (float)k->from[3]) * 0.0009765625f;
    r1i_trkVal42CE60.sy = ((float)(k->to[4] - k->from[4]) * u + (float)k->from[4]) * 0.0009765625f;
    r1i_trkVal42CE60.rot = (float)(k->to[5] - k->from[5]) * u + (float)k->from[5];
    a = (uint8_t)(k->col0 >> 24);
    b = (uint8_t)(k->col0 >> 16);
    g = (uint8_t)(k->col0 >> 8);
    r = (uint8_t)k->col0;
    to = k->col1;
    c = (int)((float)((uint8_t)(to >> 24) - a) * u + (float)a);
    c = c << 8 | (int)((float)((uint8_t)(to >> 16) - b) * u + (float)b);
    c = c << 8 | (int)((float)((uint8_t)(to >> 8) - g) * u + (float)g);
    c = c << 8 | (int)((float)((uint8_t)to - r) * u + (float)r);
    r1i_trkVal42CE60.col = (uint32_t)c;
}
