#ifndef R6F_H
#define R6F_H
#include "oogie.h"
#include "r6e.h"
/* Area r6f: remaining functions in 0x00060000..0x000D0000. All names inferred.
   Register mappings are in the comments and in config/function_states_r6f.csv.
   Callees are declared under their sub_ name so that cl never inlines a
   function recovered in this area into another one. */

/* ------------------------------------------------------------ task descriptors (0x8Bxxx) */
/* Task node (same record as R6fTask) with the word at +0x18 seen as 32 flag bits. */
/* Tree node header shared by the task records (see R6cTNode). */
typedef struct R6fDNode {
    uint8_t  unk00[8];
    struct R6fDNode *next;    /* +0x08 */
    struct R6fDNode *prev;    /* +0x0C */
    struct R6fDNode *parent;  /* +0x10 */
    struct R6fDNode *child;   /* +0x14 */
} R6fDNode;

typedef struct R6fTask {
    R6fDNode hdr;             /* +0x00 */
    union {
        uint32_t u;           /* +0x18 bit 0 owns its work block */
        uint8_t  b0;          /* +0x18 low flag byte */
        struct { uint16_t w; int8_t type; uint8_t b1B; } s;  /* type: +0x1A */
    } f18;
    R6eWork *work;            /* +0x1C */
    int8_t   state;           /* +0x20 */
    int8_t   heap;            /* +0x21 */
    uint8_t  unk22;
    uint8_t  refs;            /* +0x23 */
    union { int32_t i; uint32_t u; uint8_t b[4]; void *p; } u24; /* +0x24 */
    void    *p28;             /* +0x28 */
    uint8_t  unk2C[0x3C - 0x2C];
    void    *p3C;             /* +0x3C */
} R6fTask;

/* Record returned by the descriptor getters (a8b_descGetters, 0x24 bytes);
   same layout as R6eDescRec with the handler slots named. */
typedef struct R6fDesc {
    uint8_t  unk00[8];
    int32_t  size;                                    /* +0x08 work block size */
    int    (*init)(R6fTask *t, int arg);              /* +0x0C */
    void    *p10;                                     /* +0x10 */
    void    *p14;                                     /* +0x14 must be set to create */
    int    (*visit)(void *x, R6fTask **t, int arg);   /* +0x18 */
    int    (*compare)(R6fTask *a, R6fTask *b);        /* +0x1C */
    int    (*copy)(R6fTask *src, R6fTask *dst);       /* +0x20 */
} R6fDesc;

/* Work block viewed with the byte at +0x13 reachable. */
typedef struct R6fWork {
    uint8_t  unk00[4];
    int8_t   kind04;          /* +0x04 */
    int8_t   sub05;           /* +0x05 */
    uint8_t  unk06[2];
    void    *p08;             /* +0x08 refcounted object (an index while loading) */
    uint8_t  b0C[4];
    union { int32_t i; uint8_t b[4]; } u10;  /* +0x10 */
} R6fWork;

/* Search key built on the stack by 0x0008B290. */
typedef struct R6fKey {
    float    f00;             /* +0x00 time */
    int8_t   kind04;          /* +0x04 */
    int8_t   sub05;           /* +0x05 */
    uint8_t  unk06[2];
    void    *p08;             /* +0x08 object */
    uint32_t u0C;             /* +0x0C */
    int32_t  i10;             /* +0x10 (work blocks only) */
} R6fKey;
typedef struct R6fKeyMsg {
    uint8_t  unk00[0x1C];
    R6fKey  *key;             /* +0x1C */
} R6fKeyMsg;

/* Handler table of a task type (a8b_opsGetters, R6eOps with more slots named). */
typedef struct R6fOps {
    int32_t  size;                                         /* +0x00 record size */
    int    (*init)(R6fTask *t, int arg);                   /* +0x04 */
    void   (*destroy)(R6fTask *t);                         /* +0x08 */
    uint8_t  unk0C[0x14 - 0x0C];
    int    (*step)(R6fTask *t, int arg);                   /* +0x14 */
    int    (*event)(R6fTask *t, int arg);                  /* +0x18 */
    int    (*parse)(R6fTask *t, const uint8_t *p, int n);  /* +0x1C bytes used */
    int    (*copy)(R6fTask *dst, R6fTask *src);            /* +0x20 */
} R6fOps;
#define R6F_OPS(type) ((R6fOps *)a8b_opsGetters[type]())

/* List entry that refers to a task (0x8CC50). */
typedef struct R6fRef {
    R6fDNode hdr;             /* +0x00 */
    R6fTask *task;            /* +0x18 */
} R6fRef;

typedef uint8_t (*R6fWorkPred)(R6eWork *a, R6eWork *b);

extern int32_t r6f_g3ED524;            /* 0x003ED524 */
extern int32_t r6f_g428EFC;            /* 0x00428EFC */

R6fDesc *sub_0008AF80(int kind, int sub);
int   sub_0008B210(R6fTask *t, R6fKeyMsg *m, int n);
R6fTask *sub_0008B290(R6fTask *t, int kind, int sub);
int   sub_0008B010(R6fTask **out, R6fTask *src);
void  sub_0008B760(R6fTask *t);
R6fTask *sub_0008B780(R6fTask *a, R6fTask *b);
R6fTask *sub_0008B980(int kind, int sub);
R6fTask *sub_0008C350(R6fTask *n, R6fTask *ref, uint32_t mask);
void  a8b_RefDec(void *o);
int   sub_0007F430(void *parent, void *chain);
void *sub_0007F330(void *n);
void *sub_0007F390(void *parent, int index);
void *sub_0007F310(void *n);
uint8_t sub_0008C290(R6fTask *a, R6fTask *b);   /* a=ESI b=EDX */
int   sub_0008C4B0(R6fTask *t);
R6fTask *sub_0008C6E0(int type, void *work);
int   sub_0008C940(R6fTask **out, R6fTask *src);
R6fTask *sub_0008C900(R6fTask *a, R6fTask *b);
void  sub_0008BF60(int type);
void  sub_0008CC30(R6fRef *r);
void  sub_0008CB90(void *n);
void  sub_0008C2C0(R6fDNode *a, R6fDNode *b);
extern const char r6f_srcFile270024[];  /* 0x00270024 */

/* ------------------------------------------------------------ script blobs and task handlers (0x8Dxxx-0x8Fxxx) */
typedef struct R6fBlobHdr {
    uint8_t  head[0x1C];      /* +0x00 */
    int32_t  mode;            /* +0x1C */
} R6fBlobHdr;
typedef struct R6fBlob {
    uint32_t flags;           /* +0x00 bit 0 tasks loaded, bit 1 nodes loaded */
    uint8_t  head[0x1C];      /* +0x04 */
    int32_t  mode;            /* +0x20 copy mode for the task list */
    R6fTask *tasks;           /* +0x24 */
    R6fTask *nodes;           /* +0x28 */
} R6fBlob;
typedef struct R6fSlot48 { uint8_t unk00[0x24]; int32_t i24; uint8_t unk28[0x48 - 0x28]; } R6fSlot48;
typedef struct R6fBlockB0 { uint32_t w[0x2C]; } R6fBlockB0;
typedef struct R6fModelSet {
    uint8_t  unk00[4];
    uint32_t count;           /* +0x04 */
    uint8_t  unk08[4];
    void    *models;          /* +0x0C */
} R6fModelSet;

int   sub_0008C770(R6fTask **out, const uint8_t *data, int size);
int   sub_0008B9E0(R6fTask **out, const uint8_t *data, int size, void *parent, int mode);
R6eProc *sub_0008CD60(void);
void *sub_00089570(void *ref, int type);
uint32_t sub_0008FFC0(R6eHolder *h);
void *sub_0008FF80(void *h);
void *sub_0008FF90(R6eHolder *h);
void *sub_00037780(void);
void  sub_000375A0(void);
void  sub_000376D0(void *slot);
void *sub_000390A0(void);
void  sub_0007ED70(void *a, void *b);
void  sub_0007EAD0(void *p);
void  sub_0001EBF0(void *m, int v);

typedef struct R6fFxArg { uint8_t unk00[4]; int32_t i04; } R6fFxArg;
extern void *r6f_stageTbl2700C0[];     /* 0x002700C0 indexed by 0x000529F0() */
extern const char r6f_fxName2702F8[];  /* 0x002702F8 */
void  sub_0008BCF0(int slot, int n);
int   sub_0008BD10(void);
uint16_t sub_001BA0D0(void);
int   sub_000529F0(void);
void *sub_00089C10(int a, void *b);
int   sub_00048A00(int id, int b);
void *sub_00053BC0(const char *name, int size);
void  sub_00053BE0(void);
void  sub_000366F0(void *list, int v);
int   sub_0008B7C0(void *x, R6fTask **list, int arg);
int   sub_0008CA80(R6fTask **list, R6fTask **src, R6fTask **removed);
int   sub_0008C4D0(R6fTask **list, R6fTask **removed);
int   sub_0008B680(R6fTask *list, R6fTask *ctx, R6fTask *refs);

/* model record (0x8FAF0, 0x8FB80) */
typedef struct R6fModelRec {
    uint8_t  unk00[8];
    void    *models;          /* +0x08 */
    void    *h0C;             /* +0x0C */
} R6fModelRec;
extern const char r6f_fmt2707A0[];     /* 0x002707A0 */
extern void *r6f_ctx42C8E4;            /* 0x0042C8E4 scene context */
void  sub_0007E0A0(char *buf, const char *fmt, ...);
uint8_t sub_0008F960(void *a, void *b);
void *sub_0008F950(void **it);
void  sub_0008F920(void *list);
void  sub_00020170(void *h);
void  sub_0001D030(void *a, void *b);
void *sub_0007AA50(void *ctx);
void  a8c_Release102FA0(void *p);

/* key work block of kind 13/2 (0x8D500) */
typedef struct R6fKeyWork {
    int32_t  i00;             /* +0x00 */
    uint8_t  unk04[4];
    void    *p08;             /* +0x08 animation object */
    uint8_t  unk0C[4];
    int8_t   mode;            /* +0x10 */
    uint8_t  unk11[3];
    int32_t  i14, i18, i1C, i20;  /* +0x14..+0x20 key values per channel */
    int32_t  i24;             /* +0x24 nonzero: set flag 1 */
} R6fKeyWork;
typedef struct R6fAnimObj {
    uint8_t  unk00[0x24];
    uint32_t flags24;         /* +0x24 */
    int32_t  i28, i2C;        /* +0x28, +0x2C */
    uint8_t  ch30[0x18];      /* +0x30 */
    uint8_t  ch48[0x18];      /* +0x48 */
    uint8_t  ch60[0x18];      /* +0x60 */
    uint8_t  ch78[0x18];      /* +0x78 */
} R6fAnimObj;
/* material task: two words after the common task fields */
typedef struct R6fTaskMat { uint8_t unk00[0x2C]; int32_t i2C; int32_t i30; } R6fTaskMat;

void  sub_0007F610(void *ch, int mode, int a, int b);
void *sub_000893A0(void *ref);
void *sub_0007EB80(void *r, int a, int b);
void  sub_0008CCF0(void **root, int v);
void  sub_0008CBE0(void **root, void *n);
void  sub_00053710(int a);
void  sub_00053740(void);
void  sub_0007E910(void *m, void *r, int a, int b);
void  sub_000535F0(int a, int b, int c);
int   sub_00089610(void *ref);
int   sub_0008E340(int a, int b, void *ch, int n);   /* ch=EDI n=EBX */
void  sub_0008FCB0(R6fModelRec *rec, int a, int b);
void  sub_0008F900(void *list, void *rec);

/* ------------------------------------------------------------ sound and timing (0x88Fxx-0x8Axxx) */
typedef struct R6fPending {
    struct R6fPending *next;  /* +0x00 */
    uint8_t  unk04[0x10 - 4];
    float    time;            /* +0x10 */
    int32_t  index;           /* +0x14 into the 16-byte table at 0x003ED518 */
} R6fPending;
extern R6fPending *r6f_pendingList3ED27C;  /* 0x003ED27C */
extern uint8_t    *r6f_posTable3ED518;     /* 0x003ED518 */
typedef struct R6fBox {
    uint32_t flags;           /* +0x00 bit 2: max computed */
    uint8_t  unk04[4];
    float    max;             /* +0x08 */
    uint8_t  unk0C[0x1C - 0x0C];
    R6fTask *list;            /* +0x1C */
} R6fBox;
typedef struct R6fWorkI {
    uint8_t  unk00[0x10];
    int32_t  i10;             /* +0x10 */
    union { int32_t i; float f; } u14;  /* +0x14 */
    int32_t  i18, i1C, i20;   /* +0x18..+0x20 */
} R6fWorkI;
void  sub_0003D8C0(void *p);
void *sub_0008B0C0(R6fTask *n);
int   sub_0008B0D0(R6fTask *n);
void  sub_00089460(R6fBox *o);         /* o=EBX */
R6fTask *sub_0008AFA0(R6fTask *t);
R6fTask *sub_0008E5E0(int a, int b, int c, int d);
void  sub_0007E5C0(void *a, int b, int c, void *d);

/* eight-channel key work block and its animation object (0x89EF0) */
typedef struct R6fKeyWork8 {
    int32_t  i00;             /* +0x00 */
    int8_t   kind04;          /* +0x04 */
    int8_t   sub05;           /* +0x05 */
    uint8_t  unk06[2];
    void    *p08;             /* +0x08 animation object */
    uint8_t  unk0C[4];
    int8_t   mode;            /* +0x10 */
    uint8_t  unk11[3];
    int32_t  k[8];            /* +0x14 key value per channel */
    int32_t  loop;            /* +0x34 */
} R6fKeyWork8;
typedef struct R6fAnimObj8 {
    uint8_t  unk00[0x24];
    uint32_t flags24;         /* +0x24 */
    uint8_t  unk28[4];
    int32_t  i2C, i30;        /* +0x2C, +0x30 */
    uint8_t  ch[8][0x18];     /* +0x34 */
} R6fAnimObj8;
int   sub_0008B1A0(R6fTask *a, R6fTask *b);

/* nine-channel key work block and the target node it drives (0x8A250) */
typedef struct R6fKeyWork9 {
    int32_t  i00;             /* +0x00 */
    uint8_t  unk04[0x10 - 4];
    int32_t  i10, i14;        /* +0x10, +0x14 */
    uint8_t  unk18[4];
    int8_t   mode;            /* +0x1C */
    uint8_t  unk1D[3];
    int32_t  k[9];            /* +0x20 key value per channel */
} R6fKeyWork9;
typedef struct R6fMatNode {
    uint8_t  unk00[0x28];
    void    *p28;             /* +0x28 loaded material */
    uint8_t  unk2C[0x34 - 0x2C];
    int32_t  i34, i38, i3C, i40;  /* +0x34..+0x40 */
    uint8_t  unk44[4];
    uint8_t  ch[9][0x18];     /* +0x48 */
} R6fMatNode;
typedef struct R6fFxRec { uint8_t unk000[0x14C]; int32_t i14C; } R6fFxRec;
R6fFxRec *sub_0008E1B0(R6fMatNode *m);
void  sub_0001E9B0(void *ctx, R6fFxRec *e, int h, int a, int b);

/* ------------------------------------------------------------ render passes (0x849D0) */
typedef struct R6fCallback {
    void   (*fn)(void);       /* +0x00 */
    struct R6fCallback *next; /* +0x04 */
} R6fCallback;
typedef struct R6fCmd { int32_t a, b, c, d; } R6fCmd;
typedef struct R6fPass {
    uint32_t flags;           /* +0x000 bit 0 no state block, bit 1 no 0x001B24E0 */
    uint32_t ncmd;            /* +0x004 */
    void  *(*pre)(void *dl);  /* +0x008 */
    void  *(*post)(void *dl); /* +0x00C */
    R6fCallback *onSet;       /* +0x010 */
    R6fCallback *onDone;      /* +0x014 */
    uint8_t  unk018[0x24 - 0x18];
    uint8_t  state[0x2F0 - 0x24];  /* +0x024 */
    R6fCmd   cmd[8];          /* +0x2F0 */
} R6fPass;
typedef struct R6fPassSet {
    uint32_t count;           /* +0x00 */
    R6fPass *passes;          /* +0x04 */
} R6fPassSet;
extern uint8_t r6f_renderFlags412F30;  /* 0x00412F30 */
void *sub_00012300(void *dl, int a, int b, int c, int d);
void  sub_001B1FC0(void);
void  sub_001B2490(void *state);
void  sub_001B1FE0(void);
void  sub_001B24E0(void *dl);

/* ------------------------------------------------------------ grid walkers (0x856F0, 0x85820) */
void  sub_000853B0(int *x, int *y, void *g);   /* g=EDI */
int   sub_00085430(int *x, int *y, void *g);   /* g=EDI; -1 when done */
void  sub_000ED4C0(int c);
int   sub_000ED520(int c, int k);
void  sub_000ED590(int c, int k);
void  sub_000ED5D0(int c);
int   sub_000EDCB0(int x, int y, int *k);
void  sub_000ED600(int c);
void  sub_000ED560(int c);
void  sub_000ED4F0(int c);
void  sub_00033BF0(int c, int v);
int   sub_000EE240(void);
void  r6f_StubAD090(int a, int b);     /* 0x000AD090, returns at once on this build */
typedef struct R6fCell { int32_t x, y; } R6fCell;
typedef struct R6fCellList {
    uint8_t  unk00[4];
    int32_t  count;           /* +0x04 */
    R6fCell  cells[1];        /* +0x08 count entries */
} R6fCellList;

/* ------------------------------------------------------------ sound objects and tables (0x77xxx-0x7Axxx) */
typedef struct R6fVecEnt { int32_t id; float v[4]; } R6fVecEnt;
extern R6fVecEnt r6c_vecTable[19];     /* 0x002DFFB8, ends with id -1 */
typedef struct R6fSndSet {
    uint8_t  flags;           /* +0x00 bit 0: use f1BC/f1C0 */
    uint8_t  pad[3];
    float    f1BC, f1C0, f1C4, f1C8, f1CC;
} R6fSndSet;
typedef struct R6fSndObj {
    uint8_t  unk000[0x44];
    int32_t  voice;           /* +0x044 */
    uint8_t  unk048[0x1B8 - 0x48];
    R6fSndSet snd;            /* +0x1B8 */
} R6fSndObj;
void  sub_00084910(int voice, float a, float b, float c, float d, float e, float range);

/* prompt state (0x79370) */
extern int32_t a60_v3E83E0, a60_v3E7A54, a60_v3E7A50, a60_v3E83E4;
extern int32_t r6d_g42CA24;
int   sub_0004ECC0(int a);
void  sub_0019BEB0(int a);
void  sub_0019BE90(int a);
int   sub_001A8A40(void);
int   sub_001A8A90(void);

/* key search helpers (0x8B210-0x8E6F0) */
typedef struct R6fIdObj { uint8_t unk00[0x1C]; int32_t id; } R6fIdObj;
typedef struct R6fTimedObj { uint8_t unk00[0x30]; float start; } R6fTimedObj;
typedef struct R6fRangeArg { uint8_t unk00[0x0C]; float f0C; float f10; } R6fRangeArg;
typedef struct R6fMat { uint8_t unk00[0x1C]; int32_t *p1C; } R6fMat;
typedef struct R6fRefObj { uint8_t unk00[0x10]; int32_t i10; } R6fRefObj;
void  sub_0008F0E0(void *o, int a, float b, float c);
void  sub_0008F140(void *o);
void *sub_000893B0(void *x);
void  sub_0007ED10(void *a, void *b);
void  sub_0007E9B0(void *m, int v);
void  sub_0008E6A0(R6eTask *t);
void  sub_0008DE70(R6eTask *t, int a, int b);
int   sub_00089450(void *ref);
float sub_00090480(void *ramp, int x);

/* scene clock (0x89AB0, 0x89DD0) */
typedef struct R6fScene {
    uint32_t flags;           /* +0x00 bit 8 running, bit 9 paused */
    uint8_t  unk04[8];
    float    end;             /* +0x0C */
    float    now;             /* +0x10 */
    float    rate;            /* +0x14 */
    uint8_t  unk18[4];
    R6fTask *tasks;           /* +0x1C sorted by time */
    R6fTask *children;        /* +0x20 */
    R6fRef  *refs;            /* +0x24 */
    uint8_t  unk28[0x4C - 0x28];
    uint32_t *mask;           /* +0x4C channel enable bits */
} R6fScene;
typedef struct R6fPart { uint8_t unk00[8]; float blend; } R6fPart;
typedef struct R6fAnimHost {
    uint8_t  unk000[0x12C];
    int32_t  i12C;            /* +0x12C */
    uint8_t  unk130[4];
    R6fPart *part;            /* +0x134 */
} R6fAnimHost;
typedef struct R6fRefObjF { uint8_t unk00[0x10]; float f10; } R6fRefObjF;
uint8_t sub_0008AFC0(R6fTask *n);
void  sub_0008AFD0(R6fTask *n, R6fScene *s);
void  sub_00089B50(R6fScene *s, float t);
void  sub_00089AB0(R6fScene *s);
int   sub_0008C420(R6fTask *n, R6fScene *s);
int   sub_0008CC50(R6fRef **list, void *arg);
void *sub_00033DC0(int a, int b);
void  sub_00033D10(void *a, void *e);
void  sub_00033C20(void *p);

typedef struct R6fSceneB {
    uint8_t  unk00[0x10];
    float    now;             /* +0x10 */
    uint8_t  unk14[4];
    int32_t  mode;            /* +0x18 */
    uint8_t  unk1C[4];
    int32_t  heap;            /* +0x20 */
} R6fSceneB;
int   sub_0008C240(int heap, void *s, int ev);
int   sub_0008BFD0(int heap, void *s);

#endif
