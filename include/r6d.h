#ifndef R6D_H
#define R6D_H
#include "oogie.h"
#include "a60.h"
#include "r6c.h"
#include <string.h>
#if defined(_M_IX86)
#include <intrin.h>
#endif
/* Area r6d: functions (stack and register arguments) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6d.csv. */

/* ------------------------------------------------------------ text boxes (0x76xxx-0x77xxx) */
void *sub_000768D0(R6cText *t, void *ctx, void *fn, int n);          /* t in EDI; returns ctx */
void  sub_00076E30(R6cText *t, int colour, void *ctx, int n);        /* t=EAX colour=ESI ctx=EBX */
void  sub_00076FA0(R6cText *t, int colour, void *ctx, int n);        /* t=EAX colour=ESI */
void  sub_00038060(int v);
void  sub_000385B0(void);
void *r6d_TextDraw(void *ctx, R6cText *t);                           /* 0x000770B0 */

/* ------------------------------------------------------------ sound channels (0x771xx) */
/* Channel flag word at 0x003E69C0 (a60_chFlags). */
typedef struct R6dChFlags {
    uint32_t mode    : 2;     /* bits 0-1 */
    uint32_t unk2    : 4;
    uint32_t audible : 1;     /* bit 6 */
    uint32_t rest    : 25;
} R6dChFlags;

/* ------------------------------------------------------------ shop menu (0x60xxx-0x61xxx) */
extern int32_t r6d_menuAnim2DDB00;      /* 0x002DDB00 */
extern int32_t r6d_prices[];            /* 0x002DDA20 shop prices by item id */
extern int32_t adc_413178;              /* 0x00413178 discount flag */
void  a60_TextClear(void *t);
void  a60_FlagsClear(void *t, int bits);
int   sub_0003FA70(int a, int b, int c, float d, float e);
void  sub_0003FCB0(void *anim, int item);
int   sub_0003FBD0(int a, void *anim);
void  sub_0003FCE0(void *anim);
int   sub_000D1E10(PlayerStats *s, int index, int delta);
void  sub_000D9AB0(int id);
void  sub_00023D80(int a, int b);
int   sub_00060BF0(int v);              /* v in EAX */
int   sub_0005FFB0(int v);
void  sub_000601E0(void);
void  sub_000615F0(void);
void  sub_00061290(void);
void  sub_00060300(void);
int   r6d_ItemPrice(int id);            /* 0x00060B20 */
extern float   r6d_timer3E6100;         /* 0x003E6100 */
extern int32_t a60_v3E60D8, a60_v3E60DC, a60_v3E60E0;
void  a60_StepByFrame(float *v, int dir);
void  sub_00024D30(int a, int b);
void  sub_000243B0(int a, int b);

/* ------------------------------------------------------------ status screen (0x65xxx) */
/* Texture set records at 0x002DDD50 (0x30 bytes each). */
typedef struct R6dTexSet {
    void   **big[4];          /* +0x00 */
    void   **small[3];        /* +0x10 */
    uint8_t  unk1C[0x30 - 0x1C];
} R6dTexSet;
extern R6dTexSet r6d_texSets[];         /* 0x002DDD50 */
extern int32_t   r6d_texSet3E6538;      /* 0x003E6538 */
void  sub_00053ED0(void *img, void *dst);

extern int32_t r6d_iconSlot26DC68[];    /* 0x0026DC68 */
extern uint8_t r6d_icons42970C[];       /* 0x0042970C */
extern uint8_t r6d_iconRows429718[][20];/* 0x00429718 */
extern int32_t r6d_g429708, r6d_g428F8C, r6d_g428F90;

/* Part of the work block at 0x0042C5E8 used by the status texts. */
typedef struct R6dWork {
    uint8_t  unk00000[0xF91E8];
    uint8_t  anim[8];         /* +0xF91E8 */
    void    *text;            /* +0xF91F0 text handle */
    uint8_t  unkF91F4[0xF9208 - 0xF91F4];
    int32_t  msgTables[2];    /* +0xF9208 */
} R6dWork;
#define R6D_WORK ((R6dWork *)a60_work42C5E8)
extern int32_t r6d_statusAnims2DE3CC[]; /* 0x002DE3CC */
void  r6d_StatusShowText(int i, int id);  /* 0x00065E50, i in ESI */

/* ------------------------------------------------------------ pause screens (0x6Bxxx-0x72xxx) */
extern int32_t r6d_chapter4297F0, r6d_stage4297F4, r6d_area4297F8;
extern int32_t r6d_pos3E65E8[];         /* 0x003E65E8 */
extern void   *r6d_areaImages2DE3D8[];  /* 0x002DE3D8 */
extern void   *r6d_img2DE458, *r6d_img2DE45C, *r6d_img2DE460;
extern int32_t r6d_g3E6618;             /* 0x003E6618 */
void  sub_000DFD40(int32_t *chapter, int32_t *stage);
int   sub_0006B5E0(int chapter, int stage, int32_t *out);   /* ECX=chapter EAX=stage ESI=out */
void  sub_00053E20(void *img, void *dst);
void  sub_00026850(void);
int   sub_00038070(int v);
void  a60_Release659A0(void);
void  a60_Release6A340(void);
void  a60_ScreenRelease62200(void);
void  a60_Release72FD0(void);
void  a60_Release6DBB0(void);
int   a5b_GetVideoMode(void);
int   sub_00066050(int v);
int   sub_0006A3A0(int v);
int   sub_000622A0(int v);
int   a60_Dispatch74700(int v);
int   sub_0006EA30(int v);
int   r6d_PausePageValue(int v);        /* 0x0006C160, v in EAX */
int   sub_0006C750(int v);
void  sub_00070790(void);
void  sub_00070E90(void);
void  sub_00071230(void);
void  sub_00071400(void);
void  sub_00071940(void);
void  sub_00071C30(void);
void  sub_001A78F0(int a, int b, int c, int d, int e, int f, int g, int h, int i,
                   int j, int k, int l, int m);
/* Menu with four draw-order slots at +0x24. */
typedef struct R6dOrder {
    uint8_t  unk00[0x24];
    int32_t  o[4];            /* +0x24 */
} R6dOrder;
extern uint8_t r6d_b428F84;             /* 0x00428F84 */
extern int32_t r6d_h3E6954;             /* 0x003E6954 */
extern int32_t r6d_g42A818, r6d_g42A824;
extern int8_t  r6d_counts2DF390[][12];  /* 0x002DF390 per video mode */

/* Model with a part array (types 1 and 5 use different part records). */
typedef struct R6dModel {
    uint8_t  unk00[0x8C];
    int32_t  type;            /* +0x8C */
    uint8_t  unk90[0xC0 - 0x90];
    int32_t  count;           /* +0xC0 */
    void    *parts;           /* +0xC4 */
} R6dModel;
typedef struct R6dPart5 {     /* 0x100 bytes */
    uint8_t  unk00[0xC4];
    int32_t  active;          /* +0xC4 */
    uint8_t  unkC8[8];
    int32_t  key;             /* +0xD0 */
    uint8_t  unkD4[0x10];
    int32_t  uvA[2];          /* +0xE4 */
    int32_t  uvB[2];          /* +0xEC */
    uint8_t  unkF4[0x0C];
} R6dPart5;
typedef struct R6dPart1 {     /* 0x108 bytes */
    uint8_t  unk00[0xC4];
    int32_t  active;          /* +0xC4 */
    uint8_t  unkC8[0x10];
    int32_t  key;             /* +0xD8 */
    uint8_t  unkDC[0x10];
    int32_t  uvA[2];          /* +0xEC */
    int32_t  uvB[2];          /* +0xF4 */
    uint8_t  unkFC[0x0C];
} R6dPart1;
/* ------------------------------------------------------------ movies and endings (0x78xxx-0x79xxx) */
uint16_t r6c_TextCharAt(const uint8_t *s, unsigned n);
void *r1c_PagedElem(int i);
void  r1c_QueueKick(int arg);
void  sub_000325A0(int on);
void  sub_000487F0(int a, int b, int c);
int   sub_00048820(int a, int b, int c);
void  sub_00048860(int a, int b, int c);
int   sub_00048890(int a, int b, int c);
int   sub_0004ECC0(int a);
int   sub_0004ECD0(int a);
int   sub_0004ECE0(int a);
int   sub_0004ECF0(int a);
int   sub_0004ED00(int a);
int   sub_0004ED20(int a);
int   sub_0004ED40(int a);
void  sub_0019FCF0(int a, int b, int c, int d, int e, int f);
void  sub_001A0D30(int a, int b);
void  sub_001A8A70(int a);
int   sub_001A8A40(void);
int   sub_001A8A90(void);
void  sub_00077EF0(void);
void  sub_000408E0(int a);
void  sub_0019D8A0(int a);
void  sub_0019BE90(int v);
void  sub_00048A60(void);
void  sub_00048110(int a);
void  sub_00048370(void);
void  sub_000481B0(int a);
void  sub_000483A0(int a);
extern uint8_t r6d_b413147;             /* 0x00413147 */
extern int32_t r6d_g42CA24;             /* 0x0042CA24 */
extern int32_t a9b_g413168, a9b_g413164;
extern void *const r6d_msgTables26F32C[];   /* 0x0026F32C per video mode (message table addresses) */
void *r6d_MsgGet(void *table, int id);  /* 0x0003FA70 called with two arguments */
typedef struct R6dGlyph { uint8_t unk0[6]; uint16_t width; } R6dGlyph;   /* +0x06 width */
typedef struct R6dGlyphSize { int16_t w; int16_t h; } R6dGlyphSize;
void *sub_000380A0(void *ctx, int x, int y, int z, R6dGlyphSize *sz, int colour,
                   float sx, float sy, int ch);
void *r6d_DrawString(int x, void *ctx, int y, int colour, const uint8_t *s);  /* 0x00079590, x=EAX ctx=ECX */
/* ------------------------------------------------------------ scene nodes (0x7Axxx-0x7Dxxx) */
struct R6dNamedNode;
typedef struct R6dNodeList {
    int32_t  count;                  /* +0x00 */
    struct R6dNamedNode *head;       /* +0x04 */
    struct R6dNamedNode *tail;       /* +0x08 */
} R6dNodeList;
typedef struct R6dNamedNode {        /* 0x84 bytes */
    struct R6dNamedNode *next;       /* +0x00 */
    struct R6dNamedNode *prev;       /* +0x04 */
    R6dNodeList *list;               /* +0x08 */
    int32_t  f0C, f10, f14, f18, f1C, f20, f24;
    int32_t  a;                      /* +0x28 */
    int32_t  b;                      /* +0x2C */
    int32_t  f30, f34, f38;
    uint8_t  unk3C[4];
    char     name[0x40];             /* +0x40 */
    int32_t  f80;                    /* +0x80 */
} R6dNamedNode;
typedef struct R6dNodeOwner {
    uint8_t  unk000[0x1F8];
    R6dNodeList nodes;               /* +0x1F8 */
} R6dNodeOwner;
typedef struct R6dRes { void *data; int32_t size; } R6dRes;
typedef struct R6dScene {
    uint8_t  unk000[0x48];
    R6dRes  *res[6];                 /* +0x48 */
    uint8_t  unk060[0x200 - 0x60];
    void    *child;                  /* +0x200 */
} R6dScene;
void  sub_0007AEE0(void *child);
void  r6b_Free81B80(void *p);
void  sub_000F5D40(void *dst, const void *src);
/* ------------------------------------------------------------ characters and strings (0x7Dxxx-0x7Exxx) */
void *sub_001C7DB0(void *dst, const void *src, unsigned n);   /* CRT copy, cdecl */
typedef struct R6dChar {
    uint8_t  unk000[0x12C];
    void    *effects;                /* +0x12C */
} R6dChar;
typedef struct R6dCharObj {
    uint8_t  unk00[0x5C];
    R6dChar *chr;                    /* +0x5C */
} R6dCharObj;
void *sub_0008FDC0(int a, int b, int c);
void *r6b_FwdHolderData(void *h);
void  r6b_ResLoad(void *r);
void *r6b_ResLoaded(void *r);
void *r6b_ResTableEntry(void *r);
void  sub_0007E720(void *entry, R6dChar *chr);   /* chr in EBX */
int   r6d_TableFirstFree(void *t, void **out);  /* 0x0007E680, t in EDI */
void *a12_Table_Get(void *t, int i);
extern const char a6b_srcYCharacter[];  /* 0x0026F730 */
void *a6b_AllocAt(int heap, int align, int size, int line, const char *file);
/* ------------------------------------------------------------ scene box tree (0x82xxx) */
typedef struct R6dTreeOwner {
    uint8_t  unk00[0x0C];
    uint8_t *parts;                  /* +0x0C records of 0x50 bytes, +0x28 = offset */
    uint8_t  unk10[4];
    uint8_t  flags;                  /* +0x14 bit 0 = hidden */
} R6dTreeOwner;
typedef struct R6dTreeItem {
    struct R6dTreeItem *next;        /* +0x00 */
    uint8_t  unk04[4];
    R6dTreeOwner *owner;             /* +0x08 */
    int32_t  index;                  /* +0x0C */
} R6dTreeItem;
typedef struct R6dTree {
    struct R6dTree *left;            /* +0x00 */
    struct R6dTree *right;           /* +0x04 */
    R6dTreeItem *items;              /* +0x08 */
    uint8_t  unk0C[0x20 - 0x0C];
    R6cVec4  boxMin;                 /* +0x20 */
    R6cVec4  boxMax;                 /* +0x30 */
} R6dTree;
int   r6c_BoxBehind(const R6cVec4 *a, const R6cVec4 *b, const R6cVec4 *c, const R6cVec4 *d);
typedef struct R6dCountTable { uint8_t unk00[8]; int32_t count; } R6dCountTable;   /* +0x08 */
extern void   *a80_g3ED1B0;             /* 0x003ED1B0 count table */
extern void   *a8c_g3ECCA8;             /* 0x003ECCA8 */
/* ------------------------------------------------------------ boxes, texture headers, sound slots (0x82xxx-0x86xxx) */
typedef struct R6dIVec4 { int32_t v[4]; } R6dIVec4;    /* float vector copied as raw words */
typedef struct R6dTexHeader {
    uint32_t magic;                  /* +0x00 'P2IG' */
    int16_t  version;                /* +0x04 0x60 */
    uint8_t  unk06[6];
    int16_t  unkC, unkE;             /* +0x0C */
    uint32_t name[2];                /* +0x10 up to 8 characters */
    int32_t  f18, f1C;               /* +0x18 */
    int16_t  log2W, log2H;           /* +0x20 */
    uint8_t  b24, b25;               /* +0x24 */
    uint8_t  unk26[0x40 - 0x26];
    int32_t  f40[16];                /* +0x40 */
} R6dTexHeader;
typedef struct R6dSoundDef {
    uint8_t  unk00[5];
    int8_t   mode;                   /* +0x05 */
    uint8_t  kind;                   /* +0x06 */
    uint8_t  unk07;
    int32_t  group;                  /* +0x08 */
    int32_t  event;                  /* +0x0C */
} R6dSoundDef;
typedef struct R6dSound {            /* 0x10 bytes, also the slot array at 0x003ED1D0 */
    R6dSoundDef *def;                /* +0x00 */
    int32_t  state;                  /* +0x04 */
    int32_t  handle;                 /* +0x08 */
    int32_t  unk0C;
} R6dSound;
extern void   *a80_g3ED1D0, *a80_g3ED1D4;   /* sound array, count table */
int   sub_000A79B0(int h);
void  sub_000A7950(int h);
/* ------------------------------------------------------------ streaming jobs (0x867xx-0x86Exx) */
typedef struct R6dStreamEntry {     /* followed by n 8-byte records */
    int32_t  event;                  /* +0x00 */
    int32_t  n;                      /* +0x04 */
} R6dStreamEntry;
typedef struct R6dStreamSet {
    uint8_t  unk00[8];
    int32_t  count;                  /* +0x08 */
    uint8_t  unk0C[4];
    R6dStreamEntry entries[1];       /* +0x10 variable-sized */
} R6dStreamSet;
extern int32_t a8c_handles3ED1DC[3];    /* 0x003ED1DC */
extern void   *a80_g3ED208;             /* 0x003ED208 current stream set */
extern int32_t a8c_g3ED1F0, a8c_g3ED1E8, a8c_g3ED1D8;
extern R6dStreamEntry *a8c_g3ED1F4;     /* 0x003ED1F4 current stream entry */
extern int32_t r6c_strA3ED1F8, r6c_strB3ED1FC, r6c_strH3ED200;
int   Job_OnJobThread(void);
int   sub_000480F0(int h);
void  sub_00047A80(int h);
int   sub_00047B10(int h);
void  sub_00047B30(int h);
int   sub_00047B50(int h);
void  sub_000865F0(void);
void  sub_000862A0(void *e);
void  sub_00086460(void *e);
void  sub_00086850(int a);
void  sub_000CE8F0(void);
void  r6c_StreamPlayWait(int a);
void  r6c_StreamSwitchWait(int a);
void  r6d_StreamsStop(int unused);      /* 0x000867F0 */
/* ------------------------------------------------------------ cutscene audio (0x88xxx) */
typedef struct R6dCsData {
    uint8_t  a[0x10];                /* +0x00 */
    uint8_t  a10[0x10];              /* +0x10 */
    int32_t  a20;                    /* +0x20 */
    uint8_t  b24[0x10];              /* +0x24 */
    uint8_t  b34[0x10];              /* +0x34 */
    int32_t  b44;                    /* +0x44 */
} R6dCsData;
typedef struct R6dCsEvent {
    uint8_t  unk00[0x0C];
    R6dCsData **data;                /* +0x0C */
    int32_t  state;                  /* +0x10 0 / 10 / 20 */
    uint32_t flags;                  /* +0x14 bit 0 active, bit 1 done, bit 2 finish */
} R6dCsEvent;
extern int32_t a30_g41316C, a30_g413170;
void  sub_00053710(int a);
void  sub_00053740(void);
void  sub_000ED4C0(int t);
int   sub_000ED520(int t, int c);
void  sub_000ED590(int t, int c);
void  sub_000ED5D0(int t);
void  sub_000488C0(int a, int b, int c);
void  sub_00033BF0(int t, int v);
int   sub_000EE240(void);
void  sub_000ED600(int t);
void  sub_000ED560(int t);
void  sub_000ED4F0(int t);
void  sub_00047B70(int v);
int   sub_00047B90(int v);
void  sub_000D2A50(PlayerStats *s, int on);
void  sub_000DE330(int on);
void  sub_000ED630(int t, int cue, void *a, void *b, int c);
int   sub_000EDAD0(int t, int c);
void  sub_000488F0(int a, int b);
int   sub_00048910(int a, int b);
void  sub_00048940(int a, int b);
int   sub_00048970(int a, int b);
/* ------------------------------------------------------------ event scenes and stage objects (0x89xxx) */
extern R6cScn  r6d_scenes2E0680[];      /* 0x002E0680, 0x18-byte scene records */
extern int32_t a80_curMode;             /* 0x003ED51C */
int   r6c_ScnLeaveStep(R6cScn *s);      /* 0x00088240, s in ESI */
typedef struct R6dMaterial {
    uint8_t  unk00[0x28];
    int32_t  tex;                    /* +0x28 */
} R6dMaterial;
typedef struct R6dStateBlk { int32_t w[0x2C]; } R6dStateBlk;    /* 0xB0 bytes */
typedef struct R6dStageExt {
    uint8_t  unk00[4];
    R6cTintBlk tint;                 /* +0x04 */
    R6dMaterial *material;           /* +0x1C */
    uint8_t  unk20[4];
    uint8_t  recs[0x74 - 0x24];      /* +0x24 */
    uint8_t  holder[4];              /* +0x74 */
} R6dStageExt;
typedef struct R6dStageObj {
    uint8_t  unk00[0x1C];
    void    *nodes;                  /* +0x1C */
    uint8_t  unk20[0x48 - 0x20];
    int32_t  handle;                 /* +0x48 */
    R6dStageExt *ext;                /* +0x4C */
} R6dStageObj;
void *sub_0008B290(void *n, int a, int b);
void *a6b_Node_Next(void *n);
void  a8b_RefDec(void *o);
void  a8b_RefInc(void *o);
void  sub_0003E200(int a, int b);
void  sub_000893C0(R6dStageObj *o);
void  sub_000AD090(int a, int b);
void  r6b_ObjDestroy(int h);
unsigned r6b_HolderCountSlots(void *h);
void *r6b_HolderData(void *h);
void  sub_000375A0(void);
void  sub_000376D0(void *p);
void *r6b_HolderBlk(void *h);
void *sub_000390A0(void);
void  sub_00037BB0(int a, int b);
void  r6b_HolderFree(void *h);
void  r6b_FreeRecs4(void *p);
void  sub_0007AB10(void *obj, void *tint);
void  sub_0008BCC0(void *p);
void  sub_000360E0(void);
extern void   *a80_ctx42C8E4;           /* 0x0042C8E4 context object */
/* ------------------------------------------------------------ stage links (0x8Axxx) */
typedef struct R6dLinkObj {
    uint8_t  unk00[0x1C];
    struct R6dLinkV *link;           /* +0x1C */
} R6dLinkObj;
typedef struct R6dLinkV {
    int32_t  head;                   /* +0x00 */
    uint8_t  unk04[0x0C];
    int32_t  a, b, c, key, slot;     /* +0x10 .. +0x20 */
} R6dLink;
typedef struct R6dRefRec { uint8_t unk00[0x20]; int32_t id; } R6dRefRec;   /* +0x20 */
typedef struct R6dLinkOwner {
    uint8_t  unk00[0x5C];
    R6dChar *chr;                    /* +0x5C */
} R6dLinkOwner;
typedef struct R6dLinkTarget {
    uint8_t  unk000[0x28];
    R6dLinkOwner *owner;             /* +0x028 */
    uint8_t  unk02C[0x124 - 0x2C];
    int32_t  sound;                  /* +0x124 */
} R6dLinkTarget;
typedef struct R6dLinkSrc {
    uint8_t  unk00[0x10];
    int32_t  value;                  /* +0x10 */
    uint8_t  unk14[0x0C];
    int32_t  id;                     /* +0x20 */
} R6dLinkSrc;
typedef struct R6dLinkNode {
    uint8_t  unk00[0x24];
    uint32_t flags;                  /* +0x24 */
} R6dLinkNode;
R6dRefRec *a80_CurRefX0C(int a, int b, int c);
void *sub_0008E5E0(int id);
void *sub_00033DC0(void *list, int key);
void  sub_00033DA0(void *p, int slot);
void *sub_0008E1B0(void *t);
void  sub_00033B30(void *s);
int   sub_0008B320(R6dLinkObj *x, R6dLinkObj *y);
void *sub_0008C3C0(int id, int type);
void *sub_0008C6E0(int type, int a);
int   sub_00089540(R6dLinkSrc *p, R6dLinkNode *n);
void  r6b_NodeUnlinkRelease2(void *n);
void  sub_0008B3B0(R6dLink *l, R6dLinkNode *n);
/* END */
#endif
