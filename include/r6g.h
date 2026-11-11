#ifndef R6G_H
#define R6G_H
#include "oogie.h"
#include "r6f.h"
/* Area r6g: larger functions (300-2000 bytes) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6g.csv. Callees are declared under their sub_ name
   so that cl never inlines a function recovered in this area into another one. */



/* ------------------------------------------------------------ status screen textures (0x65F00) */
/* Texture set records at 0x002DDD50 (0x30 bytes each, layout of R6dTexSet). */
typedef struct R6gTexSet {
    int32_t  big[4];          /* +0x00 nonzero: load big texture i */
    int32_t  small[3];        /* +0x10 nonzero: build sprite j */
    uint8_t  sel[3][4];       /* +0x1C texture index per sprite layer */
    uint8_t  unk28[0x30 - 0x28];
} R6gTexSet;
/* Sprite record (0x9C bytes, set up by 0x00014D00). */
typedef struct R6gSprite {
    uint8_t  unk00[0x1C];
    float    rate;            /* +0x1C animation rate */
    uint8_t  unk20[0x40 - 0x20];
    int32_t  base;            /* +0x40 base texture (set by 0x00014D00) */
    int32_t  tex[3];          /* +0x44 layers 1..3 */
    uint8_t  unk50[0x80 - 0x50];
    int32_t  mode;            /* +0x80 */
    uint8_t  unk84[0x8C - 0x84];
    uint32_t color;           /* +0x8C */
    uint8_t  unk90[0x9C - 0x90];
} R6gSprite;
extern R6gTexSet r6d_texSets[];         /* 0x002DDD50 */
extern int32_t   r6d_texSet3E6538;      /* 0x003E6538 */
extern int32_t   r6g_tex3E6528[4];      /* 0x003E6528 */
extern R6gSprite r6g_sprites429530[3];  /* 0x00429530 */
extern uint8_t  *a60_work42C5E8;        /* 0x0042C5E8 */
int   sub_00084C00(void *p, int a);
void  sub_00014DA0(void *p);
void  sub_00014D00(void *p, void *obj, int a);
void  sub_00014E30(void *p, int idx, float a, float b, int arg);

/* ------------------------------------------------------------ text boxes (0x76E30) */
/* Text box (layout of R6cText) with the position and its two sprites named. */
typedef struct R6gText {
    uint32_t flags;           /* +0x000 */
    int16_t  x, y;            /* +0x004, +0x006 */
    int16_t  w, h;            /* +0x008, +0x00A */
    uint8_t  unk00C[0x830 - 0x0C];
    R6gSprite spr830;         /* +0x830 */
    R6gSprite spr8CC;         /* +0x8CC */
} R6gText;
void  sub_00038060(int v);
void  sub_00038380(void);
void *sub_000768D0(R6gText *t, void *ctx, void (*fn)(void), int n);   /* t=EDI */

/* ------------------------------------------------------------ player (0xBCA60, 0xCD430) */
/* Fields of Jack's character object (g_stats, PlayerStats) not named in oogie.h. */
typedef struct R6gPlayer {
    uint8_t  unk000[0xD4];
    int32_t  stateD4;         /* +0x0D4 */
    uint8_t  unk0D8[0x140 - 0xD8];
    int32_t  anim140;         /* +0x140 current animation bank (0x00420000) */
    int32_t  prev144;         /* +0x144 previous animation bank (0x00420004) */
    uint8_t  unk148[0x150 - 0x148];
    uint32_t flags150;        /* +0x150 */
    uint8_t  unk154[0x1B8 - 0x154];
    int32_t  active1B8;       /* +0x1B8 (0x00420078) */
    int32_t  side1BC;         /* +0x1BC */
    uint8_t  unk1C0[0x1CC - 0x1C0];
    int32_t  can1CC;          /* +0x1CC */
    int32_t  can1D0;          /* +0x1D0 */
    uint8_t  unk1D4[4];
    int32_t  aim1D8;          /* +0x1D8 */
    uint8_t  unk1DC[0x1000 - 0x1DC];
    uint8_t  sm[4];           /* +0x1000 action state machine (0x00420EC0) */
} R6gPlayer;
#define R6G_PLAYER ((R6gPlayer *)&g_stats)
/* Model node of the player (pointer at 0x0042C8E0). */
typedef struct R6gModel {
    uint8_t  unk000[4];
    int32_t  mode04;          /* +0x004 */
    int32_t  i08;             /* +0x008 */
    uint8_t  unk00C[0x30 - 0x0C];
    int32_t  i30;             /* +0x030 */
    uint8_t  unk034[0x12C - 0x34];
    int32_t  i12C, i130, i134, i138, i13C;  /* +0x12C..+0x13C */
} R6gModel;
extern R6gModel *r1e_g42C8E0;           /* 0x0042C8E0 */
extern uint32_t r4e_g42CA38;            /* 0x0042CA38 buttons pressed this frame */
extern uint32_t r6g_keyMask41CD00[10];  /* 0x0041CD00 button mask per action */
void  sub_0001E550(R6gModel *m);
void  sub_0004F5D0(int a);
void  sub_000BBF40(int bank);
int   sub_000BC650(void *sm);
void  sub_000BC6B0(void *sm, int st);
int   sub_000CD300(PlayerObj *p);       /* p=EAX */
int   sub_0019BE60(int k);
void  sub_000D2440(PlayerObj *p);

/* ------------------------------------------------------------ title flow (0x6D780) */
extern int8_t  a60_lang413145;          /* 0x00413145 */
extern int32_t a60_cmd3E6610, a60_arg3E661C;
extern int32_t a60_v3E6620, a60_v42C5EC, a60_v428F74, a60_v3E6614, a60_v3E68A8;
extern int32_t a60_flag428F78;
extern int32_t r6g_g42AC78;             /* 0x0042AC78 */
extern int32_t r6g_g428F20;             /* 0x00428F20 */
extern uint8_t r6g_b428F80[4];          /* 0x00428F80 */
extern uint8_t a4c_obj428F40[];         /* 0x00428F40 */
void  sub_0006C070(void);
void  sub_00022920(void);
int   sub_00060BD0(void);
void  sub_0005FE00(void);
int   sub_000774E0(void);
void  sub_00077410(void);
int   sub_00052A00(int lang);
void  sub_0019BF80(int from, int to);
void *sub_00053820(int pool, int size, int a, int b);
int   sub_0004F6D0(int id);
int   sub_0004F680(int id);
void  sub_0004FA70(int id, void *p);
int   sub_0004F4D0(void);
void  sub_000580D0(void);
void  sub_0002BAB0(void);
void  sub_0006EA20(int v);
int   sub_0005F860(void);
int   sub_00077500(void);
void  sub_00077A30(void);
int   sub_0006D350(void);
void  sub_00072EE0(void *o, int a, float t, int b);

/* ------------------------------------------------------------ 3D object models (0x79A00) */
typedef struct R6gObj7 {
    uint8_t  unk000[0x0C];
    uint8_t  light[0x34];     /* +0x00C */
    void    *colour;          /* +0x040 */
    void    *mdl;             /* +0x044 model list */
} R6gObj7;
void *sub_000846D0(int n);
int   sub_00084730(void *l, int v);
void  sub_00079980(void *l, void *light);
void  sub_000847D0(void *l, int i, int v);
void  sub_00084810(void *l, int i, void (*fn)(void));
void  sub_00084830(void *l, int i, void (*fn)(void));
void  sub_001B7E90(void);
void  sub_000796D0(void);
void  sub_00079810(void);
void  sub_00079830(void);
void  sub_00079780(void);
void  sub_00079790(void);
void  sub_000799F0(void);

/* ------------------------------------------------------------ present models (0xC9460) */
typedef struct R6gPresent {
    uint8_t  unk00[4];
    int32_t  kind;            /* +0x04 */
    int32_t  index;           /* +0x08 */
    uint8_t  unk0C[0x150 - 0x0C];
} R6gPresent;
extern R6gPresent *r6g_presents41CEBC;  /* 0x0041CEBC 12 records */
extern const char r6g_prsnt0000_276FF4[], r6g_prsnt0001_276FC8[], r6g_prsnt0002_276F9C[];
extern const char r6g_prsnt0100_276F70[], r6g_prsnt0101_276F44[], r6g_prsnt0102_276F18[];
extern const char r6g_prsnt0200_276EEC[], r6g_prsnt0201_276EC0[], r6g_prsnt0202_276E94[];
extern const char r6g_prsnt03_277020[];
void  sub_000C6920(void);
void  sub_00022630(void *o, const char *path);
void  sub_00036790(void *o);
void  sub_000C87B0(void);

/* ------------------------------------------------------------ attack hit dispatch (0xC6350, 0xC66B0) */
typedef struct R6gVec { float x, y, z, w; } R6gVec;
/* Object that receives hits (fields used by the dispatchers). */
typedef struct R6gHitObj {
    uint8_t  unk000[0x6A8];
    int32_t  nHits;           /* +0x6A8 */
    uint8_t  unk6AC[0x8AC - 0x6AC];
    R6gVec   hitPos[32];      /* +0x8AC */
    R6gVec   hitDir[32];      /* +0xAAC */
    void    *hits[0x94];      /* +0xCAC targets already hit */
    void    *self;            /* +0xEFC */
} R6gHitObj;
/* Attack record. */
typedef struct R6gAtk {
    uint8_t  unk00[4];
    int32_t  type;            /* +0x04 handler index, -1 none */
    int32_t  power;           /* +0x08 */
    uint8_t  unk0C[0x54 - 0x0C];
    void    *owner;           /* +0x54 */
    int32_t  nIgnore;         /* +0x58 */
    void    *ignore[1];       /* +0x5C nIgnore entries */
} R6gAtk;
typedef void (*R6gHitFn)(R6gHitObj *o, R6gAtk *a, void *target);
extern R6gHitFn r6g_hitFns2E6E80[];     /* 0x002E6E80 */
/* Entity slot (0x260 bytes, layout of Aa0Slot). */
typedef struct R6gSlot {
    union { uint32_t flags; int8_t flags0; } u;  /* +0x000 bit 7 active, bit 6 hidden */
    uint8_t  unk004[0x120 - 0x04];
    void    *obj;             /* +0x120 */
    uint8_t  unk124[0x260 - 0x124];
} R6gSlot;
extern R6gSlot aa0_slots[32];           /* 0x004242C0 */
void  sub_000C4420(R6gHitObj *o);
int   sub_000C5E70(R6gHitObj *o, void *t, R6gAtk *a, R6gVec *pos, R6gVec *dir);
int   sub_000C5D20(R6gHitObj *o, void *t, R6gAtk *a, R6gVec *pos, R6gVec *dir);
void  sub_000A95E0(void *t, R6gVec *dir, int power);
void  sub_000C4960(R6gHitObj *o, R6gAtk *a, int v, R6gVec *pos, R6gVec *dir);
void  sub_000C64D0(R6gHitObj *o, void *t, R6gAtk *a, int power, R6gVec *pos, R6gVec *dir);
void  sub_000CA400(R6gHitObj *o);

/* ------------------------------------------------------------ effect objects (0x7AEE0) */
typedef struct R6gEffList {
    int32_t  count;           /* +0x00 */
    struct R6gEff *head;      /* +0x04 */
    struct R6gEff *tail;      /* +0x08 */
} R6gEffList;
typedef struct R6gEff {
    struct R6gEff *next;      /* +0x00 */
    struct R6gEff *prev;      /* +0x04 */
    R6gEffList *owner;        /* +0x08 */
    void    *node0C;          /* +0x0C list node */
    void    *res10;           /* +0x10 */
    void    *res14;           /* +0x14 */
    void    *buf18;           /* +0x18 */
    void    *buf1C;           /* +0x1C */
    void    *part20;          /* +0x20 */
    void    *buf24;           /* +0x24 */
    uint8_t  unk28[0x30 - 0x28];
    uint8_t  flags30;         /* +0x30 bit 0: textures not owned */
    uint8_t  unk31[3];
    int32_t  nTex;            /* +0x34 */
    int32_t *tex;             /* +0x38 texture ids, -1 none */
    uint8_t  unk3C[0x80 - 0x3C];
    void    *buf80;           /* +0x80 */
} R6gEff;
void  sub_001B2080(void *n);
void  sub_000751C0(void *n);
void  sub_00074F10(void *n);
int   sub_001B9FC0(int idx);
void  sub_00082270(void *r);
void  sub_000820C0(void *r);
void  sub_00083070(void *r);


/* ------------------------------------------------------------ scripted event handlers (0xB3EB0, 0xB4BC0) */
/* Event state passed to the handlers with the message (0 reset, 1 start, 3 stop). */
typedef struct R6gEvt {
    uint32_t flags;           /* +0x00 bit 0 running */
    int32_t  state;           /* +0x04 10.. = steps, 20 = finished */
    int32_t  frames;          /* +0x08 */
} R6gEvt;
int   sub_000D9A70(int bit);
void  sub_000D9AB0(int bit);
void  sub_000A42F0(int a, int b);
void  sub_0001B3F0(void *o);
void  sub_000A2CC0(int a, uint32_t m);
void  sub_000A2CA0(int a, uint32_t m);

/* ------------------------------------------------------------ menu page images (0x64CE0) */
/* Image tables of the menu pages at 0x002DDB08. */
typedef struct R6gMenuImgs {
    void    *top[5];          /* +0x00 page 0 */
    void    *unk14;
    void    *bg1[2];          /* +0x18 page 1 */
    void    *name1[9];        /* +0x20 page 1, per item (loaded by name) */
    void    *pic1[9];         /* +0x44 page 1, per item */
    void    *fg1[2];          /* +0x68 */
    void    *bg2;             /* +0x70 page 2 */
    void    *name2[4];        /* +0x74 */
    void    *pic2[4];         /* +0x84 */
    void    *fg2[2];          /* +0x94 */
    void    *bg3;             /* +0x9C page 3 */
    void    *name3[2];        /* +0xA0 */
    void    *pic3[2];         /* +0xA8 */
    void    *fg3[2];          /* +0xB0 */
} R6gMenuImgs;
extern R6gMenuImgs r6g_menuImgs2DDB08;  /* 0x002DDB08 */
extern int32_t r6g_menuItem42A018;      /* 0x0042A018 */
extern int32_t r6g_menuBuf42A028;       /* 0x0042A028 double-buffer half 0/1 */
void  sub_00053ED0(void *img, void *dst);
void  sub_00053E20(void *img, void *dst);

/* ------------------------------------------------------------ menu page sprites (0x646E0) */
extern R6gSprite r6g_menuSpr42A3D4[7];  /* 0x0042A3D4 */
extern int32_t a60_hA3E64C4[3], a60_hB3E64D0[3], a60_h3E64DC, a60_hC3E64E0[3], a60_hD3E64EC[3];
void  sub_001B9720(void);
void  sub_00015070(void *p);

/* ------------------------------------------------------------ pause page images (0x6E6B0) */
extern void *r6g_pauseImgs2DF168[];     /* 0x002DF168 image table of the pause pages */


/* ------------------------------------------------------------ chapter screen sprites (0x74160) */
extern R6gSprite r6g_chapSpr42A830[7];  /* 0x0042A830 */
extern int32_t a60_h3E694C[2], a60_h3E6940[3];
extern int32_t r6d_h3E6954;             /* 0x003E6954 */
extern int32_t r6d_g42A818, r6d_g42A824;
extern int8_t  r6d_counts2DF390[][12];  /* 0x002DF390 per video mode */
int   sub_000529F0(void);

/* ------------------------------------------------------------ 3D object model load (0x7D230) */
typedef struct R6gObjMdl {
    uint8_t  unk000[0x0C];
    uint8_t  light[0x38];     /* +0x00C */
    void    *mdl;             /* +0x044 model list */
    void    *box[6];          /* +0x048 bounding/collision boxes */
} R6gObjMdl;
extern const char r6g_srcWorld26F5A4[]; /* 0x0026F5A4 "...\app\world.c" */
uint32_t *sub_00037570(void *pack, int kind);
void *sub_000847F0(void *l, int i);
void *sub_00080DA0(void *m, void *light);
void  sub_00082120(void *box, int v);
uint16_t sub_001BA0D0(void);
void  sub_001BA0B0(int g);
void  sub_0007C2B0(R6gObjMdl *o, uint32_t *f);
void  sub_0007B070(R6gObjMdl *o, uint32_t *f);
uint8_t *sub_00053B70(const char *file, int line);
uint8_t *sub_00081A20(void *box, uint8_t *buf);
void  sub_00053890(void *p, int size);

void  sub_000A2D40(int a, uint32_t m);
void  sub_000A2D10(int a, uint32_t m);
void  sub_000A4410(int a, int b);

/* Float to int truncation (copy of RFL_FTOI): the original inlines cvttss2si
   where modern cl would call __ftol2_sse; the intrinsic is used only for the
   32-bit x86 comparison build. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R6G_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R6G_FTOI(x) ((int)(x))
/* ------------------------------------------------------------ entity teardown (0xA5520) */
/* Model record of the entity pools (0x150 bytes). */
typedef struct R6gEntMdl {
    uint8_t  unk000[0x0C];
    uint32_t flags;           /* +0x00C bit 0 attached */
    uint8_t  unk010[0x150 - 0x10];
} R6gEntMdl;
typedef struct R6gCtx { uint8_t unk000[0x1E8]; void *list1E8; } R6gCtx;
extern R6gEntMdl *r6g_entMdlA3ED52C;    /* 0x003ED52C */
extern R6gEntMdl *r6g_entMdlB3ED530;    /* 0x003ED530 */
extern void   *r6g_entTblB3ED534;       /* 0x003ED534 */
extern void   *r6g_entTblA3ED538;       /* 0x003ED538 */
extern int32_t r6g_entMode423FE4;       /* 0x00423FE4 */
extern int32_t r6g_entCount423FE8;      /* 0x00423FE8 */
extern int32_t r6g_entIds423FEC[16];    /* 0x00423FEC */
void  sub_000A4DE0(R6gSlot *s);         /* s=EAX */
void  sub_000A3810(void);


/* ------------------------------------------------------------ text table loader (0x755B0) */
typedef struct R6gTxaEnt {
    float    f00;             /* +0x00 last column */
    int32_t  v[6];            /* +0x04 columns 1, 2, 4..7 */
    uint8_t  unk1C[4];
} R6gTxaEnt;
typedef struct R6gTxa {
    char     tag[4];          /* +0x00 "@TXA" */
    int32_t  count;           /* +0x04 */
    int32_t  i08, i0C;        /* +0x08 */
    R6gTxaEnt ent[1];         /* +0x10 count entries */
} R6gTxa;
extern const char r1b_fmtD[];           /* 0x0025FB00 "%d" */
extern const char r1b_fmtF[];           /* 0x0025FAFC "%f" */
void  sub_00013040(void);
char *sub_000134C0(void *a, void *b);
char *sub_00012FA0(char **pp);
char *sub_00013140(char **pp);
int   sub_001C7C70(const char *s, const char *fmt, ...);
void  sub_00012F90(void);
void  sub_000130C0(void);

/* ------------------------------------------------------------ movie screen state (0x78F50) */
extern int32_t a60_v3E7530, a60_v3E7508, a60_v3E750C, a60_v3E7510, a60_v3E7514;
extern int32_t a60_v3E74B8;
extern int32_t r6c_v3E7550;             /* 0x003E7550 */
extern int32_t *r1f_g42C7A0;            /* 0x0042C7A0 */
extern uint8_t a60_buf3E75F4[1], a60_buf3E7690[1], a60_buf3E772C[1], a60_buf3E77C8[1];
void  sub_0019B9E0(void);
void  sub_00048590(void);
int   sub_00047950(void);
void  sub_0019B9F0(void);
void  sub_0019D8A0(int a);
void  sub_00054160(int a);
void  sub_001A0D30(int a, int b);
void  sub_001A8A70(int a);
int   sub_00054180(void);
void  sub_00078050(void);
void  sub_000150B0(void *p, int n);


#endif
extern float a50_framesPerSecond;       /* 0x0042C964 */
int   sub_000A4370(int a);
void  sub_000D9B30(int bit);

/* ------------------------------------------------------------ entity teardown (0xA5520) */
/* Model record of the entity pools (0x150 bytes). */
typedef struct R6gEntMdl {
    uint8_t  unk000[0x0C];
    uint32_t flags;           /* +0x00C bit 0 attached */
    uint8_t  unk010[0x150 - 0x10];
} R6gEntMdl;
typedef struct R6gCtx { uint8_t unk000[0x1E8]; void *list1E8; } R6gCtx;
extern R6gEntMdl *r6g_entMdlA3ED52C;    /* 0x003ED52C */
extern R6gEntMdl *r6g_entMdlB3ED530;    /* 0x003ED530 */
extern void   *r6g_entTblB3ED534;       /* 0x003ED534 */
extern void   *r6g_entTblA3ED538;       /* 0x003ED538 */
extern int32_t r6g_entMode423FE4;       /* 0x00423FE4 */
extern int32_t r6g_entCount423FE8;      /* 0x00423FE8 */
extern int32_t r6g_entIds423FEC[16];    /* 0x00423FEC */
void  sub_000A4DE0(R6gSlot *s);         /* s=EAX */
void  sub_000A3810(void);

/* ------------------------------------------------------------ script tokenizer (0x90100) */
typedef struct R6gTok {
    char     text[0x100];     /* +0x000 token, upper-cased */
    uint8_t  skipped;         /* +0x100 blanks skipped before it */
    uint8_t  len;             /* +0x101 */
    uint8_t  pad102[2];
    int32_t  kind;            /* +0x104 0 ':', 1 word/number, 2 newline, 3 end */
} R6gTok;

/* ------------------------------------------------------------ text table loader (0x755B0) */
typedef struct R6gTxaEnt {
    float    f00;             /* +0x00 last column */
    int32_t  v[6];            /* +0x04 columns 1, 2, 4..7 */
    uint8_t  unk1C[4];
} R6gTxaEnt;
typedef struct R6gTxa {
    char     tag[4];          /* +0x00 "@TXA" */
    int32_t  count;           /* +0x04 */
    int32_t  i08, i0C;        /* +0x08 */
    R6gTxaEnt ent[1];         /* +0x10 count entries */
} R6gTxa;
extern const char r1b_fmtD[];           /* 0x0025FB00 "%d" */
extern const char r1b_fmtF[];           /* 0x0025FAFC "%f" */
void  sub_00013040(void);
char *sub_000134C0(void *a, void *b);
char *sub_00012FA0(char **pp);
char *sub_00013140(char **pp);
int   sub_001C7C70(const char *s, const char *fmt, ...);
void  sub_00012F90(void);
void  sub_000130C0(void);

/* ------------------------------------------------------------ movie screen state (0x78F50) */
extern int32_t a60_v3E7530, a60_v3E7508, a60_v3E750C, a60_v3E7510, a60_v3E7514;
extern int32_t a60_v3E74B8;
extern int32_t r6c_v3E7550;             /* 0x003E7550 */
extern int32_t *r1f_g42C7A0;            /* 0x0042C7A0 */
extern uint8_t a60_buf3E75F4[1], a60_buf3E7690[1], a60_buf3E772C[1], a60_buf3E77C8[1];
void  sub_0019B9E0(void);
void  sub_00048590(void);
int   sub_00047950(void);
void  sub_0019B9F0(void);
void  sub_0019D8A0(int a);
void  sub_00054160(int a);
void  sub_001A0D30(int a, int b);
void  sub_001A8A70(int a);
int   sub_00054180(void);
void  sub_00078050(void);
void  sub_000150B0(void *p, int n);

/* ------------------------------------------------------------ movie task loop (0x791A0) */
typedef struct R6gMovieEnt { int32_t id; void (*fn)(void); } R6gMovieEnt;
extern R6gMovieEnt *r6g_movieEnts3E74B0;/* 0x003E74B0 */
extern int32_t r6g_movieSel3E74B4;      /* 0x003E74B4 */
extern uint8_t r6c_obj3E73A0[];         /* 0x003E73A0 */
void  sub_00078270(void);
void  sub_00078F50(void);
void  sub_00078E70(void);
void  sub_00053CA0(int a);
int   sub_0001B150(void *o, int a);
void  sub_0001AE90(void *o);
void  sub_001A0D70(void);
void  sub_00058190(void);

#endif
