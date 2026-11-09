/* Area a4c, group 3: stream/sound requests 0x00048A00..0x00048B20 (kept apart from their callees). Names inferred. */
#include "a4c.h"

/* 0x00048A00: request stream id; returns the handle when it is already playing. */
int a4c_StreamRequest(int id, int a)
{
    if (id != 0) {
        if (a30_g3DFEC0 >= 0 && a30_g3DFEC0 == a30_g3DFEC4 && a30_g3DFEC0 == id) return a30_g3DFECC;
        if (a30_g3DFECC >= 0) a4c_StreamStop(a);
        a30_g3DFEC4 = id;
        return 0;
    }
    return sub_0019B9A0(0x3E3);
}
/* 0x00048B20: play sound id in a free slot and apply its parameters; returns the slot. */
int a4c_SoundPlay(int id, int v)
{
    int h = sub_0019B6A0(id, 0, v);
    if (h >= 0) {
        sub_00047DA0(0x4C, v);
        a4c_soundSlots[h].id = id;
        a4c_soundSlots[h].handle = h;
        a4c_SoundApplyParams(h);
    }
    return h;
}

