/* Area m1, file 326: player camera/control mode switch. Names inferred. */
#include <stdint.h>

typedef struct M1PlMode {
    uint8_t  unk000[0xD4];
    int32_t  modeD4;          /* +0x0D4 */
    uint8_t  unk0D8[0x150 - 0xD8];
    uint32_t flags150;        /* +0x150 */
    uint8_t  unk154[0x1B8 - 0x154];
    int32_t  bank1B8;         /* +0x1B8 */
    uint8_t  unk1BC[0xFD8 - 0x1BC];
    void    *objFD8;          /* +0xFD8 */
} M1PlMode;

extern uint8_t  m1_stats41FEC0[];
extern uint32_t aa0_flags420010;
extern void    *m1_scene2_42C8EC;
extern const char m1_strChjh1_276DBC[];   /* "chjh1" */
void  abc_SetStateB(void *o, int s);
void  m1_SndPlay023D80(int a, int b);
void  m1_SndBank0243B0(int a, int b);
void  m1_PlAct0CF490(void *s, int a);
void  sub_000CF3F0(void *s, int a, int b);
void  m1_StatsTick0D1930(void *s);
void  sub_000C5B10(void);
void  m1_StatsTick0D1930b(void *s);   /* alias of 0x0D1930 */
void  abc_SetStateBb(void *o, int s);    /* alias of 0x0BD4D0 */
void  sub_000C5B10b(void);                /* alias of 0x0C5B10 */
void  m1_SndPlay023D80b(int a, int b);    /* alias of 0x023D80 */
void  m1_SceneFade0D4C10(void *s);
void  m1_SceneCam0D45B0(void *s, int a, int b, float c);
void  sub_000BC6F0(const char *name, int k);
void  m1_BoneEntsClearKeptCE970(void);
void  m1_MarkJackEntriesCEF60(void);
void *m1_ObjBone01D290(void *o, int k);
void  m1_BoneRelease0CED50(void *b);

/* 0x0D2A50: switch the player to mode (0..5): set the matching state and sound bank,
   remember the mode, reset the scene camera when no bank is set, and for banks 0..1
   reload the "chjh1" bone set. */
void m1_PlSetMode0D2A50(M1PlMode *pl, int mode) {
    volatile int k;
    if (pl->flags150 & 0x80000)
        return;
    switch (mode) {
    case 0:
        if (!(pl->flags150 & 0x80000807))
            abc_SetStateB(pl, 6);
        m1_SndPlay023D80(0, 0);
        m1_SndBank0243B0(0, pl->bank1B8);
        break;
    case 1:
        if (!(pl->flags150 & 0x80000807))
            abc_SetStateB(pl, 7);
        m1_SndPlay023D80(1, 0);
        m1_SndBank0243B0(1, pl->bank1B8);
        break;
    case 2:
        aa0_flags420010 |= 4;
        m1_PlAct0CF490(m1_stats41FEC0, 0);
        break;
    case 3:
        sub_000CF3F0(m1_stats41FEC0, 4, 0);
        if (!(pl->flags150 & 0x80000007))
            abc_SetStateB(pl, 7);
        m1_SndPlay023D80(1, 0);
        m1_SndBank0243B0(1, pl->bank1B8);
        break;
    case 4:
        m1_StatsTick0D1930(m1_stats41FEC0);
        abc_SetStateB(m1_stats41FEC0, 1);
        sub_000C5B10();
        m1_SndPlay023D80(1, 0);
        m1_SndBank0243B0(1, pl->bank1B8);
        break;
    case 5:   /* same as case 4; the alias names keep cl from merging the two bodies */
        m1_StatsTick0D1930b(m1_stats41FEC0);
        abc_SetStateBb(m1_stats41FEC0, 1);
        sub_000C5B10b();
        m1_SndPlay023D80b(1, 0);
        m1_SndBank0243B0(1, pl->bank1B8);
        break;
    }
    pl->modeD4 = mode;
    if (!pl->bank1B8 && !(pl->flags150 & 0x800)) {
        m1_SceneFade0D4C10(m1_scene2_42C8EC);
        m1_SceneCam0D45B0(m1_scene2_42C8EC, 0, 0, -1.0f);
    }
    if ((uint32_t)pl->bank1B8 <= 1) {
        k = mode;
        if (mode)
            k = 1;
        sub_000BC6F0(m1_strChjh1_276DBC, k);
        m1_BoneEntsClearKeptCE970();
        m1_MarkJackEntriesCEF60();
        m1_BoneRelease0CED50(m1_ObjBone01D290(pl->objFD8, 0));
    }
}
