/* Area r3e: game functions in 0x00130000..0x0013FFFF (r3e_1). Names inferred. */
#include "r3e.h"

/* 0x00130030: run condition 0x30 (freeing obj on result 1), reset the work direction to
   (0, 0, 0, 1), set obj flag 4 and clear work flag 0x01000000; a pending flag 0x10 arms node 4. */
void r3e_Reset130030(R3eObj *obj, R3eObj *act)
{
    R3eWork *w = act->work278;
    R3eWork *v;
    R3eNode *n;

    if (sub_001456E0(obj, act, 0x30, 0) == 1)
        sub_0001D4E0(obj);
    v = act->work278;
    v->v164[2] = 0.0f;
    v->v164[1] = 0.0f;
    v->v164[0] = 0.0f;
    v->v164[3] = 1.0f;
    obj->flags10 |= 4;
    w->flags0C &= ~0x01000000u;
    if (w->flags0C & 0x10) {
        w->flags0C &= ~0x10u;
        n = sub_00113400(act, 4);
        n->f10 = 0.1f;
        n->f14 = 0.0f;
        n->f18 = 0.0f;
    }
    if (w->flags0C & 0x20)
        obj->flags10 |= 0xD;
}

/* 0x001303A0: reset the work direction, enter 0x00113A40, set work flag 0x2000 and arm act->f74
   with 2, 3 or 4 by variant (any other variant hangs). */
void r3e_Enter1303A0(R3eObj *obj, R3eObj *act)
{
    R3eWork *w = act->work278;
    float t;

    w->v164[2] = 0.0f;
    w->v164[1] = 0.0f;
    w->v164[0] = 0.0f;
    w->v164[3] = 1.0f;
    sub_00113A40(obj, act);
    w->flags0C = (w->flags0C & ~0x01000000u) | 0x2000;
    if (w->i19C == 0)
        t = 2.0f;
    else if (w->i19C == 1)
        t = 3.0f;
    else if (w->i19C == 2)
        t = 4.0f;
    else
        for (;;) ;
    act->f74 = t;
    if (w->flags0C & 0x20)
        obj->flags10 |= 0xD;
}

/* 0x00130B60: run condition 0x39, reset the work direction and rebuild obj's matrix upright:
   row 0 loses its y and is normalized, row 1 becomes (0, 1, 0), row 2 = row 0 x row 1. */
void r3e_Upright130B60(R3eObj *obj, R3eObj *act)
{
    float up[4];
    R3eWork *w = act->work278;
    R3eWork *v;

    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    if (sub_001456E0(obj, act, 0x39, 0) == 1)
        sub_0001D4E0(obj);
    v = act->work278;
    v->v164[2] = 0.0f;
    v->v164[1] = 0.0f;
    v->v164[0] = 0.0f;
    v->v164[3] = 1.0f;
    w->flags0C &= ~0x01000000u;
    obj->m20[1] = 0.0f;
    sub_001AD7E0(obj->m20, obj->m20);
    sub_000F5D40(obj->m20 + 4, up);
    sub_001ADA60(obj->m20 + 8, obj->m20, obj->m20 + 4);
    if (w->flags0C & 0x20)
        obj->flags10 |= 0xD;
}

/* 0x00130C40: run condition 0x42 and turn obj to face away from act's velocity: row 2 of the
   matrix = -(flat velocity, normalized), row 1 = (0, 1, 0), row 0 = row 1 x row 2; store the
   speed along the velocity, aim the work target at the player and arm node 6 for 1/12 s. */
void r3e_Face130C40(R3eObj *obj, R3eObj *act)
{
    float v[4];
    R3eWork *w = act->work278;
    R3eWork *u;
    R3eNode *n;
    float d;

    if (sub_001456E0(obj, act, 0x42, 0) == 1)
        sub_0001D4E0(obj);
    w->flags0C |= 4;
    obj->flags0C &= ~0x20u;
    w->flags0C &= ~0x80000u;
    sub_001ADBA0(v, act->v88, -1.0f);
    v[1] = 0.0f;
    sub_001AD7E0(v, v);
    sub_001ADBA0(obj->m20 + 8, v, -1.0f);
    obj->m20[7] = 0.0f;
    obj->m20[6] = 0.0f;
    obj->m20[4] = 0.0f;
    obj->m20[5] = 1.0f;
    sub_001ADA60(obj->m20, obj->m20 + 4, obj->m20 + 8);
    sub_001AD7E0(v, act->v88);
    d = sub_001AD9D0(v, act->v88);
    u = act->work278;
    u->v164[1] = 0.0f;
    u->v164[0] = 0.0f;
    u->v164[2] = d * r3e_frameUnits;
    u->v164[3] = 1.0f;
    sub_000F5D40(w->v154, ((R3eObj *)g_playerObj)->pos60);
    obj->flags10 |= 4;
    n = sub_00113400(act, 6);
    n->f10 = 0.083333336f;
    n->f14 = 0.0f;
    n->f18 = 0.0f;
    n->f1C = 0.0f;
}

/* 0x001310F0: try to grab the target of kind blk->f10 (0x00113670); on success aim at the player
   (flat, normalized) and, if Jack accepts (0x000D3BF0), flag act 0x100, play effect 0x14C at obj,
   attach obj (kinds 0 and 2 without the flag) and notify mode 1; then free the node.
   calls 0x0012E5E0 with ESI=1. */
void r3e_Grab1310F0(R3eObj *obj, R3eObj *act, R3eNode *blk)
{
    float dir[4];
    int h;
    int k;

    if (sub_00113670(obj, act, R3E_FTOI(blk->f10), &h) < 0)
        return;
    sub_001AD9F0(dir, ((R3eObj *)g_playerObj)->pos60, obj->pos60);
    dir[1] = 0.0f;
    dir[3] = 1.0f;
    sub_001AD7E0(dir, dir);
    if (sub_000D3BF0(&g_stats, obj, R3E_FTOI(blk->f10), &h, dir) != -1) {
        act->flags4C |= 0x100;
        sub_000494D0(0x14C, obj->pos60, 0);
        k = R3E_FTOI(blk->f10);
        sub_00036750(obj, (k == 0 || k == 2) ? 0 : 1);
        sub_0012E5E0(1);
    }
    sub_00113370(act, blk);
}

/* 0x001311E0: steer obj toward act's target: flat offset, clamped to blk->f10 when longer;
   store its components along obj's matrix rows 0 and 2 as the work direction, and free the node
   once the height difference is within blk->f14. */
void r3e_Steer1311E0(R3eObj *obj, R3eObj *act, R3eNode *blk)
{
    float d[4], f[4], e[4];
    R3eWork *w = act->work278;
    R3eWork *u;
    float dy, len, z, x;

    sub_001AD9F0(d, act->p104->pos60, obj->pos60);
    dy = sub_001A3F30(d[1]);
    d[1] = 0.0f;
    d[3] = 1.0f;
    sub_001AD7E0(e, d);
    len = sub_001AD9D0(e, d);
    if (len > blk->f10)
        sub_001ADBA0(f, d, blk->f10);
    else
        sub_000F5D40(f, d);
    z = sub_001AD9D0(obj->m20 + 8, f);
    x = sub_001AD9D0(obj->m20, f);
    u = act->work278;
    u->v164[2] = z;
    u->v164[1] = w->v164[1];
    u->v164[0] = x;
    u->v164[3] = 1.0f;
    if (blk->f14 >= dy)
        sub_00113370(act, blk);
}
