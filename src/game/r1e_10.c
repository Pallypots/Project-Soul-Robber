/* Area r1e, group 10: save image fixup, effect list release, draw helpers, cell pages 0x0005C380..0x0005EEA0. Names inferred. */
#include "r1e.h"

/* 0x0005C380: unpack a version 3 "SES" image into dst and rebuild its
   internal pointers. */
void r1e_SesUnpack(R1eSes *dst, R1eSesFile *src)
{
    int i;
    if (src->magic == 0x534553 && src->version == 3) {
        *dst = src->body;
        dst->tab = dst->tabData;
        for (i = 0; i < dst->count; i++)
            dst->ents[i].block = &dst->blocks[i];
    }
}

/* 0x0005C510: release every effect on list B, freeing the sound owner
   slots that belong to it. */
void r1e_FxListBFree(void)
{
    R1eRes *n, *next;
    R1eFx *f;
    R1eSndSlot *s;
    int k;
    for (n = r1e_fxListB3E5AAC.first; n != 0; n = next) {
        next = n->next;
        r1c_SndOwnerStop(n->data);
        f = (R1eFx *)n->data;
        if (f != 0) {
            for (s = r1e_sndSlots3E5AC0, k = 32; k != 0; k--, s++) {
                if (s->owner == f) {
                    s->handle = -1;
                    s->owner = 0;
                }
            }
            sub_0003D8C0((R1eRes *)&f->link);
            sub_00036B10((char *)f - 0x10);
        }
    }
}

/* 0x0005CA80: free the scene's effects (0x0005CA00), then list B. */
void r1e_FxFreeAll(void)
{
    r1e_SceneFxFree();
    r1e_FxListBFree();
}

/* 0x0005E8B0: draw with 0x0005D620 using the object's style.
   calls 0x0005D620 with EAX=0 EDX=0 stack=(a c style) */
int r1e_DrawPlain(int a, R1eDrawObj *o, int c)
{
    return sub_0005D620(0, 0, a, c, o->ctx->u2C.style);
}

/* 0x0005E8E0: draw with 0x0005D620 at the current item's position in its
   list.
   calls 0x0005D620 with EAX=index EDX=item stack=(a c list) */
int r1e_DrawItem(int a, R1eDrawObj *o, int c)
{
    R1eDrawCtx *x = o->ctx;
    R1eSceneItem *it = *x->u2C.items;
    R1eUList *l = it->fx->list;
    int idx = r1e_UsedIndexOf(l, sub_0003EB10(&x->vars->ents[1]));
    return sub_0005D620(idx, (int)it, a, c, (int)l);
}

/* 0x0005E930: free all cell pages and both page tables. */
void r1e_CellPagesFree(void)
{
    int i;
    if (a5b_cellTables != 0) {
        for (i = 0; i < 64; i++) {
            if (r1e_cellOwned3E604C[i] != 0) {
                if (a5b_cellTables[i] != 0)
                    sub_00053880(a5b_cellTables[i]);
                r1e_cellOwned3E604C[i] = 0;
            }
            a5b_cellTables[i] = 0;
        }
        sub_00053880(a5b_cellTables);
        a5b_cellTables = 0;
        sub_00053880(r1e_cellOwned3E604C);
        r1e_cellOwned3E604C = 0;
    }
}

/* 0x0005EEA0: install page pg in slot i (freeing an owned old page) and
   turn its row length into the second row pointer. */
void r1e_CellPageSet(int i, R1ePage *pg)
{
    if (r1e_cellOwned3E604C[i] != 0) {
        if (a5b_cellTables[i] != 0)
            sub_00053880(a5b_cellTables[i]);
        r1e_cellOwned3E604C[i] = 0;
    }
    a5b_cellTables[i] = 0;
    r1e_cellOwned3E604C[i] = 0;
    pg->row[0].p = pg->data;
    pg->row[1].p = pg->row[0].p + pg->row[1].n;
    a5b_cellTables[i] = pg;
}
