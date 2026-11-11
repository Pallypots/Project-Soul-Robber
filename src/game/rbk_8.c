/* Area rbk: enemy pieces of the 0x00189DA0 family (0x0018D000..0x0018FFFF). Names inferred. */
#include "rbk.h"

/* 0x0018DA80: spinning bomb. Landing on a wall or floor edge (contact bits 6) ends it in
   state 1. The fuse burns (flag 4 once past its maximum), the bomb spins and falls with
   gravity 0.02 per frame unit squared unless stuck (flag 2, which still falls with flag 8).
   A stuck bomb only stops (0x000C56B0). Otherwise, while Jack can be hit, a sphere of
   2.5 x scale y touching Jack's reach area makes an explosion effect (0x000C4DF0: power 10,
   radii 2.5) and ends in state 1. Called with stack args (node act). */
void rbk_Bomb18DA80(RbjNode *node, RbjActor *act)
{
    RbkBombWork *w = (RbkBombWork *)act->work74;
    RbkSphere s;
    RbkReach reach;
    float size[4];
    RbjVec4 touch, v;
    uint32_t f;

    if (node->b128 & 6) {
        rbj_SetState(node, act, 1);
        return;
    }
    w->fuse08 = w->fuseRate10 + w->fuse08;
    if (w->fuse08 > w->fuseMax0C)
        w->flags00 |= 4;
    node->rot50.x = w->spin04 + node->rot50.x;
    f = w->flags00;
    if (!(f & 2) || (f & 8))
        node->push80.y = a50_frameUnits * 0.02f * a50_frameUnits + node->push80.y;
    if (w->flags00 & 2) {
        sub_000C56B0(node);
        return;
    }
    if (sub_000CFFB0() == -1)
        return;
    sub_000F5D40(&s.c, &node->pos60);
    s.r10 = node->scale70.y * 2.5f;
    sub_000C4250(&g_stats, &reach, size);
    reach.x10 = size[0];
    reach.y14 = size[1];
    if (size[0] != 0.0f && size[1] != 0.0f && sub_000EE2B0(&s, &reach, &touch) != 0) {
        v.x = 0.0f;
        v.y = 0.0f;
        v.z = 0.0f;
        v.w = 0.0f;
        sub_000C4DF0(node, 0, 10.0f, 0, 2.5f, 0.0f, 2.5f, &s.c, &v, &v);
        rbj_SetState(node, act, 1);
    }
}


/* 0x0018FA40: start the boss arm piece. The boss is marked busy; the arm's heading is the
   boss body's yaw turned by -90 deg (wrapped above -pi) and its velocity 80 units per second
   along it, which also becomes the boss's arm direction. With a target found (0x0018F7B0)
   the boss reach is the distance to it less 30, otherwise 120. The piece is placed at the
   boss body's x/z, height -4, angles (0, 0, 90 deg). Called with stack args (node act). */
void rbk_ArmStart18FA40(RbjNode *node, RbjActor *act)
{
    RbkBoss *boss = r4i_GetMgr();
    RbkArmWork *w = (RbkArmWork *)act->work74;
    RbjVec4 target;
    float a;

    boss->busy1CA = 1;
    a = 0.0f - boss->body8C->rot50.y - 1.57079637f;
    if (-3.14159274f > a)
        a = a + 6.28318548f;
    w->vel0C.x = sub_001A3EE0(a) * (80.0f / a50_framesPerSecond);
    w->vel0C.w = 0.0f;
    w->vel0C.y = 0.0f;
    w->vel0C.z = sub_001A3ED0(a) * (80.0f / a50_framesPerSecond);
    rbj_VecNormalize(&boss->dir1D4, &w->vel0C);
    if (sub_0018F7B0(&target) != 0)
        boss->reach1CC = rbj_Distance(&target, &node->pos60) - 30.0f;
    else
        boss->reach1CC = 120.0f;
    node->pos60.y = -4.0f;
    node->pos60.x = boss->body8C->pos60.x;
    node->pos60.z = boss->body8C->pos60.z;
    node->rot50.y = 0.0f;
    node->rot50.x = 0.0f;
    node->rot50.z = 1.57079637f;
}
