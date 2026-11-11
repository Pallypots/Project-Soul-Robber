#ifndef A30_H
#define A30_H
#include "oogie.h"

/* 0x4C-byte record table at 0x0042CA2C (record start inferred from the lowest field read). */
typedef struct A30Rec4C {
    int32_t  f00;           /* +0x00 */
    uint8_t  unk04[4];
    uint32_t flags;         /* +0x08  bits 0xF000 = "not available" */
    int32_t  f0C;           /* +0x0C */
    int32_t  f10;           /* +0x10 */
    uint8_t  unk14[8];
    int32_t  f1C;           /* +0x1C */
    int32_t  f20;           /* +0x20 */
    int32_t  f24;           /* +0x24 */
    uint8_t  unk28[0x4C - 0x28];
} A30Rec4C;

/* 32-byte resource slots at 0x002C8900, 0x21E entries. */
typedef struct A30Slot {
    uint8_t  unk00[0x0C];
    int32_t  size;          /* +0x0C */
    int32_t  f10;           /* +0x10 */
    uint8_t  unk14[4];
    void    *f18;           /* +0x18  heap buffer (runtime, freed with 0x00053880) */
    int32_t  f1C;           /* +0x1C */
} A30Slot;
#define A30_SLOT_COUNT 0x21E

/* Two-byte pairs at 0x003E05F0. */
typedef struct A30BytePair { uint8_t a, b; } A30BytePair;

/* 8-byte table at 0x002C7968, 0x23 entries. */
typedef struct A30Pair8 { int32_t a; int32_t b; } A30Pair8;

/* 12-byte double buffer at 0x0042CAC4. */
typedef struct A30Buf12 { uint8_t unk[12]; } A30Buf12;

/* 0x54-byte records at 0x003DFEE4: four 0x14-byte entries. */
typedef struct A30Sub14 { int16_t w; uint8_t unk02[0x12]; } A30Sub14;
typedef struct A30Rec54 { A30Sub14 e[4]; uint8_t unk50[4]; } A30Rec54;

typedef struct A30Handle30 { uint8_t unk00[0x30]; int32_t handle; } A30Handle30;
typedef struct A30Handle0C { uint8_t unk00[0x0C]; int32_t handle; } A30Handle0C;

extern A30Rec4C    a30_rec4C[];
extern A30Slot     a30_slots[];
extern A30Slot    *a30_curSlot;
extern A30BytePair a30_bytePairs[];
extern A30Pair8    a30_pair8[];
extern A30Buf12    a30_buf12[];
extern int32_t     a30_bufIndex;
extern A30Rec54    a30_rec54[];
extern int32_t     a50_streamState;
extern int32_t     a30_g3E0DB4, a30_g3E0DC8;
extern uint8_t     a30_g3E0DD0;
extern int32_t     a30_g3DF9BC, a30_g3DF9B8, a30_g3DFA60, a30_g3DF1D8, a30_g3DF1D4;
extern int32_t     a30_g3DFEC0, a30_g3DFEC4, a30_g3DFECC, a30_g3E05BC;
extern int32_t     a30_g41316C, a30_g413170;

int  sub_00199CA0(int i);
void sub_00199EB0(int i);
int  sub_00199F70(int i);
void sub_0019B5F0(int i);
int  sub_0019B620(int i);
void sub_001AA310(int h);
void sub_001B3300(A30Buf12 *b);
void sub_000576F0(int a, int b);
#endif
