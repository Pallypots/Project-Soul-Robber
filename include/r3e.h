#ifndef R3E_H
#define R3E_H
#include "oogie.h"
#include "shared_decls.h"
/* oogie.h declares sub_000F5D40 (vector copy) and sub_00036750. */

/* Area r3e: more game functions in 0x00130000..0x00190000 (stack and register arguments).
   All names inferred. Register mappings are in the comments and in config/function_states_r3e.csv. */

/* Float to int truncation. The original inlines cvttss2si; the intrinsic is used only for the
   32-bit x86 comparison build (same as RFL_FTOI in rfl.h). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R3E_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R3E_FTOI(x) ((int)(x))
#endif
#if 0 /* PORT: this block was hidden by a misplaced #endif and never compiled on any target;
         enabling it gives redefinition errors against declarations later in this header. */
int      sub_001C7EE1(void);                                        /* rand */
float    sub_001B2770(const float *a, const float *b);              /* distance */
int      sub_0012DC90(int table, R3eObj *obj, R3eObj *act);         /* regargs: table=EAX obj=EBX act=EDI */
void     r3_SetStateA(R3eObj *obj, R3eObj *act, int state);         /* 0x00131310 regargs: obj=EBX act=EDI state=stack */
void     r3_SetStateB(R3eObj *obj, R3eObj *act, int state);         /* 0x00135A70 regargs: obj=ESI act=EDI state=stack */
int      sub_00145780(R3eObj *obj, float t);                        /* animation passed time t */
void     sub_00113480(R3eObj *act, int ev);

/* 16-byte condition records and their dispatchers (named in area r3b). */
typedef struct R3eRec16 { int32_t i[4]; } R3eRec16;
typedef int (*R3eDispFn)(R3eObj *obj, R3eObj *act, R3eRec16 *rec);
extern R3eRec16  r3b_recs279728[];                                  /* 0x00279728 */
extern R3eDispFn r3b_disp31CDFC[];                                  /* 0x0031CDFC */

/* 0x003FE3A4: one 8-byte key record (named in area r3b). */
typedef struct R3eKey8 { int32_t key; int32_t v; } R3eKey8;
extern R3eKey8 r3b_i3FE3A4[1];
typedef void (*R3eFn2)(R3eObj *a, R3eObj *b);
extern R3eFn2 r3_fsmEnter32B1B0[11];                               /* 0x0032B1B0 state enter table */

void     sub_00167200(R3eObj *a, R3eObj *b, int anim);
/* 0x003FF738: fifteen 0x44-byte records keyed by their first word (named in area r3c). */
typedef struct R3eRec44 { int32_t key; uint8_t unk04[0x44 - 4]; } R3eRec44;
extern R3eRec44 r3c_recs3FF738[15];

void     sub_00172C90(R3eObj *a, R3eObj *b, int anim);              /* regargs: b=EAX a=ESI anim=EDI */
int      sub_0017AF00(R3eObj *b, R3eObj *a);                        /* regargs: b=EAX a=stack */
void     sub_000A8ED0(int h, const float *pos, float *v, int k);
R3eNode *sub_001133E0(R3eObj *act, int key);                        /* find node */
void     sub_000A7950(int h);
/* 0x003F8A18: sixteen 0x20-byte pool entries (named in area b16). */
typedef struct R3ePool20 { uint32_t flags; uint8_t unk04[0x20 - 4]; } R3ePool20;
extern R3ePool20 b16_pool20[16];
/* 0x003F92E8 / 0x003F92EC: count pointer and base of the 0x150-byte task records (area b16). */
typedef struct R3eRec150 { int32_t unk00, unk04, kind08; uint8_t unk0C[0x150 - 0x0C]; } R3eRec150;
extern int32_t   *b16_task3F92E8;
extern R3eRec150 *b16_taskId3F92EC;


void     sub_0016FE00(R3eRec150 *rec);
void     sub_000C56B0(R3eObj *obj);
void     r3_SetState16C820(R3eObj *a, R3eObj *m, int state);       /* 0x0016C820 regargs: a=EAX m=EDI state=stack */
/* Game controller block returned by 0x000E0770 (only the touched fields). */
typedef struct R3eGame { uint8_t unk000[0x324]; int32_t i324; uint8_t unk328[4]; int32_t i32C; } R3eGame;
int      sub_000E3380(void);
void     sub_0001E9B0(void *scene, R3eObj *obj, int a, int b, int c);
extern void *r3_ctx42C8E4;                                          /* 0x0042C8E4 scene context */
void     sub_001453B0(R3eObj *obj, R3eObj *act);                    /* regargs: obj=ESI act=EDI */
void     sub_00189DE0(void *fx, int on);

#endif

/* Work block of an actor (act+0x278), only the touched fields. */
typedef struct R3eWork {
    uint32_t unk00;
    int32_t  i04;            /* +0x004 flag word, tested by sign */
    uint32_t flags08;        /* +0x008 */
    uint32_t flags0C;        /* +0x00C */
    uint32_t unk10;
    union { uint8_t blk14[0x20 - 0x14]; struct { float f14, f18, f1C; }; }; /* +0x014 block passed by address */
    void    *p20;            /* +0x020 attached effect */
    uint8_t  unk24[0x34 - 0x24];
    void    *refs34[3];      /* +0x034 held references */
    uint32_t flags40;        /* +0x040 */
    uint8_t  unk44[0x154 - 0x44];
    float    v154[4];        /* +0x154 target position */
    float    v164[4];        /* +0x164 direction (x, y, z, w) */
    uint8_t  unk174[0x17C - 0x174];
    float    f17C;           /* +0x17C */
    float    f180;           /* +0x180 cooldown */
    uint8_t  unk184[0x19C - 0x184];
    int32_t  i19C;           /* +0x19C variant 0..2 */
} R3eWork;

/* Object / actor (shared header layout as far as these functions go). */
typedef struct R3eObj {
    int32_t  kind00;         /* +0x000 */
    int32_t  type04;         /* +0x004 */
    int32_t  i08;            /* +0x008 */
    uint32_t flags0C;        /* +0x00C */
    uint32_t flags10;        /* +0x010 */
    uint8_t  unk014[0x20 - 0x14];
    union { float *m20; uint32_t flags20; struct { uint8_t b20, b21, b22, b23; }; }; /* +0x020 matrix (rows of 4 floats), or flags */
    uint32_t unk024;
    void    *p28;            /* +0x028 node */
    uint32_t unk02C;
    union { void *anim30; struct R3eAnim *pa30; }; /* +0x030 animation handle */
    uint8_t  unk034[0x4C - 0x34];
    union { uint32_t flags4C; int32_t i4C; }; /* +0x04C */
    union { int32_t state50; float f50; }; /* +0x050 state, or a value */
    union { float f54; int32_t i54; }; /* +0x054 */
    union { float f58; int32_t i58; }; /* +0x058 timer, or step counter */
    union { uint32_t flags5C; float f5C; }; /* +0x05C */
    union { float pos60[3]; struct { float f60, f64, f68; }; }; /* +0x060 position, or timers */
    int32_t  i6C;            /* +0x06C sound handle */
    void    *p70;            /* +0x070 */
    union { float f74; void *p74; struct R3eBlk74 *b74; }; /* +0x074 timer, or a link */
    float    v78[4];         /* +0x078 vector */
    float    v88[4];         /* +0x088 velocity */
    uint8_t  unk098[0xB8 - 0x98];
    int32_t  iB8;            /* +0x0B8 */
    uint8_t  unk0BC[0x104 - 0xBC];
    union { struct R3eObj *p104; float v104[3]; }; /* +0x104 target, or a position */
    uint8_t  unk110[0x128 - 0x110];
    uint32_t flags128;       /* +0x128 */
    uint8_t  unk12C[0x13C - 0x12C];
    void    *i13C;           /* +0x13C */
    uint8_t  unk140[0x270 - 0x140];
    float    f270, f274;     /* +0x270 maximum, +0x274 current (health) */
    union { R3eWork *work278; uint32_t flags278; }; /* +0x278 work block, or flags */
} R3eObj;

/* Node returned by 0x00113400 (timer values at +0x10). */
typedef struct R3eNode {
    int32_t i00;             /* +0x00 request state */
    uint8_t unk04[0x10 - 4];
    union { float f10; int32_t i10; }; /* +0x10 */
    union { float f14; int32_t i14; }; /* +0x14 timer, or a handle */
    union { float f18; int32_t i18; }; /* +0x18 */
    union { float f1C; int32_t i1C; void *p1C; }; /* +0x1C value, or a callback */
} R3eNode;
/* Block behind obj+0x74 (only the touched fields). */
typedef struct R3eBlk74 { uint32_t flags00; float f04; } R3eBlk74;
/* Work block view used by the movement setup at 0x001597D0. */
typedef struct R3eWorkM {
    uint32_t unk00;
    float    f04, f08, f0C, f10; /* +0x04 */
    uint8_t  unk14[0x24 - 0x14];
    float    f24, f28, f2C, f30; /* +0x24 */
} R3eWorkM;
/* Work block view with a vector at +0x20. */
typedef struct R3eWorkV { uint8_t unk00[0x20]; float v20[4]; } R3eWorkV;
/* Animation instance behind obj+0x30 (kind at +0x08). */
typedef struct R3eAnim { uint8_t unk00[8]; int32_t kind08; } R3eAnim;
/* Object with a scale vector at +0x70. */
typedef struct R3eScaled { uint8_t unk00[0x70]; float s70[4]; } R3eScaled;

/* ---- globals */
extern float r3e_frameUnits;                                        /* 0x0042C858 */
extern float r3e_frameSeconds;                                      /* 0x0042C85C */

/* ---- callees (stack arguments unless stated) */
void     sub_0001D4E0(R3eObj *obj);                                 /* free object */
R3eNode *sub_00113400(R3eObj *act, int key);
void     sub_00113A40(R3eObj *obj, R3eObj *act);
void     sub_001AD7E0(float *d, const float *s);                    /* normalize */
void     sub_001ADA60(float *d, const float *a, const float *b);    /* cross product */
void     sub_001ADBA0(float *d, const float *s, float k);          /* d = s * k */
void     sub_001AD9F0(float *d, const float *a, const float *b);    /* d = a - b */
float    sub_001A3F30(float x);                                     /* fabsf */
int      sub_00113670(R3eObj *obj, R3eObj *act, int idx, int *out);
int      sub_000D3BF0(PlayerStats *st, R3eObj *obj, int idx, int *h, float *dir);
void     sub_0012E5E0(int mode);                                    /* regargs: mode=ESI */
void     sub_00113370(R3eObj *act, R3eNode *blk);
int      sub_001C7EE1(void);                                        /* rand */
float    sub_001B2770(const float *a, const float *b);              /* distance */
int      sub_0012DC90(int table, R3eObj *obj, R3eObj *act);         /* regargs: table=EAX obj=EBX act=EDI */
void     r3_SetStateA(R3eObj *obj, R3eObj *act, int state);         /* 0x00131310 regargs: obj=EBX act=EDI state=stack */
void     r3_SetStateB(R3eObj *obj, R3eObj *act, int state);         /* 0x00135A70 regargs: obj=ESI act=EDI state=stack */
int      sub_00145780(R3eObj *obj, float t);                        /* animation passed time t */
void     sub_00113480(R3eObj *act, int ev);

/* 16-byte condition records and their dispatchers (named in area r3b). */
typedef struct R3eRec16 { int32_t i[4]; } R3eRec16;
typedef int (*R3eDispFn)(R3eObj *obj, R3eObj *act, R3eRec16 *rec);
extern R3eRec16  r3b_recs279728[];                                  /* 0x00279728 */
extern R3eDispFn r3b_disp31CDFC[];                                  /* 0x0031CDFC */

/* 0x003FE3A4: one 8-byte key record (named in area r3b). */
typedef struct R3eKey8 { int32_t key; int32_t v; } R3eKey8;
extern R3eKey8 r3b_i3FE3A4[1];
typedef void (*R3eFn2)(R3eObj *a, R3eObj *b);
extern R3eFn2 r3_fsmEnter32B1B0[11];                               /* 0x0032B1B0 state enter table */

void     sub_00167200(R3eObj *a, R3eObj *b, int anim);
/* 0x003FF738: fifteen 0x44-byte records keyed by their first word (named in area r3c). */
typedef struct R3eRec44 { int32_t key; uint8_t unk04[0x44 - 4]; } R3eRec44;
extern R3eRec44 r3c_recs3FF738[15];

void     sub_00172C90(R3eObj *a, R3eObj *b, int anim);              /* regargs: b=EAX a=ESI anim=EDI */
int      sub_0017AF00(R3eObj *b, R3eObj *a);                        /* regargs: b=EAX a=stack */
void     sub_000A8ED0(int h, const float *pos, float *v, int k);
R3eNode *sub_001133E0(R3eObj *act, int key);                        /* find node */
void     sub_000A7950(int h);
/* 0x003F8A18: sixteen 0x20-byte pool entries (named in area b16). */
typedef struct R3ePool20 { uint32_t flags; uint8_t unk04[0x20 - 4]; } R3ePool20;
extern R3ePool20 b16_pool20[16];
/* 0x003F92E8 / 0x003F92EC: count pointer and base of the 0x150-byte task records (area b16). */
typedef struct R3eRec150 { int32_t unk00, unk04, kind08; uint8_t unk0C[0x150 - 0x0C]; } R3eRec150;
extern int32_t   *b16_task3F92E8;
extern R3eRec150 *b16_taskId3F92EC;


void     sub_0016FE00(R3eRec150 *rec);
void     sub_000C56B0(R3eObj *obj);
void     r3_SetState16C820(R3eObj *a, R3eObj *m, int state);       /* 0x0016C820 regargs: a=EAX m=EDI state=stack */
/* Game controller block returned by 0x000E0770 (only the touched fields). */
typedef struct R3eGame { uint8_t unk000[0x324]; int32_t i324; uint8_t unk328[4]; int32_t i32C; } R3eGame;
int      sub_000E3380(void);
void     sub_0001E9B0(void *scene, R3eObj *obj, int a, int b, int c);
extern void *r3_ctx42C8E4;                                          /* 0x0042C8E4 scene context */
void     sub_001453B0(R3eObj *obj, R3eObj *act);                    /* regargs: obj=ESI act=EDI */
void     sub_00189DE0(void *fx, int on);

int      r3_FsmEnter172B50(int st, R3eObj *c, R3eObj *obj);         /* 0x00172B50 regargs: st=EAX c=ECX obj=stack; returns the handler result */
R3eObj  *sub_000CB9B0(void);
float    sub_000F7720(R3eObj *obj, const float *pos);               /* turn angle toward pos */
void     sub_0017EF30(void);
/* 0x003FE0C0: three 0x58-byte records. */
typedef struct R3eRec58 {
    int32_t i00, i04, i08;   /* +0x00 */
    uint8_t unk0C[0x1C - 0x0C];
    float   f1C, f20;        /* +0x1C */
    uint8_t unk24[0x40 - 0x24];
    float   f40;             /* +0x40 */
    uint8_t unk44[0x58 - 0x44];
} R3eRec58;
extern R3eRec58 r3e_recs3FE0C0[3];

int      sub_00147780(R3eObj *act, R3eObj *obj, int k);            /* regargs: act=EAX obj, k=stack */
int      r3e_InFrame145730(float t, unsigned int n);                /* 0x00145730 */
void     sub_00155D10(R3eObj *act, int k);

float    sub_00113200(R3eObj *obj, const float *pos);               /* turn angle toward pos */
void     sub_00139CF0(void);
void     b13_State1381E0(R3eObj *obj, R3eObj *act);                 /* 0x001381E0 node callback */
void     sub_0013A120(R3eObj *obj, int k, const void *tbl);
void     sub_0001D190(R3eObj *obj);
void     sub_001134B0(R3eObj *act);
void     sub_0001D7A0(void *fx);
void     sub_0001D8B0(void *slot, int kind);
extern const uint8_t b3b_tbl31DBD4[], b3b_tbl31DBFC[];              /* 0x0031DBD4, 0x0031DBFC (area b3b) */
/* 0x003F8CE8 / 0x003F8FB8: six 0x78-byte and six 0x88-byte component holders, two slots each. */
typedef struct R3eHold78 { uint8_t slot00[0x10]; uint8_t slot10[0x78 - 0x10]; } R3eHold78;
typedef struct R3eHold88 { uint8_t slot00[0x10]; uint8_t slot10[0x88 - 0x10]; } R3eHold88;
extern R3eHold78 r3e_holds3F8CE8[6];
extern R3eHold88 r3e_holds3F8FB8[6];
extern int32_t   r3e_i3F92F0, r3e_i3F92F4, r3e_i3F92F8, r3e_i3F92FC;
extern int32_t   r3d_i3F9300;                                       /* 0x003F9300 (area r3d) */

int      sub_0013A900(R3eObj *obj, R3eObj *act);
void     sub_00142330(R3eObj *obj, R3eObj *act);
void    *sub_001890F0(int k, const void *a, const void *b, float r);
void     r3d_Hold188C00(void *h, const float *pos);                 /* 0x00188C00 (area r3d) */
float    sub_001065B0(void);
extern void   *r3c_i3FEB10, *r3c_i3FEB14;                           /* 0x003FEB10, 0x003FEB14 (area r3c) */
extern int16_t r3c_s3FEAB8;                                         /* 0x003FEAB8 */
extern float   r3c_f3FEABC, r3c_f3FEAC0, r3c_f3FEAC4, r3c_f3FEAC8;  /* 0x003FEABC.. (area r3c) */
extern const uint8_t r3e_tbl32C2E8[], r3e_tbl32C338[], r3e_tbl32C388[], r3e_tbl32C398[];
extern const uint8_t b3b_tbl31CE1C[];                               /* 0x0031CE1C (area b3b) */
void     sub_001B2080(void *node);
int      sub_0018E640(void *ref, R3eObj *obj);                      /* release a reference */
void     sub_00048250(int h);

#endif
