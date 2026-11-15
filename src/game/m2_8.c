/* Area m2, file 8. Names inferred. */
#include <stdint.h>

extern int a60_v3E83E4, a60_v3E7A50, a60_v3E7A54, a60_v3E83E8;
extern uint8_t a60_anim3E7A58[];
extern int r6d_msgTables26F32C[];
int  sub_001A8A90(void);
void sub_00048A60(void);
void sub_00048110(int v);
void sub_00048370(void);
int  sub_000529F0(int k, int a, float b, float c);
int  a5b_GetVideoMode(int k, int a, float b, float c);
int  m2_Pick0529F0(int k, int a, float b, float c);
int  r6d_MsgGet(int id);
void sub_0003FCB0(void *anim, int msg);
int  rtc_ItemTextDraw(int a, void *anim);
void r1c_QueueKick(int v);
void sub_000481B0(int v);
void sub_000483A0(int v);

/* 0x79480: pick the active prompt (by the 0x3E83E4 sign); when there is one and 0x1A8A90 allows it, start the prompt sound once, load message 1..3 into the prompt animation and draw it (returns the draw result); otherwise stop the sound once and return a unchanged. */
int m2_Prompt79480(int a) {
    int m = a60_v3E7A50;
    if (a60_v3E83E4 <= 0) m = a60_v3E7A54;
    if (m != 0 && sub_001A8A90() == 0) {
        if (a60_v3E83E8 == 0) {
            sub_00048A60();
            sub_00048110(10);
            sub_00048370();
            a60_v3E83E8 = 1;
        }
        switch (m) {
        case 1: sub_0003FCB0(a60_anim3E7A58, r6d_MsgGet(r6d_msgTables26F32C[sub_000529F0(0, 0, 1.0f, -1.0f)])); break;
        case 2: sub_0003FCB0(a60_anim3E7A58, r6d_MsgGet(r6d_msgTables26F32C[a5b_GetVideoMode(1, 0, 1.0f, -1.0f)])); break;
        case 3: sub_0003FCB0(a60_anim3E7A58, r6d_MsgGet(r6d_msgTables26F32C[m2_Pick0529F0(2, 0, 1.0f, -1.0f)])); break;
        }
        return rtc_ItemTextDraw(a, a60_anim3E7A58);
    }
    if (a60_v3E83E8 != 0) {
        r1c_QueueKick(1000);
        sub_000481B0(100);
        sub_000483A0(100);
        a60_v3E83E8 = 0;
    }
    return a;
}

typedef struct M2Bvh8 { struct M2Bvh8 *child0, *next4; void *leaf8; uint8_t unk0C[4]; float c10[3]; float r1C; } M2Bvh8;
extern float m1_bvhMat3EC8F8[16];
extern float m1_bvhF3ECA2C;
extern float m1_bvhScaleA3ECA34;
extern float m1_bvhScaleB3ECA50;
void a3c_VecCopy(float *d, const float *s);
void rbj_VecTransform(float *d, const float *m, const float *v);
void sub_00081B90(void *leaf);
void m1_BvhWalk081D50(M2Bvh8 *n);

/* 0x81D50: walk the bounding-sphere tree: a node whose sphere (centre moved into view space) lies in front of the near plane, before the far distance and inside the view cone sides draws its leaf and descends to its children; siblings are always walked. */
void m2_BvhWalk81D50(M2Bvh8 *n) {
    float p[4];
    a3c_VecCopy(p, n->c10);
    p[3] = 1.0f;
    rbj_VecTransform(p, m1_bvhMat3EC8F8, p);
    if (p[2] + n->r1C > 0.0f && m1_bvhF3ECA2C > p[2] - n->r1C) {
        float d = p[2] + n->r1C;
        float sy = m1_bvhScaleB3ECA50 * d;
        float sx = m1_bvhScaleA3ECA34 * d;
        if (0.0f > (0.0f - sy - (p[0] + n->r1C)) * (sy - (p[0] - n->r1C)) &&
            0.0f > (0.0f - sx - (p[1] + n->r1C)) * (sx - (p[1] - n->r1C))) {
            if (n->leaf8 != 0) sub_00081B90(n->leaf8);
            if (n->child0 != 0) m1_BvhWalk081D50(n->child0);
        }
    }
    if (n->next4 != 0) m1_BvhWalk081D50(n->next4);
}

typedef struct M2Draw8 { uint8_t unk00[0x84]; int32_t i84, i88; uint8_t unk8C[8]; float depth94; uint8_t unk98[0x30]; int32_t lodC8; uint8_t unkCC[0x34]; } M2Draw8;
typedef struct M2Mdl8 { uint8_t unk00[0xC4]; M2Draw8 *drawC4; } M2Mdl8;
typedef struct M2Obj8 { uint8_t unk00[0x14]; uint32_t flags14; float far18; M2Mdl8 *mdl1C; int32_t lod20; int32_t lodNear24; } M2Obj8;
typedef struct M2Leaf8 { struct M2Leaf8 *next0; uint8_t unk04[4]; M2Obj8 *obj8; int32_t idxC; float c10[3]; float r1C; } M2Leaf8;
extern float r4j_depthMax377F48;
extern float r4j_depthMin40F1C4;
void sub_00082720(M2Mdl8 *m, M2Draw8 *d);

/* 0x81B90: for each leaf in the list whose object is visible (not flagged 0x12) and whose sphere is inside the view (near, far, cone sides, object far distance): reset its draw record, set its depth (forced max/min by flags 4/8, else the view z), pick the near model within 50 units (when it has one) and queue it. */
void m2_LeafDraw81B90(M2Leaf8 *l) {
    float p[4];
    float zf, zn;
    M2Obj8 *o = l->obj8;
    if (!(o->flags14 & 0x12)) {
        a3c_VecCopy(p, l->c10);
        p[3] = 1.0f;
        rbj_VecTransform(p, m1_bvhMat3EC8F8, p);
        zf = l->r1C + p[2];
        zn = p[2] - l->r1C;
        if (zf > 0.0f && m1_bvhF3ECA2C > zn) {
            float xn = p[0] - l->r1C, yn = p[1] - l->r1C;
            float xf = l->r1C + p[0], yf = l->r1C + p[1];
            float sy = m1_bvhScaleB3ECA50 * zf;
            float sx = m1_bvhScaleA3ECA34 * zf;
            if (0.0f > (0.0f - sy - xf) * (sy - xn) &&
                0.0f > (0.0f - sx - yf) * (sx - yn) &&
                o->far18 > zn) {
                M2Draw8 *d = (M2Draw8 *)((uint8_t *)o->mdl1C->drawC4 + (l->idxC << 8));
                d->i88 = 0; d->i84 = 0;
                if (o->flags14 & 4) d->depth94 = r4j_depthMax377F48;
                else if (o->flags14 & 8) d->depth94 = r4j_depthMin40F1C4;
                else d->depth94 = p[2];
                if (o->lodNear24 != 0 && 50.0f > zn - l->r1C * 0.5f) d->lodC8 = o->lodNear24;
                else d->lodC8 = o->lod20;
                sub_00082720(o->mdl1C, d);
            }
        }
    }
    if (l->next0 != 0) sub_00081B90(l->next0);
}
