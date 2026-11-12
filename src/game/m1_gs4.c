/* Area m1, /GS file 4: message text loaders. Names inferred. */
#include "m1.h"

/* 0x000E0010: load world message/event<lang>.bms for the current area. */
int m1_LoadEventBmsE0010(void)
{
    char path[0x100];
    sub_0007E070(path, 0xFF, m1_fmtEvent2775D4, m1_worldA41316C, m1_worldB413170, sub_00052A10());
    m1_eventBms417868 = sub_00037570(path, 0x40);
    return 0;
}

/* 0x000E0070: load world message/talk<lang>.bms for the current area. */
int m1_LoadTalkBmsE0070(void)
{
    char path[0x100];
    sub_0007E070(path, 0xFF, m1_fmtTalk277604, m1_worldA41316C, m1_worldB413170, sub_00052A10());
    m1_talkBms41786C = sub_00037570(path, 0x40);
    return 0;
}

/* 0x000E00D0: in world 0, areas 6..8 (the shops), load the shop talk text. */
int m1_LoadShopBmsE00D0(void)
{
    char path[0x100];
    int32_t b;
    if (m1_worldA41316C != 0)
        return 0;
    b = m1_worldB413170;
    if (b < 6)
        return 0;
    if (b > 8)
        return 0;
    sub_0007E070(path, 0xFF, m1_fmtShop277634, sub_00052A10(), sub_00052A10());
    m1_shopBms417874 = sub_00037570(path, 0x40);
    return 0;
}
