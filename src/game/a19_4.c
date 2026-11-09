/* Area a19, 0x0019C4B0-0x0019FFD6. Names inferred. */
#include "a19.h"

/* 0x0019C4B0: reset session state. */
void a19_SessionRestart(void)
{
    g_402F9C = 0;
    g_402780 = 0;
    sub_00052A20();
    Session_Reset();
    sub_0019C350();
}

/* 0x0019C5E0 */
void a19_Set336DD0(int v) { a19_g336DD0 = v; }

/* 0x0019D100: 0x001A1130(a), then Clock_Set402FC0(30). */
void a19_Start1A1130(int a)
{
    sub_001A1130(a);
    Clock_Set402FC0(30);
}

/* 0x0019D450 */
void a19_Set337498(int v) { a19_g337498 = v; }

/* 0x0019D6B0: close handle 0x00402FF4 and invalidate both handles. */
void a19_CloseHandle402FF4(void)
{
    sub_001AA310(a19_g402FF4);
    a19_g402FF4 = -1;
    a19_g402FF0 = -1;
    sub_001AD520();
}

/* 0x0019D8A0 */
void a19_Set402FE8(int v) { a19_g402FE8 = v; }

/* 0x0019D8C0 */
void a19_Signal402FE4(void)
{
    a19_g402FE4 = 1;
    sub_0019E810(0);
}

/* 0x0019E970 */
void a19_Set403004_403120(float a, float b)
{
    a19_g403004 = a;
    a19_g403120 = b;
}

/* 0x0019FEE0 */
int a19_Get40396C(void) { return a19_g40396C; }
/* 0x0019FFC0 */
int a19_Get403974(void) { return a19_g403974; }
/* 0x0019FFD0 */
int a19_Get403940(void) { return a19_g403940; }

/* 0x00198070 */
void a19_Run196D30_197CE0(void)
{
    sub_00196D30();
    sub_00197CE0();
}

/* 0x0019AE90 */
void a19_Run199B50_19A6F0_19AE00(void)
{
    sub_00199B50();
    sub_0019A6F0();
    sub_0019AE00();
}

