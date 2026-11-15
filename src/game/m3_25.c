/* Area m3, file 25: minion slot setup. Names inferred. */
#include <stdint.h>

typedef struct M3MinO25 { uint8_t unk00[4]; int32_t kind4; int32_t type8; uint32_t fC; uint32_t f10; uint8_t unk14[0xC]; void *mdl20; uint8_t unk24[0x7C]; float off_a0[4]; float fB0, fB4; uint8_t unkB8[0x18]; int32_t iD0; } M3MinO25;
typedef struct M3MinE25 { uint8_t unk00[0x14]; int32_t i14; float f18, f1C; uint8_t unk20[4]; void (*fn24)(void); uint8_t unk28[4]; void (*fn2C)(void); uint8_t unk30[0xC]; M3MinO25 *obj3C; uint8_t unk40[4]; int32_t slot44; float f48, f4C, f50; } M3MinE25;
typedef struct M3MinH25 { uint8_t unk00[0x20]; void *mdl20; } M3MinH25;
typedef struct M3MinS25 { uint8_t unk00[0x54]; float f54, f58; uint8_t unk5C[0x30]; M3MinH25 *hero8C; M3MinH25 *buddy90; uint8_t unk94[8]; M3MinE25 ent9C[3]; } M3MinS25;
extern M3MinS25 *m1_scr3F6130;
extern float m3_minOffA278E4C[], m3_minOffB278E78[], m3_minOffC278E88[];
void sub_0001D8B0(void *c, int kind);
void r1b_RecAddItem(void *o, void *c);
void sub_000EE270(void *c);
int  sub_0001BC40(void *h);
float sub_00171D50(int kind, int type, int a);
void sub_001012F0(void);
void sub_00101490(void);
void sub_00101910(void);
void a3c_VecCopy(float *dst, const float *src);
void rbj_VecScale(float *d, const float *s, float k);

/* 0x104C90: set up minion slot n (0..2) with object o (hangs on null): link its kind-0xD component, flag it, set its handlers and stats by slot (slot 0 uses the buddy model and scene speed, slots 1 and 2 the hero model), its offsets and anchor vector. Returns o. */
M3MinO25 *m3_MinionSlot104C90(M3MinO25 *o, int n) {
    M3MinS25 *s = m1_scr3F6130; M3MinH25 *h = s->hero8C; M3MinE25 *e = &s->ent9C[n]; float r;
    if (o == 0) for (;;) ;
    sub_0001D8B0(e, 0xD);
    r1b_RecAddItem(o, e);
    sub_000EE270(e);
    o->f10 |= 0x4C1;
    o->fC |= 0x203;
    e->obj3C = o;
    e->slot44 = n;
    e->fn24 = sub_001012F0;
    o->iD0 = sub_0001BC40(h);
    if (n == 0) {
        o->kind4 = 3; o->type8 = 0xC;
        r = sub_00171D50(3, 0xC, 0);
        s->f58 = r; s->f54 = r;
        e->f1C = -17.0f; e->f18 = -5.0f;
        o->mdl20 = s->buddy90->mdl20;
        e->i14 = 0xC;
        e->fn2C = sub_00101490;
        o->fB0 = 13.0f;
        o->fB4 = -18.0f;
        a3c_VecCopy(o->off_a0, m3_minOffA278E4C);
    } else if (n == 1) {
        o->kind4 = 3; o->type8 = 0xD;
        r = sub_00171D50(3, 0xD, 0);
        e->f4C = r; e->f48 = r;
        e->f1C = -14.0f; e->f18 = -8.0f;
        o->mdl20 = h->mdl20;
        e->i14 = 8;
        e->fn2C = sub_00101910;
        o->fB0 = 12.5f;
        o->fB4 = -27.0f;
        a3c_VecCopy(o->off_a0, m3_minOffB278E78);
    } else if (n == 2) {
        o->kind4 = 3; o->type8 = 0xD;
        r = sub_00171D50(3, 0xD, 0);
        e->f4C = r; e->f48 = r;
        e->f1C = -14.0f; e->f18 = -8.0f;
        o->mdl20 = h->mdl20;
        e->i14 = 0xE;
        e->fn2C = sub_00101910;
        o->fB0 = 12.5f;
        o->fB4 = -27.0f;
        a3c_VecCopy(o->off_a0, m3_minOffC278E88);
    }
    rbj_VecScale(o->off_a0, o->off_a0, 1.0f);
    e->f50 = 0.0f;
    return o;
}

typedef struct M3Fx25 { uint32_t f0; int32_t i4, i8; float fC, f10, f14, f18; uint8_t unk1C[8]; float pos24[4]; float dir34[4]; float up44[4]; int32_t i54; uint8_t unk58[0x88]; } M3Fx25;
extern M3Fx25 m1_entsE41E2A0[];
void sub_000C4B70(M3Fx25 *s);

/* 0xC4D30: allocate the first free effect slot (bit 0 clear) of 32, clear it and fill kind, parameters, position, direction and up vectors and the owner; returns the slot index or -1. */
int m3_FxAllocC4D30(int owner, int kind, float a, int b, float c, float d, float e, float *pos, float *dir, float *up) {
    M3Fx25 *p, *s; int i = 0;
    for (p = m1_entsE41E2A0; (int32_t)p < (int32_t)&m1_entsE41E2A0[32]; p++, i++)
        if (!(p->f0 & 1)) goto found;
    return -1;
found:
    { volatile int vi = i; if (vi < 0) return -1; }
    s = &m1_entsE41E2A0[i];
    sub_000C4B70(s);
    s->fC = a;
    s->f10 = e;
    s->i4 = kind;
    s->f0 |= 1;
    s->f14 = c;
    s->f18 = d;
    s->i8 = b;
    a3c_VecCopy(s->pos24, pos);
    a3c_VecCopy(s->dir34, dir);
    a3c_VecCopy(s->up44, up);
    s->i54 = owner;
    return i;
}

typedef struct M3NObj25 { uint8_t unk00[0xC]; uint8_t bC; uint8_t unkD[0x53]; float pos60[4]; } M3NObj25;
typedef struct M3NEnt25 { uint32_t f0; uint8_t unk04[0x60]; M3NObj25 *obj64; } M3NEnt25;
extern M3NEnt25 m1_ents41CEC0[];
void r4c_VecSub(float *dst, const float *a, const float *b);
float m1_VecLen082D70(const float *v);

/* 0xC71C0: nearest live object of the active entities (flags 1 and 0x20000000) to o within the given range; 0 when none. */
M3NObj25 *m3_NearestEntC71C0(M3NObj25 *o, float range) {
    float d[4], best, l; M3NEnt25 *p; M3NObj25 *res = 0, *q;
    d[0] = 0.0f; d[1] = 0.0f; d[2] = 0.0f; d[3] = 1.0f;
    best = 3.4028235e38f;
    for (p = m1_ents41CEC0; (int32_t)p < (int32_t)&m1_ents41CEC0[3]; p++) {
        { volatile uint32_t f = p->f0; if (!(f & 1) || !(f & 0x20000000)) continue; }
        q = p->obj64;
        if (q == 0 || !(q->bC & 1)) continue;
        r4c_VecSub(d, o->pos60, q->pos60);
        l = m1_VecLen082D70(d);
        if (range > l && best > l) { best = l; res = q; }
    }
    return res;
}

typedef struct M3SpU25 { uint8_t unk00[4]; int32_t kind4; int32_t type8; uint32_t fC; uint8_t unk10[0x50]; float pos60[4]; uint8_t unk70[0xDC]; int32_t list14C; } M3SpU25;
typedef struct M3SpR25 { uint32_t f0; int32_t type4; uint8_t unk08[0x38]; float pos40[4]; uint8_t unk50[0x88]; M3SpU25 *unitD8; } M3SpR25;
extern M3SpR25 m1_voices420F20[];
extern M3SpU25 *m1_g423F50;
extern int32_t m1_msgIds423F64[];
extern uint8_t *m1_g420F04;
extern void *m1_scene42C8E4;
void sub_00022380(void *o, void *res, void *ctx);
void r1i_UnitsAttach(void *ctx, void *o, int a, int b, int c);
void sub_0001EBF0(void *o, int a);

/* 0xA75F0: spawn pending records (sign bit set): take the first free of 56 units, find the resource for the record type among 28 ids, attach and enable the unit as kind 11 of that type, mark the record live and place the unit. */
#pragma optimize("s", on)
void m3_SpawnPendingA75F0(void) {
    void *ctx = m1_scene42C8E4; M3SpR25 *p; M3SpU25 *q, *u; int i, j; uint8_t *m;
    for (p = m1_voices420F20; (int32_t)p < (int32_t)&m1_voices420F20[56]; p++) {
        M3SpR25 *volatile vp = p; M3SpR25 *r = vp;
        if ((int32_t)r->f0 >= 0) continue;
        q = m1_g423F50;
        for (i = 0; i < 0x38; i++, q = (M3SpU25 *)((uint8_t *)q + 0x150))
            if (!(q->fC & 1)) goto got;
        q = 0;
got:
        u = q;
        r->unitD8 = u;
        if (u == 0) continue;
        for (j = 0; j < 0x1C; j++)
            if (m1_msgIds423F64[j] == r->type4) break;
        if (j >= 0x1C) continue;
        { volatile int st = 0x150; m = m1_g420F04 + j * st; }
        if (m == 0) continue;
        sub_00022380(u, m, ctx);
        r1i_UnitsAttach(ctx, r->unitD8, r->unitD8->list14C, 5, 0x11);
        r->unitD8->fC |= 1;
        r->unitD8->kind4 = 0xB;
        r->unitD8->type8 = r->type4;
        r->f0 = (r->f0 & 0x7FFFFFFE) | 1;
        a3c_VecCopy(r->unitD8->pos60, r->pos40);
        sub_0001EBF0(r->unitD8, 0);
    }
}
#pragma optimize("", on)
