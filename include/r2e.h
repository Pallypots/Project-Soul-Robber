/* Area r2e: game functions in 0x000D0000..0x0012FFFF. Names inferred. */
#ifndef R2E_H
#define R2E_H
#include "oogie.h"

/* ---------------------------------------------------------------- shared */
typedef struct R2eCtx {
    uint8_t  unk000[0x1E8];
    void    *res1E8;           /* +0x1E8 resource bank */
} R2eCtx;
extern R2eCtx *r2e_ctx;                /* 0x0042C8E4 */

/* Stage director object (same layout as r2d's R2dStage). */
typedef struct R2eModel {
    uint8_t  unk00[0x64];
    float    f64;              /* +0x64 */
} R2eModel;
typedef struct R2eSlot {
    R2eModel *p00;             /* +0x00 model */
    void    *h04;              /* +0x04 resource (from 0x0001D080) */
    float    v08[4];           /* +0x08 */
    float    f18;              /* +0x18 */
    int32_t  state1C;          /* +0x1C */
    float    t20;              /* +0x20 */
    uint8_t  unk24[0x28 - 0x24];
} R2eSlot;
typedef struct R2eStage {
    uint8_t  unk000[0x86C];
    R2eSlot  slots86C[6];      /* +0x86C */
} R2eStage;

/* Track event node walked by 0x000E2C20..0x000E2D10. */
typedef struct R2eEvt {
    uint8_t  unk00[8];
    int32_t  kind08;           /* +0x08 */
} R2eEvt;
typedef struct R2eTrack {
    int32_t  owner00;          /* +0x00 */
} R2eTrack;
typedef void (*R2eEvtFn)(R2eTrack *t, R2eEvt *e);

/* Free-slot pool at 0x003F5D30 (8 x 16 bytes), list head right after. */
typedef struct R2eQSlot {
    uint8_t  unk00[8];
    int32_t  v08;              /* +0x08 */
    int32_t  v0C;              /* +0x0C */
} R2eQSlot;
extern R2eQSlot r2e_qpool3F5D30[8];    /* 0x003F5D30 */
extern uint8_t  r2e_q3F5DB0[];         /* 0x003F5DB0 list head */


typedef struct R2eObjBC {
    uint8_t  unk00[0xBC];
    int16_t  wBC;              /* +0xBC */
} R2eObjBC;
typedef struct R2eObj68 {
    uint8_t  unk00[0x68];
    float    f68;              /* +0x68 */
} R2eObj68;

typedef struct R2eNamed {
    uint8_t  unk00[4];
    const char *name04;        /* +0x04 */
} R2eNamed;

typedef struct R2eColRec {
    uint8_t  unk00[0x0C];
    int32_t  timeC;            /* +0x0C milliseconds */
    uint8_t  rgba10[4];        /* +0x10 */
} R2eColRec;

typedef struct R2eDir {
    int32_t  key000;           /* +0x000 */
    uint8_t  unk004[0x2F4 - 4];
    uint32_t flags2F4;         /* +0x2F4 */
    uint8_t  unk2F8[0x314 - 0x2F8];
    int32_t  v314;             /* +0x314 */
} R2eDir;
typedef struct R2eCue {
    uint8_t  unk00[0x0C];
    int32_t  vC;               /* +0x0C */
    int32_t  v10;              /* +0x10 */
} R2eCue;

typedef struct R2eMdl6C {
    uint8_t  unk00[0x6C];
    int32_t  state6C;          /* +0x6C */
} R2eMdl6C;

typedef struct R2eObj30 {
    uint8_t  unk00[0x30];
    void    *p30;              /* +0x30 */
} R2eObj30;
typedef struct R2eObj58 {
    uint8_t  unk00[0x58];
    int32_t  kind58;           /* +0x58 */
} R2eObj58;

/* Boss screen object at *0x003F6130. */
typedef struct R2eScnNode { uint8_t unk00[0x64]; float f64; } R2eScnNode;
typedef struct R2eScn {
    uint8_t  unk000[0x8C];
    R2eScnNode *node8C;        /* +0x08C */
    uint8_t  unk090[0x1A8 - 0x90];
    int16_t  step1A8;          /* +0x1A8 */
    uint8_t  unk1AA[2];
    float    t1AC;             /* +0x1AC */
    float    f1B0;             /* +0x1B0 */
} R2eScn;
extern R2eScn *r2e_scr3F6130;          /* 0x003F6130 */
/* Boss controllers at *0x003F6128 and *0x003F6120 (two-part bosses). */
typedef struct R2eCtl {
    uint8_t  unk000[0x8C];
    R2eObj30 *a8C;             /* +0x08C */
    R2eObj30 *b90;             /* +0x090 */
    uint8_t  unk094[0x9C - 0x94];
    int32_t  v9C;              /* +0x09C */
    float    fA0;              /* +0x0A0 */
    uint8_t  unk0A4[2];
    int16_t  wA6;              /* +0x0A6 */
    uint8_t  unk0A8[0x1B8 - 0xA8];
    float    f1B8;             /* +0x1B8 */
} R2eCtl;
extern R2eCtl *r2e_ctl3F6128;          /* 0x003F6128 */
extern R2eCtl *r2e_minion3F6120;       /* 0x003F6120 */
extern void   *r2e_g3F1B20;            /* 0x003F1B20 */
extern float   r2e_cueLift317D7C;      /* 0x00317D7C, 24.0 */
extern uint8_t r2e_cue317D80[];        /* 0x00317D80 */

/* Actor with a body record at +0x278. */
typedef struct R2eBody {
    uint8_t  unk00[4];
    uint32_t flags4;           /* +0x04 */
    uint8_t  unk08[4];
    uint32_t flagsC;           /* +0x0C */
    uint8_t  unk10[4];
    float    v14[4];           /* +0x14 */
    uint8_t  unk24[0x2C - 0x24];
    float    v2C[3];           /* +0x2C */
    float    f38;              /* +0x38 */
    uint8_t  unk3C[0x44 - 0x3C];
    float    f44;              /* +0x44 */
    uint8_t  unk48[0x144 - 0x48];
    int32_t  v144;             /* +0x144 */
    uint8_t  unk148[4];
    int32_t  v14C;             /* +0x14C */
    uint8_t  unk150[0x164 - 0x150];
    float    v164[4];          /* +0x164 */
    uint8_t  unk174[0x188 - 0x174];
    float    f188;             /* +0x188 */
} R2eBody;
typedef struct R2eActor {
    uint8_t  unk000[0x0C];
    uint32_t flags0C;          /* +0x00C */
    uint32_t v10;              /* +0x010 */
    uint8_t  unk014[0x20 - 0x14];
    uint8_t  b20;              /* +0x020 */
    uint8_t  unk021;
    uint8_t  b22;              /* +0x022 */
    uint8_t  unk023[0x30 - 0x23];
    void    *p30;              /* +0x030 */
    uint8_t  unk034[0x4C - 0x34];
    uint32_t flags4C;          /* +0x04C */
    float    f50;              /* +0x050 */
    float    f54;              /* +0x054 */
    int32_t  v58;              /* +0x058 */
    uint8_t  unk05C[0x64 - 0x5C];
    int32_t  kind64;           /* +0x064 */
    float    f68;              /* +0x068 */
    int32_t  v6C;              /* +0x06C */
    void    *v70;              /* +0x070 handle (0x00036750) */
    float    f74;              /* +0x074 */
    float    v78[4];           /* +0x078 */
    uint8_t  unk088[0x94 - 0x88];
    void    *p94;              /* +0x094 */
    uint8_t  unk098[0xA8 - 0x98];
    int32_t  vA8;              /* +0x0A8 */
    uint8_t  unk0AC[0xB4 - 0xAC];
    float    fB4;              /* +0x0B4 */
    float    fB8;              /* +0x0B8 */
    float    fBC;              /* +0x0BC */
    float    fC0;              /* +0x0C0 */
    float    vC4[4];           /* +0x0C4 */
    float    fD4;              /* +0x0D4 */
    uint8_t  unk0D8[0x128 - 0xD8];
    uint32_t flags128;         /* +0x128 */
    uint8_t  unk12C[0x278 - 0x12C];
    R2eBody *body278;          /* +0x278 */
} R2eActor;
typedef struct R2eMove {
    uint8_t  unk00[0x20];
    int32_t  v20;              /* +0x20 */
    uint8_t  unk24[0xE8 - 0x24];
    float    fE8;              /* +0xE8 */
} R2eMove;
typedef struct R2eTurn {
    uint8_t  unk00[0x10];
    int32_t  v10;              /* +0x10 */
    int32_t  v14;              /* +0x14 */
    int32_t  v18;              /* +0x18 */
} R2eTurn;
extern float r2e_frameSeconds;         /* 0x0042C85C */
typedef struct R2eRange {
    int32_t  mode0;            /* +0x00 1 player, 2 self, 3 none */
    uint8_t  unk04[0x10 - 4];
    float    f10;              /* +0x10 min */
    float    f14;              /* +0x14 max */
} R2eRange;
typedef struct R2eHit { uint8_t unk00[4]; int32_t kind4; } R2eHit;
typedef struct R2eMgr {
    uint8_t  unk000[0x40C];
    int32_t  v40C;             /* +0x40C */
    uint8_t  unk410[0x420 - 0x410];
    int32_t  v420;             /* +0x420 */
} R2eMgr;
extern uint8_t r2e_player41FEC0[];     /* 0x0041FEC0 player record */
extern const float r2e_vec318E18[4];   /* 0x00318E18 */
extern float r2e_vec30D6A8[4];         /* 0x0030D6A8 saved position */
/* Script threads at 0x003EF034 (same layout as adc's AdcThread). */
typedef struct R2eThread {
    uint8_t *start;            /* +0x00 */
    uint8_t *pc;               /* +0x04 */
    int16_t  id;               /* +0x08 */
    uint8_t  unk0A[0x50 - 0x0A];
    float    wait;             /* +0x50 */
    uint16_t flags;            /* +0x54 */
    uint8_t  unk56[2];
    int32_t  v58;              /* +0x58 */
} R2eThread;
extern int32_t   r2e_threadCount;      /* 0x003EF030 */
extern R2eThread r2e_threads[64];      /* 0x003EF034 */
extern int32_t  *r2e_scripts417864;    /* 0x00417864 offset table, -1 ends */
typedef struct R2eCam {
    uint8_t  unk000[0x40C];
    int32_t  v40C;             /* +0x40C */
    int32_t  max410;           /* +0x410 */
    uint8_t  unk414[4];
    int32_t  seq418;           /* +0x418 */
    int32_t  v41C;             /* +0x41C */
    uint8_t  unk420[0x430 - 0x420];
    int32_t  on430;            /* +0x430 */
    int32_t  center434;        /* +0x434 */
    int32_t  lo438;            /* +0x438 */
    int32_t  hi43C;            /* +0x43C */
    int32_t  mode440;          /* +0x440 */
    int32_t  v444;             /* +0x444 */
    int32_t  v448;             /* +0x448 */
    uint8_t  unk44C[0x518 - 0x44C];
    int32_t  v518;             /* +0x518 */
} R2eCam;
/* Helper object at *0x003F611C. */
typedef struct R2eHelper {
    uint8_t  unk000[0x8C];
    R2eObj30 *p8C;             /* +0x08C */
    uint8_t  unk090[0xA8 - 0x90];
    float    fA8;              /* +0x0A8 */
    uint8_t  unk0AC[0xC8 - 0xAC];
    float    fC8;              /* +0x0C8 */
    uint8_t  unk0CC[0xF8 - 0xCC];
    int32_t  vF8;              /* +0x0F8 */
} R2eHelper;
extern R2eHelper *r2e_helper3F611C;    /* 0x003F611C */
extern float r2e_fps42C964;            /* 0x0042C964 */
/* Hook record embedded at +0x14C of an actor (0x00113E90). */
typedef struct R2eHook {
    uint8_t  unk000[4];
    void   (*fn4)(void);       /* +0x004 */
    uint8_t  unk008[0x10 - 8];
    float    f10;              /* +0x010 */
    uint8_t  unk014[0x94 - 0x14];
    int32_t *p94;              /* +0x094 */
    float    f98;              /* +0x098 */
    uint8_t  unk09C[0x11C - 0x9C];
    int32_t *p11C;             /* +0x11C */
    void    *owner120;         /* +0x120 */
} R2eHook;
typedef struct R2eHookHost {
    uint8_t  unk000[0x14C];
    R2eHook  hook14C;          /* +0x14C */
} R2eHookHost;
/* 0x150-byte entries released by 0x0010F010; +0x08 of the first is the
   count key. */
typedef struct R2eEnt {
    uint8_t  unk000[8];
    int32_t  key8;             /* +0x008 */
    uint32_t flagsC;           /* +0x00C */
    uint8_t  unk010[0x150 - 0x10];
} R2eEnt;
/* Fade queue at 0x003F47B8. */
typedef struct R2eFadeQ {
    int32_t  q[4];             /* +0x00 */
    int32_t  state;            /* +0x10 */
    float    t;                /* +0x14 */
} R2eFadeQ;
extern R2eFadeQ r2e_fadeQ3F47B8;       /* 0x003F47B8 */
typedef struct R2eSpan {
    int32_t  center0;          /* +0x00 */
    uint8_t  unk04[8];
    int32_t  widthC;           /* +0x0C */
    int32_t  v10;              /* +0x10 */
} R2eSpan;
typedef struct R2eVel {
    uint8_t  unk000[0xF0];
    float    vF0[4];           /* +0x0F0 */
    uint8_t  unk100[0x110 - 0x100];
    int32_t  v110;             /* +0x110 */
    int32_t  v114;             /* +0x114 */
} R2eVel;
typedef struct R2eGauge {
    uint8_t  unk000[0xE04];
    int32_t  vE04;             /* +0xE04 */
} R2eGauge;
/* Two-level id table at 0x00309BE8: groups of 0x204 bytes, a key and up
   to 64 (key, value) pairs, both lists ended by a negative key. */
typedef struct R2ePair { int32_t k, v; } R2ePair;
typedef struct R2eGroup {
    int32_t  key;              /* +0x000 */
    R2ePair  pairs[64];        /* +0x004 */
} R2eGroup;
extern R2eGroup r2e_groups309BE8[];    /* 0x00309BE8 */
typedef int (*R2eTestFn)(void *o, void *a, const float *v);
extern R2eTestFn r2e_fn31B0C4;         /* 0x0031B0C4 */
extern const float r2e_vec279598[4];   /* 0x00279598 */
extern float r2e_frameUnits;           /* 0x0042C858 */
extern float r2e_slotRamp317DEC;       /* 0x00317DEC, 0.8 */
extern R2eStage r2e_stage3F0758;       /* 0x003F0758 */
/* Six 0x340-byte unit records whose first word is cleared at 0x003F63E8. */
typedef struct R2eUnit { int32_t v0; uint8_t unk04[0x340 - 4]; } R2eUnit;
extern R2eUnit r2e_units3F63E8[6];     /* 0x003F63E8 */
extern void   *r2e_g3F616C;            /* 0x003F616C */
extern void   *r2e_g3F74F0;            /* 0x003F74F0 */
extern void   *r2e_g3F74F4;            /* 0x003F74F4 */
typedef struct R2eOp { uint8_t unk00[4]; uint8_t *pc; } R2eOp;
typedef struct R2eRes130 { uint8_t unk000[0x130]; int32_t v130; } R2eRes130;
typedef struct R2eCmd { int32_t id; int32_t a, b; } R2eCmd;
extern const R2eCmd r2e_cmds279330[17]; /* 0x00279330 */
extern int32_t r2e_state3F7500;        /* 0x003F7500 */
typedef struct R2eStep {
    int32_t  v0;               /* +0x00 */
    uint8_t  unk04[0x10 - 4];
    float    f10;              /* +0x10 */
    float    f14, f18, f1C;    /* +0x14..+0x1C */
} R2eStep;
typedef struct R2eCond {
    uint8_t  unk00[8];
    uint32_t mask8;            /* +0x08 */
    int32_t  invC;             /* +0x0C */
} R2eCond;

extern void   *r2e_g3F6100;            /* 0x003F6100 */
extern int32_t r2e_ids318CA8[16];      /* 0x00318CA8, -1 = empty */

/* ---------------------------------------------------------------- not analysed */
void  r2d_StageFadeColor(void *o, float f, int r, int g, int b, int a); /* 0x000E1C20 */
void  sub_000E0A80(void *o, int a, int b, int c, int d);
void  sub_000E1FD0(R2eStage *o, int idx, const void *cue);
void  sub_00189510(void *p);
int   sub_001456E0(void *a, void *b, int c, int d);
void  sub_0001D4E0(void *a);
void  sub_00145C90(float *dst, int a, const float *b);
void  sub_00145CD0(float *dst, const float *a, float f);
void *sub_000EDC20(int a, int b);
void  r2e_Part5Event(void *o, int k);                  /* 0x00108B80, regargs: o=ESI k=EDI */
int   r2e_FindOther(int id, void *self, uint32_t mask); /* 0x0011FB40, regargs: id=EAX self=EDI mask=ESI */
void  sub_00113040(void *o, void *a, int ev);
int   sub_00145940(void *a, int b, int c, int d, int e);
void  sub_001459D0(void *a, int b, int c, int d);
void  sub_00033250(void);
void  sub_000580D0(void);
void  sub_00058540(void (*fn)(void), void *arg);   /* start job fn(arg) */
void  sub_000E5300(void);
void  r2d_PlayerPlace(void *p, const void *pos);       /* 0x000D1CA0 */
void  sub_000CF330(void *p, const void *pos, float f);
float sub_001B2770(const void *a, const void *b);
void  sub_000E8690(int a, int b);
R2eHit *sub_000E2540(R2eMgr *o, int id);
void  sub_000F3BF0(void *h, int a, int b);
void  sub_000E2670(R2eMgr *o, int id, int c);
void  sub_00115000(void *a, R2eActor *o);      /* regargs: o=EAX */
void  sub_000F3B00(void *o, int a);
void  sub_000F3B30(void *o, int a);
void  sub_00113480(void *a, int b);
int   sub_0011EDE0(int id, void *o);           /* regargs: id=EAX o=EBX */
int   sub_000D9A70(int id);
int   sub_00145780(void *a, float f);
void  sub_0012E190(void *a, R2eActor *o);      /* regargs: o=EAX */
int   sub_001C7EE1(void);                      /* CRT rand (Hypothesis) */
void  sub_0013DF90(void *e, int a);
void  sub_000ED560(int type);
void  sub_00020170(void *p);
void  sub_000ED9E0(void (*fn)(void));
void  sub_00112A80(void);
void  sub_000D9AB0(int bit);
void  r2d_StageSlotSetState(R2eStage *o, int idx, int st); /* 0x000E1F60 */
int   sub_00036770(void *t, int h, int a);
void  sub_000E8920(int a, int b);
void  sub_001B2150(void *p);
void  sub_00112D30(void);
void  sub_001B21D0(void *list, void *hook);
void  sub_00113090(void *a, void *o, int k);
void  sub_00113C60(float *v, float a, float b);
void  sub_00113CB0(float *v, float a, float b);
int   sub_000F3140(int key);
void  sub_0001EB80(void *p);
void  sub_000EE270(void *m);
void  sub_0001D910(void *o, void *m);
void  sub_000720A0(float *t, int a);
float sub_000F3C70(void *n);
void  sub_000F3C40(void *n);
void  sub_000253D0(int a, int b);
void  sub_000F3B70(void *n, int a);
void *sub_0004F680(int id);
void *sub_00053AB0(void *p, int a, int b);
void  sub_000512D0(int id, void *p);
R2eStep *sub_00113400(void *a, int k);
void *sub_00109050(void *o, int k);
void  sub_0001D700(void *o);
void  sub_00033A70(void *p);
void  sub_00101240(int a);
void  sub_00101280(int a);
void  sub_000F3F00(void *o, float f);
void *sub_0001D960(void *o, int a);
int   sub_000833E0(void *p);
int   sub_00120820(void *p, void *o);  /* regargs: p1=EAX p2=ESI */
void  sub_0011F2B0(void *o, void *p, int k); /* regargs: o=EDI k=EBX */
void  sub_000ED600(int type);
int   sub_0004F6D0(int id);
void *sub_000E0BD0(R2eTrack *t, int kind, int key, int c);
R2eEvtFn sub_000E9BC0(int owner, int kind);
R2eEvtFn sub_000E9C00(int owner, int kind);
R2eEvtFn sub_000E9C40(int owner, int kind);
int   sub_000E2420(R2eStage *o);
void *sub_0001D080(void *bank, int type, int id);
void  sub_0001D7F0(void *model, int a, int b);
void  sub_000E23F0(int a, int b);
void  sub_0012D600(int a);
void  sub_000F09E0(int a);             /* regargs: p1=EAX */
void  sub_00117580(void *o, int ev, void *c); /* regargs: p3=EDI */
void  sub_000F8940(void *a, int b, int c);
void  sub_000F8B40(void *a, int b, int c);
void  sub_0005BBB0(int a);
void  sub_0003D880(void *list, void *node);
int   sub_000F5D00(void *o);
void  sub_000F3D10(void *o, void *m, int state);   /* m: state block (+0x6C state) */
void *sub_000F5F80(void *o);
int   sub_000494D0(int id, void *pos, int c);

#endif
