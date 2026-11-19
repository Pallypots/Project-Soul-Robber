/* Area m1, file 232: actor state helpers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1E232 { uint8_t unk00[0x80]; float t80; } M1E232;
typedef struct M1S232 { uint8_t unk00[0x278]; M1E232 *ext278; } M1S232;
extern float a50_frameUnits;
int  r2_PlayerOutOfReach(M1S232 *obj, void *self);      /* regargs: obj=EAX self=ESI */
void sub_0011F2B0(void *obj, int k, M1S232 *a);         /* regargs: obj=EDI k=EBX */

/* 0x00125540: count t80 down; state 0x11 if the player is out of reach, else state 0x10 when t80 runs out
   (calls 0x120820 with obj=EAX self=ESI, 0x11F2B0 with obj=EDI k=EBX). */
void m1_Chase125540(void *o, M1S232 *s)
{
    M1E232 *e = s->ext278;
    e->t80 -= a50_frameUnits;
    if (r2_PlayerOutOfReach(s, o)) {
        sub_0011F2B0(o, 0x11, s);
        return;
    }
    if (0.0f > e->t80) {
        e->t80 = 0.0f;
        sub_0011F2B0(o, 0x10, s);
    }
}

typedef struct M1P232 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1P232;
extern M1P232 *g_playerObj;
int  r2_RunSteps31A380(int idx, M1P232 *a, void *b);   /* regargs: idx=EAX a=EBX b=EDI */
void sub_00117580(M1P232 *o, int32_t mode, void *s);    /* regargs: s=EDI */
void sub_00117580d(M1P232 *o, int32_t mode, void *s);   /* same function (alias stops cl merging calls) */
float sub_001B2770(const void *a, const void *b);

/* 0x001178F0: pick the next mode: script 0 -> 10, script 2 -> 12, else by player distance: <= 40 -> 5,
   <= 100 -> 6, farther -> 7 (calls 0x114D10 with idx=EAX a=EBX b=EDI, 0x117580 with s=EDI). */
void m1_PickMode1178F0(M1P232 *o, void *s)
{
    float d;
    if (r2_RunSteps31A380(0, o, s)) {
        sub_00117580(o, 10, s);
        return;
    }
    if (r2_RunSteps31A380(2, o, s)) {
        sub_00117580(o, 12, s);
        return;
    }
    d = sub_001B2770(o->pos60, g_playerObj->pos60);
    if (d <= 40.0f) {
        sub_00117580(o, 5, s);
        return;
    }
    if (d <= 100.0f) {
        sub_00117580d(o, 6, s);
        return;
    }
    sub_00117580(o, 7, s);
}

typedef struct M1Sc232 { uint8_t unk00[0x130]; int32_t res130; } M1Sc232;
typedef struct M1G232 { uint8_t unk00[0x8C]; M1Sc232 *sc8C; } M1G232;
typedef struct M1Fo232 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1Fo232;
M1G232 *sub_00100110(void);
void *sub_00035DD0(M1Fo232 *o, int32_t res, int32_t a, int32_t b);
void sub_00033880(void *h, float *out);
void sub_00034E00(void *h, const void *pos, float *v, const float *col);
void m1_FxScale034DA0(void *h, float k);

/* 0x0018F8D0: spawn effect 4/3 from the scene's resource at o in green, scale 2.5 (regargs: o=EAX). */
void m1_GreenFx18F8D0(M1Fo232 *o)
{
    float col[4];
    float a[8];
    float b[8];
    M1G232 *g = sub_00100110();
    void *h;
    col[0] = 0.0f;
    col[1] = 1.0f;
    col[2] = 0.0f;
    col[3] = 1.0f;
    if (!o)
        return;
    h = sub_00035DD0(o, g->sc8C->res130, 4, 3);
    sub_00033880(h, a);
    sub_00034E00(h, o->pos60, b, col);
    m1_FxScale034DA0(h, 2.5f);
}

typedef struct M1Ev232 { uint8_t unk00[4]; int32_t kind4, sub8; } M1Ev232;
typedef struct M1Sub232 { uint8_t unk00[0x10]; uint32_t flags10; } M1Sub232;
typedef struct M1Pl232 { uint32_t flags0; int32_t kind4; uint8_t unk08[0x118]; M1Sub232 *sub120; } M1Pl232;
extern M1Ev232 *m3_curEvent420DBC;
int32_t Stats_HasEFC(void);

/* 0x000A3990: set or clear bit 0 of the sub-object's flags for kinds 7/34/93-95 depending on Stats_HasEFC(), skipping
   kind 7 with no event or during event 12/7 and kind 34 when flag 0x2000000 is set (regargs: o=EAX). */
void m1_EfcBit0A3990(M1Pl232 *o)
{
    M1Ev232 *ev = m3_curEvent420DBC;
    if (Stats_HasEFC() > 0) {
        switch (o->kind4) {
        case 7:
            if (!ev || (ev->kind4 == 12 && ev->sub8 == 7))
                return;
        case 34: case 93: case 94: case 95:
            o->sub120->flags10 |= 1;
        }
        return;
    }
    switch (o->kind4) {
    case 34:
        if (o->flags0 & 0x2000000)
            return;
    case 7: case 93: case 94: case 95:
        o->sub120->flags10 &= ~1u;
    }
}

int  r3_CheckConds186160(int table, void *a, void *b);   /* regargs: table=EAX a=EBX b=EDI */
void sub_00186470(void *obj, void *act, int state);       /* regargs: obj=EBX act=EDI state=stack */

/* 0x00186800: unless any of condition tables 0/13/2/4/5 holds, go to state 8 (table 1), 3 (table 6) or 10
   (calls 0x186160 with table=EAX a=EBX b=EDI, 0x186470 with obj=EBX act=EDI). */
void m1_PickState186800(void *o, void *s)
{
    if (r3_CheckConds186160(0, o, s) || r3_CheckConds186160(13, o, s) || r3_CheckConds186160(2, o, s)
        || r3_CheckConds186160(4, o, s) || r3_CheckConds186160(5, o, s))
        return;
    if (r3_CheckConds186160(1, o, s)) {
        sub_00186470(o, s, 8);
        return;
    }
    if (r3_CheckConds186160(6, o, s)) {
        sub_00186470(o, s, 3);
        return;
    }
    sub_00186470(o, s, 10);
}

typedef struct M1Fd232 { uint16_t w0, w2; volatile uint8_t b4, b5; volatile uint16_t w6; uint8_t unk08[4]; float tC; float n10; } M1Fd232;
void sub_00072DD0b(M1Fd232 *p, int mode, int x);   /* 0x72DD0 regargs: p=EAX mode=DX x=ECX */

/* 0x00072F30: fill a fade record (kind 2, mode, time t > 0, count n < 2^24) and start it with 0x72DD0
   (tail call with p=EAX mode=DX x=ECX). */
void m1_FadeSet072F30(M1Fd232 *p, uint16_t mode, float t, uint32_t n, int x)
{
    if (!(t > 0.0f))
        for (;;) ;
    if (n >= 0x1000000)
        for (;;) ;
    p->w0 = 2;
    p->w2 = mode;
    p->tC = t;
    p->n10 = (float)n;
    p->b4 = 0;
    p->b5 = 0;
    p->w6 = 2;
    sub_00072DD0b(p, mode, x);
}
