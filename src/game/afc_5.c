/* Area afc, group 5: type-5 boss body handlers 0x000FB2C0-0x000FBD20. Names inferred. */
#include "afc.h"

/* 0x000FB2C0: flag every model in the actor chain (bit 2 at +0xB8) and enter mode 2. */
void afc_ChainMarkModels(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    AfcActor *n;
    for (n = o; n != 0; n = n->next) {
        if (n->node != 0 && n->node->model != 0)
            n->node->model->flagsB8 |= 2;
    }
    o->vD0 = 2;
    a->f178 = 0.0f;
}

/* 0x000FB3B0: count an exclamation and play animation 0x13. */
void afc_Exclaim(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    a->v9C = 0;
    Grade_AddExclamations(1);
    afc_SetBothAnims(a, 0x13);
}

/* 0x000FB4A0: horizontal distance from a point to the reference point 0x00318E18. */
float afc_DistToRef(void *p)
{
    AfcVec4 d;
    sub_001AD9F0(&d, p, &afc_vec318E18);
    return afc_VecLengthXZ(&d);
}

/* 0x000FB990: allocate the boss body singleton. */
void afc_BodyCreate(void)
{
    void *p = sub_00053AB0(sub_000F30E0(5) * 0x208, 0, 0xFF);
    afc_body = (AfcSingleton *)p;
    afc_bodyState = (AfcActor *)p;
    sub_000F69E0(p);
}

/* 0x000FB9D0: free the boss body singleton. */
void afc_BodyDestroy(void)
{
    afc_bodyState = 0;
    sub_00053880(afc_body);
    afc_body = 0;
}

/* 0x000FBA00: change the body's state and clear +0xBC. */
void afc_BodySetState(int state)
{
    AfcPart *p = afc_body->part8C;
    AfcActor *a;
    if (p == 0) for (;;) ;
    a = afc_bodyState;
    if (a == 0) for (;;) ;
    sub_000F3D10(p, a, state);
    afc_body->wBC = 0;
}

/* 0x000FBA50: set the same animation on both body parts. */
void afc_BodySetAnims(int anim)
{
    AfcPart *p;
    if (afc_body == 0) for (;;) ;
    p = afc_body->part8C;
    if (p == 0) for (;;) ;
    sub_000832D0(p->node, anim);
    sub_000832D0(afc_body->part90->node, anim);
}

/* 0x000FBAF0: body singleton (must exist). */
AfcSingleton *afc_GetBody(void)
{
    if (afc_body == 0) for (;;) ;
    return afc_body;
}

/* 0x000FBD20: copy a message word into the body's +0xA8 when the helper is armed. */
void afc_BodyTakeMsg(AfcMsg *m)
{
    if (afc_GetHelper()->vE8 != 0)
        afc_body->wA8 = m->w0C;
}

/* 0x000FB080: play animation 0x42, advance +0x184 by +0x118 over a frame, clear +0xF0. */
void afc_StartMove42(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    afc_SetBothAnims(a, 0x42);
    sub_001ADB60(&a->vec184, &a->vec118, a50_frameUnits);
    a->fF0 = 0.0f;
}

/* 0x000FB130: play animation 0x43 and clear +0x9C/+0x178. */
void afc_PlayAnim43(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    afc_SetBothAnims(a, 0x43);
    a->v9C = 0;
    a->f178 = 0.0f;
}
