/* Area a4c, group 4: intrusive doubly linked list 0x0003D880..0x0003DC10. Names inferred. */
#include "a4c.h"

/* 0x0003D880: append node at the tail of list. */
void a4c_ListAppend(A4cList *list, A4cNode *node)
{
    node->owner = list;
    if (list->tail == 0) {
        list->tail = node;
        list->head = node;
        node->next = 0;
        node->prev = 0;
        list->count++;
    } else {
        list->tail->next = node;
        node->prev = list->tail;
        node->next = 0;
        list->tail = node;
        list->count++;
    }
}
/* 0x0003D8C0: unlink node from its list. */
void a4c_ListRemove(A4cNode *node)
{
    if (node->owner == 0) return;
    if (node->prev) node->prev->next = node->next;
    else node->owner->head = node->next;
    if (node->next) node->next->prev = node->prev;
    else node->owner->tail = node->prev;
    node->owner->count--;
    node->owner = 0;
    node->prev = 0;
    node->next = 0;
}
/* 0x0003D960: i-th node of list, 0 when out of range. */
A4cNode *a4c_ListGetAt(A4cList *list, int i)
{
    A4cNode *n;
    if (list == 0 || i < 0 || i >= list->count) return 0;
    for (n = list->head; i > 0; i--) {
        if (n == 0) return 0;
        n = n->next;
    }
    return n;
}
/* 0x0003DB60: call fn on each node until it returns nonzero; returns that value. */
int a4c_ListForEach(A4cList *list, A4cNodeFn fn, void *arg)
{
    A4cNode *n;
    int r;
    if (list == 0 || fn == 0) return 0;
    for (n = list->head; n; n = n->next)
        if ((r = fn(n, arg)) != 0) return r;
    return 0;
}
/* 0x0003DBC0: first node matching fn (default: data == arg). */
A4cNode *a4c_ListFind(A4cList *list, A4cNodeFn fn, void *arg)
{
    A4cNode *n;
    if (list == 0) return 0;
    if (fn == 0) fn = sub_0003DBA0;
    for (n = list->head; n; n = n->next)
        if (fn(n, arg)) return n;
    return 0;
}
/* 0x0003DC10: next node after node matching fn (default: data == arg). */
A4cNode *a4c_ListFindNext(A4cNode *node, A4cNodeFn fn, void *arg)
{
    A4cNode *n;
    if (node == 0) return 0;
    if (fn == 0) fn = sub_0003DBA0;
    for (n = node->next; n; n = n->next)
        if (fn(n, arg)) break;
    return n;
}
