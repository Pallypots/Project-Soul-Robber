/* Area m1, file 12: tail-call thunks. Names inferred. */
#include "a8c.h"
#include "a19.h"

void sub_001A7940(void);

/* 0x0003DD20: forwards to 0x102FA0 (empty release stub). */
void m1_ReleaseThunk3DD20(void)
{
    a8c_Release102FA0();
}

/* 0x0019B690: forwards to 0x19AEA0 with all six arguments. */
int m1_Thunk19B690(int a, int b, int c, int d, int e, int f)
{
    return sub_0019AEA0(a, b, c, d, e, f);
}

/* 0x001A7B90: forwards to 0x1A7940. */
void m1_Thunk1A7B90(void)
{
    sub_001A7940();
}
