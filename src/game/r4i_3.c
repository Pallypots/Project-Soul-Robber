/* Area r4i: chain effect update (0x00191860). Names inferred. */
#include "r4i.h"

/* 0x00191860: per-frame update of a chain effect (kind-1 set, hangs
   otherwise). Rates per frame: drag 1.5, pull 7.8, gravity 8.8 and
   terminal speed 180 per second, scaled by 0.78/0.83 while the work is
   not calm. After 0.15 s every link but the first fades out at 128 per
   1.85 s. For each such link not resting (falling and at height >= 1):
   rotate its world matrix by its rotation step, move it by its velocity;
   when the XZ speed is below the drag, pull the XZ velocity back by the
   larger of drag and (speed - pull); then add gravity up to the terminal
   speed. After 2 s the node is destroyed. Stack args (o a). */
void r4i_FxChainUpdate(R4iNode *o, R4iActor *a)
{
    R4iChainSet *set = o->set20;
    R4iChainWork *w = (R4iChainWork *)a->work;
    R4iChainLink *ln;
    float rate = 1.0f / r4i_fps;
    float grav = rate * 8.8f;
    float term = rate * 180.0f;
    float pull = rate * 7.8f;
    float drag = rate * 1.5f;
    float m[16];
    float d[4];
    float *vel;
    float t;
    int fade = 0;
    int n;

    if (set->kind8C != 1)
        for (;;)
            ;
    ln = set->linksC4 + 1;
    n = set->countC0 - 1;
    if (w->calm04 == 0) {
        term = term * 0.83f;
        grav = grav * 0.83f;
        pull = pull * 0.78f;
        drag = drag * 0.78f;
    }
    if (a->time6C > 0.15f)
        fade = 1;
    for (; n > 0; n--, ln++) {
        if (fade) {
            ln->fadeE8 = ln->fadeE8 - 128.0f / (r4i_fps * 1.85f);
            if (0.0f > ln->fadeE8)
                ln->fadeE8 = 0.0f;
        }
        if (ln->m00[13] > 0.0f && ln->m40[13] >= 1.0f)
            continue;
        sub_001ADA40(m, ln->m00);
        m[12] = 0.0f;
        m[13] = 0.0f;
        m[14] = 0.0f;
        m[15] = 1.0f;
        sub_001AD7C0(ln->m40, ln->m40, m);
        vel = &ln->m00[12];
        sub_001ADAF0(&ln->m40[12], &ln->m40[12], vel);
        ln->m40[15] = 1.0f;
        if (drag > r4i_VecLenXZ(vel)) {
            t = r4i_VecLenXZ(vel) - pull;
            if (drag > t)
                t = drag;
            sub_000F5D40(d, vel);
            d[1] = 0.0f;
            d[3] = 0.0f;
            sub_001AD7E0(d, d);
            sub_001ADB60(d, d, t);
            r4i_VecSub(vel, vel, d);
        }
        ln->m00[13] = ln->m00[13] + grav;
        if (ln->m00[13] > term)
            ln->m00[13] = term;
    }
    if (a->time6C > 2.0f)
        r4i_ObjDestroy(o);
}

/* 0x00197BA0: fall step of the thirteen links after the first of a
   chain record's node: fade each visible link out at 128 per 0.7 s
   (0.75 s when calm); for each link below height 0, rotate its world
   matrix by its rotation step, move it by its velocity, reduce the
   vertical velocity by the link's drop, and snap the height to 0 once it
   reaches 0. Stack arg (r). */
void r4i_ChainFall(R4iChainRec *r)
{
    R4iChainLink *ln = r->node->set20->linksC4 + 1;
    R4iDrop *e = r->e08;
    float m[16];
    float k;
    int n;

    for (n = 13; n != 0; n--, e++, ln++) {
        if (ln->fadeE8 > 0.0f) {
            if (r->calm04 == 0)
                k = r4i_fps * 0.7f;
            else
                k = r4i_fps * 0.75f;
            k = 128.0f / k;
            ln->fadeE8 = ln->fadeE8 - k;
            if (!(0.0f < ln->fadeE8))
                ln->fadeE8 = 0.0f;
        }
        if (ln->m40[13] >= 0.0f)
            continue;
        sub_001ADA40(m, ln->m00);
        m[12] = 0.0f;
        m[13] = 0.0f;
        m[14] = 0.0f;
        m[15] = 1.0f;
        sub_001AD7C0(ln->m40, ln->m40, m);
        sub_001ADAF0(&ln->m40[12], &ln->m40[12], &ln->m00[12]);
        ln->m00[13] = ln->m00[13] - e->drop;
        ln->m40[15] = 1.0f;
        if (!(ln->m40[13] < 0.0f))
            ln->m40[13] = 0.0f;
    }
}
