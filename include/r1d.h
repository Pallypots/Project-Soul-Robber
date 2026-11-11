#ifndef R1D_H
#define R1D_H
#include "oogie.h"
#include <string.h>

/* Area r1d: game functions 0x00012000..0x00060000 (fourth pass). Names
   inferred. Register-argument mappings are in config/function_states_r1d.csv. */

/* ------------------------------------------------------------ group 1 */
/* One GS register entry of a render packet template (16 bytes). */
typedef struct R1dGsEnt {
    uint16_t u00;
    uint16_t id;                /* +0x02 register id */
    uint32_t u04;
    uint32_t lo;                /* +0x08 */
    uint32_t hi;                /* +0x0C */
} R1dGsEnt;

/* texture record returned by 0x001B9650 (only the register values used) */
typedef struct R1dTex {
    uint8_t  unk00[0x28];
    uint32_t reg[10];           /* +0x28 five 64-bit register values */
} R1dTex;
R1dTex *sub_001B9650(int handle);

/* sprite packet template (0x00012010) */
typedef struct R1dSprTpl {
    R1dGsEnt ent[7];            /* +0x00 */
    uint8_t  u70;
    uint8_t  r, g, b;           /* +0x71 */
    uint32_t u74;
    uint32_t texLo, texHi;      /* +0x78 */
    uint32_t col80;             /* +0x80 */
    uint16_t w84[8];            /* +0x84 */
    uint8_t  a;                 /* +0x94 */
} R1dSprTpl;

/* quad packet template (0x00012160) */
typedef struct R1dQuadVtx {
    uint8_t  c[4];              /* +0x00 */
    int16_t  w[4];              /* +0x04 */
} R1dQuadVtx;
typedef struct R1dQuadTpl {
    R1dGsEnt ent[7];            /* +0x00 */
    uint8_t  u70[8];
    uint32_t texLo, texHi;      /* +0x78 */
    uint32_t col[4];            /* +0x80 */
    R1dQuadVtx v[4];            /* +0x90 */
} R1dQuadTpl;

/* line reader / file record stack at 0x004326A0 (same layout as area r1b) */
typedef struct R1dFileRec {
    char   *buf;                /* +0x000 */
    char   *end;                /* +0x004 */
    char    name[0x200];        /* +0x008 also the line buffer of record 0 */
} R1dFileRec;
extern R1dFileRec r1d_files4326A0[7];

/* DMA kick status words */
extern uint32_t r1d_dmaTag37B550, r1d_dmaHead37B4A8, r1d_dmaFree37B394;

/* animation bank header ("ANB" file image, "ANT" once relocated) */
typedef struct R1dAnimBank {
    int32_t u00;
    union { uint32_t magic; char tag[4]; } m;   /* +0x04 */
    int32_t u08[3];
    int32_t n14;                /* +0x14 */
    int32_t n18;                /* +0x18 */
    char    *elems;             /* +0x1C 0x54-byte elements (offsets, made absolute) */
    int32_t **lists;            /* +0x20 -1 terminated element index lists */
    struct R1dKey **keys;       /* +0x24 key tables */
} R1dAnimBank;
typedef struct R1dKey {
    int32_t u00;
    float   list;               /* +0x04 index into lists, as a float */
    int32_t u08[2];
} R1dKey;

/* allocation pool of 128 0xB0-byte slots at 0x0042CE80 */
typedef struct R1dPoolSlot {
    uint32_t flags;             /* bit 0 = in use */
    uint8_t  unk04[0xAC];
} R1dPoolSlot;
extern R1dPoolSlot r1d_pool42CE80[128];
typedef struct R1dPoolReq {
    R1dPoolSlot *slots;         /* +0x00 */
    uint32_t count;             /* +0x04 */
    int32_t  d08;               /* +0x08 */
    uint8_t  unk0C[0x30];
    uint32_t *next;             /* +0x3C */
    uint32_t *cmd;              /* +0x40 cmd[1] = slot count */
} R1dPoolReq;

void  r1d_SprTplInit(R1dSprTpl *p, int tex);
char *r1d_ReadLine(char **pp);
void  r1d_DmaKick(uint32_t addr, uint32_t qwc);
void  r1d_AnimBankFixup(R1dAnimBank *h);
void  r1d_PoolAlloc(R1dPoolReq *r);


/* ------------------------------------------------------------ group 2 */
typedef struct R1dPkt {
    uint32_t *cur;              /* +0x00 write pointer */
    uint32_t tag;               /* +0x04 */
    uint8_t  unk08[8];
} R1dPkt;
extern int32_t r1b_dma37B390;
extern int32_t r1b_pktIdx37B4A0;
extern R1dPkt  r1b_pkts37B4AC[2];
void      r1b_PktOp(void *pkt, ...);    /* 0x00102FA0 */
uint32_t  sub_000AD090(void *p, ...);   /* returns 0 on this build */
void      r1b_PktSubmit(void);          /* 0x00013AA0 */
uint64_t *sub_000138F0(void);

/* rectangle sprite (0x000141B0) */
typedef struct R1dRect {
    uint8_t  u00;
    uint8_t  r, g, b, a;        /* +0x01 */
    uint8_t  u05[3];
    int32_t  result;            /* +0x08 */
    uint32_t z;                 /* +0x0C */
    int16_t  x, y;              /* +0x10 */
    int16_t  w, h;              /* +0x14 */
} R1dRect;

/* animation track evaluated by 0x00017AE0.. */
typedef struct R1dTrack {
    uint8_t  unk00[8];
    int32_t  key;               /* +0x08 key table index */
    int32_t  frame;             /* +0x0C */
    uint8_t  unk10[0x14];
    uint32_t flags;             /* +0x24 bit 0 = disabled */
    int32_t  base;              /* +0x28 first frame */
    uint8_t  unk2C[4];
    int32_t  left;              /* +0x30 elements still to apply */
    uint8_t  unk34[8];
    R1dAnimBank *bank;          /* +0x3C */
} R1dTrack;
extern int32_t r1d_g37B554;
void sub_00015150(char *elem, int a, R1dTrack *t);     /* regargs: elem=EAX */
void sub_00015E10(char *elem, int a, R1dTrack *t);     /* regargs: elem=EAX */
void sub_00016B80(char *elem, int a, R1dTrack *t);     /* regargs: elem=EAX */
void sub_00017650(R1dTrack *t, char *elem, int a);     /* regargs: t=ESI elem=EDI */

/* menu text line */
void a60_FlagsSet(void *t, int bits);
void a60_FlagsClear(void *t, int bits);
int  sub_0003FA70(int table, int id);
void sub_0003FCB0(void *rec, int item, int a, int b, float c);
extern uint8_t r1b_menu37B580[];
extern uint8_t a1b_obj37B560[];
extern int32_t a1b_slots37BEE8[];

/* block copied by 0x000187E0 */
typedef struct R1dBlk510 { uint32_t d[0x144]; } R1dBlk510;
typedef struct R1dVec4 { float x, y, z, w; } R1dVec4;
typedef struct R1dSet {
    int32_t   d00;
    int32_t   d04;              /* +0x04 */
    int32_t   d08;              /* +0x08 */
    int32_t   d0C;
    R1dBlk510 blk;              /* +0x10 */
    R1dVec4   v[2];             /* +0x520 */
    uint8_t   unk540[0x18];
    int32_t   d558;             /* +0x558 */
} R1dSet;
void sub_000195F0(R1dSet *s);
void sub_000F5D40(void *dst, const void *src);

void r1d_PktSend9(int a, int b, int c, int d, int e, int f, int g, int h, int i);
int  r1d_RectSend(R1dRect *r);
int  r1d_TrackApplyA(int a, R1dTrack *t);
int  r1d_TrackApplyB(int a, R1dTrack *t);
int  r1d_TrackApplyC(int a, R1dTrack *t);
int  r1d_TrackApplyD(int a, R1dTrack *t);
void r1d_MenuLine(int i, int id, int a, int b, float c);
void r1d_SetCopy(R1dSet *src, R1dSet *dst);

/* ------------------------------------------------------------ group 3 */
extern int32_t  a30_g41316C, a30_g413170;
void sub_000D9AB0(int bit);
int  sub_00049B70(void);
void sub_0019E900(int a);
void sub_00048AF0(int a);

/* segment list filled by 0x0001B7B0 / 0x0001B840 */
typedef struct R1dSeg { R1dVec4 v[5]; uint8_t unk50[0x10]; } R1dSeg;
typedef struct R1dSegList {
    int32_t u00;
    int32_t count;              /* +0x04 */
    int32_t u08;
    R1dSeg *segs;               /* +0x0C */
} R1dSegList;
int sub_0007FDC0(R1dVec4 *a, R1dVec4 *b, R1dVec4 *c, int d, float e, R1dVec4 *outA, R1dVec4 *outB);
int sub_00080470(R1dVec4 *a, R1dVec4 *b, R1dVec4 *c, int d, float e, R1dVec4 *outA, R1dVec4 *outB);

/* resource node chain (next at +0x3C) */
typedef struct R1dRes { uint8_t unk00[8]; int32_t def; } R1dRes;
typedef struct R1dResNode {
    uint8_t unk00[0x30];
    R1dRes *res;                /* +0x30 */
    uint8_t unk34[8];
    struct R1dResNode *next;    /* +0x3C */
} R1dResNode;
int32_t *sub_00083120(R1dRes *r, int key);
int32_t *sub_00083140(R1dRes *r, int idx);
void     sub_000832D0(R1dRes *r, int v);

void r1d_ResetChapterFlags(void);
void r1d_SegAddA(R1dVec4 *a, R1dVec4 *b, int d, float e, R1dVec4 *c, R1dSegList *l);
void r1d_SegAddB(R1dVec4 *a, R1dVec4 *b, int d, float e, R1dVec4 *c, R1dSegList *l);
void r1d_ResChainSelect(R1dResNode *n, int key, int keep);

/* ------------------------------------------------------------ group 4 */
void r1c_ReqPush(int reg, int lo, int hi);  /* 0x000389C0 */
int  sub_00038F10(int p);
void sub_001A27D0(int mode);

/* skinned model (bone records of 0x108 bytes for type 1, 0x180 for type 9) */
typedef struct R1dBone1 {
    uint8_t u00[0x40];
    float   m[16];              /* +0x40 */
    uint8_t u80[0x58];
    int32_t sel;                /* +0xD8 */
    uint8_t uDC[0x2C];
} R1dBone1;
typedef struct R1dBone9 {
    uint8_t u00[0x40];
    float   m[16];              /* +0x40 */
    uint8_t u80[0x100];
} R1dBone9;
typedef struct R1dModelFl { uint8_t u00[0x90]; uint32_t flags; } R1dModelFl;
typedef struct R1dModel {
    uint8_t u00[0x88];
    R1dModelFl *fl;             /* +0x88 */
    int32_t type;               /* +0x8C 1 or 9 */
    uint8_t u90[0x30];
    int32_t count;              /* +0xC0 */
    void   *bones;              /* +0xC4 */
    uint8_t uC8[4];
    int32_t sel;                /* +0xCC */
} R1dModel;
typedef struct R1dMNode {
    uint8_t   u00[0x20];
    R1dModel *model;            /* +0x20 */
    uint8_t   u24[0x20];
    int32_t   sel[2];           /* +0x44 */
} R1dMNode;
typedef struct R1dMTask {
    uint8_t u00[4];
    void  (*fn)(R1dModel *m, struct R1dMTask *t);   /* +0x04 */
    uint8_t u08[8];
    R1dMNode *node;             /* +0x10 */
} R1dMTask;
void sub_001ADA40(float *dst, const float *src);
void sub_001B2150(R1dMTask *t);
void r4_HookAppendAC(R1dModel *m, R1dMTask *t);     /* 0x001B21D0 */

int  r1d_TexBasePkt2(int p);
int  r1d_TexBasePkt3(int p);
void r1d_BonesFollow(R1dModel *m, R1dMTask *t);
void r1d_BonesLink(R1dMTask *t, R1dMNode *src, R1dMNode *dst);
int  r1d_BonesSelect(R1dMNode *n, int which);

/* ------------------------------------------------------------ group 5 */
int       a50_AllocTop(const char *name, int tag);     /* 0x00053BC0 */
void      a5b_CurSlotEndTemp(void);                    /* 0x00053BE0 */
void      sub_00053880(int h);
uint32_t *sub_00037570(const char *name, int align);
int       sub_00021B00(int a, const char *name, uint32_t *buf, int h);
int       sub_000201C0(int a, const char *name, uint32_t *buf, int h);

/* sequence state blocks (a fixed field holds flag bit 0) */
typedef struct R1dSeqA {            /* 0x0037C4FC, template at 0x0037FB78 */
    uint8_t  u00[0x44];
    uint32_t flags;                 /* +0x44 */
    uint8_t  u48[0x30];
    int32_t  health;                /* +0x78 */
    int32_t  d7C;                   /* +0x7C */
    uint8_t  u80[4];
    uint16_t w84;                   /* +0x84 */
    uint8_t  u86[0xF28 - 0x86];
} R1dSeqA;
typedef struct R1dSeqB {            /* 0x0037D424, template at 0x00380C48 */
    uint8_t  u00[0x0C];
    uint32_t flags;                 /* +0x0C */
    int32_t  state;                 /* +0x10 */
    uint8_t  u14[0x1C];
    int32_t  armed;                 /* +0x30 */
    uint8_t  u34[0x674 - 0x34];
} R1dSeqB;
typedef struct R1dSeqC {            /* 0x0037DA98, template at 0x00380AA0 */
    uint8_t  u00[8];
    uint32_t flags;                 /* +0x08 */
    uint8_t  u0C[0x184 - 0x0C];
} R1dSeqC;
typedef struct R1dSeqD {            /* 0x0037DC24 */
    uint32_t flags;                 /* +0x00 */
    int32_t  state;                 /* +0x04 */
    uint8_t  u08[0x1C];
    int32_t  armed;                 /* +0x24 */
    uint8_t  u28[5];
    uint8_t  b2D;                   /* +0x2D */
    uint8_t  u2E[0xAA];
    int32_t  dD8;                   /* +0xD8 */
    uint8_t  uDC[0x2C];
    int32_t  d108;                  /* +0x108 */
} R1dSeqD;
typedef struct R1dSeqE {            /* 0x0037F480, template at 0x003812C0 */
    uint32_t flags;
    uint8_t  u04[0xD0 - 4];
} R1dSeqE;
typedef struct R1dSeqF {            /* 0x0037EDEC */
    uint32_t flags;                 /* +0x00 */
    int32_t  state2;                /* +0x04 */
    uint8_t  u08[0xD8];
    int32_t  state;                 /* +0xE0 */
} R1dSeqF;
extern R1dSeqA r1d_seqA37C4FC, r1d_seqA37FB78;
extern R1dSeqB r1d_seqB37D424, r1d_seqB380C48;
extern R1dSeqC r1d_seqC37DA98, r1d_seqC380AA0;
extern R1dSeqD r1d_seqD37DC24;
extern R1dSeqE r1d_seqE37F480, r1d_seqE3812C0;
extern R1dSeqF r1d_seqF37EDEC;
extern uint32_t r1d_flags37ED00, r1d_flags37E090, r1c_flags37F0C8;
void r1c_ClearWork42CE80(void);             /* 0x00017D30 */
void sub_00028EB0(void);
void sub_00028FE0(void);
void sub_000290F0(void);
void sub_00029230(void);
void sub_00029310(void);
void sub_00029470(void);
void sub_00029580(void);
void sub_000299F0(void);
void sub_00029AE0(void);
void sub_00023A70(void);
void sub_00029BC0(void);
void sub_00029CE0(void);
void sub_0002ACF0(void);
void sub_0002AE60(void);
void sub_0002AF80(void);
void sub_0002A950(void);
void sub_0002ABD0(void);
void sub_00023B70(void);
int  sub_00026910(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

int  r1d_LoadPack(int a, const char *name);
void r1d_SeqEnable(int which, unsigned int on);
void r1d_SeqInitAll(void);
int  r1d_Fwd26910(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
void r1d_SeqBStep(void);
void r1d_SeqDStep(void);

/* ------------------------------------------------------------ group 6 */
typedef struct R1dAnimObj {
    uint8_t   u00[0x2C];
    R1dModel *model;            /* +0x2C */
    int32_t   anim;             /* +0x30 */
} R1dAnimObj;
int sub_0003F9C0(int anim, const void *table);
extern const uint8_t r1d_anims282AD8[], r1d_anims282C7C[], r1d_anims282E24[],
                     r1d_anims282F18[], r1d_anims283008[], r1d_anims2831F4[],
                     r1d_anims2833C0[];

/* model viewer slot handles (-1 = none) */
extern int32_t a3b_mode381AB8;              /* 0x00381AB8 (100 = special mode) */
extern int32_t r1d_tex381AB4, r1d_tex381AB0, r1d_tex381A60, r1d_tex381A64, r1d_tex381A68;
extern int32_t r1d_heap381A5C, r1d_sel38182C;
extern char    r1d_path381A70[];
extern const char r1d_fmt2835E8[];
void sub_001B9FC0(int h);
void sub_0004F5D0(int tag);
void sub_0004F700(int tag);
void sub_0004F720(void);
int  a6b_Printf2(char *dst, const char *fmt, ...);     /* 0x0007E0A0 */
void sub_00053E20(const char *name, int heap);
int  sub_00053CA0(int a);
void sub_000580D0(void);
int  sub_00084C00(int heap, int a);

/* state queue at 0x00381834 */
extern int32_t r1b_queue381834[4];
void r1b_Queue381834Tick(void);             /* 0x00032600 */
void r1b_Queue381834PopA(void);             /* 0x00032670 */
void sub_000326C0(void);
void r1b_Queue381834PopB(void);             /* 0x00032840 */
void sub_000328A0(void);
void r1b_Queue381834PopC(void);             /* 0x00032A00 */
void sub_00032A50(void);
void r1b_Queue381834PopD(void);             /* 0x00032BF0 */
void sub_00032C40(void);
void sub_001A8A70(int mode);
void sub_00079340(void);

typedef struct R1dPair { int32_t u00; int32_t a; int32_t b; } R1dPair;

extern char *r1c_bank283698;                /* 0x00283698 */
extern void *r1_g3DA080, *r1_g3DA084;
void  r4_NodeDetach(void *node);            /* 0x001B2080 */
void  sub_001B2020(void *list, void *node);
char *a50_Alloc(int kind, int size, int a, int b);     /* 0x00053820 */
void  r1_BankInit(void);                    /* 0x00033330 */

int  r1d_AnimObjBind(R1dAnimObj *o, R1dModel *m);
void r1d_ViewerRelease(void);
void r1d_ViewerLoad(unsigned int idx);
int  r1d_KeyDecode(int key, R1dPair *p, int *outA, int *outB);
void r1d_BankRealloc(void);

/* ------------------------------------------------------------ group 7 */
/* effect emitter block embedded in a node (+0x20) */
typedef struct R1dEmitTgt { uint8_t u00[0xE8]; uint32_t start; int32_t armed; } R1dEmitTgt;
typedef struct R1dEmitElem {
    uint8_t  u000[0xB0];
    uint32_t flags;             /* +0x0B0 */
    uint8_t  u0B4[0x64];
    R1dEmitTgt *tgt;            /* +0x118 */
    int32_t  id;                /* +0x11C */
    uint32_t num;               /* +0x120 */
    uint32_t den;               /* +0x124 */
    uint8_t  u128[4];
} R1dEmitElem;
typedef struct R1dEmit {
    uint8_t     u00[0xB0];
    uint32_t    count;          /* +0xB0 */
    uint8_t     uB4[0x28];
    R1dEmitElem elems[1];       /* +0xDC */
} R1dEmit;
/* effect node; lives at +0x10 of a 0xB40-byte bank entry */
typedef struct R1dNode {
    int32_t  kind;              /* +0x00 0 = emitter, 1 = linked */
    uint32_t flags;             /* +0x04 */
    int32_t  id;                /* +0x08 */
    uint32_t key;               /* +0x0C */
    struct R1dNode *child;      /* +0x10 */
    R1dPair *pair;              /* +0x14 */
    uint8_t  u18[8];
    union { R1dEmit e; uint8_t raw[0xA3C]; } blk;   /* +0x20 */
    uint8_t  list2[0xC4];       /* +0xA5C */
} R1dNode;
typedef struct R1dNodeEnt {
    uint32_t flags;             /* +0x00 bit 0 = in use */
    void    *owner;             /* +0x04 */
    uint8_t  u08[8];
    R1dNode  node;              /* +0x10 */
    uint8_t  link[0x10];        /* +0xB30 */
} R1dNodeEnt;
#define R1D_ENT(n) ((R1dNodeEnt *)((char *)(n) - 0x10))
typedef struct R1dFxTab { uint8_t u00[0x20]; int32_t v20; } R1dFxTab;
typedef struct R1dFx {
    uint8_t   u00[4];
    R1dFxTab *tab;              /* +0x04 0x18-byte records */
    void     *index;            /* +0x08 */
} R1dFx;
typedef struct R1dAB { int32_t a, b; } R1dAB;
typedef struct R1dRange {
    uint32_t flags;             /* +0x00 */
    uint8_t u04[0x0C];
    void   *owner;              /* +0x10 */
    int32_t d14;                /* +0x14 */
    int32_t d18;                /* +0x18 */
    int32_t d1C[16];            /* +0x1C */
} R1dRange;
typedef struct R1dHostRec {
    uint8_t   u000[0x0C];
    uint8_t   flags;            /* +0x00C */
    uint8_t   u00D[0x127];
    R1dRange *range;            /* +0x134 */
    uint8_t   u138[0x18];
} R1dHostRec;
typedef struct R1dHostGrp {
    int32_t     count;          /* +0x00 */
    uint8_t     u04[4];
    R1dHostRec *recs;           /* +0x08 */
    uint8_t     u0C[4];
    struct R1dHostGrp *next;    /* +0x10 */
} R1dHostGrp;
/* scene context (pointer at 0x0042C8E4) */
typedef struct R1dActor {
    uint8_t      u000[0x44];
    int32_t      d44;           /* +0x044 */
    uint8_t      u048[0x1A0];
    R1dHostGrp **hosts;         /* +0x1E8 */
} R1dActor;
extern R1dActor *r1c_scene42C8E4;           /* 0x0042C8E4 */
void      sub_001B6D70(void *blk);
void      a4c_ListRemove(void *link);   /* 0x0003D8C0 */
void      sub_00036B10(void *ent);
R1dNode  *sub_00033410(int a);
int32_t  *a50_TableFind(void *index, int key);  /* 0x00052AD0 */
void      sub_001B6C80(void *blk, int def);
void      r4b_EmitSetSet11C(R1dEmitElem *e, int v); /* 0x001B6260 */
void      r4_EmitClearFlag1(void *blk);         /* 0x001B6120 */
R1dNodeEnt *r1c_PoolFind(void *cur, int stride, void *fn, void *ctx);   /* 0x00036B70 */
void      a5b_RangeInit(R1dRange *r);           /* 0x0005A400 */
void     *sub_000847F0(int a, int b);

void     r1d_NodeFree(R1dNode *n);
R1dNode *r1d_NodeFindId(int id, R1dNode *after);
R1dNode *r1d_NodeCreate(R1dFx *fx, uint32_t key);
void     r1d_NodeAttach(R1dNode *n, R1dActor *o);
int      r1d_NodeKillMatch(R1dNodeEnt *e, R1dAB *want);

/* ------------------------------------------------------------ group 9 */
typedef struct R1dRangeSpec {
    uint8_t u00[0x0C];
    int32_t d0C;                /* +0x0C */
    uint8_t u10[0x40];
    int32_t d50;                /* +0x50 */
} R1dRangeSpec;
typedef struct R1dRangeEnt {
    uint32_t flags;
    void    *owner;
    uint8_t  u08[8];
    R1dRange range;             /* +0x10 */
} R1dRangeEnt;
typedef struct R1dRangeHost {
    uint8_t   u000[0x134];
    R1dRange *range;            /* +0x134 */
} R1dRangeHost;
typedef struct R1dSpawn {
    struct R1dSpawn *next;      /* +0x00 */
    uint8_t  u04[0x0C];
    int32_t  flag;              /* +0x10 event flag, -1 = always */
    R1dRangeSpec spec;          /* +0x14 */
} R1dSpawn;
typedef struct R1dSpawnList { uint8_t u00[4]; R1dSpawn *head; } R1dSpawnList;
R1dRangeEnt *r1c_PoolTake(void *pool, int stride);     /* 0x00036AD0 */
void sub_00033710(R1dRange *r);
void sub_00033C20(R1dRange *r);
void a5b_PairSet(R1dRange *r, R1dRangeSpec *s);        /* 0x0005A6D0 */
int  sub_000D9A70(int flag);

void r1d_HostRangeNew(R1dRangeHost *h, R1dRangeSpec *s);
int  r1d_SpawnRanges(R1dSpawnList *l);

/* ------------------------------------------------------------ group 10 */
typedef int (*R1dPoolFn)(void *entry, void *ctx);
int   r1c_PoolForEach(void *pool, int stride, R1dPoolFn fn, void *ctx);   /* 0x00036B30 */
int   sub_00034AC0(void *entry, void *ctx);
int   sub_00034270(void *entry, void *ctx);
int   sub_000335D0(void *entry, void *ctx);
int   sub_00034B50(void *entry, void *ctx);
R1dFx *a50_CacheGetData(int a, int b);      /* 0x000532B0 */
extern int32_t r1d_fxBank420DA8;
void  sub_00034DD0(R1dNode *n, float *r3, float *r2, float *r1);
typedef struct R1dGrpEnt {
    struct R1dGrpEnt *next;     /* +0x00 */
    uint8_t  u04[8];
    struct R1dGrpEnt *self;     /* +0x0C */
    int32_t  id;                /* +0x10 */
    uint8_t  sub[0x10];         /* +0x14 */
} R1dGrpEnt;
typedef struct R1dGroup {
    uint8_t    u00[8];
    uint8_t    list[4];         /* +0x08 */
    R1dGrpEnt *head;            /* +0x0C */
} R1dGroup;
void *sub_00053AB0(int size, int a, int tag);
void  sub_0003D860(void *list);
void  a4c_ListAppend(void *list, void *item);   /* 0x0003D880 */

int        r1d_NodeForKey(int a, int b);
void       r1d_SceneFreeRanges(void);
R1dNode   *r1d_NodeSpawnKey(int a, int b, int c);
void       r1d_NodeRefresh(R1dNode *n);
void       r1d_SpawnReset(R1dSpawnList *l);
R1dGrpEnt *r1d_GroupFindAdd(R1dGroup *g, int id);

/* ------------------------------------------------------------ group 11 */
typedef struct R1dLnk { struct R1dLnk *next; uint8_t u04[8]; void *obj; } R1dLnk;
typedef struct R1dChainSrc { uint8_t u00[0x18]; R1dLnk *head; } R1dChainSrc;
R1dNode *sub_00035C60(void *obj, int a, int b, int c, int d);
extern uint8_t r1_bank381AC0[];             /* 0x00381AC0 static bank */

/* timer-pair block (+0x14 of a 0x6C-byte list entry) */
typedef struct R1dTimers {
    uint8_t u00[0x10];
    int32_t slot[16];           /* +0x10 */
} R1dTimers;
typedef struct R1dTEnt {
    struct R1dTEnt *next;       /* +0x00 */
    uint8_t   u04[8];
    struct R1dTEnt *self;       /* +0x0C */
    int32_t   id;               /* +0x10 */
    R1dTimers t;                /* +0x14 */
} R1dTEnt;
typedef struct R1dTList { uint8_t u00[4]; R1dTEnt *head; } R1dTList;
void a5b_TimerInit(R1dTimers *t);           /* 0x0005A6E0 */
void sub_00035320(R1dTimers *t, int a);
void r1c_ObjSlotsReset(R1dTimers *t);       /* 0x00036340 */

/* scene objects */
typedef struct R1dSceneObj { uint8_t u00[4]; int32_t d04; } R1dSceneObj;
void         a50_PushHeap(int kind);        /* 0x00053710 */
R1dSceneObj *r6b_Alloc214(void);            /* 0x00079880 */
void         r6c_ObjInit(R1dSceneObj *o);   /* 0x000798B0 */
int          sub_00079A00(R1dSceneObj *o, int v);
void         sub_0007ABB0(R1dSceneObj *o);
void         r6c_ObjResetPose(R1dSceneObj *o);  /* 0x0007ACC0 */
void         sub_00079E00(R1dSceneObj *o);
void         sub_00053740(void);
extern int32_t r1c_obj2836DC;
extern void   *r1c_bufAData3DA0C0, *r1c_bufBData3DA0B8;
extern void   *r1c_bufA3DA0C8, *r1c_bufB3DA0CC, *r1c_data3DA0D0, *r1d_g3DA0BC;
extern int32_t r1d_heap3DA0D4;
extern R1dActor *r1d_saved3DA0C4;
extern uint16_t r1d_texGrp3DA0B4;
extern const char r1d_name261588[];
void     sub_0001E550(void *p);
void     sub_00020170(void *p);
uint16_t r4b_TexSetGroup(int g);            /* 0x001BA0B0 */

R1dNode *r1d_ChainBuild(R1dChainSrc *src, int a, int b, int c, int d);
void     r1d_BankRestore(void);
void     r1d_TEntInit(R1dTEnt *e);
void     r1d_SceneCreate(void);
void     r1d_SceneDestroy(void);
R1dTEnt *r1d_TListFindAdd(R1dTList *l, int id);
void     r1d_SceneSetup(void);

/* ------------------------------------------------------------ group 13 */
void sub_000586E0(int a);
int  sub_001A8210(const char *name, int flags, int mode);  /* open */
int  r4b_FileClose(int h);                  /* 0x001A8330 */
int  r4b_FileSeek(int h, int off, int whence);  /* 0x001A8490 */
int  sub_00051850(const char *name);
int  sub_001C8036(const char *fmt, ...);    /* CRT debug print */
extern const char r1d_fmt2615AC[];

/* sound/effect channel table at 0x0042CB20 (10 records of 0x48 bytes) */
typedef struct R1dChan {
    uint8_t  u00[0x20];
    int32_t  state;             /* +0x20 0 = end of table, 1, 2 */
    uint8_t  u24[0x20];
    uint32_t flags;             /* +0x44 bit 0 = paused */
} R1dChan;
extern R1dChan r1c_tbl42CB20[10];
void sub_00037830(R1dChan *c);              /* regargs: c=EAX */
void sub_00037910(R1dChan *c, int a);       /* regargs: c=ESI */
void sub_00037790(R1dChan *c, int a);       /* regargs: c=ESI */
void sub_00037C70(void *ctx);               /* regargs: ctx=EDI */
void sub_00037DD0(void);

int  r1d_FileWrite(const char *name, void *buf, int size, int mode);
void sub_00037AF0(void);
void r1d_ChanUpdate(void *ctx);

/* ------------------------------------------------------------ group 15 */
/* font/picture set-up */
extern int32_t a3c_g2C4460, a3c_g2C4464, a3c_busy3DA310, a3c_g3DA2FC;
extern char    a3c_obj2C4090[];
extern int32_t r1d_tex3DA2EC[4];            /* 0x003DA2EC */
extern int32_t r1d_src3DA300[4];            /* 0x003DA300 */
extern const int32_t r1d_srcTbl2C3800[];    /* 0x002C3800 */
extern char    r1d_blob2C3810[];            /* 0x002C3810 */
extern int32_t r1d_g3DA318;
extern void   *r1c_paged3DA314;             /* 0x003DA314 */
extern uint8_t a60_table266AD8[];           /* 0x00266AD8 */

/* GS register request queue at 0x003DA390 */
typedef struct R1dReq { uint32_t lo, hi, reg, regHi; } R1dReq;
extern int32_t r1c_reqCount3DA390;
extern R1dReq  r1c_req3DA398[16];
typedef struct R1dTexInfo { uint8_t u00[0x18]; int32_t d18, d1C, d20; } R1dTexInfo;
R1dTexInfo *r4b_Get412F40(void);            /* 0x001BB230 */
uint32_t    sub_001BB240(int a, int b, int c);

/* packet under construction */
extern uint32_t *r1_pk3DA320, *r1d_pkEnd3DA324;

/* register list flushed by 0x00038AD0 */
typedef struct R1dRegList {
    uint8_t  u00[0x10];
    uint32_t d10;               /* +0x10 */
    uint8_t  u14[0x5C];
    int32_t  n;                 /* +0x70 */
    uint8_t  u74[4];
    uint32_t q[1][4];           /* +0x78 */
} R1dRegList;

int       r1d_PicInit(void);
void      r1d_PktClose(void);

/* ------------------------------------------------------------ group 16 */
extern int32_t r1d_pkRoom3DA328;            /* 0x003DA328 quadwords left */
void sub_00038BF0(void *stream);            /* regargs: stream=EBX */

/* fade/colour channel records at 0x003DA4A8 (0x2C bytes) */
typedef struct R1dFade {
    int32_t d00;
    int32_t mode;               /* +0x04 */
    int32_t d08;                /* +0x08 */
    int32_t level;              /* +0x0C */
    int32_t d10;                /* +0x10 */
    int32_t speed;              /* +0x14 */
    int32_t d18;                /* +0x18 */
    int32_t d1C, d20, d24, d28; /* +0x1C */
} R1dFade;
extern R1dFade r1c_chan3DA4A8[];

void r1d_PkAddTex(int a, int b, int c);
void r1d_PkAdd4(int a, int b);
void r1d_Fade1Mode(int m);

/* ------------------------------------------------------------ group 17 */
int sub_000390E0(int i, int v);             /* regargs: i=EAX */
int sub_00039440(int i, int v);             /* regargs: i=EAX */
int sub_000396E0(int v);

typedef struct R1dCamRef { uint8_t u00[0x0C]; uint32_t *flags; } R1dCamRef;
extern int32_t r1c_camList3DDC60;           /* 0x003DDC60 camera list */
int        sub_0003ABC0(void *e, int key);
R1dCamRef *sub_0003DBC0(void *list, int (*match)(void *, int), int key);
R1dCamRef *sub_0003DC10(void *node, int (*match)(void *, int), int key);

/* title/menu screen state */
extern int32_t r1d_g3DDC74, r1d_heap3DDC70, r1d_g3DDC80;
extern int32_t r1d_tex3DDC98[7];            /* 0x003DDC98 */
int  a5b_GetVideoMode(void);                /* 0x000529F0 */
void sub_001A1B90(void);
int  a60_MovieState(void);                  /* 0x00079460 */
extern uint8_t a4c_obj428F40[];             /* 0x00428F40; byte 5 = flags */
void sub_0019BEB0(int mask);
void sub_0019BE90(int mask);
void sub_0003C7E0(void);
void sub_001A0D70(void);
void r1c_JobFinish(void);                   /* 0x00058190 */
typedef struct R1dBufRec { int32_t cmd; int32_t f4, f8; } R1dBufRec;
extern int32_t   r4c_bufIndex42CAC0;
extern R1dBufRec r4c_bufs42CAC8[2];
void sub_001A5310(void);
int  sub_0003C740(int v);
int  sub_000727E0(int v, void *obj);
int  sub_00079480(int v);

void r1d_CamSetFlag(int key, int on);
void r1d_TitleRelease(void);
void r1d_TitleLoop(void);
void r1d_FrameLoop(void);

/* ------------------------------------------------------------ group 18 */
int  a1a_GroupAdd(void *job, int slot, int prio, void (*fn)(void), int a, int stack);  /* 0x001A1030 */
int  a1a_GroupReleaseOne(void *job, int slot);  /* 0x001A1060 */
void sub_0003C700(void);
extern int32_t r1d_g3DDC84, r1d_g3DDC88, r1d_g3DDC8C, r1d_g3DDC90, r1d_g3DDC94;

/* camera groups at 0x003DDCC0 */
typedef struct R1dCamNode { uint8_t u00[0x0C]; char *data; } R1dCamNode;
typedef struct R1dCamGrp { uint8_t u00[8]; int32_t count; } R1dCamGrp;
extern R1dCamGrp  *a4c_groupHdr[2];         /* 0x003DDCC0 */
extern uint8_t     a4c_groupList[];         /* 0x003DDCC8 */
extern char       *a4c_groupData[2];        /* 0x003DDCD8 */
extern char       *a4c_groupRecs[2];        /* 0x003DDCE0 */
extern R1dCamNode  a4c_groupNodes[2][64];   /* 0x003DDCF0 */

/* page text */
typedef struct R1dPage { uint8_t u00[8]; int32_t count; int32_t first; int32_t cur; } R1dPage;
extern int32_t *a4c_pg2C4B08;
extern const char r1d_fmt266FC0[];
int sub_0002E8C0(int a, int b, int c, int g, int d, int e, const char *fmt, int ch);

void r1d_TitleStart(void *job);
void r1d_CamGroupInit(int i, R1dCamGrp *g);
int  r1d_PageArrowUp(int a, int b, int c, int d, int e, R1dPage *p);
int  r1d_PageArrowDown(int a, int b, int c, int d, int e, R1dPage *p);

#endif
