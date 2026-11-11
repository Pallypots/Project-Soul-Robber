/* Area r6c: 3D sprite object callers around 0x000798B0-0x0007D1B0 (r6c_4). Names inferred. */
#include "r6c.h"

/* 0x000798B0: initialise a sprite object: work buffer, default light and colour, both sprites. */
void r6c_ObjInit(R6cObj7 *o)
{
    sub_001B32E0(o, sub_00053AB0(0x1000, 0, 0x138), 0x1000);
    sub_001B20F0(250.0f);
    sub_001B2120(0);
    o->light = r6c_light2DFF80;
    o->colour = &r6c_colour2DFF70;
    r6c_SpriteInitA();
    r6c_SpriteInitB();
}

/* 0x00079980: give every model part its table vector and light it. */
void r6c_ApplyVecs(R6cMdlList *l, R6cLight *light)
{
    unsigned i;
    for (i = 0; i < l->count; i++) {
        R6cVec4 v;
        r6c_LookupVec(i, &v);
        sub_000F5D40(&light->v24, &v);
        sub_001B7100(l->items[i].blk24, light);
    }
}

/* 0x00079DA0: rebuild the object matrix from its rotation, position and scale.
   calls 0x00079C40 with ESI=&o->m154 EAX=&o->v194; 0x00079CB0 with ESI=o */
void r6c_ObjRebuild(R6cObj7 *o)
{
    r6c_BuildMatrix(&o->m154, &o->v194, &o->v1A4, o->scale);
    sub_00079CB0(o);
}

/* 0x00079DE0: set the object matrix from b, then refresh. calls 0x00079CB0 with ESI=o */
void r6c_ObjSetMatrix(R6cObj7 *o, const void *b)
{
    sub_001ADA40(&o->m154, b);
    sub_00079CB0(o);
}

/* 0x0007AAC0: place the object's light from matrix a and intensity b. */
void r6c_ObjPlaceLight(R6cObj7 *o, const void *a, int b)
{
    sub_000385D0(&o->m154, a);
    sub_001B74E0(&o->light, 224.0f, b);
    sub_00084790(o->mdl, &o->light);
}

/* 0x0007ACC0: reset rotation and position to the default vector, scale 1, rebuild.
   calls 0x00079C40 with ESI=&o->m154 EAX=&o->v194; 0x00079CB0 with ESI=o */
void r6c_ObjResetPose(R6cObj7 *o)
{
    sub_000F5D40(&o->v194, &r6c_vec3E92DC);
    sub_000F5D40(&o->v1A4, &r6c_vec3E92DC);
    o->scale = 1.0f;
    r6c_BuildMatrix(&o->m154, &o->v194, &o->v1A4, 1.0f);
    sub_00079CB0(o);
}

/* 0x0007D1B0: draw the object's three layers, attachments and shadow; a selects the pass. */
void r6c_ObjDrawAll(R6cObj7 *o, void *a)
{
    void *h;
    sub_000AD090(0xFFFFFF);
    sub_00081E60(o->i48, 0);
    sub_00081E60(o->i4C, 0);
    sub_00081E60(o->i50, 1);
    r6c_ObjUpdateAttach(o);
    sub_000AD090(0x808080);
    h = sub_000849D0(o->mdl, a);
    sub_000AD090(0x8000);
    sub_00012300(sub_00039920(h, 0), 0x47, 0, 0x5000D, 0);
}
