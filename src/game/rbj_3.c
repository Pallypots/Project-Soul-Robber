/* Area rbj: spinning projectiles of the 0x00189DA0 actor family (rbj_3). Names inferred. */
#include "rbj.h"

/* 0x0018AD70: flying, spinning state. Flag 1 of flags10 follows 0x000CF6C0 (> 0). On a hit
   (b128 & 6): switch to state 3, play motion (5, 3) from 12 units above the node along the
   flat velocity (up = +Y), stop horizontal motion, wrap the spin angle into 0..2 pi, set
   node flags 0xA0 (clearing 0x40) and turn by pi - angle. Otherwise advance the spin by
   30 deg per frame unit and mark iF0 = 3 while rising. Either way the matrix is rotated
   about the work axis by that amount. */
void rbj_Spin18AD70(RbjNode *node, RbjActor *act)
{
    RbjStateWork *w = act->work74;
    RbjVec4 up, pos, vel;
    RbjMat4 q;
    float a, x;

    if (Stats_HasEFC() > 0)
        node->flags10 |= 1;
    else
        node->flags10 &= ~1u;
    if (node->b128 & 6) {
        rbj_SetState(node, act, 3);
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
        up.w = 0.0f;
        sub_000F5D40(&pos, &node->pos60);
        pos.y = pos.y + 12.0f;
        sub_000F5D40(&vel, &act->vel4C);
        vel.y = 0.0f;
        rbj_ObjSetMotionDir(sub_00035D80(node, 5, 3), &pos, &vel, &up);
        act->vel4C.x = 0.0f;
        act->vel4C.z = 0.0f;
        x = w->f20;
        if (x > 6.28318548f) {
            do {
                x = x - 6.28318548f;
            } while (x > 6.28318548f);
            w->f20 = x;
        }
        node->flags0C = (node->flags0C & ~0x40u) | 0xA0;
        a = 3.14159274f - w->f20;
    } else {
        a = a50_frameUnits * 0.52359879f;
        w->f20 = a + w->f20;
        if (act->vel4C.y > 0.0f)
            node->iF0 = 3;
    }
    rbj_MatAxisAngle(&q, &w->axis10, a);
    rbj_MatOrtho(node->xf20, node->xf20);
    rbj_MatMul(node->xf20, &q, node->xf20);
}

/* 0x0018AF90: spinning on the spot near Jack. While not hit and closer than 100 units to
   Jack, 0x000C56B0 runs, vertical speed is cleared, the matrix turns 30 deg per frame unit
   about Y and, when the f70 timer has run out, it is reset to 0.3 with sound 0x4B. On a hit
   or out of range: set flag 0x20, play sound 0xC3 (kind 0x1B) or 0xC9, set the throw values
   from the x scale and relaunch backwards (velocity * -1, y -2.3, speed 140) through
   0x0018A430 (EBX=act ESI=direction EDI=node). */
void rbj_Spin18AF90(RbjNode *node, RbjActor *act)
{
    RbjMat4 m;
    RbjVec4 back;
    float s;

    if (node->b128 & 6)
        goto hit;
    if (rbj_Distance(&node->pos60, (const RbjVec4 *)((uint8_t *)g_playerObj + 0x60)) >= 100.0f)
        goto hit;
    {
        sub_000C56B0(node);
        act->vel4C.y = 0.0f;
        rbj_MatIdentity(&m);
        rbj_MatRotY(&m, &m, a50_frameUnits * 0.52359879f);
        rbj_MatMul(node->xf20, node->xf20, &m);
        if (0.0f >= act->f70) {
            act->f70 = 0.3f;
            rbj_Sound(0x4B, &node->pos60, 0);
        }
        return;
    }
hit:
    node->flags0C |= 0x20;
    rbj_Sound(node->kind08 != 0x1B ? 0xC9 : 0xC3, &node->pos60, 0);
    s = node->scale70.x;
    act->f28 = s * -4.0f;
    node->fB0 = s * 5.0f;
    node->fB4 = s * -30.0f;
    node->fE8 = s * 12.0f;
    rbj_VecScale(&back, &act->vel4C, -1.0f);
    rbj_Launch18A430(act, &back, node, -2.29999995f, 140.0f);
}

/* 0x0018B260: release a held object (kinds 1..3 and 0x1B): run 0x0018B130, detach its
   matrix node, re-attach it to the scene, launch it along dir (y -1.6, speed 100) through
   0x0018A430 (EBX=actor ESI=dir EDI=o), take the holder's scale, clear the holder link and
   timer and flags10 bits 5, set the throw values from the x scale and the f70 timer
   (21 for kind 3, else 14). Hangs if the actor or its holder is missing. */
void rbj_Release18B260(RbjNode *o, const RbjVec4 *dir)
{
    RbjActor *a;
    RbjStateWork *w;
    float s;

    if (o == 0)
        return;
    if ((o->kind08 < 1 || o->kind08 > 3) && o->kind08 != 0x1B)
        return;
    a = (RbjActor *)sub_0001D960(o, 7);
    if (a == 0)
        for (;;)
            ;
    w = a->work74;
    if (w->owner04 == 0)
        for (;;)
            ;
    sub_0018B130();
    r4_NodeDetach(o->xf20);
    sub_0001E9B0(rbj_scene42C8E4, o, o->p14C, 5, 0x11);
    rbj_Launch18A430(a, dir, o, -1.60000002f, 100.0f);
    sub_000F5D40(&o->scale70, &w->owner04->scale70);
    a->f2C = o->scale70.x * -17.0f;
    w->timer0C = 0.0f;
    w->owner04 = 0;
    o->flags10 &= ~5u;
    s = o->scale70.x;
    a->f28 = s * -4.0f;
    o->fB0 = s * 5.0f;
    o->fB4 = s * -30.0f;
    o->fE8 = s * 12.0f;
    switch (o->kind08) {
    case 2:
        a->f70 = 14.0f;
        break;
    case 3:
        a->f70 = 21.0f;
        break;
    default:
        a->f70 = 14.0f;
        break;
    }
}
