#ifndef RBI_H
#define RBI_H
#include "oogie.h"
#include "shared_decls.h"
#include "rbh.h"

/* Area rbi: larger game functions in 0x000D0000..0x0018FFFF (Jack's moves, enemy AI, script
   handlers, stage logic, effects). All names inferred. Register mappings are in the comments
   and in config/function_states_rbi.csv. */

/* Float to int truncation (same as RFL_FTOI in rfl.h). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define RBI_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define RBI_FTOI(x) ((int)(x))
#endif

typedef struct RbiVec4 { float x, y, z, w; } RbiVec4;

/* ------------------------------------------------------------ shared math */
float r6c_AngleAdd(float a, float b);                                    /* 0x000829D0 wrapped sum */
void  r6c_RotateVec(RbiVec4 *out, const RbiVec4 *rot, const RbiVec4 *v); /* 0x00082A30 */
void  rbi_VecAdd(RbiVec4 *d, const RbiVec4 *a, const RbiVec4 *b);         /* 0x001ADAF0 d = a + b */

/* ------------------------------------------------------------ globals */
extern float a50_frameUnits;                     /* 0x0042C858 frame time in 1/60 s units */

/* ------------------------------------------------------------ Jack (0x0041FEC0, the PlayerStats object) */
typedef struct RbiJack {
    RbiVec4  pos;             /* +0x000 position */
    uint8_t  unk010[0xD4 - 0x10];
    int32_t  modeD4;          /* +0x0D4 */
    int32_t  stateD8;         /* +0x0D8 */
    uint8_t  unkDC[0xF4 - 0xDC];
    float    yawF4;           /* +0x0F4 */
    float    yawF8;           /* +0x0F8 */
    float    yawFC;           /* +0x0FC facing */
    float    dir100;          /* +0x100 stick direction latched while turning */
    float    dir104;          /* +0x104 last stick direction */
    uint8_t  unk108[0x110 - 0x108];
    float    velX110;         /* +0x110 */
    uint8_t  unk114[4];
    float    velZ118;         /* +0x118 */
    uint8_t  unk11C[4];
    int32_t  turning120;      /* +0x120 */
    uint8_t  unk124[4];
    int32_t  anim128;         /* +0x128 */
    int32_t  anim12C;         /* +0x12C requested animation */
    uint8_t  unk130[0x150 - 0x130];
    int32_t  flags150;        /* +0x150 (sign bit: hidden) */
    uint8_t  unk154[0x1B8 - 0x154];
    int32_t  i1B8;            /* +0x1B8 */
    uint8_t  unk1BC[0xFD8 - 0x1BC];
    void    *nodeFD8;         /* +0xFD8 model node */
} RbiJack;
/* Child node of Jack's model (0x0001D290), only the touched fields. */
typedef struct RbiNode {
    uint8_t  unk00[0xC];
    uint32_t flags0C;         /* +0x0C bit 0x10000: frozen */
    uint8_t  unk10[0x20 - 0x10];
    RbiVec4 *mtx20;           /* +0x20 4x4 matrix (4 rows) */
    uint8_t  unk24[0x70 - 0x24];
    RbiVec4  scale70;         /* +0x70 */
} RbiNode;
RbiNode *rbi_Child1D290(void *model, int id);             /* 0x0001D290 */
void  rbi_ChildHide1D4B0(void *model, int id);            /* 0x0001D4B0 */
void  rbi_SetChildAnimD0560(RbiJack *p, int anim, int id);/* 0x000D0560 */
void  rbi_MatLoad385D0(RbiVec4 *dst, const RbiVec4 *src); /* 0x000385D0 */
void  rbi_MatCopy(RbiVec4 *dst, const RbiVec4 *src);      /* 0x001ADA40 */
void  rbi_VecScale(RbiVec4 *d, const RbiVec4 *s, float k);/* 0x001ADBA0 d = s * k */
void  rbi_VecCopy(RbiVec4 *d, const RbiVec4 *s);          /* 0x000F5D40 */

/* ------------------------------------------------------------ enemy actors (0x00130000 family) */
typedef void (*RbiFn)();   /* callback slot; callees take varying arguments */
/* Scene object of an enemy (passed in ESI), only the touched fields. */
typedef struct RbiObj {
    uint8_t  unk00[4];
    int32_t  kind04;          /* +0x04 */
    int32_t  var08;           /* +0x08 variant (nonzero: large) */
    uint32_t flags0C;         /* +0x00C */
    uint32_t flags10;         /* +0x010 */
    uint8_t  unk14[0x70 - 0x14];
    RbiVec4  scale70;         /* +0x070 */
    uint8_t  unk80[0xB0 - 0x80];
    float    fB0;             /* +0x0B0 */
    float    fB4;             /* +0x0B4 */
    uint8_t  unkB8[0xD0 - 0xB8];
    int32_t  iD0;             /* +0x0D0 */
    uint8_t  unkD4[0xDC - 0xD4];
    float    fDC;             /* +0x0DC */
    uint8_t  unkE0[0xE8 - 0xE0];
    float    fE8;             /* +0x0E8 */
    int32_t  iEC;             /* +0x0EC */
    int32_t  iF0, iF4;        /* +0x0F0 */
    uint8_t  unkF8[0xFC - 0xF8];
    float    fFC;             /* +0x0FC */
    uint8_t  unk100[0x118 - 0x100];
    int32_t  i118, i11C, i120, i124; /* +0x118 */
} RbiObj;
/* Work block at act+0x278 (enemy family 0x0013D000/0x00140000). */
typedef struct RbiWorkG {
    uint8_t  unk00[8];
    int32_t  i08;             /* +0x08 */
    int32_t  i0C;             /* +0x0C */
    float    f10;             /* +0x10 */
} RbiWorkG;
/* Actor component (passed in EDI), only the touched fields. */
typedef struct RbiAct {
    uint8_t  unk00[0x24];
    int32_t  i24;             /* +0x024 */
    float    f28, f2C;        /* +0x028 */
    const void *tab30;        /* +0x030 */
    uint8_t  unk34[0x40 - 0x34];
    RbiFn    fn40;            /* +0x040 */
    uint8_t  unk44[0x4C - 0x44];
    uint32_t flags4C;         /* +0x04C */
    int32_t  i50, i54;        /* +0x050 state, previous state */
    uint8_t  unk58[0x270 - 0x58];
    float    f270;            /* +0x270 max health */
    float    f274;            /* +0x274 health */
    void    *work278;         /* +0x278 */
    RbiFn    fn27C;           /* +0x27C */
    RbiFn    fn280, fn284;    /* +0x280 */
    RbiFn    fn288;           /* +0x288 */
    const void *tab28C;       /* +0x28C */
    const void *tab290;       /* +0x290 */
    const void *tab294;       /* +0x294 */
    RbiFn    fn298;           /* +0x298 */
    RbiFn    fn29C;           /* +0x29C */
} RbiAct;
void  sub_00113E90(RbiObj *obj, RbiAct *act, const void *tab);
void  r2d_HookAttach(RbiObj *obj, RbiAct *act, int idx);       /* 0x00114400 */
float sub_00171D50(int kind, int id, int v);                   /* health of a kind */
int   sub_0001BC40(RbiObj *obj);
void  sub_00137C30(void);
void  sub_00137C70(void);
void  sub_0013AB30(void);
void  sub_0013AD50(void);
void  sub_0013D2F0(void);
void  sub_0013D630(void);
void  sub_0013D990(void);
void  sub_0013D910(void);
extern const uint8_t rbi_tab31CC20[], rbi_tab31CC74[], rbi_tab31CC80[], rbi_tab31CD28[],
                     rbi_tab31CDD0[];
extern const uint8_t rbi_tab31CEDC[], rbi_tab31CF00[], rbi_tab31CFC8[], rbi_tab31D08C[];


/* ------------------------------------------------------------ collision push-out */
typedef struct RbiBody {
    uint8_t  unk00[0x60];
    RbiVec4  pos60;           /* +0x060 */
    uint8_t  unk70[0xD8 - 0x70];
    RbiVec4  ofsD8;           /* +0x0D8 centre offset */
    float    radE8;           /* +0x0E8 radius */
    uint8_t  unkEC[4];
    uint8_t  colF0[4];        /* +0x0F0 collision filter */
} RbiBody;
extern uint32_t aa0_flags420010;                                   /* 0x00420010 */
uint8_t *rbi_Collide1B450(const RbiVec4 *pos, float r, const int32_t *mask, void *filter); /* 0x0001B450 */
float rbi_VecLen82D70(const RbiVec4 *v);                           /* 0x00082D70 */
void  rbi_VecSub(RbiVec4 *d, const RbiVec4 *a, const RbiVec4 *b);  /* 0x001AD9F0 d = a - b */
void  rbi_VecNorm(RbiVec4 *d, const RbiVec4 *s);                   /* 0x001AD7E0 */

/* ------------------------------------------------------------ three-key curves */
/* Slice record carved by 0x00062050 (six slices of n floats). */
typedef struct RbiSlices { int32_t unk00; float *s[6]; } RbiSlices;      /* 0x1C bytes */
/* Three curves of three keys (times 0, 0.5, 1) with their buffers. */
typedef struct RbiCurves {
    RbiSlices rec[3];            /* +0x00 */
    uint8_t   unk54[8];
    float     buf5C[3][30];      /* +0x5C one buffer per curve */
} RbiCurves;
typedef struct RbiWorkCv184 { uint8_t unk00[0x184]; RbiCurves cv; } RbiWorkCv184;
/* The same with 18-float buffers. */
typedef struct RbiCurvesS {
    RbiSlices rec[3];            /* +0x00 */
    float     t54;               /* +0x54 curve time */
    float     rate58;            /* +0x58 curve speed per frame unit */
    float     buf5C[3][18];      /* +0x5C */
} RbiCurvesS;
typedef struct RbiWorkCv10  { uint8_t unk00[0x10];  RbiCurvesS cv; } RbiWorkCv10;
typedef struct RbiWorkCvC   { uint8_t unk00[0xC];   RbiCurvesS cv; } RbiWorkCvC;
float r4_Distance(const float *a, const float *b);   /* 0x001B2730 */
typedef struct RbiWorkCv88  { uint8_t unk00[0x88];  RbiCurvesS cv; } RbiWorkCv88;
typedef struct RbiWorkCv84  { uint8_t unk00[0x84];  RbiCurvesS cv; } RbiWorkCv84;
void  rbi_SetSlices62050(RbiSlices *s, float *base, int n);     /* 0x00062050 */
void  rbi_Curve61C50(RbiSlices *s, int n);                      /* 0x00061C50 build the curve */

/* ------------------------------------------------------------ boss effect set-up (0x000FBD50 / 0x001003A0) */
typedef struct RbiFxObj {
    uint8_t  unk00[0xC];
    uint32_t flags0C;         /* +0x0C */
    uint8_t  unk10[0x70 - 0x10];
    RbiVec4  scale70;         /* +0x070 */
    uint8_t  unk80[0xF0 - 0x80];
    int32_t  iF0, iF4;        /* +0x0F0 */
    uint8_t  unkF8[0x11C - 0xF8];
    int32_t  i11C, i120, i124;/* +0x11C */
} RbiFxObj;
typedef struct RbiFxComp { uint8_t unk00[0x18]; float f18, f1C; } RbiFxComp;
/* Boss controller objects (*0x003F6128 and *0x003F6114), only the touched fields. */
typedef struct RbiBossCtl {
    uint8_t  unk00[0x74];
    const void *p74, *p78;    /* +0x74 */
    uint8_t  unk7C[0xC0 - 0x7C];
    float    fC0, fC4;        /* +0xC0 */
    const RbiVec4 *colC8[6];  /* +0xC8 */
} RbiBossCtl;
extern RbiBossCtl *b10_ctl;                       /* 0x003F6128 */
extern RbiBossCtl *afc_body;                      /* 0x003F6114 */
RbiFxComp *rbi_Comp1D960(void *o, int kind);      /* 0x0001D960 find component */
void  sub_000F5D60(void *o, float a, float b, float c, const float *v);
void  sub_000F5DD0(void *o, float a, float b, const float *v);
void  sub_000F90D0(RbiBossCtl *c);
extern const float rbi_v278D20[], rbi_v278D34[], rbi_v278D44[], rbi_v278D54[];
extern const float rbi_v278A88[], rbi_v278A9C[], rbi_v278AAC[], rbi_v278ABC[];
extern const uint8_t rbi_d319368[], rbi_d319410[], rbi_d319078[], rbi_d3190F8[];
extern const RbiVec4 rbi_c318EF8, rbi_c318F08, rbi_c318F18, rbi_c318F28, rbi_c318F38, rbi_c318F48;
extern const RbiVec4 rbi_c318FB8, rbi_c318FC8, rbi_c318FD8, rbi_c318FE8, rbi_c318FF8, rbi_c319008;

/* ------------------------------------------------------------ hit shapes from bone positions */
typedef struct RbiShapeObj {
    uint8_t  unk00[0x60];
    RbiVec4  pos60;           /* +0x060 */
    uint8_t  unk70[0xA0 - 0x70];
    RbiVec4  cA0;             /* +0x0A0 shape 1 centre */
    float    rB0;             /* +0x0B0 shape 1 radius */
    float    hB4;             /* +0x0B4 shape 1 height */
    uint8_t  unkB8[0xD8 - 0xB8];
    RbiVec4  cD8;             /* +0x0D8 shape 2 centre */
    float    rE8;             /* +0x0E8 shape 2 radius */
    uint8_t  unkEC[0xF8 - 0xEC];
    RbiVec4  aF8;             /* +0x0F8 segment start */
    RbiVec4  b108;            /* +0x108 segment end */
} RbiShapeObj;
void  rbi_PartMatrix145F40(void *obj, int part, RbiVec4 *m);   /* 0x00145F40 world matrix of a part */

/* ------------------------------------------------------------ thrown particles */
typedef struct RbiParticle {
    uint8_t  unk00[0xB4];
    float    gravB4;          /* +0x0B4 */
    float    velB8[3];        /* +0x0B8 */
    float    rotC4[3];        /* +0x0C4 rotation speed */
    float    angD0;           /* +0x0D0 */
    uint8_t  unkD4[0xF8 - 0xD4];
    float    fF8;             /* +0x0F8 */
} RbiParticle;
typedef struct RbiSpinner { uint8_t unk00[0x50]; float spin50; } RbiSpinner;
extern float a50_framesPerSecond;                 /* 0x0042C964 */
void  sub_000F3B00(void *o, int v);
void  sub_000F3B30(void *o, int v);
void  sub_000F3F00(void *o, float v);

/* ------------------------------------------------------------ effect stop */
typedef struct RbiFxNode { uint8_t unk00[0xC]; uint32_t flags0C; } RbiFxNode;
typedef struct RbiFxWork {
    uint8_t    unk00[0x54];
    float      f54;               /* +0x054 */
    uint8_t    unk58[0xC8 - 0x58];
    RbiFxNode *partC8;            /* +0x0C8 */
    uint8_t    unkCC[0xFC - 0xCC];
    int32_t    zFC[20];           /* +0x0FC cleared on stop */
    uint8_t    unk14C[0x15C - 0x14C];
    float      v15C[4];           /* +0x15C */
    uint8_t    unk16C[0x188 - 0x16C];
    int32_t    i188, i18C;        /* +0x188 */
    float      f190;              /* +0x190 */
} RbiFxWork;
void  sub_000F3D70(RbiFxNode *o);
void  sub_000F3BB0(RbiFxNode *o, int a, int b);
void  sub_00019000(void *list, int v);
void  sub_0001D700(RbiFxNode *o);

/* ------------------------------------------------------------ enemy set-up at 0x00108790 */
typedef struct RbiEnemyObj {
    uint8_t  unk00[4];
    int32_t  kind04;          /* +0x004 */
    int32_t  var08;           /* +0x008 */
    uint32_t flags0C;         /* +0x00C */
    uint8_t  unk10[0x50 - 0x10];
    RbiVec4  rot50;           /* +0x050 */
    RbiVec4  pos60;           /* +0x060 */
    RbiVec4  scale70;         /* +0x070 */
    uint8_t  unk80[0xA4 - 0x80];
    float    fA4;             /* +0x0A4 */
    uint8_t  unkA8[0xB0 - 0xA8];
    float    fB0, fB4;        /* +0x0B0 */
    uint8_t  unkB8[0xD0 - 0xB8];
    int32_t  iD0;             /* +0x0D0 */
    uint8_t  unkD4[0xE8 - 0xD4];
    float    fE8;             /* +0x0E8 */
    int32_t  iEC, iF0, iF4;   /* +0x0EC */
    uint8_t  unkF8[0xFC - 0xF8];
    float    fFC;             /* +0x0FC */
    uint8_t  unk100[0x118 - 0x100];
    int32_t  i118, i11C, i120, i124; /* +0x118 */
    uint8_t  unk128[0x15C - 0x128];
    uint32_t flags15C;        /* +0x15C copy of flags0C */
} RbiEnemyObj;
/* Component kind 0xD (hit handler). */
typedef struct RbiHitComp2 {
    uint8_t  unk00[0x10];
    uint32_t flags10;         /* +0x10 */
    int32_t  i14;             /* +0x14 */
    float    f18, f1C;        /* +0x18 */
    const void *tab20;        /* +0x20 */
    RbiFn    fn24, fn28, fn2C;/* +0x24 */
} RbiHitComp2;
/* Component kind 5 (state). */
typedef struct RbiStateComp {
    uint8_t  unk00[0x4C];
    int32_t  i4C;             /* +0x4C */
    uint8_t  unk50[0x54 - 0x50];
    float    hp54, hpMax58;   /* +0x54 */
    uint8_t  unk5C[0x64 - 0x5C];
    void    *game64;          /* +0x64 */
    uint8_t  unk68[0xA0 - 0x68];
    float    fA0, fA4;        /* +0xA0 */
    int32_t  iA8;             /* +0xA8 */
    RbiVec4  vAC;             /* +0xAC */
    float    fBC;             /* +0xBC */
    RbiVec4  vC0;             /* +0xC0 */
    float    fD0, fD4, fD8;   /* +0xD0 */
} RbiStateComp;
void  sub_000EE270(RbiHitComp2 *c);
void  sub_000F3AA0(RbiStateComp *c);
void  sub_000F3B70(void *o, int v);
void  sub_001063C0(void);
void  sub_00107490(void);
void  sub_001083E0(void);
extern const uint8_t rbi_tab319644[];

/* ------------------------------------------------------------ grabbed / knocked-back state entries */
/* Render node of an enemy (obj+0x20): a 3x4 basis followed by more data. */
typedef struct RbiBasis { RbiVec4 x00, y10, z20; } RbiBasis;
typedef struct RbiKbObj {
    uint8_t   unk00[0xC];
    uint32_t  flags0C;        /* +0x0C */
    uint32_t  flags10;        /* +0x10 */
    uint8_t   unk14[0x20 - 0x14];
    RbiBasis *basis20;        /* +0x20 */
} RbiKbObj;
typedef struct RbiKbAct {
    uint8_t   unk00[0x4C];
    uint32_t  flags4C;        /* +0x04C */
    uint8_t   unk50[0x88 - 0x50];
    RbiVec4   vel88;          /* +0x088 */
    uint8_t   unk98[0x278 - 0x98];
    void     *work278;        /* +0x278 */
} RbiKbAct;
/* Work block of the enemy at 0x00153C20 (act+0x278), only the touched fields. */
typedef struct RbiKbWork153 {
    uint32_t  flags00;        /* +0x00 */
    uint8_t   unk04[0x40 - 4];
    RbiVec4   target40;       /* +0x40 */
    uint32_t  flags50;        /* +0x50 */
} RbiKbWork153;
/* Work block of the enemy at 0x00159BF0 (act+0x278), only the touched fields. */
typedef struct RbiKbWork159 {
    uint32_t  flags00;        /* +0x00 */
    uint8_t   unk04[0xC - 4];
    float     rateC;          /* +0x0C */
    float     f10;            /* +0x10 */
    uint8_t   unk14[0x24 - 0x14];
    float     f24, f28, f2C, f30; /* +0x24 */
    uint8_t   unk34[0x40 - 0x34];
    uint32_t  flags40;        /* +0x40 */
    uint8_t   unk44[0x74 - 0x44];
    RbiVec4   target74;       /* +0x74 */
} RbiKbWork159;
int   rbi_Enter1456E0(void *obj, void *act, int state, int arg);   /* 0x001456E0 */
void  rbi_Motion156180(void *w, float a, float b, float c, float t);/* 0x00156180 */
float rbi_VecDot(const RbiVec4 *a, const RbiVec4 *b);               /* 0x001AD9D0 */
void  rbi_VecCross(RbiVec4 *d, const RbiVec4 *a, const RbiVec4 *b); /* 0x001ADA60 */
RbhEmit *rbi_Emit113400(void *act, int slot);                       /* 0x00113400 */

/* Work block of the enemy at 0x00187FB0 (act+0x278), only the touched fields. */
typedef struct RbiKbWork187 {
    uint8_t   unk00[8];
    RbiVec4   target08;       /* +0x08 */
    uint32_t  flags18;        /* +0x18 */
    uint8_t   unk1C[0x20 - 0x1C];
    float     f20, f24, f28, f2C; /* +0x20 */
} RbiKbWork187;

/* ------------------------------------------------------------ enemy burst at 0x00177290 */
typedef struct RbiBurstObj {
    uint8_t  unk00[0xC];
    uint32_t flags0C;         /* +0x0C */
    uint32_t flags10;         /* +0x10 */
    uint8_t  unk14[0x60 - 0x14];
    RbiVec4  pos60;           /* +0x60 */
} RbiBurstObj;
typedef struct RbiBurstAct {
    uint8_t  unk00[0x4C];
    uint32_t flags4C;         /* +0x04C */
    uint8_t  unk50[0x278 - 0x50];
    int32_t *work278;         /* +0x278 (work[5] = part value) */
} RbiBurstAct;
typedef struct RbiJoint { uint8_t unk00[0xD4]; int32_t iD4; } RbiJoint;
RbiJoint *rbi_Joint1D0F0(void *o, int k);                       /* 0x0001D0F0 */
void  sub_0013A120(void *obj, int mode, const int32_t *list);
void  rbi_Place34E00(void *node, const RbiVec4 *pos, const RbiVec4 *dir, const RbiVec4 *up); /* 0x00034E00 */
int   rbi_Sound494D0(int id, const RbiVec4 *pos, int c);       /* 0x000494D0 */

/* ------------------------------------------------------------ enemy spawn at 0x00185190 */
typedef struct RbiSpawnObj {
    uint8_t  unk00[4];
    int32_t  kind04;          /* +0x004 */
    int32_t  var08;           /* +0x008 */
    uint32_t flags0C;         /* +0x00C */
    uint32_t flags10;         /* +0x010 */
    uint8_t  unk14[0x70 - 0x14];
    RbiVec4  scale70;         /* +0x070 */
    uint8_t  unk80[0xF0 - 0x80];
    int32_t  iF0, iF4;        /* +0x0F0 */
    uint8_t  unkF8[0x124 - 0xF8];
    int32_t  i124;            /* +0x124 */
} RbiSpawnObj;
/* Slot record of the 0x003FE3B0 table (4 x 0x34 bytes). */
typedef struct RbiSlot34 {
    RbiSpawnObj *obj00;       /* +0x00 */
    uint8_t  unk04[4];
    RbiAct  *act08;           /* +0x08 */
    int32_t  i0C;             /* +0x0C */
    float    f10;             /* +0x10 */
    uint8_t  unk14[0x1C - 0x14];
    float    f1C, f20, f24, f28, f2C; /* +0x1C */
    int16_t  idx30;           /* +0x30 */
    uint8_t  unk32[2];
} RbiSlot34;
extern RbiSlot34 r3c_recs3FE3B0[4];               /* 0x003FE3B0 */
void  sub_00184670(void);
void  sub_001846E0(void);
extern const uint8_t rbi_tab32BCCC[], rbi_tab32BCD8[];
extern const float rbi_v27AA00[], rbi_v27AA14[];

/* ------------------------------------------------------------ Jack reset (0x000D3260) */
/* View of g_stats with the fields the reset touches (all names inferred). */
typedef struct RbiJackInit {
    uint8_t  u000[0x10];
    float    f010, f014, f018, f01C;          /* +0x010 */
    int32_t  i020;                            /* +0x020 */
    uint8_t  u024[0xD4 - 0x24];
    int32_t  i0D4;                            /* +0x0D4 */
    uint8_t  u0D8[0xE8 - 0xD8];
    float    f0E8;                            /* +0x0E8 */
    int32_t  i0EC;                            /* +0x0EC */
    uint8_t  u0F0[0xFC - 0xF0];
    float    yaw0FC, yaw100, yaw104, yaw108;  /* +0x0FC */
    float    f10C, f110, f114, f118, f11C;    /* +0x10C */
    uint8_t  u120[0x128 - 0x120];
    int32_t  i128, i12C;                      /* +0x128 */
    float    f130, f134;                      /* +0x130 */
    int32_t  i138, i13C, i140, i144;          /* +0x138 */
    float    f148, f14C;                      /* +0x148 */
    int32_t  i150, i154, i158;                /* +0x150 */
    float    f15C, f160;                      /* +0x15C */
    int32_t  i164;                            /* +0x164 */
    float    f168, f16C;                      /* +0x168 */
    int32_t  i170, i174, i178, i17C, i180, i184, i188, i18C; /* +0x170 */
    uint8_t  u190[0x1A8 - 0x190];
    RbiVec4  pos1A8;                          /* +0x1A8 */
    uint8_t  u1B8[0x31C - 0x1B8];
    int32_t  i31C, i320;                      /* +0x31C */
    uint8_t  u324[0x5F0 - 0x324];
    int32_t  i5F0[4];                         /* +0x5F0 set to -1 */
    int32_t  i600[9];                         /* +0x600 cleared */
    uint8_t  u624[0xD2C - 0x624];
    int32_t  iD2C;                            /* +0xD2C */
    float    fD30;                            /* +0xD30 */
    int32_t  iD34, iD38, iD3C, iD40;          /* +0xD34 */
    float    fD44, fD48, fD4C, fD50, fD54, fD58; /* +0xD44 */
    int32_t  iD5C;                            /* +0xD5C */
    uint8_t  uD60[0xEE8 - 0xD60];
    int32_t  iEE8, iEEC;                      /* +0xEE8 */
    uint8_t  uEF0[0xFD8 - 0xEF0];
    RbiBody *nodeFD8;                         /* +0xFD8 Jack's model node (+0x60 position) */
} RbiJackInit;
void  sub_000D2440(RbiJackInit *p);
void  sub_000CB340(RbiJackInit *p);
void  sub_000CBD10(RbiJackInit *p);
void  sub_000CCC50(RbiJackInit *p, int k);
void  sub_000C4420(RbiJackInit *p);
void  sub_000C5B10(void);
void  sub_000C42B0(RbiJackInit *p);
void  sub_000CC430(RbiJackInit *p);
void  sub_000C52B0(RbiJackInit *p);

/* State component (kind 5) of the enemy set up at 0x000F2D30. */
typedef struct RbiStateCompB {
    uint8_t  unk00[0x4C];
    int32_t  i4C;             /* +0x04C */
    uint8_t  unk50[0x54 - 0x50];
    float    hp54, hpMax58;   /* +0x054 */
    uint8_t  unk5C[0x64 - 0x5C];
    void    *game64;          /* +0x064 */
    uint8_t  unk68[0x74 - 0x68];
    const void *tab74, *tab78, *tab7C; /* +0x074 */
    uint8_t  unk80[0x8C - 0x80];
    int32_t  i8C;             /* +0x08C */
    RbiVec4  v90, vA0;        /* +0x090 */
    uint8_t  unkB0[0xB8 - 0xB0];
    RbiVec4  vB8;             /* +0x0B8 */
    float    fC8, fCC, fD0;   /* +0x0C8 */
    uint8_t  unkD4[0xDC - 0xD4];
    int32_t  iDC;             /* +0x0DC */
    uint8_t  unkE0[0xE4 - 0xE0];
    int32_t  iE4;             /* +0x0E4 */
    uint8_t  unkE8[0xEC - 0xE8];
    int32_t  iEC;             /* +0x0EC */
    float    vF0[4];          /* +0x0F0 */
    uint8_t  unk100[0x108 - 0x100];
    float    f108;            /* +0x108 */
    int32_t  pick10C;         /* +0x10C */
    int32_t  i110, i114;      /* +0x110 */
} RbiStateCompB;
void  sub_000F3D10(void *o, RbiStateCompB *c, int v);
void  sub_000EFDE0(void);
void  sub_000F2A60(void);
extern const uint8_t rbi_tab318A30[], rbi_tab318AB8[], rbi_tab318B40[];

/* Helper object of the boss at *0x003F611C (0x104 bytes), only the touched fields. */
typedef struct RbiHelper {
    uint8_t  unk00[0x90];
    int32_t  i90;             /* +0x090 */
    uint8_t  unk94[0xA8 - 0x94];
    float    rateA8;          /* +0x0A8 */
    float    fAC;             /* +0x0AC */
    uint8_t  unkB0[0xC0 - 0xB0];
    int32_t  iC0;             /* +0x0C0 */
    uint8_t  unkC4[0xD4 - 0xC4];
    float    fD4, fD8;        /* +0x0D4 */
    uint8_t  unkDC[0xE4 - 0xDC];
    int32_t  iE4, iE8;        /* +0x0E4 */
    int16_t  sEC;             /* +0x0EC */
    uint8_t  unkEE[2];
    float    fF0;             /* +0x0F0 */
    uint8_t  unkF4[4];
    int32_t  iF8;             /* +0x0F8 */
} RbiHelper;
extern RbiHelper *afc_helper;                     /* 0x003F611C */
typedef struct RbiFxObjB {
    uint8_t  unk00[4];
    int32_t  kind04;          /* +0x04 */
    int32_t  var08;           /* +0x08 */
    uint32_t flags0C;         /* +0x0C */
    uint32_t flags10;         /* +0x10 */
    uint8_t  unk14[0x70 - 0x14];
    RbiVec4  scale70;         /* +0x070 */
    uint8_t  unk80[0xF0 - 0x80];
    int32_t  iF0, iF4;        /* +0x0F0 */
    uint8_t  unkF8[0x11C - 0xF8];
    int32_t  i11C, i120, i124;/* +0x11C */
} RbiFxObjB;
int r2c_HelperDetach(void *);                     /* 0x000FC4E0 */
void  sub_000FDD70(void);
void  sub_000FD420(void);
extern const float rbi_v278B28[], rbi_v278B3C[], rbi_v278B4C[], rbi_v278B5C[];
extern const uint8_t rbi_tab3191B0[], rbi_tab3191DC[];

void  sub_0017C2B0(void);
void  sub_0017AA60(void);
void  sub_0017ABE0(void);
extern const uint8_t rbi_tab32B630[], rbi_tab32B65C[], rbi_tab32B688[];

/* ------------------------------------------------------------ grab start at 0x0012C3C0 */
typedef struct RbiGrabObj {
    uint8_t  unk00[0x10];
    uint32_t flags10;         /* +0x10 */
    uint8_t  unk14[0x50 - 0x14];
    RbiVec4  rot50;           /* +0x50 */
    RbiVec4  pos60;           /* +0x60 */
} RbiGrabObj;
typedef struct RbiGrabWork {
    uint8_t  unk00[8];
    void    *fx08;            /* +0x08 spawned effect */
    float    fC;              /* +0x0C */
    uint8_t  unk10[0x30 - 0x10];
    RbiVec4  v30, v40;        /* +0x30 */
    RbiVec4  v50;             /* +0x50 */
    float    f60, f64;        /* +0x60 */
} RbiGrabWork;
void *rbi_Spawn0ED630(int type, int id, const RbiVec4 *pos, const RbiVec4 *rot, int e); /* 0x000ED630 */
void  rtc_RecMatrixApply(void *rec, const RbiVec4 *v);  /* 0x00196A30 */

/* Work block of the enemy family at 0x00135000 (act+0x278), only the touched fields. */
typedef struct RbiWork135 {
    void    *obj00;           /* +0x000 */
    uint8_t  unk04[4];
    uint32_t flags08;         /* +0x008 */
    uint8_t  unk0C[0x170 - 0xC];
    int32_t  armed170;        /* +0x170 */
    uint8_t  unk174[0x17C - 0x174];
    int32_t  t17C;            /* +0x17C */
    uint8_t  unk180[4];
    int32_t  i184;            /* +0x184 */
} RbiWork135;
typedef struct RbiObj135 {
    RbiObj   o;               /* +0x000 (see RbiObj) */
    uint8_t  unk128[0x13C - 0x128];
    void    *snd13C;          /* +0x13C (passed to 0x0005BE30) */
} RbiObj135;
void  sub_001134B0(void *act);
void  sub_00025C10(int a, int b);
void  sub_00135490(void);
void  sub_00137800(void);
void  r3b_Step135500(void *, void *);
void  sub_00145E10(void);
void  sub_001354D0(void);
void  rbi_Shapes135900(RbiShapeObj *o);
extern const uint8_t rbi_tab31C718[], rbi_tab31C754[], rbi_tab31C790[];

/* Work block of the enemy family at 0x0012C000 (act+0x278), only the touched fields. */
typedef struct RbiWork12C {
    uint8_t  unk00[4];
    uint32_t flags04;         /* +0x004 */
    uint8_t  unk08[0x30 - 8];
    RbiVec4  v30, v40, v50;   /* +0x030 */
    float    f60, rate64;     /* +0x060 */
    float    f68, f6C;        /* +0x068 */
    uint8_t  unk70[0x74 - 0x70];
    float    f74, step78;     /* +0x074 */
    uint8_t  unk7C[0xB8 - 0x7C];
    RbiVec4  matB8[4];        /* +0x0B8 */
    RbiVec4  matF8[4];        /* +0x0F8 */
    float    mat138[16];      /* +0x138 */
    int32_t  i178;            /* +0x178 */
    float    f17C, f180;      /* +0x17C */
} RbiWork12C;
void  sub_0011F640(int idx, float *dst);          /* regargs: idx=EAX dst=ESI */

#endif
