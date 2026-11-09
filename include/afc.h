/* Area afc (third pass over 0x000F0000-0x000FFFFF): boss and actor helpers. Names inferred. */
#ifndef AFC_H
#define AFC_H
#include "oogie.h"

typedef struct AfcVec4 { float x, y, z, w; } AfcVec4;

/* Object with a +0x14 sub-object pointer (animation/model node; Hypothesis). */
typedef struct AfcNode {
    uint8_t  unk00[0x14];
    struct AfcModel *model;    /* +0x14 */
} AfcNode;
typedef struct AfcModel {
    uint8_t  unk00[0xB8];
    uint32_t flagsB8;          /* +0xB8 */
    uint8_t  flagsBC;          /* +0xBC */
} AfcModel;

/* Flag holder reached through +0x8C/+0x90 of an actor. */
typedef struct AfcPart {
    uint8_t  unk00[0x10];
    uint32_t flags;            /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    AfcNode *node;             /* +0x30 */
} AfcPart;

struct AfcActor;
typedef void (*AfcActorStateFn)(void *ctx, struct AfcActor *o);

/* Actor/boss object (Hypothesis: boss actor). */
typedef struct AfcActor {
    uint8_t  unk00[0x08];
    int32_t  type;             /* +0x08 */
    uint8_t  unk0C[0x30 - 0x0C];
    AfcNode *node;             /* +0x30 */
    uint8_t  unk34[0x3C - 0x34];
    struct AfcActor *next;     /* +0x3C */
    uint8_t  unk40[0x68 - 0x40];
    float    stateTime;        /* +0x68 */
    int32_t  state;            /* +0x6C */
    int32_t  prevState;        /* +0x70 */
    AfcActorStateFn *enterFns; /* +0x74 */
    uint8_t  unk78[0x7C - 0x78];
    AfcActorStateFn *exitFns;  /* +0x7C */
    uint8_t  unk80[0x8C - 0x80];
    AfcPart *part8C;           /* +0x8C */
    AfcPart *part90;           /* +0x90 */
    uint8_t  unk94[0x9C - 0x94];
    int32_t  v9C;              /* +0x9C */
    AfcVec4  vecA0;            /* +0xA0 */
    float    fB0;              /* +0xB0 */
    float    fB4;              /* +0xB4 */
    uint8_t  unkB8[0xBC - 0xB8];
    int16_t  wBC;              /* +0xBC */
    uint8_t  unkBE[0xD0 - 0xBE];
    int32_t  vD0;              /* +0xD0 */
    uint8_t  unkD4[0xD8 - 0xD4];
    AfcVec4  vecD8;            /* +0xD8 */
    float    fE8;              /* +0xE8 */
    int32_t  vEC;              /* +0xEC */
    float    fF0;              /* +0xF0 */
    uint8_t  unkF4[0x118 - 0xF4];
    AfcVec4  vec118;           /* +0x118 */
    uint8_t  unk128[0x178 - 0x128];
    float    f178;             /* +0x178 */
    uint8_t  unk17C[0x184 - 0x17C];
    AfcVec4  vec184;           /* +0x184 */
} AfcActor;

/* Same actor viewed for the +0xA4 word (separate view keeps offsets readable). */
typedef struct AfcActorA4 {
    uint8_t  unk00[0x8C];
    AfcPart *part8C;           /* +0x8C */
    uint8_t  unk90[0xA4 - 0x90];
    int16_t  wA4;              /* +0xA4 */
} AfcActorA4;

/* Boss state block cleared by afc_BossStateReset (0x000F3AA0). */
typedef struct AfcBossState {
    uint8_t  unk00[0x4C];
    int32_t  v4C;              /* +0x4C */
    int32_t  v50;              /* +0x50 */
    float    f54, f58, f5C;    /* +0x54 */
    int32_t  v60, v64;         /* +0x60 */
    float    f68;              /* +0x68 */
    int32_t  v6C, v70, v74, v78, v7C, v80; /* +0x6C */
    float    f84, f88;         /* +0x84 */
} AfcBossState;

/* Multi-part object: parts at +0x30, stride 0x150. */
typedef struct AfcSubPart {
    AfcNode *node;
    uint8_t  unk04[0x150 - 4];
} AfcSubPart;
typedef struct AfcMulti {
    uint8_t    unk00[0x08];
    int32_t    kind;           /* +0x08 */
    uint8_t    unk0C[0x30 - 0x0C];
    AfcSubPart parts[1];       /* +0x30 */
} AfcMulti;

/* Boss manager at g_acb_bossMgr. */
typedef struct AfcBossDraw {
    uint8_t  unk00[0x90];
    uint32_t flags90;          /* +0x90 */
} AfcBossDraw;
typedef struct AfcBossMgr {
    uint8_t  unk00[0xBC];
    AfcBossDraw *draw;         /* +0xBC */
    uint8_t  unkC0[0x100 - 0xC0];
    int32_t  v100;             /* +0x100 */
    int32_t  v104;             /* +0x104 */
    uint8_t  unk108[0x114 - 0x108];
    float    f114;             /* +0x114 */
    float    f118;             /* +0x118 */
    float    f11C;             /* +0x11C */
    uint8_t  unk120[0x128 - 0x120];
    int32_t  handle128;        /* +0x128 */
} AfcBossMgr;

/* Allocated record from sub_0001F210. */
typedef struct AfcAlloc {
    uint8_t  unk00[0x08];
    void    *data;             /* +0x08 */
} AfcAlloc;

extern AfcBossMgr *g_acb_bossMgr;   /* 0x003F610C */
extern float aec_fps42C964;         /* 0x0042C964 */
extern AfcAlloc *afc_listHead;      /* 0x003F60F4 */
extern void     *afc_listData;      /* 0x003F60F8 */
extern int32_t   afc_g3F60FC;       /* 0x003F60FC */
extern void     *ae0_ptr3F6100;     /* 0x003F6100 */
extern int32_t   afc_g3F6104;       /* 0x003F6104 */
extern int32_t   afc_g3F6108;       /* 0x003F6108 */

int      sub_001AEE50(void *obj, int b);
void     sub_001AEDD0(void *a, int b);
int      sub_000F3140(int kind);
void     sub_00048250(int h);
void     sub_00180A60(void);
void     sub_00181DA0(void);
void     sub_001827A0(void);
void     sub_0017D6A0(void);
int      sub_0001BC40(void *o);
void     sub_001ADB60(AfcVec4 *d, AfcVec4 *s, float k);
void     sub_001AD9F0(AfcVec4 *d, void *a, void *b);
void     sub_001AD7E0(AfcVec4 *d, AfcVec4 *s);
float    sub_001A3F50(float x);
AfcActor *sub_00100110(AfcActor *o);
AfcActor *sub_000FBAF0(AfcActor *o);
AfcActor *sub_000FE3D0(AfcActor *o);
void     sub_000F3D10(AfcPart *p, AfcActor *o, int a);
void     sub_000832D0(void *o, int anim);
int      sub_001C7EE1(void);
void     sub_000F62C0(AfcActor *o, int a);
void     sub_000ED560(int a);
AfcAlloc *sub_0001F210(int a, int b);
void     sub_0001DA40(AfcAlloc *a);
void     sub_00106340(void);
void     sub_0010C830(void);
void     sub_00108B00(void);
void     sub_000F3F40(void);
void     sub_000EED80(void);
void     sub_001011F0(void);
void     sub_00106010(void);


/* Transform source: matrix pointer +0x20, rotation +0x50, position +0x60, scale +0x70. */
typedef struct AfcXform {
    uint8_t  unk00[0x20];
    AfcVec4 *matrix;           /* +0x20, 4 rows */
    uint8_t  unk24[0x50 - 0x24];
    float    rotX, rotY, rotZ; /* +0x50 */
    uint8_t  unk5C[0x60 - 0x5C];
    AfcVec4  pos;              /* +0x60 */
    float    sclX, sclY, sclZ; /* +0x70 */
} AfcXform;

typedef struct AfcBossComp5 {
    uint8_t  unk00[0x5C];
    float    f5C;              /* +0x5C */
    uint32_t v60;              /* +0x60 */
} AfcBossComp5;

void    *sub_0001D960(void *o, int kind);
int      sub_0019BE60(int mask);
void     sub_001AD940(AfcVec4 *m);
void     sub_001ADBA0(AfcVec4 *d, AfcVec4 *s, float k);
void     sub_001AD8B0(AfcVec4 *d, AfcVec4 *s, float a);
void     sub_001AD8E0(AfcVec4 *d, AfcVec4 *s, float a);
void     sub_001AD910(AfcVec4 *d, AfcVec4 *s, float a);
void     afc_VecCopy(AfcVec4 *d, AfcVec4 *s);   /* 0x000F5D40 */
void     sub_000ED630(int a, int b, int c, int d, int e);
AfcActor *afc_DispatchByType(AfcActor *o);
void     afc_SetBothAnims(AfcActor *o, int anim);
int      afc_NodeActive(AfcActor *o);
void     afc_SetVisible(void *o, int16_t on);

/* Singleton actors at 0x003F6114 / 0x003F611C (Hypothesis: boss body and helper). */
typedef struct AfcSingleton {
    uint8_t  unk00[0x8C];
    AfcPart *part8C;           /* +0x8C */
    AfcPart *part90;           /* +0x90 */
    uint8_t  unk94[0x9C - 0x94];
    int32_t  v9C;              /* +0x9C */
    float    fA0;              /* +0xA0 */
    uint8_t  unkA4[0xA8 - 0xA4];
    int16_t  wA8;              /* +0xA8 */
    uint8_t  unkAA[0xBC - 0xAA];
    int16_t  wBC;              /* +0xBC */
    uint8_t  unkBE[0xE8 - 0xBE];
    int32_t  vE8;              /* +0xE8 */
    uint8_t  unkEC[0x1B0 - 0xEC];
    int32_t  v1B0;             /* +0x1B0 */
    uint8_t  unk1B4[0x1B8 - 0x1B4];
    float    f1B8;             /* +0x1B8 */
    int16_t  w1BC;             /* +0x1BC */
} AfcSingleton;
typedef struct AfcMsg {
    uint8_t  unk00[0x0C];
    int16_t  w0C;              /* +0x0C */
} AfcMsg;

extern AfcSingleton *afc_body;      /* 0x003F6114 */
extern AfcActor     *afc_bodyState; /* 0x003F6118 */
extern AfcSingleton *afc_helper;    /* 0x003F611C */
extern AfcVec4       afc_vec318E18; /* 0x00318E18 */

int      sub_000F30E0(int kind);
void    *sub_00053AB0(int size, int a, int b);
void     sub_00053880(void *p);
void     sub_000F69E0(void *p);
void     sub_000FB580(AfcActor *o, int a);
float    afc_VecLengthXZ(AfcVec4 *v);
AfcSingleton *afc_GetHelper(void);

extern AfcSingleton *afc_minion;      /* 0x003F6120 */
extern AfcActor     *afc_minionState; /* 0x003F6124 */
extern AfcSingleton *b10_ctl;         /* 0x003F6128 */
extern AfcActor     *b10_res3F612C;   /* 0x003F612C */
extern float         a50_frameUnits;  /* 0x0042C858 */

#endif
