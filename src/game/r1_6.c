/* Area r1, group 6: material-set selection 0x0003E2E0..0x0003E370. Names inferred. */
#include "r1.h"

/* 0x0003E2E0: apply material set/sub of s to u when the selection changed.
   regargs: s=ESI u=EDI; calls 0x0003E230 with ECX=u->list, 0x0003E260 with EAX=count EDX=u->list */
void r1_MatSelect(R1MatSel *s, R1MatUser *u)
{
    R1FlagTbl *t;
    int off;
    if (r1_lastSet != s->set || r1_lastSub != s->sub || r1_g3DE800 != r1_g3DE7E4) {
        if (s->set != -1 && s->sub != -1) {
            r1_MatClearFlag(u->list);
            t = r1_flagTbls[s->set];
            if (t) {
                off = t->off[s->sub];
                if (off) r1_MatApplyFlags(u->list, t->count, (R1FlagEnt *)((uint8_t *)t + off));
            }
        }
    }
    r1_lastSet = s->set;
    r1_lastSub = s->sub;
}

/* 0x0003E370: clear material flags of u, then apply the default flag table.
   regargs: u=ESI; calls 0x0003E260 with EAX=count EDX=u->list */
void r1_MatDefault(R1MatUser *u)
{
    R1MatNode *n;
    R1FlagTbl *t;
    for (n = u->list; n; n = n->next)
        if (n->mat) n->mat->flags &= ~0x10u;
    t = r1_flagTbl3DE7FC;
    if (t && t->off[0]) r1_MatApplyFlags(u->list, t->count, (R1FlagEnt *)((uint8_t *)t + t->off[0]));
}
