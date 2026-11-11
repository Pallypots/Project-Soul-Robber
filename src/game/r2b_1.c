/* Area r2b, group 1: Jack's character helpers (0x000D0000..0x000D0E99). Names inferred. */
#include "r2b.h"

/* 0x000D0000: set the stat word at g_stats+0xE0 to 8 and, unless g_stats mode is 2,
   pass Jack's model child 0 to 0x0CED50. */
void r2b_PlayerShowModel(void)
{
    int mode = g_stats.unk1B8;
    r2b_g41FFA0 = 8;
    if (mode != 2)
        sub_000CED50(sub_0001D290(g_playerObj, 0));
}

/* 0x000D04E0: copy a colour (4 words) into +0xD0 of the render data of every
   visible node of a sibling chain. */
void r2b_ModelSetColor(R2bModelNode *n, const uint32_t *col)
{
    if (!n)
        return;
    do {
        if ((n->flags0C & 1) && n->rend20) {
            R2bRender *r = n->rend20;
            r->colD0[0] = col[0];
            r->colD0[1] = col[1];
            r->colD0[2] = col[2];
            r->colD0[3] = col[3];
        }
        n = n->next3C;
    } while (n);
}

/* 0x000D0530: hide (show < 0) or show child id of Jack's model. */
void r2b_ShowChild(R2bPlayer *p, int show, int id)
{
    if (show < 0)
        r1_ChildHide(p->modelFD8, id);
    else
        r1_ChildShow(p->modelFD8, id);
}

/* 0x000D0560: start animation anim on model child key unless it is already the
   current animation. */
void r2b_SetChildAnim(R2bPlayer *p, int anim, int key)
{
    R2bModelNode *n = (R2bModelNode *)sub_0001D290(p->modelFD8, key);
    if (p->anim128 != anim && n) {
        n->part30->i08 = -1;
        sub_000832D0(n->part30, anim);
    }
}

/* 0x000D0850: keep the +0x604 effect alive only in mode 2 with animations
   0x200/0x203 while the model lacks flag 0x10000. */
void r2b_UpdateEffect604(R2bPlayer *p)
{
    if (p->mode1B8 == 2 && p->flags150 >= 0) {
        if ((p->anim128 != 0x200 && p->anim128 != 0x203) ||
            (p->modelFD8->flags0C & 0x10000)) {
            if (p->h604) {
                sub_00033A70(p->h604);
                p->h604 = 0;
            }
        } else if (!p->h604)
            p->h604 = adc_StatD0030(p, 0x3A);
    } else if (p->h604) {
        b16_Free33A40(p->h604);
        p->h604 = 0;
    }
}

/* 0x000D08F0: 1 when event 0xF8 is set or the +0xE04 counter allows it
   (>= 10, or > 0 when any is set), else -1. */
int r2b_CheckE04(R2bPlayer *p, int any)
{
    if (sub_000D9A70(0xF8))
        return 1;
    if (!any) {
        if (p->count_E04 >= 10)
            return 1;
        return -1;
    }
    if (p->count_E04 <= 0)
        return -1;
    return 1;
}

/* 0x000D0DC0: look up entry (a, b) in the pool and copy its two vectors (+0x40, +0x30)
   out; 1 on success, -1 when missing. */
int r2b_PoolGetA(int a, int b, void *dst40, void *dst30)
{
    void *ctx = r2b_ctx42C8E4->p54;
    void *pool = r1b_Pool80970();
    uint8_t *e;
    sub_000822D0(ctx, pool, a, b, 0, 0);
    e = sub_00080CF0(pool, a);
    if (!e)
        return -1;
    sub_000F5D40(dst40, e + 0x40);
    sub_000F5D40(dst30, e + 0x30);
    return 1;
}

/* 0x000D0E30: like 0x0D0DC0 with the second pool lookup pair (0x0824F0 / 0x080CB0). */
int r2b_PoolGetB(int a, int b, void *dst40, void *dst30)
{
    void *ctx = r2b_ctx42C8E4->p54;
    void *pool = r1b_Pool80970();
    uint8_t *e;
    sub_000824F0(ctx, pool, a, b, 0, 0);
    e = sub_00080CB0(pool, a, b);
    if (!e)
        return -1;
    sub_000F5D40(dst40, e + 0x40);
    sub_000F5D40(dst30, e + 0x30);
    return 1;
}

/* 0x000D1670: load the four textures of table 0x2E7C80 onto model child 1 and the
   five of table 0x2E7D38 onto child 2. */
void r2b_LoadTexA(R2bPlayer *p)
{
    R2bModelNode *a = (R2bModelNode *)sub_0001D290(p->modelFD8, 1);
    R2bModelNode *b = (R2bModelNode *)sub_0001D290(p->modelFD8, 2);
    int i;
    for (i = 0; i < 4; i++)
        sub_0003C2D0(&r2b_tex417880[i], a->rend20, r2b_ids2E7C80[i]);
    for (i = 0; i < 5; i++)
        sub_0003C2D0(&r2b_tex417880[8 + i], b->rend20, r2b_ids2E7D38[i]);
}

/* 0x000D1700: load the four textures of table 0x2E7C80 onto model child 2. */
void r2b_LoadTexB(R2bPlayer *p)
{
    R2bModelNode *b = (R2bModelNode *)sub_0001D290(p->modelFD8, 2);
    int i;
    for (i = 0; i < 4; i++)
        sub_0003C2D0(&r2b_tex417880[16 + i], b->rend20, r2b_ids2E7C80[i]);
}

/* 0x000D2180: clear stat flags 2 and 1 and free their effect handles. */
void r2b_ClearEffects(void)
{
    g_stats.flags &= ~2u;
    if (r2b_h4204DC) {
        b16_Free33A40(r2b_h4204DC);
        r2b_h4204DC = 0;
    }
    g_stats.flags &= ~1u;
    if (r2b_h4204D8) {
        b16_Free33A40(r2b_h4204D8);
        r2b_h4204D8 = 0;
    }
}

/* 0x000D2A00: request a change of the stats mode; -1 when already in it. */
int r2b_SetMode(int mode)
{
    if (g_stats.unk1B8 == mode)
        return -1;
    sub_000D2440(&g_stats);
    r2b_g42007C = mode;
    r2b_flags420010 |= 0x80000000u;
    r2b_g420080 = 0x20;
    return 1;
}
