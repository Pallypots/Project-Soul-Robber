/* Area r1k, group 10: intrusive list merge sort 0x0003D990.
   Names inferred. */
#include "r1k.h"

/* remove n from its list (inlined in the original) */
#define R1K_UNLINK(n, lst) do { \
    if ((n)->prev) (n)->prev->next = (n)->next; else (lst)->head = (n)->next; \
    if ((n)->next) (n)->next->prev = (n)->prev; else (lst)->tail = (n)->prev; \
    (lst)->count--; \
    (n)->list = 0; (n)->prev = 0; (n)->next = 0; \
} while (0)

/* 0x0003D990: stable merge sort of the nodes first..last (inclusive) of
   list l by cmp (negative = a after b, so b moves in front of a). Splits
   at the middle, sorts both halves recursively, then merges in place by
   relinking each node of the second half in front of the first node of
   the first half that compares below it. */
void r1k_ListMergeSort(R1kList *l, R1kLNode *first, R1kLNode *last, R1kLCmp cmp)
{
    R1kLNode *slow, *fast, *mid2, *before, *stop, *a, *b, *next, *pa;
    R1kList *lst, *dst;
    int odd;
    if (first == last)
        return;
    fast = first;
    slow = first;
    odd = 0;
    do {
        if (odd)
            slow = slow->next;
        fast = fast->next;
        odd ^= 1;
    } while (fast != last);
    stop = last->next;
    mid2 = slow->next;
    before = first->prev;
    r1k_ListMergeSort(l, first, slow, cmp);
    last = mid2->prev;
    r1k_ListMergeSort(l, mid2, fast, cmp);
    a = before ? before->next : l->head;
    b = last ? last->next : l->head;
    while (b != stop && a != b) {
        if (cmp(a, b) >= 0) {
            a = a->next;
            continue;
        }
        pa = a->prev;
        next = b->next;
        lst = b->list;
        if (pa) {
            if (lst == pa->list) {
                if (lst)
                    R1K_UNLINK(b, lst);
                b->list = pa->list;
                b->prev = pa;
                b->next = pa->next;
                pa->next = b;
                if (b->next == 0)
                    pa->list->tail = b;
                else
                    b->next->prev = b;
                pa->list->count++;
            }
        } else {
            if (lst)
                R1K_UNLINK(b, lst);
            dst = a->list;
            b->list = dst;
            if (dst->head == 0) {
                dst->tail = b;
                dst->head = b;
                b->next = 0;
                b->prev = 0;
                dst->count++;
            } else {
                dst->head->prev = b;
                b->next = dst->head;
                b->prev = 0;
                dst->head = b;
                dst->count++;
            }
        }
        b = next;
    }
}
