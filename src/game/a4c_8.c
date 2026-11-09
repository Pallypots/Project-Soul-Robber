/* Area a4c, group 8: mode dispatch, flag bit sets, shutdown 0x00046CF0..0x0004BA20. Names inferred. */
#include "a4c.h"

/* 0x00046CF0: run the update for the current mode (0..2), then draw the shared buffer. */
void a4c_ModeUpdate3(void)
{
    switch (a4c_mode3DF1EC) {
    case 0: sub_00043EE0(); break;
    case 1: sub_00044B90(); break;
    case 2: sub_000450F0(); break;
    }
    sub_0003FCE0(a4c_buf2B4D84 + a4c_g3DFA5C);
}
/* 0x00046D50: run the second update for the current mode (0..1), then draw the shared buffer. */
void a4c_ModeUpdate2(void)
{
    switch (a4c_mode3DF1EC) {
    case 0: sub_00045480(); break;
    case 1: sub_000459E0(); break;
    }
    sub_0003FCE0(a4c_buf2B4D84 + a4c_g3DFA5C);
}
/* 0x00049470: shut down sound subsystems. */
void a4c_SoundShutdown(void)
{
    sub_0019AE90();
    sub_00049000();
    sub_00049250();
    sub_00047FB0();
    sub_000483D0();
}
/* 0x00049AA0: set flag bit i (16..79). */
void a4c_FlagSetA(unsigned int i)
{
    if (i < 0x10 || i > 0x4F) for (;;) ;
    a4c_flagsA[i >> 5] |= 1u << (i & 0x1F);
}
/* 0x00049AD0: test flag bit i (16..79). */
uint32_t a4c_FlagTestA(unsigned int i)
{
    if (i < 0x10 || i > 0x4F) for (;;) ;
    return a4c_flagsA[i >> 5] & (1u << (i & 0x1F));
}
/* 0x00049B00: set flag bit i (3..49). */
void a4c_FlagSetB(unsigned int i)
{
    if (i < 3 || i >= 0x32) for (;;) ;
    i -= 3;
    a4c_flagsB[i >> 5] |= 1u << (i & 0x1F);
}
/* 0x00049B40: test flag bit i (3..49). */
uint32_t a4c_FlagTestB(unsigned int i)
{
    if (i < 3 || i >= 0x32) for (;;) ;
    i -= 3;
    return a4c_flagsB[i >> 5] & (1u << (i & 0x1F));
}
/* 0x0004BA20: reset systems and the 4-word state, then start the fade object. */
void a4c_ResetAndFade(void)
{
    sub_00039650();
    sub_00037130();
    a4c_state3E0000[0] = 2;
    a4c_state3E0000[1] = 0;
    a4c_state3E0000[2] = 0;
    a4c_state3E0000[3] = 0;
    sub_00072EE0(a4c_obj428F40, 0, 8.0f, 0);
}
