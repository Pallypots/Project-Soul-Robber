/* Area abc, group 2: event message handlers (0x000B5C10..0x000BB0F0). Names inferred.
 * Messages: 0 init, 1 start (step 10), 3 stop (step 20); other messages count
 * frames and run the current step. */
#include "abc.h"

/* 0x000B5C10: set slot 1 from event flag 0x43. */
int abc_EvSlot1Flag43(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x43)) sub_000A4410(1, 1);
        else sub_000A4410(1, 0);
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5CB0: set slot 0 from event flag 0x44. */
int abc_EvSlot0Flag44(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x44)) sub_000A4410(0, 1);
        else sub_000A4410(0, 0);
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5D50: set slot 2 from event flag 0x45. */
int abc_EvSlot2Flag45(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x45)) sub_000A4410(2, 1);
        else sub_000A4410(2, 0);
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5DF0: set slot 3 from event flag 0x46. */
int abc_EvSlot3Flag46(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x46)) sub_000A4410(3, 1);
        else sub_000A4410(3, 0);
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5EA0: start effect 0x1A on slot 0, then stop. */
int abc_EvB5EA0(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A43C0(0, 0x1A);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5F20: effect 0x2E on slots 10 and 11, then 0x000A5450(12). */
int abc_EvB5F20(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A43C0(10, 0x2E);
        sub_000A43C0(11, 0x2E);
        sub_000A5450(12);
        e->step++;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B5FC0: show or hide slot 0 from event flag 0xBE. */
int abc_EvSlot0FlagBE(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0xBE)) {
            sub_000A4410(0, 0);
            sub_000A2D10(0, 0x20);
            sub_000A2CA0(0, 0x10000000);
        } else {
            sub_000A4410(0, 0);
            sub_000A2D40(0, 0x20);
            sub_000A2CC0(0, 0x10000000);
        }
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B6380: reset slot 5 and start effect 0x2D on it. */
int abc_EvB6380(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A42F0(5, 0);
        sub_000A43C0(5, 0x2D);
        e->step++;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B6410: effect 0x2E on slots 6..8, then 0x000A5450(9). */
int abc_EvB6410(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A43C0(6, 0x2E);
        sub_000A43C0(7, 0x2E);
        sub_000A43C0(8, 0x2E);
        sub_000A5450(9);
        e->step++;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B6560: 0x000A5450(9), then effect 0x2C on slots 0..7. */
int abc_EvB6560(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        sub_000A5450(9);
        sub_000A43C0(0, 0x2C);
        sub_000A43C0(1, 0x2C);
        sub_000A43C0(2, 0x2C);
        sub_000A43C0(3, 0x2C);
        sub_000A43C0(4, 0x2C);
        sub_000A43C0(5, 0x2C);
        sub_000A43C0(6, 0x2C);
        sub_000A43C0(7, 0x2C);
        e->step++;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B6630: set slot 8 up from event flag 0x2EF, then stop. */
int abc_EvSlot8Flag2EF(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x2EF)) {
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

/* 0x000B7040: refill Jack's health and raise stat 15 to stat 14 (step 10). */
int abc_EvRefillHealth(int msg, AbcEvt2 *e)
{
    int a, b;
    if (msg == 0) { e->flags = 0; e->step = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; return 0; }
    switch (e->step) {
    case 10:
        sub_00023D80(2, 0x1E);
        abc_PlayerD0030(&abc_player, 0x50);
        Stats_Set(&g_stats, 1, Stats_Get(&g_stats, 0));
        a = Stats_Get(&g_stats, 14);
        b = Stats_Get(&g_stats, 15);
        if (a > b) Stats_Set(&g_stats, 15, a);
        e->step = 20;
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B7F90: while event flag 0xF2 is set, show slot 5 from flag 0xBE; else stop. */
int abc_EvSlot5FlagF2(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (!sub_000D9A70(0xF2)) { e->step = 20; break; }
        if (sub_000D9A70(0xBE)) {
            sub_000A4410(5, 1);
            sub_000A2D10(5, 0x20);
        } else {
            sub_000A4410(5, 0);
            sub_000A2D40(5, 0x20);
        }
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B8070: while event flag 0xF1 is set, set slot 8 from flag 0x104; else stop. */
int abc_EvSlot8FlagF1(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (!sub_000D9A70(0xF1)) { e->step = 20; break; }
        if (sub_000D9A70(0x104)) sub_000A4410(8, 1);
        else sub_000A4410(8, 0);
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000B9180: swap slots 0 and 1 from event flag 0x118. */
int abc_EvSlots01Flag118(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0x118)) {
            sub_000A4410(1, 1);
            sub_000A4410(0, 0);
            sub_000A2D40(0, 0x20);
        } else {
            sub_000A4410(1, 0);
            sub_000A4410(0, 1);
            sub_000A2D10(0, 0x20);
        }
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BAAF0: set slot 7 from event flag 0xC5. */
int abc_EvSlot7FlagC5(int msg, AbcEvt *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; e->count = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; e->count = 0; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 20; }
    e->count++;
    switch (e->step) {
    case 10:
        if (sub_000D9A70(0xC5)) sub_000A4410(7, 1);
        else sub_000A4410(7, 0);
        break;
    case 20:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}

/* 0x000BB0F0: clear slots 1, 3, 5, 7 and 9 once (step 10, done at 15). */
int abc_EvClearOddSlots(int msg, AbcEvt2 *e)
{
    if (msg == 0) { e->flags = 0; e->step = 0; return 1; }
    if (msg == 1) { e->flags |= 1; e->step = 10; return 1; }
    if (msg == 3) { e->flags = 0; e->step = 0; return 0; }
    switch (e->step) {
    case 10:
        sub_000A4410(1, 0);
        sub_000A4410(3, 0);
        sub_000A4410(5, 0);
        sub_000A4410(7, 0);
        sub_000A4410(9, 0);
        e->step++;
        break;
    case 15:
        e->flags = 0; e->step = 0;
        return 0;
    }
    return 1;
}
