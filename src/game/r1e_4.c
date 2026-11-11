/* Area r1e, group 4: camera list, trails, script variables 0x0003AF10..0x0003FC40. Names inferred. */
#include "r1e.h"

/* 0x0003AF10: give every link of the holder a camera controller from the
   pool, armed with t = -1. */
void r1e_CamArmAll(R1eHolder *h)
{
    R1eLink *l;
    R1eRes *r;
    R1eCamCtl *c;
    for (l = h->first; l != 0; l = l->next) {
        r = sub_0003DC70(r1e_camPool3DCFF0);
        if (r != 0) {
            sub_0003D880(&r1e_camList3DDC60, r);
            c = (R1eCamCtl *)r->data;
            c->flags = 1;
            c->d08 = 0;
            c->t = -1.0f;
            c->link = l;
        }
    }
}

/* 0x0003B0E0: if the first camera controller is active and started, try
   to resolve it (0x0003AAF0) and apply the result. */
void r1e_CamApplyFirst(void)
{
    int buf[4];
    R1eRes *head = r1e_camList3DDC60.first;
    R1eCamCtl *c;
    if (head != 0) {
        c = r1e_camList3DDC60.count > 0 ? (R1eCamCtl *)head->data : 0;
        if ((c->flags & 1) && c->t >= 0.0f) {
            if (sub_0003AAF0(c, buf) == 0)
                sub_000263B0(buf, ((R1eCamSrc *)c->link)->d30, r1e_g42CB08);
        }
    }
}

/* 0x0003C250: set up a trail for owner slot *index. */
void r1e_TrailInit(R1eTrail *t, R1eTrailOwner *o, int32_t *index)
{
    sub_001B2150(t);
    t->fn = (void *)sub_0003B550;
    sub_001B2160(o->slots + *index * 0x180, t);
    t->f10[0] = 0.0f;
    t->f10[1] = 0.0f;
    t->f10[2] = 0.0f;
    t->f10[3] = 0.0f;
    t->f10[4] = 0.0f;
    t->f10[5] = 0.0f;
    t->index = index;
    t->owner = o;
    t->rate = 0.05f;
    t->d2C = 0;
    t->d30 = 1;
}

/* 0x0003EB60: read a variable as a float (int, float or bool types). */
float r1e_VarGetFloat(R1eVar *v)
{
    float f = 0.0f;
    if (v != 0) {
        switch (v->type) {
        case 2: case 3:
            f = (float)v->u.i;
            break;
        case 5:
            if (v->u.i != 0)
                f = 1.0f;
            break;
        case 6:
            f = v->u.f;
            break;
        }
    }
    return f;
}

/* 0x0003EC30: make v an integer with range [min(a,b), max(a,b)], extra
   values c and d, and value x clamped to the range. */
void r1e_VarInitIntRange(R1eVar *v, int x, int a, int b, int c, int d)
{
    if (v != 0) {
        v->type = 2;
        if (a < b) {
            v->lo.i = a;
            v->hi.i = b;
        } else {
            v->lo.i = b;
            v->hi.i = a;
        }
        v->d1C.i = c;
        v->d20.i = d;
        v->type = 2;
        if (v->lo.i > x)
            v->u.i = v->lo.i;
        else if (v->hi.i < x)
            v->u.i = v->hi.i;
        else
            v->u.i = x;
    }
}

/* 0x0003ECD0: float version of 0x0003EC30 (type 6). */
void r1e_VarInitFloatRange(R1eVar *v, float x, float a, float b, float c, float d)
{
    if (v != 0) {
        v->type = 6;
        if (b > a) {
            v->lo.f = a;
            v->hi.f = b;
        } else {
            v->lo.f = b;
            v->hi.f = a;
        }
        v->d1C.f = c;
        v->d20.f = d;
        v->type = 6;
        if (v->lo.f > x)
            v->u.i = v->lo.i;
        else if (x > v->hi.f)
            v->u.i = v->hi.i;
        else
            v->u.f = x;
    }
}

/* 0x0003F780: script object operation: 0 counts the entries, 1 starts it
   unless busy, 2 forwards to 0x0003F650. Returns a (or the forward result). */
int r1e_SObjOp(int a, R1eSObj *o, int op)
{
    R1eE24 *e;
    int n;
    switch (op) {
    case 0:
        n = 0;
        if (o->x != 0 && (e = o->x->ents) != 0) {
            for (; e->d00 != 0; e++)
                n++;
        }
        o->count = n;
        break;
    case 1:
        if (sub_0003ED50(o, 0) == 0)
            sub_0003F570(o);
        break;
    case 2:
        return sub_0003F650(a, o);
    }
    return a;
}

/* 0x0003FC40: poll a sound: mark it playing (muting it if flagged) or,
   once it has ended, release it and mark it finished. */
void r1e_SndPoll(R1eSnd *s)
{
    if (s != 0) {
        if (sub_00076210(s->h) != 0) {
            sub_00076620(s->h);
            s->state = 1;
            if (s->flags & 1)
                s->h->vol = 0.0f;
            return;
        }
        if (s->h != 0)
            sub_00076060(s->h);
        s->state = 5;
        r1e_g2C4BA4 = 0;
    }
}
