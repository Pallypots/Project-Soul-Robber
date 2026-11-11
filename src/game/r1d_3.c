/* Area r1d, group 3: chapter flags, segment lists and resource chains 0x0001AFF0..0x0001D7F0. Names inferred. */
#include "r1d.h"

/* 0x0001AFF0: outside the special mode, for chapters 3..5 clear three
   event flag words and set a fixed list of event bits. */
void r1d_ResetChapterFlags(void)
{
    if (a30_g41316C != 0) return;
    if (a30_g413170 < 3 || a30_g413170 > 5) return;
    g_eventFlagBits[5] = 0xFFFFFFFF;
    g_eventFlagBits[4] = 0xFFFFFFFF;
    g_eventFlagBits[3] = 0xFFFFFFFF;
    sub_000D9AB0(0x361);
    sub_000D9AB0(0x363);
    sub_000D9AB0(0x365);
    sub_000D9AB0(0x367);
    sub_000D9AB0(0x369);
    sub_000D9AB0(0x36B);
    sub_000D9AB0(0x36D);
    sub_000D9AB0(0x381);
    if (sub_00049B70() == 1) {
        sub_000D9AB0(0xF4);
        sub_0019E900(1);
    }
    sub_00048AF0(1);
}

/* 0x0001B7B0: build a segment from a, b, c with 0x0007FDC0 and append it
   to the list when that succeeds.  regargs: c=EBX l=EDI (a, b, d, e on the stack) */
void r1d_SegAddA(R1dVec4 *a, R1dVec4 *b, int d, float e, R1dVec4 *c, R1dSegList *l)
{
    R1dVec4 va, vb;
    R1dSeg *s;
    if (sub_0007FDC0(a, b, c, d, e, &va, &vb)) {
        s = &l->segs[l->count];
        sub_000F5D40(&s->v[0], a);
        sub_000F5D40(&s->v[1], b);
        sub_000F5D40(&s->v[2], c);
        sub_000F5D40(&s->v[3], &va);
        sub_000F5D40(&s->v[4], &vb);
        l->count++;
    }
}

/* 0x0001B840: as 0x0001B7B0 with the builder 0x00080470.
   regargs: e=EDX c=EBX l=EDI (a, b, d on the stack) */
void r1d_SegAddB(R1dVec4 *a, R1dVec4 *b, int d, float e, R1dVec4 *c, R1dSegList *l)
{
    R1dVec4 va, vb;
    R1dSeg *s;
    if (sub_00080470(a, b, c, d, e, &va, &vb)) {
        s = &l->segs[l->count];
        sub_000F5D40(&s->v[0], a);
        sub_000F5D40(&s->v[1], b);
        sub_000F5D40(&s->v[2], c);
        sub_000F5D40(&s->v[3], &va);
        sub_000F5D40(&s->v[4], &vb);
        l->count++;
    }
}

/* 0x0001D7F0: for every node of the chain with a resource, select the
   entry for `key` (or entry 0 when missing); unless keep is set, an
   entry equal to the resource default selects -1. */
void r1d_ResChainSelect(R1dResNode *n, int key, int keep)
{
    int32_t *e;
    int32_t v;
    int k;
    for (; n != 0; n = n->next) {
        if (n->res == 0) continue;
        k = keep;
        e = sub_00083120(n->res, key);
        if (e == 0) {
            k = 1;
            e = sub_00083140(n->res, 0);
            if (e == 0) continue;
        }
        v = *e;
        if (!k && v == n->res->def) v = -1;
        sub_000832D0(n->res, v);
    }
}
