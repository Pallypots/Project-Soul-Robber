/* Area r6h: demo key list merge, demo_event.c area (r6h_5). Names inferred. */
#include "r6h.h"

/* 0x0008A0C0: merge the key list *src into *dst. Every key of *dst that has
   the same track/channel, time, target and value as the first key of *src is
   removed from *dst: moved into *src when replace is set, released otherwise.
   Then *src is unlinked and joined to *dst (on success *dst takes the joined
   list and *src is cleared; on failure the result is -1). If out is given it
   is reset to the first node of its list. Returns -1 for missing lists, 0 when
   *src is empty. */
int r6h_KeyListMerge(R6hNode **dst, R6hNode **src, int replace, R6hNode **out)
{
    int result = 0;
    R6hKey *key;
    R6hNode *n, *m;

    if (!dst)
        return -1;
    if (!src)
        return -1;
    if (!*src)
        return 0;
    key = (*src)->key;
    n = *dst;
    while (n) {
        R6hKey *k;
        void *a, *b;

        m = sub_0008B290(n, key->track, key->chan);
        if (!m)
            break;
        k = m->key;
        if (k->time == key->time) {
            a = k->ref;
            if (a && key->ref) {
                if (k->ref->kind != key->ref->kind)
                    goto next;
                a = k->ref->target;
                b = key->ref->target;
            } else {
                b = key->ref;
            }
            if (a == b && k->value == key->value) {
                n = sub_0007F300(m);
                if (*dst == m)
                    *dst = sub_0007F300(*dst);
                if (replace) {
                    sub_0007F2B0(m);
                    *src = sub_0007F3F0(*src, m);
                } else {
                    sub_0008B760(m);
                }
                continue;
            }
        }
    next:
        n = sub_0007F300(m);
    }
    sub_0007F2B0(*src);
    m = sub_0008B780(*dst, *src);
    if (!m) {
        result = -1;
    } else {
        *dst = m;
        *src = 0;
    }
    sub_0008B760(0);
    if (out)
        *out = sub_0007F330(*out);
    return result;
}
