/* Area acb, group 3: small globals and helpers 0x000E0230-0x000E3380. Names inferred. */
#include "acb.h"

/* 0x000E0230: field +4 of record i in the 32-byte table. */
int acb_TableGet4(int i) { return ((AcbRec32 *)g_acb_table)[i].v04; }
/* 0x000E0250: table header field +0x58. */
int acb_TableGet58(void) { return ((AcbTableHdr *)g_acb_table)->v58; }
/* 0x000E03C0: global 0x003EDD24. */
int acb_Get3EDD24(void) { return g_acb_3EDD24; }
/* 0x000E03D0: global 0x003EDD38. */
int acb_Get3EDD38(void) { return g_acb_3EDD38; }
/* 0x000E0630: clear globals 0x003F0748/0x003F074C. */
void acb_Clear3F0748(void) { g_acb_3F0748 = 0; g_acb_3F074C = 0; }
/* 0x000E0770: address of global 0x003F0758. */
int *acb_Addr3F0758(void) { return &g_acb_3F0758; }
/* 0x000E0780: clear global 0x003F0A78. */
void acb_Clear3F0A78(void) { g_acb_3F0A78 = 0; }
/* 0x000E1040: mark the object's +0x30 target with -1. */
void acb_ClearTarget30(AcbObj30 *o) { if (o) o->t30->v08 = -1; }
/* 0x000E3370: global 0x003F0A78. */
int acb_Get3F0A78(void) { return g_acb_3F0A78; }
/* 0x000E3380: global 0x003F0A7C. */
int acb_Get3F0A7C(void) { return g_acb_3F0A7C; }
