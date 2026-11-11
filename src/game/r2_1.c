/* Area r2, group 1: small register-argument helpers (0x000E3000..0x000EF92F). Names inferred. */
#include "r2.h"

/* 0x000E3000: look up an index from (a, b) via 0x0ED0C0 and, when found, apply
   0x0ED1B0 with the stack argument and n clamped to >= 0.
   regargs: a=ECX b=EAX n=EDX; arg is the stack arg */
void r2_LookupApplyN(int a, int b, int n, int arg)
{
    int i = sub_000ED0C0(a, b);
    if (i >= 0) {
        if (n < 0)
            n = 0;
        sub_000ED1B0(i, arg, n);
    }
}

/* 0x000E3030: look up an index from (a, b) via 0x0ED0C0 and, when found, apply
   0x0ECC50 with the stack argument.  regargs: a=ECX b=EAX; arg is the stack arg */
void r2_LookupApply(int a, int b, int arg)
{
    int i = sub_000ED0C0(a, b);
    if (i >= 0)
        sub_000ECC50(i, arg);
}

/* 0x000ED380: find the node keyed `key` in list 0x3F5DC0, unhook it from the
   head/tail globals and remove it.  regargs: key=EAX */
void r2_ListDrop(int key)
{
    R2Node *n = (R2Node *)sub_0003DBC0(r2_list3F5DC0, 0, key);
    if (n) {
        if (r2_head3F60E0 == n)
            r2_head3F60E0 = n->next;
        if (r2_tail3F60E4 == n)
            r2_tail3F60E4 = n->next;
        sub_0003D8C0(n);
        sub_0003D860(n);
    }
}

/* 0x000EEF90: pass obj, its kind-5 component and arg to 0x0F3D10.
   regargs: obj=ESI; arg is the stack arg */
void r2_ActorCallComp5(R2Actor *obj, int arg)
{
    if (!obj)
        for (;;) ;
    sub_000F3D10(obj, sub_0001D960(obj, 5), arg);
}

/* 0x000EF8A0: free the kind-5 component's +0xD4 handle.  regargs: obj=EAX */
void r2_Comp5FreeD4(R2Actor *obj)
{
    R2Comp5 *c = (R2Comp5 *)sub_0001D960(obj, 5);
    if (c->hD4) {
        sub_00033A70(c->hD4);
        c->hD4 = 0;
    }
}

/* 0x000EF8D0: release the kind-5 component's +0xD8 effect.  regargs: obj=EAX */
void r2_Comp5ReleaseD8(R2Actor *obj)
{
    R2Comp5 *c = (R2Comp5 *)sub_0001D960(obj, 5);
    if (c->effD8 >= 0) {
        sub_00048250(c->effD8);
        c->effD8 = -1;
    }
}

/* 0x000EF900: unless state 0x0E3380 is 4 or 5, post event 1 to 0x3E1270 and run 0x0BCA50.
   regargs: obj=EAX (only used to fetch its kind-5 component) */
void r2_CheckStateE3380(R2Actor *obj)
{
    int s;
    sub_0001D960(obj, 5);
    s = sub_000E3380();
    if (s != 4 && s != 5) {
        sub_00019000(ae0_obj3E1270, 1);
        sub_000BCA50();
    }
}
