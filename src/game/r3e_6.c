/* Area r3e: game functions in 0x00140000..0x0015FFFF (r3e_6). Names inferred. */
#include "r3e.h"

/* 0x00145730: nonzero when time t falls in frame n, i.e. n * frameSeconds lies in
   [t, t + frameSeconds); hangs for n == 0. */
int r3e_InFrame145730(float t, unsigned int n)
{
    float ft;

    if (n == 0)
        for (;;) ;
    ft = (float)n * r3e_frameSeconds;
    if (ft >= t && t + r3e_frameSeconds > ft)
        return 1;
    return 0;
}

/* 0x00145590: set up the enemy (0x001453B0) and start it in state 1 with variant kind & 1
   (kinds 2 and 3 also set work flag 8), enabling its effect; returns 0 for unknown kinds.
   calls 0x001453B0 with ESI=obj EDI=act. */
int r3e_Start145590(R3eObj *obj, R3eObj *act, int kind)
{
    int b;

    sub_001453B0(obj, act);
    switch (kind) {
    case 0:
        b = 0;
        break;
    case 1:
        b = 1;
        break;
    case 2:
        act->work278->i04 |= 8;
        b = 0;
        break;
    case 3:
        act->work278->i04 |= 8;
        b = 1;
        break;
    default:
        return 0;
    }
    sub_001130F0(obj, act, b);
    if (act->work278->p20 != 0)
        sub_00189DE0(act->work278->p20, b);
    sub_00113040(obj, act, 1);
    return 1;
}

/* 0x00142A10: clear act flag 0x10, clamp the work block at +0x14 to 20, play animation 0x22 (0x24
   with act flag 1), renew node 3 and set node 2 to mode (1 or 3, 2, 0xC3), widened with act
   flag 1. */
void r3e_Enter142A10(R3eObj *obj, R3eObj *act)
{
    int k;
    R3eNode *n;

    act->flags4C &= ~0x10u;
    sub_00113CB0(act->work278->blk14, 20.0f, 0);
    k = (act->flags20 & 1) * 2;
    sub_00113090(obj, act, k + 0x22);
    sub_00113430(act, 3);
    n = sub_00113430(act, 2);
    n->i10 = k + 1;
    n->i14 = 2;
    n->i18 = 0xC3;
    if (act->flags20 & 1) {
        n->i14 = 0x30002;
        n->i18 = 0xC400C3;
        n->i1C = 2;
    }
}

/* 0x00155830: shrink obj's scale by 1/node->f10 per call (down to 0.01) on all three axes; at the
   minimum set work flag 0x20, mark the node request done (1) and free it, else mark it busy (2). */
void r3e_Shrink155830(R3eScaled *obj, R3eObj *act, R3eNode *node)
{
    R3eWork *w;
    float s = obj->s70[0] - 1.0f / node->f10;

    w = act->work278;
    if (s < 0.01f)
        s = 0.01f;
    obj->s70[2] = s;
    obj->s70[1] = s;
    obj->s70[0] = s;
    obj->s70[3] = 1.0f;
    if (s <= 0.01f) {
        w->flags40 |= 0x20;
        if (node->i00 != 0)
            node->i00 = 1;
        sub_00113370(act, node);
    } else if (node->i00 != 0) {
        node->i00 = 2;
    }
}

/* 0x0015A190: wait for the node (a countdown in node->f10 when node->f14 is 2, else animation
   time node->f10), then clear act's flag request (0x00113190), run 0x00155D10 with mode
   node->f14, mark the node request done and free it. */
void r3e_Wait15A190(R3eObj *obj, R3eObj *act, R3eNode *node)
{
    if (node->f14 != 2.0f) {
        if (!sub_00145780(obj, node->f10))
            return;
    } else {
        node->f10 -= r3e_frameSeconds;
        if (node->f10 > 0.0f)
            return;
    }
    sub_00113190(obj, act, 0);
    sub_00155D10(act, R3E_FTOI(node->f14));
    if (node->i00 != 0)
        node->i00 = 1;
    sub_00113370(act, node);
}

/* 0x001426B0: knock obj down: clear its flag 0x20, set flags 0xD, clear act flags 0x01000078,
   start the hit sequence 2 from table 0x0031DBFC (kind 0x10) or 0x0031DBD4, free its resources,
   prune act's list, reset to pose 5 (7 with act flag 1), play effect 0xCE at the matrix origin
   and hide the attached effect. */
void r3e_Down1426B0(R3eObj *obj, R3eObj *act)
{
    void *fx;

    obj->flags0C &= ~0x20u;
    obj->flags10 |= 0xD;
    act->flags4C &= 0xFEFFFF87;
    sub_0013A120(obj, 2, obj->i08 == 0x10 ? b3b_tbl31DBFC : b3b_tbl31DBD4);
    sub_0001D190(obj);
    sub_001134B0(act);
    sub_00035D80(obj, (act->flags20 & 1) * 2 | 5, 1);
    sub_000494D0(0xCE, obj->m20 + 12, 0);
    fx = act->work278->p20;
    if (fx != 0)
        sub_0001D7A0(fx);
}

/* 0x001434E0: once 0x0013A900 allows it, step 0 plays animation 0x49, runs 0x00142330 when an
   effect is attached, clears the work +0x18 value and jumps to step 2; step 2 clears obj flag 4,
   sets the work sign bit and enters state 0x11. */
void r3e_Step1434E0(R3eObj *obj, R3eObj *act)
{
    if (!sub_0013A900(obj, act))
        return;
    switch (act->i58) {
    case 0:
        sub_00113090(obj, act, 0x49);
        if (act->work278->p20 != 0)
            sub_00142330(obj, act);
        act->work278->f18 = 0.0f;
        act->i58 = 2;
        break;
    case 2:
        obj->flags10 &= ~4u;
        act->work278->i04 |= 0x80000000;
        sub_00113040(obj, act, 0x11);
        break;
    }
}

/* 0x0013B500: knock obj down (as 0x001426B0) with hit table 0x0031CE1C, attach mode 8 (act flag 1)
   or 2, play effect 0xA6 at the matrix origin and detach node +0x28 in act mode 0x22. */
void r3e_Down13B500(R3eObj *obj, R3eObj *act)
{
    obj->flags0C &= ~0x60u;
    obj->flags10 = (obj->flags10 & ~0x20u) | 0xD;
    act->flags4C &= 0xFEFFFF87;
    sub_0013A120(obj, 2, b3b_tbl31CE1C);
    sub_0001D190(obj);
    sub_001134B0(act);
    sub_00036750(obj, (act->flags20 & 1) ? 8 : 2);
    sub_000494D0(0xA6, obj->m20 + 12, 0);
    if (act->i54 == 0x22)
        sub_001B2080(obj->p28);
}

/* 0x0013D2F0: release act's three held references (hanging unless each release returns 1), stop
   its sound, free obj's +0x13C resource and act's +0x70 handle; returns 1. */
int r3e_Release13D2F0(R3eObj *obj, R3eObj *act)
{
    void **ref = act->work278->refs34;
    int i;

    for (i = 0; i < 3; i++, ref++) {
        if (*ref != 0) {
            if (sub_0018E640(*ref, obj) != 1)
                for (;;) ;
            *ref = 0;
        }
    }
    if (act->i6C >= 0) {
        sub_00048250(act->i6C);
        act->i6C = -1;
    }
    sub_0005BE30(obj->i13C);
    if (act->p70 != 0) {
        sub_00033A70(act->p70);
        act->p70 = 0;
    }
    return 1;
}

/* 0x001597D0: run condition 0x40, set up act's movement block (rate 0.005 per frame unit, -10, a
   10-frame timer, zero vector with w 1) and clear act flags 0x70. */
void r3e_Move1597D0(R3eObj *obj, R3eObj *act)
{
    R3eWorkM *w = (R3eWorkM *)act->work278;

    sub_001456E0(obj, act, 0x40, 0);
    w->f2C = 0.0f;
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f10 = 0.0f;
    w->f0C = r3e_frameUnits * 0.005f;
    w->f30 = 1.0f;
    w->f04 = -10.0f;
    w->f08 = r3e_frameSeconds * 10.0f;
    act->flags4C &= ~0x70u;
}
