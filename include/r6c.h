#ifndef R6C_H
#define R6C_H
#include "oogie.h"
#include "shared_decls.h"
#include "a60.h"
#include "a6b.h"
#include <string.h>
/* Area r6c: functions (stack and register arguments) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6c.csv. */

/* ------------------------------------------------------------ encoded text (0x76xxx) */
/* Font record reached through 0x003E69A4: character codes below `singleCount`
   are one byte, the rest are two-byte codes. */
typedef struct R6cFont {
    uint8_t  unk00[8];
    uint16_t singleCount;     /* +0x08 */
} R6cFont;
extern R6cFont *r6c_textFont;             /* 0x003E69A4 */
extern uint32_t a19_g413174;              /* 0x00413174 */

/* Text box: page counter, encoded text and two animation players. */
typedef struct R6cText {
    union { uint32_t flags; int8_t flags0; } u00;  /* +0x00 bit 7 and bit 8 select draw passes */
    uint8_t  unk04[0x24 - 0x04];
    int32_t  pageChars;       /* +0x24 visible characters up to the next page break */
    int32_t  len;             /* +0x28 */
    uint8_t  buf[0x800];      /* +0x2C control codes 1..7, 6 = page break */
    int32_t  pos;             /* +0x82C */
    uint8_t  anim830[0x9C];   /* +0x830 */
    uint8_t  anim8CC[0x9C];   /* +0x8CC */
} R6cText;

/* Skip the parameter bytes of the code at s[i] (advance i, not past the code itself). */
#define R6C_TEXT_SKIP(s, i)                                         \
    switch ((s)[i]) {                                               \
    case 4: (i)++; break;                                           \
    case 7: (i)++; if ((s)[i] == 5) (i) += 2; break;                \
    case 1: case 2: case 3: case 5: case 6: break;                  \
    default:                                                        \
        if ((uint16_t)(s)[i] >= r6c_textFont->singleCount) (i)++;   \
        break;                                                      \
    }

int      r6c_TextPageChars(R6cText *t);                   /* 0x00076180 */
int      r6c_TextLen(const uint8_t *s);                   /* 0x00076330 */
int      r6c_TextCount(const uint8_t *s);                 /* 0x000762A0 */
int      r6c_TextIndex(const uint8_t *s, int n);          /* 0x000763A0 */
void     r6c_TextReset(R6cText *t);                       /* 0x00076120, t in EAX */

void sub_00014E80(void *p);
int  sub_0019BE60(int k);

/* ------------------------------------------------------------ sound channels (0x771xx) */
extern uint32_t *r6c_chReg670[2];          /* 0x002DF670 */

/* ------------------------------------------------------------ movie screen tasks (0x78xxx-0x79xxx) */
typedef struct R6cBuf12 { int32_t a; void *p; int32_t c; } R6cBuf12;
extern R6cBuf12 a30_buf12[2];              /* 0x0042CAC4 */
extern int32_t  a30_bufIndex;              /* 0x0042CAC0 */
extern uint8_t  a4c_obj428F40[];           /* 0x00428F40 */
extern uint8_t  r6c_obj3E73A0[];           /* 0x003E73A0 */
extern uint8_t  r6c_obj2DF680[];           /* 0x002DF680 */
extern int32_t  r6c_v3E7550;               /* 0x003E7550 */

void  r6c_MovieTask(void *task);             /* 0x00078170 */
void  r6c_MovieLoop(void);                 /* 0x000781F0 */
int   sub_00031C50(void);
int   sub_00031560(int a, int b);
void  sub_0001AE70(void *a, void *b);
int   sub_00077500(void);
void  sub_0002BAB0(void);
void  sub_00078050(void);
void  sub_00058190(void);
void  sub_001A5310(void);
void  sub_001A7EE0(void);
void *sub_00077AA0(void *p);                /* p in EAX */
void  sub_001A7B90(void);
void  sub_00038960(void);
void  sub_000791A0(void);

/* ------------------------------------------------------------ 3D sprite object (0x79xxx-0x7Dxxx) */
typedef struct R6cRgba4 { int32_t r, g, b, a; } R6cRgba4;   /* colour stored one channel per word */
typedef struct R6cVec4 { float x, y, z, w; } R6cVec4;
typedef struct R6cMtx { float r[4][4]; } R6cMtx;
typedef struct R6cLight {                  /* 0x34 bytes */
    uint8_t  unk00[0x24];
    R6cVec4  v24;             /* +0x24 */
} R6cLight;
typedef struct R6cVecEnt { int32_t id; R6cVec4 v; } R6cVecEnt;   /* 0x14 bytes */
typedef struct R6cMdl370 { int32_t w[6]; uint8_t unk018[0x24 - 0x18]; uint8_t blk24[0x370 - 0x24]; } R6cMdl370;
typedef struct R6cMdlList { uint32_t count; R6cMdl370 *items; } R6cMdlList;
typedef struct R6cTint { float x, y, c4, c8, cc; } R6cTint;
typedef struct R6cTintBlk { uint8_t flags; uint8_t pad[3]; R6cTint tint; } R6cTintBlk;  /* 0x18 bytes */
typedef struct R6cAttach {
    struct R6cAttach *next;   /* +0x00 */
    uint8_t  unk04[0x20 - 0x04];
    void    *p20;             /* +0x20 */
    uint8_t  unk24[0x2C - 0x24];
    int32_t  kind;            /* +0x2C */
    uint8_t  unk30[0x80 - 0x30];
    union { struct R6cAttach *target; int id; } u80;  /* +0x80 target, or the target's bone id */
} R6cAttach;
typedef struct R6cObj7 {
    uint8_t  unk000[0x0C];
    R6cLight light;           /* +0x00C */
    R6cRgba4 *colour;         /* +0x040 */
    R6cMdlList *mdl;          /* +0x044 */
    int32_t  i48, i4C, i50;   /* +0x048 */
    uint8_t  unk054[0x154 - 0x54];
    R6cMtx   m154;            /* +0x154 */
    R6cVec4  v194;            /* +0x194 rotation */
    R6cVec4  v1A4;            /* +0x1A4 position */
    float    scale;           /* +0x1B4 */
    R6cTintBlk t1B8;          /* +0x1B8 */
    int32_t  colR, colG, colB;/* +0x1D0 */
    uint8_t  unk1DC[0x1FC - 0x1DC];
    R6cAttach *attach;        /* +0x1FC */
} R6cObj7;
typedef struct R6cColourOut { uint8_t r, g, b, a; float scale; } R6cColourOut;
typedef struct R6cDraw {
    uint8_t  unk000[0x100];
    R6cColourOut c100;        /* +0x100 */
    uint8_t  unk108[0x1F0 - 0x108];
    R6cColourOut c1F0;        /* +0x1F0 */
} R6cDraw;
typedef struct R6cSprite {                 /* 0x38 bytes */
    uint8_t  unk00[8];
    int32_t  i08, i0C;        /* +0x08 */
    uint8_t  unk10[8];
    int32_t  i18, i1C;        /* +0x18 */
    uint8_t  b20;
    uint8_t  r, g, b, a;      /* +0x21 */
    uint8_t  unk25[0x30 - 0x25];
    int16_t  x0, y0, x1, y1;  /* +0x30 */
} R6cSprite;
extern R6cRgba4  r6c_colour2DFF70;         /* 0x002DFF70 */
extern R6cLight  r6c_light2DFF80;          /* 0x002DFF80 */
extern R6cVecEnt r6c_vecTable[19];         /* 0x002DFFB8, ends with id -1 */
extern R6cSprite r6c_sprite3E9228, r6c_sprite3E9260;
extern R6cVec4   r6c_vec3E92DC;            /* 0x003E92DC */
extern R6cRgba4  r6c_colour3E92EC;         /* 0x003E92EC */

void  r6c_LookupVec(int id, R6cVec4 *dst);                  /* 0x00079910, id in EDX, dst in EDI */
void  r6c_BuildMatrix(R6cMtx *m, const R6cVec4 *rot, const R6cVec4 *pos, float scale); /* 0x00079C40 */
void  r6c_ApplyVecs(R6cMdlList *l, R6cLight *light);        /* 0x00079980 */
void  r6c_ObjApplyTint(R6cObj7 *o);                         /* 0x00079EF0 */
void  r6c_ObjCopyColour(R6cObj7 *o, R6cDraw *d, int flags); /* 0x00079F50 */
void  r6c_SpriteInitA(void);                                /* 0x00079700 */
void  r6c_SpriteInitB(void);                                /* 0x000797A0 */
void  r6c_ObjUpdateAttach(R6cObj7 *o);                      /* 0x0007AB40 */
void *sub_001B7FF0(void *pb, int r, int g, int b, int al);
void  sub_00012110(void *p);
void  sub_000389C0(int reg, int lo, int hi);
void  sub_001A7620(int a);
void *sub_000398D0(void *a, int b);
void *sub_00039920(void *a, int b);
void  sub_001B20F0(float f);
void  sub_001B2120(float a);
void  sub_001AD910(R6cMtx *out, const R6cMtx *in, float a);
void  sub_001AD8B0(R6cMtx *out, const R6cMtx *in, float a);
void  sub_001ADBA0(float *out, const float *in, float s);
void  sub_00079CB0(R6cObj7 *o);                             /* o in ESI */
void  sub_00079B40(R6cObj7 *o);
void  sub_001B74E0(R6cLight *l, float k, int b);
void  sub_00084790(R6cMdlList *h, R6cLight *l);
int   sub_00082E50(R6cAttach *t, void *p);
void  sub_001B2080(void *a);
void  sub_00081E60(int a, int b);
void *sub_000849D0(R6cMdlList *h, void *a);

/* ------------------------------------------------------------ y_character.c scene tree (0x7Exxx-0x7Fxxx) */
typedef struct R6cPItem {                  /* member of a part list */
    int32_t  id;              /* +0x00 */
    uint8_t  unk04[0x20 - 0x04];
    struct R6cPItem *next;    /* +0x20 */
} R6cPItem;
typedef struct R6cPList {
    uint8_t  unk00[8];
    int32_t  cur;             /* +0x08 id of the current member, -1 none */
    int32_t  count;           /* +0x0C */
    R6cPItem *first;          /* +0x10 */
} R6cPList;
typedef struct R6cPart {
    uint8_t  unk00[0x0C];
    uint32_t flags;           /* +0x0C bit 0: active */
    uint8_t  unk10[0x20 - 0x10];
    R6cAttach *att;           /* +0x20 */
    uint8_t  unk24[0x30 - 0x24];
    R6cPList *list;           /* +0x30 */
    uint8_t  unk34[0x3C - 0x34];
    struct R6cPart *next;     /* +0x3C */
    uint8_t  unk40[0x12C - 0x40];
    A6bCharRes *res;          /* +0x12C */
} R6cPart;
typedef struct R6cTNode {
    uint8_t  flags;           /* +0x00 bit 1: allocated */
    uint8_t  unk01[7];
    struct R6cTNode *next;    /* +0x08 */
    struct R6cTNode *prev;    /* +0x0C */
    struct R6cTNode *parent;  /* +0x10 */
    struct R6cTNode *child;   /* +0x14 */
    uint8_t  unk18[2];
    uint8_t  refs;            /* +0x1A */
    uint8_t  unk1B;
    union { A6bRec *rec; R6cPItem *item; } u1C;   /* +0x1C */
    uint8_t  unk20[0x5C - 0x20];
    R6cPart *parts;           /* +0x5C */
} R6cTNode;
typedef struct R6cBlk20 { uint8_t unk00[0x18]; int32_t v18; int32_t unk1C; } R6cBlk20;
typedef struct R6cKeyInfo { uint8_t unk00[0x10]; int32_t i10; uint8_t unk14[0x24 - 0x14]; } R6cKeyInfo;
typedef struct R6cKeyObj { uint8_t unk00[0x1C]; int32_t i1C; } R6cKeyObj;
#define R6C_NEXT(p) ((p) ? (p)->next : 0)

extern void   *a80_ctx42C8E4;              /* 0x0042C8E4 object pointer */
R6cTNode *sub_0007F300(R6cTNode *n);       /* next sibling (NULL safe) */
R6cTNode *sub_0007F320(R6cTNode *n);       /* first child (NULL safe) */
void  a6b_SetHeap(int kind, int heap);
uint32_t *a6b_Block_Init(uint32_t *buf, uint32_t size, int line, const char *file);
int   r6c_NodeRelease(R6cPart *p);                       /* 0x0007E6C0, p in EAX */
int   r6c_TreeRelease(R6cTNode *n);                      /* 0x0007E8B0 */
void  r6c_TreeFreeAll(R6cTNode *n);                      /* 0x0007F3B0 */
R6cTNode *r6c_TreeInsertAfter(R6cTNode *a, R6cTNode *b);     /* 0x0007F3F0 */
int   r6c_ListAddUnique(R6cPList *l, R6cPItem *it);      /* 0x0007EC40, l in ESI, it in EDX */
int   r6c_ListRemove(R6cPList *l, R6cPItem *it);         /* 0x0007EC90, l in EDI, it in ESI */
int   r6c_KeyNew(R6cKeyObj **out, int v);                /* 0x0007EDE0 */
void *sub_0001DAF0(R6cPart *p, int c);
void  sub_00033B30(R6cPart *p);
void *sub_0008FE10(void *a, int b, int c);
void  sub_0008F9B0(void *r);
void  sub_000830E0(R6cPList *l, R6cPItem *it);
void  sub_00053710(int heap);
void  sub_00053740(void);
char *a6b_StrCopy(void *dst, const char *s);
int   a6b_Track_Clear(A6bTrack *t);

/* ------------------------------------------------------------ collision helpers (0x7Fxxx-0x84xxx) */
typedef struct R6cE2Rec  { int32_t v; uint8_t pad[0x108 - 4]; } R6cE2Rec;
typedef struct R6cE10Rec { int32_t v; uint8_t pad[0x180 - 4]; } R6cE10Rec;
typedef struct R6cEnt8C {
    uint8_t  unk00[0x8C];
    int32_t  type;            /* +0x8C */
    uint8_t  unk90[0xC4 - 0x90];
    struct R6cEnt8C *child;   /* +0xC4 */
} R6cEnt8C;
typedef struct R6cEnt2  { uint8_t unk00[0xD4]; R6cE2Rec recs[1]; } R6cEnt2;     /* type 2 */
typedef struct R6cEnt10 { uint8_t unk00[0x17C]; R6cE10Rec recs[1]; } R6cEnt10;  /* type 10 */
typedef struct R6cBox {                    /* 0x40 bytes */
    int32_t  i00, i04;
    void    *p08, *p0C;       /* +0x08 */
    float    max[4];          /* +0x10 */
    float    min[4];          /* +0x20 */
    int32_t  i30;             /* +0x30 */
    uint8_t  unk34[0x40 - 0x34];
} R6cBox;
typedef struct R6cBItem { struct R6cBItem *next; } R6cBItem;
typedef struct R6cBNode {
    struct R6cBNode *left;    /* +0x00 */
    struct R6cBNode *right;   /* +0x04 */
    R6cBItem *items;          /* +0x08 */
} R6cBNode;
typedef struct R6cHit {
    uint8_t  unk00[4];
    struct R6cHit *next;      /* +0x04 */
    struct R6cHitOwner *owner;/* +0x08 */
} R6cHit;
typedef struct R6cHitOwner {
    uint8_t  unk00[8];
    R6cHit  *hits;            /* +0x08 */
    void    *src;             /* +0x0C */
} R6cHitOwner;
typedef struct R6cHitSrc { uint8_t unk00[0x0C]; int32_t i0C; uint8_t unk10[0x10]; uint8_t blk20[4]; } R6cHitSrc;
typedef struct R6cLink {
    void    *owner;           /* +0x00 */
    struct R6cLink *next;     /* +0x04 */
    uint8_t  unk08[8];
    int32_t  i10;             /* +0x10 */
    int32_t  kind;            /* +0x14 */
    uint8_t  unk18[4];
    void    *obj;             /* +0x1C */
    int32_t  i20;             /* +0x20 */
} R6cLink;
typedef struct R6cLinkHead { uint8_t unk00[4]; R6cLink *first; } R6cLinkHead;
typedef struct R6cColl { uint8_t unk00[8]; uint8_t flags; } R6cColl;
typedef struct R6cRes3 {
    uint8_t  unk00[0x10];
    void    *p10;             /* +0x10 */
    void    *p14;             /* +0x14 */
    void    *p18;             /* +0x18 */
} R6cRes3;
typedef struct R6cE28 {                    /* 0x28 bytes, a part list member */
    int32_t  i00, i04, i08;
    void    *h0C;             /* +0x0C */
    float    f10;             /* +0x10 */
    int32_t  i14, i18, i1C;   /* +0x14 */
    struct R6cE28 *next;      /* +0x20 */
    int32_t  i24;             /* +0x24 */
} R6cE28;
typedef struct R6cE28List { uint8_t unk00[0x0C]; int32_t count; R6cE28 *first; } R6cE28List;

extern R6cHit   *r6c_hits3ECA00;           /* 0x003ECA00 */
extern int32_t   r6c_v3ECA1C;              /* 0x003ECA1C */
extern void     *r6c_p3ECA38;              /* 0x003ECA38 */
extern R6cHitSrc *r6c_src3ECA7C;           /* 0x003ECA7C */
extern int32_t   r6c_n3ECA20;              /* 0x003ECA20 */
extern void    **r6c_out3ECA78;            /* 0x003ECA78 collected entry pointers */
extern R6cVec4   r6c_vec3EC9E8, r6c_vec3EC864;
extern int32_t   a30_g41316C, a30_g413170;
void *sub_00080A60(R6cColl *a, const R6cVec4 *b, const R6cVec4 *c);               /* c in ECX */
void *sub_000809C0(R6cColl *a, const R6cVec4 *b, const R6cVec4 *c);               /* a in EBX, c in ECX */
void  sub_00080E20(int a);
void  sub_00082140(void *a);
int   a8c_EntryFreeChain(void *p);
void *sub_001B7520(void *b, void *a);
void *sub_001B72C0(void *b, void *x);
void  sub_001AD9F0(R6cVec4 *out, const R6cVec4 *a, const R6cVec4 *b);
void  sub_001ADE90(R6cVec4 *out, const R6cVec4 *a, const R6cVec4 *b);

/* ------------------------------------------------------------ event tables (0x84xxx-0x85xxx) */
typedef struct R6cTimedObj { uint8_t unk00[4]; int32_t kind; uint8_t unk08[4]; uint32_t flags; } R6cTimedObj;
typedef struct R6cTimed { R6cTimedObj *obj; float time; } R6cTimed;
typedef struct R6cCounted { uint8_t unk00[8]; int32_t count; } R6cCounted;
typedef struct R6cEvEnt {                  /* 0x20 bytes */
    int8_t   a, b;            /* +0x00 */
    uint8_t  unk02[2];
    int32_t  flag;            /* +0x04 event flag id */
    uint8_t  unk08[0x18];
} R6cEvEnt;
typedef struct R6cEvGroup {                /* 0x20-byte header followed by count entries */
    int32_t  key;             /* +0x00 */
    int32_t  total;           /* +0x04 */
    int32_t  limit;           /* +0x08 */
    int32_t  step;            /* +0x0C */
    uint8_t  unk10[4];
    int32_t  count;           /* +0x14 */
    uint8_t  done;            /* +0x18 */
    uint8_t  unk19[0x20 - 0x19];
    R6cEvEnt ents[1];         /* +0x20 */
} R6cEvGroup;
typedef struct R6cEvSet {
    uint8_t  unk00[8];
    int32_t  count;           /* +0x08 */
    uint8_t  unk0C[4];
    uint8_t  first[1];        /* +0x10 first group */
} R6cEvSet;
typedef struct R6cItem20 { uint8_t b[0x20]; } R6cItem20;
typedef struct R6cItemSet { uint8_t unk00[8]; int32_t count; uint8_t unk0C[4]; R6cItem20 items[1]; } R6cItemSet;
typedef struct R6cSlot16 { R6cItem20 *item; int32_t i4; int32_t i8; int32_t iC; } R6cSlot16;

extern R6cCounted *r6c_timedTab;           /* 0x003ED1B0 */
extern R6cTimed   *r6c_timed;              /* 0x003ECCA8 */
extern float       a50_frameSeconds;       /* 0x0042C85C */
extern int32_t     r6c_evIdxA;             /* 0x003ED1C8 */
extern int32_t     r6c_evIdxB;             /* 0x003ED1C4 */
extern R6cEvSet   *r6c_evSet;              /* 0x003ED1CC */
extern R6cSlot16  *r6c_slots3ED1D0;        /* 0x003ED1D0 */
extern R6cItemSet *r6c_items3ED1D4;        /* 0x003ED1D4 */
int   a80_CurEntryId(void);
void  sub_00087A90(R6cEvGroup *g, int a);
int   sub_00085590(R6cEvGroup *g);   /* returns a count (ebp) */

/* ------------------------------------------------------------ event camera and streams (0x86xxx-0x87xxx) */
typedef struct R6cCamEnt {                 /* 0x20 bytes */
    int32_t  id;              /* +0x00 */
    uint8_t  unk04[0x0C];
    float    x, y, z;         /* +0x10 */
    float    yaw;             /* +0x1C */
} R6cCamEnt;
typedef struct R6cCamSet { uint8_t unk00[8]; int32_t count; uint8_t unk0C[4]; R6cCamEnt ents[1]; } R6cCamSet;
typedef struct R6cCamRec {
    uint8_t  unk00[0x10];
    float    pos[3];          /* +0x10 */
    int32_t  i1C;             /* +0x1C */
    float    dir[3];          /* +0x20 */
} R6cCamRec;
typedef struct R6cPlSub { uint8_t unk00[0xC4]; uint8_t *pC4; } R6cPlSub;
typedef struct R6cPlBody { uint8_t unk00[0x74]; float height; } R6cPlBody;   /* at +0x300 of the model */
typedef struct R6cPlayer {
    uint8_t  unk00[0x20];
    R6cPlSub *sub;            /* +0x20 */
    uint8_t  unk24[0x60 - 0x24];
    R6cVec4  pos;             /* +0x60 */
} R6cPlayer;
typedef void (*R6cFn)(void);

extern int32_t   r6c_strA3ED1F8, r6c_strB3ED1FC, r6c_strH3ED200, r6c_busy3ED204;
extern int32_t   r6c_step3ED1EC;
extern R6cCamSet *r6c_camSet3ED210;
extern int32_t   r6c_on3ED214;
extern R6cCamRec *r6c_cam3ED218;
extern int32_t   r6c_state3ED21C, r6c_v3ED220;
extern R6cVec4   r6c_target3ED224;         /* 0x003ED224 */
extern int32_t   r6c_v3ED234, r6c_v3ED238, r6c_v3ED23C, r6c_v3ED240, r6c_step3ED244, r6c_v3ED248;
extern int32_t   r6c_v3ED24C, r6c_v3ED250, r6c_v3ED258, r6c_v3ED25C, r6c_v3ED26C, r6c_v3ED270, r6c_v3ED274;
extern R6cEvGroup *r6c_grp3ED254;
extern float     r6c_f3ED260[3];           /* 0x003ED260 */
extern void    (*r6c_jumpFns[2])(int i);   /* 0x002E03BC */
extern R6cFn     r6c_stateFns[];           /* 0x002E03C4 indexed by r6c_state3ED21C */
extern R6cFn     r6c_initFns[6];           /* 0x002E03D8 */
extern R6cFn     r6c_tickFns[6];           /* 0x002E03F0 */
void  sub_000488C0(int a, int b, int c);
int   sub_00047B10(int h);
void  sub_00047B30(int h);
int   sub_00047B50(int h);
void  sub_00047B70(int h);
void  sub_000487F0(int a, int b, int c);
int   sub_00048820(int a, int b, int c);
void  sub_00048860(int a, int b, int c);
int   sub_00048890(int a, int b, int c);
int   sub_00057EA0(void);
void  sub_000867F0(int a);
void  sub_000A57C0(int id, R6cVec4 *pos, R6cVec4 *rot);
int   sub_00085390(int a);
int   sub_00086230(int a, int b, int c);
void  sub_000D2A50(PlayerStats *s, int a);
void  sub_000EE0C0(void);
void  sub_000DE330(int a);
void  sub_000EDA10(void);
void  r6c_EvJump(int i);                   /* 0x00087030 */
void  r6c_CamFollowPlayer(void);           /* 0x00087450 */

/* ------------------------------------------------------------ event scenes (0x87Dxx-0x888xx) */
typedef struct R6cScnData { uint8_t unk00[0x10]; R6cVec4 pos; int32_t i20; } R6cScnData;
typedef struct R6cScn {
    void   (*enter)(int a);   /* +0x00 */
    void   (*leave)(int a);   /* +0x04 */
    uint8_t  unk08[4];
    R6cScnData **data;        /* +0x0C */
    int32_t  state;           /* +0x10 */
    uint32_t flags;           /* +0x14 bit 0 active, bit 1 done, bit 2 finish */
} R6cScn;
typedef struct R6cRec18 { int32_t a, b; uint8_t unk08[0x10]; } R6cRec18;
extern int32_t  r6c_v3ED510, r6c_v3ED514, a80_curMode;
extern R6cRec18 r6c_recs2E0690[9];         /* 0x002E0690 */
extern uint8_t  ae0_obj3E1270[];           /* 0x003E1270 */
void  sub_000856F0(void *a);
void  sub_00085820(void *a);
void  sub_00085930(void *a);
int   a80_Get3ED238(void);
void  a80_StatePause(void);
void  a80_StateResume(void);
int   sub_000EDAD0(int a, int b);
int   sub_00085110(int n);
int   sub_000EDA50(void);
void  sub_00019000(void *o, int a);
void  sub_000ED4C0(int a);
int   sub_000ED520(int a, int b);
void  sub_000ED5D0(int a);

#endif
