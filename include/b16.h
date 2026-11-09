#ifndef B16_H
#define B16_H
#include "oogie.h"
#include <string.h>
/* Zero a block (the original inlines this as rep stosd). The intrinsic is
 * used only for the 32-bit x86 comparison build; every other target (native
 * x64, ARM64) gets plain memset, which is the same behaviour. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define B16_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) / 4)
#else
#define B16_ZERO(p, n) memset((p), 0, (n))
#endif

/* ---- global slot table at 0x003F7508 (Hypothesis: effect/sound channel set) */
typedef struct B16Slot { uint32_t flags; uint8_t unk04[0x44]; } B16Slot;   /* 0x48 bytes */
typedef struct B16SlotSys { uint32_t flags; B16Slot slots[6]; } B16SlotSys; /* 0x1B4 bytes */
extern B16SlotSys b16_slotSys;          /* 0x003F7508 */

typedef struct B16Pair { uint32_t flags; uint8_t unk04[4]; float f08, f0C; uint8_t unk10[0x30]; int32_t i40, i44; } B16Pair;
typedef struct B16Vecs { uint8_t unk00[0x10]; float v10[4]; float v20[4]; float v30[4]; } B16Vecs;

/* ---- record pools */
typedef struct B16Rec60 { uint32_t flags; uint8_t unk04[0x5C]; } B16Rec60;  /* 0x60 bytes */
typedef struct B16Rec20 { uint32_t flags; uint8_t unk04[0x1C]; } B16Rec20;  /* 0x20 bytes */
typedef struct B16Rec18 { uint32_t flags; uint8_t unk04[0x14]; } B16Rec18;  /* 0x18 bytes */
extern float    b16_timer3F8410;        /* 0x003F8410 */
extern B16Rec60 b16_pool60[16];         /* 0x003F8418 */
extern B16Rec20 b16_pool20[16];         /* 0x003F8A18 */
extern B16Rec18 b16_pool18[5];          /* 0x003F8C20 */
extern uint8_t  b16_buf3F8C98[0x50];    /* 0x003F8C98 */
extern uint8_t  b16_buf3FD7E0[0xF0];    /* 0x003FD7E0 */
extern uint8_t  b16_buf3FD8D0[0x104];   /* 0x003FD8D0 */
extern uint8_t  b16_buf3FD9D8[0x104];   /* 0x003FD9D8 */
extern float    b16_frameDelta;         /* 0x0042C85C */
extern float    b16_frameUnits;         /* 0x0042C858 */
typedef struct B16Flag0C { uint8_t unk00[0xC]; uint32_t flags; } B16Flag0C;

/* ---- task registrations: (handle, id) pairs */
typedef struct B16Task { uint8_t unk00[8]; int32_t id; } B16Task;
extern B16Task *b16_task3F8400; extern int32_t b16_taskId3F8404;
extern B16Task *b16_task3F92E8; extern int32_t b16_taskId3F92EC;
extern B16Task *b16_task3FD7B0; extern int32_t b16_taskId3FD7B4;
B16Task *sub_0001F210(int a, int b);
void     sub_0001DA40(B16Task *t);
void     sub_00020170(B16Task *t);
void     sub_000ED9A0(void *fn);
void     sub_000ED9E0(void *fn);
void     sub_000ED560(int a);
void     sub_00166CD0(void);

/* ---- small actor state machine (0x00167xxx-0x0016Exxx) */
typedef struct B16Part { uint8_t unk00[0xB8]; uint32_t flags; } B16Part;
typedef struct B16Anim { uint8_t unk00[8]; int32_t cur; uint8_t unk0C[8]; B16Part *part; } B16Anim;
typedef struct B16Ctx { uint8_t unk00[0xC4]; uint8_t *banks; } B16Ctx;  /* 0x180-byte banks */
typedef struct B16Model {
    uint8_t  unk00[0x20];
    B16Ctx  *ctx;              /* +0x20 */
    uint8_t  unk24[0x30 - 0x24];
    B16Anim *anim;             /* +0x30 */
    uint8_t  unk34[0x3C - 0x34];
    struct B16Model *next;     /* +0x3C (also passed to 0x0001D7F0) */
    uint8_t  unk40[0x60 - 0x40];
    float    pos60[4];         /* +0x60 */
} B16Model;
typedef struct B16Work {
    uint32_t flags;            /* +0x00 */
    uint8_t  unk04[0x18];
    int32_t  point;            /* +0x1C index into 0x0031F0E0, <0 = player */
    uint8_t  unk20[0x1C];
    void    *obj3C;            /* +0x3C */
    uint8_t  unk40[0xC];
    void    *obj4C;            /* +0x4C */
    uint8_t  unk50[0x10];
} B16Work;                     /* 0x60 bytes */
typedef struct B16Act B16Act;
typedef int (*B16StateFn)(B16Model *m, B16Act *a);
typedef struct B16Link {
    uint8_t  unk00[4];
    void    *fn04;             /* +0x04 */
    uint8_t  unk08[8];
    int32_t  i10;              /* +0x10 */
    float    f14;              /* +0x14 */
    uint8_t  unk18[4];
    int32_t  i1C;              /* +0x1C */
    uint8_t  unk20[0xC];
    float    f2C, f30;         /* +0x2C */
    B16Model *owner;           /* +0x34 */
} B16Link;
struct B16Act {
    uint8_t  unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x4C - 0x14];
    uint32_t flags4C;          /* +0x4C */
    int32_t  state;            /* +0x50 */
    int32_t  step;             /* +0x54 */
    int32_t  animId;           /* +0x58 */
    float    timer;            /* +0x5C */
    float    animTime;         /* +0x60 */
    uint8_t  unk64[0x74 - 0x64];
    B16Work *work;             /* +0x74 */
    B16Link  link;             /* +0x78 */
    uint8_t  unkB0[0xCC - 0xB0];
    B16StateFn *fns;           /* +0xCC */
};
int  b16_SetState(B16Model *m, B16Act *a, int state);   /* 0x001671D0 */
void b16_PlayAnim(B16Model *m, B16Act *a, int id);      /* 0x00167200 */
void b16_AnimSet(B16Anim *anim, int id);
int  sub_000833E0(B16Anim *anim);
void sub_0001D7F0(void *o, int id, int b);
void b16_VecCopy(void *dst, const void *src);
void sub_001B2150(B16Link *l);
void sub_001B2160(void *bank, B16Link *l);
int  sub_00166FF0();
void sub_000D9B30(int a);
void b16_Free33A40(void *o);
void sub_00033A70(void *o);
void b16_Notify36750(B16Model *m, int b);
void sub_000414A0(int n);
void sub_001AD940(B16Ctx *c);
void sub_0001EB80(void *o);
int  sub_001C7EE1(void);
extern float  b16_points[][4];          /* 0x0031F0E0 */
extern uint8_t *b16_player;             /* 0x00420E98 */

/* ---- parameter tables at 0x0032B110 */
typedef struct B16Param { uint8_t unk00[4]; float *f4; float *f8; float *fC; int32_t *i10; uint8_t unk14[8]; int32_t *i1C; } B16Param;
typedef struct B16TabOwner { uint8_t unk000[0xD74]; int32_t base74; uint8_t unkD78[4]; int32_t base7C[2]; int32_t base84; } B16TabOwner;
extern void **b16_tables[];             /* 0x0032B110 */

/* ---- enemies using 0x00113090 */
typedef struct B16EWork { uint32_t flags; uint8_t unk04[0x28]; void *obj2C; } B16EWork;
typedef struct B16Enemy {
    uint8_t  unk000[0x58];
    int32_t  ticks;            /* +0x58 */
    uint8_t  unk05C[0x68 - 0x5C];
    float    f68;              /* +0x68 */
    uint8_t  unk06C[8];
    float    f74;              /* +0x74 */
    uint8_t  unk078[0x278 - 0x78];
    B16EWork *work;            /* +0x278 */
} B16Enemy;
int  sub_00113090(void *o, B16Enemy *e, int state);
void sub_0018C6A0(void *o);
typedef struct B16Hit { uint8_t unk00[0x50]; int32_t mode; } B16Hit;
B16Hit *sub_0001D960(void *o, int t);
extern void *b16_obj3FD7C4;             /* 0x003FD7C4 */
#endif
