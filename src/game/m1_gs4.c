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

/* 0x000E0150: in world 0, areas 0..2, load message/quiz<lang>.bms. */
int m1_LoadQuizBmsE0150(void)
{
    char path[0x100];
    if (m1_worldA41316C != 0)
        return 0;
    if (m1_worldB413170 > 2)
        return 0;
    sub_0007E070(path, 0xFF, m1_fmtQuiz277660, m1_worldA41316C, m1_worldB413170, sub_00052A10());
    m1_quizBms417870 = sub_00037570(path, 0x40);
    return 0;
}

/* 0x000E05B0: load logic_lgc/event.lgc, run 0xDFED0, then set state 4 if missing, 2 if loaded. */
int m1_LoadEventLgcE05B0(void)
{
    char path[0x100];
    sub_0007E070(path, 0xFF, m1_fmtEventLgc277690, m1_worldA41316C, m1_worldB413170);
    m1_eventLgc417864 = sub_00037570(path, 0x40);
    sub_000DFED0();
    m1_lgcState3F0734 = (m1_eventLgc417864 == 0) * 2 + 2;
    return 0;
}

/* 0x000E0700: load logic/rubber.rbp; keep the file and a pointer past its 16-byte header. */
int m1_LoadRubberE0700(void)
{
    char path[0x100];
    sub_0007E070(path, 0xFF, m1_fmtRubber2776C0, m1_worldA41316C, m1_worldB413170);
    m1_rubber3F0748 = sub_00037550(path, 0);
    m1_rubberBody3F074C = m1_rubber3F0748 + 0x10;
    return 0;
}

/* 0x000E0DD0: load mbattle/message/mb<n>0<lang>.bms; hangs on a bad language index. */
void *m1_LoadMbBmsE0DD0(int lang, int n)
{
    char path[0x100];
    if (lang >= 8)
        for (;;) ;
    sub_0007E070(path, 0x100, m1_fmtMb277744, n, m1_langTab317CF0[lang]);
    return sub_00037550(path, 0);
}
