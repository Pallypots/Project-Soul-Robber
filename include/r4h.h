#ifndef R4H_H
#define R4H_H
#include "oogie.h"
#include "shared_decls.h"
/* Area r4h: larger game functions in 0x00190000..0x001BC6D0 (eighth pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4h.csv. */

/* Float to int truncation (cvttss2si in the original); same as RFL_FTOI. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R4H_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R4H_FTOI(x) ((int)(x))
#endif

extern float r4c_frameSeconds;   /* 0x0042C85C frame time in seconds */
extern float r4c_frameUnits;     /* 0x0042C858 frame time in 1/60 s units */

/* ------------------------------------------------------------ scene nodes (0x001B6DC0) */
typedef struct R4hNodeRec {      /* 0x12C bytes, child records at +0xB4 */
    uint8_t  unk00[0xB0];
    uint8_t  flagsB0;            /* +0xB0 */
    uint8_t  unkB1[0xD4 - 0xB1];
    uint8_t  flagsD4;            /* +0xD4 */
    uint8_t  unkD5[0x12C - 0xD5];
} R4hNodeRec;
typedef struct R4hAnimSet {      /* *(model+0xE8) */
    uint8_t  unk00[0x8C];
    int32_t  kind8C;             /* +0x8C 1: 0x108-byte frames, 9: 0x180-byte frames */
    uint8_t  unk90[0xC4 - 0x90];
    uint8_t *framesC4;           /* +0xC4 */
} R4hAnimSet;
typedef struct R4hPose { uint8_t unk00[0xB4]; uint8_t *mtxB4; } R4hPose;   /* 0x130-byte entries */
typedef struct R4hModel {
    uint8_t  unk00[0xC8];
    R4hPose *poseC8;             /* +0xC8 */
    uint8_t  unkCC[0xE8 - 0xCC];
    R4hAnimSet *animE8;          /* +0xE8 */
} R4hModel;
typedef struct R4hXNode {
    float    local[16];          /* +0x00 */
    float    world[16];          /* +0x40 (rows +0x40 +0x50 +0x60, position +0x70) */
    struct R4hXNode *parent80;   /* +0x80 */
    uint8_t  unk84[0x90 - 0x84];
    uint32_t flags90;            /* +0x90 */
    uint8_t  unk94[0xB0 - 0x94];
    uint32_t countB0;            /* +0xB0 */
    R4hNodeRec *recsB4;          /* +0xB4 */
    uint32_t flagsB8;            /* +0xB8 */
    uint8_t  unkBC[0xC0 - 0xBC];
    R4hModel *modelC0;           /* +0xC0 */
    uint8_t  unkC4[0xCC - 0xC4];
    uint32_t flagsCC;            /* +0xCC */
    uint8_t  unkD0[0xD4 - 0xD0];
    void    *poseD4;             /* +0xD4 */
    uint8_t  unkD8[0xFC - 0xD8];
    int16_t  frameFC;            /* +0xFC */
} R4hXNode;
/* g_378188 (0x00378188, up vector here) is declared in oogie.h as char[] */
void sub_001AD7E0(float *d, const float *s);                   /* normalize */
void sub_001ADA60(float *d, const float *a, const float *b);   /* cross product */
void sub_001B6B70(R4hXNode *n);
void r4h_NodeUpdateWorld(R4hXNode *n);   /* 0x001B6DC0 */

/* ------------------------------------------------------------ effect spawner of the 0x00400688 family (0x00192000) */
/* needs r4g.h (node and actor types) included first */
#ifdef R4G_H
typedef struct R4hRec40 { R4gNode *obj; R4gActor *actor; float f08; uint8_t unk0C[4]; int32_t mode10; uint8_t unk14[0x2C]; } R4hRec40; /* 0x00400688 x16 */
extern R4hRec40 r4c_recs400688[16];
extern const float r4h_v27AE94[4], r4h_v27AEA8[4], r4h_v27AEB8[4], r4h_v27AEC8[4];
extern const uint8_t r4h_d32C688[], r4h_d32C698[];
int   sub_00191E20(void *o, void *a, void *msg);
int   r4h_FxSpawnA(R4gNode *o, R4gActor *a, int mode);   /* 0x00192000 */
#endif

/* ------------------------------------------------------------ effect records of the 0x00400390 family (0x00191B30) */
#ifndef R4G_H
typedef struct R4hRec4C {        /* 0x4C bytes */
    void    *obj;                /* +0x00 */
    void    *actor;              /* +0x04 */
    float    f08;                /* +0x08 */
    float    f0C;                /* +0x0C */
    int32_t  mode10;             /* +0x10 */
    uint8_t  unk14[0x40 - 0x14];
    int16_t  h40;                /* +0x40 */
    uint8_t  unk42[0x4C - 0x42];
} R4hRec4C;
extern R4hRec4C r4c_recs400390[10];
#endif
void r4h_FxResetB(void);         /* 0x00191B30 */

/* ------------------------------------------------------------ orbiting effect steps (0x001984C0, 0x00198640) */
typedef struct R4hOrbParent { uint8_t unk00[0x70]; float pos70[4]; } R4hOrbParent;
typedef struct R4hOrbObj {
    uint8_t  unk00[0x20];
    float   *mtx20;              /* +0x20 matrix the spin is written to */
    uint8_t  unk24[0x34 - 0x24];
    R4hOrbParent *parent34;      /* +0x34 */
    uint8_t  unk38[0x50 - 0x38];
    float    rotX50;             /* +0x50 */
    float    rotY54;             /* +0x54 */
    uint8_t  unk58[0x60 - 0x58];
    float    pos60[4];           /* +0x60 */
    uint8_t  unk70[0x80 - 0x70];
    float    vel80[4];           /* +0x80 */
} R4hOrbObj;
typedef struct R4hOrbWork { uint8_t unk00[0x08]; float f08, f0C, f10, f14, f18; } R4hOrbWork;
typedef struct R4hOrbAct { uint8_t unk00[0x74]; R4hOrbWork *work; } R4hOrbAct;
void sub_001AD8B0(void *d, const void *s, float a);            /* rotate about X */
void sub_001ADAF0(float *d, const float *a, const float *b);   /* vector add (oogie.h) */
void r4h_FxOrbitStepB(R4hOrbObj *o, R4hOrbAct *a);   /* 0x001984C0 */
void r4h_FxOrbitStepA(R4hOrbObj *o, R4hOrbAct *a);   /* 0x00198640 */

/* ------------------------------------------------------------ 0x00400CA8 effect family (0x00194620, 0x00194B50) */
typedef struct R4hFxNodeC {
    uint8_t  unk00[0x0C];
    uint32_t flagsC;             /* +0x0C */
    uint32_t flags10;            /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    float   *mtx20;              /* +0x20 */
    uint8_t  unk24[0x50 - 0x24];
    float    rotX50;             /* +0x50 */
    float    rotY54;             /* +0x54 */
    uint8_t  unk58[0x60 - 0x58];
    float    pos60[4];           /* +0x60 */
    float    scale70[4];         /* +0x70 */
    float    vel80[4];           /* +0x80 */
    uint8_t  unk90[0xA4 - 0x90];
    float    fA4;                /* +0xA4 */
    uint8_t  unkA8[0xB0 - 0xA8];
    float    fB0;                /* +0xB0 */
    float    fB4;                /* +0xB4 */
    uint8_t  unkB8[0xD0 - 0xB8];
    int32_t  kindD0;             /* +0xD0 */
    uint8_t  unkD4[0xDC - 0xD4];
    float    fDC;                /* +0xDC */
    uint8_t  unkE0[0xE8 - 0xE0];
    float    fE8;                /* +0xE8 */
    int32_t  iEC;                /* +0xEC */
    int32_t  iF0;                /* +0xF0 */
    int32_t  iF4;                /* +0xF4 */
    uint8_t  unkF8[0xFC - 0xF8];
    float    fFC;                /* +0xFC */
    uint8_t  unk100[0x10C - 0x100];
    float    f10C;               /* +0x10C */
    uint8_t  unk110[0x118 - 0x110];
    int32_t  i118;               /* +0x118 */
    int32_t  i11C;               /* +0x11C */
    int32_t  i120;               /* +0x120 */
    uint8_t  unk124[0x128 - 0x124];
    uint32_t flags128;           /* +0x128 */
    uint8_t  unk12C[0x130 - 0x12C];
    void    *list130;            /* +0x130 */
} R4hFxNodeC;
typedef struct R4hRec1C {        /* 0x00400CA8, 0x1C bytes */
    uint32_t flags;              /* +0x00 */
    float    t04;                /* +0x04 */
    float    end08;              /* +0x08 */
    float    step0C;             /* +0x0C */
    uint8_t  unk10[0x14 - 0x10];
    float    timer14;            /* +0x14 */
    R4hFxNodeC *src18;           /* +0x18 */
} R4hRec1C;
typedef struct R4hFxActC {
    uint8_t  unk00[0x28];
    float    f28;                /* +0x28 */
    float    f2C;                /* +0x2C */
    uint8_t  unk30[0x60 - 0x30];
    int32_t  state60;            /* +0x60 */
    uint8_t  unk64[0x70 - 0x64];
    float    life70;             /* +0x70 */
    R4hRec1C *work;              /* +0x74 */
    void    *fn78;               /* +0x78 */
    void    *fn7C;               /* +0x7C */
    void    *fn80;               /* +0x80 */
    const void *p84;             /* +0x84 */
    const void *p88;             /* +0x88 */
} R4hFxActC;
extern const uint8_t r4h_d32C780[], r4h_d32C79C[];
R4hRec1C *r4c_Rec1CAlloc(void);                     /* 0x00193E10 */
int   sub_0001BC40(R4hFxNodeC *o);
void  sub_001940D0(void);

void  sub_00194100(void);

void  sub_000EEA60(R4hFxNodeC *o, const float *v);
void  sub_00189DA0(void *a, void *b, int c);
void  r4h_FxBlinkStep(R4hFxNodeC *o, R4hFxActC *a);          /* 0x00194620 */
int   r4h_FxSpawnC(R4hFxNodeC *o, R4hFxActC *a, R4hFxNodeC *src);   /* 0x00194B50 */

int   sub_00087500(void);
int   Stats_HasEFC(void);                           /* 0x000CF6C0 (oogie.h) */
void  sub_000C56B0(R4hFxNodeC *o);
int   sub_000CFFB0(void);
void  sub_000C4250(void *stats, float *a, float *b);
int   sub_000EE2B0(float *a, float *b, float *c);
void  r4h_FxThrowMove(R4hFxNodeC *o, R4hFxActC *a);         /* 0x00194410 */
void  sub_001942B0(void);

/* ------------------------------------------------------------ slot effects at 0x00400A88 (0x00193C10) */
typedef struct R4hAnimInfo { uint8_t unk00[0xC4]; float fC4; uint8_t unkC8[0xDC - 0xC8]; float fDC; } R4hAnimInfo;
typedef struct R4hAnim { uint8_t unk00[0x14]; R4hAnimInfo *info14; } R4hAnim;
typedef struct R4hFxNodeD {
    uint8_t  unk00[0x0C];
    uint32_t flagsC;             /* +0x0C */
    uint32_t flags10;            /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    struct R4hAnim *anim30;      /* +0x30 */
    R4hOrbParent *parent34;      /* +0x34 parent node */
    uint8_t  unk38[0x50 - 0x38];
    float    rot50[4];           /* +0x50 */
    float    pos60[4];           /* +0x60 */
    uint8_t  unk70[0x9C - 0x70];
    float    alpha9C;            /* +0x9C */
    uint8_t  unkA0[0xF0 - 0xA0];
    int32_t  iF0;                /* +0xF0 */
    int32_t  iF4;                /* +0xF4 */
    uint8_t  unkF8[0x11C - 0xF8];
    int32_t  i11C;               /* +0x11C */
    int32_t  i120;               /* +0x120 */
    int32_t  i124;               /* +0x124 */
    uint32_t flags128;           /* +0x128 */
} R4hFxNodeD;
typedef struct R4hSlot88 {       /* 0x00400A88 x4, 0x88 bytes */
    R4hFxNodeD *obj;             /* +0x00 */
    struct R4hFxActD *actor;     /* +0x04 */
    int32_t  idx;                /* +0x08 */
    float    t0C;                /* +0x0C */
    int16_t  sub10;              /* +0x10 sub-state of slots 0 and 1 */
    uint8_t  unk12[0x14 - 0x12];
    float    f14;                /* +0x14 */
    uint8_t  unk18[0x1C - 0x18];
    float    dir1C[4];           /* +0x1C */
    float    vel2C[4];           /* +0x2C */
    float    start3C[4];         /* +0x3C */
    float    g4C;                /* +0x4C */
    float    v50;                /* +0x50 */
    float    v54;                /* +0x54 */
    float    scale58;            /* +0x58 */
    float    time5C;             /* +0x5C */
    int16_t  bounce60;           /* +0x60 */
    int16_t  flown62;            /* +0x62 */
    float    t64;                /* +0x64 */
    float    f68;                /* +0x68 */
    int16_t  h6C;                /* +0x6C */
    uint8_t  unk6E[0x70 - 0x6E];
    int32_t  toggle70;           /* +0x70 */
    uint8_t  unk74[0x78 - 0x74];
    float    aim78[4];           /* +0x78 */
} R4hSlot88;
typedef struct R4hFxActD {
    uint8_t  unk00[0x20];
    uint32_t flags20;            /* +0x20 */
    int32_t  i24;                /* +0x24 */
    float    f28;                /* +0x28 */
    float    f2C;                /* +0x2C */
    uint8_t  unk30[0x60 - 0x30];
    int32_t  state60;            /* +0x60 */
    uint8_t  unk64[0x74 - 0x64];
    R4hSlot88 *work;             /* +0x74 */
    void    *fn78;               /* +0x78 */
    void    *fn7C;               /* +0x7C */
    void    *fn80;               /* +0x80 */
    const void *p84;             /* +0x84 */
    const void *p88;             /* +0x88 */
} R4hFxActD;
extern R4hSlot88 r4c_recs400A88[4];
extern const uint8_t r4h_d32C728[], r4h_d32C734[], r4h_d32C740[], r4h_d32C760[];
int r4c_SlotStop(void *, void *);                         /* 0x00192470 */
int r4c_SlotMsg(void *, void *, void *);                          /* 0x00192530 */
void r4c_SlotScale(int idx, float s);            /* 0x00192630 regargs: idx=EAX */
void sub_0001EF00(void *o, const float *v);
int  r4h_FxSlotSpawn(R4hFxNodeD *o, R4hFxActD *a, int idx);   /* 0x00193C10 */

typedef struct R4hPlayCtx { uint8_t unk000[0x324]; int32_t i324; } R4hPlayCtx;
extern const float r4h_v318DC8[4];
extern const float r4c_v27AFE8[4], r4c_v27AFF8[4];
float sub_000F5F50(const float *v);                      /* length in XZ */
void  sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
void  sub_000EE760(void *o, float v);
void  r4h_FxSlotStep(R4hFxNodeD *o, R4hFxActD *a);       /* 0x00193A30 */

extern float a50_framesPerSecond;                /* 0x0042C964 */
extern const uint8_t r4h_d32C718[];
void  sub_000F6450(void *o, const void *p);
void  r4h_FxSlotFly(R4hFxNodeD *o, R4hFxActD *a);        /* 0x00193490 */

void  r4h_FxSlotHold(R4hFxNodeD *o, R4hFxActD *a);   /* 0x00193700 */

int   sub_001C7EE1(void);                           /* rand */
void  sub_000F5ED0(float *angle);
void  r4h_SlotThrow(R4hSlot88 *rec);                 /* 0x00192730 regargs: rec=ESI */

extern const uint8_t r4h_d32C6F8[];
void  r4h_FxSlotFlyB(R4hFxNodeD *o, R4hFxActD *a);   /* 0x00192A70 */

typedef struct R4hPosNode { uint8_t unk00[0x60]; float pos60[4]; } R4hPosNode;
typedef struct R4hSys {
    uint8_t  unk00[0x8C];
    R4hPosNode *target8C;        /* +0x8C */
    uint8_t  unk90[0x114 - 0x90];
    float    turn114;            /* +0x114 */
} R4hSys;
R4hSys *sub_000F3F80(void);
float sub_001B2770(const float *a, const float *b);  /* distance on the ground plane */
float sub_000F7720(void *o, const float *pos);       /* turn angle toward pos */
void  r4h_FxSlotAim(R4hFxNodeD *o, R4hFxActD *a);    /* 0x00192EC0 */

/* ------------------------------------------------------------ lobbed effect aim (0x00190E80) */
typedef struct R4hLobRec {
    uint8_t  unk00[0x10];
    int32_t  mode10;             /* +0x10 1: drop from its own height */
    float    vel14[4];           /* +0x14 */
    uint8_t  unk24[0x28 - 0x24];
    float    g28;                /* +0x28 */
    float    vy2C;               /* +0x2C */
} R4hLobRec;
typedef struct R4hLobAct { uint8_t unk00[0x74]; R4hLobRec *work; } R4hLobAct;
void  sub_00101340(float *pos);
void  r4h_FxLobAim(R4hFxNodeD *o, R4hLobAct *a);     /* 0x00190E80 */

/* ------------------------------------------------------------ joint follower (0x00198B40) */
typedef struct R4hJoint { uint8_t unk00[0x30]; float off30[4]; uint8_t unk40[0x70 - 0x40]; float pos70[4]; } R4hJoint;
typedef struct R4hJntObj { uint8_t unk00[0x54]; float rotY54; } R4hJntObj;
typedef struct R4hJntWork { int32_t i00; int32_t i04; } R4hJntWork;
typedef struct R4hJntAct { uint8_t unk00[0x6C]; float t6C; uint8_t unk70[4]; R4hJntWork *work; } R4hJntAct;
extern float r4h_lerp32C910;     /* 0x0032C910 */
extern float r4c_g32C8CC;        /* 0x0032C8CC */
extern float r4h_end32C914;      /* 0x0032C914 */
void  sub_001ADCD0(float *d, const float *a, const float *b, float t);   /* lerp */
void  sub_001ADBA0(float *d, const float *s, float k);          /* d = s * k (4 components) */
void  r4h_FxJointHold(R4hJntObj *o, R4hJntAct *a);  /* 0x00198B40 */

/* ------------------------------------------------------------ popped piece drop (0x00197E40) */
typedef struct R4hPopObj {
    uint8_t  unk00[0x0C];
    uint32_t flagsC;             /* +0x0C */
    uint8_t  unk10[0x60 - 0x10];
    float    pos60[4];           /* +0x60 */
    uint8_t  unk70[0x128 - 0x70];
    uint32_t flags128;           /* +0x128 */
} R4hPopObj;
typedef struct R4hPopRec {
    R4hPopObj *src;              /* +0x00 */
    int32_t  kind04;             /* +0x04 passed to 0x00196DB0 */
    float    rate08;             /* +0x08 */
    int16_t  sound0C;            /* +0x0C */
    int16_t  blink0E;            /* +0x0E */
    int16_t  held10;             /* +0x10 */
    uint8_t  unk12[0x18 - 0x12];
    float    acc18;              /* +0x18 */
    float    vel1C;              /* +0x1C */
    float    h20;                /* +0x20 */
    float    last24[4];          /* +0x24 */
    uint8_t  unk34[0x38 - 0x34];
    float    base38;             /* +0x38 */
} R4hPopRec;
typedef struct R4hPopAct { uint8_t unk00[0x6C]; float t6C; uint8_t unk70[4]; R4hPopRec *work; } R4hPopAct;
extern const uint8_t r4h_d32C848[];
void  sub_000F60C0(void *o, int a, int b);
void  sub_00196DB0(int kind, R4hPopObj *o);           /* regargs: kind=EAX o=ECX */
void  r4h_FxPopDrop(R4hPopObj *o, R4hPopAct *a);      /* 0x00197E40 */

/* ------------------------------------------------------------ hopping effect aim (0x001956A0) */
typedef struct R4hHopRec {
    uint8_t  unk00[0x0C];
    float    t0C;                /* +0x0C */
    int32_t  mode10;             /* +0x10 1: random hop near Jack */
    float    f14;                /* +0x14 */
    uint8_t  unk18[0x44 - 0x18];
    float    vel44[4];           /* +0x44 */
    uint8_t  unk54[0x84 - 0x54];
    float    g84;                /* +0x84 */
} R4hHopRec;
typedef struct R4hHopAct { uint8_t unk00[0x74]; R4hHopRec *work; } R4hHopAct;
void  r4c_FxScale(void *o, float s);                  /* 0x001955B0 regargs: o=EAX */
void  r4h_FxHopAim(R4hFxNodeD *o, R4hHopAct *a);      /* 0x001956A0 */

/* ------------------------------------------------------------ wave pieces fanned out from a source (0x00193E50) */
typedef struct R4hWaveObj {
    uint8_t  unk00[0x54];
    float    rotY54;             /* +0x54 */
    uint8_t  unk58[0x60 - 0x58];
    float    pos60[4];           /* +0x60 */
    float    scale70[4];         /* +0x70 */
    float    vel80[4];           /* +0x80 */
} R4hWaveObj;
typedef struct R4hWaveRec { uint32_t flags; uint8_t unk04[4]; float speed08; float rise0C; uint32_t bit10; } R4hWaveRec;
typedef struct R4hWaveAct { uint8_t unk00[0x74]; R4hWaveRec *work; } R4hWaveAct;
void  r4h_FxWaveSpawn(R4hWaveObj *o, R4hWaveObj *src, uint32_t used);   /* 0x00193E50 */

#endif
