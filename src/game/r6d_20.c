/* Area r6d: event scene and stage object helpers around 0x00089040-0x00089876 (r6d_20). Names inferred. */
#include "r6d.h"

/* 0x00089040: step the leave sequence of the current event scene; 1 while it runs.
   calls 0x00088240 with ESI=&scene */
int r6d_ScnLeaveCurrent(void)
{
    if (!a80_curMode)
        return 0;
    if (r6c_ScnLeaveStep(&r6d_scenes2E0680[a80_curMode]))
        return 1;
    a80_curMode = 0;
    return 0;
}

/* 0x000895A0: the n-th matching node of an object and the next matching node after it. */
void r6d_NodePairAt(R6dStageObj *o, int n, void **out)
{
    int i = 0;
    void *p = sub_0008B290(o->nodes, 1, 1);
    while (p) {
        if (i >= n) {
            out[0] = p;
            out[1] = sub_0008B290(a6b_Node_Next(p), 1, 1);
            return;
        }
        p = sub_0008B290(a6b_Node_Next(p), 1, 1);
        i++;
    }
    out[0] = 0;
    out[1] = 0;
}

/* 0x00089740: switch the object's material, keeping reference counts and the render state. */
void r6d_StageSetMaterial(R6dStageObj *o, R6dMaterial *m)
{
    if (o->ext->material == m)
        return;
    if (o->ext->material)
        a8b_RefDec(o->ext->material);
    if (m) {
        a8b_RefInc(m);
        sub_0003E200(4, m->tex);
    } else {
        sub_0003E200(4, 0);
    }
    o->ext->material = m;
}

/* 0x000897B0: destroy a stage object and everything it owns; returns 0. */
int r6d_StageObjFree(R6dStageObj *o)
{
    unsigned n;
    uint8_t *p;
    R6dStateBlk *blk;
    if (o) {
        sub_000893C0(o);
        sub_000AD090(0, 0);
        r6b_ObjDestroy(o->handle);
        n = r6b_HolderCountSlots(&o->ext->holder);
        p = (uint8_t *)r6b_HolderData(&o->ext->holder);
        sub_000375A0();
        for (; n > 0; n--) {
            sub_000376D0(p);
            p += 0x48;
        }
        blk = (R6dStateBlk *)r6b_HolderBlk(&o->ext->holder);
        *(R6dStateBlk *)sub_000390A0() = *blk;
        sub_00037BB0(4, 0);
        r6b_HolderFree(&o->ext->holder);
        r6b_FreeRecs4(&o->ext->recs);
        sub_0007AB10(a80_ctx42C8E4, &o->ext->tint);
        sub_0008BCC0(o->ext);
        sub_0008BCC0(o);
        sub_000360E0();
    }
    return 0;
}
