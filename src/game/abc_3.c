/* Area abc, group 3: table getters and event message handlers (0x000BA4B0..0x000BBC00). Names inferred. */
#include "abc.h"

/* 0x000BA4B0: address of the table at 0x002E5DE0. */
uint8_t *abc_GetTable2E5DE0(void) { return abc_d2E5DE0; }

/* 0x000BB0E0: address of the table at 0x002E5EEC. */
uint8_t *abc_GetTable2E5EEC(void) { return abc_d2E5EEC; }

/* 0x000BB330: set slot 8 up from event flag 0x2EE, then stop. */
int abc_EvSlot8Flag2EE(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x2EE)) {
            sub_000A42F0(8, 2);
            sub_000A2D70(8, 1);
            sub_000A2D40(8, 0x20);
            sub_000A2CC0(8, 0x80);
            sub_000A2CC0(8, 0x10000000);
        } else {
            sub_000A3690(8, 0);
            sub_000A3480(8, 0, 1);
            sub_000A43C0(8, 2);
        }
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BB7E0: put slot 3 in mode 0 or 2 from event flag 0x3D (steps 0 and 10). */
int abc_EvSlot3Flag3D(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 0:
        sub_000A42F0(3, sub_000D9A70(0x3D) ? 0 : 2);
        e->step++;
        break;
    case 10:
        sub_000A42F0(3, sub_000D9A70(0x3D) ? 0 : 2);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BB8B0: put slot 1 in mode 0 or 2 from event flag 0x3E (steps 0 and 10). */
int abc_EvSlot1Flag3E(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 0:
        sub_000A42F0(1, sub_000D9A70(0x3E) ? 0 : 2);
        e->step++;
        break;
    case 10:
        sub_000A42F0(1, sub_000D9A70(0x3E) ? 0 : 2);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BB980: put slot 0 in mode 0 or 2 from event flag 0x3F (steps 0 and 10). */
int abc_EvSlot0Flag3F(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 0:
        sub_000A42F0(0, sub_000D9A70(0x3F) ? 0 : 2);
        e->step++;
        break;
    case 10:
        sub_000A42F0(0, sub_000D9A70(0x3F) ? 0 : 2);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BBA50: put slot 2 in mode 0 or 2 from event flag 0x40 (steps 0 and 10). */
int abc_EvSlot2Flag40(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 0:
        sub_000A42F0(2, sub_000D9A70(0x40) ? 0 : 2);
        e->step++;
        break;
    case 10:
        sub_000A42F0(2, sub_000D9A70(0x40) ? 0 : 2);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BBB30: show slot 7 from event flag 0xE4 and turn slot 8 off. */
int abc_EvSlot7FlagE4(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0xE4)) {
            sub_000A4410(7, 0);
            sub_000A2D40(7, 0x20);
        } else {
            sub_000A4410(7, 1);
            sub_000A2D10(7, 0x20);
        }
        sub_000A4410(8, 0);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BBC00: show slot 9 from event flag 0xE5 and turn slot 10 off. */
int abc_EvSlot9FlagE5(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0xE5)) {
            sub_000A4410(9, 0);
            sub_000A2D40(9, 0x20);
        } else {
            sub_000A4410(9, 1);
            sub_000A2D10(9, 0x20);
        }
        sub_000A4410(10, 0);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}
