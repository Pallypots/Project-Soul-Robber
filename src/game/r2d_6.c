/* Area r2d, group 6: stage events, effect tick, sound banks and object list helpers (0x000E3EB0..0x000EDF07). Names inferred. */
#include "r2d.h"

/* 0x000E3EB0: start effect (0x48510(a) + b) at part c of the object found
   by (kind, id) (kind 1 = the player); returns its handle or -1. */
int r2d_StageFxAt(int a, int b, int kind, int id, int c)
{
    int fx = sub_00048510(a) + b;
    void *o;
    if (kind == 1)
        o = g_playerObj;
    else
        o = sub_0001D080(r2d_ctx->list1E8, kind, id);
    if (!o)
        return -1;
    return sub_000494D0(fx, (uint8_t *)sub_0001D0F0(o, c) + 0x70, 0);
}

/* 0x000E3FA0: mark every track (1, 2, 5, 6, 7) as played up to the current
   stream position. */
void r2d_StageMarkTracks(R2dStage *o)
{
    uint32_t pos = r2d_StageStreamPos(o);
    r2b_TrackMarkBefore(o, 1, pos, 0);
    r2b_TrackMarkBefore(o, 2, pos, 0);
    r2b_TrackMarkBefore(o, 5, pos, 0);
    r2b_TrackMarkBefore(o, 6, pos, 0);
    r2b_TrackMarkBefore(o, 7, pos, 0);
}

/* 0x000E3FF0: clear the model value +8 of the object found by (kind, id)
   (kind 1 = the player; kind 3 repeats it 0xF3140(id) times). */
void r2d_StageClearModel(int kind, int id)
{
    int n = 1;
    R2dRec150 *o;
    if (kind == 3)
        n = sub_000F3140(id);
    if (kind == 1)
        o = (R2dRec150 *)g_playerObj;
    else
        o = sub_0001D080(r2d_ctx->list1E8, kind, id);
    if (o && n > 0) {
        do {
            o->m30->i08 = -1;
        } while (--n);
    }
}

/* 0x000E40F0: apply 0x1AEDD0(v) to the model of each of the n parts of the
   object found by (kind, id) (kind 1 = the player; kind 3 has
   0xF3140(id) parts). */
void r2d_StageModelSet(int kind, int id, float v)
{
    int n = 1;
    R2dRec150 *o;
    if (kind == 3)
        n = sub_000F3140(id);
    if (kind == 1)
        o = (R2dRec150 *)g_playerObj;
    else
        o = sub_0001D080(r2d_ctx->list1E8, kind, id);
    if (o && n > 0) {
        do {
            sub_001AEDD0(o->m30->p14, v);
            o++;
        } while (--n);
    }
}

/* 0x000E99F0: run one tick of every effect record by its state.
   calls 0x000E8220/0x000E82E0/0x000E83A0/0x000E8D90/0x000E8E80 with ESI=f */
void r2d_FxTickAll(void)
{
    R2dFx *f;
    int i;
    for (i = 0; i < 32; i++) {
        f = &r2c_fx3F1B5C[i];
        switch (f->state04) {
        case 0:
            f->flags &= ~1u;
            break;
        case 1:
            sub_000E8220(f);
            break;
        case 2:
            sub_000E82E0(f);
            break;
        case 3:
            sub_000E83A0(f);
            break;
        case 4:
            sub_000E8D90(f);
            break;
        case 5:
            sub_000E8E80(f);
            break;
        }
    }
}

/* 0x000EC350: open sound set (a, b) unless one is open. */
void r2d_BankOpen(int a, int b)
{
    void *r;
    if (aec_3F59D4)
        return;
    r = sub_0001F210(a, b);
    aec_3F59D0 = r;
    aec_3F59D4 = ((int32_t *)r)[2];
    sub_0001DA40(r);
    aec_3F59E8 = a;
    aec_3F59EC = b;
    aec_3F59F0 = 0;
}

/* 0x000EC3A0: load bank i (0..6) if it is not resident; returns 0, or -1
   with no sound set open or a bad index. */
int r2d_BankLoad(int i)
{
    if (!aec_3F59D4)
        return -1;
    if (i < 0 || i >= 7)
        return -1;
    if (!sub_0004F6D0(r2d_banks318680[i])) {
        sub_000512D0(r2d_banks318680[i], sub_00053AB0(sub_0004F680(r2d_banks318680[i]), 0, 0x1DE));
        aec_3F59E4 = i;
    }
    return 0;
}

/* 0x000ECB60: flush pending bank work, then run the current bank if it is
   resident. */
void r2d_BankRun(void)
{
    if (aec_3F59DC)
        sub_000EC770();
    if (aec_3F59E4 < 0 || aec_3F59E4 >= 7)
        for (;;) ;
    if (sub_0004F6D0(r2d_banks318680[aec_3F59E4]))
        sub_0004F5D0(r2d_banks318680[aec_3F59E4]);
}

/* 0x000ECC10: load the named data for bank record i (-1 = none). */
void r2d_BankLoadData(int i)
{
    R2dBank *b;
    uint8_t *d;
    if (i == -1)
        return;
    if (i >= 5)
        for (;;) ;
    b = &aec_recs1C[i];
    d = sub_00037550(r2d_names3187A0[i], 0);
    b->data14 = d;
    b->body18 = d + 0x10;
}

/* 0x000ED100: first active entry of the list, or NULL.
   regargs: l=ESI */
R2dEnt *r2d_ListFirstActive(R2dList *l)
{
    R2dEnt *e = l->arr08;
    int i = 0;
    if (e)
        for (i = 0; i < l->count; i++, e++)
            if (e->flags0C & 1)
                break;
    return i < l->count ? e : 0;
}

/* 0x000ED150: the active entry after cur in the list, or NULL (cur itself
   when the list or cur is NULL).
   regargs: l=ECX cur=EAX */
R2dEnt *r2d_ListNextActive(R2dList *l, R2dEnt *cur)
{
    R2dEnt *e;
    int i;
    if (!l || !cur)
        return cur;
    e = l->arr08;
    if (!e)
        return 0;
    for (i = 0; i < l->count; i++, e++)
        if (e == cur)
            break;
    if (i >= l->count)
        return 0;
    for (e++, i++; i < l->count; i++, e++)
        if (e->flags0C & 1)
            break;
    return i < l->count ? e : 0;
}

/* 0x000ED780: destroy an active object whose component 0xD agrees (its
   +0x24 callback returns non-zero); returns 1 when destroyed.
   calls 0x000ED380 with EAX=o */
int r2d_ObjDestroy(R2dEnt *o)
{
    R2dComp *c;
    if (!o || !(o->flags0C & 1))
        return 0;
    c = sub_0001D960(o, 0xD);
    if (!c || !c->fn24(o))
        return 0;
    r2_ListDrop(o);
    o->flags0C &= ~1u;
    sub_0001EB80(o);
    sub_000362B0(o);
    sub_0001D190(o);
    sub_0001B3F0(o);
    return 1;
}

/* 0x000EDDA0: the object's component value +0x14 (kind 0xC objects go
   through 0xA2050); with out, also store its part pointer. */
int r2d_ObjCompValue(R2dEnt *o, uint8_t **out)
{
    R2dComp *c;
    if (((int32_t *)o)[1] == 0xC)
        return sub_000A2050(o, out);
    c = sub_0001D960(o, 0xD);
    if (!c)
        for (;;) ;
    if (out)
        *out = sub_0001D0F0(o, c->v14);
    return c->v14;
}

/* 0x000EDE00: the object's position raised by its component height +0x18
   (origin when there is no object). */
void r2d_ObjTopA(R2dNode *o, float *out)
{
    R2dComp *c;
    if (!o) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = 1.0f;
        return;
    }
    sub_000F5D40(out, o->pos60);
    c = sub_0001D960(o, 0xD);
    if (c)
        out[1] = c->f18 + out[1];
}

/* 0x000EDE60: as 0x0EDE00 with the component height +0x1C. */
void r2d_ObjTopB(R2dNode *o, float *out)
{
    R2dComp *c;
    if (!o) {
        out[0] = 0.0f;
        out[1] = 0.0f;
        out[2] = 0.0f;
        out[3] = 1.0f;
        return;
    }
    sub_000F5D40(out, o->pos60);
    c = sub_0001D960(o, 0xD);
    if (c)
        out[1] = c->f1C + out[1];
}

/* 0x000EDEC0: fill a target record from the node: position + offset, w = 1
   and the two words +0xB0/+0xB4. */
void r2d_ObjTarget(R2dNode *o, float *out)
{
    if (!o || !out)
        return;
    r4c_VecAdd(out, o->pos60, o->vA0);
    out[3] = 1.0f;
    ((int32_t *)out)[4] = o->vB0;
    out[5] = o->fB4;
}
