/* Area m2, file 7. Names inferred. */
#include <stdint.h>

extern float m2_bbMax3ECA80[4];
extern uint8_t *m2_bbNode3ECA90;
typedef struct M2BNode7 { uint8_t unk00[2]; uint16_t child2; uint16_t sib4; uint8_t unk06[2]; int32_t box8; uint8_t unk0C[4]; float local10[16]; } M2BNode7;
extern M2BNode7 *m2_bbSub3ECA94;
extern float m2_bbMin3ECA98[4];
void r4e_MatIdentity(float *m);
void sub_00083A30(int idx, float *m);
void a3c_VecCopy(float *d, const float *s);

/* 0x83B70: compute the bounding box of node n: start from an empty box (+-8388000), grow it over the node's parts (0x83A30 with an identity matrix), give every axis at least 0.01 of size, and copy the corners out. */
void m2_NodeBox83B70(float *outMax, float *outMin, uint8_t *n) {
    float m[16];
    m2_bbMax3ECA80[2] = -8388000.0f; m2_bbMax3ECA80[1] = -8388000.0f; m2_bbMax3ECA80[0] = -8388000.0f;
    m2_bbMax3ECA80[3] = 1.0f;
    m2_bbMin3ECA98[2] = 8388000.0f; m2_bbMin3ECA98[1] = 8388000.0f; m2_bbMin3ECA98[0] = 8388000.0f;
    m2_bbMin3ECA98[3] = 1.0f;
    m2_bbNode3ECA90 = n;
    m2_bbSub3ECA94 = (M2BNode7 *)(n + 0x20);
    r4e_MatIdentity(m);
    sub_00083A30(*(int *)(n + 0xC), m);
    if (0.01f > m2_bbMax3ECA80[0] - m2_bbMin3ECA98[0]) m2_bbMax3ECA80[0] = m2_bbMin3ECA98[0] + 0.01f;
    if (0.01f > m2_bbMax3ECA80[1] - m2_bbMin3ECA98[1]) m2_bbMax3ECA80[1] = m2_bbMin3ECA98[1] + 0.01f;
    if (0.01f > m2_bbMax3ECA80[2] - m2_bbMin3ECA98[2]) m2_bbMax3ECA80[2] = m2_bbMin3ECA98[2] + 0.01f;
    a3c_VecCopy(outMax, m2_bbMax3ECA80);
    a3c_VecCopy(outMin, m2_bbMin3ECA98);
}

void rbj_MatMul(float *d, const float *a, const float *b);
void rbj_VecTransform(float *d, const float *m, const float *v);

/* 0x83A30: grow the bounding box over node idx: chain its local matrix onto the parent's, transform its box corners and widen the min/max, then recurse into its child (with this matrix) and its sibling (with the parent's). */
void m2_NodeBoxGrow83A30(int idx, float *parent) {
    float lo[4], hi[4], m[16];
    M2BNode7 *n = &m2_bbSub3ECA94[idx];
    rbj_MatMul(m, parent, n->local10);
    if (n->box8 != 0) {
        uint8_t *b = m2_bbNode3ECA90 + n->box8;
        rbj_VecTransform(lo, m, (float *)(b + 0x10));
        rbj_VecTransform(hi, m, (float *)(b + 0x20));
        if (m2_bbMin3ECA98[0] > lo[0]) m2_bbMin3ECA98[0] = lo[0];
        if (m2_bbMin3ECA98[1] > lo[1]) m2_bbMin3ECA98[1] = lo[1];
        if (m2_bbMin3ECA98[2] > lo[2]) m2_bbMin3ECA98[2] = lo[2];
        if (hi[0] > m2_bbMax3ECA80[0]) m2_bbMax3ECA80[0] = hi[0];
        if (hi[1] > m2_bbMax3ECA80[1]) m2_bbMax3ECA80[1] = hi[1];
        if (hi[2] > m2_bbMax3ECA80[2]) m2_bbMax3ECA80[2] = hi[2];
    }
    if (n->child2 != 0xFFFF) sub_00083A30(n->child2, m);
    if (n->sib4 != 0xFFFF) sub_00083A30(n->sib4, parent);
}
