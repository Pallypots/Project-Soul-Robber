#ifndef R4B_H
#define R4B_H
#include "oogie.h"
#include "shared_decls.h"
/* Area r4b: remaining game functions in 0x00190000..0x001BC6D0 (second pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4b.csv. */

/* ------------------------------------------------------------ scene nodes (0x001B0E00..0x001B2730) */
typedef struct R4bHook {      /* hook list entry walked by 0x001B24E0 */
    struct R4bHook *next;     /* +0x00 */
    uint32_t unk04;
    void (*fn)(void *dl, void *node, struct R4bHook *h); /* +0x08 */
} R4bHook;
typedef void (*R4bNodeFn)(void *dl, void *node);   /* dl: display-list pointer passed through 0x001B24E0 */

typedef struct R4bPart {      /* 0x180-byte part record */
    uint8_t  unk000[0x40];
    float    m40[16];         /* +0x40 */
    uint8_t  unk080[0x8C - 0x80];
    int32_t  type8C;          /* +0x8C */
    uint8_t  unk090[0xBC - 0x90];
    float    mBC[16];         /* +0xBC */
    float    mFC[16];         /* +0xFC */
    float    m13C[16];        /* +0x13C */
    uint8_t  unk17C[0x180 - 0x17C];
} R4bPart;

typedef struct R4bSkel { uint8_t unk00[0x1C]; int32_t root1C; } R4bSkel;
typedef struct R4bTexInfo { uint8_t unk00[0x0C]; int32_t size0C; } R4bTexInfo;

typedef struct R4bNode {
    float    m00[16];         /* +0x00 local matrix */
    float    m40[16];         /* +0x40 world matrix */
    struct R4bNode *parent;   /* +0x80 */
    struct R4bNode *next;     /* +0x84 */
    struct R4bNode *child;    /* +0x88 */
    int32_t  type8C;          /* +0x8C 0..17 */
    int32_t  i90;             /* +0x90 */
    float    f94;             /* +0x94 */
    void    *p98;             /* +0x98 per-type entry */
    R4bNodeFn *fns9C;         /* +0x9C per-type null-terminated function list */
    int32_t  iA0;             /* +0xA0 */
    struct R4bNode *linkA4;   /* +0xA4 next node in the same bucket */
    R4bHook *hooksA8;         /* +0xA8 */
    R4bHook *hooksAC;         /* +0xAC */
    int32_t  iB0;             /* +0xB0 */
    void    *texB4;           /* +0xB4 */
    void    *selB8;           /* +0xB8 */
    void    *pBC;             /* +0xBC */
    int32_t  count;           /* +0xC0 parts */
    R4bPart *parts;           /* +0xC4 */
    int32_t  iC8;             /* +0xC8 */
    int32_t  iCC;             /* +0xCC */
    float    colD0[4];        /* +0xD0 */
    int32_t  iE0, iE4;        /* +0xE0 */
    int32_t  iE8, iEC;        /* +0xE8 */
} R4bNode;

typedef struct R4bBone { uint8_t unk[0x130]; } R4bBone;
typedef struct R4bSkin {
    uint8_t  unk00[0xB0];
    int32_t  count;           /* +0xB0 */
    R4bBone *bones;           /* +0xB4 */
    uint8_t  unkB8[0xC4 - 0xB8];
    float    fC4;             /* +0xC4 */
    uint8_t  unkC8[0xD8 - 0xC8];
    float    fD8;             /* +0xD8 */
} R4bSkin;
typedef struct R4bSkinRef { uint8_t unk00[0xB4]; struct { uint8_t unk00[0xC4]; int32_t iC4; } *ownerB4; } R4bSkinRef;

extern R4bNode *r4_g412F80[0x33]; /* 0x00412F80 */
extern R4bNode *r4_g413060[0x33]; /* 0x00413060 */
extern void   *r4_g40F324;
extern void *r4_g40F208;
extern int32_t r4b_g40F330, r4b_g40F388;
typedef struct R4bCam R4bCam;
extern R4bCam *r4b_g40F334;    /* 0x0040F334 current camera */
extern int32_t r4b_g41312C;
extern void   *r4b_g377FA8[18];
extern R4bNodeFn *r4b_g378040[18];
extern float   r4b_g40F20C[4];

void sub_001B05E0(void *a, int b);
void sub_001B0E20(void *bone, float t);
void sub_001B1200(R4bNode *n, R4bPart *base, int idx);
void sub_001B25B0(void *n);
void r4_MatCopyRotation(float *d, const float *s);
uint32_t *r4_Set40F324(uint32_t *cmd, void *b);      /* 0x001B2A10, returns cmd */
uint32_t *r4_Select40F208(uint32_t *cmd, void *b);   /* 0x001B26A0, returns cmd */
void sub_001A69C0(int a, int b);
void sub_001A32F0(void *n, void *p);
void sub_001ADE10(float *m, const float *a, const float *b, const float *c, const float *d);


/* 0x001B13F0: part with a skeleton bone (same layout as R4Part in r4.h) */
typedef struct R4bSkelMats { uint8_t unk00[0xB4]; uint8_t *mats; } R4bSkelMats; /* 0x130-byte bone matrices */
typedef struct R4bPartOwner { uint8_t unk00[0xC8]; R4bSkelMats *skel; } R4bPartOwner;
typedef struct R4bBonePart {
    uint8_t       unk000[0xB4];
    int32_t       boneB4;     /* +0xB4 */
    R4bPartOwner *ownerB8;    /* +0xB8 */
    uint8_t       unkBC[0x17C - 0xBC];
    int32_t       i17C;       /* +0x17C */
} R4bBonePart;

/* ------------------------------------------------------------ meshes with 0x108-byte items (0x001B3070..0x001B32D9) */
typedef struct R4bMeshSrc { uint8_t unk00[0x38]; int32_t slot38; } R4bMeshSrc;
typedef struct R4bMeshItem {  /* 0x108 bytes */
    uint8_t      unk000[0x30];
    float        v30[4];      /* +0x30 */
    float        m40[16];     /* +0x40 */
    void        *parent80;    /* +0x80 */
    uint8_t      unk084[0x8C - 0x84];
    int32_t      type8C;      /* +0x8C */
    uint8_t      unk090[0x94 - 0x90];
    int32_t      i94;         /* +0x94 */
    uint8_t      unk098[0xB4 - 0x98];
    int32_t      boneB4;      /* +0xB4 */
    uint8_t      unkB8[0xBC - 0xB8];
    R4bMeshSrc  *srcBC;       /* +0xBC */
    uint8_t      unkC0[0xD4 - 0xC0];
    R4bSkelMats *skelD4;      /* +0xD4 */
    int32_t      iD8;         /* +0xD8 */
    float        vDC[4];      /* +0xDC */
    uint8_t      unkEC[0x100 - 0xEC];
    int32_t      i100, i104;  /* +0x100 */
} R4bMeshItem;
typedef struct R4bMesh {
    uint8_t      unk00[0x88];
    R4bMeshItem *child88;     /* +0x88 */
    uint8_t      unk8C[0x94 - 0x8C];
    int32_t      i94;         /* +0x94 */
    uint8_t      unk98[0xB0 - 0x98];
    uint32_t     flagsB0;     /* +0xB0 bit 0 */
    uint8_t      unkB4[0xBC - 0xB4];
    struct { uint8_t unk00[0x0C]; int32_t root0C; } **skelBC; /* +0xBC */
    uint32_t     count;       /* +0xC0 */
    R4bMeshItem *items;       /* +0xC4 */
    void        *iC8;         /* +0xC8 */
    float        vCC[4];      /* +0xCC */
    uint8_t      unkDC[0xE0 - 0xDC];
    int32_t      iE0, iE4;    /* +0xE0 */
} R4bMesh;
typedef struct R4bCmdCtx { uint32_t *cur; uint32_t *start; } R4bCmdCtx;
extern int32_t r4b_g40F330, r4b_g40F388;
void r4b_MeshCopyI94(R4bMesh *m);  /* 0x001B31D0 */

/* ------------------------------------------------------------ emitter sets with 0x12C-byte items (0x001B6260..0x001B6B6B) */
typedef struct R4bPoolItem {  /* 0x134 bytes (R4PoolItem in r4.h) */
    uint8_t             unk00[0x80];
    struct R4bPoolItem *prev; /* +0x80 */
    struct R4bPoolItem *next; /* +0x84 */
    struct R4bPool     *owner;/* +0x88 */
    uint8_t             unk8C[0x134 - 0x8C];
} R4bPoolItem;
typedef struct R4bPool { R4bPoolItem *free; int32_t used; uint32_t cap; uint32_t unk0C; } R4bPool;
typedef struct R4bEmitDef {
    uint8_t unk00[0x28];
    float   f28, f2C, f30, f34, f38;  /* +0x28 */
    uint8_t unk3C[0x44 - 0x3C];
    float   f44, f48, f4C;            /* +0x44 */
    uint8_t unk50[0x64 - 0x50];
    float   f64, f68;                 /* +0x64 */
    uint8_t unk6C[0x70 - 0x6C];
    float   f70, f74;                 /* +0x70 */
    int32_t i78;                      /* +0x78 */
    uint8_t unk7C[0xC4 - 0x7C];
    float   fC4;                      /* +0xC4 */
    uint8_t unkC8[0xD8 - 0xC8];
    int32_t iD8, iDC, iE0;            /* +0xD8 */
    uint8_t unkE4[0xF0 - 0xE4];
} R4bEmitDef;                         /* 0xF0 bytes */
typedef struct R4bEmitDefList { int32_t count; R4bEmitDef *defs; } R4bEmitDefList;
typedef struct R4bEmitItem {  /* 0x12C bytes */
    uint8_t      unk000[0xB0];
    int32_t      iB0;         /* +0xB0 bit 0 = active */
    uint8_t      unkB4[0xC0 - 0xB4];
    int32_t      usedC0;      /* +0xC0 pool items held */
    R4bPoolItem *firstC4;     /* +0xC4 */
    R4bPoolItem *lastC8;      /* +0xC8 */
    uint8_t      unkCC[0xD8 - 0xCC];
    float        fD8, fDC, fE0, fE4, fE8, fEC, fF0, fF4, fF8, fFC, f100, f104, f108; /* +0xD8 */
    int32_t      i10C;        /* +0x10C */
    uint8_t      unk110[0x118 - 0x110];
    R4bEmitDef  *def118;      /* +0x118 */
    int32_t      i11C, i120, i124; /* +0x11C */
    uint8_t      unk128[0x12C - 0x128];
} R4bEmitItem;
typedef struct R4bEmitSet {
    uint8_t      unk00[0x80];
    void        *p80;         /* +0x80 */
    uint8_t      unk84[0xB0 - 0x84];
    uint32_t     count;       /* +0xB0 */
    R4bEmitItem *items;       /* +0xB4 */
    uint32_t     flagsB8;     /* +0xB8 */
    float        fBC, fC0, fC4, fC8; /* +0xBC */
    uint8_t      unkCC[0xD0 - 0xCC];
    float        fD0, fD4, fD8;      /* +0xD0 */
    uint8_t      unkDC[0x11C - 0xDC];
    int32_t      i11C;        /* +0x11C */
} R4bEmitSet;
typedef struct R4bEmitHolder {
    uint8_t     unk00[0xB0];
    R4bEmitSet *set;          /* +0xB0 */
    float       fB4;          /* +0xB4 */
} R4bEmitHolder;
extern R4bPool *r4b_g40F32C;
void sub_001B6310(R4bEmitSet *s, float a, float b, float c, float d);
int  sub_001B5C70(int arg, R4bEmitItem *it);
void r4_PoolInit(R4bPool *pool);              /* 0x001B33F0 pool=ECX */
void r4b_EmitSetScale(R4bEmitSet *s, float scale); /* 0x001B6670 */
void r4b_EmitSetReleaseAll(R4bEmitSet *s);         /* 0x001B6270 */

/* ------------------------------------------------------------ camera block (0x001B7320, 0x001B7360) */
struct R4bCam {
    uint8_t unk000[0x80];
    void   *parent80;         /* +0x80 */
    uint8_t unk084[0x8C - 0x84];
    int32_t type8C;           /* +0x8C */
    uint8_t unk090[0xB0 - 0x90];
    float   mB0[16];          /* +0xB0 */
    float   mF0[16];          /* +0xF0 */
    float   m130[16];         /* +0x130 */
    float   m170[16];         /* +0x170 */
    float   m1B0[16];         /* +0x1B0 */
    float   m1F0[16];         /* +0x1F0 */
    float   m230[16];         /* +0x230 */
    float   v270[8];          /* +0x270 */
    uint8_t fog290[0x38];     /* +0x290 fog block (R4Fog in r4.h) */
    int32_t i2C8;             /* +0x2C8 */
};
void r4_FogInit(void *fog);   /* 0x001B1DB0 */
void sub_001A6C90(const float *m);
extern uint32_t r4b_g3780E8[4];
uint32_t *sub_001B7C30(int x, uint32_t *cmd, void *p, int k); /* x=EAX cmd=ESI p,k=stack */

/* ------------------------------------------------------------ type-12 nodes with 0x110-byte items (0x001B8240..0x001B83C8) */
typedef struct R4bNodeCItem { /* 0x110 bytes */
    uint8_t unk000[0x94];
    int32_t i94;              /* +0x94 */
    uint8_t unk098[0xD0 - 0x98];
    const float *iD0;         /* +0xD0 light (float[4]) copied from the node's +0xB8 */
    uint8_t unkD4[0xD8 - 0xD4];
    float   vD8[4];           /* +0xD8 */
    int32_t iE8, iEC;         /* +0xE8 */
    uint8_t unkF0[0x110 - 0xF0];
} R4bNodeCItem;
typedef struct R4bNodeC {
    uint8_t unk00[0x8C];
    int32_t type8C;           /* +0x8C */
    uint8_t unk90[0x94 - 0x90];
    int32_t i94;              /* +0x94 */
    uint8_t unk98[0xB0 - 0x98];
    int32_t iB0, iB4;         /* +0xB0 */
    const float *iB8;         /* +0xB8 light (float[4]) set by 0x001B82E0 */
    int32_t iBC;              /* +0xBC */
    int32_t count;            /* +0xC0 */
    R4bNodeCItem *items;      /* +0xC4 */
    int32_t iC8;              /* +0xC8 */
    float   vCC[4];           /* +0xCC (+0xD4/+0xD8 also used as sizes) */
    uint8_t unkDC[0xE0 - 0xDC];
    int32_t iE0, iE4;         /* +0xE0 */
    const float *matsE8;      /* +0xE8 two matrices (local, world) */
    int32_t iEC;              /* +0xEC */
} R4bNodeC;
void r4b_NodeCCopyI94(R4bNodeC *n); /* 0x001B8390 */


void sub_001A6CF0(R4bCam *c);
void sub_001A6CC0(float *m);
uint32_t *sub_001B1E80(void *fog, uint32_t *cmd);
void sub_001A6EE0(float *v);

/* 0x001B8E10..0x001B8FAF */
typedef struct R4bMeshRef { uint8_t unk00[0xC0]; R4bMesh *mesh; } R4bMeshRef;
void sub_001B8C80(R4bMesh *m, R4bMeshItem *base, int idx);
void sub_001A2350(int i, const float *m);

/* ------------------------------------------------------------ texture entries (0x001B9650..0x001B9D15) */
typedef struct R4bTexUser {   /* heap-2 block record (R4Blk2 in r4.h) */
    uint8_t  unk00[8];
    int32_t  timer;           /* +0x08 */
    uint8_t  unk0C[0x1C - 0x0C];
    uint16_t w1C, w1E;        /* +0x1C */
} R4bTexUser;
typedef struct R4bTexEnt {    /* 0x58 bytes (R4TexEnt in r4.h) */
    uint32_t    key[4];       /* +0x00 name key */
    uint8_t     flags;        /* +0x10 bit 0 = in use, bit 1, bit 2 */
    uint8_t     unk11[0x14 - 0x11];
    void       *hdr14;        /* +0x14 texture header */
    int32_t     timer18;      /* +0x18 */
    uint8_t     unk1C[0x1E - 0x1C];
    uint16_t    group1E;      /* +0x1E */
    struct R4bTexEnt *next20; /* +0x20 */
    struct R4bTexEnt *prev24; /* +0x24 */
    uint8_t     v28[8];       /* +0x28 */
    uint8_t     v30[8];       /* +0x30 */
    uint8_t     v38[8];       /* +0x38 */
    uint8_t     v40[0x10];    /* +0x40 */
    R4bTexUser *user50;       /* +0x50 */
    uint8_t     unk54[4];
} R4bTexEnt;
typedef struct R4bTexTable {  /* 0x20-byte header followed by the entries */
    uint32_t   size;          /* +0x00 */
    uint32_t   count;         /* +0x04 */
    int32_t    used;          /* +0x08 */
    R4bTexEnt *first;         /* +0x0C */
    R4bTexEnt *last;          /* +0x10 */
    R4bTexEnt *freeFirst;     /* +0x14 */
    R4bTexEnt *freeLast;      /* +0x18 */
    uint16_t   group1C;       /* +0x1C */
    uint16_t   unk1E;
} R4bTexTable;
extern R4bTexTable *r4b_g40F758;
extern R4bTexEnt    r4b_g40F4F8;  /* scratch entry */
void sub_001A64F0(R4bTexEnt *e);
void sub_001B9950(void *a, void *b, void *c, void *d, int flag);
int  r4_TexFindByKey(uint16_t group, const uint32_t *key);  /* 0x001B9B90 group=ESI key=ECX */
void sub_001B93E0(void);
void sub_001BA170(void);
void sub_001B9460(R4bTexEnt *dst, void *hdr);               /* dst=EAX hdr=ECX */
void sub_001B9EC0(R4bTexEnt *dst, void *hdr, int w);        /* dst=ESI hdr,w=stack */
int  r4b_TexFree(int idx);                                  /* 0x001B9FC0 */
extern R4bTexTable *r4_g40F390;
extern R4bTexEnt *r4b_g40F750;
extern uint32_t   r4b_g40F754;   /* frame parity */
extern R4bTexEnt  r4b_g40F398[2];
extern R4bTexEnt  r4b_g40F448[2];
void     r4_Heap2Init(void);
uint16_t r4_Heap2Word0C(void);
void     sub_001BB710(int a, int b);
void     sub_001A6820(R4bTexEnt *e);
R4bTexEnt *r4b_TexEntGet(int idx); /* 0x001B9650 */

int  sub_001BA6E0(int group, void *x);   /* x deref'd ([ebx+0x20]) */

/* ------------------------------------------------------------ type-17 nodes (0x001BA820..0x001BA982) */
typedef struct R4bPartRec { uint8_t unk000[0x3C0]; R4bPart *part; } R4bPartRec; /* 0x3C4 bytes */
typedef struct R4bNodeP {
    uint8_t     unk00[0x8C];
    int32_t     type8C;       /* +0x8C */
    uint8_t     unk90[0xB0 - 0x90];
    float       colB0[4];     /* +0xB0 */
    int32_t     iC0, iC4, iC8; /* +0xC0 */
    uint8_t     unkCC[0xD0 - 0xCC];
    int32_t     countD0;      /* +0xD0 */
    R4bPartRec *recsD4;       /* +0xD4 */
    int32_t     iD8;          /* +0xD8 */
    uint8_t     unkDC[0xE0 - 0xDC];
    int32_t     iE0, iE4, iE8; /* +0xE0 */
    float       fEC;          /* +0xEC */
    int32_t     iF0, iF4;     /* +0xF0 */
} R4bNodeP;
typedef struct R4bNodeParts { uint8_t unk00[0xC4]; R4bPart *parts; } R4bNodeParts;

/* ------------------------------------------------------------ 0x00412F40, heap 1 (0x001BB2A0) */
extern int32_t r4b_g412F40[3];
typedef struct R4bHeap { uint32_t size; uint32_t count; void *first; } R4bHeap; /* R4Heap in r4.h */
typedef struct R4bBlk { uint8_t unk[0x10]; } R4bBlk;
extern R4bHeap *r4_g40F75C;
extern R4bBlk  *r4_g40F760;
extern R4bHeap *r4b_g40F764;
void r4_HeapClearUsed(void);

/* ------------------------------------------------------------ type-5 nodes with 0x100-byte items (0x001BB810..0x001BBA1C) */
typedef struct R4bNode5Item { /* 0x100 bytes */
    uint8_t  unk00[0x80];
    void    *parent80;        /* +0x80 */
    uint8_t  unk84[0x8C - 0x84];
    int32_t  type8C;          /* +0x8C */
    uint32_t flags90;         /* +0x90 */
    uint8_t  unk94[0xF8 - 0x94];
    int32_t  iF8, iFC;        /* +0xF8 */
} R4bNode5Item;
typedef struct R4bNode5Src { uint8_t unk00[8]; int32_t i08; int32_t root0C; } R4bNode5Src;
typedef struct R4bNode5 {
    uint8_t       unk00[0x88];
    R4bNode5Item *child88;    /* +0x88 */
    int32_t       type8C;     /* +0x8C */
    uint32_t      flags90;    /* +0x90 bit 8 */
    uint8_t       unk94[0xB0 - 0x94];
    int32_t       iB0, iB4, iB8; /* +0xB0 */
    R4bNode5Src **srcBC;      /* +0xBC */
    int32_t       count;      /* +0xC0 */
    R4bNode5Item *items;      /* +0xC4 */
    float         colC8[4];   /* +0xC8 */
    int32_t       iD8, iDC;   /* +0xD8 */
    int32_t       iE0, iE4;   /* +0xE0 */
} R4bNode5;
void sub_001A6E80(int on);
void sub_001BBA20(R4bNode5 *n, R4bNode5Item *base, int idx);

/* 0x001BBC40: type-6 draw node */
typedef struct R4bSubInfo { uint8_t unk00[0x0C]; int32_t size0C; } R4bSubInfo; /* 0x10 bytes */
typedef struct R4bModelInfo { uint8_t unk00[4]; R4bSubInfo *subs; } R4bModelInfo;
typedef struct R4bModel6 { float m00[16]; float m40[16]; uint8_t unk80[0xBC - 0x80]; R4bModelInfo *infoBC; } R4bModel6;
typedef struct R4bNode6 {
    uint8_t    unk00[0x8C];
    int32_t    type8C;        /* +0x8C */
    uint32_t   flags90;       /* +0x90 bit 8 */
    uint8_t    unk94[0xA0 - 0x94];
    struct R4bNode6 *prevA0;  /* +0xA0 previously drawn node */
    uint8_t    unkA4[0xB4 - 0xA4];
    int32_t    subB4;         /* +0xB4 */
    uint8_t    unkB8[0xC0 - 0xB8];
    R4bModel6 *modelC0;       /* +0xC0 */
    void      *itemsC4;       /* +0xC4 */
    void      *texC8;         /* +0xC8 */
    void      *selCC;         /* +0xCC */
    int32_t    texD0;         /* +0xD0 */
    uint8_t    unkD4[0xF8 - 0xD4];
    int32_t    iF8, iFC;      /* +0xF8 */
} R4bNode6;
void sub_001A2EB0(R4bNode6 *n);
uint32_t *r4b_MatUpload(float *m, uint32_t *cmd);   /* 0x001B8EA0 */

/* 0x00412F30.. */
extern float   r4b_g412F34;
extern int32_t r4b_g412F30;
uint16_t r4b_TexSetGroup(uint16_t g);                /* 0x001BA0B0 */
void     r4b_NodeBucketsClear(void);                 /* 0x001B1FC0 */
void     r4_Set40F328(int a);
typedef struct R4bP2od { uint32_t magic; uint16_t w4; } R4bP2od;

/* 0x001BC060: sound voice table */
typedef struct R4bVoiceBufs { void *buf[4]; int32_t data[4]; } R4bVoiceBufs;        /* 0x20 bytes */
typedef struct R4bVoiceHnd { int32_t enable; int32_t h; int32_t size; } R4bVoiceHnd; /* 0x0C bytes */
typedef struct R4bVoiceSet {
    R4bVoiceBufs bufs[2];     /* +0x00 */
    int32_t      count;       /* +0x40 */
    int32_t      a44, a48;    /* +0x44 format pair for voices 0 and 3 */
    int32_t      a4C, a50;    /* +0x4C format pair for voices 1 and 2 */
    uint8_t      unk54[0x58 - 0x54];
    R4bVoiceHnd  hnd[2][4];   /* +0x58 */
} R4bVoiceSet;
void *sub_001C8864(uint32_t n);
void OOG_STDCALL sub_001D6030(void *res, void *mem);
void r4b_VoiceSetFree(int unused, R4bVoiceSet *s);  /* 0x001BC060 */
int  r4b_VoiceAlloc(int a, int b, int fmt, void **res, void **mem, int32_t *data, int32_t *size); /* 0x001BC130 */
void OOG_STDCALL sub_001D3AB0(int stage, void *rt);
int  OOG_STDCALL sub_001BD587(int h);
void sub_001C885F(void *p);

/* ------------------------------------------------------------ movie playback (0x001A7DC0..0x001A820A) */
typedef struct R4bBink { int32_t width, height, frames, frameNum; } R4bBink; /* Bink handle header */
extern uint8_t  a1a_b40B144;      /* movie playing */
extern R4bBink *a1a_g40B148;      /* open movie */
extern R4bVoiceSet a1a_g40B150;   /* movie surfaces */
extern int32_t  a1a_g40F124;
extern int32_t  r4b_g40B140;      /* game mode */
extern float    r4b_g40B0F8, r4b_g40B0FC, r4b_g40B100, r4b_g40B104;
extern int32_t  aac_g1E243C;
void OOG_STDCALL sub_0022E730(R4bBink *b);
void OOG_STDCALL sub_0022E980(R4bBink *b);
void OOG_STDCALL sub_0022E840(R4bBink *b, int v);
void OOG_STDCALL sub_0022E7E0(R4bBink *b, int track, int32_t *chans, int32_t *vols, int n);
int  sub_0019FFC0(void);
void sub_001BC6D0(void *p);
void *OOG_STDCALL sub_001D3A80(int a);
void sub_001BC6C0(void);
void sub_001BC320(int a, R4bVoiceSet *s, int w, int h, int x, int y, float sx, float sy, float alpha);
void __fastcall sub_001D4350(int reg, int v);

/* ------------------------------------------------------------ file slots (0x001A8330..0x001A8584) */
typedef struct R4bOverlapped { uint32_t status; uint32_t done; uint32_t pos; uint32_t posHigh; void *event; } R4bOverlapped; /* OVERLAPPED */
extern void         *r4b_g40B210[65];   /* file handles, slot 0 unused */
extern int32_t       r4b_g40B318;       /* open files */
extern R4bOverlapped r4b_g40B320[65];
extern int32_t       r4b_g40B864;       /* async read busy */
extern int32_t       r4b_g40B868;       /* async slot */
extern void         *r4b_g40B86C;       /* async buffer */
extern uint32_t      r4b_g40B870;       /* async size */
extern void         *r4b_g40B874;       /* async thread */
extern int32_t       r4b_g40B878;       /* error count */
int  OOG_STDCALL sub_001BC6FD(void *h);                 /* CloseHandle */
int  OOG_STDCALL sub_001BCC81(void *h, void *buf, uint32_t n, R4bOverlapped *ov, int x); /* ReadFile */
int  OOG_STDCALL sub_001BC741(void);                    /* GetLastError */
void *OOG_STDCALL sub_001BD49C(void *sa, int stack, void (*proc)(void *), void *arg, int flags, void *id); /* CreateThread */
int  OOG_STDCALL sub_001BD23E(void *h, int prio);       /* SetThreadPriority */
uint32_t OOG_STDCALL sub_001BCCD2(void *h, void *hi);   /* GetFileSize */
int  OOG_STDCALL sub_001BC7AE(void *h, R4bOverlapped *ov, uint32_t *n, int wait); /* GetOverlappedResult */
#ifdef _MSC_VER
__declspec(noreturn)
#endif
void OOG_STDCALL sub_001BD345(int code);                /* ExitThread */
void sub_001A7A70(void);

#endif
