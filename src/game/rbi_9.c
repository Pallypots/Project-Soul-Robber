/* Area rbi: grabbed / knocked-back state entries (rbi_9). Names inferred.
   Kept apart from the callee 0x001456E0. */
#include "rbi.h"

/* 0x00153C20: enter state 0x48 (knocked back): clear actor flags 0x70 and object flag 0x20,
   set work flags 3 and clear 0x80000; turn the body to face against the velocity (flat,
   upright basis), slide back at the speed of the velocity, remember Jack's position, set
   object flag 4 and start emitter 0xA (rate 1/12). */
void rbi_KnockBack153C20(RbiKbObj *obj, RbiKbAct *act)
{
    RbiKbWork153 *w = (RbiKbWork153 *)act->work278;
    RbiBasis *b;
    RbiVec4 v;
    RbhEmit *e;

    rbi_Enter1456E0(obj, act, 0x48, 0);
    act->flags4C &= ~0x70u;
    obj->flags0C &= ~0x20u;
    w->flags00 |= 3;
    w->flags50 &= 0xFFF7FFFFu;
    rbi_VecScale(&v, &act->vel88, -1.0f);
    v.y = 0.0f;
    rbi_VecNorm(&v, &v);
    rbi_VecScale(&obj->basis20->z20, &v, -1.0f);
    obj->basis20->y10.w = 0.0f;
    obj->basis20->y10.z = 0.0f;
    obj->basis20->y10.x = 0.0f;
    obj->basis20->y10.y = 1.0f;
    b = obj->basis20;
    rbi_VecCross(&b->x00, &b->y10, &b->z20);
    rbi_VecNorm(&v, &act->vel88);
    rbi_Motion156180(w, -(a50_frameUnits * rbi_VecDot(&v, &act->vel88)), 0.0f, 0.0f,
                     a50_frameUnits * 0.003f);
    rbi_VecCopy(&w->target40, (const RbiVec4 *)((uint8_t *)g_playerObj + 0x60));
    obj->flags10 |= 4;
    e = rbi_Emit113400(act, 0xA);
    e->f10 = 0.0833333358f;
    e->f14 = 0.0f;
    e->f18 = 0.0f;
    e->f1C = 0.0f;
}

/* 0x00159BF0: enter state 0x48 (knocked back) for the enemy at 0x00159000: as 0x00153C20,
   with work flag 0x10000 cleared, the slide set up in place (speed of the velocity, rate
   0.005 per frame unit) instead of through 0x00156180, Jack's position kept at +0x74 and
   emitter 9. */
void rbi_KnockBack159BF0(RbiKbObj *obj, RbiKbAct *act)
{
    RbiKbWork159 *w = (RbiKbWork159 *)act->work278;
    RbiBasis *b;
    RbiVec4 v;
    RbhEmit *e;

    rbi_Enter1456E0(obj, act, 0x48, 0);
    obj->flags0C &= ~0x20u;
    act->flags4C &= ~0x70u;
    w->flags00 |= 3;
    w->flags40 &= 0xFFFEFFFFu;
    rbi_VecScale(&v, &act->vel88, -1.0f);
    v.y = 0.0f;
    rbi_VecNorm(&v, &v);
    rbi_VecScale(&obj->basis20->z20, &v, -1.0f);
    obj->basis20->y10.w = 0.0f;
    obj->basis20->y10.z = 0.0f;
    obj->basis20->y10.x = 0.0f;
    obj->basis20->y10.y = 1.0f;
    b = obj->basis20;
    rbi_VecCross(&b->x00, &b->y10, &b->z20);
    rbi_VecNorm(&v, &act->vel88);
    w->f2C = a50_frameUnits * rbi_VecDot(&v, &act->vel88);
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f30 = 1.0f;
    w->f10 = 0.0f;
    w->rateC = a50_frameUnits * 0.005f;
    rbi_VecCopy(&w->target74, (const RbiVec4 *)((uint8_t *)g_playerObj + 0x60));
    obj->flags10 |= 4;
    e = rbi_Emit113400(act, 9);
    e->f10 = 0.0833333358f;
    e->f14 = 0.0f;
    e->f18 = 0.0f;
    e->f1C = 0.0f;
}

/* 0x00187FB0: enter state 0x40 (pushed) for the enemy at 0x00187000: reset the slide block
   (0, 0, 0, 1), set work flag 0x10 and clear 0x200, clear object flag 0x20, face along the
   velocity (flat, upright basis), slide back at its speed, remember Jack's position at +0x08,
   set object flag 4 and start emitter 7 (rate 1/12). */
void rbi_Pushed187FB0(RbiKbObj *obj, RbiKbAct *act)
{
    RbiKbWork187 *w = (RbiKbWork187 *)act->work278;
    RbiBasis *b;
    RbiVec4 v;
    RbhEmit *e;

    rbi_Enter1456E0(obj, act, 0x40, 0);
    w->f28 = 0.0f;
    w->f24 = 0.0f;
    w->f20 = 0.0f;
    w->f2C = 1.0f;
    w->flags18 |= 0x10;
    obj->flags0C &= ~0x20u;
    w->flags18 &= ~0x200u;
    rbi_VecCopy(&v, &act->vel88);
    v.y = 0.0f;
    rbi_VecNorm(&v, &v);
    rbi_VecScale(&obj->basis20->z20, &v, -1.0f);
    obj->basis20->y10.w = 0.0f;
    obj->basis20->y10.z = 0.0f;
    obj->basis20->y10.x = 0.0f;
    obj->basis20->y10.y = 1.0f;
    b = obj->basis20;
    rbi_VecCross(&b->x00, &b->y10, &b->z20);
    rbi_VecNorm(&v, &act->vel88);
    w->f28 = -(a50_frameUnits * rbi_VecDot(&v, &act->vel88));
    w->f24 = 0.0f;
    w->f20 = 0.0f;
    w->f2C = 1.0f;
    rbi_VecCopy(&w->target08, (const RbiVec4 *)((uint8_t *)g_playerObj + 0x60));
    obj->flags10 |= 4;
    e = rbi_Emit113400(act, 7);
    e->f10 = 0.0833333358f;
    e->f14 = 0.0f;
    e->f18 = 0.0f;
    e->f1C = 0.0f;
}

/* 0x0012C3C0: enter state 5 (grab start): keep the start point (+0x30 to +0x40), reset the
   pull block (0, 0, 0, 1 and two 1.0 factors), object flags 5 on, actor flags 0x70 off,
   sound 0xF6 at the enemy, attachments 5 and (1 or 2, armed when actor flag bit 0 is set),
   then spawn effect 5/0xA 20 units below the enemy with its rotation; the effect must exist
   (the original hangs otherwise) and gets a zero offset. */
void rbi_GrabStart12C3C0(RbiGrabObj *obj, RbhComp *act)
{
    RbiVec4 off = { 0.0f, -20.0f, 0.0f, 0.0f };
    RbiVec4 zero = { 0.0f, 0.0f, 0.0f, 0.0f };
    RbiVec4 rot, pos;
    RbiGrabWork *w2 = (RbiGrabWork *)act->work278;
    RbiGrabWork *w;

    rbi_Enter1456E0(obj, act, 5, 0);
    w = (RbiGrabWork *)act->work278;
    rbi_VecCopy(&w->v40, &w->v30);
    w->v50.z = 0.0f;
    w->v50.y = 0.0f;
    w->v50.x = 0.0f;
    w->v50.w = 1.0f;
    w->f60 = 1.0f;
    w->f64 = 1.0f;
    obj->flags10 |= 5;
    act->flags4C &= ~0x70u;
    rbi_Sound494D0(0xF6, &obj->pos60, 0);
    sub_00036750(obj, 5);
    sub_00036750(obj, (act->bytes20[0] & 1) ? 2 : 1);
    rbi_VecAdd(&pos, &obj->pos60, &off);
    rbi_VecCopy(&rot, &obj->rot50);
    w2->fx08 = rbi_Spawn0ED630(5, 0xA, &pos, &rot, 1);
    if (!w2->fx08)
        for (;;)
            ;
    w2->fC = 0.0f;
    rtc_RecMatrixApply(w2->fx08, &zero);
}

/* 0x0012CAA0: enter state 0 (spin up) of the enemy family at 0x0012C000: keep the start
   point, reset the pull block with the rate 1/30 per frame unit (factor 1 only when that
   rate is exactly 1), a 10-second fall timer at -15, the spin matrix copied and rebuilt
   (0x0011F640 kind 1), a spin speed of 0.008 per frame unit and a step of 2 pi / (6 s)
   (the original hangs if the step is not at most 2 pi), then object flag 1 on and actor flags
   0x70 off.
   calls 0x0011F640 with EAX=1 ESI=&w->mat138 */
void rbi_SpinUp12CAA0(RbiKbObj *obj, RbiKbAct *act)
{
    RbiWork12C *w;
    float rate, spin, step;

    rbi_Enter1456E0(obj, act, 0, 0);
    w = (RbiWork12C *)act->work278;
    rate = a50_frameUnits * 0.0333333351f;
    rbi_VecCopy(&w->v40, &w->v30);
    w->v50.z = 0.0f;
    w->v50.y = 0.0f;
    w->v50.x = 0.0f;
    w->v50.w = 1.0f;
    if (rate == 1.0f)
        w->f60 = 1.0f;
    else
        w->f60 = 0.0f;
    w->rate64 = rate;
    w = (RbiWork12C *)act->work278;
    w->f6C = a50_frameSeconds * 10.0f;
    w->f68 = -15.0f;
    w->flags04 |= 1;
    spin = a50_frameUnits * 0.00800000038f;
    w = (RbiWork12C *)act->work278;
    w->flags04 |= 4;
    rbi_MatCopy(w->matF8, w->matB8);
    sub_0011F640(1, w->mat138);
    w->f17C = 0.0f;
    w->f180 = spin;
    w->i178 = 1;
    step = 6.28318548f / (a50_framesPerSecond * 6.0f);
    w = (RbiWork12C *)act->work278;
    /* assert-style hang: the original re-compares the step on every spin */
    if (!(step <= 6.28318548f))
        for (;;) ;
    w->f74 = 5.0f;
    w->step78 = step;
    w->flags04 |= 2;
    obj->flags10 |= 1;
    act->flags4C &= ~0x70u;
}
