#ifndef A8B_H
#define A8B_H
#include "oogie.h"
#include "shared_decls.h"

/* Cutscene (demo) object; fields named by offset. Names inferred. */
struct A8bWork;
typedef struct A8bObj {
    uint8_t  unk00[8];
    struct A8bObj *link08;      /* +0x08 referenced object (refcounted) */
    uint8_t  unk0C[0x0C];
    uint32_t flags18;           /* +0x18 bit 1: active */
    struct A8bWork *work1C;     /* +0x1C per-event work block */
    uint8_t  unk20[3];
    uint8_t  ref23;             /* +0x23 reference count */
    uint32_t flags24;           /* +0x24 bit 0: shown */
    void    *x28;               /* +0x28 handle */
} A8bObj;

/* Byte view of the same object for the narrow fields at +0x18..+0x1B. */
typedef struct A8bObjB {
    uint8_t  unk00[0x18];
    uint8_t  flags18;           /* +0x18 */
    uint8_t  b19;
    int8_t   type1A;            /* +0x1A object type (index into type table) */
} A8bObjB;

typedef union A8bTriple { int32_t i[3]; float f[3]; } A8bTriple;

typedef struct A8bWork {
    uint8_t  unk00[4];
    int8_t   kind04;            /* +0x04 */
    uint8_t  unk05[3];
    A8bObj  *target08;          /* +0x08 target object */
    uint8_t  unk0C[4];
    A8bTriple v10;              /* +0x10..+0x1B */
    uint8_t  set1C;             /* +0x1C */
    uint8_t  unk1D[3];
    int32_t  i20;               /* +0x20 */
    uint8_t  unk24[8];
    float    f2C, f30, f34;     /* +0x2C..+0x34 */
} A8bWork;

/* Per-type handler block returned by the type getters. */
typedef struct A8bTypeOps {
    uint8_t unk00[0x0C];
    int   (*fn0C)(A8bObj *o, int arg);   /* +0x0C */
    int   (*fn10)(A8bObj *o, int arg);   /* +0x10 */
} A8bTypeOps;

typedef uint8_t *(*A8bDescGetter)(void);
typedef A8bTypeOps *(*A8bOpsGetter)(void);

/* functions defined in area a8b */
A8bWork *a8b_GetWork(A8bObj *o);
A8bObj  *a8b_GetActiveTarget(A8bObj *o);
void     a8b_RefInc(A8bObj *o);
void     a8b_RefDec(A8bObj *o);

/* external callees */
int  sub_0007E620(void *h);
void sub_0008E200(A8bObj *t);
void sub_0008B400(A8bObj *o);
int  sub_0008B860(void *a, void *b, void *c, unsigned char (*pred)(void *a, void *b)); /* pred called indirectly */
unsigned char sub_0008B2F0(void *a, void *b);   /* key match predicate (a8c_Key3Equal) */
void sub_0008ECA0(A8bObj *t);
void sub_0003D0A0(int a);
void *sub_0007F480(int a, int b, int, int, void *);

extern uint8_t a8b_desc2E0A48[], a8b_desc2E0B48[], a8b_desc2E0BC0[], a8b_desc2E0C38[];
extern uint8_t a8b_desc2E0CD8[], a8b_desc2E0DB8[], a8b_desc2E0E30[], a8b_desc2E0EA0[];
extern uint8_t a8b_desc2E1000[], a8b_desc2E1078[], a8b_desc27001C[];
extern A8bDescGetter a8b_descGetters[];
extern A8bOpsGetter a8b_opsGetters[];
extern int32_t a8b_slots428EE0[];
extern void *a8b_g3ED528;
#endif
