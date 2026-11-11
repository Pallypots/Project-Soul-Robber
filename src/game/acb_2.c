/* Area acb, group 2: boss manager / menu glue 0x000E7630-0x000F6A80. Names inferred. */
#include "acb.h"

/* 0x000F4120: boss HUD step: tail into 0x00180930 when +0xA8 set and +0xB0 clear, else clear +0xB0. */
void acb_BossHudStep(void)
{
    AcbBossMgr *m = g_acb_bossMgr;
    if (m == 0) for (;;) ;
    if (m->v104 == 2) return;
    if (m->wA8 != 0 && m->wB0 == 0) { sub_00180930(); return; }
    m->wB0 = 0;
}
/* 0x000F4160: call 0x00181D20 unless state 2 or +0xA8 clear. */
void acb_BossHud_F4160(void)
{
    AcbBossMgr *m = g_acb_bossMgr;
    if (m == 0) for (;;) ;
    if (m->v104 != 2 && m->wA8 != 0) sub_00181D20();
}
/* 0x000F4190: call 0x0017D590 unless state 2 or +0xA8 clear. */
void acb_BossHud_F4190(void)
{
    AcbBossMgr *m = g_acb_bossMgr;
    if (m == 0) for (;;) ;
    if (m->v104 != 2 && m->wA8 != 0) sub_0017D590();
}
/* 0x000F4A00: set boss manager +0x100 to 2. */
void acb_BossMgrSet100(void) { g_acb_bossMgr->v100 = 2; }

/* 0x000F69A0: queue damage on the current boss. */
void acb_BossDamage(float dmg)
{
    AcbBossMgr *m = sub_000FE3D0();
    sub_000F3BF0(m->sub8C, dmg, 1);
}
/* 0x000F69C0: boss manager short +0xAA. */
int16_t acb_BossGetAA(void) { return ((AcbBossMgr *)sub_000FE3D0())->wAA; }
/* 0x000F69D0: boss manager float +0x54. */
float acb_BossGet54(void) { return ((AcbBossMgr *)sub_000FE3D0())->f54; }
/* 0x000F6A80: player state is 4 or 5. */
int acb_PlayerState45(void)
{
    int s = PlayerObj_GetState((PlayerObj *)&g_stats);
    if (s == 4 || s == 5) return 1;
    return 0;
}

/* 0x000EC010: play sound 0x30A and open menu 5. */
void acb_OpenMenu5(void) { sub_00048AF0(0x30A); sub_000A34B0(0, 5, 0); }
/* 0x000EC1E0: play sound 0x30A and open menu 4. */
void acb_OpenMenu4(void) { sub_00048AF0(0x30A); sub_000A34B0(0, 4, 0); }
/* 0x000EC070: 0x0017C460(0). */
void acb_17C460Off(void) { sub_0017C460(0); }
/* 0x000EC1D0: 0x0017C460(1). */
void acb_17C460On(void) { sub_0017C460(1); }
/* 0x000EC1A0: 0x00183320(0). */
void acb_183320Off(void) { sub_00183320(0); }
/* 0x000EC1B0: 0x00183320(1). */
void acb_183320On(void) { sub_00183320(1); }
/* 0x000EBD60: forward second argument to 0x000FE630. */
int acb_Fwd_FE630(int unused, int v) { return sub_000FE630(v); }
/* 0x000EBD80: forward second argument to 0x00100370. */
int acb_Fwd_100370(int unused, int v) { return sub_00100370(v); }
/* 0x000EBDA0: forward second argument to 0x000FBD20. */
int acb_Fwd_FBD20(int unused, int v) { return sub_000FBD20(v); }
/* 0x000ED350: call the installed hook, if any. */
void acb_CallHook(void) { if (g_acb_hook) g_acb_hook(); }
/* 0x000ED360: hook argument when a hook is installed, else 0. */
int acb_HookArg(void) { return g_acb_hook ? g_acb_hookArg : 0; }
/* 0x000EDA10: run 0x00174540 then 0x00166DD0. */
void acb_Run_EDA10(void) { sub_00174540(); sub_00166DD0(); }
/* 0x000E8BB0: set global float 0x003F4B38. */
void acb_Set3F4B38(float f) { g_acb_3F4B38 = f; }
/* 0x000E7630: clear global 0x003F57BC. */
void acb_Clear3F57BC(void) { g_acb_3F57BC = 0; }
/* 0x000EED80: clear global 0x003F60F0. */
void acb_Clear3F60F0(void) { g_acb_3F60F0 = 0; }
/* 0x000EFB80: zero float +0x10C. */
void acb_Zero10C(AcbF10C *o) { o->f10C = 0.0f; }
