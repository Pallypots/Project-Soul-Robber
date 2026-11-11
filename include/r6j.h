#ifndef R6J_H
#define R6J_H
#include "oogie.h"
/* Area r6j: larger functions (300-2500 bytes) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6j.csv. Callees are declared under their sub_ name
   (or an existing name with the same VA). */

/* Float to int truncation (copy of RFL_FTOI). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R6J_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R6J_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ menu item availability (0x605B0) */
int  sub_000D9A70(int bit);               /* event flag bit test */
extern int32_t r6i_g413178;               /* 0x00413178 */

/* ------------------------------------------------------------ shop list page draw (0x60BF0) */
/* Sprite record (0x9C bytes, layout of R6hSprite / R6gSprite). */
typedef struct R6jSprite {
    float    x, y;            /* +0x00 */
    uint8_t  unk08[0x80 - 0x08];
    int32_t  mode;            /* +0x80 */
    uint8_t  unk84[0x8C - 0x84];
    uint32_t color;           /* +0x8C */
    uint8_t  unk90[0x9C - 0x90];
} R6jSprite;
extern R6jSprite r6j_shopSpr3E6114[6];    /* 0x003E6114 row, up arrow, down arrow, price tag, item name, help text */
extern int16_t   a60_w3E60F8, a60_w3E60FA; /* cursor row, list top */
extern uint8_t   r6i_alpha3E60FC;         /* 0x003E60FC fade alpha */
extern uint16_t  r6h_menuItems3E6104[];   /* 0x003E6104 */
extern uint16_t  r6h_menuCount3E6112;     /* 0x003E6112 */
extern const float   r6j_rowY2DDAF4[3];   /* 0x002DDAF4 row y positions */
extern const uint8_t r6j_itemTag2DD9EC[]; /* 0x002DD9EC price tag frame per item */
extern const int32_t r6d_prices[];        /* 0x002DDA20 item prices */
void  sub_000150B0(R6jSprite *s, int frame);
void *sub_00017C00(void *cmd, R6jSprite *s);
void *r1d_TrackApplyD(void *cmd, R6jSprite *s);   /* 0x00017C90 */
void  sub_00014E80(R6jSprite *s);
void *sub_0002B950(void *cmd, float x, float y, uint32_t color, int value);
int   sub_000529F0(void);                 /* video mode 0..6 */

/* ------------------------------------------------------------ room scripts */
/* Three-word script state (layout of R6iKeyStep). */
typedef struct R6jStep {
    uint32_t flags;           /* +0x0 */
    int32_t  phase;           /* +0x4 */
    int32_t  count;           /* +0x8 frames in the script */
} R6jStep;
/* Actor record (0x260 bytes each at 0x004242C0; only touched fields). */
typedef struct R6jActor {
    uint32_t flags;           /* +0x000 bit 0x800 motion done */
    uint8_t  unk004[0x48 - 0x04];
    int32_t  state48;         /* +0x048 */
    uint8_t  unk04C[0x70 - 0x4C];
    float    pos70[4];        /* +0x070 x, y, z, w */
    uint8_t  unk080[0x120 - 0x80];
    void    *model120;        /* +0x120 (returned by 0x000A42A0) */
    uint8_t  unk124[0x260 - 0x124];
} R6jActor;
extern R6jActor aa0_slots[32];            /* 0x004242C0 actor records */
extern uint64_t  a50_frameCounter0;       /* 0x0042C918 frame counter */
R6jActor *sub_000A4290(int idx);          /* actor record idx of 0x004242C0 */
void  sub_000A42F0(int idx, int v);
void  sub_000A4410(int id, int on);
int   sub_000A2CE0(int idx, uint32_t mask);
void  sub_000A2CC0(int idx, uint32_t mask);
void  sub_000CAE20(PlayerStats *p, float v);
int   r6b_Slot0Value110(void);            /* 0x00095300 */
void  sub_000A2D40(int idx, uint32_t mask);
void  sub_000A2D10(int idx, uint32_t mask);
void  sub_000A2CA0(int idx, uint32_t mask);
void  sub_000A3620(int idx, int v);
void  sub_000A2DD0(int idx, int a, int b);
void  sub_000DFD40(int32_t *chapter, int32_t *stage);

/* ------------------------------------------------------------ script text tokenizer (0x90100) */
typedef struct R6jToken {
    char     text[0x100];     /* +0x000 upper-cased token text */
    uint8_t  lead;            /* +0x100 skipped blanks */
    uint8_t  len;             /* +0x101 */
    uint8_t  pad102[2];
    int32_t  kind;            /* +0x104 0 ':' 1 word 2 new line 3 end */
} R6jToken;
void  sub_000A43C0(int idx, int v);
void  sub_000A5450(int idx);
int   sub_000A4370(int idx);
extern uint8_t ae0_obj3E1270[];           /* 0x003E1270 camera object */
void  sub_00019000(void *cam, int mode);
void  sub_0001AB00(void *cam, int a, int b, int c, int d);
void  sub_0019BE90(int id);
void  sub_0019BEB0(int id);
void  sub_000D1930(PlayerStats *p);
void  sub_000DDF20(int32_t *a, int32_t *b);

/* Model objects reached through actor records (only touched fields). */
typedef struct R6jMat {
    uint8_t  unk00[0xC4];
    float    fC4;             /* +0xC4 */
} R6jMat;
typedef struct R6jNode {
    uint8_t  unk00[0x14];
    R6jMat  *mat14;           /* +0x14 */
} R6jNode;
typedef struct R6jPart {
    uint8_t  unk00[0x30];
    R6jNode *node30;          /* +0x30 */
} R6jPart;
typedef struct R6jModel {
    uint8_t  unk00[0x30];
    R6jNode *node30;          /* +0x30 */
    uint8_t  unk34[0x3C - 0x34];
    R6jPart *part3C;          /* +0x3C */
    uint8_t  unk40[0x60 - 0x40];
    float    pos60[4];        /* +0x60 */
} R6jModel;
extern int32_t a30_g413170;               /* 0x00413170 */
R6jModel *sub_000A42A0(int idx);          /* model of actor record idx (+0x120) */
void  sub_000F5D40(void *dst, const void *src);
void  sub_00036C00(int a, int b, float t); /* screen fade (dir, colour, seconds) */
int   sub_00036D40(void);                  /* fade running */
void  sub_000D9AB0(int bit);              /* set event flag */
void  sub_000D9B30(int bit);              /* clear event flag */
int   sub_00145780(void *model, float t); /* animation passed time t */
void  sub_0001B3F0(void *model);
extern float a50_framesPerSecond;         /* 0x0042C964 */
extern uint32_t r6j_g420DAC;              /* 0x00420DAC g_stats + 0xEEC */
extern const int32_t r6j_trapDamage2E5EE0[]; /* 0x002E5EE0 damage by 0x00413178 */
extern const int32_t r6j_trapDamage2E5910[]; /* 0x002E5910 damage by 0x00413178 */
extern const int32_t r6j_trapDamage2E4ECC[]; /* 0x002E4ECC damage by 0x00413178 */
extern const int32_t r6j_trapDamage2E4C54[]; /* 0x002E4C54 damage by 0x00413178 */
extern const int32_t r6j_trapDamage2E4FF0[]; /* 0x002E4FF0 damage by 0x00413178 */
void  sub_00048AF0(int sound);
void  sub_000D1D00(PlayerStats *p);
void  sub_000DDEF0(int a, int b);
void  sub_000DDF40(void);
void  sub_0019D8B0(void);
void  sub_000A2E10(int idx, int v);
void  a80_Set3ED238(void);                /* 0x00087510 */
void  sub_00087BA0(void);
void  a80_Set3ED23C(int v);               /* 0x00087520 */
void  sub_00019350(int frames, float t);  /* screen shake (frames, strength) */
void  sub_000AA2E0(int id);
int   sub_00048A00(int a, int b);
int   sub_00047F20(void);                 /* returns 0x003DFEC0 */
void *sub_00047F30(void);                 /* returns 0x003DFECC */
void  sub_00049180(void *snd, int ch, int a, float vol, int b, int c, float d);

#endif
