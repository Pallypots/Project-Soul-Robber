/* Area r1b, group 8: part visibility sync and record walks 0x0001D720..0x0001DA40 (kept apart from their callees). Names inferred. */
#include "r1b.h"

/* 0x0001D720: sync each object's part visibility with its 0x10000 flag. */
void r1b_RecSyncVisible(R1bRec *r)
{
    R1bPart *p;
    for (; r; r = r->next) {
        p = r->part;
        if (!(r->flags & 0x10000)) {
            if (p == 0 || !(p->flags & 0x10)) continue;
            p->flags &= ~0x10u;
            if (p->link) r1b_PartsUnhideTree(p->link);
        } else {
            if (p == 0 || (p->flags & 0x10)) continue;
            p->flags |= 0x10;
            if (p->link) r1b_PartsHideTree(p->link);
        }
    }
}

/* 0x0001D7A0: hide the part of every object in a chain. */
void r1b_RecHideAll(R1bRec *r)
{
    R1bPart *p;
    for (; r; r = r->next) {
        p = r->part;
        if (p == 0 || (p->flags & 0x10)) continue;
        p->flags |= 0x10;
        if (p->link) r1b_PartsHideTree(p->link);
    }
}

/* 0x0001DA40: visit every object chain of every record in a table node. */
void r1b_TableVisit(R1bLNode *t)
{
    int i;
    R1bRec *r;
    for (i = 0; i < t->count; i++) {
        for (r = &t->recs[i]; r; r = r->next) sub_0001D980(r);
    }
}
