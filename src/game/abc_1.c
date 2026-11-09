/* Area abc, group 1: event message handlers (0x000B2420..0x000B4800). Names inferred.
 * Messages: 0 init, 1 start (step 10), 3 stop (step 20); other messages count
 * frames and run the current step. */
#include "abc.h"

/* 0x000B2420: set object 0 from event flag 0x2C0. */
int abc_EvFlag2C0(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x2C0)) {
            sub_000A3620(0, 0);
            sub_000A2E10(0, 0);
        } else {
            sub_000A3620(0, 1);
        }
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B2600: set slots 12 and 13 from event flags 0x2C1 and 0x2FC (step 11) after running 0x000B1EF0 (step 10). */
int abc_EvSlotsCDFlag2C1(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000B1EF0();
        e->step++;
        break;
    case 11: {
        AbcSlot *sl = sub_000A4290(12);
        int m;
        if (sub_000D9A70(0x2C1)) {
            sub_000A2D10(12, 0x20);
            sub_000A2D40(13, 0x20);
            sub_000A2CA0(12, 0x10000000);
            sub_000A2CC0(13, 0x10000000);
            m = sl->mode48;
            if (m == 0 || m == 3 || m == 5) {
                sub_000A42F0(12, 2);
                sub_000A42F0(13, 2);
            }
        } else {
            sub_000A2D40(12, 0x20);
            sub_000A2D40(13, 0x20);
            sub_000A2CC0(12, 0x10000000);
            sub_000A2CC0(13, 0x10000000);
            m = sl->mode48;
            if (m == 1 || m == 2 || m == 4) {
                if (sub_000D9A70(0x2FC)) {
                    sub_000A42F0(12, 3);
                    sub_000A42F0(13, 5);
                } else {
                    sub_000A42F0(12, 0);
                    sub_000A42F0(13, 0);
                }
            }
        }
        break;
    }
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B3660: set slot 15 up from event flag 0x2D2, then stop. */
int abc_EvSlotFFlag2D2(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x2D2)) {
            sub_000A42F0(15, 2);
            sub_000A2D70(15, 1);
            sub_000A2D40(15, 0x20);
            sub_000A2CC0(15, 0x80);
            sub_000A2CC0(15, 0x10000000);
        } else {
            sub_000A3690(15, 0);
            sub_000A3480(15, 0, 1);
            sub_000A43C0(15, 2);
        }
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B3360: show or hide slot 14 from event flag 0x2CF. */
int abc_EvSlotEFlag2CF(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x2CF)) {
            sub_000A4410(14, 0);
            sub_000A2D40(14, 0x20);
            sub_000A2CC0(14, 0x10000000);
        } else {
            sub_000A4410(14, 1);
            sub_000A2D10(14, 0x20);
            sub_000A2CA0(14, 0x10000000);
        }
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B3440: effect 0x22 on slots 4, 6, 8, 10, 12 (step 10); steps 11 and 20 end. */
int abc_EvEvenSlotsFx22(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A43C0(4, 0x22);
        sub_000A43C0(6, 0x22);
        sub_000A43C0(8, 0x22);
        sub_000A43C0(10, 0x22);
        sub_000A43C0(12, 0x22);
        e->step++;
        break;
    case 11:
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B3A10: free the handles of slots 4..12, then stop. */
int abc_EvFreeSlots4to12(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        {
            int i;
            for (i = 4; i <= 12; i++) {
                AbcSlot *sl = sub_000A4290(i);
                sub_00033A70(sl->h14C);
                sl->h14C = 0;
                sub_00048250(sl->i154);
                sl->i154 = -1;
            }
        }
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B3E20: effects 0x0E on slot 1 and 0x0F on slot 3. */
int abc_EvB3E20(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A43C0(1, 0x0E);
        sub_000A43C0(3, 0x0F);
        e->step++;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B4700: reset slot 2 and hide slot 18 (step 10), stop once slot 2 is done (step 11). */
int abc_EvB4700(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A42F0(2, 0);
        sub_000A2D10(18, 0x20);
        sub_000A4410(18, 0);
        sub_000D9B30(0x2B0);
        e->step++;
        sub_000A9DA0(2)->i08 = 0;
        break;
    case 11:
        if (sub_000A4370(2)) e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B47D0: show or hide slots 18 and 19 from event flag 0x2B1. */
int abc_EvSlots1819Flag2B1(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x2B1)) {
            sub_000A4410(19, 1);
            sub_000A2D10(18, 0x20);
            sub_000A2D10(19, 0x20);
            sub_000A2CA0(18, 0x10000000);
            sub_000A2CA0(19, 0x10000000);
        } else {
            sub_000A4410(19, 0);
            sub_000A2D40(19, 0x20);
            sub_000A2CC0(18, 0x10000000);
            sub_000A2CC0(19, 0x10000000);
        }
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}
