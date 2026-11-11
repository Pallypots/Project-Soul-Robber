/* Area r6f: scene clock and timed task dispatch around 0x00089AB0-0x0008E473 (r6f_13). Names inferred. */
#include "r6f.h"

/* 0x00089AB0: start every task of the scene whose time has come and whose
   channel bits are enabled by the scene mask (kind 12 is skipped while mask
   bit 0x400 is set). */
int r6f_SceneStartDue(R6fScene *s)
{
    float now = s->now;
    R6fTask *n;
    R6fKey *w;
    uint32_t m, c, d;
    for (n = s->tasks; n; n = (R6fTask *)sub_0007F300(n)) {
        w = (R6fKey *)n->work;
        if (w->f00 > now)
            break;
        m = ~*s->mask;
        c = ~w->u0C;
        d = m & 0x3FC;
        if ((m & c) & 3) {
            if ((*s->mask & 0x400) && w->kind04 == 12)
                continue;
            if ((d & c) & 0x3FC) {
                if (!sub_0008AFC0(n))
                    sub_0008AFD0(n, s);
            }
        }
    }
    return 0;
}

/* 0x00089DD0: advance a running scene (bit 8) unless paused (bit 9): step the
   clock by its rate, mark it finished at the end, start due tasks; then let
   each child handle the scene and step the reference list. */
int r6f_SceneUpdate(R6fScene *s)
{
    R6fTask *n;
    int r;
    if (s->flags & 0x100) {
        if (!(s->flags & 0x200)) {
            sub_00089B50(s, s->rate + s->now);
            if (s->end == s->now)
                s->flags |= 0x202;
        }
        sub_00089AB0(s);
    }
    for (n = s->children; n; n = (R6fTask *)sub_0007F300(n)) {
        r = sub_0008C420(n, s);
        if (r)
            return r;
    }
    sub_0008CC50(&s->refs, s);
    return 0;
}

/* 0x0008E3D0: look up the animation entry of the task's id; attach it and, when
   asked, set the blend of the attached part from the scene time since the
   task's start (x0.5, not negative); without an entry drop the part. */
void r6f_TaskAnimAttach(R6eTask *t, uint8_t setBlend)
{
    R6fAnimHost *a = (R6fAnimHost *)((R6eAnimRef *)t->p28)->p5C;
    uint8_t *e;
    R6fRefObjF *r;
    float d;
    sub_00053710(4);
    e = (uint8_t *)sub_00033DC0(a->p12C, t->i124);
    sub_00053740();
    if (e) {
        sub_00033D10(a, e + 0x14);
        if (a->part) {
            r = (R6fRefObjF *)sub_00089390();
            if (setBlend) {
                d = r->f10 - t->f34;
                if (r->f10 < t->f34)
                    d = 0.0f;
                a->part->blend = d * 0.5f;
            }
        }
    } else if (a->part) {
        sub_00033C20(a->part);
        a->part = 0;
    }
}

/* 0x0008A610: while the scene time lies between the first two kind-1/1 nodes
   of list, switch the scene to the first node's mode (event 3 or 4 when it
   changes) and run 0x0008BFD0 on it. */
int r6f_SceneTrackMode(R6fTask *list, R6fSceneB *s)
{
    int r = 0;
    R6fTask *a, *b;
    R6fKey *wa;
    if (!s)
        return -1;
    a = sub_0008B290(list, 1, 1);
    if (!a)
        return -1;
    wa = (R6fKey *)a->work;
    b = sub_0008B290((R6fTask *)sub_0007F300(a), 1, 1);
    if (!b)
        return -1;
    if (s->now >= ((R6fKey *)a->work)->f00 && ((R6fKey *)b->work)->f00 > s->now) {
        if (s->mode != wa->i10) {
            r = sub_0008C240(s->heap, s, ((wa->i10 - 1) & 1) + 3);
            if (r)
                return r;
            s->mode = wa->i10;
        }
        return sub_0008BFD0(s->heap, s);
    }
    return r;
}
