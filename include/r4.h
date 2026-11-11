#ifndef R4_H
#define R4_H
#include "oogie.h"
/* Area r4: register-argument functions (and their callers) in 0x00190000..0x001BC6D0.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4.csv. */

/* ------------------------------------------------------------ actors driven by work slots */
typedef struct R4Slot R4Slot;
typedef struct R4Actor {
    uint8_t  unk000[0x0C];
    uint32_t flagsC;          /* +0x0C */
    uint32_t flags10;         /* +0x10 */
    uint8_t  unk014[0x20 - 0x14];
    void    *p20;             /* +0x20 transform node */
    uint8_t  unk024[0x28 - 0x24];
    void    *p28;             /* +0x28 */
    uint8_t  unk02C[0x60 - 0x2C];
    float    pos60[4];        /* +0x60 */
    float    f70, f74, f78;   /* +0x70 scale (Hypothesis) */
    uint8_t  unk07C[0xF0 - 0x7C];
    int32_t  iF0, iF4;        /* +0xF0 */
    uint8_t  unk0F8[0x118 - 0xF8];
    int32_t  i118;            /* +0x118 */
    int32_t  i11C;            /* +0x11C */
    int32_t  i120;            /* +0x120 */
    int32_t  i124;            /* +0x124 */
    uint8_t  unk128[0x130 - 0x128];
    int32_t  i130;            /* +0x130 */
} R4Actor;
#define R4_ACTOR_F64(a) (*(float *)((uint8_t *)(a) + 0x64))

typedef int (*R4Callback)(void *a, void *b, void *c);
typedef struct R4Ctl {        /* controller/component of an actor */
    uint8_t    unk00[0x24];
    int32_t    i24;           /* +0x24 */
    float      f28, f2C;      /* +0x28 */
    uint8_t    unk30[0x74 - 0x30];
    R4Slot    *slot74;        /* +0x74 */
    void      *fn78;          /* +0x78 */
    void      *fn7C;          /* +0x7C */
    void      *fn80;          /* +0x80 */
    void      *p84;           /* +0x84 */
    void      *p88;           /* +0x88 */
} R4Ctl;

struct R4Slot {               /* 0x00400E50, 18 records of 0x8C */
    int32_t  i00;             /* +0x00 */
    R4Actor *actor;           /* +0x04 0 = free */
    R4Ctl   *ctl;             /* +0x08 */
    float    fC;              /* +0x0C */
    int32_t  type;            /* +0x10 0..4, -1 none */
    uint8_t  unk14[4];
    float    f18, f1C;        /* +0x18 */
    uint8_t  unk20[0x58 - 0x20];
    uint16_t w58;             /* +0x58 */
    uint8_t  unk5A[0x80 - 0x5A];
    uint16_t w80, w82;        /* +0x80 */
    uint8_t  unk84[0x8C - 0x84];
};
extern R4Slot a9b_g400E50[18];

/* 0x00400A88: four 0x88-byte records reset by 0x00193990. */
typedef struct R4Rec88 {
    int32_t  i00, i04, i08;   /* +0x00, i08 = -1 */
    float    f0C;             /* +0x0C */
    uint16_t w10;             /* +0x10 */
    uint8_t  unk12[0x1C - 0x12];
    float    v1C[4];          /* +0x1C */
    float    v2C[4];          /* +0x2C */
    float    f3C, f40, f44, f48, f4C, f50; /* +0x3C */
    uint8_t  unk54[4];
    float    f58;             /* +0x58 */
    uint8_t  unk5C[0x64 - 0x5C];
    float    f64, f68;        /* +0x64 */
    uint16_t w6C;             /* +0x6C */
    uint8_t  unk6E[0x88 - 0x6E];
} R4Rec88;
extern R4Rec88 a9b_g400A88[4];

/* 0x00401828 points at six 0x44-byte link records. */
typedef struct R4Link44 { R4Actor *actor; uint8_t unk04[0x0A]; uint16_t wE; uint8_t unk10[0x34]; } R4Link44;
extern R4Link44 *a19_g401828;

extern void *r4_g32C7C8[];    /* 0x0032C7C8 table handed to slot controllers */
extern void *r4_g32C800[];    /* 0x0032C800 */

int  r4_SlotRelease(R4Actor *a, R4Ctl *ctl, void *msg); /* 0x00195150 */
int  a9b_WorkTick(void *a, void *b, void *c);   /* 0x001951E0 */
int  sub_00195210(void *a, void *b, void *c);
int  sub_00195400(void *a, void *b, void *c);
int  sub_00196B40(void *a, void *b, void *c);

void r4_SlotInitType2(R4Slot *s);            /* 0x001953B0 s=EDI */
void r4_SlotInitType3(R4Slot *s);            /* 0x00196850 s=EDI */
void r4_SlotInitType4(R4Slot *s);            /* 0x001968A0 s=EDI */
void r4_SlotInitType0(R4Slot *s);            /* 0x00196790 s=ESI */
int  r4_SlotAttach(R4Actor *a, R4Ctl *c, int type); /* 0x00196900 */

/* callees */
void sub_0001EE80(void *o, void *fn);
void sub_0001D7A0(void *o);
void sub_00189DA0(void *a, void *b, int c);
void sub_0001EBF0(void *o, int n);
void sub_0001EF00(void *o, float *v);
void sub_00033B30(void *o);
void sub_0001EB80(void *o);
void sub_001ADA40(void *node, const float *m);
void sub_000385D0(void *a, void *b);

/* ------------------------------------------------------------ scene nodes (0x001B1430..0x001B2A2A) */
typedef struct R4Hook {       /* singly linked hook list entry */
    struct R4Hook *next;      /* +0x00 */
    void (*fn)(void *node, struct R4Hook *h); /* +0x04 */
} R4Hook;
typedef struct R4Node {
    uint8_t        unk00[0x80];
    struct R4Node *parent;    /* +0x80 */
    struct R4Node *next;      /* +0x84 next sibling */
    struct R4Node *child;     /* +0x88 first child */
    uint8_t        unk8C[0xA4 - 0x8C];
    int32_t        iA4;       /* +0xA4 */
    R4Hook        *hooksA8;   /* +0xA8 pushed at the head */
    R4Hook        *hooksAC;   /* +0xAC appended at the tail */
} R4Node;
extern R4Node *r4_g412F80[0x33]; /* 0x00412F80 */
extern R4Node *r4_g413060[0x33]; /* 0x00413060 */
extern float r4_g377F48;         /* 0x00377F48 upper limit */
extern float r4_g40F1C4;         /* 0x0040F1C4 lower limit */
extern int32_t r4_g40F1BC, r4_g40F1C0, r4_g40F208, r4_g40F324, r4_g40F328;
extern void *r4_g40F1B0;
extern uint8_t r4_g367EA8[];     /* 0x00367EA8 embedded DDS image */

typedef struct R4Skel { uint8_t unk00[0xB4]; uint8_t *mats; } R4Skel;     /* 0x130-byte records at +0xB4 */
typedef struct R4PartOwner { uint8_t unk00[0xC8]; R4Skel *skel; } R4PartOwner;
typedef struct R4Part {       /* 0x180 bytes */
    uint8_t      unk000[0xB4];
    int32_t      boneB4;      /* +0xB4 */
    R4PartOwner *ownerB8;     /* +0xB8 */
    uint8_t      unkBC[0x17C - 0xBC];
    int32_t      i17C;        /* +0x17C */
} R4Part;
typedef struct R4Model {
    uint8_t  unk00[0xC0];
    uint32_t count;           /* +0xC0 */
    R4Part  *parts;           /* +0xC4 */
    int32_t  iC8;             /* +0xC8 */
    int32_t  iCC;             /* +0xCC */
    uint8_t  unkD0[0xE8 - 0xD0];
    int32_t  iE8, iEC;        /* +0xE8 */
} R4Model;

typedef struct R4Fog {
    float    f00, f04, f08, f0C;   /* +0x00 */
    float    f10;
    float    f14, f18, f1C, f20;   /* +0x14 */
    float    f24, f28, f2C, f30;   /* +0x24 */
    uint32_t *cmd34;               /* +0x34 */
} R4Fog;

void  sub_001AD7E0(void *d, const void *s);
int   sub_001B2270(void *p);
void *sub_001BA7F0(const void *img);
uint8_t *sub_001B9650(void *tex);
int   sub_001B9CA0(int a, void *tex);
void  sub_001ADEE0(void *m, int a, int b, int c);
void  sub_001A7280(int a);
void  sub_001AD9F0(float *d, const float *a, const float *b);
float sub_001AD9D0(const float *a, const float *b);
float sub_001A3F50(float x);

/* ------------------------------------------------------------ node pool (0x001B3380..0x001B3443) */
typedef struct R4PoolItem {   /* 0x134 bytes */
    uint8_t            unk00[0x80];
    struct R4PoolItem *prev;  /* +0x80 */
    struct R4PoolItem *next;  /* +0x84 */
    struct R4Pool     *owner; /* +0x88 */
    int32_t            i8C;   /* +0x8C */
    uint8_t            unk90[0x134 - 0x90];
} R4PoolItem;
typedef struct R4Pool {
    R4PoolItem *free;         /* +0x00 */
    int32_t     used;         /* +0x04 */
    uint32_t    cap;          /* +0x08 */
    uint32_t    unk0C;
    R4PoolItem  items[1];     /* +0x10, cap entries */
} R4Pool;
R4PoolItem *r4_PoolAlloc(R4Pool *pool);   /* 0x001B3380 pool=ECX */
void r4_PoolFree(R4PoolItem *it);         /* 0x001B33C0 it=ECX */
void r4_PoolInit(R4Pool *pool);           /* 0x001B33F0 pool=ECX */

/* 0x001B60C0 */
typedef struct R4Emit {       /* 0x12C bytes */
    uint8_t unk00[0xB0];
    uint8_t flagsB0;          /* +0xB0 bit 0 = active */
    uint8_t unkB1[0xC0 - 0xB1];
    int32_t iC0;              /* +0xC0 */
    uint8_t unkC4[0xCC - 0xC4];
    float   fCC;              /* +0xCC */
    uint8_t unkD0[0x12C - 0xD0];
} R4Emit;
typedef struct R4EmitSet {
    uint8_t  unk00[0x80];
    void    *p80;             /* +0x80 */
    uint8_t  unk84[0xB0 - 0x84];
    uint32_t count;           /* +0xB0 */
    R4Emit  *items;           /* +0xB4 */
    uint32_t flagsB8;         /* +0xB8 */
} R4EmitSet;

/* ------------------------------------------------------------ texture table (0x0040F390) */
typedef struct R4TexEnt {     /* 0x58 bytes */
    union { char name[8]; uint32_t key[4]; } id; /* +0x00 */
    uint8_t  flags;           /* +0x10 bit 0 = in use */
    uint8_t  unk11[0x1E - 0x11];
    uint16_t group;           /* +0x1E */
    struct R4TexEnt *next;    /* +0x20 */
    uint8_t  unk24[0x58 - 0x24];
} R4TexEnt;
typedef struct R4TexTable { uint8_t unk00[0x0C]; R4TexEnt *first; uint8_t unk10[0x0C]; uint16_t group1C; } R4TexTable;
extern R4TexTable *r4_g40F390;
int r4_TexFindByKey(uint16_t group, const uint32_t *key);  /* 0x001B9B90 group=ESI key=ECX */
int r4_TexFindByName(uint16_t group, const char *name);    /* 0x001B9BF0 stack */

/* ------------------------------------------------------------ small block heaps */
typedef struct R4Blk {        /* 0x10-byte block record */
    uint32_t      unk0;
    struct R4Blk *next;       /* +0x04 */
    uint8_t       used;       /* +0x08 */
    uint8_t       unk9;
    uint8_t       lock0A, lock0B; /* +0x0A, +0x0B access flags */
    uint16_t      addr;       /* +0x0C */
    uint16_t      size;       /* +0x0E */
} R4Blk;
typedef struct R4Heap { uint32_t unk0; uint32_t count; R4Blk *first; } R4Heap;
extern R4Heap *r4_g40F75C;
extern R4Blk  *r4_g40F760;    /* block record array */
typedef struct R4Blk2 {       /* 0x20-byte record */
    struct R4Blk2 *next;      /* +0x00 */
    uint8_t  used, b5;        /* +0x04 */
    uint8_t  unk06[0x10 - 6];
    uint8_t *owner;           /* +0x10, owner +0x50 points back */
    uint8_t  unk14[0x1C - 0x14];
    uint16_t w1C, w1E;        /* +0x1C */
} R4Blk2;
typedef struct R4Heap2 { uint32_t unk0; uint32_t count; uint16_t w8, wA, wC; } R4Heap2;
extern R4Heap2 *r4_g40F768;
extern R4Blk2  *r4_g40F76C;
extern int32_t r4_g412F4C[3], r4_g412F58[3];
uint8_t  r4_HeapKindCode(int kind);                               /* 0x001BB0B0 kind=EAX (low 16 bits) */
R4Blk   *r4_HeapFindBlock(uint16_t addr);                         /* 0x001BB120 addr=EDX */
int      r4_HeapRunCost(R4Blk *b, uint16_t size, uint8_t code);   /* 0x001BB030 b=EDX size=ECX code=EBX(BL) */
uint16_t r4_HeapFindFit(uint8_t code, R4Blk *first, uint16_t size); /* 0x001BB3E0 code=EAX first=ECX size=stack */
void     r4_HeapMerge(void);                                      /* 0x001BB160 */
int      sub_001BB440(uint16_t size, uint16_t addr, uint8_t code, int flag); /* size=EAX addr=EDX code,flag=stack */
void     r4_Heap2Reset(void);                                     /* 0x001BB660 */

/* ------------------------------------------------------------ skinned meshes (0x001AEE50, 0x001AEF60) */
typedef struct R4Bone {       /* 0x130 bytes */
    uint8_t  unk000[0xB8];
    uint32_t maskB8;          /* +0xB8 */
    int32_t  iBC;             /* +0xBC */
    uint8_t  unkC0[0xCC - 0xC0];
    int32_t  iCC;             /* +0xCC */
    float    fD0;             /* +0xD0 */
    uint8_t  unkD4[0x130 - 0xD4];
} R4Bone;
typedef struct R4Skin { uint8_t unk00[0xB0]; int32_t count; R4Bone *bones; } R4Skin;
extern int32_t r4_g40F150, r4_g40F154, r4_g40F158, r4_g40F15C;
extern float   r4_g40F160[16];   /* 0x0040F160 matrix */
void sub_001AD940(float *m);
void r4_SkinReset(R4Skin *s);    /* 0x001AEF60 s=EAX */

/* ------------------------------------------------------------ worker threads (0x0040EDD8) */
typedef struct R4ThreadRec { void *handle; int32_t id; int32_t unk08; int32_t state; int32_t unk10[2]; } R4ThreadRec;
extern R4ThreadRec aac_g40EDD8[32];
extern int32_t r4_g40EDDC;       /* = aac_g40EDD8[0].id */
extern void   *r4_g40F0D8;       /* lock */
void  sub_001AA1E0(void *lock);
void  sub_001AA1F0(void *lock);
void *sub_001AA1A0(void);
int   sub_001BD50A(void);
void  OOG_STDCALL sub_001BC71B(int a, int b, int c, void *d, int e, int f, int g);
void  OOG_STDCALL sub_001BD3B2(int a);
#ifdef _MSC_VER
__declspec(noreturn)
#endif
void  OOG_STDCALL sub_001BD345(int code);  /* does not return (thread exit) */
int   r4_ThreadSetState(int id, int state);   /* 0x001AD340 id=EAX state=stack */

/* ------------------------------------------------------------ 0x001A1CE0 */
extern int32_t a1a_g4046D4;
extern int32_t a1a_g4046D8[9];   /* [0] count, [1..8] handles (-1 = none) */
extern void   *r4_g337EE4[8];
void OOG_STDCALL sub_001D1B80(void *a, int32_t *out);
#endif
