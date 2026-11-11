#ifndef A80_H
#define A80_H
#include "oogie.h"
#include "shared_decls.h"

/* Small pool descriptor at 0x003E9410. */
typedef struct A80Pool {
    int32_t capacity;       /* +0x00 */
    int32_t used;           /* +0x04 */
    int32_t head;           /* +0x08 */
    void   *storage;        /* +0x0C */
} A80Pool;

struct A80Sub;

/* Generic object with flag words (fields named by offset). */
typedef struct A80Obj {
    uint32_t flags;         /* +0x00 */
    int32_t  x04;           /* +0x04 */
    uint32_t flags08;       /* +0x08 */
    uint8_t  unk0C[0x0C];
    float    f18;           /* +0x18 */
    uint8_t  unk1C[4];
    int32_t  x20;           /* +0x20 */
    int32_t  x24;           /* +0x24 */
    uint8_t  unk28[8];
    uint32_t flags30;       /* +0x30 */
    uint8_t  unk34[0x14];
    void    *x48;           /* +0x48 */
    struct A80Sub *sub4C;   /* +0x4C */
    struct A80Sub *sub50;   /* +0x50 */
} A80Obj;

typedef struct A80Sub {
    int32_t  x00;
    uint8_t  unk04[0x18];
    void    *x1C;           /* +0x1C */
    uint8_t  unk20[0x10];
    uint32_t mask30;        /* +0x30 */
} A80Sub;

typedef struct A80Pair { int32_t a; int32_t b; } A80Pair;
typedef struct A80Ref  { int32_t x00; int32_t x04; int32_t x08; void *x0C; } A80Ref;

/* 24-byte mode record table at 0x002E0680, indexed by a80_curMode. */
typedef struct A80ModeRec {
    int32_t a;                              /* +0x00 */
    int32_t b;                              /* +0x04 */
    void  (*update)(struct A80ModeRec *r);  /* +0x08 */
    int32_t c, d;                           /* +0x0C */
    int32_t flags;                          /* +0x14 */
} A80ModeRec;

typedef struct A80IdVal { int32_t id; int32_t value; } A80IdVal;

typedef int (*A80Fn2)(int a, int b);

void sub_00082C80(int a, int b, void *tbl);
void sub_000252A0(int a, int b);
A80Ref *sub_0008CD60(void);
void sub_0007AB10(void *ctx, void *p);

extern A80Pool a80_pool;
extern uint8_t a80_poolStorage[];
extern uint8_t a80_tbl2E0380[];
extern uint8_t a80_obj2E0958[], a80_obj2E09C8[];
extern const char a80_str26FA20[], a80_str26FACC[], a80_str26FA70[];
extern int32_t a80_g3ED1C4, a80_g3ED1C8, a80_g3ED1CC;
extern void   *a80_g3ED1B0, *a80_g3ED1D0, *a80_g3ED1D4;   /* 0x003ED1B0.. table pointers */
extern int32_t a80_g3ED204, a80_g3ED210, a80_g3ED214, a80_g3ED218;
extern void   *a80_g3ED208;             /* 0x003ED208 current stream set */
extern int32_t a80_state3ED21C, a80_saved3ED220, a80_g3ED238, a80_g3ED23C, a80_g3ED248;
extern int32_t *a80_ptr3ED240;
extern int32_t a80_g3ED25C, a80_mode3ED274;
extern uint32_t a80_flags3ED258;
extern int32_t a80_curMode;
extern A80ModeRec a80_modeTable[];
extern A80Fn2 a80_fnTab2E03B4[], a80_fnTab2E0408[];
extern A80IdVal a80_idTab2E0908[];
extern void   *a80_ctx42C8E4;           /* 0x0042C8E4 context object */
#endif
