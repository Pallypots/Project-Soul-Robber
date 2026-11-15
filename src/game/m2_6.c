/* Area m2, file 6. Names inferred. */
#include <stdint.h>


typedef struct M2Hit6 { int32_t i0; struct M2Hit6 *next4; int32_t i8; int32_t idxC; float c10[4]; } M2Hit6;
typedef struct M2Node6 { uint8_t unk00[2]; uint16_t child2; uint16_t sib4; uint8_t unk06[2]; int32_t box8; uint8_t unk0C[4]; M2Hit6 hit; uint8_t unk30[0x20]; } M2Node6;
extern M2Node6 *r6c_p3ECA38;
extern uint8_t *r6c_src3ECA7C;
extern M2Hit6 *r6c_hits3ECA00;
extern M2Hit6 *r6c_v3ECA1C;
void  r4c_VecAdd(float *d, const float *a, const float *b);
void  r4c_Vec4Scale(float *d, const float *a, float s);
void  r4c_VecSub(float *d, const float *a, const float *b);
float rbi_VecLen82D70(const float *v);
void  sub_00080E20(int idx);

/* 0x80E20: walk node idx and its children/siblings; each node with a box gets its hit record (centre = middle of the box corners, radius = half diagonal + 0.01) appended to the hit list. */
void m2_HitTree80E20(int idx) {
    float t[4];
    for (;;) {
        M2Node6 *n = &r6c_p3ECA38[idx];
        if (n->box8 != 0) {
            M2Hit6 *h = &n->hit;
            float *c = h->c10;
            uint8_t *b;
            h->i0 = 0; h->next4 = 0; h->i8 = 0;
            c[0] = 0.0f; c[1] = 0.0f; c[2] = 0.0f; c[3] = 1.0f;
            h->idxC = idx;
            b = r6c_src3ECA7C + n->box8;
            r4c_VecAdd(t, (float *)(b + 0x20), (float *)(b + 0x10));
            r4c_Vec4Scale(c, t, 0.5f);
            r4c_VecSub(t, (float *)(b + 0x20), c);
            c[3] = rbi_VecLen82D70(t) + 0.01f;
            if (r6c_v3ECA1C != 0) r6c_v3ECA1C->next4 = h;
            else r6c_hits3ECA00 = h;
            r6c_v3ECA1C = h;
        }
        if (n->child2 != 0xFFFF) sub_00080E20(n->child2);
        if (n->sib4 == 0xFFFF) return;
        idx = n->sib4;
    }
}
