/* Area m1, file 8: init sequences. Names inferred. */
#include "m1h.h"

/* 0x00052840: initialise 17 of the 19 lock objects at 0x42C7C0 (slots 9 and 13 are not
 * touched here) in the original order; returns its argument. */
void *m1_InitLocks52840(void *arg)
{
    sub_001B29F0(&m1_locks42C7C0[1]);
    sub_001B29F0(&m1_locks42C7C0[15]);
    sub_001B29F0(&m1_locks42C7C0[5]);
    sub_001B29F0(&m1_locks42C7C0[18]);
    sub_001B29F0(&m1_locks42C7C0[11]);
    sub_001B29F0(&m1_locks42C7C0[17]);
    sub_001B29F0(&m1_locks42C7C0[6]);
    sub_001B29F0(&m1_locks42C7C0[16]);
    sub_001B29F0(&m1_locks42C7C0[7]);
    sub_001B29F0(&m1_locks42C7C0[12]);
    sub_001B29F0(&m1_locks42C7C0[3]);
    sub_001B29F0(&m1_locks42C7C0[8]);
    sub_001B29F0(&m1_locks42C7C0[14]);
    sub_001B29F0(&m1_locks42C7C0[4]);
    sub_001B29F0(&m1_locks42C7C0[10]);
    sub_001B29F0(&m1_locks42C7C0[2]);
    sub_001B29F0(&m1_locks42C7C0[0]);
    return arg;
}

/* 0x00048590: stop stream 500, reset the sound game state, stop channels
 * 1,2,3,4,9,5,6,8, release ids 3,4,9,5,6,8, then 0x19AAA0. */
void m1_SoundReset48590(void)
{
    sub_00047BF0(0x1F4);
    sub_000E3BA0(sub_000E0770());
    sub_000E0810(sub_000E0770());
    sub_0019A6A0(1);
    sub_0019A6A0(2);
    sub_0019A6A0(3);
    sub_0019A6A0(4);
    sub_0019A6A0(9);
    sub_0019A6A0(5);
    sub_0019A6A0(6);
    sub_0019A6A0(8);
    sub_0019A0E0(3);
    sub_0019A0E0(4);
    sub_0019A0E0(9);
    sub_0019A0E0(5);
    sub_0019A0E0(6);
    sub_0019A0E0(8);
    sub_0019AAA0();
}
