#ifndef RBG_H
#define RBG_H
#include "oogie.h"
#include "shared_decls.h"
/* oogie.h declares g_3EDB38 / g_3EDB3C. */

/* Area rbg: larger game functions in 0x000D0000..0x0018FFFF (enemy/boss states, script
   handlers, Jack's actions, effects). All names inferred. Register mappings are in the
   comments and in config/function_states_rbg.csv. */

/* Float to int truncation. The original inlines cvttss2si; the intrinsic is used only for the
   32-bit x86 comparison build (same as RFL_FTOI in rfl.h). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define RBG_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define RBG_FTOI(x) ((int)(x))
#endif

/* Zero n bytes the way the original's inlined memset does (dwords, then the remaining bytes).
   The intrinsics are used only for the 32-bit x86 comparison build; other targets use memset. */
#include <string.h>
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define RBG_ZERO(p, n) (__stosd((unsigned long *)(p), 0, (n) >> 2),                         __stosb((unsigned char *)(p) + ((n) & ~3u), 0, (n) & 3))
/* Copy n dwords the way the original's inlined struct copy does (rep movsd). */
#define RBG_COPYD(d, s, n) __movsd((unsigned long *)(d), (const unsigned long *)(s), (n))
#else
#define RBG_ZERO(p, n) memset((p), 0, (n))
#define RBG_COPYD(d, s, n) memcpy((d), (s), (n) * 4u)
#endif

/* Animation player behind model+0x30 (only the touched fields). */
typedef struct RbgAnimNode { uint8_t unk00[0x84]; int32_t i84, i88; } RbgAnimNode;
typedef struct RbgAnim {
    uint8_t      unk00[8];
    int32_t      i08;            /* +0x08 current entry, -1 none */
    uint8_t      unk0C[0x14 - 0x0C];
    RbgAnimNode *node14;         /* +0x14 */
    int32_t      i18;            /* +0x18 */
    void        *owner1C;        /* +0x1C */
} RbgAnim;
/* Jack's model object (g_stats.unkFD8), only the touched fields. */
typedef struct RbgModel {
    uint8_t  unk000[0x20];
    void    *i20;                /* +0x020 node (passed to 0x00083160/0x0007FD60) */
    uint8_t  unk024[0x30 - 0x24];
    RbgAnim *anim30;             /* +0x030 */
    void    *i34;                /* +0x034 list (passed to 0x0007FD30) */
    uint8_t  unk038[0x134 - 0x38];
    void    *h134;               /* +0x134 */
    uint8_t  unk138[0x13C - 0x138];
    void    *h13C;               /* +0x13C */
    uint8_t  unk140[0x14C - 0x140];
    int32_t  i14C;               /* +0x14C */
} RbgModel;
typedef struct RbgRenderC4 {
    uint8_t unk000[0x17C];
    int32_t i17C;                /* +0x17C */
    uint8_t unk180[0x1E4 - 0x180];
    float   v1E4[4];             /* +0x1E4 */
} RbgRenderC4;
/* Render block behind object+0x20 (only the touched fields). */
typedef struct RbgRender {
    uint8_t  unk00[0x30];
    float    v30[4];             /* +0x30 translation row */
    uint8_t  unk40[0xC4 - 0x40];
    struct RbgRenderC4 *pC4;     /* +0xC4 */
    uint8_t  unkC8[0xE8 - 0xC8];
    uint32_t flagsE8, iEC;       /* +0xE8 */
} RbgRender;
/* 0x150-byte object records (component tables). */
typedef struct RbgRec150 {
    uint8_t    unk00[8];
    int32_t    i08;              /* +0x08 */
    uint32_t   flags0C;          /* +0x0C bit 0: in use */
    uint32_t   flags10;          /* +0x10 */
    uint8_t    unk14[0x20 - 0x14];
    RbgRender *r20;              /* +0x20 */
    uint8_t    unk24[0x30 - 0x24];
    RbgAnim   *anim30;           /* +0x30 */
    uint8_t    unk34[0x3C - 0x34];
    struct RbgRec150 *next3C;    /* +0x3C child chain */
    uint8_t    unk40[0x50 - 0x40];
    float      v50[4];           /* +0x50 direction */
    float      pos60[4];         /* +0x60 */
    float      v70[4];           /* +0x70 */
    uint8_t    unk80[0xA0 - 0x80];
    uint32_t   bA0[14];          /* +0xA0 */
    uint32_t   bD8[8];           /* +0xD8 */
    uint32_t   bF8[11];          /* +0xF8 */
    uint8_t    unk124[4];
    uint32_t   flags128;         /* +0x128 */
    uint8_t    unk12C[0x134 - 0x12C];
    void      *h134;             /* +0x134 */
    uint8_t    unk138[4];
    void      *h13C;             /* +0x13C */
    uint8_t    unk140[0x14C - 0x140];
    int32_t    i14C;             /* +0x14C */
} RbgRec150;
typedef struct RbgTbl { int32_t unk00, unk04; RbgRec150 *recs08; } RbgTbl;
typedef void (*RbgFn)();   /* callback slot; callees take varying arguments */
typedef struct RbgComp {
    uint8_t  unk00[0x20];
    uint32_t flags20;            /* +0x20 */
    RbgFn    fn24, fn28, fn2C;   /* +0x24 callbacks */
    int32_t  i30;                /* +0x30 */
    uint8_t  unk34[0x4C - 0x34];
    uint32_t flags4C;            /* +0x4C */
    int32_t  i50;                /* +0x50 */
    uint8_t  unk54[4];
    int32_t  i58;                /* +0x58 */
    float    f5C;                /* +0x5C */
    uint8_t  unk60[0x6C - 0x60];
    union { int32_t kind6C; int32_t snd6C; }; /* +0x6C mode, or a sound handle */
    void    *p70;                /* +0x70 */
    float    f74;                /* +0x74 timer */
    uint8_t  unk78[0x88 - 0x78];
    float    v88[4];             /* +0x88 velocity */
    uint8_t  unk98[0xB0 - 0x98];
    RbgFn    fnB0, fnB4, fnB8, fnBC, fnC0, fnC4; /* +0xB0 callbacks */
    int32_t  iC8, iCC;           /* +0xC8 */
    RbgFn    fnD0;               /* +0xD0 */
    uint8_t  unkD4[0x278 - 0xD4];
    struct RbgWork *work278;     /* +0x278 actor work block */
} RbgComp;
/* Actor work block (act+0x278), only the touched fields. */
typedef struct RbgWork {
    uint32_t flags00;            /* +0x00 */
    uint32_t flags04;            /* +0x04 */
    uint8_t  unk08[0x34 - 8];
    void    *refs34[3];          /* +0x34 held references */
    uint8_t  unk40[0x50 - 0x40];
    uint32_t flags50;            /* +0x50 */
    int32_t  anim54;             /* +0x54 pending reaction */
    uint8_t  unk58[0xDC - 0x58];
    float    fDC;                /* +0xDC */
    uint8_t  unkE0[0x1BC - 0xE0];
    int32_t  hit1BC;             /* +0x1BC hit kind */
    uint8_t  unk1C0[4];
    int32_t  i1C4;               /* +0x1C4 */
    uint8_t  unk1C8[0x1DC - 0x1C8];
    float    v1DC[4];            /* +0x1DC */
} RbgWork;
typedef struct RbgNode { uint8_t unk00[0x10]; int32_t i10, i14; } RbgNode;
/* Jack's character object (g_stats, 0x0041FEC0); a separate view with the fields used here. */
typedef struct RbgJack {
    uint8_t   unk000[0xD4];
    int32_t   iD4;               /* +0x0D4 */
    uint8_t   unkD8[0xE0 - 0xD8];
    int32_t   iE0;               /* +0x0E0 */
    uint8_t   unkE4[4];
    float     fE8;               /* +0x0E8 */
    uint8_t   unkEC[0x128 - 0xEC];
    int32_t   anim128, anim12C;  /* +0x128 */
    uint8_t   unk130[0x1B8 - 0x130];
    int32_t   i1B8;              /* +0x1B8 */
    uint8_t   unk1BC[0xEF4 - 0x1BC];
    RbgAnim  *danceEF4;          /* +0xEF4 dance script animation */
    uint8_t   unkEF8[0xFD0 - 0xEF8];
    void     *sceneFD0;          /* +0xFD0 */
    RbgTbl   *tblFD4;            /* +0xFD4 */
    RbgModel *modelFD8;          /* +0xFD8 */
} RbgJack;
typedef struct RbgCtx { uint8_t unk000[0x2D0]; RbgAnim *anim2D0; } RbgCtx;

/* ---- 0x000D00B0: Mayor dance script loader */
extern const char rbg_sDance00[], rbg_sDance01[], rbg_sDance02[], rbg_sDance03[],
                  rbg_sDance04[], rbg_sDance05[];                   /* 0x002771FC.. dance script paths */
extern const char rbg_sJkMngSub[];                                  /* 0x00277130 source file name */
extern RbgCtx *abc_p42C8E0;                                         /* 0x0042C8E0 */
void  sub_0004F700(int movie);
void *sub_00053BC0(const char *file, int line);
int  *sub_00083140(RbgAnim *h, int a);
void  sub_000831A0(RbgAnim *h, int a, int v);
void  sub_0004F720(void);
void  sub_00053BE0(void);

/* ---- 0x000D0200 */
void  sub_0001E9B0(void *scene, void *o, int a, int b, int c);
void  sub_001B1190(RbgAnimNode *n, float t);
typedef struct RbgAnimEnt { uint8_t unk00[8]; uint8_t b08; uint8_t unk09[3]; void *i0C; float f10; int32_t unk14, i18; } RbgAnimEnt;   /* i0C: motion data pointer (0x001AEBF0 derefs +8) */


/* ---- 0x000D2A50 */
void  PlayerObj_ClearFlags(PlayerObj *p, uint32_t lo, uint32_t hi); /* 0x000CF3F0 */
void  PlayerObj_SetAnim(PlayerObj *p, int anim);                    /* 0x000CF490 */
void  sub_000243B0(int a, int b);
void  sub_000D1930(PlayerStats *p);
void  sub_000C5B10(void);
void  sub_000D4C10(uint8_t *rig);
void  sub_000BC6F0(const char *name, int on);
extern const char rbg_s276DBC[];                                    /* 0x00276DBC */

/* ---- 0x000D72B0 */
typedef struct RbgStage { uint32_t flags00; int32_t i04; uint8_t unk08[0x314 - 8]; } RbgStage;
extern const RbgStage r2b_stages2E7D58[];                           /* 0x002E7D58 stage records */
typedef struct RbgModes { int32_t i00, i04, stage08; } RbgModes;
extern RbgModes r2_modes3EDB60;                                     /* 0x003EDB60 (area r2) */
extern int32_t  rbg_g41786C;                                        /* 0x0041786C menu handle */
void  sub_000DFD60(int h, int a, int b);
int   sub_000D9A70(int bit);                                        /* test event bit */
void  sub_000DFDB0(int h, int item, int b);

/* ---- 0x000E1350 */
typedef struct RbgPair { RbgRec150 *a, *b; int32_t v; } RbgPair;
typedef struct RbgPairOwner {
    uint8_t  unk000[0x520];
    int32_t  active520;          /* +0x520 */
    RbgTbl  *tblA524, *tblB528;  /* +0x524 */
    void    *resA52C, *resB530;  /* +0x52C */
    RbgPair  pairs534[1];        /* +0x534 12-byte slots (count not measured) */
} RbgPairOwner;
extern void *r3_ctx42C8E4;                                          /* 0x0042C8E4 scene context */
extern const float rbg_v3F1B44[4];                                  /* 0x003F1B44 */
void  sub_0001EBF0(RbgRec150 *o, int a);

/* ---- 0x000DE6D0 */
extern int32_t adc_var3EDCF4;                                       /* 0x003EDCF4 */
extern int32_t adc_30D6B8;                                          /* 0x0030D6B8 last unlocked item, -1 none */
extern const int32_t rbg_bits30C238[];                              /* 0x0030C238 bit index per item */
void  sub_000252A0(int a, int b);

/* ---- 0x000E3820: image layers of a menu page */
typedef struct RbgImgHdr { uint8_t unk00[8]; int32_t v08; uint16_t w0C, w0E; uint8_t data10[1]; } RbgImgHdr;
typedef struct RbgLayer { int32_t n00, v04, w08; uint8_t *data0C; void *cur10; } RbgLayer; /* also a timeline track (cur10 = cursor) */
typedef struct RbgImgSet { RbgImgHdr *hdr; uint8_t unk04[0x40 - 4]; } RbgImgSet;
typedef struct RbgPage {
    int32_t    id00;             /* +0x000 */
    uint8_t    unk004[0x0C - 4];
    RbgLayer   layers0C[8];      /* +0x00C */
    RbgImgHdr *srcAC[4];         /* +0x0AC */
    RbgImgSet  setsBC[8];        /* +0x0BC selectable sets */
    RbgImgHdr *src2BC[3];        /* +0x2BC */
    int32_t    vals2C8[8];       /* +0x2C8 value per set */
    int32_t    res2E8;           /* +0x2E8 */
    int32_t    snd2EC;           /* +0x2EC sound id, < 0 none */
    uint32_t   len2F0;           /* +0x2F0 */
    uint8_t    b2F4;             /* +0x2F4 bit 0: no loop */
    uint8_t    unk2F5[3];
    int32_t    started2F8;       /* +0x2F8 */
    int32_t    strm2FC;          /* +0x2FC stream */
    uint8_t    unk300[0x310 - 0x300];
    int32_t    hidden310;        /* +0x310 */
    int32_t    sel314;           /* +0x314 selected set, -1 none */
    int32_t    i318;             /* +0x318 */
    int32_t    rec31C;           /* +0x31C */
    int32_t    on320;            /* +0x320 */
    int32_t    mode324;          /* +0x324 */
    int32_t    done328;          /* +0x328 */
    uint8_t    unk32C[0x408 - 0x32C];
    int32_t    active408;        /* +0x408 */
    int32_t    pos40C, end410;   /* +0x40C */
    uint8_t    unk414[0x430 - 0x414];
    struct { int32_t on00; uint8_t unk04[0x14 - 4]; int32_t fx14; uint8_t unk18[4]; } fx430[8]; /* +0x430 */
} RbgPage;
extern int32_t rbg_g3F1B1C;                                         /* 0x003F1B1C */

/* ---- 0x000E2E70 */
extern const uint32_t rbg_len317B64[];                              /* 0x00317B64 length per page id */
void *r2b_TrackFire(RbgPage *o, int idx, uint32_t pos, uint32_t base);       /* 0x000E0BD0 */
void  r2b_TrackMarkBefore(RbgPage *o, int idx, uint32_t lim, uint32_t base); /* 0x000E0B70 */
void  sub_0019AB40(int snd);
void  sub_0019AAC0(int snd, int loop);
void  sub_00053F70(uint32_t t);
void  sub_00054010(void);
int   sub_0019A900(int strm);
void  sub_000580D0(void);
int   sub_0019ADE0(int kind);
int   sub_0019AD10(int kind, int i);
void  sub_0019AC20(int strm, int i, int v);

/* ---- 0x000F0430 */
void  sub_000E1040(RbgRec150 *o);
void  sub_000E1060(RbgRec150 *o, int anim, int a, int b);
void  sub_000F3D10(RbgRec150 *o, RbgComp *c, int k);

/* ---- 0x000F3DA0 */
int   sub_000F3140(int key);
int   sub_00082FC0(RbgAnimEnt *e, int entry);
void  sub_001AEFD0(RbgAnimNode *n, void *anim, int mask, int t);
void  sub_00082F90(RbgAnim *a, RbgAnimEnt *e);

/* ---- 0x000FB580 */

/* ---- 0x000F1EF0: boss finish sequence */
typedef struct RbgScore { uint8_t unk000[0x2F0]; int32_t score2F0; } RbgScore;
typedef struct RbgSeq {
    uint8_t   unk000[0x64];
    RbgScore *p64;               /* +0x064 */
    uint8_t   unk068[0x104 - 0x68];
    int32_t   level104;          /* +0x104 1..6 */
    uint8_t   unk108[4];
    float     f10C;              /* +0x10C */
    int32_t   step110;           /* +0x110 */
} RbgSeq;
extern const float rbg_dmg278410[6];                                /* 0x00278410 100, 250 .. 1350 */
void  rbg_GroupAnim0F3DA0(RbgRec150 *g, int anim, int ms, int mode);
void  r2d_SwitchOn(void *o);                                        /* 0x000EF930 regargs: o=EBX */
void  r2d_SwitchOff(void *o);                                       /* 0x000EF9B0 regargs: o=EBX */
void  r2c_SetEffectD4(RbgRec150 *o, int kind);                      /* 0x000F0B10 regargs: o=EDI */
void  r2c_SetSoundD8(RbgRec150 *o, int id, int c);                  /* 0x000F0B70 regargs: o=ESI */
void  r2_Comp5FreeD4(RbgRec150 *o);                                 /* 0x000EF8A0 regargs: o=EAX */
void  r2_Comp5ReleaseD8(RbgRec150 *o);                              /* 0x000EF8D0 regargs: o=EAX */
void  r2_ActorCallComp5(RbgRec150 *o, int arg);                     /* 0x000EEF90 regargs: o=ESI */
void  sub_000F0C80(RbgRec150 *o, RbgSeq *s);
void  sub_000F0D80(RbgRec150 *o, RbgSeq *s);

/* ---- 0x000E63A0: stage mode change */
typedef void (*RbgModeFn)(void *h, int mode, int old);
typedef struct RbgScene { uint8_t unk000[0x1E8]; void *recs1E8; } RbgScene;
extern RbgPage r2e_stage3F0758;                                     /* 0x003F0758 current stage */
extern const RbgModeFn rbg_modeFn317C7C[];                          /* 0x00317C7C per stage id */
extern const int32_t rbg_i317BB8[];                                 /* 0x00317BB8 per stage id */
extern uint8_t ae0_obj3E1270[];                                     /* 0x003E1270 */
extern uint8_t aa0_enabled413142;                                   /* 0x00413142 */
void  PlayerObj_SetFlags(PlayerObj *p, uint32_t lo, uint32_t hi);   /* 0x000CF3C0 */
void  sub_000E3390(RbgPage *p);
void  sub_0019BEB0(int m);
int   sub_000E2420(RbgPage *p);
void *sub_0001D080(void *recs, int kind, int key);
void  sub_00019000(void *o, int a);
void  sub_0001AB00(void *o, int a, int b, int c, int d);
void  sub_000E5C30(RbgPage *p);
int sub_000E98E0(int fx, int a);
void  sub_0019BE90(int m);
void  sub_000E3BA0(RbgPage *p);
void  sub_00048330(int h, int a);
void  sub_0019AA00(int strm, int a);
void  sub_000CFF90(PlayerStats *p, int a, float t);
void  sub_000CEF00(void);
void  sub_000E0E40(int a);
void  sub_000253D0(int a, int b);
void  sub_000E8690(int a, int b);
void  sub_000E8920(int a, int b);
void  sub_000E89F0(int a, int b);
void  sub_000E8A50(int a, int b);
void  sub_000E16E0(RbgPage *p, int i, float t);
void  sub_000E19F0(RbgPage *p, float t);
void  sub_000C85C0(void);
void  sub_000A8B80(void);
void  sub_00049A40(int a, int b);

/* ---- 0x000E6D80: stage timeline update */
void *rbg_PageNext0E2E70(RbgPage *o, void *skip, uint32_t pos);    /* regargs: o=ESI skip=EAX pos=ECX */
void  sub_000E3C90(RbgPage *p);
int   PlayerObj_GetState(PlayerObj *p);                             /* 0x000CF4F0 */
void  r2c_FxResetAll(void);                                         /* 0x000E8530 */
void *sub_000E4DD0(RbgPage *p, void *prev, uint32_t pos);           /* regargs: pos=EAX */
void *sub_000E2C20(RbgPage *p, uint32_t pos);                       /* regargs: p=EDI */
void *sub_000E2C70(RbgPage *p, uint32_t pos);                       /* regargs: p=EDI */
void *sub_000E2CC0(RbgPage *p, uint32_t pos);                       /* regargs: p=EDI */
void *sub_000E2D10(RbgPage *p, uint32_t pos);                       /* regargs: p=EDI */
void  sub_000E6910(RbgPage *p);                                     /* regargs: p=ESI */
void  sub_000E26B0(RbgPage *p, uint32_t pos);                       /* regargs: p=ESI */
void  r2_SeqStep(RbgPage *p);                                       /* 0x000E48C0 regargs: p=ESI */
void  sub_000E4C00(RbgPage *p);                                     /* regargs: p=EBX */
void  sub_000EC730(void);
void  sub_000E4160(RbgPage *p);
void  sub_000E44E0(RbgPage *p);
void  sub_000E4A20(RbgPage *p);
void  sub_000E17A0(RbgPage *p);
void  sub_000E1A60(RbgPage *p);                                     /* regargs: p=EAX */
void  sub_000E1CD0(RbgPage *p);                                     /* regargs: p=ESI */
void *sub_000E4E90(RbgPage *p, uint32_t pos, void *prev, int key, int kind); /* regargs: key=EDI kind=EBX */
void *sub_000E2D60(RbgPage *p, uint32_t pos, void *prev);           /* regargs: p=ESI pos=EAX */

/* ---- 0x001089C0 / 0x0010C840 */
typedef struct RbgSlotE8 {
    uint8_t slot00[0x10];        /* +0x00 */
    uint8_t slot10[0x4C - 0x10]; /* +0x10 */
    void   *used4C;              /* +0x4C */
    uint8_t unk50[0x8C - 0x50];
    uint8_t bones8C[0xE8 - 0x8C];/* +0x8C */
} RbgSlotE8;
extern RbgSlotE8 *b10_obj3F6138;                                    /* 0x003F6138 */
extern uint8_t   *b10_obj3F6160;                                    /* 0x003F6160 */
int   sub_000F30E0(int k);                                          /* count */
void  sub_0001D8B0(void *slot, int kind);
void  sub_0001D8D0(RbgRec150 *o, void *slot);
void  sub_000362B0(RbgRec150 *o);
void  sub_00108790(RbgRec150 *o);
void  sub_000192B0(void *list, RbgRec150 *o);
void  sub_000ED4C0(int a);
void  sub_000ED5D0(int a);
int   sub_000ED520(int a, int b);

/* ---- 0x0015B6B0 / 0x0015BB20: reaction pickers */
int   r3_CheckConds1558F0(int table, void *a, void *b);             /* 0x001558F0 regargs: table=EAX a=EBX b=EDI */
void  sub_0015A270(RbgRec150 *obj, int anim, RbgComp *act);        /* regargs: act=ESI, obj and anim on the stack */

/* ---- 0x00182E50 */
extern int32_t b7c_count3FE374;                                     /* 0x003FE374 step */
RbgRec150 *sub_00181C20(int i);
RbgRec150 *sub_00181BE0(int i);
void  sub_00181CE0(int i, int a);
int   sub_00181D40(int a);
void  rtc_PairAnimA(int i, int anim);                               /* 0x00181CA0 */

/* ---- 0x001673E0: effect object spawn */
typedef int (*RbgInitFn)(RbgRec150 *o, RbgComp *c, int arg);
typedef struct RbgKind12 { int32_t id; void *p04; RbgInitFn init08; } RbgKind12;
extern RbgKind12  b4c_sndTab279924[4];                              /* 0x00279924 per kind */
extern int32_t   *b16_task3F8400;                                   /* 0x003F8400 template count */
extern RbgRec150 *b16_taskId3F8404;                                 /* 0x003F8404 templates */
extern int32_t   *r3d_i3F8408;                                      /* 0x003F8408 pool count */
extern RbgRec150 *b4c_objs3F840C;                                   /* 0x003F840C pool */
void  sub_0001D470(RbgRec150 *o, int k);
void  sub_000EE270(RbgComp *c);
void  sub_00166C90(void);
void  sub_00166CE0(void);
void  sub_00166D70(void);
void  sub_00166E20(void);

/* ---- 0x0013D4E0 */
int   sub_001C7EE1(void);                                           /* rand */

/* ---- 0x0016FE00 */
void  rbg_Rebuild16FE00(RbgRec150 *o, const void *tmpl);            /* regargs: o=EBX */

/* ---- 0x0013BF80: condition records and dispatchers (named in area r3b) */
typedef struct RbgRec16 { int32_t i[4]; } RbgRec16;
typedef int (*RbgDispFn)(void *obj, void *act, RbgRec16 *rec);
extern RbgRec16  r3b_recs279728[];                                  /* 0x00279728 */
extern RbgDispFn r3b_disp31CDFC[];                                  /* 0x0031CDFC */
extern float     r3e_frameSeconds;                                  /* 0x0042C85C */
int   r3b_Dispatch139B10(int k, void *act, void *obj);              /* 0x00139B10 regargs: k=EAX act=EDX obj=stack */

/* ---- 0x0013A670 */

/* ---- 0x0014E6B0 */
int   sub_00156040(void);
void  sub_001134B0(void *act);
void  sub_001561D0(RbgWork *w, float a, float b);
void  sub_00113AA0(void *obj, void *act);
void  sub_00048250(int h);
void  sub_00147580(RbgRec150 *obj, int anim, RbgComp *act);        /* regargs: anim=EBX act=ESI obj=stack */

/* ---- 0x0015A270: work block view of the second enemy family */
typedef struct RbgWorkB {
    uint32_t flags00;            /* +0x00 */
    float    f04, f08;           /* +0x04 settle speed and step */
    uint8_t  unk0C[0x40 - 0x0C];
    uint32_t flags40;            /* +0x40 */
    uint8_t  unk44[0xD8 - 0x44];
    float    fD8;                /* +0xD8 */
    uint8_t  unkDC[0x1B8 - 0xDC];
    int32_t  hit1B8;             /* +0x1B8 hit kind */
    uint8_t  unk1BC[4];
    int32_t  i1C0;               /* +0x1C0 */
    uint8_t  unk1C4[0x1D8 - 0x1C4];
    float    v1D8[4];            /* +0x1D8 */
} RbgWorkB;

#endif
