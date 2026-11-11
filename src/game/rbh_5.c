/* Area rbh: game functions in 0x00140000..0x0014FFFF (rbh_5). Names inferred. */
#include "rbh.h"

/* 0x00140370: set up an enemy of the family at 0x00140000 in start kind (0..15, 7 unused):
   initialise it, pick a random wait of 2*(base + rand() % range) frames, apply the kind's flag
   and enter its first state (all but state 4 also spawn the charge effect). Some kinds set the
   actor flag 0x400 or work flag 0x10. Returns 1, or 0 for an unknown kind.
   calls 0x00140200 with ESI=obj EDI=act; 0x0013D380 with EDI=act EBX=obj */
int rbh_EnemyStart140370(void *obj, RbhComp *act, int kind)
{
    RbhWorkG *w;
    int flag, state, base, range;

    if (kind >= 16)
        return 0;
    sub_00140200(obj, act);
    w = (RbhWorkG *)act->work278;
    switch (kind) {
    case 13:
        act->flags4C |= 0x400;
    case 0:
        flag = 0;
        state = 1;
        base = 0x14;
        range = 6;
        break;
    case 14:
        act->flags4C |= 0x400;
    case 1:
        state = 1;
        flag = 1;
        base = 0x1E;
        range = 6;
        break;
    case 2:
        state = 2;
        flag = 1;
        base = 0x1E;
        range = 6;
        break;
    case 3:
        state = 3;
        flag = 1;
        base = 0x1E;
        range = 6;
        break;
    case 4:
        flag = 0;
        state = 7;
        base = 0x28;
        range = 0xB;
        break;
    case 5:
        flag = 1;
        state = 7;
        base = 0x3C;
        range = 0xB;
        break;
    case 6:
        flag = 0;
        state = 4;
        base = 0x28;
        range = 0xB;
        break;
    case 15:
        act->flags4C |= 0x400;
    case 8:
        flag = 0;
        state = 8;
        base = 0x28;
        range = 0xB;
        break;
    case 9:
        w->flags04 |= 0x10;
        flag = 0;
        state = 1;
        base = 0x28;
        range = 0xB;
        break;
    case 10:
        w->flags04 |= 0x10;
        flag = 1;
        state = 1;
        base = 0x3C;
        range = 0xB;
        break;
    case 11:
        flag = 0;
        state = 6;
        base = 0x14;
        range = 6;
        break;
    case 12:
        state = 6;
        flag = 1;
        base = 0x1E;
        range = 6;
        break;
    default:
        return 0;
    }
    w->t14 = (sub_001C7EE1() % range + base) * 2;
    sub_001130F0(obj, act, flag);
    if (state != 4)
        r3_SpawnCharge13D380(act, obj);
    sub_00113040(obj, act, state);
    w->f18 = 100.0f;
    return 1;
}
