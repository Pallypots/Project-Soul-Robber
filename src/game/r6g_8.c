/* Area r6g: scripted event handler (r6g_8). Names inferred. */
#include "r6g.h"

/* 0x000B4BC0: event handler: step 10 waits for event bit 0xCD (counting up to
   step 11 while it is clear), step 11 waits for bit 0x11B and sets bit 0xCD;
   either way the actor of slot 0 is hidden and the camera mode is set before
   finishing. Message 0 resets, 1 starts, 3 stops. Returns 0 when finished. */
int r6g_EvtWaitBits(int msg, R6gEvt *e)
{
    if (msg == 0) {
        e->flags = 0;
        e->state = 0;
        return 1;
    }
    if (msg == 1) {
        e->flags |= 1;
        e->state = 10;
        return 1;
    }
    if (msg == 3) {
        e->flags = 0;
        e->state = 0;
        return 0;
    }
    switch (e->state) {
    case 10:
        if (sub_000D9A70(0xCD)) {
            sub_000A42F0(0, 2);
            sub_0001B3F0(aa0_slots[0].obj);
            aa0_slots[0].u.flags |= 0x40;
            sub_000A2CC0(0, 0x10000000);
            e->state = 0x14;
            return 1;
        }
        sub_000A2CA0(0, 0x10000000);
        e->state++;
        break;
    case 11:
        if (sub_000D9A70(0x11B)) {
            sub_000A42F0(0, 1);
            sub_0001B3F0(aa0_slots[0].obj);
            aa0_slots[0].u.flags |= 0x40;
            sub_000A2CC0(0, 0x10000000);
            sub_000D9AB0(0xCD);
            e->state = 0x14;
            return 1;
        }
        break;
    case 0x14:
        e->flags = 0;
        e->state = 0;
        return 0;
    }
    return 1;
}

/* Apply f(g, v) to the eight groups 0x10..0x17. */
#define R6G_GROUPS8(f, v) \
    f(0x10, v); f(0x11, v); f(0x12, v); f(0x13, v); \
    f(0x14, v); f(0x15, v); f(0x16, v); f(0x17, v)

/* 0x000B3760: event handler: unless event bit 0xF3 is set (then it finishes),
   switch the eight groups 0x10..0x17 on or off every frame according to event
   bit 0xBF. Message 0 resets, 1 starts, 3 stops. Returns 0 when finished. */
int r6g_EvtGroupsByBit(int msg, R6gEvt *e)
{
    if (msg == 0) {
        e->flags = 0;
        e->state = 0;
        e->frames = 0;
        return 1;
    }
    if (msg == 1) {
        e->flags |= 1;
        e->frames = 0;
        e->state = 10;
        return 1;
    }
    if (msg == 3) {
        e->flags = 0;
        e->state = 0x14;
    }
    e->frames++;
    if (e->state == 10) {
        if (sub_000D9A70(0xF3)) {
            e->state = 0x14;
            return 1;
        }
        if (sub_000D9A70(0xBF)) {
            R6G_GROUPS8(sub_000A4410, 1);
            R6G_GROUPS8(sub_000A2D10, 0x20);
            R6G_GROUPS8(sub_000A2CA0, 0x10000000);
        } else {
            R6G_GROUPS8(sub_000A4410, 0);
            R6G_GROUPS8(sub_000A2D40, 0x20);
            R6G_GROUPS8(sub_000A2CC0, 0x10000000);
        }
    } else if (e->state == 0x14) {
        e->flags = 0;
        e->state = 0;
        return 0;
    }
    return 1;
}

/* 0x000AFE00: event script: set event bit 0xDD, wait a frame, start camera
   move 1 and wait for it, wait two seconds, start camera move 3 and wait for
   it, clear bit 0xDD and finish. Message 0 resets, 1 starts, 3 stops.
   Returns 0 when finished. */
int r6g_EvtCameraPan(int msg, R6gEvt *e)
{
    if (msg == 0) {
        e->flags = 0;
        e->state = 0;
        return 1;
    }
    if (msg == 1) {
        e->flags |= 1;
        e->state = 10;
        return 1;
    }
    if (msg == 3) {
        e->flags = 0;
        e->state = 0;
        return 0;
    }
    switch (e->state) {
    case 10:
        sub_000D9AB0(0xDD);
        e->state++;
        break;
    case 11:
    case 16:
        e->state++;
        break;
    case 12:
        sub_000A42F0(0, 1);
        e->state++;
        break;
    case 14:
        e->state++;
        e->frames = R6G_FTOI(a50_framesPerSecond * 2.0f);
        break;
    case 15:
        if (--e->frames == 0)
            e->state++;
        break;
    case 17:
        sub_000A42F0(0, 3);
        e->state++;
        break;
    case 13:
    case 18:
        if (sub_000A4370(0))
            e->state++;
        break;
    case 19:
        sub_000D9B30(0xDD);
        e->state++;
        break;
    case 20:
        e->flags = 0;
        e->state = 0;
        return 0;
    }
    return 1;
}
