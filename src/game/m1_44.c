/* Area m1, file 44: simple actor setups (shared template, parameters differ). Names inferred. */
#include <stdint.h>

typedef struct M1ObjS {
    uint8_t  unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x70 - 0x14];
    float    v70[4];           /* +0x70: 1, 1, 1, 0 */
} M1ObjS;
typedef void (*M1CbS)(void);
typedef struct M1ActS {
    uint8_t  unk000[0x20];
    uint32_t flags20;          /* +0x020 */
    uint8_t  unk024[0x27C - 0x24];
    M1CbS    update27C;        /* +0x27C */
    uint8_t  unk280[0x288 - 0x280];
    M1CbS    draw288;          /* +0x288 */
    void    *paramA28C;        /* +0x28C */
    void    *paramB290;        /* +0x290 */
} M1ActS;
void sub_00183C10(void);
void sub_00183200(void);
void sub_0001EBF0(M1ObjS *o, int v);
void sub_0001D610(void *o);
void sub_00113040(void *owner, void *obj, int what);

#define M1_SIMPLE_SETUP(name, pa, pb) \
extern uint8_t pa[], pb[]; \
int name(M1ObjS *o, M1ActS *a) \
{ \
    a->paramA28C = pa; \
    a->paramB290 = pb; \
    a->update27C = sub_00183C10; \
    a->draw288 = sub_00183200; \
    o->v70[0] = 1.0f; \
    o->v70[1] = 1.0f; \
    o->v70[2] = 1.0f; \
    o->v70[3] = 0.0f; \
    o->flags10 |= 0xC1; \
    a->flags20 |= 0x80000000; \
    sub_0001EBF0(o, 2); \
    sub_0001D610(o); \
    sub_00113040(o, a, 0); \
    return 1; \
}
/* Each sets up an actor with update 0x183C10, draw 0x183200 and its own parameter
 * pair, scale (1, 1, 1), flags 0xC1 / 0x80000000, mode 2, then event 0. Returns 1. */
M1_SIMPLE_SETUP(m1_Setup179060, m1_p32B39C, m1_p32B3A0)   /* 0x00179060 */
M1_SIMPLE_SETUP(m1_Setup17EBF0, m1_p32B7C8, m1_p32B7CC)   /* 0x0017EBF0 */
M1_SIMPLE_SETUP(m1_Setup17EC80, m1_p32B7D0, m1_p32B7D4)   /* 0x0017EC80 */
M1_SIMPLE_SETUP(m1_Setup17ED70, m1_p32B7D8, m1_p32B7EC)   /* 0x0017ED70 */
M1_SIMPLE_SETUP(m1_Setup17EEA0, m1_p32B800, m1_p32B804)   /* 0x0017EEA0 */
M1_SIMPLE_SETUP(m1_Setup183140, m1_p32B8C8, m1_p32B8CC)   /* 0x00183140 */
M1_SIMPLE_SETUP(m1_Setup183290, m1_p32B8D0, m1_p32B8DC)   /* 0x00183290 */

typedef struct M1ObjF {
    uint8_t  unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x50 - 0x14];
    float    rot50[4];         /* +0x50 */
    float    pos60[4];         /* +0x60 */
    float    v70[4];           /* +0x70 */
} M1ObjF;
extern uint8_t m1_p32BC74[], m1_p32BC88[];

/* 0x00183D30: places a fixed actor at (-16, -120, -188), unrotated, scale 1, with
 * the standard callbacks and parameters 0x32BC74/0x32BC88, then event 1. Returns 1. */
int m1_SetupFixed183D30(M1ObjF *o, M1ActS *a)
{
    a->paramA28C = m1_p32BC74;
    a->paramB290 = m1_p32BC88;
    a->update27C = sub_00183C10;
    a->draw288 = sub_00183200;
    o->pos60[0] = -16.0f;
    o->pos60[1] = -120.0f;
    o->pos60[2] = -188.0f;
    o->pos60[3] = 1.0f;
    o->rot50[0] = 0.0f;
    o->rot50[1] = 0.0f;
    o->rot50[2] = 0.0f;
    o->rot50[3] = 1.0f;
    o->v70[0] = 1.0f;
    o->v70[1] = 1.0f;
    o->v70[2] = 1.0f;
    o->v70[3] = 0.0f;
    o->flags10 |= 0x101;
    sub_0001D610(o);
    sub_00113040(o, a, 1);
    return 1;
}

typedef struct M1PairG { void *obj00; void *act04; uint8_t unk08[0x10 - 8]; float f10; } M1PairG;
extern M1PairG m1_pair3FE38C;            /* 0x003FE38C */
extern uint8_t m1_p32BC5C[], m1_p32BC68[], m1_p32BBC0[];
extern const float m1_start27A9AC[4];    /* 0x0027A9AC */
typedef struct M1ObjG {
    uint8_t  unk000[0xC];
    uint32_t flags0C;          /* +0x00C */
    uint32_t flags10;          /* +0x010 */
    uint8_t  unk014[0x30 - 0x14];
    void    *anim030;          /* +0x030 */
    uint8_t  unk034[0x60 - 0x34];
    float    pos060[4];        /* +0x060 */
    uint8_t  unk070[0x124 - 0x70];
    int32_t  f124;             /* +0x124 */
} M1ObjG;
typedef struct M1ActG {
    uint8_t  unk000[0x30];
    void    *p030;             /* +0x030 */
    uint8_t  unk034[0x278 - 0x34];
    M1PairG *pair278;          /* +0x278 */
    M1CbS    update27C;        /* +0x27C */
    uint8_t  unk280[0x288 - 0x280];
    M1CbS    draw288;          /* +0x288 */
    void    *paramA28C;        /* +0x28C */
    void    *paramB290;        /* +0x290 */
} M1ActG;
void sub_00183360(void);
void sub_001833B0(void);
void sub_000F5D40(void *dst, const void *src);
void sub_0001D700(void *o);
void sub_000832D0(void *anim, int id);

/* 0x00183A80: sets up the singleton actor pair at 0x3FE38C (callbacks 0x183360 /
 * 0x1833B0), places o at its start, starts animation 0 and event 0. Returns 1. */
int m1_SetupPair183A80(M1ObjG *o, M1ActG *a)
{
    a->pair278 = &m1_pair3FE38C;
    m1_pair3FE38C.obj00 = o;
    m1_pair3FE38C.act04 = a;
    a->paramA28C = m1_p32BC5C;
    a->paramB290 = m1_p32BC68;
    a->update27C = sub_00183360;
    a->draw288 = sub_001833B0;
    o->flags10 |= 0x44D;
    o->flags0C = (o->flags0C & ~0xE0u) | 3;
    o->f124 = 0;
    a->p030 = m1_p32BBC0;
    sub_000F5D40(o->pos060, m1_start27A9AC);
    sub_0001D700(o);
    sub_000832D0(o->anim030, 0);
    sub_00113040(o, a, 0);
    m1_pair3FE38C.f10 = 0.0f;
    return 1;
}

typedef struct M1Hold34B {
    void   *obj00;             /* +0x00 */
    int32_t f04;
    void   *act08;             /* +0x08 */
    int32_t f0C;               /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x34 - 0x14];
} M1Hold34B;
extern M1Hold34B m1_holdsB3FE3B0[4];   /* 0x003FE3B0 */
extern uint8_t m1_p32BCCC[], m1_p32BCD8[];
typedef struct M1ActH {
    uint8_t    unk000[0x278];
    M1Hold34B *hold278;        /* +0x278 */
    M1CbS      update27C;      /* +0x27C */
    uint8_t    unk280[0x288 - 0x280];
    M1CbS      draw288;        /* +0x288 */
    void      *paramA28C;      /* +0x28C */
    void      *paramB290;      /* +0x290 */
} M1ActH;
typedef struct M1ObjH {
    uint8_t  unk00[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x70 - 0x14];
    float    v70[3];           /* +0x70 */
} M1ObjH;
void sub_00184670(void);
void m1_Stub102FA0(void);

/* 0x001852E0: binds o and a to hold slot i (callbacks 0x184670 / 0x102FA0), scale
 * 1. Returns 1. */
int m1_SetupHold1852E0(M1ObjH *o, M1ActH *a, int i)
{
    M1Hold34B *h = &m1_holdsB3FE3B0[i];
    o->flags0C = (o->flags0C & ~0xE0u) | 1;
    o->flags10 |= 0x44D;
    a->hold278 = h;
    h->f10 = 0.0f;
    h->obj00 = o;
    h->act08 = a;
    a->paramA28C = m1_p32BCCC;
    a->paramB290 = m1_p32BCD8;
    a->update27C = sub_00184670;
    a->draw288 = m1_Stub102FA0;
    h->f0C = 0;
    o->v70[2] = 1.0f;
    o->v70[1] = 1.0f;
    o->v70[0] = 1.0f;
    return 1;
}
