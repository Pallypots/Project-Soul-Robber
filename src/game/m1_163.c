/* Area m1, file 163: link and light helpers (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Lk163 {
    uint8_t unk00[4]; void *cb4; uint8_t unk08[8]; float f10; uint8_t unk14[0x80]; void *p94; float f98;
    uint8_t unk9C[0x80]; void *p11C; void *o120;
} M1Lk163;
typedef struct M1Ob163 { uint8_t unk00[0x20]; void *m20; } M1Ob163;
typedef struct M1Ai163 { uint8_t unk00[0x14C]; M1Lk163 link14C; } M1Ai163;
void sub_001B2150(void *l);
void m1_LinkCb112D30(void);
int  m1_LinkAttach1B21D0(void *m, M1Lk163 *l);

/* 0x113E90: set up an actor's model link (callback, owner, optional parameter block) and attach it. */
void m1_AiLinkInit113E90(M1Ob163 *o, M1Ai163 *e, uint8_t *p) {
    M1Lk163 *l = &e->link14C; int volatile r;
    sub_001B2150(l);
    l->cb4 = (void *)m1_LinkCb112D30;
    l->o120 = o;
    l->f98 = 0.0f;
    l->f10 = 0.0f;
    if (p == 0) {
        l->p94 = 0; l->p11C = 0;
        r = m1_LinkAttach1B21D0(o->m20, l);
        return;
    }
    l->p94 = p; l->p11C = p + 4;
    r = m1_LinkAttach1B21D0(o->m20, l);
}

typedef struct M1Ck163 { uint8_t unk00[0x40]; struct { uint8_t unk00[0xC]; int32_t nC; } *x40; } M1Ck163;
typedef struct M1Lo163 { uint8_t unk00[0x84]; struct M1Lo163 *x84; uint8_t *x88; uint8_t unk8C[0x4C]; float fD8; } M1Lo163;
typedef struct M1Lt163 { uint8_t unk00[0x84]; void *x84; struct M1Lt163b *x88; int32_t type8C; uint8_t unk90[0x48]; float fD8; } M1Lt163;
typedef struct M1Lt163b { uint8_t unk00[0x84]; struct M1Lt163c *x84; } M1Lt163b;
typedef struct M1Lt163c { uint8_t unk00[0x84]; M1Lt163 *x84; } M1Lt163c;
typedef struct M1Ln163 { uint8_t unk00[0x28]; M1Lt163 *obj28; } M1Ln163;
extern M1Ck163 *m1_scene42C8E4;


void *sub_0007F300(void *n);
void *sub_0007F320(void *n);
int   sub_0008C940(void **out, void *n);
void  sub_0007F3F0(void *dst, void *sub);
void  sub_0007F430(void *dst, void *sub);
void  sub_0008BF70(void *t);

/* 0x8C9B0: build a tree node and its two children recursively; frees on error. */
int m1_TreeBuild08C9B0(void **out, void *node) {
    void *tmp, *l, *r; volatile int err; int e;
    err = 0;
    if (node == 0) return -1;
    tmp = 0;
    l = sub_0007F300(node);
    r = sub_0007F320(node);
    if ((e = sub_0008C940(out, node)) != 0) { err = e; goto done; }
    if (l != 0) {
        if ((e = m1_TreeBuild08C9B0(&tmp, l)) != 0) { err = e; goto done; }
        sub_0007F3F0(*out, tmp); tmp = 0;
    }
    if (r != 0) {
        if ((e = m1_TreeBuild08C9B0(&tmp, r)) != 0) { err = e; goto done; }
        sub_0007F430(*out, tmp); tmp = 0;
    }
done:
    sub_0008BF70(tmp);
    if (err != 0) { sub_0008BF70(*out); *out = 0; }
    return err;
}

int  sub_0008B010(void **out, void *n);
void sub_0008B400(void *t);
typedef int (*M1Add163)(void *dst, void *sub);

/* 0x8B480: second tree builder (checks the child attach results too); frees on error. */
int m1_TreeBuild2_08B480(void **out, void *node) {
    void *tmp, *l, *r; volatile int err; int e;
    err = 0;
    if (node == 0) return 0;
    tmp = 0;
    l = sub_0007F300(node);
    r = sub_0007F320(node);
    if ((e = sub_0008B010(out, node)) != 0) { err = e; goto done; }
    if (l != 0) {
        if ((e = m1_TreeBuild2_08B480(&tmp, l)) != 0) { err = e; goto done; }
        if (((M1Add163)sub_0007F3F0)(*out, tmp) == 0) { err = -1; goto done; }
        tmp = 0;
    }
    if (r != 0) {
        if ((e = m1_TreeBuild2_08B480(&tmp, r)) != 0) { err = e; goto done; }
        if (((M1Add163)sub_0007F430)(*out, tmp) == 0) { err = -1; goto done; }
        tmp = 0;
    }
done:
    sub_0008B400(tmp);
    if (err != 0) { sub_0008B400(*out); *out = 0; }
    return err;
}


typedef struct M1St163 { uint32_t f0; } M1St163;
typedef struct M1Ai163b { uint8_t unk00[0x74]; M1St163 *st74; } M1Ai163b;
int sub_00167200(void *o, M1Ai163b *e, int st);

/* 0x16ADA0: switch the boss to mode 7 or 9 depending on its phase flag. */
void m1_BossMode16ADA0(void *o, M1Ai163b *e) {
    int volatile r;
    if (e->st74->f0 & 0x100) r = sub_00167200(o, e, 7);
    else r = sub_00167200(o, e, 9);
}
