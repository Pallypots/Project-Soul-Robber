#ifndef R4C_H
#define R4C_H
#include "oogie.h"
/* Area r4c: remaining game functions in 0x00190000..0x001BC6D0 (third pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4c.csv. */

/* ------------------------------------------------------------ shared timing globals */
extern float   r4c_fps;          /* 0x0042C964 frames per second */
extern float   r4c_frameUnits;   /* 0x0042C858 */
extern float   r4c_frameSeconds; /* 0x0042C85C */
extern void   *r4c_ctx42C8E4;    /* 0x0042C8E4 */

/* ------------------------------------------------------------ effect objects (0x00190000..0x00193000) */
/* Scene node driven by the effect callbacks (arg 1 of the callbacks). */
typedef struct R4cNode {
    uint8_t  unk00[0x08];
    int32_t  kind;            /* +0x08 */
    uint32_t flagsC;          /* +0x0C */
    uint32_t flags10;         /* +0x10 */
    int32_t  i14;             /* +0x14 */
    uint8_t  unk18[0x20 - 0x18];
    void    *p20;             /* +0x20 */
    uint8_t  unk24[0x28 - 0x24];
    void    *p28;             /* +0x28 model */
    uint8_t  unk2C[0x30 - 0x2C];
    void    *anim30;          /* +0x30 */
    uint8_t  unk34[0x50 - 0x34];
    float    rot50[4];        /* +0x50 */
    float    pos[4];          /* +0x60 */
    float    scale70[4];      /* +0x70 */
    float    v80[4];          /* +0x80 */
    uint8_t  unk90[0xA0 - 0x90];
    float    vA0[4];          /* +0xA0 */
    float    fB0;             /* +0xB0 */
    float    fB4;             /* +0xB4 */
    uint8_t  unkB8[0xD0 - 0xB8];
    int32_t  iD0;             /* +0xD0 */
    uint8_t  unkD4[0xD8 - 0xD4];
    float    vD8[4];          /* +0xD8 */
    float    fE8;             /* +0xE8 */
    int32_t  iEC;             /* +0xEC */
    uint8_t  unkF0[0xF8 - 0xF0];
    float    vF8[4];          /* +0xF8 */
    float    v108[4];         /* +0x108 */
    int32_t  i118;            /* +0x118 */
    uint8_t  unk11C[0x124 - 0x11C];
    int32_t  i124;            /* +0x124 */
    uint32_t flags128;        /* +0x128 */
    uint8_t  unk12C[0x130 - 0x12C];
    int32_t  i130;            /* +0x130 */
    uint8_t  unk134[0x140 - 0x134];
    struct R4cCam *cam140;    /* +0x140 */
    uint8_t  unk144[0x14C - 0x144];
    int32_t  i14C;            /* +0x14C */
} R4cNode;

/* Controlling actor (arg 2 of the callbacks). */
typedef struct R4cActor {
    uint8_t  unk00[0x24];
    int32_t  i24;             /* +0x24 */
    uint8_t  unk28[0x60 - 0x28];
    int32_t  state60;         /* +0x60 */
    uint8_t  unk64[0x6C - 0x64];
    float    f6C;             /* +0x6C state time */
    float    f70;             /* +0x70 */
    void    *work;            /* +0x74 per-effect work block */
    int    (*fn78)(R4cNode *, struct R4cActor *);  /* +0x78 */
    void   (*fn7C)(R4cNode *, struct R4cActor *);  /* +0x7C */
    void   (*fn80)(R4cNode *, struct R4cActor *);  /* +0x80 */
    void    *p84;             /* +0x84 */
    void    *p88;             /* +0x88 */
} R4cActor;

typedef struct R4cMsg { int32_t id; uint8_t unk04[0x1C]; float v20[4]; } R4cMsg;
typedef struct R4cMgr { uint8_t unk00[0x134]; int32_t h134; } R4cMgr;
typedef struct R4cSys { uint8_t unk00[0x8C]; void *p8C; } R4cSys;

/* work block of the 0x00190260 family */
typedef struct R4cFxA {
    int32_t i00, i04, i08;
    float   v0C[4];           /* +0x0C velocity */
    float   f1C;              /* +0x1C distance travelled */
} R4cFxA;
/* work block of the 0x001911F0 family */
typedef struct R4cFxB {
    int32_t i00, i04;
    float   f08;              /* +0x08 */
    uint8_t unk0C[0x14 - 0x0C];
    float   v14[4];           /* +0x14 velocity */
    float   f24;              /* +0x24 distance travelled */
} R4cFxB;
/* work block of the 0x00190900 family (also the 0x00400120 slot records) */
typedef struct R4cFxC {
    int32_t i00, i04;
    uint8_t unk08[4];
    float   f0C;              /* +0x0C */
    int32_t i10;              /* +0x10 */
    uint8_t unk14[0x40 - 0x14];
    int16_t s40;              /* +0x40 */
} R4cFxC;
/* 0x88-byte slot record at 0x00400A88 (x4); also the work block of the 0x00192470 family */
typedef struct R4cSlot {
    R4cNode *obj;             /* +0x00 */
    int32_t i04;
    int32_t idx08;            /* +0x08 slot index 0..3, -1 = none */
    float   f0C;
    int16_t s10;              /* +0x10 */
    uint8_t unk12[2];
    float   f14, f18;         /* +0x14 */
    float   v1C[4];           /* +0x1C */
    float   v2C[4];           /* +0x2C velocity */
    float   q3C[4];           /* +0x3C */
    float   f4C, f50;         /* +0x4C */
    uint8_t unk54[4];
    float   f58;              /* +0x58 */
    uint8_t unk5C[4];
    int16_t s60, s62;         /* +0x60 */
    float   f64, f68;         /* +0x64 */
    int16_t s6C;              /* +0x6C */
    uint8_t unk6E[2];
    int32_t i70;              /* +0x70 */
    uint8_t unk74[4];
    float   v78[4];           /* +0x78 */
} R4cSlot;
typedef struct R4cRec1C { uint32_t flags; int32_t f[6]; } R4cRec1C;      /* 0x00400CA8 x15 */

typedef struct R4cRec24 { int32_t f[9]; } R4cRec24;                          /* 0x004000B0 x3 */
typedef struct R4cRec18 { R4cNode *obj; int32_t i4; float f8, fC, f10, f14; } R4cRec18; /* 0x00400120 x26 */
typedef struct R4cRec4C { R4cNode *obj; R4cActor *actor; uint8_t unk08[0x44]; } R4cRec4C; /* 0x00400390 x10 */
typedef struct R4cRec40 { R4cNode *obj; int32_t i4; int32_t i8; float fC; int32_t i10; uint8_t unk14[0x2C]; } R4cRec40; /* 0x00400688 x16 */

extern R4cRec24 r4c_recs4000B0[3];
extern R4cRec18 r4c_recs400120[26];
extern R4cRec4C r4c_recs400390[10];
extern R4cRec40 r4c_recs400688[16];
extern R4cSlot  r4c_recs400A88[4];
extern R4cRec1C r4c_recs400CA8[15];
extern float    r4c_spin32C5E4[3];    /* 0x0032C5E4 spin per frame */
extern float    r4c_spin32C644[3];    /* 0x0032C644 */
extern int32_t  r4c_g32C6E8[2], r4c_g32C6F0[2];
extern float    r4c_v27B00C[4], r4c_v27B01C[4], r4c_v27AFE8[4], r4c_v27AFF8[4];
extern float    r4c_v27AF9C[4], r4c_v27AFB0[4], r4c_v27AFC0[4], r4c_v27AFD0[4];

/* callees (stack args unless noted) */
void   r4c_VecAdd(float *d, const float *a, const float *b);   /* 0x001ADAF0 */
void   r4c_VecSub(float *d, const float *a, const float *b);   /* 0x001AD9F0 */
void   r4c_VecScale(float *d, const float *s, float k);        /* 0x001ADB60 */
float  r4c_VecLenXZ(const float *v);                           /* 0x000F5F50 */
float  r4c_VecLen(const float *v);                             /* 0x000F5F10 */
void   r4c_Spin(R4cNode *o, const float *rate);                /* 0x000F6450 */
void   r4c_Model34E00(void *h, float *pos, float *out, float *col); /* 0x00034E00 */
void   sub_000F5D40(void *dst, const void *src);
void   sub_000C56B0(R4cNode *o);
void   sub_0018F8D0(R4cNode *o);                               /* regargs: p1=EAX */
void   sub_000ED780(void *o);
R4cMgr *sub_00100110(void);
void   sub_00048250(int h);
void   sub_00189DA0(void *a, void *b, int c);
void   sub_000F3FD0(R4cNode *o);
void  *sub_000ED630(int a, int b, float *pos, int c, int d);
void  *sub_00035DD0(void *fx, int a, int b, int c);
void   sub_00033880(void *h, float *out);
void  *sub_0001D960(void *o, int kind);   /* component lookup */
void   sub_000494D0(int id, float *pos, int c);
int    sub_000F5CD0(void *o, int a, int b);
void   sub_00033B30(R4cNode *o);
void   sub_0001EB80(R4cNode *o);
int    sub_00101360(void);
R4cNode *sub_001012D0(int i);
void   sub_0001C9E0(R4cNode *o, int unused, void (*fn)(R4cNode *, void *));
void  *sub_00101220(void);
float  sub_001A3EC0(float y, float x);
R4cSys *sub_000F3F80(void);
void   sub_001B2080(void *n);
void   sub_001B2020(void *parent, void *n);
void  *sub_0001D0F0(void *o, int part);
void   sub_001AD940(void *m);
void  *sub_000CB9B0(void);
void   sub_0001E9B0(void *ctx, R4cNode *o, int a, int b, int c);
int    sub_001C7EE1(void);
void   r4c_Fn1909C0(R4cNode *o, R4cActor *a);                  /* 0x001909C0 */

/* r4c_1 */
void r4c_FxKill(R4cNode *o);                                   /* 0x00190A00 regargs: p1=EDI */
void r4c_FxCheckHit(R4cNode *o, void *other);                 /* 0x00190AF0 */
int  r4c_FxStop(R4cNode *o, R4cActor *a);                      /* 0x00190900 */
void r4c_SlotAttach(int idx, int part);                        /* 0x00192320 */
void r4c_SlotScale(int idx, float s);                          /* 0x00192630 regargs: p1=EAX */
int    sub_000F5D00(R4cNode *o);
void   sub_000EE760(R4cNode *o, float k);
/* ------------------------------------------------------------ bounce effects (0x00194780..0x00194EF6) */
typedef struct R4cFxE {       /* work block of the 0x001948A0 family */
    uint32_t flags;           /* +0x00 */
    float    f04, f08, f0C;   /* +0x04 */
    uint8_t  unk10[0x18 - 0x10];
    void    *p18;             /* +0x18 spin target */
} R4cFxE;
typedef struct R4cFxF {       /* work block set up by 0x00194D90 */
    void    *owner;           /* +0x00 */
    uint8_t  unk04[0x24 - 0x04];
    float    v24[4];          /* +0x24 */
    float    v34[4];          /* +0x34 */
    uint8_t  unk44[0x54 - 0x44];
    float    f54;             /* +0x54 */
} R4cFxF;
typedef struct R4cRec8C {     /* 0x00400E54 x18 */
    R4cNode *obj;             /* +0x00 */
    int32_t  i04, i08;
    int32_t  state0C;         /* +0x0C */
    uint8_t  unk10[0x54 - 0x10];
    int16_t  s54;             /* +0x54 */
    uint8_t  unk56[0x8C - 0x56];
} R4cRec8C;
typedef struct R4cOwner { uint8_t unk00[4]; int32_t i04, i08; } R4cOwner;
extern R4cRec8C r4c_recs400E54[18];
void   sub_00049700(int id, int r, int g, int b, float *pos, int a, float size, int c);
int    sub_000C46A0(float a, float b, float c, float *pos, float *v0, float *v1);
void   sub_000C4D30(R4cNode *o, int a, float b, int c);
void   sub_000C4DF0(R4cNode *o, int a, float b, int c, float d, float e, float f, float *pos, float *v0, float *v1);
void   r4c_Vec4Scale(float *d, const float *s, float k);      /* 0x001ADBA0 */
void   sub_0018D680(R4cNode *o, void *p, float k);
void   sub_000EE6D0(R4cNode *o, float k);
/* ------------------------------------------------------------ thrown effects (0x001955B0..0x00197790) */
typedef struct R4cFxG { uint8_t unk00[0x18]; float f18; } R4cFxG;
typedef struct R4cFxH {       /* work of 0x00195B60 */
    uint8_t  unk00[0x1C];
    float    f1C;             /* +0x1C scale */
    uint8_t  unk20[0x80 - 0x20];
    int16_t  s80, s82;        /* +0x80 */
} R4cFxH;
typedef struct R4cFxK {       /* work of 0x00195C80..0x00196430 */
    uint8_t  unk00[0x08];
    void    *p08;             /* +0x08 */
    float    f0C;             /* +0x0C age */
    uint8_t  unk10[0x18 - 0x10];
    float    f18;             /* +0x18 */
    uint8_t  unk1C[0x20 - 0x1C];
    float    f20;             /* +0x20 distance */
    float    v24[4];          /* +0x24 start */
    float    v34[4];          /* +0x34 target */
    float    v44[4];          /* +0x44 velocity */
    float    f54;             /* +0x54 speed */
    int16_t  s58;             /* +0x58 */
    uint8_t  unk5A[0x60 - 0x5A];
    float    v60[4];          /* +0x60 */
} R4cFxK;
typedef struct R4cFxL {       /* work of 0x00197160..0x00197650 */
    int32_t  i00, i04;
    int32_t  kind08;          /* +0x08 passed to 0x00196DB0 */
    int16_t  s0C, s0E, s10, s12;
    float    f14;             /* +0x14 distance */
    uint8_t  unk18[0x20 - 0x18];
    float    v20[4];          /* +0x20 velocity */
} R4cFxL;
typedef struct R4cFxJ {       /* work of 0x001976B0 */
    R4cNode *obj;             /* +0x00 */
    uint8_t  unk04[4];
    float    f08;             /* +0x08 */
    int16_t  s0C, s0E, s10;   /* +0x0C */
    uint8_t  unk12[0x18 - 0x12];
    float    f18, f1C, f20;   /* +0x18 */
    uint8_t  unk24[0x34 - 0x24];
    float    v34[4];          /* +0x34 */
} R4cFxJ;
typedef struct R4cRec44 { R4cNode *obj; int32_t i4; uint8_t unk08[0x3C]; } R4cRec44;
typedef struct R4cRec70 { R4cNode *obj; uint8_t unk04[0x6C]; } R4cRec70;
extern R4cRec40 *r4c_g401830;   /* 0x00401830, 4 records */
extern R4cRec44 *r4c_g401828;   /* 0x00401828, 6 records */
extern R4cRec70 *r4c_g40182C;   /* 0x0040182C, 6 records */
extern R4cNode  *r4c_g3F6100;   /* 0x003F6100 */
extern float     r4c_spin32C7B8[3], r4c_spin32C838[3];
extern float     r4c_v27B0CC[4], r4c_v27B0E0[4], r4c_v27B0F0[4], r4c_v27B100[4];
int    sub_000F6A80(void);
void   sub_000F60C0(R4cNode *o, int a, int b);
void   sub_0001EEC0(R4cNode *o, float k);
void   sub_0001EE80(R4cNode *o, void (*fn)(void));
void   sub_00196B40(void);
void  *sub_00053AB0(int size, int a, int line);
void   sub_001AD7E0(float *d, const float *s);
void  *sub_000E23F0(int a, int b);
void   sub_000F5EA0(float *d, const float *a, const float *b);
void   sub_000C61B0(PlayerStats *s, R4cNode *o);
void   sub_00196DB0(int kind, R4cNode *o);                    /* regargs: p1=EAX p2=ECX */
/* ------------------------------------------------------------ dynamic records and timed effects (0x00197CE0..0x00199500) */
typedef struct R4cCam {
    uint8_t  unk00[0x28];
    float    v28[4];          /* +0x28 */
    uint8_t  unk38[0x58 - 0x38];
    float    m58[4][4];       /* +0x58 rows; row 3 is the translation */
} R4cCam;
typedef struct R4cPart { uint8_t unk00[0x30]; float v30[3]; } R4cPart;
typedef struct R4cModelX { uint8_t unk00[0xDC]; float fDC; } R4cModelX;
typedef struct R4cRec1C8 { int32_t f0, f4; uint8_t unk08[0x14]; } R4cRec1C8;   /* 0x00401838 x8 */
typedef struct R4cRecB18 { R4cNode *obj; int32_t i4, i8; uint8_t unk0C[0x0C]; } R4cRecB18; /* 0x00401918 x8 */
typedef struct R4cTimedW { int32_t i00; void *i04; int32_t i08; float v0C[4]; } R4cTimedW;  /* +0x04 handle, +0x0C velocity */
typedef struct R4cTimedV { int32_t i00, i04; float v08[4]; } R4cTimedV;       /* +0x08 velocity */
extern R4cRec1C8 r4c_recs401838[8];
extern R4cRecB18 r4c_recs401918[8];
extern float r4c_g32C8CC, r4c_g32C8DC, r4c_g32C8F8, r4c_g32C8FC, r4c_g32C900, r4c_g32C904;
extern float r4c_g32C908, r4c_g32C918, r4c_g32C91C, r4c_g32C920;
extern int32_t r4c_g32C870[1], r4c_g32C874[1], r4c_g32C88C[1], r4c_g32C8B4[1];
void   sub_001977A0(void *rec, int x);                         /* regargs: rec on stack, x=ECX */
void   sub_00198020(R4cNode *o, R4cActor *a);
void   sub_0001D7A0(R4cNode *o);
int    sub_0001BC40(R4cNode *o);
int    sub_001984A0(R4cNode *o, R4cActor *a);
void   sub_00198640(R4cNode *o, R4cActor *a);
void   sub_001987B0(R4cNode *o, R4cActor *a);
void   sub_00034CF0(void *h, float a, float b, float c, float d);
void   r4c_CamPoint(float *out, R4cNode *o);                   /* 0x00198DA0 regargs: p1=ESI p2=EDI */
/* ------------------------------------------------------------ sound voices and cues (0x001998C0..0x00199C9F) */
typedef struct R4cBank {      /* 0x003316A0 x11 */
    uint8_t  used00;          /* +0x00 */
    uint8_t  unk01[0x0F];
    int8_t   first10;         /* +0x10 first voice / stream index */
    int8_t   count11;         /* +0x11 */
    uint8_t  unk12[2];
    uint16_t vol14;           /* +0x14 */
    uint8_t  unk16[2];
} R4cBank;
typedef struct R4cVoice {     /* 0x00401B30 x16 */
    int32_t  f00, busy04, f08, f0C;
    int32_t  state10;         /* +0x10 */
    int32_t  ch14;            /* +0x14 */
    int32_t  f18;
    int32_t  vol1C;           /* +0x1C */
    int32_t  n20;             /* +0x20 */
} R4cVoice;
typedef struct R4cStream {    /* 0x00401D70 x45 */
    int32_t  used00, f04, cue08, bank0C, state10;
    uint8_t  unk14[0x34 - 0x14];
    int32_t  f34;             /* +0x34 */
} R4cStream;
typedef struct R4cCue { int32_t bank; uint8_t unk04[0x0C]; } R4cCue;   /* 0x00330F30 x119 */
extern R4cBank   r4c_banks3316A0[11];
extern R4cVoice  r4c_voices401B30[16];
extern R4cStream r4c_streams401D70[45];
extern R4cCue    r4c_cues330F30[119];
extern int32_t   r4c_g402764;          /* master volume */
extern void     *r4c_g402778;          /* lock */
void   sub_001AA950(int ch);
void   sub_001ABC00(int vol);
void   sub_001AA970(int ch);
int    sub_00199850(int i);
void   sub_001AAA00(int ch, int a);
void   sub_001AA9D0(int ch);
void   sub_001AA1E0(void *lock);
void   sub_001AA1F0(void *lock);
void   sub_001AB1D0(int cue, int bank);
/* ------------------------------------------------------------ render targets (0x001A1E90..0x001A1F46) */
extern void   *r4c_targets404734[14];  /* 0x00404734 */
extern int32_t r4c_offsets4046FC[14];  /* 0x004046FC */
extern int32_t r4c_curTarget40476C;    /* 0x0040476C */
void OOG_STDCALL sub_001D2750(void *t, uint32_t off);
void OOG_STDCALL sub_001D2850(void *t, uint32_t *out);
void OOG_STDCALL sub_001D2470(void **out);
void OOG_STDCALL sub_001D27B0(void *t, int32_t off);
uint32_t r4c_TargetSetOffset(int i, uint32_t off);             /* 0x001A1E90 */
/* ------------------------------------------------------------ session, options and loaders (0x0019C2D0..0x0019D78F) */
typedef struct R4cLoader {    /* set up by 0x0019C940 */
    int32_t  id;              /* +0x00 */
    void    *buf;             /* +0x04 */
    int32_t  i08, i0C, i10;   /* +0x08 */
    uint8_t  b14;             /* +0x14 */
} R4cLoader;
typedef struct R4cGroup { uint8_t unk00[4]; int32_t i04; } R4cGroup;   /* group of 0x001A1030 entries */
extern int32_t  r4c_g402FA4;
extern uint32_t r4c_g402780;
extern uint8_t  r4c_opt413140, r4c_opt413141, r4c_opt413142, r4c_opt413143, r4c_opt413144;
extern uint8_t  r4c_opt413145, r4c_opt413146, r4c_opt413147, r4c_opt413148, r4c_opt413149;
extern uint8_t  r4c_opt41314A, r4c_opt41314B;
extern uint16_t r4c_opt41314C;
int    sub_000325D0(void);
int    sub_00032450(int a);
uint32_t sub_0004ECD0(int pad);
uint8_t sub_001AB610(void);
void   sub_0019BED0(void);
int    sub_0004F680(int id);
int    sub_0008D340(void);
int    sub_00037FC0(void);
void   sub_00058540(void (*fn)(void *), void *arg);
void   sub_0019C620(void *arg);
void   sub_001A1030(void *g, int a, int b, void (*fn)(void), int d, int e);
void   sub_001A10F0(void *g);
void   sub_0019C9A0(void);
void   sub_0019C6F0(void);
void   sub_0019CE60(void);
int    sub_0004F6D0(int id);
void   sub_00053710(int a);
void   sub_0004FA70(int id, void *buf);
int    sub_0004F4D0(void);
void   sub_000586E0(int a);
void   sub_00053740(void);
void   sub_0004F700(int id);
void   sub_0005EE40(void);
void   sub_0004F720(void);
/* ------------------------------------------------------------ stage flow, jobs and tables (0x0019E6E0..0x001A1672) */
typedef struct R4cJob { uint8_t unk00[8]; int32_t skip08; } R4cJob;   /* +0x08 skip request */
typedef struct R4cShockEnt { int32_t id, val; } R4cShockEnt;
typedef struct R4cShockTab { uint8_t unk00[8]; int32_t n; R4cShockEnt e[1]; } R4cShockTab;
typedef struct R4cBufRec { uint32_t *cmd; int32_t f4, f8; } R4cBufRec;   /* 0x0042CAC8, 12 bytes */
extern int32_t     r4c_g403130;
extern void       *r4c_g40431C;
extern int32_t     r4c_g404318, r4c_g403988, r4c_g40396C;
extern R4cShockTab *r4c_g40398C;
extern int32_t     r4c_g403984;
extern int32_t     r4c_bufIndex42CAC0;
extern R4cBufRec   r4c_bufs42CAC8[2];
void   sub_0019B9E0(void);
void   sub_0005C510(void);
int    sub_000E3370(void);
int    sub_000E0770(void);
void   sub_000E51A0(int a);
int    sub_000D9A70(int bit);
void   sub_00048A60(void);
void   sub_00048110(int a);
void   sub_00048370(void);
void   sub_000DF970(void);
void   sub_0019B9F0(void);
void   sub_00053880(void *p);
void   sub_0019BE50(int a);
void   sub_001A1090(void *g, int a);
void   sub_001A10C0(void *g, int a);
void   sub_0005EB10(int a, int b);
void   sub_001A1130(int a);
int    sub_00079460(void);
void   sub_000580D0(void);
void   sub_001A0D70(void);
void   sub_00058190(void);
uint32_t *sub_0019C800(uint32_t *cmd);                       /* regargs: p1=EAX, result EAX */
uint32_t *sub_00079480(uint32_t *cmd);
void   sub_001B96D0(void);
int    sub_000AD090(int a, ...);
void   sub_001A8A70(int a);
void   sub_001A13E0(void);
void   sub_001A1280(void);
void   sub_001A1320(void);
/* ------------------------------------------------------------ D3D resource release (0x001A3F60) */
extern void   *r4c_g40AD70, *r4c_g40AD74;
extern uint8_t r4c_g40AD78[0x18], r4c_g40AD90[0x10];
extern void   *r4c_g40AE10, *r4c_g40AE14;
void OOG_STDCALL sub_001D3210(void *a, void *b);
void OOG_STDCALL sub_001D3850(void *a);
void OOG_STDCALL sub_001D3D80(void *a, void *b, void *c);
void OOG_STDCALL sub_001D5F50(void *a);
#endif
