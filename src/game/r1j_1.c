/* Area r1j, group 1: camera 0x000193F0.
   Names inferred. */
#include "r1j.h"

/* 0x000193F0: initialise camera c: identity base matrix, blend state and
   the work words cleared (+0x288/+0x28C to -1), the six view matrices set
   to identity with a 45 degree field of view, and the ten curve channels
   given 16-key slice buffers. */
void r1j_CamInit(R1iCam *c)
{
    int i;
    sub_001AD940(c->m10);
    c->flags = 0;
    c->blend = 0.0f;
    c->blendTo = 0.0f;
    for (i = 0; i < 17; i++)
        c->w244[i] = 0;
    c->cfg = 0;
    c->i288 = -1;
    c->i28C = -1;
    c->i12BC = 1;
    c->i12C0 = 0;
    sub_001AD940(c->view[0].m);
    c->view[0].fov = 45.0f;
    sub_001AD940(c->view[1].m);
    c->view[1].fov = 45.0f;
    sub_001AD940(c->view[2].m);
    c->view[2].fov = 45.0f;
    sub_001AD940(c->view[3].m);
    c->view[3].fov = 45.0f;
    sub_001AD940(c->view[4].m);
    c->view[4].fov = 45.0f;
    sub_001AD940(c->view[5].m);
    c->view[5].fov = 45.0f;
    sub_00062050(&c->cv.ch[0], c->cv.ch[0].buf, 16);
    sub_00062050(&c->cv.ch[1], c->cv.ch[1].buf, 16);
    sub_00062050(&c->cv.ch[2], c->cv.ch[2].buf, 16);
    sub_00062050(&c->cv.ch[3], c->cv.ch[3].buf, 16);
    sub_00062050(&c->cv.ch[4], c->cv.ch[4].buf, 16);
    sub_00062050(&c->cv.ch[5], c->cv.ch[5].buf, 16);
    sub_00062050(&c->cv.ch[6], c->cv.ch[6].buf, 16);
    sub_00062050(&c->cv.ch[7], c->cv.ch[7].buf, 16);
    sub_00062050(&c->cv.ch[8], c->cv.ch[8].buf, 16);
    sub_00062050(&c->cv.ch[9], c->cv.ch[9].buf, 16);
}
