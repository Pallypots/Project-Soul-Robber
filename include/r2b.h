#ifndef R2B_H
#define R2B_H
#include "oogie.h"
#include "r2.h"
#include "ad0.h"
/* Area r2b: functions in 0x000D0000..0x00130000 left over by earlier areas
   (stack and register arguments). All names inferred. Register mappings are in
   the comments and in config/function_states_r2b.csv. */

/* Jack's character object as used by the 0x000D0xxx helpers (layout of PlayerObj). */
typedef struct R2bModelNode R2bModelNode;
typedef struct R2bPlayer {
    uint8_t  unk000[0x128];
    int32_t  anim128;          /* +0x128 */
    uint8_t  unk12C[0x150 - 0x12C];
    int32_t  flags150;         /* +0x150 sign bit tested */
    uint8_t  unk154[0x1B8 - 0x154];
    int32_t  mode1B8;          /* +0x1B8 */
    uint8_t  unk1BC[0x604 - 0x1BC];
    void    *h604;             /* +0x604 effect handle */
    uint8_t  unk608[0xE04 - 0x608];
    int32_t  count_E04;        /* +0xE04 */
    uint8_t  unkE08[0xEF4 - 0xE08];
    int32_t  hEF4;             /* +0xEF4 */
    uint8_t  unkEF8[0xFD8 - 0xEF8];
    R2bModelNode *modelFD8;    /* +0xFD8 */
} R2bPlayer;
/* Model node: +0x0C flags, +0x20 render data, +0x3C next sibling. */
typedef struct R2bRender { uint8_t unk00[0xD0]; uint32_t colD0[4]; } R2bRender;
struct R2bModelNode {
    uint8_t   unk00[0xC];
    uint32_t  flags0C;         /* +0x0C */
    uint8_t   unk10[0x20 - 0x10];
    R2bRender *rend20;         /* +0x20 */
    uint8_t   unk24[0x30 - 0x24];
    R2Part   *part30;          /* +0x30 */
    uint8_t   unk34[0x3C - 0x34];
    R2bModelNode *next3C;      /* +0x3C */
};
typedef struct R2bCtx54 {
    uint8_t unk000[0x54];
    void   *p54;               /* +0x054 */
    uint8_t unk058[0x1EC - 0x58];
    void   *p1EC;              /* +0x1EC */
    void   *p1F0;              /* +0x1F0 */
} R2bCtx54;

/* Globals */
extern int32_t   r2b_g41FFA0;          /* 0x0041FFA0 (g_stats + 0xE0) */
extern R2bCtx54 *r2b_ctx42C8E4;        /* 0x0042C8E4 */

/* External callees */
void  r1_ChildHide(void *model, int id);                      /* 0x0001D4B0 */
void  r1_ChildShow(void *model, int id);                      /* 0x0001D470 */
void *adc_StatD0030(void *p, int v);                          /* 0x000D0030 */
void  b16_Free33A40(void *h);                                   /* 0x00033A40 */
void *r1b_Pool80970(void);                                    /* 0x00080970 */
int   sub_000D9A70(int id);
void *sub_0001D290(void *o, int k);
void  sub_000CED50(void *p);
void  sub_000822D0(void *ctx, void *pool, const float *pos, float r, void *list, void *out);
void  sub_000824F0(void *ctx, void *pool, const float *from, const float *to, void *list, void *out);
uint8_t *sub_00080CF0(void *pool, const float *pos);
uint8_t *sub_00080CB0(void *pool, const float *from, const float *to);

void  sub_0003C2D0(void *dst, void *rend, int id);
void  sub_000D2440(PlayerStats *s);
void  sub_000D1930(PlayerStats *s);
void  r1_NodeHide(void *n);                                   /* 0x0001D700 */
void  r4_HookRemoveA8(void *o, void *hook);                   /* 0x001B2190 */
void  sub_000BD4D0(void *s, int a);
extern uint32_t r2b_flags420010;       /* 0x00420010 (g_stats + 0x150) */
extern int32_t  r2b_g42007C;           /* 0x0042007C */
extern int32_t  r2b_g420080;           /* 0x00420080 */
extern void    *r2b_h4204D8;           /* 0x004204D8 handle */
extern void    *r2b_h4204DC;           /* 0x004204DC handle */
extern int32_t  r2b_g41FFEC;           /* 0x0041FFEC */
extern const int32_t r2b_ids2E7C80[4]; /* 0x002E7C80 */
extern const int32_t r2b_ids2E7D38[5]; /* 0x002E7D38 */
typedef struct R2bTex { uint8_t b[0xC0]; } R2bTex;
extern R2bTex r2b_tex417880[];         /* 0x00417880 */
typedef struct R2bHook3EDB40 { int32_t unk00; int32_t i04; int32_t unk08[2]; int32_t i10; } R2bHook3EDB40;
extern R2bHook3EDB40 r2b_hook3EDB40;   /* 0x003EDB40 */
typedef struct R2bA8 { uint8_t unk00[0xA8]; void *hookA8; } R2bA8;

void  sub_00022630(void *o, const char *path);
void *r1_StateNew(int a);                                     /* 0x0001D160 */
int   sub_000E0250(void);
void  sub_00048330(int h, int a);
int   sub_00048B20(int id, int a);
extern void *r2b_state42C8DC;          /* 0x0042C8DC */
extern void *r2b_g42C8D4;              /* 0x0042C8D4 */
extern const char r2b_str277288[];     /* 0x00277288 */
extern const int32_t r2b_tab2772F0[];  /* 0x002772F0 */
extern const int32_t r2b_tab300D80[];  /* 0x00300D80 */
/* Stage record table at 0x002E7D58 (0x314 bytes each, indexed by r2_modes3EDB60.unk08). */
typedef struct R2bStageEnt { uint8_t unk00[0xC]; int32_t kind0C; int32_t v10; int32_t unk14; } R2bStageEnt;
typedef struct R2bStage { uint32_t flags00; uint8_t unk04[0x10]; R2bStageEnt ent14[32]; } R2bStage;
extern const R2bStage r2b_stages2E7D58[]; /* 0x002E7D58 */

void  sub_000D9AB0(int id);
void  sub_000D9180(int k, void *a, int b);                    /* k=ECX */
void  sub_000D97B0(void *a);                                  /* a=ECX */
typedef struct R2bPair { int32_t a, b; } R2bPair;
extern R2bPair r2b_pairs3EDC14[];      /* 0x003EDC14 */
extern uint32_t r2b_bits3EDC38[32];    /* 0x003EDC38 (g_ad0_scriptVars) */

void  sub_00035A10(void *o, int i, int on);
void  sub_0005C580(void *o, int i, int on);
int   af0_GetVar3EE6AC(void);                                 /* 0x000DFDF0 */
extern const int32_t r2b_bits300F38[]; /* 0x00300F38 bits set at reset, -1 terminated */

void  sub_00049A40(int a, int b);
void  sub_00049B00(int a);
void  sub_0019FCF0(int a, int b, int c, int d, int e, int f);
void  sub_001A8A70(int a);
void  sub_000408D0(int a);
void  sub_0019D830(int a);
void  sub_0019D7F0(int a);
void  af0_SetVar3EDCC0(int v);                                /* 0x000DDE90 */
int   sub_00047BB0(void);
void  sub_00048A00(int a, int b);
int   sub_000EDA20(int a, int b);
int   sub_00060BD0(void);
void  sub_0019B9E0(void);
void  sub_0019B9F0(void);
void  sub_000325A0(int a);
int   sub_000869C0(void);
void  sub_00087450(void);
extern int32_t a9b_g413164;            /* 0x00413164 */
extern int32_t b3b_mode42CAFC;         /* 0x0042CAFC */
extern int32_t r2b_g3EDCB8;            /* 0x003EDCB8 */

int   sub_000DE100(int a, int b);
int   sub_000E0640(int a, float *b, float *c);
void  sub_000CC230(PlayerStats *s, int i, float *b, float *c);
void  sub_000DFD40(int *a, int *b);
int   r1_KeyStateW(int a, int b, int c);                      /* 0x00048820 */
int   r2b_AD090(int a, int b, int c);                         /* 0x000AD090 */
int   sub_000DEA20(int a);
int   a12_Level_37C544(void);                                 /* 0x00026660 */
int   a12_Level_37D434(void);                                 /* 0x00026680 */
int   a12_Level_37DAA4(void);                                 /* 0x000266A0 */
int   a12_Level_37DC28(void);                                 /* 0x000266C0 */
int   a12_Level_37DCFC(void);                                 /* 0x000266E0 */
int   a12_Level_37ED04(void);                                 /* 0x00026700 */
int   a12_Level_37E094(void);                                 /* 0x00026720 */
int   a12_Level_37EECC(void);                                 /* 0x00026740 */
int   a12_FlagBit0(void);                                     /* 0x00026760 */
int   a12_FlagBit1(void);                                     /* 0x00026770 */
int   sub_0019BE60(int k);
int   sub_0019BE70(int k);
void  sub_0019BE90(uint32_t v);
void  sub_0019BEB0(uint32_t v);

int   sub_000482B0(int h);
void  a60_PostCommand(int a, int b);                          /* 0x0006C1C0 */
void  sub_0019E870(int a);
int   sub_000DE4D0(int a, int b);
int   sub_0002C810(void);
int   af0_GetVar3EDCF8(void);                                 /* 0x000DE940 */
void  a5b_Swap2DD4D8(int a);                                  /* 0x0005BBB0 */
int   sub_00088150(void);
/* Script context with the cue handle word at +0x58. */
typedef struct R2bScriptCtx { ScriptCtx c; int32_t snd58; } R2bScriptCtx;

void  sub_000DE910(void);
void  sub_0019E8B0(int a, int b);
void  ac0_SetTarget(PlayerStats *s, int i, float *b, float *c); /* 0x000CBD20 */

void  sub_000E0380(void *o, int a, int b);
extern void *r2b_g417868;              /* 0x00417868 */
/* Script thread record (layout of AdcThread, 0x5C bytes). */
typedef struct R2bThread { uint8_t unk00[0x54]; uint16_t flags54; uint16_t pad56; int32_t unk58; } R2bThread;
extern int32_t   adc_threadCount;      /* 0x003EF030 */
extern R2bThread adc_threads[64];      /* 0x003EF034 */

extern void   *g_acb_table;           /* 0x003F0740 */
void  sub_0003FC10(void *rec);
int   sub_0003FA70(void *tbl, int b, int c, float d, float e);
void  sub_0003FCB0(void *rec, int item);
extern int32_t af0_var3F0734;          /* 0x003F0734 */
extern int32_t af0_var3F0738;          /* 0x003F0738 */
extern int32_t af0_var3F073C;          /* 0x003F073C */
void  sub_000DFF40(R2bThread *t);                             /* t=ESI */
void  sub_000D75E0(void);
void  sub_000D7C10(void);
void  sub_000D8820(void);

int   a6b_Printf3(char *buf, int size, const char *fmt, ...);  /* 0x0007E070 */
extern const char *r2b_names317CD0[];  /* 0x00317CD0 */
extern const char r2b_str317CBC[];     /* 0x00317CBC */
extern const char r2b_fmt27772C[];     /* 0x0027772C */
int   sub_0004F4D0(void);
int   sub_0004F6D0(int id);
int   sub_0004F680(int id);
void *sub_00053820(int pool, int size, int a, int b);
void  sub_0004FA70(int id, void *p);
void  sub_0004F4E0(void);
typedef struct R2bLoader { uint8_t unk00[8]; int32_t loaded08; } R2bLoader;
/* Timed item list: items of a variable stride, each starting with a position. */
typedef struct R2bTimed { uint32_t pos00; int16_t len04; uint16_t on06; } R2bTimed;
typedef struct R2bTrack { uint32_t unk00; uint32_t count04; uint32_t stride08; uint8_t *items0C; uint32_t unk10; } R2bTrack;
typedef struct R2bTracks { uint8_t unk00[0xC]; R2bTrack tr0C[1]; } R2bTracks;

extern void   *r2b_g3F1B1C;           /* 0x003F1B1C */
extern uint8_t aec_413140;             /* 0x00413140 */
extern int32_t aec_3F0A84;             /* 0x003F0A84 */
extern uint8_t aec_3F118C[];           /* 0x003F118C */

/* r2b_1 */
void *r2b_PickTargetB(const R2Cond *c, R2Ctx *ctx, void *self); /* 0x0011EE30 c=EAX ctx=ECX */
void r2b_PlayerShowModel(void);                               /* 0x000D0000 */
void r2b_ModelSetColor(R2bModelNode *n, const uint32_t *col); /* 0x000D04E0 */
void r2b_ShowChild(R2bPlayer *p, int show, int id);           /* 0x000D0530 */
void r2b_SetChildAnim(R2bPlayer *p, int anim, int key);       /* 0x000D0560 */
void r2b_UpdateEffect604(R2bPlayer *p);                       /* 0x000D0850 */
int  r2b_CheckE04(R2bPlayer *p, int any);                     /* 0x000D08F0 */
int  r2b_PoolGetA(const float *pos, float r, void *dst40, void *dst30);        /* 0x000D0DC0 */
int  r2b_PoolGetB(const float *from, const float *to, void *dst40, void *dst30); /* 0x000D0E30 */
void r2b_LoadTexA(R2bPlayer *p);                              /* 0x000D1670 */
void r2b_LoadTexB(R2bPlayer *p);                              /* 0x000D1700 */
void r2b_ClearEffects(void);                                  /* 0x000D2180 */
int  r2b_SetMode(int mode);                                   /* 0x000D2A00 */
/* r2b_2 */
void r2b_PlayerReset(void);                                   /* 0x000D34E0 */
void r2b_HookStop(int a, int unused, R2bA8 *o);               /* 0x000D4560 */
void r2b_SetFlagByKind(uint32_t *p, int k);                  /* 0x000D51C0 */
void r2b_Set42C8ECTop(int on);                                /* 0x000D5620 */
void r2b_Set42C8ECBit2(void);                                 /* 0x000D5650 */
void r2b_LoadShadow(uint8_t *o, const char *path);            /* 0x000D5660 */
int  r2b_TakeButtons(uint16_t b);                             /* 0x000D7090 b=EAX */
int  r2b_GetMode0(void);                                      /* 0x000D71E0 */
int  r2b_StageEntryId(void);                                  /* 0x000D71F0 */
int  r2b_StageRunLength(void);                                /* 0x000D7240 */
int  r2b_GetModeA8(void);                                     /* 0x000D74D0 */
int  r2b_CheckStep(void);                                     /* 0x000D74E0 */
void r2b_PlayCue(int id);                                     /* 0x000D7510 */
void r2b_StopCue(void);                                       /* 0x000D7570 */
void r2b_ResetModesD(void);                                   /* 0x000D7590 */
int  r2b_StageFlag200(void);                                  /* 0x000D7BF0 */
/* r2b_3 */
int  r2b_PairA(int i);                                        /* 0x000D8FF0 */
int  r2b_PairB(int i);                                        /* 0x000D9000 */
int  r2b_GetBlkI10(void);                                     /* 0x000D9010 */
void r2b_BlkFromPlayer(void);                                 /* 0x000D9020 */
void r2b_BlkSetup(void *a, int b);                            /* 0x000D9A30 */
int  r2b_TestBit(int i);                                      /* 0x000D9A70 */
void r2b_SetBit(int i);                                       /* 0x000D9AB0 */
void r2b_ClearBit(int i);                                     /* 0x000D9B30 */
int  r2b_OpJumpIfBit(ScriptCtx *c);                           /* 0x000D9F40 */
int  r2b_OpSetBit(ScriptCtx *c);                              /* 0x000D9FA0 */
int  r2b_OpWaitVar5(void);                                    /* 0x000DA3B0 */
int  r2b_OpStatMove(ScriptCtx *c);                            /* 0x000DA580 */
int  r2b_OpJumpIfStat(ScriptCtx *c);                          /* 0x000DA5D0 */
int  r2b_OpMusic(ScriptCtx *c);                               /* 0x000DA420 */
int  r2b_OpSetLevels(ScriptCtx *c);                           /* 0x000DA640 */
int  r2b_OpChapter(ScriptCtx *c);                             /* 0x000DA6D0 */
int  r2b_OpVoice(ScriptCtx *c);                               /* 0x000DA950 */
int  r2b_OpJumpIfNotEDA20(ScriptCtx *c);                      /* 0x000DAB20 */
int  r2b_OpJumpIf60BD0(ScriptCtx *c);                         /* 0x000DADC0 */
int  r2b_OpWait869C0(void);                                   /* 0x000DAF40 */
int  r2b_OpJumpIfPlayer(ScriptCtx *c);                        /* 0x000DB3B0 */
int  r2b_OpStatCC230(ScriptCtx *c);                           /* 0x000DB460 */
int  r2b_OpWaitKey(void);                                     /* 0x000DB860 */
int  r2b_OpWaitAD090(void);                                   /* 0x000DB9F0 */
int  r2b_OpJumpIfDEA20(ScriptCtx *c);                         /* 0x000DBDC0 */
int  r2b_OpWaitLevel(ScriptCtx *c);                           /* 0x000DC0D0 */
int  r2b_OpJumpIfChapter(ScriptCtx *c);                       /* 0x000DC3C0 */
int  r2b_OpJumpIfNot19BE60(ScriptCtx *c);                     /* 0x000DC500 */
int  r2b_OpJumpIfNot19BE70(ScriptCtx *c);                     /* 0x000DC550 */
int  r2b_OpSet19BE90(ScriptCtx *c);                           /* 0x000DC5A0 */
int  r2b_OpStopCues(R2bScriptCtx *s);                         /* 0x000DCD20 */
int  r2b_OpJumpIfCueDone(R2bScriptCtx *s);                    /* 0x000DCD50 */
int  r2b_OpPostCmd(ScriptCtx *c);                             /* 0x000DCDB0 */
int  r2b_OpJumpIfDE4D0(ScriptCtx *c);                         /* 0x000DCDE0 */
int  r2b_OpJumpUnlessVar5(ScriptCtx *c);                      /* 0x000DD120 */
int  r2b_OpJumpUnlessArea(ScriptCtx *c);                      /* 0x000DD3F0 */
int  r2b_OpJumpIf88150(ScriptCtx *c);                         /* 0x000DDAC0 */
int  r2b_OpJumpIfStatCmp(ScriptCtx *c);                       /* 0x000DD250 */
int  r2b_OpJumpIfStatK(ScriptCtx *c);                         /* 0x000DD310 */
int  r2b_OpUi(ScriptCtx *c);                                  /* 0x000DD4B0 */
int  r2b_OpSetBitRange(ScriptCtx *c);                         /* 0x000DDA00 */
int  r2b_OpSetTarget(ScriptCtx *c);                           /* 0x000DDD00 */
/* r2b_5 */
void r2b_ApplyUnlocks(void);                                  /* 0x000DF830 */
void r2b_SuspendThreads(int keep);                            /* 0x000DFCC0 */
void r2b_RunThreads(void);                                    /* 0x000E0510 */
/* r2b_6 */
void r2b_TableSet(void *tbl, int b, int c, int idx);          /* 0x000E01D0 */
void r2b_ScriptTick(void);                                    /* 0x000E0570 */
int  r2b_MapKind(int k);                                      /* 0x000E0790 */
char *r2b_FormatName(char *buf, int kind, int a, int b, int c); /* 0x000E0870 */
int  r2b_LoadD9(R2bLoader *o);                                /* 0x000E08D0 */
void r2b_TrackMarkBefore(R2bTracks *o, int idx, uint32_t lim, uint32_t base); /* 0x000E0B70 */
R2bTimed *r2b_TrackFire(R2bTracks *o, int idx, uint32_t pos, uint32_t base); /* 0x000E0BD0 */
R2bTimed *r2b_TrackFind(R2bTracks *o, int idx, uint32_t pos, uint32_t base); /* 0x000E0C30 */
int  r2b_Wrap10(int v);                                       /* 0x000E0CD0 */
int  r2b_Wrap25(int v);                                       /* 0x000E0D30 */
void r2b_PlayHint(int b);                                     /* 0x000E0E40 */
#endif
