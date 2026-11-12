#ifndef RBL_H
#define RBL_H
#include "oogie.h"
#include "shared_decls.h"
#include "adc.h"

/* Area rbl: larger game functions in 0x000D0000..0x0018FFFF (script handlers, Jack's
   states, enemy and boss AI, stage logic). All names inferred. Register mappings are in
   the comments and in config/function_states_rbl.csv. */

/* ------------------------------------------------------------ channel requests (0x00023D80..0x00025F90) */
void sub_000243B0(int a, int b);
void sub_000251B0(int a, int b);
void sub_000252A0(int a, int b);
void sub_000253D0(int a, int b);
void sub_00025C10(int a, int b);
void sub_00025D50(int a, int b);
void sub_00025F50(int a, int b);   /* callers push 2 args; callee reads only a */
void sub_00025F90(int a, int b);   /* callers push 2 args; callee reads only a */

int rbl_ScrChannel0DBEA0(ScriptCtx *c);
int sub_00048B20(int id, int b);
int rbl_ScrSound0DC700(AdcThread *t);

/* ------------------------------------------------------------ game objects */
/* Object record (the EDI object of 0x0011F2B0). Only touched fields are named. */
typedef struct RblEnt {
    uint8_t  unk00[4];
    int32_t  type04;          /* +0x04 */
    int32_t  sub08;           /* +0x08 */
    uint32_t flags0C;         /* +0x0C bit 0: alive */
    uint32_t flags10;         /* +0x10 */
} RblEnt;
/* State block of a component (+0x278). */
typedef struct RblState {
    uint8_t  unk00[4];
    uint32_t flags04;         /* +0x04 */
    uint8_t  unk08[0x98 - 0x08];
    int32_t  i98;             /* +0x98 */
} RblState;
/* Component found with sub_0001D960(obj, kind). */
typedef struct RblComp {
    int32_t  kind00;          /* +0x00 */
    uint8_t  unk04[0x20 - 0x04];
    uint32_t flags20;         /* +0x20 */
    uint8_t  unk24[0x278 - 0x24];
    RblState *state278;       /* +0x278 */
} RblComp;
void sub_0011F2B0(void *obj, int k, void *a);   /* regargs: obj=EDI k=EBX; a on the stack */
int  rbl_EntCommand1208A0(RblEnt *e, int cmd);

/* Enemy work record (second argument of the state handlers; same +0x278 state block). */
typedef struct RblFoe {
    uint8_t  unk00[0x58];
    int32_t  step58;          /* +0x58 */
    uint8_t  unk5C[0x64 - 0x5C];
    int32_t  anim64;          /* +0x64 */
    uint8_t  unk68[0x6C - 0x68];
    int32_t  sound6C;         /* +0x6C */
    void    *attach70;        /* +0x70 */
    uint8_t  unk74[0x278 - 0x74];
    RblState *state278;       /* +0x278 */
} RblFoe;
/* Object with a position at +0x60. */
typedef struct RblObj {
    uint8_t  unk00[0x60];
    float    pos60[4];        /* +0x60 */
} RblObj;
void sub_0001D4E0(void *a);
void sub_00088190(void);

/* ------------------------------------------------------------ enemy reactions */
int   r3_CheckConds1558F0(int table, void *a, void *b);   /* 0x001558F0 regargs: table=EAX a=EBX b=EDI */
void  sub_0015A270(void *obj, int anim, void *act);       /* regargs: act=ESI, obj and anim on the stack */

/* ------------------------------------------------------------ enemies of the 0x00113040 state machine */
extern float a50_frameUnits;            /* 0x0042C858 */
extern float a50_frameSeconds;          /* 0x0042C85C */
int   sub_001C7EE1(void);               /* rand */
/* Enemy work block (+0x278). */
typedef struct RblEWork {
    uint8_t  unk00[4];
    uint32_t flags04;          /* +0x04 */
    uint8_t  unk08[0x14 - 0x08];
    float    f14;              /* +0x14 */
    float    f18;              /* +0x18 */
} RblEWork;
/* Enemy record (second argument of the state handlers). */
typedef struct RblEnemy {
    uint8_t  unk000[0x20];
    union {
        uint32_t w;            /* +0x20 bit 0, bit 16 */
        uint8_t  b[4];         /* +0x22 bit 0: side */
    } u20;
    uint8_t  unk024[0x4C - 0x24];
    uint32_t flags4C;          /* +0x4C */
    uint8_t  unk050[0x58 - 0x50];
    int32_t  i58;              /* +0x58 step */
    float    f5C;              /* +0x5C state time */
    uint8_t  unk060[0x64 - 0x60];
    int32_t  i64;              /* +0x64 */
    float    f68;              /* +0x68 */
    int32_t  fx6C;             /* +0x6C */
    void    *i70;              /* +0x70 */
    float    f74;              /* +0x74 timer */
    uint8_t  unk078[0xFC - 0x78];
    float    angFC;            /* +0xFC */
    float    f100;             /* +0x100 distance */
    uint8_t  unk104[0x270 - 0x104];
    float    maxHp270;         /* +0x270 */
    float    hp274;            /* +0x274 */
    RblEWork *work;            /* +0x278 */
} RblEnemy;
/* Owner object of an enemy. */
typedef struct RblOwner {
    uint8_t  unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    uint8_t *model20;          /* +0x20 (+0x30 = position) */
    uint8_t  unk24[0x30 - 0x24];
    void    *anim30;           /* +0x30 */
} RblOwner;
void  sub_00033A70(void *p);
void  sub_00048250(int h);
int   sub_00139FE0(RblOwner *o, RblEnemy *e);
void  sub_00113C60(float *v, float a, float b);
void  sub_00033A70(void *p);
void  sub_00048250(int h);
float sub_001A3F30(float v);
void  sub_00142270(RblOwner *o, RblEnemy *e);
/* Condition checks of table 0x0031DBBC with their 16-byte records at 0x00279848. */
typedef struct RblRec16 { float f[4]; } RblRec16;
typedef int (*RblCheckFn)(void *a, void *b, RblRec16 *rec);
extern RblCheckFn r3b_disp31DBBC[];     /* 0x0031DBBC */
extern RblRec16   r3b_recs279848[];     /* 0x00279848 */
int   r3b_Dispatch143740(int idx, void *b, void *a);   /* regargs: idx=EAX b=EDX a=stack */
void  rbl_Recover142DA0(RblOwner *o, RblEnemy *e);
void  rbl_Rise142F10(RblOwner *o, RblEnemy *e);
void  rbl_Stagger1440B0(RblOwner *o, RblEnemy *e);

/* ------------------------------------------------------------ effect slot pools */
/* 0x003FE1C8: 4 slots of 0x44 bytes. */
typedef struct RblSlot44 {
    void    *obj00;            /* +0x00 */
    void    *act04;            /* +0x04 */
    int32_t  i08;              /* +0x08 */
    int16_t  s0C;              /* +0x0C */
    uint8_t  unk0E[2];
    float    f10;              /* +0x10 */
    uint8_t  unk14[4];
    float    v18[3];           /* +0x18 */
    float    v24[4];           /* +0x24 */
    int32_t  i34;              /* +0x34 */
    float    v38[3];           /* +0x38 */
} RblSlot44;
extern RblSlot44 r3c_slots3FE1C8[4];    /* 0x003FE1C8 */
void  rbl_SlotsReset181870(void);

/* ------------------------------------------------------------ boss of the 0x00179E40 family */
typedef int  (*RblFn)();               /* state callbacks (arguments vary) */
typedef void (*RblVoidFn)();
/* Shared state block at 0x003FDC3C (0x30 bytes, cleared by 0x00179E40). */
typedef struct RblBossWork {
    uint32_t flags00;          /* +0x00 */
    float    v04[4];           /* +0x04 home point */
    uint8_t  unk14[0x20 - 0x14];
    float    f20;              /* +0x20 */
    uint8_t  unk24[0x2C - 0x24];
    void    *obj2C;            /* +0x2C */
} RblBossWork;
extern RblBossWork r3d_blk3FDC3C;      /* 0x003FDC3C */
/* Boss body object (first argument). */
typedef struct RblBody {
    uint8_t  unk000[0x04];
    int32_t  i04;              /* +0x04 kind */
    int32_t  i08;              /* +0x08 id */
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk014[0x20 - 0x14];
    uint8_t *model20;          /* +0x20 (+0x40 local matrix) */
    uint8_t  unk024[0x30 - 0x24];
    struct RblAnim *anim30;    /* +0x30 */
    uint8_t  unk034[0x50 - 0x34];
    float    f50, yaw54, f58, f5C;   /* +0x50 */
    float    pos60[4];         /* +0x60 */
    float    scale70[3];       /* +0x70 */
    float    f7C;              /* +0x7C */
    uint8_t  unk080[0xA4 - 0x80];
    float    fA4;              /* +0xA4 */
    uint8_t  unk0A8[0xB0 - 0xA8];
    float    fB0, fB4;         /* +0xB0 */
    uint8_t  unk0B8[0xD0 - 0xB8];
    int32_t  iD0;              /* +0xD0 */
    uint8_t  unk0D4[0xDC - 0xD4];
    float    fDC;              /* +0xDC */
    uint8_t  unk0E0[0xE8 - 0xE0];
    float    fE8;              /* +0xE8 */
    int32_t  iEC;              /* +0xEC */
    int32_t  iF0;              /* +0xF0 */
    uint32_t uF4;              /* +0xF4 */
    uint8_t  unk0F8[0xFC - 0xF8];
    float    fFC;              /* +0xFC */
    uint8_t  unk100[0x10C - 0x100];
    float    f10C;             /* +0x10C */
    uint8_t  unk110[0x118 - 0x110];
    int32_t  i118, i11C;       /* +0x118 */
    uint32_t u120;             /* +0x120 */
    int32_t  i124;             /* +0x124 */
    uint32_t flags128;         /* +0x128 */
} RblBody;
/* Animation holder (+0x30 of a body): the playing instance at +0x14. */
typedef struct RblAnim {
    uint8_t  unk00[0x14];
    void    *inst14;           /* +0x14 */
} RblAnim;
/* Boss actor record (second argument). */
typedef struct RblBossAct {
    uint8_t  unk000[0x24];
    int32_t  i24;              /* +0x24 */
    float    f28, f2C;         /* +0x28 */
    const void *desc30;        /* +0x30 */
    uint8_t  unk034[0x50 - 0x34];
    int32_t  i50, i54;         /* +0x50 */
    uint8_t  unk058[0x6C - 0x58];
    int32_t  snd6C;            /* +0x6C */
    uint8_t  unk070[0x78 - 0x70];
    float    v78[4];           /* +0x78 velocity */
    float    v88[4];           /* +0x88 initial velocity */
    uint8_t  unk098[0x270 - 0x98];
    float    maxHp270;         /* +0x270 */
    float    hp274;            /* +0x274 */
    void    *work278;          /* +0x278 work block */
    RblFn    fn27C, fn280, fn284, fn288;   /* +0x27C */
    RblFn   *tab28C, *tab290, *tab294;     /* +0x28C state tables */
    RblVoidFn fn298;           /* +0x298 */
    RblFn    fn29C;            /* +0x29C */
} RblBossAct;
extern RblFn rbl_states32B4C0[5];      /* 0x0032B4C0 */
extern RblFn rbl_states32B4D4[5];      /* 0x0032B4D4 */
extern RblFn rbl_states32B4E8[5];      /* 0x0032B4E8 */
extern const int32_t rbl_desc32B49C[]; /* 0x0032B49C */
int   sub_00179E40();
int   sub_00179EC0();
int   sub_00179FE0();
int   sub_0017A350();
int   sub_00145E10();
float sub_00113290(void *o, const float *pt);
int   sub_0001BC40(void *o);
void  r3_SetStateD(void *obj, void *act, int state);   /* 0x0017A2B0 obj=EBX act=ESI state=stack */
int   rbl_BossInit17A820(RblBody *o, RblBossAct *a);
/* Timer / effect node of an actor (0x001133E0). */
typedef struct RblNode {
    uint8_t  unk00[0x10];
    float    f10;              /* +0x10 */
    int32_t  i14;              /* +0x14 effect handle */
} RblNode;
typedef struct RblJoint { uint8_t unk00[0x90]; uint32_t flags90; } RblJoint;
RblNode *sub_001133E0(void *e, int slot);
void  sub_00113370(void *e, RblNode *n);
float sub_00113200(void *o, void *target);
void  sub_001AD7E0(float *d, const float *s);          /* normalise */
int   sub_0017AF00(void *b, void *a);                  /* regargs: b=EAX a=stack */
void  sub_000A8ED0(int h, const float *pos, float *v, int k);
void  sub_000A7950(int h);
void  rbl_BossThrow17B320(RblBody *o, RblBossAct *a);
void  rbl_BossThrowFlat17B4D0(RblBody *o, RblBossAct *a);
/* 0x003FDAF8: 9 slots of 0x24 bytes for the minions of this boss. */
typedef struct RblSlot24 {
    RblBody    *obj00;         /* +0x00 */
    RblBossAct *act04;         /* +0x04 */
    uint8_t  unk08[0x10 - 0x08];
    int32_t  i10;              /* +0x10 */
    int16_t  s14;              /* +0x14 slot index */
    int16_t  s16;              /* +0x16 */
    float    v18[3];           /* +0x18 */
} RblSlot24;
extern RblSlot24 b7c_pool3FDAF8[9];     /* 0x003FDAF8 */
extern RblFn rbl_states32B3B4[];        /* 0x0032B3B4 */
extern RblFn rbl_states32B3CC[];        /* 0x0032B3CC */
extern const float rbl_place27A418[4];  /* 0x0027A418 */
extern const float rbl_minionPos27A468[9][4];  /* 0x0027A468 */
extern const float rbl_minionYaw27A4F8[9];     /* 0x0027A4F8 */
int   sub_00179190();
int   sub_00179240();
int   sub_001792D0();
float sub_00171D50(int kind, int id, int v);
void  sub_000F5D60(void *o, float a, float b, float c, const float *v);
void  sub_0001D700(void *o);
int   rbl_MinionInit179C00(RblBody *o, RblBossAct *a, int k);
extern RblFn rbl_states32B344[];        /* 0x0032B344 */
extern RblFn rbl_states32B370[];        /* 0x0032B370 */
int   sub_001784D0();
int   sub_001784E0();
int   sub_001786F0();
int   sub_001787A0();
int   rbl_BossInit178EB0(RblBody *o, RblBossAct *a, int mode);

/* ------------------------------------------------------------ more boss/minion set-ups */
/* 0x003FE2D8: 4 records of 0x24 bytes. */
typedef struct RblRec24 {
    uint8_t  unk00[4];
    RblBody *obj04;            /* +0x04 */
    uint8_t  unk08[0x18 - 0x08];
    float    v18[3];           /* +0x18 */
} RblRec24;
extern RblRec24 b7c_idRecs3FE2D8[4];    /* 0x003FE2D8 */
/* 0x003FE0C0: 3 records of 0x58 bytes. */
typedef struct RblRec58 {
    RblBody    *obj00;         /* +0x00 */
    RblBossAct *act04;         /* +0x04 */
    uint8_t  unk08[4];
    int32_t  i0C;              /* +0x0C index */
    uint8_t  unk10[0x18 - 0x10];
    int32_t  i18;              /* +0x18 */
    float    f1C, f20;         /* +0x1C */
    float    v24[4];           /* +0x24 */
    float    v34[3];           /* +0x34 */
    uint8_t  unk40[0x58 - 0x40];
} RblRec58;
extern RblRec58 r3e_recs3FE0C0[3];      /* 0x003FE0C0 */
extern float    rbl_hp3FE09C[3];        /* 0x003FE09C health per record */
extern void    *a80_ctx42C8E4;          /* 0x0042C8E4 */
extern RblFn rbl_states32B870[];        /* 0x0032B870 */
extern RblFn rbl_states32B874[];        /* 0x0032B874 */
extern RblFn rbl_states32B818[];        /* 0x0032B818 */
extern RblFn rbl_states32B82C[];        /* 0x0032B82C */
extern const float rbl_place27A8E4[4];  /* 0x0027A8E4 */
extern const float rbl_place27A768[4];  /* 0x0027A768 */
int   sub_00181E00();
int   sub_00181EF0();
int   sub_00182060();
int   sub_0017F050();
int   sub_001806E0();
int   sub_0017F0F0();
void  sub_0001E9B0(void *ctx, void *m, int a, int b, int c);
void  sub_0001EBF0(void *m, int a);
int   rbl_BossInit1824F0(RblBody *o, RblBossAct *a, int k);
int   rbl_BossInit1807D0(RblBody *o, RblBossAct *a, int k);

#endif
