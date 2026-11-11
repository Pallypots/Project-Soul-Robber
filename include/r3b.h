#ifndef R3B_H
#define R3B_H
#include "oogie.h"
#include "shared_decls.h"
/* Area r3b: more game functions in 0x00130000..0x00190000 (stack and register arguments).
   All names inferred. Register mappings are in the comments and in config/function_states_r3b.csv. */

/* ---- character state machine views (obj = character object, act = actor state block) */

/* Work block hung off an actor at +0x278, as seen by these functions. */
typedef struct R3bWork {
    uint32_t unk00;
    union { void *p; uint32_t flags; } u04; /* +0x04 handle or flag word */
    uint32_t flags08;        /* +0x08 */
    float    f0C;            /* +0x0C */
    int32_t  i10, i14;       /* +0x10, +0x14 */
    union {
        uint32_t flags18;    /* +0x18 flag word, or start of a timer block */
        float    f18;        /* +0x18 the same slot as a value */
    };
    float    f1C;            /* +0x1C */
    int32_t  i20;            /* +0x20 counter block */
    uint8_t  unk24[0x34 - 0x24];
    void    *p34;            /* +0x34 */
    uint8_t  unk38[0x140 - 0x38];
    float    i140;           /* +0x140 */
    uint32_t unk144;
    float    i148;           /* +0x148 */
    uint8_t  unk14C[0x160 - 0x14C];
    float    v160[4];        /* +0x160 (y.. at +0x164) */
    float    f170;           /* +0x170 */
    uint8_t  unk174[0x184 - 0x174];
    float    f184;           /* +0x184 */
} R3bWork;

typedef struct R3bAct {
    int32_t  kind00;         /* +0x000 component kind */
    uint8_t  unk004[0x20 - 4];
    uint8_t  b20[2];         /* +0x020 */
    uint8_t  b22;            /* +0x022 bit 0: facing/side flag */
    uint8_t  unk023[0x4C - 0x23];
    uint32_t flags4C;        /* +0x04C */
    int32_t  state50;        /* +0x050 */
    int32_t  i54;            /* +0x054 */
    int32_t  step58;         /* +0x058 sub-step */
    uint8_t  unk05C[0x64 - 0x5C];
    int32_t  i64;            /* +0x064 */
    float    f68;            /* +0x068 time in state */
    int32_t  h6C;            /* +0x06C */
    void    *h70;            /* +0x070 attached part handle */
    float    f74;            /* +0x074 */
    float    v78[4];         /* +0x078 */
    uint8_t  unk088[0x278 - 0x88];
    R3bWork *work278;        /* +0x278 */
} R3bAct;

typedef struct R3bObj {
    uint32_t unk000;
    int32_t  type04;         /* +0x004 */
    uint32_t unk008;
    uint32_t flags0C;        /* +0x00C */
    uint32_t flags10;        /* +0x010 */
    uint8_t  unk014[0x20 - 0x14];
    uint8_t *p20;            /* +0x020 model; position block at +0x30 */
    uint8_t  unk024[0x30 - 0x24];
    union {
        void   *anim30;      /* +0x030 animation handle */
        struct R3bAnim *pa30; /* +0x030 the same, as a record */
    };
    uint8_t  unk034[0x4C - 0x34];
    float    f4C, f50, f54, f58; /* +0x04C..+0x058 */
    uint32_t unk05C;
    float    pos60[3];       /* +0x060 position (y at +0x64) */
    uint32_t unk06C;
    float    f70;            /* +0x070 */
    uint8_t  unk074[0xE8 - 0x74];
    float    fE8;            /* +0x0E8 */
    uint8_t  unk0EC[0xF8 - 0xEC];
    int32_t  iF8;            /* +0x0F8 */
    float    fFC;            /* +0x0FC */
    float    f100;           /* +0x100 */
    struct R3bObj *p104;     /* +0x104 target */
} R3bObj;

/* Animation record behind obj+0x30; its player instance at +0x14. */
typedef struct R3bAnimInst { uint8_t unk00[0xC4]; float rateC4; } R3bAnimInst;
typedef struct R3bAnim { uint8_t unk00[0x14]; R3bAnimInst *inst14; } R3bAnim;

/* Script step record (state, counter, arguments) used by the step callbacks. */
typedef struct R3bStep {
    int32_t i00, i04;        /* +0x00, +0x04 */
    float   f08;             /* +0x08 elapsed */
    int32_t phase0C;         /* +0x0C */
    union { int32_t i; float f; } a10; /* +0x10 */
    int32_t i14;             /* +0x14 */
} R3bStep;
typedef struct R3bClamp { uint8_t unk00[0x10]; float hi10, lo14, max18, min1C; } R3bClamp;
typedef struct R3bPair { float f0, f4; } R3bPair;

/* Item list behind 0x003F74FC: records of 0x150 bytes. */
typedef struct R3bItem { uint8_t unk00[8]; int32_t type08; uint8_t flags0C; uint8_t unk0D[0x150 - 0x0D]; } R3bItem;
extern R3bItem *r3b_items3F74FC;                     /* 0x003F74FC */
extern float r3_frameUnits;                          /* 0x0042C858 */

/* Motion block at +0x74 of some components. */
typedef struct R3bMotion { uint32_t flags; float f04, f08, f0C, f10; void *p14; } R3bMotion;
typedef struct R3bComp74 { uint8_t unk00[0x74]; R3bMotion *p74; } R3bComp74;

/* Timer record returned by 0x00113430. */
typedef struct R3bTimer {
    uint8_t unk00[0x10];
    union { int32_t i; float f; } a10, a14, a18; /* +0x10..+0x18 */
    int32_t i1C;             /* +0x1C */
} R3bTimer;

/* Condition-list entry as read by 0x001356D0. */
typedef struct R3bCond {
    int32_t active, kind;    /* +0x00, +0x04 */
    int32_t i08, i0C;        /* +0x08, +0x0C */
    union { int32_t i; float f; } a10, a14; /* +0x10, +0x14 */
    float   i18;             /* +0x18 */
} R3bCond;

/* Object picked by the condition target resolver 0x00155940 (seen through its +0x60 block). */
typedef struct R3bTgt {
    uint8_t unk00[0x60];
    union {
        float pos60[3];      /* +0x60 position */
        struct { int32_t i60, i64, i68; } h; /* +0x60.. read as handles by the animation checks */
    } u60;
} R3bTgt;

/* 0x38-byte records at 0x0031C878: three vectors and two keys. */
typedef struct R3bKeyVec { float v00[4]; float v[2][4]; int32_t key[2]; } R3bKeyVec;
extern R3bKeyVec r3b_keyvec31C878[];                 /* 0x0031C878 */

/* 16-byte per-slot records handed to the condition dispatchers. */
typedef struct R3bRec16 { int32_t i[4]; } R3bRec16;
typedef int (*R3bDispFn)(void *a, void *b, R3bRec16 *rec);
extern R3bRec16  r3b_recs279728[];                   /* 0x00279728 */
extern R3bDispFn r3b_disp31CDFC[];                   /* 0x0031CDFC */
extern R3bRec16  r3b_recs2797C8[];                   /* 0x002797C8 */
extern R3bDispFn r3b_disp31D0B8[];                   /* 0x0031D0B8 */
extern R3bRec16  r3b_recs279848[];                   /* 0x00279848 */
extern R3bDispFn r3b_disp31DBBC[];                   /* 0x0031DBBC */

extern uint32_t  r3b_block3FFB38[0x50];              /* 0x003FFB38 */
extern uint32_t  r3b_block3FFC78[0x5A];              /* 0x003FFC78 */
extern int32_t   r3b_i3FE38C, r3b_i3FE390, r3b_i3FE398, r3b_i3FE3A4, r3b_i3FE3A8;
extern float     r3b_timer3FE39C;                    /* 0x003FE39C */
extern float     r3_frameDelta;                      /* 0x0042C85C */

/* Callees (stack arguments unless stated). */
void  sub_000ED600(int v);
void *sub_000EDC20(int a, int b);                    /* object iterator */
void  sub_001134B0(void *act);
void *sub_00113400(void *act, int slot);
void  sub_0001D4E0(void *obj);
void  sub_00088190(void);
void  sub_00145CD0(float *d, const float *s, float k);
int   sub_0013A4A0(void *obj, void *act);
void  sub_0013A840(void *obj, void *act);
int   sub_001A8830(void *a, void *b);
void  b16_TickTimer(void);
void  b1b_EnemyMarkParts(void *obj, void *act);
void  sub_0017D780(void);
void  sub_001859C0(void *obj, void *act);
void  sub_00185C90(void *obj, void *act);
int   a80_Get3ED238(void);
void  sub_001751D0(void *h, void *a);
void  sub_00189DA0(void *a, void *b, int c);

int   sub_001C7EE1(void);                            /* CRT rand */
float sub_001A3F30(float v);                         /* absolute value */
void  sub_00113370(void *act, void *step);
void  sub_0001D700(void *o);

int   sub_0013A7B0(void *obj, void *act);
void  sub_00113C90(void *blk, int a, int b);
void  sub_00113480(void *act, int ev);
void  sub_0013B960(void *obj, void *act);
int   r3_SpawnCharge13D380(void *act, void *obj);    /* act=EDI obj=EBX */

R3bTgt *sub_00155940(R3bCond *c, void *b, void *a); /* c=EAX b=ECX a=stack */
float sub_001B2770(const float *a, const float *b);  /* distance */
int   sub_001460A0(R3bTgt *t);

/* r3b functions called from other r3b files. */
int   r3b_Any135780(int kind);                       /* 0x00135780 kind=EAX */
#endif
