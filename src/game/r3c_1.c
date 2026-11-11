/* Area r3c: game functions in 0x00130000..0x0015FFFF (r3c_1). Names inferred. */
#include "r3c.h"

/* 0x00155940: resolve a condition's target object by selector *sel.
   regargs: sel=EAX obj=ECX given=stack. */
R3cObj *r3c_Target155940(const int32_t *sel, R3cObj *obj, R3cObj *given)
{
    R3cWork *w = obj->work278;
    R3cObj *t;

    switch (*sel) {
    case 1:
        return (R3cObj *)g_playerObj;
    case 2:
        if (obj->iF8 == 1) {
            t = obj->p104;
            if ((t->flags0C & 1) && t->type04 == 13)
                return t;
        }
        return 0;
    case 3:
        return w->p38;
    case 4:
        return given;
    case 5:
        return 0;
    default:
        for (;;)
            ;
    }
}

/* 0x0013FCD0: turn obj to face the player (+pi) and turn act->fFC the opposite way. */
void r3c_FacePlayer13FCD0(R3cObj *obj, R3cObj *act)
{
    obj->f54 = sub_00113200(obj, ((R3cObj *)g_playerObj)->pos60) + obj->f54 + 3.1415927f;
    act->fFC = act->fFC - (sub_00113200(obj, ((R3cObj *)g_playerObj)->pos60) + 3.1415927f);
}

/* 0x00145A50: convert a and b, blend them by t and store the result in dst. */
int r3c_Blend145A50(void *dst, const void *a, const void *b, float t)
{
    float v0[4], v1[4], v2[4];

    sub_001A8820(v1, a);
    sub_001A8820(v0, b);
    sub_001A8840(v2, v1, v0, t);
    return sub_001A8830(dst, v2);
}


/* 0x00156040: is o out of the player's reach (busy, beyond 200, or more than 100 apart in height)?
   regargs: o=ESI. */
int r3c_OutOfReach156040(R3cObj *o)
{
    if (sub_00087500())
        return 1;
    if (sub_001B2770(o->pos60, ((R3cObj *)g_playerObj)->pos60) >= 200.0f)
        return 1;
    if (sub_001A3F30(o->pos60[1] - ((R3cObj *)g_playerObj)->pos60[1]) >= 100.0f)
        return 1;
    return 0;
}
