/* Area r1d, group 4: texture base packets and bone links 0x0001EDE0..0x0001F070. Names inferred. */
#include "r1d.h"

/* 0x0001EDE0: queue register 0x4C from the current texture's base bits,
   build the packet at p and switch to mode 2; returns the packet end. */
void *r1d_TexBasePkt2(void *p)
{
    R1dTex *t = sub_001B9650(-1);
    uint64_t v = ((uint64_t)(t->reg[0] & 0x3FE0) | 0x1FFFFFE001000000ull) >> 5;
    void *r;
    r1c_ReqPush(0x4C, (int)(uint32_t)v, (int)(uint32_t)(v >> 32));
    r = sub_00038F10(p);
    sub_001A27D0(2);
    return r;
}

/* 0x0001EE30: as 0x0001EDE0 but switches to mode 3. */
void *r1d_TexBasePkt3(void *p)
{
    R1dTex *t = sub_001B9650(-1);
    uint64_t v = ((uint64_t)(t->reg[0] & 0x3FE0) | 0x1FFFFFE001000000ull) >> 5;
    void *r;
    r1c_ReqPush(0x4C, (int)(uint32_t)v, (int)(uint32_t)(v >> 32));
    r = sub_00038F10(p);
    sub_001A27D0(3);
    return r;
}

/* 0x0001EF40: task callback: copy every bone matrix of m onto the bones of
   the task's target model. */
void r1d_BonesFollow(R1dModel *m, R1dMTask *t)
{
    int i;
    switch (m->type) {
    case 1: {
        R1dBone1 *src = (R1dBone1 *)m->bones;
        R1dBone1 *dst = (R1dBone1 *)t->node->model->bones;
        for (i = m->count; i > 0; i--, src++, dst++)
            sub_001ADA40(dst->m, src->m);
        break;
    }
    case 9: {
        R1dBone9 *src = (R1dBone9 *)m->bones;
        R1dBone9 *dst = (R1dBone9 *)t->node->model->bones;
        for (i = m->count; i > 0; i--, src++, dst++)
            sub_001ADA40(dst->m, src->m);
        break;
    }
    }
}

/* 0x0001EFE0: make dst's skeleton follow src's (same type and bone count)
   through task t. */
void r1d_BonesLink(R1dMTask *t, R1dMNode *src, R1dMNode *dst)
{
    R1dModel *a, *b;
    if (t == 0 || src == 0 || dst == 0) return;
    a = src->model;
    if (a == 0) return;
    b = dst->model;
    if (b == 0) return;
    if (a->type != b->type) return;
    switch (a->type) {
    case 1:
        if (a->count != b->count) return;
        break;
    case 9:
        if (a->count != b->count) return;
        break;
    }
    sub_001B2150(t);
    t->fn = r1d_BonesFollow;
    t->node = dst;
    dst->model->fl->flags |= 0x20;
    r4_HookAppendAC(src->model, t);
}

/* 0x0001F070: apply selection `which` (0 or 1) of a node to its model;
   1 when applied, 0 otherwise. */
int r1d_BonesSelect(R1dMNode *n, int which)
{
    R1dModel *m;
    R1dBone1 *b;
    int v, i;
    if (n == 0) return 0;
    m = n->model;
    if (m == 0) return 0;
    if (which < 0 || which > 1) return 0;
    v = n->sel[which];
    if (v < 0) return 0;
    switch (m->type) {
    case 1:
        b = (R1dBone1 *)m->bones;
        for (i = 0; i < m->count; i++, b++)
            b->sel = n->sel[which];
        return 1;
    case 9:
        m->sel = v;
        return 1;
    }
    return 0;
}
