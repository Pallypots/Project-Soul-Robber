/* Area r1h, group 9: debug sound test menu 0x0005D250. Names inferred. */
#include "r1h.h"

/* 0x0005D250: message handler of the debug sound test menu bound to the
   world's sound test block (+0x1F0). Message 0 sets up the id item (0..9)
   and the pitch item (-0x7D00..0x7D00, step 100); message 1 copies edited
   values back, resets the pitch to 0x1800 on button 0x200 and plays the
   sound on row 3 with button 0x20; other messages go to the default
   handler. */
void *r1h_SndTestProc(void *ctx, R1hMenu *m, int msg)
{
    R1hSndTest *t = r1h_world42C8E4->p1F0;
    switch (msg) {
    case 0:
        ctx = sub_0003F780(ctx, m, 0);
        sub_0003EC30(&m->items->items[0], t->id, 0, 9, 1, 1);
        sub_0003EC30(&m->items->items[1], t->pitch, -0x7D00, 0x7D00, 100, 10);
        return ctx;
    case 1:
        if (sub_0003F770(m))
            return ctx;
        switch (m->sel) {
        case 0:
            if (sub_0003F570(m))
                t->id = sub_0003EB10(&m->items->items[m->sel]);
            sub_0004ECE0(m->pad);
            return ctx;
        case 1:
            if (sub_0003F570(m))
                t->pitch = sub_0003EB10(&m->items->items[m->sel]);
            if (sub_0004ECE0(m->pad) & 0x200) {
                t->pitch = 0x1800;
                sub_0003EA10(&m->items->items[m->sel], 0x1800);
            }
            return ctx;
        case 3:
            if (sub_0004ECE0(m->pad) & 0x20)
                sub_001997E0(t->id, t->pitch);
            return ctx;
        }
        return ctx;
    default:
        return sub_0003F780(ctx, m, msg);
    }
}
