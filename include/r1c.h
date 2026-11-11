#ifndef R1C_H
#define R1C_H
#include "oogie.h"
#include <string.h>

/* Area r1c: game functions 0x00012000..0x00060000 (third pass). Names
   inferred. Register-argument mappings are in config/function_states_r1c.csv. */

/* Zero a block (the original inlines this as rep stos). The intrinsic is
 * used only for the 32-bit x86 comparison build; other targets use memset. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define R1C_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) / 4)
#else
#define R1C_ZERO(p, n) memset((p), 0, (n))
/* ------------------------------------------------------------ group 6 */
typedef struct R1cTexCtx { uint8_t unk00[0x28]; uint64_t q28; } R1cTexCtx;
R1cTexCtx *sub_001B9650(int h);
int  sub_00038F10(int p);
void sub_001A27D0(int mode);

/* colour scale block at 0x0037EE10 */
typedef struct R1cColBlk {
    int32_t inited;             /* +0x00 */
    uint8_t unk04[8];
    uint8_t alpha;              /* +0x0C */
    uint8_t unk0D[0x37];
    float   scale[13][2];       /* +0x44 */
} R1cColBlk;
extern R1cColBlk r1c_col37EE10;

typedef struct R1cChan2C { int32_t kind; uint8_t unk04[0x28]; } R1cChan2C;
extern R1cChan2C r1c_chan3DA4A8[];          /* 0x003DA4A8 */
int  sub_000390E0(int i, int v);            /* regargs: i=EAX */
int  sub_00039440(int i, int v);            /* regargs: i=EAX */
int  sub_000396E0(int v);

typedef struct R1cResEnt { uint8_t unk00[0x0C]; void *res; } R1cResEnt;
typedef struct R1cResList { uint8_t unk00[0x10]; void *res; } R1cResList;
R1cResEnt *sub_0003DC50(void *list);

typedef struct R1cVar {
    uint8_t unk00[8];
    int32_t type;               /* +0x08 */
    uint8_t unk0C[4];
    union { int32_t i; float f; } u;    /* +0x10 */
} R1cVar;

BackgroundJob *r1c_JobById(int id);        /* 0x00057F80 (recovered in area a5b) */
void sub_0003D910(void *node);
void sub_001AD6A0(void);

typedef struct R1cStream {
    int32_t d00, d04, d08, d0C;
    int32_t count;              /* +0x10 */
    int32_t size;               /* +0x14 */
    int32_t d18, d1C;
} R1cStream;
extern int32_t r1c_stream2DD4D8;            /* 0x002DD4D8 */

int  r1c_PktTexBase(int p);
void r1c_ColInitOnce(void);
int  r1c_CamCompare(R1cCam *a, R1cCam *b);
void r1c_ListRelease(R1cResList *l);
int  r1c_VarIsSet(R1cVar *v);
int  r1c_JobWake(int id);
int  r1c_StreamReset(R1cStream *s);

/* ------------------------------------------------------------ group 7 */
int  sub_00079460(void);
int  sub_0019BE70(int mask);
void sub_0019BE90(int mask);
void sub_0019BEB0(int mask);
extern int32_t r1c_state3816D0;             /* 0x003816D0 */

typedef struct R1cEmitter {
    uint8_t unk00[0x14];
    int32_t d14;                /* +0x14 */
    int32_t target;             /* +0x18 */
    int32_t param[16];          /* +0x1C */
} R1cEmitter;
void sub_0005A400(void *o);

typedef struct R1cMot { uint8_t unk00[0x10]; int32_t id; } R1cMot;
typedef struct R1cMotNode {
    struct R1cMotNode *next;    /* +0x00 */
    uint8_t unk04[8];
    R1cMot *mot;                /* +0x0C */
} R1cMotNode;
typedef struct R1cMotList {
    int32_t from;               /* +0x00 */
    int32_t to;                 /* +0x04 */
    uint8_t unk08[4];
    R1cMotNode *head;           /* +0x0C */
} R1cMotList;
typedef struct R1cMotObj { uint8_t unk00[0x130]; R1cMotList *motions; } R1cMotObj;
int  sub_00035D20(R1cMot *m, void *o, int from, int to, int flags);

typedef struct R1cSlotObj { uint8_t unk00[0x10]; int32_t slot[16]; } R1cSlotObj;
void sub_0005A6E0(void *o);
void sub_00035320(void *o, int a);

typedef struct R1cDataObj { uint8_t unk00[0xE8]; uint8_t desc[4]; } R1cDataObj;
void  sub_00053710(int heap);
int   sub_0004F680(void *desc);
void *sub_00053AB0(int size, int a, int tag);
void  sub_000512D0(void *desc, void *p);
void  sub_00053740(void);
extern void *r1c_data3DA0D0;                /* 0x003DA0D0 */
extern void *r1c_obj2836DC;                 /* 0x002836DC */

typedef struct R1cFlagVar { uint8_t unk00[4]; int32_t value; } R1cFlagVar;
R1cFlagVar *sub_0003F8B0(int ctx, void *type, int a);
extern uint8_t r1c_flagType2C4B94[];        /* 0x002C4B94 variable type descriptor */
extern char r1c_name3DE808[32];             /* 0x003DE808 */
extern const char r1c_fmtS25FF04[];         /* 0x0025FF04 "%s" */

extern int32_t r1c_q3DFECC;                 /* 0x003DFECC */
void sub_001999E0(int ch, int voice);
void sub_0019B800(int ch, int voice);
void sub_00047DA0(int vol, int voice);

void r1c_PadModeTick(void);
int  r1c_ObjPlayMotion(R1cMotObj *o, int id, int flags);
int  r1c_ListPlayMotion(void *o, R1cMotList *l, int id, int flags);
void r1c_ObjSlotsReset(R1cSlotObj *o);
int  r1c_ObjLoadData(R1cDataObj *o);
R1cFlagVar *r1c_FlagVarSet(int ctx, int value, const char *name);
void r1c_SndStartPending(int voice);

/* ------------------------------------------------------------ group 8 */
extern int32_t r1c_tex380C24[9];            /* 0x00380C24 texture handles */
extern uint32_t r1c_state37C4F8[0xD9E];     /* 0x0037C4F8 game state block */
extern int32_t r1c_g3813B4;                 /* 0x003813B4 */
void  sub_001B9FC0(int h);
void *sub_000529F0(void);
void  sub_0004F5D0(void *p);

extern int32_t  r1c_seqStep37C544;          /* 0x0037C544 */
extern uint32_t r1c_seqFlags37C540;         /* 0x0037C540 */
extern int32_t  r1c_seqStep37ED04;          /* 0x0037ED04 */
extern uint32_t r1c_seqFlags37ED00;         /* 0x0037ED00 */
void sub_00028630(void); void sub_00028740(void); void sub_00028890(void);
void sub_00028930(void); void sub_00028B10(void); void sub_00028CB0(void);
void sub_0002A070(void); void sub_0002A160(void); void sub_0002A240(void);
void sub_0002A2C0(void); void sub_0002A3A0(void); void sub_0002A460(void);

typedef struct R1cActorState { uint8_t unk00[8]; int32_t id; } R1cActorState;
typedef struct R1cMotTab { uint8_t unk00[4]; R1cMotNode *head; } R1cMotTab;
typedef struct R1cActor {
    uint8_t        unk00[0x30];
    R1cActorState *state;       /* +0x30 */
    uint8_t        unk34[0xF8];
    R1cMotTab     *table;       /* +0x12C */
    uint8_t        unk130[4];
    void          *effect;      /* +0x134 */
} R1cActor;
void sub_00033C20(void *effect);
void sub_00033D10(void *o, void *entry);

typedef struct R1cRBuf { uint8_t unk00[8]; void *data; } R1cRBuf;
typedef struct R1cScene { uint8_t unk00[0x1E8]; void *root; } R1cScene;
R1cRBuf *sub_0001F210(int a, int b);
void     sub_0001DA40(R1cRBuf *b);
R1cRBuf *sub_00022260(int a, int b, int c, int d);
void     sub_0001CFF0(void *root, R1cRBuf *b, int a);
extern R1cRBuf *r1c_bufA3DA0C8, *r1c_bufB3DA0CC;
extern void *r1c_bufAData3DA0C0, *r1c_bufBData3DA0B8;
extern R1cScene *r1c_scene42C8E4;           /* 0x0042C8E4 */

typedef struct R1cCamNode {
    uint8_t    unk00[0x0C];
    R1cCamSet *set;             /* +0x0C */
    R1cCamSet  setData;         /* +0x10 */
    uint8_t    unk18[8];
} R1cCamNode;
extern R1cCamNode r1c_camNodes3DD000[99];   /* 0x003DD000 */
extern uint8_t r1c_camList3DDC60[16];       /* 0x003DDC60 active camera list (count, first...) */
extern int32_t r1c_camFlag42CB04, r1c_camFlag42CB08, r1c_camFlag42CB0C;

typedef struct R1cSndRec { uint8_t unk00[8]; int32_t handle; uint8_t unk0C[0x14]; } R1cSndRec;
typedef struct R1cStage {
    uint8_t   unk00[0x2B4D84];
    R1cSndRec amb;              /* +0x2B4D84 */
    int32_t   ambTable;         /* +0x2B4DA4 */
} R1cStage;
extern R1cStage *r1c_stage3DFA5C;           /* 0x003DFA5C */
typedef struct R1cWorld {
    uint8_t   unk00[0x122A20];
    R1cSndRec snd[4];           /* +0x122A20 */
    int32_t   sndTable[4];      /* +0x122AA0 */
} R1cWorld;
extern R1cWorld *r1c_world3E3934;           /* 0x003E3934 */
void sub_00076060(int h);
int  sub_0003FA70(int table, int id);
void sub_0003FCB0(void *rec, int item, int a, int b, float c);

typedef struct R1cHeap { int32_t d00; char *start; char *end; int32_t id; } R1cHeap;
typedef struct R1cHeapReg { int32_t d00, d04, d08, d0C, d10, d14; } R1cHeapReg;
int  sub_001AA240(R1cHeapReg *r);

typedef struct R1cJobFull {
    int32_t state, thread, handle, d0C, d10, d14;
    void *func, *arg;
} R1cJobFull;
void sub_001AD440(int thread);
void sub_001AD6E0(void);
void sub_001AA460(int handle);
void sub_001AD4B0(int tid);
extern int32_t r1c_threads3E46A0[16];       /* 0x003E46A0 */
extern int32_t r1c_nThreads3E46DC;          /* 0x003E46DC */

typedef struct R1cIdEnt {
    uint8_t unk00[0x0C];
    struct R1cIdEnt *self;      /* +0x0C */
    int32_t id;                 /* +0x10 */
    uint8_t unk14[0x0C];
    uint8_t body[0x450];        /* +0x20 */
} R1cIdEnt;
typedef struct R1cIdNode {
    struct R1cIdNode *next;     /* +0x00 */
    uint8_t unk04[8];
    R1cIdEnt *ent;              /* +0x0C */
} R1cIdNode;
typedef struct R1cIdList { uint8_t unk00[4]; R1cIdNode *head; } R1cIdList;
void sub_0005CAF0(void *body);

typedef struct R1cEvObj {
    uint8_t unk00[4];
    int32_t busy;               /* +0x04 */
    uint8_t unk08[0x20];
    int32_t kind;               /* +0x28 */
    uint8_t unk2C[4];
    void   *child;              /* +0x30 */
} R1cEvObj;
int  sub_0004ECE0(int kind);
void sub_0005A990(void *o, void (*fn)(void), void *ctx);
void sub_0005D030(void);
extern uint8_t r1c_ctx2DD624[];             /* 0x002DD624 */

void r1c_GameStateReset(void);
void r1c_SeqARun(void);
void r1c_SeqBRun(void);
void r1c_ObjRefreshMotion(void *unused, R1cActor *o);
void r1c_RenderBufsCreate(void);
void r1c_CamInit(void);
void r1c_StageAmbient(int id);
int  r1c_HeapSetup(R1cHeap *buf, int size);
void r1c_JobReset(void);
void r1c_JobYield(void);
R1cIdEnt *r1c_IdListGet(R1cIdList *l, int id);
int  r1c_ObjEventEx(int ev, R1cEvObj *o, int mode);

#endif

/* ------------------------------------------------------------ thunk targets */
void sub_00014B60(void);
void sub_00014BE0(int which);
void sub_0002C5E0(void);
int  sub_001A11B0(void *group);
void sub_000373A0(int a, int b, int c, int d);
void sub_000375A0(void);
void sub_00037B20(int arg);
void sub_001997D0(void);
int  sub_00199D90(int i);
int  sub_00199E70(int i);
int  sub_0019A930(int i);
void sub_0019AC20(int h, int i, int v);
void sub_00057C70(void);
int  sub_001A8680(void);

void r1c_PktInitThunk(void);
void r1c_PktFlushThunk(int which);
void r1c_StateUpdateThunk(void);
int  r1c_GroupResumeThunk(void *group);
void r1c_LoadThunk(int a, int b, int c, int d);
void r1c_TableResetThunk(void);
void r1c_TablePassThunk(int arg);
void r1c_Store402760Thunk(void);
int  r1c_EntIsLinkedThunk(int i);
int  r1c_SlotHas4Thunk(int i);
int  r1c_GetRecThunk(int i);
void r1c_SetRecThunk(int h, int i, int v);
void r1c_ShutdownThunk(void);
int  r1c_Poll1A8680Thunk(void);

/* ------------------------------------------------------------ group 2 */
extern uint32_t r1c_work42CE80[0x1600];     /* 0x0042CE80 work area */
extern uint32_t r1c_flags37F0C8;            /* 0x0037F0C8 */
extern uint32_t r1c_flags37C4F8;            /* 0x0037C4F8 */
void sub_0002C4E0(int arg);                 /* regargs: arg=EAX */

/* chained node with an effect block at +0x20 */
typedef struct R1cNode {
    int32_t busy;               /* +0x00 */
    uint8_t unk04[0x0C];
    struct R1cNode *next;       /* +0x10 */
    uint8_t unk14[0x0C];
    uint8_t blk[0xD0];          /* +0x20 block (flags at blk+0xB8) */
} R1cNode;
void sub_001B6060(void *blk);
void sub_001B6070(void *blk);
int  sub_001B6140(void *blk);
void sub_001B6270(void *blk);
void sub_001B6130(void *blk);
void sub_001B6310(void *blk, float a, float b, float c, float d);
void sub_001B6610(void *blk, float a, float b, float c, float d);
void sub_00033560(void *node);

/* camera shake block at 0x003DA098 */
typedef struct R1cShake {
    uint32_t flags;             /* +0x00 */
    int32_t  d04;               /* +0x04 */
    float    f08;               /* +0x08 */
    float    x, y, z;           /* +0x0C */
    float    f18;               /* +0x18 */
} R1cShake;
extern R1cShake r1c_shake3DA098;

int  sub_001A8490(int h, int pos, int whence);
int  sub_001A8330(int h);
void sub_000586E0(int arg);

/* 0x48-byte record of the table at 0x0042CB20 (10 records) */
typedef struct R1cRec48 {
    uint8_t  unk00[0x20];
    int32_t  count;             /* +0x20 */
    uint32_t flags;             /* +0x24 */
    uint8_t  unk28[0x20];
} R1cRec48;
extern R1cRec48 r1c_tbl42CB20[10];
void sub_00037830(R1cRec48 *r);             /* regargs: r=EAX */

/* paged table of 10-byte elements */
typedef struct R1cPaged {
    uint8_t  *direct;           /* +0x00 */
    uint8_t **pages;            /* +0x04 */
    uint16_t  count;            /* +0x08 */
} R1cPaged;
extern R1cPaged *r1c_paged3DA314;

void  r1c_ClearWork42CE80(void);
void  r1c_SetFlagBit0(int mode);
void  r1c_SetFlagBit1(int mode);
void  r1c_StepIfEnabled(int arg);
void  r1c_NodeFreeChain(R1cNode *n);
int   r1c_NodeChainBusy(R1cNode *n);
void  r1c_NodeChainSet4(R1cNode *n, float a, float b, float c, float d);
void  r1c_NodeChainSet4b(R1cNode *n, float a, float b, float c, float d);
void  r1c_NodeChainRun(R1cNode *n, int on);
void  r1c_ShakeReset(void);
void  r1c_ShakeSetOffset(float x, float y, float z);
void *r1c_PagedElem(int i);

/* ------------------------------------------------------------ group 3 */
/* effect controller reached through an object's owner */
typedef struct R1cFxCtl {
    uint8_t unk00[4];
    int32_t param;              /* +0x04 */
    void   *handler;            /* +0x08 must be 0x0001ED90 */
    uint8_t unk0C[0x0C];
    float   rate;               /* +0x18 */
} R1cFxCtl;
typedef struct R1cFxOwner {
    uint8_t   unk00[0xA8];
    R1cFxCtl *ctl;              /* +0xA8 */
} R1cFxOwner;
typedef struct R1cFxObj {
    uint8_t     unk00[0x0C];
    uint32_t    flags;          /* +0x0C */
    uint8_t     unk10[0x18];
    R1cFxOwner *owner;          /* +0x28 */
} R1cFxObj;
void sub_0001ED90(void);

int  sub_0002CC20(void);
void sub_001A1060(void *target, int ev);
void sub_00058190(void);
void sub_000580D0(void);

int  sub_00057690(int id, int *area, int *sub);
int  a6b_Printf3(char *buf, int size, const char *fmt, ...);   /* 0x0007E070 */
extern const char r1c_fmtFxPath[];          /* 0x00261498 "host0:data/world/%02x%02x/ptk/fx%02x%02x" */
extern const char r1c_fmtPtPath[];          /* 0x0026BE18 "host0:data/world/%02x%02x/ptk/pt%02x%02x" */

/* pool of fixed-stride entries; the header takes the first stride */
typedef struct R1cPoolOwner { uint8_t unk00[4]; int32_t used; } R1cPoolOwner;
typedef struct R1cPoolEnt {
    uint32_t      flags;        /* +0x00 bit 0 = in use */
    R1cPoolOwner *owner;        /* +0x04 */
} R1cPoolEnt;
typedef struct R1cPool { int32_t count; } R1cPool;

/* camera settings */
typedef struct R1cCamSet { uint32_t flags; float value; } R1cCamSet;
typedef struct R1cCam { uint8_t unk00[0x0C]; R1cCamSet *set; } R1cCam;
extern int32_t r1c_camCount3DDC60;          /* 0x003DDC60 */
extern R1cCam *r1c_cam3DDC64;               /* 0x003DDC64 */

/* group header block at 0x003DDCC0 */
typedef struct R1cGrpHdr {
    int32_t d00;                /* +0x00 */
    int32_t d04;                /* +0x04 */
    int32_t list[4];            /* +0x08 cleared by 0x0003D860 */
    int32_t data;               /* +0x18 */
    int32_t d1C;                /* +0x1C */
    int32_t recs;               /* +0x20 */
    int32_t d24;                /* +0x24 */
    int32_t d28;                /* +0x28 */
} R1cGrpHdr;
extern R1cGrpHdr r1c_grp3DDCC0;
void sub_0003D860(void *blk);

typedef struct R1cRange {
    uint8_t unk00[8];
    int32_t state;              /* +0x08 */
    uint8_t unk0C[4];
    int32_t cur;                /* +0x10 */
    int32_t min;                /* +0x14 */
    int32_t max;                /* +0x18 */
} R1cRange;

typedef void (*R1cHFunc)(int ev, void *o, int mode);
typedef struct R1cHTab { uint8_t unk00[4]; R1cHFunc handle; } R1cHTab;
typedef struct R1cHObj { uint8_t unk00[0x38]; R1cHTab *vt; } R1cHObj;
int  sub_0003F780(int ev, void *o, int mode);

typedef struct R1cRec18 { uint16_t w00; uint8_t unk02[0x16]; } R1cRec18;
extern R1cRec18 r1c_tbl3DFA68[];
void sub_0019A4B0(int i);

typedef struct R1cKeyVal { int32_t key, a, b, c; } R1cKeyVal;
extern R1cKeyVal r1c_tbl2C7A84[9];

extern int32_t r1c_q3DFEC0, r1c_q3DFEC4, r1c_q3DFEC8;
void sub_00048AA0(int arg);                 /* regargs: arg=ESI */

typedef struct R1cSlot14 { int32_t used; uint8_t unk04[0x10]; } R1cSlot14;
typedef struct R1cSlotList {
    uint8_t   unk00[8];
    int32_t   count;            /* +0x08 */
    uint8_t   unk0C[4];
    R1cSlot14 slot[1];          /* +0x10 */
} R1cSlotList;

void r1c_FxCtlSetParam(R1cFxObj *o, int v);
void r1c_FxCtlSetRate(R1cFxObj *o, float rate);
void r1c_MainLoop(void *target);
void r1c_FxPackPath(char *buf, int id);
R1cPoolEnt *r1c_PoolTake(R1cPool *pool, int stride);
float r1c_CamValue(void);
void r1c_GroupHdrReset(void);
void r1c_ObjDispatch(int ev, R1cHObj *o, int mode);
void r1c_SlotStop(int i);
int  r1c_LookupA(int key);
int  r1c_LookupB(int key);
void r1c_QueueKick(int arg);
void r1c_PtPackPath(char *buf, int id);
int  r1c_SlotFindFree(R1cSlotList *l);

/* ------------------------------------------------------------ group 4/5 */
extern int32_t r1c_mode381400;              /* 0x00381400 */
void sub_0002D230(void);
void sub_0002D790(void);
void sub_0002DBC0(void);
void sub_0002C870(void);

/* LSB-first bit stream reader */
struct R1cBits;
typedef void (*R1cBitsRefill)(struct R1cBits *b);
typedef struct R1cBits {
    int32_t       limit;        /* +0x00 byte position that triggers refill (<0 never) */
    uint32_t     *base;         /* +0x04 */
    uint32_t     *ptr;          /* +0x08 current word */
    uint32_t      bit;          /* +0x0C bit index in the word */
    int32_t       pos;          /* +0x10 bytes consumed */
    R1cBitsRefill refill;       /* +0x14 */
    int32_t       d18;          /* +0x18 */
} R1cBits;

typedef int (*R1cPoolFn)(void *entry, void *ctx);

extern int32_t r1c_reqCount3DA390;          /* 0x003DA390 */
typedef struct R1cReq { int32_t a, b; int64_t value; } R1cReq;
extern R1cReq r1c_req3DA398[16];            /* 0x003DA398 */

extern char r1c_free3DCFF0[];               /* 0x003DCFF0 free camera list */
void sub_0003D8C0(void *node);              /* unlink */
void sub_0003D880(void *list, void *node);  /* append */

typedef struct R1cXNode {
    uint8_t  unk00[0x40];
    uint8_t  m40[0x40];         /* +0x40 transform */
    struct R1cXNode *parent;    /* +0x80 */
    struct R1cXNode *sibling;   /* +0x84 */
    struct R1cXNode *child;     /* +0x88 */
    uint8_t  unk8C[4];
    uint32_t flags;             /* +0x90 bit 0x40 = hidden */
} R1cXNode;
void sub_001AD7C0(void *dst, void *parentM, void *node);

typedef struct R1cAttObj { uint8_t unk00[0x12C]; void *table; } R1cAttObj;
void *sub_00053630(const char *name, int a, int b);
char *sub_000363F0(void *table, int key);
void  sub_000358C0(void *slot, void *res);

typedef struct R1cJobRef { uint8_t unk00[0x0C]; void *obj; } R1cJobRef;
extern uint8_t r1c_jobLists[6][16];         /* 0x003E46E0 */
int  sub_001AD560(void);                    /* current thread id */
R1cJobRef *sub_0003DBC0(void *list, int (*match)(void *, int), int key);
int  a50_ObjIdIs(void *ref, int id);        /* 0x00057EF0 */

typedef struct R1cChan { int32_t handle; void *owner; uint8_t unk08[0x24]; } R1cChan;
extern R1cChan r1c_chan3E5AD4[32];          /* 0x003E5AD4 */
void sub_00036B10(void *entry);

typedef struct R1cEmit {
    float   x, y, z, w;         /* +0x00 */
    int32_t d10, d14;           /* +0x10 */
    int32_t r, g, b;            /* +0x18 */
    int32_t d24;                /* +0x24 */
    float   f28;                /* +0x28 */
} R1cEmit;

typedef struct R1cBankEnt { uint8_t unk00[0x18]; int32_t id; } R1cBankEnt;
extern R1cPool *r1c_bank283698;             /* 0x00283698 */

typedef struct R1cJob {
    int32_t state;              /* +0x00 */
    int32_t thread;             /* +0x04 */
    int32_t handle;             /* +0x08 */
} R1cJob;
void sub_001AA310(int handle);
void r1b_PktOp(void *pkt, ...);             /* 0x00102FA0 */
void sub_001AD520(void);

void     r1c_ModeRun(void);
uint32_t r1c_BitRead(R1cBits *b, uint32_t n);
int      r1c_PoolForEach(R1cPool *pool, int stride, R1cPoolFn fn, void *ctx);
void    *r1c_PoolFind(R1cPool *pool, int stride, R1cPoolFn fn, void *ctx);
void     r1c_ShakeSet4(float x, float y, float z, float w);
void     r1c_ReqPush(int value, int a, int b);
void     r1c_CamFlush(void);
void     r1c_NodeUpdate(R1cXNode *n);
void     r1c_ObjAttach(R1cAttObj *o, int key, const char *name);
BackgroundJob *r1c_JobCurrent(void);       /* 0x00057F30 (recovered in area a5b) */
void     r1c_SndOwnerFree(char *owner);
void     r1c_EmitDefaults(R1cEmit *e);
uint32_t r1c_BitReadTagged(uint32_t *p);
void    *r1c_BankFind(int id);
void     r1c_JobFinish(void);
void     r1c_SndOwnerStop(void *owner);

/* ------------------------------------------------------------ group 6 */
typedef struct R1cTexCtx { uint8_t unk00[0x28]; uint64_t q28; } R1cTexCtx;
R1cTexCtx *sub_001B9650(int h);
int  sub_00038F10(int p);
void sub_001A27D0(int mode);

/* colour scale block at 0x0037EE10 */
typedef struct R1cColBlk {
    int32_t inited;             /* +0x00 */
    uint8_t unk04[8];
    uint8_t alpha;              /* +0x0C */
    uint8_t unk0D[0x37];
    float   scale[13][2];       /* +0x44 */
} R1cColBlk;
extern R1cColBlk r1c_col37EE10;

typedef struct R1cChan2C { int32_t kind; uint8_t unk04[0x28]; } R1cChan2C;
extern R1cChan2C r1c_chan3DA4A8[];          /* 0x003DA4A8 */
int  sub_000390E0(int i, int v);            /* regargs: i=EAX */
int  sub_00039440(int i, int v);            /* regargs: i=EAX */
int  sub_000396E0(int v);

typedef struct R1cResEnt { uint8_t unk00[0x0C]; void *res; } R1cResEnt;
typedef struct R1cResList { uint8_t unk00[0x10]; void *res; } R1cResList;
R1cResEnt *sub_0003DC50(void *list);

typedef struct R1cVar {
    uint8_t unk00[8];
    int32_t type;               /* +0x08 */
    uint8_t unk0C[4];
    union { int32_t i; float f; } u;    /* +0x10 */
} R1cVar;

BackgroundJob *r1c_JobById(int id);        /* 0x00057F80 (recovered in area a5b) */
void sub_0003D910(void *node);
void sub_001AD6A0(void);

typedef struct R1cStream {
    int32_t d00, d04, d08, d0C;
    int32_t count;              /* +0x10 */
    int32_t size;               /* +0x14 */
    int32_t d18, d1C;
} R1cStream;
extern int32_t r1c_stream2DD4D8;            /* 0x002DD4D8 */

int  r1c_PktTexBase(int p);
void r1c_ColInitOnce(void);
int  r1c_CamCompare(R1cCam *a, R1cCam *b);
void r1c_ListRelease(R1cResList *l);
int  r1c_VarIsSet(R1cVar *v);
int  r1c_JobWake(int id);
int  r1c_StreamReset(R1cStream *s);

/* ------------------------------------------------------------ group 7 */
int  sub_00079460(void);
int  sub_0019BE70(int mask);
void sub_0019BE90(int mask);
void sub_0019BEB0(int mask);
extern int32_t r1c_state3816D0;             /* 0x003816D0 */

typedef struct R1cEmitter {
    uint8_t unk00[0x14];
    int32_t d14;                /* +0x14 */
    int32_t target;             /* +0x18 */
    int32_t param[16];          /* +0x1C */
} R1cEmitter;
void sub_0005A400(void *o);

typedef struct R1cMot { uint8_t unk00[0x10]; int32_t id; } R1cMot;
typedef struct R1cMotNode {
    struct R1cMotNode *next;    /* +0x00 */
    uint8_t unk04[8];
    R1cMot *mot;                /* +0x0C */
} R1cMotNode;
typedef struct R1cMotList {
    int32_t from;               /* +0x00 */
    int32_t to;                 /* +0x04 */
    uint8_t unk08[4];
    R1cMotNode *head;           /* +0x0C */
} R1cMotList;
typedef struct R1cMotObj { uint8_t unk00[0x130]; R1cMotList *motions; } R1cMotObj;
int  sub_00035D20(R1cMot *m, void *o, int from, int to, int flags);

typedef struct R1cSlotObj { uint8_t unk00[0x10]; int32_t slot[16]; } R1cSlotObj;
void sub_0005A6E0(void *o);
void sub_00035320(void *o, int a);

typedef struct R1cDataObj { uint8_t unk00[0xE8]; uint8_t desc[4]; } R1cDataObj;
void  sub_00053710(int heap);
int   sub_0004F680(void *desc);
void *sub_00053AB0(int size, int a, int tag);
void  sub_000512D0(void *desc, void *p);
void  sub_00053740(void);
extern void *r1c_data3DA0D0;                /* 0x003DA0D0 */
extern void *r1c_obj2836DC;                 /* 0x002836DC */

typedef struct R1cFlagVar { uint8_t unk00[4]; int32_t value; } R1cFlagVar;
R1cFlagVar *sub_0003F8B0(int ctx, void *type, int a);
extern uint8_t r1c_flagType2C4B94[];        /* 0x002C4B94 variable type descriptor */
extern char r1c_name3DE808[32];             /* 0x003DE808 */
extern const char r1c_fmtS25FF04[];         /* 0x0025FF04 "%s" */

extern int32_t r1c_q3DFECC;                 /* 0x003DFECC */
void sub_001999E0(int ch, int voice);
void sub_0019B800(int ch, int voice);
void sub_00047DA0(int vol, int voice);

void r1c_PadModeTick(void);
int  r1c_ObjPlayMotion(R1cMotObj *o, int id, int flags);
int  r1c_ListPlayMotion(void *o, R1cMotList *l, int id, int flags);
void r1c_ObjSlotsReset(R1cSlotObj *o);
int  r1c_ObjLoadData(R1cDataObj *o);
R1cFlagVar *r1c_FlagVarSet(int ctx, int value, const char *name);
void r1c_SndStartPending(int voice);

/* ------------------------------------------------------------ group 8 */
extern int32_t r1c_tex380C24[9];            /* 0x00380C24 texture handles */
extern uint32_t r1c_state37C4F8[0xD9E];     /* 0x0037C4F8 game state block */
extern int32_t r1c_g3813B4;                 /* 0x003813B4 */
void  sub_001B9FC0(int h);
void *sub_000529F0(void);
void  sub_0004F5D0(void *p);

extern int32_t  r1c_seqStep37C544;          /* 0x0037C544 */
extern uint32_t r1c_seqFlags37C540;         /* 0x0037C540 */
extern int32_t  r1c_seqStep37ED04;          /* 0x0037ED04 */
extern uint32_t r1c_seqFlags37ED00;         /* 0x0037ED00 */
void sub_00028630(void); void sub_00028740(void); void sub_00028890(void);
void sub_00028930(void); void sub_00028B10(void); void sub_00028CB0(void);
void sub_0002A070(void); void sub_0002A160(void); void sub_0002A240(void);
void sub_0002A2C0(void); void sub_0002A3A0(void); void sub_0002A460(void);

typedef struct R1cActorState { uint8_t unk00[8]; int32_t id; } R1cActorState;
typedef struct R1cMotTab { uint8_t unk00[4]; R1cMotNode *head; } R1cMotTab;
typedef struct R1cActor {
    uint8_t        unk00[0x30];
    R1cActorState *state;       /* +0x30 */
    uint8_t        unk34[0xF8];
    R1cMotTab     *table;       /* +0x12C */
    uint8_t        unk130[4];
    void          *effect;      /* +0x134 */
} R1cActor;
void sub_00033C20(void *effect);
void sub_00033D10(void *o, void *entry);

typedef struct R1cRBuf { uint8_t unk00[8]; void *data; } R1cRBuf;
typedef struct R1cScene { uint8_t unk00[0x1E8]; void *root; } R1cScene;
R1cRBuf *sub_0001F210(int a, int b);
void     sub_0001DA40(R1cRBuf *b);
R1cRBuf *sub_00022260(int a, int b, int c, int d);
void     sub_0001CFF0(void *root, R1cRBuf *b, int a);
extern R1cRBuf *r1c_bufA3DA0C8, *r1c_bufB3DA0CC;
extern void *r1c_bufAData3DA0C0, *r1c_bufBData3DA0B8;
extern R1cScene *r1c_scene42C8E4;           /* 0x0042C8E4 */

typedef struct R1cCamNode {
    uint8_t    unk00[0x0C];
    R1cCamSet *set;             /* +0x0C */
    R1cCamSet  setData;         /* +0x10 */
    uint8_t    unk18[8];
} R1cCamNode;
extern R1cCamNode r1c_camNodes3DD000[99];   /* 0x003DD000 */
extern uint8_t r1c_camList3DDC60[16];       /* 0x003DDC60 active camera list (count, first...) */
extern int32_t r1c_camFlag42CB04, r1c_camFlag42CB08, r1c_camFlag42CB0C;

typedef struct R1cSndRec { uint8_t unk00[8]; int32_t handle; uint8_t unk0C[0x14]; } R1cSndRec;
typedef struct R1cStage {
    uint8_t   unk00[0x2B4D84];
    R1cSndRec amb;              /* +0x2B4D84 */
    int32_t   ambTable;         /* +0x2B4DA4 */
} R1cStage;
extern R1cStage *r1c_stage3DFA5C;           /* 0x003DFA5C */
typedef struct R1cWorld {
    uint8_t   unk00[0x122A20];
    R1cSndRec snd[4];           /* +0x122A20 */
    int32_t   sndTable[4];      /* +0x122AA0 */
} R1cWorld;
extern R1cWorld *r1c_world3E3934;           /* 0x003E3934 */
void sub_00076060(int h);
int  sub_0003FA70(int table, int id);
void sub_0003FCB0(void *rec, int item, int a, int b, float c);

typedef struct R1cHeap { int32_t d00; char *start; char *end; int32_t id; } R1cHeap;
typedef struct R1cHeapReg { int32_t d00, d04, d08, d0C, d10, d14; } R1cHeapReg;
int  sub_001AA240(R1cHeapReg *r);

typedef struct R1cJobFull {
    int32_t state, thread, handle, d0C, d10, d14;
    void *func, *arg;
} R1cJobFull;
void sub_001AD440(int thread);
void sub_001AD6E0(void);
void sub_001AA460(int handle);
void sub_001AD4B0(int tid);
extern int32_t r1c_threads3E46A0[16];       /* 0x003E46A0 */
extern int32_t r1c_nThreads3E46DC;          /* 0x003E46DC */

typedef struct R1cIdEnt {
    uint8_t unk00[0x0C];
    struct R1cIdEnt *self;      /* +0x0C */
    int32_t id;                 /* +0x10 */
    uint8_t unk14[0x0C];
    uint8_t body[0x450];        /* +0x20 */
} R1cIdEnt;
typedef struct R1cIdNode {
    struct R1cIdNode *next;     /* +0x00 */
    uint8_t unk04[8];
    R1cIdEnt *ent;              /* +0x0C */
} R1cIdNode;
typedef struct R1cIdList { uint8_t unk00[4]; R1cIdNode *head; } R1cIdList;
void sub_0005CAF0(void *body);

typedef struct R1cEvObj {
    uint8_t unk00[4];
    int32_t busy;               /* +0x04 */
    uint8_t unk08[0x20];
    int32_t kind;               /* +0x28 */
    uint8_t unk2C[4];
    void   *child;              /* +0x30 */
} R1cEvObj;
int  sub_0004ECE0(int kind);
void sub_0005A990(void *o, void (*fn)(void), void *ctx);
void sub_0005D030(void);
extern uint8_t r1c_ctx2DD624[];             /* 0x002DD624 */

void r1c_GameStateReset(void);
void r1c_SeqARun(void);
void r1c_SeqBRun(void);
void r1c_ObjRefreshMotion(void *unused, R1cActor *o);
void r1c_RenderBufsCreate(void);
void r1c_CamInit(void);
void r1c_StageAmbient(int id);
int  r1c_HeapSetup(R1cHeap *buf, int size);
void r1c_JobReset(void);
void r1c_JobYield(void);
R1cIdEnt *r1c_IdListGet(R1cIdList *l, int id);
int  r1c_ObjEventEx(int ev, R1cEvObj *o, int mode);

#endif
