/* Area r1, group 11: callers of the part and state helpers 0x0001D160..0x0005BB30. Names inferred. */
#include "r1.h"

/* 0x0001D160: allocate and reset a state block. calls 0x0001CEB0 with ESI=s EAX=id */
R1State *r1_StateNew(int32_t id)
{
    R1State *s = (R1State *)sub_00053AB0(0x150, 0, 0x1EB);
    r1_StateReset(s, id);
    return s;
}

/* 0x0001D470: unhide child id of o (parts shown unless o itself is hidden). calls 0x0001D3B0 with ESI=child */
void r1_ChildShow(R1PartPair *o, int32_t id)
{
    R1PartPair *c;
    for (c = o->next; c; c = c->next) {
        if (c->id == id) {
            c->flags &= ~0x10000u;
            if (!(o->flags & 0x10000)) r1_PartsShow(c);
            return;
        }
    }
}

/* 0x0001D4B0: hide child id of o. calls 0x0001D410 with ESI=child */
void r1_ChildHide(R1PartPair *o, int32_t id)
{
    R1PartPair *c;
    for (c = o->next; c; c = c->next) {
        if (c->id == id) {
            c->flags |= 0x10000;
            r1_PartsHide(c);
            return;
        }
    }
}

/* 0x0001D700: hide a node and its parts. calls 0x0001D410 with ESI=n */
void r1_NodeHide(R1PartPair *n)
{
    if (n) {
        n->flags |= 0x10000;
        r1_PartsHide(n);
    }
}

/* 0x0005BB30: store the facing dot of the linked target. calls 0x0005BAC0 with EAX=mode stack=target,scale */
int r1_TargetDot(R1TgtArg *a)
{
    R1TgtOut *o = a->o;
    R1Target *t = o->ref->l->h->t;
    int mode = r1_modeOverride;
    if (mode == -1) mode = t->mode;
    o->dot = r1_DirDot(mode, t->pos, t->scale);
    return 0;
}
