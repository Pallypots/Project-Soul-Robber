#ifndef R1F_H
#define R1F_H
#include "oogie.h"
#include "a12.h"
#include <string.h>
#if defined(_M_IX86)
#include <intrin.h>
#endif

/* Area r1f: game functions 0x00012000..0x00060000 (sixth pass). Names
   inferred. Register-argument mappings are in config/function_states_r1f.csv. */

/* float -> int truncation as the original inlines it (cvttss2si) */
#if defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
#define R1F_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R1F_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ group 1 */
/* actor dispatchers (0x0001C400..) use A12Actor (kind at +0xD0) */
typedef struct R1fActorB {
    uint8_t  unk00[4];
    int32_t  sub;               /* +0x04 */
    uint8_t  unk08[0xC8];
    int32_t  kind;              /* +0xD0 */
} R1fActorB;
void a1b_Swap_1C260(void *a, void *b);           /* 0x0001C260 */

/* ------------------------------------------------------------ group 3 */
/* stage fades: a queue timer (as area r1's R1QTimer) followed by the fade
   level byte; the stage flag word sits just before it */
typedef struct R1fFade {
    int32_t  q[8];              /* +0x00 queued requests */
    int32_t  state;             /* +0x20 */
    float    t;                 /* +0x24 */
    float    reload;            /* +0x28 */
    uint8_t  level;             /* +0x2C fade level 0..0x80 */
} R1fFade;
extern R1fFade  r1_qt37DAA4;                     /* 0x0037DAA4 */
extern uint32_t r1f_flags37DAA0;                 /* 0x0037DAA0 */
void sub_000720A0(float *t, int a);

/* stage A state block at 0x0037C540 (inside area r1d's R1dSeqA) */
typedef struct R1fSeqA {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 queued requests */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    uint8_t  level8;            /* +0x2C */
    uint8_t  u2D;
    int16_t  level16;           /* +0x2E */
    int32_t  d30;               /* +0x30 */
    int32_t  d34;               /* +0x34 */
    int32_t  d38;               /* +0x38 */
    int32_t  d3C;               /* +0x3C */
    uint16_t w40;               /* +0x40 */
    uint16_t w42;               /* +0x42 */
    float    f44;               /* +0x44 */
} R1fSeqA;
extern R1fSeqA r1f_seqA37C540;                   /* 0x0037C540 */

/* stage B state block at 0x0037D430 (inside area r1d's R1dSeqB) */
typedef struct R1fSeqB {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    uint8_t  u2C[4];
    int32_t  d30;               /* +0x30 */
    int32_t  d34;               /* +0x34 */
    int32_t  d38;               /* +0x38 */
    int16_t  level;             /* +0x3C */
    uint8_t  u3E[2];
    float    f40;               /* +0x40 */
    uint8_t  u44[2];
    uint16_t w46;               /* +0x46 */
} R1fSeqB;
extern R1fSeqB r1f_seqB37D430;                   /* 0x0037D430 */

extern uint8_t r1f_stepper37D51C[];              /* 0x0037D51C */
extern float   r1f_scaleX37D8E0;                 /* 0x0037D8E0 */
extern float   r1f_scaleY37D8E4;                 /* 0x0037D8E4 */
extern float   r1f_scaleX37D94C;                 /* 0x0037D94C */
void  sub_00014E30(void *p, int a, int b, int c, int d);
float sub_001A3ED0(float x);                     /* sin */
void  r1_QueuePop8(int32_t *q);                  /* 0x000268D0 regargs: q=EAX */
void  sub_000243B0(int a, int b);

/* generic stage block: flag word, queue timer, then per-stage fields */
typedef struct R1fStage {
    uint32_t flags;             /* +0x00 bit 0 = active */
    int32_t  q[8];              /* +0x04 queued requests */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    uint8_t  level;             /* +0x2C */
    uint8_t  level2;            /* +0x2D */
    uint8_t  u2E[2];
    int32_t  d30;               /* +0x30 */
    int32_t  d34;               /* +0x34 */
    float    f38;               /* +0x38 */
    float    f3C;               /* +0x3C */
} R1fStage;
extern R1fStage r1f_seqD37DC24;                  /* 0x0037DC24 */
extern R1fStage r1f_seqE37DCF8;                  /* 0x0037DCF8 */
extern R1fStage r1f_seqF37ED00;                  /* 0x0037ED00 */
typedef struct R1fStageG {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    uint8_t  level;             /* +0x2C */
    uint8_t  u2D;
    uint16_t n2E;               /* +0x2E */
    uint16_t n30;               /* +0x30 */
} R1fStageG;
extern R1fStageG r1f_seqG37E090;                 /* 0x0037E090 */
void sub_00048AF0(int id);

/* stage block with the fade level at +0x30 (0x0037F480, as stage C) */
typedef struct R1fStage2 {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    float    reload;            /* +0x2C */
    uint8_t  level;             /* +0x30 */
} R1fStage2;
extern R1fStage2 r1f_seqI37F480;                 /* 0x0037F480 */
extern R1fStage  r1f_seqJ37FB3C;                 /* 0x0037FB3C */
/* curtain block passed by pointer (level at +0x28, timer at +0x30) */
typedef struct R1fCurtain {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 */
    int32_t  state;             /* +0x24 */
    int32_t  level;             /* +0x28 */
    uint8_t  u2C[4];
    float    t;                 /* +0x30 */
} R1fCurtain;

/* stage H block at 0x0037EDEC (flag word of area r1d's R1dSeqF) */
typedef struct R1fPair { float a, b; } R1fPair;
typedef struct R1fStageH {
    uint32_t flags;             /* +0x00 */
    int32_t  q[8];              /* +0x04 */
    int32_t  state;             /* +0x24 */
    float    t;                 /* +0x28 */
    int32_t  d2C;               /* +0x2C */
    uint8_t  level;             /* +0x30 */
    uint8_t  u31[3];
    int32_t  v[13];             /* +0x34 */
    R1fPair  pair[13];          /* +0x68 */
} R1fStageH;
extern R1fStageH r1f_seqH37EDEC;                 /* 0x0037EDEC */

/* ------------------------------------------------------------ group 6 */
/* sound channel settings: two 0x2C-byte records at 0x003DA4A8 */
typedef struct R1fChan {
    int32_t kind;               /* +0x00 */
    int32_t d04;                /* +0x04 */
    int32_t d08;                /* +0x08 */
    int32_t d0C;                /* +0x0C */
    int32_t level;              /* +0x10 */
    int32_t d14;                /* +0x14 */
    int32_t d18;                /* +0x18 */
    int32_t d1C, d20, d24, d28; /* +0x1C */
} R1fChan;
extern R1fChan r1e_chan3DA4A8[2];                /* 0x003DA4A8 */

/* ------------------------------------------------------------ group 8 */
/* sound name tables at 0x0026BD78: {id, list} pairs ending with id -1; each
   list holds {key, val, alt} triples ending with key -1 */
typedef struct R1fKeyVal { int32_t key; int32_t val; int32_t alt; } R1fKeyVal;
typedef struct R1fKeyTab { int32_t id; R1fKeyVal *list; } R1fKeyTab;
extern R1fKeyTab r1f_sndTab26BD78[];             /* 0x0026BD78 */
/* 17 sound entries of 0x14 bytes at 0x003E2550 (as area r1's R1Ent20) */
typedef struct R1fEnt {
    uint8_t  u00[4];
    int32_t  a;                 /* +0x04 */
    int32_t  b;                 /* +0x08 */
    int32_t  used;              /* +0x0C */
    int32_t  life;              /* +0x10 */
} R1fEnt;
extern R1fEnt r1_ents3E2550[17];                 /* 0x003E2550 */
void sub_00052EC0(int *outKey, int key, int *outSub, int sub);  /* regargs: outKey=EAX key=EDX outSub=EBX */

/* ------------------------------------------------------------ group 9 */
/* job group setup (0x000575D0) */
void sub_001A8A70(int a);
void sub_001A1030(void *g, int slot, int prio, void (*fn)(void), int a, int stack);
void sub_001A1060(void *g, int slot);
void sub_000550F0(void);
void sub_000574F0(void);
void sub_00057160(void);
extern int32_t r1f_g3E3940;                      /* 0x003E3940 */
extern int32_t a5b_g3E3910;                      /* 0x003E3910 */
extern int32_t r1f_g42C7A0;                      /* 0x0042C7A0 */

/* model node with child list (0x0005AB00) */
typedef struct R1fAnimCtl {
    uint8_t  u00[8];
    int32_t  anim;              /* +0x08 */
} R1fAnimCtl;
typedef struct R1fModel {
    uint8_t  u00[4];
    int32_t  kind;              /* +0x04 12..13 = group */
    uint8_t  u08[0x28];
    R1fAnimCtl *ctl;            /* +0x30 */
    uint8_t  u34[8];
    struct R1fModel *next;      /* +0x3C */
} R1fModel;
void sub_000832D0(void *o, int anim);

/* save worker job (0x0005A200) */
uint16_t sub_00072FA0(void *obj);
uint32_t sub_0004ECE0(int pad);
uint32_t sub_0004ECF0(int pad);
uint32_t sub_0004ED20(int pad);
uint32_t sub_0004ED40(int pad);
void sub_00059720(void);
void sub_000599D0(void);
void sub_00058D20(void);
extern uint8_t a4c_obj428F40[];                  /* 0x00428F40 */
extern int32_t r1e_sndTab3E4750;                 /* 0x003E4750 save state */
extern int32_t r1f_busy3E4770;                   /* 0x003E4770 */

/* ------------------------------------------------------------ group 10 */
/* movie table: 0x21E records of 0x20 bytes at 0x002C8900 */
typedef struct R1fMovie {
    uint8_t  u00[0x0C];
    int32_t  sizeA;             /* +0x0C */
    int32_t  sizeB;             /* +0x10 */
    int32_t  pos;               /* +0x14 file offset */
    void    *buf;               /* +0x18 */
    int32_t  mode;              /* +0x1C */
} R1fMovie;
extern R1fMovie r1e_movies2C8900[0x21E];         /* 0x002C8900 */
extern int32_t  r1e_mId3E0DBC;                   /* 0x003E0DBC */
extern void    *r1e_mArg3E0DC4;                  /* 0x003E0DC4 caller buffer */
extern void    *r1e_m3E0DC8;                     /* 0x003E0DC8 */
extern int32_t  a50_streamHandle;                /* 0x003E0D68 */
extern R1fMovie *a30_curSlot;                    /* 0x003E11F0 */
void *sub_00053AB0(int size, int a, int tag);
void  sub_001A8490(int fd, int pos, int whence);
void  sub_00102FA0(int a, ...);
void  sub_001A8410(int fd, void *buf, int size);

/* movie archive: 0x20-byte header read to 0x003E0D90, then a directory of
   0x20-byte entries after a 0x20-byte header */
typedef struct R1fArcHdr {
    uint8_t  u00[0x18];
    int32_t  size;              /* +0x18 */
    int32_t  count;             /* +0x1C */
} R1fArcHdr;
typedef struct R1fArcEnt {
    uint8_t  name[0x18];        /* +0x00 */
    int32_t  pos;               /* +0x18 */
    int32_t  size;              /* +0x1C */
} R1fArcEnt;
extern R1fArcHdr  r1f_hdr3E0D90;                 /* 0x003E0D90 */
extern const char *r1e_m3E0DC0;                  /* 0x003E0DC0 archive name */
extern int32_t    r1f_dirSize3E0D6C;             /* 0x003E0D6C */
extern R1fArcEnt *r1f_dir3E0D70;                 /* 0x003E0D70 */
extern int32_t    r1f_dirCount3E0D74;            /* 0x003E0D74 */
int       sub_001A8210(const char *name, int mode);
R1fMovie *sub_0004F8E0(const char *name);        /* regargs: name=EDI */

/* ------------------------------------------------------------ group 11 */
/* GS packet words at 0x003DE500 (0x003DE560 is a packet buffer) */
extern uint32_t r1f_pkt3DE500[];                 /* 0x003DE500 */
void sub_000AD090(void *p, ...);                 /* returns 0 on this build */


/* main loop (0x0003E0F0) */
void sub_0003DF90(void);
void sub_001A5480(void);
int  sub_001C80BE(int t);                        /* CRT time */
void sub_001C7ED4(int seed);                     /* CRT srand */
void sub_0004F0B0(void);
int  sub_000586E0(int a);
void sub_0019C4B0(void);
void sub_0005E9B0(void);
void sub_0004F4C0(void);
void sub_00049470(void);
void sub_000ED350(void);
void sub_0019C4D0(void);
int  sub_001C7EE1(void);                         /* CRT rand */
extern int32_t b3b_mode42CAFC;                   /* 0x0042CAFC */
extern int32_t g_ad0_42CAE0;                     /* 0x0042CAE0 */
extern int32_t r1e_g42CAF0;                      /* 0x0042CAF0 */
extern int32_t r1f_g42CAF4, r1f_g42CAF8;         /* 0x0042CAF4 / 0x0042CAF8 */
extern int32_t r4e_g42CB00;                      /* 0x0042CB00 */
extern int32_t r1f_g42CADC;                      /* 0x0042CADC */

/* ------------------------------------------------------------ group 12 */
/* menu worker jobs (0x00046F00 / 0x00046FA0) */
void sub_00038960(void);
void sub_00079340(void);
void sub_00045CC0(void);
void r1f_MenuJob(void);                          /* 0x00046F00 */
void sub_00046D90(void);
void sub_00046E90(void);
int  sub_00079460(void);
uint32_t sub_0004ED00(int pad);
uint32_t sub_0004ECD0(int pad);
void sub_000580D0(void);
void sub_001A0D70(void);
void sub_00058190(void);
extern int32_t rtc_g3DF9B4;                      /* 0x003DF9B4 */
extern int32_t a30_g3DF1D4;                      /* 0x003DF1D4 */
extern float   r1f_f3DF1DC;                      /* 0x003DF1DC */
extern int32_t r1f_g3DFA34;                      /* 0x003DFA34 */
extern int32_t r1f_g3DF1E8;                      /* 0x003DF1E8 */
extern uint8_t a60_b428F45;                      /* 0x00428F45 */

/* menu / title dispatchers (0x00046E90 / 0x0004E970) */
void sub_00040240(void);
void sub_00046CF0(void);
void sub_00046D50(void);
void sub_000403A0(void);
void sub_0003FCE0(void *p);
void sub_00043A90(void);
void sub_00043C20(void);
extern int32_t a4c_mode3DF1EC;                   /* 0x003DF1EC */
extern int32_t a4c_g3DFA5C;                      /* 0x003DFA5C */
extern uint8_t a4c_buf2B4D84[];                  /* 0x002B4D84 */
void sub_0004B090(void);
void sub_0004D9E0(void);
void sub_0004E830(void);
void sub_0004E1C0(void);
void sub_0004E3A0(void);
extern int32_t a4c_state3E0000;                  /* 0x003E0000 */
void sub_0004B320(void);
void sub_0004B7A0(void);
void sub_0004E030(void);
void sub_0004BA20(void);
extern int32_t r1f_sub3E0004;                    /* 0x003E0004 */

/* ------------------------------------------------------------ group 15 */
/* stage loader (0x00031B60) */
const char *sub_00052A10(unsigned id);
int  a6b_Printf2(char *buf, const char *fmt, ...); /* 0x0007E0A0 */
void sub_0004F700(int a);
void sub_00053E20(const char *name, void *dst);
int  sub_00053CA0(int a);
void sub_0004F720(void);
void sub_001B9FC0(int tex);
int  sub_00084C00(void *p, int a);
void sub_00014DA0(void *p);
void sub_00014D00(void *obj, void *p, int tex);
extern uint32_t r1f_stage381830;                 /* 0x00381830 */
extern char     r1f_name3817E8[];                /* 0x003817E8 */
extern const char r1f_fmt283614[];               /* 0x00283614 */
extern char    *r1d_heap381A5C;                  /* 0x00381A5C */
extern int32_t  r1d_tex381AB0;                   /* 0x00381AB0 */
extern uint8_t  r1f_spr381888[];                 /* 0x00381888 */

/* ------------------------------------------------------------ group 13 */
/* screen jobs (0x0002E470 / 0x0002E4E0) */
void sub_0002D230(void);
void sub_0002D790(void);
void sub_0002DBC0(void);
void sub_0002C870(void);
void sub_0002C750(void);
void sub_0002CF50(void);
void r1f_ScreenJob(void);                        /* 0x0002E470 */
void sub_0002E2F0(void);
void sub_00053C70(void);
extern int32_t r1c_mode381400;                   /* 0x00381400 */
extern int32_t r1c_state3816D0;                  /* 0x003816D0 */


#endif
