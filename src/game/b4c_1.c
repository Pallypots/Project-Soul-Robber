/* Area b4c, group 1: level helpers 0x001669C0-0x00166DD0. Names inferred. */
#include "b4c.h"

/* 0x001669C0: send command 7 and stop every table sound except id 0x21D. */
void b4c_StopSounds1669C0(void)
{
    B4cSnd *s;
    sub_000ED600(7);
    for (s = b4c_sndTab279924; s < b4c_sndTab279924 + 4; s++) {
        int id = s->id;
        if (id != 0x21D && sub_0004F6D0(id)) sub_0004F5D0(id);
    }
}

/* 0x00166C90: ask handler type 9 whether to finish; clear active bit if so. */
int b4c_TryFinish166C90(B4cObj *o)
{
    B4cHandler *h = sub_0001D960(o, 9);
    if (h == 0) for (;;) ;
    if (h->fnB4(o, h)) {
        o->flagsC &= ~1u;
        sub_0001EB80(o);
        return 1;
    }
    return 0;
}

/* 0x00166D70: dispatch an event to the object's own handler type. */
int b4c_Dispatch166D70(B4cObj *o, int arg)
{
    B4cHandler *h;
    int r;
    if (o == 0) for (;;) ;
    h = sub_0001D960(o, sub_000EE5F0(o));
    if (h == 0) for (;;) ;
    r = h->fnBC(o, h, arg);
    if (r == 1) {
        sub_00025D50(r, r);
        return r;
    }
    if (r == -1) return 1;
    return r;
}

/* 0x00166DD0: run handler slot 0xD0 for every active object. */
void b4c_UpdateAll166DD0(void)
{
    int off;
    if (b4c_objs3F840C == 0) return;
    for (off = 0; off < 16 * 0x150; off += 0x150) {
        B4cObj *o = (B4cObj *)((uint8_t *)b4c_objs3F840C + off);
        if (o->flagsC & 1) {
            B4cHandler *h = sub_0001D960(o, 9);
            if (h == 0) for (;;) ;
            h->fnD0(o, h);
        }
    }
}
