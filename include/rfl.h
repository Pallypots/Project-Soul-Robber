/* Area rfl: float-returning and leftover game functions in 0x000D0000..0x0018FFFF. Names inferred. */
#ifndef RFL_H
#define RFL_H
#include "oogie.h"
#include <string.h>

/* ---------------------------------------------------------------- types */
/* Actor with a scene position at +0x60 and a yaw at +0x54. */
typedef struct RflActor {
    uint8_t  unk00[0x0C];
    uint32_t flagsC;           /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    uint8_t *part20;           /* +0x20 render part (matrix at +0x20) */
    uint8_t  unk24[0x30 - 0x24];
    void    *anim30;           /* +0x30 */
    uint8_t *p34;              /* +0x34 part (motion vector at +0x70) */
    uint8_t  unk38[0x50 - 0x38];
    float    f50;              /* +0x50 */
    float    yaw54;            /* +0x54 */
    uint8_t  unk58[0x60 - 0x58];
    float    pos60[4];         /* +0x60 */
    float    scale70;          /* +0x70 */
    uint8_t  unk74[0x80 - 0x74];
    float    v80[4];           /* +0x80 */
    uint8_t  unk90[0xF0 - 0x90];
    uint32_t flagsF0;          /* +0xF0 */
    uint8_t  unkF4[0x128 - 0xF4];
    uint32_t flags128;         /* +0x128 */
} RflActor;

/* Lock-on target: kind 1 points at another actor, kind 2 holds a point. */
typedef struct RflTarget {
    uint8_t  unk00[0xF8];
    int32_t  kindF8;           /* +0xF8 */
    uint8_t  unkFC[0x104 - 0xFC];
    void    *ref104;           /* +0x104 actor (kind 1) or start of a point (kind 2) */
} RflTarget;

/* Player record at 0x0041FEC0 (only the yaw is used here). */
typedef struct RflPlayer {
    uint8_t  unk000[0x108];
    float    yaw108;           /* +0x108 (0x0041FFC8) */
} RflPlayer;
extern RflPlayer rfl_player;           /* 0x0041FEC0 */
extern RflActor *rfl_playerObj;        /* 0x00420E98 */

/* Context at *0x0042C8E4. */
typedef struct RflCtx {
    uint8_t  unk00[0x54];
    void    *v54;              /* +0x54 */
} RflCtx;
extern RflCtx *rfl_ctx;                /* 0x0042C8E4 */

typedef struct RflTblEnt { int32_t *vals; } RflTblEnt;
extern RflTblEnt **rfl_tables32B110[]; /* 0x0032B110 */
extern int32_t rfl_level413178;        /* 0x00413178 difficulty index 0..2 */

/* ---------------------------------------------------------------- callees */
float r4_Distance(const float *a, const float *b);      /* 0x001B2730 */
float r4_DistanceXZ(const float *a, const float *b);    /* 0x001B2770 */
float sub_00113200(void *o, const float *target);
float sub_001A3EC0(float y, float x);                   /* atan2 */
float sub_001A3ED0(float x);                            /* sin */
float sub_001A3EE0(float x);                            /* cos */
float sub_001A3F20(float x);                            /* acos (Hypothesis) */
void  sub_001AD7E0(float *d, const float *s);           /* normalise */
void  sub_001AD8E0(float *d, const float *s, float a);  /* rotate about Y */
void  sub_001AD940(float *m);                           /* identity */
void  sub_001AD9B0(float *d, const float *m, const float *v); /* transform */
float sub_001AD9D0(const float *a, const float *b);     /* dot */
void  sub_001AD9F0(float *d, const float *a, const float *b); /* d = a - b */
void  sub_001ADA60(float *d, const float *a, const float *b); /* cross */
void  sub_001ADBA0(float *d, const float *s, float k);
void  sub_000F5D40(float *d, const float *s);           /* copy vector */
int   sub_001C7EE1(void);                               /* CRT rand */
void *r1b_Pool80970(void);                              /* 0x00080970 */
void  sub_000824F0(void *a, void *pool, const float *p, int b, int c, int d);
uint8_t *sub_00080CB0(void *pool, const float *p, int b);

/* Event-script context (same layout as af0's Af0Script). Handlers return
   0x1000 = branch taken, 0x2000 | n = done and skip n operand bytes,
   0x3000 = wait, 0x4000 = branch (Hypothesis). */
typedef struct RflScript {
    int32_t  unk00;
    uint8_t *pc;               /* +0x04 operand pointer */
    uint8_t  unk08[0x50 - 0x08];
    float    wait50;           /* +0x50 */
} RflScript;
#define RFL_RD16(p) ((int16_t)((p)[1] << 8) | (p)[0])
#define RFL_RD32(p) ((((((uint32_t)(p)[3] << 8) | (p)[2]) << 8 | (p)[1]) << 8) | (p)[0])
typedef union RflBits { uint32_t u; float f; } RflBits;

/* Float to int truncation. The original inlines cvttss2si where the value
   is in an SSE register (modern cl calls __ftol2_sse instead); the
   intrinsic is used only for the 32-bit x86 comparison build. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define RFL_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define RFL_FTOI(x) ((int)(x))
#endif

typedef struct RflAnimState { uint8_t unk00[8]; int32_t cur8; } RflAnimState;
typedef struct RflNode {
    uint8_t  unk00[0x30];
    RflAnimState *anim30;      /* +0x30 */
} RflNode;
typedef struct RflAnimComp {
    uint8_t  unk00[0x60];
    int32_t  anim60;           /* +0x60 */
    float    t64;              /* +0x64 */
} RflAnimComp;

extern float rfl_fps42C964;            /* 0x0042C964 */
float sub_000DE2F0(float lo, float hi);  /* random float in [lo, hi] */
float a12_GetFloat37DC54(void);          /* 0x00026640 */
int   sub_000DFE00(void);                /* script variable 0x3EE6C0 */
void  sub_00019350(int a, uint32_t b);
void  af0_SetVar3EDCF0(int v);           /* 0x000DE510 */
RflNode *sub_000DE170(int a, int b);     /* find node */
void *sub_0001D960(void *o, int kind);   /* component lookup */
void *sub_00083120(void *anim, int id);
void  sub_000832D0(void *anim, int id);
void  sub_0001D4E0(void *obj);

/* Screen element animated by the fade steps at 0x000E8220/0x000E82E0. */
typedef struct RflFadeRec { int32_t v; uint8_t unk04[0x0C]; } RflFadeRec;
typedef struct RflFadeObj {
    uint32_t flags0;           /* +0x00 */
    int32_t  mode4;            /* +0x04 */
    int32_t  unk08;
    int32_t  stateC;           /* +0x0C */
    float    t10;              /* +0x10 frame countdown */
    uint8_t  alpha14;          /* +0x14 */
    uint8_t  unk15[0x28 - 0x15];
    int32_t  i28;              /* +0x28 */
    float    f2C;              /* +0x2C */
    float    f30;              /* +0x30 */
    float    f34;              /* +0x34 */
    RflFadeRec rec38[7];       /* +0x38 */
} RflFadeObj;

/* Caption block at 0x003F43DC. */
typedef struct RflCaption {
    uint32_t flags0;           /* 0x003F43DC */
    int32_t  q[4];             /* 0x003F43E0 queue */
    int32_t  state14;          /* 0x003F43F0 */
    float    t18;              /* 0x003F43F4 */
    uint8_t  alpha1C;          /* 0x003F43F8 */
} RflCaption;
extern RflCaption rfl_caption;         /* 0x003F43DC */
extern RflCaption rfl_caption2;        /* 0x003F47B4 */
extern RflCaption rfl_caption3;        /* 0x003F4870 */
extern RflCaption rfl_caption4;        /* 0x003F4B18 */

void  sub_000720A0(float *t, int mode);  /* frame countdown */
float sub_001A3F00(float x, float y);    /* fmod */

/* Enemy record used by 0x000F6BC0. */
typedef struct RflEnemy {
    uint8_t  unk00[0x6C];
    int32_t  mode6C;           /* +0x6C */
    uint8_t  unk70[0x8C - 0x70];
    RflActor *link8C;          /* +0x8C */
    uint8_t  unk90[0xBC - 0x90];
    int16_t  doneBC;           /* +0xBC */
} RflEnemy;
extern RflEnemy *rfl_minion3F6120;       /* 0x003F6120 */
extern RflEnemy *rfl_ctl3F6128;          /* 0x003F6128 */
extern float rfl_vec318E18[4];           /* 0x00318E18 arena centre */

/* Behaviour state returned by 0x000F5F80. */
typedef struct RflAiState {
    uint8_t  unk00[0xA0];
    float    tA0;              /* +0xA0 */
    uint8_t  unkA4[0xAE - 0xA4];
    int16_t  flagAE;           /* +0xAE */
    uint8_t  unkB0[0xB4 - 0xB0];
    float    timerB4;          /* +0xB4 */
    float    waitB8;           /* +0xB8 */
    int16_t  doneBC;           /* +0xBC */
    uint8_t  unkBE[0xF0 - 0xBE];
    float    distF0;           /* +0xF0 */
    uint8_t  unkF4[0x144 - 0xF4];
    int16_t  on144;            /* +0x144 */
    int16_t  dir146;           /* +0x146 */
    float    radius148;        /* +0x148 */
    float    rate14C;          /* +0x14C */
    float    angle150;         /* +0x150 */
    uint8_t  unk154[0x184 - 0x154];
    float    vel184[4];        /* +0x184 */
} RflAiState;
typedef struct RflHelper {
    uint8_t  unk00[0xE8];
    int32_t  turnE8;           /* +0xE8 */
} RflHelper;

extern float a50_frameUnits;             /* 0x0042C858 */
extern float a50_frameSeconds;           /* 0x0042C85C */
float sub_001A3F50(float x);             /* square root */
RflAiState *sub_000F5F80(RflActor *o);   /* behaviour state of o */
RflHelper  *sub_000FC4D0(void);
int   sub_000F5D00(RflActor *o);         /* node active */
void  sub_000F62F0(RflAiState *st, int anim);
float sub_000F7C40(RflActor *a, RflActor *target, float maxStep); /* turn toward target */
float r2c_BossStepSpeed(RflActor *o);    /* 0x000F7AE0 */
float afc_VecLengthXZ(const float *v);   /* 0x000F5F50 */
void  r4c_VecAdd(float *d, const float *a, const float *b);   /* 0x001ADAF0 d = a + b */
void  sub_000C56B0(RflActor *o);
void  sub_000C62A0(RflActor *o);
void  sub_000F62C0(RflAiState *st, int step);
void  sub_001ADB60(float *d, const float *s, float k);
void  sub_000F3D10(void *owner, RflActor *o, int a);

/* Boss health component (kind 5 of 0x0001D960). */
typedef struct RflHealth {
    uint8_t  unk00[0x54];
    float    hp54;             /* +0x54 */
    uint8_t  unk58[0x90 - 0x58];
    RflActor *link90;          /* +0x90 */
} RflHealth;
float sub_000F3C70(RflActor *o);         /* pending damage (acb_GetBoss5C) */
int   sub_000F3CB0(RflActor *o);         /* pending flags (acb_GetBoss60) */
void  sub_000F3BF0(RflActor *o, float amt, int flags); /* add pending damage */
void  sub_000F3C40(RflActor *o);         /* clear pending damage */

/* Enemy body used by the step choosers at 0x001238A0/0x00126090. */
typedef struct RflBodyState { uint8_t unk00[4]; uint32_t flags4; } RflBodyState;
typedef struct RflBody {
    uint8_t  unk00[0x20];
    uint32_t flags20;          /* +0x20 */
    uint8_t  unk24[0x278 - 0x24];
    RflBodyState *state278;    /* +0x278 */
} RflBody;
int   sub_000833E0(void *anim);          /* animation idle */
int   r2_PlayerOutOfReach(RflBody *obj, RflActor *self);  /* 0x00120820 obj=EAX self=ESI */
int   r2_RunSteps31C110(int idx, RflActor *a, RflBody *b); /* 0x0011EDE0 idx=EAX a=EBX b=EDI */
void  sub_0011F2B0(RflActor *obj, int k, RflBody *a);     /* obj=EDI k=EBX */

/* Enemy (foe) record used by the state choosers at 0x00138B40.. */
typedef struct RflFoeTarget {
    uint8_t  unk00[4];
    int32_t  state4;           /* +0x04 */
    int32_t  i8;               /* +0x08 */
    uint32_t flagsC;           /* +0x0C */
} RflFoeTarget;
typedef struct RflTimer { uint8_t unk00[0x10]; int32_t v10; } RflTimer;
typedef struct RflFoe {
    uint8_t  unk00[0x20];
    uint32_t flags20;          /* +0x20 */
    uint8_t  unk24[0x4C - 0x24];
    uint32_t flags4C;          /* +0x4C */
    uint8_t  unk50[0x58 - 0x50];
    int32_t  step58;           /* +0x58 */
    float    t5C;              /* +0x5C */
    uint8_t  unk60[0x64 - 0x60];
    int32_t  anim64;           /* +0x64 */
    uint8_t  unk68[0x74 - 0x68];
    float    f74;              /* +0x74 */
    float    v78[4];           /* +0x78 */
    float    v88[4];           /* +0x88 */
    uint8_t  unk98[0xF8 - 0x98];
    int32_t  kindF8;           /* +0xF8 */
    float    angleFC;          /* +0xFC */
    float    dist100;          /* +0x100 */
    RflFoeTarget *target104;   /* +0x104 */
    uint8_t  unk108[0x278 - 0x108];
    RflBodyState *body278;     /* +0x278 */
} RflFoe;
int   r3_CheckConds135730(int table, RflActor *obj, void *act); /* 0x00135730 table=EAX obj=EBX act=EDI */
void  r3_SetStateB(RflActor *obj, void *act, int state);       /* 0x00135A70 obj=ESI act=EDI state=stack */
void  sub_00113480(RflFoe *e, int slot);
void  sub_00113040(void *owner, RflFoe *e, int state);
void  sub_00113090(void *owner, RflFoe *e, int anim);
RflTimer *sub_00113430(RflFoe *e, int slot);
int   a80_Get3ED238(void);               /* 0x00087500 */
void *sub_00113400(RflFoe *e, int slot);
extern float rfl_f3F7504;                /* 0x003F7504 */
typedef int (*RflCheckFn)(RflActor *o, RflFoe *e, const float *lim);
extern RflCheckFn rfl_checks31CE18[];    /* 0x0031CE18 */
extern RflCheckFn rfl_checks31D0B8[];    /* 0x0031D0B8 */
extern const float rfl_lim279798[];      /* 0x00279798 */
extern const float rfl_lim2797C8[];      /* 0x002797C8 */
void  sub_0001D610(RflActor *o);
void  sub_001AEDD0(void *inst, int v);
typedef struct RflAnimInst { uint8_t unk00[0x14]; void *inst14; } RflAnimInst;
typedef struct RflAnimKey { uint8_t unk00[0x10]; int32_t v10; } RflAnimKey;

/* Pickup actor record (0x00167xxx): +0x50 state, +0x74 link. */
typedef struct RflLink { uint32_t flags0; uint8_t unk04[0x1C - 4]; float pos1C[4]; } RflLink;
typedef struct RflPick {
    uint8_t  unk00[0x50];
    uint32_t state50;          /* +0x50 */
    uint8_t  unk54[0x74 - 0x54];
    RflLink *link74;           /* +0x74 */
} RflPick;
float sub_00113290(RflActor *o, const float *pt);   /* vertical angle to pt */
void  sub_001671D0(RflActor *o, RflPick *e, int state);
void  sub_00167200(RflActor *o, RflPick *e, int anim);

/* Trap/turret record (0x0016Dxxx..0x00170xxx): step at +0x54, link at +0x74. */
typedef struct RflTrapLink {
    uint32_t flags0;           /* +0x00 */
    uint8_t  unk04[0x0C - 0x04];
    float    pt0C[4];          /* +0x0C aim point */
    uint8_t  unk1C[0x20 - 0x1C];
    float    v20[4];           /* +0x20 */
    uint8_t  unk30[0x40 - 0x30];
    float    f40;              /* +0x40 */
} RflTrapLink;
typedef struct RflTrap {
    uint8_t  unk00[0x4C];
    uint32_t flags4C;          /* +0x4C */
    int32_t  mode50;           /* +0x50 */
    int32_t  step54;           /* +0x54 */
    float    f58;              /* +0x58 */
    float    t5C;              /* +0x5C */
    float    v60[3];           /* +0x60 */
    float    f6C;              /* +0x6C */
    uint8_t  unk70[0x74 - 0x70];
    RflTrapLink *link74;       /* +0x74 */
    float    v78[4];           /* +0x78 */
} RflTrap;
float sub_00082D70(const float *v);      /* vector length */
void  r3_SetState16C820(RflTrap *a, RflActor *m, int state);  /* 0x0016C820 a=EAX m=EDI state=stack */
uint8_t *sub_0001D0F0(RflActor *o, int k);

/* ---------------------------------------------------------------- rfl */
float rfl_ActorHeading(const RflActor *a);
float rfl_TurnDelta(RflActor *a, const float *pos);
float rfl_TurnToward(RflActor *a, const float *pos, float maxStep);
float rfl_TargetDistance(RflActor *obj, RflTarget *t);
float rfl_TargetDistanceXZ(RflActor *obj, RflTarget *t);
float rfl_TargetDistance113200(void *obj, RflTarget *t);
float rfl_FacingAngleXZ(RflActor *a, float x, float z);
float rfl_AngleFromZ(const float *dir);
float rfl_PickDistance(const float *pos, int b, int c, int d, void *out);
float rfl_TableValue(int tbl, int row, int col);
float rfl_PlayerAngleTo(const float *pos);
void  rfl_ActorStep(RflActor *a, float dist);
void  rfl_MtxRotateAxis(float *dst, float *m, const float *axis, float angle);
void  rfl_VecScaledDir(float *dst, float *v, float k);
int   rfl_FacingInRange(RflActor *a, float x, float z, float lo, float hi);
int   rfl_TurnFacingXZ(RflActor *a, float x, float z, float maxStep);
int   rfl_TurnFacingXZAxis(RflActor *a, float x, float z, float maxStep);
float sub_001A3F30(float v);                            /* absolute value */
int   sub_001A8830(float *m, const float *q);           /* quaternion to matrix */
void  sub_001AD7C0(float *d, const float *a, const float *b); /* matrix product */

#endif
