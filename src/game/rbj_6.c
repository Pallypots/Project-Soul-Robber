/* Area rbj: falling and walking helpers (rbj_6). Names inferred. */
#include "rbj.h"

/* 0x0016FCB0: falling movement for actors with the velocity at +0x5C: gravity 196 per second
   squared, horizontal braking 10 * 0.8 (10 * 8 on the ground) towards zero, move the node
   by velocity * frame time, stop vertical speed on the ground, add the one-frame push
   (then cleared) and reset w = 1.
   regargs: act=EAX node on the stack. */
void rbj_Fall16FCB0(RbjCAct *act, RbjNode *node)
{
    RbjVec4 step;
    RbjVec4 *push;
    float k;

    k = (node->b128 & 0x18) ? 8.0f : 0.8f;
    act->vel5C.y = a50_frameSeconds * 196.0f + act->vel5C.y;
    if (act->vel5C.x > 0.0f) {
        act->vel5C.x = act->vel5C.x - k * 10.0f * a50_frameSeconds;
        if (act->vel5C.x < 0.0f)
            act->vel5C.x = 0.0f;
    } else if (act->vel5C.x < 0.0f) {
        act->vel5C.x = k * 10.0f * a50_frameSeconds + act->vel5C.x;
        if (act->vel5C.x > 0.0f)
            act->vel5C.x = 0.0f;
    }
    if (act->vel5C.z > 0.0f) {
        act->vel5C.z = act->vel5C.z - k * 10.0f * a50_frameSeconds;
        if (act->vel5C.z < 0.0f)
            act->vel5C.z = 0.0f;
    } else if (act->vel5C.z < 0.0f) {
        act->vel5C.z = k * 10.0f * a50_frameSeconds + act->vel5C.z;
        if (act->vel5C.z > 0.0f)
            act->vel5C.z = 0.0f;
    }
    rbj_VecScale4(&step, &act->vel5C, a50_frameSeconds);
    rbj_VecAdd(&node->pos60, &node->pos60, &step);
    if (node->b128 & 0x18)
        act->vel5C.y = 0.0f;
    push = &node->push80;
    rbj_VecAdd(&node->pos60, &node->pos60, push);
    push->x = 0.0f;
    push->y = 0.0f;
    push->z = 0.0f;
    push->w = 1.0f;
    node->pos60.w = 1.0f;
}

/* 0x00169A50: walking movement. While work flag 0x20000 is set the fade timer runs down
   and 0x000EE6D0 gets the faded-in fraction (1.0 and the flag cleared when it runs out;
   the fade lasts 90 frame units). The yaw is wrapped into -pi..pi, the push vector is
   turned by it (except in state 8), and the vertical speed grows by 0.2 per frame unit
   while airborne (not in state 7); on the ground or in state 7 a rising speed is cleared.
   The speed is added to the push y. */
void rbj_Walk169A50(RbjNode *node, RbjBAct *act)
{
    RbjDWork *w = (RbjDWork *)act->work74;
    RbjMat4 m;
    float t, k;

    if (w->flags00 & 0x20000) {
        t = w->fade10 - a50_frameSeconds;
        w->fade10 = t;
        if (0.0f > t) {
            sub_000EE6D0(node, 1.0f);
            w->flags00 &= ~0x20000u;
        } else {
            k = 90.0f / a50_frameUnits * a50_frameSeconds;
            sub_000EE6D0(node, (k - t) / k);
        }
    }
    if (node->rot50.y > 3.14159274f)
        node->rot50.y = node->rot50.y - 6.28318548f;
    if (node->rot50.y < -3.14159274f)
        node->rot50.y = node->rot50.y + 6.28318548f;
    rbj_MatIdentity(&m);
    rbj_MatRotY(&m, &m, node->rot50.y);
    if (act->state50 != 8)
        rbj_VecTransform(&node->push80, &m, &node->push80);
    if (!(node->b128 & 0x18) && act->state50 != 7)
        w->fall18 = a50_frameUnits * 0.199999988f + w->fall18;
    else if (w->fall18 > 0.0f)
        w->fall18 = 0.0f;
    node->push80.y = node->push80.y + w->fall18;
}

/* 0x00168DD0: rising piece. Phase 0 sets node flag 8, work flags 0x40 (clearing 0x484),
   fE8 = 1.6, the rise vector (0, 0.1, 0, 1) with the start height, frees the old chain
   and goes on. Phase 1 accelerates the rise by 0.1 up to 2 into the push y, tips the x
   angle down by 10 deg per frame unit to at most -90 deg and, once on the ground or 10 units
   up (then work flag 0x1000), starts a 1.5 s timer and motion (2, 0). Phase 2 shrinks the
   node with the timer (scale timer * 2/3), keeps rising while flag 0x1000 is set, and
   when the timer runs out frees the motion and destroys the node. */
void rbj_Rise168DD0(RbjNode *node, RbjBAct *act)
{
    RbjEWork *w = (RbjEWork *)act->work74;
    RbjVec4 t;
    float s, r;

    switch (act->phase54) {
    case 0:
        node->flags10 |= 8;
        w->flags00 = (w->flags00 & 0xFFFFFB7Bu) | 0x40;
        node->fE8 = 1.60000002f;
        t.x = 0.0f;
        t.z = 0.0f;
        t.y = 0.100000001f;
        t.w = 1.0f;
        sub_000F5D40(&w->rise1C, &t);
        w->rise1C.x = node->pos60.y;
        if (w->chain5C != 0)
            sub_00033A70(w->chain5C);
        act->phase54++;
    case 1:
        if (2.0f > w->rise1C.y)
            w->rise1C.y = w->rise1C.y + 0.100000001f;
        node->push80.y = w->rise1C.y;
        r = node->rot50.x - a50_frameUnits * 0.174532935f;
        node->rot50.x = r;
        if (-1.57079637f > r)
            node->rot50.x = -1.57079637f;
        if (node->b128 & 0x18) {
            act->timer5C = 1.5f;
            act->phase54++;
        } else {
            if (!(node->pos60.y - w->rise1C.x > 10.0f))
                return;
            act->timer5C = 1.5f;
            act->phase54++;
            w->flags00 |= 0x1000;
        }
        w->motion3C = sub_00035D80(node, 2, 0);
        return;
    case 2:
        if (0.0f > act->timer5C) {
            sub_00033A40(w->motion3C);
            w->motion3C = 0;
            rbj_ObjDestroy(node);
            return;
        }
        s = act->timer5C * 0.666666687f;
        node->scale70.x = s;
        node->scale70.y = s;
        node->scale70.z = s;
        node->scale70.w = 1.0f;
        if (w->flags00 & 0x1000)
            node->push80.y = w->rise1C.y;
        return;
    }
}
