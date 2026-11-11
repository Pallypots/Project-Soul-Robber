/* Area r6f: key blending, material task handler and model lookup around 0x0008D500-0x0008FED2 (r6f_6). Names inferred. */
#include "r6f.h"

/* 0x0008D500: find the (up to) two kind-13/2 nodes driving the same animation
   object as t and blend their four key channels into it. */
int r6f_TaskBlendKeys(R6fTask *t)
{
    R6fAnimObj *o = (R6fAnimObj *)t->work->p08;
    R6fKeyWork *wa = 0, *wb = 0;
    R6fTask *first, *second, *n;
    int i;
    if (!o)
        return 0;
    first = 0;
    second = 0;
    i = 0;
    n = t;
    do {
        n = sub_0008B290(n, 13, 2);
        if (!n)
            break;
        if (n->work->p08 == o) {
            switch (i) {
            case 0:
                first = n;
                wa = (R6fKeyWork *)n->work;
                break;
            case 1:
                second = n;
                wb = (R6fKeyWork *)n->work;
                break;
            }
            i++;
        }
        n = (R6fTask *)sub_0007F300(n);
    } while (i < 2);
    if (!second) {
        wb = (R6fKeyWork *)first->work;
        second = first;
    }
    sub_0007F610(o->ch30, wa->mode, wa->i14, wb->i14);
    sub_0007F610(o->ch48, wa->mode, wa->i18, wb->i18);
    sub_0007F610(o->ch60, wa->mode, wa->i1C, wb->i1C);
    sub_0007F610(o->ch78, wa->mode, wa->i20, wb->i20);
    o->i28 = ((R6fKeyWork *)first->work)->i00;
    o->i2C = ((R6fKeyWork *)second->work)->i00;
    if (wa->i24)
        o->flags24 |= 1;
    else
        o->flags24 &= ~1;
    return 0;
}

/* 0x0008E480: material task handler: state 1 requests a load (state 3); in
   state 3 load the material of ref (retrying on failure) or refresh it. */
int r6f_TaskMatHandler(R6fTask *t, void *ref)
{
    uint32_t w;
    int n;
    switch (t->state) {
    case 1:
        w = t->f18.s.w;
        if (!(w & 2)) {
            t->f18.s.w = (uint16_t)(w | 8);
            t->state = 3;
        }
        return 0;
    case 3:
        break;
    default:
        return -1;
    }
    if (!(t->f18.b0 & 2)) {
        sub_0007F4A0(6, sub_0008BCD0(t->heap));
        t->p28 = sub_0007EB80(sub_000893A0(ref), ((R6fTaskMat *)t)->i2C, ((R6fTaskMat *)t)->i30);
        if (!t->p28) {
            if (++t->unk22 < 1) {
                t->f18.b0 |= 8;
                return 0;
            }
            t->f18.u = (t->f18.u & ~0xC) | 2;
            return 0;
        }
        t->f18.u = (t->f18.u & ~0xC) | 2;
        sub_0008CCF0(&ref, t);
        sub_0008CBE0((void **)((uint8_t *)sub_00089390() + 0x24), ref);
        return 0;
    }
    sub_0007F4A0(6, sub_0008BCD0(t->heap));
    sub_00053710(4);
    sub_0007E910(t->p28, sub_000893A0(ref), ((R6fTaskMat *)t)->i2C, ((R6fTaskMat *)t)->i30);
    sub_00053740();
    sub_000535F0(-1, ((R6fTaskMat *)t)->i2C, ((R6fTaskMat *)t)->i30);
    n = sub_00089610(ref);
    sub_0008E340((uint8_t)t->workId, ref, (void *)(intptr_t)((R6eAnimRef *)t->p28)->i5C, n);
    return 0;
}

/* 0x0008FE10: find the model record with keys a and b in a list, creating
   (and adding) it when missing; NULL when it cannot be loaded. */
R6fModelRec *r6f_ModelListGet(void *list, int a, int b)
{
    R6eLink *end, *found, *it, *last;
    R6ePred pred;
    R6fModelRec *rec;
    end = sub_0008F8F0(list);
    pred.fn = (uint8_t (*)(R6ePred *, void *))r6e_PredMatch;
    pred.a = a;
    pred.b = b;
    it = (R6eLink *)sub_000894D0(list);
    last = sub_0008F8F0(list);
    found = sub_0008F970(&it, &last, &pred);
    if (sub_0008F960(&found, &end)) {
        rec = (R6fModelRec *)sub_00053AB0(0x10, 0, 0x292);
        sub_0008FCB0(rec, a, b);
        if (rec->models) {
            sub_0008F900(list, rec);
            return rec;
        }
        return 0;
    }
    return (R6fModelRec *)sub_0008FF80(&found);
}
