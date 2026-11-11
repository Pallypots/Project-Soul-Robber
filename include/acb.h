/* Area acb (second pass over 0x000C0000-0x000FFFFF): boss/hit helpers. Names inferred. */
#ifndef ACB_H
#define ACB_H
#include "oogie.h"

/* Object carrying a flag word at +0x10 (Hypothesis: boss/actor object). */
typedef struct AcbFlagObj {
    uint8_t  unk00[0x10];
    uint32_t flags;           /* +0x10 */
} AcbFlagObj;

/* Component of kind 5 returned by sub_0001D960 (boss state component; Hypothesis). */
typedef struct AcbBossComp {
    uint8_t  unk00[0x50];
    int32_t  v50;             /* +0x50 */
    uint8_t  unk54[0x5C - 0x54];
    float    f5C;             /* +0x5C */
    int32_t  v60;             /* +0x60 */
    uint8_t  unk64[0x80 - 0x64];
    int32_t  v80;             /* +0x80 */
    float    f84;             /* +0x84 */
    float    f88;             /* +0x88 */
} AcbBossComp;

/* State machine object: handler table indexed by state, timer. */
typedef void (*AcbStateFn)(void *ctx, struct AcbStateObj *o);
typedef struct AcbStateObj {
    uint8_t     unk00[0x68];
    float       timer;        /* +0x68 */
    int32_t     state;        /* +0x6C */
    uint8_t     unk70[0x78 - 0x70];
    AcbStateFn *handlers;     /* +0x78 */
} AcbStateObj;

/* Group with records of 0x150 bytes starting at +0x30. */
typedef struct AcbSlotTarget {
    uint8_t  unk00[8];
    int32_t  v08;             /* +0x08 */
} AcbSlotTarget;
typedef struct AcbSlot {
    AcbSlotTarget *target;    /* +0x00 */
    uint8_t  unk04[0x150 - 4];
} AcbSlot;
typedef struct AcbGroup {
    uint8_t  unk00[8];
    int32_t  kind;            /* +0x08 */
    uint8_t  unk0C[0x30 - 0x0C];
    AcbSlot  slots[1];        /* +0x30 */
} AcbGroup;

/* Global boss manager at 0x003F610C. */
typedef struct AcbBossMgr {
    uint8_t  unk00[0x54];
    float    f54;             /* +0x54 */
    uint8_t  unk58[0x8C - 0x58];
    void    *sub8C;           /* +0x8C */
    uint8_t  unk90[0xA8 - 0x90];
    int16_t  wA8;             /* +0xA8 */
    int16_t  wAA;             /* +0xAA */
    uint8_t  unkAC[0xB0 - 0xAC];
    int16_t  wB0;             /* +0xB0 */
    uint8_t  unkB2[0x100 - 0xB2];
    int32_t  v100;            /* +0x100 */
    int32_t  v104;            /* +0x104 */
} AcbBossMgr;

extern AcbBossMgr *g_acb_bossMgr;    /* 0x003F610C */
extern void       *g_acb_bossAux;    /* 0x003F6110 */
extern float       a50_frameSeconds; /* 0x0042C85C */

void *sub_0001D960(void *obj, int kind);
int   sub_0019BE60(int k);
void  sub_00053880(void *p);
int   sub_000F3140(int kind);
void  sub_000F3D10(void *a, void *b, int c);

void  sub_00180930(void);
void  sub_00181D20(void);
void  sub_0017D590(void);
AcbBossMgr *sub_000FE3D0(void);
void  sub_000F3BF0(void *boss, int dmg, int flag);
void  sub_00048AF0(int id);
void  sub_000A34B0(int a, int b, int c);
void  sub_0017C460(int on);
void  sub_00183320(int on);
int   sub_000FE630(int v);
int   sub_00100370(int v);
int   sub_000FBD20(int v);
void  sub_00174540(void);
void  sub_00166DD0(void);

typedef void (*AcbVoidFn)(void);
extern AcbVoidFn g_acb_hook;       /* 0x003F5A90 */
extern int       g_acb_hookArg;    /* 0x003F5B98 */
extern float     g_acb_3F4B38;     /* 0x003F4B38 */
extern int       g_acb_3F57BC;     /* 0x003F57BC */
extern void     *g_acb_3F60F0;     /* 0x003F60F0 */

/* Object with a float at +0x10C. */
typedef struct AcbF10C { uint8_t unk00[0x10C]; float f10C; } AcbF10C;

/* 32-byte record table pointed to by 0x003F0740. */
typedef struct AcbRec32 { int32_t v00; int32_t v04; uint8_t unk08[0x18]; } AcbRec32;
typedef struct AcbTableHdr { uint8_t unk00[0x58]; int32_t v58; } AcbTableHdr;
extern void *g_acb_table;          /* 0x003F0740 */
extern int   g_acb_3EDD24;         /* 0x003EDD24 */
extern int   g_acb_3EDD38;         /* 0x003EDD38 */
extern int   g_acb_3F0748;         /* 0x003F0748 */
extern int   g_acb_3F074C;         /* 0x003F074C */
extern int   g_acb_3F0758;         /* 0x003F0758 */
extern int   g_acb_3F0A78;         /* 0x003F0A78 */
extern int   g_acb_3F0A7C;         /* 0x003F0A7C */
typedef struct AcbObj30 { uint8_t unk00[0x30]; AcbSlotTarget *t30; } AcbObj30;

#endif
