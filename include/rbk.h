#ifndef RBK_H
#define RBK_H
#include "oogie.h"
#include "rbj.h"

/* Area rbk: larger game functions in 0x000D0000..0x0018FFFF (Jack's moves and actions,
   enemy and boss AI states). All names inferred. Register mappings are in the comments
   and in config/function_states_rbk.csv. */

/* Float to int truncation (same as RFL_FTOI in rfl.h). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define RBK_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define RBK_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ collision probes */
/* Probe description passed to 0x000EEBC0: a kind, a point count and the points. */
typedef struct RbkProbe {
    int32_t  kind00;          /* +0x00 */
    int32_t  count04;         /* +0x04 */
    float   *shape08;         /* +0x08 */
} RbkProbe;
/* Probe result (0x18 bytes) built by 0x000EEBC0 and read by 0x000EE3B0. */
typedef struct RbkProbeBox { float f[6]; } RbkProbeBox;
/* Sphere: centre and radius (first argument of 0x000EE2B0). */
typedef struct RbkSphere {
    RbjVec4  c;               /* +0x00 */
    float    r10;             /* +0x10 */
} RbkSphere;
/* Hit result of 0x000EE3B0: a sphere (radius > 0: hit) and a point. */
typedef struct RbkHit {
    RbkSphere s;              /* +0x00 */
    RbjVec4  point14;         /* +0x14 */
} RbkHit;
/* Node transform seen as two matrices (world at +0, local at +0x40). */
typedef struct RbkXform2 {
    RbjMat4  m;               /* +0x00 */
    RbjMat4  local40;         /* +0x40 */
} RbkXform2;
/* Jack's guard / reach area filled by 0x000C4250. */
typedef struct RbkReach {
    uint8_t  unk00[0x10];
    float    x10;             /* +0x10 */
    float    y14;             /* +0x14 */
} RbkReach;
void  sub_000EEBC0(void *coll, RbkProbe *probe, RbkProbeBox *box);
void  sub_000EE3B0(RbjXform *xf, RbkProbeBox *box, RbkHit *hit);
void  sub_000C4250(PlayerStats *s, RbkReach *reach, float *size);
int   sub_000EE2B0(RbkSphere *s, RbkReach *reach, RbjVec4 *point);
int   sub_000CFFB0(void);
float sub_00113290(RbjNode *o, const RbjVec4 *pt);
void  r3_Rotate18CB10(RbjNode *o, float a);                     /* 0x0018CB10 o=ESI a=stack */
int   sub_00049700(int id, int r, int g, int b, const RbjVec4 *pos, int a, float size, int c);
int   sub_000D3BF0(PlayerStats *s, RbjNode *node, int kind, RbjVec4 *point, RbjVec4 *dir);

/* ------------------------------------------------------------ actors of the 0x0018C1B0 family */
typedef struct RbkAct {
    uint8_t  unk00[0x6C];
    void    *coll6C;          /* +0x6C collision object */
    uint8_t  unk70[4];
    void    *work74;          /* +0x74 */
} RbkAct;
int rbk_HitJack18BCA0(RbjNode *node, RbkAct *act);

/* Work block of the rolling actor (0x0018CB60). */
typedef struct RbkRollWork {
    uint32_t flags00;         /* +0x00 bit 4: no steering / done, 8: no gravity, 0x20: low bounce */
    float    spin04;          /* +0x04 roll speed */
} RbkRollWork;
void rbk_Roll18CB60(RbjNode *node, RbjActor *act);

/* Work block of the thrown piece set up by 0x0018D400. */
typedef struct RbkShotWork {
    uint8_t  unk00[4];
    float    speed04;         /* +0x04 */
    uint8_t  unk08[4];
    float    lift0C;          /* +0x0C */
    float    fwd10;           /* +0x10 */
} RbkShotWork;
typedef struct RbkCompHolder {
    uint8_t  unk00[0x74];
    void    *work74;          /* +0x74 */
} RbkCompHolder;
void rbk_Throw18D400(RbjNode *o, RbjNode *from, int mode);

/* ------------------------------------------------------------ Jack (view of PlayerStats, 0x0041FEC0) */
/* Only the fields touched by rbk functions; the same object as PlayerStats in oogie.h. */
typedef struct RbkJack {
    RbjVec4  move000;         /* +0x000 this frame's movement, cleared after use */
    uint8_t  unk010[0xD4 - 0x10];
    int32_t  modeD4;          /* +0x0D4 4, 5: cannot be hit */
    int32_t  stateD8;         /* +0x0D8 current action (0x1D, 0x1E: holding) */
    uint8_t  unkDC[0xE4 - 0xDC];
    float    timerE4;         /* +0x0E4 counts up to 1000 */
    float    timerE8;         /* +0x0E8 counts up to 1000 */
    int32_t  modeEC;          /* +0x0EC */
    uint8_t  unkF0[4];
    float    yawGoalF4;       /* +0x0F4 heading the stick asks for */
    float    yawFromF8;       /* +0x0F8 heading the turn starts from */
    float    yawFC;           /* +0x0FC current move heading */
    float    turnRef100;      /* +0x100 stick angle when the turn began */
    float    stick104;        /* +0x104 stick angle (negated) */
    float    yaw108;          /* +0x108 facing */
    uint8_t  unk10C[4];
    float    moveX110;        /* +0x110 root motion x per frame unit */
    float    moveY114;        /* +0x114 root motion y per frame unit */
    float    moveZ118;        /* +0x118 root motion z per frame unit */
    uint8_t  unk11C[4];
    int32_t  turning120;      /* +0x120 */
    uint8_t  unk124[4];
    int32_t  anim128;         /* +0x128 current animation id */
    uint8_t  unk12C[0x148 - 0x12C];
    float    f148;            /* +0x148 */
    float    fallSpeed14C;    /* +0x14C vertical move this frame, < 0 rising */
    uint32_t flags150;        /* +0x150 bit 0x80: no step-up, 0x400000: on the floor, 0x2000000: no floor test */
    uint32_t flags154;        /* +0x154 */
    uint8_t  unk158[0x164 - 0x158];
    int32_t  guard164;        /* +0x164 */
    float    guardTime168;    /* +0x168 */
    uint8_t  unk16C[0x1A8 - 0x16C];
    RbjVec4  prev1A8;         /* +0x1A8 position before the move (y: 15 lower, floor probe start) */
    int32_t  costume1B8;      /* +0x1B8 */
    uint8_t  unk1BC[0xD2C - 0x1BC];
    int32_t  hurtD2C;         /* +0xD2C non-zero: recovering from a hit */
    float    hurtTimeD30;     /* +0xD30 */
    int32_t  lastDamageD34;   /* +0xD34 */
    int32_t  lastSrcAD38;     /* +0xD38 */
    int32_t  lastSrcBD3C;     /* +0xD3C */
    int32_t  lastKindD40;     /* +0xD40 */
    uint8_t  unkD44[4];
    float    stunD48;         /* +0xD48 */
    uint8_t  unkD4C[4];
    float    knockD50;        /* +0xD50 */
    float    knockD54;        /* +0xD54 */
    uint8_t  unkD58[4];
    void    *linkD5C;         /* +0xD5C last attacker / grabbed object */
    uint32_t flagsD60;        /* +0xD60 bit 0: invulnerable */
    uint8_t  unkD64[0xEE8 - 0xD64];
    int32_t  floorKindEE8;    /* +0xEE8 floor material id 0..0x14 */
    uint32_t floorBitsEEC;    /* +0xEEC floor flags & 0xF00 */
    uint8_t  unkEF0[0xFD8 - 0xEF0];
    RbjNode *modelFD8;        /* +0xFD8 Jack's model node (g_playerObj) */
} RbkJack;
/* Attacker record passed to 0x000D3BF0 (ids at +4/+8 index the damage table). */
typedef struct RbkAttacker {
    uint8_t  unk00[4];
    int32_t  idA04;           /* +0x04 */
    int32_t  idB08;           /* +0x08 */
} RbkAttacker;
/* Message sent to an object by 0x000EE010. */
typedef struct RbkMsg {
    int32_t  id00;            /* +0x00 */
    int32_t  a04;             /* +0x04 */
    int32_t  a08;             /* +0x08 */
    float    f0C;             /* +0x0C */
    RbjVec4  v10;             /* +0x10 */
    RbjVec4  v20;             /* +0x20 */
} RbkMsg;
int   sub_0019BE60(int mask);
int   sub_00171EB0(int a, int b, int kind, int field);
void  sub_000D21E0(RbkJack *j, RbkAttacker *src, RbjVec4 *dir, int amount);
void  sub_000EE010(void *obj, RbkMsg *msg);
void  sub_000D1930(RbkJack *j);
void  sub_000BD4A0(RbkJack *j, int a, float b);
void  sub_000CFE00(RbkJack *j, RbkAttacker *src, RbjVec4 *dir);
void  rtc_PlayerEventB(RbkJack *j);                             /* 0x000D3620 */
int   rbk_JackHit0D3BF0(RbkJack *j, RbkAttacker *src, int kind, RbjVec4 *point, RbjVec4 *dir);

typedef void (*RbkKnockFn)(RbkJack *j, RbkAttacker *src, RbjVec4 *dir);
void  sub_000CFC80(RbkJack *j, RbkAttacker *src, RbjVec4 *dir);
void  sub_000CFF10(RbkJack *j, RbkAttacker *src, RbjVec4 *dir);
void  rbk_Knock0D21E0(RbkJack *j, RbkAttacker *src, RbjVec4 *dir, int kind);

#define RBK_JACK ((RbkJack *)&g_stats)
/* Floor polygon found by the collision queries (record with its attributes at +0x50). */
typedef struct RbkFloor {
    uint8_t  unk00[0x44];
    float    y44;             /* +0x44 floor height */
} RbkFloor;
RbkFloor *sub_0001B490(RbjVec4 *from, RbjVec4 *to, int *mask, void *out);
int   sub_00080D80(RbkFloor *f, int mask);
int   sub_00080D90(RbkFloor *f);
int   sub_00080D60(RbkFloor *f);
int   sub_000A47A0(void);
int   sub_00080970(void);
void  sub_000824F0(void *world, int set, RbjVec4 *from, RbjVec4 *to, int a, int b);
RbkFloor *sub_00080CB0(int set, RbjVec4 *from, RbjVec4 *to);
/* Collision world holder (0x0042C8E4 points at it). */
typedef struct RbkScene {
    uint8_t  unk00[0x5C];
    void    *world5C;         /* +0x5C */
} RbkScene;
int   rbk_Floor0D1490(RbjNode *node, int a, int b, int *mask);

/* Motion block of Jack's model (model +0x34): root motion per frame at +0x70 / +0x78. */
typedef struct RbkMotion {
    uint8_t  unk00[0x70];
    float    dx70;            /* +0x70 */
    uint8_t  unk74[4];
    float    dz78;            /* +0x78 */
} RbkMotion;
typedef struct RbkModelHead {
    uint8_t  unk00[0x34];
    RbkMotion *motion34;      /* +0x34 */
} RbkModelHead;
#define RBK_MOTION(node) (((RbkModelHead *)(node))->motion34)
extern float   rbk_g420EB0;                                     /* 0x00420EB0 */
extern int32_t rbk_g42CA34;                                     /* 0x0042CA34 */
extern int32_t rbk_g42CA38;                                     /* 0x0042CA38 */
void  sub_000CC2A0(RbkJack *j);
void  sub_000C6850(RbkJack *j);
void  sub_000CC360(RbkJack *j);
void  sub_000CC9E0(RbkJack *j);
void  sub_000C4600(RbkJack *j);
void  sub_000D0D30(RbkJack *j);
void  sub_000C9790(void);
void  sub_000C6B90(RbkJack *j);
void  sub_000C9A70(void);
void  sub_000C9980(void);
void  sub_000D2D30(RbkJack *j);
void  sub_000CDA50(RbkJack *j, int a, int b);
void  sub_000D0A50(RbkJack *j);
void  sub_000C2A40(RbkJack *j);
void  sub_000CCB30(RbkJack *j);
void  sub_000CC920(RbkJack *j);
void  sub_000D05B0(RbkJack *j);
void  sub_000D0850(RbkJack *j);
void  sub_000D2C40(RbkJack *j);
void  sub_000243B0(int a, int b);
void  sub_000CBD10(RbkJack *j);
void  sub_000CA010(RbkJack *j);
void  sub_000CA340(RbkJack *j);
void  sub_000D1F90(RbkJack *j);
void  sub_000D2090(RbkJack *j);
void  sub_000CBA30(RbkJack *j);

/* Push records of a model node (two hit-push slots). */
typedef struct RbkPushA {
    RbjVec4  v00;             /* +0x00 */
    float    size10;          /* +0x10 */
    int32_t  kind14;          /* +0x14 */
    uint8_t  unk18[8];
} RbkPushA;
typedef struct RbkPushB {
    RbjVec4  v00;             /* +0x00 */
    RbjVec4  v10;             /* +0x10 */
    int32_t  kind20;          /* +0x20 */
} RbkPushB;
typedef struct RbkModelPush {
    uint8_t  unk00[0xD8];
    RbkPushA pushD8;          /* +0x0D8 */
    RbkPushB pushF8;          /* +0x0F8 */
} RbkModelPush;
extern int32_t rbk_g413164;                                     /* 0x00413164 current stage */
void  sub_000D0EA0(RbkJack *j);
void  sub_000D0F50(RbkJack *j);
void  sub_000D1180(RbkJack *j);
void  rbk_JackMove0D2D90(RbkJack *j);

extern const char rbg_s276DBC[];                                /* 0x00276DBC "chjh1" */
void  sub_000BD4D0(RbkJack *j, int state);
void  sub_000C5B10(void);
void  sub_000D4C10(void *rig);
void  sub_000D45B0(void *rig, int a, int b, float c);
void  sub_000BC6F0(const char *name, int on);
void  sub_000CED50(void *child);
void *sub_0001D290(RbjNode *o, int id);

int   rbk_JackHurt0D3E10(RbkJack *j, RbjVec4 *dir, int kind, int damage);
int   rbk_JackHitBy0D3FA0(RbkJack *j, RbkAttacker *src, int idA, int idB, int kind, RbjVec4 *dir);

/* ------------------------------------------------------------ Jack's aim rig (0x0042C8EC, 0x418 bytes) */
typedef struct RbkRigBone {
    RbjMat4  m;               /* +0x00 local matrix (row 3: position) */
    uint8_t  unk40[0x80 - 0x40];
    struct RbkRigBone *parent80; /* +0x80 */
    uint8_t  unk84[4];
    struct RbkRigBone *next88;   /* +0x88 */
    int32_t  kind8C;          /* +0x8C 10: chain bone */
} RbkRigBone;
typedef struct RbkRigRoot {
    int32_t  id00;            /* +0x00 */
    int32_t  n04;             /* +0x04 */
    uint8_t  unk08[0x20 - 8];
    RbkRigBone *bone20;       /* +0x20 */
    uint8_t  unk24[0x3C - 0x24];
    struct RbkRigRoot *next3C; /* +0x3C */
} RbkRigRoot;
typedef struct RbkRig {
    int32_t  a00, a04;        /* +0x00 */
    int32_t  cur08;           /* +0x08 current record id */
    int32_t  next0C;          /* +0x0C record id being blended in */
    float    fade10;          /* +0x10 */
    int32_t  show14;          /* +0x14 1: appearing, 2: vanishing */
    int32_t  step18;          /* +0x18 */
    float    time1C;          /* +0x1C */
    float    size20;          /* +0x20 */
    float    p24[8];          /* +0x24 blended parameters; [4] (+0x34) segment length */
    float    len44[16];       /* +0x44 */
    RbjVec4  pos84[16];       /* +0x84 joint positions */
    RbjVec4  vel184[16];      /* +0x184 */
    uint8_t  unk284[0x10];
    RbjVec4  rest294[16];     /* +0x294 */
    float    f394, f398;      /* +0x394 */
    RbjVec4  v39C;            /* +0x39C */
    int32_t  a3AC;            /* +0x3AC */
    RbkRigRoot *root3B0;      /* +0x3B0 */
    uint8_t  unk3B4[4];
    float    f3B8;            /* +0x3B8 */
    int32_t  a3BC;            /* +0x3BC */
    float    f3C0[4];         /* +0x3C0 */
    float    from3D0[8];      /* +0x3D0 blend start values */
    float    to3F0[8];        /* +0x3F0 blend end values */
    float    blendTime410;    /* +0x410 > 0: blending */
    float    blendT414;       /* +0x414 */
} RbkRig;
void *sub_00053AB0(int size, int a, int tag);
RbkRigRoot *r1_StateNew(int i);                                 /* 0x0001D160 */
void  r1b_RecAddChild(RbkRigRoot *root, RbkRigRoot *child);     /* 0x0001D240 */
RbkRig *rbk_RigNew0D42F0(void);

void  sub_001B1F70(RbjMat4 *d, const RbjMat4 *s);              /* matrix inverse */
float sub_00082D70(const RbjVec4 *v);                           /* vector length */
void  rbk_RigFollow0D4630(RbkRig *r, int mode);
void  rbk_RigBlend0D4940(RbkRig *r);
void  r1_ChildShow(RbkRigRoot *root, int id);                   /* 0x0001D470 */
void  r1_ChildHide(RbkRigRoot *root, int id);                   /* 0x0001D4B0 */
void  rbk_RigScale0D4C60(RbkRig *r);

void  r4e_VecLerp4(RbjVec4 *d, const RbjVec4 *a, const RbjVec4 *b, float t);  /* 0x001ADC60 d = (a - b) * t + b */
void  rbk_RigSegment0D5050(const RbjVec4 *p0, RbjVec4 *p1, RbjVec4 *p2, const RbjVec4 *target, float len, float t);

extern uint32_t rbk_g418B40;                                    /* 0x00418B40 */
extern uint8_t  rbk_g418A80[];                                  /* 0x00418A80 light set */
void  r4b_NodePRewind(void *set);                               /* 0x001BA8F0 */
void  r1_NodeShow(RbkRigRoot *rec);                             /* 0x0001D610 */
void  r1_NodeHide(RbkRigRoot *rec);                             /* 0x0001D700 */
void  rbk_RigShow0D5200(RbkRig *r);

/* Entity slots at 0x004242C0 (32 x 0x260). */
typedef struct RbkSlotObj {
    uint8_t  unk00[0xC];
    uint32_t flags0C;         /* +0x0C bit 0x20: solid */
    uint8_t  unk10[0xD0 - 0x10];
    int32_t  kindD0;          /* +0xD0 */
} RbkSlotObj;
typedef struct RbkSlot {
    uint32_t flags00;         /* +0x000 bit 0: used, 0x10000000: hookable */
    uint8_t  unk04[0x120 - 4];
    RbkSlotObj *obj120;       /* +0x120 */
    uint8_t  unk124[0x260 - 0x124];
} RbkSlot;
extern RbkSlot g_ac0_entities[32];                              /* 0x004242C0 */
extern uint64_t rbk_frames42C918;                               /* 0x0042C918 64-bit frame counter */
/* Box of an entity built by 0x0001B4D0. */
typedef struct RbkBox { float f[16]; } RbkBox;
float sub_000CA300(RbkJack *j);
void  r1i_BoxBuild(RbkSlotObj *o, RbkBox *box);                 /* 0x0001B4D0 */
int   sub_0001BAD0(RbkBox *box, RbjVec4 *from, RbjVec4 *to, RbjVec4 *hit);
int   sub_0001B9E0(float *r, RbjVec4 *pos, float len, RbjVec4 *a, RbjVec4 *b);
void *rbk_JackFx0D0060(RbkJack *j, int id, RbjVec4 *pos);       /* 0x000D0060 */
void  sub_000AA2E0(int n);
int   rbk_RigHook0D53B0(RbkJack *j, RbkRig *r, int k, RbjVec4 *hit, RbjVec4 *hit2);

void  rbk_RigParams0D56C0(RbkRig *r, float seg, float p5, float p6, float p7, float p0, float p1, float p2, float p3);

/* Hit record returned by the world probes 0x00080CB0 / 0x00080CF0. */
typedef struct RbkWorldHit {
    uint8_t  unk00[0x30];
    RbjVec4  normal30;        /* +0x30 */
    RbjVec4  point40;         /* +0x40 */
} RbkWorldHit;
void  sub_000822D0(void *world, int set, RbjVec4 *centre, float r, int mask, int b);
RbkWorldHit *sub_00080CF0(int set, RbjVec4 *centre);
void  rbk_RigReach0D58F0(RbkRig *r, void *world, int mask, int unused, int k);

/* Scene holder at 0x0042C8E4 seen with its collision world at +0x54. */
typedef struct RbkScene54 {
    uint8_t  unk00[0x54];
    void    *world54;         /* +0x54 */
} RbkScene54;
void  sub_00082200(void *world, RbjVec4 *from, RbjVec4 *to, int b);
void  rbk_RigReachAll0D60F0(RbkRig *r);

/* Work block of the spinning flier (0x0018C070). */
typedef struct RbkSpinWork {
    uint8_t  unk00[0x10];
    float    spin10;          /* +0x10 angle per frame */
    RbjVec4  axis14;          /* +0x14 */
    RbjVec4  vel24;           /* +0x24 */
} RbkSpinWork;
int   sub_0018BB20(RbjNode *node);                              /* node=EAX */
void  rfl_MtxRotateAxis(RbjMat4 *d, const RbjMat4 *s, const RbjVec4 *axis, float a);   /* 0x00145AA0 */
void  rfl_VecScaledDir(RbjVec4 *d, const RbjVec4 *s, float len);                         /* 0x00145CD0 */

/* Work block of the spinning bomb (0x0018DA80). */
typedef struct RbkBombWork {
    uint32_t flags00;         /* +0x00 bit 2: stuck, 4: fuse burnt, 8: falls while stuck */
    float    spin04;          /* +0x04 */
    float    fuse08;          /* +0x08 */
    float    fuseMax0C;       /* +0x0C */
    float    fuseRate10;      /* +0x10 */
} RbkBombWork;
void  rbk_Bomb18DA80(RbjNode *node, RbjActor *act);


/* Boss manager returned by 0x00100110. */
typedef struct RbkBoss {
    uint8_t  unk00[0x8C];
    RbjNode *body8C;          /* +0x8C boss body node */
    uint8_t  unk90[0x1CA - 0x90];
    int16_t  busy1CA;         /* +0x1CA */
    float    reach1CC;        /* +0x1CC */
    uint8_t  unk1D0[4];
    RbjVec4  dir1D4;          /* +0x1D4 */
} RbkBoss;
/* Work block of the boss arm piece (0x0018FA40). */
typedef struct RbkArmWork {
    uint8_t  unk00[0xC];
    RbjVec4  vel0C;           /* +0x0C */
} RbkArmWork;
extern float a50_framesPerSecond;                               /* 0x0042C964 */
RbkBoss *r4i_GetMgr(void);                                      /* 0x00100110 */
float sub_001A3ED0(float a);                                    /* sin */
float sub_001A3EE0(float a);                                    /* cos */
int   sub_0018F7B0(RbjVec4 *out);
void  rbk_ArmStart18FA40(RbjNode *node, RbjActor *act);

/* Analog stick block (0x00420EA0; magnitude at +0x10). */
typedef struct RbkStick {
    uint8_t  unk00[0x10];
    float    mag10;           /* +0x10 */
} RbkStick;
extern RbkStick rbk_stick420EA0;                                /* 0x00420EA0 */
float sub_000BC040(RbkStick *st);                               /* stick angle */
float r6c_AngleAdd(float a, float b);                           /* 0x000829D0 */
void  r6c_RotateVec(RbjVec4 *d, const RbjVec4 *euler, const RbjVec4 *v);   /* 0x00082A30 */

/* @@RBK_END */
#endif
