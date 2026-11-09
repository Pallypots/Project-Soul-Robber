/* Area a3c, group 2: table accessors near 0x00039650..0x0003ABE0. Names inferred. */
#include "a3c.h"

/* 0x00039650: mark both enable words. */
void a3c_EnableBoth(void)
{
    *(int32_t *)&a3c_tbl3DB944[0] = 1;
    a3c_g3DCD94 = 1;
}

/* 0x00039810: record i of the 0x2C-byte table. */
A3cRec2C *a3c_Rec2CGet(int i) { return &a3c_tbl3DA4A8[i]; }

/* 0x000398C0: record i of the 0x1450-byte table. */
A3cRec1450 *a3c_Rec1450Get(int i) { return &a3c_tbl3DB944[i]; }

/* 0x0003ABC0: key three links deep equals k. */
int a3c_DeepKeyIs(A3cLink0C *p, int k)
{
    return ((A3cKey14 *)p->next->next)->key == k;
}

/* 0x0003ABE0: clear the list head and field +0x10. */
void a3c_ClearWithTail(A3cRec10 *p)
{
    a3c_Clear16((A3cQuad *)p);
    p->f10 = 0;
}
