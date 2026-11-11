/* Area aec, group 1: leaf helpers 0x000E0350-0x000EFA30. Names inferred. */
#include "aec.h"

/* 0x000E0350: free both table buffers and clear their pointers. */
void aec_FreeTables(void)
{
    sub_00053880(g_acb_table);
    sub_00053880(aec_3F0744);
    g_acb_table = 0;
    aec_3F0744 = 0;
}
/* 0x000E0380: register entry b (unless -1) in list 0x003EDD20 with time 30 and -1. */
void aec_Register3EDD20(void *a, int b, int c)
{
    if (b == -1) return;
    sub_0003FCB0(&aec_3EDD20, sub_0003FA70(a, b), c, 30.0f, -1.0f);
}
/* 0x000E0810: release handle +0x2FC if valid. */
void aec_ReleaseHandle2FC(AecObj *o)
{
    if (o->v2FC >= 0) {
        sub_0019A9D0(o->v2FC);
        o->v2FC = -1;
    }
}
/* 0x000E0840: 0x000494D0(0x00048510(a) + b, c, 1). */
void aec_E0840(int a, int b, void *c)
{
    sub_000494D0(sub_00048510(a) + b, c, 1);
}
/* 0x000E0C80: limit for row kind 0..6. */
int aec_RowLimit(int kind)
{
    switch (kind) {
    case 0: return 0x1A;
    case 1: return 0x14;
    case 2: return 0x15;
    case 3: return 0x18;
    case 4: return 0x1B;
    case 5: case 6: return 0x10;
    default: return 0x10;
    }
}
/* 0x000E0EA0: when enabled, n==1 -> 0x000E9950(0,0), n>1 -> 0x000E9950(1,n-2). */
void aec_E0EA0(int n)
{
    if (aec_413140 == 0 && aec_3F0A84 == 0) return;
    if (n <= 0) return;
    if (n == 1) sub_000E9950(0, 0);
    else sub_000E9950(1, n - 2);
}
/* 0x000E1F30: free slot i target and clear it. */
void aec_FreeSlot(AecObj *o, int i)
{
    AecSlotTarget **p = &o->slots[i].target;
    if (*p) sub_0001EB80(*p);
    *p = 0;
}
/* 0x000E2320: slot target float +0x64 = slot +0x18 + 24. */
void aec_SlotSetTime(AecObj *o, int i)
{
    AecSlot *s = &o->slots[i];
    if (s->target) s->target->f64 = s->f18 + aec_slotTimeAdd;
}
/* 0x000E23B0: when slot target flag 2 is set, call 0x000E1F60(o, i, 1). */
void aec_SlotCheck(AecObj *o, int i)
{
    AecSlotTarget *t = o->slots[i].target;
    if (t && (sub_001AEE90(t->o30->v14, 0) & 2))
        sub_000E1F60(o, i, 1);
}
/* 0x000E23F0: actor lookup: kind 1 is the player, else via context +0x1E8. */
void *aec_FindActor(int kind, int id)
{
    if (kind == 1) return g_playerObj;
    return sub_0001D080(aec_ctx42C8E4->v1E8, kind, id);
}
/* 0x000E2420: map record kind 0..6 to a code. */
int aec_KindCode(int *rec)
{
    switch (*rec) {
    case 0: return 0;
    case 1: return 1;
    case 2: return 6;
    case 3: return 3;
    case 4: return 7;
    case 5: return 8;
    case 6: return 9;
    default: return 0;
    }
}
/* 0x000E2670: look up record i and dispatch through the slot handler table. */
int aec_SlotDispatch(int a, int i, int arg)
{
    void *r = sub_000E2540(a, i);
    if (r == 0) for (;;) ;
    if (aec_slotFns[i] == 0) for (;;) ;
    return aec_slotFns[i](r, arg);
}
/* 0x000E3350: append to list 0x003F118C when enabled. */
void aec_E3350(void *a)
{
    if (g_acb_3F0A78) sub_0003FBD0(a, &aec_3F118C);
}
/* 0x000E8CE0: clear 0x003F49D0/D4 in mode 10000. */
void aec_E8CE0(void)
{
    if (g_acb_3F57BC == 10000) { aec_3F49D0 = 0; aec_3F49D4 = 0; }
}
/* 0x000E9BA0: run 0x000E9B00 in mode 10000. */
void aec_E9BA0(void)
{
    if (g_acb_3F57BC == 10000) sub_000E9B00();
}
/* 0x000EC320: clear the 0x003F59D0 block. */
void aec_ClearBlock59D0(void)
{
    aec_3F59D8 = 0; aec_3F59DC = 0; aec_3F59E4 = 0; aec_3F59E8 = 0; aec_3F59EC = 0;
    aec_3F59F0 = 0; aec_3F59D0 = 0; aec_3F59D4 = 0; aec_3F59E0 = 0;
}
/* 0x000EC620: list head 0x003F59C4. */
AecNode *aec_ListHead59C4(void) { return aec_list3F59C4; }
/* 0x000EC630: 1 when no list entry satisfies 0x00034AF0. */
int aec_ListNoneMatch(void)
{
    AecNode *n;
    for (n = aec_list3F59C4; n; n = n->next) {
        AecKey *k = (AecKey *)n->payload;
        if (sub_00034AF0(k->kind, k->sub)) return 0;
    }
    return 1;
}
/* 0x000EC730: call each listed object's component-0x0C update. */
void aec_ListUpdate(void)
{
    AecNode *n = aec_list3F59C4;
    while (n) {
        void *obj = n->payload;
        AecNode *next = n->next;
        AecComp0C *c = (AecComp0C *)sub_0001D960(obj, 0xC);
        if (c == 0) for (;;) ;
        c->update(obj);
        n = next;
    }
}
/* 0x000ECBB0: run 0x000ECB60 then clear four globals. */
void aec_ECBB0(void)
{
    sub_000ECB60();
    aec_3F59D0 = 0; aec_3F59D4 = 0; aec_3F59E4 = 0; aec_3F59F0 = 0;
}
/* 0x000ECBD0: reset record i of 0x003F59F8. */
void aec_ResetRec(int i)
{
    AecRec1C *r;
    if (i == -1) return;
    if (i >= 5) for (;;) ;
    r = &aec_recs1C[i];
    r->v00 = 0; r->v04 = -1; r->v08 = -1; r->v0C = 0; r->v10 = -1;
}
/* 0x000ED0C0: map (kind, sub) to a slot index, -1 if none. */
int aec_KindSlot(int kind, int sub)
{
    switch (kind) {
    case 1: return 0;
    case 3:
        switch (sub) {
        case 0: return 1;
        case 7: return 2;
        case 9: return 4;
        }
    }
    return -1;
}
/* 0x000ED3D0: kind 2..5, or kind 8 with sub below 10. */
int aec_KindIsA(int kind, int sub)
{
    if (kind < 2) return 0;
    if (kind <= 5) return 1;
    if (kind == 8 && (sub < 0 || sub < 10)) return 1;
    return 0;
}
/* 0x000ED400: kind 6, or kind 8 with sub outside 0..9. */
int aec_KindIsB(int kind, int sub)
{
    switch (kind) {
    case 6: return 1;
    case 8: if (sub < 0 || sub >= 10) return 1;
    }
    return 0;
}
/* 0x000ED9E0: find entry a in list 0x003F5DB0 and remove/free it. */
void aec_RemoveEntry(void *a)
{
    void *p = sub_0003DBC0(&aec_3F5DB0, 0, a);
    if (p) { sub_0003D8C0(p); sub_0003D860(p); }
}
/* 0x000EDA20: list 0x003F5DC4 contains (kind, sub). */
int aec_ListHas(int kind, int sub)
{
    AecNode *n;
    for (n = aec_list3F5DC4; n; n = n->next) {
        AecKey *k = (AecKey *)n->payload;
        if (k->kind == kind && k->sub == sub) return 1;
    }
    return 0;
}
/* 0x000EDA90: list 0x003F5DC4 has an entry of class B (see 0x000ED400). */
int aec_ListHasB(void)
{
    AecNode *n;
    for (n = aec_list3F5DC4; n; n = n->next) {
        AecKey *k = (AecKey *)n->payload;
        int sub = k->sub;
        switch (k->kind) {
        case 6: return 1;
        case 8: if (sub < 0 || sub >= 10) return 1;
        }
    }
    return 0;
}
/* 0x000EDAD0: count entries of kind (and sub, unless sub < 0). */
int aec_ListCount(int kind, int sub)
{
    int cnt = 0;
    AecNode *n;
    if (kind < 0) return 0;
    for (n = aec_list3F5DC4; n; n = n->next) {
        AecKey *k = (AecKey *)n->payload;
        if (k->kind == kind && (sub < 0 || k->sub == sub)) cnt++;
    }
    return cnt;
}
/* 0x000EDBE0: find payload for (kind, sub). */
AecKey *aec_ListFind(int kind, int sub)
{
    AecNode *n;
    if (kind < 0 || sub < 0) return 0;
    for (n = aec_list3F5DC4; n; n = n->next) {
        AecKey *k = (AecKey *)n->payload;
        if (k->kind == kind && k->sub == sub) return k;
    }
    return 0;
}
/* 0x000EDF10: component 0x0D flag bit 0. */
int aec_Comp0DFlag(void *obj)
{
    AecComp0D *c = (AecComp0D *)sub_0001D960(obj, 0xD);
    if (c) return c->flags & 1;
    return 0;
}
/* 0x000EDF30: set component 0x0D value i (0..1). */
void aec_Comp0DSet(void *obj, int i, int v)
{
    AecComp0D *c;
    if (i >= 2) return;
    c = (AecComp0D *)sub_0001D960(obj, 0xD);
    if (c) c->vals[i] = v;
}
/* 0x000EDF60: get component 0x0D value i (0..1). */
int aec_Comp0DGet(void *obj, int i)
{
    AecComp0D *c;
    if (i < 2) {
        c = (AecComp0D *)sub_0001D960(obj, 0xD);
        if (c) return c->vals[i];
    }
    return 0;
}
/* 0x000EE240: every kind 2..5 and 8 below 0x13 passes 0x000EE1B0. */
int aec_AllKindsReady(void)
{
    int i;
    for (i = 0; i < 0x13; i++) {
        if (i < 2) continue;
        if (i > 5 && i != 8) continue;
        if (!sub_000EE1B0(i)) return 0;
    }
    return 1;
}
/* 0x000EE270: initialise callback object. */
void aec_InitCbObj(AecCbObj *o)
{
    o->v14 = 0;
    o->f18 = 0.0f;
    o->f1C = 0.0f;
    o->v10 = 0;
    o->v20 = 0;
    o->cb24 = (AecCb)sub_000AD090;
    o->cb28 = sub_00102FA0;
    o->cb2C = (AecCb)sub_000AD090;
    o->v30 = 0;
    o->v34 = 0;
    o->v38 = 0;
}
/* 0x000EEB90: 0x000EE470 with scale 1.0. */
int aec_EEB90(int a, int b, int c, int d)
{
    return sub_000EE470(a, b, c, 1.0f, d);
}
/* 0x000EEDF0: free 0x003F60F0 and clear it. */
void aec_Free3F60F0(void)
{
    sub_00053880(g_acb_3F60F0);
    g_acb_3F60F0 = 0;
}
/* 0x000EFA30: close menu 8 if +0xEC is set. */
void aec_CloseMenu8(int unused, AecEC *o)
{
    if (o->vEC) {
        sub_000A34B0(0, 8, 0);
        o->vEC = 0;
    }
}
