/* Area r1i, group 2: key sequence player 0x00014E80. Names inferred. */
#include "r1i.h"

/* 0x00014E80: advance key sequence player p by one frame (unless flags 1|8
   or input 0x8000 pause it). When the current key's time runs out, step
   through the keys of the current track until time is left:
   -1 end (hold the last key with flag 4, else restart and mark done),
   0 wait, 1 value (sets value from the next wait key, rate and span),
   2 loop end (restart unless flag 2, then like -1), 3 jump to track arg. */
void r1i_SeqPlayUpdate(R1iSprite *p)
{
    int track, key, start, n;
    R1iKey *keys, *e;
    uint32_t f;
    if (p->flags & 9)
        return;
    if (sub_0019BE60(0x8000) == 1)
        return;
    if (p->time > 0.0f)
        p->time -= p->speed * a50_frameUnits;
    if (!(0.0f >= p->time))
        return;
    track = p->track;
    do {
        key = ++p->key;
        if (p->changed)
            p->changed = 0;
        keys = p->data->tracks[track];
        switch (keys[key].cmd) {
        case 0:
            p->time += keys[key].dur;
            break;
        case 1:
            p->changed = 1;
            start = key;
        rescan:
            n = 0;
            for (e = &keys[start]; e->cmd != 0; e++) {
                if (e->cmd == -1) {
                    start = 0;
                    goto rescan;
                }
                n++;
            }
            p->value = R1I_FTOI(keys[start + n].arg);
            p->rate = keys[key].arg;
            p->span = keys[key].dur;
            p->time = p->rate * keys[key].dur + p->time;
            p->i30 = 0;
            break;
        case 2:
            f = p->flags | 0x80;
            p->flags = f;
            if (!(f & 2)) {
                p->key = 0;
                p->time += p->data->tracks[track][0].dur;
                break;
            }
            goto hold;
        case 3:
            track = p->track = R1I_FTOI(keys[key].arg);
            p->key = 0;
            p->time += p->data->tracks[track][0].dur;
            break;
        case -1:
            f = p->flags | 0x80;
            p->flags = f;
        hold:
            if (!(f & 4)) {
                p->key = 0;
                p->time = p->data->tracks[track][0].dur;
                p->flags = f | 1;
            } else {
                p->key = --key;
                p->time += keys[key].dur;
            }
            break;
        }
    } while (0.0f >= p->time);
}
