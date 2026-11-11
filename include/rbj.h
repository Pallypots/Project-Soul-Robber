#ifndef RBJ_H
#define RBJ_H
#include "oogie.h"

/* Area rbj: larger game functions in 0x000D0000..0x0018FFFF (enemy AI, Jack's moves, script
   handlers, stage logic, effects). All names inferred. Register mappings are in the comments
   and in config/function_states_rbj.csv. */

/* Float to int truncation (same as RFL_FTOI in rfl.h). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define RBJ_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define RBJ_FTOI(x) ((int)(x))
#endif

typedef struct RbjVec4 { float x, y, z, w; } RbjVec4;
typedef struct RbjMat4 { RbjVec4 r[4]; } RbjMat4;
typedef struct RbjBone RbjBone;

/* ------------------------------------------------------------ vector / matrix library */
void  rbj_VecNormalize(RbjVec4 *d, const RbjVec4 *s);            /* 0x001AD7E0 */
float rbj_VecDot(const RbjVec4 *a, const RbjVec4 *b);            /* 0x001AD9D0 */
void  rbj_VecCross(RbjVec4 *d, const RbjVec4 *a, const RbjVec4 *b); /* 0x001ADA60 */
void  rbj_VecScale(RbjVec4 *d, const RbjVec4 *s, float k);       /* 0x001ADB60 d = s * k */
void  rbj_MatIdentity(RbjMat4 *m);                              /* 0x001AD940 */
void  rbj_MatRotX(RbjMat4 *d, const RbjMat4 *s, float a);        /* 0x001AD8B0 */
void  rbj_MatRotY(RbjMat4 *d, const RbjMat4 *s, float a);        /* 0x001AD8E0 */
void  rbj_MatRotZ(RbjMat4 *d, const RbjMat4 *s, float a);        /* 0x001AD910 */
void  rbj_MatCopy(RbjMat4 *d, const RbjMat4 *s);                /* 0x001ADA40 */
float rbj_Acos(float x);                                         /* 0x001A3F20 */
float rbj_Sqrt(float x);                                         /* 0x001A3F50 */

extern float a50_frameSeconds;                                  /* 0x0042C85C */
void  rbj_VecSub(RbjVec4 *d, const RbjVec4 *a, const RbjVec4 *b);  /* 0x001AD9F0 d = a - b */
void  rbj_VecAdd(RbjVec4 *d, const RbjVec4 *a, const RbjVec4 *b);  /* 0x001ADAF0 d = a + b */
void  rbj_VecScale4(RbjVec4 *d, const RbjVec4 *s, float k);      /* 0x001ADBA0 d = s * k */
void  rbj_VecTransform(RbjVec4 *d, const void *m, const RbjVec4 *v); /* 0x001AD9B0 */
void  rbj_MatOrtho(void *d, const void *s);                     /* 0x000385D0 */
int   rbj_ObjDestroy(void *o);                                  /* 0x000ED780 */
RbjBone *rbj_Joint(void *o, int k);                             /* 0x0001D0F0 */
void  rbj_ObjSetMotionDir(void *motion, const RbjVec4 *pos, const RbjVec4 *dir, const RbjVec4 *up); /* 0x00034DD0 */
int   rbj_Sound(int id, const RbjVec4 *pos, int c);             /* 0x000494D0 */

void  r4_NodeDetach(void *xf);                                 /* 0x001B2080 */
void  sub_0018B130(void);
void  rbj_MatMul(void *d, const void *a, const void *b);         /* 0x001AD7C0 */
void  rbj_MatAxisAngle(RbjMat4 *d, const RbjVec4 *axis, float a); /* 0x001B2890 */
float rbj_Distance(const RbjVec4 *a, const RbjVec4 *b);          /* 0x001B2770 */
void  sub_000C56B0(void *o);

/* ------------------------------------------------------------ state-machine actors (0x00189DA0 family) */
typedef struct RbjStateWork {
    uint32_t flags00;         /* +0x00 */
    struct RbjNode *owner04;  /* +0x04 holder object */
    uint32_t flags08;         /* +0x08 */
    float    timer0C;         /* +0x0C */
    RbjVec4  axis10;          /* +0x10 */
    float    f20;             /* +0x20 */
} RbjStateWork;

typedef struct RbjActor RbjActor;
/* Bone / joint transform block (0x80 bytes). */
struct RbjBone {
    RbjMat4  m;               /* +0x00 */
    uint8_t  unk40[0x70 - 0x40];
    RbjVec4  pos70;           /* +0x70 */
};
typedef struct RbjXform {
    RbjMat4  m;               /* +0x00 */
    uint8_t  unk40[0x70 - 0x40];
    RbjVec4  pos70;           /* +0x70 */
    RbjBone *parent80;        /* +0x80 attached-to bone */
    uint8_t  unk84[0xC4 - 0x84];
    RbjBone *bonesC4;         /* +0xC4 */
} RbjXform;
/* Scene object (0x150-byte records: the pool at 0x00414444 and the templates at 0x003FF584). */
typedef struct RbjNode {
    uint8_t  unk00[8];
    int32_t  kind08;          /* +0x08 */
    uint32_t flags0C;         /* +0x0C bit 0: in use */
    uint32_t flags10;         /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    RbjXform *xf20;           /* +0x20 */
    uint8_t  unk24[0x30 - 0x24];
    void    *anim30;          /* +0x30 */
    uint8_t  unk34[0x50 - 0x34];
    RbjVec4  rot50;           /* +0x50 Euler angles x, y, z */
    RbjVec4  pos60;           /* +0x60 */
    RbjVec4  scale70;         /* +0x70 */
    RbjVec4  push80;          /* +0x80 one-frame push, cleared after use */
    uint8_t  unk90[0xA0 - 0x90];
    RbjVec4  vA0;             /* +0xA0 */
    float    fB0;             /* +0xB0 */
    float    fB4;             /* +0xB4 */
    uint8_t  unkB8[0xE8 - 0xB8];
    float    fE8;             /* +0xE8 */
    uint8_t  unkEC[4];
    int32_t  iF0;             /* +0xF0 */
    uint8_t  unkF4[4];
    RbjVec4  vF8;             /* +0xF8 */
    RbjVec4  v108;            /* +0x108 */
    uint8_t  unk118[0x128 - 0x118];
    uint8_t  b128;            /* +0x128 bits 0x18: on the ground */
    uint8_t  unk129[0x130 - 0x129];
    void    *p130;            /* +0x130 motion list */
    uint8_t  unk134[0x14C - 0x134];
    void    *p14C;            /* +0x14C */
} RbjNode;
typedef void (*RbjStateFn)(RbjNode *node, RbjActor *act);
typedef int  (*RbjActFn)(RbjNode *node, RbjActor *act);
struct RbjActor {
    uint8_t  unk00[0x28];
    float    f28;             /* +0x28 */
    float    f2C;             /* +0x2C */
    uint8_t  unk30[0x4C - 0x30];
    RbjVec4  vel4C;           /* +0x4C */
    int32_t  i5C;             /* +0x5C */
    int32_t  state60;         /* +0x60 */
    int32_t  prev64;          /* +0x64 */
    int32_t  i68;             /* +0x68 */
    float    timer6C;         /* +0x6C */
    float    f70;             /* +0x70 */
    RbjStateWork *work74;     /* +0x74 */
    RbjActFn fn78;            /* +0x78 may-end test */
    RbjStateFn fn7C;          /* +0x7C per-frame movement */
    RbjActFn fn80;            /* +0x80 */
    RbjStateFn *states84;     /* +0x84 state entry handlers */
    RbjStateFn *update88;     /* +0x88 state update handlers */
};
/* Component 0xD of a spawned object (set up by 0x000EE270). */
typedef struct RbjComp {
    uint8_t  unk00[0x24];
    void    *fn24, *fn28, *fn2C;  /* +0x24.. callbacks */
} RbjComp;
typedef int (*RbjKindInit)(RbjNode *node, RbjActor *act, void *arg);
extern RbjNode  *rbj_pool414444;           /* 0x00414444 object pool (0x150-byte records) */
extern int32_t  *rbj_poolCount414440;      /* 0x00414440 -> number of pool records */
extern int32_t  *rbj_tmplSet3FF57C;        /* 0x003FF57C -> number of templates (first word) */
extern RbjNode  *rbj_tmpl3FF584;           /* 0x003FF584 template records */
extern void     *rbj_scene42C8E4;          /* 0x0042C8E4 */
extern RbjKindInit rbj_kindInit32C448[];   /* 0x0032C448 per-kind init, kinds 0..0x22 */
extern float a50_frameUnits;               /* 0x0042C858 */
void  sub_00022380(RbjNode *o, RbjNode *tmpl, void *scene);
void  sub_0001E9B0(void *scene, RbjNode *o, void *p, int a, int b);
void  sub_0001EBF0(RbjNode *o, int a);
void *sub_0001D960(RbjNode *o, int id);
void  sub_000EE270(RbjComp *c);
void  sub_0001EB80(RbjNode *o);
int   sub_000AD090(RbjNode *node, RbjActor *act);
int   rbj_TryEnd189CF0(RbjNode *node);              /* 0x00189CF0 */
void  rbj_Update189D30(RbjNode *node);              /* 0x00189D30 */
int   rbj_Call189E90(RbjNode *node, void *arg);     /* 0x00189E90 */
void  rbj_Move189ED0(RbjNode *node, RbjActor *act);
RbjNode *rbj_Spawn18A060(int kind, const RbjVec4 *pos, const RbjVec4 *rot, void *arg);
void rbj_SetState(RbjNode *node, RbjActor *act, int state);     /* 0x00189DA0 */
/* Work block of carried objects (second layout of +0x74). */
typedef struct RbjCarryWork {
    uint32_t flags00;         /* +0x00 bit 2: drop requested */
    float    f04;             /* +0x04 */
    uint8_t  unk08[4];
    RbjNode *holder0C;        /* +0x0C */
} RbjCarryWork;
int   sub_001C7EE1(void);                                       /* rand */
int   a80_Get3ED238(void);                                      /* 0x00087500 */
void  rbj_MatTranslate(RbjMat4 *d, const RbjMat4 *s, const RbjVec4 *t); /* 0x001AE010 */
void *rbj_ListPlayMotion(RbjNode *o, void *list, int a, int b);   /* 0x00035DD0 */
void  rbj_Place34E00(void *mot, const RbjVec4 *pos, const RbjVec4 *dir, const RbjVec4 *up); /* 0x00034E00 */
int   sub_00049700(int id, int r, int g, int b, const RbjVec4 *pos, int a, float size, int c);
int   sub_000C46A0(float a, float b, float c, const RbjVec4 *pos, RbjVec4 *v0, RbjVec4 *v1);
void  sub_000C4D30(RbjNode *o, int a, float b, int c);
void  sub_000C4DF0(RbjNode *o, int a, float b, int c, float d, float e, float f,
                   const RbjVec4 *pos, RbjVec4 *v0, RbjVec4 *v1);
/* ------------------------------------------------------------ actors of the 0x001671D0 family */
typedef struct RbjBWork {
    uint32_t flags00;         /* +0x00 bit 4: target is the second kind; bit 0x10 cleared on retarget */
    uint8_t  unk04[0x10 - 4];
    RbjVec4 *target10;        /* +0x10 position being approached */
    uint8_t  unk14[0x20 - 0x14];
    float    timer20;         /* +0x20 */
    float    bob24;           /* +0x24 bobbing angle */
    float    radius28;        /* +0x28 */
    float    f2C;             /* +0x2C */
} RbjBWork;
typedef struct RbjBAct {
    uint8_t  unk00[0x50];
    int32_t  state50;         /* +0x50 */
    int32_t  phase54;         /* +0x54 */
    uint8_t  unk58[4];
    float    timer5C;         /* +0x5C */
    uint8_t  unk60[0x74 - 0x60];
    RbjBWork *work74;         /* +0x74 */
} RbjBAct;
/* 0x003F8C20: five 0x18-byte target slots (bit 2: used, bit 4: kind). */
typedef struct RbjTargetSlot {
    uint32_t flags;           /* +0x00 */
    uint8_t  unk04[0x14 - 4];
    RbjNode *obj14;           /* +0x14 */
} RbjTargetSlot;
extern RbjTargetSlot b16_pool18[5];        /* 0x003F8C20 */
int  b16_SetState(RbjNode *node, RbjBAct *a, int state);        /* 0x001671D0 */
/* Actor with its velocity at +0x5C (callers of 0x0016FCB0). */
typedef struct RbjCAct {
    uint8_t  unk00[0x5C];
    RbjVec4  vel5C;           /* +0x5C */
} RbjCAct;
/* Work block with a fade timer (0x00169A50). */
typedef struct RbjDWork {
    uint32_t flags00;         /* +0x00 bit 0x20000: fading in */
    uint8_t  unk04[0x10 - 4];
    float    fade10;          /* +0x10 */
    uint8_t  unk14[4];
    float    fall18;          /* +0x18 vertical speed */
} RbjDWork;
void  sub_000EE6D0(RbjNode *o, float v);
/* Work block of the rising piece (0x00168DD0). */
typedef struct RbjEWork {
    uint32_t flags00;         /* +0x00 bit 0x1000: left the ground */
    uint8_t  unk04[0x1C - 4];
    RbjVec4  rise1C;          /* +0x1C x: start height, y: rise speed */
    uint8_t  unk2C[0x3C - 0x2C];
    void    *motion3C;        /* +0x3C */
    uint8_t  unk40[0x5C - 0x40];
    void    *chain5C;         /* +0x5C */
} RbjEWork;
void  sub_00033A70(void *p);
void rbj_Rise168DD0(RbjNode *node, RbjBAct *act);
/* Work block of the homing piece (0x0016DFD0). */
typedef struct RbjFWork {
    uint8_t  unk00[0xC];
    RbjVec4  goalC;           /* +0x0C */
    uint8_t  unk1C[0x40 - 0x1C];
    float    floor40;         /* +0x40 */
} RbjFWork;
/* Work block of the circling flyer (0x0016E250). */
typedef struct RbjGWork {
    uint32_t flags00;         /* +0x00 bit 0x400: closing in, 0x2000: fast turn */
    uint8_t  unk04[0x34 - 4];
    float    f34;             /* +0x34 */
    float    f38;             /* +0x38 */
    float    yaw3C;           /* +0x3C */
    float    floor40;         /* +0x40 */
} RbjGWork;
int   sub_000833E0(void *anim);                                 /* animation finished */
void  b16_PlayAnim(RbjNode *node, RbjBAct *a, int id);           /* 0x00167200 */
void rbj_Circle16E250(RbjNode *node, RbjBAct *act);
extern const RbjVec4 rbj_vec31F410;                              /* 0x0031F410 (3.91, -2.13, -44.98, 1) */
float sub_00113290(RbjNode *o, const RbjVec4 *pt);              /* signed angle from o's facing to pt */
void  r3_SetState16C820(RbjBAct *a, RbjNode *node, int state);  /* 0x0016C820 a=EAX node=EDI */
void rbj_Home16DFD0(RbjNode *node, RbjBAct *act);
void rbj_Fall16FCB0(RbjCAct *act, RbjNode *node);
void rbj_Walk169A50(RbjNode *node, RbjBAct *act);
void rbj_Bob16C690(RbjBAct *act, RbjNode *node);
void rbj_PickTarget16BF80(RbjNode *node, RbjBAct *act);
void rbj_Burst18CE50(RbjNode *node, RbjActor *act);
void rbj_Drop18C540(RbjNode *o);
void rbj_Hover18C950(RbjNode *node, RbjActor *act);

void rbj_Release18B260(RbjNode *o, const RbjVec4 *dir);
void rbj_Spin18AD70(RbjNode *node, RbjActor *act);
void rbj_Spin18AF90(RbjNode *node, RbjActor *act);
void rbj_Launch18A430(RbjActor *act, const RbjVec4 *dir, RbjNode *node, float y, float speed);

#endif
