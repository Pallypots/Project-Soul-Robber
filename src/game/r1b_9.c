/* Area r1b, group 9: scene script command handlers and part walks 0x0001E0C0..0x00020170. Names inferred. */
#include "r1b.h"

/* 0x0001E0C0: command: select item *arg on the target (or forward it to the
   attached controller); returns the operand size 4. */
int r1b_CmdSelect(R1bCmdCtx *ctx, int32_t *arg, R1bCmdTarget *t)
{
    int32_t v = *arg;
    if (t->ctl) {
        t->ctl->sel30 = v;
        return 4;
    }
    if (v > -1) {
        sub_0007FD30(t->p2C, ctx->p34, v);
        sub_0007FD60(ctx->p20, v);
    }
    return 4;
}

/* 0x0001E370: command: set a 2D position on the target (or its controller);
   returns the operand size 8. */
int r1b_CmdSetPos(R1bCmdCtx *ctx, const float *arg, R1bCmdTarget *t)
{
    float pos[2];
    pos[0] = arg[0];
    pos[1] = arg[1];
    if (t->ctl == 0) {
        sub_00074DF0(ctx->p20, ctx->p44, pos);
        return 8;
    }
    t->ctl->flags1C |= 2;
    t->ctl->x38 = pos[0];
    t->ctl->y3C = pos[1];
    return 8;
}

/* 0x0001E3F0: command: copy a 4-word colour to +0x90; returns 16. */
int r1b_CmdColor90(R1bColorObj *o, const int32_t *arg)
{
    o->c90[0] = arg[0];
    o->c90[1] = arg[1];
    o->c90[2] = arg[2];
    o->c90[3] = arg[3];
    return 16;
}

/* 0x0001E430: command: copy a 4-word colour to +0x50; returns 16. */
int r1b_CmdColor50(R1bColorObj *o, const int32_t *arg)
{
    o->c50[0] = arg[0];
    o->c50[1] = arg[1];
    o->c50[2] = arg[2];
    o->c50[3] = arg[3];
    return 16;
}

/* 0x0001E460: command: copy a 4-word colour to +0x60; returns 16. */
int r1b_CmdColor60(R1bColorObj *o, const int32_t *arg)
{
    o->c60[0] = arg[0];
    o->c60[1] = arg[1];
    o->c60[2] = arg[2];
    o->c60[3] = arg[3];
    return 16;
}

/* 0x0001E490: command: fill the four words at +0x70 with one value; returns 16. */
int r1b_CmdFill70(R1bColorObj *o, const int32_t *arg)
{
    o->c70[0] = *arg;
    o->c70[1] = *arg;
    o->c70[2] = *arg;
    o->c70[3] = *arg;
    return 16;
}

/* 0x0001EB80: detach the nodes of an object and of its chain's controllers. */
void r1b_RecDetachNodes(R1bRec *r)
{
    if (r->part20 && r->part20->attached80) r4_NodeDetach(r->part20);
    do {
        if (r->part && r->part->attached80) r4_NodeDetach(r->part);
        if (r->sub30 && r->sub30->node14 && r->sub30->node14->attached80)
            r4_NodeDetach(r->sub30->node14);
        r = r->next;
    } while (r);
}

/* 0x0001EC10: set value v on every part (and every type-1 part item) of a chain. */
void r1b_RecSetPartValue(R1bRec *r, int v)
{
    R1bPart *p;
    int i;
    do {
        p = r->part20;
        if (p) {
            switch (p->kind) {
            case 1:
                p->vB8 = v;
                for (i = 0; i < r->part20->count; i++)
                    ((R1bPartItem108 *)r->part20->items)[i].vD0 = v;
                break;
            case 9:
                p->vB8 = v;
                break;
            }
        }
        r = r->next;
    } while (r);
}

/* 0x0001EC90: set the global value at 0x0037C4A0 on a part tree. */
void r1b_PartsSetF94(R1bPart *p)
{
    do {
        p->f94 = r1b_f37C4A0;
        if (p->link) r1b_PartsSetF94(p->link);
        p = p->next;
    } while (p);
}

/* 0x0001F460: command: create a controller for the target, or flag the
   existing one; returns 0. */
int r1b_CmdMakeCtl(int a, int unused, R1bCmdTarget *t)
{
    void *p;
    (void)unused;
    if (t->ctl == 0) {
        p = sub_00053AB0(0x14, 0, 0xEFF);
        sub_0001EFE0(p, t->p20, a);
        return 0;
    }
    t->ctl->flags1C |= 1;
    return 0;
}

/* 0x00020170: release every record of a table node, then its table and itself. */
void r1b_TableFree(R1bLNode *t)
{
    int i;
    for (i = 0; i < t->count; i++) sub_0001F300(&t->recs[i]);
    sub_00053880(t->recs);
    sub_00053880(t);
}
