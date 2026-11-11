/* Area r1h, group 15: vibration pattern load 0x0005EBB0. Names inferred. */
#include "r1h.h"

/* 0x0005EBB0: (re)create vibration pattern slot from file id: copies the
   two key lists of the loaded file, or when the file is not loaded makes
   a default pattern of one key per list. */
void r1h_ShockLoad(int slot, const char *id)
{
    int32_t *used = &r1h_shockUsed3E604C[slot];
    R1hShock **pp = &r1h_shock3E6050[slot];
    R1hShock *s;
    R1hShockFile *f;
    R1hSeEnt *src, *dst;
    if (*used) {
        if (*pp)
            sub_00053880(*pp);
        *used = 0;
    }
    *pp = 0;
    s = (R1hShock *)sub_00053AB0(sizeof(R1hShock), 0, 0x17E);
    f = sub_00037570(id, 4);
    if (!f) {
        R1hSeEnt *k = s->buf0;
        s->h.m.keys[0] = k;
        s->h.m.len = 30;
        s->h.m.keys[1] = &k[30];
        k[0] = r1h_shockDef2DD7C0;
        k[1] = r1h_shockDef2DD7C2;
        k[30] = r1h_shockDef2DD7BC;
        k[31] = r1h_shockDef2DD7BE;
    } else {
        s->h.hdr = f->hdr;
        src = f->keys;
        dst = s->buf0;
        s->h.m.keys[0] = dst;
        while (src->time >= 0)
            *dst++ = *src++;
        *dst = *src;
        src = &f->keys[f->hdr.off1];
        dst = s->buf1;
        s->h.m.keys[1] = dst;
        while (src->time >= 0)
            *dst++ = *src++;
        *dst = *src;
    }
    r1h_shock3E6050[slot] = s;
    r1h_shockUsed3E604C[slot] = 1;
}
