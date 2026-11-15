/* Area m2, file gs2: security-cookie functions (compiled with /GS). Names inferred. */
#include <stdint.h>

typedef struct M2Spr2 { uint8_t unk00[0x24]; uint32_t flags24; uint8_t unk28[0x1C]; void *h44; uint8_t unk48[0x54]; } M2Spr2;
typedef struct M2Hud2 { uint8_t unk00[0x968]; uint8_t layout968[0x20]; void *res988; } M2Hud2;
extern int a1b_i3816D0;
extern M2Hud2 *r1_hud;
extern uint32_t m1_wipe381400[0xB1];
extern const char *m2_names2826FC[2];
extern void *m2_h3813E8[2];
extern void *r1b_handles3813F4[2];
extern const char *m2_name282710;
extern void *m2_bank3816C8;
extern M2Spr2 m2_spr381454[4];
extern const char *m2_fmt282714;
extern int r1b_v3816CC;
extern int r1_curHudId;
void  m1_SndBank0243B0(int a, int b);
void  sub_000252A0(int a, int b);
void  aab_Add24D30(int a, int b);
void  r1g_CounterRequest(int a, int b);
void  sub_000253D0(int a, int b);
int   a5b_GetVideoMode(void);
int   m1_FileBusy04F6D0(int id);
int   m1_FileSize04F680(int id);
void *a50_Alloc(int heap, int size, int a, int b);
void  r1e_MovieStartA(int id, void *mem);
int   sub_0004F4D0(void);
int   sub_00053CA0(int a);
void *m1_PathOp53D70(const char *name);
void *sub_00084C00(void *h, int a);
void  r1d_AnimBankFixup(void *bank);
void  r1e_SpriteInit(M2Spr2 *s, void *bank, void *h);
void  r1b_StepperSet(M2Spr2 *s, int a, int b, int c, int d);
int   sub_00038070(int a);
void  m1_Stub102FA0();
void  sub_00075F00(M2Hud2 *h);
void  sub_0003FAB0(void *layout, M2Hud2 *h);
const char *a50_GetVideoModeName(void);
int   a6b_Printf3(char *buf, int size, const char *fmt, ...);
void *a50_Sub53D50(const char *path, int a);
void  r1b_ApplyLayout(void *layout, int a);
void  r1_HudSelect(void);
void  sub_00023BC0(int a);
void  sub_000325A0(int a);

/* 0x2CC20: HUD start-up step: 0 resets the sound banks and counters, 2 starts the intro movie for the video mode, 3 waits for loading, 100 allocates the HUD and clears the wipe table, 101 (when ready) loads the HUD sprite banks and layout, builds the four HUD sprites and selects the HUD (state 10000). Returns 1 until finished. Security-cookie function. */
int m2_HudStartup2CC20(void) {
    char path[0x80];
    int i, k;
    switch (a1b_i3816D0) {
    case 0:
        m1_SndBank0243B0(0, 0);
        m1_SndBank0243B0(0, 0);
        sub_000252A0(0, 0);
        aab_Add24D30(0, 0);
        r1g_CounterRequest(0, 0);
        sub_000253D0(0, 0);
        a1b_i3816D0 = 2;
        break;
    case 2:
        k = a5b_GetVideoMode() + 0xC3;
        if (m1_FileBusy04F6D0(k) == 0) r1e_MovieStartA(k, a50_Alloc(4, m1_FileSize04F680(k), 0, 0));
        a1b_i3816D0 = 3;
        break;
    case 3:
        if (sub_0004F4D0() == 0) a1b_i3816D0 = 100;
        break;
    case 100:
        r1_hud = (M2Hud2 *)a50_Alloc(4, 0x98C, 0, 0);
        for (i = 0; i < 0xB1; i++) m1_wipe381400[i] = 0;
        a1b_i3816D0 = 101;
    case 101:
        if (sub_00053CA0(1) != 0) break;
        for (i = 0; i < 2; i++) {
            m2_h3813E8[i] = m1_PathOp53D70(m2_names2826FC[i]);
            r1b_handles3813F4[i] = sub_00084C00(m2_h3813E8[i], 0);
        }
        m2_bank3816C8 = m1_PathOp53D70(m2_name282710);
        r1d_AnimBankFixup(m2_bank3816C8);
        r1e_SpriteInit(&m2_spr381454[0], m2_bank3816C8, r1b_handles3813F4[0]);
        m2_spr381454[0].h44 = r1b_handles3813F4[1];
        r1b_StepperSet(&m2_spr381454[0], 0, 0, 0, 0);
        m2_spr381454[1] = m2_spr381454[0];
        m2_spr381454[2] = m2_spr381454[0];
        m2_spr381454[3] = m2_spr381454[0];
        *(uint32_t volatile *)&m2_spr381454[1].flags24 |= 4;
        *(uint32_t volatile *)&m2_spr381454[2].flags24 |= 4;
        r1b_v3816CC = sub_00038070(1);
        m1_Stub102FA0();
        sub_00075F00(r1_hud);
        sub_0003FAB0(r1_hud->layout968, r1_hud);
        a6b_Printf3(path, 0x7F, m2_fmt282714, a50_GetVideoModeName(), a50_GetVideoModeName());
        r1_hud->res988 = a50_Sub53D50(path, 0);
        r1b_ApplyLayout(r1_hud->layout968, 0);
        r1_curHudId = -1;
        r1_HudSelect();
        sub_00023BC0(1);
        sub_000325A0(0);
        a1b_i3816D0 = 10000;
        break;
    }
    return a1b_i3816D0 != 10000;
}
