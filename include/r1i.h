#ifndef R1I_H
#define R1I_H
#include "oogie.h"
#include <string.h>

/* Area r1i: larger game functions 0x00012000..0x00060000 (ninth pass).
   Names inferred. Register-argument mappings are in
   config/function_states_r1i.csv. */

/* float -> int truncation as the original inlines it (cvttss2si) */
#if defined(_M_IX86) || defined(_M_X64)
#include <xmmintrin.h>
#define R1I_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R1I_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ GS packets */
/* one GS register entry of a packet template (16 bytes) */
typedef struct R1iGsEnt {
    uint16_t u00;
    uint16_t id;                /* +0x02 register id */
    uint32_t u04;
    uint32_t lo;                /* +0x08 */
    uint32_t hi;                /* +0x0C */
} R1iGsEnt;
/* texture record returned by 0x001B9650 (five 64-bit register values) */
typedef struct R1iTex {
    uint8_t  u00[0x28];
    uint32_t reg[10];           /* +0x28 */
} R1iTex;
R1iTex *sub_001B9650(int handle);
void    sub_001A69C0(uint32_t lo, uint32_t hi);   /* texture register flush */

/* sprite packet template (0xA0 bytes, built by 0x00012010) */
typedef struct R1iSpr {
    R1iGsEnt ent[7];            /* +0x00 */
    uint8_t  u70;
    uint8_t  r, g, b;           /* +0x71 */
    uint32_t u74;
    uint32_t texLo, texHi;      /* +0x78 */
    uint32_t z;                 /* +0x80 */
    uint16_t xy[8];             /* +0x84 uv0, xy0, uv1, xy1 */
    uint8_t  a;                 /* +0x94 */
    uint8_t  u95[0x0B];
} R1iSpr;
/* quad packet template (0xC0 bytes, built by 0x00012160) */
typedef struct R1iQuadVtx {
    uint8_t  c[4];              /* +0x00 */
    int16_t  w[4];              /* +0x04 */
} R1iQuadVtx;
typedef struct R1iQuadTpl {
    R1iGsEnt ent[7];            /* +0x00 */
    uint8_t  u70[8];
    uint32_t texLo, texHi;      /* +0x78 */
    uint32_t z[4];              /* +0x80 */
    R1iQuadVtx v[4];            /* +0x90 */
} R1iQuadTpl;
/* small state packet (0x38 bytes, built by 0x00012110) */
typedef struct R1iStPkt {
    R1iGsEnt ent[2];            /* +0x00 */
    uint8_t  u20;
    uint8_t  r, g, b;           /* +0x21 */
    uint8_t  a;                 /* +0x24 */
    uint8_t  u25[7];
    uint32_t z;                 /* +0x2C */
    int16_t  x, y;              /* +0x30 */
    int16_t  w, h;              /* +0x34 */
} R1iStPkt;
extern uint32_t r1i_gifTag2803C0[3];            /* 0x002803C0 sprite GIF tag */
extern uint32_t r1i_gifTag2803E0[3];            /* 0x002803E0 rectangle GIF tag */

uint32_t *r1i_SprPkt(uint32_t *p, const R1iSpr *s);           /* 0x00012360 */
uint32_t *r1i_RectPkt(uint32_t *p, const R1iStPkt *s);        /* 0x000125A0 */

/* ------------------------------------------------------------ key sequences */
extern float a50_frameUnits;                    /* 0x0042C858 frame time in 1/60 s units */
int  sub_0019BE60(int k);
/* one key of a sequence track (16 bytes) */
typedef struct R1iKey {
    int32_t  cmd;               /* +0x00 -1 end, 0 wait, 1 value, 2 loop end, 3 jump track */
    float    arg;               /* +0x04 value or target track */
    float    dur;               /* +0x08 frames */
    uint32_t u0C;
} R1iKey;
typedef struct R1iSeqData {
    uint8_t  u00[0x24];
    R1iKey **tracks;            /* +0x24 */
} R1iSeqData;
/* animated sprite (0x9C bytes, set up by 0x00014D00) */
typedef struct R1iSprite {
    float    x, y;              /* +0x00 */
    int32_t  track;             /* +0x08 */
    int32_t  key;               /* +0x0C */
    float    time;              /* +0x10 frames left on the current key */
    float    rot;               /* +0x14 */
    int32_t  z;                 /* +0x18 */
    float    sx, sy;            /* +0x1C */
    uint32_t flags;             /* +0x24 1 done, 2 loop, 4 hold, 8 paused, 0x80 ended */
    int32_t  changed;           /* +0x28 */
    int32_t  value;             /* +0x2C */
    int32_t  i30;               /* +0x30 */
    float    rate;              /* +0x34 */
    float    span;              /* +0x38 */
    R1iSeqData *data;           /* +0x3C */
    uint8_t  u40[0x48];
    float    speed;             /* +0x88 */
    uint32_t color;             /* +0x8C */
    uint8_t  u90[0x0C];
} R1iSprite;
void r1i_SeqPlayUpdate(R1iSprite *p);                       /* 0x00014E80 */

/* ------------------------------------------------------------ sprite tracks */
/* track command (0x14 bytes) followed by a key record */
typedef struct R1iTrkCmd {
    int32_t  u00;
    uint32_t start;             /* +0x04 start time */
    int32_t  data;              /* +0x08 index into R1iTrack.data */
    int32_t  anim;              /* +0x0C */
    int32_t  tex;               /* +0x10 index into R1iTrack.tex */
} R1iTrkCmd;
/* key record kind 0: fixed position (0x10 bytes) */
typedef struct R1iTrkFix {
    int32_t  kind;
    int32_t  x, y, z;           /* +0x04 */
} R1iTrkFix;
/* key record kind 1: interpolated values (0x44 bytes) */
typedef struct R1iTrkLerp {
    int32_t  kind;
    int32_t  t0;                /* +0x04 */
    int32_t  len;               /* +0x08 */
    int32_t  from[6];           /* +0x0C x y z sx sy rot */
    uint32_t col0;              /* +0x24 */
    int32_t  to[6];             /* +0x28 */
    uint32_t col1;              /* +0x40 */
} R1iTrkLerp;
typedef struct R1iTrkItem {
    uint32_t flags;             /* +0x00 2 seen, 4 started, 8 finished */
    R1iSprite spr;              /* +0x04 */
    uint8_t  uA0[0x10];
} R1iTrkItem;                   /* 0xB0 bytes */
typedef struct R1iTrack {
    R1iTrkItem *items;          /* +0x00 */
    uint32_t count;             /* +0x04 */
    int32_t  idx;               /* +0x08 */
    void    *data[4];           /* +0x0C */
    int32_t  tex[4];            /* +0x1C */
    int16_t  x, y, z;           /* +0x2C */
    uint8_t  u32[2];
    float    time;              /* +0x34 */
    void    *start;             /* +0x38 */
    void    *begin;             /* +0x3C */
    uint8_t *cur;               /* +0x40 */
} R1iTrack;
/* current interpolated key values (0x0042CE60) */
typedef struct R1iTrkVal {
    float    x, y, z, sx, sy, rot;
    uint32_t col;               /* +0x18 */
} R1iTrkVal;
extern R1iTrkVal r1i_trkVal42CE60;              /* 0x0042CE60 */
extern int32_t   a1b_val37B558;                 /* 0x0037B558 */
void r1i_TrackLerp(R1iTrack *t);                /* 0x00017F70 regargs t=EAX */
void r1i_TrackStepA(R1iTrack *t);               /* 0x000181B0 regargs t=EDI */
void r1i_TrackStepC(R1iTrack *t);               /* 0x00018340 regargs t=EDI */
void sub_00014D00(R1iSprite *s, void *data, int tex);
void sub_00014E30(R1iSprite *s, int a, int b, int c, int d);
int  sub_00017AE0(int v, R1iSprite *s);
uint32_t *r1i_SprDraw17C00(uint32_t *p, R1iSprite *s);   /* 0x00017C00 */
int  sub_00017C00(int v, R1iSprite *s);

/* ------------------------------------------------------------ key curves */
/* one curve: slice pointers (times, values, spline terms) and storage */
typedef struct R1iCurve {
    int32_t  u00;
    float   *t;                 /* +0x04 key times */
    float   *v;                 /* +0x08 key values */
    float   *s[4];              /* +0x0C */
    uint8_t  buf[0x180];        /* +0x1C */
} R1iCurve;                     /* 0x19C bytes */
typedef struct R1iCurveSet {
    int32_t  count;             /* +0x000 */
    R1iCurve ch[10];            /* +0x004 */
} R1iCurveSet;
/* one source key (0x50 bytes) */
typedef struct R1iCurveKey {
    float    dur;               /* +0x00 time since the previous key */
    uint8_t  u04[0x18];
    float    c[3];              /* +0x1C */
    uint32_t u28;
    float    b[3];              /* +0x2C */
    uint32_t u38;
    float    a[3];              /* +0x3C */
    uint32_t u48;
    float    d;                 /* +0x4C */
} R1iCurveKey;
typedef struct R1iCurveSrc {
    int32_t  count;             /* +0x00 */
    R1iCurveKey key[1];         /* +0x04 */
} R1iCurveSrc;
void sub_00061C50(R1iCurve *c, int n);          /* build the curve */
int  r1i_CurveSetBuild(R1iCurveSet *s, const R1iCurveSrc *src);   /* 0x00019030 */

/* ------------------------------------------------------------ aim limit */
typedef float R1iMat[4][4];
void  sub_000385D0(R1iMat dst, const R1iMat src);   /* orthonormal copy */
void  sub_000F5D40(float *dst, const float *src);   /* vector copy */
void  sub_001AD9A0(R1iMat dst, const R1iMat src);   /* inverse */
void  sub_001AD9B0(float *dst, const R1iMat m, const float *v);
void  sub_001AD7E0(float *d, const float *s);       /* normalise */
float sub_001AD9D0(const float *a, const float *b); /* dot */
float sub_001A3F20(float x);                        /* acos (Hypothesis) */
void  sub_001ADC60(float *d, const float *a, const float *b, float t);   /* lerp */
void  sub_001ADA60(float *d, const float *a, const float *b);            /* cross */
extern float r1i_vec3781A8[4];                      /* 0x003781A8 origin */
typedef struct R1iAimCfg {
    uint32_t u00;
    uint32_t flags;             /* +0x004 2 limit, 0x400/0x800 rebuild axes */
    float    thresh;            /* +0x008 blend start threshold */
    uint8_t  u00C[0x538];
    float    rate;              /* +0x544 blend rate */
    float    limYaw;            /* +0x548 */
    float    limPitch;          /* +0x54C */
    float    tiltX;             /* +0x550 */
    float    tiltY;             /* +0x554 */
} R1iAimCfg;
typedef struct R1iAim {
    uint8_t  u000[0x60];
    R1iMat   m;                 /* +0x060 */
    float    fov;               /* +0x0A0 */
    uint8_t  u0A4[0x0C];
    R1iMat   mB0;               /* +0x0B0 */
    uint8_t  u0F0[0xD0];
    float    target[4];         /* +0x1C0 */
    uint8_t  u1D0[0x70];
    R1iAimCfg *cfg;             /* +0x240 */
} R1iAim;
void r1i_AimLimit(R1iAim *o);                       /* 0x00018B70 regargs o=EAX */

/* ------------------------------------------------------------ camera */
void sub_001AD940(R1iMat m);                        /* identity */
void sub_00062050(R1iCurve *c, void *buf, int n);   /* carve the slices */
typedef struct R1iCamView {
    R1iMat   m;                 /* +0x00 */
    float    fov;               /* +0x40 */
    uint8_t  u44[0x0C];
} R1iCamView;                   /* 0x50 bytes */
typedef struct R1iCam {
    uint32_t flags;             /* +0x000 */
    uint8_t  u004[0x0C];
    R1iMat   m10;               /* +0x010 */
    float    blend, blendTo;    /* +0x050 */
    int32_t  blending;          /* +0x058 */
    uint32_t u05C;
    R1iCamView view[6];         /* +0x060 */
    R1iAimCfg *cfg;             /* +0x240 */
    int32_t  w244[17];          /* +0x244 */
    int32_t  i288, i28C;        /* +0x288 */
    uint8_t  u290[0x10];
    R1iCurveSet cv;             /* +0x2A0 */
    int32_t  i12BC;             /* +0x12BC */
    int32_t  i12C0;             /* +0x12C0 */
} R1iCam;

typedef struct R1iActor {
    uint8_t  u00[0x60];
    float    pos[4];            /* +0x60 */
} R1iActor;
extern int32_t   r1i_g42C8F8;                   /* 0x0042C8F8 camera enabled */
extern R1iActor *r1i_player420E98;              /* 0x00420E98 */
extern float     r1i_vec378198[4];              /* 0x00378198 */
extern const float r1i_camHeights25FB3C[2];     /* 0x0025FB3C -25, 5 */
R1iActor *sub_000192C0(R1iCam *c);              /* regargs c=EDI; focus target or 0 */
void  sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
void  sub_001ADAF0(float *d, const float *a, const float *b);   /* d = a + b */
void  sub_001ADBA0(float *d, const float *s, float k);          /* d = s * k */
float sub_001A3EF0(float x);                    /* tan (Hypothesis) */
void r1i_CamFollow(R1iCam *c);                  /* 0x000196D0 */
void r1i_CamFrame(R1iCam *c);                   /* 0x00019820 */

float sub_001A3F30(float v);                    /* absolute value */
void  sub_001ADCD0(float *dst, const float *to, const float *from, float t);
extern int32_t a1b_i37C050;                     /* 0x0037C050 */
void r1i_CamBlend(R1iCam *c, float t);          /* 0x0001A800 */

/* ------------------------------------------------------------ bounding boxes */
void  sub_001ADBF0(R1iMat d, const R1iMat m, const float *v);  /* scale */
void  sub_001AD7C0(R1iMat d, const R1iMat a, const R1iMat b);  /* multiply */
void  sub_001ADB60(float *d, const float *s, float k);         /* d = s * k */
float sub_00082D70(const float *v);                            /* length */
typedef struct R1iBoxObj {
    uint8_t  u00[0x0C];
    uint32_t flags;             /* +0x0C 0x100: use the matrix at +0x20 */
    uint8_t  u10[0x10];
    float  (*mtx)[4];           /* +0x20 */
    uint8_t  u24[0x2C];
    float    rot[4];            /* +0x50 */
    float    pos[4];            /* +0x60 */
    uint8_t  u70[0x30];
    float    max[4];            /* +0xA0 */
    float    min[4];            /* +0xB0 */
    float    scale[4];          /* +0xC0 */
} R1iBoxObj;
typedef struct R1iBox {
    float    c[8][4];           /* +0x00 corners */
    float    center[4];         /* +0x80 */
    float    radius;            /* +0x90 */
} R1iBox;
void r1i_BoxBuild(const R1iBoxObj *o, R1iBox *b);              /* 0x0001B4D0 */

/* ------------------------------------------------------------ body contacts */
typedef struct R1iBody R1iBody;
struct R1iBodyNode { uint8_t u00[0x70]; float v70[4]; };
typedef void (*R1iHitFn)(R1iBody *self, R1iBody *other, int pushed);
struct R1iBody {
    uint8_t  u000[4];
    int32_t  kind;              /* +0x004 6: never pushed */
    uint8_t  u008[4];
    uint32_t flagsC;            /* +0x00C 0x400: no contact response */
    uint8_t  u010[0x10];
    struct R1iBodyNode *node;   /* +0x020 */
    uint8_t  u024[0x3C];
    float    pos[4];            /* +0x060 */
    uint8_t  u070[0x48];
    float    vel[4];            /* +0x0B8 */
    uint8_t  u0C8[0x0C];
    R1iHitFn onHit;             /* +0x0D4 */
    float    ofs[3];            /* +0x0D8 */
    uint8_t  u0E4[4];
    float    radius;            /* +0x0E8 */
    int32_t  iEC;               /* +0x0EC */
    uint8_t  list0F0[8];        /* +0x0F0 */
    uint8_t  u0F8[0x30];
    uint32_t flags128;          /* +0x128 1 touched, 0x80000000 pushed */
};
int   sub_0001B9E0(const R1iBox *b, const float *p, float r, float *hit, int z);
float r4_Distance(const float *a, const float *b);               /* 0x001B2730 */
void  r1i_BodyPushOut(R1iBody *a, R1iBody *b, const R1iBox *box); /* 0x0001C280 regargs a=ESI b=EDI */

/* regargs a=EDI b=ESI d=EBX pa=ECX, pb on the stack: centres pa/pb, d = pb - pa
   (flat), returns the overlap depth */
float sub_0001BDC0(R1iBody *a, R1iBody *b, float *d, float *pa, float *pb);
extern float r1i_pushMax2807A0;                 /* 0x002807A0 push-apart limit per frame unit */

/* body set-up view (0x0001C8A0) */
typedef struct R1iBodyInit {
    uint8_t  u000[0x0C];
    uint32_t flagsC;            /* +0x00C */
    uint8_t  u010[0x90];
    float    max[4];            /* +0x0A0 */
    float    min[4];            /* +0x0B0 */
    float    fC0, scale;        /* +0x0C0 */
    uint8_t  u0C8[8];
    int32_t  iD0;               /* +0x0D0 */
    R1iHitFn onHit;             /* +0x0D4 */
    float    ofs[4];            /* +0x0D8 */
    float    radius;            /* +0x0E8 */
    int32_t  iEC;               /* +0x0EC */
    uint8_t  list0F0[8];        /* +0x0F0 */
    float    vF8[4];            /* +0x0F8 */
    float    v108[4];           /* +0x108 */
    int32_t  i118;              /* +0x118 */
    uint8_t  list11C[8];        /* +0x11C */
    int32_t  i124;              /* +0x124 */
    uint32_t flags128;          /* +0x128 */
} R1iBodyInit;
void sub_00102FA0(R1iBody *self, R1iBody *other, int pushed);  /* empty stub */
void sub_00080D20(void *list);                  /* list reset */
void r1i_BodyInit(R1iBodyInit *b);              /* 0x0001C8A0 */

void *sub_00080970(void);                       /* collision pool */
void  sub_000822D0(void *ctx, void *pool, const float *pos, float r, void *list, void *out);
uint8_t *sub_00080CF0(void *pool, const float *pos);  /* nearest hit (point at +0x40) or 0 */
int r1i_BodyHitWorld(R1iBody *b, float *pos, void **list);   /* 0x0001C630 */

/* ------------------------------------------------------------ char units */
typedef struct R1iMdlNode {
    uint8_t  u00[0x80];
    int32_t  hidden;            /* +0x80 */
    struct R1iMdlNode *child84; /* +0x84 */
    struct R1iMdlNode *child88; /* +0x88 */
    uint8_t  u8C[0x40];
    float    col[4];            /* +0xCC */
    uint8_t  uDC[0x10];
    void    *cam;               /* +0xEC */
} R1iMdlNode;
typedef struct R1iUnitFx {
    uint8_t  u00[0x14];
    R1iMdlNode *node;           /* +0x14 */
} R1iUnitFx;
typedef struct R1iUnitTex {
    int32_t  kind;              /* +0x00 1: owns the unit texture */
    uint8_t  u04[4];
    struct R1iUnitTex *next;    /* +0x08 */
    uint8_t  u0C[0x10];
    uint32_t flags;             /* +0x1C 4 loaded */
    uint8_t  u20[0x20];
    int32_t  tex;               /* +0x40 */
    int32_t  i44;               /* +0x44 */
} R1iUnitTex;
typedef struct R1iBlk0C { uint8_t u00[0x0C]; void *buf; } R1iBlk0C;
typedef struct R1iBlk14 { uint8_t u00[0x14]; void *buf; } R1iBlk14;
typedef struct R1iUnit {
    uint8_t  u00[4];
    int32_t  res4, res8;        /* +0x04 resource pair released by 0x000533B0 */
    uint32_t flags;             /* +0x0C 1 shown, 4 locked, 0x10 effect model */
    uint8_t  u10[4];
    int32_t  i14, i18;          /* +0x14 */
    uint8_t  u1C[4];
    R1iMdlNode *shadow;         /* +0x20 */
    void    *p24;               /* +0x24 */
    R1iMdlNode *model;          /* +0x28 */
    void    *p2C;               /* +0x2C */
    R1iUnitFx *fx;              /* +0x30 */
    void    *p34;               /* +0x34 */
    uint8_t  u38[4];
    struct R1iUnit *next;       /* +0x3C */
    R1iUnitTex *texList;        /* +0x40 */
    int32_t  tex[3];            /* +0x44 */
    float    v50[4];            /* +0x50 */
    float    v60[4];            /* +0x60 */
    float    v70[4];            /* +0x70 */
    float    v80[4];            /* +0x80 */
    float    v90[4];            /* +0x90 */
    uint8_t  uA0[0x8C];
    R1iBlk0C *blk12C;           /* +0x12C */
    R1iBlk14 *blk130;           /* +0x130 */
    void    *p134;              /* +0x134 */
    R1iBlk0C *blk138;           /* +0x138 */
    void    *p13C;              /* +0x13C */
    int32_t  i140, i144;        /* +0x140 */
    void    *buf148;            /* +0x148 */
    int32_t  state;             /* +0x14C */
} R1iUnit;
typedef struct R1iScene {
    uint8_t  u00[0x40];
    int32_t *ambient;           /* +0x40 four colour components */
    void    *cams;              /* +0x44 */
    uint8_t  u48[0x18];
    float    light[4];          /* +0x60 */
} R1iScene;
void *sub_000847F0(void *cams, int id);
void  sub_001B2020(void *parent, void *n);
void  sub_001B82E0(R1iMdlNode *n, const float *light);
void  sub_001B3160(R1iMdlNode *n);
void  r1i_UnitsAttach(R1iScene *s, R1iUnit *u, int shadowCam, int modelCam, int fxCam);  /* 0x0001E9B0 */

void sub_00074F10(R1iMdlNode *n);
void sub_000754A0(R1iMdlNode *n);
void sub_000751C0(R1iMdlNode *n);
void sub_001B9FC0(int tex);                     /* free texture */
void sub_00053880(void *p);                     /* free */
void sub_000533B0(int a, int b);
void sub_00033C20(void *p);
void sub_0005BC50(void *p);
void r1i_UnitsRelease(R1iUnit *head);           /* 0x0001E550 */

/* ------------------------------------------------------------ screen wipe */
typedef struct R1iWipeBar {
    int32_t  x;                 /* +0x00 */
    float    y;                 /* +0x04 */
    int32_t  w;                 /* +0x08 */
    float    h;                 /* +0x0C current height */
    int32_t  col;               /* +0x10 */
} R1iWipeBar;
extern int32_t    r1i_wipeState37C4C0;          /* 0x0037C4C0 1 opening, 2 closing, 3 done */
extern int32_t    r1i_wipeMax37C4C4;            /* 0x0037C4C4 */
extern float      r1i_wipeSpeed37C4C8;          /* 0x0037C4C8 */
extern R1iWipeBar r1i_wipe37C4CC[2];            /* 0x0037C4CC */
void      r1c_ReqPush(int value, int a, int b); /* 0x000389C0 */
uint32_t *r1_PacketBuild(uint32_t *p);          /* 0x00038F10 */
uint32_t *sub_00072180(uint32_t *p, int x, float y, int w, float h, int z,
                       int c0, int c1, int c2, int c3);
void r1i_WipeDraw(uint32_t *p);                 /* 0x000227B0 */

/* ------------------------------------------------------------ HUD orbit */
extern int16_t   r1i_hudX37DCF4, r1i_hudY37DCF6;   /* 0x0037DCF4 / 0x0037DCF6 */
extern uint32_t  r1i_hudFlags37DCF8;               /* 0x0037DCF8 */
extern float     r1i_hudSpin37DD20;                /* 0x0037DD20 */
extern const float r1i_kNeg3_2602C0;               /* 0x002602C0 constant -3.0 */
extern int32_t   r1i_hudOfs37DD2C;                 /* 0x0037DD2C */
extern R1iSprite r1i_hudSpr37DD30[5];              /* 0x0037DD30 */
float sub_001A3F00(float x, float y);              /* fmod */
float sub_001A3EE0(float x);                       /* sine-type */
float sub_001A3ED0(float x);                       /* cosine-type */
uint32_t *r1i_HudOrbitDraw(uint32_t *p);           /* 0x00022E70 regargs p=EAX */

/* ------------------------------------------------------------ HUD set-up */
extern uint32_t r1i_hudOn37C4F8;               /* 0x0037C4F8 */
extern int32_t  r1i_life37C570, r1i_lifeMax37C574;  /* 0x0037C570 / 0x0037C574 */
extern int16_t  r1i_lifeX37C56E;               /* 0x0037C56E */
extern int32_t  r1i_lifeSt37C544, r1i_lifeT37C548, r1i_lifeT37C564;
extern float    r1i_lifeF37C584;               /* 0x0037C584 */
extern uint8_t  r1i_soulA37D45C;               /* 0x0037D45C */
extern int16_t  r1i_soulW37D478, r1i_soulV37D47A, r1i_soulW37D47C;
extern int16_t  r1i_soulK37D474, r1i_soulK37D476, r1i_soulX37D46C;
extern int32_t  r1i_soulSt37D434, r1i_soulT37D438, r1i_soulT37D454, r1i_soulM37D460;
extern int32_t  r1i_itemSt37DAA4, r1i_itemT37DAA8, r1i_itemT37DAC4;
extern float    r1i_itemF37DACC;               /* 0x0037DACC */
extern uint8_t  r1i_itemA37DAD0;               /* 0x0037DAD0 */
extern int32_t  r1i_itemV37DAD4, r1i_itemV37DAD8, r1i_itemV37DADC;
extern uint32_t r1i_itemCol37DAE0;             /* 0x0037DAE0 */
extern uint32_t r1i_hudFl37F0C8;               /* 0x0037F0C8 */
extern int32_t  r1i_hud37FB70;                 /* 0x0037FB70 */
extern int32_t  r1i_keySt37F484, r1i_keyT37F488, r1i_keyT37F4A4;
extern float    r1i_keyF37F4AC;                /* 0x0037F4AC */
extern uint8_t  r1i_keyA37F4B0;                /* 0x0037F4B0 */
int  Stats_Get(PlayerStats *s, int index);     /* 0x000CF790 */
void r1i_HudSetup(int resume);                 /* 0x00026B50 regargs resume=EDI */


#endif
