/* Area r1, group 3: mesh-part helpers 0x0001B8D0..0x0001E850. Names inferred. */
#include "r1.h"

/* 0x0001CEB0: reset a state block to its defaults.
   regargs: id=EAX s=ESI */
void r1_StateReset(R1State *s, int32_t id)
{
    int k;
    s->id = id;
    s->f50[3] = 0.0f; s->f50[2] = 0.0f; s->f50[1] = 0.0f; s->f50[0] = 0.0f;
    s->i04 = -1; s->i08 = -1; s->i44 = -1; s->i48 = -1; s->i4C = -1;
    for (k = 0; k < 13; k++) s->w0C[k] = 0;
    s->w40 = 0;
    s->f60[0] = 0.0f; s->f60[1] = 0.0f; s->f60[2] = 0.0f; s->f6C = 1.0f;
    s->f7C = 0.0f; s->f70[2] = 1.0f; s->f70[1] = 1.0f; s->f70[0] = 1.0f;
    s->f80[0] = 0.0f; s->f80[1] = 0.0f; s->f80[2] = 0.0f; s->f8C = 1.0f;
    s->f90[3] = 128.0f; s->f90[2] = 128.0f; s->f90[1] = 128.0f; s->f90[0] = 128.0f;
    sub_0001C8A0(s);
    for (k = 0; k < 8; k++) s->w12C[k] = 0;
    s->mode = 9;
}

/* 0x0001D3B0: clear the hidden flag on both parts (stops early when part a is not hidden).
   regargs: o=ESI */
void r1_PartsShow(R1PartPair *o)
{
    R1Part *p = o->a;
    if (p) {
        if (!(p->flags & 0x10)) return;
        p->flags &= ~0x10u;
        if (p->link) sub_0001D330(p->link);
    }
    p = o->b;
    if (p && (p->flags & 0x10)) {
        p->flags &= ~0x10u;
        if (p->link) sub_0001D330(p->link);
    }
}

/* 0x0001D410: set the hidden flag on both parts (stops early when part a is already hidden).
   regargs: o=ESI */
void r1_PartsHide(R1PartPair *o)
{
    R1Part *p = o->a;
    if (p) {
        if (p->flags & 0x10) return;
        p->flags |= 0x10;
        if (p->link) sub_0001D370(p->link);
    }
    p = o->b;
    if (p && !(p->flags & 0x10)) {
        p->flags |= 0x10;
        if (p->link) sub_0001D370(p->link);
    }
}

/* 0x0001DAA0: item idx of a part (stride 0x108 for kind 1, 0x180 for kind 9), else null.
   regargs: p=EDX idx=ECX */
void *r1_PartItem(R1Part *p, int idx)
{
    switch (p->kind) {
    case 1:
        if (idx > p->count) idx = p->count - 1;
        return p->items + idx * 0x108;
    case 9:
        if (idx > p->count) idx = p->count - 1;
        return p->items + idx * 0x180;
    }
    return 0;
}

/* 0x0001E4C0: choose a render-state block from a kind and flag word.
   regargs: k=EDX */
R1Opaque *r1_PickBlock(R1KindFlags *k)
{
    uint32_t f;
    switch (k->kind) {
    case 0:
        f = k->flags;
        if (f & 1) return &r1_blk42C8C0;
        if (f & 2) {
            if (f & 4) return &r1_blk42C820;
            return &r1_blk42C8A0;
        }
        if (f & 4) return &r1_blk42C940;
        return &r1_blk42C8A0;
    case 1:
        if (k->flags & 2) return &r1_blk42C9C0;
        return &r1_blk42C880;
    case 2:
        f = k->flags;
        if (f & 2) return &r1_blk42C860;
        if (f & 8) {
            if (f & 4) return &r1_blk42C9E0;
            return &r1_blk42C920;
        }
        if (f & 4) return &r1_blk42C9A0;
        return &r1_blk42C7E0;
    }
    return 0;
}

/* 0x0001E850: grow a range record to cover both parts' item counts.
   regargs: o=EAX r=EDI */
void r1_PartsRange(R1PartPair *o, int32_t *r)
{
    R1Part *p = o->a;
    int n = 0, lo, hi;
    if (p) {
        switch (p->kind) {
        case 1: case 9: n = p->count; break;
        }
    }
    r[0] = r[0] > n ? r[0] : n;
    p = o->b;
    if (p) {
        lo = 0; hi = 0;
        switch (p->kind) {
        case 1: lo = 1; hi = p->count; break;
        case 12: lo = 2; hi = p->count; break;
        }
        r[1] = r[1] > lo ? r[1] : lo;
        r[2] = r[2] <= hi ? hi : r[2];
    }
}
