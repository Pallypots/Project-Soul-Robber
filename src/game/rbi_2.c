/* Area rbi: enemy set-up of the families at 0x0013D000 and 0x00140000 (rbi_2). Names inferred. */
#include "rbi.h"

/* 0x0013D030: initialise an enemy of the family whose states live at 0x0013AB30: install its
   handlers and state tables, attach it to the model, read its health, scale it by 1.2 for
   the large variant (obj->var08) and set its hit and reach sizes from that scale.
   regargs: obj=ESI act=EDI */
void rbi_EnemyInit13D030(RbiObj *obj, RbiAct *act)
{
    RbiWorkG *w = (RbiWorkG *)act->work278;
    float s;

    act->fn27C = sub_00137C30;
    act->fn288 = sub_00137C70;
    act->tab28C = rbi_tab31CC80;
    act->tab290 = rbi_tab31CD28;
    act->fn298 = sub_0013AB30;
    act->tab294 = rbi_tab31CDD0;
    act->fn29C = sub_0013AD50;
    sub_00113E90(obj, act, rbi_tab31CC74);
    r2d_HookAttach(obj, act, 8);
    act->flags4C |= 0x1000078;
    act->tab30 = rbi_tab31CC20;
    act->f270 = act->f274 = sub_00171D50(obj->kind04, obj->var08, 0);
    s = 1.0f;
    if (obj->var08)
        s = 1.2f;
    obj->scale70.z = s;
    obj->scale70.y = s;
    obj->scale70.x = s;
    obj->scale70.w = 1.0f;
    w->i0C = 7;
    w->i08 = 2;
    w->f10 = obj->scale70.x * -3.5f;
    act->i24 = 3;
    act->f28 = obj->scale70.x * -11.0f;
    act->f2C = obj->scale70.x * -21.0f;
    obj->i124 = 2;
    obj->iD0 = sub_0001BC40(obj);
    obj->fB0 = obj->scale70.x * 5.0f;
    obj->iF0 = 2;
    obj->iF4 = 2;
    obj->i118 = 2;
    obj->i120 = 2;
    obj->iEC = 0;
    obj->fDC = obj->scale70.x * -10.0f;
    obj->fE8 = obj->scale70.x * 6.0f;
    obj->fFC = obj->fDC;
    obj->i11C = 1;
}

/* 0x00140200: initialise an enemy of the family at 0x00140000 (always the 1.2 scale): the
   same set-up as 0x0013D030 with this family's handlers and tables, plus the hook at +0x40.
   The sizes are the 0x0013D030 ones pre-multiplied by 1.2 (exact original values).
   regargs: obj=ESI act=EDI */
void rbi_EnemyInit140200(RbiObj *obj, RbiAct *act)
{
    RbiWorkG *w = (RbiWorkG *)act->work278;

    act->fn27C = sub_0013D2F0;
    act->fn288 = sub_00137C70;
    act->tab28C = rbi_tab31CF00;
    act->tab290 = rbi_tab31CFC8;
    act->fn298 = sub_0013D630;
    act->tab294 = rbi_tab31D08C;
    act->fn29C = sub_0013D990;
    act->fn40 = sub_0013D910;
    sub_00113E90(obj, act, rbi_tab31CC74);
    r2d_HookAttach(obj, act, 8);
    act->flags4C |= 0x1000078;
    act->tab30 = rbi_tab31CEDC;
    act->f270 = act->f274 = sub_00171D50(obj->kind04, obj->var08, 0);
    obj->scale70.z = 1.2f;
    obj->scale70.y = 1.2f;
    obj->scale70.x = 1.2f;
    obj->scale70.w = 1.0f;
    w->f10 = -4.20000029f;
    w->i0C = 7;
    w->i08 = 2;
    act->f28 = -14.4000015f;
    act->i24 = 3;
    act->f2C = -21.6000004f;
    obj->i124 = 2;
    obj->iD0 = sub_0001BC40(obj);
    obj->iF0 = 2;
    obj->iF4 = 2;
    obj->i118 = 2;
    obj->i120 = 2;
    obj->fB0 = 7.20000076f;
    obj->iEC = 0;
    obj->fDC = -12.0f;
    obj->fE8 = 8.40000057f;
    obj->fFC = -12.0f;
    obj->i11C = 1;
}
