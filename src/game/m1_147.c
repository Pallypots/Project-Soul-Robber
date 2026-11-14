/* Area m1, file 147: node transform helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Obj147 { uint8_t unk00[0x20]; void *m20; uint8_t unk24[0x3C]; float pos60[4]; } M1Obj147;
typedef struct M1Nd147 {
    uint32_t flags0; uint8_t unk04[0xC]; float s10; uint8_t unk14[0x2C]; float v40[4];
    uint8_t unk50[4]; float rot54; uint8_t unk58[0x28]; float s80; float s84; float s88;
    uint8_t unk8C[0xD8 - 0x8C]; M1Obj147 *objD8;
} M1Nd147;
void sub_000F5D40(float *d, const void *s);
void sub_001AD940(float (*m)[4]);
void sub_001AD8E0(float (*d)[4], float (*s)[4], float a);
void sub_001ADBA0(float *d, const float *s, float k);
void sub_001ADA40(void *d, float (*m)[4]);

/* 0xA7830: rebuild a node's object matrix from its yaw, per-axis scale and position. */
void m1_NodeXform0A7830(M1Nd147 *n) {
    float m[4][4]; M1Obj147 *o = n->objD8; void *dst = o->m20;
    sub_000F5D40(o->pos60, n->v40);
    n->v40[3] = 1.0f;
    o->pos60[3] = 1.0f;
    if (!(n->flags0 & 0x20000000)) { n->s88 = n->s10; n->s84 = n->s10; n->s80 = n->s10; }
    sub_001AD940(m);
    sub_001AD8E0(m, m, 0.0f - n->rot54);
    sub_001ADBA0(m[0], m[0], n->s80);
    sub_001ADBA0(m[1], m[1], n->s84);
    sub_001ADBA0(m[2], m[2], n->s88);
    sub_000F5D40(m[3], o->pos60);
    sub_001ADA40(dst, m);
}

typedef struct M1Tri147 { struct M1Tri147 *link0; struct M1Tri147 *next4; } M1Tri147;
typedef struct M1Grp147 { uint8_t unk00[4]; struct M1Grp147 *next4; M1Tri147 *first8; } M1Grp147;
typedef struct M1Box147 { int32_t a0; int32_t a4; M1Tri147 *first8; int32_t aC; float v10[4]; float v20[4]; float v30[4]; uint8_t v40[4]; } M1Box147;
typedef struct M1Tree147 { struct M1Box147 *box0; M1Grp147 *list4; uint8_t unk08[8]; float lo10[4]; float hi20[4]; } M1Tree147;
extern int32_t m1_bvhDirty3EC9FC;
int  m1_BvhSplit0812B0(void *v, M1Box147 *b);
void m1_BvhFinish081930(M1Box147 *b);

/* 0x81A20: build the root box of a collision tree and chain all triangles into one list. */
int m1_BvhBuild081A20(M1Tree147 *t, M1Box147 *b) {
    M1Grp147 *g; M1Tri147 *e, *prev; int r; float *p, *q;
    if (t->list4 == 0) return 0;
    t->box0 = b;
    b->aC = 0; b->a0 = 0; b->a4 = 0; b->first8 = 0;
    b->v10[0] = 0.0f; b->v10[1] = 0.0f; b->v10[2] = 0.0f; b->v10[3] = 1.0f;
    p = b->v30; p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    q = b->v20; q[0] = 0.0f; q[1] = 0.0f; q[2] = 0.0f; q[3] = 1.0f;
    sub_000F5D40(p, t->lo10);
    sub_000F5D40(q, t->hi20);
    m1_bvhDirty3EC9FC = 1;
    for (prev = 0, g = t->list4; g != 0; g = g->next4) {
        e = g->first8;
        if (prev != 0) prev->link0 = e;
        while (e->next4 != 0) { e->link0 = e->next4; e = e->next4; }
        prev = e;
    }
    b->first8 = t->list4->first8;
    r = m1_BvhSplit0812B0(b->v40, b);
    m1_BvhFinish081930(b);
    return r;
}

typedef struct M1Ob147 { uint8_t unk00[8]; int32_t kind08; uint32_t fC; uint32_t f10; } M1Ob147;
typedef struct M1Pl147 { uint8_t unk00[0x98]; M1Ob147 *o98; uint8_t unk9C[0xF8 - 0x9C]; void *xF8; uint8_t unkFC[0x1A8 - 0xFC]; M1Ob147 *x1A8; } M1Pl147;
M1Pl147 *sub_00100110(void);
M1Pl147 *sub_000FBAF0(void);
M1Pl147 *sub_000FE3D0(void);
void sub_00033B30(M1Ob147 *o);
void sub_000ED780(M1Ob147 *o);
void sub_0001EB80(M1Ob147 *o);
void sub_000F69E0(M1Pl147 *p);
int  sub_0001D960(M1Ob147 *o, int k);
void sub_0001D910(M1Ob147 *o, int h);

/* 0xF6C90: detach an object from the player and hide it. */
int m1_ObjDetach0F6C90(M1Ob147 *o) {
    M1Pl147 *p; int a, b;
    if (o == 0) for (;;) ;
    if (!(o->fC & 1)) return 0;
    if (o->kind08 == 3) p = sub_000FE3D0();
    else if (o->kind08 == 4) p = sub_00100110();
    else if (o->kind08 == 5) p = sub_000FBAF0();
    else p = sub_000FE3D0();
    sub_00033B30(o);
    if (o->kind08 == 3 && p->x1A8 != 0) {
        if (p->x1A8->fC & 1) sub_000ED780(p->x1A8);
        p->x1A8 = 0;
    }
    if (p->xF8 != 0) {
        p->o98->f10 |= 0xD; p->o98->fC &= ~1u;
        sub_0001EB80(p->o98);
    }
    sub_000F69E0(p);
    o->f10 |= 0xD; o->fC &= ~1u;
    sub_0001EB80(o);
    a = sub_0001D960(o, 5);
    b = sub_0001D960(o, 0xD);
    sub_0001D910(o, a);
    sub_0001D910(o, b);
    return 1;
}

typedef struct M1Ac147 {
    uint8_t unk00[0xD4]; int32_t d4; uint8_t unkD8[0xEC - 0xD8]; uint32_t ec;
    uint8_t unkF0[0x150 - 0xF0]; uint32_t flags150; uint8_t unk154[0x1B8 - 0x154]; int32_t mode1B8;
    uint8_t unk1BC[0xD7C - 0x1BC]; int32_t slotD7C[4]; int32_t idxD8C;
} M1Ac147;
extern uint32_t m1_btnA41CD00;
extern uint32_t m1_btnB41CD04;
int  m1_ActCanAct0CC970(M1Ac147 *o);
void sub_000BD4D0(M1Ac147 *o, int st);
void m1_SndBank0243B0(int a, int b);
void m1_SndPlay023D80(int a, int b);
void sub_00048AF0(int k);

/* 0xCCF60: handle the special-move and weapon-cycle buttons. */
int m1_ActButtons0CCF60(M1Ac147 *o, uint32_t btn) {
    int i, old, n;
    if (o->ec == 0 && !(o->flags150 & 1) && (m1_btnA41CD00 & btn) && m1_ActCanAct0CC970(o) >= 0) {
        o->ec |= 4; o->flags150 |= 0x800;
        sub_000BD4D0(o, 0x24);
        return 1;
    }
    if (!(o->ec & 0x40) && (m1_btnB41CD04 & btn)) {
        if (o->d4 == 0) { m1_SndBank0243B0(1, o->mode1B8); m1_SndPlay023D80(1, 0x78); }
        i = o->idxD8C; old = i;
        for (n = 0; ; ) {
            i++;
            o->idxD8C = i;
            if (i > 3) o->idxD8C = 0;
            i = o->idxD8C;
            if (o->slotD7C[i] >= 0) break;
            if (++n >= 4) break;
        }
        if (old != i) { m1_SndBank0243B0(2, 0); sub_00048AF0(0); }
    }
    return -1;
}

