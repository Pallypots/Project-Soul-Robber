#ifndef A1B_H
#define A1B_H
#include "oogie.h"
#include "shared_decls.h"
#include "a12.h"

/* Object stepped by sub_00014E80 (0x00015070). */
typedef struct A1bStepper {
    uint8_t  unk00[0x10];
    float    t10;           /* +0x10 */
    uint8_t  unk14[0x10];
    uint32_t flags24;       /* +0x24, bit 7 = done */
} A1bStepper;

typedef struct A1bAnimSet {
    uint8_t  unk00[0x24];
    struct A1bAnimEntry **entries;   /* +0x24 */
} A1bAnimSet;
typedef struct A1bAnimEntry {
    uint8_t  unk00[8];
    int32_t  length;        /* +0x08 */
} A1bAnimEntry;
typedef struct A1bAnimState {
    uint8_t  unk00[8];
    int32_t  cur;           /* +0x08 */
    int32_t  time;          /* +0x0C */
    int32_t  length;        /* +0x10 */
    uint8_t  unk14[0x14];
    int32_t  r28;           /* +0x28 */
    uint8_t  unk2C[0x10];
    A1bAnimSet *set;        /* +0x3C */
} A1bAnimState;

/* Large manager object (0x00019000..0x000192B0). */
typedef struct A1bMgr {
    uint8_t  unk000[0x27C];
    int32_t  sel27C;        /* +0x27C */
    uint8_t  unk280[4];
    int32_t  sel284;        /* +0x284 */
    uint8_t  unk288[0x12BC - 0x288];
    int32_t  mode12BC;      /* +0x12BC */
    int32_t  v12C0;         /* +0x12C0 */
} A1bMgr;

typedef struct A1bTimer {
    uint8_t  unk000[0x108];
    int32_t  t108;          /* +0x108 */
    int32_t  t10C;          /* +0x10C */
    int32_t  t110;          /* +0x110 */
} A1bTimer;

char *sub_00013370(const char *path);
void  sub_00014E80(A1bStepper *s);
void  sub_0003FC10(int32_t *p);
void  a60_Set3E74B8(void);
void  sub_000D9AB0(int id);

extern int32_t  a1b_buf4326A0, a1b_end4326A4;
extern int32_t  a1b_val37B558;
extern int32_t  a1b_obj37B560;
extern int32_t  a1b_slots37BEE8[];
extern int32_t  a1b_i37C048, a1b_i37C050, a1b_i37C05C;
extern float    a1b_f37C04C, a1b_f37C054, a1b_f37C058;
typedef struct A1bCbOwner {
    uint8_t  unk00[0xD4];
    void    *callback;      /* +0xD4 */
} A1bCbOwner;
typedef struct A1bLink {
    int32_t  id;            /* +0x00 */
    uint8_t  unk04[4];
    struct A1bLink *next;   /* +0x08 */
} A1bLink;
typedef struct A1bLinkOwner {
    uint8_t  unk00[0x40];
    A1bLink *first;         /* +0x40 */
} A1bLinkOwner;
typedef struct A1bTblOwner {
    uint8_t  unk00[0x20];
    void    *table;         /* +0x20 */
} A1bTblOwner;
typedef struct A1bSub { uint8_t unk00[0x14]; int32_t v14; } A1bSub;
typedef struct A1bSubOwner {
    uint8_t  unk000[0x140];
    A1bSub  *sub;           /* +0x140 */
} A1bSubOwner;

void  sub_0001D980(A12Node *n);
void *__fastcall sub_0001DAA0(int index, void *table);
void *sub_0001F6C0(int a, int b, int c, int d, void *e);
void  sub_000226B0(void);
void *sub_000227B0(void *x);
int   sub_000D9A70(int id);
void  sub_0002C7A0(void);

extern int32_t  a1b_on37C4C0;
extern float    a1b_f37C4D8, a1b_f37C4E4, a1b_f37C4EC;
extern int32_t  a1b_state3813B4, a1b_i37F0CC, a1b_i37F0E0, a1b_i37F0F0, a1b_i37FA9C;
extern uint32_t a1b_flags37C4F8;
extern int32_t  a1b_i37C570, a1b_i37C574, a1b_i3816D0;
extern uint8_t  a1b_b37D45C;
#endif
