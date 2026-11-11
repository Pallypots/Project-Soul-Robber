#ifndef B1B_H
#define B1B_H
#include "oogie.h"
#include "shared_decls.h"
#include <string.h>

/* Object at *0x003F6128 (Hypothesis: menu/HUD controller, same as b10_ctl). */
typedef struct B1bRes { uint8_t unk00[0x30]; void *handle; /* +0x30 */ } B1bRes;
typedef struct B1bCtl {
    uint8_t  unk000[0x8C];
    B1bRes  *res8C;          /* +0x8C */
    B1bRes  *res90;          /* +0x90 */
    uint8_t  unk094[0xBC - 0x94];
    int16_t  wBC;            /* +0xBC */
    uint8_t  unkBE[0x138 - 0xBE];
    int32_t  i138;           /* +0x138 -1 = none */
    uint8_t  unk13C[0x1FC - 0x13C];
    int16_t  w1FC;           /* +0x1FC */
} B1bCtl;

/* Object at *0x003F6130 (Hypothesis: second menu screen). */
typedef struct B1bScr {
    uint8_t  unk000[0x8C];
    void    *res8C;          /* +0x8C */
    uint8_t  unk090[0x1C0 - 0x90];
    int32_t  i1C0;           /* +0x1C0 */
} B1bScr;

typedef struct B1bObj90 { uint8_t unk00[0x8C]; int32_t i8C; } B1bObj90; /* 0x90 bytes */

typedef struct B1bEvt { uint8_t unk00[0x68]; float f68; int32_t i6C; } B1bEvt;

/* Component flags block used by 0x001012F0. */
typedef struct B1bComp {
    uint8_t  unk00[0xC];
    uint32_t flags0C;        /* +0x0C */
    uint32_t flags10;        /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    int32_t  i20;            /* +0x20 */
} B1bComp;

typedef struct B1bF50 { uint8_t unk00[0x50]; float f50; } B1bF50;

extern B1bCtl *b10_ctl;      /* 0x003F6128 */
extern B1bScr *b10_scr;      /* 0x003F6130 */
extern void   *b10_obj3F6134;/* 0x003F6134 */

void  sub_000F3D10(void *a, void *b, int c);
int   sub_000F30E0(int kind);
void  sub_000F3F00(void *o, float v);
void  sub_0001D910(void *o, void *c);
void  sub_00101240(int v);
void  sub_00102F10(void *a, B1bEvt *e);
void  sub_00101380(void);
#endif
#ifndef B1B_H2
#define B1B_H2
/* ---- group 2 (0x0010D500-0x001153A0) */
typedef struct B1bActor {
    uint8_t  unk000[0x20];
    void    *p20;            /* +0x20 */
    uint8_t  unk024[0x54 - 0x24];
    float    f54;            /* +0x54 */
    uint8_t  unk058[0x60 - 0x58];
    uint8_t  pos60[0xA4 - 0x60]; /* +0x60 */
    float    fA4;            /* +0xA4 */
    uint8_t  unkA8[0xB4 - 0xA8];
    float    fB4;            /* +0xB4 */
    uint8_t  unkB8[0x128 - 0xB8];
    uint8_t  b128;           /* +0x128 */
    uint8_t  unk129[0x164 - 0x129];
    float    f164;           /* +0x164 */
    uint8_t  unk168[0x278 - 0x168];
    struct B1bInfo *info;    /* +0x278 */
} B1bActor;
typedef struct B1bInfo { uint8_t unk00[0x44]; float f44; } B1bInfo;
typedef struct B1bRange { uint8_t unk00[0x10]; float lo; float hi; } B1bRange;
typedef struct B1bComp4 { uint8_t unk00[0x4C]; uint32_t flags4C; } B1bComp4;
/* Enemy node (0x28 bytes): kind 0 = free, 1 = used, 2 = locked (Hypothesis). */
typedef struct B1bNode {
    int32_t kind;            /* +0x00 */
    int32_t id;              /* +0x04 -1 = none */
    float   f08;             /* +0x08 */
    int32_t i0C, i10, i14;   /* +0x0C..+0x14 */
    union {
        struct { float f18, f1C; };     /* +0x18 +0x1C timer view */
        struct { int32_t i18, i1C; };   /* +0x18 +0x1C code view */
    };
    struct B1bNode *prev;    /* +0x20 */
    struct B1bNode *next;    /* +0x24 */
} B1bNode;
typedef struct B1bEnemy {
    uint8_t  unk000[0x4C];
    uint32_t flags4C;        /* +0x4C */
    uint8_t  unk050[0x60 - 0x50];
    B1bNode *nodes;          /* +0x60 list head */
    int32_t  anim64;         /* +0x64 current animation */
    float    f68;            /* +0x68 animation time */
    uint8_t  unk06C[0x2A0 - 0x6C];
    B1bNode  pool[4];        /* +0x2A0 */
} B1bEnemy;
typedef struct B1bCmd { int32_t id; const char *name; void *fn; } B1bCmd;
extern B1bCmd b10_cmdTable[17];        /* 0x00279330 */

void  sub_000F3B00(void *o, int v);
void  sub_000F3BB0(void *o, int a, int b);
void b1b_VecOp2(void *a, void *b);   /* 0x000F5D40 with two args */
void  sub_000ED600(int v);
int   sub_0004F6D0(int id);
void  b1b_CmdRun(int id);           /* 0x0004F5D0 called with a command id */
B1bNode *sub_00113300(B1bEnemy *e);
void  sub_00113370(B1bEnemy *e, B1bNode *n);
B1bNode *b1b_NodeRenew(B1bEnemy *e, int id);
void *sub_000EDC20(int a, int b);
#endif
#ifndef B1B_H3
#define B1B_H3
/* ---- group 3 (0x0011A500-0x0011DBD0): enemy reactions */
typedef struct B1bEInfo {
    uint8_t  unk00[4];
    uint32_t flags04;        /* +0x04 */
    uint8_t  unk08[0x14 - 8];
    float    f14;            /* +0x14 */
    uint8_t  unk18[0x20 - 0x18];
    void    *p20;            /* +0x20 */
    int32_t  i24;            /* +0x24 */
    uint8_t  unk28[0x34 - 0x28];
    void    *p34;            /* +0x34 effect handle */
} B1bEInfo;
typedef struct B1bFoe {
    uint8_t  unk000[0x20];
    uint8_t  b20;            /* +0x20 */
    uint8_t  unk021;
    uint8_t  b22;            /* +0x22 bit 0 = flag 0x10000 of the +0x20 word */
    uint8_t  unk023[0x4C - 0x23];
    uint32_t flags4C;        /* +0x4C */
    int32_t  state;          /* +0x50 */
    uint8_t  unk054[4];
    int32_t  i58;            /* +0x58 */
    uint8_t  unk05C[0x74 - 0x5C];
    float    f74;            /* +0x74 */
    uint8_t  unk078[0x278 - 0x78];
    B1bEInfo *info;          /* +0x278 */
} B1bFoe;
typedef struct B1bOwn { uint8_t unk00[0x10]; uint32_t flags10; } B1bOwn;
typedef struct B1bReq { uint8_t unk00[8]; int32_t side; } B1bReq;

extern float a50_frameUnits;     /* 0x0042C858 */
extern float a50_frameSeconds;   /* 0x0042C85C */
int   sub_001C7EE1(void);
void  b10_AddClampF(float *v, float d, float max);
int   sub_00143760(B1bReq *r, void *b, void *c);
#endif
#ifndef B1B_H4
#define B1B_H4
/* ---- group 4 (0x00113090-0x00113E00): enemy core */
typedef struct B1bAnim { uint8_t unk00[8]; int32_t cur; } B1bAnim;
typedef struct B1bSub14 { uint8_t unk00[0xB8]; uint32_t flagsB8; } B1bSub14;
typedef struct B1bSub30 { uint8_t unk00[0x14]; B1bSub14 *p14; } B1bSub30;
struct B1bECtl;
typedef struct B1bOwner {
    uint8_t  unk000[0xC];
    uint32_t flags0C;        /* +0x0C */
    uint8_t  unk010[0x20 - 0x10];
    uint8_t *p20;            /* +0x20 model */
    uint8_t  unk024[0x30 - 0x24];
    void    *p30;            /* +0x30 animation player / part */
    uint8_t  unk034[0x3C - 0x34];
    void    *p3C;            /* +0x3C model / next part */
    uint8_t  unk040[0x60 - 0x40];
    float    pos60[4];       /* +0x60 */
    uint8_t  unk070[0xD0 - 0x70];
    int32_t  iD0;            /* +0xD0 */
} B1bOwner;
typedef struct B1bECtl {
    uint8_t  unk000[0x14C];
    float    v14C[4];        /* +0x14C */
    uint8_t  unk15C[0x27C - 0x15C];
    int (*canStart)(B1bOwner *o, struct B1bECtl *c); /* +0x27C */
} B1bECtl;
void  sub_0001D7F0(void *model, int anim, int b);
void  sub_001AD9F0(float *dst, const float *a, const float *b);
float sub_001B27C0(const float *a, const float *b);
void  sub_000EE760(B1bOwner *o, float v);
int   sub_000EE5F0(B1bOwner *o);
void  sub_001134B0(B1bECtl *c);
void  sub_001B2200(void *model, float *v);
#endif
#ifndef B1B_H5
#define B1B_H5
/* ---- group 5 (0x0011A370-0x0011ACC0): enemy reaction states */
void  sub_00139FA0(void *o, B1bFoe *e, int state);
void  sub_00033560(void *h);
void  b10_SubClampF(float *v, float d, float min);
void  b1b_EnemyMarkParts(B1bOwner *o, B1bEnemy *e);
#endif
#ifndef B1B_H6
#define B1B_H6
/* ---- group 6 (0x0012D970-0x0012DDB0): actor condition checks */
typedef struct B1bCInfo {
    uint8_t  unk000[0xC];
    uint32_t flags0C;        /* +0x0C */
    uint8_t  unk010[0x180 - 0x10];
    float    f180;           /* +0x180 */
} B1bCInfo;
typedef struct B1bCAct {
    uint8_t  unk000[0xF8];
    int32_t  targetMode;     /* +0xF8 */
    uint8_t  unk0FC[0x104 - 0xFC];
    void    *target;         /* +0x104 */
    uint8_t  unk108[0x278 - 0x108];
    B1bCInfo *info;          /* +0x278 */
} B1bCAct;
typedef struct B1bMask { uint8_t unk00[8]; uint32_t mask; int32_t want; } B1bMask;
/* g_playerObj (0x00420E98) is declared in oogie.h */
#endif
