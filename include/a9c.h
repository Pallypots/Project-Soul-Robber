/* Area a9c: third pass over game functions 0x00190000-0x0019FFFF.
 * Reference build OOGIE-XBOX-US-RETAIL. All names INFERRED. VAs in
 * config/symbols_a9c.csv. Record layouts are Hypothesis (fields used here). */
#ifndef A9C_H
#define A9C_H
#include "oogie.h"

/* Per-object work block reached through object +0x74. */
typedef struct a9c_Work {
    uint32_t flags0;         /* +0x00 (some kinds store an owner object here) */
    int32_t  f4;             /* +0x04 */
    int32_t  f8;             /* +0x08 */
    float    fC;             /* +0x0C */
    int32_t  f10;            /* +0x10 */
    float    f14;            /* +0x14 */
    float    f18;            /* +0x18 */
} a9c_Work;

typedef struct a9c_Obj {
    uint8_t   p00[8];
    int32_t   f08;           /* +0x08 kind */
    uint8_t   p0C[0x60 - 0x0C];
    int32_t   f60;           /* +0x60 */
    float     f64;           /* +0x64 */
    int32_t   f68;           /* +0x68 */
    float     f6C;           /* +0x6C */
    float     f70;           /* +0x70 */
    a9c_Work *work;          /* +0x74 */
    uint8_t   p78[0x84 - 0x78];
    float     f84;           /* +0x84 */
    uint8_t   p88[0x128 - 0x88];
    uint32_t  f128;          /* +0x128 */
} a9c_Obj;
#define A9C_OWNER(w) ((a9c_Obj *)(w)->flags0)

typedef struct a9c_Rec18 { int32_t f0, f4; uint8_t p8[0x10]; } a9c_Rec18;          /* 0x00400120 x26 */
typedef struct a9c_Slot38 { int32_t f0, f4, f8; uint8_t pC[4]; int32_t f10, f14; uint8_t p18[0x20]; } a9c_Slot38; /* 0x00401D70 x45 */
typedef struct a9c_Link24 { int8_t b0; uint8_t p1[0x0F]; int8_t b10, b11; uint8_t p12[6]; } a9c_Link24; /* 0x003316A0 x11 */
typedef struct a9c_Ent16 { int32_t f0; uint8_t p4[0x0C]; } a9c_Ent16;              /* 0x00330F30 x0x77 */

typedef struct a9c_Rec60 { int32_t f0, f4, f8, fC; uint8_t p10[8]; int32_t f18; uint8_t p1C[0x40]; int32_t f5C; } a9c_Rec60; /* 0x004019D8 x3 */
typedef struct a9c_Rec36 { int32_t f0; uint8_t p4[0x20]; } a9c_Rec36; /* 0x003317C0 x0x264 */
extern a9c_Rec60  a9c_g4019D8[3];
extern a9c_Rec36  a9c_g3317C0[0x264];
extern int32_t    a30_g41316C, a30_g413170;
extern int32_t    a19_g401828, a19_g40182C, a19_g401830;
extern int32_t    a80_ctx42C8E4;
extern uint8_t    a9c_g3DE5B0[1];
extern float      a9c_g403124;
extern int32_t    a9b_g40312C;
extern a9c_Rec18  a9c_g400120[26];
extern a9c_Slot38 a9c_g401D70[45];
extern a9c_Link24 a9c_g3316A0[11];
extern a9c_Ent16  a9c_g330F30[0x77];
extern int32_t   *a19_g403128;
extern int32_t    a19_g3374A0;
extern int32_t    a9c_g403968;
extern int32_t    a50_frameCounter0;
extern float      a50_frameSeconds;

void sub_00189DA0(void *a, void *b, int c);
void sub_000ED780(void *a);
void sub_0001EEC0(void *a, int b);
void sub_0001D720(void *a);
void sub_00197BA0(a9c_Work *w);
int  sub_00199E20(int i);
int  sub_001AB0A0(int i);
void sub_0004EB50(void);
void sub_0004EC40(void);
int  sub_001A7E30(void);
int  Video_GetRateMode(void);
void sub_001BA640(int a);
void sub_001B96D0(void);
int  sub_001A0CC0(void);
void sub_001A0D30(int a, int b);
void sub_000D1D00(PlayerStats *s);
void sub_000D1930(PlayerStats *s);
void sub_001A8A70(int a);
void sub_00079340(void);
void sub_00079F50(int ctx, void *p, int k);
void sub_001A11B0(void);
void sub_001A1130(int a);
void sub_00049860(int a);
void sub_0019A230(int i, int b);
void sub_0019A4B0(int i);
void sub_00053880(int h);
int  sub_001C7EE1(void);
int  a1a_GroupAdd(void *g, int a, int b, int c, int d, int e);
int  a1a_GroupReleaseAll(void *g);
void sub_0019D460(void);
void sub_0019D120(void);
void sub_0019D390(void);
#endif
