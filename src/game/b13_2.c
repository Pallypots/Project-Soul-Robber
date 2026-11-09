/* Area b13, group 2: enemy state handlers 0x00138Cxx-0x0013Exxx. Names inferred. */
#include "b13.h"

/* 0x00138CC0: arm a 0.008 timer; after one second switch to animation 0xD. */
void b13_State138CC0(B13Owner *o, B13Enemy *e)
{
    sub_00113400(e, 5)->t = 0.008f;
    if (e->stateTime68 >= 60.0f / a50_frameUnits * a50_frameSeconds) {
        o->flags10 &= ~0x24u;
        sub_00113040(o, e, 0xD);
    }
}

/* 0x00138F70: turn toward the player by the angle from 0x00113200 plus pi. */
void b13_Turn138F70(B13Owner *o, B13Enemy *e)
{
    float d = sub_00113200(o, (uint8_t *)g_playerObj + 0x60) + 3.1415927f;
    o->f54 += d;
    e->fFC -= d;
}

/* 0x00139FA0: stop, enter state with the given animation, stop the model. */
void b13_StateAnim139FA0(B13Owner *o, B13Enemy *e, int anim)
{
    sub_0001D700(o);
    o->flags10 |= 5;
    e->flags4C &= ~0x78u;
    sub_00113090(o, e, anim);
    sub_001AEDD0(o->model->handle14, 0);
}

/* 0x0013AA80: remember p in a 4-slot list; when full, shift out the oldest. */
void b13_SlotsAdd(void **slots, void *p)
{
    int i;
    for (i = 0; i < 4; i++)
        if (slots[i] == 0 || slots[i] == p) break;
    if (i < 4) {
        slots[i] = p;
        return;
    }
    slots[0] = slots[1];
    slots[1] = slots[2];
    slots[2] = slots[3];
    slots[3] = p;
}

/* 0x0013E0B0: enter state with animation 0x63. */
void b13_State13E0B0(B13Owner *o, B13Enemy *e)
{
    o->flags10 |= 6;
    o->flagsC &= ~0x20u;
    e->flags4C |= 8;
    sub_00113090(o, e, 0x63);
}

/* 0x0013E210: mirrored animation 0/1, behaviour flag 0x10. */
void b13_State13E210(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, e->side22 & 1);
    o->flags10 |= 6;
    e->behav->flags4 |= 0x10;
}

/* 0x0013E640: mirrored animation 4/5 and timer slot 9. */
void b13_State13E640(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, (e->side22 & 1) + 4);
    o->flags10 |= 0x20;
    e->flags4C &= ~0x10u;
    sub_00113430(e, 9);
}

/* 0x0013E680: animation 0x14, one exclamation point, owner flag 4. */
void b13_State13E680(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x14);
    Grade_AddExclamations(1);
    o->flags10 |= 4;
}

/* 0x0013EB80: animation 0x13, clear owner flag 0x20. */
void b13_State13EB80(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x13);
    o->flags10 &= ~0x20u;
}

/* 0x0013EBE0: animation 0x40 and timer slot 6 = 0x21. */
void b13_State13EBE0(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x40);
    sub_00113430(e, 6)->a = 0x21;
}

/* 0x0013ED00: 0x00113A40 then signal behaviour resource +0x34. */
void b13_State13ED00(B13Owner *o, B13Enemy *e)
{
    sub_00113A40(o, e);
    sub_0018E7F0(e->behav->res34, 1);
}

/* 0x0013ED30: animation 0x1A, clear owner flag 0x20, set flag 0x10. */
void b13_State13ED30(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x1A);
    o->flags10 &= ~0x20u;
    e->flags4C |= 0x10;
}

/* 0x0013EDF0: animation 0x2B, owner flag 0x20, flag 0x10. */
void b13_State13EDF0(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x2B);
    o->flags10 |= 0x20;
    e->flags4C |= 0x10;
}

/* 0x0013EF90: animation 0x23, owner flag 0x20. */
void b13_State13EF90(B13Owner *o, B13Enemy *e)
{
    sub_00113090(o, e, 0x23);
    o->flags10 |= 0x20;
}
