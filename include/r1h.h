#ifndef R1H_H
#define R1H_H
#include "oogie.h"
#include <string.h>

/* Area r1h: larger game functions 0x00012000..0x00060000 (eighth pass).
   Names inferred. Register-argument mappings are in
   config/function_states_r1h.csv. */

/* float -> int truncation as the original inlines it (cvttss2si) */
#if defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
#define R1H_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R1H_FTOI(x) ((int)(x))
#endif

uint32_t sub_0004ECE0(int pad);                 /* newly pressed buttons */

/* ------------------------------------------------------------ debug menus */
/* debug text output (as area r1g): every call returns the new context */
int sub_0003E460(int ctx, int x, int y, int *px, int *py, void *m);  /* title */
int sub_0003E550(int ctx, int x, int y, int *px, int *py, void *m);  /* page arrow up */
int sub_0003E5B0(int ctx, int x, int y, int *px, int *py, void *m);  /* page arrow down */
int sub_0003E610(int ctx, int x, int y, int *px, int *py, int hilite, int on, const char *fmt, ...);
int sub_0003F780(int ctx, void *m, int msg);    /* default menu handler */
int sub_0003ED50(void *m, int mode);            /* nonzero while the cursor moves */
int  sub_0003F570(void *m);                     /* cursor update, nonzero when the value changed */

/* tree node shown by the tree menu (only the link fields used) */
typedef struct R1hNode {
    uint8_t  u00[0x80];
    struct R1hNode *parent;     /* +0x80 */
    struct R1hNode *next;       /* +0x84 sibling */
    struct R1hNode *child;      /* +0x88 first child */
    int32_t  type;              /* +0x8C index into r1h_nodeTypeNames */
} R1hNode;
typedef struct R1hTreeData {
    uint8_t  u00[0x2C];
    R1hNode *cur;               /* +0x2C */
} R1hTreeData;
typedef struct R1hMenu {
    uint32_t u00;
    int32_t  sel;               /* +0x04 */
    int32_t  count;             /* +0x08 */
    int32_t  first;             /* +0x0C first visible */
    int32_t  visible;           /* +0x10 */
    uint8_t  u14[4];
    int32_t  x, y;              /* +0x18 */
    uint8_t  u20[8];
    int32_t  pad;               /* +0x28 */
    uint32_t u2C;
    void    *owner;             /* +0x30 menu system */
    R1hTreeData *data;          /* +0x34 */
    struct R1hMenuData *items;  /* +0x38 */
} R1hMenu;
typedef R1hMenu R1hTreeMenu;
typedef struct R1hMenuItem {
    const char *name;           /* +0x00 */
    void    *sub;               /* +0x04 submenu opened on accept */
    uint32_t flags;             /* +0x08 bit 12: no submenu */
    uint8_t  u0C[0x18];
} R1hMenuItem;                  /* 0x24 bytes */
typedef struct R1hMenuData {
    uint8_t  u00[8];
    R1hMenuItem *items;         /* +0x08 */
} R1hMenuData;
/* regargs: px=ECX py=EAX mode=EDX */
int  sub_0002EF30(int ctx, R1hMenu *m, int *px, int *py, int mode);
/* regargs: px=EBX py=EDI hilite=ESI it=ECX */
int  sub_0002EBC0(int ctx, int x, int y, int *px, int *py, int hilite, R1hMenuItem *it);
void sub_0003EF00(R1hMenuItem *it, int pad);
int  r1h_NodeMenuProc(int ctx, R1hMenu *m, int msg);       /* 0x0002F2A0 */
extern const char *r1h_nodeTypeNames[];         /* 0x00282830 */
extern const char r1h_str2609BC[];              /* 0x002609BC header */
extern const char r1h_fmt2609AC[];              /* 0x002609AC "%d %s %d" style */
extern const char r1h_fmt260990[];              /* 0x00260990 empty slot */
void sub_0002EAD0(R1hTreeMenu *m, R1hNode *n);
void sub_0002EB80(R1hTreeMenu *m, R1hNode *n);
typedef struct R1hNodeEx {
    R1hNode  n;
    uint32_t flags;             /* +0x90 */
} R1hNodeEx;
extern R1hMenuData r1h_nodeMenuData;            /* 0x00282A74 fixed rows of the node menu */
extern const char r1h_fmt260954[];              /* 0x00260954 "name value" row */
extern const char r1h_fmt26094C[];              /* 0x0026094C "name" row */
int  sub_0003E9E0(R1hMenuData *d);              /* item count */
void sub_0003EAF0(R1hMenuItem *it, int on);
int  r1h_NodeRows(int ctx, R1hMenu *m, int *px, int *py, int mode);   /* 0x0002EF30 */
int  r1h_TreeMenuProc(int ctx, R1hTreeMenu *m, int msg);   /* 0x0002ECB0 */

/* ------------------------------------------------------------ GS packets */
typedef struct R1hGsEnt {
    uint16_t u00;
    uint16_t id;                /* +0x02 register id */
    uint32_t u04;
    uint32_t lo;                /* +0x08 */
    uint32_t hi;                /* +0x0C */
} R1hGsEnt;
/* sprite packet template (0xA0 bytes, built by 0x00012010) */
typedef struct R1hSpr {
    R1hGsEnt ent[7];            /* +0x00 */
    uint8_t  u70;
    uint8_t  r, g, b;           /* +0x71 */
    uint32_t u74;
    uint32_t texLo, texHi;      /* +0x78 */
    uint32_t col80;             /* +0x80 */
    uint16_t w84[8];            /* +0x84 */
    uint8_t  a;                 /* +0x94 */
    uint8_t  u95[0x0B];
} R1hSpr;
/* small state packet (0x38 bytes, built by 0x00012110) */
typedef struct R1hStPkt {
    uint8_t  u00[0x21];
    uint8_t  r, g, b;           /* +0x21 */
    uint8_t  a;                 /* +0x24 */
    uint8_t  u25[0x13];
} R1hStPkt;
/* one screen-filter channel (0x1450 bytes each, table at 0x003DA500) */
typedef struct R1hFilt {
    uint8_t  u000[0x100];
    R1hSpr   spr[16];           /* +0x100 */
    uint8_t  uB00[0x500];
    R1hSpr   s1000;             /* +0x1000 */
    uint8_t  u10A0[0x1E0];
    R1hSpr   s1280;             /* +0x1280 */
    R1hStPkt st[4];             /* +0x1320 */
    uint8_t  u1400[0x38];
    uint32_t texW;              /* +0x1438 */
    uint32_t texH;              /* +0x143C */
    int32_t  tex;               /* +0x1440 texture handle */
    int32_t  u1444;             /* +0x1444 */
    int32_t  mode;              /* +0x1448 blend mode 0..2 */
    uint32_t u144C;
} R1hFilt;
/* per-channel parameters (0x2C bytes each, table at 0x003DA4A8) */
typedef struct R1hChan {
    uint8_t  u00[4];
    int32_t  count;             /* +0x04 */
    uint8_t  col08;             /* +0x08 */
    uint8_t  u09[3];
    uint8_t  alpha;             /* +0x0C */
    uint8_t  u0D[3];
    uint8_t  grey;              /* +0x10 */
    uint8_t  u11[0x0B];
    int32_t  w;                 /* +0x1C */
    int32_t  h;                 /* +0x20 */
    uint8_t  u24[8];
} R1hChan;
extern R1hFilt  r1h_filt3DA500[];               /* 0x003DA500 */
extern R1hChan  r1e_chan3DA4A8[];               /* 0x003DA4A8 */
extern int32_t  a3c_w3DA4A0;                    /* 0x003DA4A0 */
extern uint32_t r1h_zbuf3DCDA0;                 /* 0x003DCDA0 frame/z base */
extern int32_t  a3c_h3DCDA4;                    /* 0x003DCDA4 */
extern uint32_t a3c_w3DCE58;                    /* 0x003DCE58 screen width */
extern int32_t  a3c_h3DCE5C;                    /* 0x003DCE5C screen height */
typedef struct R1hTex {
    uint8_t  u00[0x28];
    uint64_t q28;               /* +0x28 */
} R1hTex;
R1hTex   *sub_001B9650(int handle);
typedef struct R1hFrame {
    uint8_t  u00[0x18];
    uint32_t a, b, c;           /* +0x18 */
} R1hFrame;
R1hFrame *sub_001BB230(void);
uint32_t  sub_001BB240(uint32_t c, uint32_t a, uint32_t b);
void      sub_001A4D70(int ch);
uint32_t *sub_00012300(uint32_t *p, uint64_t reg, uint64_t val);
uint32_t *sub_00012360(uint32_t *p, R1hSpr *s);
uint32_t *sub_000125A0(uint32_t *p, R1hStPkt *s);
uint32_t *sub_000396E0(uint32_t *p);
void      sub_00102FA0(int a, ...);       /* debug stub (returns at once) */
void      r1h_Nop102FA0(void);           /* 0x00102FA0 same stub called without arguments */
uint32_t *r1h_FiltDrawBlend(uint32_t *p, int ch);       /* 0x00039920 */

/* ------------------------------------------------------------ system setup */
extern void   *r1h_res3E1204;                   /* 0x003E1204 */
extern void   *r1h_res3E1208;                   /* 0x003E1208 */
extern int32_t r1h_res3E120C;                   /* 0x003E120C */
extern void   *r1h_res3E1210;                   /* 0x003E1210 */
extern void   *r1h_res3E1214;                   /* 0x003E1214 */
extern void   *r1h_res3E1218;                   /* 0x003E1218 */
extern int32_t r1h_h2DCD48;                     /* 0x002DCD48 */
extern const char r1h_name2CCCC8[];             /* 0x002CCCC8 */
void *sub_00053820(int kind, int size, int a, int b);   /* allocate */
void  sub_001BBD90(void);
void  sub_00012000(void);
void  sub_001BB2A0(void *p, int size);
void  sub_001BB2E0(int a, int b, int c);
void  sub_001BB780(void *p, int size, int w, int h, int d);
void  sub_001BB1D0(int a, int b, int c);
void  sub_001BB1F0(int a, int b, int c);
void  sub_001BB210(int a, int b, int c);
void  sub_001BA650(void *p, int size);
void  sub_001B9720(void);
void  sub_001B9730(void);
int   sub_00084C00(const char *name, int a);
void  r1h_GfxInit(void);                        /* 0x00052360 */

extern int32_t r1h_busy3E0540;                  /* 0x003E0540 */
extern int32_t r1h_g3E0598;                     /* 0x003E0598 */
extern int32_t r1h_g3E05BC;                     /* 0x003E05BC */
extern int32_t r1h_g3E00CC;                     /* 0x003E00CC */
extern int32_t r1h_g41316C;                     /* 0x0041316C */
extern int32_t r1h_g413170;                     /* 0x00413170 */
void sub_000325A0(int on);
void sub_00038070(int a);
void sub_00049870(void);
void sub_0004BDA0(void);
void sub_00058540(void (*fn)(void), int a);
int  sub_00057E90(void);
void sub_000580D0(void);
void sub_000488C0(int a, int b, int c);
int  sub_00047A50(int a, int b, int c);
void sub_001AB850(void);
void sub_000487F0(int a, int b, int c);
int  sub_00048820(int a, int b, int c);
void sub_00048860(int a, int b, int c);
int  sub_00048890(int a, int b, int c);
void r1h_WaitIdle(void);                        /* 0x0004E6D0 */

/* ------------------------------------------------------------ boot / scene */
extern uint64_t r1h_frames42C918;               /* 0x0042C918 frame counter */
extern int32_t  r1h_g42CADC;                    /* 0x0042CADC */
int  sub_000AD090(int a, ...);                  /* stub returning 0 */
void sub_00053A40(void);
void sub_0003DE20(int a);
void sub_0004EFE0(void);
void sub_00077190(void);
void sub_000582C0(void);
void sub_0003DD20(void);
void sub_000583C0(void);
void sub_00052520(void);
void sub_00049490(int a);
int  sub_00047920(void);
void sub_000ED290(void);
void sub_0004F490(void);
void sub_0004F540(int a);
int  sub_0004F4D0(void);
void sub_0004F4C0(void);
void sub_000524A0(void);
void r1h_Boot(void);                            /* 0x0003DF90 */

typedef struct R1hSndTest {
    uint8_t  u00[0x10];
    int32_t  id;                /* +0x10 */
    int32_t  pitch;             /* +0x14 */
    void    *p18;               /* +0x18 */
} R1hSndTest;
typedef struct R1hWorld {
    uint8_t  u000[0x1EC];
    struct { uint8_t u[0x10]; void *p10; } *p1EC;   /* +0x1EC */
    struct R1hSndTest *p1F0;   /* +0x1F0 */
    void    *p1F4;              /* +0x1F4 */
    uint8_t  u1F8[0x10];
    int32_t  snd208;            /* +0x208 */
} R1hWorld;
extern R1hWorld *r1h_world42C8E4;               /* 0x0042C8E4 */
extern uint8_t   r1h_list3E1270[];              /* 0x003E1270 */
void sub_00047BF0(int a);
void sub_0005FE00(void);
void sub_000A8B80(void);
void sub_000C85C0(void);
void sub_000C5380(void);
int  sub_00019020(void *l);
void sub_00019000(void *l, int n);
void sub_00034BB0(void);
void sub_00034B70(void);
void sub_00053350(int a, int b);
void sub_00053880(void *p);                     /* free */
void sub_0005CA80(void);
void sub_0003AAB0(void);
void sub_0003ACC0(void *p);
void sub_000DFC80(void);
void sub_000A9D00(void);
void sub_00087440(void);
void sub_00087560(int i);
void sub_001660C0(void);
void sub_00037BC0(void);
void sub_0004F5D0(int id);
void sub_00018B10(void *l);
void sub_000A56C0(void);
void sub_00039820(int a);
void sub_0007D090(R1hWorld *w);
void r1h_SceneRelease(void);                    /* 0x00057C70 */

/* ------------------------------------------------------------ stage textures */
extern int32_t r1h_flag3E64C0;                  /* 0x003E64C0 loaded */
extern int32_t r1h_texA3E60A0[4];               /* 0x003E60A0 texture handles, -1 none */
extern int32_t r1h_texB3E60B0[6];               /* 0x003E60B0 texture handles, -1 none */
extern void   *r1h_buf3E60C8;                   /* 0x003E60C8 */
extern void   *r1h_buf3E60CC;                   /* 0x003E60CC */
void sub_001B9FC0(int tex);                     /* release texture */
int  sub_000529F0(void);
int  sub_0004F6D0(int id);
void r1h_StageTexRelease(void);                 /* 0x0005FE00 */

/* ------------------------------------------------------------ vibration (shock) pattern debug menu */
typedef struct R1hSeEnt {
    uint8_t  level;             /* +0 0..255 */
    int8_t   time;              /* +1 frames, -1 ends the list */
} R1hSeEnt;
extern int32_t r1h_seq3E6094;                   /* 0x003E6094 pattern being edited */
extern int32_t r1h_g3E6090;                     /* 0x003E6090 */
extern const char r1h_fmt26CE9C[];              /* 0x0026CE9C title */
extern const char r1h_fmt26CE84[];              /* 0x0026CE84 entry row */
extern const char r1h_str26CE78[];              /* 0x0026CE78 end row */
R1hSeEnt **sub_0005EBA0(int seq);
uint32_t sub_0004ECD0(int pad);                 /* held buttons */
uint32_t sub_0004ECF0(int pad);                 /* repeating buttons */
void sub_0005EB40(int a);
void sub_0005EB10(int a, int seq);
int  sub_0005ED30(int seq, int at, int a);      /* insert entry */
int  sub_0005EDA0(int seq, int at, int a);      /* delete entry */
void sub_0003E410(R1hMenu *m, int a);           /* close menu */
int  r1h_SeqEditProc(int ctx, R1hMenu *m, int msg);     /* 0x0005F290 */

int  r1h_SeqEdit2Proc(int ctx, R1hMenu *m, int msg);    /* 0x0005F580 */

extern int32_t r1h_g3E6098;                     /* 0x003E6098 */

int  sub_0003F770(void *m);                     /* nonzero while the cursor moves */
int  sub_0003EB10(R1hMenuItem *it);             /* item value */
void sub_0003EA10(R1hMenuItem *it, int v);      /* set item value */
void sub_0003EC30(R1hMenuItem *it, int v, int lo, int hi, int step, int big);   /* set up a number item */
void sub_001997E0(int id, int pitch);
int  r1h_SndTestProc(int ctx, R1hMenu *m, int msg);     /* 0x0005D250 */

/* ------------------------------------------------------------ sound sequencer (seseq.c) */
typedef struct R1hSeqSlot {
    int32_t  used;              /* +0x00 */
    int32_t  v04;               /* +0x04 */
    int32_t  u08;
    int32_t  v0C;               /* +0x0C */
    void    *work;              /* +0x10 */
} R1hSeqSlot;                   /* 0x14 bytes */
typedef struct R1hSeqWork {
    uint8_t  u00[0x30];
} R1hSeqWork;
typedef struct R1hSeqData {
    uint8_t  u00[8];
    int32_t  count;             /* +0x08 */
    uint8_t  u0C[4];
    R1hSeqSlot slot[16];        /* +0x10 */
    R1hSeqWork work[16];        /* +0x150 */
} R1hSeqData;
typedef struct R1hSeqNode {
    uint8_t  u00[0x20];
    uint32_t flags;             /* +0x20 */
} R1hSeqNode;
typedef struct R1hSeqOwner {
    uint8_t  u00[4];
    int32_t  v04;               /* +0x04 */
    int32_t  v08;               /* +0x08 */
    uint8_t  u0C[0x24];
    struct { uint8_t u[8]; int32_t id; } *p30;   /* +0x30 */
    uint8_t  u34[0x104];
    void    *p138;              /* +0x138 */
    struct { uint8_t u[4]; void *p04; } *p13C;   /* +0x13C */
} R1hSeqOwner;
typedef struct R1hSeqObj {
    R1hSeqOwner *owner;         /* +0x00 */
    void    *data;              /* +0x04 */
    int32_t  index;             /* +0x08 */
    int32_t  v0C;               /* +0x0C */
} R1hSeqObj;
void *sub_00053AB0(int size, int a, int line);  /* allocate (line of seseq.c) */
void  sub_0003D860(void *p);
void  sub_0005CEB0(R1hSeqOwner *o);
void  sub_0005C1E0(R1hSeqOwner *o);
void  sub_0005C0E0(void *data, int a, int b, int id);
R1hSeqNode *sub_0005CC70(void *list, int id);
void  sub_0005CB90(R1hSeqOwner *o, uint32_t *flags);
int   sub_0005BE80(R1hSeqData *d);              /* free slot or -1 */
void  sub_0005BEB0(R1hSeqWork *w);
void  sub_0005A700(R1hSeqSlot *s);
int   sub_0005A8F0(R1hSeqData *d);              /* first used slot or -1 */
int   sub_0005A870(R1hSeqData *d, int k);       /* next used slot or -1 */
int   r1h_SeqObjProc(int msg, R1hSeqObj *o);    /* 0x0005D030 */


/* ------------------------------------------------------------ slot select */
typedef struct R1hSaveData {
    uint8_t  u000000[0x122D30];
    int32_t  used[5];           /* +0x122D30 */
} R1hSaveData;
extern int32_t  r1h_wait3E3984;                 /* 0x003E3984 input delay frames */
extern int32_t  r1h_state3E3F44;                /* 0x003E3F44 */
extern int32_t  r1h_slot3E3960;                 /* 0x003E3960 cursor 0..4 */
extern int32_t  r1h_mode3E3950;                 /* 0x003E3950 1 = saving */
extern R1hSaveData *r1h_save3E3934;             /* 0x003E3934 */
extern uint32_t *r1h_keys2C4AE8;                /* 0x002C4AE8 [0] accept mask, [1] cancel mask */
uint32_t sub_0004ED20(int pad);
uint32_t sub_0004ED40(int pad);
int  sub_000544F0(void);
void sub_00048AF0(int se);                      /* menu sound */
int  r1h_SlotSelect(void);                      /* 0x00054E90 */

/* ------------------------------------------------------------ 2D animation sets */
typedef struct R1hAnim {
    int32_t  v00, v04;          /* +0x00 */
    uint8_t  u08[0x0C];
    int32_t  v14;               /* +0x14 */
    uint8_t  u18[4];
    int32_t  v1C, v20;          /* +0x1C */
    uint32_t flags;             /* +0x24 */
    uint8_t  u28[0x1C];
    int32_t  tex[6];            /* +0x44 extra textures */
    uint8_t  u5C[0x24];
    int32_t  v80;               /* +0x80 */
    uint8_t  u84[4];
    int32_t  v88, v8C;          /* +0x88 */
    uint8_t  u90[0x0C];
} R1hAnim;                      /* 0x9C bytes */
typedef struct R1hLangEnt {
    int8_t   v;
    uint8_t  u01[3];
} R1hLangEnt;
extern R1hAnim  r1h_anim3E4774[6];              /* 0x003E4774 */
extern char    *r1h_pak3E474C;                  /* 0x003E474C loaded 2D data file */
extern int32_t  r1h_tex3E4740[3];               /* 0x003E4740 */
extern int32_t  r1h_tex3E4B20[2];               /* 0x003E4B20 */
extern int32_t  r1h_tex3E4B30[2];               /* 0x003E4B30 */
extern int32_t  r1h_lang3E4760;                 /* 0x003E4760 */
extern int32_t  r1h_g3E4764;                    /* 0x003E4764 */
extern R1hLangEnt r1h_langTbl2DD1C8[];          /* 0x002DD1C8 */
extern int8_t   r1h_lang413145;                 /* 0x00413145 */
void sub_00014DA0(void *src);
void sub_00014D00(R1hAnim *a, void *src, int tex);
void sub_00014E30(R1hAnim *a, int b, int c, int d, int e);
void sub_00052A00(int lang);
void r1h_AnimSetLoad(int kind);                 /* 0x00059020, regargs kind=EAX */


void r1h_EfsLoad(void *p, const void *f);       /* 0x000358C0, defined in r1h_14.c with the area r1g pool types */


/* vibration patterns: header (12 bytes) then two key lists ended by time -1 */
typedef struct R1hShockHdr {
    uint32_t a;
    int32_t  off1;              /* +0x04 file: index of list 1 in keys[] */
    uint32_t c;                 /* +0x08 */
} R1hShockHdr;
typedef struct R1hShock {
    union {
        R1hShockHdr hdr;
        struct {
            R1hSeEnt *keys[2];  /* +0x00 */
            uint16_t len;       /* +0x08 */
        } m;
    } h;
    R1hSeEnt buf0[100];         /* +0x0C */
    R1hSeEnt buf1[100];         /* +0xD4 */
} R1hShock;                     /* 0x19C bytes */
typedef struct R1hShockFile {
    R1hShockHdr hdr;
    R1hSeEnt keys[1];           /* +0x0C */
} R1hShockFile;
extern int32_t   *r1h_shockUsed3E604C;          /* 0x003E604C */
extern R1hShock **r1h_shock3E6050;              /* 0x003E6050 */
extern R1hSeEnt   r1h_shockDef2DD7BC;           /* 0x002DD7BC default key, list 1 */
extern R1hSeEnt   r1h_shockDef2DD7BE;           /* 0x002DD7BE default end, list 1 */
extern R1hSeEnt   r1h_shockDef2DD7C0;           /* 0x002DD7C0 default key, list 0 */
extern R1hSeEnt   r1h_shockDef2DD7C2;           /* 0x002DD7C2 default end, list 0 */
R1hShockFile *sub_00037570(int id, int kind);   /* loaded file or 0 */
void r1h_ShockLoad(int slot, int id);           /* 0x0005EBB0 */


/* debug menu key configuration */
extern uint32_t r1h_keyDown2C4B0C;              /* 0x002C4B0C */
extern uint32_t r1h_keyUp2C4B10;                /* 0x002C4B10 */
extern uint32_t r1h_keyOk2C4B1C;                /* 0x002C4B1C */
extern uint32_t r1h_keyBack2C4B20;              /* 0x002C4B20 */
extern uint32_t r1h_keyPage2C4B24;              /* 0x002C4B24 */
void sub_0003F8B0(void *owner, void *menu, int a);  /* open submenu */
int  r1h_MenuCursor(R1hMenu *m, int flags);     /* 0x0003ED50 */


/* ------------------------------------------------------------ screen markers */
typedef struct R1hMark {
    float    x, y, z;           /* +0x00 screen x, y and depth */
    void    *obj;               /* +0x0C */
    int32_t  tag;               /* +0x10 */
} R1hMark;                      /* 0x14 bytes */
typedef struct R1hMarks {
    int32_t  n;                 /* +0x00 */
    R1hMark  m[1];              /* +0x04 */
} R1hMarks;
typedef struct R1hCamModel {
    uint8_t  u000[0x1F0];
    uint8_t  vp1F0[0x40];       /* +0x1F0 viewport */
    float    mtx230[16];        /* +0x230 view matrix */
} R1hCamModel;
typedef struct R1hWorld44 {
    uint8_t  u00[0x44];
    void    *cams;              /* +0x44 */
} R1hWorld44;
extern uint32_t  r1h_flags37C4F8;               /* 0x0037C4F8 bit 0: markers on */
extern R1hMarks  r1h_marks37F0F0;               /* 0x0037F0F0 */
R1hCamModel *sub_000847F0(void *list, int id);
void sub_000F5D40(float *dst, const float *src);    /* copy 4 floats */
void sub_001AD9B0(float *dst, const float *mtx, const float *src);
void sub_001AE140(int *xy, void *vp, int *z, int a);
void r1h_MarkAdd(const float *pos, float yofs, void *obj, int tag);   /* 0x000264F0 */


#endif
