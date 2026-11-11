/* Area r6f: render pass list and nine-channel key blending (r6f_9). Names inferred. */
#include "r6f.h"

/* 0x000849D0: emit every pass of a pass set into the display list dl: its
   commands (or a default one), the pre/post hooks and, unless disabled, the
   state block with its callbacks; returns the advanced list pointer. */
void *r6f_PassSetEmit(R6fPassSet *s, void *dl)
{
    uint32_t i, j;
    R6fPass *p;
    R6fCallback *c;
    R6fCmd *cmd;
    for (i = 0; i < s->count; i++) {
        p = &s->passes[i];
        if (!p->ncmd) {
            dl = sub_00012300(dl, 0x47, 0, 0x5000D, 0);
        } else {
            for (j = 0, cmd = p->cmd; j < p->ncmd; j++, cmd++)
                dl = sub_00012300(dl, cmd->a, cmd->b, cmd->c, cmd->d);
        }
        if (p->pre)
            dl = p->pre(dl);
        if (!(p->flags & 1)) {
            sub_001B1FC0();
            sub_001B2490(p->state);
            sub_001B1FE0();
            if (!(r6f_renderFlags412F30 & 1)) {
                for (c = p->onSet; c; c = c->next)
                    c->fn();
            }
            if (!(p->flags & 2))
                sub_001B24E0(dl);
            for (c = p->onDone; c; c = c->next)
                c->fn();
        }
        if (p->post)
            dl = p->post(dl);
    }
    return dl;
}

/* 0x0008A250: blend the nine key channels of t's work with the next node of
   the same kind and object (or itself) into t's active target, after
   refreshing its effect; clears t's flag 2 when there is no loaded target. */
int r6f_TaskBlendKeys9(R6fTask *t)
{
    R6fMatNode *m;
    R6fFxRec *e;
    R6fKeyWork9 *w, *w2;
    R6fKey key;
    R6fKeyMsg msg;
    R6fTask *n;
    m = (R6fMatNode *)sub_0008AFA0(t);
    if (!m || !m->p28) {
        t->f18.u &= ~2;
        return 0;
    }
    e = sub_0008E1B0(m);
    if (e)
        sub_0001E9B0(r6f_ctx42C8E4, e, e->i14C, 5, 0x11);
    w = (R6fKeyWork9 *)sub_0008B0C0(t);
    sub_0007F1E0(&msg, 0, 0x20);
    sub_0007F1E0(&key, 0, 0x10);
    msg.key = &key;
    key.kind04 = t->work->kind04;
    key.sub05 = t->work->sub05;
    key.p08 = t->work->p08;
    n = (R6fTask *)sub_0008B210((R6fTask *)sub_0007F300(t), &msg, 0x1C);
    if (!n || !(w2 = (R6fKeyWork9 *)sub_0008B0C0(n)))
        w2 = w;
    sub_0007F610(m->ch[0], w->mode, w->k[0], w2->k[0]);
    sub_0007F610(m->ch[1], w->mode, w->k[1], w2->k[1]);
    sub_0007F610(m->ch[2], w->mode, w->k[2], w2->k[2]);
    sub_0007F610(m->ch[3], w->mode, w->k[3], w2->k[3]);
    sub_0007F610(m->ch[4], w->mode, w->k[4], w2->k[4]);
    sub_0007F610(m->ch[5], w->mode, w->k[5], w2->k[5]);
    sub_0007F610(m->ch[6], w->mode, w->k[6], w2->k[6]);
    sub_0007F610(m->ch[7], w->mode, w->k[7], w2->k[7]);
    sub_0007F610(m->ch[8], w->mode, w->k[8], w2->k[8]);
    m->i34 = w->i00;
    m->i38 = w2->i00;
    m->i3C = w->i10;
    m->i40 = w->i14;
    return 0;
}
