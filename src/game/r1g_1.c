/* Area r1g, group 1: immediate-mode primitives 0x00013CA0..0x00014940. Names inferred. */
#include "r1g.h"

/* 0x00013CA0: draw a textured sprite (four corners, flat colour).
   regargs: s=ESI. Returns s->next. */
int r1g_DrawTexSpr(const R1gTexSpr *s)
{
    uint64_t *p = sub_000134E0();
    p[1] = ((((uint64_t)s->b | 0x18000) << 8 | s->g) << 8) | s->r;
    p[2] = (uint64_t)s->texHi << 32 | s->texLo;
    p[4] = (((uint64_t)s->z[0] << 16 | s->c[0].y) << 16) | s->c[0].x;
    p[3] = (uint64_t)s->c[0].v << 16 | s->c[0].u;
    p[6] = (((uint64_t)s->z[1] << 16 | s->c[1].y) << 16) | s->c[1].x;
    p[5] = (uint64_t)s->c[1].v << 16 | s->c[1].u;
    p[8] = (((uint64_t)s->z[2] << 16 | s->c[2].y) << 16) | s->c[2].x;
    p[7] = (uint64_t)s->c[2].v << 16 | s->c[2].u;
    p[10] = (((uint64_t)s->z[3] << 16 | s->c[3].y) << 16) | s->c[3].x;
    p[9] = (uint64_t)s->c[3].v << 16 | s->c[3].u;
    r1b_PktSubmit();
    return s->next;
}

/* 0x00013E30: draw a textured quad with per-vertex colours.
   regargs: q=ESI. Returns q->next. */
int r1g_DrawTexQuad(const R1gTexQuad *q)
{
    uint64_t *p = sub_00013990();
    int i;
    p[1] = (uint64_t)q->texHi << 32 | q->texLo;
    for (i = 0; i < 4; i++) {
        const R1gTexQuadV *v = &q->v[i];
        p[2 + 3 * i] = (((((uint64_t)v->a | 0x100) << 8 | v->b) << 8 | v->g) << 8) | v->r;
        p[4 + 3 * i] = (((uint64_t)q->z[i] << 16 | v->y) << 16) | v->x;
        p[3 + 3 * i] = (uint64_t)v->v << 16 | v->u;
    }
    r1b_PktSubmit();
    return q->next;
}

/* 0x00014380: draw a gouraud-shaded triangle.
   regargs: t=ESI. Returns t->next. */
int r1g_DrawTri(const R1gTri *t)
{
    uint64_t *p = sub_00013640();
    int i;
    for (i = 0; i < 3; i++) {
        p[1 + 2 * i] = (((((uint64_t)t->c[i][3] | 0x100) << 8 | t->c[i][2]) << 8 | t->c[i][1]) << 8) | t->c[i][0];
        p[2 + 2 * i] = (((uint64_t)t->z[i] << 16 | t->xy[i][1]) << 16) | t->xy[i][0];
    }
    r1b_PktSubmit();
    return t->next;
}

/* 0x00014940: clear the whole 512x224 screen to colour (r,g,b,a) with a
   one-off packet sent straight to the device. */
void r1g_ClearScreen(int r, int g, int b, int a)
{
    R1gPkt pkt;
    r1b_dev37B4A4 = sub_001A1FD0(2);
    r1b_PktOp(&pkt, (uint32_t)(uintptr_t)r1g_buf37B2A0 | 0x20000000);
    r1b_PktOp(&pkt);
    r1b_PktOp(&pkt, 0x800A, 0x10000000);
    r1b_PktOp(&pkt, 0xE, 0);
    r1b_PktOp(&pkt, 1, 0);
    r1b_PktOp(&pkt, 0x1A, 0);
    r1b_PktOp(&pkt, 0x100000, 0);
    r1b_PktOp(&pkt, 0x4C, 0);
    r1b_PktOp(&pkt, (uint64_t)(sub_001BB240(0, 0x200, 0xE0) | 0x31000000) | 0x100000000ull);
    r1b_PktOp(&pkt, 0x4E, 0);
    r1b_PktOp(&pkt, 0, 0);
    r1b_PktOp(&pkt, 0x18, 0);
    r1b_PktOp(&pkt, 0x4000000, 0x4000000);
    r1b_PktOp(&pkt, 0x40, 0);
    r1b_PktOp(&pkt, 0x30000, 0);
    r1b_PktOp(&pkt, 0x47, 0);
    r1b_PktOp(&pkt, 6, 0);
    r1b_PktOp(&pkt, 0, 0);
    r1b_PktOp(&pkt, ((((((uint64_t)(uint8_t)a | 0x3F80000000ull) << 8) | (uint8_t)b) << 8 | (uint8_t)g) << 8) | (uint8_t)r);
    r1b_PktOp(&pkt, 1, 0);
    r1b_PktOp(&pkt, 0, 0);
    r1b_PktOp(&pkt, 4, 0);
    r1b_PktOp(&pkt, 0x40004000, 0);
    r1b_PktOp(&pkt, 4, 0);
    sub_000AD090(&pkt);
    sub_001A2020(r1b_dev37B4A4, pkt.tag & 0x0FFFFFFF, sub_000AD090(&pkt));
    sub_000AD090(0, 0);
}

/* 0x000144F0: draw a diamond as a triangle fan: centre (x,y) in colour c0,
   the four points (x-w/2,y) (x,y-h/2) (x+w/2,y) (x,y+h/2) in colour c1, and
   the first point again to close it. regargs: d=ESI. Returns d->next. */
int r1g_DrawDiamond(const R1gDiamond *d)
{
    unsigned int x = d->x;
    unsigned int hw = d->w >> 1;
    unsigned int hh = d->h >> 1;
    unsigned int y = d->y;
    int z = d->z;
    uint8_t b0 = d->c1[0], b1 = d->c1[1], b2 = d->c1[2];
    uint64_t *p = sub_000136F0();
    uint64_t zy, edge;
    p[1] = (((((uint64_t)d->c0[3] | 0x100) << 8 | d->c0[2]) << 8 | d->c0[1]) << 8) | d->c0[0];
    zy = ((uint64_t)(int64_t)z << 16 | (int64_t)(int)y) << 16;
    p[2] = zy | (int64_t)(int)x;
    edge = ((((int64_t)(int)(b2 | 0x10000)) << 8 | (int64_t)(int)b1) << 8) | (int64_t)(int)b0;
    p[3] = edge;
    p[4] = zy | (int64_t)(int)(x - hw);
    p[5] = edge;
    p[6] = (((uint64_t)(int64_t)z << 16 | (int64_t)(int)(y - hh)) << 16) | (int64_t)(int)x;
    p[7] = edge;
    p[8] = zy | (int64_t)(int)(x + hw);
    p[9] = edge;
    p[10] = (((uint64_t)(int64_t)z << 16 | (int64_t)(int)(y + hh)) << 16) | (int64_t)(int)x;
    p[11] = p[3];
    p[12] = p[4];
    r1b_PktSubmit();
    return d->next;
}

#define R1G_RGBAQ(r, g, b, a) \
    (((((uint64_t)(int64_t)(int)((a) | 0x100) << 8 | (uint64_t)(int64_t)(int)(b)) << 8 \
       | (uint64_t)(int64_t)(int)(g)) << 8) | (uint64_t)(int64_t)(int)(r))
#define R1G_XYZ(pt) \
    ((((uint64_t)(pt)->z << 16 | (pt)->y) << 16) | (pt)->x)

/* 0x000146D0: draw a line strip with a colour gradient from c0 to c1,
   starting at point m % n of a ring of n points and walking backwards.
   Nothing is drawn unless n >= 2 and m >= 2. Returns s->next. */
int r1g_DrawGradStrip(const R1gStrip *s)
{
    int n = s->n;
    int m = s->m;
    if (n >= 2 && m >= 2) {
        uint64_t *p;
        const R1gPt *pt;
        int k, dr, dg, db, da, r, g, b, a, j, i;
        sub_000137A0();
        r1b_PktSubmit();
        p = sub_00013850();
        pt = &s->pts[m % n];
        p[0] = R1G_RGBAQ(s->c0[0], s->c0[1], s->c0[2], s->c0[3]);
        p[1] = R1G_XYZ(pt);
        r1b_PktSubmit();
        k = (n < m) ? n - 1 : m - 1;
        dr = (s->c0[0] - s->c1[0]) / k;
        dg = (s->c0[1] - s->c1[1]) / k;
        db = (s->c0[2] - s->c1[2]) / k;
        da = (s->c0[3] - s->c1[3]) / k;
        i = k - 1;
        if (i >= 0) {
            r = i * dr + s->c1[0];
            g = i * dg + s->c1[1];
            b = i * db + s->c1[2];
            a = i * da + s->c1[3];
            j = n + m - 1;
            i = k;
            do {
                pt = &s->pts[j % n];
                p = sub_00013850();
                p[0] = R1G_RGBAQ(r, g, b, a);
                p[1] = R1G_XYZ(pt);
                r1b_PktSubmit();
                a -= da;
                b -= db;
                g -= dg;
                r -= dr;
                j--;
            } while (--i);
        }
    }
    return s->next;
}
