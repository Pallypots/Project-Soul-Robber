#ifndef R2C_H
#define R2C_H
#include "oogie.h"
#include "shared_decls.h"
#include <string.h>

/* Zero a block (the original inlines this as rep stos). The intrinsic is
 * used only for the 32-bit x86 comparison build; other targets use memset. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define R2C_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) / 4)
#else
#define R2C_ZERO(p, n) memset((p), 0, (n))
#endif
#if 0 /* PORT: this block was hidden by a misplaced #endif and never compiled on any target;
         enabling it gives redefinition errors against declarations later in this header. */
/* ---------------------------------------------------------------- r2c_3 */
typedef struct R2cAnimTarget { uint8_t unk00[0xB8]; uint32_t flagsB8; } R2cAnimTarget;
typedef struct R2cPart { uint8_t unk00[8]; int32_t i08; uint8_t unk0C[8]; R2cAnimTarget *t14; } R2cPart;
/* Model node: +0x30 animation part, +0x3C next sibling, +0xD0 handle. */
typedef struct R2cModel {
    uint8_t  unk00[0x0C];
    uint32_t flags0C;          /* +0x0C bit 0: active */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    R2cPart *part30;           /* +0x30 */
    uint8_t  unk34[0x3C - 0x34];
    struct R2cModel *next3C;   /* +0x3C */
    uint8_t  unk40[0xD0 - 0x40];
    int32_t  vD0;              /* +0xD0 */
    uint8_t  unkD4[0x14C - 0xD4];
    int32_t  v14C;             /* +0x14C */
} R2cModel;
/* Global boss manager (0x130 bytes) at 0x003F610C. */
typedef struct R2cBossMgr {
    uint8_t  unk000[0x6C];
    int32_t  v6C;              /* +0x06C */
    uint8_t  unk070[0x8C - 0x70];
    R2cModel *sub8C;           /* +0x08C */
    R2cModel *sub90;           /* +0x090 */
    void    *h94;              /* +0x094 handle */
    uint8_t  unk098[0xA6 - 0x98];
    int16_t  wA6;              /* +0x0A6 */
    int16_t  wA8;              /* +0x0A8 */
    uint8_t  unk0AA[0xB8 - 0xAA];
    int32_t  vB8;              /* +0x0B8 */
    int32_t  vBC;              /* +0x0BC */
    uint8_t  unk0C0[0x110 - 0xC0];
    int32_t  v110;             /* +0x110 */
    uint8_t  unk114[0x120 - 0x114];
    int32_t  v120;             /* +0x120 */
    int32_t  h124;             /* +0x124 */
    int32_t  h128;             /* +0x128 */
    int32_t  h12C;             /* +0x12C */
} R2cBossMgr;
extern R2cBossMgr *g_acb_bossMgr;      /* 0x003F610C */
extern R2cBossMgr *g_acb_bossAux;      /* 0x003F6110 */
/* Stage game state returned by 0x000E0770. */
typedef struct R2cGame {
    int32_t  v000;             /* +0x000 */
    uint8_t  unk004[0x308 - 4];
    int32_t  v308;             /* +0x308 */
    int32_t  v30C;             /* +0x30C */
    uint8_t  unk310[4];
    int32_t  v314;             /* +0x314 */
} R2cGame;
typedef struct R2cKind {
    uint8_t  unk00[8];
    int32_t  kind08;           /* +0x08 3..5 select the boss form */
    uint8_t  unk0C[0x30 - 0xC];
    R2cPart *p30;              /* +0x30 */
    uint8_t  unk34[0x50 - 0x34];
    uint32_t v50[4];           /* +0x50 */
    uint32_t v60[4];           /* +0x60 */
} R2cKind;
typedef struct R2cMover {
    uint8_t  unk000[0xF8];
    uint32_t vF8[4];           /* +0x0F8 */
    uint32_t v108[4];          /* +0x108 */
    int32_t  v118;             /* +0x118 */
} R2cMover;
/* Boss object reset by 0x0F69E0 (0x208 bytes). */
typedef struct R2cBoss {
    uint8_t  unk000[0x8C];
    R2cModel *sub8C;           /* +0x08C */
    R2cModel *sub90;           /* +0x090 */
    int32_t  v94, v98;         /* +0x094 */
    uint8_t  unk09C[0xC8 - 0x9C];
    int32_t  vC8, vCC, vD0, vD4, vD8, vDC; /* +0x0C8 */
    uint8_t  unk0E0[0x12C - 0xE0];
    int32_t  v12C;             /* +0x12C */
    uint8_t  unk130[4];
    int32_t  h134, h138, h13C, h140; /* +0x134 */
    uint8_t  unk144[0x1A8 - 0x144];
    int32_t  v1A8;             /* +0x1A8 */
    uint8_t  unk1AC[0x1C0 - 0x1AC];
    int32_t  v1C0, v1C4;       /* +0x1C0 */
    uint8_t  unk1C8[0x206 - 0x1C8];
    int16_t  w206;             /* +0x206 */
} R2cBoss;
R2cModel *sub_0001D2B0(R2cModel *m, int idx);
void      sub_00192380(int side, int anim);
void      sub_000E0A80(R2cGame *g, int a, int b, int c, int d);
void      sub_000E51F0(R2cGame *g);
int       sub_000F30E0(int kind);
void      sub_000C75E0(R2cModel *m);
int       sub_0001BC40(R2cModel *m);

void r2c_BossSetAnim(int anim);                       /* 0x000F4370 anim=ESI */
void r2c_BossDefeat(void);                            /* 0x000F4610 */
void r2c_BossMgrCreate(void);                         /* 0x000F4D90 */
void r2c_Vec4Copy(uint32_t *dst, const uint32_t *src);  /* 0x000F5D40 */
int  r2c_CountA6(const R2cKind *k);                   /* 0x000F5FB0 */
int  r2c_CountState6C(const R2cKind *k);              /* 0x000F6030 */
void r2c_BossInit(R2cBoss *b);                        /* 0x000F69E0 */
void r2c_BossModelReset(R2cBoss *b);                  /* 0x000F6AA0 */

/* ---------------------------------------------------------------- r2c_4 */
/* Boss body object (afc_body 0x003F6114 and the per-form objects). */
typedef struct R2cBossObj {
    uint8_t  unk000[0x10];
    uint8_t  comp10[0x6C - 0x10]; /* +0x010 component block */
    int32_t  v6C;              /* +0x06C state */
    uint8_t  unk070[0x8C - 0x70];
    R2cModel *sub8C;           /* +0x08C */
    R2cModel *sub90;           /* +0x090 */
    int32_t  v94;              /* +0x094 */
    uint8_t  unk098[4];
    int32_t  v9C;              /* +0x09C step */
    uint8_t  unk0A0[4];
    int16_t  wA4, wA6, wA8, wAA, wAC, wAE, wB0, wB2; /* +0x0A4 */
    uint8_t  unk0B4[0xBC - 0xB4];
    int16_t  wBC;              /* +0x0BC */
    uint8_t  unk0BE[0xE4 - 0xBE];
    int32_t  vE4;              /* +0x0E4 */
    int32_t  vE8;              /* +0x0E8 */
    int16_t  wEC;              /* +0x0EC */
    uint8_t  unk0EE[0x134 - 0xEE];
    int32_t  h134;             /* +0x134 */
    int32_t  h138;             /* +0x138 */
    int32_t  h13C;             /* +0x13C */
    uint8_t  unk140[0x1D0 - 0x140];
    int16_t  w1D0;             /* +0x1D0 */
    uint8_t  unk1D2[0x1EC - 0x1D2];
    float    pos1EC[4];        /* +0x1EC */
} R2cBossObj;
/* Helper object (0x104 bytes) at afc_helper 0x003F611C. */
typedef struct R2cHelper {
    uint8_t  unk000[0x8C];
    R2cModel *sub8C;           /* +0x08C */
    void    *sub90;            /* +0x090 */
    int32_t  v94;              /* +0x094 */
    uint8_t  unk098[0xB4 - 0x98];
    int32_t  vB4, vB8, vBC;    /* +0x0B4 */
    uint8_t  unk0C0[0x104 - 0xC0];
} R2cHelper;
extern R2cBossObj *afc_body;           /* 0x003F6114 */
extern R2cBossObj *afc_bodyState;      /* 0x003F6118 */
extern R2cHelper  *afc_helper;         /* 0x003F611C */
extern float a50_framesPerSecond;      /* 0x0042C964 */
extern void *aec_ctx42C8E4;            /* 0x0042C8E4 */
R2cBossObj *sub_000F5F80(const R2cKind *k);
void  sub_000F62F0(R2cBossObj *e, int step);
void  sub_000F62C0(R2cBossObj *e, int step);
void  sub_000FB580(const R2cKind *k, int a);
R2cBossObj *sub_000FC4D0(void);
void  sub_000FBA00(int a);
void  sub_000F3AA0(R2cBossObj *b);
void  sub_0001D8B0(void *comp, int kind);
void  sub_0001D8D0(R2cModel *m, void *comp);
void  sub_0001E9B0(void *ctx, R2cModel *m, int a, int b, int c);
void  sub_0001EBF0(R2cModel *m, int a);
void  sub_000EE270(void *comp);
void  sub_000FBD50(void);
void  sub_000E3BA0(R2cGame *g);
void  sub_00033B30(R2cModel *m);
void  sub_0001D910(R2cModel *m, void *comp);
void  sub_000FE2E0(int a);
void  sub_00100020(int a);
R2cKind *sub_000FC4B0(void);
void  sub_000FE330(int a);
void  sub_00100070(int a);
void  sub_000FBA50(int a);

void  r2c_BossAnimIfActive(int anim);                 /* 0x000F4E10 */
float r2c_BossStepSpeed(const R2cKind *k);            /* 0x000F7AE0 */
float r2c_DistTo(void *a, R2cKind *b, float c);       /* 0x000F7C40 */
void  r2c_SnapToHelper(R2cKind *k);                   /* 0x000F9430 */
void  r2c_FormCue20(const R2cKind *k);                /* 0x000F9A10 */
void  r2c_StepA(const R2cKind *k);                    /* 0x000FA740 */
void  r2c_StepB(const R2cKind *k);                    /* 0x000FB3E0 */
void  r2c_StepC(const R2cKind *k);                    /* 0x000FB440 */
void  r2c_StepD(const R2cKind *k);                    /* 0x000FB710 */
void  r2c_BodyAnim(int anim);                         /* 0x000FBA90 */
void  r2c_BodyCheckRecover(void);                     /* 0x000FBCA0 */
void  r2c_BodyAnim21(void);                           /* 0x000FBEA0 */
void  r2c_BodyAnim24(void);                           /* 0x000FC310 */
R2cModel *r2c_BodyAttach(R2cModel *m);                /* 0x000FC410 */
int   r2c_HelperDetach(R2cModel *m);                  /* 0x000FC4E0 */
void  r2c_HelperStop(void);                           /* 0x000FD1C0 */
void  r2c_HelperCreate(void);                         /* 0x000FD3C0 */

/* ---------------------------------------------------------------- r2c_5 */
extern R2cBossObj *afc_minion;         /* 0x003F6120 */
extern R2cBossObj *afc_minionState;    /* 0x003F6124 */
extern R2cBossObj *b10_ctl;            /* 0x003F6128 */
extern R2cBossObj *b10_res3F612C;      /* 0x003F612C */
void  sub_000FE040(void);
void  sub_000FE660(void);
void  sub_001003A0(void);
void  sub_00184530(void);

R2cModel *r2c_HelperAttach(R2cModel *m);              /* 0x000FE1F0 */
void  r2c_MinionAnim(int anim);                       /* 0x000FE370 */
void  r2c_MinionCheckRecover(void);                   /* 0x000FE5A0 */
void  r2c_MinionAnim2(void);                          /* 0x000FE890 */
void  r2c_MinionAnim2D(void);                         /* 0x000FFE50 */
R2cModel *r2c_MinionAttach(R2cModel *m);              /* 0x000FFF30 */
void  r2c_CtlAnim(int anim);                          /* 0x001000B0 */
void  r2c_CtlCheckRecover(void);                      /* 0x001002E0 */
void  r2c_CtlAnim2(void);                             /* 0x001004F0 */
void  r2c_CtlAnim21(void);                            /* 0x001005F0 */
void  r2c_CtlAnim22(void);                            /* 0x001008A0 */
void  r2c_CtlAnim23(void);                            /* 0x00100990 */
void  r2c_CtlAnim25(void);                            /* 0x00100A70 */
void  r2c_CtlAnim0(void);                             /* 0x00100F10 */
void  r2c_CtlAnim29(void);                            /* 0x00101040 */
R2cModel *r2c_CtlAttach(R2cModel *m);                 /* 0x00101170 */

/* ---------------------------------------------------------------- r2c_6 */
/* Script boss object at b10_scr 0x003F6130: sound at +0x238, effect at +0x23C. */
typedef struct R2cScr {
    uint8_t  unk000[0x10];
    uint8_t  comp10[0x8C - 0x10]; /* +0x010 component block */
    R2cModel *sub8C;           /* +0x08C */
    uint8_t  unk090[0x238 - 0x90];
    int32_t  h238;             /* +0x238 */
    void    *h23C;             /* +0x23C handle */
} R2cScr;
/* Small object (0x90 bytes) at b10_obj3F6134. */
typedef struct R2cObj90 {
    uint8_t  unk000[0x10];
    uint8_t  comp10[0x8C - 0x10]; /* +0x010 component block */
    R2cModel *sub8C;           /* +0x08C */
} R2cObj90;
/* Owner object reached through component 5 +0x64: four children at +0x9A8. */
typedef struct R2cOwner { uint8_t unk000[0x9A8]; R2cModel *kids9A8[4]; } R2cOwner;
typedef struct R2cComp5b { uint8_t unk00[0x64]; R2cOwner *owner64; } R2cComp5b;
typedef struct R2cKeyObj { uint8_t unk00[4]; int32_t kind04; int32_t v08; } R2cKeyObj;
extern R2cScr   *b10_scr;              /* 0x003F6130 */
extern R2cObj90 *b10_obj3F6134;        /* 0x003F6134 */
extern void     *r2c_fx3F613C[5];      /* 0x003F613C effect handles */
void  sub_00101280(int a);
void  sub_00105D80(void);
void  sub_001061B0(void);
void  sub_001208A0(R2cModel *m, int a);
int   sub_000336A0(void *h);

void  r2c_ScrStop(void);                              /* 0x00104AF0 */
R2cModel *r2c_ScrAttach(R2cModel *m);                 /* 0x00105F90 */
int   r2c_ScrDetach(R2cModel *m);                     /* 0x00106020 */
void  r2c_Obj90Create(void);                          /* 0x00106170 */
R2cModel *r2c_Obj90Attach(R2cModel *m);               /* 0x001062C0 */
void  r2c_ReleaseKids(R2cKeyObj *o);                  /* 0x00106550 */
void *r2c_PushEffect(void *obj, int kind);            /* 0x00109050 */

/* ---------------------------------------------------------------- r2c_7 / r2c_8 */
/* Actor description record at +0x278: flag word at +4. */
typedef struct R2cDesc { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[4]; float vC; uint8_t unk10[4]; float v14; } R2cDesc;
/* Enemy actor fields used by the hit/target helpers. */
typedef struct R2cActor {
    uint8_t  unk000[0x20];
    uint8_t  b20;              /* +0x020 bit 0: disabled */
    uint8_t  unk021[0x30 - 0x21];
    R2cPart *p30;              /* +0x030 */
    uint8_t  unk034[0x58 - 0x34];
    int32_t  v58;              /* +0x058 */
    uint8_t  unk05C[4];
    float    v60;              /* +0x060 */
    uint8_t  unk064[4];
    float    v68;              /* +0x068 */
    uint8_t  unk06C[0xC8 - 0x6C];
    struct R2cActor *pC8;      /* +0x0C8 */
    uint8_t  unk0CC[0xF8 - 0xCC];
    int32_t  vF8;              /* +0x0F8 */
    uint8_t  unk0FC[0x104 - 0xFC];
    struct R2cKeyRec *p104;    /* +0x104 */
    uint8_t  unk108[0x278 - 0x108];
    R2cDesc *p278;             /* +0x278 */
} R2cActor;
typedef struct R2cKeyRec { uint8_t unk00[4]; int32_t kind04; int32_t v08; uint8_t flags0C; } R2cKeyRec;
/* Component with a handler table: slot +0x29C. */
typedef struct R2cHandler {
    uint8_t  unk000[0x29C];
    int    (*fn29C)(void *obj, struct R2cHandler *h, int a);  /* +0x29C */
} R2cHandler;
void  sub_0001D700(void *obj);
void  sub_000F3D10(void *obj, void *c, int a);
void  sub_000F3B70(void *obj, int a);
void  sub_000F3B30(void *obj, int a);
void  sub_0010FD50(R2cActor *o);                      /* o=EAX */
int   sub_000EE5F0(void *obj);
void  sub_00025D50(int a, int b);
void  sub_00117580(R2cActor *o, int a, void *b);      /* b=EDI */
void *r2b_PickTargetB(const R2cCmd *c, void *ctx, void *self); /* 0x0011EE30 c=EAX ctx=ECX */
void  sub_0011F2B0(void *obj, int k, void *a);        /* obj=EDI k=EBX */
int   r2_PlayerOutOfReach(void *obj, void *self);     /* 0x00120820 obj=EAX self=ESI */
int   r2_AnyFlag2000(int kind, void *self);           /* 0x0011FAC0 kind=EAX self=EDI */
int   r3b_Any135780(int kind);                        /* 0x00135780 kind=EAX */
void  sub_00137F50(void *key, int mode);   /* mode compared with 3, jump-table index */

int   r2c_DropTarget(void *obj, int flag);            /* 0x0010A750 */
void  r2c_HitFlash(R2cActor *o, R2cActor *src);       /* 0x00110050 */
int   r2c_RunHandler(void *obj, int a);               /* 0x00112AA0 */
void  r2c_DescTrigger(void *a, R2cActor *b, const R2cCmd *c); /* 0x00114A90 */
void  r2c_NotifyKind2(int p);                        /* 0x001154A0 p=ESI */
void  r2c_AnimDoneStep(R2cActor *o, void *b);         /* 0x001183E0 */
void  r2c_AnimDoneStep23(R2cActor *o, R2cActor *b);   /* 0x00119970 */
int   r2c_PartnerFree(const R2cKind *k, R2cActor *z); /* 0x0011DCF0 */
int   r2c_TargetCheckPlayer(void *self, void *ctx, const R2cCmd *c); /* 0x0011EF60 */
int   r2c_TargetCheck(void *self, void *ctx, const R2cCmd *c);       /* 0x0011EFD0 */
int   r2c_KeyMatches(void *unused, R2cActor *w, const int *mode);    /* 0x0011F010 */
void  r2c_DescStep2F(void *obj, R2cActor *z);         /* 0x0012B080 */
void  r2c_Step2F(void *obj, void *a);                 /* 0x0012BA10 */
void  r2c_AnimDoneStep1(R2cActor *o, void *a);        /* 0x0012C7C0 */
void  r2c_Step1(void *obj, void *a);                  /* 0x0012CEE0 */
int   r2c_NoFlag2000(void *self);                     /* 0x0012D2C0 */
int   r2c_Any0or14(void);                             /* 0x0012DD40 */
void  r2c_NotifyKind2B(int mode);                     /* 0x0012E5E0 mode=ESI */

#endif
/* Area r2c: more functions in 0x000D0000..0x00130000 (stack and register
   arguments). All names inferred. Register mappings are in the comments and in
   config/function_states_r2c.csv. */

/* Intrusive doubly linked list (0x0003D880 family, same layout as A4cList). */
typedef struct R2cNode {
    struct R2cNode *next;      /* +0x00 */
    struct R2cNode *prev;      /* +0x04 */
    void           *owner;     /* +0x08 */
    void           *data;      /* +0x0C */
} R2cNode;
typedef struct R2cList {
    int32_t  count;            /* +0x00 */
    R2cNode *head;             /* +0x04 */
    R2cNode *tail;             /* +0x08 */
    int32_t  unk0C;
} R2cList;
/* Key record carried by list nodes: kind at +4, sub-id at +8. */
typedef struct R2cKey { uint8_t unk00[4]; int32_t kind; int32_t sub; } R2cKey;

void  a4c_ListAppend(R2cList *list, R2cNode *node);   /* 0x0003D880 */
R2cNode *sub_0003D960(R2cList *list, int index);      /* 0x0003D960 */

/* ---------------------------------------------------------------- r2c_1 */
/* Effect record table at 0x003F1B5C (0x144 bytes each). */
typedef struct R2cFx {
    uint8_t  flags;            /* +0x00 bit 0: in use */
    uint8_t  unk01[3];
    int32_t  state04;          /* +0x04 */
    int32_t  mode08;           /* +0x08 */
    int32_t  t0C;              /* +0x0C */
    uint8_t  unk10[0x24 - 0x10];
    int32_t  v24;              /* +0x24 */
    uint8_t  unk28[4];
    float    a2C;              /* +0x2C */
    float    a30;              /* +0x30 */
    uint8_t  unk34[0xC4 - 0x34];
    int32_t  vC4;              /* +0x0C4 */
    uint8_t  unkC8[0x144 - 0xC8];
} R2cFx;
extern R2cFx r2c_fx3F1B5C[32];         /* 0x003F1B5C */
/* Effect slot table at 0x003F4D10 (16 slots of 0xA0 bytes). */
typedef struct R2cSlot { uint32_t flags; uint8_t unk04[0xA0 - 4]; } R2cSlot;
extern R2cSlot r2_slots3F4D10[16];     /* 0x003F4D10 */
/* Four fader blocks: state and three counters at the start of each. */
typedef struct R2cFader { int32_t state, t04, t08, t0C, t10; uint8_t unk14[8]; int32_t v1C; } R2cFader;
extern R2cFader r2c_fadeA3F43E0;       /* 0x003F43E0 */
extern R2cFader r2c_fadeB3F47B8;       /* 0x003F47B8 */
extern R2cFader r2c_fadeC3F4874;       /* 0x003F4874 */
extern R2cFader r2c_fadeD3F4B1C;       /* 0x003F4B1C */
extern int   aec_3F49D0;               /* 0x003F49D0 */
extern int   aec_3F49D4;               /* 0x003F49D4 */
extern int   r2_g3F49DC;               /* 0x003F49DC */
extern int   g_acb_3F57BC;             /* 0x003F57BC */
typedef struct R2cClock { uint8_t unk00[0x18]; volatile uint32_t ticks18; } R2cClock;
extern R2cClock *r2c_clock3F4AB8;      /* 0x003F4AB8 */

/* Object with a counter pair at +0x40C/+0x410 (Hypothesis: a boss gauge). */
typedef struct R2cGauge {
    uint8_t  unk000[0x408];
    int32_t  on408;            /* +0x408 */
    int32_t  cur40C;           /* +0x40C */
    int32_t  max410;           /* +0x410 */
} R2cGauge;
/* Holder of 32 part handles at +0x3B0. */
typedef struct R2cHolder { uint8_t unk000[0x3B0]; int32_t parts3B0[32]; } R2cHolder;
/* Script command: index at +0x0C, arguments after it. */
typedef struct R2cCmd {
    uint8_t  unk00[0x0C];
    int32_t  vC;               /* +0x0C */
    union { int32_t v10; float f10; };  /* +0x10 (int or float by command) */
    union { int32_t v14; float f14; };  /* +0x14 */
    union { int32_t v18; float f18; };  /* +0x18 */
    int32_t  v1C;              /* +0x1C */
} R2cCmd;

extern R2cList aec_3F5DB0;             /* 0x003F5DB0 */
extern R2cList r2_list3F5DC0;          /* 0x003F5DC0 */
typedef int (*R2cKeyFilter)(int kind, int sub);
extern R2cKeyFilter r2c_filter3189CC;      /* 0x003189CC */
extern int   r2c_iter3189D0;           /* 0x003189D0 */
extern int   r2c_kind3189D4;           /* 0x003189D4 */
extern int   r2c_sub3189D8;            /* 0x003189D8 */
extern R2cNode *r2_tail3F60E4;         /* 0x003F60E4 */

int  sub_000E3380(void);
void sub_000E63A0(int a);
void sub_000E8920(int a, int b);
int  r2_SlotAlloc(float a, float b);                      /* 0x000E8D00 */
int  sub_000E3F20(int a, int b, int c);

void r2c_GaugeFullCheck(R2cGauge *g);                 /* 0x000E9C60 */
int  r2c_FxStart(unsigned idx, unsigned mode);        /* 0x000E98E0 */
void r2c_WaitTicks(int on, unsigned n);               /* 0x000E9950 */
void r2c_FaderC(int on, int v);                       /* 0x000E89F0 */
void r2c_FxResetAll(void);                            /* 0x000E8530 */
void r2c_LinkPart(R2cHolder *h, const R2cCmd *c);     /* 0x000EAE50 */
int  r2c_ListHasActive(void);                         /* 0x000EDA50 */
void *r2c_FindNext(void);                             /* 0x000EDB90 */
void *r2c_FindKey(int kind, int sub);                 /* 0x000EDC20 */

/* ---------------------------------------------------------------- r2c_2 */
/* Component kind 0x0D: hit callback at +0x2C, query callback at +0x30. */
typedef struct R2cComp0D {
    uint8_t  unk00[0x2C];
    int    (*onHit2C)(void *obj, void *target);       /* +0x2C */
    int    (*query30)(void *obj, int a, int *out);    /* +0x30 */
} R2cComp0D;
/* Component kind 5 (state component): effect handles at +0xD4/+0xD8. */
typedef struct R2cComp5 {
    uint8_t  unk00[0xD4];
    void    *hD4;              /* +0x0D4 attached effect, 0 = none */
    int32_t  hD8;              /* +0x0D8 sound/effect id, -1 = none */
} R2cComp5;
/* Actor state block: kind at +0x70, flags at +0x100/+0x104. */
typedef struct R2cState {
    uint8_t  unk000[0x70];
    int32_t  kind70;           /* +0x070 */
    uint8_t  unk074[0x100 - 0x74];
    int32_t  v100;             /* +0x100 */
    int32_t  v104;             /* +0x104 */
} R2cState;
void  sub_00048250(int h);

int  r2c_CompHit(void *obj, void *target);            /* 0x000EE010 */
int  r2c_CompQuery(void *obj, int a, int *out);       /* 0x000EE040 */
void r2c_StateFreeD4(void *obj, R2cState *st);        /* 0x000EFB90 */
void r2c_StateFreeD4B(void *obj, R2cState *st);       /* 0x000EFC90 */
void r2c_SetEffectD4(void *obj, int kind);            /* 0x000F0B10 obj=EDI */
void r2c_SetSoundD8(void *obj, int id, int c);        /* 0x000F0B70 obj=ESI */

/* ---------------------------------------------------------------- r2c_3 */
typedef struct R2cAnimTarget { uint8_t unk00[0xB8]; uint32_t flagsB8; } R2cAnimTarget;
typedef struct R2cPart { uint8_t unk00[8]; int32_t i08; uint8_t unk0C[8]; R2cAnimTarget *t14; } R2cPart;
/* Model node: +0x30 animation part, +0x3C next sibling, +0xD0 handle. */
typedef struct R2cModel {
    uint8_t  unk00[0x0C];
    uint32_t flags0C;          /* +0x0C bit 0: active */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    R2cPart *part30;           /* +0x30 */
    uint8_t  unk34[0x3C - 0x34];
    struct R2cModel *next3C;   /* +0x3C */
    uint8_t  unk40[0xD0 - 0x40];
    int32_t  vD0;              /* +0xD0 */
    uint8_t  unkD4[0x14C - 0xD4];
    int32_t  v14C;             /* +0x14C */
} R2cModel;
/* Global boss manager (0x130 bytes) at 0x003F610C. */
typedef struct R2cBossMgr {
    uint8_t  unk000[0x6C];
    int32_t  v6C;              /* +0x06C */
    uint8_t  unk070[0x8C - 0x70];
    R2cModel *sub8C;           /* +0x08C */
    R2cModel *sub90;           /* +0x090 */
    void    *h94;              /* +0x094 handle */
    uint8_t  unk098[0xA6 - 0x98];
    int16_t  wA6;              /* +0x0A6 */
    int16_t  wA8;              /* +0x0A8 */
    uint8_t  unk0AA[0xB8 - 0xAA];
    int32_t  vB8;              /* +0x0B8 */
    int32_t  vBC;              /* +0x0BC */
    uint8_t  unk0C0[0x110 - 0xC0];
    int32_t  v110;             /* +0x110 */
    uint8_t  unk114[0x120 - 0x114];
    int32_t  v120;             /* +0x120 */
    int32_t  h124;             /* +0x124 */
    int32_t  h128;             /* +0x128 */
    int32_t  h12C;             /* +0x12C */
} R2cBossMgr;
extern R2cBossMgr *g_acb_bossMgr;      /* 0x003F610C */
extern R2cBossMgr *g_acb_bossAux;      /* 0x003F6110 */
/* Stage game state returned by 0x000E0770. */
typedef struct R2cGame {
    int32_t  v000;             /* +0x000 */
    uint8_t  unk004[0x308 - 4];
    int32_t  v308;             /* +0x308 */
    int32_t  v30C;             /* +0x30C */
    uint8_t  unk310[4];
    int32_t  v314;             /* +0x314 */
} R2cGame;
typedef struct R2cKind {
    uint8_t  unk00[8];
    int32_t  kind08;           /* +0x08 3..5 select the boss form */
    uint8_t  unk0C[0x30 - 0xC];
    R2cPart *p30;              /* +0x30 */
    uint8_t  unk34[0x50 - 0x34];
    uint32_t v50[4];           /* +0x50 */
    uint32_t v60[4];           /* +0x60 */
} R2cKind;
typedef struct R2cMover {
    uint8_t  unk000[0xF8];
    uint32_t vF8[4];           /* +0x0F8 */
    uint32_t v108[4];          /* +0x108 */
    int32_t  v118;             /* +0x118 */
} R2cMover;
/* Boss object reset by 0x0F69E0 (0x208 bytes). */
typedef struct R2cBoss {
    uint8_t  unk000[0x8C];
    R2cModel *sub8C;           /* +0x08C */
    R2cModel *sub90;           /* +0x090 */
    int32_t  v94, v98;         /* +0x094 */
    uint8_t  unk09C[0xC8 - 0x9C];
    int32_t  vC8, vCC, vD0, vD4, vD8, vDC; /* +0x0C8 */
    uint8_t  unk0E0[0x12C - 0xE0];
    int32_t  v12C;             /* +0x12C */
    uint8_t  unk130[4];
    int32_t  h134, h138, h13C, h140; /* +0x134 */
    uint8_t  unk144[0x1A8 - 0x144];
    int32_t  v1A8;             /* +0x1A8 */
    uint8_t  unk1AC[0x1C0 - 0x1AC];
    int32_t  v1C0, v1C4;       /* +0x1C0 */
    uint8_t  unk1C8[0x206 - 0x1C8];
    int16_t  w206;             /* +0x206 */
} R2cBoss;
R2cModel *sub_0001D2B0(R2cModel *m, int idx);
void      sub_00192380(int side, int anim);
void      sub_000E0A80(R2cGame *g, int a, int b, int c, int d);
void      sub_000E51F0(R2cGame *g);
int       sub_000F30E0(int kind);
void      sub_000C75E0(R2cModel *m);
int       sub_0001BC40(R2cModel *m);

void r2c_BossSetAnim(int anim);                       /* 0x000F4370 anim=ESI */
void r2c_BossDefeat(void);                            /* 0x000F4610 */
void r2c_BossMgrCreate(void);                         /* 0x000F4D90 */
void r2c_Vec4Copy(uint32_t *dst, const uint32_t *src);  /* 0x000F5D40 */
int  r2c_CountA6(const R2cKind *k);                   /* 0x000F5FB0 */
int  r2c_CountState6C(const R2cKind *k);              /* 0x000F6030 */
void r2c_BossInit(R2cBoss *b);                        /* 0x000F69E0 */
void r2c_BossModelReset(R2cBoss *b);                  /* 0x000F6AA0 */

/* ---------------------------------------------------------------- r2c_4 */
/* Boss body object (afc_body 0x003F6114 and the per-form objects). */
typedef struct R2cBossObj {
    uint8_t  unk000[0x10];
    uint8_t  comp10[0x6C - 0x10]; /* +0x010 component block */
    int32_t  v6C;              /* +0x06C state */
    uint8_t  unk070[0x8C - 0x70];
    R2cModel *sub8C;           /* +0x08C */
    R2cModel *sub90;           /* +0x090 */
    int32_t  v94;              /* +0x094 */
    uint8_t  unk098[4];
    int32_t  v9C;              /* +0x09C step */
    uint8_t  unk0A0[4];
    int16_t  wA4, wA6, wA8, wAA, wAC, wAE, wB0, wB2; /* +0x0A4 */
    uint8_t  unk0B4[0xBC - 0xB4];
    int16_t  wBC;              /* +0x0BC */
    uint8_t  unk0BE[0xE4 - 0xBE];
    int32_t  vE4;              /* +0x0E4 */
    int32_t  vE8;              /* +0x0E8 */
    int16_t  wEC;              /* +0x0EC */
    uint8_t  unk0EE[0x134 - 0xEE];
    int32_t  h134;             /* +0x134 */
    int32_t  h138;             /* +0x138 */
    int32_t  h13C;             /* +0x13C */
    uint8_t  unk140[0x1D0 - 0x140];
    int16_t  w1D0;             /* +0x1D0 */
    uint8_t  unk1D2[0x1EC - 0x1D2];
    float    pos1EC[4];        /* +0x1EC */
} R2cBossObj;
/* Helper object (0x104 bytes) at afc_helper 0x003F611C. */
typedef struct R2cHelper {
    uint8_t  unk000[0x8C];
    R2cModel *sub8C;           /* +0x08C */
    void    *sub90;            /* +0x090 */
    int32_t  v94;              /* +0x094 */
    uint8_t  unk098[0xB4 - 0x98];
    int32_t  vB4, vB8, vBC;    /* +0x0B4 */
    uint8_t  unk0C0[0x104 - 0xC0];
} R2cHelper;
extern R2cBossObj *afc_body;           /* 0x003F6114 */
extern R2cBossObj *afc_bodyState;      /* 0x003F6118 */
extern R2cHelper  *afc_helper;         /* 0x003F611C */
extern float a50_framesPerSecond;      /* 0x0042C964 */
extern void *aec_ctx42C8E4;            /* 0x0042C8E4 */
R2cBossObj *sub_000F5F80(const R2cKind *k);
void  sub_000F62F0(R2cBossObj *e, int step);
void  sub_000F62C0(R2cBossObj *e, int step);
void  sub_000FB580(const R2cKind *k, int a);
R2cBossObj *sub_000FC4D0(void);
void  sub_000FBA00(int a);
void  sub_000F3AA0(R2cBossObj *b);
void  sub_0001D8B0(void *comp, int kind);
void  sub_0001D8D0(R2cModel *m, void *comp);
void  sub_0001E9B0(void *ctx, R2cModel *m, int a, int b, int c);
void  sub_0001EBF0(R2cModel *m, int a);
void  sub_000EE270(void *comp);
void  sub_000FBD50(void);
void  sub_000E3BA0(R2cGame *g);
void  sub_00033B30(R2cModel *m);
void  sub_0001D910(R2cModel *m, void *comp);
void  sub_000FE2E0(int a);
void  sub_00100020(int a);
R2cKind *sub_000FC4B0(void);
void  sub_000FE330(int a);
void  sub_00100070(int a);
void  sub_000FBA50(int a);

void  r2c_BossAnimIfActive(int anim);                 /* 0x000F4E10 */
float r2c_BossStepSpeed(const R2cKind *k);            /* 0x000F7AE0 */
float r2c_DistTo(void *a, R2cKind *b, float c);       /* 0x000F7C40 */
void  r2c_SnapToHelper(R2cKind *k);                   /* 0x000F9430 */
void  r2c_FormCue20(const R2cKind *k);                /* 0x000F9A10 */
void  r2c_StepA(const R2cKind *k);                    /* 0x000FA740 */
void  r2c_StepB(const R2cKind *k);                    /* 0x000FB3E0 */
void  r2c_StepC(const R2cKind *k);                    /* 0x000FB440 */
void  r2c_StepD(const R2cKind *k);                    /* 0x000FB710 */
void  r2c_BodyAnim(int anim);                         /* 0x000FBA90 */
void  r2c_BodyCheckRecover(void);                     /* 0x000FBCA0 */
void  r2c_BodyAnim21(void);                           /* 0x000FBEA0 */
void  r2c_BodyAnim24(void);                           /* 0x000FC310 */
R2cModel *r2c_BodyAttach(R2cModel *m);                /* 0x000FC410 */
int   r2c_HelperDetach(R2cModel *m);                  /* 0x000FC4E0 */
void  r2c_HelperStop(void);                           /* 0x000FD1C0 */
void  r2c_HelperCreate(void);                         /* 0x000FD3C0 */

/* ---------------------------------------------------------------- r2c_5 */
extern R2cBossObj *afc_minion;         /* 0x003F6120 */
extern R2cBossObj *afc_minionState;    /* 0x003F6124 */
extern R2cBossObj *b10_ctl;            /* 0x003F6128 */
extern R2cBossObj *b10_res3F612C;      /* 0x003F612C */
void  sub_000FE040(void);
void  sub_000FE660(void);
void  sub_001003A0(void);
void  sub_00184530(void);

R2cModel *r2c_HelperAttach(R2cModel *m);              /* 0x000FE1F0 */
void  r2c_MinionAnim(int anim);                       /* 0x000FE370 */
void  r2c_MinionCheckRecover(void);                   /* 0x000FE5A0 */
void  r2c_MinionAnim2(void);                          /* 0x000FE890 */
void  r2c_MinionAnim2D(void);                         /* 0x000FFE50 */
R2cModel *r2c_MinionAttach(R2cModel *m);              /* 0x000FFF30 */
void  r2c_CtlAnim(int anim);                          /* 0x001000B0 */
void  r2c_CtlCheckRecover(void);                      /* 0x001002E0 */
void  r2c_CtlAnim2(void);                             /* 0x001004F0 */
void  r2c_CtlAnim21(void);                            /* 0x001005F0 */
void  r2c_CtlAnim22(void);                            /* 0x001008A0 */
void  r2c_CtlAnim23(void);                            /* 0x00100990 */
void  r2c_CtlAnim25(void);                            /* 0x00100A70 */
void  r2c_CtlAnim0(void);                             /* 0x00100F10 */
void  r2c_CtlAnim29(void);                            /* 0x00101040 */
R2cModel *r2c_CtlAttach(R2cModel *m);                 /* 0x00101170 */

/* ---------------------------------------------------------------- r2c_6 */
/* Script boss object at b10_scr 0x003F6130: sound at +0x238, effect at +0x23C. */
typedef struct R2cScr {
    uint8_t  unk000[0x10];
    uint8_t  comp10[0x8C - 0x10]; /* +0x010 component block */
    R2cModel *sub8C;           /* +0x08C */
    uint8_t  unk090[0x238 - 0x90];
    int32_t  h238;             /* +0x238 */
    void    *h23C;             /* +0x23C handle */
} R2cScr;
/* Small object (0x90 bytes) at b10_obj3F6134. */
typedef struct R2cObj90 {
    uint8_t  unk000[0x10];
    uint8_t  comp10[0x8C - 0x10]; /* +0x010 component block */
    R2cModel *sub8C;           /* +0x08C */
} R2cObj90;
/* Owner object reached through component 5 +0x64: four children at +0x9A8. */
typedef struct R2cOwner { uint8_t unk000[0x9A8]; R2cModel *kids9A8[4]; } R2cOwner;
typedef struct R2cComp5b { uint8_t unk00[0x64]; R2cOwner *owner64; } R2cComp5b;
typedef struct R2cKeyObj { uint8_t unk00[4]; int32_t kind04; int32_t v08; } R2cKeyObj;
extern R2cScr   *b10_scr;              /* 0x003F6130 */
extern R2cObj90 *b10_obj3F6134;        /* 0x003F6134 */
extern void     *r2c_fx3F613C[5];      /* 0x003F613C effect handles */
void  sub_00101280(int a);
void  sub_00105D80(void);
void  sub_001061B0(void);
void  sub_001208A0(R2cModel *m, int a);
int   sub_000336A0(void *h);

void  r2c_ScrStop(void);                              /* 0x00104AF0 */
R2cModel *r2c_ScrAttach(R2cModel *m);                 /* 0x00105F90 */
int   r2c_ScrDetach(R2cModel *m);                     /* 0x00106020 */
void  r2c_Obj90Create(void);                          /* 0x00106170 */
R2cModel *r2c_Obj90Attach(R2cModel *m);               /* 0x001062C0 */
void  r2c_ReleaseKids(R2cKeyObj *o);                  /* 0x00106550 */
void *r2c_PushEffect(void *obj, int kind);            /* 0x00109050 */

/* ---------------------------------------------------------------- r2c_7 / r2c_8 */
/* Actor description record at +0x278: flag word at +4. */
typedef struct R2cDesc { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[4]; float vC; uint8_t unk10[4]; float v14; } R2cDesc;
/* Enemy actor fields used by the hit/target helpers. */
typedef struct R2cActor {
    uint8_t  unk000[0x20];
    uint8_t  b20;              /* +0x020 bit 0: disabled */
    uint8_t  unk021[0x30 - 0x21];
    R2cPart *p30;              /* +0x030 */
    uint8_t  unk034[0x58 - 0x34];
    int32_t  v58;              /* +0x058 */
    uint8_t  unk05C[4];
    float    v60;              /* +0x060 */
    uint8_t  unk064[4];
    float    v68;              /* +0x068 */
    uint8_t  unk06C[0xC8 - 0x6C];
    struct R2cActor *pC8;      /* +0x0C8 */
    uint8_t  unk0CC[0xF8 - 0xCC];
    int32_t  vF8;              /* +0x0F8 */
    uint8_t  unk0FC[0x104 - 0xFC];
    struct R2cKeyRec *p104;    /* +0x104 */
    uint8_t  unk108[0x278 - 0x108];
    R2cDesc *p278;             /* +0x278 */
} R2cActor;
typedef struct R2cKeyRec { uint8_t unk00[4]; int32_t kind04; int32_t v08; uint8_t flags0C; } R2cKeyRec;
/* Component with a handler table: slot +0x29C. */
typedef struct R2cHandler {
    uint8_t  unk000[0x29C];
    int    (*fn29C)(void *obj, struct R2cHandler *h, int a);  /* +0x29C */
} R2cHandler;
void  sub_0001D700(void *obj);
void  sub_000F3D10(void *obj, void *c, int a);
void  sub_000F3B70(void *obj, int a);
void  sub_000F3B30(void *obj, int a);
void  sub_0010FD50(R2cActor *o);                      /* o=EAX */
int   sub_000EE5F0(void *obj);
void  sub_00025D50(int a, int b);
void  sub_00117580(R2cActor *o, int a, void *b);      /* b=EDI */
void *r2b_PickTargetB(const R2cCmd *c, void *ctx, void *self); /* 0x0011EE30 c=EAX ctx=ECX */
void  sub_0011F2B0(void *obj, int k, void *a);        /* obj=EDI k=EBX */
int   r2_PlayerOutOfReach(void *obj, void *self);     /* 0x00120820 obj=EAX self=ESI */
int   r2_AnyFlag2000(int kind, void *self);           /* 0x0011FAC0 kind=EAX self=EDI */
int   r3b_Any135780(int kind);                        /* 0x00135780 kind=EAX */
void  sub_00137F50(void *key, int mode);   /* mode compared with 3, jump-table index */

int   r2c_DropTarget(void *obj, int flag);            /* 0x0010A750 */
void  r2c_HitFlash(R2cActor *o, R2cActor *src);       /* 0x00110050 */
int   r2c_RunHandler(void *obj, int a);               /* 0x00112AA0 */
void  r2c_DescTrigger(void *a, R2cActor *b, const R2cCmd *c); /* 0x00114A90 */
void  r2c_NotifyKind2(int p);                        /* 0x001154A0 p=ESI */
void  r2c_AnimDoneStep(R2cActor *o, void *b);         /* 0x001183E0 */
void  r2c_AnimDoneStep23(R2cActor *o, R2cActor *b);   /* 0x00119970 */
int   r2c_PartnerFree(const R2cKind *k, R2cActor *z); /* 0x0011DCF0 */
int   r2c_TargetCheckPlayer(void *self, void *ctx, const R2cCmd *c); /* 0x0011EF60 */
int   r2c_TargetCheck(void *self, void *ctx, const R2cCmd *c);       /* 0x0011EFD0 */
int   r2c_KeyMatches(void *unused, R2cActor *w, const int *mode);    /* 0x0011F010 */
void  r2c_DescStep2F(void *obj, R2cActor *z);         /* 0x0012B080 */
void  r2c_Step2F(void *obj, void *a);                 /* 0x0012BA10 */
void  r2c_AnimDoneStep1(R2cActor *o, void *a);        /* 0x0012C7C0 */
void  r2c_Step1(void *obj, void *a);                  /* 0x0012CEE0 */
int   r2c_NoFlag2000(void *self);                     /* 0x0012D2C0 */
int   r2c_Any0or14(void);                             /* 0x0012DD40 */
void  r2c_NotifyKind2B(int mode);                     /* 0x0012E5E0 mode=ESI */

#endif
