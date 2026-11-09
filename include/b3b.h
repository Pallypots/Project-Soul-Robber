#ifndef B3B_H
#define B3B_H
#include "oogie.h"

/* Area b3b (0x00130000-0x0018FFFF, second pass): enemy condition predicates
 * and small state helpers. Names inferred. */

/* Per-enemy work block at component+0x278 (Hypothesis). */
typedef struct B3bWork {
    uint8_t  unk00[0x04];
    uint32_t flags04;        /* +0x04 */
    uint32_t flags08;        /* +0x08 */
    uint8_t  unk0C[0x14 - 0x0C];
    float    f14;            /* +0x14 */
    uint8_t  unk18[0x20 - 0x18];
    void    *res20;          /* +0x20 */
    uint8_t  unk24[0x34 - 0x24];
    void    *res34[3];       /* +0x34 */
    uint32_t flags40;        /* +0x40 */
    uint8_t  unk44[0x4C - 0x44];
    float    f4C;            /* +0x4C */
    uint32_t flags50;        /* +0x50 */
    float    f54;            /* +0x54 */
    float    f58;            /* +0x58 */
    uint8_t  unk5C[0x60 - 0x5C];
    float    f60;            /* +0x60 */
    int32_t  i64;            /* +0x64 */
    float    f68;            /* +0x68 */
    int32_t  i6C;            /* +0x6C */
} B3bWork;

/* Enemy component, second argument of handlers and predicates. */
typedef struct B3bEnemy {
    uint8_t  unk000[0x20];
    uint8_t  b20;            /* +0x20 bit 0 */
    uint8_t  unk021;
    uint8_t  side22;         /* +0x22 bit 0 mirrored */
    uint8_t  unk023[0x4C - 0x23];
    uint32_t flags4C;        /* +0x4C */
    uint8_t  unk050[0x54 - 0x50];
    int32_t  state54;        /* +0x54 current state */
    int32_t  counter58;      /* +0x58 */
    float    f5C;            /* +0x5C */
    uint8_t  unk060[0x74 - 0x60];
    union {
        uint32_t *block74;   /* +0x74 six-dword block (second actor type) */
        float     f74;       /* +0x74 timer (enemy state handlers) */
    } u74;
    uint8_t  unk078[0x278 - 0x78];
    B3bWork *work;           /* +0x278 */
} B3bEnemy;

/* Owner actor, first argument. */
typedef struct B3bOwner {
    uint8_t  unk00[0x08];
    int32_t  kind08;         /* +0x08 variant (0x10 = alternate table) */
    uint32_t flagsC;         /* +0x0C */
    uint32_t flags10;        /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    int32_t  handle30;       /* +0x30 */
} B3bOwner;

/* Predicate parameter record, third argument. */
typedef struct B3bCond {
    uint8_t  unk00[8];
    uint32_t a8;             /* +0x08 mask / low bound / flag */
    uint32_t aC;             /* +0x0C value / high bound / modulus */
    float    lo;             /* +0x10 */
    float    hi;             /* +0x14 */
} B3bCond;

/* Integer view of a parameter record (Hypothesis). */
typedef struct B3bArgs { uint8_t unk00[0x10]; int32_t p10, p14, p18; } B3bArgs;

/* Two-float pair stored at +4. */
typedef struct B3bPair { uint32_t unk0; float x, y; } B3bPair;

extern float b10_f3F7504;                    /* 0x003F7504 */

int  sub_001C7EE1(void);                     /* CRT rand */
unsigned sub_0018B6B0(void);                 /* count of active slots */
void sub_000ED780(B3bOwner *o);
void sub_0015A3D0(B3bOwner *o, B3bEnemy *e, B3bWork *w);
void sub_00185540(B3bOwner *o);
int  sub_000833E0(int handle);
void sub_00167200(B3bOwner *o, B3bEnemy *e, int anim);
void sub_00113370(B3bEnemy *e, B3bCond *n);
int  sub_00145940(B3bOwner *o, int a, int b, int c, int d);
void sub_001459D0(B3bOwner *o, int a, int b, int c);
unsigned sub_00185420(B3bOwner *o);
extern float a50_frameSeconds;               /* 0x0042C85C */
extern float b3b_fZero25FB34;                /* 0x0025FB34 constant 0.0 */
extern int32_t b3b_mode42CAFC;               /* 0x0042CAFC (Hypothesis: game mode) */

int  *sub_0001D960(void *obj, int kind);
void sub_0013A380(B3bOwner *o, int n, const int32_t *tbl);
void sub_0018E700(void *res, int arg);
extern const int32_t b3b_tbl31CE1C[];         /* 0x0031CE1C */

typedef int (*B3bCheckFn)(B3bOwner *o, B3bEnemy *e, const void *tbl);
extern B3bCheckFn b3b_checkFns31D0B8[];       /* 0x0031D0B8 */
extern const uint8_t b3b_tbl2797C8[];         /* 0x002797C8 16-byte records */
extern float a50_frameUnits;                  /* 0x0042C858 */
void sub_00113090(B3bOwner *o, B3bEnemy *e, int state);
int  sub_00113040(B3bOwner *o, B3bEnemy *e, int state);
void sub_00113480(B3bEnemy *e, int slot);
void sub_00139FA0(B3bOwner *o, B3bEnemy *e, int state);
void b10_AddClampF(float *v, float d, float max);

/* Generic game object header (type/subtype) checked before component lookup. */
typedef struct B3bObj {
    uint8_t  unk00[4];
    int32_t  type4;          /* +0x04 */
    int32_t  sub8;           /* +0x08 */
    uint32_t flagsC;         /* +0x0C bit 0 active */
} B3bObj;

/* Owner viewed through its model pointer at +0x30. */
typedef struct B3bAnimState { uint8_t unk00[0xD8]; float timeD8; } B3bAnimState;
typedef struct B3bModel { uint8_t unk00[0x14]; B3bAnimState *anim14; } B3bModel;
typedef struct B3bActor { uint8_t unk00[0x30]; B3bModel *model30; } B3bActor;

extern const int32_t b3b_tbl31DBD4[];         /* 0x0031DBD4 */
extern const int32_t b3b_tbl31DBFC[];         /* 0x0031DBFC */

#endif
