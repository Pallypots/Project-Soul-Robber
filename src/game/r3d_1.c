/* Area r3d: game functions in 0x00130000..0x0015FFFF (r3d_1). Names inferred. */
#include "r3d.h"

/* 0x00139D50: restart obj's animation at a random frame: (rand % 4, +3 on an even roll) / rate. */
void r3d_RandomFrame139D50(R3cObj *obj)
{
    float t = (float)(sub_001C7EE1() % 4);
    R3cAnimInst *inst;

    if (sub_001C7EE1() % 2 < 1)
        t += 3.0f;
    inst = obj->pa30->inst14;
    sub_001AEDF0(inst, R3D_FTOI(t / inst->rateC4));
}

/* 0x00136E60: run condition 0x10 (freeing obj on result 1), reset the work vector at +0x160
   to (0, 0, 0, 1) and set obj flags 5 and act flags 0x70. */
void r3d_Reset136E60(R3cObj *obj, R3cObj *act)
{
    R3dWork160 *w;

    if (sub_001456E0(obj, act, 0x10, 0) == 1)
        sub_0001D4E0(obj);
    w = (R3dWork160 *)act->work278;
    w->v160[2] = 0.0f;
    w->v160[1] = 0.0f;
    w->v160[0] = 0.0f;
    w->v160[3] = 1.0f;
    obj->flags10 |= 5;
    act->flags4C |= 0x70;
}

/* 0x00147710: set the timer values of act's node key, skipping any given as -1.
   regargs: act=ECX key=EAX (a..d on the stack); calls 0x00113400 with (act, key) on the stack. */
R3dNode *r3d_SetNode147710(void *act, int key, float a, float b, float c, float d)
{
    R3dNode *n = sub_00113400(act, key);

    if (a != -1.0f)
        n->f10 = a;
    if (b != -1.0f)
        n->f14 = b;
    if (c != -1.0f)
        n->f18 = c;
    if (d != -1.0f)
        n->f1C = d;
    return n;
}

/* 0x0013E130: restart obj (0x0001D700), enter state 0x1B, rewind its animation and arm act->f74
   with a random wait of 10..18 frame units. */
void r3d_Restart13E130(R3cObj *obj, R3cObj *act)
{
    sub_0001D700(obj);
    obj->flags10 &= ~0x20u;
    act->flags4C &= 0xFFFFFF87;
    sub_00113090(obj, act, 0x1B);
    sub_001AEDD0(obj->pa30->inst14, 0);
    act->f74 = ((float)(sub_001C7EE1() % 9) + 10.0f) / r3c_frameUnits * r3c_frameSeconds;
}

/* 0x0013E1A0: clear obj flag 0x20, enter state 0x1C and set act's node 3 to a swing of
   +-1 degree per frame unit between +-15 degrees. */
void r3d_Swing13E1A0(R3cObj *obj, R3cObj *act)
{
    R3dNode *n;
    float v;

    obj->flags10 &= ~0x20u;
    act->flags4C &= 0xFFFFFF87;
    sub_00113090(obj, act, 0x1C);
    n = sub_00113430(act, 3);
    v = r3c_frameUnits * 0.017453292f;
    n->f10 = v;
    n->f14 = 0.0f - v;
    n->f18 = 0.2617994f;
    n->f1C = -0.2617994f;
}

/* 0x001474D0: condition: act's target is live and matches selector rec[0]
   (1: type 1 below kind 3, 2: type 13, 3: type 2 kind 6). First argument unused. */
int r3d_TargetIs1474D0(void *unused, R3cObj *act, const int32_t *rec)
{
    R3cObj *t = act->p104;
    int k;

    if (!t || !(t->flags0C & 1))
        return 0;
    k = rec[0];
    if (k == 1 && act->iF8 == 1 && t->type04 == 1 && t->i08 < 3)
        return 1;
    if (k == 2 && act->iF8 == 1 && t->type04 == 13)
        return 1;
    if (k == 3 && act->iF8 == 1 && t->type04 == 2 && t->i08 == 6)
        return 1;
    return 0;
}

/* 0x00155B70: as 0x001474D0 but selector 3 wants type 2 kind 7. */
int r3d_TargetIs155B70(void *unused, R3cObj *act, const int32_t *rec)
{
    R3cObj *t = act->p104;
    int k;

    if (!t || !(t->flags0C & 1))
        return 0;
    k = rec[0];
    if (k == 1 && act->iF8 == 1 && t->type04 == 1 && t->i08 < 3)
        return 1;
    if (k == 2 && act->iF8 == 1 && t->type04 == 13)
        return 1;
    if (k == 3 && act->iF8 == 1 && t->type04 == 2 && t->i08 == 7)
        return 1;
    return 0;
}

/* 0x00157810: run condition 0x16, reset the work motion (vector (0, 0, 0, 1), speed 0.005 per
   frame unit), set obj flag 0x20 and clear act flags 0x70 and work flag 4. */
void r3d_Reset157810(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    sub_001456E0(obj, act, 0x16, 0);
    w->f2C = 0.0f;
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f30 = 1.0f;
    w->f10 = 0.0f;
    w->f0C = r3c_frameUnits * 0.005f;
    obj->flags10 |= 0x20;
    act->flags4C &= ~0x70u;
    w->flags40 &= ~4u;
}

/* 0x00159960: run condition 0x46, reset the work motion like 0x00157810, clear obj flag 0x20
   (+0x0C) and act flags 0x70 and set work flag 2. */
void r3d_Reset159960(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    sub_001456E0(obj, act, 0x46, 0);
    w->f2C = 0.0f;
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f30 = 1.0f;
    w->f10 = 0.0f;
    w->f0C = r3c_frameUnits * 0.005f;
    obj->flags0C &= ~0x20u;
    act->flags4C &= ~0x70u;
    w->flags00 |= 2;
}

/* 0x0013B9A0: clear obj flags, store obj's position in act+0x88, fire effect 0x84 at obj's
   matrix origin, start animation 7 and enter state 0x45 (act word +0x58 = 2). */
void r3d_Hit13B9A0(R3cObj *obj, R3cObj *act)
{
    obj->flags10 &= 0xFFFFFFEB;
    obj->flags0C &= ~0x20u;
    act->flags4C &= ~8u;
    sub_000F5D40(((R3dAct *)act)->v88, obj->pos60);
    sub_000494D0(0x84, obj->m20 + 12, 0);
    sub_00036750(obj, 7);
    sub_00113090(obj, act, 0x45);
    obj->flags10 |= 4;
    ((R3dAct *)act)->i58 = 2;
}

/* 0x001467B0: run condition 7, start the work motion at 0.003 per frame unit, set obj flags 5,
   clear act flags 0x1000070, start animation 0 and fire effect 0x131 at obj. */
void r3d_Start1467B0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    sub_001456E0(obj, act, 7, 0);
    b4c_MotionSet156180(w, 0.0f, 0.0f, 0.0f, r3c_frameUnits * 0.003f);
    obj->flags10 |= 5;
    act->flags4C &= 0xFEFFFF8F;
    sub_00036750(obj, 0);
    sub_000494D0(0x131, obj->pos60, 0);
}

/* 0x00159650: run condition 0x13, reset the work motion like 0x00157810, set obj flag 0x20,
   clear act flags 0x70 and add one exclamation point. */
void r3d_Reset159650(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    sub_001456E0(obj, act, 0x13, 0);
    w->f2C = 0.0f;
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f30 = 1.0f;
    w->f10 = 0.0f;
    w->f0C = r3c_frameUnits * 0.005f;
    obj->flags10 |= 0x20;
    act->flags4C &= ~0x70u;
    Grade_AddExclamations(1);
}

/* 0x0013F140: phase 0: after 20 frame units of act->f5C set obj flag 0x20, clear flags 6 and
   go to phase 1; phase 1: at the end of the animation enter state 0xC. */
void r3d_Phase13F140(R3cObj *obj, R3cObj *act)
{
    R3dAct *a = (R3dAct *)act;

    switch (a->i58) {
    case 0:
        if (act->f5C >= 20.0f / r3c_frameUnits * r3c_frameSeconds) {
            obj->flags0C |= 0x20;
            obj->flags10 &= ~6u;
            a->i58++;
        }
        break;
    case 1:
        if (sub_000833E0(obj->anim30))
            sub_00113040(obj, act, 0xC);
        break;
    }
}

/* 0x00146BA0: run condition 0x40, start the work motion at 0.003 per frame unit with limits
   (-10, 10 per second) and clear act flags 0x70. */
void r3d_Start146BA0(R3cObj *obj, R3cObj *act)
{
    R3cWork *w = act->work278;

    sub_001456E0(obj, act, 0x40, 0);
    b4c_MotionSet156180(w, 0.0f, 0.0f, 0.0f, r3c_frameUnits * 0.003f);
    sub_001561D0(w, -10.0f, r3c_frameSeconds * 10.0f);
    act->flags4C &= ~0x70u;
}

/* 0x00138310: set obj flag 0x20, clear act flag 0x10, set act's node 9 to a swing of
   +-2 degrees per frame unit between +-160 degrees and enter state 0xC/0xD by act flag
   bit 0x10000. */
void r3d_Swing138310(R3cObj *obj, R3cObj *act)
{
    R3dNode *n;
    float v;

    obj->flags10 |= 0x20;
    act->flags4C &= ~0x10u;
    n = sub_00113430(act, 9);
    v = r3c_frameUnits * 0.034906585f;
    n->f10 = v;
    n->f14 = 0.0f - v;
    n->f18 = -2.792527f;
    n->f1C = 2.792527f;
    sub_00113090(obj, act, (act->b22 & 1) + 0xC);
}

/* 0x0013E5C0: enter state 0xA/0xB by act flag bit 0x10000, set obj flag 0x20 and act flag 0x10
   and set act's node 3 to a swing of +-1.5 degrees per frame unit between +-10 degrees. */
void r3d_Swing13E5C0(R3cObj *obj, R3cObj *act)
{
    R3dNode *n;
    float v;

    sub_00113090(obj, act, (act->b22 & 1) + 0xA);
    obj->flags10 |= 0x20;
    act->flags4C |= 0x10;
    n = sub_00113430(act, 3);
    v = r3c_frameUnits * 0.02617994f;
    n->f10 = v;
    n->f14 = 0.0f - v;
    n->f18 = 0.17453294f;
    n->f1C = -0.17453294f;
}

/* 0x00142990: clear act flag 0x10, start the work clamp at +0x14 (20), enter state 0x21/0x23
   by act flag bit 0, and fill act's node 2 with the matching animation keys. */
void r3d_Start142990(R3cObj *obj, R3cObj *act)
{
    R3dNode *n;
    int k;

    act->flags4C &= ~0x10u;
    sub_00113CB0(&act->work278->i14, 20.0f, 0);
    k = (((R3dAct *)act)->flags20 & 1) << 1;
    sub_00113090(obj, act, k + 0x21);
    n = sub_00113430(act, 2);
    n->i10 = k;
    n->i14 = 2;
    n->i18 = 0xC3;
    if (act->b20 & 1) {
        n->i14 = 0x30002;
        n->i18 = 0xC400C3;
        n->i1C = 2;
    }
}

/* 0x0013EE90: (act flag bit 0x10000 required) enter state 0x29, set obj flag 0x20 and act flag
   0x10 and set act's node 3 to a swing of +-2 degrees per frame unit between +-10 degrees. */
void r3d_Swing13EE90(R3cObj *obj, R3cObj *act)
{
    R3dNode *n;
    float v;

    if (!(act->b22 & 1))
        for (;;)
            ;
    sub_00113090(obj, act, 0x29);
    obj->flags10 |= 0x20;
    act->flags4C |= 0x10;
    n = sub_00113430(act, 3);
    v = r3c_frameUnits * 0.034906585f;
    n->f10 = v;
    n->f14 = 0.0f - v;
    n->f18 = 0.17453294f;
    n->f1C = -0.17453294f;
}

/* 0x0013EF10: (act flag bit 0x10000 required) enter state 0x2A, set obj flag 0x20 and act flag
   0x10 and set act's node 3 to a swing of +-1 degree per frame unit between +-10 degrees. */
void r3d_Swing13EF10(R3cObj *obj, R3cObj *act)
{
    R3dNode *n;
    float v;

    if (!(act->b22 & 1))
        for (;;)
            ;
    sub_00113090(obj, act, 0x2A);
    obj->flags10 |= 0x20;
    act->flags4C |= 0x10;
    n = sub_00113430(act, 3);
    v = r3c_frameUnits * 0.017453292f;
    n->f10 = v;
    n->f14 = 0.0f - v;
    n->f18 = 0.17453294f;
    n->f1C = -0.17453294f;
}

/* 0x001471F0: count down obj's fade value +0x70 by 1/rec->f10 (not below 0) into +0x70..+0x78
   with +0x7C = 1; at 0 set work flag 0x20, mark rec done (1) and drop it, else mark it 2. */
void r3d_Fade1471F0(R3cObj *obj, R3cObj *act, R3dFade *rec)
{
    R3dWork *w;
    float v = obj->f70 - 1.0f / rec->f10;

    w = (R3dWork *)act->work278;
    if (0.0f > v)
        v = 0.0f;
    obj->f78 = v;
    obj->f74 = v;
    obj->f70 = v;
    obj->f7C = 1.0f;
    if (0.0f < v) {
        if (rec->state)
            rec->state = 2;
        return;
    }
    w->flags50 |= 0x20;
    if (rec->state)
        rec->state = 1;
    sub_00113370(act, rec);
}

/* 0x00139540: turn obj toward act's heading +0xFC (offset by pi) when it leaves the window
   (f1C, f18), by at most the limits (f14, f10), and take the turn off act's heading. */
void r3d_Turn139540(R3cObj *obj, R3cObj *act, const R3dLimits *lim)
{
    float a = act->fFC;

    if (a > 0.0f)
        a -= 3.1415927f;
    else
        a += 3.1415927f;
    if (lim->f1C > a || a > lim->f18) {
        if (a > lim->f10)
            a = lim->f10;
        if (lim->f14 > a)
            a = lim->f14;
        obj->f54 += a;
        act->fFC -= a;
    }
}

/* 0x001569B0: run condition 5 and reset the work motion (vector (0, 0, 3 per second, 1),
   speed 0.005 per frame unit), clearing act flags 0x70. */
void r3d_Reset1569B0(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    sub_001456E0(obj, act, 5, 0);
    w->f2C = 0.0f - r3c_frameSeconds * -3.0f;
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f30 = 1.0f;
    w->f10 = 0.0f;
    w->f0C = r3c_frameUnits * 0.005f;
    act->flags4C &= ~0x70u;
}

/* 0x00138AC0: phase 0: at the end of the animation run 0x00113190, give act's node 1 the
   timers (0.25, 0.25, 0) and go to phase 1; phase 1: once node 1 is gone enter state 0x1C. */
void r3d_Phase138AC0(R3cObj *obj, R3cObj *act)
{
    R3dAct *a = (R3dAct *)act;
    R3dNode *n;

    switch (a->i58) {
    case 0:
        if (sub_000833E0(obj->anim30)) {
            sub_00113190(obj, act, 0);
            n = sub_00113430(act, 1);
            n->f10 = 0.25f;
            n->f14 = 0.25f;
            n->i18 = 0;
            a->i58++;
        }
        break;
    case 1:
        if (!sub_001133E0(act, 1))
            sub_00113040(obj, act, 0x1C);
        break;
    }
}

/* 0x00146C20: run condition 0x37, start the work motion (40 and -50 per second, speed 0.003
   per frame unit), clear act flags 0x70, set work flags 7 and count the work step +0x58. */
void r3d_Start146C20(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    sub_001456E0(obj, act, 0x37, 0);
    b4c_MotionSet156180(w, r3c_frameSeconds * 40.0f, r3c_frameSeconds * -50.0f, 0.0f,
                        r3c_frameUnits * 0.003f);
    act->flags4C &= ~0x70u;
    w->flags00 |= 7;
    w->i58++;
}

/* 0x00156930: run condition 0, reset the work motion like 0x00157810 with +0x50 = 300, set
   obj flag 0x20, act flags 0x70 and work flag 0x200. */
void r3d_Reset156930(R3cObj *obj, R3cObj *act)
{
    R3dWork *w = (R3dWork *)act->work278;

    sub_001456E0(obj, act, 0, 0);
    w->f0C = r3c_frameUnits * 0.005f;
    w->f2C = 0.0f;
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f30 = 1.0f;
    w->f10 = 0.0f;
    w->f50 = 300.0f;
    obj->flags10 |= 0x20;
    act->flags4C |= 0x70;
    w->flags40 |= 0x200;
}
