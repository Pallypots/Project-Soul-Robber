/* Area r1i, group 8: camera blend 0x0001A800. Names inferred. */
#include "r1i.h"

/* 0x0001A800: blend camera c towards its target view (view 4) by t
   (clamped to 0..1). The secondary blend factor eases towards blendTo
   while the difference exceeds the configured threshold. Look direction
   (unless flag 2 of the configuration), up row and position are
   interpolated by t; the field of view by 0.3 (state 8..13) or 0.1 when
   camera flag 2 is set, else by t. */
void r1i_CamBlend(R1iCam *c, float t)
{
    R1iAimCfg *cfg;
    float b;
    if (t > 1.0f)
        t = 1.0f;
    else if (0.0f > t)
        t = 0.0f;
    cfg = c->cfg;
    if (sub_001A3F30(c->blendTo - c->blend) > cfg->thresh)
        c->blending = 1;
    if (c->blending) {
        b = (c->blendTo - c->blend) * cfg->rate * a50_frameUnits + c->blend;
        c->blend = b;
        if (b > 1.0f)
            c->blend = 1.0f;
        else if (0.0f > b)
            c->blend = 0.0f;
        if (0.0001f > sub_001A3F30(c->blendTo - c->blend))
            c->blending = 0;
    }
    if (!(c->cfg->flags & 2))
        sub_001ADCD0(c->view[0].m[2], c->view[4].m[2], c->view[0].m[2], t);
    sub_001ADCD0(c->view[0].m[1], c->view[4].m[1], c->view[0].m[1], t);
    sub_001ADCD0(c->view[0].m[3], c->view[4].m[3], c->view[0].m[3], t);
    if (c->flags & 2) {
        if (a1b_i37C050 >= 8 && a1b_i37C050 <= 13)
            c->view[0].fov = (c->view[4].fov - c->view[0].fov) * 0.3f + c->view[0].fov;
        else
            c->view[0].fov = (c->view[4].fov - c->view[0].fov) * 0.1f + c->view[0].fov;
    } else {
        c->view[0].fov = (c->view[4].fov - c->view[0].fov) * t + c->view[0].fov;
    }
}
