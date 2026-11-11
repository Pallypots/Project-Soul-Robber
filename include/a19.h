/* Area a19: game functions 0x00190000-0x0019FFFF. Reference build
 * OOGIE-XBOX-US-RETAIL. All names INFERRED. VAs in config/symbols_a19.csv. */
#ifndef A19_H
#define A19_H
#include "oogie.h"

/* Per-object work block reached through actor +0x74. */
typedef struct a19_Work {
    int32_t f0;              /* +0x00 */
    uint8_t p04[4];
    int32_t f8;              /* +0x08 */
    uint8_t p0C[0x14 - 0x0C];
    float   v14[3];          /* +0x14 vector (Hypothesis) */
    float   f20;             /* +0x20 */
    float   f24;             /* +0x24 */
    uint8_t p28[0x30 - 0x28];
    float   v30[3];          /* +0x30 */
    uint8_t p3C[0x44 - 0x3C];
    float   v44[3];          /* +0x44 */
    float   f50;             /* +0x50 */
    uint8_t p54[0x70 - 0x54];
    float   v70[3];          /* +0x70 */
    uint8_t p7C[0x88 - 0x7C];
    int16_t s88;             /* +0x88 */
    int16_t s8A;             /* +0x8A */
} a19_Work;

/* Generic game actor; only fields used here. */
typedef struct a19_Actor {
    uint8_t   p00[0x0C];
    uint32_t  flagsC;        /* +0x0C */
    uint32_t  flags10;       /* +0x10 */
    uint8_t   p14[0x60 - 0x14];
    int32_t   f60;           /* +0x60 */
    uint8_t   p64[4];
    int32_t   f68;           /* +0x68 */
    uint8_t   p6C[0x74 - 0x6C];
    a19_Work *work;          /* +0x74 */
} a19_Actor;

/* Accessors at +0x18/+0x1C share the work block: f18/f1C overlap v14[1]/v14[2]. */
#define A19_F18(w) ((w)->v14[1])
#define A19_F1C(w) ((w)->v14[2])

typedef struct a19_Rec24 { int32_t f[9]; } a19_Rec24;                         /* 0x004000B0 x3 */
typedef struct a19_Rec40 { int32_t f0, f4; uint8_t p8[4]; float fC; int32_t f10; uint8_t p14[0x2C]; } a19_Rec40; /* 0x00400688 x16 */
typedef struct a19_Rec18 { int32_t f0, f4; uint8_t p8[0x10]; } a19_Rec18;     /* 0x00400120 x26 */
typedef struct a19_Rec88 { int32_t f0; uint8_t p4[0x84]; } a19_Rec88;         /* 0x00400A88 x4 */
typedef struct a19_RecB4C { int32_t f0; uint8_t p4[0x20]; } a19_RecB4C;      /* 0x00401B4C x16 */
typedef struct a19_Rec38 { int32_t f0; uint8_t p4[0x34]; } a19_Rec38;         /* 0x00401D98 x45 */
typedef struct a19_Rec30 { int32_t f0; uint8_t p4[0x2C]; } a19_Rec30;         /* 0x00401AF8 x1 */
typedef struct a19_Rec60 { int32_t f0; uint8_t p4[4]; int32_t f8; uint8_t pC[0x50]; int32_t f5C; } a19_Rec60; /* 0x004019D8 x3 */
typedef struct a19_Rec12 { uint8_t p0[8]; int8_t b8; int8_t b9; uint8_t pA[8]; } a19_Rec12; /* 0x0032C930, 18 bytes */

extern a19_Rec88  a19_g400A88[4];
extern int32_t    a19_g400CA8[0x69];
extern void      *a19_g401828, *a19_g40182C, *a19_g401830;   /* heap blocks (0x00401828..) */
extern a19_RecB4C a19_g401B4C[16];
extern a19_Rec38  a19_g401D98[45];
extern a19_Rec60  a19_g4019D8[3];
extern int32_t    a19_g401B28;
extern a19_Rec12  a19_g32C930[996];
extern int32_t    a19_g402758, a19_g402760, a19_g402764, a19_g402768, a19_g402770, a19_g402774;
extern int32_t    a19_g402F94;
extern uint32_t   a19_g413174;
extern uint8_t    a19_g41314A, a19_g41314B;
extern int32_t    a19_g336DD0, a19_g337498, a19_g3374A0;
extern int32_t    a19_g402FE4, a19_g402FE8, a19_g402FF0, a19_g402FF4;
extern int32_t   *a19_g403128;
extern float      a19_g403004, a19_g403120;
extern int32_t    a19_g403940, a19_g40396C, a19_g403974;

void a19_VecOp(float *a, float *b);                 /* 0x000F5D40 (2-arg use) */
a19_Actor *sub_0001D960(void *obj, int kind);      /* find component of `kind` (Hypothesis) */
void sub_00189DA0(void *a, void *b, int c);
void sub_0001D720(a19_Actor *a);
int  sub_001AB610(void);
int  sub_001AB3D0(int a, int b);
void sub_0019AA00(int a, int b);
int  sub_0019AEA0(int a, int b, int c, int d, int e, int f);
void sub_00052A20(void);
void sub_0019C350(void);
void sub_001A1130(int a);
void sub_001AA310(int a);
void sub_001AD520(void);
int  sub_001AA520(int a);
void sub_0019E810(int a);
void sub_00196D30(void);
void sub_00197CE0(void);
void sub_00199B50(void);
void sub_0019A6F0(void);
void sub_0019AE00(void);
#endif
