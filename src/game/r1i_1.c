/* Area r1i, group 1: GS packet builders 0x00012360..0x000125A0.
   Names inferred. */
#include "r1i.h"

/* store a 64-bit GS value as two little-endian words */
static void r1i_put64(uint32_t *p, uint64_t v)
{
    p[0] = (uint32_t)v;
    p[1] = (uint32_t)(v >> 32);
}

/* 0x00012360: write the DMA packet of sprite template s at p: flush the
   texture registers of the entries that hold register 0x42, then a GIF
   tag, the PRIM (0x156), RGBAQ (Q=1), TEX0 and two UV/XYZ2 pairs, and an
   end tag. Returns the end tag (next write position). */
uint32_t *r1i_SprPkt(uint32_t *p, const R1iSpr *s)
{
    uint64_t v;
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x11000000;
    if (s->ent[0].id == 0x42) sub_001A69C0(s->ent[0].lo, s->ent[0].hi);
    if (s->ent[1].id == 0x42) sub_001A69C0(s->ent[1].lo, s->ent[1].hi);
    if (s->ent[2].id == 0x42) sub_001A69C0(s->ent[2].lo, s->ent[2].hi);
    if (s->ent[6].id == 0x42) sub_001A69C0(s->ent[6].lo, s->ent[6].hi);
    if (s->ent[4].id == 0x42) sub_001A69C0(s->ent[4].lo, s->ent[4].hi);
    if (s->ent[5].id == 0x42) sub_001A69C0(s->ent[5].lo, s->ent[5].hi);
    if (s->ent[3].id == 0x42) sub_001A69C0(s->ent[3].lo, s->ent[3].hi);
    p[5] = 0;
    p[6] = 0;
    p[4] = 0x10000005;
    p[7] = 0x50000005;
    p[8] = r1i_gifTag2803C0[0];
    p[9] = r1i_gifTag2803C0[1];
    p[10] = r1i_gifTag2803C0[2];
    p[11] = 0;
    p[13] = 0;
    p[12] = 0x156;
    v = ((((int64_t)s->a | 0x100) << 8 | (int64_t)s->b) << 8 | (int64_t)s->g) << 8 | (int64_t)s->r;
    r1i_put64(p + 14, v);
    p[16] = s->texLo;
    p[17] = s->texHi;
    r1i_put64(p + 18, (int64_t)s->xy[1] << 16 | (int64_t)s->xy[0]);
    r1i_put64(p + 20, (((uint64_t)s->z << 16 | (int64_t)s->xy[3]) << 16) | (int64_t)s->xy[2]);
    r1i_put64(p + 22, (int64_t)s->xy[5] << 16 | (int64_t)s->xy[4]);
    r1i_put64(p + 24, (((uint64_t)s->z << 16 | (int64_t)s->xy[7]) << 16) | (int64_t)s->xy[6]);
    p[26] = 0;
    p[27] = 0;
    p[29] = 0;
    p[30] = 0;
    p[31] = 0;
    p[28] = 0x70000000;
    return p + 28;
}

/* 0x000125A0: write the DMA packet of rectangle s at p: flush the texture
   registers of entries 0 and 1 when they hold register 0x42, then a GIF
   tag, PRIM 0x4E, RGBAQ (Q=1) and two XYZ2 corners (x, y) and
   (x + w, y + h / 2), and an end tag. Returns the end tag. */
uint32_t *r1i_RectPkt(uint32_t *p, const R1iStPkt *s)
{
    uint64_t v;
    p[0] = 0x10000000;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0x11000000;
    if (s->ent[0].id == 0x42) sub_001A69C0(s->ent[0].lo, s->ent[0].hi);
    if (s->ent[1].id == 0x42) sub_001A69C0(s->ent[1].lo, s->ent[1].hi);
    p[5] = 0;
    p[6] = 0;
    p[4] = 0x10000003;
    p[7] = 0x50000003;
    p[8] = r1i_gifTag2803E0[0];
    p[9] = r1i_gifTag2803E0[1];
    p[10] = r1i_gifTag2803E0[2];
    p[11] = 0;
    p[13] = 0;
    p[12] = 0x4E;
    v = ((((int64_t)s->a | 0x100) << 8 | (int64_t)s->b) << 8 | (int64_t)s->g) << 8 | (int64_t)s->r;
    r1i_put64(p + 14, v);
    r1i_put64(p + 16, (((uint64_t)s->z << 16 | (int64_t)s->y) << 16) | (int64_t)s->x);
    r1i_put64(p + 18, (((uint64_t)s->z << 16 | (int64_t)(s->y + s->h / 2)) << 16)
                      | (int64_t)(s->w + s->x));
    p[21] = 0;
    p[22] = 0;
    p[23] = 0;
    p[20] = 0x70000000;
    return p + 20;
}
