/* Area r4g: effect spawners near 0x00190000 (r4g_1). Names inferred. */
#include "r4g.h"

/* 0x00190710: spawn callback of the falling effect: take a free record at
   0x004000B0, set up collision, callbacks and scale, then enter state 1.
   Returns 0 when all three records are busy. Stack args (o a). */
int r4g_FxFallSpawn(R4gNode *o, R4gActor *a)
{
    R4gRec24 *rec;
    int i;
    for (i = 0; i < 3; i++)
        if (!r4c_recs4000B0[i].obj)
            break;
    if (i >= 3)
        return 0;
    rec = &r4c_recs4000B0[i];
    rec->obj = o;
    a->work = rec;
    o->flags10 = (o->flags10 & ~0x141u) | 0x200;
    o->i124 = 1;
    o->flagsC = (o->flagsC & ~0x80u) | 1;
    sub_000F5D60(o, 2.5f, -1.0f, 2.0f, r4g_v27AE08);
    sub_000F5DD0(o, 2.5f, 2.0f, r4g_v27ADF0);
    o->iF0 = 2;
    o->iF4 = 2;
    sub_000F5E30(o, 2.5f, r4g_v27AE18, r4g_v27AE28);
    o->i11C = 1;
    o->i120 = 2;
    a->f28 = 0.0f;
    a->f2C = -7.5f;
    a->p84 = r4g_d32C614;
    a->p88 = r4g_d32C62C;
    a->fn78 = (void *)sub_0018F6F0;
    a->fn7C = (void *)sub_0018F760;
    a->fn80 = (void *)sub_001905E0;
    a->i24 = 0;
    o->scale70[2] = 2.5f;
    o->scale70[1] = 2.5f;
    o->scale70[0] = 2.5f;
    sub_000F5D40(o->pos, r4g_v32C5F4);
    sub_00189DA0(o, a, 1);
    return 1;
}

/* 0x00192180: spawn callback of the 0x00400390 effect family; as
   the 0x00400688 spawner (0x00192000) with its own sizes and message handler, and the table value
   of the node kind kept twice in the record. Stack args (o a mode). */
int r4g_FxSpawnB(R4gNode *o, R4gActor *a, int mode)
{
    R4gRec4C *rec;
    int i;
    if (!o)
        return 0;
    for (i = 0; i < 10; i++)
        if (!r4c_recs400390[i].obj)
            break;
    if (i >= 10)
        return 0;
    rec = &r4c_recs400390[i];
    rec->obj = o;
    rec->actor = a;
    rec->mode10 = mode;
    a->work = rec;
    o->flagsC = (o->flagsC & ~0x20u) | 3;
    o->flags10 |= 0x41;
    a->i24 = 0;
    o->i124 = 1;
    sub_000F5D60(o, 1.0f, -15.0f, 4.7f, r4g_v27AEF0);
    sub_000F5DD0(o, 1.0f, 5.5f, r4g_v27AF04);
    o->iF0 = 2;
    o->iF4 = (int32_t)0x80000000u;
    sub_000F5E30(o, 1.0f, r4g_v27AF14, r4g_v27AF24);
    o->i11C = 1;
    o->i120 = (int32_t)0x80000000u;
    a->f28 = 7.0f;
    a->p84 = r4g_d32C6A8;
    a->p88 = r4g_d32C6C8;
    a->fn78 = (void *)sub_00190900;
    a->fn7C = (void *)sub_001909C0;
    a->fn80 = (void *)sub_00191EA0;
    rec->f44 = rec->f48 = sub_00171D50(o->i04, o->kind, 0);
    if (o->p28) {
        rec->f08 = 1.5f;
        sub_0001EE80(o, sub_00196B40);
    }
    if (mode == 2) {
        sub_00189DA0(o, a, 1);
        return 1;
    }
    if (mode == 0 || mode == 1)
        sub_00189DA0(o, a, 2);
    return 1;
}
