/* Area a19, 0x001984A0-0x0019BEC4. Names inferred. */
#include "a19.h"

/* 0x001984A0: release work block: clear its first field, detach it. */
int a19_DetachWork(void *unused, a19_Actor *a)
{
    a->work->f0 = 0;
    a->work = 0;
    return 1;
}

/* 0x001987E0 */
void a19_Apply2ClearWork8(void *obj, a19_Actor *a)
{
    sub_00189DA0(obj, a, 2);
    a->work->f8 = 0;
}

/* 0x001997D0 */
void a19_Store402760(void)
{
    a19_g402760 = sub_001AB610();
}

/* 0x001997E0: remember b, forward to 0x001AB3D0. */
int a19_Forward1AB3D0(int a, int b)
{
    a19_g402758 = b;
    return sub_001AB3D0(a, b);
}

/* 0x00199800 */
void a19_Set402764(int v) { a19_g402764 = v; }
/* 0x00199810 */
int a19_Get402764(void) { return a19_g402764; }
/* 0x00199820 */
void a19_Set402768(int v) { a19_g402768 = v; }
/* 0x00199830 */
void a19_Set402770(int v) { a19_g402770 = v; }
/* 0x00199840 */
void a19_Set402774(int v) { a19_g402774 = v; }

/* 0x00199AE0: record i (0..15) at 0x00401B4C, else 0. */
int a19_GetRec401B4C(int i)
{
    if (i < 0 || i >= 16)
        return 0;
    return a19_g401B4C[i].f0;
}

/* 0x0019A460: record i (0..44) at 0x00401D98, else 0. */
int a19_GetRec401D98(int i)
{
    if (i < 0 || i >= 45)
        return 0;
    return a19_g401D98[i].f0;
}

/* 0x0019A580: byte +8 of 18-byte table entry i. */
int a19_GetTblB8(int i) { return a19_g32C930[i].b8; }
/* 0x0019A590: byte +9 of 18-byte table entry i. */
int a19_GetTblB9(int i) { return a19_g32C930[i].b9; }

/* 0x0019A930 */
int a19_GetRec4019D8(int i)
{
    if (i < 0 || i >= 3)
        return 0;
    return a19_g4019D8[i].f0;
}

/* 0x0019A9B0: clear record i at 0x004019D8. */
void a19_ClearRec4019D8(int i)
{
    if (i >= 0) {
        a19_g4019D8[i].f8 = 0;
        a19_g4019D8[i].f0 = 0;
        a19_g4019D8[i].f5C = 0;
    }
}

/* 0x0019AAA0 */
void a19_InitAll19AA00(void)
{
    int i;
    for (i = 0; i < 3; i++)
        sub_0019AA00(i, 0x22);
    a19_g401B28 = 0;
}

/* 0x0019B9A0: 0x0019AEA0 with default parameters. */
int a19_Call19AEA0Default(int a)
{
    return sub_0019AEA0(a, 0x80, 0x5A, 0x7F, 0x80, 0x80);
}

/* 0x0019B9D0 */
int a19_Get402F9C(void) { return g_402F9C; }
/* 0x0019B9E0 */
void a19_Inc402FA8(void) { g_402FA8++; }
/* 0x0019BA00 */
int a19_Get402FA8(void) { return g_402FA8; }
/* 0x0019BA10 */
void a19_Set402FC4(int v) { g_402FC4 = v; }
/* 0x0019BA20 */
uint8_t a19_Get41314A(void) { return a19_g41314A; }
/* 0x0019BA30 */
uint8_t a19_Get41314B(void) { return a19_g41314B; }

/* 0x0019BE50: swap in a new value, return the old one. */
int a19_Exchange402F94(int v)
{
    int old = a19_g402F94;
    a19_g402F94 = v;
    return old;
}

/* 0x0019BE60: 1 if any of mask's bits are set in 0x00413174. */
int a19_TestAny413174(uint32_t mask) { return (a19_g413174 & mask) != 0; }
/* 0x0019BE70: 1 if all of mask's bits are set. */
int a19_TestAll413174(uint32_t mask) { return (a19_g413174 & mask) == mask; }
/* 0x0019BE90 */
void a19_Set413174(uint32_t mask) { a19_g413174 |= mask; }
/* 0x0019BEB0 */
void a19_Clear413174(uint32_t mask) { a19_g413174 &= ~mask; }

