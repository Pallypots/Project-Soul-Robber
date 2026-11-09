#ifndef B7C_H
#define B7C_H
#include "oogie.h"
#include <string.h>
/* Area b7c: game functions 0x00170000-0x00190000 (third pass). Names inferred. */

/* Zero a record (the original inlines rep stosd). Intrinsic only on x86. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define B7C_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) / 4)
#else
#define B7C_ZERO(p, n) memset((p), 0, (n))
#endif

/* ---- enemy object: work block pointer at +0x278 (layout varies per type) */
typedef struct B7CEnemy { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x1C]; void *anim30;
                          uint8_t unk34[0x244]; void *work; } B7CEnemy;
/* AI owner object */
typedef struct B7COwner { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk14[0x1C];
                          void *anim30; } B7COwner;

/* work block variants (Hypothesis: one per enemy type) */
typedef struct B7CWorkA { uint32_t flags; uint8_t unk04[0x20]; void *fx24[3]; } B7CWorkA;
typedef struct B7CWorkB { uint32_t flags; uint8_t unk04[0x24]; void *fx28[3]; } B7CWorkB;
typedef struct B7CWorkC { uint8_t unk00[8]; float f08; int32_t i0C; int32_t i10; uint8_t unk14[2]; int16_t s16; } B7CWorkC;
typedef struct B7CWorkD { uint8_t unk00[0x26]; int16_t mode26; uint8_t unk28[0x1C]; float f44; } B7CWorkD;

/* state block passed to some handlers */
typedef struct B7CState { uint8_t unk00[0x4C]; int32_t i4C; int32_t i50; float f54; float f58; } B7CState;
typedef struct B7CFlag128 { uint8_t unk00[0x128]; uint32_t flags128; } B7CFlag128;
typedef struct B7CMove { uint8_t unk00[0x78]; float f78, f7C, f80, f84; } B7CMove;
typedef struct B7CF10 { uint8_t unk00[0x10]; float f10; } B7CF10;

/* hit component (query type 8) */
typedef struct B7CHit { uint8_t unk00[0x5C]; uint8_t flags5C; uint8_t unk5D[0x5F]; int32_t iBC; uint8_t unkC0[0xC]; int32_t iCC; } B7CHit;
typedef struct B7CHandle { uint8_t unk00[4]; int32_t type; } B7CHandle;

/* ---- tasks */
typedef struct B7CTask { uint8_t unk00[8]; int32_t id; } B7CTask;
extern B7CTask *b16_task3FD7B0; extern int32_t b16_taskId3FD7B4;
extern B7CTask *b7c_task3FD7C8; extern int32_t b7c_taskId3FD7CC;

/* ---- pools */
typedef struct B7CRec30 { uint32_t flags; uint8_t unk04[0x2C]; } B7CRec30;
typedef struct B7CRec34 { uint32_t flags; uint8_t unk04[0x30]; } B7CRec34;
typedef struct B7CRec24 { void *obj; uint8_t unk04[0x20]; } B7CRec24;
typedef struct B7CRec54 { int32_t used; uint8_t unk04[0x50]; } B7CRec54;
extern B7CRec30 b7c_pool3FD7E0[5];      /* 0x003FD7E0 */
extern B7CRec34 b7c_pool3FD8D0[5];      /* 0x003FD8D0 */
extern B7CRec34 b7c_pool3FD9D8[5];      /* 0x003FD9D8 */
extern B7CRec24 b7c_pool3FDAF8[9];      /* 0x003FDAF8 */
extern B7CRec54 b7c_pool3FDC70[6];      /* 0x003FDC70 */
extern uint16_t b7c_w3FDAE0[10];        /* 0x003FDAE0 */

extern void *b16_tables[];              /* 0x0032B110 */
typedef void (*B7CStateFn)(void *o, B7CState *s);
extern B7CStateFn b7c_stateFns32B1B0[]; /* 0x0032B1B0 */
extern float b16_frameDelta;            /* 0x0042C85C */

int   aab_Rand(void);                                   /* 0x001C7EE1 */
void  sub_000ED560(int a);
void  sub_000ED600(int a);
void  sub_00020170(B7CTask *t);
B7CTask *sub_0001F210(int a, int b);
void  sub_0001DA40(B7CTask *t);
int   sub_0004F6D0(int i);
void  sub_0004F5D0(int i);
B7CHandle *sub_000EDBE0(int a, int b);
void *sub_0001D960(void *h, int kind);
int   sub_000833E0(void *p);
void  sub_000832D0(void *anim, int id);
void  sub_000ED780(void *p);
void  sub_0018D650(void *p);
void  sub_001940A0(void *p);
void  sub_00113040(void *o, void *e, int st);
void  sub_00113090(void *o, void *e, int st);
B7CF10 *sub_001133E0(void *e, int i);
int   sub_00176070(void *o, void *e, void *w);
void  b7c_VecCopy(void *a, void *b);   /* 0x000F5D40 */
void  sub_00178860(void *a, void *b);
void  sub_00178D50(void *a, void *b);

#endif
