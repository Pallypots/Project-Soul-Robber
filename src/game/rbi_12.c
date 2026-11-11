/* Area rbi: enemy set-up of the family at 0x00135000 (rbi_12). Names inferred.
   Kept apart from 0x00135900 (rbi_6.c), which it calls. */
#include "rbi.h"

/* 0x00137A20: set up an enemy of the family at 0x00135000 in mode 0 (armed: work flag 1,
   20-frame timer registered through 0x00025C10, first state 0xE) or mode 1 (unarmed, first
   state 1); any other mode hangs. Installs nine handlers and three tables, scale 1.25, the
   model hook 0xA, reach and hit shapes (0x00135900), the kind's health and the flag set-up,
   then enters the first state. Returns 1.
   calls 0x00135900 with ESI=obj */
int rbi_EnemyInit137A20(RbiObj135 *obj, RbiAct *act, int mode)
{
    RbiWork135 *w = (RbiWork135 *)act->work278;
    int st;

    w->obj00 = obj;
    act->tab28C = rbi_tab31C718;
    act->tab290 = rbi_tab31C754;
    act->tab294 = rbi_tab31C790;
    act->fn27C = sub_00135490;
    act->fn29C = sub_000AD090;
    act->fn280 = sub_00137800;
    act->fn284 = r3b_Step135500;
    act->fn288 = sub_00145E10;
    act->fn298 = sub_001354D0;
    obj->o.scale70.z = 1.25f;
    obj->o.scale70.y = 1.25f;
    obj->o.scale70.x = 1.25f;
    obj->o.scale70.w = 1.0f;
    r2d_HookAttach(&obj->o, act, 0xA);
    act->f28 = -5.0f;
    act->i24 = 2;
    act->f2C = 0.0f;
    obj->o.i124 = 1;
    obj->o.iD0 = sub_0001BC40(&obj->o);
    obj->o.iEC = 0;
    obj->o.i118 = 2;
    rbi_Shapes135900((RbiShapeObj *)obj);
    obj->o.iF0 = 2;
    obj->o.iF4 = 2;
    obj->o.i120 = 2;
    obj->o.i11C = 1;
    obj->o.flags0C |= 0x100;
    act->flags4C |= 0x200;
    w->flags08 |= 0x80000;
    act->i54 = 0;
    act->i50 = 0;
    act->f270 = act->f274 = sub_00171D50(obj->o.kind04, obj->o.var08, 0);
    w->i184 = -1;
    switch (mode) {
    case 0:
        w->flags08 |= 1;
        w->armed170 = 1;
        w->t17C = 0x14;
        sub_00025C10(1, 0x14);
        st = 0xE;
        break;
    case 1:
        w->flags08 &= ~1u;
        w->armed170 = 0;
        st = 1;
        break;
    default:
        for (;;)
            ;
    }
    sub_001130F0(obj, act, 0);
    w = (RbiWork135 *)act->work278;
    sub_001134B0(act);
    obj->o.flags0C |= 0xE0;
    obj->o.flags10 &= 0xFFFFFEE8u;
    act->flags4C &= 0xFFFFFE8Fu;
    w->flags08 &= 0xFFFFFFB9u;
    sub_0005BE30(obj->snd13C);
    sub_00113040(obj, act, st);
    return 1;
}
