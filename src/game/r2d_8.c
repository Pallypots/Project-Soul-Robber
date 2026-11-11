/* Area r2d, group 8: list pruning, track targets and model reset (0x001134B0..0x00113B19). Names inferred. */
#include "r2d.h"

/* 0x001134B0: release every list entry of the owner that is not in state 2
   (unlink it and reset it). */
void r2d_PListPrune(R2dPOwner *o)
{
    R2dPEnt *e, *next;
    if (!o->head60)
        return;
    for (e = o->head60; e; e = next) {
        next = e->next24;
        if (e->state == 2)
            continue;
        if (e->prev20)
            e->prev20->next24 = e->next24;
        if (e->next24)
            e->next24->prev20 = e->prev20;
        if (o->head60 == e)
            o->head60 = e->next24;
        e->state = 0;
        e->v04 = -1;
        e->f08 = 0.0f;
        e->v0C = 0;
        e->v10 = 0;
        e->v14 = 0;
        e->v18 = 0;
        e->v1C = 0;
        e->prev20 = 0;
        e->next24 = 0;
    }
}

/* 0x00113600: the tracker's target offset from a: mode 1 = its object's
   position, mode 2 = its own vector at +0x104, otherwise (0, 0, 0, 1). */
void r2d_TrkTargetOffset(const uint8_t *a, R2dTrkObj *t, float *out)
{
    switch (t->mode0F8) {
    case 1:
        sub_001AD9F0(out, t->ref104 + 0x60, a + 0x60);
        return;
    case 2:
        sub_001AD9F0(out, &t->ref104, a + 0x60);
        return;
    }
    out[0] = 0.0f;
    out[1] = 0.0f;
    out[2] = 0.0f;
    out[3] = 1.0f;
}

/* 0x00113AA0: clear the control's 0x280 bits and the models' bit 1, run
   0x113090 twice, reset the model weight to 1 and refresh its node. */
void r2d_GfxReset(R2dGfxNode *m, R2dGfxCtl *o)
{
    R2dGfxNode *n;
    o->flags4C &= ~0x280u;
    for (n = m; n; n = n->next3C)
        if (n->p30 && n->p30->p14)
            n->p30->p14->flagsB8 &= ~2u;
    sub_00113090(m, o, o->v64);
    sub_00113090(m, o, o->v64);
    sub_000EE760(m, 1.0f);
    m->vD0 = sub_0001BC40(m);
    sub_000C75E0(m);
}

