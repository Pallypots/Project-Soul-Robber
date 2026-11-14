/* Area m1, file 168: range-check revisits. Names inferred. */
#include <stdint.h>

typedef struct M1Mdl168 { uint8_t unk00[0x18]; uint8_t *bones; } M1Mdl168;
typedef struct M1Kind168 { uint8_t unk00[8]; int32_t kind08; uint8_t unk0C[0x30 - 0xC]; M1Mdl168 *mdl30; } M1Kind168;
typedef struct M1Room168 { uint8_t unk00[0x120]; M1Kind168 *k120; uint8_t unk124[0x12C - 0x124]; uint8_t *ents[8]; } M1Room168;
void sub_000A21C0(M1Room168 *r, void *out);
void sub_000F5D40(float *d, const void *s);

/* 0xA24C0: copy the room anchor and the head bone into each room entity. */
void m1_RoomPose0A24C0(M1Room168 *r) {
    struct { uint8_t *p; float a[4]; float b[4]; } l;
    uint8_t **pe; int i; volatile int j; volatile int k;
    l.p = 0;
    l.b[0] = 0.0f; l.b[1] = 0.0f; l.b[2] = 0.0f; l.b[3] = 1.0f;
    l.a[0] = 0.0f; l.a[1] = 0.0f; l.a[2] = 0.0f; l.a[3] = 1.0f;
    sub_000A21C0(r, &l.p);
    k = r->k120->kind08;
    if (k >= 0x1B && k <= 0x1C) j = 3; else j = 0;
    sub_000F5D40(l.b, r->k120->mdl30->bones + j * 0x130 + 0x20);
    sub_000F5D40(l.a, l.p + 0x70);
    pe = r->ents;
    for (i = 8; i != 0; i--, pe++)
        if (*pe != 0) sub_000F5D40((float *)(*pe + 0x60), l.a);
}

typedef struct M1Cl168 { uint8_t unk00[0xC]; void *xC; } M1Cl168;
typedef struct M1An168 { uint8_t unk00[8]; int32_t x8; uint8_t unk0C[8]; void *x14; } M1An168;
typedef struct M1Ch168 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[0x28]; M1An168 *anim30; uint8_t unk34[8]; struct M1Ch168 *next3C; } M1Ch168;
M1Cl168 *sub_00083120(M1An168 *a, int id);
void m1_AnimClip1AF640(void *p, void *clip);
void sub_001AEF10(void *p, int k);
void sub_001AEED0(void *p, int k);
void sub_001AEDD0(void *p, int k);

#define M1_RESTART168(n) do { M1An168 *a_ = (n)->anim30; M1Cl168 *c_ = sub_00083120(a_, a_->x8); \
    if (c_ != 0 && c_->xC != 0) { m1_AnimClip1AF640(a_->x14, c_->xC); sub_001AEF10(a_->x14, 2); \
    sub_001AEED0(a_->x14, 4); sub_001AEDD0(a_->x14, 0); } } while (0)

/* 0x5AA20: restart an object's animation; chain kinds (12..13) restart every linked piece too. */
void m1_AnimRestart05AA20(M1Ch168 *o) {
    int chain; volatile int k;
    if (o == 0) chain = 0;
    else { k = o->kind4; chain = (k >= 12 && k <= 13) ? 1 : 0; }
    M1_RESTART168(o);
    if (chain == 0) return;
    for (o = o->next3C; o != 0; o = o->next3C) M1_RESTART168(o);
}

void m1_AnimSpeed1B1190(void *p, int k);
void sub_000832D0(void *a, int id);

#define M1_RESPEED168(n, sp) do { M1An168 *a_ = (n)->anim30; M1Cl168 *c_ = sub_00083120(a_, a_->x8); \
    if (c_ != 0 && c_->xC != 0) { m1_AnimClip1AF640(a_->x14, c_->xC); m1_AnimSpeed1B1190(a_->x14, sp); } } while (0)

/* 0x5ABD0: restart an object's animation at a given speed; chain kinds (12..13) do every linked piece. */
void m1_AnimRestartAt05ABD0(M1Ch168 *o, int sp) {
    int chain; volatile int k;
    if (o == 0) chain = 0;
    else { k = o->kind4; chain = (k >= 12 && k <= 13) ? 1 : 0; }
    M1_RESPEED168(o, sp);
    if (chain == 0) return;
    for (o = o->next3C; o != 0; o = o->next3C) M1_RESPEED168(o, sp);
}

#define M1_REPLAY168(n) do { M1An168 *a_ = (n)->anim30; int id_ = a_->x8; a_->x8 = -1; sub_000832D0(a_, id_); } while (0)

/* 0x5AB00: replay an object's current animation from the start; chain kinds do every linked piece. */
void m1_AnimReplay05AB00(M1Ch168 *o) {
    volatile int chain; volatile int k;
    if (o == 0) chain = 0;
    else { k = o->kind4; chain = (k >= 12 && k <= 13) ? 1 : 0; }
    M1_REPLAY168(o);
    if (chain == 0) return;
    for (o = o->next3C; o != 0; o = o->next3C) M1_REPLAY168(o);
}
