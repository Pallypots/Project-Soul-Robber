/* Area r1i, group 14: attach character units to scene cameras 0x0001E9B0.
   Names inferred. */
#include "r1i.h"

/* 0x0001E9B0: attach the shown, visible nodes of unit u and the units
   chained after it to cameras of scene s: the first unit's shadow to
   shadowCam; each model to modelCam with the scene ambient colour and
   light (effect models, flag 0x10, get the colour on their grandchild and
   go to camera 7 when shadowCam is set); each effect node to fxCam.
   A camera index of -1 or less means none. */
void r1i_UnitsAttach(R1iScene *s, R1iUnit *u, int shadowCam, int modelCam, int fxCam)
{
    R1iMdlNode *n;
    void *cam;
    uint32_t f;
    if (u->shadow && (u->flags & 1) && !u->shadow->hidden && shadowCam > -1)
        sub_001B2020(sub_000847F0(s->cams, shadowCam), u->shadow);
    do {
        if (u->model) {
            f = u->flags;
            if ((f & 1) && !u->model->hidden) {
                if (!(f & 0x10)) {
                    if (modelCam > -1) {
                        cam = sub_000847F0(s->cams, modelCam);
                        sub_001B2020(cam, u->model);
                        u->model->cam = cam;
                        u->model->col[0] = (float)s->ambient[0];
                        u->model->col[1] = (float)s->ambient[1];
                        u->model->col[2] = (float)s->ambient[2];
                        u->model->col[3] = (float)s->ambient[3];
                        sub_001B82E0(u->model, s->light);
                    }
                } else if (shadowCam > -1) {
                    n = u->model->child88->child84->child84;
                    n->col[0] = (float)s->ambient[0];
                    n->col[1] = (float)s->ambient[1];
                    n->col[2] = (float)s->ambient[2];
                    n->col[3] = (float)s->ambient[3];
                    sub_001B3160(n);
                    sub_001B2020(sub_000847F0(s->cams, 7), u->model);
                }
            }
        }
        if (u->fx && (u->flags & 1) && u->fx->node && !u->fx->node->hidden && fxCam > -1)
            sub_001B2020(sub_000847F0(s->cams, fxCam), u->fx->node);
        u = u->next;
    } while (u);
}
