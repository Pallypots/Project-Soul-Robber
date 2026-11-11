/* Area r4h: orbiting effect steps (r4h_6). Names inferred. */
#include "r4h.h"

/* 0x001984C0: per-frame step of an effect circling its parent: advance
   the two orbit offsets, write the spin (X then Y rotation) to the
   object's matrix, place the offset around the parent with the Y rotation,
   add it and the pending velocity to the position, then clear the
   velocity. Stack args (o a). */
void r4h_FxOrbitStepB(R4hOrbObj *o, R4hOrbAct *a)
{
    R4hOrbWork *w = a->work;
    float v[4];
    float m[16];
    float *p;
    float *vel;

    v[0] = 0.0f;
    v[1] = w->f14;
    v[2] = w->f18;
    v[3] = 1.0f;
    w->f14 = w->f0C + w->f14;
    w->f18 = w->f10 + w->f18;
    sub_001AD940(m);
    sub_001AD8B0(m, m, o->rotX50);
    sub_001AD8E0(m, m, o->rotY54);
    sub_001ADA40(o->mtx20, m);
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->rotY54);
    p = o->parent34->pos70;
    v[0] = p[0] + v[0];
    v[1] = p[1] + v[1];
    v[2] = p[2] + v[2];
    v[3] = p[3];
    sub_001AD9B0(v, m, v);
    p = o->pos60;
    p[0] = p[0] + v[0];
    p[1] = p[1] + v[1];
    p[2] = p[2] + v[2];
    p[3] = p[3];
    vel = o->vel80;
    sub_001ADAF0(p, p, vel);
    vel[0] = 0.0f;
    vel[1] = 0.0f;
    vel[2] = 0.0f;
    vel[3] = 1.0f;
    o->pos60[3] = 1.0f;
}

/* 0x00198640: as 0x001984C0 for the effect without a spin matrix: only
   the Y rotation places the orbit offset. Stack args (o a). */
void r4h_FxOrbitStepA(R4hOrbObj *o, R4hOrbAct *a)
{
    R4hOrbWork *w = a->work;
    float v[4];
    float m[16];
    float *p;
    float *vel;

    v[0] = 0.0f;
    v[1] = w->f10;
    v[2] = w->f14;
    v[3] = 1.0f;
    w->f10 = w->f08 + w->f10;
    w->f14 = w->f0C + w->f14;
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->rotY54);
    p = o->parent34->pos70;
    v[0] = p[0] + v[0];
    v[1] = p[1] + v[1];
    v[2] = p[2] + v[2];
    v[3] = p[3];
    sub_001AD9B0(v, m, v);
    p = o->pos60;
    p[0] = p[0] + v[0];
    p[1] = p[1] + v[1];
    p[2] = p[2] + v[2];
    p[3] = p[3];
    vel = o->vel80;
    sub_001ADAF0(p, p, vel);
    vel[0] = 0.0f;
    vel[1] = 0.0f;
    vel[2] = 0.0f;
    vel[3] = 1.0f;
    o->pos60[3] = 1.0f;
}
