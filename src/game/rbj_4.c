/* Area rbj: carried and hovering objects of the 0x00189DA0 actor family (rbj_4). Names inferred. */
#include "rbj.h"

/* 0x0018C540: drop a carried object when its work flag 2 is set: detach it from the bone it
   hangs on (keeping that bone's position), re-attach it to the scene, take the holder's
   scale and rotation, push it 40 units per second backwards along its yaw, pick a random
   spin pi / (60 + rand % 30), set node flags 0x1E0, clear flags10 bits 5 and switch to
   state 1. Hangs if the actor or the holder is missing. */
void rbj_Drop18C540(RbjNode *o)
{
    RbjActor *a;
    RbjCarryWork *w;
    RbjBone *bone;
    RbjVec4 v;
    RbjMat4 m;
    int r;

    a = (RbjActor *)sub_0001D960(o, 7);
    if (a == 0)
        for (;;)
            ;
    w = (RbjCarryWork *)a->work74;
    if (w->holder0C == 0)
        for (;;)
            ;
    if (!(w->flags00 & 2))
        return;
    bone = o->xf20->parent80;
    r4_NodeDetach(o->xf20);
    sub_0001E9B0(rbj_scene42C8E4, o, o->p14C, 5, 0x11);
    sub_000F5D40(&o->pos60, &bone->pos70);
    sub_000F5D40(&o->scale70, &w->holder0C->scale70);
    sub_000F5D40(&o->rot50, &w->holder0C->rot50);
    v.w = 1.0f;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f - a50_frameSeconds * 40.0f;
    rbj_MatIdentity(&m);
    rbj_MatTranslate(&m, &m, &v);
    rbj_MatRotY(&m, &m, o->rot50.y);
    sub_000F5D40(&o->push80, &m.r[3]);
    r = sub_001C7EE1() % 30;
    w->flags00 &= ~2u;
    w->f04 = 3.14159274f / ((float)r + 60.0f);
    o->flags0C |= 0x1E0;
    o->flags10 &= ~5u;
    rbj_SetState(o, a, 1);
}

/* 0x0018C950: hovering state. Switches to state 2 when 0x00087500 reports true (unless
   already there). Otherwise flag 1 of flags10 follows 0x000CF6C0 unless work flags 6 are
   set, the x and y angles are wrapped into -pi..pi, the node moves by its push vector
   (not cleared), its matrix is rebuilt from the x then y rotation and, above height 200,
   it switches to state 2. */
void rbj_Hover18C950(RbjNode *node, RbjActor *act)
{
    RbjStateWork *w = act->work74;
    RbjMat4 m;

    if (a80_Get3ED238() != 0 && act->state60 != 2) {
        rbj_SetState(node, act, 2);
        return;
    }
    if (!(w->flags00 & 6)) {
        if (Stats_HasEFC() > 0)
            node->flags10 |= 1;
        else
            node->flags10 &= ~1u;
    }
    if (node->rot50.x > 3.14159274f)
        node->rot50.x = node->rot50.x - 6.28318548f;
    if (node->rot50.x < -3.14159274f)
        node->rot50.x = node->rot50.x + 6.28318548f;
    if (node->rot50.y > 3.14159274f)
        node->rot50.y = node->rot50.y - 6.28318548f;
    if (node->rot50.y < -3.14159274f)
        node->rot50.y = node->rot50.y + 6.28318548f;
    rbj_VecAdd(&node->pos60, &node->pos60, &node->push80);
    node->pos60.w = 1.0f;
    rbj_MatIdentity(&m);
    rbj_MatRotX(&m, &m, node->rot50.x);
    rbj_MatRotY(&m, &m, node->rot50.y);
    rbj_MatCopy(&node->xf20->m, &m);
    if (node->pos60.y > 200.0f)
        rbj_SetState(node, act, 2);
}

/* 0x0018CE50: burst. Plays motion (4, 3) of the node's motion list at its position facing -Z
   (up = +Y), a light 0x20E (grey 0x80, size 100) and, with work flag 4, effect 0x000C46A0
   (12.5, 1/60, 2.5) handed to 0x000C4D30 (kind 10, 10.0); otherwise 0x000C4DF0
   (0, 10.0, 0, 12.5, 1.0, 2.5). The node is then destroyed. */
void rbj_Burst18CE50(RbjNode *node, RbjActor *act)
{
    RbjVec4 v, up, dir;
    void *mot;

    dir.z = -1.0f;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 0.0f;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.w = 1.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    up.w = 1.0f;
    mot = rbj_ListPlayMotion(node, node->p130, 4, 3);
    rbj_Place34E00(mot, &node->pos60, &dir, &up);
    sub_00049700(0x20E, 0x80, 0x80, 0x80, &node->pos60, 1, 100.0f, 0);
    if (act->work74->flags00 & 4) {
        sub_000C4D30(node, 10, 10.0f,
                     sub_000C46A0(12.5f, 0.0166666675f, 2.5f, &node->pos60, &v, &v));
        rbj_ObjDestroy(node);
        return;
    }
    sub_000C4DF0(node, 0, 10.0f, 0, 12.5f, 1.0f, 2.5f, &node->pos60, &v, &v);
    rbj_ObjDestroy(node);
}
