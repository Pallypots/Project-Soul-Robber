/* Area rbi: Jack's movement (0x000D0000..0x000D5FFF). Names inferred. */
#include "rbi.h"

/* 0x000D05B0: grow or shrink the carried item (child node 3 of Jack's model) while Jack is
   in mode 1 and visible. During the hold animations 0x310, 0x313 and 0x316..0x31A it grows by
   0.05 per frame unit up to 1.0 (rebuilt through 0x000385D0); otherwise it shrinks by the same
   rate, keeping its position, until it reaches 0.1, when it is hidden (scale 0.05) and its
   animation reset. A frozen node (flag 0x10000) is left alone. The node matrix rows are
   scaled by the node's scale. The original also zero-fills the position vector first (a
   dead store, omitted). */
void rbi_HeldScale0D05B0(RbiJack *p)
{
    RbiVec4 pos;
    RbiVec4 m[4];
    RbiNode *n;
    RbiVec4 *mtx;
    int a;

    if (p->i1B8 != 1 || p->flags150 < 0)
        return;
    n = rbi_Child1D290(p->nodeFD8, 3);
    mtx = n->mtx20;
    a = p->anim12C;
    if (a == 0x310 || a == 0x313 || a == 0x316 || a == 0x317 || a == 0x318 || a == 0x319
        || a == 0x31A) {
        if (n->flags0C & 0x10000)
            return;
        if (1.0f > n->scale70.x) {
            n->scale70.x += a50_frameUnits * 0.05f;
            n->scale70.y += a50_frameUnits * 0.05f;
            n->scale70.z += a50_frameUnits * 0.05f;
        } else {
            n->scale70.z = 1.0f;
            n->scale70.y = 1.0f;
            n->scale70.x = 1.0f;
        }
        rbi_MatLoad385D0(m, mtx);
        rbi_VecScale(&m[0], &m[0], n->scale70.x);
        rbi_VecScale(&m[1], &m[1], n->scale70.y);
        rbi_VecScale(&m[2], &m[2], n->scale70.z);
        rbi_MatCopy(mtx, m);
        return;
    }
    if (n->flags0C & 0x10000)
        return;
    if (n->scale70.x > 0.1) {
        n->scale70.x -= a50_frameUnits * 0.05f;
        n->scale70.y -= a50_frameUnits * 0.05f;
        n->scale70.z -= a50_frameUnits * 0.05f;
        rbi_MatCopy(m, mtx);
        rbi_VecCopy(&pos, &m[3]);
        rbi_VecScale(&m[0], &m[0], n->scale70.x);
        rbi_VecScale(&m[1], &m[1], n->scale70.y);
        rbi_VecScale(&m[2], &m[2], n->scale70.z);
        rbi_VecCopy(&m[3], &pos);
        rbi_MatCopy(mtx, m);
    } else {
        n->scale70.z = 0.05f;
        n->scale70.y = 0.05f;
        n->scale70.x = 0.05f;
        rbi_ChildHide1D4B0(p->nodeFD8, 3);
        rbi_SetChildAnimD0560(p, 0, 3);
    }
}

/* 0x000D12E0: push a sphere (centre pos, radius body->radE8) out of the scenery. Unless
   collision is off (flag 0x1000000 of 0x00420010), up to two contacts from 0x0001B450 are
   resolved: the offset from the contact point (+0x40) is measured on the ground plane, its
   upward part dropped, normalised and pos moved along it by the overlap. Then the body is
   placed at pos minus its centre offset. Returns 1 when something was hit. */
int rbi_PushOut0D12E0(RbiBody *body, RbiVec4 *pos, const int32_t *mask)
{
    RbiVec4 d = { 0.0f, 0.0f, 0.0f, 1.0f };
    RbiVec4 n = { 0.0f, 0.0f, 0.0f, 1.0f };
    float r = body->radE8;
    int hits = 0;
    float len;
    uint8_t *hit;

    if (aa0_flags420010 & 0x1000000) {
        rbi_VecSub(&body->pos60, pos, &body->ofsD8);
        return 0;
    }
    hit = rbi_Collide1B450(pos, r, mask, body->colF0);
    while (hit) {
        rbi_VecSub(&d, pos, (const RbiVec4 *)(hit + 0x40));
        d.y = 0.0f;
        len = rbi_VecLen82D70(&d);
        rbi_VecSub(&n, pos, (const RbiVec4 *)(hit + 0x40));
        if (n.y > 0.0f)
            n.y = 0.0f;
        rbi_VecNorm(&n, &n);
        rbi_VecScale(&n, &n, len <= r ? r - len : len - r);
        rbi_VecAdd(pos, pos, &n);
        if (++hits >= 2)
            break;
        hit = rbi_Collide1B450(pos, r, mask, body->colF0);
    }
    rbi_VecSub(&body->pos60, pos, &body->ofsD8);
    return hits != 0;
}
