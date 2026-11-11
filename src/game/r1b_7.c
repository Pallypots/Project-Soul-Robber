/* Area r1b, group 7: scene object records and part trees 0x0001D190..0x0001D910. Names inferred. */
#include "r1b.h"

/* 0x0001D190: release an object's two resources. */
void r1b_RecFreeRes(R1bRec *r)
{
    if (r == 0) return;
    if (r->res134) {
        sub_00033C20(r->res134);
        r->res134 = 0;
    }
    if (r->res13C) {
        sub_0005BC50(r->res13C);
        r->res13C = 0;
    }
}

/* 0x0001D1E0: set an object's 8-character name key. */
void r1b_RecSetName(R1bRec *r, const char *name)
{
    int i;
    char *d = r1b_key42CE40.c;
    for (i = 8; i != 0; i--, d++) {
        if (*name) *d = *name++;
        else *d = 0;
    }
    r->key[0] = r1b_key42CE40.w[0];
    r->key[1] = r1b_key42CE40.w[1];
}

/* 0x0001D240: append a child object to a parent's child chain. */
void r1b_RecAddChild(R1bRec *parent, R1bRec *child)
{
    R1bRec *p;
    child->parent = parent;
    p = parent->next;
    if (p == 0) {
        parent->next = child;
        return;
    }
    while (p->next) p = p->next;
    p->next = child;
}

/* 0x0001D2D0: find the object named name in a parent's chain. */
R1bRec *r1b_RecFindName(R1bRec *root, const char *name)
{
    int i;
    R1bRec *p;
    char *d = r1b_key42CE40.c;
    for (i = 8; i != 0; i--, d++) {
        if (*name) *d = *name++;
        else *d = 0;
    }
    for (p = root->next; p; p = p->next) {
        if (p->key[0] == r1b_key42CE40.w[0] && p->key[1] == r1b_key42CE40.w[1]) break;
    }
    return p;
}

/* 0x0001D330: clear the hidden flag on a part, its sub-parts and its siblings. */
void r1b_PartsUnhideTree(R1bPart *p)
{
    do {
        p->flags &= ~0x10u;
        if (p->link) r1b_PartsUnhideTree(p->link);
        p = p->next;
    } while (p);
}

/* 0x0001D370: set the hidden flag on a part, its sub-parts and its siblings. */
void r1b_PartsHideTree(R1bPart *p)
{
    do {
        p->flags |= 0x10;
        if (p->link) r1b_PartsHideTree(p->link);
        p = p->next;
    } while (p);
}

/* 0x0001D860: test whether an object's name key equals name. */
int r1b_RecNameIs(R1bRec *r, const char *name)
{
    int i;
    char *d = r1b_key42CE40.c;
    for (i = 8; i != 0; i--, d++) {
        if (*name) *d = *name++;
        else *d = 0;
    }
    if (r->key[0] == r1b_key42CE40.w[0] && r->key[1] == r1b_key42CE40.w[1]) return 1;
    return 0;
}

/* 0x0001D8D0: append an item to an object's item list. */
void r1b_RecAddItem(R1bRec *r, R1bItem *it)
{
    R1bItem *p = r->items;
    if (p == 0) {
        r->items = it;
        return;
    }
    while (p->next) p = p->next;
    p->next = it;
}

/* 0x0001D910: unlink an item from an object's item list, freeing it if owned. */
void r1b_RecRemoveItem(R1bRec *r, R1bItem *it)
{
    R1bItem *p, *prev = 0;
    for (p = r->items; p; p = p->next) {
        if (p == it) {
            if (prev) prev->next = p->next;
            else r->items = p->next;
            if (p->flags & 1) sub_00053880(p);
            return;
        }
        prev = p;
    }
}
