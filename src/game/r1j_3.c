/* Area r1j, group 3: quad packet template 0x00012160.
   Names inferred. */
#include "r1j.h"

/* 0x00012160: fill quad packet template p with its default GS registers
   and the texture registers of texture `tex`; the four vertices get
   colour 0x80 in every channel, depth 0xFFFFF0 and zero coordinates. */
void r1j_QuadTplInit(R1iQuadTpl *p, int tex)
{
    R1iTex *t = sub_001B9650(tex);
    p->ent[0].id = 0x42;
    p->ent[0].lo = 0x44;
    p->ent[0].hi = 0;
    p->ent[1].id = 0x3B;
    p->ent[1].lo = 0x8080;
    p->ent[1].hi = 0x40;
    p->ent[2].id = 0x47;
    p->ent[2].lo = 0x5000D;
    p->ent[2].hi = 0;
    p->texLo = t->reg[0];
    p->texHi = t->reg[1];
    p->ent[3].id = 0x14;
    p->ent[3].lo = t->reg[2];
    p->ent[3].hi = t->reg[3];
    p->ent[4].id = 0x34;
    p->ent[4].lo = t->reg[4];
    p->ent[4].hi = t->reg[5];
    p->ent[5].id = 0x36;
    p->ent[5].lo = t->reg[6];
    p->ent[5].hi = t->reg[7];
    p->ent[6].id = 8;
    p->ent[6].lo = t->reg[8];
    p->ent[6].hi = t->reg[9];
    p->v[0].c[3] = 0x80;
    p->v[0].c[2] = 0x80;
    p->v[0].c[1] = 0x80;
    p->v[0].c[0] = 0x80;
    p->v[1].c[3] = 0x80;
    p->v[1].c[2] = 0x80;
    p->v[1].c[1] = 0x80;
    p->v[1].c[0] = 0x80;
    p->v[2].c[3] = 0x80;
    p->v[2].c[2] = 0x80;
    p->v[2].c[1] = 0x80;
    p->v[2].c[0] = 0x80;
    p->v[3].c[3] = 0x80;
    p->v[3].c[2] = 0x80;
    p->v[3].c[1] = 0x80;
    p->v[3].c[0] = 0x80;
    p->z[3] = 0xFFFFF0;
    p->z[2] = 0xFFFFF0;
    p->z[1] = 0xFFFFF0;
    p->z[0] = 0xFFFFF0;
    p->v[3].w[3] = 0;
    p->v[3].w[2] = 0;
    p->v[2].w[3] = 0;
    p->v[2].w[2] = 0;
    p->v[1].w[3] = 0;
    p->v[1].w[2] = 0;
    p->v[0].w[3] = 0;
    p->v[0].w[2] = 0;
    p->v[3].w[1] = 0;
    p->v[3].w[0] = 0;
    p->v[2].w[1] = 0;
    p->v[2].w[0] = 0;
    p->v[1].w[1] = 0;
    p->v[1].w[0] = 0;
    p->v[0].w[1] = 0;
    p->v[0].w[0] = 0;
}
