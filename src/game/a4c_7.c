/* Area a4c, group 7: menu items and text helpers 0x0003E410..0x0003FCB0. Names inferred. */
#include "a4c.h"

/* 0x0003E410: store a value in the item's target, notify, and notify the parent while it is still referenced. */
void a4c_ItemRelease(A4cMenuItem *it, int v)
{
    if (it->target) it->target->f14 = v;
    sub_0003F880(0, it, 3);
    it->ref->count--;
    if (it->ref->count >= 0) sub_0003F880(0, it->target, 5);
}
/* 0x0003E460: print "[%s]" with the item's name (or the default "MENU"). */
void a4c_ItemPrintName(void *a, int b, int c, void *d, void *e, A4cMenuItem *it)
{
    const char *name = it->def ? it->def->name : a4c_strMenu;
    sub_0002E8C0(a, b, c, *a4c_pg2C4B08, d, e, a4c_strFmtBracket, name);
}
/* 0x0003F570: process the current entry of the item's table. */
int a4c_ItemProcessEntry(A4cMenuItem *it)
{
    A4cMenuDef *o = it->def;
    if (o == 0 || o->entries == 0) return 0;
    return sub_0003EF00(&o->entries[it->index], it->f28);
}
/* 0x0003F9E0: look up an element, flag it and move it by (16,32). */
void a4c_ElemNudge(void *a, void *b)
{
    A4cElem *e = sub_0003F8B0(a, b, 0);
    if (e) {
        e->flags |= 1;
        e->x += 0x10;
        e->y += 0x20;
    }
}
/* 0x0003FAB0: attach text t to box b and reset it. */
void a4c_TextBoxAttach(A4cTextBox *b, void *t)
{
    if (b == 0) for (;;) ;
    b->state = 5;
    b->text = t;
    b->scale = 1.0f / 3.0f;
    b->f1C = -1;
    if (t) { sub_00075F00(t); a60_TextClear(t); }
}
/* 0x0003FC10: clear the box's text and reset the global box pointer. */
void a4c_TextBoxClose(A4cTextBox *b)
{
    if (b == 0) for (;;) ;
    if (b->text) a60_TextClear(b->text);
    b->state = 5;
    a4c_g2C4BA4 = 0;
}
/* 0x0003FCB0: create with a zero third argument. */
int a4c_CreateDefault(int a, int b, int c, int d, int e)
{
    return sub_0003FAF0(a, b, 0, c, d, e);
}
