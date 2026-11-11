/* Area r1e, group 1: camera shake, part list scan 0x00018E70..0x0001E7D0. Names inferred. */
#include "r1e.h"

/* 0x00018E70: while the shake counter runs, push the mover's position back
   along its forward axis by the shake amount on every other tick.
   regargs: o=ESI */
void r1e_ShakeStep(R1eMover *o)
{
    R1eVec4 v;
    R1eMat m;
    int old;
    if (r1e_shake37C048 > 0) {
        old = r1e_shake37C048--;
        if (!(old & 2)) {
            r1e_MatOrtho(m, o->m);
            sub_001AD7E0(v, m[1]);
            sub_001ADBA0(v, v, 0.0f - r1e_shakeAmt37C04C);
            v[3] = 0.0f;
            r4c_VecAdd(o->m[3], o->m[3], v);
        }
    }
}

/* 0x0001E7D0: walk a part list; store the head part's value in *first and
   the largest value of the other parts in *rest. Parts whose object is of
   kind 1 or 9 take that object's value, others keep the previous one. */
void r1e_PartValues(int value, int *first, int *rest, R1ePart *head)
{
    R1ePart *p;
    R1ePartObj *o;
    if (first == 0)
        first = &value;
    if (rest == 0)
        rest = &value;
    *first = 0;
    *rest = 0;
    for (p = head; p != 0; p = p->next) {
        o = p->obj;
        if (o != 0 && (p->flags & 1)) {
            switch (o->kind) {
            case 1: case 9:
                value = o->value;
                break;
            }
            if (p == head)
                *first = value;
            else if (value > *rest)
                *rest = value;
        }
    }
}

