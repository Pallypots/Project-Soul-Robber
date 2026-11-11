#ifndef R4G_H
#define R4G_H
#include "oogie.h"
#include "shared_decls.h"
/* Area r4g: larger game functions in 0x00190000..0x001BC6D0 (seventh pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4g.csv. */

/* Float to int truncation (cvttss2si in the original); same as RFL_FTOI. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R4G_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R4G_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ scene node and actor (effect callbacks) */
typedef struct R4gNode {
    uint8_t  unk00[0x04];
    int32_t  i04;             /* +0x04 */
    int32_t  kind;            /* +0x08 */
    uint32_t flagsC;          /* +0x0C */
    uint32_t flags10;         /* +0x10 */
    uint8_t  unk14[0x28 - 0x14];
    void    *p28;             /* +0x28 model */
    uint8_t  unk2C[0x50 - 0x2C];
    float    rot50[4];        /* +0x50 */
    float    pos[4];          /* +0x60 */
    float    scale70[4];      /* +0x70 */
    uint8_t  unk80[0xF0 - 0x80];
    int32_t  iF0;             /* +0xF0 */
    int32_t  iF4;             /* +0xF4 */
    uint8_t  unkF8[0x11C - 0xF8];
    int32_t  i11C;            /* +0x11C */
    int32_t  i120;            /* +0x120 */
    int32_t  i124;            /* +0x124 */
    uint32_t flags128;        /* +0x128 */
} R4gNode;

typedef struct R4gActor {
    uint8_t  unk00[0x24];
    int32_t  i24;             /* +0x24 */
    float    f28;             /* +0x28 */
    float    f2C;             /* +0x2C */
    uint8_t  unk30[0x74 - 0x30];
    void    *work;            /* +0x74 per-effect work block */
    void    *fn78;            /* +0x78 */
    void    *fn7C;            /* +0x7C */
    void    *fn80;            /* +0x80 */
    const void *p84;          /* +0x84 */
    const void *p88;          /* +0x88 */
} R4gActor;

typedef struct R4gRec24 { void *obj; int32_t f[8]; } R4gRec24;   /* 0x004000B0 x3 */
extern R4gRec24 r4c_recs4000B0[3];

extern const float r4g_v27ADF0[4];     /* 0x0027ADF0 */
extern const float r4g_v27AE08[4];     /* 0x0027AE08 */
extern const float r4g_v27AE18[4];     /* 0x0027AE18 */
extern const float r4g_v27AE28[4];     /* 0x0027AE28 */
extern const float r4g_v32C5F4[4];     /* 0x0032C5F4 */
extern const uint8_t r4g_d32C614[];    /* 0x0032C614 */
extern const uint8_t r4g_d32C62C[];    /* 0x0032C62C */

void sub_000F5D60(void *o, float a, float b, float c, const float *v);
void sub_000F5DD0(void *o, float a, float b, const float *v);
void sub_00189DA0(void *a, void *b, int c);
void sub_0018F6F0(void *o, void *a);
void sub_0018F760(void *o, void *a);
int  sub_001905E0(void *o, void *a, void *msg);

int  r4g_FxFallSpawn(R4gNode *o, R4gActor *a);   /* 0x00190710 */

/* slot records of the effect spawner at 0x00192180 */
typedef struct R4gRec4C { R4gNode *obj; R4gActor *actor; float f08; uint8_t unk0C[4]; int32_t mode10; uint8_t unk14[0x30]; float f44, f48; } R4gRec4C; /* 0x00400390 x10 */
extern R4gRec4C r4c_recs400390[10];

extern const float r4g_v27AEF0[4], r4g_v27AF04[4], r4g_v27AF14[4], r4g_v27AF24[4];
extern const uint8_t r4g_d32C6A8[], r4g_d32C6C8[];
int   sub_00190900(void *o, void *a);
void  sub_001909C0(void *o, void *a);

int   sub_00191EA0(void *o, void *a, void *msg);
float sub_00171D50(int kind, int id, int v);
int   r4g_FxSpawnB(R4gNode *o, R4gActor *a, int mode);   /* 0x00192180 */

/* ------------------------------------------------------------ sound pool layout (0x001995A0) */
typedef struct R4gPool { uint32_t size0; uint32_t size1; uint8_t unk08[0x10]; } R4gPool;  /* 0x003316A4 x11 */
typedef struct R4gCueRec { int32_t pool; int32_t wave0; int32_t wave1; int32_t unk0C; } R4gCueRec; /* 0x00330F30 x119 */
typedef struct R4gWaveSize { uint32_t size; uint32_t unk04; } R4gWaveSize;   /* 0x0041344C, 8 bytes each */
extern R4gPool     r4g_pools3316A4[11];
extern R4gCueRec   r4c_cues330F30[119];
extern R4gWaveSize r4g_waves41344C[];
extern uint32_t    r4g_poolBase402750;    /* 0x00402750 */
extern uint32_t    r4g_poolTotal402754;   /* 0x00402754 */
void r4g_SndPoolLayout(void);             /* 0x001995A0 */

/* ------------------------------------------------------------ static model draw node (0x001B8FB0) */
typedef struct R4gBoneDesc {   /* 0x50 bytes */
    uint16_t id00;            /* +0x00 */
    uint16_t child02;         /* +0x02 first child, 0xFFFF = none */
    uint16_t sib04;           /* +0x04 next sibling, 0xFFFF = none */
    int16_t  bone06;          /* +0x06 */
    int32_t  off08;           /* +0x08 offset of the mesh data */
    uint8_t  unk0C[4];
    float    m10[16];         /* +0x10 bind matrix */
} R4gBoneDesc;
typedef struct R4gSubInfo { int32_t f00; R4gBoneDesc *bones04; uint8_t unk08[4]; int32_t size0C; } R4gSubInfo;  /* 0x10 bytes */
typedef struct R4gModelInfo { uint8_t *base; R4gSubInfo *subs; } R4gModelInfo;
typedef struct R4gModel {     /* model / mesh owning the draw nodes */
    uint8_t  unk00[0xB4];
    void    *texB4;           /* +0xB4 (texture, see r4b) */
    void    *iB8;             /* +0xB8 */
    R4gModelInfo *infoBC;     /* +0xBC */
    uint8_t  unkC0[0xCC - 0xC0];
    float    vCC[4];          /* +0xCC */
    uint8_t  unkDC[0xE0 - 0xDC];
    int32_t  iE0, iE4;        /* +0xE0 */
} R4gModel;
typedef struct R4gMeshDesc { uint8_t unk00[4]; uint32_t flags4; } R4gMeshDesc;
typedef struct R4gCam { uint8_t unk000[0x1F0]; float m1F0[16]; } R4gCam;
typedef struct R4gDrawNode {  /* 0x108 bytes */
    float    m00[16];         /* +0x00 */
    float    m40[16];         /* +0x40 world matrix */
    struct R4gDrawNode *parent80; /* +0x80 */
    struct R4gDrawNode *sib84;    /* +0x84 */
    struct R4gDrawNode *child88;  /* +0x88 */
    int32_t  type8C;          /* +0x8C */
    uint8_t  unk90[0xA0 - 0x90];
    struct R4gDrawNode *prevA0; /* +0xA0 previously drawn node */
    uint8_t  unkA4[0xB0 - 0xA4];
    int32_t  iB0;             /* +0xB0 */
    int32_t  subB4;           /* +0xB4 */
    R4gBoneDesc *descB8;      /* +0xB8 */
    R4gMeshDesc *meshBC;      /* +0xBC */
    R4gModel *modelC0;        /* +0xC0 */
    int32_t  itemsC4;         /* +0xC4 */
    void    *texC8;           /* +0xC8 */
    void    *selCC;           /* +0xCC */
    void    *texD0;           /* +0xD0 */
    int32_t  iD4;             /* +0xD4 */
    int32_t  texD8;           /* +0xD8 */
    float    vDC[4];          /* +0xDC */
    float    vEC[4];          /* +0xEC */
    uint8_t  unkFC[0x100 - 0xFC];
    int32_t  fmt100;          /* +0x100 */
    int32_t  fmt104;          /* +0x104 */
} R4gDrawNode;
extern void   *r4_g40F324;            /* 0x0040F324 */
extern void   *r4_g40F208;            /* 0x0040F208 */
extern R4gCam *r4b_g40F334;           /* 0x0040F334 current camera */
extern int32_t r4b_g41312C;           /* 0x0041312C */
uint32_t *sub_001B2A10(uint32_t *cmd, void *sel);
uint32_t *sub_001B26A0(uint32_t *cmd, void *tex);
void      sub_001A69C0(int a, int b);
uint32_t *sub_001B8EE0(R4gDrawNode *n, uint32_t *cmd);
void      sub_001A6C90(const float *m);
void      sub_001A2350(int i, const float *m);
int       sub_001A3080(R4gDrawNode *n);
uint32_t *sub_001B3340(uint32_t *cmd, int items);
uint32_t *r4g_DrawStaticNode(uint32_t *cmd, R4gDrawNode *n);   /* 0x001B8FB0 */
void      r4g_MeshLinkNode(R4gModel *m, R4gDrawNode *base, int idx); /* 0x001B8C80 */

/* ------------------------------------------------------------ skinned draw node link (0x001B8410) */
typedef struct R4gSkinNode {  /* 0x110 bytes */
    float    m00[16];         /* +0x00 */
    float    m40[16];         /* +0x40 */
    struct R4gSkinNode *parent80; /* +0x80 */
    struct R4gSkinNode *sib84;    /* +0x84 */
    struct R4gSkinNode *child88;  /* +0x88 */
    uint8_t  unk8C[0xB0 - 0x8C];
    int32_t  iB0;             /* +0xB0 */
    int32_t  subB4;           /* +0xB4 */
    R4gBoneDesc *descB8;      /* +0xB8 */
    R4gMeshDesc *meshBC;      /* +0xBC */
    R4gModel *modelC0;        /* +0xC0 */
    int32_t  itemsC4;         /* +0xC4 */
    void    *texC8;           /* +0xC8 */
    void    *selCC;           /* +0xCC */
    void    *texD0;           /* +0xD0 */
    int32_t  iD4;             /* +0xD4 */
    float    vD8[4];          /* +0xD8 */
    int32_t  fmtE8, fmtEC;    /* +0xE8 */
    uint8_t  unkF0[0xFC - 0xF0];
    int16_t  boneFC;          /* +0xFC */
    uint8_t  unkFE[2];
    float    v100[4];         /* +0x100 */
} R4gSkinNode;
void r4g_SkinLinkNode(R4gModel *m, R4gSkinNode *base, int idx);   /* 0x001B8410 */

/* ------------------------------------------------------------ music tracks (0x0019B6A0, 0x0019B800) */
typedef struct R4gSeqPart { int16_t id; uint16_t vol; uint16_t a; uint16_t b; } R4gSeqPart;
typedef struct R4gSeq {       /* 0x003317C0 x612, 0x24 bytes */
    union {
        struct { int16_t bank; int8_t chan; uint8_t b3; } h;
        int32_t bits;         /* parts in bits 28..31 */
    } u;
    R4gSeqPart parts[4];      /* +0x04 */
} R4gSeq;
typedef struct R4gTrkPart { int32_t id; int32_t vol; int32_t a; int32_t b; } R4gTrkPart;
typedef struct R4gTrack {     /* 0x004019D8 x3, 0x60 bytes */
    int32_t  used00;          /* +0x00 */
    int32_t  busy04;          /* +0x04 */
    int32_t  state08;         /* +0x08 */
    int32_t  snd0C;           /* +0x0C index into r4d_snd3317C0 */
    int32_t  chan10;          /* +0x10 */
    uint8_t  unk14[4];
    int32_t  parts18;         /* +0x18 number of parts */
    R4gTrkPart part[3];       /* +0x1C */
    uint8_t  unk4C[0x5C - 0x4C];
    int32_t  n5C;             /* +0x5C pause depth */
} R4gTrack;
extern R4gTrack r4d_tracks4019D8[3];
extern R4gSeq   r4d_snd3317C0[612];
extern int32_t  r4d_g402748, r4d_g401B28;
int    sub_0019A900(int i);
void   sub_001AB4A0(int bank, int kind);
void   sub_001ABD10(int a, int i);
void   sub_001ABFE0(int i, int a);
void   sub_001ABF20(int a, int i);
void   sub_0019ABB0(R4gTrack *t, int k, int vol, int i);   /* regargs: t=EAX k=ESI vol=EDX */
int    r4g_TrackStart(int snd, int unused1, int unused2); /* 0x0019B6A0 (callers push 3 args) */
void   r4g_TrackResume(int i, int unused);  /* 0x0019B800 (callers push 2 args) */

/* ------------------------------------------------------------ music player open (0x001ABD10) */
typedef struct R4gMus {       /* 0x0040E358 x4, 0x70 bytes */
    int32_t  cue00;           /* +0x00 cue id, -1 when free */
    int32_t  mode04;          /* +0x04 engine index */
    uint8_t  unk08[0x24 - 0x08];
    int32_t  id24;            /* +0x24 */
    uint8_t  b28;             /* +0x28 */
    uint8_t  paused29;        /* +0x29 */
    uint8_t  unk2A[0x70 - 0x2A];
} R4gMus;
typedef struct R4gCueRec14 { uint8_t unk00[0x14]; } R4gCueRec14;      /* 0x14-byte cue records */
typedef struct R4gCueMap { int32_t id; int32_t cueA; int32_t cueB; } R4gCueMap;   /* 0x0027B720 x16 */
typedef struct R4gDrvMsg { int32_t kind; int32_t x; int32_t f08; int32_t f0C; } R4gDrvMsg;
extern R4gMus      r4f_mus40E358[4];
extern void       *r4f_musPlay40E300[];   /* 0x0040E300 */
extern void       *r4f_engines40C868[];   /* 0x0040C868, indexed by the driver mode */
extern int32_t     r4d_drvMode40E348;     /* 0x0040E348 */
extern int32_t     aac_g365158, aac_g36515C, aac_g365160;
extern R4gCueRec14 r4f_cues338858[], r4f_cues33AE40[];
extern R4gCueMap   r4f_cueMap27B720[16];
extern void       *r4f_playA40E5CC, *r4f_playB40E34C;
extern int32_t     r4f_curA40E5D0, r4f_curB40C864;
extern int32_t     r4g_fail40C860;        /* 0x0040C860 failed open count */
int    OOG_STDCALL sub_0022268D(void *eng, R4gCueRec14 *c, uint32_t *out);
int    OOG_STDCALL sub_002226C0(void *eng, R4gDrvMsg *m, void *out);
int    sub_001ABC10(int a, int id);
void   sub_001A7A70(void);
void   r4g_MusOpen(int unused, int id);   /* 0x001ABD10 */

/* ------------------------------------------------------------ 0x180-byte bone node link (0x001B1200) */
typedef struct R4gBoneDesc2 { uint16_t id00; uint16_t child02; uint16_t sib04; uint8_t unk06[2]; int32_t rel08; uint8_t unk0C[4]; float m10[16]; } R4gBoneDesc2;
typedef struct R4gBoneOwner { uint8_t unk00[0xBC]; void **imgBC; } R4gBoneOwner;
typedef struct R4gBone180 {   /* 0x180 bytes */
    float    m00[16];         /* +0x00 local matrix */
    float    m40[16];         /* +0x40 world matrix */
    struct R4gBone180 *parent80; /* +0x80 */
    struct R4gBone180 *sib84;    /* +0x84 */
    struct R4gBone180 *child88;  /* +0x88 */
    uint8_t  unk8C[0xB0 - 0x8C];
    int32_t  iB0;             /* +0xB0 */
    int32_t  idxB4;           /* +0xB4 */
    R4gBoneOwner *ownerB8;    /* +0xB8 */
    uint8_t  xfBC[0x17C - 0xBC]; /* +0xBC decomposed transform */
    int32_t  i17C;            /* +0x17C */
} R4gBone180;
R4gBoneDesc2 *sub_001AE8E0(void *img, int k);
void      sub_001AE060(void *xf, const float *m);
void      r4g_BoneLinkNode(R4gBoneOwner *m, R4gBone180 *base, int idx);   /* 0x001B1200 */

/* ------------------------------------------------------------ boot loading thread (0x001A13E0) */
typedef struct R4gLoadCtx { uint8_t unk00[4]; int32_t state04; int32_t go08; } R4gLoadCtx;
void   sub_000580D0(void);
void   sub_001A1AC0(void);
void   sub_0019B9E0(void);
void   sub_0019B9F0(void);
void   sub_000DFD40(int *a, int *b);
void   sub_000487F0(int a, int b, int c);
int    sub_00048820(int a, int b, int c);
void   sub_00048860(int a, int b, int c);
int    sub_00048890(int a, int b, int c);
void   sub_0019BEB0(int a);
void   sub_0006C030(void);
int    sub_0006D350(void);
void   sub_000325A0(int a);
int    sub_0006DA80(void);
void   sub_0006C070(void);
void   sub_00032140(int a, int b, int c);
void   sub_00058670(void);
void   sub_001A13D0(void);
void   sub_000488C0(int a, int b, int c);
void   sub_00079340(void);
void   sub_001A0D70(void);
void   sub_00058190(void);
void   r4g_BootLoadThread(R4gLoadCtx *c);   /* 0x001A13E0 */

/* ------------------------------------------------------------ game main (0x0019BCF0) */
extern uint64_t a50_frameCounter0;     /* 0x0042C918 64-bit frame counter */
void   sub_001A5500(void);
void   sub_0004EC40(void);
void   sub_0004EB50(void);
void   sub_00058780(void);
void   sub_0019D680(void);
void   sub_000583C0(void);
void   sub_0005EB50(void);
void   sub_0005E9B0(void);
void   sub_0005E930(void);
void   sub_0019BC60(void);
void   sub_0004F0B0(void);
void   sub_0004F4C0(void);
void   sub_00049470(void);
void   sub_001A53F0(void);
void   sub_001BA6B0(void);
void   sub_00053C40(void);
void   r4g_GameMain(void);            /* 0x0019BCF0 */

/* ------------------------------------------------------------ model ground snap callback (0x00196B40) */
typedef struct R4gHitObj { uint8_t unk00[0x20]; float *mtx20; } R4gHitObj;
typedef struct R4gSnapArg {
    uint8_t  unk00[0x10];
    R4gHitObj *obj10;         /* +0x10 */
    float    scale14;         /* +0x14 */
    float    scale18;         /* +0x18 */
    float    off1C[3];        /* +0x1C */
} R4gSnapArg;
typedef struct R4gHit { uint8_t unk00[0x40]; float pos40[4]; } R4gHit;
typedef struct R4gCtxE4 { uint8_t unk00[0x54]; void *p54; } R4gCtxE4;
extern R4gCtxE4 *a80_ctx42C8E4;     /* 0x0042C8E4 */
int     sub_000F5CD0(void *o, int a, int b);
void   *sub_00080970(void);
void    sub_000824F0(void *ctx, void *pool, const float *from, const float *to, void *list, void *out);
void    r4g_ModelSnapToGround(float *m, R4gSnapArg *p);   /* 0x00196B40 */

/* ------------------------------------------------------------ pop effect spawner (0x00198080) */
typedef struct R4gPopRec {    /* *0x00401830 x4, 0x40 bytes */
    R4gNode  *obj;            /* +0x00 */
    R4gActor *actor;          /* +0x04 */
    int32_t  idx08;           /* +0x08 */
    int16_t  s0C, s0E;        /* +0x0C */
    int16_t  s10, s12;        /* +0x10 */
    uint8_t  unk14[4];
    float    f18;             /* +0x18 vertical speed */
    float    f1C;             /* +0x1C */
    float    v20[4];          /* +0x20 velocity */
    float    v30[4];          /* +0x30 direction to the player */
} R4gPopRec;
typedef struct R4gPlayer { uint8_t unk00[0x60]; float pos[4]; } R4gPlayer;
extern float a50_frameUnits;          /* 0x0042C858 */
void  sub_001AD9F0(float *d, const float *a, const float *b);
float sub_000F5F50(const float *v);
void  sub_001AD7E0(float *d, const float *s);
void  r4g_PopAim(R4gPopRec *rec);     /* 0x00196E70 regargs: rec=ESI */
extern R4gPopRec *r4c_g401830;        /* 0x00401830 */
extern const float r4g_v27B1B0[4], r4g_v27B1C4[4], r4g_v27B1D4[4], r4g_v27B1E4[4];
extern const uint8_t r4g_d32C858[], r4g_d32C864[];

int   sub_00197D90(void *o, void *a);
void  sub_00197040(void *o, void *a);
int   sub_00197160(void *o, void *a, void *msg);
void  sub_00197650(void *o, void *x);
void  sub_0001C9E0(void *o, int unused, void (*fn)(void *, void *));
void  sub_0001EF00(void *o, const float *v);
int   r4g_FxPopSpawn(R4gNode *o, R4gActor *a);   /* 0x00198080 */

/* ------------------------------------------------------------ scene play loop (0x001A0970) */
typedef struct R4gScene { int32_t kind; } R4gScene;
extern int32_t r4g_skipIds27B380[4];  /* 0x0027B380 scenes that may be skipped with button 0x40 too */
extern int32_t r4g_scene403970;       /* 0x00403970 current scene id */
extern int32_t r4g_g403980;           /* 0x00403980 */
extern int32_t a19_g403940, a9c_g403968, r4f_g404338, r4e_g404334, a19_g403974, a19_g40396C;
int    sub_001A0CE0(void);
int    sub_001A7DC0(void);
int    sub_001A80C0(void);
void   sub_001A01A0(int id);
void   sub_001A0020(int id, int prev);
void   sub_001A0200(void);
uint32_t sub_001A9130(int pad);
void   sub_0019FEF0(float a, int b, int c, int d, int e, int f);
void   sub_001A1090(R4gScene *s, int a);
void   sub_0019FE60(R4gScene *s);
void   r4g_ScenePlayLoop(R4gScene *s);   /* 0x001A0970 */

#endif
