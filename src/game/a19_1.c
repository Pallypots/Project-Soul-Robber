/* Area a19, 0x00190530-0x00196A21. Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a19.h"

/* 0x00190530: clear work float +0x1C. */
void a19_ClearWork1C(void *unused, a19_Actor *a)
{
    A19_F1C(a->work) = 0.0f;
}

/* 0x00191450: clear flag 0x20. */
void a19_ClearFlag20(a19_Actor *a)
{
    a->flagsC &= ~0x20u;
}

/* 0x00191460: vector op on work +0x14/+0x30, then clear +0x20. */
void a19_WorkVec14(void *unused, a19_Actor *a)
{
    a19_Work *w = a->work;
    a19_VecOp(w->v14, w->v30);
    w->f20 = 0.0f;
}

/* 0x00191510: clear work float +0x24. */
void a19_ClearWork24(void *unused, a19_Actor *a)
{
    a->work->f24 = 0.0f;
}

/* 0x00192450: first field of record i (0..3) at 0x00400A88, else 0. */
int a19_GetRec400A88(int i)
{
    if (i < 0 || i >= 4)
        return 0;
    return a19_g400A88[i].f0;
}

/* 0x00193DF0: zero the 0x69-dword block at 0x00400CA8. */
void a19_Clear400CA8(void)
{
    int i;
    for (i = 0; i < 0x69; i++)
        a19_g400CA8[i] = 0;
}

/* 0x00194770: set flag 0x40. */
void a19_SetFlag40(a19_Actor *a)
{
    a->flags10 |= 0x40;
}

/* 0x00195C50: vector op on work +0x44/+0x70, then clear +0x50. */
void a19_WorkVec44(void *unused, a19_Actor *a)
{
    a19_Work *w = a->work;
    a19_VecOp(w->v44, w->v70);
    w->f50 = 0.0f;
}

/* 0x00195D10: clear work float +0x20. */
void a19_ClearWork20(void *unused, a19_Actor *a)
{
    a->work->f20 = 0.0f;
}

/* 0x00196A10 */
void a19_Clear401828(void)
{
    a19_g401830 = 0;
    a19_g401828 = 0;
    a19_g40182C = 0;
}


