/* Area rbk: Jack's movement (0x000D2D90). Names inferred. */
#include "rbk.h"

/* 0x000D2D90: move Jack one frame. Unless the action is 0: the position before the move is
   kept (+0x1A8, y 15 lower), the vertical move is root motion y plus the fall speed (both
   per frame unit) and the fall speed grows by 0.04 per frame unit; both are capped at 10.
   They are zeroed with flag 0x800000 or in stage 0x11 mode 4. Then turning (0x000D0EA0) and
   walking (0x000D0F50) run, the model is marked moved (0xE0), moved by the frame's
   movement and linked (0x000D1180); its two push records get the move back (size 6, kind
   2; kind 3 with the vertical move added). The model takes Jack's facing and the frame's
   movement is cleared. Called with stack arg (j). */
void rbk_JackMove0D2D90(RbkJack *j)
{
    RbjVec4 zero;
    RbkPushA *pa;
    RbkPushB *pb;
    float fu, dy;

    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    zero.w = 1.0f;
    if (j->stateD8 == 0)
        return;
    sub_000F5D40(&j->prev1A8, &j->modelFD8->pos60);
    j->prev1A8.y = j->modelFD8->pos60.y - 15.0f;
    fu = a50_frameUnits;
    dy = j->moveY114 * fu + j->f148 * fu;
    j->fallSpeed14C = dy;
    j->f148 = a50_frameUnits * 0.04f + j->f148;
    if (dy > 10.0f) {
        j->fallSpeed14C = 10.0f;
        j->f148 = 10.0f;
    }
    if ((j->flags150 & 0x800000) || (rbk_g413164 == 0x11 && j->modeD4 == 4)) {
        j->fallSpeed14C = 0.0f;
        j->f148 = 0.0f;
    }
    sub_000D0EA0(j);
    sub_000D0F50(j);
    j->modelFD8->flags0C |= 0xE0;
    rbj_VecAdd(&j->modelFD8->pos60, &j->modelFD8->pos60, &j->move000);
    sub_000D1180(j);
    pa = &((RbkModelPush *)j->modelFD8)->pushD8;
    rbj_VecSub(&pa->v00, &j->prev1A8, &j->modelFD8->pos60);
    pa->size10 = 6.0f;
    pa->kind14 = 2;
    pb = &((RbkModelPush *)j->modelFD8)->pushF8;
    rbj_VecSub(&pb->v00, &j->prev1A8, &j->modelFD8->pos60);
    sub_000F5D40(&pb->v10, &pb->v00);
    pb->v00.y = j->fallSpeed14C + pb->v00.y;
    pb->kind20 = 3;
    j->modelFD8->rot50.y = j->yaw108;
    sub_000F5D40(&j->move000, &zero);
}

