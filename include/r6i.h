#ifndef R6I_H
#define R6I_H
#include "oogie.h"
#include "shared_decls.h"

/* Float to int truncation (copy of RFL_FTOI). The original inlines
   cvttss2si where the value is in an SSE register (modern cl calls
   __ftol2_sse instead); the intrinsic is used only for the 32-bit x86
   comparison build. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R6I_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R6I_FTOI(x) ((int)(x))
#endif
void  sub_000A2E10(int idx, int v);
void  sub_000A2E50(int idx, int v);
void  sub_000A4340(int idx, int v);
int   sub_000A4370(int idx);

/* ------------------------------------------------------------ room script 0xB89B0 */
extern uint8_t   ae0_obj3E1270[];         /* 0x003E1270 camera object */
void  sub_000A5450(int idx);
int   a80_AnyLowFlags(void);              /* 0x00087AF0 */
int   a80_ModeFlag1(void);                /* 0x00088170 */
void  sub_0019BE90(int id);
void  sub_0019BEB0(int id);
void  sub_000D1D00(PlayerStats *p);
void  sub_00019000(void *cam, int mode);
void  sub_0001AB00(void *cam, int a, int b, int c, int d);
void  sub_000A43C0(int idx, int v);
int   r2b_PairB(int i);                   /* 0x000D9000 */
void  a80_Set3ED23C(int v);               /* 0x00087520 */

/* ------------------------------------------------------------ switch room scripts (0xB95C0, 0xB97A0) */
extern uint64_t  a50_frameCounter0;       /* 0x0042C918 frame counter */
int   sub_000A2CE0(int idx, uint32_t mask);
void  sub_000CAE20(PlayerStats *p, float v);
int   r6b_Slot0Value110(void);            /* 0x00095300 */
void  sub_000D1930(PlayerStats *p);
void  sub_000DFD40(int32_t *chapter, int32_t *stage);

/* Area r6i: larger functions (300-2500 bytes) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6i.csv. Callees are declared under their sub_ name
   (or an existing name with the same VA) so that cl never inlines a function
   recovered in this area into another one. */

/* ------------------------------------------------------------ menu item availability (0x605B0) */
int  sub_000D9A70(int bit);               /* event flag bit test */
extern int32_t r6i_g413178;               /* 0x00413178 */

/* ------------------------------------------------------------ message page (0x61290) */
/* Menu block pointed to by 0x003E60CC (only touched fields). */
typedef struct R6iMenuBlk {
    uint8_t  unk000[0x968];
    uint8_t  snd968[4];       /* +0x968 sound object */
    int32_t  mode96C;         /* +0x96C */
    void    *text970;         /* +0x970 text handle */
} R6iMenuBlk;
typedef void (*R6iPageFn)(void);
extern R6iMenuBlk *a60_menu3E60CC;        /* 0x003E60CC */
extern int32_t   a60_state3E60D4;         /* 0x003E60D4 page */
extern int32_t   a60_v3E60D8;             /* 0x003E60D8 page step */
extern int32_t   a60_v3E60DC, a60_v3E60E0;
extern int32_t   r6i_next3E60E4[4];       /* 0x003E60E4 queued page, step, DC, E0 */
extern int16_t   a60_w3E60F8, a60_w3E60FA; /* list top, cursor */
extern uint8_t   r6i_alpha3E60FC;         /* 0x003E60FC fade alpha */
extern float     r6d_timer3E6100;         /* 0x003E6100 */
extern uint16_t  r6h_menuItems3E6104[];   /* 0x003E6104 */
extern int32_t   a60_res3E64BC;           /* 0x003E64BC */
extern uint32_t *r1e_padMasks2C4AE8;      /* 0x002C4AE8 */
extern R6iPageFn r6i_pageFns2DDAE0[];     /* 0x002DDAE0 */
uint32_t sub_0004ECD0(int pad);
uint32_t sub_0004ECF0(int pad);
uint32_t sub_0004ED00(int pad);
uint32_t sub_0004ED20(int pad);
uint32_t sub_0004ED40(int pad);
void  r6d_MenuShowText(int id);
void  a60_StepByFrame(float *v, int dir);
void  sub_0003FC40(void *snd);
void  a60_TextClear(void *t);

/* ------------------------------------------------------------ status page step (0x68740) */
/* Part of the work block at 0x0042C5E8 used by the status texts. */
/* Screen adjustment settings at 0x00413140 (16 bytes; also saved in the
   work block at +0xB7B80). */
typedef struct R6iScreenCfg {
    int32_t  a, b, c;         /* +0x0 */
    int16_t  x;               /* +0xC horizontal offset -75..75 */
    int16_t  xhi;             /* +0xE */
} R6iScreenCfg;
typedef struct R6iWork {
    uint8_t  unk00000[0xB7B80];
    R6iScreenCfg savedCfg;    /* +0xB7B80 */
    uint8_t  unkB7B90[0xF91E8 - 0xB7B90];
    uint8_t  anim[4];         /* +0xF91E8 sound/voice object */
    int32_t  mode;            /* +0xF91EC */
} R6iWork;
extern R6iWork  *a60_work42C5E8;          /* 0x0042C5E8 */
extern uint8_t   r6g_b428F80[8];          /* 0x00428F80 page, phase, step, flag, queued 4..7 */
extern int32_t   r6d_g428F8C;             /* 0x00428F8C selected icon slot */
extern float     r6i_timer428F94;         /* 0x00428F94 */
extern uint8_t   r6i_alpha428F98;         /* 0x00428F98 */
extern uint8_t   r6i_b428FA8;             /* 0x00428FA8 status entry */
extern float     r6i_f428FAC;             /* 0x00428FAC */
extern int32_t   r6i_g428FB0;             /* 0x00428FB0 picked icon id */
extern uint8_t   r6d_icons42970C[];       /* 0x0042970C */
extern int32_t   a60_res3E6540;           /* 0x003E6540 */
int   r6d_StatusIcon(int k);              /* 0x00065DB0, k in EDX */
void  r6d_StatusShowText(int i, int id);  /* 0x00065E50, i in ESI */
void  r6b_ReleaseRes3E6540(void);         /* 0x00065AC0 */
void  a60_InitRes65AA0(void);             /* 0x00065AA0 */
void  sub_00065A50(int id);
int   sub_00053C90(void);

/* ------------------------------------------------------------ manual pages (0x68A60) */
/* Texture set records at 0x002DDD50 (0x30 bytes each). */
typedef struct R6iTexSet {
    uint8_t  unk00[0x2C];
    uint32_t pages;           /* +0x2C number of pages */
} R6iTexSet;
extern R6iTexSet r6d_texSets[];           /* 0x002DDD50 */
extern int32_t   r6d_texSet3E6538;        /* 0x003E6538 */
extern int32_t   r6g_tex3E6528[4];        /* 0x003E6528 loaded textures */
extern uint32_t  r6i_page429704;          /* 0x00429704 current page */
extern uint8_t   r6i_alpha428F9A;         /* 0x00428F9A */
extern uint8_t   r6i_alpha428F9B;         /* 0x00428F9B */
extern uint8_t   r6i_obj4292C0[];         /* 0x004292C0 */
void  sub_00015070(void *obj);

/* ------------------------------------------------------------ results page (0x6A970) */
/* Sprite records at 0x0042983C (0x9C bytes each; only the flags are used). */
typedef struct R6iSpr {
    uint8_t  unk00[0x10];
    uint32_t flags;           /* +0x10 bit 0 hidden, bit 3 ... */
    uint8_t  unk14[0x9C - 0x14];
} R6iSpr;
extern R6iSpr    r6i_spr42983C[];         /* 0x0042983C */
extern float     r6i_f4297E8;             /* 0x004297E8 */
extern uint8_t   r6i_b4297EC, r6i_b4297ED;
extern int32_t   r6i_g4297FC;             /* 0x004297FC */
extern int32_t   r6i_g429814;             /* 0x00429814 */
extern float     r6i_f42981C;             /* 0x0042981C */
extern int16_t   r6i_w429820;             /* 0x00429820 */
extern int32_t   a60_val3E65FC;           /* 0x003E65FC */
extern int32_t   r6i_count3E6600;         /* 0x003E6600 rows shown */
extern float     r6i_timer3E6604;         /* 0x003E6604 */
extern int32_t   r6g_g428F20;             /* 0x00428F20 page phase */
extern uint8_t   a4c_obj428F40[];         /* 0x00428F40 fade timer object */
void  sub_00072F30(void *o, int kind, float t, uint32_t color, int z);

/* ------------------------------------------------------------ title texture release (0x6E490) */
extern int32_t   a60_h3E68B8[32];         /* 0x003E68B8 title texture handles */
extern int32_t   a60_h42C6F0;             /* 0x0042C6F0 title background texture */
extern float     r6i_f42906C, r6i_f429070;
/* Release a texture handle if one is held. */
#define R6I_RELEASE_TEX(h)              if ((h) != -1) {                        sub_001B9FC0(h);                    (h) = -1;                       }

/* ------------------------------------------------------------ title menu page (0x71230) */
extern float     r6i_timer42AC80;         /* 0x0042AC80 */
extern uint8_t   r6i_alpha42AC84;         /* 0x0042AC84 */
extern uint8_t   r6i_alpha42AC85;         /* 0x0042AC85 */
void  r6i_TitleReleaseTextures(void);     /* 0x0006E490 */
void  sub_0006DD40(void);

/* ------------------------------------------------------------ simple page (0x73FC0) */
extern float     r6i_timer42A828;         /* 0x0042A828 */
extern uint8_t   r6i_alpha42A82C;         /* 0x0042A82C */

/* ------------------------------------------------------------ screen adjust page (0x71940) */
extern R6iScreenCfg r6i_cfg413140;        /* 0x00413140 */
void  sub_001A76A0(int x);

/* ------------------------------------------------------------ title letter animation (0x6C3F0) */
typedef struct R6iVec2 { float x, y; } R6iVec2;
/* Title letter key pose (16 bytes): position and scale. Five letters per key
   at 0x0042C600. */
typedef struct R6iLetterKey {
    R6iVec2  pos;             /* +0x0 */
    R6iVec2  scl;             /* +0x8 */
} R6iLetterKey;
/* Bezier control points between key k and k+1 (two points per letter), five
   letters per key at 0x0042C700, indexed by key - 1. */
typedef struct R6iLetterCtl {
    R6iVec2  a;               /* +0x0 */
    R6iVec2  b;               /* +0x8 */
} R6iLetterCtl;
extern int32_t      r6e_g42C5D8;          /* 0x0042C5D8 mode: 1 forward, 2 back */
extern float        r6e_f42C5DC;          /* 0x0042C5DC timer (110 frames) */
extern int32_t      r6e_g42C5E0;          /* 0x0042C5E0 from key */
extern int32_t      r6e_g42C5E4;          /* 0x0042C5E4 to key */
extern R6iLetterKey r6i_keys42C600[][5];  /* 0x0042C600 */
extern R6iLetterCtl r6i_ctl42C700[][5];   /* 0x0042C700 */
extern R6iVec2      r6h_titlePos42C588[5];/* 0x0042C588 animated letter positions */
extern R6iVec2      r6h_titleScl42C5B0[5];/* 0x0042C5B0 animated letter scales */
float sub_001A3ED0(float x);
void  sub_00071FE0(const R6iVec2 *pts, float t, R6iVec2 *out);

/* ------------------------------------------------------------ results banner (0x6AB70) */
extern int32_t   r6i_g429800;             /* 0x00429800 banner state */
extern float     r6i_f429804;             /* 0x00429804 banner timer */
extern float     r6i_f429808, r6i_f42980C, r6i_f429810;

/* ------------------------------------------------------------ task list loader (0x8B9E0) */
/* Record table returned by the descriptor getters (0x24-byte entries; the
   size of each kind's data record at +0x08). */
typedef struct R6iDesc {
    uint8_t  unk00[8];
    int32_t  size;            /* +0x08 */
    uint8_t  unk0C[0x24 - 0x0C];
} R6iDesc;
typedef R6iDesc *(*R6iDescGetter)(void);
extern R6iDescGetter a8b_descGetters[8];  /* 0x002E0D68 */
/* Task work block / serialized data record header. */
typedef struct R6iWorkRec {
    uint8_t  unk00[4];
    int8_t   kind04;          /* +0x04 -1 ends a record list */
    int8_t   sub05;           /* +0x05 */
    uint8_t  unk06[2];
    int32_t  link08;          /* +0x08 node index while loading, -1 none */
    uint8_t  unk0C[4];
    union { uint32_t u; uint8_t b[4]; } u10; /* +0x10 */
} R6iWorkRec;
typedef struct R6iTask {
    uint8_t  unk00[0x1C];
    R6iWorkRec *work;         /* +0x1C */
} R6iTask;
R6iTask *sub_0008B980(int kind, int sub);
int   r6d_MemCopy(void *dst, const void *src, int n);
void *a6b_Node_Nth(void *list, int n);
void  a8b_SetLink(R6iWorkRec *w, void *node);
R6iTask *r6c_TreeInsertAfter(R6iTask *a, R6iTask *b);
R6iTask *a6b_Node_First(R6iTask *n);
void  r6f_TaskFreeChain(R6iTask *n);

/* ------------------------------------------------------------ gimmick sequence (0x9ED40) */
typedef struct R6iModel {
    uint8_t  unk00[0x30];
    void    *anim30;          /* +0x30 animation player */
} R6iModel;
typedef struct R6iPart {
    uint8_t  unk00[0x0C];
    uint8_t  flags0C;         /* +0x0C bit 0 alive */
} R6iPart;
typedef struct R6iGimmick {
    uint8_t  unk00[0x40];
    int32_t  state40;         /* +0x40 */
    uint8_t  unk44[0x120 - 0x44];
    R6iModel *model120;       /* +0x120 */
    uint8_t  unk124[0x12C - 0x124];
    R6iPart *part12C;         /* +0x12C */
} R6iGimmick;
extern void *r1_ctx42C8E4;                /* 0x0042C8E4 */
void  sub_0001E9B0(void *ctx, R6iModel *m, int a, int b, int c);
void  sub_000A4010(R6iGimmick *g, int anim);
int   sub_0017C4D0(void);
void  sub_000A22C0(R6iGimmick *g, R6iPart *p);
void  sub_000A5440(R6iGimmick *g);

/* ------------------------------------------------------------ door key step (0xB34F0) */
/* Three-word step state passed in ESI. */
typedef struct R6iKeyStep {
    uint32_t flags;           /* +0x0 */
    int32_t  phase;           /* +0x4 10 open check, 0x14 done */
    int32_t  count;           /* +0x8 */
} R6iKeyStep;
/* Actor record (0x260 bytes each at 0x004242C0; only touched fields). */
typedef struct R6iActor {
    uint8_t  unk00[0x48];
    int32_t  state48;         /* +0x48 */
} R6iActor;
R6iActor *sub_000A4290(int idx);          /* actor record idx of 0x004242C0 */
void  sub_000A42F0(int idx, int v);
void  sub_000A2D70(int idx, int v);
void  sub_000A2CC0(int idx, uint32_t v);
void  sub_000A1940(R6iActor *actor, int anim);    /* set actor motion (-1 default) */
void  sub_000D9B30(int bit);
void  sub_000D9AB0(int bit);
void  sub_000A2DD0(int idx, int a, int b);

/* ------------------------------------------------------------ room scripts (0xB16F0, 0xB3EB0) */
void  sub_000A2D10(int idx, int v);
void  sub_000A2D40(int idx, int v);
void  sub_000A2CA0(int idx, uint32_t v);
void  sub_000A4410(int idx, int v);

/* ------------------------------------------------------------ room script 0xBACA0 */
extern float     r1e_fps42C964;           /* 0x0042C964 frames per second */
int   sub_00036D40(void);
void  sub_000A2E10(int idx, int v);
void  sub_000A2E50(int idx, int v);
void  sub_000A4340(int idx, int v);
int   sub_000A4370(int idx);

/* ------------------------------------------------------------ room script 0xB89B0 */
extern uint8_t   ae0_obj3E1270[];         /* 0x003E1270 camera object */
void  sub_000A5450(int idx);
int   a80_AnyLowFlags(void);              /* 0x00087AF0 */
int   a80_ModeFlag1(void);                /* 0x00088170 */
void  sub_0019BE90(int id);
void  sub_0019BEB0(int id);
void  sub_000D1D00(PlayerStats *p);
void  sub_00019000(void *cam, int mode);
void  sub_0001AB00(void *cam, int a, int b, int c, int d);
void  sub_000A43C0(int idx, int v);
int   r2b_PairB(int i);                   /* 0x000D9000 */
void  a80_Set3ED23C(int v);               /* 0x00087520 */

/* ------------------------------------------------------------ switch room scripts (0xB95C0, 0xB97A0) */
extern uint64_t  a50_frameCounter0;       /* 0x0042C918 frame counter */
int   sub_000A2CE0(int idx, uint32_t mask);
void  sub_000CAE20(PlayerStats *p, float v);
int   r6b_Slot0Value110(void);            /* 0x00095300 */
void  sub_000D1930(PlayerStats *p);
void  sub_000DFD40(int32_t *chapter, int32_t *stage);

#endif
