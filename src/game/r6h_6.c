/* Area r6h: texture scroll animation, tex_ex.c (r6h_6). Names inferred. */
#include "r6h.h"

/* 0x00074F40: advance the scrolling texture layers of every animated texture
   object by the frame time, wrapping the offsets into 0..1. Type 5 objects
   have 0x100-byte layers, type 1 objects 0x108-byte layers; layers without a
   texture are skipped. */
void r6h_TexScrollUpdate(void)
{
    R6hTexNode *n;
    int i;

    for (n = r6h_texAnims3E6998; n; n = n->next) {
        R6hTexObj *o = n->obj;
        if (o->type == 5) {
            for (i = 0; i < o->count; i++) {
                R6hTexLayerA *l = &((R6hTexLayerA *)o->layers)[i];
                float t;
                if (!l->tex)
                    continue;
                if (l->du != 0.0f) {
                    t = l->du * a50_frameUnits + l->u;
                    l->u = t;
                    if (t > 1.0f)
                        l->u = t - 1.0f;
                    else if (0.0f > t)
                        l->u = t + 1.0f;
                }
                if (l->dv != 0.0f) {
                    t = l->dv * a50_frameUnits + l->v;
                    l->v = t;
                    if (t > 1.0f)
                        l->v = t - 1.0f;
                    else if (0.0f > t)
                        l->v = t + 1.0f;
                }
            }
        } else if (o->type == 1) {
            for (i = 0; i < o->count; i++) {
                R6hTexLayerB *l = &((R6hTexLayerB *)o->layers)[i];
                float t;
                if (!l->tex)
                    continue;
                if (l->du != 0.0f) {
                    t = l->du * a50_frameUnits + l->u;
                    l->u = t;
                    if (t > 1.0f)
                        l->u = t - 1.0f;
                    else if (0.0f > t)
                        l->u = t + 1.0f;
                }
                if (l->dv != 0.0f) {
                    t = a50_frameUnits * l->dv + l->v;
                    l->v = t;
                    if (t > 1.0f)
                        l->v = t - 1.0f;
                    else if (0.0f > t)
                        l->v = t + 1.0f;
                }
            }
        }
    }
}
