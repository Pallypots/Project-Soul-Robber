/* Area r1h, group 8: vibration pattern debug editor 0x0005F290. Names inferred. */
#include "r1h.h"

/* 0x0005F290: message handler of the debug menu that edits the keys
   (level, time) of vibration pattern r1h_seq3E6094. Message 0 counts the
   keys (plus the end row); message 1 test-plays the pattern on button
   0x80, moves the cursor, changes the selected key's level and time by 1
   (10 while button 2 is held), inserts or deletes keys and closes the menu
   on button 0x40; message 2 draws the title, one row per key and the end
   row. */
int r1h_SeqEditProc(int ctx, R1hMenu *m, int msg)
{
    R1hSeEnt *keys = *sub_0005EBA0(r1h_seq3E6094);
    R1hSeEnt *k;
    R1hSeEnt *e;
    int n, step, x, y, i;
    n = 1;
    for (k = keys; k->time >= 0; k++)
        n++;
    keys = *sub_0005EBA0(r1h_seq3E6094);
    e = &keys[m->sel];
    switch (msg) {
    case 0:
        ctx = sub_0003F780(ctx, m, 0);
        m->count = n;
        r1h_g3E6090 = 0;
        return ctx;
    case 1:
        if ((int8_t)sub_0004ECE0(0) < 0) {           /* button 0x80 */
            sub_0005EB40(1);
            sub_0005EB10(0, r1h_seq3E6094);
        }
        step = 1;
        if (sub_0004ECD0(0) & 2)
            step = 10;
        if (sub_0004ECF0(0) & 0x1000)
            m->sel--;
        if (sub_0004ECF0(0) & 0x4000)
            m->sel++;
        if (m->sel < 0)
            m->sel = 0;
        if (m->sel > m->count - 1)
            m->sel = m->count - 1;
        if (sub_0004ECF0(0) & 0x2000) {
            if (e->level + step > 255)
                e->level = 255;
            else
                e->level += step;
        }
        if ((int8_t)(sub_0004ECF0(0) >> 8) < 0) {   /* button 0x8000 */
            if (e->level - step < 0)
                e->level = 0;
            else
                e->level -= step;
        }
        if (sub_0004ECF0(0) & 8) {
            if (e->time + step > 255)
                e->time = (int8_t)255;
            else
                e->time += step;
        }
        if (sub_0004ECF0(0) & 4) {
            if (e->time - step < 1)
                e->time = 1;
            else
                e->time -= step;
        }
        if (sub_0004ECE0(0) & 0x20) {
            if (sub_0005ED30(r1h_seq3E6094, m->sel, 0))
                m->count++;
        }
        if (sub_0004ECE0(0) & 0x10) {
            if (sub_0005EDA0(r1h_seq3E6094, m->sel, 0))
                m->count--;
        }
        if (sub_0004ECE0(0) & 0x40)
            sub_0003E410(m, -1);
        return ctx;
    case 2:
        x = m->x;
        y = m->y;
        ctx = sub_0003E460(ctx, x, y, &x, &y, m);
        ctx = sub_0003E610(ctx, x, y, &x, &y, 0, 0, r1h_fmt26CE9C, r1h_seq3E6094);
        i = 0;
        for (k = keys; k->time != -1; k++) {
            ctx = sub_0003E610(ctx, x, y, &x, &y, m->sel == i, 0, r1h_fmt26CE84, i, k->level, k->time);
            i++;
        }
        return sub_0003E610(ctx, x, y, &x, &y, m->sel == i, 0, r1h_str26CE78);
    }
    return ctx;
}

/* 0x0005F580: as 0x0005F290 for the second key list (+4) of vibration
   pattern r1h_seq3E6094, whose level is only on or off: buttons 0x2000 and
   0x8000 set it to 1 and 0. Message 0 clears r1h_g3E6098 instead of
   r1h_g3E6090, and keys are inserted and deleted in list 1. */
int r1h_SeqEdit2Proc(int ctx, R1hMenu *m, int msg)
{
    R1hSeEnt *keys = sub_0005EBA0(r1h_seq3E6094)[1];
    R1hSeEnt *k;
    R1hSeEnt *e;
    int n, step, x, y, i;
    n = 1;
    for (k = keys; k->time >= 0; k++)
        n++;
    keys = sub_0005EBA0(r1h_seq3E6094)[1];
    e = &keys[m->sel];
    switch (msg) {
    case 0:
        ctx = sub_0003F780(ctx, m, 0);
        m->count = n;
        r1h_g3E6098 = 0;
        return ctx;
    case 1:
        if ((int8_t)sub_0004ECE0(0) < 0) {           /* button 0x80 */
            sub_0005EB40(1);
            sub_0005EB10(0, r1h_seq3E6094);
        }
        step = 1;
        if (sub_0004ECD0(0) & 2)
            step = 10;
        if (sub_0004ECF0(0) & 0x1000)
            m->sel--;
        if (sub_0004ECF0(0) & 0x4000)
            m->sel++;
        if (m->sel < 0)
            m->sel = 0;
        if (m->sel > m->count - 1)
            m->sel = m->count - 1;
        if (sub_0004ECF0(0) & 0x2000)
            e->level = 1;
        if ((int8_t)(sub_0004ECF0(0) >> 8) < 0)     /* button 0x8000 */
            e->level = 0;
        if (sub_0004ECF0(0) & 8) {
            if (e->time + step > 255)
                e->time = (int8_t)255;
            else
                e->time += step;
        }
        if (sub_0004ECF0(0) & 4) {
            if (e->time - step < 1)
                e->time = 1;
            else
                e->time -= step;
        }
        if (sub_0004ECE0(0) & 0x20) {
            if (sub_0005ED30(r1h_seq3E6094, m->sel, 1))
                m->count++;
        }
        if (sub_0004ECE0(0) & 0x10) {
            if (sub_0005EDA0(r1h_seq3E6094, m->sel, 1))
                m->count--;
        }
        if (sub_0004ECE0(0) & 0x40)
            sub_0003E410(m, -1);
        return ctx;
    case 2:
        x = m->x;
        y = m->y;
        ctx = sub_0003E460(ctx, x, y, &x, &y, m);
        ctx = sub_0003E610(ctx, x, y, &x, &y, 0, 0, r1h_fmt26CE9C, r1h_seq3E6094);
        i = 0;
        for (k = keys; k->time != -1; k++) {
            ctx = sub_0003E610(ctx, x, y, &x, &y, m->sel == i, 0, r1h_fmt26CE84, i, k->level, k->time);
            i++;
        }
        return sub_0003E610(ctx, x, y, &x, &y, m->sel == i, 0, r1h_str26CE78);
    }
    return ctx;
}
