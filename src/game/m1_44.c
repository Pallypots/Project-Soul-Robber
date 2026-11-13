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
void sub_0001EBF0(void *o, int v);
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

typedef struct M1PairK { void *obj00; void *act04; } M1PairK;
extern M1PairK m1_pair3FDE68;          /* 0x003FDE68 */
extern void   *m1_resA3FDE70;          /* 0x003FDE70 */
extern float   m1_f3FDED4;             /* 0x003FDED4 */
extern uint8_t m1_p32B760[], m1_p32B770[];
extern const float m1_start27A618[4];  /* 0x0027A618 */
extern void   *a80_ctx42C8E4;          /* 0x0042C8E4 */
typedef struct M1ObjK2 {
    uint8_t  unk000[0xC];
    uint32_t flags0C;          /* +0x00C */
    uint32_t flags10;          /* +0x010 */
    uint8_t  unk014[0x30 - 0x14];
    void    *anim030;          /* +0x030 */
    uint8_t  unk034[0x60 - 0x34];
    float    pos060[4];        /* +0x060 */
    float    v070[3];          /* +0x070 */
    uint8_t  unk07C[0x124 - 0x7C];
    int32_t  f124;             /* +0x124 */
} M1ObjK2;
typedef struct M1ActK2 {
    uint8_t  unk000[0x278];
    M1PairK *pair278;          /* +0x278 */
    M1CbS    update27C;        /* +0x27C */
    uint8_t  unk280[0x288 - 0x280];
    M1CbS    draw288;          /* +0x288 */
    void    *paramA28C;        /* +0x28C */
    void    *paramB290;        /* +0x290 */
} M1ActK2;
void  sub_0017D810C(void);     /* 0x0017D810 as a callback */
void  sub_0017D920(void);
void  sub_0001EB80(void *o);
void  sub_0001E9B0(void *ctx, void *o, int a, int b, int c);
void *sub_00036750(void *o, int b);

/* 0x0017E310: sets up the scene's singleton actor (pair at 0x3FDE68): flags, layer,
 * mode 3, callbacks 0x17D810 / 0x17D920, start position, event 0, animation 0, and
 * creates the shared effect once. Returns 1. */
int m1_SetupScene17E310(M1ObjK2 *o, M1ActK2 *a)
{
    if (o == 0)
        for (;;) ;
    if (a == 0)
        for (;;) ;
    a->pair278 = &m1_pair3FDE68;
    m1_pair3FDE68.obj00 = o;
    m1_pair3FDE68.act04 = a;
    o->flags0C = (o->flags0C & ~0xE0u) | 1;
    o->flags10 |= 0x44D;
    o->f124 = 0;
    sub_0001EB80(o);
    sub_0001E9B0(a80_ctx42C8E4, o, 0xC, 5, 0x11);
    sub_0001EBF0(o, 3);
    a->paramA28C = m1_p32B760;
    a->paramB290 = m1_p32B770;
    a->update27C = sub_0017D810C;
    a->draw288 = sub_0017D920;
    o->v070[2] = 1.0f;
    o->v070[1] = 1.0f;
    o->v070[0] = 1.0f;
    sub_000F5D40(o->pos060, m1_start27A618);
    sub_00113040(o, a, 0);
    sub_000832D0(o->anim030, 0);
    if (m1_resA3FDE70 == 0)
        m1_resA3FDE70 = sub_00036750(o, 0);
    m1_f3FDED4 = 0.0f;
    return 1;
}

typedef struct M1Part90 { uint8_t unk00[0x40]; float m40[16]; uint8_t unk80[0x90 - 0x80]; uint32_t flags90; } M1Part90;
typedef struct M1PairL {
    void     *obj00;           /* 0x003FE368 */
    void     *act04;           /* 0x003FE36C */
    uint8_t   unk08[0x14 - 8];
    M1Part90 *part14;          /* 0x003FE37C */
    float     f18, f1C;        /* 0x003FE380, 0x003FE384 */
} M1PairL;
extern M1PairL m1_pair3FE368;
extern uint8_t m1_p32B890[], m1_p32B8AC[];
extern const float m1_start27A95C[4];   /* 0x0027A95C */
typedef struct M1ObjL {
    uint8_t  unk000[0xC];
    uint32_t flags0C;          /* +0x00C */
    uint32_t flags10;          /* +0x010 */
    uint8_t  unk014[0x20 - 0x14];
    void    *mtx020;           /* +0x020 */
    uint8_t  unk024[0x30 - 0x24];
    void    *anim030;          /* +0x030 */
    uint8_t  unk034[0x60 - 0x34];
    float    pos060[4];        /* +0x060 */
    float    v070[3];          /* +0x070 */
    uint8_t  unk07C[0x124 - 0x7C];
    int32_t  f124;             /* +0x124 */
} M1ObjL;
typedef struct M1ActL {
    uint8_t  unk000[0x28];
    float    f028;             /* +0x028 */
    uint8_t  unk02C[0x278 - 0x2C];
    M1PairL *pair278;          /* +0x278 */
    M1CbS    update27C;        /* +0x27C */
    uint8_t  unk280[0x288 - 0x280];
    M1CbS    draw288;          /* +0x288 */
    void    *paramA28C;        /* +0x28C */
    void    *paramB290;        /* +0x290 */
} M1ActL;
void      sub_001827E0(void);
void      sub_00182850(void);
M1Part90 *sub_0001D0F0L(void *o, int part);   /* 0x0001D0F0 */
void      sub_000F3FD0(void *o);
void      sub_001ADA40(float *dst, const void *src);

/* 0x00183010: sets up the singleton at 0x3FE368: flags, layer, mode 3, callbacks
 * 0x1827E0 / 0x182850, start position, remembers part 5 (flag 0x40) and copies o's
 * matrix into it, event 0, animation 0. Returns 1. */
int m1_SetupSingle183010(M1ObjL *o, M1ActL *a)
{
    a->pair278 = &m1_pair3FE368;
    m1_pair3FE368.obj00 = o;
    m1_pair3FE368.act04 = a;
    a->paramA28C = m1_p32B890;
    a->paramB290 = m1_p32B8AC;
    a->update27C = sub_001827E0;
    a->draw288 = sub_00182850;
    o->flags0C = (o->flags0C & ~0xE0u) | 1;
    o->flags10 |= 0x44D;
    o->f124 = 0;
    a->f028 = 0.0f;
    sub_0001EB80(o);
    sub_0001E9B0(a80_ctx42C8E4, o, 0xC, 5, 0x11);
    sub_0001EBF0(o, 3);
    o->v070[2] = 1.0f;
    o->v070[1] = 1.0f;
    o->v070[0] = 1.0f;
    sub_000F5D40(o->pos060, m1_start27A95C);
    m1_pair3FE368.part14 = sub_0001D0F0L(o, 5);
    m1_pair3FE368.part14->flags90 |= 0x40;
    sub_000F3FD0(o);
    sub_001ADA40(m1_pair3FE368.part14->m40, o->mtx020);
    m1_pair3FE368.f18 = 0.0f;
    m1_pair3FE368.f1C = 0.0f;
    sub_00113040(o, a, 0);
    sub_000832D0(o->anim030, 0);
    return 1;
}

typedef struct M1LinkObj {
    uint8_t  unk000[0xC];
    uint32_t flags0C;          /* +0x00C */
    uint32_t flags10;          /* +0x010 */
    uint8_t  unk014[0x20 - 0x14];
    void    *node020;          /* +0x020 */
    uint8_t  unk024[0x30 - 0x24];
    void    *anim030;          /* +0x030 */
    uint8_t  unk034[0x54 - 0x34];
    float    rot054;           /* +0x054 */
    uint8_t  unk058[0x70 - 0x58];
    float    v070[3];          /* +0x070 */
    uint8_t  unk07C[0x124 - 0x7C];
    int32_t  f124;             /* +0x124 */
} M1LinkObj;
typedef struct M1Link24L {
    M1LinkObj *a00;            /* +0x00 */
    M1LinkObj *b04;            /* +0x04 partner */
    void      *c08;            /* +0x08 */
    int32_t    key0C;          /* +0x0C */
    uint8_t    unk10[0x24 - 0x10];
} M1Link24L;
extern M1Link24L m1_linksL3FE2D8[4];   /* 0x003FE2D8 */
extern uint8_t m1_p32B878[], m1_p32B884[];
typedef struct M1ActLk {
    uint8_t    unk000[0x28];
    float      f028;           /* +0x028 */
    uint8_t    unk02C[0x278 - 0x2C];
    M1Link24L *link278;        /* +0x278 */
    M1CbS      update27C;      /* +0x27C */
    uint8_t    unk280[0x288 - 0x280];
    M1CbS      draw288;        /* +0x288 */
    void      *paramA28C;      /* +0x28C */
    void      *paramB290;      /* +0x290 */
} M1ActLk;
void  sub_00181E80(void);
void  sub_001B2080(void *node);
void *sub_00182760(void *node);
void  sub_001B2020(void *parent, void *node);
void *sub_0001D0F0K(void *o, int part);   /* 0x0001D0F0 */

/* 0x00182630: binds o and a to link slot i (0..3): callbacks 0x181E80 / 0x102FA0,
 * attaches o's node under 0x182760 and the partner's node under o's part 3, faces
 * i quarter turns, plays animation 3 on both and sends event 0. Returns 1. */
int m1_SetupLink182630(M1LinkObj *o, M1ActLk *a, int i)
{
    M1Link24L *l;
    M1LinkObj *b;
    void *n;
    if (o == 0)
        for (;;) ;
    if (i >= 4)
        for (;;) ;
    l = &m1_linksL3FE2D8[i];
    a->link278 = l;
    l->a00 = o;
    l->c08 = a;
    l->key0C = i;
    a->paramA28C = m1_p32B878;
    a->paramB290 = m1_p32B884;
    a->update27C = sub_00181E80;
    a->draw288 = m1_Stub102FA0;
    o->flags0C = (o->flags0C & ~0xE0u) | 1;
    o->flags10 |= 0x44D;
    o->f124 = 0;
    a->f028 = 0.0f;
    o->v070[2] = 1.0f;
    o->v070[1] = 1.0f;
    o->v070[0] = 1.0f;
    sub_001B2080(o->node020);
    n = o->node020;
    sub_001B2020(sub_00182760(n), n);
    b = l->b04;
    sub_001B2080(b->node020);
    n = b->node020;
    sub_001B2020(sub_0001D0F0K(o, 3), n);
    sub_0001EBF0(o, 3);
    o->rot054 = (float)i * 1.5707964f;
    sub_000832D0(b->anim030, 3);
    sub_000832D0(o->anim030, 3);
    sub_00113040(o, a, 0);
    return 1;
}
