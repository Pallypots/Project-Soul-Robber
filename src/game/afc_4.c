/* Area afc, group 4: actor state handlers 0x000F9D10-0x000FB280. Names inferred. */
#include "afc.h"

/* 0x000F9D10: reset both part animations then play animation 0x18. */
void afc_PlayAnim18(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    afc_SetBothAnims(a, -1);
    afc_SetBothAnims(a, 0x18);
}

/* 0x000FA710: play animation 0x3A and clear +0x9C. */
void afc_PlayAnim3A(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    afc_SetBothAnims(a, 0x3A);
    a->v9C = 0;
}

/* 0x000FAF30: clear +0x178 and +0x9C. */
void afc_ClearTimers(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    a->f178 = 0.0f;
    a->v9C = 0;
}

/* 0x000FB280: when the node is active, mark +0xBC and hide the actor. */
void afc_HideWhenActive(AfcActor *o)
{
    AfcActor *a = afc_DispatchByType(o);
    if (afc_NodeActive(o)) {
        a->wBC = 1;
        afc_SetVisible(a, 0);
    }
}
