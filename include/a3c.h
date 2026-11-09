#ifndef A3C_H
#define A3C_H
#include "oogie.h"

/* 10-byte element of the paged table at 0x003DA314 (0x00037FF0). */
typedef struct A3cElem10 { uint8_t b[10]; } A3cElem10;
typedef struct A3cPaged {
    A3cElem10  *direct;     /* +0x00 first `count` elements */
    A3cElem10 **pages;      /* +0x04 256-element pages after that */
    uint16_t    count;      /* +0x08 */
} A3cPaged;

typedef struct A3cFlags24 { uint8_t unk00[0x24]; uint32_t flags; } A3cFlags24;
typedef struct A3cQuad { int32_t f00, f04, f08, f0C; } A3cQuad;
typedef struct A3cTriple { int32_t f00, f04, f08; } A3cTriple;
typedef struct A3cKey14 { uint8_t unk00[0x14]; int32_t key; } A3cKey14;
typedef struct A3cLink0C { uint8_t unk00[0x0C]; struct A3cLink0C *next; } A3cLink0C;
typedef struct A3cId0C { uint8_t unk00[0x0C]; int32_t id; } A3cId0C;
typedef struct A3cRec10 { uint8_t unk00[0x10]; int32_t f10; } A3cRec10;
typedef struct A3cHolder { int32_t f00; void *first; void *second; } A3cHolder;
/* Offset table: count, then count offsets relative to the table start (0x0003FA70). */
typedef struct A3cOffTab { uint32_t count; int32_t off[1]; } A3cOffTab;

typedef struct A3cRec2C { uint8_t b[0x2C]; } A3cRec2C;
typedef struct A3cRec1450 { uint8_t b[0x1450]; } A3cRec1450;

extern int32_t   a3c_tbl3DA2D8[5];  /* 0x003DA2D8 */
extern int32_t   a3c_g2C4460;       /* 0x002C4460 */
extern int32_t   a3c_g2C4464;       /* 0x002C4464 */
extern int32_t   a3c_busy3DA310;    /* 0x003DA310 */
extern A3cPaged *a3c_paged3DA314;   /* 0x003DA314 */
extern char      a3c_obj2C4090[];   /* 0x002C4090 */
extern int32_t   a3c_g3DA2FC;       /* 0x003DA2FC */
extern uint32_t  a3c_mask3DA330;    /* 0x003DA330 */
extern int32_t   a3c_n3DA334;       /* 0x003DA334 */
extern int32_t   a3c_tbl3DA338[16]; /* 0x003DA338 */
extern int32_t   a3c_g3DA390;       /* 0x003DA390 */
extern char      a3c_obj3DCDA8[];   /* 0x003DCDA8 */
extern int32_t   a3c_w3DCE58, a3c_h3DCE5C, a3c_w3DA4A0, a3c_h3DCDA4;
extern A3cRec1450 a3c_tbl3DB944[];  /* 0x003DB944 */
extern int32_t   a3c_g3DCD94;       /* 0x003DCD94 */
extern A3cRec2C  a3c_tbl3DA4A8[];   /* 0x003DA4A8 */
extern int32_t   a3c_g3DDCB8;       /* 0x003DDCB8 */
extern int32_t   a3c_tbl2C4AD0[];   /* 0x002C4AD0 */
extern int32_t   a3c_g2C4AE8;       /* 0x002C4AE8 */
extern int32_t   a3c_tbl3DDCC0[];   /* 0x003DDCC0 */
extern int32_t   a3c_g3DDCE8;       /* 0x003DDCE8 */
extern uint32_t  a3c_flags3DE4F8;   /* 0x003DE4F8 */
extern int32_t   a3c_g3DE4F0, a3c_g3DE4F4;

void sub_00037AE0(void);
void sub_00014D00(void *p, void *obj, int a);
void sub_000580D0(void);
void sub_001A4FB0(void *p);
void sub_001A1130(int a);
int  sub_0003C3C0(void);
void sub_0003D8C0(void *node);
void sub_0003D990(void *p, int a, int b, int c);
void sub_001A7490(void);
void sub_001B9720(void);
int  sub_0003ED50(int a, int b);
int  sub_0003F8B0(int a, int b, int c);
void a3c_Clear16(A3cQuad *q);

/* Pool node: busy word at +0, next at +0x10 (0x000338A0 and neighbours). */
typedef struct A3cPNode {
    int32_t busy;           /* +0x00 */
    uint8_t unk04[0x0C];
    struct A3cPNode *next;  /* +0x10 */
    uint8_t unk14[4];
    int32_t f18;            /* +0x18 */
    uint8_t unk1C[4];
    uint8_t sub20[0x10];    /* +0x20 */
    uint8_t sub30[0x10];    /* +0x30 */
} A3cPNode;
typedef struct A3cChain3C { uint8_t unk00[0x3C]; struct A3cChain3C *next; } A3cChain3C;
typedef struct A3cPair { int32_t a, b; } A3cPair;
typedef struct A3cPoolHdr { int32_t count; void *head; } A3cPoolHdr;
typedef struct A3cPoolEnt { int32_t f00; A3cPoolHdr *owner; } A3cPoolEnt;
typedef struct A3cTask {
    uint8_t unk00[4];
    void   *fn;             /* +0x04 */
    uint8_t unk08[8];
    int32_t arg;            /* +0x10 */
    int32_t f14;            /* +0x14 */
    uint8_t sub18[4];       /* +0x18 */
} A3cTask;
typedef struct A3cRec30 { uint8_t b[0x20]; uint8_t sub20[0x10]; } A3cRec30;

extern char     *a3b_base283698;     /* 0x00283698 */
extern A3cRec30 *a3c_ptr3DDCE0[];    /* 0x003DDCE0 */

void a3c_VecCopy(void *dst, const void *src);   /* 0x000F5D40 */
void sub_001B60C0(void *p);
void sub_001B6130(void *p);
void sub_00036B30(void *base, int count, void *cb, void *ctx);
void sub_00033B10(void);
void sub_00033B70(void);
void sub_000335D0(void);
void sub_00034B50(void);
void sub_00036290(void);
void sub_000362F0(void);
void sub_000337A0(A3cPNode *n, int a, int b, int c);
void sub_00033800(A3cPNode *n, int a, int b, int c);
void sub_000338D0(A3cPNode *n, int a, int b);
void sub_001B6A60(void *p, int a);
void sub_0005A510(void *a, void *fn);
void sub_00033C20(void *p);
void sub_001B2150(void *p);
void sub_001B26C0(void *p);
void sub_0003D540(void);
#endif
