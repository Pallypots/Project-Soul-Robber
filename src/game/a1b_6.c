/* Area a1b, group 6: globals and flags near 0x00022260..0x0002CC00. Names inferred. */
#include "a1b.h"

/* 0x00022260: call sub_0001F6C0 with an extra zero argument. */
void *a1b_Call1F6C0(int a, int b, int c, int d) { return sub_0001F6C0(a, b, c, d, 0); }
/* 0x00022750: set enable; when cleared call sub_000226B0. */
void a1b_SetOn(int32_t on) { a1b_on37C4C0 = on; if (!on) sub_000226B0(); }
/* 0x00022770: get enable. */
int32_t a1b_GetOn(void) { return a1b_on37C4C0; }
/* 0x00022780: set a blend value and its complement. */
void a1b_SetBlend(float v)
{
    a1b_f37C4D8 = v;
    a1b_f37C4EC = v;
    a1b_f37C4E4 = 224.0f - v;
}
/* 0x00022900: filter x through sub_000227B0 when enabled. */
void *a1b_Filter(void *x) { if (a1b_on37C4C0) return sub_000227B0(x); return x; }
/* 0x00022980: clear four values when state is 10000. */
void a1b_ResetIf10000(void)
{
    if (a1b_state3813B4 == 10000) {
        a1b_i37F0CC = 0; a1b_i37F0E0 = 0; a1b_i37F0F0 = 0; a1b_i37FA9C = 0;
    }
}
/* 0x00023BC0: set (1), clear (0) or toggle (2) flag bit 0. */
void a1b_SetFlag0(uint32_t mode)
{
    if (mode > 2) for (;;) ;
    if (mode == 2) mode = ~a1b_flags37C4F8 & 1;
    if (mode == 0) a1b_flags37C4F8 &= ~1u;
    else if (mode == 1) a1b_flags37C4F8 |= 1;
}
/* 0x00023BF0: get flag bit 0. */
int a1b_GetFlag0(void) { return a1b_flags37C4F8 & 1; }
/* 0x00026280: set the pair. */
void a1b_SetPair2(int32_t a, int32_t b) { a1b_i37C570 = a; a1b_i37C574 = b; }
/* 0x000264C0: when flag bit 0 is set and event 0xF0 is not, raise 0x37FA9C. */
void a1b_Check264C0(void)
{
    if ((a1b_flags37C4F8 & 1) && !sub_000D9A70(0xF0)) a1b_i37FA9C = 1;
}
/* 0x00026840: set byte. */
void a1b_SetByte(uint8_t v) { a1b_b37D45C = v; }
/* 0x0002C790: clear state. */
void a1b_Clear3816D0(void) { a1b_i3816D0 = 0; }
/* 0x0002CC00: call sub_001A1130 then sub_0002C7A0. */
void a1b_Call2CC00(void *a) { sub_001A1130(a); sub_0002C7A0(); }

