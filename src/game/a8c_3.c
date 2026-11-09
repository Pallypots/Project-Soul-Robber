/* Area a8c, group 3: stage table and scene node helpers (0x88150-0x8BF50). Names inferred. */
#include "a8c.h"

/* 0x00088150: bit 1 of the current stage record's flags (0 if none). */
int a8c_StageFlag2(void)
{
    int i = a8c_g3ED51C;
    if (i == 0) return 0;
    return (uint32_t)(a8c_stageRecs[i].flags14 & 2) >> 1;
}

/* 0x00089420: run 0x8C450 on every child of o. */
int a8c_ChildrenApply(A8cNode *o)
{
    A8cNode *n;
    for (n = o->child20; n; n = sub_0007F300(n))
        sub_0008C450(n, o);
    return 0;
}

/* 0x00089540: replace the child chain via 0x8C900; -1 on failure. */
int a8c_ChildrenReplace(A8cNode *o, int a)
{
    A8cNode *n = sub_0008C900(o->child20, a);
    if (n == 0) return -1;
    o->child20 = n;
    return 0;
}

/* 0x00089570: first child of the given type. */
A8cNode *a8c_ChildFindType(A8cNode *o, int type)
{
    A8cNode *n = o->child20;
    while (n) {
        if (n->type1A == type) return n;
        n = sub_0007F300(n);
    }
    return n;
}

/* 0x0008B2F0: true if two keys match (float +0, ints +8 and +0xC). */
char a8c_Key3Equal(A8cKey3 *a, A8cKey3 *b)
{
    return b->f00 == a->f00 && b->i08 == a->i08 && b->i0C == a->i0C;
}

/* 0x0008BF50: handler i of table 0x2E10E8. */
void a8c_Dispatch2E10E8(int i) { a8c_tbl2E10E8[i](); }

/* 0x00089610: number of matching nodes in the work chain. */
int a8c_CountMatches(A8cObj *o)
{
    int n = -1;
    A8cNode *p = sub_0008B290((A8cNode *)o->work1C, 1, 1);
    while (p) {
        n++;
        p = sub_0008B290(sub_0007F300(p), 1, 1);
    }
    if (n > 0) return n;
    return 0;
}

/* 0x00089880: create two sub-events (index 0 and 1) and chain them. */
void a8c_AddTwoEvents(A8cObj *o)
{
    int i;
    for (i = 0; i < 2; i++) {
        A8cObj *e = sub_0008B980(1, 1);
        ((A8cWork *)e->work1C)->w10.i = i;
        o->work1C = sub_0008B780(o->work1C, e);
    }
}

/* 0x0008A520: move the active target using work values; clear active bit if none. */
int a8c_MoveTarget(A8cObj *o)
{
    A8cWork *w = (A8cWork *)o->work1C;
    A8cObj *t = sub_0008AFA0(o);
    if (t == 0) { o->flags18 &= ~2u; return 0; }
    sub_0008E1C0(t, w->w00.f, w->w14.f, w->w00.f + w->w10.f, w->w18.f);
    return 0;
}

/* 0x0008AA40: copy event a onto b, including work +0x10..+0x18 and +0x20. */
int a8c_CopyEvent4(A8cObj *a, A8cObj *b)
{
    A8cWork *s = (A8cWork *)a->work1C, *d = (A8cWork *)b->work1C;
    sub_0008B700(a, b);
    d->w10 = s->w10; d->w14 = s->w14; d->w18 = s->w18; d->w20 = s->w20;
    return 0;
}

/* 0x0008AAF0: copy event a onto b, including work +0x10..+0x18. */
int a8c_CopyEvent3(A8cObj *a, A8cObj *b)
{
    A8cWork *s = (A8cWork *)a->work1C, *d = (A8cWork *)b->work1C;
    sub_0008B700(a, b);
    d->w10 = s->w10; d->w14 = s->w14; d->w18 = s->w18;
    return 0;
}

/* 0x0008AC30: restore the referenced model state, then reset the ids. */
int a8c_EventRestore(A8cObj *o)
{
    A8cWork *w = (A8cWork *)o->work1C;
    if (w->p08) {
        uint8_t *r = sub_00033DC0((uint8_t *)w->p08 + 0x28, w->w10.i);
        if (r) sub_00033DA0(r + 0x14, w->w14.i);
    }
    sub_0008B3E0(w);
    w->w10.i = -1;
    w->w14.i = -1;
    return 0;
}

/* 0x0008AFD0: mark active and call the descriptor handler for the event kind. */
int a8c_EventActivate(A8cObj *o, int arg)
{
    A8cWorkHdr *w;
    o->flags18 |= 2;
    w = (A8cWorkHdr *)o->work1C;
    if (w == 0) return -1;
    return a8b_descGetters[w->kind04]()[w->rec05].fn14(o, arg);
}
