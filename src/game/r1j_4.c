/* Area r1j, group 4: quad packet writers 0x00012710 and 0x00012B50.
   Names inferred. */
#include "r1j.h"

/* store a 64-bit GS value as two little-endian words */
static void r1j_put64(uint32_t *p, uint64_t v)
{
    p[0] = (uint32_t)v;
    p[1] = (uint32_t)(v >> 32);
}

/* RGBAQ value of vertex v (Q = 1) */
#define R1J_RGBAQ(v) \
    (((((int64_t)(v)->c[3] | 0x100) << 8 | (int64_t)(v)->c[2]) << 8 \
      | (int64_t)(v)->c[1]) << 8 | (int64_t)(v)->c[0])
/* UV value of vertex v */
#define R1J_UV(v) \
    ((int64_t)(uint16_t)(v)->w[1] << 16 | (int64_t)(uint16_t)(v)->w[0])
/* XYZ2 value of vertex v at depth z */
#define R1J_XYZ(v, z) \
    ((((uint64_t)(z) << 16 | (int64_t)(uint16_t)(v)->w[3]) << 16) \
     | (int64_t)(uint16_t)(v)->w[2])

/* write the DMA packet of quad template s at p (shared body of the two
   writers; a macro because both copies are inline in the original);
   p is left at the end tag */
#define R1J_QUAD_PKT_BODY(p, s) do { \
    (p)[0] = 0x10000000; \
    (p)[1] = 0; \
    (p)[2] = 0; \
    (p)[3] = 0x11000000; \
    if ((s)->ent[0].id == 0x42) sub_001A69C0((s)->ent[0].lo, (s)->ent[0].hi); \
    sub_001A69C0((s)->ent[0].lo, (s)->ent[0].hi); \
    if ((s)->ent[1].id == 0x42) sub_001A69C0((s)->ent[1].lo, (s)->ent[1].hi); \
    if ((s)->ent[2].id == 0x42) sub_001A69C0((s)->ent[2].lo, (s)->ent[2].hi); \
    if ((s)->ent[6].id == 0x42) sub_001A69C0((s)->ent[6].lo, (s)->ent[6].hi); \
    if ((s)->ent[4].id == 0x42) sub_001A69C0((s)->ent[4].lo, (s)->ent[4].hi); \
    if ((s)->ent[5].id == 0x42) sub_001A69C0((s)->ent[5].lo, (s)->ent[5].hi); \
    if ((s)->ent[3].id == 0x42) sub_001A69C0((s)->ent[3].lo, (s)->ent[3].hi); \
    (p)[5] = 0; \
    (p)[6] = 0; \
    (p)[4] = 0x10000009; \
    (p)[7] = 0x50000009; \
    (p)[8] = r1j_gifTag2803F0[0]; \
    (p)[9] = r1j_gifTag2803F0[1]; \
    (p)[10] = r1j_gifTag2803F0[2]; \
    (p)[11] = 0; \
    (p)[13] = 0; \
    (p)[12] = 0x15C; \
    (p)[14] = (s)->texLo; \
    (p)[15] = (s)->texHi; \
    (p)[16] = r1j_gifTag280400[0]; \
    (p)[17] = r1j_gifTag280400[1]; \
    (p)[19] = 0; \
    (p)[18] = r1j_gifTag280400[2]; \
    r1j_put64((p) + 20, R1J_RGBAQ(&(s)->v[0])); \
    r1j_put64((p) + 22, R1J_UV(&(s)->v[0])); \
    r1j_put64((p) + 24, R1J_XYZ(&(s)->v[0], (s)->z[0])); \
    r1j_put64((p) + 26, R1J_RGBAQ(&(s)->v[1])); \
    r1j_put64((p) + 28, R1J_UV(&(s)->v[1])); \
    r1j_put64((p) + 30, R1J_XYZ(&(s)->v[1], (s)->z[1])); \
    r1j_put64((p) + 32, R1J_RGBAQ(&(s)->v[2])); \
    r1j_put64((p) + 34, R1J_UV(&(s)->v[2])); \
    r1j_put64((p) + 36, R1J_XYZ(&(s)->v[2], (s)->z[2])); \
    r1j_put64((p) + 38, R1J_RGBAQ(&(s)->v[3])); \
    r1j_put64((p) + 40, R1J_UV(&(s)->v[3])); \
    r1j_put64((p) + 42, R1J_XYZ(&(s)->v[3], (s)->z[3])); \
    (p)[44] = 0x70000000; \
    (p)[45] = 0; \
    (p)[46] = 0; \
    (p)[47] = 0; \
    (p) += 44; \
} while (0)

/* 0x00012710: write the DMA packet of quad template s at p: flush the
   texture registers of the entries that hold register 0x42 (entry 0 is
   flushed a second time unconditionally), GIF tags, PRIM 0x15C, TEX0 and
   four RGBAQ/UV/XYZ2 vertices, an end tag; then 0x001A7870(s). Returns the
   end tag. */
uint32_t *r1j_QuadPktA(uint32_t *p, const R1iQuadTpl *s)
{
    R1J_QUAD_PKT_BODY(p, s);
    sub_001A7870(s);
    return p;
}

/* 0x00012B50: the same packet as 0x00012710, then 0x001A7880(s). */
uint32_t *r1j_QuadPktB(uint32_t *p, const R1iQuadTpl *s)
{
    R1J_QUAD_PKT_BODY(p, s);
    sub_001A7880(s);
    return p;
}
