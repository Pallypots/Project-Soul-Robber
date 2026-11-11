#ifndef R3D_H
#define R3D_H
#include "oogie.h"
#include "shared_decls.h"
#include "r3c.h"
#include <string.h>

/* Float to int truncation and block zeroing. The original inlines cvttss2si and rep stosd;
   the intrinsics are used only for the 32-bit x86 comparison build. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#include <xmmintrin.h>
#define R3D_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#define R3D_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) >> 2)
#else
#define R3D_FTOI(x) ((int)(x))
#define R3D_ZERO(p, n) memset((p), 0, (n))
#endif
/* Area r3d: more game functions in 0x00130000..0x00190000 (stack and register arguments).
   All names inferred. Register mappings are in the comments and in config/function_states_r3d.csv.
   Object views (R3cObj, R3cWork, ...) and many callee prototypes come from r3c.h. */

/* Work block of a kind-6 component: three reference slots at +0x24. */
typedef struct R3dRefs {
    uint8_t  unk00[0x10];
    uint32_t flags10;        /* +0x10 */
    uint8_t  unk14[0x24 - 0x14];
    union { void *refs24[3]; struct { void *pad24; void *refs28[3]; }; }; /* +0x24 / +0x28 slot lists */
} R3dRefs;

/* Kind-7 component (only touched fields). */
typedef struct R3dComp7 {
    uint8_t  unk00[0x60];
    int32_t  mode60;         /* +0x60 index into fns88 */
    uint8_t  unk64[0x6C - 0x64];
    float    f6C, f70;       /* +0x6C timer up, +0x70 timer down */
    uint8_t  unk74[0x7C - 0x74];
    R3cCompFn fn7C;          /* +0x7C tick */
    uint8_t  unk80[0x88 - 0x80];
    R3cCompFn *fns88;        /* +0x88 per-mode handlers */
} R3dComp7;

/* Work block view reaching the vector at +0x160. */
typedef struct R3dWork160 { uint8_t unk00[0x160]; float v160[4]; } R3dWork160;
/* Node returned by 0x00113400 (four timer values at +0x10). */
typedef struct R3dNode {
    uint8_t unk00[0x10];
    union { float f10; int32_t i10; }; /* +0x10 */
    union { float f14; int32_t i14; }; /* +0x14 */
    union { float f18; int32_t i18; }; /* +0x18 */
    union { float f1C; int32_t i1C; }; /* +0x1C */
} R3dNode;
/* Blend motion block (set up by 0x00156180/0x001561D0). */
typedef struct R3dMotion {
    uint8_t unk00[0x0C];
    float   speed0C;         /* +0x0C */
    float   t10;             /* +0x10 blend 0..1 */
    float   v14[4];          /* +0x14 current / start */
    float   v24[4];          /* +0x24 target */
} R3dMotion;
/* Actor view for fields that R3cObj types differently. */
typedef struct R3dAct {
    uint8_t  unk00[0x20];
    uint32_t flags20;        /* +0x20 */
    uint8_t  unk24[0x58 - 0x24];
    int32_t  i58;            /* +0x58 */
    uint8_t  unk5C[0x6C - 0x5C];
    int32_t  h6C;            /* +0x6C handle (-1 none) */
    void    *h70;            /* +0x70 block */
    uint8_t  unk74[0x78 - 0x74];
    float    v78[4];         /* +0x78 velocity */
    float    v88[4];         /* +0x88 */
} R3dAct;
/* Record of the 4-entry pair table at 0x003FE2D8 (named in area b7c). */
typedef struct R3dPair { R3cObj *a; R3cObj *b; R3cObj *owner; int32_t key; uint8_t unk10[0x24 - 0x10]; } R3dPair;
/* Work block view with a velocity at +0x34 and a distance at +0x44. */
typedef struct R3dWork34 { uint8_t unk00[0x34]; float v34[4]; float f44; } R3dWork34;
/* Motion block view (act+0x74). */
typedef struct R3dBlk74 {
    union { uint32_t flags; struct { int16_t s00, s02; }; }; /* +0x00 flags; +0x02 effect handle */
    float    f04, f08;       /* +0x04 rate, +0x08 */
    uint8_t  unk0C[0x20 - 0x0C];
    float    f20, f24, f28, f2C; /* +0x20 vector */
    uint8_t  unk30[0x40 - 0x30];
    float    f40;            /* +0x40 */
} R3dBlk74;
/* Model context behind obj+0x20: 0x180-byte banks at +0xC4. */
typedef struct R3dBank { uint8_t unk00[0x74]; float f74; uint8_t unk78[0x180 - 0x78]; } R3dBank;
typedef struct R3dCtx { uint8_t unk00[0x74]; float f74; uint8_t unk78[0xC4 - 0x78]; R3dBank *banksC4; } R3dCtx;
/* 16-byte condition records and their dispatchers (named in area r3b). */
typedef struct R3dRec16 { int32_t i[4]; } R3dRec16;
typedef int (*R3dDispFn)(void *a, void *b, R3dRec16 *rec);

/* Work block view (act+0x278) for the functions that use these offsets. */
typedef struct R3dWork {
    uint32_t flags00;        /* +0x00 */
    uint8_t  unk04[0x0C - 0x04];
    float    f0C;            /* +0x0C */
    union { float f10; int32_t i10; void *p10; }; /* +0x10 (p: effect handle) */
    union { float f14; int32_t i14; void *p14; }; /* +0x14 */
    union { float f18; int32_t i18; void *p18; }; /* +0x18 */
    union { float f1C; int32_t i1C; void *p1C; }; /* +0x1C */
    float    f20;            /* +0x20 */
    union { float f24; int32_t i24; void *p24; }; /* +0x24 */
    union { float f28; int16_t s28; int32_t i28; }; /* +0x28 */
    float    f2C, f30;       /* +0x2C, +0x30 */
    uint8_t  unk34[0x40 - 0x34];
    uint32_t flags40;        /* +0x40 */
    uint8_t  unk44[0x50 - 0x44];
    union { uint32_t flags50; float f50; }; /* +0x50 */
    uint8_t  unk54[0x58 - 0x54];
    int32_t  i58;            /* +0x58 step counter */
    uint8_t  unk5C[0x88 - 0x5C];
    float    f88, f8C;       /* +0x88, +0x8C */
    uint8_t  unk90[0x94 - 0x90];
    float    f94, f98;       /* +0x94, +0x98 */
} R3dWork;

/* Fade request record passed to 0x001471F0. */
typedef struct R3dFade { int32_t state; uint8_t unk04[0x10 - 4]; float f10; } R3dFade;
/* Hold records used by 0x00188C00 (as released by 0x00189510). */
typedef struct R3dHold2 {
    R3cObj  *obj;            /* +0x00 */
    uint8_t  unk04[0x14 - 4];
    float    f14;            /* +0x14 timer */
    uint8_t  unk18[0x24 - 0x18];
    float    f24[3];         /* +0x24 per-row factors */
    uint8_t  unk30[0x44 - 0x30];
    float   *m44;            /* +0x44 matrix */
} R3dHold2;
typedef struct R3dHold { int32_t state; float f4; int32_t i8; R3dHold2 *pC; } R3dHold;

/* Turn limits record passed to 0x00139540. */
typedef struct R3dLimits { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } R3dLimits;

/* ---- globals */
extern R3dPair    b7c_idRecs3FE2D8[4];               /* 0x003FE2D8 (area b7c) */
extern R3cId0C    b4c_sndTab279924[4];               /* 0x00279924 (area b4c): id at +0 */
extern uint8_t    r3d_blk3FDC3C[0x30];               /* 0x003FDC3C state block */
extern int32_t    r3d_ids32B208[24];
extern int32_t    b7c_taskId3FD7CC;                  /* 0x003FD7CC (area b7c) */
extern int32_t    r3d_i3FD7D8;                       /* 0x003FD7D8 sound request state */
extern R3cObj    *r3d_objs3FE050[3];                 /* 0x003FE050 pending objects */
extern float      r3d_f3FE05C;                       /* 0x003FE05C */
extern int32_t    r3d_i3FE0B8;                       /* 0x003FE0B8 */                 /* 0x0032B208 sound ids */
extern const float *r3d_vecs31F3E0[];                 /* 0x0031F3E0 preset positions by slot */
extern R3dRec16  r3b_recs279728[];                    /* 0x00279728 (area r3b) */
extern R3dDispFn r3b_disp31CDFC[];                    /* 0x0031CDFC (area r3b) */
extern float     r3d_rate32B698[];                    /* 0x0032B698 spin rate */
extern int32_t   b7c_stage3FE060;                     /* 0x003FE060 (area b7c) */
extern void    *b16_task3F8400;                       /* 0x003F8400 (named in area b16) */
extern int32_t  b16_taskId3F8404, b16_taskId3F92EC;   /* 0x003F8404, 0x003F92EC (area b16) */
extern int32_t  r3d_i3F8408, r3d_i3F840C;             /* 0x003F8408, 0x003F840C */
extern R3cRecD4 r3d_recs3F76C0[16];                   /* 0x003F76C0 */
extern int32_t  r3d_i31F024;                          /* 0x0031F024 */
extern int32_t  r3d_i3F9300;                          /* 0x003F9300 sound request state */

/* ---- callees (stack arguments unless stated) */
int b16_Buf3F8C98Init(void);                      /* 0x0016C3B0 (area b16) */
int b16_Pool20Init(void);                         /* 0x00169710 (area b16) */
int b16_Pool60Init(void);                         /* 0x001675D0 (area b16) */
int b16_Pool18Init(void);                         /* 0x0016B880 (area b16) */
void    sub_00033B30(void *o);
void    r2b_ClearBit(int i);                          /* 0x000D9B30 (area r2b) */
void    r2b_SetBit(int i);                            /* 0x000D9AB0 (area r2b) */
void    sub_0001D4E0(void *o);
R3dNode *sub_00113400(void *act, int key);
void    sub_0017F390(void);
void    sub_00182770(int k);
int     r2b_TestBit(int i);                           /* 0x000D9A70 (area r2b) */
void    b4c_MotionSet156180(void *w, float a, float b, float c, float t); /* 0x00156180 (area b4c) */
void    sub_000EE850(void *o, float v);
int     sub_00048100(int h);
float   sub_001B27C0(const float *a, const float *b);
void    sub_001561D0(void *w, float a, float b);
void    sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
void    sub_001ADBA0(float *d, const float *s, float k);
void    sub_000A7950(int h);
void    sub_000C56B0(void *o);
void    r4c_Spin(void *o, const float *rate);         /* 0x000F6450 (area r4c) */
float   r4c_VecLenXZ(const float *v);                 /* 0x000F5F50 (area r4c) */

#endif
