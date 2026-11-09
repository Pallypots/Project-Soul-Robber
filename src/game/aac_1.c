/* Area aac, group 1: render-state setters, small globals and lock wrappers (0x1A3F50-0x1AAA00). Names inferred. */
#include "aac.h"

/* 0x001A5B90: write device register 0x40304 and cache it, under the render lock. */
void aac_SetReg40304(int v)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D4350(0x40304, v);
    aac_g1E243C = v;
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A6C60: set render state 0x16 under the render lock. */
void aac_SetState16(int v)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D2490(0x16, v);
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A6EE0: set render state 0x18 under the render lock. */
void aac_SetState18(int v)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D2490(0x18, v);
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A6F10: write device register 0x40300 and cache it, under the render lock. */
void aac_SetReg40300(int v)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D4350(0x40300, v);
    aac_g1E2440 = v;
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A6F50: write device register 0x40340 and cache it, under the render lock. */
void aac_SetReg40340(int v)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D4350(0x40340, v);
    aac_g1E2444 = v;
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A7230: clear the target (flags 0x80, z 1.0) under the render lock. */
void aac_ClearStencil(void)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D6ED0(0, 0, 0x80, 0, 1.0f, 0);
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A8760: clear word 0x40B87C. */
void aac_Clear40B87C(void) { aac_g40B87C = 0; }

/* 0x001A8820: library call forwarder. */
int aac_Call_1A8820(int a, int b) { return sub_001E543D(a, b); }
/* 0x001A8830: library call forwarder. */
int aac_Call_1A8830(int a, int b) { return sub_001E4DA4(a, b); }
/* 0x001A8840: library call forwarder with the middle arguments swapped. */
int aac_Call_1A8840(int a, int b, int c, int d) { return sub_001E5571(a, c, b, d); }

/* 0x001A87D0: map the library's mode 3..6 to 4,2,3,5; anything else is 1. */
int aac_MapMode(void)
{
    switch (sub_001BD5B2()) {
    case 1: return 1;
    case 2: return 1;
    case 3: return 4;
    case 4: return 2;
    case 5: return 3;
    case 6: return 5;
    }
    return 1;
}

/* 0x001A8A40: an id is current. */
int aac_HasCurrentId(void) { return aac_g3650C8 != -1; }

/* 0x001A8A50: move the current id to previous and clear it. */
void aac_RetireCurrentId(void)
{
    aac_g3650CC = aac_g3650C8;
    aac_g3650C8 = -1;
}

/* 0x001A8A70: set word 0x40BE18, resetting through 0x79340 when it changes to 0. */
void aac_Set40BE18(int v)
{
    if (aac_g40BE18 != v && v == 0)
        sub_00079340();
    aac_g40BE18 = v;
}
/* 0x001A8A90: get word 0x40BE18. */
int aac_Get40BE18(void) { return aac_g40BE18; }

/* 0x001A91F0: reset the ids and initialise the two library blocks. */
int aac_InitIds(void)
{
    aac_g3650C8 = -1;
    aac_g3650CC = -1;
    sub_0025942D(2, aac_g3650D0);
    sub_001A8AA0(aac_g40B9A4);
    return 0;
}

/* 0x001A96C0: store three words. */
void aac_SetTriple(int a, int b, int c)
{
    aac_g40C03C = a;
    aac_g40BF20 = b;
    aac_g40C028 = c;
}

/* 0x001A96E0: copy a string into buffer 0x40C040. */
void aac_SetPath40C040(const char *s)
{
    char *d = aac_g40C040;
    while ((*d++ = *s++) != 0)
        ;
}
/* 0x001A9700: copy a string into buffer 0x40C044. */
void aac_SetStr40C044(const char *s)
{
    char *d = aac_g40C044;
    while ((*d++ = *s++) != 0)
        ;
}
/* 0x001A9720: copy a string into buffer 0x40C02C. */
void aac_SetStr40C02C(const char *s)
{
    char *d = aac_g40C02C;
    while ((*d++ = *s++) != 0)
        ;
}

/* 0x001A9740: set word 0x40BF24. */
void aac_Set40BF24(int v) { aac_g40BF24 = v; }

/* 0x001A9750: free bytes available on the drive named by buffer 0x40C040, 0 on failure. */
uint64_t aac_GetFreeBytes(void)
{
    uint64_t avail, total, freeb;
    if (sub_001BDFF2(aac_g40C040, &avail, &total, &freeb) == 0)
        return 0;
    return avail;
}

/* 0x001A9C00: position-weighted byte checksum, inverted. */
uint32_t aac_Checksum(const uint8_t *p, uint32_t n)
{
    uint32_t sum = 0, i = 1;
    for (; n != 0; n--) {
        sum += p[i - 1] * i;
        i++;
    }
    return ~sum;
}

/* 0x001AA1D0: library call forwarder. */
int aac_Call_1AA1D0(int a) { return sub_001BD587(a); }
/* 0x001AA1E0: enter a critical section. */
void aac_EnterCs(void *cs) { RtlEnterCriticalSection(cs); }
/* 0x001AA1F0: leave a critical section. */
void aac_LeaveCs(void *cs) { RtlLeaveCriticalSection(cs); }

/* 0x001AA520: call 0x1AA3E0(a, 1) while holding handle 0x40C858. */
int aac_Locked_1AA520(int a)
{
    int r;
    sub_001BD1CC(aac_g40C858, (uint32_t)-1);
    r = sub_001AA3E0(a, 1);
    sub_001BCFF2(aac_g40C858);
    return r;
}

/* 0x001AA550: call 0x1AA4D0(a, b) while holding handle 0x40C858. */
int aac_Locked_1AA550(int a, int b)
{
    int r;
    sub_001BD1CC(aac_g40C858, (uint32_t)-1);
    r = sub_001AA4D0(a, b);
    sub_001BCFF2(aac_g40C858);
    return r;
}

/* 0x001AA950: raise flag 0x40E6A8 unless mode is 1 or 2. */
void aac_RaiseFlag(void)
{
    if (aac_g40E348 != 1 && aac_g40E348 != 2)
        aac_g40E6A8 = 1;
}

/* 0x001AA9D0: unless mode is 1 or 2, drop flag 0x40E6A8 and post message 2. */
void aac_DropFlag(void)
{
    if (aac_g40E348 != 1 && aac_g40E348 != 2) {
        aac_g40E6A8 = 0;
        sub_00222726(aac_g40C868, aac_g40E350, 2, 0);
    }
}

/* 0x001AAA00: forward the second argument with handles 0x40C868/0x40E300 (first argument unused). */
int aac_Forward_1AAA00(int unused, int b)
{
    (void)unused;
    return sub_0022275D(aac_g40C868, aac_g40E300, b);
}
