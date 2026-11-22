/* Area m1, file 291: action events. Names inferred. */
#include <stdint.h>

typedef struct M1Ev291 { int32_t kind0; int32_t r4; uint32_t flags8; float vC; float v10[4]; float v20[4]; } M1Ev291;
typedef struct M1Hd291 { uint8_t unk00[4]; int32_t kind4; uint8_t unk08[8]; uint8_t b10; } M1Hd291;
typedef struct M1Ac291 { uint8_t unk00[0xEC]; uint32_t flagsEC; } M1Ac291;
typedef struct M1Ob291 { uint8_t unk00[0x54]; M1Hd291 *h54; } M1Ob291;
int32_t sub_000CF790(M1Ac291 *a, int32_t k);
void sub_000F5D40(float *d, const float *s);
int32_t sub_000EE010(M1Hd291 *h, M1Ev291 *e);
void sub_000A95E0(M1Hd291 *h, float *p, int32_t v);
void sub_0009F6D0(M1Hd291 *h, M1Ev291 *e, M1Hd291 *x);

/* 0x000C4960: send event 12 (value v, actor a's flag 0x40, stat 4) with directions p and q (both forced to
   w = 1) to o's handler. Kind-12 handlers get it directly through 0x0009F6D0; others through 0x000EE010, and
   when that accepts it 0x000A95E0 runs with a zero offset. Handlers with flag 8 ignore it. */
void m1_SendEvent12C4960(M1Ac291 *a, M1Ob291 *o, int32_t v, float *p, float *q)
{
    M1Hd291 *h = o->h54;
    float z[4];
    M1Ev291 e;
    if (!h || (h->b10 & 8)) return;
    e.kind0 = 0xC;
    if (h->kind4 != 0xC) {
        z[0] = 0.0f;
        z[1] = 0.0f;
        z[2] = 0.0f;
        z[3] = 1.0f;
        e.flags8 = a->flagsEC & 0x40;
        e.vC = (float)v;
        e.r4 = sub_000CF790(a, 4);
        q[3] = 1.0f;
        p[3] = 1.0f;
        sub_000F5D40(e.v10, p);
        sub_000F5D40(e.v20, q);
        if (sub_000EE010(o->h54, &e) == 1)
            sub_000A95E0(o->h54, z, v);
        return;
    }
    e.vC = (float)v;
    e.flags8 = a->flagsEC & 0x40;
    e.r4 = sub_000CF790(a, 4);
    q[3] = 1.0f;
    p[3] = 1.0f;
    sub_000F5D40(e.v10, p);
    sub_000F5D40(e.v20, q);
    h = o->h54;
    sub_0009F6D0(h, &e, h);
}

typedef struct M1Ct291 { int32_t kind0; uint8_t unk04[0x24]; void *(*ctor28)(int32_t a, float *pos, float *rot, int32_t b); } M1Ct291;   /* 0x2C */
typedef struct M1Rn291 { uint8_t unk00[0x14]; void *h14; } M1Rn291;
typedef struct M1En291 { uint8_t unk00[0x20]; float *m20; uint8_t unk24[4]; float *m28; uint8_t unk2C[4]; M1Rn291 *r30;
    uint8_t unk34[0x1C]; float rot50[4]; float pos60[4]; float sx70, sy74, sz78; } M1En291;
typedef struct M1Sl291 { uint8_t unk00[8]; void *busy8; M1En291 *eC; } M1Sl291;                       /* 0x10 */
extern M1Ct291 m3_charTypes278248[];
extern uint8_t m1_entList3F5DC0[];
extern M1Sl291 m1_entSlots3F5DD0[0x30];
void sub_0003D880(void *list, M1Sl291 *s);
void sub_001AD940(float *m);
void sub_001ADBF0(float *d, const float *s, const float *rot);
void sub_001AE010(float *d, const float *s, const float *v);
void sub_001ADA40(float *d, const float *s);
void sub_001B2490(void *h);
void sub_0001B3A0(M1En291 *e);

/* 0x000ED630: create an entity of the given kind through its constructor (kind table at 0x00278248), at pos
   and rot (default origin), put it in a free list slot (hangs if none) and build its world matrix from its
   scale, rotation and position; then refresh its render passes and show it. Returns the entity or 0. */
M1En291 *m1_SpawnKindED630(int32_t kind, int32_t a, float *pos, float *rot, int32_t b)
{
    M1Ct291 *t;
    M1En291 *e;
    M1Sl291 *s;
    float z[4], m[16];
    int32_t i = 0, k = 2;               /* first table entry's kind, known to the original compiler */
    M1Ct291 *volatile q = m3_charTypes278248;
    M1En291 **volatile pe;              /* walks &slot.eC; busy flag at -4, slot base at -0xC */
    while (k != kind) {
        k = q[1].kind0;
        q++;
        i++;
        if (k < 0) break;
    }
    { M1Ct291 *volatile tv = &m3_charTypes278248[i]; t = tv; }
    z[0] = 0.0f;
    z[1] = 0.0f;
    z[2] = 0.0f;
    z[3] = 1.0f;
    e = t->ctor28(a, pos ? pos : z, rot ? rot : z, b);
    if (!e) return 0;
    for (pe = &m1_entSlots3F5DD0[0].eC; ; pe = (M1En291 **)((uint8_t *)pe + sizeof(M1Sl291))) {
        s = (M1Sl291 *)((uint8_t *)pe - 0xC);
        if (!((void **)pe)[-1] && !*pe) break;
        if ((intptr_t)((uint8_t *)pe + sizeof(M1Sl291)) >= (intptr_t)&m1_entSlots3F5DD0[0x30].eC) for (;;) ;
    }
    {
        M1Sl291 *volatile sv = s;      /* store through the slot base (+0xC) like the orig */
        sv->eC = e;
        sub_0003D880(m1_entList3F5DC0, sv);
    }
    sub_001AD940(m);
    m[0] = e->sx70;
    m[5] = e->sy74;
    m[10] = e->sz78;
    sub_001ADBF0(m, m, e->rot50);
    sub_001AE010(e->m20, m, e->pos60);
    if (e->m28)
        sub_001ADA40(e->m28, e->m20);
    if (e->r30 && e->r30->h14)
        sub_001B2490(e->r30->h14);
    sub_0001B3A0(e);
    return e;
}
