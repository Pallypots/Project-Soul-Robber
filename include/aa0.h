#ifndef AA0_H
#define AA0_H
#include "oogie.h"
/* Area aa0 (0x000A0000..0x000C0000). All names inferred. */

/* 0x004242C0: array of 0x260-byte records (count Hypothesis). */
typedef struct Aa0Slot {
    uint32_t flags;          /* +0x000 bit0 = active */
    uint8_t  unk004[0xB0 - 0x04];
    float    vecB0[4];       /* +0x0B0 */
    uint8_t  unkC0[0x120 - 0xC0];
    void    *obj120;         /* +0x120 */
    int32_t  val124;         /* +0x124 */
    uint8_t  unk128[0x260 - 0x128];
} Aa0Slot;
extern Aa0Slot aa0_slots[16];               /* 0x004242C0 */

/* Object with a state word and a reset-on-change timer. */
typedef struct Aa0StateA {
    uint8_t unk00[0x1C];
    int32_t state;           /* +0x1C */
    int32_t timer;           /* +0x20 */
} Aa0StateA;
typedef struct Aa0StateB {
    uint8_t unk00[0x3C];
    int32_t state;           /* +0x3C */
    int32_t timer;           /* +0x40 */
} Aa0StateB;
typedef struct Aa0Pair54 {
    uint8_t unk00[0x54];
    float   f54;             /* +0x54 */
    float   f58;             /* +0x58 */
} Aa0Pair54;
/* 16-byte record in the table pointed to by 0x003ED748. */
typedef struct Aa0Rec16 {
    int32_t unk0;
    int8_t  flag;            /* +0x04 */
    uint8_t unk5[11];
} Aa0Rec16;
/* Dispatch object: a kind word selects a handler. */
typedef struct Aa0Disp {
    uint32_t flags;          /* +0x00 */
    int32_t  kind;           /* +0x04 */
    uint8_t  unk08[0x1C - 0x08];
    int32_t  kind1C;         /* +0x1C */
} Aa0Disp;
typedef void (*Aa0Handler)(Aa0Disp *);

extern Aa0Rec16 *aa0_rec16Table;            /* 0x003ED748 */
extern uint32_t aa0_flags420010;            /* 0x00420010 */
extern uint32_t aa0_flags420EF8;            /* 0x00420EF8 */
extern float    aa0_float420EFC;            /* 0x00420EFC */
extern uint32_t aa0_flags3ED764;            /* 0x003ED764 */
extern int32_t  aa0_word3ED74C;             /* 0x003ED74C */
extern uint8_t  aa0_enabled413142;          /* 0x00413142 */

void aa0_Vec4Copy(void *dst, const void *src);   /* 16-byte copy */
int  sub_000E5B70(int n);
int  sub_0005EB10(int a, int b);
int  sub_000AC8A0(void *a, void *b, int kind);
int  sub_000AC9D0(void *a, void *b, int kind);
int  sub_000ADB60(void *a, void *b, int kind);
void sub_000A5450(int slot);

/* Static descriptors returned by the 6-byte getters. */
extern uint8_t aa0_desc2E4968[], aa0_desc2E4C60[], aa0_desc2E4ED8[], aa0_desc2E4F90[],
    aa0_desc2E5000[], aa0_desc2E50C0[], aa0_desc2E5380[], aa0_desc2E5460[], aa0_desc2E54C0[],
    aa0_desc2E5600[], aa0_desc3ED98C[], aa0_desc2E5650[], aa0_desc2E5670[], aa0_desc2E5750[],
    aa0_desc2E5830[], aa0_desc2E5850[], aa0_desc2E591C[], aa0_desc2E5950[], aa0_desc2E5A00[],
    aa0_desc2E5C20[], aa0_desc2E5CC0[], aa0_desc3ED9C0[], aa0_desc2E5D30[], aa0_desc2E5DC0[],
    aa0_desc2E5E50[], aa0_desc2E5F10[], aa0_desc2E6040[], aa0_desc2E6090[];
#endif
