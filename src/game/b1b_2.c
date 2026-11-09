/* Area b1b, group 2: actor/enemy helpers 0x0010D500-0x001153A0. Names inferred. */
#include "b1b.h"

/* 0x0010ED60: when the actor value at +0x54 is not positive, apply setting 0x16. */
void b1b_ActApply16(B1bActor *a, B1bActor *b)
{
    if (b->f54 <= 0.0f) {
        if (a == 0) for (;;) ;
        sub_000F3D10(a, sub_0001D960(a, 5), 0x16);
    }
}

/* 0x0010EF50: set value 5 then reset via 0x000F3BB0. */
void b1b_ActReset5(void *a)
{
    sub_000F3B00(a, 5);
    sub_000F3BB0(a, 0, 0);
}

/* 0x0010EFD0: when +0x164 is positive and flag bits 0x18 are set, apply setting 10. */
void b1b_ActApply10(B1bActor *a, B1bActor *b)
{
    if (b->f164 > 0.0f && (a->b128 & 0x18))
        sub_000F3D10(a, sub_0001D960(a, 5), 10);
}

/* 0x0010F090: update the attached object, then halve and negate +0xB4 into +0xA4. */
void b1b_ActUpdate(B1bActor *o)
{
    sub_001AD940(o->p20);
    b1b_VecOp2(o->pos60, (uint8_t *)o->p20 + 0x70);
    o->fA4 = o->fB4 * -0.5f;
}

/* 0x00112630: run every enabled command except 0x21D. */
void b1b_CmdRunAll(void)
{
    int i;
    sub_000ED600(2);
    for (i = 0; i < 17; i++) {
        int id = b10_cmdTable[i].id;
        if (id != 0x21D && sub_0004F6D0(id) != 0)
            b1b_CmdRun(id);
    }
}

/* 0x00113430: allocate a fresh node for an id, releasing any existing one unless locked. */
B1bNode *b1b_NodeRenew(B1bEnemy *e, int id)
{
    B1bNode *n;
    for (n = e->nodes; n != 0; n = n->next) {
        if (n->id == id) {
            if (n->kind == 2)
                return 0;
            sub_00113370(e, n);
            break;
        }
    }
    n = sub_00113300(e);
    if (n != 0)
        n->id = id;
    return n;
}

/* 0x00114E20: 1 if any object in list 2 has a type-4 component with flag 0x100. */
int b1b_AnyFlagged(void)
{
    void *o;
    for (o = sub_000EDC20(2, 1); o != 0; o = sub_000EDC20(-1, -1)) {
        B1bComp4 *c = (B1bComp4 *)sub_0001D960(o, 4);
        if (c != 0 && (c->flags4C & 0x100))
            return 1;
    }
    return 0;
}

/* 0x00114E60: 1 if the actor info value +0x44 lies within [lo, hi]. */
int b1b_InRange(void *unused, B1bActor *a, B1bRange *r)
{
    B1bInfo *i = a->info;
    return i->f44 >= r->lo && r->hi >= i->f44;
}

/* 0x001153A0: count the objects in list 2. */
int b1b_CountList2(void)
{
    int n = 0;
    void *o;
    for (o = sub_000EDC20(2, 1); o != 0; o = sub_000EDC20(-1, -1))
        n++;
    return n;
}
