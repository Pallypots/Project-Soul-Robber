/* Area rbj: state-machine actors of the 0x00189DA0 family (rbj_1). Names inferred. */
#include "rbj.h"

/* 0x0018A430: turn a node to face a direction and launch it. The node's matrix is rebuilt
   (-90 deg about X, -90 deg about Y, 15 deg about Z, then the yaw between -Z and the flat
   direction about Y), its position copied from the transform block, the velocity set to the
   flat direction with height y scaled to speed, the work axis set to dir x (0,-1,0) and the
   actor switched to state 2.
   regargs: act=EBX dir=ESI node=EDI; y and speed on the stack. */
void rbj_Launch18A430(RbjActor *act, const RbjVec4 *dir, RbjNode *node, float y, float speed)
{
    RbjStateWork *w = act->work74;
    RbjVec4 a, b;
    RbjMat4 m;
    float ang;

    a.x = 0.0f;
    a.y = 0.0f;
    a.z = -1.0f;
    a.w = 1.0f;
    sub_000F5D40(&b, dir);
    b.y = 0.0f;
    rbj_VecNormalize(&b, &b);
    ang = rbj_VecDot(&b, &a);
    if (ang > 1.0f)
        ang = 1.0f;
    else if (ang < -1.0f)
        ang = -1.0f;
    ang = rbj_Acos(ang);
    rbj_VecCross(&a, &a, &b);
    if (a.y < 0.0f)
        ang = 0.0f - ang;
    rbj_MatIdentity(&m);
    rbj_MatRotX(&m, &m, -1.57079637f);
    rbj_MatRotY(&m, &m, -1.57079637f);
    rbj_MatRotZ(&m, &m, 0.261799395f);
    rbj_MatRotY(&m, &m, ang);
    rbj_MatCopy(&node->xf20->m, &m);
    sub_000F5D40(&node->pos60, &node->xf20->pos70);
    ang = rbj_Sqrt(dir->x * dir->x + dir->z * dir->z);
    ang = 1.0f / ang;
    a.x = dir->x * ang;
    a.y = y;
    a.z = ang * dir->z;
    a.w = 0.0f;
    rbj_VecNormalize(&a, &a);
    rbj_VecScale(&act->vel4C, &a, speed);
    a.x = 0.0f;
    a.y = -1.0f;
    a.z = 0.0f;
    a.w = 1.0f;
    rbj_VecCross(&w->axis10, dir, &a);
    w->f20 = 0.0f;
    rbj_SetState(node, act, 2);
}

/* 0x0018A660: falling state. When the work block has an owner, destroy the node unless the
   owner's flag 1 is set. Otherwise apply gravity (196 per second squared) to the velocity,
   brake the horizontal velocity towards zero (rate 10 * 0.8, or 10 * 4 on the ground), move
   the node by velocity * frame time plus its one-frame push (then cleared), reset w = 1, take
   two offsets from bone 3 of the parent skeleton, raise the second by 0.5 (copied to vF8,
   whose y is then -10 - step y) and run the work timer. The matrix is re-orthonormalised at the end. */
void rbj_Fall18A660(RbjNode *node, RbjActor *act)
{
    RbjNode *owner = act->work74->owner04;
    RbjVec4 step;
    RbjVec4 *bone, *push;
    float k;

    if (owner != 0) {
        if (!(owner->flags0C & 1))
            rbj_ObjDestroy(node);
    } else {
        k = (node->b128 & 0x18) ? 4.0f : 0.8f;
        act->vel4C.y = a50_frameSeconds * 196.0f + act->vel4C.y;
        if (act->vel4C.x > 0.0f) {
            act->vel4C.x = act->vel4C.x - k * 10.0f * a50_frameSeconds;
            if (act->vel4C.x < 0.0f)
                act->vel4C.x = 0.0f;
        } else if (act->vel4C.x < 0.0f) {
            act->vel4C.x = k * 10.0f * a50_frameSeconds + act->vel4C.x;
            if (act->vel4C.x > 0.0f)
                act->vel4C.x = 0.0f;
        }
        if (act->vel4C.z > 0.0f) {
            act->vel4C.z = act->vel4C.z - k * 10.0f * a50_frameSeconds;
            if (act->vel4C.z < 0.0f)
                act->vel4C.z = 0.0f;
        } else if (act->vel4C.z < 0.0f) {
            act->vel4C.z = k * 10.0f * a50_frameSeconds + act->vel4C.z;
            if (act->vel4C.z > 0.0f)
                act->vel4C.z = 0.0f;
        }
        rbj_VecScale4(&step, &act->vel4C, a50_frameSeconds);
        rbj_VecAdd(&node->pos60, &node->pos60, &step);
        if (node->b128 & 0x18)
            act->vel4C.y = 0.0f;
        push = &node->push80;
        rbj_VecAdd(&node->pos60, &node->pos60, push);
        push->x = 0.0f;
        push->y = 0.0f;
        push->z = 0.0f;
        push->w = 1.0f;
        node->pos60.w = 1.0f;
        bone = &node->xf20->bonesC4[3].pos70;
        rbj_VecSub(&node->vA0, bone, &node->xf20->pos70);
        rbj_VecSub(&node->v108, bone, &node->xf20->pos70);
        sub_000F5D40(&node->vF8, &node->v108);
        node->v108.y = node->v108.y + 0.5f;
        node->vF8.y = -10.0f - step.y;
        act->work74->timer0C = act->work74->timer0C + a50_frameSeconds;
    }
    rbj_MatOrtho(node->xf20, node->xf20);
}

/* 0x0018A9A0: landing state entry. Sets f70 = 1. If work flag 0x10000 is set, plays motion
   (2, 1); otherwise plays motion (4, 3) aimed at the node's flat facing (-Z through its
   matrix, normalised in x/z) from its position raised to joint 1's height, with up = +Y.
   Then sound 0xC5 at the position, clears node flags 0xC0 and sets flags10 bits 0xD. */
void rbj_Land18A9A0(RbjNode *node, RbjActor *act)
{
    RbjVec4 dir, up, pos;
    void *mot;
    float inv;

    act->f70 = 1.0f;
    if (act->work74->flags08 & 0x10000) {
        sub_00035D80(node, 2, 1);
    } else {
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = -1.0f;
        dir.w = 0.0f;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
        up.w = 0.0f;
        sub_000F5D40(&pos, &node->pos60);
        pos.y = rbj_Joint(node, 1)->pos70.y;
        rbj_VecTransform(&dir, node->xf20, &dir);
        inv = 1.0f / rbj_Sqrt(dir.z * dir.z + dir.x * dir.x);
        dir.x = inv * dir.x;
        dir.y = 0.0f;
        dir.z = inv * dir.z;
        dir.w = 0.0f;
        mot = sub_00035D80(node, 4, 3);
        rbj_ObjSetMotionDir(mot, &pos, &dir, &up);
    }
    rbj_Sound(0xC5, &node->pos60, 0);
    node->flags0C &= ~0xC0u;
    node->flags10 |= 0xD;
}

/* 0x00189ED0: default per-frame movement (the actor's +0x7C callback). Wraps the yaw into
   -pi..pi and builds the scale/rotation matrix (Z, Y, X order; the result is not used),
   moves the node by its one-frame push (then cleared) and its velocity, stops vertical speed
   on the ground, adds gravity (0.06 per frame unit) and damps horizontal speed by 0.1 per
   frame unit. */
void rbj_Move189ED0(RbjNode *node, RbjActor *act)
{
    RbjMat4 m;
    RbjVec4 p;
    RbjVec4 *push;

    if (node->rot50.y > 3.14159274f)
        node->rot50.y = node->rot50.y - 6.28318548f;
    if (node->rot50.y < -3.14159274f)
        node->rot50.y = node->rot50.y + 6.28318548f;
    rbj_MatIdentity(&m);
    m.r[0].x = node->scale70.x;
    m.r[1].y = node->scale70.y;
    m.r[2].z = node->scale70.z;
    rbj_MatRotZ(&m, &m, node->rot50.z);
    rbj_MatRotY(&m, &m, node->rot50.y);
    rbj_MatRotX(&m, &m, node->rot50.x);
    push = &node->push80;
    rbj_VecAdd(&p, &node->pos60, push);
    push->x = 0.0f;
    push->y = 0.0f;
    push->z = 0.0f;
    push->w = 1.0f;
    rbj_VecAdd(&p, &p, &act->vel4C);
    p.w = 1.0f;
    if (node->b128 & 0x18)
        act->vel4C.y = 0.0f;
    act->vel4C.y = a50_frameUnits * 0.0599999987f + act->vel4C.y;
    act->vel4C.x = (1.0f - a50_frameUnits * 0.100000001f) * act->vel4C.x;
    act->vel4C.z = (1.0f - a50_frameUnits * 0.100000001f) * act->vel4C.z;
    sub_000F5D40(&node->pos60, &p);
}
