/* Area aec, group 2: table lookups and command handlers 0x000E9BC0-0x000EC1C0. Names inferred. */
#include "aec.h"

/* 0x000E9BC0: table 0x0031852C lookup with bounds asserts. */
int aec_Lookup31852C(int row, int col)
{
    if (row > 6) for (;;) ;
    while (sub_000E0CD0(col) >= sub_000E0C80(row)) ;
    return aec_tbl31852C[row][sub_000E0CD0(col)];
}
/* 0x000E9C00: table 0x00318548 lookup with bounds asserts. */
int aec_Lookup318548(int row, int col)
{
    if (row > 6) for (;;) ;
    while (sub_000E0D30(col) >= sub_000E0CF0(row)) ;
    return aec_tbl318548[row][sub_000E0D30(col)];
}
/* 0x000E9C40: table 0x00318564 lookup with bounds asserts. */
int aec_Lookup318564(int row, int col)
{
    if (row > 6) for (;;) ;
    if (col >= 8) for (;;) ;
    return aec_tbl318564[row][col];
}
/* 0x000EA220: clear +0x32C and post event 4. */
void aec_EA220(AecObj *o)
{
    if (o == 0) return;
    o->v32C = 0;
    sub_000E0A80(o, 4, o->v00, o->v314, 0);
}
/* 0x000EA250: command: 0x000E3EB0 with five args. */
void aec_CmdE3EB0(void *ctx, AecCmd *c)
{
    if (c) sub_000E3EB0(c->vC, c->v10, c->v14, c->v18, c->v1C);
}
/* 0x000EA280: command: 0x000E0840(w0C, w0E, data). */
void aec_CmdE0840(void *ctx, AecCmdW *c)
{
    if (c) sub_000E0840(c->wC, c->wE, c->data);
}
/* 0x000EA3A0: forward to 0x000CEEA0. */
void aec_EA3A0(void) { sub_000CEEA0(); }
/* 0x000EA3B0: forward to 0x000CEF00. */
void aec_EA3B0(void) { sub_000CEF00(); }
/* 0x000EA6C0: post event 4 with command value. */
void aec_CmdEvent4(AecObj *o, AecCmd *c)
{
    if (o && c) sub_000E0A80(o, 4, o->v00, o->v314, c->vC);
}
/* 0x000EA7B0: dispatch on record kind 3 or 6. */
void aec_EA7B0(int *p)
{
    if (p == 0) return;
    switch (*p) {
    case 3: sub_000F6F00(p); break;
    case 6: sub_001060B0(p); break;
    }
}
/* 0x000EA8C0: command: 0x000E1350 then 0x000E1520. */
void aec_CmdE1350(AecObj *o, AecCmdW *c)
{
    if (o && c) {
        sub_000E1350(o, c->wC, c->data, 0);
        sub_000E1520(o, c->wC, c->wE);
    }
}
/* 0x000EAE20: command: 0x000E1F60(o, vC, v10). */
void aec_CmdE1F60(AecObj *o, AecCmd *c)
{
    if (o && c) sub_000E1F60(o, c->vC, c->v10);
}
/* 0x000EAEA0: command: free +0x3B0[vC]. */
void aec_CmdFree3B0(AecObj *o, AecCmd *c)
{
    void *p;
    if (c && o) {
        p = o->a3B0[c->vC];
        if (p) { sub_00033A70(p); o->a3B0[c->vC] = 0; }
    }
}
/* 0x000EAFA0: command: free +0x330[vC]. */
void aec_CmdFree330(AecObj *o, AecCmd *c)
{
    void *p;
    if (c && o) {
        p = o->a330[c->vC];
        if (p) { sub_000EC670(p); o->a330[c->vC] = 0; }
    }
}
/* 0x000EAFE0: command: 0x000D2A00(vC). */
void aec_CmdD2A00(void *ctx, AecCmd *c)
{
    if (c) sub_000D2A00(c->vC);
}
/* 0x000EB040: command: 0x000E4950 with milliseconds converted to seconds. */
void aec_CmdE4950(void *o, AecCmd *c)
{
    if (c && o) sub_000E4950(o, (float)c->v14 * 0.001f, c->v18, c->vC, c->v10);
}
/* 0x000EB1D0: command: 0x000E1C80 with milliseconds converted to seconds. */
void aec_CmdE1C80(void *o, AecCmd *c)
{
    if (c && o) sub_000E1C80(o, (float)c->vC * 0.001f);
}
/* 0x000EB600: set +0x998 to 1. */
void aec_Set998(uint8_t *o) { if (o) *(int32_t *)(o + 0x998) = 1; }
/* 0x000EB620: set +0x998 to 0. */
void aec_Clear998(uint8_t *o) { if (o) *(int32_t *)(o + 0x998) = 0; }
/* 0x000EBBF0: actor (3,1) component 5 +0x154 = 1. */
void aec_EBBF0(void) { ((AecComp5 *)sub_0001D960(sub_000E23F0(3, 1), 5))->v154 = 1; }
/* 0x000EBC10: actor (3,1) component 5 +0x154 = 0. */
void aec_EBC10(void) { ((AecComp5 *)sub_0001D960(sub_000E23F0(3, 1), 5))->v154 = 0; }
/* 0x000EBD50: forward to 0x000FE5A0. */
void aec_EBD50(void) { sub_000FE5A0(); }
/* 0x000EBD70: forward to 0x001002E0. */
void aec_EBD70(void) { sub_001002E0(); }
/* 0x000EBD90: forward to 0x000FBCA0. */
void aec_EBD90(void) { sub_000FBCA0(); }
/* 0x000EBED0: forward to 0x000F4120 (boss HUD step). */
void aec_EBED0(void) { sub_000F4120(); }
/* 0x000EBEE0: forward to 0x000F4160. */
void aec_EBEE0(void) { sub_000F4160(); }
/* 0x000EBEF0: forward to 0x000F4190. */
void aec_EBEF0(void) { sub_000F4190(); }
/* 0x000EC030: forward to 0x001790F0. */
void aec_EC030(void) { sub_001790F0(); }
/* 0x000EC1C0: forward to 0x00179140. */
void aec_EC1C0(void) { sub_00179140(); }
/* 0x000EC040: actor (3,7) component 5 handle +0x10C to 0x0017FFB0. */
void aec_EC040(void)
{
    AecComp5 *c = (AecComp5 *)sub_0001D960(sub_000E23F0(3, 7), 5);
    if (c->v10C >= 0) sub_0017FFB0(c->v10C);
}
