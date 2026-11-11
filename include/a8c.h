#ifndef A8C_H
#define A8C_H
#include "oogie.h"

/* Area a8c: demo (cutscene) system helpers, third pass over 0x80000-0x8FFFF.
   Structures are named by offset; all names inferred. */

/* Object whose bit 0 at +0x08 selects a handler (0x80CF0). */
typedef struct A8cFlagObj {
    uint8_t  unk00[8];
    uint32_t flags08;           /* +0x08 */
} A8cFlagObj;

/* Mask pair compared against a filter (0x80D40). */
typedef struct A8cFilter {
    uint8_t  unk00[0x30];
    uint32_t mask30;            /* +0x30 */
    uint32_t mask34;            /* +0x34 */
} A8cFilter;

/* Keyed list node (next at +4, key at +0x10). */
typedef struct A8cKeyNode {
    uint8_t  unk00[4];
    struct A8cKeyNode *next04;  /* +0x04 */
    uint8_t  unk08[8];
    int32_t  key10;             /* +0x10 */
    uint8_t  unk14[4];
    float    f18;               /* +0x18 */
    uint8_t  unk1C[8];
    int32_t  i24;               /* +0x24 */
} A8cKeyNode;

typedef struct A8cKeyList {
    uint8_t  unk00[4];
    A8cKeyNode *head04;         /* +0x04 */
} A8cKeyList;

/* Owner with a node chain at +8 (0x82270). */
typedef struct A8cChainNode {
    uint8_t  unk00[4];
    struct A8cChainNode *next04;/* +0x04 */
} A8cChainNode;

typedef struct A8cChainOwner {
    int32_t **ctx00;            /* +0x00 */
    uint8_t  unk04[4];
    A8cChainNode *head08;       /* +0x08 */
} A8cChainOwner;

/* Doubly linked parent/child at +0x80..+0x88 (0x82720). */
typedef struct A8cLinkObj {
    uint8_t  unk00[0x80];
    struct A8cLinkObj *parent80;/* +0x80 */
    struct A8cLinkObj *sib84;   /* +0x84 */
    struct A8cLinkObj *child88; /* +0x88 */
} A8cLinkObj;

/* Callback list hanging at +0x24 (0x82F40..0x82F90). */
typedef struct A8cCbNode {
    struct A8cCbNode *next00;   /* +0x00 */
    void (*fn04)(struct A8cCbNode *n, int arg); /* +0x04, also used as key */
} A8cCbNode;

typedef struct A8cCbOwner {
    uint8_t  unk00[0x14];
    int32_t  i14;               /* +0x14 frame count */
    uint8_t  unk18[4];
    int32_t  i1C;               /* +0x1C */
    uint8_t  unk20[4];
    A8cCbNode *head24;          /* +0x24 */
} A8cCbOwner;

/* Table entry list at +0x10, next at +0x20 (0x83120..0x83450). */
typedef struct A8cEntry {
    int32_t  key00;             /* +0x00 */
    int32_t  key04;             /* +0x04 */
    int32_t  val08;             /* +0x08 */
    int32_t  i0C;               /* +0x0C */
    int32_t  i10;               /* +0x10 */
    int32_t  val14;             /* +0x14 */
    int32_t  i18;               /* +0x18 */
    int32_t  i1C;               /* +0x1C */
    struct A8cEntry *next20;    /* +0x20 */
} A8cEntry;

typedef struct A8cEntryOwner {
    uint8_t  unk00[0x0C];
    int32_t  count0C;           /* +0x0C */
    A8cEntry *head10;           /* +0x10 */
} A8cEntryOwner;

/* Array of 0x370-byte slots at +4 (0x847D0..0x84B10). */
typedef struct A8cSlot {
    int32_t  i00;               /* +0x00 */
    uint8_t  unk04[4];
    int32_t  i08;               /* +0x08 */
    int32_t  i0C;               /* +0x0C */
    void    *list10;            /* +0x10 node list head */
    uint8_t  unk14[0x10];
    uint8_t  sub24[0x370 - 0x24]; /* +0x24 */
} A8cSlot;

typedef struct A8cSlotOwner {
    uint32_t count00;           /* +0x00 slot count */
    A8cSlot *slots04;           /* +0x04 */
} A8cSlotOwner;

typedef struct A8cVoice {
    uint8_t  unk00[0x34];
    int32_t  i34;               /* +0x34 */
} A8cVoice;

/* Scene object with a child chain at +0x20 (0x89420..0x89570). */
typedef struct A8cNode {
    uint8_t  unk00[0x1A];
    int8_t   type1A;            /* +0x1A */
    uint8_t  unk1B[5];
    struct A8cNode *child20;    /* +0x20 */
} A8cNode;

/* 0x18-byte stage record table at 0x2E0680. */
typedef struct A8cStageRec {
    uint8_t  unk00[0x14];
    int8_t   flags14;           /* +0x14 */
    uint8_t  unk15[3];
} A8cStageRec;

typedef struct A8cModelRef {
    uint8_t  unk00[0x14];
    uint8_t *model14;           /* +0x14 */
} A8cModelRef;

typedef struct A8cKey3 {
    float    f00;               /* +0x00 */
    uint8_t  unk04[4];
    int32_t  i08;               /* +0x08 */
    int32_t  i0C;               /* +0x0C */
} A8cKey3;

/* Header with a count at +8 (0x3ED1B0, 0x3ED1D4). */
typedef struct A8cCounted {
    uint8_t  unk00[8];
    int32_t  count08;           /* +0x08 */
} A8cCounted;

/* 0x10-byte demo command record; kind at +4 indexes 0x2E03A8. */
typedef struct A8cCmd {
    uint8_t  unk00[4];
    int32_t  kind04;            /* +0x04 */
    uint8_t  unk08[8];
} A8cCmd;

/* Pair table at 0x3ED1F4: count +4, pairs from +8. */
typedef struct A8cPairTab {
    uint8_t  unk00[4];
    int32_t  count04;           /* +0x04 */
    struct { int32_t a, b; } pairs08[1]; /* +0x08 */
} A8cPairTab;

/* Packed channel block: count +0, flags +4, data from +0x60. */
typedef struct A8cChanHdr {
    int32_t  count00;           /* +0x00 */
    uint32_t flags04;           /* +0x04 bits 0..2 select channel count */
    uint8_t  unk08[0x58];
    int32_t  data60[1];         /* +0x60 */
} A8cChanHdr;

/* Demo player state at 0x3ED254: object with float +0x10 and byte +0x18. */
typedef struct A8cDemo {
    uint8_t  unk00[0x10];
    float    f10;               /* +0x10 */
    uint8_t  unk14[4];
    uint8_t  b18;               /* +0x18 */
} A8cDemo;

/* Demo event object (same layout family as A8bObj). */
typedef struct A8cObj {
    uint8_t  unk00[0x18];
    uint32_t flags18;           /* +0x18 bit 1: active */
    void    *work1C;            /* +0x1C */
} A8cObj;

typedef union A8cWord { int32_t i; float f; void *p; } A8cWord;

/* Per-event work block. */
typedef struct A8cWork {
    A8cWord  w00;               /* +0x00 */
    uint8_t  unk04[4];
    void    *p08;               /* +0x08 */
    uint8_t  unk0C[4];
    A8cWord  w10, w14, w18;     /* +0x10..+0x1B */
    uint8_t  unk1C[4];
    A8cWord  w20;               /* +0x20 */
} A8cWork;

/* Work header: kind +4, record +5. */
typedef struct A8cWorkHdr {
    uint8_t  unk00[4];
    int8_t   kind04;            /* +0x04 */
    int8_t   rec05;             /* +0x05 */
} A8cWorkHdr;

/* 0x24-byte event descriptor record; handler at +0x14. */
typedef struct A8cDescRec {
    uint8_t  unk00[0x14];
    int    (*fn14)(A8cObj *o, int arg);   /* +0x14 */
    uint8_t  unk18[0x0C];
} A8cDescRec;
typedef A8cDescRec *(*A8cDescGetter)(void);

typedef void (*A8cVoidFn)(void);
typedef void (*A8cCmdFn)(A8cCmd *c);
typedef int  (*A8cIntFn)(void);

/* globals */
extern uint8_t  a8c_buf3EC448[];
extern A8cCounted *a8c_g3ED1B0;
extern uint8_t  a8c_list3ED1B4[];
extern void    *a8c_g3ECCA8;
extern void    *a8c_g3ED1D0;
extern A8cCounted *a8c_g3ED1D4;
extern int32_t  a8c_g3ED1CC;
extern A8cIntFn a8c_tbl2E03A0[];
extern A8cPairTab *a8c_g3ED1F4;
extern A8cVoidFn a8c_tbl2E0438[];
extern A8cVoidFn a8c_tbl2E0450[];
extern int32_t  a8c_g3ED274;
extern A8cVoidFn a8c_tbl2E0468[];
extern uint32_t a8c_g3ED258;
extern int32_t  a8c_g3ED51C;
extern A8cStageRec a8c_stageRecs[];
extern A8cVoidFn a8c_tbl2E10E8[];
extern void    *a8c_g3ECCA8;
extern A8cCmdFn a8c_tbl2E03A8[];
extern int32_t  a8c_g3ED208, a8c_g3ED1F0, a8c_g3ED1D8, a8c_g3ED1E8, a8c_g3ED1EC, a8c_g3ED20C;
extern int32_t  a8c_handles3ED1DC[3];
extern A8cDemo *a8c_g3ED254;
extern int32_t  a8c_g3ED25C, a8c_g3ED26C;
extern float    a8c_g3ED260, a8c_g3ED264, a8c_g3ED268;
extern float    a50_frameSeconds;
extern int32_t  a30_g41316C, a30_g413170;
extern A8cDescGetter a8b_descGetters[];

/* external callees */
void  sub_00081B10(int32_t *ctx, A8cChainNode *n);
void  sub_00082200(void *root, const float *from, const float *to, void *list);
float sub_001AD9D0(float x);
void  sub_001A3F50(float x);
void  sub_001B1FC0(void);
void  sub_001B2490(void *p);
void  sub_001B1FE0(void);
int   sub_001BA7F0(int a);
void  a8c_Release102FA0(int h);
int   sub_001BA7C0(int a);
A8cVoice *sub_001B9650(int a);
void  sub_0003D860(void *list);
void  sub_00053880(void *p);
void *sub_00057E90(void);
int   sub_000862A0(void);
int   sub_00086460(void);
void  sub_0008C450(A8cNode *n, A8cNode *o);
A8cNode *sub_0007F300(A8cNode *n);
A8cNode *sub_0008C900(A8cNode *n, int a);

void *a5b_AllocCur(int size, int a, int tag);
int   sub_00086230(int a, int b, int c);
void  sub_001B7100(void *p, int a);
void  sub_001B72E0(void *p, int a);
void  sub_001B7300(void *p, int a);
void  sub_001A6820(A8cVoice *v);
void  sub_001A6620(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7);
void *sub_00053820(int pool, int size, int a, int b);
int   sub_000480F0(int h);
void  sub_00047B70(int h);
int   sub_00085590(A8cDemo *d);
int   sub_000EDA90(void);
void  sub_00087030(int i);
void  sub_000DE330(int a);
void  sub_000D2A50(void *s, int a);
void  sub_00033BF0(int a, int b);
int   sub_000EE240(void);
void  sub_000ED600(int a);
void  sub_000ED560(int a);
void  sub_000ED4F0(int a);
int   sub_00047B90(int h);
A8cNode *sub_0008B290(A8cNode *n, int a, int b);
A8cObj *sub_0008B980(int a, int b);
void *sub_0008B780(void *list, A8cObj *o);
A8cObj *sub_0008AFA0(A8cObj *o);
void  sub_0008E1C0(A8cObj *t, float a, float b, float c, float d);
void  sub_0008B700(A8cObj *a, A8cObj *b);
uint8_t *sub_00033DC0(void *p, int id);
void  sub_00033DA0(void *p, int v);
void  sub_0008B3E0(A8cWork *w);

#endif
