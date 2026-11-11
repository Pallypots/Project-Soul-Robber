#ifndef R3C_H
#define R3C_H
#include "oogie.h"
/* Area r3c: more game functions in 0x00130000..0x00190000 (stack and register arguments).
   All names inferred. Register mappings are in the comments and in config/function_states_r3c.csv. */

/* ---- views of the character/actor objects used by these functions (only touched fields) */

/* Work block hung off an actor at +0x278. */
typedef struct R3cWork {
    union { uint32_t flags00; struct R3cObj *obj00; }; /* +0x00 flags, or the owner object */
    union { uint32_t flags04; struct R3cObj *act04; }; /* +0x04 flags, or the owner actor */
    int32_t  i08;            /* +0x08 */
    union { int16_t s; int32_t i; float f; } u0C; /* +0x0C */
    union { float f10; int32_t i10; }; /* +0x10 */
    union { int32_t i14; float f14; }; /* +0x14 */
    union { uint32_t flags18; float f18; }; /* +0x18 */
    float    f1C;            /* +0x1C */
    union { float f20; int32_t i20; }; /* +0x20 */
    union { float f24; struct { int16_t s24, s26; }; }; /* +0x24 */
    float    f28, f2C;       /* +0x28, +0x2C */
    union { int32_t i30; struct { int16_t s30, s32; }; float f30; }; /* +0x30 (also a float x, see 0x00185DC0) */
    struct R3cObj *p34;      /* +0x34 */
    union { struct R3cObj *p38; float f38; }; /* +0x38 (also a float z, see 0x00185DC0) */
    uint8_t  unk3C[0x44 - 0x3C];
    float    f44, f48;       /* +0x44, +0x48 */
    uint8_t  unk4C[0x54 - 0x4C];
    int16_t  s54;            /* +0x54 */
    uint8_t  unk56[0x6C - 0x56];
    float    f6C;            /* +0x6C */
} R3cWork;

/* Animation record behind obj+0x30. */
typedef struct R3cAnimInst { uint8_t unk00[0xC4]; float rateC4; } R3cAnimInst;
typedef struct R3cAnim { uint8_t unk00[8]; int32_t i08; uint8_t unk0C[0x14 - 0x0C]; R3cAnimInst *inst14; } R3cAnim;
typedef struct R3cKey { uint8_t unk00[0x10]; int32_t i10; } R3cKey;

/* Motion/flag block at +0x74 of some components. */
typedef struct R3cBlk74 {
    uint32_t flags;          /* +0x00 (low half also read as a 16-bit kind) */
    int32_t  i04;            /* +0x04 */
    int32_t  i08;            /* +0x08 */
    float    f0C;            /* +0x0C */
    float    f10;            /* +0x10 */
    uint8_t  unk14[0x24 - 0x14];
    float    v24[4];         /* +0x24 */
    float    v34[4];         /* +0x34 */
} R3cBlk74;

typedef struct R3cObj R3cObj;
typedef int (*R3cCompFn)(R3cObj *o, void *comp);
typedef int (*R3cCompFn3)(R3cObj *o, void *comp, void *arg);

/* Object / actor / component (they share a header layout as far as these functions go). */
struct R3cObj {
    int32_t  kind00;         /* +0x000 component kind */
    int32_t  type04;         /* +0x004 */
    int32_t  i08;            /* +0x008 */
    uint32_t flags0C;        /* +0x00C */
    uint32_t flags10;        /* +0x010 */
    uint8_t  unk014[0x20 - 0x14];
    union { uint8_t b20; float *m20; struct { uint8_t pad20, b21, b22, b23; }; }; /* +0x020 flag bytes, or a matrix (3 rows of 0x10) */
    uint8_t  unk024[0x30 - 0x24];
    union { int32_t anim30; struct R3cAnim *pa30; }; /* +0x030 animation handle */
    uint8_t  unk034[0x3C - 0x34];
    R3cObj  *p3C;            /* +0x03C linked object */
    uint8_t  unk040[0x4C - 0x40];
    uint32_t flags4C;        /* +0x04C */
    union { int32_t state50; float f50; }; /* +0x050 */
    union { float f54; int32_t i54; }; /* +0x054 */
    float    f58;            /* +0x058 */
    union { float f5C; uint32_t flags5C; }; /* +0x05C */
    union { float pos60[3]; struct { int32_t i60, i64, i68; }; }; /* +0x060 position, or mode words */
    union { float f6C; R3cCompFn fn6C; }; /* +0x06C */
    float    f70;            /* +0x070 */
    union { float f74; R3cBlk74 *p74; }; /* +0x074 */
    union { R3cCompFn fn78; float f78; }; /* +0x078 component callback */
    float    f7C;            /* +0x07C */
    union { R3cCompFn3 fn80; float f80; }; /* +0x080 component callback */
    union { float f84; R3cCompFn *fns84; }; /* +0x084 value, or per-mode callbacks */
    uint8_t  unk088[0x90 - 0x88];
    uint32_t flags90;        /* +0x090 */
    uint8_t  unk094[0xB0 - 0x94];
    float    fB0;            /* +0x0B0 radius */
    uint32_t unk0B4;
    int32_t  iB8;            /* +0x0B8 */
    uint8_t  unk0BC[0xD8 - 0xBC];
    float    fD8, fDC, fE0, fE4; /* +0x0D8..+0x0E4 */
    float    fE8;            /* +0x0E8 */
    uint32_t unk0EC;
    union { float fF0; int32_t iF0; }; /* +0x0F0 (start of a block passed by address) */
    uint32_t unk0F4;
    int32_t  iF8;            /* +0x0F8 */
    float    fFC;            /* +0x0FC */
    uint32_t unk100;
    R3cObj  *p104;           /* +0x104 target */
    uint8_t  unk108[0x128 - 0x108];
    uint32_t flags128;       /* +0x128 */
    uint32_t unk12C;
    int32_t  i130;           /* +0x130 */
    int32_t  i134;           /* +0x134 */
    int32_t  i138;           /* +0x138 */
    uint8_t  unk13C[0x1C4 - 0x13C];
    R3cObj  *p1C4;           /* +0x1C4 */
    uint8_t  unk1C8[0x1E8 - 0x1C8];
    float    f1E8;           /* +0x1E8 */
    uint8_t  unk1EC[0x1FC - 0x1EC];
    int16_t  s1FC;           /* +0x1FC */
    uint8_t  unk1FE[0x270 - 0x1FE];
    int32_t  i270, i274;     /* +0x270, +0x274 */
    R3cWork *work278;        /* +0x278 */
};

/* Condition argument record (+0x08 key, +0x10/+0x14 range). */
typedef struct R3cRange {
    int32_t i00, i04, i08, i0C;
    union { float lo; int32_t i10; };  /* +0x10 */
    union { float hi; int32_t i14; };  /* +0x14 */
    union { float val; int32_t i18; }; /* +0x18 */
} R3cRange;

/* ---- globals */
typedef struct R3cSlot44 { R3cObj *obj; R3cObj *act; uint8_t unk08[0x44 - 8]; } R3cSlot44;
extern R3cSlot44 r3c_slots3FE1C8[4];                 /* 0x003FE1C8 */
extern R3cObj  *r3c_obj3FE368, *r3c_act3FE36C;       /* 0x003FE368, 0x003FE36C */
extern int32_t  r3c_i3FE378, r3c_i3FE37C;            /* 0x003FE378, 0x003FE37C */
extern float    r3c_f3FE380, r3c_f3FE384;            /* 0x003FE380, 0x003FE384 */
typedef struct R3cRec24 { int32_t i0, i4, i8; float fC; uint8_t unk10[0x24 - 0x10]; } R3cRec24;
extern R3cRec24 r3c_recs3FF588[12];                  /* 0x003FF588 */
typedef struct R3cRec44 { int32_t i0; uint8_t unk04[0x44 - 4]; } R3cRec44;
extern R3cRec44 r3c_recs3FF738[15];                  /* 0x003FF738 */
typedef struct R3cRecA0 { int32_t i0; uint8_t unk04[0xA0 - 4]; } R3cRecA0;
extern R3cRecA0 r3c_recs3FE488[8];                   /* 0x003FE488 */
typedef struct R3cRec18 { uint32_t w[6]; } R3cRec18;
extern R3cRec18 r3c_recs3FFC78[15];                  /* 0x003FFC78 */
extern int16_t  r3c_s3FEAB8;                         /* 0x003FEAB8 */
extern float    r3c_f3FEABC, r3c_f3FEAC0, r3c_f3FEAC4, r3c_f3FEAC8;
extern R3cObj  *r3c_obj3FF57C;                       /* 0x003FF57C */
extern int32_t  r3c_i3FF584;                         /* 0x003FF584 */
typedef struct R3cId0C { int32_t id; int32_t i4, i8; } R3cId0C;
extern R3cId0C  r3c_ids279F00[40];                   /* 0x00279F00 */
extern const float r3c_vec27A95C[];                  /* 0x0027A95C zero vector */
extern float    r3c_halfDegree32B8E8;                /* 0x0032B8E8 = 0.5 degree in radians */
extern float    r3c_f32BCA4;                         /* 0x0032BCA4 = -2.85 */
extern float    r3c_frameUnits;                      /* 0x0042C858 */
extern float    r3c_frameSeconds;                    /* 0x0042C85C */

extern R3cObj  *r3c_obj3FE38C, *r3c_act3FE390;       /* 0x003FE38C, 0x003FE390 */
typedef struct R3cRec54 { R3cObj *obj; uint8_t unk04[0x18 - 4]; int32_t id18; uint8_t unk1C[0x54 - 0x1C]; } R3cRec54;
extern R3cRec54 r3c_recs3FDC70[6];                   /* 0x003FDC70 */
typedef struct R3cRec20 { uint32_t w[8]; } R3cRec20;
extern R3cRec20 r3c_recs3FFB38[10];                  /* 0x003FFB38 */
extern int16_t  r3c_s3FDAE0[9];                      /* 0x003FDAE0 */
extern int32_t  r3c_i3FEB10, r3c_i3FEB14;            /* 0x003FEB10, 0x003FEB14 */
extern float    r3c_framesPerSecond;                 /* 0x0042C964 */
typedef void (*R3cFsmFn)(void *a, void *b);
extern R3cFsmFn r3_fsmEnter32B1B0[11];               /* 0x0032B1B0 (named in area r3) */

/* Node returned by 0x001133E0 (timer at +0x10). */
typedef struct R3cNode { uint8_t unk00[0x10]; float f10; } R3cNode;
/* Component with a scale value at +0x2C. */
typedef struct R3cComp2C { uint8_t unk00[0x2C]; float f2C; } R3cComp2C;
/* Object returned by 0x000A4290 (state word at +0x40). */
typedef struct R3cA4290 { uint8_t unk00[0x40]; int32_t i40; } R3cA4290;

/* Player-like object read by the parameter getters 0x00171AA0..0x00171C27. */
typedef struct R3cPlayer {
    uint8_t  unk000[0xEC];
    uint8_t  bEC;            /* +0x0EC bit 0x40: alternate parameter set */
    uint8_t  unk0ED[0xD60 - 0xED];
    uint32_t flagsD60;       /* +0xD60 */
    uint8_t  unkD64[0xD6C - 0xD64];
    int32_t  iD6C;           /* +0xD6C parameter column */
} R3cPlayer;
typedef union R3cParams { int32_t i[0x100]; float f[0x100]; } R3cParams;
extern R3cParams **r3c_params32B114;                /* 0x0032B114 */
extern uint8_t  r3c_flags3FDC3C;                     /* 0x003FDC3C */
extern R3cObj  *r3c_obj3FDC68;                       /* 0x003FDC68 */

extern R3cObj  *r3c_obj3FD7C4;                       /* 0x003FD7C4 */
extern int32_t  r3c_i3FD7B0, r3c_i3FD7B4, r3c_i3FD7B8, r3c_i3FD7BC, r3c_i3FD7C0;
typedef struct R3cRecD4 { uint8_t a[0x10]; uint8_t b[0xD4 - 0x10]; } R3cRecD4;
extern R3cRecD4 r3c_recs3FD2B8[6];                   /* 0x003FD2B8 */
extern int32_t  r3c_i413178;                         /* 0x00413178 */
extern R3cCompFn r3c_fns32B1DC[];                    /* 0x0032B1DC by state +0x4C */
extern R3cCompFn r3c_fns31F50C[];                    /* 0x0031F50C by state +0x50 (kind < 10) */
extern R3cCompFn r3c_fns31F52C[];                    /* 0x0031F52C by state +0x50 (kind >= 10) */
typedef struct R3cRec34 { int32_t i0, i4, i8, iC; uint8_t unk10[0x34 - 0x10]; } R3cRec34;
extern R3cRec34 r3c_recs3FE3B0[4];                   /* 0x003FE3B0 */
extern int32_t  r3c_i3FE480;                         /* 0x003FE480 */
extern float    r3c_f3FE394, r3c_f3FE3A0;            /* 0x003FE394, 0x003FE3A0 */
extern int32_t  r3c_i3FE398;                         /* 0x003FE398 */

typedef struct R3cItem150 { int32_t i00; int32_t type04; int32_t i08; uint8_t unk0C[0x150 - 0x0C]; } R3cItem150;
extern R3cItem150 *r3c_items3FD7D4;                  /* 0x003FD7D4, 16 entries */
typedef struct R3cTblEnt { uint8_t unk00[0x18]; int32_t *vals18; } R3cTblEnt;
extern R3cTblEnt **r3c_tables32B110[];               /* 0x0032B110 */
typedef struct R3cRec24b { R3cObj *obj; uint8_t unk04[0x24 - 4]; } R3cRec24b;
extern R3cRec24b r3c_recs4000B0[3];                  /* 0x004000B0 */

/* Game-state object returned by 0x000E0770. */
typedef struct R3cGame { uint8_t unk000[0x324]; int32_t i324; } R3cGame;

/* ---- callees (stack arguments unless stated) */
int     sub_001456E0(void *obj, void *act, int a, int b);
void    sub_00113040(void *obj, void *act, int state);
void    sub_00113090(void *obj, void *act, int state);
void    sub_001134B0(void *act);
void    sub_00186470(R3cObj *obj, R3cObj *act, int k);  /* obj=EBX act=EDI k=stack */
R3cObj *sub_0001F210(int a, int b);
void    sub_0001DA40(void *p);
int     sub_00113670(void *a, void *b, int c, float *out);
void    sub_0018DA80(void *a, void *b);
void    sub_00189DA0(void *a, void *b, int c);
void    sub_00167200(void *a, void *b, int k);
R3cObj *sub_0001D960(void *o, int kind);             /* component lookup */
float   sub_001065B0(void);
void    sub_000ED560(int v);
void    sub_00020170(void *p);
void    sub_0001EB80(void *o);
int     sub_000EE5F0(void *o);
R3cObj *sub_00100110(void);
R3cGame *sub_000E0770(void);
int     sub_0001B450(void *a, float f, void *b, float *v);
int     sub_000ED780(void *o);
void    sub_001789E0(void *obj, void *act);
void    sub_000ED600(int v);
int     sub_0004F6D0(int id);
int     sub_000833E0(int anim);

int     sub_001730A0(void *a, void *b, float k);   /* a=EAX b=EBX k=stack */
void    sub_00172C90(void *a, void *b, int anim);  /* b=EAX a=ESI anim=EDI */
R3cA4290 *sub_000A4290(int id);
void    sub_000A22C0(R3cA4290 *x, R3cObj *o);
void   *sub_000ED630(int type, int id, const float *pos, const float *rot, int e); /* returns the spawned object (EAX = ESI at 0x000ED775) */
void    sub_000FB4D0(void *o);
R3cNode *sub_001133E0(void *act, int k);
int     sub_000494D0(int id, const float *pos, int c);
void    sub_001AD7E0(float *d, const float *s);
void    sub_001ADA60(float *d, const float *a, const float *b);
int     sub_001C7EE1(void);                        /* CRT rand */

void    sub_0003AEB0(int a, int b);
int     sub_00101220(void);
int     sub_000F3B50(int a);
void    sub_0001D700(void *o);
void    sub_001ADB60(float *a, float *b, float k);
float   sub_00113200(void *o, const float *pos);
int     sub_000F40B0(void);
int     sub_00145940(void *obj, float x, float z, float lo, float hi); /* floats: x,z passed to 0x00145820; lo,hi compared with comiss */
void    sub_001459D0(void *obj, float x, float z, float v);
void    sub_001A8820(float *d, const void *s);
void    sub_001A8840(float *d, const float *a, const float *b, float t);
int     sub_001A8830(void *d, const float *s);
float   sub_001B2770(const float *a, const float *b);   /* distance */

void    sub_00048250(int h);
void    sub_000CE9F0(void *o);
R3cKey *sub_00083120(R3cAnim *a, int k);
void    sub_001AEDD0(void *inst, int v);
void    sub_0001D8B0(void *p, int k);
void    sub_0018CB60(void *a, void *b);
void    sub_0016FCB0(R3cObj *c, void *o);         /* c=EAX o=stack */
void    sub_00113370(void *act, void *step);

void    sub_0013D4E0(int h, void *obj, int k);
int     sub_001AEE90(void *inst, int k);
int     sub_000E3380(void);
void    sub_001671D0(void *a, void *b, int k);

int     sub_00087500(void);
float   sub_001A3F30(float v);                       /* absolute value */
void    sub_0018E270(R3cObj *obj, R3cObj *c, int k);   /* obj=ESI c=EAX k=stack */
void    sub_0001F070(void *o, int k);
void    sub_0001EBF0(void *o, int k);
int     sub_00176150(void *obj, void *act, int32_t *p);
float   sub_00113290(void *o, const float *pos);
void    sub_001AEDF0(void *inst, int v);

/* ---- r3c functions */
R3cObj *r3c_Target155940(const int32_t *sel, R3cObj *obj, R3cObj *given); /* sel=EAX obj=ECX given=stack */

#endif
