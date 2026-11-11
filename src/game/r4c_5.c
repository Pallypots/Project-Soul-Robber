/* Area r4c: thrown effect callbacks around 0x001955B0-0x00197790 (r4c_5). Names inferred. */
#include "r4c.h"

/* 0x001955B0: scale effect o and its attachment vectors by s; stores s in the component's work +0x18.
   regargs: p1=EAX (o); s on the stack. */
void r4c_FxScale(R4cNode *o, float s)
{
    R4cFxG *w = (R4cFxG *)((R4cActor *)sub_0001D960(o, 7))->work;
    float t;
    o->scale70[3] = 1.0f;
    o->scale70[2] = s;
    o->scale70[1] = s;
    o->scale70[0] = s;
    w->f18 = s;
    t = s * 3.4f;
    o->fB0 = t;
    o->fB4 = s * -6.8f;
    sub_000F5D40(o->vA0, r4c_v27B0CC);
    r4c_VecScale(o->vA0, o->vA0, s);
    o->fE8 = t;
    sub_000F5D40(o->vD8, r4c_v27B0E0);
    r4c_VecScale(o->vD8, o->vD8, s);
    sub_000F5D40(o->vF8, r4c_v27B0F0);
    sub_000F5D40(o->v108, r4c_v27B100);
    r4c_VecScale(o->vF8, o->vF8, s);
    r4c_VecScale(o->v108, o->v108, s);
}

/* 0x00195B60: grow the effect from work +0x1C and free it after 0.18 s in its state. Stack args (o a). */
void r4c_FxGrowFade(R4cNode *o, R4cActor *a)
{
    R4cFxH *w = (R4cFxH *)a->work;
    o->fE8 = w->f1C;
    o->fB0 = w->f1C;
    o->fB4 = w->f1C * -2.0f;
    o->vA0[1] = w->f1C;
    if (w->s80)
        sub_000C56B0(o);
    if (w->s82 && !sub_000F6A80())
        sub_000F60C0(o, 0, 0);
    w->f1C = 9.0f / (r4c_fps * 0.18f) + w->f1C;
    if (a->f6C > 0.18f)
        sub_000ED780(o);
}

/* 0x00195C80: move the thrown effect and accelerate it upward; hand back to the thrower after 11 s or on contact. Stack args (o a). */
void r4c_FxThrowRise(R4cNode *o, R4cActor *a)
{
    R4cFxK *w = (R4cFxK *)a->work;
    float lim;
    r4c_VecAdd(o->pos, o->pos, w->v44);
    w->v44[1] = 3.0f / r4c_fps + w->v44[1];
    lim = 140.0f / r4c_fps;
    if (w->v44[1] > lim)
        w->v44[1] = lim;
    if (w->f0C > 11.0f || (o->flags128 & 0xA))
        sub_00189DA0(o, w->p08, 2);
    w->f0C += r4c_frameSeconds;
}

/* 0x00195D20: move and spin the thrown effect; hand back after 60 units, 11 s or on contact. Stack args (o a). */
void r4c_FxThrowFly(R4cNode *o, R4cActor *a)
{
    R4cFxK *w = (R4cFxK *)a->work;
    r4c_VecAdd(o->pos, o->pos, w->v44);
    w->f20 += r4c_VecLenXZ(w->v44);
    r4c_Spin(o, r4c_spin32C7B8);
    sub_000C56B0(o);
    if (w->f20 >= 60.0f || w->f0C > 11.0f || (o->flags128 & 0xA))
        sub_00189DA0(o, w->p08, 2);
    w->f0C += r4c_frameSeconds;
}

/* 0x00195DE0: slide the thrown effect in X/Z and spin it; hand back after 80 units, 11 s or on contact. Stack args (o a). */
void r4c_FxThrowSlide(R4cNode *o, R4cActor *a)
{
    R4cFxK *w = (R4cFxK *)a->work;
    o->pos[0] += w->v44[0];
    o->pos[2] = w->v44[2] + o->pos[2];
    w->f20 += r4c_VecLenXZ(w->v44);
    r4c_Spin(o, r4c_spin32C7B8);
    sub_000C56B0(o);
    if (w->f20 > 80.0f || w->f0C > 11.0f || (o->flags128 & 0xA))
        sub_00189DA0(o, w->p08, 2);
    w->f0C += r4c_frameSeconds;
}

/* 0x00196120: place the thrown effect at its start and aim it at the target with speed +0x54. Stack args (o a). */
void r4c_FxThrowAim(R4cNode *o, R4cActor *a)
{
    R4cFxK *w = (R4cFxK *)a->work;
    float d[4];
    sub_000F5D40(o->pos, w->v24);
    o->pos[3] = 1.0f;
    r4c_VecSub(d, w->v34, o->pos);
    d[3] = 0.0f;
    sub_001AD7E0(d, d);
    r4c_VecScale(w->v44, d, w->f54);
    w->v44[3] = 0.0f;
    o->scale70[2] = 0.3f;
    o->scale70[1] = 0.3f;
    o->scale70[0] = 0.3f;
    sub_0001EEC0(o, w->f18);
    sub_000F5D40(w->v60, o->pos);
    w->s58 = 0;
}

/* 0x00196430: as 0x00196120 but aims 2.5 units below the target. Stack args (o a). */
void r4c_FxThrowAimLow(R4cNode *o, R4cActor *a)
{
    R4cFxK *w = (R4cFxK *)a->work;
    float d[4];
    sub_000F5D40(o->pos, w->v24);
    o->pos[3] = 1.0f;
    w->v34[1] = w->v34[1] - 2.5f;
    r4c_VecSub(d, w->v34, o->pos);
    d[3] = 0.0f;
    sub_001AD7E0(d, d);
    r4c_VecScale(w->v44, d, w->f54);
    w->v44[3] = 0.0f;
    o->scale70[2] = 0.3f;
    o->scale70[1] = 0.3f;
    o->scale70[0] = 0.3f;
    sub_0001EEC0(o, w->f18);
    sub_000F5D40(w->v60, o->pos);
    w->s58 = 0;
}

/* 0x00196C90: free the objects of the three dynamic record tables at 0x00401830/28/2C. No inputs. */
void r4c_FreeDynRecs(void)
{
    int i;
    if (r4c_g401830)
        for (i = 0; i < 4; i++)
            if (r4c_g401830[i].obj)
                sub_000ED780(r4c_g401830[i].obj);
    if (r4c_g401828)
        for (i = 0; i < 6; i++)
            if (r4c_g401828[i].obj)
                sub_000ED780(r4c_g401828[i].obj);
    if (r4c_g40182C)
        for (i = 0; i < 6; i++)
            if (r4c_g40182C[i].obj)
                sub_000ED780(r4c_g40182C[i].obj);
}

/* 0x00196D30: allocate the three dynamic record tables if missing; hangs if an allocation fails. No inputs. */
void r4c_AllocDynRecs(void)
{
    if (!r4c_g401830) {
        r4c_g401830 = (R4cRec40 *)sub_00053AB0(0x100, 0, 0x3AD);
        if (!r4c_g401830)
            for (;;)
                ;
    }
    if (!r4c_g401828) {
        r4c_g401828 = (R4cRec44 *)sub_00053AB0(0x198, 0, 0x3B3);
        if (!r4c_g401828)
            for (;;)
                ;
    }
    if (!r4c_g40182C) {
        r4c_g40182C = (R4cRec70 *)sub_00053AB0(0x2A0, 0, 0x3B9);
        if (!r4c_g40182C)
            for (;;)
                ;
    }
}

/* 0x001976B0: reset the motion of work block w (first entry: rise speed, start point, model hook).
   regargs: p1=EDI. */
void r4c_FxJReset(R4cFxJ *w)
{
    int n = w->s10;
    R4cNode *o;
    float *p;
    w->s0C = 0;
    o = w->obj;
    p = o->pos;
    o->scale70[3] = 1.0f;
    o->scale70[2] = 1.0f;
    o->scale70[1] = 1.0f;
    o->scale70[0] = 1.0f;
    if (n == 0) {
        w->f18 = 1.1f / r4c_fps;
        w->f1C = r4c_frameUnits * 2.25f;
        w->f20 = 0.0f;
        sub_000F5D40(w->v34, p);
        sub_000F5D40(p, p);
        w->v34[1] = -83.0f;
        o->pos[1] = -83.0f;
        if (o->p28) {
            sub_0001EE80(o, sub_00196B40);
            w->f08 = 1.6f;
            sub_0001EEC0(o, 1.6f);
        }
    } else if (n == 1) {
        sub_000F5D40(p, p);
    }
    w->s10 = (int16_t)n;
    w->s0E = 0;
    o->flagsC &= ~0x100u;
}
