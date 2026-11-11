/* Area rbj: actors of the 0x001671D0 family (rbj_5). Names inferred. */
#include "rbj.h"

/* 0x0016BF80: pick a target. Phase 0 starts a timer of 30 * frame time and moves to phase
   1; in phase 1, while the timer is negative, the first used target slot of each kind
   (flags bit 2, with and without bit 4) is looked up. With neither the actor goes to state 2.
   Otherwise the nearer one (99999 when missing) becomes the work target, work flag 4 tells
   which kind, flag 0x10 is cleared and the actor goes to state 0. */
void rbj_PickTarget16BF80(RbjNode *node, RbjBAct *act)
{
    RbjBWork *w = act->work74;
    RbjNode *a, *b;
    float da, db;
    int i;

    da = 99999.0f;
    db = 99999.0f;
    switch (act->phase54) {
    case 0:
        act->timer5C = a50_frameSeconds * 30.0f;
        act->phase54 = 1;
    case 1:
        break;
    default:
        return;
    }
    if (!(0.0f > act->timer5C))
        return;
    a = 0;
    for (i = 0; i < 5; i++) {
        if ((b16_pool18[i].flags & 2) && !(b16_pool18[i].flags & 4)) {
            a = b16_pool18[i].obj14;
            break;
        }
    }
    b = 0;
    for (i = 0; i < 5; i++) {
        if ((b16_pool18[i].flags & 2) && (b16_pool18[i].flags & 4)) {
            b = b16_pool18[i].obj14;
            break;
        }
    }
    if (a == 0 && b == 0) {
        b16_SetState(node, act, 2);
        return;
    }
    if (a != 0)
        da = rbj_Distance(&node->pos60, &a->pos60);
    if (b != 0)
        db = rbj_Distance(&node->pos60, &b->pos60);
    w->target10 = db > da ? &a->pos60 : &b->pos60;
    w->flags00 = (w->flags00 | (db > da ? 0 : 4)) & ~0x10u;
    b16_SetState(node, act, 0);
}

/* 0x0016C690: bobbing. Runs the work timer down; once it is negative, the bob angle advances
   by 0.75 deg (wrapped at pi) and the height change of a point at radius28 rotated by it
   is taken off the node's push y and f2C; the node's x angle then turns towards
   -(2 or 3) * change, at most 2 deg per frame unit.
   regargs: act=EAX node=EDI. */
void rbj_Bob16C690(RbjBAct *act, RbjNode *node)
{
    RbjBWork *w = act->work74;
    RbjMat4 m;
    RbjVec4 t;
    float k, d, lim, nlim;

    w->timer20 = w->timer20 - a50_frameSeconds;
    if (!(0.0f > w->timer20))
        return;
    rbj_MatIdentity(&m);
    t.x = 0.0f;
    t.y = 0.0f;
    t.w = 1.0f;
    t.z = w->radius28;
    rbj_MatTranslate(&m, &m, &t);
    rbj_MatRotX(&m, &m, w->bob24);
    sub_000F5D40(&t, &m.r[3]);
    w->bob24 = w->bob24 + 0.0130899698f;
    if (w->bob24 > 3.14159274f)
        w->bob24 = w->bob24 - 6.28318548f;
    rbj_MatRotX(&m, &m, 0.0130899698f);
    rbj_VecSub(&t, &t, &m.r[3]);
    node->push80.y = node->push80.y - t.y;
    w->f2C = w->f2C - t.y;
    k = (t.y > 0.0f) ? 2.0f : 3.0f;
    d = 0.0f - k * t.y - node->rot50.x;
    lim = a50_frameUnits * 0.0349065848f;
    nlim = 0.0f - lim;
    if (nlim > d) {
        node->rot50.x = node->rot50.x + nlim;
        return;
    }
    if (d > lim)
        d = lim;
    node->rot50.x = node->rot50.x + d;
}

/* 0x0016DFD0: homing piece. Phase 0 turns towards the work goal 1 deg per frame unit
   (right when more than 2 deg off, otherwise left) and, until within 1 unit (then phase 1),
   pushes forward 10 units per second (scaled by -0.1 while more than 50 deg off). Phase 1
   tips the x angle up to 10 deg, turns towards the fixed point (3.91, -2.13, -44.98)
   with a 5 deg dead zone and, once aimed, switches to state 0xB when above the floor
   height or hit (through 0x0016C820 with EAX=act EDI=node). Below the floor height the
   node rises 3 units per second. */
void rbj_Home16DFD0(RbjNode *node, RbjBAct *act)
{
    RbjFWork *w = (RbjFWork *)act->work74;
    float d;

    switch (act->phase54) {
    case 0:
        d = sub_00113290(node, &w->goalC);
        if (d > 0.0349065848f)
            node->rot50.y = a50_frameUnits * 0.0174532924f + node->rot50.y;
        else if (0.0349065848f > d)
            node->rot50.y = node->rot50.y - a50_frameUnits * 0.0174532924f;
        if (1.0f > rbj_Distance(&node->pos60, &w->goalC)) {
            act->phase54++;
        } else {
            node->push80.z = 0.0f - a50_frameSeconds * 10.0f * a50_frameUnits;
            if (d > 0.872664631f || -0.872664631f > d)
                node->push80.z = a50_frameSeconds * 10.0f * a50_frameUnits * -0.100000001f;
        }
        break;
    case 1:
        if (0.174532935f > node->rot50.x)
            node->rot50.x = a50_frameUnits * 0.00872664619f + node->rot50.x;
        d = sub_00113290(node, &rbj_vec31F410);
        if (d > 0.0872664675f)
            node->rot50.y = a50_frameUnits * 0.0174532924f + node->rot50.y;
        else if (-0.0872664675f > d)
            node->rot50.y = node->rot50.y - a50_frameUnits * 0.0174532924f;
        else if (node->pos60.y > w->floor40 || (node->b128 & 6))
            r3_SetState16C820(act, node, 0xB);
        break;
    }
    if (w->floor40 > node->pos60.y)
        node->push80.y = a50_frameSeconds * 3.0f * a50_frameUnits;
}

/* 0x0016E250: circling flyer. Turns towards Jack 1 deg per frame unit outside a 10 deg dead
   zone (three times as fast with work flag 0x2000) and sinks 5 units per second above the
   floor height. Phase 0 waits for the node's animation, plays animation 1 and starts a
   random 20..30 s timer. Phase 1: within 20 units or more than 45 deg off, a closing-in
   flag 0x400 becomes 0x2000 (yaw remembered); otherwise, unless 0x2400 is set, flag 0x400
   is set with f38 = 10 frame units. When the timer runs out the actor switches to state 0xE
   (0x0016C820 with EAX=act EDI=node) and work flags 0x202080 and f34 are cleared. */
void rbj_Circle16E250(RbjNode *node, RbjBAct *act)
{
    RbjGWork *w = (RbjGWork *)act->work74;
    const RbjVec4 *jack = (const RbjVec4 *)((uint8_t *)g_playerObj + 0x60);
    float step, dist, ang;

    step = 0.0f;
    dist = rbj_Distance(&node->pos60, jack);
    ang = sub_00113290(node, jack);
    if (ang > 0.174532935f)
        step = a50_frameUnits * 0.0174532924f;
    else if (-0.174532935f > ang)
        step = 0.0f - a50_frameUnits * 0.0174532924f;
    if (w->flags00 & 0x2000)
        step = step * 3.0f;
    node->rot50.y = step + node->rot50.y;
    if (node->pos60.y > w->floor40)
        node->push80.y = 0.0f - a50_frameSeconds * 5.0f * a50_frameUnits;
    switch (act->phase54) {
    case 0:
        if (sub_000833E0(node->anim30) != 0) {
            b16_PlayAnim(node, act, 1);
            act->phase54++;
            act->timer5C = ((float)(sub_001C7EE1() % 600) + 1200.0f) / a50_frameUnits
                           * a50_frameSeconds;
        }
        break;
    case 1:
        if (20.0f > dist || ang > 0.785398185f || -0.785398185f > ang) {
            if (w->flags00 & 0x400) {
                w->flags00 = (w->flags00 & ~0xC00u) | 0x2000;
                w->f38 = 0.0f;
                w->yaw3C = node->rot50.y;
            }
        } else if (!(w->flags00 & 0x2400)) {
            w->flags00 = (w->flags00 & ~0x2800u) | 0x400;
            w->f38 = 10.0f / a50_frameUnits * a50_frameSeconds;
        }
        if (0.0f > act->timer5C) {
            r3_SetState16C820(act, node, 0xE);
            w->flags00 &= 0xFFDFDF7Fu;
            w->f34 = 0.0f;
        }
        break;
    }
}
