/* Area m1, /GS file 8: printf-style text front ends. Names inferred. */
#include <stdarg.h>
#include "m1.h"

/* 0x0002E8C0: format the text (up to 0x3FF chars) and draw it via 0x2E560 at scale (1, 2). */
int m1_DrawTextf2E8C0(int a1, int a2, int a3, int a4, int a5, int a6, const char *fmt, ...)
{
    va_list ap;
    char buf[0x400];
    va_start(ap, fmt);
    sub_0007DAF0(buf, 0x3FF, fmt, &ap);
    va_end(ap);
    return sub_0002E560(a1, a2, a3, a4, a5, a6, 1.0f, 2.0f, buf);
}

/* 0x0003E4B0: format the text (up to 0xFF chars) and draw it as "[text]" through 0x2E8C0,
 * with the 4th draw argument taken from *0x2C4B08. */
int m1_DrawTagf3E4B0(int a1, int a2, int a3, int a4, int a5, const char *fmt, ...)
{
    va_list ap;
    char buf[0x100];
    va_start(ap, fmt);
    sub_0007DAF0(buf, 0xFF, fmt, &ap);
    va_end(ap);
    return m1_DrawTextf2E8C0(a1, a2, a3, *m1_pg2C4B08, a4, a5, m1_strFmtBracket266FB0, buf);
}


/* 0x0003E610: format a menu line (up to 0xFF chars) and draw it through 0x2E8C0 as
 * "%c%s" with a '+' marker when marked (a7) or ' ' otherwise; colour is the
 * selected or normal entry of *0x2C4B08 (a6). */
int m1_DrawMenuLinef3E610(int a1, int a2, int a3, int a4, int a5, int selected, int marked,
                          const char *fmt, ...)
{
    va_list ap;
    char buf[0x100];
    int colour;
    va_start(ap, fmt);
    sub_0007DAF0(buf, 0xFF, fmt, &ap);
    ap = 0;
    colour = selected ? m1_pg2C4B08[2] : m1_pg2C4B08[1];
    return m1_DrawTextf2E8C0(a1, a2, a3, colour, a4, a5, m1_fmtItem266FC8,
                             marked ? '+' : ' ', buf);
}
