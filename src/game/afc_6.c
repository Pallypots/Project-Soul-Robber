/* Area afc, group 6: helper singleton 0x000FC490-0x000FC710. Names inferred. */
#include "afc.h"

/* 0x000FC490: free the helper singleton. */
void afc_HelperDestroy(void)
{
    sub_00053880(afc_helper);
    afc_helper = 0;
}

/* 0x000FC4B0: helper's first part (must exist). */
AfcPart *afc_HelperPart(void)
{
    AfcPart *p = afc_helper->part8C;
    if (p == 0) for (;;) ;
    return p;
}

/* 0x000FC4D0: helper singleton (must exist). */
AfcSingleton *afc_GetHelper(void)
{
    if (afc_helper == 0) for (;;) ;
    return afc_helper;
}

/* 0x000FC710: set the helper's animation. */
void afc_HelperSetAnim(int anim)
{
    AfcPart *p = afc_helper->part8C;
    if (p == 0) for (;;) ;
    sub_000832D0(p->node, anim);
}

/* 0x000FD190: after 3.5 s in the current state, move the helper to state 2. */
void afc_HelperTimeout(void *ctx, AfcActor *o)
{
    if (o->stateTime > 3.5f)
        sub_000F3D10(afc_helper->part8C, (AfcActor *)afc_helper, 2);
}
