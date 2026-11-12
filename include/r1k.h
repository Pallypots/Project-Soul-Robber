#ifndef R1K_H
#define R1K_H
#include "oogie.h"
#include "shared_decls.h"

/* Area r1k: larger game functions 0x00012000..0x00060000 (eleventh pass).
   Names inferred. Register-argument mappings are in
   config/function_states_r1k.csv. */

/* ------------------------------------------------------------ pads */
uint32_t sub_0004ECD0(int pad);                 /* held buttons */
uint32_t sub_0004ECF0(int pad);                 /* repeating buttons */
uint32_t sub_0004ED00(int pad);
uint32_t sub_0004ED20(int pad);
uint32_t sub_0004ED40(int pad);

/* ------------------------------------------------------------ fades / timers */
extern uint8_t a4c_obj428F40[];                 /* 0x00428F40 fade object */
void     a60_TimerSetCount(void *o, int n);     /* 0x00072EB0 */
void     sub_00072EE0(void *o, int a, float t, int b);
void     sub_00072F30(void *o, int kind, float t, uint32_t color, int z);
uint16_t a60_TimerKind(void *o);                /* 0x00072FA0 fade running */
void     a60_StepByFrame(float *v, int dir);    /* 0x000720A0 */

/* ------------------------------------------------------------ title attract menu */
extern int32_t a4c_mode3DF1EC;                  /* 0x003DF1EC step */
extern int32_t r1f_g3DF1E8;                     /* 0x003DF1E8 menu state */
extern float   r1f_f3DF1DC;                     /* 0x003DF1DC idle time */
extern int32_t r1k_g3DF1F0;                     /* 0x003DF1F0 */
extern int32_t r1k_g3DF1F4;                     /* 0x003DF1F4 */
void r1k_PressStartStep(void);                  /* 0x00040240 */

/* ------------------------------------------------------------ sprites */
/* Sprite record (0x9C bytes, layout of R6jSprite). */
typedef struct R1kSprite {
    float    x, y;            /* +0x00 */
    int32_t  frame;           /* +0x08 */
    uint8_t  unk0C[0x14 - 0x0C];
    float    f14;             /* +0x14 */
    uint8_t  unk18[0x1C - 0x18];
    float    sx;              /* +0x1C */
    float    sy;              /* +0x20 */
    uint8_t  unk24[0x80 - 0x24];
    int32_t  mode;            /* +0x80 */
    uint8_t  unk84[0x8C - 0x84];
    uint32_t color;           /* +0x8C */
    uint8_t  unk90[0x9C - 0x90];
} R1kSprite;
void  sub_000150B0(R1kSprite *s, int frame);
void *r1d_TrackApplyD(void *cmd, R1kSprite *s); /* 0x00017C90 draw sprite */
int   sub_000529F0(void);                       /* video mode */
int   sub_001C7EE1(void);                       /* rand */

/* ------------------------------------------------------------ title logo */
extern int32_t   a30_g3DF9BC;                   /* 0x003DF9BC current stage */
extern int32_t   a30_g3DF9B8;                   /* 0x003DF9B8 */
extern R1kSprite r1k_logoSpr3DF214;             /* 0x003DF214 */
void *r1k_LogoDraw(void *cmd);                  /* 0x000400D0 */

/* ------------------------------------------------------------ title background stars */
/* star particle (0x14 bytes) in the stage block at +0x2B419C */
typedef struct R1kStar {
    float x, y;               /* +0x00 position */
    float vx, vy;             /* +0x08 velocity */
    float life;               /* +0x10 */
} R1kStar;
/* per-stage star parameters (16 bytes, index = stage 0..0x1B) */
typedef struct R1kStarDef {
    uint32_t color;           /* +0x00 rgb (alpha byte clear) */
    uint8_t  alpha;           /* +0x04 */
    uint8_t  mode;            /* +0x05 sprite mode */
    uint8_t  count;           /* +0x06 number of stars */
    uint8_t  speed;           /* +0x07 velocity range in 1/256 units */
    float    life;            /* +0x08 */
    float    grow;            /* +0x0C extra scale at the end of life */
} R1kStarDef;
extern uint8_t *r1c_stage3DFA5C;                /* 0x003DFA5C stage block */
extern const R1kStarDef r1k_starDefs2C58E0[];   /* 0x002C58E0 */
#define R1K_STAR(i) ((R1kStar *)(r1c_stage3DFA5C + 0x2B419C) + (i))
void r1k_StarSpawn(int i);                      /* 0x00040D20 */

/* ------------------------------------------------------------ message queue B */
extern uint32_t  r1j_seqFlags37E090;            /* 0x0037E090 */
extern int32_t   r1e_qB37E094[8];               /* 0x0037E094 */
extern int32_t   r1e_qStateB37E0B4;             /* 0x0037E0B4 */
extern float     r1e_qWaitB37E0B8;              /* 0x0037E0B8 */
extern uint8_t   r1k_b37E0BC;                   /* 0x0037E0BC */
extern uint16_t  r1e_qLeftB37E0BE;              /* 0x0037E0BE glyph count */
extern R1kSprite r1k_qSpr37E0C4[];              /* 0x0037E0C4 glyph sprites */
void r1k_QueueStepBPop(void);                   /* 0x0002A570 */


/* ------------------------------------------------------------ HUD life gauge (sequence block A) */
typedef struct R1kTrack { uint8_t b[0x44]; } R1kTrack;   /* animation track */
void r1b_TrackReset(R1kTrack *t);               /* 0x00018150 */
void r1_QueuePop8(int32_t *q);                  /* 0x000268D0 regargs: q=EAX */
typedef struct R1kSeqA {        /* 0x0037C4FC (layout of R1jSeqA) */
    uint8_t  u00[0x44];
    uint32_t flags;             /* +0x44 */
    int32_t  queue[8];          /* +0x48 command queue, [0] current */
    int32_t  state;             /* +0x68 */
    float    timer;             /* +0x6C */
    uint8_t  u70[4];
    int32_t  maxHealth;         /* +0x74 */
    int32_t  health;            /* +0x78 */
    int32_t  pending;           /* +0x7C health points still to remove */
    int32_t  d80;               /* +0x80 */
    uint16_t w84;               /* +0x84 */
    uint16_t w86;               /* +0x86 */
    uint8_t  u88[4];
    R1kSprite pip[15];          /* +0x8C life pips, one per two health points */
    uint8_t  u9B0[0xAE8 - 0x9B0];
    R1kTrack track[16];         /* +0xAE8 pip flash tracks */
} R1kSeqA;
extern R1kSeqA r1j_seqA37C4FC;                  /* 0x0037C4FC */
void r1k_LifeLoseStep(void);                    /* 0x00028B10 */
void r1k_LifeGainStep(void);                    /* 0x00028930 */

/* ------------------------------------------------------------ star field (loading screen) */
/* block at [0x003E474C]: sprite at +0xC9400, stars at +0xC949C */
extern uint8_t *r1e_bank3E474C;                 /* 0x003E474C */
extern const R1kStarDef r1k_starDef2DD1B8;      /* 0x002DD1B8 */
#define R1K_FSPR() ((R1kSprite *)(r1e_bank3E474C + 0xC9400))
#define R1K_FSTAR(i) ((R1kStar *)(r1e_bank3E474C + 0xC949C) + (i))
float sub_001A3ED0(float x);                    /* sin */
void  r1k_FieldStarSpawn(int i);                /* 0x00058ED0 */
void *r1k_FieldStarsDraw(void *cmd);            /* 0x000592E0 */

/* ------------------------------------------------------------ loading screen */
extern uint32_t  r1k_g3E4754;                   /* 0x003E4754 page (>= 3 second set) */
extern int32_t   r1h_lang3E4760;                /* 0x003E4760 language */
extern R1kSprite r1h_anim3E4774[];              /* 0x003E4774 three sprites */
void  sub_00014E80(R1kSprite *s);               /* advance sprite animation */
void *r1k_LoadingDraw(void *cmd);               /* 0x00059450 */
extern int32_t   r1k_done3E4750;                /* 0x003E4750 loading screen finished */
extern float     r1k_timer3E4768;               /* 0x003E4768 */
extern int32_t   r1k_g3E4758, r1k_g3E475C;      /* 0x003E4758, 0x003E475C */
void rtc_SetRateMode(int mode);                 /* 0x00052900 */
void r1k_LoadingStep(void);                     /* 0x00058D20 */

/* ------------------------------------------------------------ primitive batches */
typedef struct R1kVtx { float x, y, z; uint32_t flags; } R1kVtx;   /* 16 bytes */
extern R1kVtx *r1g_batchCur3DCEFC;              /* 0x003DCEFC vertex write pointer */
void  r1g_BatchBegin(void *p, uint32_t mode, int count);   /* 0x0003A0D0 */
void *sub_0003A2A0(void);                       /* close the batch, returns the packet end */
void *r1k_DrawAxes(void *p, float sx, float sy, float sz);   /* 0x0003A540 */

/* ------------------------------------------------------------ intrusive lists */
typedef struct R1kList R1kList;
typedef struct R1kLNode {
    struct R1kLNode *next;      /* +0x00 */
    struct R1kLNode *prev;      /* +0x04 */
    R1kList         *list;      /* +0x08 owning list, NULL when unlinked */
} R1kLNode;
struct R1kList {
    int32_t   count;            /* +0x00 */
    R1kLNode *head;             /* +0x04 */
    R1kLNode *tail;             /* +0x08 */
};
typedef int (*R1kLCmp)(R1kLNode *a, R1kLNode *b);
void r1k_ListMergeSort(R1kList *l, R1kLNode *first, R1kLNode *last, R1kLCmp cmp);   /* 0x0003D990 */

/* ------------------------------------------------------------ title background */
typedef struct R1kQuad {        /* screen quad passed to 0x00072420 (layout of R6hQuad) */
    float    x, y, w, h;        /* +0x00 */
    float    u0, v0, u1, v1;    /* +0x10 */
    uint32_t col[4];            /* +0x20 */
    int32_t  tex;               /* +0x30 */
    int32_t  z;                 /* +0x34 */
} R1kQuad;
extern int32_t rtc_tex3DF9C0;                   /* 0x003DF9C0 background texture */
void *sub_00072420(void *cmd, R1kQuad *q);
#define R1K_TSPR() ((R1kSprite *)(r1c_stage3DFA5C + 0x2B4100))
void *r1k_TitleStarsDraw(void *cmd);            /* 0x00041520 */

#endif
