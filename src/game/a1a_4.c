/* Area a1a, group 4: movie helpers and hook message handlers. Names inferred. */
#include "a1a.h"

/* 0x001A7870: call 0x1A5560 with mode 0. */
void a1a_Mode0_1A7870(int v) { sub_001A5560(v, 0); }
/* 0x001A7880: call 0x1A5560 with mode 1. */
void a1a_Mode1_1A7880(int v) { sub_001A5560(v, 1); }

/* 0x001A7F90: close the open file/stream if active. */
void a1a_Close_1A7F90(void)
{
    if (a1a_b40B144) {
        a1a_b40B144 = 0;
        sub_001BC060(a1a_g40F124, a1a_g40B150);
        sub_0022F0E0(a1a_g40B148);
        a1a_g40B148 = 0;
    }
}

/* 0x001A7FD0: active flag. */
int a1a_IsActive_1A7FD0(void) { return a1a_b40B144 != 0; }

/* 0x001A7FE0: on odd ticks call 0x22EF40 and count; returns the counter. */
int a1a_Tick_1A7FE0(void)
{
    if (a1a_g40B20C & 1) {
        sub_0022EF40(a1a_g40B148);
        a1a_g40B13C++;
    }
    a1a_g40B20C++;
    return a1a_g40B13C;
}

/* 0x001A80C0: get counter 0x40B13C. */
int a1a_Get40B13C(void) { return a1a_g40B13C; }

/* 0x001A8580: message 2 installs a hook. */
int a1a_MsgAddHook(int msg, A1aHook h, int b)
{
    if (msg == 2)
        a1a_AddHook(h, b);
    return 0;
}

/* 0x001A85A0: message 2 removes a hook slot. */
int a1a_MsgRemoveHook(int msg, int slot)
{
    if (msg == 2)
        a1a_RemoveHook(slot);
    return 0;
}

/* 0x001A85D0: message 2 clears the device callback; returns 1 if it was set. */
int a1a_MsgClearCb(int msg)
{
    int old;
    if (msg != 2)
        return 0;
    sub_001D2E90(0);
    old = a1a_g40B880;
    a1a_g40B880 = 0;
    return old == 1;
}

/* 0x001A8600: message 2 installs a1a_RunHooks as device callback; returns 1 if newly set. */
int a1a_MsgSetCb(int msg)
{
    int old;
    if (msg != 2)
        return 0;
    sub_001D2E90(a1a_RunHooks);
    old = a1a_g40B880;
    a1a_g40B880 = 1;
    return old != 1;
}

/* 0x001A8630: library call (v, -1, 0, 4). */
void *a1a_Wait_1A8630(int v) { return sub_001BD517(v, -1, 0, 4); }

/* 0x001A8650: init block 0x40B858 and clear state words. */
void a1a_Init_1A8650(void)
{
    sub_001BD59E(a1a_g40B858);
    a1a_g40B848 = 0;
    a1a_g40B84C = 0;
    a1a_g40B850 = 0;
    a1a_g40B854 = 0;
    a1a_g40B87C = 0;
}
