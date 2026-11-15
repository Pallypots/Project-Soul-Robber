/* Area m2, file 12. Names inferred. */
#include <stdint.h>

typedef struct M2Bone12 { uint8_t b[0x130]; } M2Bone12;
typedef struct M2Pose12 { uint8_t unk00[0xB8]; uint32_t flagsB8; } M2Pose12;
typedef struct M2Anim12 { int32_t id0; uint8_t unk04[4]; uint8_t flags8; uint8_t unk09[3]; void *motC; float speed10; uint8_t unk14[0xC]; struct M2Anim12 *next20; } M2Anim12;
typedef struct M2AnCtx12 { uint8_t unk00[8]; int32_t cur8; uint8_t unk0C[4]; M2Anim12 *list10; M2Pose12 *parts14; M2Bone12 *bones18; } M2AnCtx12;
int  r4b_Get8(void *mot);
void sub_001AEA00(M2Bone12 *bones, M2Pose12 *p, int n);
void m2_BoneBind1AEA00(M2Bone12 *bones, M2Pose12 *p, int n);
void *a5b_AllocCur(int size, int a, int tag);
void r4_NodeAttach(void *node, M2Pose12 *p);
void m1_AnimClip1AF640(M2Pose12 *p, void *clip);
void r4d_PartsClearMask(M2Pose12 *p, int m);
void r4d_PartsSetMask(M2Pose12 *p, int m);
void sub_001AEDD0(M2Pose12 *p, float speed);
void sub_00082F90(M2AnCtx12 *c, M2Anim12 *a);

/* 0x831A0: start animation id on the context: bind its bones (allocating a bone buffer of 0x130 bytes per bone when the context has none), attach the optional node, set the clip, loop mask 1 by its flag and speed, clear pose flag 2 and apply it. The id is remembered even when it is not found. */
void m2_AnimStart831A0(M2AnCtx12 *c, int id, void *node) {
    M2Anim12 *a = c->list10;
    if (a == 0) { c->cur8 = id; return; }
    for (; a != 0; a = a->next20)
        if (id == a->id0) break;
    if (a != 0 && a->motC != 0) {
        if (c->bones18 != 0) {
            sub_001AEA00(c->bones18, c->parts14, r4b_Get8(a->motC));
        } else {
            int n = r4b_Get8(a->motC);
            m2_BoneBind1AEA00(a5b_AllocCur(r4b_Get8(a->motC) * (int)sizeof(M2Bone12), 0, 0x35B), c->parts14, n);
        }
        if (node != 0) r4_NodeAttach(node, c->parts14);
        m1_AnimClip1AF640(c->parts14, a->motC);
        if (!(a->flags8 & 1)) r4d_PartsSetMask(c->parts14, 1);
        else r4d_PartsClearMask(c->parts14, 1);
        sub_001AEDD0(c->parts14, a->speed10 * 60.0f * 0.016666668f);
        c->parts14->flagsB8 &= ~2u;
        sub_00082F90(c, a);
    }
    c->cur8 = id;
}

typedef struct M2Hdr12 { int32_t kind0; int32_t i4; int32_t i8, iC; int32_t i10, i14; int32_t i18; } M2Hdr12;
extern uint8_t *m1_gfx283698;
extern uint8_t m2_g42C840[];
uint8_t *r1c_PoolTake(uint8_t *pool, int size);
void r4e_Node14Init(uint8_t *b);
void sub_001B61B0(uint8_t *b, uint8_t *dst);
void r4b_NodeInitType16(uint8_t *e);
void r4b_EmitHolderSetSet(uint8_t *e, uint8_t *b);
void a4c_ListAppend(void *list, void *node);

/* 0x33410: create a scene object of kind 0 (node with 8 emitter slots bound to the default table and an emitter holder) or kind 1 (identity transforms, unit scale, linked into the bank's object list). Returns its header (+0x10), or 0 when the pool is full. */
M2Hdr12 *m2_ObjCreate33410(int kind) {
    uint8_t *o = r1c_PoolTake(m1_gfx283698, 0xB40);
    M2Hdr12 *h;
    uint32_t i;
    if (o == 0) return 0;
    h = (M2Hdr12 *)(o + 0x10);
    h->kind0 = kind;
    h->i4 = 0; h->i8 = -1; h->iC = -1; h->i10 = 0; h->i14 = 0; h->i18 = -1;
    switch (kind) {
    case 0:
        r4e_Node14Init(o + 0x30);
        *(uint32_t *)(o + 0xE0) = 8;
        sub_001B61B0(o + 0x30, o + 0x10C);
        for (i = 0; i < *(uint32_t *)(o + 0xE0); i++)
            *(uint8_t **)(o + 0x1C8 + i * 0x12C) = m2_g42C840;
        r4b_NodeInitType16(o + 0xA6C);
        r4b_EmitHolderSetSet(o + 0xA6C, o + 0x30);
        break;
    case 1: {
        float *f = (float *)(o + 0x30);
        f[0] = 0.0f; f[1] = 0.0f; f[2] = 0.0f; f[3] = 1.0f;
        f[4] = 0.0f; f[5] = 0.0f; f[6] = 0.0f; f[7] = 1.0f;
        *(int32_t *)(o + 0x64) = -1;
        *(float *)(o + 0x68) = 0.0f; *(float *)(o + 0x6C) = 0.0f;
        *(int32_t *)(o + 0x70) = 1; *(int32_t *)(o + 0x74) = 1;
        *(float *)(o + 0x78) = 1.0f; *(float *)(o + 0x7C) = 1.0f; *(float *)(o + 0x80) = 1.0f;
        *(M2Hdr12 **)(o + 0xB3C) = h;
        a4c_ListAppend(m1_gfx283698 + 0x5844C, o + 0xB30);
        break;
    }
    }
    return h;
}
