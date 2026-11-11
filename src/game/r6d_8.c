/* Area r6d: pause screen helpers around 0x0006D310-0x0007227D (r6d_8). Names inferred. */
#include "r6d.h"

/* 0x0006D310: in the item page, translate a value and show it.
   calls 0x0006C160 with EAX=v */
void *r6d_PauseShowValue(void *v)
{
    if (a60_v3E6620 == 10000)
        v = sub_000727E0(sub_0003FBD0(r6d_PausePageValue(sub_0006C750(v)), R6D_WORK->anim),
                         a4c_obj428F40);
    return v;
}

/* 0x00071F90: run the current pause page. */
void r6d_PausePageRun(void)
{
    switch (a60_phase428F81) {
    case 1:
        sub_00070E90();
        break;
    case 2:
        sub_00071230();
        break;
    case 3:
        sub_00071400();
        break;
    case 4:
        sub_00071940();
        break;
    case 5:
        sub_00071C30();
        break;
    case 0:
    case 6:
        sub_00070790();
        break;
    }
}

/* 0x00072230: forward thirteen arguments to 0x001A78F0 and return the first one. */
int r6d_Forward13(int r, int a, int b, int c, int d, int e, int f, int g, int h, int i,
                  int j, int k, int l, int m)
{
    sub_001A78F0(a, b, c, d, e, f, g, h, i, j, k, l, m);
    return r;
}
