/* Area r6f: key blending and list merge around 0x00089EF0-0x0008AD99 (r6f_8). Names inferred. */
#include "r6f.h"

/* 0x00089EF0: blend the eight key channels of t's work with those of the next
   node of the same kind and object (or with itself) into the animation object;
   when looping, clear bit 0 of the leading type-2 nodes of ref. */
int r6f_TaskBlendKeys8(R6fTask *t, void *ref)
{
    int r = 0;
    R6fKeyWork8 *w, *w2;
    R6fAnimObj8 *o;
    R6fKey key;
    R6fKeyMsg m;
    R6fTask *n;
    if (!ref)
        return -1;
    w = (R6fKeyWork8 *)t->work;
    if (!w) {
        r = -1;
        return r;
    }
    o = (R6fAnimObj8 *)w->p08;
    if (!o)
        return r;
    sub_0007F1E0(&m, 0, 0x20);
    sub_0007F1E0(&key, 0, 0x10);
    m.key = &key;
    key.kind04 = ((R6fKeyWork8 *)t->work)->kind04;
    key.sub05 = ((R6fKeyWork8 *)t->work)->sub05;
    key.p08 = ((R6fKeyWork8 *)t->work)->p08;
    n = (R6fTask *)sub_0008B210((R6fTask *)sub_0007F300(t), &m, 0x1C);
    if (!n || !(w2 = (R6fKeyWork8 *)n->work))
        w2 = w;
    sub_0007F610(o->ch[0], w->mode, w->k[0], w2->k[0]);
    sub_0007F610(o->ch[1], w->mode, w->k[1], w2->k[1]);
    sub_0007F610(o->ch[2], w->mode, w->k[2], w2->k[2]);
    sub_0007F610(o->ch[3], w->mode, w->k[3], w2->k[3]);
    sub_0007F610(o->ch[4], w->mode, w->k[4], w2->k[4]);
    sub_0007F610(o->ch[5], w->mode, w->k[5], w2->k[5]);
    sub_0007F610(o->ch[6], w->mode, w->k[6], w2->k[6]);
    sub_0007F610(o->ch[7], w->mode, w->k[7], w2->k[7]);
    o->i2C = w->i00;
    o->i30 = w2->i00;
    if (w->loop) {
        n = (R6fTask *)sub_00089570(ref, 2);
        if (n) {
            do {
                n->u24.i &= ~1;
                n = (R6fTask *)sub_0007F300(n);
            } while (n && n->f18.s.type == 2);
        }
        o->flags24 |= 1;
        return r;
    }
    o->flags24 &= ~1;
    return r;
}

/* 0x0008AC80: merge the node *src into *list: nodes of the same kind that
   compare equal (0x0008B1A0) are removed (to *removed, else released). */
int r6f_TaskMergeEqual(R6fTask **list, R6fTask **src, R6fTask **removed)
{
    int r = 0;
    R6fTask *s, *n, *hit, *t, *c;
    R6eWork *w;
    if (!list || !src)
        return -1;
    s = *src;
    if (!s)
        return 0;
    w = s->work;
    n = *list;
    if (n) {
        do {
            n = sub_0008B290(n, w->kind04, w->sub05);
            if (!n)
                break;
            if (!sub_0008B1A0(n, s)) {
                hit = n;
                n = (R6fTask *)sub_0007F300(n);
                if (*list == hit)
                    *list = (R6fTask *)sub_0007F300(*list);
                if (removed) {
                    sub_0007F2B0(hit);
                    *removed = (R6fTask *)sub_0007F3F0(*removed, hit);
                } else {
                    sub_0008B760(hit);
                }
            } else {
                n = (R6fTask *)sub_0007F300(n);
            }
        } while (n);
    }
    t = *src;
    *src = 0;
    sub_0007F2B0(t);
    c = sub_0008B780(*list, t);
    if (!c) {
        r = -1;
    } else {
        *list = c;
        t = 0;
    }
    sub_0008B760(t);
    if (removed)
        *removed = (R6fTask *)sub_0007F330(*removed);
    return r;
}
