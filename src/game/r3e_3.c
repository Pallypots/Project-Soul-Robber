/* Area r3e: game functions in 0x00137000..0x0013FFFF (r3e_3). Names inferred. */
#include "r3e.h"

/* 0x00138740: play animation 0x3E or 0x60 (+1 for act flag byte bit) by the sign of the work flag
   word, set obj flag 4 (clearing 0x20), clear act flag 8 and the work sign bit. */
void r3e_Anim138740(R3eObj *obj, R3eObj *act)
{
    if (act->work278->i04 < 0)
        sub_00113090(obj, act, (act->b22 & 1) + 0x3E);
    else
        sub_00113090(obj, act, (act->b22 & 1) + 0x60);
    obj->flags10 = (obj->flags10 & ~0x20u) | 4;
    act->flags4C &= ~8u;
    act->work278->i04 &= 0x7FFFFFFF;
}

/* 0x001387C0: clear obj flag 0x20, play animation 0x40 or 0x41 by work flag 0x01000000 and
   clear that flag. */
void r3e_Anim1387C0(R3eObj *obj, R3eObj *act)
{
    R3eWork *w;

    obj->flags10 &= ~0x20u;
    w = act->work278;
    sub_00113090(obj, act, (w->i04 & 0x01000000) ? 0x40 : 0x41);
    w->i04 &= ~0x01000000;
}

/* 0x0013AAD0: compact a list of four objects: every non-empty entry whose flag 1 is clear is
   removed and the rest moved up, the freed last slot set to 0. */
void r3e_Compact13AAD0(R3eObj **list)
{
    int i, j;

    for (i = 0; i < 4; i++) {
        if (list[i] != 0 && !(list[i]->flags0C & 1)) {
            for (j = i; j < 3; j++)
                list[j] = list[j + 1];
            list[j] = 0;
            i--;
        }
    }
}

/* 0x0013BCE0: when the animation ends set act flags 0x38 and enter state 0x11, 0x12 or 0xD by
   condition records 0 and 1 of 0x00279728. */
void r3e_State13BCE0(R3eObj *obj, R3eObj *act)
{
    int st;

    if (!sub_000833E0(obj->anim30))
        return;
    st = 0x11;
    if (!r3b_disp31CDFC[0](obj, act, &r3b_recs279728[0]))
        st = r3b_disp31CDFC[1](obj, act, &r3b_recs279728[1]) ? 0x12 : 0xD;
    act->flags4C |= 0x38;
    sub_00113040(obj, act, st);
}

/* 0x0013EC10: play animation 0x40 or 0x41 by work flag 0x01000000 and clear that flag. */
void r3e_Anim13EC10(R3eObj *obj, R3eObj *act)
{
    R3eWork *w = act->work278;

    sub_00113090(obj, act, (w->i04 & 0x01000000) ? 0x40 : 0x41);
    w->i04 &= ~0x01000000;
}

/* 0x0013A0A0: two-step wake-up: once act's +0x5C clock reaches 10 frames show obj (0x0001D610)
   and arm a 25-frame timer; when that runs out clear obj flag 1 and return 1. */
int r3e_Wake13A0A0(R3eObj *obj, R3eObj *act)
{
    switch (act->i58) {
    case 0:
        if (act->f5C >= 10.0f / r3e_frameUnits * r3e_frameSeconds) {
            sub_0001D610(obj);
            act->f74 = 25.0f / r3e_frameUnits * r3e_frameSeconds;
            act->i58++;
        }
        break;
    case 1:
        if (act->f74 <= 0.0f) {
            obj->flags10 &= ~1u;
            return 1;
        }
        break;
    }
    return 0;
}

/* 0x0013E420: without act flag byte bit enter state 0x28; otherwise set act flag 0x10, arm node 10
   with a turn (2 degrees per frame unit, limits 25 and 5 degrees, mode 0x510001), set obj flag
   0x20 and play animation 1. */
void r3e_Turn13E420(R3eObj *obj, R3eObj *act)
{
    R3eNode *n;

    if (!(act->b22 & 1)) {
        sub_00113040(obj, act, 0x28);
        return;
    }
    act->flags4C |= 0x10;
    n = sub_00113430(act, 10);
    n->f10 = r3e_frameUnits * 0.034906585f;
    n->f14 = 0.43633232f;
    n->f18 = 0.08726647f;
    n->i1C = 0x510001;
    obj->flags10 |= 0x20;
    sub_00113090(obj, act, 1);
}

/* 0x0013F9C0: set node 5's rate to 0.008; once act's +0x68 clock reaches 60 frames clear obj
   flags 0x24 and enter state 0x28 (no act flag byte bit), 0xC (work flag 0x10, rearming the
   timer) or 0x13. */
void r3e_State13F9C0(R3eObj *obj, R3eObj *act)
{
    float t;
    int st;

    sub_00113400(act, 5)->f10 = 0.008f;
    t = 60.0f / r3e_frameUnits * r3e_frameSeconds;
    if (act->f68 >= t) {
        st = 0x28;
        if (act->b22 & 1) {
            st = 0x13;
            if (act->work278->i04 & 0x10) {
                st = 0xC;
                act->f74 = t;
            }
        }
        obj->flags10 &= ~0x24u;
        sub_00113040(obj, act, st);
    }
}

/* 0x0013B590: play animation 6, set obj flag 2 (clearing 0x20), clear act flag 0x10, on one roll in
   32 mark items (0x00139CF0), detach obj and arm node 1 (0.3, 0.25, 1) with callback 0x001381E0. */
void r3e_Enter13B590(R3eObj *obj, R3eObj *act)
{
    R3eNode *n;

    sub_00113090(obj, act, 6);
    obj->flags10 = (obj->flags10 & ~0x20u) | 2;
    act->flags4C &= ~0x10u;
    if (sub_001C7EE1() % 32 < 1)
        sub_00139CF0();
    sub_00036750(obj, 0);
    n = sub_00113430(act, 1);
    n->f10 = 0.3f;
    n->f14 = 0.25f;
    n->i18 = 1;
    n->p1C = (void *)b13_State1381E0;
}
