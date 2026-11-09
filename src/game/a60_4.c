/* Area a60, group 4: 0x00077000..0x0007FFFF. Names inferred. */
#include "a60.h"

/* 0x00077220: start channel ch (0 or 1) streaming source arg. */
void a60_ChannelStart(int ch, int arg)
{
    int v, id;
    switch (ch) {
    case 0: v = 9; break;
    case 1: v = 10; break;
    default: return;
    }
    sub_001A85D0(v);
    if (a60_chId[ch] < 0) {
        id = sub_001A8580(v, arg, -1);
        a60_chId[ch] = id;
        if (id < 0)
            return;
    }
    a60_chFlags[ch] |= 0x300;
    *a60_chReg660[ch] |= 0x100;
    *a60_chReg660[ch] |= 0x200;
    sub_001A8600(v);
}

/* 0x000772B0: stop channel ch (0 or 1). */
void a60_ChannelStop(int ch)
{
    int v;
    switch (ch) {
    case 0: v = 9; break;
    case 1: v = 10; break;
    default: return;
    }
    sub_001A85D0(v);
    if (a60_chId[ch] >= 0) {
        sub_001A85A0(v, a60_chId[ch]);
        a60_chId[ch] = -1;
        a60_chFlags[ch] &= ~0x300;
        *a60_chReg660[ch] &= ~0x100u;
        *a60_chReg660[ch] &= ~0x200u;
    }
}

/* 0x00077330: clear bit 7 of the channel and return its 16-bit level. */
uint16_t a60_ChannelLevel(int ch)
{
    a60_chFlags[ch] &= ~0x80;
    *a60_chReg660[ch] &= ~0x80u;
    return (uint16_t)*a60_chReg650[ch];
}

/* 0x00077360: set the channel's 16-bit level. */
void a60_ChannelSetLevel(int ch, uint16_t v)
{
    uint32_t *r = a60_chReg650[ch];
    *r = (*r & 0xFFFF0000u) | v;
}

/* 0x00077380: set bits 0xC00 in the channel control word. */
void a60_ChannelSetC00(int ch) { *a60_chReg660[ch] |= 0xC00; }

/* 0x00077410: shut down the screen and free its resources. */
void a60_Shutdown77410(void)
{
    int i;
    a60_v3E7398 = 0;
    for (i = 0; i < 2; i++)
        if (a60_h3E7500[i] != -1) { sub_001B9FC0(a60_h3E7500[i]); a60_h3E7500[i] = -1; }
    if (a60_h3E69F0 != -1) { sub_001B9FC0(a60_h3E69F0); a60_h3E69F0 = -1; }
    if (a60_h3E69F4 != -1) { sub_001B9FC0(a60_h3E69F4); a60_h3E69F4 = -1; }
    sub_00053880(a60_p3E6A04);
    sub_0004F5D0(sub_000529F0() + 0xBC);
    sub_0004F5D0(0xB8);
}

/* 0x000774D0: setter. */
void a60_Set3E7A4C(int v) { a60_v3E7A4C = v; }

/* 0x000774E0: 0 when the screen is in state 10000, else -1. */
int a60_IsReady774E0(void) { return (a60_v3E7398 == 10000) - 1; }

/* 0x00077A30: initialise the screen's counters and four lists. */
void a60_Init77A30(void)
{
    a60_v3E7538 = a60_h3E7500[0];
    a60_v3E7530 = 2;
    a60_v3E7508 = 0;
    a60_v3E750C = 0xF2;
    a60_v3E7510 = 0;
    a60_v3E7514 = 0;
    sub_000150B0(a60_buf3E75F4, 2);
    sub_000150B0(a60_buf3E7690, 3);
    sub_000150B0(a60_buf3E772C, 0x1B);
    sub_000150B0(a60_buf3E77C8, 5);
}

/* 0x00077EA0: latch newly pressed buttons on 4 pads; 0x800 if any pad pressed START. */
int a60_PollPressed(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        uint32_t old = a60_pad3E7540[i];
        uint32_t cur = sub_001A9130(i);
        uint32_t n = (cur ^ old) & cur;
        a60_pad3E7540[i] = n;
        if (n & 0x800)
            return 0x800;
    }
    return 0;
}

/* 0x00078110: pump the loader until it reports done. */
void a60_WaitLoad78110(void)
{
    sub_0019B9E0();
    sub_00048590();
    while (sub_00047950() != 1)
        sub_000580D0();
    sub_0019B9F0();
}

/* 0x00078140: set flag. */
void a60_Set3E74B8(void) { a60_v3E74B8 = 1; }

/* 0x000792F0: reset the movie player. */
void a60_MovieReset(void)
{
    a60_v3E7A54 = 0;
    a60_v3E7A50 = 0;
    a60_v3E83E4 = 0;
    a60_v3E83E0 = 0;
    a60_v3E83E8 = 0;
    sub_0003FAB0(a60_anim3E7A58, &a60_flags3E7A78);
    sub_00018620(a60_anim3E7A58, 0x14);
    a60_FlagBit2(&a60_flags3E7A78, 1);
}

/* 0x00079340: stop the movie. */
void a60_MovieStop(void)
{
    a60_v3E83E0 = 1;
    a60_v3E7A54 = 0;
    a60_v3E7A50 = 0;
    a60_v3E83E4 = 0;
    sub_0019BEB0(0x10);
}

/* 0x00079460: movie state value. */
int a60_MovieState(void)
{
    return a60_v3E83E4 > 0 ? a60_v3E7A50 : a60_v3E7A54;
}

/* 0x00079B30: forward the second argument. */
void a60_Forward79B30(int unused, int v) { sub_00052840(v); }

/* 0x00079FD0: copy the name of entry id, and its save block if present. */
void a60_LoadEntry(int id)
{
    const char *s;
    char *d;
    a60_name3E9298[0] = 0;
    s = sub_000133E0(id);
    d = a60_name3E9298;
    while ((*d++ = *s++) != 0) ;
    if (sub_00013480(id))
        a60_save3E83F0 = a60_save4326A0;
    else
        a60_save3E83F0.w[0] = 0;
}
