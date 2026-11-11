/* Area r1e, group 12: record initialisers and step queues 0x00014D00..0x00033C80. Names inferred. */
#include "r1e.h"

/* 0x00014D00: initialise a sprite record (grey colours, unit scale). */
void r1e_SpriteInit(R1eSprite *s, void *a, int b)
{
    s->d08 = 0;
    s->d0C = 0;
    s->d3C = a;
    s->d84 = 0;
    s->d28 = 0;
    s->d2C = 0;
    s->d30 = 0;
    s->f10 = 0.0f;
    s->f14 = 0.0f;
    s->d40 = b;
    s->f00 = 0.0f;
    s->f04 = 0.0f;
    s->f1C = 1.0f;
    s->f20 = 1.0f;
    s->d18 = -1;
    s->d80 = 4;
    s->d24 = 0x41;
    s->f34 = 0.0f;
    s->f38 = 0.0f;
    s->f88 = 1.0f;
    s->col[3] = 0x80808080;
    s->col[2] = 0x80808080;
    s->col[1] = 0x80808080;
    s->col[0] = 0x80808080;
}

/* 0x000226B0: set the default view rectangles. */
void r1e_ViewInit(void)
{
    r1e_view37C4CC[0] = -256.0f;
    r1e_view37C4CC[5] = -256.0f;
    r1e_view37C4CC[1] = -224.0f;
    r1e_view37C4CC[6] = 224.0f;
    r1e_view37C4CC[2] = 512.0f;
    r1e_view37C4CC[3] = 0.0f;
    r1e_view37C4CC[7] = 512.0f;
    r1e_view37C4CC[8] = 0.0f;
    r1e_view37C4CC[4] = -0.0f;
    r1e_view37C4CC[9] = -0.0f;
    r1e_viewOn37C4C0 = 0;
    r1e_viewKind37C4C4 = 0x34;
    r1e_viewZoom37C4C8 = 2.0f;
}

/* 0x0002A3A0: step queue A: start a 10-unit wait, then count it down and
   shift the queue by one entry when it runs out. */
void r1e_QueueStepA(void)
{
    switch (r1e_qStateA37ED24) {
    case 0:
        r1e_qWaitA37ED28 = 10.0f;
        r1e_qStateA37ED24 = 1;
        break;
    case 1:
        r1e_qTimeA37ED3C -= 0.01f;
        if (r1e_qTimeA37ED3C <= 0.0f) {
            r1e_qA37ED04[0] = r1e_qA37ED04[1];
            r1e_qA37ED04[1] = r1e_qA37ED04[2];
            r1e_qA37ED04[2] = r1e_qA37ED04[3];
            r1e_qA37ED04[3] = r1e_qA37ED04[4];
            r1e_qA37ED04[4] = r1e_qA37ED04[5];
            r1e_qA37ED04[5] = r1e_qA37ED04[6];
            r1e_qTimeA37ED3C = 0.0f;
            r1e_qA37ED04[6] = r1e_qA37ED04[7];
            r1e_qA37ED04[7] = 0;
            r1e_qStateA37ED24 = 0;
        }
        break;
    }
}

/* 0x0002A7A0: step queue B: start a 360-unit wait, then shift the queue
   by one entry once the wait counter has reached zero. */
void r1e_QueueStepB(void)
{
    switch (r1e_qStateB37E0B4) {
    case 0:
        r1e_qWaitB37E0B8 = 360.0f;
        r1e_qStateB37E0B4 = 1;
        break;
    case 1:
        if (r1e_qLeftB37E0BE == 0) {
            r1e_qB37E094[0] = r1e_qB37E094[1];
            r1e_qB37E094[1] = r1e_qB37E094[2];
            r1e_qB37E094[2] = r1e_qB37E094[3];
            r1e_qB37E094[3] = r1e_qB37E094[4];
            r1e_qB37E094[4] = r1e_qB37E094[5];
            r1e_qB37E094[5] = r1e_qB37E094[6];
            r1e_qB37E094[6] = r1e_qB37E094[7];
            r1e_qB37E094[7] = 0;
            r1e_qStateB37E0B4 = 0;
        }
        break;
    }
}

/* 0x00033C80: initialise a transform record: identity axes, unit scale. */
void r1e_XformInit(R1eXform *x)
{
    x->ax[0][3] = 0.0f;
    x->ax[0][1] = 0.0f;
    x->ax[0][0] = 0.0f;
    x->ax[0][2] = 1.0f;
    x->ax[1][3] = 0.0f;
    x->ax[1][2] = 0.0f;
    x->ax[1][0] = 0.0f;
    x->ax[1][1] = 1.0f;
    x->ax[2][2] = 0.0f;
    x->ax[2][1] = 0.0f;
    x->ax[2][0] = 0.0f;
    x->ax[2][3] = 1.0f;
    x->d30 = -1;
    x->d34 = 0;
    x->d38 = 1;
    x->scale[3] = 1.0f;
    x->scale[2] = 1.0f;
    x->scale[1] = 1.0f;
    x->scale[0] = 1.0f;
    x->scale[4] = 1.0f;
    x->scale[5] = 1.0f;
    x->f54 = 0.0f;
}
