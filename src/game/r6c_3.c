/* Area r6c: movie screen tasks and 3D sprite object leaves around 0x00078170-0x0007AB40 (r6c_3). Names inferred. */
#include "r6c.h"

/* 0x00078170: movie task: wait for loading to finish, start playback, then finish the task. */
void r6c_MovieTask(void *task)
{
    if (!sub_00031C50())
        while (sub_00031560(0, 0))
            sub_000580D0();
    sub_0001AE70(r6c_obj3E73A0, r6c_obj2DF680);
    while (sub_00077500())
        sub_000580D0();
    sub_0002BAB0();
    sub_00078050();
    sub_000580D0();
    sub_000580D0();
    sub_001A1060(task, 1);
    sub_00058190();
}

/* 0x000781F0: movie render loop: draw the current frame into the active buffer every frame.
   calls 0x00077AA0 with EAX=frame */
void r6c_MovieLoop(void)
{
    for (;;) {
        void *frame = a30_buf12[a30_bufIndex].p;
        sub_001A5310();
        if (a60_v3E7398 == 10000) {
            sub_001A7EE0();
            frame = sub_000727E0(sub_00077AA0(frame), a4c_obj428F40);
        }
        frame = sub_000324B0(frame);
        if (r6c_v3E7550)
            sub_00079480(frame);
        a30_buf12[a30_bufIndex].p = frame;
        sub_001A7B90();
        sub_000580D0();
    }
}

/* 0x00079270: register the three movie tasks and reset the movie state. */
void r6c_MovieStart(void *task)
{
    sub_00038960();
    sub_001A1030(task, 0, 0, r6c_MovieTask, 3, 0x2000);
    sub_001A1030(task, 1, 0, sub_000791A0, 3, 0x2000);
    sub_001A1030(task, -1, 5, r6c_MovieLoop, 3, 0x2000);
    sub_001A1060(task, 0);
    sub_001A1060(task, -1);
    a60_v3E7398 = 0;
    a60_v3E74B8 = 0;
}

/* 0x000796D0: set the fog colour from the table at 0x002DFF70. */
void *r6c_SetFogColour(void *a)
{
    return sub_001B7FF0(a, (uint8_t)r6c_colour2DFF70.r, (uint8_t)r6c_colour2DFF70.g,
                 (uint8_t)r6c_colour2DFF70.b, (uint8_t)r6c_colour2DFF70.a);
}

/* 0x00079700: initialise the first full-screen sprite. */
void r6c_SpriteInitA(void)
{
    R6cSprite *s = &r6c_sprite3E9228;
    sub_00012110(s);
    s->i0C = 0;
    s->i1C = 0;
    s->r = (uint8_t)r6c_colour3E92EC.r;
    s->i08 = 0x48;
    s->i18 = 0x31001;
    s->g = (uint8_t)r6c_colour3E92EC.g;
    s->b = (uint8_t)r6c_colour3E92EC.b;
    s->a = (uint8_t)r6c_colour3E92EC.a;
    s->x0 = 0x7000;
    s->y0 = 0x7900;
    s->x1 = 0x2000;
    s->y1 = 0x1C00;
}

/* 0x000797A0: initialise the second full-screen sprite (black). */
void r6c_SpriteInitB(void)
{
    R6cSprite *s = &r6c_sprite3E9260;
    sub_00012110(s);
    s->i08 = 0x48;
    s->i0C = 0;
    s->i18 = 0x31001;
    s->i1C = 0;
    s->b = 0;
    s->g = 0;
    s->r = 0;
    s->a = 0;
    s->x0 = 0x7000;
    s->y0 = 0x7900;
    s->x1 = 0x2000;
    s->y1 = 0x1C00;
}

/* 0x00079830: point the GPU at the current back buffer and draw object a. */
void *r6c_DrawToBackBuffer(void *a)
{
    uint8_t *surf = sub_001B9650(-1);
    uint64_t v = (*(uint32_t *)(surf + 0x28) & 0x3FE0) | 0x1000000;
    v >>= 5;
    sub_000389C0(0x4C, (int)v, (int)(v >> 32));
    sub_001A7620(0);
    return sub_00039920(sub_000398D0(sub_00038F10(a), 1), 1);
}

/* 0x00079C40: build a matrix from rotation angles (z, x, y), a per-row scale and a position.
   regargs: m=ESI rot=EAX */
void r6c_BuildMatrix(R6cMtx *m, const R6cVec4 *rot, const R6cVec4 *pos, float scale)
{
    sub_001AD940(m);
    sub_001AD910(m, m, rot->z);
    sub_001AD8B0(m, m, rot->x);
    sub_001AD8E0(m, m, rot->y);
    sub_001ADBA0(m->r[0], m->r[0], scale);
    sub_001ADBA0(m->r[1], m->r[1], scale);
    sub_001ADBA0(m->r[2], m->r[2], scale);
    sub_000F5D40(m->r[3], pos);
    m->r[3][3] = 1.0f;
}

/* 0x00079F50: copy the object's colour into one of the two colour slots of a draw record. */
void r6c_ObjCopyColour(R6cObj7 *o, R6cDraw *d, int flags)
{
    if (flags & 1) {
        d->c100.r = (uint8_t)o->colR;
        d->c100.g = (uint8_t)o->colG;
        d->c100.b = (uint8_t)o->colB;
        d->c100.a = 0x80;
        d->c100.scale = 1.0f;
    } else {
        d->c1F0.r = (uint8_t)o->colR;
        d->c1F0.g = (uint8_t)o->colG;
        d->c1F0.b = (uint8_t)o->colB;
        d->c1F0.a = 0x80;
        d->c1F0.scale = 1.0f;
    }
}

/* 0x0007AB40: re-attach or detach each linked attachment of the object. */
void r6c_ObjUpdateAttach(R6cObj7 *o)
{
    R6cAttach *n;
    for (n = o->attach; n; n = n->next) {
        if (n->kind == 1 && n->u80.target) {
            R6cAttach *t = n->u80.target;
            uint8_t *m = sub_000847F0(o->mdl, t->u80.id);
            if (!sub_00082E50(t, m + 0x230))
                sub_001B2020(m, n->p20);
            else
                sub_001B2080(n->p20);
        }
    }
}
