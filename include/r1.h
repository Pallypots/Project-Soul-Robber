#ifndef R1_H
#define R1_H
#include "oogie.h"

/* Area r1: functions that took register arguments in the original (see notes
   in config/function_states_r1.csv for the exact register mapping). */

/* 0xB0-byte pool entry; first word holds flags. */
typedef struct R1Entry {
    uint32_t flags;             /* +0x00 */
    uint8_t  unk04[0xB0 - 4];
} R1Entry;

typedef struct R1EntryList {
    R1Entry  *items;            /* +0x00 */
    uint32_t  count;            /* +0x04 */
} R1EntryList;

typedef struct R1Sel {
    int32_t unk00;
    int32_t kind;               /* +0x04 */
} R1Sel;

typedef struct R1SelOwner {
    uint8_t  unk000[0x100];
    uint32_t setA[20];          /* +0x100 */
    uint32_t setB[20];          /* +0x150 */
    uint32_t cur[20];           /* +0x1A0 */
    uint8_t  unk1F0[0x12BC - 0x1F0];
    int32_t  enabled;           /* +0x12BC */
    R1Sel   *sel;               /* +0x12C0 */
} R1SelOwner;

typedef float R1Vec4[4];

/* Mesh-part record shared by 0x0001D3B0..0x0001E850. */
typedef struct R1Part {
    uint8_t  unk00[0x88];
    void    *link;              /* +0x88 */
    int32_t  kind;              /* +0x8C */
    uint32_t flags;             /* +0x90 */
    uint8_t  unk94[0xC0 - 0x94];
    int32_t  count;             /* +0xC0 */
    uint8_t *items;             /* +0xC4 */
} R1Part;

typedef struct R1PartPair {
    int32_t  id;                /* +0x00 */
    uint8_t  unk04[8];
    uint32_t flags;             /* +0x0C */
    uint8_t  unk10[0x10];
    R1Part  *a;                 /* +0x20 */
    int32_t  unk24;
    R1Part  *b;                 /* +0x28 */
    uint8_t  unk2C[0x10];
    struct R1PartPair *next;    /* +0x3C */
} R1PartPair;
void r1_PartsShow(R1PartPair *o);
void r1_PartsHide(R1PartPair *o);
void *sub_00053AB0(int size, int a, int tag);

typedef struct R1KindFlags {
    int32_t  kind;              /* +0x00 */
    uint32_t flags;             /* +0x04 */
} R1KindFlags;

/* 0x150-byte state block set up by 0x0001CEB0. */
typedef struct R1State {
    int32_t  id;                /* +0x00 */
    int32_t  i04, i08;          /* +0x04 */
    int32_t  w0C[13];           /* +0x0C..+0x3C */
    int32_t  w40;               /* +0x40 */
    int32_t  i44, i48, i4C;     /* +0x44 */
    float    f50[4];            /* +0x50 */
    float    f60[3];            /* +0x60 */
    float    f6C;               /* +0x6C */
    float    f70[3];            /* +0x70 */
    float    f7C;               /* +0x7C */
    float    f80[3];            /* +0x80 */
    float    f8C;               /* +0x8C */
    float    f90[4];            /* +0x90 */
    uint8_t  unkA0[0x12C - 0xA0];
    int32_t  w12C[8];           /* +0x12C */
    int32_t  mode;              /* +0x14C */
} R1State;

typedef struct R1Opaque R1Opaque;
extern R1Opaque r1_blk42C7E0, r1_blk42C820, r1_blk42C860, r1_blk42C880, r1_blk42C8A0,
                r1_blk42C8C0, r1_blk42C920, r1_blk42C940, r1_blk42C9A0, r1_blk42C9C0,
                r1_blk42C9E0;
void sub_0001D330(void *p);
void sub_0001D370(void *p);
void sub_0001C8A0(R1State *s);
typedef struct R1Timer {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04..+0x20 queued values */
    int32_t  state;             /* +0x24 */
    int32_t  level;             /* +0x28 */
    int32_t  unk2C;
    float    t;                 /* +0x30 */
} R1Timer;

typedef struct R1Hud {
    uint8_t  unk000[0x968];
    uint8_t  slot968[8];        /* +0x968 */
    int32_t  h970;              /* +0x970 */
    uint8_t  unk974[0x988 - 0x974];
    void    *tbl988;            /* +0x988 */
} R1Hud;

typedef struct R1Chan {
    uint8_t  unk00[0x8C];
    int32_t  busy;              /* +0x8C */
    uint8_t  unk90[0xB0 - 0x90];
} R1Chan;

typedef struct R1Bank {
    uint8_t  unk00000[0x55140];
    uint8_t  sub55140[0x5844C - 0x55140];   /* +0x55140 */
    uint8_t  sub5844C[0x10];                /* +0x5844C */
    R1Chan   chans[2];                      /* +0x5845C */
} R1Bank;

extern int32_t  r1_curHudId;
extern R1Hud   *r1_hud;
void sub_000720A0(float *t, int mode);
void sub_00076060(int h);
void *sub_0003FA70(void *tbl, int id);
void sub_0003FCB0(void *slot, void *item, int a, int b, float c);
void sub_00036A90(void *p, int a, int b);
void sub_0003D860(void *p);
void sub_001B25B0(void *p);
/* Linked material node (0x0003E230..0x0003E370). */
typedef struct R1Mat {
    uint8_t  unk00[0x14];
    uint32_t flags;             /* +0x14 */
} R1Mat;
typedef struct R1MatNode {
    struct R1MatNode *next;     /* +0x00 */
    uint8_t  unk04[0x0C];
    R1Mat   *mat;               /* +0x10 */
    uint8_t  unk14[0x40 - 0x14];
    char     name[1];           /* +0x40 */
} R1MatNode;
typedef struct R1FlagEnt {
    char     name[12];          /* +0x00 */
    uint32_t flags;             /* +0x0C */
} R1FlagEnt;
typedef struct R1FlagTbl {
    int32_t  unk00, unk04;
    int32_t  count;             /* +0x08 */
    int32_t  unk0C;
    int32_t  off[1];            /* +0x10 offsets from the table start */
} R1FlagTbl;
typedef struct R1MatUser {
    uint8_t    unk000[0x1FC];
    R1MatNode *list;            /* +0x1FC */
} R1MatUser;
typedef struct R1MatSel {
    uint8_t  unk000[0x278];
    int32_t  set;               /* +0x278 */
    int32_t  sub;               /* +0x27C */
} R1MatSel;
extern R1FlagTbl *r1_flagTbls[];        /* 0x003DE7EC */
extern R1FlagTbl *r1_flagTbl3DE7FC;
extern int32_t    r1_lastSet, r1_lastSub, r1_g3DE800, r1_g3DE7E4;
void r1_MatClearFlag(R1MatNode *n);
void r1_MatApplyFlags(R1MatNode *list, int count, R1FlagEnt *e);

typedef struct R1Fader {
    uint8_t  unk00[0x1C];
    float    level;             /* +0x1C */
    int32_t  active;            /* +0x20 */
    int32_t  handle;            /* +0x24 */
} R1Fader;
int sub_00076180(R1Fader *f);
typedef struct R1Stream { uint8_t unk00[0x30]; int32_t handle; /* +0x30 */ } R1Stream;

/* Memory heap blocks (0x00047080..0x00047160). */
typedef struct R1Blk {
    int32_t  w00;               /* +0x00 */
    void    *owner;             /* +0x04 */
    int32_t  w08, w0C;          /* +0x08 */
    uint8_t  link10[0x0C];      /* +0x10 */
    struct R1Blk *self;         /* +0x1C */
    uint32_t avail;             /* +0x20 */
    int32_t  w24;               /* +0x24 */
    uint8_t  unk28[8];
    int32_t  w30;               /* +0x30 */
} R1Blk;
typedef struct R1BlkNode {
    struct R1BlkNode *next;     /* +0x00 */
    uint8_t  unk04[8];
    R1Blk   *blk;               /* +0x0C */
} R1BlkNode;
typedef struct R1Heap {
    int32_t    unk00;
    R1Blk     *first;           /* +0x04 */
    R1Blk     *cur;             /* +0x08 */
    uint8_t    list0C[4];       /* +0x0C */
    R1BlkNode *nodes;           /* +0x10 */
    uint8_t    unk14[0x2C - 0x14];
    int32_t    size;            /* +0x2C */
} R1Heap;

typedef struct R1KeyRec {
    int32_t a, b;               /* +0x00 key pair; a == -1 ends the table */
    union { int16_t w[4]; struct { int32_t lo, hi; } d; } u;   /* +0x08 */
} R1KeyRec;
extern R1KeyRec r1_keyTbl[];    /* 0x002C6B20 */

int  sub_001AA520(int h);
void sub_0003D880(void *list, void *node);
int  sub_001A8500(void *p, int a, int *out);
typedef struct R1File { int32_t h; int32_t pos; } R1File;

typedef struct R1Ent20 {
    uint32_t flags;             /* +0x00 */
    int32_t  a;                 /* +0x04 */
    int32_t  b;                 /* +0x08 */
    int32_t  used;              /* +0x0C */
    int32_t  life;              /* +0x10 */
} R1Ent20;
R1Ent20 *r1_EntFind(R1Ent20 *prev, int a, int b);
R1Ent20 *sub_000531C0(int a, int b);
R1Ent20 *sub_00053400(int slot, int a, int b);
void sub_00052E10(R1Ent20 *e);
extern R1Ent20 r1_ents3E2550[]; /* 0x003E2550, 17 records of 0x14 bytes */

typedef struct R1Res { int32_t state; int32_t a; int32_t b; int32_t unk0C; void *h; } R1Res;
typedef struct R1ResNode { uint8_t link[0x10]; R1Res r; } R1ResNode;
extern uint8_t r1_resFree3E3F54[1];

typedef struct R1Ctx { uint8_t unk000[0x184]; float pos[4]; /* +0x184 */ } R1Ctx;
typedef struct R1Model { uint8_t unk00[0x60]; float pos[4]; /* +0x60 */ } R1Model;
extern R1Ctx   *r1_ctx42C8E4;
extern R1Model *r1_model420E98;

void sub_001A8490(int h, int pos, int whence);
void sub_00102FA0(int a);
void sub_001A8410(int h, void *buf, int n);
void sub_00052EC0(int *outA, int a, int *outB, int b);
void sub_00053880(void *h);
void sub_0003D8C0(void *node);
void sub_000F5D40(float *d, const float *s);
void sub_001AD9F0(float *d, const float *a, const float *b);
void sub_001AD7E0(float *d, const float *s);
float sub_001AD9D0(const float *a, const float *b);
/* 0x4C-byte hold-detector record (table at 0x0042CA2C). */
typedef struct R1Hold {
    uint8_t unk00[0x0C];
    int32_t src;                /* +0x0C */
    int32_t out;                /* +0x10 */
    int32_t cnt;                /* +0x14 */
    int32_t state;              /* +0x18 */
    uint8_t unk1C[4];
    int32_t src2;               /* +0x20 */
    int32_t out2;               /* +0x24 */
    int32_t cnt2;               /* +0x28 */
    int32_t state2;             /* +0x2C */
    uint8_t unk30[0x1C];
} R1Hold;
extern R1Hold r1_holds[];       /* 0x0042CA2C */

void sub_001AB850(void);
typedef struct R1Target {
    float    pos[4];            /* +0x00 */
    uint8_t  unk10[0x14];
    int32_t  mode;              /* +0x24 */
    float    scale;             /* +0x28 */
} R1Target;
typedef struct R1TgtHold { uint8_t unk00[0x10]; R1Target *t; } R1TgtHold;
typedef struct R1TgtLink { uint8_t unk00[0x0C]; R1TgtHold *h; } R1TgtLink;
typedef struct R1TgtRef  { int32_t unk00; R1TgtLink *l; } R1TgtRef;
typedef struct R1TgtOut  { uint8_t unk00[4]; R1TgtRef *ref; uint8_t unk08[0x1C]; float dot; /* +0x24 */ } R1TgtOut;
typedef struct R1TgtArg  { uint8_t unk00[0x0C]; R1TgtOut *o; } R1TgtArg;
extern int32_t r1_modeOverride; /* 0x002DD4D8, -1 = use the target's own mode */
void r1_StateReset(R1State *s, int32_t id);
float r1_DirDot(int mode, const float *p, float scale);

int  r1_KeyWord(int a, int b, int k);
int  r1_KeyDword(int a, int b);
int  sub_00047A80(int v);
void sub_00199EB0(int v);
void sub_0019B5F0(int v);
void sub_0019B5C0(int v);
int  sub_00199F70(int v);
int  sub_0019B620(int v);
int  sub_00199CA0(int v);
typedef struct R1FxSlot { R1Timer t; uint8_t unk34[0x2A4 - 0x34]; } R1FxSlot;
extern R1FxSlot r1_fx[2];       /* 0x0037F550 */
void sub_0002B380(R1Timer *t);
void sub_0002B450(R1Timer *t);
void r1_TimerStep(R1Timer *t);
void r1_BankInit(R1Bank *b);
extern R1Bank  *r1_bank;        /* 0x00283698 */
extern R1Bank   r1_bank381AC0;
extern int32_t  r1_g3DA080, r1_g3DA084;
void sub_001B2020(int a, void *chan);
void r1_MatSelect(R1MatSel *s, R1MatUser *u);
void r1_MatDefault(R1MatUser *u);
/* Queue with a countdown: 8 queued values, state, running time, reload time. */
typedef struct R1QTimer {
    int32_t q[8];               /* +0x00 */
    int32_t state;              /* +0x20 */
    float   t;                  /* +0x24 */
    float   reload;             /* +0x28 -1 = wait forever */
} R1QTimer;
extern R1QTimer r1_qt37DAA4, r1_qt37DCFC, r1_qt37F484;
void r1_QueuePop8(int32_t *q);
void r1_ResRelease(R1Res *r);
R1Res *sub_00057F80(int id);
int  sub_001AD560(void);
int  sub_001AD440(int h);
int  sub_001AA310(int h);
extern int32_t r1_g3E3F90;

uint32_t *sub_00038AD0(uint32_t *p, void *src);
extern uint8_t r1_pk3DA320[1];
extern int32_t  r1_i37C050;
extern float    r1_f37C054, r1_f37C058;
extern float    r1_frameUnits;
extern R1Sel    r1_sel37BEF8;
extern uint8_t  r1_obj37BF58[1];

int sub_000E3370(void);
int sub_00087AF0(void);
int sub_00088170(void);
int sub_000CB9F0(void *p);
R1Sel *sub_000CB9B0(void);
R1Sel *r1_PickSel(R1SelOwner *o);

#endif
