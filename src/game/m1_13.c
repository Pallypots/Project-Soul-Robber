/* Area m1, file 13: empty stubs and tiny helpers. Names inferred. */

void sub_000FD5F0(void);

/* 0x000F8D30: empty stub. */
void m1_StubF8D30(void)
{
}

/* 0x00102FA0: empty debug/release stub (called with varying arguments). */
void m1_Stub102FA0(void)
{
}

/* 0x001A7C00: returns a 64-bit zero (EDX:EAX). */
__int64 m1_Zero64_1A7C00(void)
{
    return 0;
}

/* 0x000FD8F0: forwards to 0xFD5F0. */
void m1_ThunkFD8F0(void)
{
    sub_000FD5F0();
}

int sub_001BD792(void);
int sub_001BD749(void);

/* 0x001A88B0: 1 when the XDK query returns 3 and flag 0x40 is clear. */
int m1_Check1A88B0(void)
{
    if (sub_001BD792() == 3) {
        if (sub_001BD749() & 0x40)
            return 0;
        return 1;
    }
    return 0;
}
