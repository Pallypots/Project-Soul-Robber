#ifndef A1A_H
#define A1A_H
#include "oogie.h"

/* 0x0027B420: 0x14-byte records, first field -1 terminates the table. */
typedef struct A1aIdRec {
    int32_t id;             /* +0x00 */
    int32_t unk04[4];
} A1aIdRec;

/* Job message record reached through node->+0x0C. */
typedef struct A1aJobMsg {
    uint8_t unk00[0x10];
    int32_t kind;           /* +0x10 */
    int32_t a;              /* +0x14 */
    int32_t b;              /* +0x18 */
} A1aJobMsg;
typedef struct A1aJobNode {
    uint8_t unk00[0x0C];
    A1aJobMsg *msg;         /* +0x0C */
} A1aJobNode;

/* Handle wrapper: first word is a resource-group id. */
typedef struct A1aGroup { int32_t id; } A1aGroup;
typedef struct A1aRes { int32_t unk00; int32_t handle; /* +0x04 */ } A1aRes;

/* Fixed list of up to 8 16-byte items. */
typedef struct A1aQuad { int32_t v[4]; } A1aQuad;
typedef struct A1aQuadList {
    uint32_t count;         /* +0x00 */
    int32_t  unk04;
    A1aQuad  items[8];      /* +0x08 */
} A1aQuadList;

/* Three words passed to library calls. */
typedef struct A1aTriple { int32_t a, b; int32_t c[1]; } A1aTriple;

typedef struct A1aRec90 { uint8_t b[0x90]; } A1aRec90;

typedef void (*A1aHook)(int);

typedef struct A1aState {
    uint8_t unk00[0x20];
    int32_t handle;         /* +0x20 */
    uint8_t unk24[0x0C];
    int32_t mode;           /* +0x30 */
    int32_t p34;            /* +0x34 */
    int32_t p38;            /* +0x38 */
} A1aState;
typedef struct A1aStateOwner {
    uint8_t unk00[0x10];
    A1aState *st;           /* +0x10 */
} A1aStateOwner;

void sub_001A0320(void);
void sub_00102FA0(void);
int  sub_00058B00(int a, int b, int c, int d, A1aGroup *g, int id, int e);
A1aRes *sub_00057FC0(int group, int key);
A1aRes *sub_00058020(int group);
A1aRes *sub_00058060(A1aRes *r, int group);
int  sub_000588D0(int h);
void sub_000581E0(int h);
void sub_00058960(int h);
void sub_00058130(int h);
void sub_00058910(int h);
void sub_001A0830(void);
void sub_001A0B80(void);
void sub_001A0BD0(void);
A1aJobNode *sub_0003DC70(void *q);
void sub_0003D880(void *q, A1aJobNode *n);
void sub_00053710(int);
void sub_00053740(void);
int  sub_0004F680(int);
int  sub_00053AB0(int, int, int);
void sub_000512D0(int, int);
void OOG_STDCALL sub_001D1C10(int *out);
void OOG_STDCALL sub_001D1C30(int v);
void sub_001A5300(void);
void sub_001A52F0(void);
void OOG_STDCALL sub_001D3D80(int a, int b, int *c);
void OOG_STDCALL sub_001D2F40(void *a, void *b, void *c);
int  __fastcall sub_001D24F0(int a, int b);

int  a1a_GroupAdd(A1aGroup *g, int a, int b, int c, int d, int e);
int  a1a_GroupReleaseOne(A1aGroup *g, int key);
int  a1a_GroupReleaseAll(A1aGroup *g);

extern int32_t a1a_g403960, a1a_g403964, a1a_g40396C;
extern A1aIdRec a1a_idTable[];
extern int32_t a1a_g4044A0, a1a_g4044A4;
extern uint8_t a1a_g404420[];
extern uint8_t a1a_jobQueue404410[], a1a_jobQueue4044A8[];
extern int32_t a1a_g4046BC, a1a_g4046CC, a1a_g4046D0, a1a_g4046D4;
extern int32_t a1a_g4046D8[9];
extern A1aRec90 a1a_rec404770[];
extern int32_t a1a_g40AD10, a1a_g40AD40, a1a_g40AD44;
extern A1aHook a1a_hooks40AD1C[9];   /* slot 8 is set only by a1a_SwapHook8 */
typedef struct A1aObj54 { uint8_t unk00[0x54]; int32_t res; /* +0x54 */ } A1aObj54;
extern void *a1a_renderLock;
extern int32_t a1a_g40B0E4, a1a_g40B0EC, a1a_g40AEC8, a1a_g40AECC;
extern int32_t a1a_g1E2148, a1a_g1E24C0;
extern float a1a_f361AE0;
int  OOG_STDCALL sub_001BCEF9(int h);
int  OOG_STDCALL sub_001D76A0(int);
void OOG_STDCALL sub_001BD0D6(int, int);
void OOG_STDCALL sub_001D5F50(int);
void OOG_STDCALL sub_001D2CF0(int, int);
void OOG_STDCALL sub_001D55A0(int);
void OOG_STDCALL sub_001D6ED0(int, int, int, int, float, int);
void OOG_STDCALL sub_001D2E10(int, void *);
void OOG_STDCALL sub_001E522D(int, void *, void *);
void sub_001A5560(int, int);
void sub_001BC060(int, void *);
void OOG_STDCALL sub_0022F0E0(int);
void OOG_STDCALL sub_0022EF40(int);
void OOG_STDCALL sub_001D2E90(void (*)(void));
int  OOG_STDCALL sub_001BD517(int, int, int, int);
void OOG_STDCALL sub_001BD59E(void *);
void a1a_RunHooks(void);
int  a1a_AddHook(A1aHook h, int unused);
void a1a_RemoveHook(int i);
extern uint8_t a1a_b40B144;
extern int32_t a1a_g40F124, a1a_g40B148, a1a_g40B13C, a1a_g40B20C, a1a_g40B880;
extern uint8_t a1a_g40B150[], a1a_g40B858[];
extern int32_t a1a_g40B848, a1a_g40B84C, a1a_g40B850, a1a_g40B854, a1a_g40B87C;
#endif
