/* Area rbk: enemy AI of the 0x0018C1B0 family. Names inferred. */
#include "rbk.h"

/* 0x0018BCA0: swipe hit test against Jack. A two-point probe (radius 0.05, reach 0.2,
   length 4) is built from the actor's collision object and tested against the node's
   transform. On a hit with Jack's reach area non-empty, the hit point is checked against
   that area; when it is inside, Jack is hit (0x000D3BF0 kind 1) from the flat direction
   node -> Jack. Returns the inside test (0 when nothing was hit).
   regargs: node=EDI act=stack. */
int rbk_HitJack18BCA0(RbjNode *node, RbkAct *act)
{
    RbjXform *xf = node->xf20;
    RbkProbe probe;
    float shape[12];
    float size[4];
    RbkReach reach;
    RbkHit hit;
    RbkProbeBox box;
    RbjVec4 dir;
    int r;

    shape[0] = 0.05f;
    shape[1] = 1.0f;
    shape[2] = 0.0f;
    shape[3] = 0.0f;
    shape[4] = 0.0f;
    shape[5] = 1.0f;
    shape[6] = 0.2f;
    shape[7] = 4.0f;
    shape[8] = 0.0f;
    shape[9] = 0.0f;
    shape[10] = 0.0f;
    shape[11] = 1.0f;
    probe.kind00 = 0;
    probe.count04 = 2;
    probe.shape08 = shape;
    sub_000EEBC0(act->coll6C, &probe, &box);
    sub_000EE3B0(xf, &box, &hit);
    if (0.0f >= hit.s.r10)
        return 0;
    sub_000C4250(&g_stats, &reach, size);
    reach.x10 = size[0];
    reach.y14 = size[1];
    if (size[0] == 0.0f || size[1] == 0.0f)
        return 0;
    r = sub_000EE2B0(&hit.s, &reach, &hit.point14);
    if (r != 0) {
        rbj_VecSub(&dir, (const RbjVec4 *)((uint8_t *)g_playerObj + 0x60), &node->pos60);
        dir.y = 0.0f;
        dir.w = 1.0f;
        rbj_VecNormalize(&dir, &dir);
        sub_000D3BF0(&g_stats, node, 1, &hit.point14, &dir);
    }
    return r;
}

/* 0x0018CB60: rolling actor. The node's local matrix is rebuilt from its yaw just to measure
   the signed angle to Jack and is then overwritten by a copy of the world matrix. The roll
   angle advances by the work speed. On the ground the vertical push is reflected (-1),
   the roll gets a double step, the bounce is clamped to -0.7 (or -0.3 with work flag 0x20)
   and -0.3 frame units, the actor steers 0.25 rad towards Jack when more than 30 deg off
   (unless flag 4), and a fresh landing (bit 8) plays motion 5 and sound 0x20C. Gravity of
   0.02 per frame unit squared applies unless flag 8. With flag 4 the node is stopped
   (0x000C56B0); otherwise, while Jack is attackable (0x000CFFB0 != -1), a sphere of 2.5 x
   scale y around the node is tested against Jack's reach area. A touch, a landing on a wall
   (bits 6 without 0x18), or a state timer above 5 switches to state 2. */
void rbk_Roll18CB60(RbjNode *node, RbjActor *act)
{
    RbkRollWork *w = (RbkRollWork *)act->work74;
    RbkXform2 *xf = (RbkXform2 *)node->xf20;
    RbjMat4 save, rot;
    RbkSphere s;
    RbkReach reach;
    float size[4];
    RbjVec4 dir, up, touch;
    float ang, lim, bounce;
    void *mot;
    uint32_t f;

    rbj_MatCopy(&save, &xf->m);
    rbj_MatIdentity(&rot);
    rbj_MatRotY(&xf->local40, &rot, node->rot50.y);
    ang = sub_00113290(node, (const RbjVec4 *)((uint8_t *)g_playerObj + 0x60));
    rbj_MatCopy(&xf->local40, &save);
    node->rot50.x = node->rot50.x + w->spin04;
    if (node->b128 & 0x18) {
        node->push80.y = node->push80.y * -1.0f;
        bounce = -0.3f;
        node->rot50.x = w->spin04 * 2.0f + node->rot50.x;
        if (w->flags00 & 0x20)
            lim = a50_frameUnits * bounce;
        else
            lim = a50_frameUnits * -0.7f;
        if (lim > node->push80.y)
            node->push80.y = lim;
        lim = a50_frameUnits * bounce;
        if (node->push80.y > lim)
            node->push80.y = lim;
        if (!(w->flags00 & 4)) {
            if (ang > 0.52359879f)
                r3_Rotate18CB10(node, 0.249582097f);
            else if (-0.52359879f > ang)
                r3_Rotate18CB10(node, -0.249582097f);
        }
        if (node->b128 & 8) {
            mot = rbj_ListPlayMotion(node, node->p130, 5, 3);
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = -1.0f;
            dir.w = 1.0f;
            up.x = 0.0f;
            up.y = 1.0f;
            up.z = 0.0f;
            up.w = 1.0f;
            rbj_Place34E00(mot, &node->pos60, &dir, &up);
            sub_00049700(0x20C, 0x80, 0x80, 0x80, &node->pos60, 1, 100.0f, 0);
        }
    }
    if (!(w->flags00 & 8))
        node->push80.y = a50_frameUnits * 0.02f * a50_frameUnits + node->push80.y;
    if (w->flags00 & 4) {
        sub_000C56B0(node);
    } else if (sub_000CFFB0() != -1) {
        sub_000F5D40(&s.c, &node->pos60);
        s.r10 = node->scale70.y * 2.5f;
        sub_000C4250(&g_stats, &reach, size);
        reach.x10 = size[0];
        reach.y14 = size[1];
        if (size[0] != 0.0f && size[1] != 0.0f && sub_000EE2B0(&s, &reach, &touch) != 0)
            goto hit;
    }
    f = node->b128;
    if ((f & 6) && !(f & 0x18))
        goto hit;
    if (!(act->timer6C > 5.0))
        return;
hit:
    rbj_SetState(node, act, 2);
}

/* 0x0018D400: launch a thrown piece o from the thrower `from` (component 7 of o must
   exist). o takes the thrower's position (13 x scale y lower), scale and yaw. Two launch
   sets are kept as a table (x angle, lift, push, unused): bit 0 of mode picks the high
   throw (-7 deg / 120 / 2.33 frame units) over the flat one (-30 deg / 60 / 0.75 frame
   units); a high throw at Jack within 100 units who is above the thrower is made flat
   (angle 0). The push is the forward vector rotated by the angle and yaw; the work's
   forward speed is the push expressed back in o's yaw frame, its lift the table value and
   its speed one frame unit (0.3 for the flat throw). Called with stack args (o from mode). */
void rbk_Throw18D400(RbjNode *o, RbjNode *from, int mode)
{
    RbjVec4 set[2];
    RbjMat4 m;
    RbjVec4 v;
    RbkCompHolder *comp;
    RbkShotWork *w;
    void *jack;
    float ang;
    int k;

    set[0].x = -0.52359879f;
    set[0].y = 60.0f;
    set[0].z = a50_frameUnits * 0.75f;
    set[0].w = a50_frameUnits * -0.374999702f;
    set[1].x = -0.122173049f;
    set[1].y = 120.0f;
    set[1].z = a50_frameUnits * 2.32999992f;
    set[1].w = a50_frameUnits * -0.283954591f;
    comp = (RbkCompHolder *)sub_0001D960(o, 7);
    if (comp == 0)
        return;
    w = (RbkShotWork *)comp->work74;
    sub_000F5D40(&o->pos60, &from->pos60);
    o->pos60.y = o->pos60.y - from->scale70.y * 13.0f;
    sub_000F5D40(&o->scale70, &from->scale70);
    o->rot50.y = from->rot50.y;
    rbj_MatIdentity(&m);
    k = mode & 1;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
    v.w = 1.0f;
    ang = set[k].x;
    if (k != 0) {
        jack = g_playerObj;
        if (100.0f > rbj_Distance(&from->pos60, (const RbjVec4 *)((uint8_t *)jack + 0x60))
            && ((const RbjVec4 *)((uint8_t *)jack + 0x60))->y > from->pos60.y)
            ang = 0.0f;
    }
    rbj_MatRotX(&m, &m, ang);
    rbj_MatRotY(&m, &m, o->rot50.y);
    v.z = 0.0f - set[k].z;
    rbj_VecTransform(&v, &m, &v);
    sub_000F5D40(&o->push80, &v);
    rbj_MatIdentity(&m);
    rbj_MatRotY(&m, &m, 0.0f - o->rot50.y);
    v.y = 0.0f;
    rbj_VecTransform(&v, &m, &v);
    w->lift0C = set[k].y;
    w->fwd10 = 0.0f - v.z;
    w->speed04 = k != 0 ? a50_frameUnits : a50_frameUnits * 0.3f;
}

