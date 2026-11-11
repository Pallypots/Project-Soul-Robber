/* Area r1d, group 10: effect node queries and scene groups 0x00034AF0..0x00035BF0. Names inferred. */
#include "r1d.h"

/* 0x00034AF0: run the key matcher 0x00034AC0 over every node of the bank
   for key (a, b); b of -1 matches any value of byte 3. */
int r1d_NodeForKey(int a, int b)
{
    uint32_t q[2];
    uint32_t mask = (b == -1) ? 0x00FF0000 : 0xFFFF0000;
    q[0] = (((a & 0xFF) | (b << 8)) << 16) & mask;
    q[1] = mask;
    return r1c_PoolForEach(r1c_bank283698, 0xB40, sub_00034AC0, q);
}

/* 0x00034BB0: free the range record of every flagged host of the scene. */
void r1d_SceneFreeRanges(void)
{
    R1dHostGrp **hosts;
    R1dHostGrp *g;
    int i;
    if (r1c_scene42C8E4 == 0) return;
    hosts = r1c_scene42C8E4->hosts;
    if (hosts == 0) return;
    for (g = *hosts; g != 0; g = g->next) {
        if (g->recs == 0) continue;
        for (i = 0; i < g->count; i++) {
            if ((g->recs[i].flags & 1) && g->recs[i].range != 0) {
                sub_00033C20(g->recs[i].range);
                g->recs[i].range = 0;
            }
        }
    }
}

/* 0x00034C30: create the effect node for key (a, b, c); the player-bound
   keys (1, 0xFF) and (-3, *) take the current effect bank instead of c's
   high bits (0 when there is none). */
R1dNode *r1d_NodeSpawnKey(int a, int b, int c)
{
    int k;
    if (a == 1) {
        if (b == 0xFF) goto bank;
    } else if (a == -3) {
        goto bank;
    }
    k = c;
    goto make;
bank:
    if (r1d_fxBank420DA8 == -1) return 0;
    k = (r1d_fxBank420DA8 << 4) | (c & 0xF);
make:
    return r1d_NodeCreate(a50_CacheGetData(a, b),
                          (((a & 0xFF) | (b << 8)) << 16) | (k & 0xFFFF));
}

/* 0x00034F90: re-attach an emitter node to the scene and refresh it from
   its matrix; a null node hangs. */
void r1d_NodeRefresh(R1dNode *n)
{
    float m[16];
    if (n == 0) for (;;) ;
    if (n->kind != 0) return;
    if (*(int32_t *)&n->blk.raw[0x80] != 0) {
        r4_NodeDetach(&n->blk);
        n->pair = 0;
    }
    if (n->kind == 0)
        sub_001ADA40(m, (float *)&n->blk.raw[0x40]);
    r1d_NodeAttach(n, r1c_scene42C8E4);
    sub_00034DD0(n, &m[12], &m[8], &m[4]);
}

/* 0x00035BF0: the group entry with id, or a new one appended to the
   group; 0 when the group is null or memory runs out. */
R1dGrpEnt *r1d_GroupFindAdd(R1dGroup *g, int id)
{
    R1dGrpEnt *p, *e;
    if (g == 0) return 0;
    for (p = g->head; p != 0; p = p->next) {
        e = p->self;
        if (e->id == id) {
            if (p->self != 0) return e;
            break;
        }
    }
    e = sub_00053AB0(0x24, 0, 0x105D);
    if (e != 0) {
        sub_0003D860(e->sub);
        e->self = e;
        e->id = id;
        a4c_ListAppend(g->list, e);
    }
    return e;
}
