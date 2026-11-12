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
