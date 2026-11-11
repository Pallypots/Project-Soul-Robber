/* Area r4d: timers, file and render-state helpers around 0x001A6E80-0x001A96BC (r4d_8). Names inferred. */
#include "r4d.h"

/* 0x001A7280: under the render lock, send 13 dwords from p+0x40 and 17 from p to the GPU. Stack arg (p). */
void r4d_RenderUpload(uint8_t *p)
{
    RtlEnterCriticalSection(g_renderLock);
    sub_001D24F0(0x0D, (int)(intptr_t)(p + 0x40));
    sub_001D2680(0x11, p, 0x0C);
    RtlLeaveCriticalSection(g_renderLock);
}

/* 0x001A7890: forward to 0x001A5F50 with b=1. Stack arg (o); calls 0x001A5F50 with ECX=o. */
void r4d_Call1A5F50(void *o)
{
    sub_001A5F50(o, 1);
}

/* 0x001A8720: start the performance timer with no length. No inputs. */
void r4d_TimerStart(void)
{
    int64_t now;
    sub_001BD59E(&r4d_timerFreq40B858);
    sub_001BD58D(&now);
    r4d_timerStart40B848 = now;
    r4d_timerOn40B87C = 1;
}

/* 0x001A8770: start the performance timer for ms milliseconds. Stack arg (ms). */
void r4d_TimerStartMs(int ms)
{
    int64_t now;
    sub_001BD59E(&r4d_timerFreq40B858);
    sub_001BD58D(&now);
    r4d_timerStart40B848 = now;
    r4d_timerLen40B850 = (int64_t)ms * r4d_timerFreq40B858 / 1000;
}

/* 0x001A8860: read the whole file at 0x0027B658 into buf; 0 on success, -1 if it cannot be opened. Stack arg (buf). */
int r4d_LoadFile(void *buf)
{
    uint32_t n, size;
    void *h = sub_001BCD0D(r4d_path27B658, 0x80000000u, 0, 0, 4, 0x80, 0);
    if (h == (void *)-1)
        return -1;
    size = sub_001BCCD2(h, 0);
    sub_001BC813(h, buf, size, &n, 0);
    sub_001BC6FD(h);
    return 0;
}

/* 0x001A8920: read the system clock into six words. Stack args (year month day hour minute second). */
void r4d_GetDateTime(uint16_t *year, uint16_t *month, uint16_t *day, uint16_t *hour, uint16_t *minute, uint16_t *second)
{
    R4dSysTime t;
    sub_001BDD62(&t);
    *year = t.year;
    *month = t.month;
    *day = t.day;
    *hour = t.hour;
    *minute = t.minute;
    *second = t.second;
}

/* 0x001A9630: 7 when the selected pad (a=0: current, else the other one) is present and c is 1 or 2, else 0.
   Stack args (a unused c). */
int r4d_PadCheck(int a, int unused, int c)
{
    int idx;
    (void)unused;
    if (a) {
        idx = r4d_padSel3650C8 != 1;
    } else {
        idx = r4d_padSel3650C8;
        if (idx < 0)
            return 0;
    }
    if (!r4d_pads40B9A4[idx].fD0)
        return 0;
    switch (c) {
    case 1: case 2:
        return 7;
    }
    return 0;
}

/* 0x001A9680: 6 when the selected pad (a=0: current, else the other one) is present, else 0. Stack arg (a). */
int r4d_PadPresent(int a)
{
    int idx;
    if (a) {
        idx = r4d_padSel3650C8 != 1;
    } else {
        idx = r4d_padSel3650C8;
        if (idx < 0)
            return 0;
    }
    return r4d_pads40B9A4[idx].fD0 ? 6 : 0;
}
