/* Area m1, file 2 (compiled with /GS: the original uses the stack cookie). */
#include "m1.h"

/* 0x00053D70: format a path from `name` and the current mode (0x00052A10),
 * then pass it to 0x00037570 with 0x40. */
void m1_PathOp53D70(const char *name)
{
    char buf[0x80];
    sub_0007E0A0(buf, name, sub_00052A10());
    sub_00037570(buf, 0x40);
}

/* 0x00053ED0: format a path the same way, then load that file into dst. */
void m1_LoadFmt53ED0(const char *name, void *dst)
{
    char buf[0x80];
    sub_0007E0A0(buf, name, sub_00052A10());
    sub_00053E20(buf, dst);
}

/* 0x00065A50: build a file name from a number with the format at 0x2DDCCC
 * and load it into the work block at offset 0x40080. */
void m1_LoadNum65A50(int n)
{
    char buf[0x40];
    sub_0007E0A0(buf, m1_fmt2DDCCC, n);
    sub_00053E20(buf, a60_work42C5E8 + 0x40080);
}

/* 0x00053DC0: format a path (as 0x53D70), hand it to 0x4F580, then run 0x4F4E0 and 0x4F6F0. */
void m1_LoadRun53DC0(const char *name, int arg)
{
    char buf[0x80];
    sub_0007E0A0(buf, name, sub_00052A10());
    sub_0004F580_m1(buf, arg);
    sub_0004F4E0();
    sub_0004F6F0();
}
