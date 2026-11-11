#ifndef R6E_H
#define R6E_H
#include "oogie.h"
#include "shared_decls.h"
#include <string.h>
#if defined(_M_IX86)
#include <intrin.h>
#endif
/* Area r6e: functions (stack and register arguments) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6e.csv. Callees are declared under their sub_ name
   (or an existing name with the same address) so that cl never inlines a
   function recovered in this area into another one. */

/* ------------------------------------------------------------ script processes (0x8Cxxx-0x8Dxxx) */
typedef struct R6eProcRef {
    uint8_t  unk00[4];
    int32_t  i04;             /* +0x04 */
    uint8_t  unk08[0x14 - 0x08];
    float    f14;             /* +0x14 */
} R6eProcRef;

typedef struct R6eProc R6eProc;
typedef int (*R6eProcFn)(R6eProc *p);
typedef struct R6eProcState {          /* 0x00270088, 8-byte records */
    R6eProcFn step;                    /* +0x00 */
    R6eProcFn enter;                   /* +0x04 */
} R6eProcState;
struct R6eProc {
    uint32_t flags;           /* +0x00 bit 0 running, bit 2 stopped, bit 3 done */
    int8_t   state;           /* +0x04 index into r6b_procStates */
    uint8_t  unk05[3];
    int32_t  timer;           /* +0x08 */
    R6eProcRef *ref;          /* +0x0C */
    int32_t  i10;             /* +0x10 */
    uint16_t w14;             /* +0x14 */
};
extern R6eProcState r6b_procStates[];  /* 0x00270088 */
extern R6eProc *a8b_g3ED528;           /* 0x003ED528 the single process record */

/* ------------------------------------------------------------ script tasks (0x8Bxxx-0x8Fxxx) */
typedef struct R6eTask R6eTask;
typedef struct R6eOps {
    int32_t  size;                                 /* +0x00 record size */
    uint8_t  unk04[4];
    void   (*destroy)(R6eTask *t);                 /* +0x08 */
    uint8_t  unk0C[0x18 - 0x0C];
    int    (*event)(R6eTask *t, int arg);          /* +0x18 */
} R6eOps;
typedef R6eOps *(*R6eOpsGetter)(void);
extern R6eOpsGetter a8b_opsGetters[];  /* 0x002E10E8, 8 entries */

typedef struct R6eAnimRef { uint8_t unk00[0x5C]; void *p5C; } R6eAnimRef;

/* Lookup key argument of 0x0008D7F0: a name on entry, reused for the size result. */
typedef union R6eKeyArg { void *name; int size; } R6eKeyArg;

/* Work block of a task (pointer at +0x1C). */
typedef struct R6eWork {
    uint8_t  unk00[4];
    int8_t   kind04;          /* +0x04 */
    int8_t   sub05;           /* +0x05 */
    uint8_t  unk06[2];
    void    *p08;             /* +0x08 refcounted object */
    uint8_t  b0C[4];
    union { int32_t i; uint8_t b; } u10; /* +0x10 */
    int32_t  i14;             /* +0x14 */
    uint8_t  unk18[0x24 - 0x18];
    int32_t  i24;             /* +0x24 */
} R6eWork;

/* Record table returned by the descriptor getters: 0x24-byte entries at +0x00,
   the size of each kind at +0x08. */
typedef struct R6eDescRec { uint8_t unk00[8]; int32_t size; uint8_t unk0C[0x24 - 0x0C]; } R6eDescRec;
typedef R6eDescRec *(*R6eDescGetter)(void);
extern R6eDescGetter a8b_descGetters[];/* 0x002E0D68, 8 entries */

struct R6eTask {
    uint32_t flags00;         /* +0x00 */
    uint8_t  unk04[0x18 - 0x04];
    union { uint16_t w; uint8_t b; } f18;  /* +0x18 bit 1 active, bits 2..3 mode */
    int8_t   type;            /* +0x1A index into a8b_opsGetters */
    uint8_t  unk1B;
    union {
        R6eWork *work;        /* +0x1C work block */
        int32_t  workId;      /* +0x1C packed id (kind<<20 | sub<<8 | n) for id-keyed tasks */
    };
    int8_t   state;           /* +0x20 1/3 running, 2 idle, 4 waiting */
    int8_t   heap;            /* +0x21 */
    uint8_t  unk22;
    uint8_t  refs;            /* +0x23 */
    union { int32_t i; uint32_t u; uint8_t b[4]; void *p; } u24; /* +0x24 */
    void    *p28;             /* +0x28 */
    int32_t  i2C;             /* +0x2C */
    union { float f; int32_t i; } u30; /* +0x30 */
    float    f34;             /* +0x34 */
    uint8_t  unk38[4];
    void    *p3C;             /* +0x3C */
    uint8_t  unk40[4];
    void    *i44;             /* +0x44 (0x0003D090 value) */
    uint8_t  unk48[0x120 - 0x48];
    void    *p120;            /* +0x120 refcounted resource */
    int32_t  i124;            /* +0x124 */
};

/* Argument record of 0x0008D4A0. */
typedef struct R6eArg20 { uint8_t unk00[0x20]; int32_t i20; } R6eArg20;
/* Second argument of 0x0008BC30. */
typedef struct R6eArg44 { uint8_t unk00[0x44]; void *i44; } R6eArg44;

/* refcounted resource (0x904C0) */
typedef struct R6eRes {
    uint8_t  unk00[0x10];
    int32_t  refs;            /* +0x10 */
} R6eRes;

/* object with a handler index at +0x3C (0x90560) */
typedef struct R6eDisp { uint8_t unk00[0x3C]; int32_t index; } R6eDisp;
typedef void (*R6eDispFn)(R6eDisp *o);
extern R6eDispFn r6e_dispFns2E1398[];  /* 0x002E1398 */

/* growable array of fixed-size records (0x8DD80, 0x8FFE0, 0x90020) */
typedef struct R6eArr {
    uint8_t *data;            /* +0x00 */
    uint32_t stride;          /* +0x04 */
    uint32_t keyLen;          /* +0x08 bytes compared by the finders */
    uint32_t cap;             /* +0x0C */
    uint32_t count;           /* +0x10 */
} R6eArr;

/* slot owner (0x8FF30) */
typedef struct R6eSlot48 { uint32_t w[0x12]; } R6eSlot48;
typedef struct R6eHolder { R6eSlot48 *data; } R6eHolder;

/* list search (0x8F970, 0x8FC50, 0x8FDC0) */
typedef struct R6eLink { struct R6eLink *next; } R6eLink;
typedef struct R6ePred R6ePred;
struct R6ePred {
    uint8_t (*fn)(R6ePred *p, void *node);   /* +0x00 */
    int32_t  a;                               /* +0x04 */
    int32_t  b;                               /* +0x08 */
};
typedef struct R6eLinkNode { uint8_t unk00[8]; void *p08; } R6eLinkNode;

/* linear ramp (0x90420, 0x90480) */
typedef struct R6eRamp { float x0, y0, x1, y1; } R6eRamp;

/* entity record (0x9xxxx) */
typedef struct R6eEnt {
    uint32_t flags;           /* +0x00 */
    uint8_t  unk04[0x40 - 4];
    int32_t  i40;             /* +0x40 */
} R6eEnt;

/* descriptors */
extern uint8_t r6b_desc270340[], r6b_desc270380[], r6b_desc2703A4[];
extern const char r6e_srcFile270054[], r6e_srcFile26FF8C[], r6e_srcFile270114[];
extern float a50_frameUnits;           /* 0x0042C858 */

/* ------------------------------------------------------------ callees */
R6eOps *sub_0008BF50(int type);
int   sub_000A33E0(struct R6eActor *e);
void  sub_000A41D0(struct R6eActor *e, int v);
int   sub_000A4180(struct R6eActor *e);
void  sub_000A4740(struct R6eActor *e, int v);
int   sub_000341C0(void *p);
int   sub_000341E0(void *p);
void  sub_000342A0(void);
void  sub_0008F350(void *x, void *t);   /* regargs: t=EDI; x on the stack (deref +0x20) */
void  sub_0008D220(R6eProc *p);
void  sub_0008BCC0(void *p);
int sub_0007E240(void *p);
void *sub_00089390(void);
void *sub_0008B560(void *a);
void *sub_0008C5F0(void *a);
void  sub_0008B400(void *n);
uint8_t sub_000896D0(void *ref, int mask);
R6eLink *sub_0008F970(R6eLink **it, R6eLink **end, R6ePred *p);
void  sub_0007E2D0(void *ch, int a);
void  sub_0007E310(void *ch, int a);
void  sub_0008E240(void *ch, int a, int i, void *b); /* i=ECX b=EDX */
void *sub_0008FFB0(void *p);
void *sub_0008F430(int a);
void *sub_0007F370(void *p);
int sub_0007EC20(void *p);
int   sub_00047EE0(void);
void  sub_000896A0(R6eProcRef *ref, int mask);
int   sub_00089DD0(R6eProcRef *ref);
void *sub_0008C3C0(int a, int b);
void  sub_0008B3B0(R6eWork *w, void *a);
int   sub_000897B0(R6eProcRef *ref);
void  sub_0007E190(void *p);
void *sub_0007F300(void *n);
void *sub_0007F320(void *n);
void  sub_0007F3B0(void *n);
void *sub_0007F350(void *n);
void *sub_0007F510(void *key, int *out);
int   sub_0008D780(void *a, void *x, int key);
int   sub_00089660(void *ref);
void  sub_0008E3D0(R6eTask *t, int v);
void  sub_0008DD80(R6eArr *a, uint32_t n);
void  sub_000904C0(void *r);
int sub_0007EB40(void *p);
void  sub_0003D0A0(int a);
void  sub_0003D020(int a, void *b);
void  sub_0003D100(int a);
void  sub_000186A0(int a, void *b);
void  sub_00018580(int a, int b, int c, float d, float e);
void  sub_00018610(void);
void  a8b_RefInc(void *o);
void *sub_000897A0(void *ref);
void  sub_0007E340(void *p);
void  sub_00090410(void *p);
int   sub_0008BCD0(int heap);
int   sub_0008BD00(int i);
void  sub_0007F4A0(int slot, int heap);
void *sub_0007F240(void *p, int size, int tag, const char *file);
int   sub_0008B0E0(void *n, int a, int b);
int   sub_000894D0(void *p);
int   sub_001BBDD0(void *p);
R6eLink *sub_0008F8F0(void *l);
uint8_t r6e_PredMatch(R6ePred *p, R6eLinkNode *n);

/* ------------------------------------------------------------ actor slots (0x004242C0, 32 x 0x260) */
typedef struct R6eModel { uint8_t unk00[4]; int32_t i04; int32_t i08; uint32_t flags0C; } R6eModel;
typedef struct R6eActor R6eActor;
struct R6eActor {
    uint32_t flags;           /* +0x000 */
    int32_t  id;              /* +0x004 */
    int32_t  i08;             /* +0x008 */
    float    f0C;             /* +0x00C */
    uint8_t  unk10[0x18 - 0x10];
    int32_t  kind18;          /* +0x018 handler index */
    uint8_t  unk1C[0x40 - 0x1C];
    int32_t  state40;         /* +0x040 */
    int32_t  kind44;          /* +0x044 handler index, -1 none */
    uint8_t  unk48[0x60 - 0x48];
    float    pos60[4];        /* +0x060 */
    uint8_t  unk70[0x80 - 0x70];
    float    pos80[4];        /* +0x080 */
    float    vec90[4];        /* +0x090 */
    uint8_t  unkA0[0xF0 - 0xA0];
    float    vecF0[4];        /* +0x0F0 */
    uint8_t  unk100[0x110 - 0x100];
    int32_t  i110[4];         /* +0x110 */
    R6eModel *model;          /* +0x120 */
    int32_t  i124;            /* +0x124 */
    uint32_t flags128;        /* +0x128 */
    R6eActor *links[8];       /* +0x12C */
    uint8_t  unk14C[0x154 - 0x14C];
    int32_t  snd154[2];       /* +0x154 */
    uint8_t  unk15C[0x260 - 0x15C];
};
extern R6eActor aab_slots[32];         /* 0x004242C0 */
typedef int (*R6eActorFn)(R6eActor *a, int arg);
extern R6eActorFn r6e_actorFns2E17C0[]; /* 0x002E17C0 */
extern R6eActorFn r6e_actorFns2E2758[]; /* 0x002E2758 */
typedef struct R6eKindObj { uint32_t flags; int32_t kind; } R6eKindObj;
extern int32_t a30_g41316C, a30_g413170, r6e_g3ED760;
typedef struct R6eRecDC { uint32_t flags; uint8_t unk04[0xD4 - 4]; void *hD4; R6eModel *modelD8; } R6eRecDC;
extern R6eRecDC aab_recDC[8];          /* 0x00420F20 */
typedef struct R6eObj128 { uint8_t unk00[0x128]; uint32_t flags128; } R6eObj128;

R6eActor *sub_000A4290(int i);
R6eActor *sub_000A42C0(int a);
R6eKindObj *sub_000EDB10(int a);
R6eKindObj *sub_000EDB90(void);
int   sub_000A0FD0(R6eKindObj *o);
void  r4c_VecAdd(float *d, const float *a, const float *b);   /* 0x001ADAF0 */
void  r4c_VecSub(float *d, const float *a, const float *b);   /* 0x001AD9F0 */
void  sub_0001D700(R6eModel *m);
float sub_00171D50(int a, int b, int c);
void  sub_00048250(int h);
void  sub_000A21C0(R6eActor *a, uint8_t **out);
void  sub_000A7700(R6eRecDC *r);
int   sub_000324A0(int a);

/* ------------------------------------------------------------ player / misc (0x6Cxxx-0xCFxxx) */
typedef struct R6eRec8C {
    int32_t  i00, i04, i08;   /* +0x00 */
    int32_t  a0C[16];         /* +0x0C */
    float    f4C[16];         /* +0x4C */
} R6eRec8C;
typedef struct R6ePlayer {
    uint8_t  unk000[0x150];
    uint32_t flags150;        /* +0x150 */
    uint8_t  unk154[0x18C - 0x154];
    int32_t  i18C;            /* +0x18C */
    uint8_t  unk190[0x1D8 - 0x190];
    int32_t  i1D8;            /* +0x1D8 */
    uint8_t  unk1DC[0x200 - 0x1DC];
    R6eRec8C recs[4];         /* +0x200 */
} R6ePlayer;
typedef struct R6eMisc { uint8_t b[0x10]; uint32_t flags0C_; } R6eMisc;
typedef struct R6eActObj { uint8_t unk00[0x0C]; uint32_t flags0C; uint8_t b10; } R6eActObj;
typedef struct R6eOwnerEFC { uint8_t unk000[0xEFC]; R6eActObj *actEFC; uint8_t unkF00[0xFAC - 0xF00]; float fFAC; } R6eOwnerEFC;
typedef struct R6eChVol { uint16_t vol; uint16_t hi; } R6eChVol;
extern uint32_t a60_chFlags[2];        /* 0x003E69C0 */
extern R6eChVol a60_chVol[2];          /* 0x003E69D8 */
extern int32_t  a60_chId[2];           /* 0x003E69A8 */
extern uint32_t *a60_chReg650[2], *a60_chReg660[2];
extern int32_t r6e_g41CD2C, r6e_g41CD30, r6e_g41CD18;
extern uint8_t g_ac0_stickX, g_ac0_stickY;
extern int32_t r6e_g42C5D8, r6e_g42C5E0, r6e_g42C5E4;
extern float   r6e_f42C5DC;
extern uint32_t aa0_flags420010, g_ac0_42CA38;
extern int32_t r6e_g420BEC, r6e_g41FF94;
extern uint8_t r6e_obj420EC0[];
typedef struct R6eObj7A { uint8_t unk000[0x1B8]; int32_t blk1B8[6]; } R6eObj7A;

int   sub_000CD180(R6ePlayer *p, int i);
int   sub_000CD300(R6ePlayer *p);       /* p=EAX */
int   sub_0019BE60(int mask);
void  sub_000BC6B0(void *q, int v);
void  sub_000CB390(R6ePlayer *p, void *m);

#endif
