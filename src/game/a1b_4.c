/* Area a1b, group 4: manager accessors and menu actions near 0x00019000..0x0001B130. Names inferred. */
#include "a1b.h"

/* 0x00019000: set mode and clear both selections. */
void a1b_MgrSetMode(A1bMgr *m, int32_t mode) { m->mode12BC = mode; m->sel27C = -1; m->sel284 = -1; }
/* 0x00019020: get mode. */
int32_t a1b_MgrGetMode(A1bMgr *m) { return m->mode12BC; }
/* 0x000192B0: set value 0x12C0. */
void a1b_MgrSetV(A1bMgr *m, int32_t v) { m->v12C0 = v; }
/* 0x0001AE70: reset timer and set period. */
void a1b_TimerStart(A1bTimer *t, int32_t p) { t->t108 = 0; t->t10C = 0; t->t110 = p; }
/* 0x0001AE90: reset timer. */
void a1b_TimerReset(A1bTimer *t) { t->t10C = 0; t->t108 = 0; }
/* 0x0001AEB0: action then close. */
void a1b_Act_1AEB0(void) { a60_Set3E74B8(); sub_00048AF0(1); }
/* 0x0001AF10: trigger 0xF4 and 0xF5 then close. */
void a1b_Act_1AF10(void) { sub_000D9AB0(0xF4); sub_000D9AB0(0xF5); sub_00048AF0(1); }
/* 0x0001AF30: trigger 0xF4 and 0xF8 then close. */
void a1b_Act_1AF30(void) { sub_000D9AB0(0xF4); sub_000D9AB0(0xF8); sub_00048AF0(1); }
/* 0x0001AF50: set stat 4 to 2 then close. */
void a1b_Act_1AF50(void) { Stats_Set(&g_stats, 4, 2); sub_00048AF0(1); }
/* 0x0001B0E0: add 30 to stat 1, notify, then close. */
void a1b_Act_1B0E0(void) { sub_000D1E10(&g_stats, 1, 30); sub_00023D80(2, 30); sub_00048AF0(1); }
/* 0x0001B110: close and set cheat bit 0. */
void a1b_Cheat1(void) { sub_00048AF0(1); g_cheatFlags |= 1; }
/* 0x0001B130: close and set cheat bit 1. */
void a1b_Cheat2(void) { sub_00048AF0(1); g_cheatFlags |= 2; }
