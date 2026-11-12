/* Area m1, file 22: sound idle check. Names inferred. */

int  sub_0019A1D0(int bank);
int  sub_0019A900(int i);
void sub_001AB860(void);

/* 0x00047950: 1 (after calling 0x1AB860) when banks 3,4,9,5,6,8 are all idle
 * and none of channels 0..2 is busy; otherwise 0. */
int m1_AllIdle47950(void)
{
    int i;
    if (sub_0019A1D0(3) || sub_0019A1D0(4) || sub_0019A1D0(9) ||
        sub_0019A1D0(5) || sub_0019A1D0(6) || sub_0019A1D0(8))
        return 0;
    for (i = 0; i < 3; i++) {
        if (sub_0019A900(i) > 0)
            return 0;
    }
    sub_001AB860();
    return 1;
}

