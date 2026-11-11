/* Area rbi: enemy burst effect (rbi_10). Names inferred. */
#include "rbi.h"

/* 0x00177290: start the burst of an enemy: object flags 0xD on (0x20 off), actor flag
   0x1000000 off, joint 2 takes the work value, parts 0x12..0x1E switched by 0x0013A120,
   the effect node (3, 3) placed 7.5 units from the enemy away from Jack, facing away from
   him, then sound/effect 0x1A at the enemy. */
void rbi_Burst177290(RbiBurstObj *obj, RbiBurstAct *act)
{
    int32_t parts[14] = { 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C,
                          0x1D, 0x1E, -1 };
    int32_t *w;
    RbiVec4 up, dir, pos;
    void *node;

    obj->flags10 = (obj->flags10 & ~0x20u) | 0xD;
    obj->flags0C &= ~0x20u;
    w = act->work278;
    act->flags4C &= 0xFEFFFFFFu;
    rbi_Joint1D0F0(obj, 2)->iD4 = w[5];
    sub_0013A120(obj, 1, parts);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    up.w = 1.0f;
    rbi_VecSub(&dir, &obj->pos60, (const RbiVec4 *)((uint8_t *)g_playerObj + 0x60));
    rbi_VecNorm(&dir, &dir);
    rbi_VecScale(&pos, &dir, 7.5f);
    node = sub_00035D80(obj, 3, 3);
    rbi_VecAdd(&pos, &pos, &obj->pos60);
    rbi_Place34E00(node, &pos, &dir, &up);
    rbi_Sound494D0(0x1A, &obj->pos60, 0);
}

/* 0x00185190: take slot idx of the 0x003FE3B0 table for an enemy: link object, actor and
   slot, install the actor's handlers and tables, read its health, set its flags and
   collision sizes (1.0, -25, 4.6 / 1.0, 4.8), scale 1, clear the slot's motion fields and
   enter state 1. Returns 1. */
int rbi_SlotSpawn185190(RbiSpawnObj *obj, RbiAct *act, int idx)
{
    RbiSlot34 *s = &r3c_recs3FE3B0[idx];

    act->work278 = s;
    s->idx30 = (int16_t)idx;
    s->act08 = act;
    s->f10 = 0.0f;
    s->obj00 = obj;
    act->tab28C = rbi_tab32BCCC;
    act->tab290 = rbi_tab32BCD8;
    act->fn27C = sub_00184670;
    act->fn288 = sub_00102FA0;
    act->fn29C = sub_001846E0;
    obj->flags0C |= 1;
    act->f270 = act->f274 = sub_00171D50(obj->kind04, obj->var08, 0);
    obj->flags10 |= 0x441;
    obj->flags0C &= ~0xC0u;
    obj->i124 = 0;
    sub_000F5D60(obj, 1.0f, -25.0f, 4.5999999f, rbi_v27AA00);
    sub_000F5DD0(obj, 1.0f, 4.79999971f, rbi_v27AA14);
    obj->iF0 = 2;
    obj->iF4 = 2;
    act->f28 = -4.0f;
    obj->scale70.z = 1.0f;
    obj->scale70.y = 1.0f;
    obj->scale70.x = 1.0f;
    s->i0C = 0;
    s->f1C = 0.0f;
    s->f20 = 0.0f;
    s->f24 = 0.0f;
    s->f28 = 0.0f;
    s->f2C = 0.0f;
    sub_00113040(s->obj00, s->act08, 1);
    return 1;
}

/* 0x0017C320: set up an enemy of the family at 0x0017A000: install its handlers and
   tables, scale 1, the kind's health, reach (-10, -8), collision sizes (4.0, -10, -6), flag
   0x10, actor flag 0x1000000 off, renew emitters 0 and 3 and enter state 1. Returns 1. */
int rbi_EnemyInit17C320(RbiObj *obj, RbiAct *act)
{
    act->fn27C = sub_0017C2B0;
    act->fn288 = sub_0017AA60;
    act->fn29C = sub_0017ABE0;
    act->tab28C = rbi_tab32B630;
    act->tab290 = rbi_tab32B65C;
    act->tab294 = rbi_tab32B688;
    obj->scale70.z = 1.0f;
    obj->scale70.y = 1.0f;
    obj->scale70.x = 1.0f;
    obj->scale70.w = 0.0f;
    act->f270 = act->f274 = sub_00171D50(obj->kind04, obj->var08, 0);
    act->f28 = -10.0f;
    act->f2C = -8.0f;
    obj->iD0 = sub_0001BC40(obj);
    obj->fB4 = -10.0f;
    obj->fB0 = 4.0f;
    obj->fDC = -6.0f;
    obj->fE8 = 4.0f;
    obj->iF0 = 2;
    obj->iF4 = 2;
    obj->fFC = -6.0f;
    obj->i11C = 1;
    obj->i120 = 2;
    obj->flags10 |= 0x10;
    act->flags4C &= 0xFEFFFFFFu;
    sub_00113430((RbhComp *)act, 0);
    sub_00113430((RbhComp *)act, 3);
    sub_00113040(obj, act, 1);
    return 1;
}
