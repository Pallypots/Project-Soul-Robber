/* Area a80, group 3: mode table, flag words and object accessors. Names inferred. */
#include "a80.h"

/* 0x00087AE0: get word 0x3ED25C. */
int32_t a80_Get3ED25C(void) { return a80_g3ED25C; }
/* 0x00087AF0: any of the low two flag bits set. */
int a80_AnyLowFlags(void) { return (a80_flags3ED258 & 3) != 0; }
/* 0x00087B90: set flag 0x200000. */
void a80_SetFlag200000(void) { a80_flags3ED258 |= 0x200000; }
/* 0x00087BA0: set flag 0x10000. */
void a80_SetFlag10000(void) { a80_flags3ED258 |= 0x10000; }
/* 0x00087D80: select mode 5. */
void a80_Mode5(void) { a80_mode3ED274 = 5; }
/* 0x00087EC0: select mode 11. */
void a80_Mode11(void) { a80_mode3ED274 = 11; }
/* 0x00087ED0: select mode 12. */
void a80_Mode12(void) { a80_mode3ED274 = 12; }
/* 0x00088130: run the current mode record's update callback. */
void a80_ModeUpdate(void)
{
    A80ModeRec *r = &a80_modeTable[a80_curMode];
    if (r->update) r->update(r);
}
/* 0x00088170: current mode flag bit 0 (0 for mode 0). */
int a80_ModeFlag1(void)
{
    if (a80_curMode == 0) return 0;
    return (signed char)a80_modeTable[a80_curMode].flags & 1;
}
/* 0x00088190: set flag bit 2 on the current mode record. */
void a80_ModeSetFlag4(void)
{
    if (a80_curMode != 0) a80_modeTable[a80_curMode].flags |= 4;
}
/* 0x000882E0: call 0x252A0 with zeros. */
void a80_Call252A0(void) { sub_000252A0(0, 0); }
/* 0x00089390: field 0x0C of the current reference, 0 if none. */
int32_t a80_CurRefX0C(void) { A80Ref *r = sub_0008CD60(); if (r) return r->x0C; return 0; }
/* 0x000893A0: get field 0x48. */
int32_t a80_GetX48(A80Obj *o) { return o->x48; }
/* 0x000893B0: get field 0x20. */
int32_t a80_GetX20(A80Obj *o) { return o->x20; }
/* 0x00089450: flag bit 9. */
uint32_t a80_FlagBit9(A80Obj *o) { return (o->flags >> 9) & 1; }
/* 0x000894D0: get field 0x04. */
int32_t a80_GetX04(A80Obj *o) { return o->x04; }
/* 0x00089660: get field 0x18 as a word. */
int32_t a80_GetX18(A80Obj *o) { return *(int32_t *)&o->f18; }
/* 0x00089670: print the object's id with a format. */
void a80_PrintId(A80Obj *o, int out) { sub_0007E0A0(out, a80_str26FACC, a80_str26FA20, o->x04); }
/* 0x00089690: value for id from table 0x2E0908. */
int32_t a80_IdValue(int u, int i) { return a80_idTab2E0908[i].value; }
/* 0x000896A0: clear flag bits. */
void a80_ClearFlags(A80Obj *o, uint32_t m) { o->flags &= ~m; }
/* 0x000896C0: set flag bits. */
void a80_SetFlags(A80Obj *o, uint32_t m) { o->flags |= m; }
/* 0x000896D0: test flag bits. */
int a80_TestFlags(A80Obj *o, uint32_t m) { return (o->flags & m) != 0; }
/* 0x000896E0: release slot 0x24 and report whether it emptied. */
int a80_ReleaseX24(A80Obj *o) { sub_0008CC50(&o->x24, o); return o->x24 == 0; }
/* 0x00089700: forward sub4C+4 to 0x7AB10 with the global context. */
void a80_ForwardSub4C(A80Obj *o) { sub_0007AB10(a80_ctx42C8E4, (uint8_t *)o->sub4C + 4); }
/* 0x00089720: forward a fixed string to 0x7AB10. */
void a80_ForwardStr(void) { sub_0007AB10(a80_ctx42C8E4, (void *)a80_str26FA70); }
/* 0x000897A0: field 0x1C of sub4C. */
int32_t a80_Sub4CX1C(A80Obj *o) { return o->sub4C->x1C; }
/* 0x00089E60: address of static object 0x2E0958. */
void *a80_Obj2E0958(void) { return a80_obj2E0958; }
/* 0x00089EE0: address of static object 0x2E09C8. */
void *a80_Obj2E09C8(void) { return a80_obj2E09C8; }
