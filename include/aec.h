/* Area aec (third pass over 0x000E0000-0x000EFFFF): small game helpers. Names inferred. */
#ifndef AEC_H
#define AEC_H
#include "oogie.h"
#include "shared_decls.h"
#include "acb.h"

/* Target of a 0x28-byte slot record: sub-object at +0x30, float at +0x64. */
typedef struct AecSlotSub { uint8_t unk00[0x14]; void *v14; } AecSlotSub;
typedef struct AecSlotTarget {
    uint8_t     unk00[0x30];
    AecSlotSub *o30;          /* +0x30 */
    uint8_t     unk34[0x64 - 0x34];
    float       f64;          /* +0x64 */
} AecSlotTarget;
typedef struct AecSlot {
    AecSlotTarget *target;    /* +0x00 */
    uint8_t  unk04[0x18 - 4];
    float    f18;             /* +0x18 */
    uint8_t  unk1C[0x28 - 0x1C];
} AecSlot;

/* Large stage/actor object (Hypothesis): fields used by these helpers. */
typedef struct AecObj {
    int32_t  v00;             /* +0x000 */
    uint8_t  unk004[0x2FC - 4];
    int32_t  v2FC;            /* +0x2FC handle, -1 = none */
    uint8_t  unk300[0x314 - 0x300];
    int32_t  v314;            /* +0x314 */
    uint8_t  unk318[0x32C - 0x318];
    int32_t  v32C;            /* +0x32C */
    void    *a330[0x20];      /* +0x330 */
    void    *a3B0[0x20];      /* +0x3B0 */
    uint8_t  unk430[0x86C - 0x430];
    AecSlot  slots[1];        /* +0x86C */
} AecObj;

/* Script-style command record: index at +0x0C and more args after it. */
typedef struct AecCmd {
    uint8_t  unk00[0x0C];
    int32_t  vC;              /* +0x0C */
    int32_t  v10;             /* +0x10 */
    int32_t  v14;             /* +0x14 */
    int32_t  v18;             /* +0x18 */
    int32_t  v1C;             /* +0x1C */
} AecCmd;
typedef struct AecCmdW {
    uint8_t  unk00[0x0C];
    int16_t  wC;              /* +0x0C */
    int16_t  wE;              /* +0x0E */
    uint8_t  data[4];         /* +0x10 */
} AecCmdW;

/* Linked list node with a payload record at +0x0C. */
typedef struct AecKey { uint8_t unk00[4]; int32_t kind; int32_t sub; } AecKey;
typedef struct AecNode { struct AecNode *next; uint8_t unk04[8]; void *payload; } AecNode;

/* Component kind 0x0D: flags at +0x10, hit callback at +0x2C, two values at +0x34. */
typedef struct AecComp0D {
    uint8_t  unk00[0x10];
    int32_t  flags;           /* +0x10 */
    uint8_t  unk14[0x2C - 0x14];
    int    (*onHit)(void *obj, void *target); /* +0x2C */
    uint8_t  unk30[4];
    int32_t  vals[2];         /* +0x34 */
} AecComp0D;
/* Component kind 0x0C: update callback at +0x14. */
typedef struct AecComp0C { uint8_t unk00[0x14]; void (*update)(void *obj); } AecComp0C;
/* Component kind 5 fields used here. */
typedef struct AecComp5 {
    uint8_t  unk00[0x10C];
    int32_t  v10C;            /* +0x10C */
    uint8_t  unk110[0x154 - 0x110];
    int32_t  v154;            /* +0x154 */
} AecComp5;

/* 0x1C-byte record table at 0x003F59F8 (5 entries). */
typedef struct AecRec1C { int32_t v00, v04, v08, v0C, v10; uint8_t unk14[8]; } AecRec1C;
extern AecRec1C aec_recs1C[5];      /* 0x003F59F8 */

typedef struct AecCtx { uint8_t unk00[0x1E8]; void *v1E8; } AecCtx;
extern AecCtx *aec_ctx42C8E4;       /* 0x0042C8E4 */
extern float   aec_fps42C964;       /* 0x0042C964 */
extern float   aec_slotTimeAdd;     /* 0x00317D7C (24.0) */
extern void   *aec_3F0744;          /* 0x003F0744 */
extern int     aec_3F0A84;          /* 0x003F0A84 */
extern uint8_t aec_413140;          /* 0x00413140 */
extern uint8_t aec_413142;          /* 0x00413142 */
extern int     aec_3EDD20;          /* 0x003EDD20 */
extern int     aec_3F118C;          /* 0x003F118C */
extern int     aec_3F49D0;          /* 0x003F49D0 */
extern int     aec_3F49D4;          /* 0x003F49D4 */
extern AecNode *aec_list3F59C4;     /* 0x003F59C4 */
extern int     aec_3F59D0, aec_3F59D4, aec_3F59D8, aec_3F59DC, aec_3F59E0,
               aec_3F59E4, aec_3F59E8, aec_3F59EC, aec_3F59F0;
extern int     aec_3F5DB0;          /* 0x003F5DB0 */
extern AecNode *aec_list3F5DC4;     /* 0x003F5DC4 */
typedef int (*AecSlotFn)(void *rec, int arg);
extern AecSlotFn aec_slotFns[];     /* 0x00317C50 */
extern int    *aec_tbl31852C[7];    /* 0x0031852C */
extern int    *aec_tbl318548[7];    /* 0x00318548 */
extern int    *aec_tbl318564[7];    /* 0x00318564 */

void  sub_0019A9D0(int h);
int   sub_00048510(int a);
void  sub_000E9950(int a, int b);
void  sub_000E1F60(AecObj *o, int i, int f);
void *sub_0001D080(void *a, int b, int c);
void  sub_000E9B00(void);
int   sub_000E0C80(int a);
int   sub_000E0CD0(int b);
int   sub_000E0CF0(int a);
int   sub_000E0D30(int b);
void  sub_000E0A80(AecObj *o, int k, int a, int b, int c);
int sub_000E3EB0(int a, int b, int c, int d, int e);
void  sub_000E0840(int a, int b, void *c);
void  sub_000CEEA0(void);
void  sub_000CEF00(void);
void  sub_000F6F00(int *p);
void  sub_001060B0(int *p);
void  sub_000E1350(AecObj *o, int a, void *b, int c);
void  sub_000E1520(AecObj *o, int a, int b);
void  sub_000EC670(void *p);
int sub_000D2A00(int a);
void  sub_000E4950(void *a, float f, int b, int c, int d);
void  sub_000E1C80(void *a, float f);
void  sub_0012D600(int a);
void  sub_000FE5A0(void);
void  sub_001002E0(void);
void  sub_000FBCA0(void);
void  sub_000F4120(void);
void  sub_000F4160(void);
void  sub_000F4190(void);
void  sub_001790F0(void);
void  sub_00179140(void);
void  sub_0017FFB0(int h);
int   sub_00034AF0(int a, int b);
void  sub_000ECB60(void);
void  sub_0003D8C0(void *p);
void  sub_0003D860(void *p);
int   sub_000EE1B0(int i);
int   sub_000EE470(int a, int b, int c, float f, int d);

/* Object initialised by 0x000EE270: three callbacks and zeroed state. */
typedef void (*AecCb)();
typedef struct AecCbObj {
    uint8_t unk00[0x10];
    int32_t v10, v14;
    float   f18, f1C;
    int32_t v20;
    AecCb   cb24, cb28, cb2C;
    int32_t v30, v34, v38;
} AecCbObj;
typedef struct AecEC { uint8_t unk00[0xEC]; int32_t vEC; } AecEC;

#endif
