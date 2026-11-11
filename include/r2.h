#ifndef R2_H
#define R2_H
#include "oogie.h"
#include "shared_decls.h"
/* Area r2: register-argument functions in 0x000D0000..0x00130000. All names inferred.
   Register mappings of callees are in the comments and in config/function_states_r2.csv. */

/* Generic actor: +0x60 position, +0x8C / +0x90 linked actors, +0x278 state block. */
typedef struct R2Actor R2Actor;
typedef struct R2Part { uint8_t unk00[8]; int32_t i08; } R2Part;      /* +0x08 animation id */
struct R2Actor {
    uint8_t  unk000[0x30];
    R2Part  *part30;           /* +0x030 */
    uint8_t  unk034[0x60 - 0x34];
    float    pos60[4];         /* +0x060 */
    uint8_t  unk070[0x8C - 0x70];
    R2Actor *link8C;           /* +0x08C */
    R2Actor *link90;           /* +0x090 */
    uint8_t  unk094[0xB0 - 0x94];
    float    fB0;              /* +0x0B0 */
    uint8_t  unk0B4[0xBC - 0xB4];
    uint16_t wBC;              /* +0x0BC */
};

/* Component of kind 5 (fields used by the wrappers below). */
typedef struct R2Comp5 {
    uint8_t unk000[0x6C];
    int32_t mode6C;            /* +0x06C */
    uint8_t unk070[0xD4 - 0x70];
    void   *hD4;               /* +0x0D4 handle freed by 0x00033A70 */
    int32_t effD8;             /* +0x0D8 effect id released by 0x00048250 */
    uint8_t unk0DC[0xE4 - 0xDC];
    int32_t effE4;             /* +0x0E4 effect id */
} R2Comp5;

/* State block found at +0x278 of most actors (fields used in this area). */
typedef struct R2State {
    uint8_t  unk000[4];
    uint32_t flags04;          /* +0x004 */
    uint8_t  unk008[4];
    uint32_t flags0C;          /* +0x00C */
    uint8_t  unk010[4];
    float    f14;              /* +0x014 */
    uint8_t  unk018[0x20 - 0x18];
    void    *h20;              /* +0x020 */
    uint8_t  unk024[0x34 - 0x24];
    void    *h34;              /* +0x034 handle (0x00036750) */
    uint8_t  unk038[0x50 - 0x38];
    float    f50;              /* +0x050 (also used54 in other actors) */
    int32_t  used54;           /* +0x054 */
    int32_t  free58;           /* +0x058 */
    float    f5C, f60, f64;    /* +0x05C */
    uint8_t  unk068[0xB8 - 0x68];
    float    vecB8[16];        /* +0x0B8 */
    float    vecF8[16];        /* +0x0F8 */
    float    mat138[16];       /* +0x138 */
    int32_t  kind178;          /* +0x178 */
    float    f17C;             /* +0x17C */
    float    f180;             /* +0x180 */
    uint8_t  unk184[0x190 - 0x184];
    int32_t  used190;          /* +0x190 */
    int32_t  free194;          /* +0x194 */
} R2State;
/* Actor seen through its +0x278 state block. */
typedef struct R2Body {
    uint8_t  unk000[0x20];
    uint32_t flags20;          /* +0x020 */
    uint8_t  unk024[0x60 - 0x24];
    float    pos60[1];         /* +0x060 */
    float    y64;              /* +0x064 */
    uint8_t  unk068[0x74 - 0x68];
    float    f74;              /* +0x074 */
    uint8_t  unk078[0x278 - 0x78];
    R2State *st278;            /* +0x278 */
} R2Body;
/* Component of kind 4: +0x22 flags byte, +0x50 state, +0x278 state block. */
typedef struct R2Comp4 {
    uint8_t  unk000[0x22];
    uint8_t  flags22;          /* +0x022 */
    uint8_t  unk023[0x50 - 0x23];
    int32_t  state50;          /* +0x050 */
    uint8_t  unk054[0x278 - 0x54];
    R2State *st278;            /* +0x278 */
} R2Comp4;

/* Target-selection condition record and context (0x00114D60 / 0x0011EE30). */
typedef struct R2Cond { int32_t kind; uint8_t unk04[0xC]; float min10; float max14; } R2Cond;
typedef struct R2Linked { uint8_t unk00[4]; int32_t kind04; uint8_t unk08[4]; uint8_t flags0C; } R2Linked;
typedef struct R2Ctx {
    uint8_t   unk000[0xF8];
    int32_t   mode0F8;         /* +0x0F8 */
    uint8_t   unk0FC[0x104 - 0xFC];
    R2Linked *link104;         /* +0x104 */
} R2Ctx;
/* Step record of the handler scripts run by 0x00114D10 and friends (0x18 bytes). */
typedef struct R2Step { int32_t key00; int32_t type04; uint8_t unk08[0x10]; } R2Step;
typedef int (*R2StepFn)(void *a, void *b, R2Step *s);
/* Point table entry: three vectors then two keys (0x38 bytes). */
typedef struct R2PtRec { float v[3][4]; int32_t key30[2]; } R2PtRec;

/* Doubly linked node found by 0x0003DBC0 (next at +0). */
typedef struct R2Node { struct R2Node *next; } R2Node;

/* Small typed record (+4 kind, +8 sub-kind). */
typedef struct R2Rec { uint32_t unk00; int32_t kind04; int32_t sub08; } R2Rec;

/* Globals */
extern R2Actor *b10_ctl;              /* 0x003F6128 */
extern R2Actor *b10_res3F612C;        /* 0x003F612C */
extern R2Actor *b10_scr;              /* 0x003F6130 */
extern R2Actor *afc_helper;           /* 0x003F611C */
extern R2Actor *r2_player;            /* 0x00420E98 */
extern uint8_t  ae0_obj3E1270[];      /* 0x003E1270 */
extern uint8_t  r2_list3F5DC0[];      /* 0x003F5DC0 */
extern R2Node  *r2_head3F60E0;        /* 0x003F60E0 */
extern R2Node  *r2_tail3F60E4;        /* 0x003F60E4 */

/* External callees (stack arguments unless noted) */
void    sub_000F3D10(void *a, void *b, int c);
void    sub_00048250(int id);
void    sub_00019000(void *a, int b);
int     sub_000E3380(void);
void    sub_0003D8C0(void *node);
void    sub_0003D860(void *node);
int     sub_000ED0C0(int a, int b);
int     sub_000ECC50(int i, int b);
void    sub_000ED1B0(int i, int b, int c);

/* r2_1 */
void r2_PartCall3D10(int a);                                  /* 0x000FC6F0 a=EAX */
void r2_ActorCallComp5(R2Actor *obj, int arg);                /* 0x000EEF90 obj=ESI */
void r2_LookupApply(int a, int b, int arg);                   /* 0x000E3030 a=ECX b=EAX */
void r2_LookupApplyN(int a, int b, int n, int arg);           /* 0x000E3000 a=ECX b=EAX n=EDX */
void r2_Comp5FreeD4(R2Actor *obj);                            /* 0x000EF8A0 obj=EAX */
void r2_Comp5ReleaseD8(R2Actor *obj);                         /* 0x000EF8D0 obj=EAX */
void r2_CheckStateE3380(R2Actor *obj);                        /* 0x000EF900 obj=EAX */
void r2_ListDrop(void *key);                                   /* 0x000ED380 key=EAX */
void *r2_SelectKind(int kind);                                /* 0x0011B140 kind=EAX */
void   *sub_000C7130(void *a);
float   sub_001B2770(const float *a, const float *b);         /* distance between two points */
extern float a50_frameUnits;          /* 0x0042C858 */

/* r2_2 */
R2Actor *r2_NearTarget(R2Actor *obj);                         /* 0x000FB6C0 obj=EDI */
void r2_PartCallRes(R2Actor *obj, int arg);                   /* 0x00100030 obj=ECX */
void r2_SetPairAnim(R2Actor *a, R2Actor *b, int anim);        /* 0x001000C0 a=ECX b=EAX */
void r2_TurnAndNotify(R2Actor *obj, void *arg);               /* 0x00100FF0 */
void r2_EffectAtPart(void *a, int c, int id);                 /* 0x00107310 a=ECX c=EAX */
void r2_SetComp5Mode(R2Actor *obj, int mode);                 /* 0x00108B80 obj=ESI mode=EDI */
void r2_SetComp5ModeB(R2Actor *obj, int mode);                /* 0x0010CB30 obj=ESI mode=EDI */
void r2_Comp5StartE4(R2Actor *obj, int id);                   /* 0x0010D2B0 obj=EAX */
void r2_Comp5ReleaseE4(R2Actor *obj);                         /* 0x0010D2F0 obj=EAX */
void    sub_001ADC60(float *dst, const float *a, const float *b, float t);
void    sub_0011F640(int idx, float *dst);                     /* idx=EAX dst=ESI */
void   *sub_000EDC20(int a, int b);   /* object iterator */
void    sub_00025C10(int a, int b);
void    sub_00119FF0(void *a, void *b, int c);
void    sub_00113AA0(void *a, void *b);
void    sub_00033560(void *h);
typedef int (*R2TblFn)(int a, int b, void *c);
extern R2TblFn   r2_fn31B0C4[];       /* 0x0031B0C4 */
extern float     r2_vec279598[][4];   /* 0x00279598 */
extern R2Step   *r2_steps31A380[];    /* 0x0031A380 */
extern R2StepFn  r2_stepFn31A394[];   /* 0x0031A394 */
extern R2Step   *r2_steps31C110[];    /* 0x0031C110 */
extern R2StepFn  r2_stepFn31C174[];   /* 0x0031C174 */
extern R2Step   *r2_steps31C510[];    /* 0x0031C510 */
extern R2StepFn  r2_stepFn31C524[];   /* 0x0031C524 */
extern R2PtRec   r2_pts31C538[];      /* 0x0031C538 */
extern float     r2_pts31C618[][8];   /* 0x0031C618 */

/* r2_3 */
void r2_LerpMat(const float *a, const float *b, float *dst, float t);    /* 0x00112CD0 a=EAX b=ECX dst=EDX */
int  r2_RunSteps31A380(int idx, void *a, void *b);            /* 0x00114D10 idx=EAX a=EBX b=EDI */
void *r2_PickTarget(const R2Cond *c, R2Ctx *ctx, void *self); /* 0x00114D60 c=EAX ctx=ECX; self=stack */
void r2_UpdateFreeSlots(R2Body *obj);                         /* 0x00115440 obj=EAX */
int  r2_CallTbl31B0C4(int a, int b, int arg);                 /* 0x0011B020 a=EAX b=EDX */
int  r2_GetHitKind(R2Body *obj, int *out);                    /* 0x0011B0D0 obj=ECX out=EDX */
void r2_RecNotify(R2Rec *p, void *b, int c);                  /* 0x0011B110 p=ESI b=EBX c=EDI */
int  r2_RecHit(R2Rec *p, int arg);                            /* 0x0011B170 p=ESI */
void r2_BodyReattach(R2Body *obj, void *b);                   /* 0x0011B1C0 obj=EAX b=EDI */
int  r2_RunSteps31C110(int idx, void *a, void *b);            /* 0x0011EDE0 idx=EAX a=EBX b=EDI */
void *r2_PickTargetB(const R2Cond *c, R2Ctx *ctx, void *self);/* 0x0011EE30 c=EAX ctx=ECX */
void r2_BodyResetMat(R2Body *obj, int kind, float f);         /* 0x0011FA60 obj=EAX kind=EBX */
int  r2_AnyFlag2000(int kind, void *self);                    /* 0x0011FAC0 kind=EAX self=EDI */
int  r2_AnyFlagMask(int kind, void *self, uint32_t mask);     /* 0x0011FB40 kind=EAX self=EDI mask=ESI */
int  r2_RunSteps31C510(int idx, void *a, void *b);            /* 0x0012DC90 idx=EAX a=EBX b=EDI */
void r2_GetPoint(R2Body *obj, int idx, int key, float *dst);  /* 0x0012E330 obj=ECX idx=EAX key=ESI dst=EDI */
int  r2_CountKinds0E(void);                                   /* 0x0012E540 */
float   sub_001A3F30(float v);                                 /* absolute value */
float   sub_000F7720(void *a, const void *b);
extern float afc_vec318E18[];         /* 0x00318E18 */
extern float a50_frameSeconds;        /* 0x0042C85C */
/* Block of mode words at 0x003EDB60 (reset by 0x0D7040 / 0x0D7440 / 0x0D7480). */
typedef struct R2Modes {
    int32_t i00, i04;          /* 0x3EDB60 */
    int32_t unk08;
    int32_t i0C;               /* 0x3EDB6C */
    int32_t unk10;
    float   f14;               /* 0x3EDB74 */
    int32_t unk18[5];
    int32_t i2C[5];            /* 0x3EDB8C..0x3EDB9C */
    int32_t i40, i44;          /* 0x3EDBA0 */
    int32_t i48[6];            /* 0x3EDBA8..0x3EDBBC */
    int32_t unk60[11];
    int32_t i8C, i90, i94;     /* 0x3EDBEC */
    float   f98;               /* 0x3EDBF8 */
} R2Modes;
extern R2Modes r2_modes3EDB60;        /* 0x003EDB60 */
/* Block at 0x003EDC00 (reset by 0x0D8F80). */
typedef struct R2Blk3EDC00 {
    float   v00[3];
    float   f0C;
    int32_t i10, i14, i18, i1C, i20, i24, i28, i2C, i30;
} R2Blk3EDC00;
extern R2Blk3EDC00 r2_blk3EDC00;      /* 0x003EDC00 */
/* Actor fields used by 0x0010F0D0 / 0x000EFCF0 / 0x000FCA00. */
typedef struct R2Mover {
    uint8_t unk000[0x70];
    float   scale70[3];        /* +0x070 */
    uint8_t unk07C[0xA4 - 0x7C];
    float   fA4;               /* +0x0A4 */
    uint8_t unk0A8[0xB0 - 0xA8];
    float   fB0, fB4;          /* +0x0B0 */
    uint8_t unk0B8[0xF0 - 0xB8];
    float   velF0[4];          /* +0x0F0 */
} R2Mover;
typedef struct R2Helper {
    uint8_t  unk000[0x8C];
    R2Actor *link8C;           /* +0x08C */
    uint8_t  unk090[0xF4 - 0x90];
    float    fF4;              /* +0x0F4 */
    uint8_t  unk0F8[0x100 - 0xF8];
    int32_t  i100;             /* +0x100 */
} R2Helper;
typedef struct R2Comp13 { uint8_t unk00[0x18]; float f18; } R2Comp13;

/* r2_4 */
int  r2_TargetInRange(void *self, R2Ctx *ctx, const R2Cond *c);       /* 0x00114DC0 */
int  r2_TargetInRangeB(void *self, R2Ctx *ctx, const R2Cond *c);      /* 0x0011EE90 */
int  r2_TargetHeightInRange(R2Body *self, R2Ctx *ctx, const R2Cond *c);/* 0x0011EEF0 */
int  r2_AnyFlag2000Kinds(void *self);                         /* 0x0011FB10 self=EAX */
int  r2_AnyFlagKinds(uint32_t mask, void *self);              /* 0x0011FB90 mask=EAX self=ECX */
void r2_UpdateFreeSlotsB(R2Body *obj);                        /* 0x0012E590 obj=EAX */
void r2_ClearVel(R2Mover *obj);                               /* 0x000EFCF0 obj=EAX */
void r2_SetScale(R2Mover *obj, float s);                      /* 0x0010F0D0 obj=ESI */
void r2_ResetBlk3EDC00(void);                                 /* 0x000D8F80 */
void r2_HelperFace(void *a);                                  /* 0x000FCA00 */
void r2_ResetModesA(void);                                    /* 0x000D7040 */
void r2_ResetModesB(void);                                    /* 0x000D7440 */
void r2_ResetModesC(int v);                                   /* 0x000D7480 */
int     aab_Rand(void);                                        /* 0x001C7EE1 (CRT rand) */
void    b10_AddClampF(float *v, float d, float max);
void    b10_SubClampF(float *v, float d, float min);
void    a5b_SndRelease(void);
void    af0_SetVar3EDD1C(int v);
int     a80_Get3ED238(void);
void    sub_001AD9F0(float *dst, const float *a, const float *b);
void    sub_001B2150(void *p);
void    sub_00101280(int a);
int     sub_00053F60(void);
int     sub_0017F000(int i);
int     sub_000F3CB0(void *p);
float   sub_000F3C70(void *p);
void    sub_0011F620(void);
extern float a50_framesPerSecond;     /* 0x0042C964 */
extern R2Actor *g_acb_bossMgr;        /* 0x003F610C */
extern float r2_chance31A094[][2];    /* 0x0031A094 */

/* Nearest-point table read by 0x000D9100. */
typedef struct R2PtTable { int32_t count; int32_t id04[255]; float pt400[1][4]; } R2PtTable;
/* Hook record at +0xA0 of a state block (0x0012D350). */
typedef struct R2Hook {
    uint8_t  unk00[4];
    void   (*fn04)(void);      /* +0x04 */
    uint8_t  unk08[8];
    void    *a10, *b14;        /* +0x10 */
    float    m18[16], m58[16], m98[16];
    uint8_t  unkD8[4];
    float    fDC, fE0;         /* +0xDC */
} R2Hook;
typedef struct R2Owner { uint8_t unk00[0xC4]; uint8_t *listC4; } R2Owner;
typedef struct R2HookHost { uint8_t unk00[0x20]; R2Owner *owner20; } R2HookHost;
typedef struct R2HookBody { uint8_t unk000[0x278]; uint8_t *st278; } R2HookBody;
/* Kind-5 component fields used by 0x000EF810 / 0x0010CAA0. */
typedef struct R2Comp5B {
    uint8_t unk000[0x10C];
    int32_t pick10C;           /* +0x10C */
    uint8_t unk110[0x14C - 0x110];
    int32_t kind14C;           /* +0x14C */
    int32_t row150;            /* +0x150 */
    uint8_t unk154[4];
    int32_t col158;            /* +0x158 */
} R2Comp5B;
typedef struct R2Spin { uint8_t unk000[0xC8]; float fC8; uint8_t unk0CC[4]; float fD0; } R2Spin;
typedef struct R2Boss { uint8_t unk000[0x8C]; void *link8C; uint8_t unk090[0x120 - 0x90]; float f120; } R2Boss;
typedef struct R2Scr { uint8_t unk000[0x1A8]; uint16_t w1A8; } R2Scr;

/* r2_5 */
int  r2_NearestPoint(const R2PtTable *t, const float *pos);   /* 0x000D9100 t=EBX */
typedef struct R2Msg { uint32_t unk00; uint8_t *data04; } R2Msg;
typedef struct R2MotionSt { uint8_t unk00[0x30]; float v30[4]; float v40[4]; float f50, f54, f58, f5C, f60, f64; } R2MotionSt;
int  r2_MsgCheckRange(R2Msg *msg);                            /* 0x000DDC60 */
int  r2_PickRandomSlot(R2Actor *obj);                         /* 0x000EF810 obj=EAX */
void r2_SetBallistic(R2Mover *obj, float t, float h, float d);/* 0x000EFD50 obj=EAX */
void r2_BossClampSpeed(void);                                 /* 0x000F4510 */
void r2_ScrPickDir(void *a);                                  /* 0x00102FC0 */
void r2_RandomSpin(R2Spin *o);                                /* 0x00109460 */
int  r2_RollAttack(R2Actor *obj);                             /* 0x0010CAA0 obj=EAX */
void r2_BodyAdjust14(R2Body *obj);                            /* 0x0011A300 obj=EAX */
void r2_BodySetMotion(R2Body *obj, float a, float b, float c, float d); /* 0x0011F480 obj=EAX */
int  r2_PlayerOutOfReach(R2Body *obj, R2Body *self);          /* 0x00120820 obj=EAX self=ESI */
void r2_HookInit(R2HookHost *a, R2HookBody *b);               /* 0x0012D350 a=EBX b=EDI */
float   afc_VecLengthXZ(const float *v);
float   r4_Distance(const float *a, const float *b);
void    sub_00014E80(void *p);
void    sub_000150B0(void *p, int n);
float   sub_00113200(void *o, const float *target);
float   sub_00113290(void *o, const float *pt);
void    sub_001AD7E0(float *dst, const float *src);
void    sub_0001D610(void *obj);
extern int   g_acb_3F0A7C;            /* 0x003F0A7C */
extern int   aec_3F49D0;              /* 0x003F49D0 */
extern int   aec_3F49D4;              /* 0x003F49D4 */
extern int   r2_g3F49DC;              /* 0x003F49DC */
extern float r2_fade3F49E0[2];        /* 0x003F49E0 */
extern float r2_fade3F4A7C[2];        /* 0x003F4A7C */
extern int32_t r2_anim317758[][17][2];/* 0x00317758 */
extern float r2_center3194C8[];       /* 0x003194C8 */
extern R2Actor *afc_minion;           /* 0x003F6120 */

/* Effect slot table at 0x003F4D10 (16 slots of 0xA0 bytes). */
typedef struct R2Slot {
    uint32_t flags;            /* +0x00 bit 0: in use */
    uint8_t  obj04[0x14];      /* +0x04 */
    float    f18;              /* +0x18 random angle 0..359 */
    uint8_t  unk1C[4];
    float    f20, f24;         /* +0x20 */
    uint8_t  unk28[0xA0 - 0x28];
} R2Slot;
extern R2Slot r2_slots3F4D10[16];     /* 0x003F4D10 */
typedef struct R2Boss2 {
    uint8_t unk000[0x8C];
    void   *link8C;            /* +0x08C */
    uint8_t unk090[0x100 - 0x90];
    int32_t i100;              /* +0x100 */
    int32_t i104;              /* +0x104 */
    int32_t dir108;            /* +0x108 */
} R2Boss2;
typedef struct R2Seq { int32_t row; uint8_t unk04[0x510 - 4]; int32_t on510; int32_t step514; } R2Seq;
typedef struct R2Minion { uint8_t unk000[0x94]; void *obj94; uint8_t unk098[4]; int32_t i9C; } R2Minion;
typedef struct R2Arg68 { uint8_t unk00[0x68]; float f68; } R2Arg68;
typedef struct R2Scr2 { uint8_t unk000[0x1A8]; uint16_t w1A8; uint8_t unk1AA[2]; float f1AC; uint8_t unk1B0[0x1CC - 0x1B0]; int32_t i1CC; } R2Scr2;

/* r2_6 */
void r2_BossPickDir(void);                                    /* 0x000F43E0 */
int  r2_SlotAlloc(float a, float b);                              /* 0x000E8D00 */
void r2_SeqStep(R2Seq *q);                                    /* 0x000E48C0 q=ESI */
void r2_MinionTurn(R2Actor *obj, R2Arg68 *arg);               /* 0x000FE9E0 */
void r2_ClampToCenter(R2Actor *obj);                          /* 0x00102E80 obj=EAX */
void *r2_ApplyFades(void *v);                                  /* 0x000E8080 v=EAX */
int  r2_InAttackCone(R2Actor *self, R2Body *other, const float *rec); /* 0x0011B040 */
int  r2_PointInView(R2Body *self, const float *pt, float *dist, float *ang); /* 0x00113F10 self=EDI pt=ESI */
void r2_ScrPickDirB(void *a);                                 /* 0x00103640 */
extern R2Actor *afc_body;             /* 0x003F6114 */
typedef struct R2Scr3 {
    uint8_t  unk000[0x8C];
    R2Actor *link8C;           /* +0x08C */
    uint8_t  unk090[0x1AC - 0x90];
    float    f1AC;             /* +0x1AC */
    uint8_t  unk1B0[0x1C0 - 0x1B0];
    int32_t  i1C0;             /* +0x1C0 */
    uint8_t  unk1C4[0x240 - 0x1C4];
    int32_t  order240[18];     /* +0x240 */
    int32_t  pick288[4];       /* +0x288 */
    int32_t  i298;             /* +0x298 */
} R2Scr3;
typedef struct R2Mover2 {
    uint8_t unk000[0x70];
    float   scale70[3];        /* +0x070 */
    uint8_t unk07C[0xA4 - 0x7C];
    float   fA4;               /* +0x0A4 */
    uint8_t unk0A8[0xB0 - 0xA8];
    float   fB0, fB4;          /* +0x0B0 */
    uint8_t unk0B8[0xDC - 0xB8];
    float   fDC;               /* +0x0DC */
    uint8_t unk0E0[0xE8 - 0xE0];
    float   fE8;               /* +0x0E8 */
    uint8_t unk0EC[0xFC - 0xEC];
    float   fFC;               /* +0x0FC */
} R2Mover2;
typedef struct R2Comp13B { uint8_t unk00[0x18]; float f18, f1C; } R2Comp13B;

/* r2_7 */
void r2_ScrApproach(void);                                    /* 0x00103200 */
void r2_BodyTurn(R2Actor *obj, R2Arg68 *arg);                 /* 0x000FBEF0 */
void r2_CtlTurn(R2Actor *obj, R2Arg68 *arg);                  /* 0x00100640 */
void r2_SetScaleB(R2Mover2 *obj, float s);                    /* 0x0010D320 obj=ESI */
int     sub_000CF560(void *p, int a);
float   sub_001A3EE0(float x);                                 /* cosine of degrees (Hypothesis) */
void    sub_001ADBA0(float *d, const float *s, float k);
int     sub_00199E70(int id);
void   *sub_000FC4D0(void);
/* Actor with three effect ids at +0x134 (0x000F7100). */
typedef struct R2EffHolder { uint8_t unk000[0x134]; int32_t eff134[3]; } R2EffHolder;
/* Part with a flag word at +0x10. */
typedef struct R2FlagPart { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } R2FlagPart;
typedef struct R2Trio {
    uint8_t     unk000[0x8C];
    R2FlagPart *link8C;        /* +0x08C */
    uint8_t     unk090[0xA4 - 0x90];
    uint16_t    wA4;           /* +0x0A4 */
    uint8_t     unk0A6[0xBC - 0xA6];
    uint16_t    wBC;           /* +0x0BC */
} R2Trio;
typedef struct R2TrioHelper { uint8_t unk000[0xB4]; R2FlagPart *partB4[3]; } R2TrioHelper;
typedef struct R2PlayerRot { uint8_t unk00[0x20]; float row20[4]; } R2PlayerRot;
typedef struct R2PlayerX { uint8_t unk00[0x20]; R2PlayerRot *rot20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } R2PlayerX;

/* r2_8 */
void r2_TrioReleaseEffects(void);                             /* 0x000F7100 */
void r2_TrioReset(void);                                      /* 0x000F8B40 */
int  r2_PlayerInFrontA(R2Body *obj, R2Actor *self);           /* 0x001154D0 obj=EAX */
int  r2_PlayerInFrontB(R2Body *obj, R2Actor *self);           /* 0x0012E630 obj=EAX */
#endif
