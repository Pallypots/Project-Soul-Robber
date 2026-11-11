#ifndef R1B_H
#define R1B_H
#include "oogie.h"
#include <string.h>

/* Area r1b: game functions 0x00012000..0x00060000 (second pass). Names
   inferred. Register-argument mappings are in config/function_states_r1b.csv. */

/* Zero a block (the original inlines this as rep stos). The intrinsic is
 * used only for the 32-bit x86 comparison build; other targets use memset. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define R1B_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) / 4)
#define R1B_ZEROB(p, n) __stosb((unsigned char *)(p), 0, (n))
#else
#define R1B_ZERO(p, n) memset((p), 0, (n))
#define R1B_ZEROB(p, n) memset((p), 0, (n))
#endif

/* ------------------------------------------------------------ text tokens */
extern char r1b_tok37B1A0[256];         /* 0x0037B1A0 token buffer */
extern char r1b_seg37B120[64];          /* 0x0037B120 path segment buffer */
extern char r1b_name37B160[64];         /* 0x0037B160 last path segment */
extern const char r1b_fmtF[];           /* 0x0025FAFC "%f" */
extern const char r1b_fmtD[];           /* 0x0025FB00 "%d" */
extern const char r1b_fmtX[];           /* 0x0025FB04 "%x" */
int   r1b_sscanf(const char *s, const char *fmt, ...);  /* 0x001C7C70 (CRT) */

char *r1b_NextToken(char **pp);
char *r1b_NextSegment(char **pp);
char *r1b_PathTail(char *path);
float r1b_ParseFloat(char *s);
int   r1b_ParseInt(char *s);
int   r1b_ParseHex(char *s);
char *r1b_FindKey(char *s, const char *key);

/* ------------------------------------------------------------ file buffer */
extern int32_t a1b_buf4326A0, a1b_end4326A4;
int32_t sub_00037570(const char *name, int align);
int   sub_000374C0(const char *name);

/* file record stack at 0x004326A0 (record 0 is the current file) */
typedef struct R1bFileRec {
    int32_t buf;                /* +0x000 */
    int32_t end;                /* +0x004 */
    char    name[0x200];        /* +0x008 */
} R1bFileRec;
extern R1bFileRec r1b_files4326A0[7];
void r1b_PopFile(void);

/* ------------------------------------------------------------ render state */
/* render state block initialised by 0x00012110 */
typedef struct R1bState {
    uint8_t  unk00[2];
    uint16_t w02;               /* +0x02 */
    uint8_t  unk04[4];
    uint32_t d08;               /* +0x08 */
    uint32_t d0C;               /* +0x0C */
    uint8_t  unk10[2];
    uint16_t w12;               /* +0x12 */
    uint8_t  unk14[4];
    uint32_t d18;               /* +0x18 */
    uint32_t d1C;               /* +0x1C */
    uint8_t  unk20;
    uint8_t  b21, b22, b23, b24;/* +0x21..+0x24 */
    uint8_t  unk25[7];
    uint32_t d2C;               /* +0x2C */
    uint16_t w30, w32, w34, w36;/* +0x30..+0x36 */
} R1bState;
void r1b_StateDefaults(R1bState *s);
uint32_t *r1b_PacketWrap(uint32_t *p, int kind, int sub, int a, int b);
void sub_001A69C0(int a, int b);

/* ------------------------------------------------------------ packets */
/* DMA-style packet buffers (PS2 heritage) */
typedef struct R1bPkt {
    uint32_t *cur;              /* +0x00 write pointer */
    uint32_t tag;               /* +0x04 */
    uint8_t  unk08[8];
} R1bPkt;
extern int32_t  r1b_dma37B390;
extern int32_t  r1b_pktIdx37B4A0;
extern int32_t  r1b_dev37B4A4;
extern R1bPkt   r1b_pkts37B4AC[2];
extern R1bPkt   r1b_pkt37B540;
extern uint32_t r1b_fixed37B544;        /* tag of r1b_pkt37B540 */
extern int32_t  r1b_g432680, r1b_g432684, r1b_g432688;
void r1b_DmaKick(uint32_t addr, uint32_t qwc);   /* 0x00013A30, regargs addr=stack qwc=EDX */
uint32_t sub_000AD090(void *p, ...);    /* returns 0 on this build */
void sub_001A1FF0(int dev, uint32_t tag);
void    r1b_PktOp(void *pkt, ...);      /* 0x00102FA0 */
int32_t sub_001A1FD0(int n);

/* ------------------------------------------------------------ steppers */
typedef struct R1bAnimEntry {
    uint8_t  unk00[8];
    int32_t  length;            /* +0x08 */
} R1bAnimEntry;
typedef struct R1bAnimSet {
    uint8_t  unk00[0x24];
    R1bAnimEntry **entries;     /* +0x24 */
} R1bAnimSet;
typedef struct R1bStepper {
    float    f00;               /* +0x00 */
    float    f04;               /* +0x04 */
    int32_t  cur;               /* +0x08 */
    int32_t  time;              /* +0x0C */
    union {
        int32_t length;         /* +0x10 */
        float   t10;
    } u10;
    uint8_t  unk14[4];
    int32_t  arg18;             /* +0x18 */
    uint8_t  unk1C[8];
    uint32_t flags;             /* +0x24, bit 7 = done */
    int32_t  i28;               /* +0x28 */
    uint8_t  unk2C[0x10];
    R1bAnimSet *set;            /* +0x3C */
} R1bStepper;
void sub_00014E80(R1bStepper *s);

/* ------------------------------------------------------------ tracks */
/* track record (0x00017D50..0x000184D0); entries are 0xB0 bytes */
typedef struct R1bTrackEntry {
    uint32_t flags;
    uint8_t  unk04[0xB0 - 4];
} R1bTrackEntry;
typedef struct R1bTrack {
    R1bTrackEntry *items;       /* +0x00 */
    uint32_t count;             /* +0x04 */
    int32_t  v08;               /* +0x08 */
    int32_t  v0C, v10, v14, v18, v1C, v20, v24, v28;  /* +0x0C..+0x28 */
    uint16_t w2C, w2E, w30;     /* +0x2C..+0x30 */
    uint8_t  unk32[2];
    float    t34;               /* +0x34 */
    int32_t *start;             /* +0x38 */
    int32_t *begin;             /* +0x3C */
    int32_t *cur;               /* +0x40 */
} R1bTrack;
struct R1EntryList;
void r1_ClearList(struct R1EntryList *l);      /* 0x00017F40, regargs l=EAX */
void sub_000181B0(R1bTrack *t);                /* regargs t=EDI */
void sub_00018340(R1bTrack *t);                /* regargs t=EDI */
void sub_00017DE0(R1bTrack *t);                /* regargs t=ESI */
void sub_00017E80(R1bTrack *t);                /* regargs t=ESI */

/* ------------------------------------------------------------ misc objects */
typedef struct R1bSlot {
    int32_t a;                  /* +0x0 */
    int32_t b;                  /* +0x4 */
    void   *buf;                /* +0x8 */
} R1bSlot;
typedef struct R1bSlots {
    uint8_t unk000[0x244];
    R1bSlot slot[4];            /* +0x244 */
    void   *extra;              /* +0x274 */
} R1bSlots;
void sub_00053880(void *p);

typedef struct R1bPose {
    uint8_t unk00[0x10];
    float   v10[4];             /* +0x10 */
    float   v20[4];             /* +0x20 */
    float   v30[4];             /* +0x30 */
    float   f40;                /* +0x40 */
} R1bPose;
void sub_001ADCD0(float *dst, const float *to, const float *from, float t);

extern int32_t a1b_i37C050, a1b_i37C05C;
extern float   a1b_f37C054, a1b_f37C058;
void r1b_FadeStart(int mode, float duration);

typedef struct R1bXSrc {
    uint8_t  unk00[0x10];
    uint32_t kind;              /* +0x10 */
    uint8_t  unk14[0xC];
    float    mat[16];           /* +0x20 */
    float    f60;               /* +0x60 */
} R1bXSrc;
typedef struct R1bXObj {
    uint8_t  unk000[0x50];
    int32_t  i50;               /* +0x050 */
    uint8_t  unk054[0xB0 - 0x54];
    float    mat[16];           /* +0x0B0 */
    float    fF0;               /* +0x0F0 */
    uint8_t  unk0F4[0x1E0 - 0xF4];
    float    f1E0;              /* +0x1E0 */
    uint8_t  unk1E4[0x240 - 0x1E4];
    R1bXSrc *src;               /* +0x240 */
    uint8_t  unk244[0x288 - 0x244];
    int32_t  target;            /* +0x288 */
    uint8_t  unk28C[0x2A0 - 0x28C];
    float    m2A0[16];          /* +0x2A0 */
} R1bXObj;
void sub_001ADA40(float *dst, const float *src);
void sub_000191F0(float *dst, float *m, int a);
void sub_0001A710(R1bXObj *o, void *target);
extern int32_t r1b_g42C8F8;

extern int32_t a30_g41316C, a30_g413170;
extern int32_t r1b_ev413408[6];
void sub_000D9AB0(int id);
void sub_00048AF0(int a);

/* menu layout table at 0x002804E0, 32 bytes per entry */
typedef struct R1bLayout {
    uint16_t x0;  uint8_t p02[2];   /* +0x00 */
    uint16_t y0;  uint8_t p06[2];   /* +0x04 */
    uint16_t x1;  uint8_t p0A[2];   /* +0x08 */
    uint16_t y1;  uint8_t p0E[2];   /* +0x0C */
    int32_t  d10;                   /* +0x10 */
    int32_t  d14;                   /* +0x14 */
    uint16_t w18; uint8_t p1A[2];   /* +0x18 */
    uint16_t w1C; uint8_t p1E[2];   /* +0x1C */
} R1bLayout;
typedef struct R1bRect {
    uint8_t  unk00[0x10];
    int32_t  d10;                   /* +0x10 */
    int32_t  d14;                   /* +0x14 */
    uint16_t w18;                   /* +0x18 */
    uint16_t w1A;                   /* +0x1A */
} R1bRect;
typedef struct R1bMenu {
    uint8_t  unk00[8];
    R1bRect *rect;                  /* +0x08 */
} R1bMenu;
extern const R1bLayout r1b_layouts2804E0[];
extern R1bMenu a1b_obj37B560;
extern uint8_t r1b_menu37B580[];
extern int32_t a1b_slots37BEE8[];
void a60_RectSet0(R1bRect *r, int x, int y);
void a60_RectSet1(R1bRect *r, int x, int y);
void sub_00075F00(void *m);
void sub_0003FAB0(void *anim, void *owner);
void r1b_ApplyLayout(R1bMenu *m, int idx);

/* ------------------------------------------------------------ node pool */
typedef struct R1bNode {
    uint8_t unk00[8];
    void   *owner;              /* +0x08 non-zero while in use */
    void   *data;               /* +0x0C */
} R1bNode;
typedef struct R1bNodeOwner {
    uint8_t  unk00[0xC];
    uint32_t flags;             /* +0x0C bit 0 = ready */
} R1bNodeOwner;
extern uint8_t r1b_list37C468[];
extern R1bNode r1b_nodes37C068[64];
void  sub_0003D860(void *n);
void  sub_0003D880(void *list, void *n);
void  sub_0003D8C0(void *n);
void *sub_0003DBC0(void *list, int a, void *key);

typedef struct R1bCtx {
    uint8_t unk00[0x54];
    void   *obj54;              /* +0x54 */
} R1bCtx;
extern R1bCtx *r1_ctx42C8E4;
void  sub_00082200(void *o, int a, int b, int c);
void *r1b_Pool80970(void);              /* 0x00080970 */
void  sub_000822D0(int z, void *p, int a, int b, int c, int d);
void  sub_000824F0(int z, void *p, int a, int b, int c, int d);
void  sub_00080CF0(void *p, int a);
void *sub_00080CB0(void *p, int a, int b);
void  r6_Mat1ADB40(float *dst, const void *src);
typedef struct R1bLocObj {
    uint8_t unk000[0x60];
    float   f60[4];             /* +0x060 */
    uint8_t unk070[0x11C - 0x70];
    uint8_t f11C[4];            /* +0x11C */
} R1bLocObj;

/* ------------------------------------------------------------ lists */
struct R1bPart;
typedef struct R1bRecSub {
    uint8_t  unk00[0x14];
    struct R1bPart *node14;     /* +0x14 */
} R1bRecSub;
typedef struct R1bItem {
    uint8_t  unk00[8];
    struct R1bItem *next;       /* +0x08 */
    uint8_t  flags;             /* +0x0C bit 0 = owned (freed on removal) */
} R1bItem;
/* 0x150-byte scene object record (tables of these hang off R1bLNode) */
typedef struct R1bRec {
    uint8_t  unk000[4];
    int32_t  a;                 /* +0x004 */
    int32_t  b;                 /* +0x008 */
    uint32_t flags;             /* +0x00C */
    uint8_t  unk010[4];
    uint32_t key[2];            /* +0x014 8-character name */
    uint8_t  unk01C[4];
    struct R1bPart *part20;     /* +0x020 */
    uint8_t  unk024[4];
    struct R1bPart *part;       /* +0x028 */
    uint8_t  unk02C[4];
    struct R1bRecSub *sub30;    /* +0x030 */
    uint8_t  unk034[4];
    struct R1bRec *parent;      /* +0x038 */
    struct R1bRec *next;        /* +0x03C */
    R1bItem *items;             /* +0x040 */
    uint8_t  unk044[0x134 - 0x44];
    void    *res134;            /* +0x134 */
    uint8_t  unk138[4];
    void    *res13C;            /* +0x13C */
    uint8_t  unk140[0x150 - 0x140];
} R1bRec;
typedef struct R1bLNode {
    int32_t  count;             /* +0x00 */
    uint8_t  unk04[4];
    R1bRec  *recs;              /* +0x08 */
    int32_t  value;             /* +0x0C */
    struct R1bLNode *next;      /* +0x10 */
} R1bLNode;
typedef struct R1bList {
    R1bLNode *head;             /* +0x00 */
} R1bList;

typedef struct R1bPart {
    uint8_t  unk00[0x80];
    int32_t  attached80;        /* +0x80 non-zero while attached */
    struct R1bPart *next;       /* +0x84 */
    struct R1bPart *link;       /* +0x88 */
    int32_t  kind;              /* +0x8C */
    uint32_t flags;             /* +0x90 bit 4 = hidden */
    float    f94;               /* +0x94 */
    uint8_t  unk98[0xB8 - 0x98];
    int32_t  vB8;               /* +0xB8 */
    uint8_t  unkBC[4];
    int32_t  count;             /* +0xC0 */
    uint8_t *items;             /* +0xC4 */
} R1bPart;
typedef struct R1bPartItem108 {
    uint8_t  unk000[0xD0];
    int32_t  vD0;               /* +0xD0 */
    uint8_t  unk0D4[0x108 - 0xD4];
} R1bPartItem108;
typedef struct R1bPartOwner {
    uint8_t  unk00[0x20];
    R1bPart *part;              /* +0x20 */
} R1bPartOwner;

extern union R1bKey { char c[8]; uint32_t w[2]; } r1b_key42CE40;   /* 0x0042CE40 */
void sub_00033C20(void *p);
void sub_0005BC50(void *p);
void sub_0001D980(R1bRec *r);
void r1b_PartsUnhideTree(R1bPart *p);
void r1b_PartsHideTree(R1bPart *p);

/* ------------------------------------------------------------ script commands */
typedef struct R1bCtl {
    uint8_t  unk00[0x1C];
    uint32_t flags1C;           /* +0x1C */
    uint8_t  unk20[0x10];
    int32_t  sel30;             /* +0x30 */
    uint8_t  unk34[4];
    float    x38;               /* +0x38 */
    float    y3C;               /* +0x3C */
} R1bCtl;
typedef struct R1bCmdTarget {
    uint8_t  unk00[0x20];
    void    *p20;               /* +0x20 */
    uint8_t  unk24[4];
    R1bCtl  *ctl;               /* +0x28 */
    void    *p2C;               /* +0x2C */
} R1bCmdTarget;
typedef struct R1bCmdCtx {
    uint8_t  unk00[0x20];
    void    *p20;               /* +0x20 */
    uint8_t  unk24[0x10];
    void    *p34;               /* +0x34 */
    uint8_t  unk38[0xC];
    void    *p44;               /* +0x44 */
} R1bCmdCtx;
typedef struct R1bColorObj {
    uint8_t  unk00[0x50];
    int32_t  c50[4];            /* +0x50 */
    int32_t  c60[4];            /* +0x60 */
    int32_t  c70[4];            /* +0x70 */
    uint8_t  unk80[0x10];
    int32_t  c90[4];            /* +0x90 */
} R1bColorObj;
void  sub_0007FD30(void *a, void *b, int v);
void  sub_0007FD60(void *a, int v);
void  sub_00074DF0(void *a, void *b, float *pos);
void  r4_NodeDetach(struct R1bPart *n);
extern float r1b_f37C4A0;
void *sub_00053AB0(int size, int a, int tag);
void  sub_0001EFE0(void *p, void *owner, int a);
void  sub_0001F300(R1bRec *r);
void  r1b_PartsSetF94(R1bPart *p);
/* ------------------------------------------------------------ menus and screens */
extern int32_t  r1b_queue37ED04[8];     /* 0x0037ED04 state queue; [0] is current */
extern int32_t  r1b_qstate37ED24, r1b_busy37ED30;
extern uint32_t r1b_flags37ED00;
extern int32_t  a12_state37C544;
extern uint32_t r1b_flags37C540;
extern int32_t  r1b_state37D434, r1b_armed37D454;
extern uint32_t r1b_flags37D430;
extern int32_t  r1b_state37DC28, r1b_armed37DC48;
extern uint32_t r1b_flags37DC24;
extern uint8_t  r1b_b37DC51;
extern int32_t  r1b_state37EECC, r1b_state37EDF0;
extern uint32_t r1b_flags37EDEC;
void r1b_QueueStep37ED04(void);
void sub_00028630(void); void sub_00028740(void); void sub_00028890(void);
void sub_00028930(void); void sub_00028B10(void); void sub_00028CB0(void);
void sub_00028EB0(void); void sub_00028FE0(void); void sub_000290F0(void);
void sub_00029230(void); void sub_00029310(void); void sub_00029470(void);
void sub_00029580(void); void sub_000299F0(void); void sub_00029AE0(void);
void sub_00023A70(void); void sub_00029BC0(void); void sub_00029CE0(void);
void sub_0002A070(void); void sub_0002A160(void); void sub_0002A2C0(void);
void sub_0002A3A0(void); void sub_0002A460(void); void sub_0002ACF0(void);
void sub_0002AE60(void); void sub_0002AF80(void); void sub_0002A950(void);
void sub_0002ABD0(void); void sub_00023B70(void);

extern int32_t  a1b_i3816D0;            /* 10000 while the screen runs */
extern int32_t  r1b_handles3813F4[2];
extern void    *r1b_buf3816C4;
extern int32_t  r1b_mode381400;
extern uint32_t r1b_step381404;
extern int32_t  r1b_v381408, r1b_v38140C, r1b_flag381420;
extern int32_t  r1b_v3816CC;
void sub_001B9FC0(int h);
int  sub_000529F0(void);
void r1b_Cmd4F5D0(int cmd);             /* 0x0004F5D0 */
void sub_000243B0(int a, int b);
void sub_00038070(int a);
void r1b_ScreenMode4(void);
void sub_0002D230(void); void sub_0002D790(void); void sub_0002DBC0(void);
void sub_00038960(void);
void a1a_GroupAdd(int s, int a, int b, void (*fn)(void), int c, int d);
void a1a_GroupReleaseOne(int s, int a);
void a50_RecsClear(void);
void sub_0002CF50(void); void sub_0002E470(void); void sub_0002E2F0(void);
typedef struct R1bBindObj {
    uint8_t  unk00[0x2C];
    int32_t  v2C;               /* +0x2C */
    void    *p30;               /* +0x30 */
} R1bBindObj;
extern uint8_t r1b_name282884[];
int  sub_0003F9C0(void *a, void *b);

extern int32_t  r1b_queue381834[4];     /* 0x00381834 state queue */
extern uint16_t r1b_qbusy381844;
extern float    r1b_qtimer38184C;
extern uint8_t  r1b_fadeA381874, r1b_fadeB381875;
extern float    r1b_fade381878;
void sub_000720A0(float *t, int a);
/* R1B_END */
#endif
