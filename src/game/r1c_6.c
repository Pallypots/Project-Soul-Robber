/* Area r1c, group 6: mixed helpers 0x0001ED90..0x0005C3E0. Names inferred. */
#include "r1c.h"

/* 0x0001ED90: queue register 0x4C from the current texture's address bits
   and build the packet at p; returns the packet end. */
int r1c_PktTexBase(int p)
{
    R1cTexCtx *t = sub_001B9650(-1);
    uint64_t v = ((t->q28 >> 5) & 0x1FF) | 0x7FFFFFFF00080000ull;
    int r;
    r1c_ReqPush(0x4C, (int)(uint32_t)v, (int)(uint32_t)(v >> 32));
    r = sub_00038F10(p);
    sub_001A27D0(1);
    return r;
}

/* 0x00023B70: one-time initialisation of the colour scale table: thirteen
   pairs set to 1.0 and the alpha byte to 0x80. */
void r1c_ColInitOnce(void)
{
    int i;
    if (r1c_col37EE10.inited != 0) return;
    for (i = 0; i < 13; i++) {
        r1c_col37EE10.scale[i][0] = 1.0f;
        r1c_col37EE10.scale[i][1] = 1.0f;
    }
    r1c_col37EE10.alpha = 0x80;
    r1c_col37EE10.inited++;
}

/* 0x0003A950: compare two cameras by priority value for sorting: a camera
   without an active, non-negative value sorts last. */
int r1c_CamCompare(R1cCam *a, R1cCam *b)
{
    R1cCamSet *sb = b->set;
    R1cCamSet *sa = a->set;
    if (!(sb->flags & 1) || 0.0f > sb->value) return 1;
    if (!(sa->flags & 1) || 0.0f > sa->value) return -1;
    if (sb->value > sa->value) return 1;
    if (sa->value > sb->value) return -1;
    return 0;
}

/* 0x0003ACC0: release every resource referenced by a list's entries, then
   the list's own resource. */
void r1c_ListRelease(R1cResList *l)
{
    R1cResEnt *e;
    for (e = sub_0003DC50(l); e != 0; e = sub_0003DC50(l)) {
        if (e->res != 0)
            sub_00053880(e->res);
    }
    if (l->res != 0) {
        sub_00053880(l->res);
        l->res = 0;
    }
}

/* 0x0003EBD0: 1 when a typed variable holds a nonzero value (types 2..4
   integer, 5 integer, 6 float), else 0. */
int r1c_VarIsSet(R1cVar *v)
{
    int r = 0;
    if (v == 0) return 0;
    switch (v->type) {
    case 2:
    case 3:
    case 4:
        return v->u.i != 0;
    case 6:
        return (int)v->u.f != 0;
    case 5:
        r = v->u.i != 0;
        break;
    }
    return r != 0;
}

/* 0x00058910: wake a background job that is waiting (state 2) on another
   thread; 0 on success, -1 otherwise. */
int r1c_JobWake(int id)
{
    R1cJob *j = (R1cJob *)r1c_JobById(id);
    if (j == 0 || j->thread == -1 || j->thread == sub_001AD560() || j->state != 2)
        return -1;
    j->state = 1;
    sub_0003D910((char *)j - 0x10);
    sub_001AD6A0();
    return 0;
}

/* 0x0005C3E0: reset a stream descriptor (block size 0x1800, 4 buffers) and
   forget the current stream; returns 0. */
int r1c_StreamReset(R1cStream *s)
{
    if (s == 0) return 0;
    s->d00 = 0;
    s->d04 = 0;
    s->d08 = 0;
    s->d0C = 0;
    s->count = 0;
    s->size = 0;
    s->d18 = 0;
    s->d1C = 0;
    sub_0003D860(s);
    s->count = 4;
    s->size = 0x1800;
    r1c_stream2DD4D8 = -1;
    return 0;
}
