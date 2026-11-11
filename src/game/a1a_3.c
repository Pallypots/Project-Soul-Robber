/* Area a1a, group 3: render-thread lock wrappers and device state setters. Names inferred. */
#include "a1a.h"

/* 0x001A52F0: leave the render lock. */
void a1a_Unlock(void) { RtlLeaveCriticalSection(a1a_renderLock); }
/* 0x001A5300: enter the render lock. */
void a1a_Lock(void) { RtlEnterCriticalSection(a1a_renderLock); }

/* 0x001A5380: set word 0x40B0EC. */
void a1a_Set40B0EC(int v) { a1a_g40B0EC = v; }
/* 0x001A5390: get word 0x40B0EC. */
int a1a_Get40B0EC(void) { return a1a_g40B0EC; }

/* 0x001A53A0: library call on handle 0x40B0E4. */
int a1a_Call_1A53A0(void) { return sub_001BCEF9(a1a_g40B0E4); }

/* 0x001A53B0: while the device is busy, pump it (mode 8 or 2 by flag bit 0). */
void a1a_Pump_1A53B0(int flags)
{
    if (sub_001D76A0(4) == 0)
        return;
    do {
        sub_001BD0D6((flags & 1) ? 8 : 2, 1);
    } while (sub_001D76A0(4) != 0);
}

/* 0x001A6C90: set device stage 6 under the lock. */
void a1a_SetStage6(const float *v)
{
    RtlEnterCriticalSection(a1a_renderLock);
    sub_001D2CF0(6, v);
    RtlLeaveCriticalSection(a1a_renderLock);
}

/* 0x001A6CC0: set device stage 0 under the lock. */
void a1a_SetStage0(const float *v)
{
    RtlEnterCriticalSection(a1a_renderLock);
    sub_001D2CF0(0, v);
    RtlLeaveCriticalSection(a1a_renderLock);
}

/* 0x001A6CF0: set device stage 1 to the object's +0x130 block under the lock. */
void a1a_SetStage1(uint8_t *o)
{
    RtlEnterCriticalSection(a1a_renderLock);
    sub_001D2CF0(1, o + 0x130);
    RtlLeaveCriticalSection(a1a_renderLock);
}

/* 0x001A6D20: set dirty bit 0x2000 and store value under the lock. */
void a1a_SetDirty2000(int v)
{
    RtlEnterCriticalSection(a1a_renderLock);
    a1a_g1E2148 |= 0x2000;
    a1a_g1E24C0 = v;
    RtlLeaveCriticalSection(a1a_renderLock);
}

/* 0x001A6D60: set float 0x361AE0. */
void a1a_SetF361AE0(float f) { a1a_f361AE0 = f; }

/* 0x001A6E40: enable or disable device feature under the lock. */
void a1a_Enable_1A6E40(int on)
{
    RtlEnterCriticalSection(a1a_renderLock);
    if (on) {
        sub_001D55A0(1);
        RtlLeaveCriticalSection(a1a_renderLock);
        return;
    }
    sub_001D55A0(0);
    RtlLeaveCriticalSection(a1a_renderLock);
}

/* 0x001A7270: get word 0x40AECC. */
int a1a_Get40AECC(void) { return a1a_g40AECC; }

/* 0x001A73F0: fetch two 64-byte blocks and pass them on. */
void a1a_Combine_1A73F0(void *p)
{
    uint8_t b[0x40];
    uint8_t a[0x40];
    sub_001D2E10(0, a);
    sub_001D2E10(1, b);
    sub_001E522D(p, a, b);
}

/* 0x001A7620: set word 0x40AEC8. */
void a1a_Set40AEC8(int v) { a1a_g40AEC8 = v; }
/* 0x001A7630: get word 0x40AEC8. */
int a1a_Get40AEC8(void) { return a1a_g40AEC8; }
