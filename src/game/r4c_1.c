/* Area r4c: effect object callbacks around 0x00190260-0x00191E66 (r4c_1). Names inferred. */
#include "r4c.h"

/* 0x00190260: start a falling effect: clear rotation and velocity, fall speed -20/fps. Stack args. */
void r4c_FxFallInit(R4cNode *o, R4cActor *a)
{
    R4cFxA *w = (R4cFxA *)a->work;
    o->rot50[0] = 0.0f;
    o->rot50[1] = 0.0f;
    o->rot50[2] = 0.0f;
    o->rot50[3] = 1.0f;
    w->v0C[1] = 0.0f;
    w->v0C[0] = 0.0f;
    w->v0C[2] = 0.0f;
    w->v0C[3] = 0.0f;
    w->v0C[1] = -20.0f / r4c_fps;
    o->flagsC |= 0x80;
    w->i04 = 0;
    w->i08 = 0;
    o->flags10 |= 0x44D;
}

/* 0x00190540: move and spin the effect; remove it after 60 units or on contact. Stack args. */
void r4c_FxFallUpdate(R4cNode *o, R4cActor *a)
{
    R4cFxA *w = (R4cFxA *)a->work;
    r4c_VecAdd(o->pos, o->pos, w->v0C);
    w->f1C += r4c_VecLenXZ(w->v0C);
    r4c_Spin(o, r4c_spin32C5E4);
    sub_000C56B0(o);
    if (w->f1C >= 60.0f || (o->flags128 & 0x1F)) {
        sub_0018F8D0(o);
        sub_000ED780(o);
    }
}

/* 0x001905B0: zero the three records at 0x004000B0. No inputs. */
void r4c_ClearRecs4000B0(void)
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++)
            r4c_recs4000B0[i].f[j] = 0;
        r4c_recs4000B0[i].f[0] = 0;
    }
}

/* 0x001905E0: message handler of the falling effect. Stack args (o a msg). */
int r4c_FxFallMsg(R4cNode *o, R4cActor *a, R4cMsg *msg)
{
    R4cMgr *mgr = sub_00100110();
    R4cFxA *w = (R4cFxA *)a->work;
    switch (msg->id) {
    case 1: case 2: case 3: case 5: case 32: case 34: case 35:
        if (mgr->h134 != -1) {
            sub_00048250(mgr->h134);
            mgr->h134 = -1;
        }
        /* fall through */
    case 12:
        sub_0018F8D0(o);
        sub_000ED780(o);
        return 0;
    case 14: case 40:
        if (mgr->h134 != -1) {
            sub_00048250(mgr->h134);
            mgr->h134 = -1;
        }
        sub_00189DA0(o, a, 3);
        return 1;
    case 26: case 27: case 28:
        sub_00189DA0(o, a, 4);
        return 0;
    case 42:
        r4c_VecScale(w->v0C, msg->v20, r4c_frameUnits);
        w->v0C[3] = 0.0f;
        sub_00189DA0(o, a, 5);
        return 0;
    }
    return 0;
}

/* 0x001908A0: release every object held by the 0x00400688, 0x00400390 and 0x00400120 records. No inputs. */
void r4c_ReleaseAllRecs(void)
{
    int i;
    for (i = 0; i < 16; i++)
        if (r4c_recs400688[i].obj)
            sub_000ED780(r4c_recs400688[i].obj);
    for (i = 0; i < 10; i++)
        if (r4c_recs400390[i].obj)
            sub_000ED780(r4c_recs400390[i].obj);
    for (i = 0; i < 26; i++)
        if (r4c_recs400120[i].obj)
            sub_000ED780(r4c_recs400120[i].obj);
}

/* 0x00190900: stop callback for kinds 0x18/0x19/0x1C/0x1D; returns 1 when stopped. Stack args. */
int r4c_FxStop(R4cNode *o, R4cActor *a)
{
    R4cFxC *w;
    int k;
    if (!(o->flagsC & 1))
        return 0;
    k = o->kind;
    if (k == 0x19) {
        w = (R4cFxC *)a->work;
        w->i04 = 0;
        w->i10 = 3;
        w->f0C = 0.0f;
    } else if (k == 0x18) {
        w = (R4cFxC *)a->work;
        w->i04 = 0;
        w->f0C = 0.0f;
        w->i10 = 3;
        w->s40 = 0;
    } else if (k == 0x1C || k == 0x1D) {
        w = (R4cFxC *)a->work;
        w->i04 = 2;
    } else {
        return 0;
    }
    w->i00 = 0;
    sub_00033B30(o);
    a->work = 0;
    sub_0001EB80(o);
    o->flagsC &= ~3u;
    o->flags10 |= 0xD;
    return 1;
}

/* 0x00190AF0: kill the effect when any of its three hit tests (3,8/12/13) on other fires. Stack args (o other).
   Calls 0x00190A00 with EDI=o. */
void r4c_FxCheckHit(R4cNode *o, void *other)
{
    int h8 = sub_000F5CD0(other, 3, 8);
    int h12 = sub_000F5CD0(other, 3, 12);
    int h13 = sub_000F5CD0(other, 3, 13);
    if (h8 || h12 || h13)
        r4c_FxKill(o);
}

/* 0x00190B40: kill o and the first state-3 record object within 12 units; returns 1 on a hit.
   regargs: p1=EAX. Calls 0x00190A00 with EDI. */
int r4c_FxCollide(R4cNode *o)
{
    R4cRec4C *r;
    R4cNode *p;
    float d[4];
    if (!o)
        return 0;
    for (r = r4c_recs400390; r < r4c_recs400390 + 10; r++) {
        p = r->obj;
        if (p && p != o && r->actor->state60 == 3) {
            r4c_VecSub(d, o->pos, p->pos);
            if (12.0f > r4c_VecLen(d)) {
                r4c_FxKill(o);
                r4c_FxKill(p);
                return 1;
            }
        }
    }
    return 0;
}

/* 0x001911F0: aim the effect at the player (or the nearer of two targets) at 110/fps. Stack args. */
void r4c_FxAim(R4cNode *o, R4cActor *a)
{
    R4cFxB *w = (R4cFxB *)a->work;
    float d1[4], d2[4];
    float l1;
    float *t1, *t2;
    if (sub_00101360() == 1) {
        r4c_VecSub(w->v14, sub_001012D0(0)->pos, o->pos);
    } else {
        t1 = sub_001012D0(1)->pos;
        t2 = sub_001012D0(2)->pos;
        r4c_VecSub(d1, t1, o->pos);
        r4c_VecSub(d2, t2, o->pos);
        l1 = r4c_VecLenXZ(d1);
        if (r4c_VecLenXZ(d2) > l1)
            sub_000F5D40(w->v14, d1);
        else
            sub_000F5D40(w->v14, d2);
    }
    o->flagsC &= ~0x20u;
    r4c_VecScale(w->v14, w->v14, 110.0f / r4c_fps / r4c_VecLenXZ(w->v14));
    w->v14[1] = 0.0f;
    w->v14[3] = 0.0f;
    w->f24 = 0.0f;
}

/* 0x001912F0: move the aimed effect; kill it after 80 units or on contact, else spin. Stack args. */
void r4c_FxAimUpdate(R4cNode *o, R4cActor *a)
{
    R4cFxB *w = (R4cFxB *)a->work;
    r4c_VecAdd(o->pos, o->pos, w->v14);
    w->f24 += r4c_VecLenXZ(w->v14);
    sub_000C56B0(o);
    if (w->f24 > 80.0f || (o->flags128 & 6))
        r4c_FxKill(o);
    else
        r4c_Spin(o, r4c_spin32C644);
}

/* 0x00191360: start a dropped effect: install the hit test, clear rotation and velocity. Stack args. */
void r4c_FxDropInit(R4cNode *o, R4cActor *a)
{
    R4cFxB *w = (R4cFxB *)a->work;
    o->flagsC |= 0x20;
    sub_0001C9E0(o, 0, r4c_FxCheckHit);
    o->flags10 = (o->flags10 & ~0x40u) | 0x200;
    o->rot50[0] = 0.0f;
    o->rot50[1] = 0.0f;
    o->rot50[2] = 0.0f;
    o->rot50[3] = 1.0f;
    w->v14[0] = 0.0f;
    w->v14[1] = 0.0f;
    w->v14[2] = 0.0f;
    w->v14[3] = 0.0f;
    w->f08 = 1.5f;
}

/* 0x001913E0: accelerate the effect upward (3/fps per frame, capped at 140/fps). Stack args. */
void r4c_FxRise(R4cNode *o, R4cActor *a)
{
    float *v = ((R4cFxB *)a->work)->v14;
    float step = 1.0f / r4c_fps;
    float lim = step * 140.0f;
    v[1] = step * 3.0f + v[1];
    if (v[1] > lim)
        v[1] = lim;
    o->pos[1] += v[1];
    if (o->flags128 & 0x1E)
        v[1] = 0.0f;
}

/* 0x00191490: move and accelerate the effect; kill it on contact, else spin. Stack args. */
void r4c_FxRiseUpdate(R4cNode *o, R4cActor *a)
{
    R4cFxB *w = (R4cFxB *)a->work;
    float lim;
    r4c_VecAdd(o->pos, o->pos, w->v14);
    w->v14[1] = 3.0f / r4c_fps + w->v14[1];
    lim = 140.0f / r4c_fps;
    if (w->v14[1] > lim)
        w->v14[1] = lim;
    if (!(o->flags128 & 0xA))
        r4c_Spin(o, r4c_spin32C644);
    else
        r4c_FxKill(o);
}

/* 0x00191520: move and spin the effect; kill it after 60 units or on contact. Stack args. */
void r4c_FxFlyUpdate(R4cNode *o, R4cActor *a)
{
    R4cFxB *w = (R4cFxB *)a->work;
    r4c_VecAdd(o->pos, o->pos, w->v14);
    w->f24 += r4c_VecLenXZ(w->v14);
    r4c_Spin(o, r4c_spin32C644);
    sub_000C56B0(o);
    if (w->f24 >= 60.0f || (o->flags128 & 0xA))
        r4c_FxKill(o);
    else
        r4c_Spin(o, r4c_spin32C644);
}

/* 0x00191B00: reset the sixteen records at 0x00400688. No inputs. */
void r4c_ResetRecs400688(void)
{
    R4cRec40 *r;
    int i;
    for (i = 0; i < 16; i++) {
        r = &r4c_recs400688[i];
        r->obj = 0;
        r->i4 = 0;
        r->i10 = 3;
        r->fC = 0.0f;
    }
}

/* 0x00191CA0: bind node o to a free 0x00400120 slot and install the stop callbacks; returns 1 on success. Stack args (o a x). */
int r4c_SlotBind(R4cNode *o, R4cActor *a, int x)
{
    R4cRec18 *r;
    int i;
    if (!o)
        return 0;
    i = 0;
    for (r = r4c_recs400120; r < r4c_recs400120 + 26; r++, i++)
        if (r->obj == 0)
            goto found;
    return 0;
found:
    if (i >= 26)
        return 0;
    r = &r4c_recs400120[i];
    r->obj = o;
    a->work = r;
    r->i4 = x;
    o->flagsC = (o->flagsC & ~0xE0u) | 3;
    o->flags10 = (o->flags10 & ~0x200u) | 0x5CD;
    a->p84 = r4c_g32C6E8;
    a->p88 = r4c_g32C6F0;
    a->fn78 = r4c_FxStop;
    a->fn7C = r4c_Fn1909C0;
    r->f8 = 0.0f;
    r->fC = 0.0f;
    r->f10 = 0.0f;
    r->f14 = 0.0f;
    return 1;
}

/* 0x00191D50: kill every 0x00400390 object inside radius and the angle range [a0, a1] around pos;
   returns 1 if one of them was not in state 5..7. Stack args (a0 a1 radius pos). Calls 0x00190A00 with EDI. */
int r4c_FxKillInArc(float a0, float a1, float radius, float *pos)
{
    float d[4];
    float ang;
    int hit = 0;
    int i, k;
    sub_00101220();
    for (i = 0; i < 10; i++) {
        R4cNode *o = r4c_recs400390[i].obj;
        if (!o)
            continue;
        r4c_VecSub(d, o->pos, pos);
        if (radius > r4c_VecLenXZ(d)) {
            ang = sub_001A3EC0(d[0], d[2]);
            if (0.0f > ang)
                ang += 6.2831855f;
            if (ang >= a0 && a1 >= ang) {
                k = r4c_recs400390[i].actor->state60;
                if (k != 5 && k != 6 && k != 7)
                    hit = 1;
                r4c_FxKill(o);
            }
        }
    }
    return hit;
}

/* 0x00191E20: message handler: message 5 switches the actor to state 3, 10/12/32/35 kill the effect. Stack args (o a msg). */
int r4c_FxMsg(R4cNode *o, R4cActor *a, R4cMsg *msg)
{
    switch (msg->id) {
    case 5:
        if (a->state60 != 3)
            sub_00189DA0(o, a, 3);
        return 0;
    case 10: case 12: case 32: case 35:
        r4c_FxKill(o);
        return 0;
    }
    return 0;
}
