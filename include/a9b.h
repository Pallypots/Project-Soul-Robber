/* Area a9b: second pass over game functions 0x00190000-0x001BC6CF.
 * Reference build OOGIE-XBOX-US-RETAIL. All names INFERRED. VAs in
 * config/symbols_a9b.csv. */
#ifndef A9B_H
#define A9B_H
#include "oogie.h"

/* Per-object work block reached through actor +0x74 (fields used here only). */
typedef struct a9b_Work {
    uint32_t flags0;         /* +0x00 (some kinds store an owner pointer here) */
    int32_t  f4;             /* +0x04 */
    int32_t  f8;             /* +0x08 */
    float    fC;             /* +0x0C */
    int32_t  f10;            /* +0x10 */
    uint8_t  p14[0x18 - 0x14];
    int32_t  f18;            /* +0x18 (int view; float view via A9B_WF18) */
    uint8_t  p1C[0x20 - 0x1C];
    float    f20;            /* +0x20 */
    uint8_t  p24[0x44 - 0x24];
    float    v44[3];         /* +0x44 vector (Hypothesis) */
    float    f50;            /* +0x50 */
} a9b_Work;
#define A9B_WF18(w) (*(float *)&(w)->f18)

typedef struct a9b_Actor {
    uint8_t   p00[0x30];
    int32_t   f30;           /* +0x30 */
    uint8_t   p34[0x60 - 0x34];
    int32_t   f60;           /* +0x60 */
    float     f64;           /* +0x64 */
    int32_t   f68;           /* +0x68 */
    uint8_t   p6C[0x70 - 0x6C];
    float     f70;           /* +0x70 */
    a9b_Work *work;          /* +0x74 */
} a9b_Actor;

typedef struct a9b_Rec4C { int32_t f0; uint8_t p4[0x48]; } a9b_Rec4C;          /* 0x004003A0 x10 */
typedef struct a9b_Rec40 { int32_t f0, f4; uint8_t p8[4]; float fC; int32_t f10; uint8_t p14[0x2C]; } a9b_Rec40; /* 0x00400688 x16 */
typedef struct a9b_Rec18 { int32_t f0, f4; uint8_t p8[0x10]; } a9b_Rec18;      /* 0x00400120 x26 */
typedef struct a9b_Rec88 { a9b_Actor *obj; uint8_t p4[0x84]; } a9b_Rec88;       /* 0x00400A88 x4 */
typedef struct a9b_Rec8C { int32_t f0, f4; uint8_t p8[8]; int32_t f10; uint8_t p14[0x78]; } a9b_Rec8C; /* 0x00400E50 x18 */
typedef struct a9b_Rec30 { int32_t f0; uint8_t p4[4]; int32_t f8; uint8_t pC[0x24]; } a9b_Rec30;          /* 0x00401AF8 x1 */
typedef struct a9b_Rec24w { uint16_t f0; uint8_t p2[0x16]; } a9b_Rec24w;        /* 0x003317B8 x1 (24 bytes) */
typedef struct a9b_Rec36 { int32_t f0; uint8_t p4[2]; uint16_t w6; uint8_t p8[0x1C]; } a9b_Rec36; /* 0x003317C0 x0x264; words at +6+8j */
typedef struct a9b_Slot24 { int32_t f0, f4; uint8_t p8[8]; int32_t f10; uint8_t p14[8]; int32_t f1C; uint8_t p20[4]; } a9b_Slot24; /* 0x00401B30 x16 */
typedef struct a9b_Slot38 { int32_t f0, f4, f8; uint8_t pC[4]; int32_t f10, f14; uint8_t p18[0x20]; } a9b_Slot38; /* 0x00401D70 x45 */
typedef struct a9b_Link24 { int8_t b0; uint8_t p1[0x0F]; int8_t b10; uint8_t p11[7]; } a9b_Link24; /* 0x003316A0 x11 */
typedef struct a9b_Ent18 { uint8_t p0[2]; uint16_t w2; uint8_t p4[0x0E]; } a9b_Ent18; /* 0x0032C930 x996 */
typedef struct a9b_Sub10 { int32_t f0; uint8_t p4[0x0C]; } a9b_Sub10;
typedef struct a9b_Rec60 { int32_t f0, f4, f8; uint8_t pC[0x14]; a9b_Sub10 sub[4]; } a9b_Rec60; /* 0x004019D8 x3 */

extern a9b_Rec4C  a9b_g4003A0[10];
extern a9b_Rec40  a9b_g400688[16];
extern a9b_Rec18  a9b_g400120[26];
extern a9b_Rec88  a9b_g400A88[4];
extern a9b_Rec8C  a9b_g400E50[18];
extern a9b_Slot24 a9b_g401B30[16];
typedef struct a9b_Ent16 { int32_t f0; uint8_t p4[0x0C]; } a9b_Ent16;   /* 0x00330F30 x0x77 */
typedef struct a9b_Buf12 { int32_t f0, f4, f8; } a9b_Buf12;            /* 0x0042CAC4 */
extern a9b_Ent16  a9b_g330F30[0x77];
extern a9b_Buf12  a30_buf12[2];
extern int32_t    a30_bufIndex;
extern int32_t    a9b_g413160, a9b_g413164, a9b_g413168, a30_g41316C, a30_g413170;
extern uint32_t   a19_g413174;
extern float      a9b_g402FC8, a9b_g402FCC, a9b_g402FD0;
extern int32_t    a19_g402FE4, a19_g402FE8, a19_g402FF0;
extern int32_t   *a19_g403128;
extern int32_t    a19_g3374A0, a9b_g40312C;
extern a9b_Slot38 a9b_g401D70[45];
extern a9b_Link24 a9b_g3316A0[11];
extern a9b_Ent18  a19_g32C930[996];
extern a9b_Rec60  a19_g4019D8[3];
extern int32_t    a19_g401B28;
extern a9b_Rec30  a9b_g401AF8[1];
extern a9b_Rec24w a9b_g3317B8[1];
extern a9b_Rec36  a9b_g3317C0[0x264];
extern uint16_t   a9b_g3316B4;
extern int32_t    g_402FA8;
extern int32_t    a19_g402FF4;
extern float      a50_frameSeconds;

void sub_001777A0(int a, void *b, int c);
void sub_00189DA0(void *a, void *b, int c);
void sub_000ED780(void *a);
void sub_00033A70(void *p);
int  sub_00199E20(int i);
int  sub_00199C10(int i, int v);
void sub_001AD440(int h);
void sub_001AA310(int h);
void sub_001AA460(int h);
int  sub_001AD3A0(void);
void sub_001AD520(void);
void sub_000408B0(int a);
void sub_000408C0(int a);
void sub_001A0D70(void);
int  sub_000324B0(int a);
void sub_000580D0(void);
void sub_0019E530(void);
void a9b_BufferWorker(void);
int  a1a_GroupAdd(void *g, int a, int b, int c, int d, int e);
int  a1a_GroupReleaseAll(void *g);
int  sub_0019BE60(int k);
void sub_0001EEC0(void *a, int b);
void sub_001ADB60(float *dst, float *src, float s);
void sub_0001D720(a9b_Actor *a);
void sub_0001D7A0(a9b_Actor *a);
int  sub_001AA520(int a);
void *__fastcall sub_001D24F0(int size, int b);
#endif
