/* Area a9c, 0x00198000-0x00199FFF (slot tables). Reference build OOGIE-XBOX-US-RETAIL. Names inferred. */
#include "a9c.h"

/* 0x00198020: destroy the object once +0x6C exceeds 0.75 (work +4 set) or 0.7. */
void a9c_CullPastLimit(a9c_Obj *o, a9c_Obj *a)
{
    a9c_Work *w = a->work;
    float lim;
    sub_00197BA0(w);
    lim = w->f4 ? 0.75f : 0.7f;
    if (a->f6C > lim)
        sub_000ED780(o);
}

/* 0x00199D90: whether entry i (0..0x76) of 0x00330F30 is the one its linked 0x00401D70 slot points back to. */
int a9c_Ent330F30IsLinked(int i)
{
    a9c_Link24 *l;
    if (i <= -1 || i >= 0x77) for (;;) ;
    l = &a9c_g3316A0[a9c_g330F30[i].f0];
    if (l->b0 && a9c_g401D70[l->b10].f8 == i)
        return 1;
    return 0;
}

/* 0x00199E20: state of active slot i (0..44) of 0x00401D70: 7 when busy, else +0x10; -1 if none. */
int sub_00199E20(int i)
{
    a9c_Slot38 *s;
    if (i < 0 || i >= 45)
        return -1;
    s = &a9c_g401D70[i];
    if (s->f0 && s->f10 >= 0) {
        if (sub_001AB0A0(i))
            return 7;
        return s->f10;
    }
    return -1;
}

/* 0x00199E70: whether active slot i (0..44) of 0x00401D70 with valid +0x10 has +4 set. */
int a9c_Slot401D70Has4(int i)
{
    if (i >= 0 && i < 45 && a9c_g401D70[i].f0 && a9c_g401D70[i].f10 >= 0)
        return a9c_g401D70[i].f4 != 0;
    return 0;
}
