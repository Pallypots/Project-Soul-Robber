#ifndef R6H_H
#define R6H_H
#include "oogie.h"
#include "shared_decls.h"
/* Area r6h: larger functions (300-2500 bytes) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6h.csv. Callees are declared under their sub_ name
   (or an existing name with the same VA) so that cl never inlines a function
   recovered in this area into another one. Self-contained: no other area
   header is included, to keep prototypes from clashing. */

/* ------------------------------------------------------------ page state machine (0x6D910) */
typedef void (*R6hPageFn)(void);
extern int32_t   r6g_g428F20;             /* 0x00428F20 page phase */
extern uint8_t   r6g_b428F80[8];          /* 0x00428F80 current page / next page bytes */
extern uint8_t   a4c_obj428F40[];         /* 0x00428F40 fade timer object */
extern uint8_t  *a60_work42C5E8;          /* 0x0042C5E8 work block */
extern R6hPageFn r6h_pageEnter2DF108[];   /* 0x002DF108 enter function per page */
extern R6hPageFn r6h_pageLeave2DF124[];   /* 0x002DF124 leave function per page */
uint16_t sub_00072FA0(void *obj);
void  sub_00072EE0(void *o, int a, float t, int b);
int   sub_00053C90(void);
void  sub_0006C3F0(void);
void  sub_0006A2E0(void);
void  sub_0006BF80(void);
void  sub_00065310(void);
void  sub_00074DB0(void);
void  sub_00071F90(void);
void  sub_0006D780(void);

/* ------------------------------------------------------------ title particles (0x6C270, 0x6C750) */
/* Particle kind records at 0x002DF0C8 (16 bytes each, four of them). */
typedef struct R6hFxKind {
    uint32_t color;           /* +0x0 RGB of the particle sprite */
    uint8_t  alpha;           /* +0x4 alpha scale */
    uint8_t  sprite;          /* +0x5 sprite index */
    uint8_t  count;           /* +0x6 particles in use */
    uint8_t  range;           /* +0x7 speed range (rand modulus) */
    float    life;            /* +0x8 lifetime */
    float    fade;            /* +0xC fade rate */
} R6hFxKind;
/* Particle records at 0x003E6628 (20 bytes each). */
typedef struct R6hFx {
    float x, y;               /* +0x00 */
    float vx, vy;             /* +0x08 */
    float life;               /* +0x10 */
} R6hFx;
extern R6hFxKind r6h_fxKinds2DF0C8[];
extern R6hFx     r6h_fx3E6628[];
int   sub_001C7EE1(void);
float sub_001A3ED0(float x);
void  sub_0006C270(int idx, int alt, int kind);   /* idx=EAX alt=ECX kind=EDX */
/* Sprite record (0x9C bytes, same layout as R6gSprite of area r6g). */
typedef struct R6hSprite {
    float    x, y;            /* +0x00 */
    uint8_t  unk08[0x1C - 0x08];
    float    sx, sy;          /* +0x1C scale */
    uint8_t  unk24[0x80 - 0x24];
    int32_t  mode;            /* +0x80 */
    uint8_t  unk84[0x8C - 0x84];
    uint32_t color;           /* +0x8C */
    uint8_t  unk90[0x9C - 0x90];
} R6hSprite;
/* Screen quad passed to 0x00072420 (0x38 bytes). */
typedef struct R6hQuad {
    float    x, y, w, h;      /* +0x00 */
    float    u0, v0, u1, v1;  /* +0x10 */
    uint32_t col[4];          /* +0x20 */
    int32_t  tex;             /* +0x30 */
    int32_t  z;               /* +0x34 */
} R6hQuad;
typedef struct R6hVec2 { float x, y; } R6hVec2;
extern R6hSprite r6h_titleSpr42C27C[5];   /* 0x0042C27C title letters */
extern R6hVec2   r6h_titlePos42C588[5];   /* 0x0042C588 animated letter positions */
extern R6hVec2   r6h_titleScl42C5B0[5];   /* 0x0042C5B0 animated letter scales */
extern const R6hVec2 r6h_titleOff2DF140[5]; /* 0x002DF140 letter offsets */
extern R6hSprite r6h_fxSpr428FB4;         /* 0x00428FB4 particle sprite */
extern int32_t   a60_h42C6F0;             /* 0x0042C6F0 title background texture */
extern int32_t   a60_v3E68A8;             /* 0x003E68A8 */
void *sub_00072420(void *cmd, R6hQuad *q);
void *sub_000720D0(void *cmd, float x, float y, float w, float h, int tex,
                   uint32_t c0, uint32_t c1, uint32_t c2, uint32_t c3);
void *sub_0006E960(void *cmd);
void  sub_000720A0(float *t, int a);

/* ------------------------------------------------------------ demo (cutscene) objects (0x89C10) */
/* Demo work block (0x184 bytes, allocated by 0x00089C10). */
typedef struct R6hView { uint32_t v[6]; } R6hView;
typedef struct R6hDemoWk {
    uint32_t flags;           /* +0x000 */
    R6hView  view;            /* +0x004 scene view, copied as a whole */
    int32_t  w1C;             /* +0x01C */
    int32_t  w20;             /* +0x020 */
    uint8_t  keys[0x50];      /* +0x024 key arrays (0x00090020) */
    uint8_t  holder[4];       /* +0x074 slot holder (0x0008FEE0) */
    uint8_t  tag[4];          /* +0x078 sound tag, 5 bytes copied with b7C[0] */
    uint8_t  b7C[4][64];      /* +0x07C */
    uint8_t  unk17C[0x184 - 0x17C];
} R6hDemoWk;
typedef struct R6hDemo {
    int32_t  state;           /* +0x00 */
    int32_t  id;              /* +0x04 */
    float    t8, tC, t10;     /* +0x08 */
    uint8_t  unk14[0x48 - 0x14];
    void    *list;            /* +0x48 */
    R6hDemoWk *wk;            /* +0x4C */
} R6hDemo;
typedef struct R6hKeyVal { int32_t key; uint32_t val; } R6hKeyVal;
extern const char      r6h_demoFile26FAFC[];   /* 0x0026FAFC source file name */
extern const R6hKeyVal r6h_demoFlags26FA30[8]; /* 0x0026FA30 */
extern const uint8_t   r6h_demoTag26FB40[5];   /* 0x0026FB40 */
extern uint8_t  r4c_opt413140;                 /* 0x00413140 */
extern void    *a80_ctx42C8E4;                 /* 0x0042C8E4 */
int   sub_0008BD00(int i);
void *sub_0008FB60(void);
R6hView *sub_0007AB00(void *ctx);
void *sub_0007AAB0(void *ctx);
void  sub_00090020(void *p);
void  sub_0008FEE0(void *p);
void  sub_0008FF30(void *p, void *v);
void  sub_0008FF60(void *p, void *v);
void  sub_00089880(R6hDemo *d);
void  sub_00033390(void);
void  sub_00035B20(void *v);

/* ------------------------------------------------------------ demo key lists (0x8A0C0) */
typedef struct R6hKeyRef {
    uint8_t  unk00[0x1A];
    uint8_t  kind;            /* +0x1A */
    uint8_t  unk1B;
    void    *target;          /* +0x1C */
} R6hKeyRef;
typedef struct R6hKey {
    float    time;            /* +0x00 */
    int8_t   track;           /* +0x04 */
    int8_t   chan;            /* +0x05 */
    uint8_t  unk06[2];
    R6hKeyRef *ref;           /* +0x08 */
    int32_t  value;           /* +0x0C */
} R6hKey;
typedef struct R6hNode {
    uint8_t  unk00[0x1C];
    R6hKey  *key;             /* +0x1C */
} R6hNode;
R6hNode *sub_0008B290(R6hNode *list, int track, int chan);
R6hNode *sub_0007F300(R6hNode *n);
void     sub_0008B760(R6hNode *n);
R6hNode *sub_0008B780(R6hNode *a, R6hNode *b);
R6hNode *sub_0007F330(R6hNode *n);

/* ------------------------------------------------------------ demo key stream (0x8B9E0) */
/* Key descriptor records (0x24 bytes; +0x08 = stored size of the key kind). */
typedef struct R6hDescRec { uint8_t unk00[8]; int32_t size; uint8_t unk0C[0x24 - 0x0C]; } R6hDescRec;
typedef R6hDescRec *(*R6hDescGetter)(void);
extern R6hDescGetter a8b_descGetters[8];      /* 0x002E0D68 per key group */
/* Stored key body (the node's key copied from the stream). */
typedef struct R6hKeyBody {
    uint8_t  unk00[4];
    int8_t   group;           /* +0x04 0xFF ends the stream */
    int8_t   kind;            /* +0x05 */
    uint8_t  unk06[2];
    int32_t  link;            /* +0x08 index of the linked node, -1 none */
    uint8_t  unk0C[4];
    uint32_t bits;            /* +0x10 top byte cleared for group 8 kind 1 */
} R6hKeyBody;
typedef struct R6hBodyNode {
    uint8_t  unk00[0x1C];
    R6hKeyBody *body;         /* +0x1C */
} R6hBodyNode;
R6hBodyNode *sub_0008B980(int group, int kind);
void *sub_0007F390(void *parent, int index);
void  sub_0008B3B0(R6hKeyBody *k, void *link);
void  sub_0008B400(void *list);

/* ------------------------------------------------------------ texture scroll animation, tex_ex.c (0x74F40) */
typedef struct R6hTexLayerA {          /* 0x100 bytes (object type 5) */
    uint8_t  unk000[0xC4];
    int32_t  tex;             /* +0xC4 */
    uint8_t  unk0C8[0xE4 - 0xC8];
    float    u, v;            /* +0xE4 scroll offsets */
    float    du, dv;          /* +0xEC scroll speeds */
    uint8_t  unk0F4[0x100 - 0xF4];
} R6hTexLayerA;
typedef struct R6hTexLayerB {          /* 0x108 bytes (object type 1) */
    uint8_t  unk000[0xC4];
    int32_t  tex;             /* +0xC4 */
    uint8_t  unk0C8[0xEC - 0xC8];
    float    u, v;            /* +0xEC */
    float    du, dv;          /* +0xF4 */
    uint8_t  unk0FC[0x108 - 0xFC];
} R6hTexLayerB;
typedef struct R6hTexObj {
    uint8_t  unk00[0x8C];
    int32_t  type;            /* +0x8C */
    uint8_t  unk90[0xC0 - 0x90];
    int32_t  count;           /* +0xC0 */
    void    *layers;          /* +0xC4 */
} R6hTexObj;
typedef struct R6hTexNode {
    struct R6hTexNode *next;  /* +0x0 */
    uint8_t  unk04[8];
    R6hTexObj *obj;           /* +0xC */
} R6hTexNode;
extern R6hTexNode *r6h_texAnims3E6998;  /* 0x003E6998 */
extern float a50_frameUnits;            /* 0x0042C858 frame time */

/* ------------------------------------------------------------ texture animation table loader, tex_ex.c (0x75220) */
typedef struct R6hTexSize { uint8_t unk00[0xC]; uint32_t h; uint32_t w; } R6hTexSize;
typedef struct R6hTexEnt  { uint8_t unk00[0x14]; R6hTexSize *size; } R6hTexEnt;
typedef struct R6hTxaFrame { float frame, u, v; int32_t pad; } R6hTxaFrame;
typedef struct R6hTxa {
    char     magic[4];        /* +0x0 "@TXA" */
    int32_t  count;           /* +0x4 */
    int32_t  unk8, unkC;      /* +0x8 */
    R6hTxaFrame frames[1];    /* +0x10 */
} R6hTxa;
extern const char r1b_fmtF[];           /* 0x0025FAFC "%f" */
void  sub_00013040(void);
char *sub_000134C0(void *a, void *b);
char *sub_00012FA0(char **pp);
char *sub_00013140(char **pp);
int   sub_001C7C70(const char *s, const char *fmt, ...);
void  sub_00012F90(void);
void  sub_000130C0(void);

/* ------------------------------------------------------------ menu item lists (0x603C0) */
extern int16_t r6h_menuItems3E6104[7];  /* 0x003E6104 item ids of the current list */
extern int16_t r6h_menuCount3E6112;     /* 0x003E6112 */
extern int32_t rfl_level413178;         /* 0x00413178 */
int   sub_000D9A70(int bit);

/* ------------------------------------------------------------ character model setup, y_character.c (0x7E720) */
typedef struct R6hMdlRes {
    uint8_t  unk00[0x8C];
    int32_t  type;            /* +0x8C */
    uint8_t  unk90[0xC0 - 0x90];
    int32_t  count;           /* +0xC0 */
} R6hMdlRes;
typedef struct R6hMdlSkel {
    uint8_t  unk00[0x14];
    void    *node;            /* +0x14 0xE0-byte node */
    void    *bones;           /* +0x18 0x130 bytes per bone */
} R6hMdlSkel;
typedef struct R6hChar {
    uint8_t  unk000[0x20];
    R6hMdlRes *res;           /* +0x020 */
    uint8_t  unk024[0x30 - 0x24];
    R6hMdlSkel *skel;         /* +0x030 */
    uint8_t  unk034[0x14C - 0x34];
    int32_t  kind;            /* +0x14C */
} R6hChar;
typedef struct R6hFxParm { int32_t unk0; int32_t a; int32_t unk8; int32_t b; int32_t unk10; int32_t c; } R6hFxParm;
int   sub_0007F4B0(int i);
void  sub_00053710(int heap);
void  sub_00053740(void);
void  sub_001AEA00(void *bones, void *node, int n);
void  sub_0001E9B0(void *ctx, R6hChar *c, int a, int b, int d);
R6hFxParm *sub_00039810(int i);

/* ------------------------------------------------------------ status screen texture release (0x64B50) */
extern int32_t a60_hA3E64C4[3];   /* 0x003E64C4 sub-page 0 textures */
extern int32_t a60_hB3E64D0[3];   /* 0x003E64D0 sub-page 1 textures */
extern int32_t a60_h3E64DC;       /* 0x003E64DC sub-page 1 fourth texture */
extern int32_t a60_hC3E64E0[3];   /* 0x003E64E0 sub-page 3 textures */
extern int32_t a60_hD3E64EC[3];   /* 0x003E64EC sub-page 2 textures */
void  sub_001B9720(void);

/* ------------------------------------------------------------ demo player, demo_player.c area (0x8CE10) */
typedef struct R6hDemoData {
    uint8_t  unk00[0x1C];
    void    *keys;            /* +0x1C key list */
    void    *events;          /* +0x20 event list */
} R6hDemoData;
typedef struct R6hDemoPlayer {
    uint8_t  unk00[4];
    uint8_t  done;            /* +0x04 */
    uint8_t  unk05[3];
    int32_t  state;           /* +0x08 */
    R6hDemoData *demo;        /* +0x0C */
} R6hDemoPlayer;
extern const int32_t r6h_demoTracks2700E0[12];  /* 0x002700E0 track ids loaded by the demo player */
void  sub_000893C0(R6hDemoData *d);
void  sub_0008BCF0(int a, int b);
int   sub_000898C0(R6hDemoData *d, int track, int pass);
int   sub_0008B480(void **dst, void *list);
int   sub_0008C9B0(void **dst, void *list);
void  sub_000894E0(R6hDemoData *d);
uint8_t sub_000896E0(R6hDemoData *d);
void  sub_000899C0(R6hDemoData *d);
void  sub_000896C0(R6hDemoData *d, int flags);

/* ------------------------------------------------------------ event triggers (0x94C10) */
typedef struct R6hEvtObj {
    uint32_t flags;           /* +0x0 bit 28: pending */
    int32_t  kind;            /* +0x4 */
} R6hEvtObj;
extern int32_t a30_g41316C;       /* 0x0041316C chapter */
extern int32_t a30_g413170;       /* 0x00413170 stage of the chapter */
int   sub_000A44C0(R6hEvtObj *e);
void  sub_000D9AB0(int bit);

/* ------------------------------------------------------------ actor intro animation (0x9ED40) */
typedef struct R6hActRef { uint8_t unk00[0xC]; uint8_t flags; } R6hActRef;
typedef struct R6hActor {
    uint8_t  unk000[0x40];
    int32_t  state;           /* +0x040 */
    uint8_t  unk044[0x120 - 0x44];
    R6hChar *model;           /* +0x120 */
    uint8_t  unk124[0x12C - 0x124];
    R6hActRef *ref;           /* +0x12C */
} R6hActor;
void  sub_000A4010(R6hActor *a, int anim);
int   sub_0017C4D0(void);
void  sub_000A22C0(R6hActor *a, R6hActRef *r);
void  sub_000A5440(R6hActor *a);

/* ------------------------------------------------------------ event script step (0xB3C80) */
typedef struct R6hScr {
    uint32_t flags;           /* +0x0 bit 0: id comes from the script reader */
    int32_t  state;           /* +0x4 10, 11, 0x63 */
} R6hScr;
extern uint8_t ae0_obj3E1270[];   /* 0x003E1270 */
void  sub_000DFD40(int *err, int *id);
int   sub_000A4370(int id);
void  sub_000CF4E0(PlayerStats *s);
void  sub_0019BEB0(int a);
void  sub_00019000(void *o, int a);
void  sub_000A4340(int id, int a);
void  sub_000DDF20(int *a, int *b);
void  sub_0019BE90(int a);
void  sub_0001AB00(void *o, int a, int b, int c, int d);
void  sub_000D1D00(PlayerStats *s);

/* ------------------------------------------------------------ door/switch event scripts (0xB3EB0, 0xB16F0) */
typedef struct R6hScr3 {
    uint32_t flags;           /* +0x0 */
    int32_t  state;           /* +0x4 */
    int32_t  ticks;           /* +0x8 steps run */
} R6hScr3;
typedef struct R6hSwitch { uint8_t unk00[0x48]; int32_t pos; } R6hSwitch;
void  sub_000A2D40(int obj, int bits);
void  sub_000A2D10(int obj, int bits);
void  sub_000A2CC0(int obj, uint32_t bits);
void  sub_000A2CA0(int obj, uint32_t bits);
void  sub_000A4410(int obj, int on);
R6hSwitch *sub_000A4290(int obj);
void  sub_000A42F0(int obj, int a);

/* ------------------------------------------------------------ menu boot sequence (0x6D350) */
extern int32_t  a60_v3E6620;       /* 0x003E6620 boot step */
extern int32_t  a60_cmd3E6610;     /* 0x003E6610 page to open */
extern int32_t  a60_arg3E661C;     /* 0x003E661C argument of the page */
extern int32_t  a60_flag428F78;    /* 0x00428F78 */
extern int32_t  r6h_g42A014;       /* 0x0042A014 status group */
extern int32_t  r6g_menuItem42A018;/* 0x0042A018 */
extern int32_t  r6h_g42A01C;       /* 0x0042A01C */
extern uint32_t r6d_g42A818;       /* 0x0042A818 */
extern uint32_t r6d_g42A824;       /* 0x0042A824 */
int   sub_000529F0(void);
int   sub_0004F6D0(int id);
int   sub_0004F6B0(int id);
int   sub_0004F4D0(void);
void  sub_00065AE0(int v);
void  sub_00065A50(int v);
void  sub_0006BFA0(void);
void  sub_0006B5D0(int v);
void  sub_00064CE0(int v);
void  sub_00074510(int v);
void  sub_0006E6B0(int v);
void  sub_0006EA20(int v);
void  sub_0004F700(int id);
void  sub_0004F720(void);
int   sub_0006CAB0(void);

/* ------------------------------------------------------------ node local matrix (0x7E350) */
typedef struct R6hXform {
    uint8_t  unk00[0xC];
    uint8_t  flags;           /* +0x0C bit 0: transform active */
    uint8_t  unk0D[0x20 - 0xD];
    void    *target;          /* +0x20 */
    uint8_t  unk24[0x50 - 0x24];
    float    rot[3];          /* +0x50 degrees */
    uint8_t  unk5C[4];
    float    pos[3];          /* +0x60 */
    uint8_t  unk6C[4];
    float    scale[3];        /* +0x70 */
} R6hXform;
typedef struct R6hXNode { uint8_t unk00[0x5C]; R6hXform *xf; } R6hXNode;
void  sub_001AD910(float m[4][4], float s[4][4], float a);
void  sub_001AD8B0(float m[4][4], float s[4][4], float a);
void  sub_001ADBA0(float *d, float *s, float k);

/* ------------------------------------------------------------ actor model sync (0xA3B80) */
typedef struct R6hVec4 { float x, y, z, w; } R6hVec4;
typedef struct R6hBody {
    uint8_t  unk00[0x8];
    int32_t  type;            /* +0x08 */
    uint32_t flags;           /* +0x0C bit 8: matrix driven by the node */
    uint8_t  unk10[0x20 - 0x10];
    uint8_t *node;            /* +0x20 (+0x30: node position) */
    uint8_t  unk24[0x40 - 0x24];
    R6hVec4  v40;             /* +0x40 */
    R6hVec4  rot;             /* +0x50 */
    R6hVec4  pos;             /* +0x60 */
} R6hBody;
typedef struct R6hActor2 {
    uint32_t flags;           /* +0x000 */
    uint8_t  unk004[0x10 - 0x4];
    float    scale;           /* +0x010 */
    uint8_t  unk014[0x70 - 0x14];
    R6hVec4  pos;             /* +0x070 */
    R6hVec4  rot;             /* +0x080 */
    uint8_t  unk090[0x120 - 0x90];
    R6hBody *body;            /* +0x120 */
} R6hActor2;

/* ------------------------------------------------------------ curve keys (0xA32A0) */
/* Six slices of n floats carved from one block by 0x00062050 (layout of A60Slices). */
typedef struct R6hSlices {
    int32_t  unk00;
    float   *s[6];            /* +0x04 */
} R6hSlices;
typedef struct R6hCurves {
    R6hSlices sl[3];          /* +0x00, +0x1C, +0x38 */
    uint8_t  unk54[0x5C - 0x54];
    float    buf[3][18];      /* +0x5C, +0xA4, +0xEC */
} R6hCurves;
void  sub_00062050(R6hSlices *s, float *base, int n);
void  sub_00061C50(R6hSlices *s, int n);

/* ------------------------------------------------------------ attack hit test (0xA1220) */
typedef struct R6hHitter {
    uint32_t flags;           /* +0x000 */
    int32_t  kind;            /* +0x004 */
    uint8_t  unk008[0x20 - 0x8];
    float    off[3];          /* +0x020 hit centre offset */
    float    radius[3];       /* +0x02C */
    uint8_t  unk038[0x70 - 0x38];
    R6hVec4  pos;             /* +0x070 */
    uint8_t  unk080[0x120 - 0x80];
    R6hBody *body;            /* +0x120 */
} R6hHitter;
typedef struct R6hHitBox {
    uint8_t  unk00[0x20];
    uint8_t *node;            /* +0x20 (+0x70: node matrix/position) */
    uint8_t  unk24[0xA0 - 0x24];
    R6hVec4  centre;          /* +0xA0 */
    float    size[2];         /* +0xB0 */
} R6hHitBox;
extern void *g_playerObj;     /* 0x00420E98 (+0x60 position) */
int   sub_000A2890(R6hVec4 *a, R6hVec4 *b, R6hVec4 *c, R6hVec4 *d);
void  sub_001AD9F0(R6hVec4 *d, void *a, void *b);
int   sub_000D3BF0(PlayerStats *s, R6hBody *b, int a, R6hVec4 *out, R6hVec4 *dir);
void  sub_00135EB0(int a);

/* ------------------------------------------------------------ wandering object (0xA6B50) */
typedef struct R6hWander {
    uint32_t flags;           /* +0x00 */
    uint8_t  unk04[0x20 - 0x4];
    int32_t  state;           /* +0x20 */
    uint8_t  unk24[0x2C - 0x24];
    float    speed;           /* +0x2C */
    uint8_t  unk30[0x54 - 0x30];
    float    heading;         /* +0x54 radians */
    uint8_t  unk58[0x64 - 0x58];
    float    v64;             /* +0x64 */
    uint8_t  unk68[0x90 - 0x68];
    float    timer;           /* +0x90 */
    float    dur;             /* +0x94 */
    float    turn;            /* +0x98 radians per frame unit */
} R6hWander;

/* ------------------------------------------------------------ spinning object (0xA59D0) */
typedef struct R6hSpinner {
    uint32_t flags;           /* +0x00 bit 27: coloured on start */
    int32_t  kind;            /* +0x04 */
    uint8_t  unk08[0x10 - 0x8];
    float    scale;           /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    int32_t  state;           /* +0x20 */
    uint8_t  unk24[0x54 - 0x24];
    float    heading;         /* +0x54 */
    uint8_t  unk58[0xD8 - 0x58];
    void    *model;           /* +0xD8 */
} R6hSpinner;
void  sub_000D04E0(void *model, float *rgba);

/* ------------------------------------------------------------ motion record reset (0xA7700) */
typedef struct R6hMotion {
    uint32_t flags;           /* +0x00 */
    int32_t  v04;             /* +0x04 */
    float    f08, f0C;        /* +0x08 */
    float    f10;             /* +0x10 (1.0) */
    float    f14;             /* +0x14 (10.0) */
    int32_t  target;          /* +0x18 (-1) */
    int32_t  v1C, v20;        /* +0x1C */
    float    f24, f28, f2C;   /* +0x24 (0, 4, 0) */
    R6hVec4  v[5];            /* +0x30..+0x7F (0,0,0,1) each */
    uint8_t  unk80[0x90 - 0x80];
    int32_t  w[16];           /* +0x90 */
    int32_t  vD0, vD4, vD8;   /* +0xD0 */
} R6hMotion;

#endif
