/* Area r4c: effect kill and slot helpers 0x00190A00, 0x00192320, 0x00192630 (r4c_2). Names inferred. */
#include "r4c.h"

/* 0x00190A00: kill effect o: spawn the burst (kinds 0x18/0x19), play it at o's position, free o.
   regargs: p1=EDI. For other kinds the burst handle and flag are left unset as in the original. */
void r4c_FxKill(R4cNode *o)
{
    void *fx;
    int flag;
    void *h;
    float col[4];
    float m[16];
    float out[8];
    if (!o)
        return;
    sub_000F3FD0(o);
    if (o->kind == 0x19) {
        fx = sub_000ED630(5, 0x1D, o->pos, 0, 0);
        flag = 0;
    } else if (o->kind == 0x18) {
        fx = sub_000ED630(5, 0x1C, o->pos, 0, 1);
        flag = 0;
    }
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    h = sub_00035DD0(fx, o->i130, flag, 3);
    sub_00033880(h, m);
    r4c_Model34E00(h, o->pos, out, col);
    if (fx) {
        sub_00189DA0(fx, (void *)sub_0001D960(fx, 7), 1);
        sub_000494D0(0x78, ((R4cNode *)fx)->pos, 1);
    }
    sub_000ED780(o);
}

/* 0x00192320: re-parent the node of slot idx (0..3) under part `part` of the current scene. Stack args (idx part). */
void r4c_SlotAttach(int idx, int part)
{
    void *scene = sub_000F3F80()->p8C;
    R4cSlot *r;
    if (idx < 0 || idx >= 4)
        return;
    r = &r4c_recs400A88[idx];
    sub_001B2080(r->obj->p20);
    sub_001B2020(sub_0001D0F0(scene, part), r->obj->p20);
}

/* 0x00192630: scale the node of slot idx (0..3) and its attachment vectors by s.
   regargs: p1=EAX (idx); s on the stack. */
void r4c_SlotScale(int idx, float s)
{
    R4cSlot *r;
    R4cNode *o;
    if (idx < 0 || idx >= 4)
        return;
    r = &r4c_recs400A88[idx];
    o = r->obj;
    o->scale70[3] = 1.0f;
    o->scale70[2] = s;
    o->scale70[1] = s;
    o->scale70[0] = s;
    r->f14 = s * 0.215f;
    o->fB0 = s * 2.0f;
    o->fB4 = s * -3.5f;
    sub_000F5D40(o->vA0, r4c_v27AF9C);
    r4c_VecScale(o->vA0, o->vA0, s);
    o->fE8 = s * 1.5f;
    sub_000F5D40(o->vD8, r4c_v27AFB0);
    r4c_VecScale(o->vD8, o->vD8, s);
    sub_000F5D40(o->vF8, r4c_v27AFC0);
    sub_000F5D40(o->v108, r4c_v27AFD0);
    r4c_VecScale(o->vF8, o->vF8, s);
    r4c_VecScale(o->v108, o->v108, s);
}
