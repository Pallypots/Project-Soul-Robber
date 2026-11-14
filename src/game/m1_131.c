/* Area m1, file 131: small helpers. Names inferred. */
#include <stdint.h>

extern int32_t m1_resA3E4B30[2];
extern int32_t m1_resB3E4B20[2];
extern int32_t m1_resC3E4740[4];
extern int32_t m1_resD3E4B28[2];
extern int32_t m1_res3E4B1C;
void sub_001B9FC0(int h);
void sub_00053880(int h);
void sub_0004F5D0(int id);

/* 0x00058B40: release the title-screen resources: free every held handle (-1 = none) in the
 * three pairs and the singles, free the 0x3E474C block, and unload files 0xD1 and 0xA0. */
void m1_TitleFree058B40(void)
{
    int i;
    m1_res3E4B1C = 0;
    for (i = 0; i < 2; i++) {
        if (m1_resA3E4B30[i] != -1) {
            sub_001B9FC0(m1_resA3E4B30[i]);
            m1_resA3E4B30[i] = -1;
        }
        if (m1_resB3E4B20[i] != -1) {
            sub_001B9FC0(m1_resB3E4B20[i]);
            m1_resB3E4B20[i] = -1;
        }
        if (m1_resC3E4740[i] != -1) {
            sub_001B9FC0(m1_resC3E4740[i]);
            m1_resC3E4740[i] = -1;
        }
    }
    if (m1_resC3E4740[2] != -1) {
        sub_001B9FC0(m1_resC3E4740[2]);
        m1_resC3E4740[2] = -1;
    }
    if (m1_resD3E4B28[0] != -1) {
        sub_001B9FC0(m1_resD3E4B28[0]);
        m1_resD3E4B28[0] = -1;
    }
    if (m1_resD3E4B28[1] != -1) {
        sub_001B9FC0(m1_resD3E4B28[1]);
        m1_resD3E4B28[1] = -1;
    }
    sub_00053880(m1_resC3E4740[3]);
    sub_0004F5D0(0xD1);
    sub_0004F5D0(0xA0);
}

extern int32_t m1_sl37FB40, m1_sl37FB44, m1_sl37FB48, m1_sl37FB4C, m1_sl37FB60, m1_sl37FB6C;
extern float m1_sl37FB64;

/* 0x000261A0: panel slide request (as 0xE8920 on 0x37FB40): mode 1 records the argument and
 * opens it (from states 0 and 2: state 1, step 3, target 2; from 3 only clears +0x20), mode 0
 * closes it (from state 1 mirroring the position 20 - x, or from state 3). */
void m1_PanelSlide0261A0(int mode, int arg)
{
    switch (mode) {
    case 0:
        switch (m1_sl37FB40) {
        case 1:
            m1_sl37FB64 = 20.0f - m1_sl37FB64;
            m1_sl37FB40 = 2;
            m1_sl37FB44 = 0;
            return;
        case 3:
            m1_sl37FB60 = 0;
            m1_sl37FB40 = 2;
            m1_sl37FB44 = 0;
            return;
        }
        return;
    case 1:
        m1_sl37FB6C = arg;
        switch (m1_sl37FB40) {
        case 0:
            m1_sl37FB40 = 1;
            m1_sl37FB44 = 3;
            m1_sl37FB48 = 2;
            m1_sl37FB4C = 0;
            m1_sl37FB60 = 0;
            return;
        case 2:
            m1_sl37FB40 = 1;
            m1_sl37FB44 = 3;
            m1_sl37FB48 = 2;
            m1_sl37FB4C = 0;
            return;
        case 3:
            m1_sl37FB60 = 0;
            return;
        }
        return;
    }
}
