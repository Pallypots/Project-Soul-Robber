/* Area r2d: game functions in 0x000D0000..0x0012FFFF. Names inferred. */
#ifndef R2D_H
#define R2D_H
#include "oogie.h"

/* ---------------------------------------------------------------- shared */
/* Player character record at 0x0041FEC0 (the same object oogie.h calls
   PlayerStats; only the fields used by r2d are named here). */
typedef struct R2dPlayer {
    uint8_t  unk000[0xD8];
    int32_t  stateD8;          /* +0x0D8 (0x0041FF98) */
    int32_t  vDC;              /* +0x0DC */
    int32_t  vE0;              /* +0x0E0 (0x0041FFA0) */
    uint8_t  unkE4[0xE8 - 0xE4];
    float    fE8;              /* +0x0E8 */
    uint32_t vEC;              /* +0x0EC */
    float    fF0;              /* +0x0F0 */
    uint8_t  unkF4[0xFC - 0xF4];
    float    fFC;              /* +0x0FC (0x0041FFBC) */
    uint8_t  unk100[0x108 - 0x100];
    float    f108;             /* +0x108 (0x0041FFC8) */
    float    f10C;             /* +0x10C */
    float    v110[3];          /* +0x110 */
    float    f11C;             /* +0x11C */
    uint8_t  unk120[0x140 - 0x120];
    int32_t  v140;             /* +0x140 (0x00420000) */
    uint8_t  unk144[0x148 - 0x144];
    float    f148;             /* +0x148 */
    float    f14C;             /* +0x14C */
    uint32_t flags150;         /* +0x150 (0x00420010) */
    uint8_t  unk154[0x164 - 0x154];
    int32_t  v164;             /* +0x164 */
    float    f168;             /* +0x168 */
    uint8_t  unk16C[0x190 - 0x16C];
    float    f190;             /* +0x190 */
    int32_t  v194;             /* +0x194 */
    float    v198[4];          /* +0x198 */
    uint8_t  unk1A8[0x1B8 - 0x1A8];
    int32_t  mode1B8;          /* +0x1B8 (0x00420078) */
    uint8_t  unk1BC[0x1C0 - 0x1BC];
    int32_t  v1C0;             /* +0x1C0 */
    float    f1C4;             /* +0x1C4 */
    int32_t  v1C8;             /* +0x1C8 */
    int32_t  v1CC;             /* +0x1CC */
    int32_t  v1D0;             /* +0x1D0 */
    int32_t  v1D4;             /* +0x1D4 */
    uint8_t  unk1D8[0x5F0 - 0x1D8];
    int32_t  fx5F0;            /* +0x5F0 effect handle, -1 none */
    uint8_t  unk5F4[0x600 - 0x5F4];
    void    *snd600;           /* +0x600 handle (0x00036750) */
    uint8_t  unk604[0x608 - 0x604];
    void    *snd608;           /* +0x608 handle (0x00036750) */
    uint8_t  unk60C[0xE04 - 0x60C];
    int32_t  vE04;             /* +0xE04 */
    uint8_t  unkE08[0xFD8 - 0xE08];
    struct R2dNode *nodeFD8;   /* +0xFD8 */
} R2dPlayer;
extern R2dPlayer r2d_player;           /* 0x0041FEC0 */

/* Scene node: +0x0C flags, +0x20 render part, +0x3C next sibling. */
typedef struct R2dPart {
    uint8_t  unk00[0x70];
    float    v70[4];           /* +0x70 */
    uint8_t  unk80[0xD0 - 0x80];
    float    colD0[4];         /* +0xD0 */
} R2dPart;
typedef struct R2dNode {
    uint8_t  unk00[0x0C];
    uint32_t flags0C;          /* +0x0C */
    uint8_t  unk10[0x20 - 0x10];
    R2dPart *part20;           /* +0x20 */
    uint8_t  unk24[0x3C - 0x24];
    struct R2dNode *next3C;    /* +0x3C */
    uint8_t  unk40[0x60 - 0x40];
    float    pos60[4];         /* +0x60 */
    uint8_t  unk70[0xA0 - 0x70];
    float    vA0[4];           /* +0x0A0 */
    int32_t  vB0;              /* +0x0B0 */
    float    fB4;              /* +0x0B4 */
    uint8_t  unkB8[0xD0 - 0xB8];
    int32_t  vD0;              /* +0x0D0 */
} R2dNode;

/* Camera rig at *0x0042C8EC. */
typedef struct R2dRig {
    uint32_t flags;            /* +0x000 */
    int32_t  v04;              /* +0x004 */
    uint8_t  unk08[0x394 - 0x08];
    float    f394;             /* +0x394 */
    float    f398;             /* +0x398 */
    float    v39C[4];          /* +0x39C */
    uint8_t  unk3AC[0x3B0 - 0x3AC];
    R2dNode *node3B0;          /* +0x3B0 */
    uint8_t  unk3B4[0x3B8 - 0x3B4];
    float    f3B8;             /* +0x3B8 */
    uint32_t flags3BC;         /* +0x3BC */
    float    f3C0;             /* +0x3C0 */
    float    f3C4;             /* +0x3C4 */
    float    f3C8;             /* +0x3C8 */
    float    f3CC;             /* +0x3CC */
} R2dRig;

/* Four floats at 0x00417F20. */
typedef struct R2dTint { float a, b, c, d; } R2dTint;
extern R2dTint r2d_tint417F20;         /* 0x00417F20 */
extern float   a50_frameUnits;         /* 0x0042C858 */

/* Light records of 0xC0 bytes; flags word first (0x00417938 + 0xC0*i). */
typedef struct R2dLight { uint32_t flags; uint8_t unk04[0xBC]; } R2dLight;
extern R2dLight r2d_lights417938[20];  /* 0x00417938 */
/* Light set at 0x00418A80. */
typedef struct R2dLightSet {
    uint8_t  unk00[0xC0];
    uint32_t flagsC0;          /* +0xC0 (0x00418B40) */
    uint8_t  unkC4[0xD4 - 0xC4];
    void    *pD4;              /* +0xD4 (0x00418B54) */
    uint8_t  unkD8[0xE8 - 0xD8];
    int32_t  texE8;            /* +0xE8 (0x00418B68) */
    float    fEC;              /* +0xEC (0x00418B6C) */
    uint8_t  unkF0[0x100 - 0xF0];
    uint8_t  data100[4];       /* +0x100 (0x00418B80) */
} R2dLightSet;
extern R2dLightSet r2d_lightSet;       /* 0x00418A80 */
extern const char  r2d_str27724C[];    /* 0x0027724C texture path */
/* Context at *0x0042C8E4. */
typedef struct R2dCtx { uint8_t unk00[0x44]; int32_t v44; uint8_t unk48[0x1E8 - 0x48]; void *list1E8; } R2dCtx;
extern R2dCtx *r2d_ctx;                /* 0x0042C8E4 */

/* Stage director object (the e0000-e5000 helpers). */
typedef struct R2dLink { void *h0; void *h4; void *tgt8; } R2dLink;
typedef struct R2dTrackV { float f0; float f4; float v8[4]; float v18[4]; } R2dTrackV;
typedef struct R2dSlot { void *p00; uint8_t unk04[0x1C - 4]; int32_t state1C; float t20; int32_t n24; } R2dSlot;
typedef struct R2dStage {
    int32_t  key000;           /* +0x000 */
    uint8_t  unk004[0x2E8 - 4];
    int32_t  id2E8;            /* +0x2E8 */
    int32_t  h2EC;             /* +0x2EC stream handle, -1 none */
    int32_t  v2F0;             /* +0x2F0 */
    uint8_t  unk2F4[4];
    int32_t  v2F8;             /* +0x2F8 */
    int32_t  h2FC;             /* +0x2FC */
    uint8_t  unk300[0x3F0 - 0x300];
    float    f3F0;             /* +0x3F0 */
    float    f3F4;             /* +0x3F4 */
    float    f3F8, f3FC, f400, f404; /* +0x3F8..+0x404 */
    uint8_t  unk408[0x510 - 0x408];
    int32_t  v510;             /* +0x510 */
    int32_t  v514;             /* +0x514 */
    uint8_t  unk518[0x534 - 0x518];
    R2dLink  links534[8];      /* +0x534 */
    R2dTrackV trk594[12];      /* +0x594 */
    uint8_t  unk774[0x794 - 0x774];
    float    f794;             /* +0x794 */
    float    f798;             /* +0x798 */
    int32_t  v79C[5];          /* +0x79C */
    float    f7B0;             /* +0x7B0 */
    uint8_t  unk7B4[0x850 - 0x7B4];
    int32_t  v850[5];          /* +0x850 */
    uint8_t  unk864[0x86C - 0x864];
    R2dSlot  slots86C[6];      /* +0x86C (slot k of the 1-based list is slots86C[k - 1]) */
} R2dStage;
typedef void (*R2dSlotFn)(R2dStage *o, int idx);
extern R2dSlotFn r2d_slotExit317C30[];  /* 0x00317C30 */
extern R2dSlotFn r2d_slotEnter317BF0[]; /* 0x00317BF0 */
typedef struct R2dCue { uint32_t pos00; int16_t len04; uint16_t on06; int32_t id08; } R2dCue;
typedef void (*R2dCueFn)(R2dStage *o, R2dCue *c);
typedef struct R2dAnimRow { int32_t id; uint8_t unk04[0x84]; } R2dAnimRow;
extern R2dAnimRow r2_anim317758[];      /* 0x00317758 */
extern int32_t g_acb_3F0A78;           /* 0x003F0A78 */
extern int32_t g_acb_3F0A7C;           /* 0x003F0A7C */
extern int32_t r2d_g3F0A80;            /* 0x003F0A80 */

/* Effect records at 0x003F1B5C (0x144 bytes, 32 of them). */
typedef struct R2dFx { uint32_t flags; int32_t state04; uint8_t unk08[8]; float t10; uint8_t unk14[0x144 - 0x14]; } R2dFx;
extern R2dFx r2c_fx3F1B5C[32];         /* 0x003F1B5C */

/* Generic part record (0x150 bytes) with a model at +0x30. */
typedef struct R2dModel { uint8_t unk00[8]; int32_t i08; uint8_t unk0C[8]; void *p14; } R2dModel;
typedef struct R2dRec150 { uint8_t unk00[0x30]; R2dModel *m30; uint8_t unk34[0x150 - 0x34]; } R2dRec150;

/* Sound bank state 0x003F59D0.. */
extern void   *aec_3F59D0;
extern int32_t aec_3F59D4, aec_3F59DC, aec_3F59E4, aec_3F59E8, aec_3F59EC, aec_3F59F0;
extern int32_t r2d_banks318680[7];     /* 0x00318680 slot indices (0x0004F5D0 family indexes 0x002C8900 with them) */
extern const char *r2d_names3187A0[5]; /* 0x003187A0 */
typedef struct R2dBank { uint8_t unk00[0x14]; uint8_t *data14; uint8_t *body18; } R2dBank;
extern R2dBank aec_recs1C[5];          /* 0x003F59F8 */

/* Active-object list: count and an array of 0x150-byte entries. */
typedef struct R2dEnt { uint8_t unk00[0x0C]; uint32_t flags0C; uint8_t unk10[0x150 - 0x10]; } R2dEnt;
typedef struct R2dList { int32_t count; int32_t unk04; R2dEnt *arr08; } R2dList;

/* Component returned by 0x1D960(o, 0xD). */
typedef struct R2dComp {
    uint8_t unk00[0x14];
    int32_t v14;               /* +0x14 */
    float   f18;               /* +0x18 */
    float   f1C;               /* +0x1C */
    uint8_t unk20[4];
    int   (*fn24)(void *o);    /* +0x24 */
} R2dComp;
typedef struct R2dSlot10 { uint8_t unk00[8]; int32_t v08; int32_t v0C; } R2dSlot10;
extern R2dSlot10 r2d_slots3F5D30[8];   /* 0x003F5D30 */
extern uint8_t   aec_3F5DB0[];         /* 0x003F5DB0 list head */

typedef struct R2dVec4 { float x, y, z, w; } R2dVec4;
/* Mover with two vectors at +0xF8/+0x108 (0x0F5E30). */
typedef struct R2dMover { uint8_t unk000[0xF8]; R2dVec4 vF8; R2dVec4 v108; int32_t v118; } R2dMover;
/* Screen / boss scene object at *0x003F6130. */
typedef struct R2dScnModel { uint8_t unk00[8]; int32_t kind08; uint8_t unk0C[8]; uint8_t *p14; } R2dScnModel;
typedef struct R2dScnNode { uint8_t unk00[0x30]; R2dScnModel *m30; uint8_t unk34[0x64 - 0x34]; float f64; } R2dScnNode;
typedef struct R2dScn { uint8_t unk000[0x8C]; R2dScnNode *node8C; uint8_t unk090[0x1B0 - 0x90]; float f1B0; } R2dScn;
extern R2dScn *b10_scr;                /* 0x003F6130 */
extern void *b10_obj3F6138;            /* 0x003F6138 */
extern void *b10_obj3F6150;            /* 0x003F6150 */
extern void *g_acb_3F60F0;             /* 0x003F60F0 */
/* Hook record at +0x114 of a 0x114400 owner. */
typedef struct R2dHook { uint8_t unk00[4]; void (*fn04)(void); uint8_t unk08[8]; int32_t v10; float f14; uint8_t unk18[4]; int32_t v1C; uint8_t unk20[0x2C - 0x20]; float f2C; float f30; void *owner34; } R2dHook;
typedef struct R2dHookOwner { uint8_t unk000[0x114]; R2dHook hook114; } R2dHookOwner;
typedef struct R2dHookSrcM { uint8_t unk00[0xC4]; uint8_t *rows; } R2dHookSrcM;
typedef struct R2dHookSrc { uint8_t unk00[0x20]; R2dHookSrcM *m20; } R2dHookSrc;

extern float a50_frameSeconds;         /* 0x0042C85C */
extern const R2dVec4 r2d_vec27916C;    /* 0x0027916C */
extern R2dScn *b10_obj3F6134;          /* 0x003F6134 (object with a node at +0x8C) */
/* Timed sound slot inside the scene object (0x54 bytes from +0xDC). */
typedef struct R2dScnSnd { int32_t h00; uint8_t unk04[0xC]; float t10; uint8_t unk14[0x54 - 0x14]; } R2dScnSnd;
typedef struct R2dScnT { uint8_t unk000[0xDC]; R2dScnSnd snd[3]; uint8_t unk1D8[0x200 - 0x1D8]; float t200; float t204; } R2dScnT;
/* Particle-ish list entry (0x28 bytes) linked at +0x20/+0x24. */
typedef struct R2dPEnt { int32_t state; int32_t v04; float f08; int32_t v0C, v10, v14, v18, v1C; struct R2dPEnt *prev20; struct R2dPEnt *next24; } R2dPEnt;
typedef struct R2dPOwner { uint8_t unk00[0x60]; R2dPEnt *head60; } R2dPOwner;
typedef struct R2dTrkObj { uint8_t unk000[0xF8]; int32_t mode0F8; uint8_t unk0FC[8]; uint8_t *ref104; } R2dTrkObj;
typedef struct R2dHook2 { uint8_t unk000[4]; void (*fn04)(void); uint8_t unk008[8]; float f10; uint8_t unk014[0x94 - 0x14]; uint8_t *p94; float f98; uint8_t unk09C[0x11C - 0x9C]; uint8_t *p11C; void *src120; } R2dHook2;
typedef struct R2dHook2Owner { uint8_t unk000[0x14C]; R2dHook2 h; } R2dHook2Owner;
typedef struct R2dSrc20 { uint8_t unk00[0x20]; void *list20; } R2dSrc20;
typedef struct R2dGfxCtl { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[0x64 - 0x50]; int32_t v64; } R2dGfxCtl;
typedef struct R2dGfxPart { uint8_t unk00[0xB8]; uint32_t flagsB8; } R2dGfxPart;
typedef struct R2dGfxPartH { uint8_t unk00[0x14]; R2dGfxPart *p14; } R2dGfxPartH;
typedef struct R2dGfxNode { uint8_t unk00[0x30]; R2dGfxPartH *p30; uint8_t unk34[0x3C - 0x34]; struct R2dGfxNode *next3C; uint8_t unk40[0xD0 - 0x40]; int32_t vD0; } R2dGfxNode;
typedef struct R2dGauge { uint8_t unk00[0x54]; float f54; uint8_t unk58[0x90 - 0x58]; int32_t h90; } R2dGauge;

/* Filter list: nodes {next, ..., +0xC item}; filters are fn(a, b). */
typedef int (*R2dFilter)(int a, int b);
typedef struct R2dFItem { uint8_t unk00[4]; int32_t v04; int32_t v08; } R2dFItem;
typedef struct R2dFNode { struct R2dFNode *next; uint8_t unk04[8]; R2dFItem *item0C; } R2dFNode;
extern R2dFilter r2d_filters3189C0[3];  /* 0x003189C0 */
extern R2dFilter r2c_filter3189CC;     /* 0x003189CC */
extern R2dFNode *aec_list3F5DC4;       /* 0x003F5DC4 */
extern R2dFNode *r2_tail3F60E4;        /* 0x003F60E4 */
/* Object kind/id pair and its components. */
typedef struct R2dKObj { uint8_t unk00[4]; int32_t kind04; int32_t id08; } R2dKObj;
typedef struct R2dKComp { uint8_t unk00[0x34]; int32_t v34; } R2dKComp;
typedef struct R2dKDst { uint8_t unk000[0x70]; float f70; float f74; uint8_t unk078[0x270 - 0x78]; float f270; float f274; } R2dKDst;
typedef struct R2dSwComp { uint8_t unk00[0xDC]; int32_t vDC; uint8_t unkE0[4]; int32_t vE4; } R2dSwComp;
typedef struct R2dGame { int32_t v000; uint8_t unk004[0x308 - 4]; int32_t v308; int32_t v30C; uint8_t unk310[4]; int32_t v314; } R2dGame;

/* List heads and node pools initialised by 0x0ED430. */
typedef struct R2dQNode { uint8_t b[0x10]; } R2dQNode;
extern R2dQNode r2d_q3F5DC0;           /* 0x003F5DC0 */
extern R2dQNode r2d_q3F5DB0;           /* 0x003F5DB0 */
extern R2dQNode r2d_q3F60D0;           /* 0x003F60D0 */
extern R2dQNode r2d_qpool3F5DD0[48];   /* 0x003F5DD0 */
extern R2dQNode r2d_qpool3F5D30[8];    /* 0x003F5D30 */
extern void *r2d_g3F60E0;              /* 0x003F60E0 */
extern void *r2d_g3F60E4;              /* 0x003F60E4 */
/* Scaled render parts (0x0EE660). */
typedef struct R2dSPart { uint8_t unk00[0x8C]; int32_t kind8C; uint8_t unk90[0xD8 - 0x90]; float fD8; float fDC; } R2dSPart;
typedef struct R2dSNode { uint8_t unk00[0x20]; R2dSPart *part20; uint8_t unk24[0x3C - 0x24]; struct R2dSNode *next3C; uint8_t unk40[0x9C - 0x40]; float f9C; } R2dSNode;

/* ---------------------------------------------------------------- callees */
void  sub_001AD9F0(void *dst, const void *a, const void *b);
int   sub_000D9A70(int id);
void  sub_000D1930(R2dPlayer *p);
void  sub_000BD4D0(void *p, int state);
void  sub_000CED00(void *p);
void *sub_0001D290(void *o, int k);
void  sub_000D51E0(R2dRig *r);
void  sub_001BA8F0(void *o);
int   sub_000494D0(int id, const void *pos, int flag);
void  sub_00048250(int h);
int   sub_000847F0(int a, int b);
void  sub_001BA820(void *o);
void  sub_001BA910(void *o, void *part, const int *ids, void *dst);
void  sub_001BA8B0(void *o, int n);
void  sub_001B2020(int h, void *o);
int   sub_00084CE0(const char *path);
void  sub_0001EB80(void *o);
R2dCue *r2b_TrackFire(R2dStage *o, int idx, uint32_t pos, uint32_t base);
void  r2b_TrackMarkBefore(R2dStage *o, int idx, uint32_t lim, uint32_t base);
R2dCueFn sub_000E9BC0(int key, int id);
R2dCueFn sub_000E9C00(int key, int id);
R2dCueFn sub_000E9C40(int key, int id);
int   sub_000E07F0(R2dStage *o);
int   sub_0019A950(int id, int b);
void  sub_00053F20(int a);
void  sub_00053F70(int a);
void  sub_0019AA00(int h, int ms);
void  sub_00054040(void);
uint32_t sub_00053F60(void);
uint32_t sub_00048530(int id);
uint32_t sub_00048560(int id);
void  sub_000E3C00(R2dStage *o);
void  sub_0019AB40(int h);
void  sub_000D0200(R2dPlayer *p, int a, int id);
uint32_t r2d_StageStreamPos(R2dStage *o);
void  sub_000E8220(R2dFx *f);
void  sub_000E82E0(R2dFx *f);
void  sub_000E83A0(R2dFx *f);
void  sub_000E8D90(R2dFx *f);
void  sub_000E8E80(R2dFx *f);
int   sub_000F3140(int id);
void *sub_0001D080(void *list, int kind, int id);
void  sub_001AEDD0(void *o, int v);
int   sub_00048510(int a);
uint8_t *sub_0001D0F0(void *o, int k);
void *sub_0001F210(int a, int b);
void  sub_0001DA40(void *o);
int   sub_0004F6D0(int slot);
int   sub_0004F680(int slot);
void *sub_00053AB0(int size, int a, int line);
void  sub_000512D0(int slot, void *mem);
void  sub_000EC770(void);
uint8_t *sub_00037550(const char *name, int a);
R2dComp *sub_0001D960(void *o, int k);
void  r2_ListDrop(void *o);
void  sub_000362B0(void *o);
void  sub_0001D190(void *o);
void  sub_0001B3F0(void *o);
void  a4c_ListAppend(void *list, void *item);
int   sub_000A2050(void *o, uint8_t **out);
void  r4c_VecAdd(float *d, const float *a, const float *b);
void  sub_001ADB60(R2dVec4 *d, const R2dVec4 *a, const void *m);
int   sub_000F30E0(int k);
void  sub_001B2150(R2dHook *h);
void  sub_001B2160(void *row, R2dHook *h);
void  sub_00113FB0(void);
void *r2c_FindKey(int a, int b);
void  sub_001208A0(void *e, int v);
float sub_001B2770(const void *a, const void *b);
void  sub_00112D30(void);
void  sub_001B21D0(void *list, R2dHook2 *h);
void  sub_00113090(R2dGfxNode *m, R2dGfxCtl *o, int v);
void  sub_000EE760(R2dGfxNode *m, float f);
int   sub_0001BC40(R2dGfxNode *m);
void  sub_000C75E0(R2dGfxNode *m);
int   sub_000EE5F0(void *o);
float sub_00171D50(int kind, int id, int v);
R2dGame *sub_000E0770(void);
void  sub_000F3B30(void *o, int v);
void  sub_000F3B00(void *o, int v);
void  sub_000E0A80(R2dGame *g, int a, int b, int c, int d);
void  sub_000E51F0(R2dGame *g);
void  sub_000E0FB0(int v);
void  sub_0003D860(R2dQNode *n);
void  sub_00112490(void);
void  sub_000F31A0(void);
void  sub_00174B40(void);
void  sub_00189960(void);
void  sub_00171F30(void);
void  sub_0016F6F0(void);
void  sub_001668D0(void);
void  sub_001B3160(R2dSPart *p);
void  sub_000CF330(R2dPlayer *p, const void *pos, float f);
void  r2d_PlayerPlace(R2dPlayer *p, const void *pos);
float sub_000F3C70(void *o);
int   sub_000F3CB0(void *o);
void  sub_000F3BF0(int h, float v, int k);
void  sub_000F3C40(void *o);
void  sub_000D5650(void);

/* ---------------------------------------------------------------- r2d_1 */
void r2d_PlayerSetLink(R2dPlayer *p);
void r2d_TintA(void);
void r2d_TintB(void);
void r2d_PlayerPlace(R2dPlayer *p, const void *pos);
void r2d_PlayerResetD8(R2dPlayer *p);
void r2d_PlayerCheckFall(R2dPlayer *p);
void r2d_PlayerWarp(const void *pos, float angle);
void r2d_RigSetAim(R2dRig *r, const void *vec, float a, float b);
void r2d_RigClear(R2dRig *r);
void r2d_LightsRefresh(void);

#endif
