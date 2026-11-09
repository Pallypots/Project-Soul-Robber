/* Area a8b, group 2: demo event callers (0x8A220-0x8CDA0). Names inferred. */
#include "a8b.h"

/* 0x0008A220: mark the work block set and reset its scale to 1,1,1. */
int a8b_WorkResetScale(A8bObj *o)
{
    A8bWork *w = a8b_GetWork(o);
    w->set1C = 1;
    w->f2C = 1.0f; w->f30 = 1.0f; w->f34 = 1.0f;
    return 0;
}
/* 0x0008A4C0: query the target's handle through 0x7E620; -1 if no arg or work. */
int a8b_QueryTarget(A8bObj *o, int arg)
{
    A8bWork *w;
    A8bObj *t;
    if (arg == 0) return -1;
    w = o->work1C;
    if (w == 0) return -1;
    t = w->target08;
    if (t == 0) return 0;
    return sub_0007E620(t->x28);
}
/* 0x0008A570: run 0x8E200 on the active target. */
int a8b_TargetAction(A8bObj *o)
{
    A8bObj *t = a8b_GetActiveTarget(o);
    if (t) sub_0008E200(t);
    return 0;
}
/* 0x0008A590: pass the active target's handle to 0x1EB80, else clear the active bit. */
int a8b_TargetHandle(A8bObj *o)
{
    A8bObj *t = a8b_GetActiveTarget(o);
    if (t) { sub_0001EB80(sub_0008E1B0(t)); return 0; }
    o->flags18 &= ~2u;
    return 0;
}
/* 0x0008B3B0: replace the referenced object, adjusting reference counts. */
void a8b_SetLink(A8bObj *o, A8bObj *n)
{
    if (o->link08) a8b_RefDec(o->link08);
    o->link08 = n;
    if (n) a8b_RefInc(n);
}
/* 0x0008B3E0: drop the referenced object. */
void a8b_ClearLink(A8bObj *o)
{
    if (o->link08) { a8b_RefDec(o->link08); o->link08 = 0; }
}
/* 0x0008BB90: run 0x8B860 with callback 0x8B2F0. */
int a8b_Run8B860(int a, int b, int c) { return sub_0008B860(a, b, c, sub_0008B2F0); }
/* 0x0008BBC0: if work flag 0x10 is set, run 0x8ECA0 on the active target. */
int a8b_TargetAction2(A8bObj *o)
{
    if (o->work1C->v10.i[0]) {
        A8bObj *t = a8b_GetActiveTarget(o);
        if (t) sub_0008ECA0(t);
    }
    return 0;
}
/* 0x0008BC80: validate args, then 0x3D0A0(0) if 0x3D090(0) reports set. */
int a8b_Check3D090(A8bObj *o, int arg)
{
    if (o == 0 || arg == 0 || o->work1C == 0) return -1;
    if (sub_0003D090(0)) sub_0003D0A0(0);
    return 0;
}
/* 0x0008BCD0: 10 for kind 5, else 4. */
int a8b_KindValue(int kind) { return kind == 5 ? 10 : 4; }
/* 0x0008C420: call the type handler at +0x0C for an active object. */
int a8b_CallOps0C(A8bObjB *o, int arg)
{
    if (o->flags18 & 2) {
        int (*fn)(A8bObj *, int) = a8b_opsGetters[o->type1A]()->fn0C;
        if (fn) return fn((A8bObj *)o, arg);
    }
    return 0;
}
/* 0x0008C450: call the type handler at +0x10 for an active object. */
int a8b_CallOps10(A8bObjB *o, int arg)
{
    if (o->flags18 & 2) {
        int (*fn)(A8bObj *, int) = a8b_opsGetters[o->type1A]()->fn10;
        if (fn) fn((A8bObj *)o, arg);
    }
    return 0;
}
/* 0x0008CC30: base cleanup then 0x8CB90, for a non-null object. */
int a8b_Destroy8CC30(A8bObj *o)
{
    if (o == 0) return 0;
    sub_0007F2B0(o);
    return sub_0008CB90(o);
}
