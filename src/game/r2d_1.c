/* Area r2d, group 1: player record and camera rig helpers (0x000D1180..0x000D4C56). Names inferred. */
#include "r2d.h"

/* 0x000D1180: copy the player's link settings into its node's record at
   +0xA0 and rebuild it from the stored vector. */
void r2d_PlayerSetLink(R2dPlayer *p)
{
    R2dNode *n = p->nodeFD8;
    R2dPart *part = n->part20;
    float *rec = n->vA0;
    *(int32_t *)&rec[4] = p->v194;
    rec[5] = p->f190 * -1.0f;
    sub_001AD9F0(rec, p->v198, part->v70);
    rec[3] = 1.0f;
    *(int32_t *)&rec[12] = 3;
}

/* 0x000D1890: set the tint block to (0.1, 0.95, 0.2, 0.5). */
void r2d_TintA(void)
{
    r2d_tint417F20.d = 0.5f;
    r2d_tint417F20.a = 0.1f;
    r2d_tint417F20.b = 0.95f;
    r2d_tint417F20.c = 0.2f;
}

/* 0x000D18E0: set the tint block to (0.1, 0.95, 0.2, 0.98). */
void r2d_TintB(void)
{
    r2d_tint417F20.d = 0.98f;
    r2d_tint417F20.a = 0.1f;
    r2d_tint417F20.b = 0.95f;
    r2d_tint417F20.c = 0.2f;
}

/* 0x000D1CA0: move the player's node to pos, refresh the lights and clear
   the motion vectors. */
void r2d_PlayerPlace(R2dPlayer *p, const void *pos)
{
    sub_000F5D40(p->nodeFD8->pos60, pos);
    r2d_LightsRefresh();
    p->v110[2] = 0.0f;
    p->v110[1] = 0.0f;
    p->v110[0] = 0.0f;
    p->f11C = 1.0f;
    p->f14C = 0.0f;
    p->f148 = 0.0f;
}

/* 0x000D2440: reset the 0x1C0 block, reading event bits 0xF5 and 0xF4. */
void r2d_PlayerResetD8(R2dPlayer *p)
{
    p->v1C0 = -1;
    p->f1C4 = 0.0f;
    p->v1C8 = 1;
    p->v1CC = sub_000D9A70(0xF5);
    p->v1D0 = sub_000D9A70(0xF4);
    p->v1D4 = 0;
}

/* 0x000D2D30: once the player has fallen far enough (speed * frame units +
   distance above 1.2) with none of the blocking flags, enter state 0x1F. */
void r2d_PlayerCheckFall(R2dPlayer *p)
{
    if (p->stateD8 && !(p->flags150 & 0x80E022C6)) {
        if (p->v110[1] * a50_frameUnits + p->f148 > 1.2f) {
            sub_000D1930(p);
            sub_000BD4D0(p, 0x1F);
            p->flags150 |= 0x200000;
        }
    }
}

/* 0x000D23D0: warp the player to pos facing angle and enter state 0x21. */
void r2d_PlayerWarp(const void *pos, float angle)
{
    sub_000F5D40((uint8_t *)g_playerObj + 0x60, pos);
    r2d_player.f108 = angle;
    r2d_player.fFC = angle;
    sub_000D1930(&r2d_player);
    r2d_player.flags150 |= 2;
    sub_000BD4D0(&r2d_player, 0x21);
    sub_000CED00(sub_0001D290(g_playerObj, 0));
}

