#ifndef RBH_H
#define RBH_H
#include "oogie.h"
#include "shared_decls.h"

/* Area rbh: larger game functions in 0x000D0000..0x0018FFFF (enemy/boss AI, Jack's actions,
   script handlers, stage timeline, effects). All names inferred. Register mappings are in the
   comments and in config/function_states_rbh.csv. */

/* Float to int truncation. The original inlines cvttss2si; the intrinsic is used only for the
   32-bit x86 comparison build (same as RFL_FTOI in rfl.h). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define RBH_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define RBH_FTOI(x) ((int)(x))
#endif

/* Zero n bytes the way the original's inlined memset does (dwords, then the remaining bytes).
   The intrinsics are used only for the 32-bit x86 comparison build; other targets use memset. */
#include <string.h>
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define RBH_ZERO(p, n) (__stosd((unsigned long *)(p), 0, (n) >> 2), \
                        __stosb((unsigned char *)(p) + ((n) & ~3u), 0, (n) & 3))
/* Zero n dwords (rep stosd). */
#define RBH_ZEROD(p, n) __stosd((unsigned long *)(p), 0, (n))
#else
#define RBH_ZERO(p, n) memset((p), 0, (n))
#define RBH_ZEROD(p, n) memset((p), 0, (n) * 4u)
#endif

/* ------------------------------------------------------------ shared callees */
void  sub_000580D0(void);                            /* yield one frame while waiting */
int   sub_000F30E0(int kind);                        /* record count of a kind */
void  sub_000ED4C0(int a);
int   sub_000ED520(int a, int b);                    /* nonzero while busy */
void  sub_000ED5D0(int a);

/* ------------------------------------------------------------ globals */
extern uint8_t *b10_obj3F6160;                       /* 0x003F6160, 0x198-byte records */

/* ------------------------------------------------------------ 2D sprites (0x9C bytes) */
typedef struct RbhSprite {
    uint8_t unk00[0x44];
    int32_t tex44;               /* +0x44 texture handle */
    uint8_t unk48[0x9C - 0x48];
} RbhSprite;
int   sub_0004F4D0(void);                            /* nonzero while busy */
int   sub_0004F6B0(int id);                          /* movie/resource size */
int   sub_0004F6D0(int id);                          /* nonzero when already loaded */
void  sub_00053E20(const char *name, void *dst);     /* load file into dst */
void  sub_00053ED0(const char *name, void *dst);     /* load file into dst */
void  sub_00014DA0(void *data);
void  sub_000150B0(RbhSprite *s, int frame);
void  sub_000150E0(RbhSprite *s, int k);

/* Checkpoint screen blocks (0x003F1B58..0x003F57AC is cleared as one block). */
typedef struct RbhFx { uint8_t unk00[0xA8]; RbhSprite sprA8; } RbhFx;           /* 0x144 bytes */
typedef struct RbhSlot { uint32_t flags; RbhSprite spr04; } RbhSlot;            /* 0xA0 bytes */
typedef struct RbhFadeA { uint8_t unk00[0x2C]; RbhSprite spr[6]; } RbhFadeA;
typedef struct RbhFadeB { uint8_t unk00[0x1C]; RbhSprite spr1C; } RbhFadeB;
typedef struct RbhFadeC { uint8_t unk00[0x24]; RbhSprite spr24, sprC0; } RbhFadeC;
typedef struct RbhFadeD { uint8_t unk00[0x20]; RbhSprite spr[3]; } RbhFadeD;
extern uint32_t   rbh_block3F1B58[0xF15];            /* 0x003F1B58 */
extern RbhFx      r2c_fx3F1B5C[32];                  /* 0x003F1B5C */
extern RbhFadeA   r2c_fadeA3F43E0;                   /* 0x003F43E0 */
extern RbhFadeB   r2c_fadeB3F47B8;                   /* 0x003F47B8 */
extern RbhFadeC   r2c_fadeC3F4874;                   /* 0x003F4874 */
extern int32_t    rbh_ckptSet3F49D8;                 /* 0x003F49D8 */
extern RbhSprite  r2_fade3F49E0;                     /* 0x003F49E0 */
extern RbhSprite  r2_fade3F4A7C;                     /* 0x003F4A7C */
extern RbhFadeD   r2c_fadeD3F4B1C;                   /* 0x003F4B1C */
extern RbhSlot    r2_slots3F4D10[16];                /* 0x003F4D10 */
extern RbhSprite  rbh_spr3F5710;                     /* 0x003F5710 */
extern uint8_t   *rbh_ckptBuf3F57AC;                 /* 0x003F57AC */
extern int32_t    rbh_tex3F57B0, rbh_tex3F57B4, rbh_tex3F57B8;
extern uint32_t   g_acb_3F57BC;                      /* 0x003F57BC load step */
extern const char *rbh_ckptFiles317E1C[17];          /* 0x00317E1C */

/* ------------------------------------------------------------ enemy family B (0x150000) */
int   r3_CheckConds1558F0(int table, void *obj, void *act);   /* regargs: table=EAX obj=EBX act=EDI */
void  sub_0015A270(void *obj, int anim, void *act);          /* regargs: act=ESI, obj and anim on the stack */

/* ------------------------------------------------------------ actor components */
/* Actor component (only the touched fields; same layout as RbgComp). */
typedef struct RbhTgtRender { uint8_t unk00[0xC4]; uint8_t *pC4; } RbhTgtRender;
/* Target object of an enemy (Jack or another scene object), only the touched fields. */
typedef struct RbhTarget {
    uint8_t       unk00[4];
    int32_t       kind04;        /* +0x04 */
    int32_t       i08;           /* +0x08 */
    uint32_t      flags0C;       /* +0x0C bit 0: active */
    uint8_t       unk10[0x20 - 0x10];
    RbhTgtRender *r20;           /* +0x20 */
    uint8_t       unk24[0x60 - 0x24];
    float         pos60[4];      /* +0x60 */
} RbhTarget;
typedef struct RbhComp {
    uint8_t  unk00[0x20];
    union {
        uint32_t flags20;        /* +0x20 */
        uint8_t  bytes20[4];     /* +0x20 the same flags read bytewise (bytes20[2] bit 0 = 0x10000) */
    };
    uint8_t  unk24[0x4C - 0x24];
    uint32_t flags4C;            /* +0x4C */
    int32_t  i50;                /* +0x50 current state */
    uint8_t  unk54[0x58 - 0x54];
    int32_t  i58;                /* +0x58 sub-state */
    float    f5C;                /* +0x5C timer */
    uint8_t  unk60[0x64 - 0x60];
    int32_t  i64;                /* +0x64 move id */
    uint8_t  unk68[0x74 - 0x68];
    float    f74;                /* +0x74 timer */
    uint8_t  unk78[0x88 - 0x78];
    float    v88[4];             /* +0x88 velocity */
    uint8_t  unk98[0xF8 - 0x98];
    int32_t  iF8;                /* +0x0F8 */
    float    fFC;                /* +0x0FC angle to target */
    float    f100;               /* +0x100 distance to Jack */
    struct RbhTarget *target104; /* +0x104 */
    uint8_t  unk108[0x274 - 0x108];
    float    f274;               /* +0x274 health */
    void    *work278;            /* +0x278 actor work block */
} RbhComp;
/* Work block of the enemy family at 0x00110000 (act+0x278), only the touched fields. */
typedef struct RbhWorkC {
    uint32_t flags00;            /* +0x00 */
    uint32_t flags04;            /* +0x04 */
    uint8_t  unk08[0x5C - 8];
    int32_t  hit5C;              /* +0x5C hit kind */
    uint8_t  unk60[0x7C - 0x60];
    float    v7C[4];             /* +0x7C */
} RbhWorkC;
void  sub_00113AA0(void *p, RbhComp *act);
/* Work block of the enemy family at 0x00120000 (act+0x278), only the touched fields. */
typedef struct RbhWorkD {
    uint8_t  unk00[0xC];
    uint32_t flags0C;            /* +0x0C */
    uint8_t  unk10[0x198 - 0x10];
    int32_t  hit198;             /* +0x198 hit kind */
    uint8_t  unk19C[0x1B8 - 0x19C];
    float    v1B8[4];            /* +0x1B8 */
} RbhWorkD;
int  rbh_HitState12D6F0(void *p, RbhComp *act);
/* Work block of the enemy family at 0x0011E000 (act+0x278), only the touched fields. */
typedef struct RbhWorkE {
    uint32_t flags00;            /* +0x000 */
    uint32_t flags04;            /* +0x004 */
    uint8_t  unk08[0x1D8 - 8];
    float    f1D8;               /* +0x1D8 */
    uint8_t  unk1DC[0x348 - 0x1DC];
    int32_t  hit348;             /* +0x348 hit kind */
    uint8_t  unk34C[4];
    int32_t  i350;               /* +0x350 */
    uint8_t  unk354[0x368 - 0x354];
    float    v368[4];            /* +0x368 */
} RbhWorkE;
/* Work block of the enemy family at 0x00180000 (act+0x278), only the touched fields. */
typedef struct RbhWorkF {
    uint8_t  unk00[0x18];
    uint32_t flags18;            /* +0x18 */
    uint8_t  unk1C[0x40 - 0x1C];
    int32_t  hit40;              /* +0x40 hit kind */
    uint8_t  unk44[0x60 - 0x44];
    float    v60[4];             /* +0x60 */
} RbhWorkF;
int  rbh_HitState185680(RbhComp *act);
/* Work block of the enemy family at 0x00140000 (act+0x278), only the touched fields. */
typedef struct RbhWorkG {
    uint32_t flags00;            /* +0x00 */
    uint32_t flags04;            /* +0x04 */
    uint8_t  unk08[0x14 - 8];
    int32_t  t14;                /* +0x14 frames */
    float    f18;                /* +0x18 */
    uint8_t  unk1C[0x24 - 0x1C];
    int32_t  n24;                /* +0x24 counter */
} RbhWorkG;
void  sub_00140200(void *obj, RbhComp *act);          /* regargs: obj=ESI act=EDI */
int   r3_SpawnCharge13D380(void *act, void *obj);     /* regargs: act=EDI obj=EBX */
int   sub_001C7EE1(void);                             /* rand */
int  rbh_EnemyStart140370(void *obj, RbhComp *act, int kind);

/* ------------------------------------------------------------ Jack's actor (b10_scr) */
typedef struct RbhModel { uint8_t unk00[8]; int32_t kind08; } RbhModel;
typedef struct RbhBody {
    uint8_t   unk00[0x30];
    RbhModel *model30;           /* +0x30 */
    uint8_t   unk34[0x54 - 0x34];
    float     yaw54;             /* +0x54 */
} RbhBody;
typedef struct RbhObj { uint8_t unk00[0x60]; float pos60[4]; } RbhObj;
/* 0x54-byte attachment records at scr+0x12C; scr+0x1C4 (the hit flag) falls at +0x44 of the
   second one. */
typedef struct RbhHand {
    RbhObj  *obj;                /* +0x00 */
    uint8_t  unk04[0x44 - 4];
    int32_t  hit44;              /* +0x44 (record 1 only: scr+0x1C4 hit flag) */
    uint8_t  unk48[0x54 - 0x48];
} RbhHand;
typedef struct RbhScr {
    uint8_t  unk000[0x68];
    float    f68;                /* +0x068 */
    int32_t  state6C;            /* +0x06C */
    uint8_t  unk070[0x8C - 0x70];
    RbhBody *body8C;             /* +0x08C */
    uint8_t  unk090[0x12C - 0x90];
    RbhHand  hands12C[2];        /* +0x12C */
} RbhScr;
extern RbhScr *b10_scr;                                /* 0x003F6130 */
typedef struct RbhSphere { float c[4]; float r; } RbhSphere;
int   sub_000F6A80(void);
int   r2d_ScnInWindow(void);                           /* 0x00102F40 */
void  r4e_VecAdd4(float *dst, const float *a, const float *b); /* vector add */
int   sub_000F61D0(RbhBody *b, RbhSphere *s, int mask, float *hit); /* -1 when no hit */
extern const float rbh_ofs278EB0[2][4];                /* 0x00278EB0 hand offsets */

/* ------------------------------------------------------------ mode words (0x003EDB60) */
typedef struct RbhModes {
    uint8_t  unk00[0x50];
    int32_t  alt50;              /* +0x50 (0x3EDBB0) */
    uint8_t  unk54[0x5C - 0x54];
    int32_t  pick5C;             /* +0x5C (0x3EDBBC) last pick */
    uint32_t used60[11];         /* +0x60 (0x3EDBC0) 10 used bits per word, values 0..109 */
} RbhModes;
extern RbhModes r2_modes3EDB60;                      /* 0x003EDB60 */
int   a5b_GetVideoMode(void);                        /* 0x000529F0 */

/* ------------------------------------------------------------ warp / room entry points */
typedef struct RbhWarpMap { int32_t chapter, stage, room; } RbhWarpMap;   /* 12 bytes */
typedef struct RbhEntry { int32_t id; float pos[4]; float yaw14; } RbhEntry; /* 0x18 bytes */
typedef struct RbhRoom { int32_t id; RbhEntry entries[30]; } RbhRoom;      /* 0x2D4 bytes */
extern RbhWarpMap rbh_warpMap301038[84];             /* 0x00301038, ends with chapter -1 */
extern RbhRoom    rbh_rooms301428[48];               /* 0x00301428, ends with id -1 */
extern int32_t    adc_var3EDCCC, adc_var3EDCD0;      /* pending room / entry, -2 locked */
extern int32_t    rbh_g3E14EC, rbh_g3E14F4;          /* 0x003E14EC, 0x003E14F4 */
/* View of g_stats with the movement fields this area touches. */
typedef struct RbhPlayer {
    uint8_t unk000[0xFC];
    float   angleFC;             /* +0x0FC */
    uint8_t unk100[0x108 - 0x100];
    float   angle108;            /* +0x108 */
    uint8_t unk10C[0x110 - 0x10C];
    float   v110[4];             /* +0x110 */
    uint8_t unk120[0x148 - 0x120];
    float   f148, f14C;          /* +0x148 */
} RbhPlayer;
#define RBH_PLAYER ((RbhPlayer *)&g_stats)
void  sub_000DFD40(int32_t *chapter, int32_t *stage);
void  r2d_PlayerPlace(void *p, const void *pos);     /* 0x000D1CA0 */
float r6c_AngleAdd(float a, float b);                /* 0x000829D0 wrapped sum */

/* ------------------------------------------------------------ effect objects (0x00100000) */
typedef struct RbhKindRec { uint8_t unk00[8]; int32_t kind08; } RbhKindRec;
/* Effect descriptor passed to the spawners. */
typedef struct RbhFxDesc {
    RbhKindRec *kind00;          /* +0x00 */
    float       f04;             /* +0x04 */
    int32_t     i08;             /* +0x08 1: register in ae0_obj3E1270 */
    int32_t     color0C;         /* +0x0C index into rbh_colors3196A0 */
} RbhFxDesc;
/* 0xFC-byte effect records behind b10_obj3F6150 (count sub_000F30E0(2)). */
typedef struct RbhFxRec {
    uint8_t     slot00[0x10];    /* +0x00 component slot (kind 5) */
    uint8_t     slot10[0x10];    /* +0x10 component slot (kind 0xD) */
    uint8_t     unk20[0x4C - 0x20];
    int32_t     used4C;          /* +0x4C */
    uint8_t     unk50[0x54 - 0x50];
    float       f54, f58;        /* +0x54 */
    uint8_t     unk5C[0x90 - 0x5C];
    RbhKindRec *kind90;          /* +0x90 */
    uint8_t     unk94[0x9C - 0x94];
    int32_t     mode9C;          /* +0x9C */
    int32_t     iA0, iA4;        /* +0xA0 */
    uint8_t     unkA8[0xFC - 0xA8];
} RbhFxRec;
typedef struct RbhRenderC4 { uint8_t unk00[0xDC]; float vDC[4]; } RbhRenderC4;
typedef struct RbhRender { uint8_t unk00[0xC4]; RbhRenderC4 *pC4; } RbhRender;
typedef struct RbhModelNode { uint8_t unk00[0x20]; RbhRender *r20; } RbhModelNode;
/* Scene object (0x150-byte records), only the touched fields. */
typedef struct RbhSceneObj {
    uint8_t       unk000[0x3C];
    RbhModelNode *node3C;        /* +0x03C */
    uint8_t       unk040[0x50 - 0x40];
    float         v50[4];        /* +0x050 direction */
    float         pos60[4];      /* +0x060 */
    uint8_t       unk070[0x14C - 0x70];
    int32_t       res14C;        /* +0x14C */
} RbhSceneObj;
extern RbhFxRec *b10_obj3F6150;                      /* 0x003F6150 */
extern void     *r3_ctx42C8E4;                       /* 0x0042C8E4 scene context */
extern uint8_t   ae0_obj3E1270[];                    /* 0x003E1270 */
extern const float rbh_colors3196A0[][4];            /* 0x003196A0 */
void  sub_0001D8B0(void *slot, int kind);
void  sub_0001D8D0(RbhSceneObj *o, void *slot);
void  sub_0001E9B0(void *scene, void *o, int a, int b, int c);
void  sub_0001EBF0(RbhSceneObj *o, int a);
void  sub_000192B0(void *list, RbhSceneObj *o);
void  sub_0010A7A0(RbhSceneObj *o);                  /* regargs: o=ESI */

/* ------------------------------------------------------------ enemy family at 0x00130000 */
typedef struct RbhAnimClip { uint8_t unk00[0xC4]; float fC4; uint8_t unkC8[0xDC - 0xC8]; float fDC; } RbhAnimClip;
typedef struct RbhAnimPlayer { uint8_t unk00[0x14]; RbhAnimClip *clip14; } RbhAnimPlayer;
typedef struct RbhEnemy {
    uint8_t  unk00[0xC];
    uint32_t flags0C;            /* +0x0C */
    uint32_t flags10;            /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    union {
        void   *anim30;                       /* +0x30 animation handle */
        struct RbhAnimPlayer *player30;       /* +0x30 the same, as a pointer */
    };
    uint8_t  unk34[0x60 - 0x34];
    float    pos60[4];           /* +0x60 */
} RbhEnemy;
typedef struct RbhRec16 { uint8_t b[16]; } RbhRec16;
typedef int (*RbhDispFn)(RbhEnemy *obj, RbhComp *act, const RbhRec16 *rec);
extern RbhDispFn r3b_disp31CDFC[];                   /* 0x0031CDFC */
extern RbhRec16  r3b_recs279728[];                   /* 0x00279728 */
extern float     r3_frameUnits;                      /* 0x0042C858 */
extern float     a50_frameSeconds;                   /* 0x0042C85C */
int   r3b_Dispatch139B10(int k, RbhComp *act, RbhEnemy *obj); /* regargs: k=EAX act=EDX obj=stack */
void  sub_00113480(RbhComp *act, int ev);
void  rbh_Wait13CA10(RbhEnemy *obj, RbhComp *act);
typedef struct RbhEmit { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } RbhEmit;
void  rbh_Slam13C630(RbhEnemy *obj, RbhComp *act);
void  rbh_Rise13C7E0(RbhEnemy *obj, RbhComp *act);
void  rbh_Move11AEC0(RbhEnemy *obj, RbhComp *act);
RbhTarget *sub_000C7130(RbhEnemy *obj);
float r4_Distance(const float *a, const float *b);   /* 0x001B2730 */
float sub_001B2770(const float *a, const float *b);  /* distance on the ground plane */
float sub_001135C0(RbhEnemy *obj, RbhComp *act);
float sub_00113570(RbhEnemy *obj, RbhComp *act);
typedef struct RbhWorkH { uint32_t flags00, flags04; uint8_t unk08[0x14 - 8]; uint8_t list14[0x10]; } RbhWorkH;
RbhEmit *sub_00113400(RbhComp *act, int slot);
extern float b10_f3F7504;                            /* 0x003F7504 */
void  rbh_Wait13C4F0(RbhEnemy *obj, RbhComp *act);
void  rbh_Rise13BAF0(RbhEnemy *obj, RbhComp *act);
float sub_00113200(RbhEnemy *obj, const void *target);  /* angle to target */
float sub_001A3F30(float v);                         /* absolute value */
void  rbh_Idle13BDC0(RbhEnemy *obj, RbhComp *act);
void  sub_00113370(RbhComp *act, RbhEmit *e);
void  rbh_Walk13C0E0(RbhEnemy *obj, RbhComp *act);
void  rbh_Guard13C2D0(RbhEnemy *obj, RbhComp *act);

/* ------------------------------------------------------------ recovered */
RbhSceneObj *rbh_FxAttach10C6B0(RbhSceneObj *obj, const float *pos, const float *dir,
                                const RbhFxDesc *d);
int  rbh_HitState1146D0(void *p, RbhComp *act);
void rbh_HandHit1051D0(void);
void rbh_EnterRoom0DDF40(void);
int rbh_CkptLoad0E70C0(int set);
void rbh_Recover13CD00(RbhEnemy *obj, RbhComp *act);

#endif
