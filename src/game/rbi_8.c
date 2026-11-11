/* Area rbi: enemy set-up near 0x00108000 (rbi_8). Names inferred. */
#include "rbi.h"

/* 0x00108790: set up an enemy object: visible and solid (flag 1 on, 2 off, copied to +0x15C),
   rotation and offset cleared, scale 1.2, collision sizes, the hit component (kind 0xD) with
   its three handlers, its table and 4 hit points of kind data, and the state component
   (kind 5) with the kind's health, the game context and cleared motion fields. */
void rbi_EnemySetup108790(RbiEnemyObj *o)
{
    RbiHitComp2 *h = (RbiHitComp2 *)rbi_Comp1D960(o, 0xD);
    RbiStateComp *s = (RbiStateComp *)rbi_Comp1D960(o, 5);

    o->rot50.z = 0.0f;
    o->rot50.y = 0.0f;
    o->rot50.x = 0.0f;
    o->pos60.z = 0.0f;
    o->pos60.y = 0.0f;
    o->pos60.x = 0.0f;
    o->flags15C = o->flags0C = (o->flags0C & ~2u) | 1;
    o->pos60.w = 1.0f;
    o->rot50.w = 1.0f;
    o->scale70.z = 1.2f;
    o->scale70.y = 1.2f;
    o->scale70.x = 1.2f;
    o->scale70.w = 1.0f;
    o->i124 = 1;
    o->iD0 = sub_0001BC40((RbiObj *)o);
    o->fB0 = 12.0f;
    o->fB4 = -28.8000031f;
    o->fA4 = 0.0f;
    o->fE8 = 0.0f;
    o->iEC = 0;
    o->iF0 = 2;
    o->iF4 = 2;
    o->i118 = 0;
    o->fFC = -24.0f;
    o->i11C = 1;
    o->i120 = 2;
    sub_000EE270(h);
    h->f18 = -21.6000004f;
    h->flags10 |= 0x80000000u;
    h->fn24 = sub_00107490;
    h->fn28 = sub_001083E0;
    h->fn2C = sub_001063C0;
    h->tab20 = rbi_tab319644;
    h->i14 = 4;
    h->f1C = -34.8000031f;
    sub_000F3AA0(s);
    s->i4C = 1;
    s->hpMax58 = s->hp54 = sub_00171D50(o->kind04, o->var08, 0);
    s->game64 = sub_000E0770();
    sub_000F3B70(o, 0);
    sub_000F3BB0((RbiFxNode *)o, 0, 0);
    s->fA4 = 0.0f;
    s->fA0 = 0.0f;
    s->iA8 = 0;
    s->vAC.x = 0.0f;
    s->vAC.y = 0.0f;
    s->vAC.z = 0.0f;
    s->vAC.w = 1.0f;
    s->vC0.x = 0.0f;
    s->vC0.y = 0.0f;
    s->vC0.z = 0.0f;
    s->vC0.w = 1.0f;
    s->fD8 = 0.0f;
    s->fD4 = 0.0f;
    s->fD0 = 0.0f;
    s->fBC = 0.0f;
}

/* 0x000F2D30: set up an enemy object (the 0x000EFDE0 family): visible and solid, flags
   0xC1 through 0x000F3B00, rotation and offset cleared, scale 1.2, collision sizes, the hit
   component (kind 0xD) with its two handlers, the state component (kind 5) with the kind's
   health, the game context and its three tables, its kind-5 link, cleared motion vectors,
   drift (frame time * 0) and a random pick 0..5.
   regargs: o=ESI */
void rbi_EnemySetup0F2D30(RbiEnemyObj *o)
{
    RbiHitComp2 *h = (RbiHitComp2 *)rbi_Comp1D960(o, 0xD);
    RbiStateCompB *s = (RbiStateCompB *)rbi_Comp1D960(o, 5);

    o->flags0C = (o->flags0C & ~2u) | 1;
    sub_000F3B00(o, 0xC1);
    o->rot50.z = 0.0f;
    o->rot50.y = 0.0f;
    o->rot50.x = 0.0f;
    o->pos60.z = 0.0f;
    o->pos60.y = 0.0f;
    o->pos60.x = 0.0f;
    o->pos60.w = 1.0f;
    o->rot50.w = 1.0f;
    o->scale70.z = 1.2f;
    o->scale70.y = 1.2f;
    o->scale70.x = 1.2f;
    o->scale70.w = 1.0f;
    o->i124 = 1;
    o->iD0 = sub_0001BC40((RbiObj *)o);
    o->fB0 = 12.0f;
    o->fB4 = -28.8000031f;
    o->fA4 = 0.0f;
    o->fE8 = 0.0f;
    o->iEC = 0;
    o->iF0 = 2;
    o->iF4 = 2;
    o->i118 = 0;
    o->fFC = -24.0f;
    o->i11C = 1;
    o->i120 = 2;
    sub_000EE270(h);
    h->f18 = -21.6000004f;
    h->flags10 |= 0x80000000u;
    h->fn24 = sub_000EFDE0;
    h->fn28 = sub_000F2A60;
    h->i14 = 0;
    h->f1C = -33.6000023f;
    sub_000F3AA0((RbiStateComp *)s);
    s->i4C = 1;
    s->hpMax58 = s->hp54 = sub_00171D50(o->kind04, o->var08, 0);
    s->game64 = sub_000E0770();
    s->tab74 = rbi_tab318A30;
    s->tab78 = rbi_tab318AB8;
    s->tab7C = rbi_tab318B40;
    sub_000F3B70(o, 0);
    sub_000F3D10(o, (RbiStateCompB *)rbi_Comp1D960(o, 5), 0);
    s->i8C = 0;
    s->v90.x = 0.0f;
    s->v90.y = 0.0f;
    s->v90.z = 0.0f;
    s->v90.w = 1.0f;
    s->vA0.x = 0.0f;
    s->vA0.y = 0.0f;
    s->vA0.z = 0.0f;
    s->vA0.w = 1.0f;
    s->vB8.x = 0.0f;
    s->vB8.y = 0.0f;
    s->vB8.z = 0.0f;
    s->vB8.w = 1.0f;
    s->fD0 = 0.0f;
    s->fCC = 0.0f;
    s->fC8 = 0.0f;
    s->iDC = 1;
    s->iE4 = 0;
    s->pick10C = sub_001C7EE1() % 6;
    s->iEC = 0;
    s->f108 = 0.0f;
    s->vF0[0] = a50_frameSeconds * 0.0f;
    s->vF0[1] = a50_frameSeconds * 0.0f;
    s->vF0[2] = a50_frameSeconds * 0.0f;
    s->vF0[3] = a50_frameSeconds * 0.0f;
    s->i110 = 0;
    s->i114 = 0;
}
