/* Area r1, group 1: register-argument helpers 0x00013300..0x000192C0. Names inferred. */
#include "r1.h"

/* 0x00017F40: clear the flags of every entry in a list and drop the list.
   regargs: l=EAX */
void r1_ClearList(R1EntryList *l)
{
    uint32_t i;
    if (l->items == 0) return;
    for (i = 0; i < l->count; i++) l->items[i].flags = 0;
    l->items = 0;
}

/* 0x00018E00: clear flag 2 and advance the global fade timer.
   regargs: flags=EAX */
void r1_TickFade(uint32_t *flags)
{
    float lim;
    *flags &= ~2u;
    if (r1_i37C050 == 0) return;
    if (r1_f37C054 > r1_f37C058) {
        r1_f37C058 = r1_frameUnits + r1_f37C058;
        if (r1_i37C050 == 6) lim = r1_f37C054 * 0.3f;
        else if (r1_i37C050 == 13) lim = r1_f37C054 * 0.2f;
        else return;
        if (r1_f37C058 > lim) r1_i37C050 = 1;
    } else {
        r1_i37C050 = 0;
    }
}

/* 0x000192C0: choose the active selection record for an owner (or none).
   regargs: o=EDI */
R1Sel *r1_PickSel(R1SelOwner *o)
{
    R1Sel *s;
    if (o->enabled == 0) return 0;
    if (!sub_000E3370() && !sub_00087AF0() && !sub_00088170()) {
        if (sub_000CB9F0(r1_obj37BF58) == 1) return &r1_sel37BEF8;
        return 0;
    }
    if (!sub_000E3370() && sub_000CB9F0(r1_obj37BF58) == 1) return &r1_sel37BEF8;
    s = o->sel;
    if (s == 0) {
        s = sub_000CB9B0();
        if (s == 0) return 0;
    }
    if (s->kind < 2 || s->kind > 4) s = 0;
    return s;
}
