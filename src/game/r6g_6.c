/* Area r6g: attack hit dispatch (r6g_6). Names inferred. */
#include "r6g.h"

/* Index of t in list[0..n), -1 when absent (inlined by both compilers). */
static int r6g_FindPtr(void *const *list, int n, void *t)
{
    int i;
    if (!n)
        return -1;
    for (i = 0; i < n; i++) {
        if (list[i] == t)
            return i;
    }
    return -1;
}

/* Run the attack's handler on target t unless t was already hit, is ignored by
   the attack, is o itself or the attack's owner. */
#define R6G_HIT_TARGET(o, a, t)                                         \
    if (r6g_FindPtr((o)->hits, (o)->nHits, (t)) < 0 &&                  \
        r6g_FindPtr((a)->ignore, (a)->nIgnore, (t)) < 0 &&              \
        (t) && (t) != (o)->self && (t) != (a)->owner && (a)->type != -1) \
        r6g_hitFns2E6E80[(a)->type]((o), (a), (t))

/* 0x000C6350: apply attack a of o to every active entity slot, then for every
   target already in o's hit list test the hit again (0x000C5E70); on a hit push
   the target back with the attack power and for attack types 8, 10 and 11 add
   the hit effect. */
void r6g_AttackHitSlots(R6gHitObj *o, R6gAtk *a)
{
    R6gSlot *s;
    int i;
    sub_000C4420(o);
    for (s = aa0_slots; s < aa0_slots + 32; s++) {
        void *t;
        if (s->u.flags0 >= 0)
            continue;
        t = s->obj;
        R6G_HIT_TARGET(o, a, t);
    }
    if (o->nHits <= 0)
        return;
    for (i = 0; i < o->nHits; i++) {
        void *t = o->hits[i];
        if (!t)
            continue;
        if (sub_000C5E70(o, t, a, &o->hitPos[o->nHits], &o->hitDir[o->nHits]) <= 0)
            continue;
        sub_000A95E0(t, &o->hitDir[o->nHits], a->power);
        if (a->type != 8 && (a->type <= 9 || a->type > 11))
            continue;
        sub_000C4960(o, a, 1, &o->hitPos[o->nHits], &o->hitDir[o->nHits]);
    }
}

/* 0x000C66B0: like 0x000C6350 but over the objects returned by the object
   iterator (0x000EDB10/0x000EDB90); the re-test uses 0x000C5D20 and a hit runs
   0x000C64D0; a miss of type 10/11 adds the hit effect and type 14 runs
   0x000CA400. */
void r6g_AttackHitObjects(R6gHitObj *o, R6gAtk *a)
{
    void *t;
    int i;
    sub_000C4420(o);
    t = sub_000EDB10(0);
    while (t) {
        R6G_HIT_TARGET(o, a, t);
        t = sub_000EDB90();
    }
    if (o->nHits <= 0)
        return;
    for (i = 0; i < o->nHits; i++) {
        t = o->hits[i];
        if (!t)
            continue;
        if (sub_000C5D20(o, t, a, &o->hitPos[o->nHits], &o->hitDir[o->nHits]) > 0) {
            sub_000A95E0(t, &o->hitDir[o->nHits], a->power);
            sub_000C64D0(o, t, a, a->power, &o->hitPos[o->nHits], &o->hitDir[o->nHits]);
        } else if (a->type >= 10) {
            if (a->type > 11) {
                if (a->type == 14)
                    sub_000CA400(o);
            } else {
                sub_000C4960(o, a, 1, &o->hitPos[o->nHits], &o->hitDir[o->nHits]);
            }
        }
    }
}
