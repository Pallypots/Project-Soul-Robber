#ifndef R1G_H
#define R1G_H
#include "oogie.h"
#include <string.h>

/* Area r1g: larger game functions 0x00012000..0x00060000 (seventh pass).
   Names inferred. Register-argument mappings are in
   config/function_states_r1g.csv. */

/* float -> int truncation as the original inlines it (cvttss2si) */
#if defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
#define R1G_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R1G_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ GS packets */
/* One GS register entry of a render packet template (16 bytes), as area r1d. */
typedef struct R1gGsEnt {
    uint16_t u00;
    uint16_t id;                /* +0x02 register id */
    uint32_t u04;
    uint32_t lo;                /* +0x08 */
    uint32_t hi;                /* +0x0C */
} R1gGsEnt;

/* texture record returned by 0x001B9650 (only the register values used) */
typedef struct R1gTex {
    uint8_t  unk00[0x28];
    uint32_t reg[10];           /* +0x28 five 64-bit register values */
} R1gTex;
R1gTex *sub_001B9650(int handle);
void sub_001A69C0(uint32_t lo, uint32_t hi);

/* sprite packet template (built by 0x00012010) */
typedef struct R1gSprTpl {
    R1gGsEnt ent[7];            /* +0x00 */
    uint8_t  u70;
    uint8_t  r, g, b;           /* +0x71 */
    uint32_t u74;
    uint32_t texLo, texHi;      /* +0x78 */
    uint32_t col80;             /* +0x80 */
    uint16_t w84[8];            /* +0x84 */
    uint8_t  a;                 /* +0x94 */
} R1gSprTpl;

/* quad packet template (0x00012160) */
typedef struct R1gQuadVtx {
    uint8_t  c[4];              /* +0x00 */
    int16_t  w[4];              /* +0x04 */
} R1gQuadVtx;
typedef struct R1gQuadTpl {
    R1gGsEnt ent[7];            /* +0x00 */
    uint8_t  u70[8];
    uint32_t texLo, texHi;      /* +0x78 */
    uint32_t col[4];            /* +0x80 */
    R1gQuadVtx v[4];            /* +0x90 */
} R1gQuadTpl;

extern uint32_t r1g_gifTag2803C0[3];            /* 0x002803C0 */

/* immediate-mode primitives sent through the current packet buffer */
uint64_t *sub_000134E0(void);                   /* textured sprite packet head */
uint64_t *sub_00013990(void);                   /* textured gouraud quad packet head */
uint64_t *sub_00013640(void);                   /* gouraud triangle packet head */
void      r1b_PktSubmit(void);                  /* 0x00013AA0 */

/* textured sprite with four corners (0x00013CA0, regarg ESI) */
typedef struct R1gTexSpr {
    uint8_t  u00;
    uint8_t  r, g, b;           /* +0x01 */
    int32_t  next;              /* +0x04 returned */
    uint32_t texLo, texHi;      /* +0x08 */
    uint32_t z[4];              /* +0x10 */
    struct { uint16_t u, v, x, y; } c[4];   /* +0x20 */
} R1gTexSpr;

/* textured quad with per-vertex colour (0x00013E30, regarg ESI) */
typedef struct R1gTexQuadV {
    uint8_t  r, g, b, a;        /* +0x00 */
    uint16_t u, v;              /* +0x04 */
    uint16_t x, y;              /* +0x08 */
} R1gTexQuadV;
typedef struct R1gTexQuad {
    uint32_t u00;
    int32_t  next;              /* +0x04 returned */
    uint32_t texLo, texHi;      /* +0x08 */
    uint32_t z[4];              /* +0x10 */
    R1gTexQuadV v[4];           /* +0x20 */
} R1gTexQuad;

/* gouraud triangle (0x00014380, regarg ESI) */
typedef struct R1gTri {
    uint8_t  u00;
    uint8_t  c[3][4];           /* +0x01 r,g,b,a per vertex */
    uint8_t  u0D[3];
    int32_t  next;              /* +0x10 returned */
    uint32_t z[3];              /* +0x14 */
    uint16_t xy[3][2];          /* +0x20 */
} R1gTri;

/* full-screen clear (0x00014940) */
typedef struct R1gPkt {
    uint32_t *cur;              /* +0x00 */
    uint32_t tag;               /* +0x04 */
    uint8_t  unk08[8];
} R1gPkt;
extern int32_t r1b_dev37B4A4;                   /* 0x0037B4A4 */
extern uint8_t r1g_buf37B2A0[];                 /* 0x0037B2A0 */
int32_t  sub_001A1FD0(int n);
void     r1b_PktOp(void *pkt, ...);             /* 0x00102FA0 */
uint32_t sub_000AD090();                        /* returns 0 on this build; called with 0, 1 or 2 arguments */
uint32_t sub_001BB240(int a, int b, int c);
void     sub_001A2020(int dev, uint32_t tag, uint32_t n);


/* flat diamond: a centre and four points half a width/height away
   (0x000144F0, regarg ESI) */
typedef struct R1gDiamond {
    uint8_t  u00;
    uint8_t  c0[4];             /* +0x01 centre r,g,b,a */
    uint8_t  c1[3];             /* +0x05 edge r,g,b */
    int32_t  next;              /* +0x08 returned */
    int32_t  z;                 /* +0x0C */
    uint16_t x, y;              /* +0x10 */
    uint16_t w, h;              /* +0x14 */
} R1gDiamond;
uint64_t *sub_000136F0(void);                   /* triangle fan packet head */


/* gradient line strip through a ring of points (0x000146D0) */
typedef struct R1gPt {
    uint32_t x, y, z;           /* +0x00 */
    uint32_t u0C;
} R1gPt;
typedef struct R1gStrip {
    uint32_t u00;
    uint8_t  c0[4];             /* +0x04 start colour r,g,b,a */
    uint8_t  c1[4];             /* +0x08 end colour r,g,b,a */
    int32_t  next;              /* +0x0C returned */
    uint16_t n;                 /* +0x10 ring size */
    uint16_t m;                 /* +0x12 point count / start */
    R1gPt   *pts;               /* +0x14 */
} R1gStrip;
void      sub_000137A0(void);                   /* line-strip mode packet */
uint64_t *sub_00013850(void);                   /* one line-strip vertex packet head */


/* ------------------------------------------------------------ button-sequence (cheat code) matcher */
typedef struct R1gKeyEnt {
    char     key;               /* +0 button letter (u d r l a b c U D R L A B C ?) */
    uint8_t  u01[3];
    int32_t  life;              /* +4 frames until it expires */
} R1gKeyEnt;
typedef struct R1gCode {
    const char *seq;            /* +0 button letters, 0 ends the table */
    int32_t     id;             /* +4 */
} R1gCode;
typedef struct R1gKeyBuf {
    R1gKeyEnt ent[32];          /* +0x000 ring */
    uint8_t   u100[8];
    int32_t   head;             /* +0x108 oldest */
    int32_t   tail;             /* +0x10C next free */
    R1gCode  *codes;            /* +0x110 */
    int32_t   matched;          /* +0x114 */
} R1gKeyBuf;
uint32_t sub_0004ECE0(int pad);                 /* newly pressed buttons */


/* ------------------------------------------------------------ HUD stage queues */
/* stage G (0x0037E090, as area r1f): counter display */
typedef struct R1gStageG {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 queued requests */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    uint8_t  level;             /* +0x2C */
    uint8_t  u2D;
    uint16_t max;               /* +0x2E */
    uint16_t cur;               /* +0x30 */
} R1gStageG;
extern R1gStageG r1f_seqG37E090;                /* 0x0037E090 */
void sub_00032140(int a, int b, int c);

/* stage H (0x0037EDEC, as area r1f) and the combo banner block K after it */
typedef struct R1gStageH {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    int32_t  table;             /* +0x2C combo threshold row 0..1 */
} R1gStageH;
extern R1gStageH r1f_seqH37EDEC;                /* 0x0037EDEC */
typedef struct R1gStageK {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 */
    int32_t  state;             /* +0x24 */
    uint8_t  b28;               /* +0x28 */
} R1gStageK;
extern R1gStageK r1g_stageK37EEC8;              /* 0x0037EEC8 */
extern int16_t  r1g_comboRank37EEBC;            /* 0x0037EEBC next threshold index */
extern int16_t  r1g_combo37EEBE;                /* 0x0037EEBE current combo, max 999 */
extern int16_t  r1g_comboRankShown37EEC0;       /* 0x0037EEC0 */
extern int16_t  r1g_comboShown37EEC2;           /* 0x0037EEC2 */
extern int16_t  r1g_comboReset37EEC4;           /* 0x0037EEC4 1 after a reset */
extern const uint16_t r1g_comboSteps28090C[2][6];  /* 0x0028090C */
void Grade_AddBestCombo(int combo);             /* 0x00041480 */
void sub_00048AF0(int id);


/* ------------------------------------------------------------ char_unit.c */
typedef struct R1gBufObj {
    uint8_t  unk00[0x0C];
    void    *buf0C;             /* +0x0C */
    uint8_t  unk10[4];
    void    *buf14;             /* +0x14 */
} R1gBufObj;
typedef struct R1gLink {
    uint8_t  unk00[8];
    struct R1gLink *next;       /* +0x08 */
    uint8_t  flags;             /* +0x0C bit 0: heap-owned */
} R1gLink;
typedef struct R1gCharUnit {
    uint32_t u00;
    int32_t  resA;              /* +0x04 */
    int32_t  resB;              /* +0x08 */
    uint8_t  flags;             /* +0x0C bit 2: shares its resources */
    uint8_t  unk0D[3];
    uint32_t u10;
    int32_t  id14;              /* +0x14 name/id pair */
    int32_t  id18;              /* +0x18 */
    int32_t  nodes;             /* +0x1C */
    void    *model;             /* +0x20 */
    void    *nodeBuf;           /* +0x24 nodes * 0x180 bytes */
    void    *node28;            /* +0x28 */
    void    *buf2C;             /* +0x2C */
    void    *anim30;            /* +0x30 (buffer at +0x18) */
    void    *p34;               /* +0x34 */
    uint8_t  unk38[4];
    struct R1gCharUnit *child;  /* +0x3C */
    R1gLink *links;             /* +0x40 */
    int32_t  tex[3];            /* +0x44 texture handles, -1 none */
    uint8_t  unk50[0x12C - 0x50];
    R1gBufObj *obj12C;          /* +0x12C */
    R1gBufObj *obj130;          /* +0x130 */
    uint8_t  unk134[4];
    R1gBufObj *obj138;          /* +0x138 */
    uint8_t  unk13C[4];
    void    *task140;           /* +0x140 root unit only */
    void    *p144;              /* +0x144 child units only */
    void    *p148;              /* +0x148 */
    uint8_t  unk14C[4];
} R1gCharUnit;                  /* 0x150 bytes */
typedef struct R1gUnitTbl {
    int32_t  count;             /* +0x00 */
    uint32_t u04;
    R1gCharUnit *units;         /* +0x08 */
} R1gUnitTbl;
typedef struct R1gAnimObj {
    uint8_t  unk00[0x18];
    void    *buf18;             /* +0x18 */
} R1gAnimObj;
void *a5b_AllocCur(int size, int a, int tag);   /* 0x00053AB0 */
int   a50_AllocTop(const char *name, int tag);  /* 0x00053BC0 */
void  a5b_CurSlotEndTemp(void);                 /* 0x00053BE0 */
void  r1e_PartValues(int *a, int *b, R1gCharUnit *u);   /* 0x0001E7D0 */
R1gUnitTbl *sub_0001F210(int a, int b);
void  r4b_NodeReset(void *n);                   /* 0x001B25B0 */
void *r4e_NodeInit(void *n);                    /* 0x001AE970 */
R1gAnimObj *sub_00083030(void *node, int a, R1gCharUnit *u);
void *sub_0007FC60(void);
void  a3c_TaskInit(void *t, R1gCharUnit *u);    /* 0x0003D6C0 */
extern const char r1g_srcCharUnit25FC08[];      /* 0x0025FC08 "\Project\nightmareXbox\app\char_unit.c" */
void a5b_HeapOp47640(void *p);                  /* 0x00053880 heap free */
void a60_Remove6994(void *m);                   /* 0x00074F10 */
void a60_Remove6974(void *m);                   /* 0x000754A0 */
void a60_DetachEff6984(void *m);                /* 0x000751C0 */
void r4b_TexFree(int h);                        /* 0x001B9FC0 */
void r1_EntAge(int a, int b);                   /* 0x00053350 */
void r1b_RecFreeRes(void *u);                   /* 0x0001D190 */

void  r1_PartsRange(R1gCharUnit *u, int out[3]);  /* 0x0001E850, regargs u=EAX out=EDI */


/* model node (0xF0 bytes, copied whole) */
typedef struct R1gModel {
    uint8_t  unk00[0x8C];
    int32_t  kind;              /* +0x8C */
    uint8_t  unk90[0xA8 - 0x90];
    int32_t  dA8;               /* +0xA8 */
    uint8_t  unkAC[0xC0 - 0xAC];
    uint32_t used;              /* +0xC0 */
    uint8_t  unkC4[0xF0 - 0xC4];
} R1gModel;
/* unit link of kind 1: attach to another unit */
typedef struct R1gAttach {
    int32_t  kind;              /* +0x00 */
    uint32_t u04;
    struct R1gAttach *next;     /* +0x08 */
    uint32_t u0C;
    R1gCharUnit *target;        /* +0x10 */
    int32_t  bone;              /* +0x14 */
    uint8_t  u18[4];
    uint8_t  flags;             /* +0x1C */
    uint8_t  u1D[3];
    int32_t  d20, d24;          /* +0x20 */
    int32_t  d28, d2C;          /* +0x28 */
    uint8_t  u30[8];
    uint8_t  uv38[8];           /* +0x38 */
    int32_t  d40, d44;          /* +0x40 */
} R1gAttach;
R1gCharUnit *r1b_RecFindName(R1gCharUnit *c, const int32_t *ids);  /* 0x0001D2D0 */
void *sub_0001DAF0(R1gCharUnit *c, int bone);
void r4b_NodeInitType9(R1gModel *m);            /* 0x001B1440 */
void r4_ModelSetCC(R1gModel *m, int tex);       /* 0x001B1530 */
void r4b_Node5SetE0(R1gModel *m, int a, int b); /* 0x001BBA00 */
void r4_ModelSetE8(R1gModel *m, int a, int b);  /* 0x001B1540 */
void r4b_NodeAttachParts(void *buf, R1gModel *m);   /* 0x001B1360 */
void r4_NodeAttach(void *bone, R1gModel *m);    /* 0x001B2020 */
void a60_AttachEff6974(R1gModel *m, int tex, int a, int b);   /* 0x00075420 */
void r4e_Node1Init(R1gModel *m);                /* 0x001B2FE0 */
void r4b_MeshAttachItems(void *buf, R1gModel *m);   /* 0x001B8E10 */
void r4d_PartsBoneOffset(R1gModel *m, int tex); /* 0x001B30C0 */
void r4f_EmitASetPair(R1gModel *m, int a, int b);   /* 0x001B3210 */
void r6d_ModelSetUV2(R1gModel *m, int tex, void *uv);   /* 0x00074DF0 */
void a60_AttachEff6984(R1gModel *m, int a, int b);  /* 0x00075150 */
void r4_HookRemoveAC(void *m, void *h);         /* 0x001B2200 */
void r4_HookAppendAC(void *m, void *h);         /* 0x001B21D0 */
void r1d_BonesLink(void *p, R1gCharUnit *c, R1gCharUnit *u);   /* 0x0001EFE0 */


/* ------------------------------------------------------------ effman.c */
/* slot pool of an effect: header (0x50 bytes, loaded whole) and two
   parallel tables grown 16 slots at a time by sub_00035320 */
typedef struct R1gPoolE60 {
    uint8_t  u00[0x34];
    uint32_t d34;               /* +0x34 */
    uint8_t  u38[0x28];
} R1gPoolE60;
typedef struct R1gPoolE14 {
    int32_t  used;              /* +0x00 0 = free */
    int32_t  d04, d08, d0C;
    R1gPoolE60 *data;           /* +0x10 */
} R1gPoolE14;
typedef struct R1gPoolHdr {
    uint8_t  u00[8];
    int32_t  cap;               /* +0x08 */
    R1gPoolE14 *slots;          /* +0x0C */
    uint8_t  u10[0x40];
} R1gPoolHdr;
typedef struct R1gPool {
    R1gPoolHdr hdr;             /* +0x00 */
    R1gPoolE14 *tbl14;          /* +0x50 */
    R1gPoolE60 *tbl60;          /* +0x54 */
} R1gPool;
/* the same pool as stored in a file: table offsets instead of pointers */
typedef struct R1gPoolBlob {
    R1gPoolHdr hdr;             /* +0x00 */
    int32_t  off14;             /* +0x50 */
    int32_t  off60;             /* +0x54 */
} R1gPoolBlob;
void sub_00035320(R1gPool *p, int cap);         /* (re)allocate the tables */

/* effect object (0x6C bytes) */
typedef struct R1gEffObj {
    uint8_t  u00[0x0C];
    struct R1gEffObj *self;     /* +0x0C */
    int32_t  id;                /* +0x10 */
    R1gPool  pool;              /* +0x14 */
} R1gEffObj;
/* effect file record of kinds 0 and 1 (0x7B0 bytes) */
typedef struct R1gEffRec {
    int32_t  id;                /* +0x000 */
    uint8_t  u04[0x0C];
    R1gPoolHdr hdr;             /* +0x010 */
    R1gPoolE14 e14[16];         /* +0x060 */
    R1gPoolE60 e60[16];         /* +0x1A0 */
    uint8_t  u7A0[0x10];
} R1gEffRec;
typedef struct R1gEffFile {
    uint32_t u00;
    uint32_t kind;              /* +0x04 */
    int32_t  count;             /* +0x08 */
    uint8_t  u0C[4];
    uint8_t  packed[0x10];      /* +0x10 kind 2: id at +0x10 of each entry, blob after */
    R1gEffRec rec[1];           /* +0x20 kinds 0, 1 */
} R1gEffFile;
R1gEffFile *a3b_Fwd373A0Z(int id, int a);      /* 0x00037570 */
void a3c_Clear16(void *task);                   /* 0x0003D860 */
void r1d_TEntInit(R1gEffObj *e);                /* 0x00036390 */
void a4c_ListAppend(void *list, void *item);    /* 0x0003D880 */

/* effect pool file ("EFS ") */
typedef struct R1gEfsFile {
    uint32_t magic;             /* +0x000 0x534645 */
    uint32_t kind;              /* +0x004 1: fixed tables, 2 and 3: packed image */
    uint8_t  u08[8];
    R1gPoolHdr hdr;             /* +0x010 (kinds 2, 3: R1gPoolBlob) */
    R1gPoolE14 e14[16];         /* +0x060 */
    R1gPoolE60 e60[16];         /* +0x1A0 */
} R1gEfsFile;
int      r1g_PoolAlloc(R1gPool *p);                          /* 0x00035700 */
uint8_t *r1g_PoolLoad(const R1gPoolBlob *b, R1gPool *p);     /* 0x000357E0, regargs p=EBX */


/* ------------------------------------------------------------ debug menus */
typedef struct R1gMenuItem {
    const char *name;           /* +0x00 */
    uint8_t  u04[0x20];
} R1gMenuItem;                  /* 0x24 bytes */
typedef struct R1gMenuData {
    uint8_t  u00[8];
    R1gMenuItem *items;         /* +0x08 */
} R1gMenuData;
typedef struct R1gMenu {
    uint32_t u00;
    int32_t  sel;               /* +0x04 */
    int32_t  count;             /* +0x08 */
    int32_t  first;             /* +0x0C first visible */
    int32_t  visible;           /* +0x10 */
    uint8_t  u14[4];
    int32_t  x, y;              /* +0x18 */
    uint8_t  u20[8];
    int32_t  pad;               /* +0x28 */
    uint8_t  u2C[0x0C];
    R1gMenuData *data;          /* +0x38 */
} R1gMenu;
int  r1e_SObjOp(int ctx, R1gMenu *m, int msg);  /* 0x0003F780 default handler */
int  sub_0003E4B0(int ctx, int x, int y, int *px, int *py, const char *fmt, ...);   /* title */
int  r1d_PageArrowUp(int ctx, int x, int y, int *px, int *py, R1gMenu *m);         /* 0x0003E550 */
int  sub_0003E610(int ctx, int x, int y, int *px, int *py, int hilite, int on, const char *fmt, ...);
int  r1d_PageArrowDown(int ctx, int x, int y, int *px, int *py, R1gMenu *m);       /* 0x0003E5B0 */
int  a3c_CallED50(R1gMenu *m);                  /* 0x0003F770 */
void a4c_ItemProcessEntry(R1gMenu *m);          /* 0x0003F570 */
void a4c_ItemRelease(R1gMenu *m, int sel);      /* 0x0003E410 */
extern const char r1g_str3816DC[], r1g_str38171C[], r1g_fmt26058C[];



/* ------------------------------------------------------------ primitive batch */
int       r4_Set40F324(int p, void *buf);       /* 0x001B2A10, returns p */
uint8_t  *sub_0003A020(uint8_t *out, const float *mtx);   /* regargs out=EAX mtx=EBX; returns the packet end */
extern float    rtc_mtx3DCE70[2][16];           /* 0x003DCE70 */
extern uint8_t  r1g_buf42C800[], r1g_buf42C900[];
extern uint8_t *r1g_batchHead3DCEF0;            /* 0x003DCEF0 */
extern uint8_t *r1g_batchStart3DCEF8;           /* 0x003DCEF8 */
extern uint8_t *r1g_batchCur3DCEFC;             /* 0x003DCEFC */
extern int32_t  r1g_batchCount3DCF00;           /* 0x003DCF00 */
extern uint32_t r1g_batchFlags3DCF04;           /* 0x003DCF04 low 3 bits: mode */
extern int32_t  r1g_batchC3DCF08;               /* 0x003DCF08 */
extern int32_t  r1g_batchA3DCFE4;               /* 0x003DCFE4 */
extern int32_t  r1g_batchB3DCFE8;               /* 0x003DCFE8 */


/* ------------------------------------------------------------ music volume */
extern int32_t r1e_g3DFED4;                     /* 0x003DFED4 volume 0..128 */
extern int32_t r1c_q3DFECC;                     /* 0x003DFECC playing handle, -1 none */
extern int32_t r1c_q3DFEC0;                     /* 0x003DFEC0 track id */
int  sub_00199B00(int id);                      /* base volume of a voice */
void r4d_VoiceStoreVolume(int h, int vol, int pan);     /* 0x00199B20 */
int  sub_0019A8E0(int id);
int  sub_0019ADE0(int id);                      /* part count */
int  sub_0019AD10(int id, int part);            /* part base volume */
void r4d_TrackSetPartVolumeIfPlaying(int h, int part, int vol, int pan);   /* 0x0019AD50 */


/* ------------------------------------------------------------ block heap */
struct R1gHeap;
typedef struct R1gBlk {
    int32_t  used;              /* +0x00 */
    struct R1gHeap *heap;       /* +0x04 */
    struct R1gBlk *next;        /* +0x08 */
    struct R1gBlk *prev;        /* +0x0C */
    uint8_t  node[0x0C];        /* +0x10 free/used list node */
    struct R1gBlk *self;        /* +0x1C */
    uint32_t size;              /* +0x20 block size including the header */
    uint32_t avail;             /* +0x24 size - 0x44 (free) or requested size (used) */
    uint8_t  u28[0x14];
    int32_t  d3C;               /* +0x3C */
} R1gBlk;
typedef struct R1gHeap {
    uint8_t  u00[8];
    R1gBlk  *last;              /* +0x08 */
    uint8_t  freeList[0x10];    /* +0x0C */
    uint8_t  usedList[0x10];    /* +0x1C */
} R1gHeap;
void a4c_ListRemove(void *node);                /* 0x0003D8C0 */


#endif
