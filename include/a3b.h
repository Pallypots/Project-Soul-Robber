#ifndef A3B_H
#define A3B_H
#include "oogie.h"
#include "shared_decls.h"

/* 0x1C-byte record reset by 0x00031070. */
typedef struct A3bRec1C { int32_t id; int32_t f04, f08, f0C, f10, f14, f18; } A3bRec1C;
/* 0x14-byte record set up by 0x00031090. */
typedef struct A3bRec14 { int32_t f00; int32_t f04, f08, f0C, f10; } A3bRec14;

/* 20-byte entries addressed through +0x50 of a table object (0x00033DA0). */
typedef struct A3bEnt14 { int32_t f00; uint8_t unk04[0x10]; } A3bEnt14;
typedef struct A3bTable {
    uint8_t   unk00[8];
    int32_t   count;        /* +0x08 */
    uint8_t   unk0C[0x50 - 0x0C];
    A3bEnt14 *entries;      /* +0x50 */
} A3bTable;

/* Singly linked list node (0x00033DC0). */
typedef struct A3bItem { uint8_t unk00[0x10]; int32_t key; } A3bItem;
typedef struct A3bNode { struct A3bNode *next; uint8_t unk04[8]; A3bItem *item; } A3bNode;
typedef struct A3bList { int32_t f00; A3bNode *head; } A3bList;

typedef struct A3bObj {
    int32_t f00;
    uint32_t flags;         /* +0x04 */
    int32_t f08;
    uint8_t unk0C[0x24 - 0x0C];
    int32_t f24;            /* +0x24 */
} A3bObj;

extern char    a3b_name3817A0[];    /* 0x003817A0 */
extern int32_t a3b_mode381AB8;      /* 0x00381AB8 (100 = special mode) */
extern int32_t a3b_g381834;         /* 0x00381834 */
extern int32_t a3b_g381850;         /* 0x00381850 */
extern int32_t a3b_tbl381A60[];     /* 0x00381A60 */
extern int32_t a3b_g381884;         /* 0x00381884 */
extern char   *a3b_base283698;      /* 0x00283698 */

void sub_001A8A70(int v);
int  sub_00031C60(int v);
void sub_00033130(void);
void sub_000331D0(void);
void sub_00079340(void);
void sub_00033560(void *p);
void sub_00053350(int a, int b);
void sub_0003D860(void *p);
int  sub_000342C0();

/* Pool node: busy word at +0, next at +0x10 (0x00034D70 and neighbours). */
typedef struct A3bPNode {
    int32_t busy;           /* +0x00 */
    uint8_t unk04[0x0C];
    struct A3bPNode *next;  /* +0x10 */
    uint8_t unk14[0x0C];
    uint8_t sub20[4];       /* +0x20 */
} A3bPNode;

/* Callback record (0x00034270): p+0x10 is passed on, flags at +0x24, owner at +0x28. */
typedef struct A3bCbRec {
    uint8_t unk00[0x1C];
    uint32_t mask;          /* +0x1C */
    uint8_t unk20[4];
    uint32_t flags;         /* +0x24 */
    int32_t owner;          /* +0x28 */
} A3bCbRec;
typedef struct A3bMatch { uint32_t value; uint32_t mask; } A3bMatch;

typedef struct A3bRange { int32_t f00; int32_t f04; int32_t f08; } A3bRange;
typedef struct A3bRef { int32_t f00; int32_t refs; } A3bRef;
typedef struct A3bHandle { uint32_t flags; A3bRef *ref; } A3bHandle;

extern int32_t a3b_g3DA098;         /* 0x003DA098 */
extern uint8_t a3b_obj3DA0A4[];     /* 0x003DA0A4 */
extern float   a3b_f3DA0B0;         /* 0x003DA0B0 */
extern uint8_t a3b_obj42CB20[];     /* 0x0042CB20 */

void sub_00034500(int a, void *item);
void sub_001B6670(void *p, float a);
void sub_001B67F0(void *p, float a);
void sub_001B6A90(void *p);
void sub_001B6B10(void *p);
void sub_000339C0(A3bPNode *n, void *a);
void sub_00034F90(A3bPNode *n);
void sub_00036260(void *p);
void sub_00035FD0(void *p, int a, int b);
void sub_000368F0(void *p, int a, int b);
void *sub_000373A0(const void *name, int offset, int size, void *buf); /* returns buf, or a new block when buf is 0 */
#endif
