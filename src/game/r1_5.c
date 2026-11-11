/* Area r1, group 5: material-flag and fader helpers 0x0003E230..0x0003FA90. Names inferred. */
#include "r1.h"
#include <string.h>

/* 0x0003E230: clear flag 0x10 on every material in a node list.
   regargs: n=ECX */
void r1_MatClearFlag(R1MatNode *n)
{
    for (; n; n = n->next)
        if (n->mat) n->mat->flags &= ~0x10u;
}

/* 0x0003E260: for each named entry, OR its flags into the material of the matching node.
   regargs: count=EAX list=EDX; e is the stack argument */
void r1_MatApplyFlags(R1MatNode *list, int count, R1FlagEnt *e)
{
    R1MatNode *n;
    for (; count > 0; count--, e++) {
        for (n = list; n; n = n->next) {
            if (strcmp(n->name, e->name) == 0) {
                if (n->mat) n->mat->flags |= e->flags;
                break;
            }
        }
    }
}

/* 0x0003FA90: reset a fader and fetch its handle.
   regargs: f=ESI */
int r1_FaderReset(R1Fader *f)
{
    f->active = 0;
    f->handle = sub_00076180(f);
    f->level = 0.0f;
    return 0;
}

/* 0x0003E3C0: apply the material selection s to u, or the default table when s is null.
   calls 0x0003E2E0 with ESI=s EDI=u, 0x0003E370 with ESI=u */
void r1_MatApply(R1MatUser *u, R1MatSel *s)
{
    if (s) {
        r1_g3DE800 = 0;
        r1_MatSelect(s, u);
        r1_g3DE7E4 = 0;
    } else {
        r1_g3DE800 = 1;
        r1_MatDefault(u);
        r1_g3DE7E4 = 1;
    }
}
