/* Area m1, file 215: tail-call thunks into the libraries. Names inferred. */
#include "shared_decls.h"

int  sub_001BD50A(void);            /* XAPI: current thread */
void sub_001D2ED0(void);            /* D3D: device helper, no arguments */

/* 0x001AD6A0: forwards to SwitchToThread (0x1BD332). */
int m1_YieldThunk1AD6A0(void)
{
    return SwitchToThread();
}

/* 0x001AD560: forwards to 0x1BD50A (the current thread). */
int m1_CurThreadThunk1AD560(void)
{
    return sub_001BD50A();
}

/* 0x001A53F0: forwards to the D3D helper at 0x1D2ED0. */
void m1_D3dHelperThunk1A53F0(void)
{
    sub_001D2ED0();
}

/* 0x001AB850: forwards to the XACT helper at 0x223F9C. */
void m1_XactHelperThunk1AB850(void)
{
    sub_00223F9C();
}
