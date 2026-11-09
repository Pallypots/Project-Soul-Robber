/* Area b1b, group 4: enemy core helpers 0x00113090-0x00113E00. Names inferred. */
#include "b1b.h"

/* 0x00113090: play an animation (restart if already current) and reset its timer. */
void b1b_EnemyPlayAnim(B1bOwner *o, B1bEnemy *e, int anim)
{
    if (e->anim64 == anim) {
        sub_000832D0(o->p30, -1);
    } else {
        sub_000832D0(o->p30, anim);
        e->anim64 = anim;
    }
    sub_0001D7F0(o->p3C, anim, 0);
    if (((B1bAnim *)o->p30)->cur != e->anim64) for (;;) ;
    e->f68 = 0.0f;
}

/* 0x00113290: measure the target position in the model's frame (forward axis -1 z). */
float b1b_EnemyAim(B1bOwner *o, void *target)
{
    float dir[4], rel[4];
    dir[0] = 0.0f;
    dir[1] = 0.0f;
    dir[2] = -1.0f;
    dir[3] = 0.0f;
    sub_001AD9F0(rel, target, o->pos60);
    sub_001AD9B0(dir, (float *)(o->p20 + 0x40), dir);
    return sub_001B27C0(dir, rel);
}

/* 0x00113300: take a free node from the pool and append it to the list. */
B1bNode *b1b_NodeAlloc(B1bEnemy *e)
{
    B1bNode *n, *t;
    int i;
    n = e->pool;
    for (i = 0; i < 4; i++, n++)
        if (n->kind == 0)
            break;
    if (i >= 4)
        return 0;
    if (e->nodes == 0) {
        e->nodes = n;
        n->kind = 1;
        return n;
    }
    for (t = e->nodes; t->next != 0; t = t->next) { }
    t->next = n;
    n->prev = t;
    n->kind = 1;
    return n;
}

/* 0x00113370: unlink and clear a node unless locked; returns the following node. */
B1bNode *b1b_NodeFree(B1bEnemy *e, B1bNode *n)
{
    B1bNode *next;
    if (e == 0 || n == 0)
        return 0;
    next = n->next;
    if (n->kind == 2)
        return next;
    if (n->prev != 0)
        n->prev->next = next;
    if (n->next != 0)
        n->next->prev = n->prev;
    if (e->nodes == n)
        e->nodes = n->next;
    n->kind = 0;
    n->i0C = 0;
    n->i10 = 0;
    n->i14 = 0;
    n->f18 = 0;
    n->f1C = 0;
    n->prev = 0;
    n->next = 0;
    n->id = -1;
    n->f08 = 0.0f;
    return next;
}

/* 0x00113A40: flag the enemy (0x280), mark every part, and start fade 2.0. */
void b1b_EnemyMarkParts(B1bOwner *o, B1bEnemy *e)
{
    B1bOwner *p;
    e->flags4C |= 0x280;
    for (p = o; p != 0; p = (B1bOwner *)p->p3C) {
        B1bSub30 *s = (B1bSub30 *)p->p30;
        if (s != 0 && s->p14 != 0)
            s->p14->flagsB8 |= 2;
    }
    sub_000EE760(o, 2.0f);
    o->iD0 = 2;
}

/* 0x00113E00: try to start the enemy's current controller; 1 on success. */
int b1b_EnemyStart(B1bOwner *o)
{
    B1bECtl *c = (B1bECtl *)sub_0001D960(o, sub_000EE5F0(o));
    if (c == 0) for (;;) ;
    if (c->canStart(o, c) == 0)
        return 0;
    o->flags0C &= ~1u;
    sub_0001EB80(o);
    sub_001134B0(c);
    sub_001B2200(o->p20, c->v14C);
    return 1;
}
