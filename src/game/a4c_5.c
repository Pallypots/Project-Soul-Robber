/* Area a4c, group 5: node groups and boot-area helpers 0x0003D020..0x0003E200. Names inferred. */
#include "a4c.h"

/* 0x0003D0A0: unqueue all nodes of group i and forget it. */
void a4c_GroupFree(int i)
{
    A4cNode *n = a4c_ListFind(&a4c_groupList, 0, (int)(intptr_t)a4c_groupData[i]);
    while (n) {
        A4cNode *next = n->next;
        a4c_ListRemove(n);
        n = next;
    }
    a4c_groupHdr[i] = 0;
    a4c_groupRecs[i] = 0;
    a4c_groupData[i] = 0;
    if (a3c_g3DDCE8 == i) a3c_g3DDCE8 = 0;
}
/* 0x0003D120: read the two values of record j of group i. */
void a4c_GroupGetPair(int i, int j, int32_t *a, int32_t *b)
{
    if (a4c_groupHdr[i]) {
        A4cRec30 *r = &a4c_groupRecs[i][j];
        *a = r->f10.i;
        *b = r->f14.i;
    }
}
/* 0x0003D160: set the two float values of record j of group i. */
void a4c_GroupSetPairF(int i, int j, float a, float b)
{
    if (a4c_groupHdr[i]) {
        A4cRec30 *r = &a4c_groupRecs[i][j];
        r->f10.f = a;
        r->f14.f = b;
    }
}
/* 0x0003D910: move node to the tail of its list. */
void a4c_ListMoveToTail(A4cNode *node)
{
    A4cList *list = node->owner;
    if (list == 0) return;
    a4c_ListRemove(node);
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
/* 0x0003DCB0: if flag bit 0 is set, swap it for bit 1 around a flush; returns v. */
int a4c_FlushIfPending(int v)
{
    if (a3c_flags3DE4F8 & 1) {
        sub_001A7430();
        a3c_flags3DE4F8 = (a3c_flags3DE4F8 & ~1u) | 2;
        sub_001B9720();
        sub_001A7430();
    }
    return v;
}
/* 0x0003E1C0: reset the selection state. */
void a4c_SelectReset(void)
{
    a4c_sel3DE7EC[0] = 0;
    a4c_sel3DE7EC[1] = 0;
    a4c_sel3DE7EC[2] = 0;
    a4c_sel3DE7EC[3] = 0;
    a4c_sel3DE7EC[4] = 0;
    a4c_g3DE804 = -1;
    a4c_g3DE7E8 = -1;
    a4c_g3DE800 = 0;
    a4c_g3DE7E4 = -1;
}
/* 0x0003E200: set selection slot i and invalidate the cached state. */
void a4c_SelectSet(int i, int v)
{
    a4c_sel3DE7EC[i] = v;
    a4c_g3DE804 = -1;
    a4c_g3DE7E8 = -1;
    a4c_g3DE800 = 0;
    a4c_g3DE7E4 = -1;
}
