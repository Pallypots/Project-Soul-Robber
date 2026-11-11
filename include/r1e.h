#ifndef R1E_H
#define R1E_H
#include "oogie.h"
#include "shared_decls.h"
#include <string.h>
#if defined(_M_IX86)
#include <intrin.h>
#endif

/* Area r1e: game functions 0x00012000..0x00060000 (fifth pass). Names
   inferred. Register-argument mappings are in config/function_states_r1e.csv. */

typedef float R1eVec4[4];
typedef float R1eMat[4][4];

/* shared vector / matrix helpers */
/* sub_000F5D40 (vector copy) is declared in oogie.h */
void r1e_MatOrtho(R1eMat dst, const R1eMat src);              /* 0x000385D0 */
void sub_001AD7E0(float *dst, const float *src);
void sub_001ADBA0(float *dst, const float *src, float s);
void r4c_VecAdd(float *dst, const float *a, const float *b);    /* 0x001ADAF0 */
void sub_001ADA60(float *dst, const float *a, const float *b);  /* cross product */

/* ------------------------------------------------------------ group 1 */
/* camera pull state (0x00018E70) */
extern int32_t r1e_shake37C048;                  /* 0x0037C048 */
extern float   r1e_shakeAmt37C04C;               /* 0x0037C04C */
typedef struct R1eMover {
    uint8_t unk00[0x10];
    R1eMat  m;                  /* +0x10 row 3 (+0x40) is the position */
} R1eMover;

/* linked hit-part list (0x0001E7D0) */
typedef struct R1ePartObj {
    uint8_t unk00[0x8C];
    int32_t kind;               /* +0x8C */
    uint8_t unk90[0x30];
    int32_t value;              /* +0xC0 */
} R1ePartObj;
typedef struct R1ePart {
    uint8_t unk00[0x0C];
    uint8_t flags;              /* +0x0C */
    uint8_t unk0D[0x13];
    R1ePartObj *obj;            /* +0x20 */
    uint8_t unk24[0x18];
    struct R1ePart *next;       /* +0x3C */
} R1ePart;

/* stage state machines (0x0002C300) */
extern int32_t r1e_state37EECC;                  /* 0x0037EECC */
extern uint32_t r1e_flags37EDEC;                 /* 0x0037EDEC */
extern int32_t r1e_state37EDF0;                  /* 0x0037EDF0 */
void sub_0002ACF0(void);
void sub_0002AE60(void);
void sub_0002AF80(void);
void sub_0002A950(void);
void sub_0002ABD0(void);
void sub_00023B70(void);

/* ------------------------------------------------------------ group 2 */
extern int32_t r1e_state381850;                  /* 0x00381850 */
extern float   r1e_timer38186C;                  /* 0x0038186C */
extern float   r1e_timer381870;                  /* 0x00381870 */
void sub_00032DD0(void);
void sub_00032F90(void);
void sub_000330A0(void);
void sub_000720A0(float *t, int a);

/* effect node with a transform at +0x20 */
typedef struct R1eFxNode {
    int32_t busy;               /* +0x00 */
    uint8_t unk04[0x10];
    int32_t d14;                /* +0x14 */
    int32_t d18;                /* +0x18 */
    int32_t clr[4];             /* +0x1C */
    R1eMat  m;                  /* +0x2C ... (only for the clear routine) */
} R1eFxNode;
typedef struct R1eXfNode {
    int32_t busy;               /* +0x00 */
    uint8_t unk04[0x1C];
    R1eMat  m;                  /* +0x20 rows 1..3 = axes/position */
} R1eXfNode;
typedef struct R1eRange {
    uint8_t unk00[0x14];
    int32_t d14;                /* +0x14 */
    int32_t d18;                /* +0x18 */
    int32_t clr[16];            /* +0x1C */
} R1eRange;
void sub_0005A400(void *r);

/* effect-file name tables (0x00033DF0 / 0x00052E60) */
typedef struct R1eKeyVal { int32_t key; int32_t val; int32_t alt; } R1eKeyVal;
typedef struct R1eKeyTab { int32_t id; R1eKeyVal *list; } R1eKeyTab;
extern R1eKeyTab r1e_fxTab260FC0[];              /* 0x00260FC0 */
extern R1eKeyTab r1e_sndTab26BD78[];             /* 0x0026BD78 */
int  a6b_Printf3(char *buf, int size, const char *fmt, ...);
int  sub_00033E50(int a, int type);              /* regargs: a=ECX type=EDX */
extern const char r1e_fmtEfs261444[];            /* 0x00261444 */
extern const char r1e_fmtEfl26145C[];            /* 0x0026145C */
extern const char r1e_fmtEfr261470[];            /* 0x00261470 */
extern const char r1e_fmtEfr261484[];            /* 0x00261484 */

/* spawn helper (0x000362F0) */
typedef struct R1eShape { uint8_t unk00[0x4C]; float w; float h; } R1eShape;
typedef struct R1eSpawnSrc { uint8_t unk00[0x10]; R1eShape *shape; } R1eSpawnSrc;
typedef struct R1eSpawner { uint8_t unk00[0x10]; void *owner; uint8_t unk14[4]; int32_t tag; } R1eSpawner;
typedef struct R1eSpawned { uint8_t unk00[8]; int32_t tag; } R1eSpawned;
R1eSpawned *sub_00035000(void *owner, R1eSpawnSrc *src, int a, int b, int c);

/* object bank (0x000367E0) */
typedef struct R1ePool R1ePool;
typedef int (*R1ePoolFn)(void *ent, void *ctx);
extern char *r1e_bank283698;                     /* 0x00283698 */
int  r1c_PoolForEach(void *pool, int stride, R1ePoolFn fn, void *ctx);
int  sub_000367B0(void *ent, void *ctx);
int  sub_00036180(void *ent, void *ctx);
extern uint8_t r1e_flags412F30;                  /* 0x00412F30 */
extern float   a50_frameUnits;                   /* 0x0042C858 */
typedef struct R1eAnimEnt { int32_t kind; uint8_t unk04[0x54]; float t; } R1eAnimEnt;
typedef struct R1eAnimLink { struct R1eAnimLink *next; uint8_t unk04[8]; R1eAnimEnt *ent; } R1eAnimLink;

/* ------------------------------------------------------------ group 3 */
int  sub_001A8330(int fd);
int  sub_00051850(const char *name);
int  sub_001C8036(const char *fmt, ...);
extern const char r1e_strOpenErr2615AC[];        /* 0x002615AC */

/* ten channel records at 0x0042CB20 (0x48 bytes) */
typedef struct R1eQuad { int32_t v[4]; } R1eQuad;
typedef struct R1eSlot48 {
    R1eQuad pos;                /* +0x00 */
    float   dir[4];             /* +0x10 */
    int32_t state;              /* +0x20 */
    int32_t d24, d28;           /* +0x24 */
    float   f2C;                /* +0x2C */
    int32_t d30, d34;           /* +0x30 */
    float   f38, f3C, f40;      /* +0x38 */
    int32_t flags;              /* +0x44 */
} R1eSlot48;
extern R1eSlot48 r1e_slots42CB20[10];            /* 0x0042CB20 */
extern int32_t   r1e_g42CE38;                    /* 0x0042CE38 */
void sub_00037830(R1eSlot48 *s);                 /* regargs: s=EAX */
void sub_00037790(R1eSlot48 *s, int a);          /* regargs: s=ESI */
void sub_00037910(R1eSlot48 *s, int a);          /* regargs: s=ESI */

/* packet writer (0x00038AD0) */
typedef struct R1eGsBatch {
    uint8_t  unk00[0x10];
    uint32_t tex;               /* +0x10 */
    uint8_t  unk14[0x5C];
    int32_t  count;             /* +0x70 */
    uint8_t  unk74[4];
    uint32_t regs[1][4];        /* +0x78 count 16-byte entries */
} R1eGsBatch;

/* growable stream (0x00038BF0) */
typedef struct R1eStream {
    uint8_t  unk00[4];
    char    *cur;               /* +0x04 */
    int32_t  left;              /* +0x08 */
    int32_t  used;              /* +0x0C */
    uint8_t  unk10[4];
    int32_t  units;             /* +0x14 */
    uint8_t  unk18[0x164];
    int32_t  step;              /* +0x17C */
} R1eStream;
char *sub_00038B50(R1eStream *s, char *p);       /* regargs: s=ECX */

/* sound channels: 0x2C-byte settings and 0x1450-byte voices */
typedef struct R1eChan {
    int32_t kind;               /* +0x00 */
    int32_t d04;                /* +0x04 */
    int32_t d08;                /* +0x08 */
    int32_t d0C;                /* +0x0C */
    int32_t level;              /* +0x10 */
    int32_t d14;                /* +0x14 */
    int32_t d18;                /* +0x18 */
    int32_t d1C, d20, d24, d28; /* +0x1C */
} R1eChan;
extern R1eChan r1e_chan3DA4A8[];                 /* 0x003DA4A8 */
typedef struct R1eVoiceCol { uint8_t pad; uint8_t r, g, b; uint8_t a; uint8_t unk[0x33]; } R1eVoiceCol;
typedef struct R1eVoice {
    uint8_t     unk0000[0x1340];
    R1eVoiceCol col[4];         /* +0x1340 stride 0x38 */
    uint8_t     unk13E0[0x70];
} R1eVoice;
extern R1eVoice r1e_voice3DA500[];               /* 0x003DA500 */
int  sub_000390E0(int i, int v);                 /* regargs: i=EAX */
int  sub_00039440(int i, int v);                 /* regargs: i=EAX */

/* ------------------------------------------------------------ group 4 */
/* resource list at 0x003DDC60 and the free pool at 0x003DCFF0 */
typedef struct R1eLink { struct R1eLink *next; } R1eLink;
typedef struct R1eHolder { uint8_t unk00[4]; R1eLink *first; } R1eHolder;
typedef struct R1eCamCtl {
    uint8_t flags;              /* +0x00 */
    uint8_t unk01[3];
    float   t;                  /* +0x04 */
    int32_t d08;                /* +0x08 */
    void   *link;               /* +0x0C */
} R1eCamCtl;
typedef struct R1eCamSrc { uint8_t unk00[0x30]; int32_t d30; } R1eCamSrc;
typedef struct R1eRes { struct R1eRes *next; uint8_t unk04[8]; void *data; } R1eRes;
typedef struct R1eResList { int32_t count; R1eRes *first; } R1eResList;
extern R1eResList r1e_camList3DDC60;             /* 0x003DDC60 */
extern uint8_t    r1e_camPool3DCFF0[];           /* 0x003DCFF0 */
R1eRes *sub_0003DC70(void *pool);
void sub_0003D880(void *list, void *r);
int  sub_0003AAF0(R1eCamCtl *c, void *out);
void sub_000263B0(void *buf, int a, int b);
extern int32_t r1e_g42CB08;                      /* 0x0042CB08 */

/* trail record (0x0003C250) */
typedef struct R1eTrailOwner { uint8_t unk00[0xC4]; char *slots; } R1eTrailOwner;
typedef struct R1eTrail {
    uint8_t unk00[4];
    void   *fn;                 /* +0x04 */
    uint8_t unk08[8];
    float   f10[6];             /* +0x10 */
    float   rate;               /* +0x28 */
    int32_t d2C;                /* +0x2C */
    int32_t d30;                /* +0x30 */
    R1eTrailOwner *owner;       /* +0x34 */
    int32_t *index;             /* +0x38 */
} R1eTrail;
void sub_001B2150(R1eTrail *t);
int  sub_0003B550(void *a);

/* script variable */
typedef struct R1eVar {
    uint8_t unk00[8];
    int32_t type;               /* +0x08 */
    uint8_t unk0C[4];
    union { int32_t i; float f; } u;    /* +0x10 */
    union { int32_t i; float f; } lo;   /* +0x14 */
    union { int32_t i; float f; } hi;   /* +0x18 */
    union { int32_t i; float f; } d1C;  /* +0x1C */
    union { int32_t i; float f; } d20;  /* +0x20 */
} R1eVar;

/* script object */
typedef struct R1eE24 { int32_t d00; uint8_t unk04[0x20]; } R1eE24;
typedef struct R1eE3C { uint8_t unk00[0x14]; int32_t d14; uint8_t unk18[0x24]; } R1eE3C;
typedef struct R1eSObjX { uint8_t unk00[8]; R1eE24 *ents; } R1eSObjX;
typedef struct R1eSObjY { uint8_t unk00[4]; int32_t n; R1eE3C *ents; } R1eSObjY;
typedef struct R1eSObj {
    uint8_t unk00[4];
    int32_t d04;                /* +0x04 */
    int32_t count;              /* +0x08 */
    uint8_t unk0C[0x1C];
    int32_t d28;                /* +0x28 */
    uint8_t unk2C[4];
    R1eSObjY *y;                /* +0x30 */
    uint8_t unk34[4];
    R1eSObjX *x;                /* +0x38 */
} R1eSObj;
void *sub_0003F650(void *a, R1eSObj *o);
void *r1e_SObjOp(void *a, R1eSObj *o, int op);  /* 0x0003F780 */
extern uint32_t r1e_mask2C4B1C;                  /* 0x002C4B1C */
void sub_0003E410(R1eSObj *o, int a);

/* sound handle owner (0x0003FC40) */
typedef struct R1eSndH { uint8_t unk00[0x1C]; float vol; } R1eSndH;
typedef struct R1eSnd { uint8_t flags; uint8_t unk01[3]; int32_t state; R1eSndH *h; } R1eSnd;
int  sub_00076210(R1eSndH *h);
void sub_00076620(R1eSndH *h);
extern int32_t r1e_g2C4BA4;                      /* 0x002C4BA4 */

/* ------------------------------------------------------------ group 5 */
int  sub_00199DE0(int slot);
void sub_0019B5C0(int st);
typedef struct R1ePair { int32_t a; int32_t h; } R1ePair;
extern R1ePair r1e_pairs3DFEA0[4];               /* 0x003DFEA0 */
extern int32_t r1e_g3DFED4;                      /* 0x003DFED4 */
int  sub_0019A930(int h);
void sub_00047DA0(int a, int b);
typedef struct R1eKey2 { int32_t a; int32_t b; uint8_t unk08[8]; } R1eKey2;
extern R1eKey2  r1e_keys2C7E40[0x75];            /* 0x002C7E40 */
extern uint32_t r1e_bits413410[];                /* 0x00413410 */
extern uint8_t  r1e_ids2C7E08[0x38];             /* 0x002C7E08 */
extern uint32_t r1e_bits4133FC[];                /* 0x004133FC */
int  sub_000D9A70(int id);
int  r1e_CollectRank(void);                      /* 0x0004BE20 */

/* ------------------------------------------------------------ group 6 */
typedef struct R1eCount18 { int32_t n; uint8_t unk04[0x14]; } R1eCount18;
extern R1eCount18 r1e_counts4131C4[24];          /* 0x004131C4 */
extern uint8_t    r1e_flags413430;               /* 0x00413430 */
extern void      *r1e_buf3E05DC, *r1e_buf3E05E0; /* 0x003E05DC / 0x003E05E0 */
extern int32_t    r1e_g42CAC0;                   /* 0x0042CAC0 */
extern uint8_t    r1e_q42CAC4[], r1e_q42CAD0[];  /* 0x0042CAC4 / 0x0042CAD0 */
extern int32_t    r1e_g42CAF0;                   /* 0x0042CAF0 */
extern uint64_t   r1e_frame42C918;               /* 0x0042C918 */
extern uint8_t    r1e_scr3DE700[], r1e_scr3DE610[], r1e_pkt3DE5B0[];
void r1b_PktOp();                    /* 0x00102FA0 */
typedef void (*R1eStateFn)(void);
extern int32_t    r1e_mstate3E0DB4;              /* 0x003E0DB4 */
extern R1eStateFn r1e_mfuncs2C8890[];            /* 0x002C8890 */
int  sub_00057EC0(void);
int  sub_00057EA0(void);
void sub_000580D0(void);
typedef struct R1eMovie {
    uint8_t unk00[0x0C];
    int32_t size;               /* +0x0C */
    int32_t d10;                /* +0x10 */
    uint8_t unk14[8];
    int32_t d1C;                /* +0x1C */
} R1eMovie;
extern R1eMovie r1e_movies2C8900[0x21E];         /* 0x002C8900 */
extern int32_t r1e_mId3E0DBC, r1e_m3E0DC0, r1e_m3E0DC8, r1e_m3E0DB8, r1e_m3E0DCC;
extern void   *r1e_mArg3E0DC4;  /* 0x003E0DC4 caller buffer */
extern uint8_t r1e_mb3E0DD0;                     /* 0x003E0DD0 */

/* ------------------------------------------------------------ group 7 */
void sub_00014940(int a, int b, int c, int d);
extern int32_t r1e_h2DCD48;                      /* 0x002DCD48 */
extern void *r1e_res3E1204, *r1e_res3E1208;      /* 0x003E1204 / 0x003E1208 */
extern void *r1e_res3E1210, *r1e_res3E1214, *r1e_res3E1218;
typedef struct R1eMotInfo { uint8_t unk00[0xD8]; int32_t index; } R1eMotInfo;
typedef struct R1eMotAnim { uint8_t unk00[4]; R1eMotInfo *info; } R1eMotAnim;
typedef struct R1eMotRef { R1eMotAnim *anim; uint8_t unk04[0x10]; int32_t key; } R1eMotRef;
typedef struct R1eMotHdr { uint32_t count; uint8_t unk04[0x0C]; R1eMotRef refs[1]; } R1eMotHdr;
typedef struct R1eMotFrame { int32_t d00, d04, d08, d0C, d10, d14; } R1eMotFrame;
typedef struct R1eMotSet { uint8_t unk00[4]; R1eMotFrame *frames; R1eMotHdr *hdr; } R1eMotSet;
typedef struct R1eMotEnt { uint8_t unk00[0x0C]; R1eMotSet *set; uint8_t unk10[4]; } R1eMotEnt;
R1eMotEnt *sub_000531C0(int a, int b);
void *a5b_AllocCurHigh(int size, const void *file, int line);  /* 0x00053B10 */
void *r1c_LoadThunk(const char *name, int a, int size, void *buf);   /* 0x00037590 */
int  r1e_FileSize(const char *name);             /* 0x000374C0 */
int  sub_001A8680(void);
void sub_001A8770(unsigned ms);
void sub_00077360(int t, uint32_t v);
extern int32_t  r1e_timer2DCDB8;                 /* 0x002DCDB8 */
extern uint32_t r1e_tick2DCDBC;                  /* 0x002DCDBC */
extern uint16_t r1e_tickLo2DCDC0;                /* 0x002DCDC0 */
typedef struct R1eInfo {
    uint8_t unk00[0x10];
    int32_t wide;               /* +0x10 */
    int32_t d14, d18, d1C, d20, d24, d28;   /* +0x14 */
} R1eInfo;
extern int32_t r1e_g3E393C, r1e_mode413168, r1e_g413178, r1e_g413164, r1e_g41316C, r1e_g413170;
float sub_0019C110(void);
int  sub_00057660(int a, int b);
int  sub_000CF790(void *p, int n);
extern uint8_t r1e_buf41FEC0[];                  /* 0x0041FEC0 */
typedef struct R1eMsgSlot { uint8_t unk00[8]; void *snd; uint8_t unk0C[0x14]; } R1eMsgSlot;
typedef struct R1eWorld {
    uint8_t    unk000000[0x122A20];
    R1eMsgSlot msg[4];          /* +0x122A20 */
    void      *font[4];         /* +0x122AA0 */
} R1eWorld;
extern R1eWorld *r1e_world3E3934;                /* 0x003E3934 */
extern int32_t   r1e_g3E3988;                    /* 0x003E3988 */
extern uint32_t *r1e_padMasks2C4AE8;             /* 0x002C4AE8 */
uint32_t sub_0004ED20(int a);

/* ------------------------------------------------------------ group 8 */
typedef struct R1eChapter { uint32_t start; int32_t pages; } R1eChapter;
extern R1eChapter r1e_chapters26C2D0[13];        /* 0x0026C2D0 */
typedef struct R1eHQueue { int32_t items[15]; int32_t count; } R1eHQueue;
void sub_001AD4F0(int h);
typedef void (*R1eJobFn)(void *arg);
typedef struct R1eJob {
    int32_t  d00;               /* +0x00 */
    int32_t  d04;               /* +0x04 */
    int32_t  handle;            /* +0x08 */
    int32_t  bucket;            /* +0x0C */
    int32_t  d10, d14;          /* +0x10 */
    R1eJobFn done;              /* +0x18 */
    void    *arg;               /* +0x1C */
    uint8_t  unk20[4];
    int32_t  owner;             /* +0x24 */
} R1eJob;
typedef struct R1eBucket { uint8_t unk00[0x10]; } R1eBucket;
extern R1eBucket r1e_buckets3E46E0[6];           /* 0x003E46E0 */
int  sub_00057F10(void *e, int key);
void sub_0003D8C0(R1eRes *r);
void sub_001AD520(void);
extern int32_t r1e_running3E3F7C;                /* 0x003E3F7C */
extern R1eJob  r1e_mainJob3E3F64;                /* 0x003E3F64 */
extern R1eRes *r1e_pending3E3F58;                /* 0x003E3F58 */
extern int32_t r1e_idle3E46A0[];                 /* 0x003E46A0 */
extern int32_t r1e_nIdle3E46DC;                  /* 0x003E46DC */
void sub_001AD6E0(void);
R1eJob *sub_00057F30(void);
void sub_001AD6A0(void);
void sub_001AD4B0(int t);
int  sub_00058A40(int a, void *b, void *c, int d, void *e, int f, int g);
void *sub_00053850(int a, int b, void *c, int d);
void sub_00058ED0(int i);                        /* regargs: i=EAX */
typedef struct R1eSpread { float share; uint8_t unk04[0x10]; } R1eSpread;
typedef struct R1eSpreadBank { uint8_t unk00[0xC94AC]; R1eSpread spread[32]; } R1eSpreadBank;
extern R1eSpreadBank *r1e_bank3E474C;            /* 0x003E474C */
extern float   r1e_total2DD1C0;                  /* 0x002DD1C0 */
extern uint8_t r1e_parts2DD1BE;                  /* 0x002DD1BE */

/* ------------------------------------------------------------ group 9 */
int a1a_GroupAdd(void *dev, int a, int b, int (*fn)(void *), int c, int size);  /* 0x001A1030 */
int a1a_GroupReleaseOne(void *dev, int a);      /* 0x001A1060 */
int  sub_0005A1C0(void *a);
int  sub_0005A200(void *a);
int  sub_0005A2F0(void *a);
extern int32_t r1e_sndTab3E4750[0xF3];           /* 0x003E4750 */
extern int32_t r1e_g3E4B1C;                      /* 0x003E4B1C */
typedef struct R1eSlotOwner { uint8_t unk00[0x8C]; int32_t kind; uint8_t unk90[0x34]; char *slots; } R1eSlotOwner;
typedef struct R1eKObj {
    uint8_t unk00[4];
    int32_t kind;               /* +0x04 */
    uint8_t unk08[0x18];
    R1eSlotOwner *owner;        /* +0x20 */
    int32_t d24;                /* +0x24 */
} R1eKObj;
typedef struct R1eHost { uint8_t unk00[0x10]; R1eKObj *obj; } R1eHost;
typedef struct R1eScnCtx { uint8_t unk00[0x3B0]; void *d3B0; } R1eScnCtx;
extern R1eScnCtx *r1e_ctx42C8EC;                    /* 0x0042C8EC */
int   a5b_CountLeadingFlagged(R1eKObj *o);       /* 0x0005A720 */
int r2c_CompQuery(R1eKObj *o, int n, void *a);   /* 0x000EE040 */
void *a12_List_At(R1eKObj *o, int n);            /* 0x0001D2B0 */
void *r1e_ObjChild(R1eKObj *o, int n);           /* 0x0005A760 */
typedef struct R1eUEnt { int32_t used; uint8_t unk04[0x10]; } R1eUEnt;
typedef struct R1eUList { uint8_t unk00[8]; int32_t count; R1eUEnt *ents; } R1eUList;
int  r1e_UsedIndexOf(R1eUList *l, int target);   /* 0x0005A920 */
typedef struct R1eAnimCtl { uint8_t unk00[8]; int32_t cur; } R1eAnimCtl;
typedef struct R1eModel {
    uint8_t unk00[4];
    int32_t kind;               /* +0x04 */
    uint8_t unk08[0x28];
    R1eAnimCtl *anim;           /* +0x30 */
    uint8_t unk34[8];
    struct R1eModel *next;      /* +0x3C */
} R1eModel;
typedef struct R1eSndSlot {
    int32_t d00;                /* +0x00 */
    uint8_t unk04[0x0C];
    struct R1eSndSlot *self;    /* +0x10 */
    int32_t handle;             /* +0x14 */
    void   *owner;              /* +0x18 */
    uint8_t unk1C[0x10];
} R1eSndSlot;
extern R1eSndSlot r1e_sndSlots3E5AC0[32];        /* 0x003E5AC0 */
extern uint8_t    r1e_fxPool3E4B70[];            /* 0x003E4B70 */
extern R1eResList r1e_fxListA3E4B60;             /* 0x003E4B60 */
extern R1eResList r1e_fxListB3E5AAC;             /* 0x003E5AAC */
extern int32_t    a5b_g3E6040, a5b_g2DD4D8;      /* 0x003E6040 / 0x002DD4D8 */
void  sub_00036A90(void *pool, int stride, int n);
void  sub_0003D860(void *list);
char *r1c_PoolTake(void *pool, int stride);      /* 0x00036AD0 */
typedef struct R1eFx {
    uint8_t unk00[0x14];
    uint8_t link[0x0C];         /* +0x14 list link */
    struct R1eFx *self;         /* +0x20 */
    float   scale;              /* +0x24 */
    int32_t d28;                /* +0x28 */
} R1eFx;

/* ------------------------------------------------------------ group 10 */
typedef struct R1eSesEnt { void *block; uint8_t unk04[0x10]; } R1eSesEnt;
typedef struct R1eSesBlock { uint8_t unk00[0x30]; } R1eSesBlock;
typedef struct R1eSes {
    uint8_t    unk00[8];
    int32_t    count;           /* +0x08 */
    void      *tab;             /* +0x0C */
    uint8_t    tabData[0x10];   /* +0x10 */
    R1eSesEnt  ents[15];        /* +0x20 */
    uint8_t    unk14C[4];
    R1eSesBlock blocks[16];     /* +0x150 */
} R1eSes;
typedef struct R1eSesFile { uint32_t magic; int32_t version; uint8_t unk08[8]; R1eSes body; } R1eSesFile;
void r1c_SndOwnerStop(void *fx);                 /* 0x0005BE30 */
void r1c_SndOwnerFree(void *fx);                 /* 0x0005BC50 */
void sub_00036B10(void *entry);
void r1e_SceneFxFree(void);                      /* 0x0005CA00 */
typedef struct R1eFxList { uint8_t unk00[4]; R1eUList *list; } R1eFxList;
typedef struct R1eSceneItem {
    uint8_t  unk000[0x0C];
    uint8_t  flags;             /* +0x0C */
    uint8_t  unk00D[0x12F];
    R1eFxList *fx;              /* +0x13C */
    uint8_t  unk140[0x10];
} R1eSceneItem;
typedef struct R1eDrawCtx {
    uint8_t  unk00[0x2C];
    union { int32_t style; R1eSceneItem **items; } u2C;  /* +0x2C */
    uint8_t  unk30[8];
    R1eSObjX *vars;             /* +0x38 */
} R1eDrawCtx;
typedef struct R1eDrawObj { uint8_t unk00[0x34]; R1eDrawCtx *ctx; } R1eDrawObj;
int  sub_0005D620(int ea, void *ed, int a, int b, void *c);   /* regargs: ea=EAX ed=EDX; c = base pointer */
int  sub_0003EB10(void *var);
typedef struct R1eCell { uint8_t ch; int8_t attr; } R1eCell;
typedef struct R1ePage { union { R1eCell *p; int32_t n; } row[2]; uint8_t unk08[4]; R1eCell data[1]; } R1ePage;
extern R1ePage **a5b_cellTables;                 /* 0x003E6050 */
extern int32_t  *r1e_cellOwned3E604C;            /* 0x003E604C */
void a5b_ChansReset(void);                       /* 0x0005EB50 */
void r1e_CellPagesFree(void);                    /* 0x0005E930 */
extern int32_t   a5b_g3E608C;                    /* 0x003E608C */

/* ------------------------------------------------------------ group 11 */
typedef struct R1eItemGroup {
    int32_t count;              /* +0x00 */
    uint8_t unk04[4];
    R1eSceneItem *items;        /* +0x08 */
    uint8_t unk0C[4];
    struct R1eItemGroup *next;  /* +0x10 */
} R1eItemGroup;
typedef struct R1eScene { uint8_t unk00[0x1E8]; R1eItemGroup **groups; } R1eScene;
extern R1eScene *r1e_scene42C8E4;                /* 0x0042C8E4 */

/* ------------------------------------------------------------ group 12 */
typedef struct R1eSprite {
    float    f00, f04;          /* +0x00 */
    int32_t  d08, d0C;          /* +0x08 */
    float    f10, f14;          /* +0x10 */
    int32_t  d18;               /* +0x18 */
    float    f1C, f20;          /* +0x1C */
    int32_t  d24, d28, d2C, d30;/* +0x24 */
    float    f34, f38;          /* +0x34 */
    void    *d3C;               /* +0x3C */
    int32_t  d40;               /* +0x40 */
    uint8_t  unk44[0x3C];
    int32_t  d80, d84;          /* +0x80 */
    float    f88;               /* +0x88 */
    uint32_t col[4];            /* +0x8C */
} R1eSprite;
extern int32_t r1e_viewOn37C4C0;                 /* 0x0037C4C0 */
extern int32_t r1e_viewKind37C4C4;               /* 0x0037C4C4 */
extern float   r1e_viewZoom37C4C8;               /* 0x0037C4C8 */
extern float   r1e_view37C4CC[10];               /* 0x0037C4CC */
extern int32_t r1e_qA37ED04[8];                  /* 0x0037ED04 */
extern int32_t r1e_qStateA37ED24;                /* 0x0037ED24 */
extern float   r1e_qWaitA37ED28;                 /* 0x0037ED28 */
extern float   r1e_qTimeA37ED3C;                 /* 0x0037ED3C */
extern int32_t r1e_qB37E094[8];                  /* 0x0037E094 */
extern int32_t r1e_qStateB37E0B4;                /* 0x0037E0B4 */
extern float   r1e_qWaitB37E0B8;                 /* 0x0037E0B8 */
extern int16_t r1e_qLeftB37E0BE;                 /* 0x0037E0BE */
typedef struct R1eXform {
    float   ax[3][4];           /* +0x00 */
    int32_t d30, d34, d38;      /* +0x30 */
    float   scale[6];           /* +0x3C */
    float   f54;                /* +0x54 */
} R1eXform;

/* ------------------------------------------------------------ group 13 */
typedef struct R1eLink48 {
    int32_t d00, d04;           /* +0x00 */
    struct R1eLink48 *next;     /* +0x08 */
    int32_t d0C, d10, d14, d18, d1C, d20, d24, d28, d2C, d30;   /* +0x0C */
    float   scale;              /* +0x34 */
    float   f38, f3C;           /* +0x38 */
    int32_t d40, d44;           /* +0x40 */
} R1eLink48;
typedef struct R1eLinkHost { uint8_t unk00[0x40]; R1eLink48 *first; } R1eLinkHost;
extern int32_t  r1e_seqQC381850[4];              /* 0x00381850 */
extern uint16_t r1e_seqStateC381860;             /* 0x00381860 */
extern float    r1e_seqTimeC381864;              /* 0x00381864 */
extern float    r1e_seqInitC381868;              /* 0x00381868 */
extern uint32_t r1e_lsFlags3DA098;               /* 0x003DA098 */
extern int32_t  r1e_lsMode3DA09C;                /* 0x003DA09C */
extern float    r1e_lsGain3DA0A0;                /* 0x003DA0A0 */
extern float    r1e_lsPos3DA0A4[4];              /* 0x003DA0A4 */
extern float    r1e_lsPan3DA0B0;                 /* 0x003DA0B0 */
extern float    r1e_points2836AC[][4];           /* 0x002836AC */
extern float    r1e_fps42C964;                   /* 0x0042C964 */
extern int32_t  r1e_g42C8B4, r1e_g42C854, r1e_g42C8E0, r1e_g42C958, r1e_g42C9D4, r1e_g42C8F4;
extern int32_t  r1e_g42C960, r1e_g42C8E8, r1e_g42C8F8, r1e_g42C8D8, r1e_g42C934, r1e_g42C95C, r1e_g42C954;
extern float    r1e_g42C8F0;                     /* 0x0042C8F0 */
extern float    r1e_camMat3E1220[4][4];          /* 0x003E1220 */
extern float    r1e_camFov3E1260;                /* 0x003E1260 */

#endif
