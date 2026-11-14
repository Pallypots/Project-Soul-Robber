/* Area m1, file 181: field screen helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Quad181 { float a[4]; float b[4]; uint32_t col[4]; int32_t tex30; int32_t z34; } M1Quad181;
extern int32_t m1_fieldTex3E4B2C;
void *r1k_FieldStarsDraw(void);
void *sub_00012300(void *dl, int a, int b, int c, int d);
void *sub_00072420(void *dl, M1Quad181 *q);

/* 0x59690: draw the star field, then a full-screen (512x448) grey quad with the field texture. */
void *m1_FieldFade059690(void) {
    M1Quad181 q; void *dl;
    dl = sub_00012300(r1k_FieldStarsDraw(), 0x42, 0, 0x44, 0);
    q.tex30 = m1_fieldTex3E4B2C; q.z34 = 0;
    q.a[0] = 0.0f; q.a[2] = 512.0f; q.a[1] = 0.0f; q.a[3] = 448.0f;
    q.b[0] = 0.0f; q.b[1] = 0.0f; q.b[2] = 512.0f; q.b[3] = 448.0f;
    q.col[3] = 0x80808080; q.col[2] = 0x80808080; q.col[1] = 0x80808080; q.col[0] = 0x80808080;
    return sub_00072420(dl, &q);
}

typedef struct M1Fx181 { uint32_t flags0; uint8_t unk04[0xC]; void *owner10; } M1Fx181;
typedef struct M1Snd181 { uint8_t unk00[0x10]; int32_t id10; uint8_t unk14[0xC]; uint8_t e20[0xC]; void *p2C; } M1Snd181;
typedef struct M1Nd181 { struct M1Nd181 *next0; uint8_t unk04[8]; M1Snd181 *snd0C; } M1Nd181;
typedef struct M1Ls181 { uint8_t unk00[4]; M1Nd181 *first4; } M1Ls181;
typedef struct M1Own181 { uint8_t unk00[0x30]; struct { uint8_t unk00[8]; int32_t id8; } *p30; uint8_t unk34[0x104]; M1Ls181 *ls138; M1Fx181 *fx13C; } M1Own181;
void r1c_SndOwnerFree(M1Fx181 *fx);
M1Fx181 *r1e_FxNew(int kind);
void a5b_PairSet(M1Fx181 *fx, void *e);

/* 0x5C2E0: (re)attach an owner's sound effect: free the old one, find the list entry matching the owner's id and start a new effect on it. */
void m1_SndAttach05C2E0(int unused, M1Own181 *o) {
    M1Nd181 *n; M1Snd181 *s; uint8_t *e;
    if (o == 0) return;
    if (o->fx13C) { r1c_SndOwnerFree(o->fx13C); o->fx13C = 0; }
    if (o->ls138 == 0 || (n = o->ls138->first4) == 0) return;
    for (;;) {
        s = n->snd0C;
        if (s->id10 == o->p30->id8) break;
        n = n->next0;
        if (n == 0) return;
    }
    o->fx13C = r1e_FxNew(0);
    if (o->fx13C == 0) return;
    o->fx13C->owner10 = o;
    e = s->e20;
    *(uint8_t **)(e + 0xC) = e + 0x10;
    a5b_PairSet(o->fx13C, e);
    o->fx13C->flags0 |= 1;
}
