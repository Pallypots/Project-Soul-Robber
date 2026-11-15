/* Area m2, file 24: scene node setup. Names inferred. */
#include <stdint.h>

typedef struct M2NRec24 { float v0[4], v10[4], v20[4]; uint8_t unk30[4]; uint32_t key34; uint32_t flags38; int32_t a3C, a40, a44, a48, s4C, s50, s54; float f58; } M2NRec24;
typedef struct M2NDef24 { uint8_t unk00[8]; int32_t i8; int32_t boneC; M2NRec24 *rec10; } M2NDef24;
typedef struct M2NMdl24 { uint8_t unk00[0x8C]; int32_t kind8C; uint8_t unk90[0x34]; uint8_t *bonesC4; } M2NMdl24;
typedef struct M2NChild24 { uint8_t unk00[0x20]; M2NMdl24 *mdl20; } M2NChild24;
typedef struct M2Node24 { int32_t err0; uint32_t flags4; uint8_t unk08[0x18]; uint8_t emit20[0xCC]; uint32_t modeEC; } M2Node24;
extern uint8_t *r2d_ctx;
void  r1d_KeyDecode(uint32_t key, void *e, int *x, int *y);
M2Node24 *r1d_NodeSpawnKey(int x, int y, int id);
void  r4e_MatIdentity(float *m);
M2NChild24 *r1e_ObjChild(void *e, int id);
void  sub_00034F00(M2Node24 *o, M2NChild24 *c, int bone);
void  sub_00034F60(M2Node24 *o, void *ctx);
void  rbi_VecCross(float *d, const float *a, const float *b);
void  r4e_VecCross3(float *d, const float *a, const float *b);
void  aa0_Vec4Copy(float *d, const float *s);
void  a3c_VecCopy(float *d, const float *s);
void  rbi_MatCopy(float *d, const float *s);
void  rbi_MatLoad385D0(float *d, const float *s);
void  rbj_MatMul(float *d, const float *a, const float *b);
void  r1e_XfSetAxes(M2Node24 *o, float *a, float *b, float *c);
void  sub_001B6310(void *em, int a, int b, int c, int d);
void  r4b_EmitSetSetD0(void *em, int v);
void  r4b_EmitSetScale(void *em, int v);
void  r4b_EmitSetSetD8(void *em, int v);
void  sub_00034E60(M2Node24 *o, float v);
void  sub_00034E30(M2Node24 *o);
void  sub_00034E90(M2Node24 *o);
void  r1c_NodeChainRun(M2Node24 *o, int on);
void  sub_000338A0(M2Node24 *o);

/* 0x35000: create the scene node for entity e from definition d: spawn it at the decoded (or given, flag 4) cell, bind it to the entity's child model (following a bone, flag 1 of the record attaches it directly unless flag 1 is given; record flags 0x40/4 aim it along the bone, else copy the bone matrix), apply the record's local transform, emitter settings, draw mode and fade, then run its chain. Returns the node or 0. */
M2Node24 *m2_NodeSetup35000(void *e, M2NDef24 *d, int x, int y, uint8_t fl) {
    M2NRec24 *r = d->rec10;
    M2Node24 *o;
    float m[16], n[16];
    uint32_t f, mode;
    int a, b;
    if (fl & 4) { a = x; b = y; }
    else { int t1, t2; r1d_KeyDecode(r->key34, e, &t2, &t1); a = t2; b = t1; }
    o = r1d_NodeSpawnKey(a, b, r->key34 & 0xFFFF);
    if (o == 0) return 0;
    r4e_MatIdentity(m);
    if (r->flags38 & 8) o->flags4 |= 2;
    if (e != 0) {
        M2NChild24 *c = r1e_ObjChild(e, d->i8);
        uint8_t *bn;
        if (c == 0 || c->mdl20 == 0) goto tail;
        f = r->flags38;
        if ((f & 1) && !(fl & 1)) { sub_00034F00(o, c, d->boneC); goto tail; }
        if (!(fl & 2)) {
            switch (c->mdl20->kind8C) {
            case 1: bn = c->mdl20->bonesC4 + d->boneC * 0x108; break;
            case 9: bn = c->mdl20->bonesC4 + d->boneC * 0x180; break;
            default: goto attach;
            }
            if (bn == 0) goto attach;
            if (f & 0x40) {
                rbi_VecCross(m, m + 4, (float *)(bn + 0x60));
                rbi_VecCross(m + 8, m, m + 4);
                a3c_VecCopy(m + 12, (float *)(bn + 0x70));
            } else if (f & 4) {
                r4e_VecCross3(m, m + 4, (float *)(bn + 0x60));
                r4e_VecCross3(m + 8, m, m + 4);
                aa0_Vec4Copy(m + 12, (float *)(bn + 0x70));
            } else {
                rbi_MatCopy(m, (float *)(bn + 0x40));
            }
        }
    }
attach:
    sub_00034F60(o, r2d_ctx);
tail:
    a3c_VecCopy(n + 12, r->v20);
    a3c_VecCopy(n + 8, r->v0);
    a3c_VecCopy(n + 4, r->v10);
    rbi_MatLoad385D0(n, n);
    rbj_MatMul(m, m, n);
    r1e_XfSetAxes(o, m + 12, m + 8, m + 4);
    if (o->err0 == 0) {
        sub_001B6310(o->emit20, r->a3C, r->a40, r->a44, r->a48);
        if (o->err0 == 0) {
            r4b_EmitSetSetD0(o->emit20, r->s4C);
            if (o->err0 == 0) r4b_EmitSetScale(o->emit20, r->s50);
        }
    }
    f = r->flags38;
    if (f & 4) mode = 2;
    else mode = (f >> 3) & 8;
    if (o->err0 == 0) {
        o->modeEC = ((((f >> 1) & 8) | (f & 2)) >> 1) | mode;
        r4b_EmitSetSetD8(o->emit20, r->s54);
    }
    if (r->flags38 & 0x20) {
        if (r->f58 > 0.0f) sub_00034E60(o, r->f58);
        else sub_00034E30(o);
    } else sub_00034E90(o);
    r1c_NodeChainRun(o, ~(r->flags38 >> 7) & 1);
    sub_000338A0(o);
    return o;
}
