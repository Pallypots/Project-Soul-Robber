#ifndef R4I_H
#define R4I_H
#include "oogie.h"
#include "shared_decls.h"
#include "r4c.h"
#include "r4f.h"
/* Area r4i: larger game functions in 0x00190000..0x001BC6D0 (ninth pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4i.csv. */

/* Float to int truncation (cvttss2si in the original); same as RFL_FTOI. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R4I_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R4I_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ effects (0x00190000..0x00198000) */
typedef struct R4iSphere { float c[4]; float r; } R4iSphere;   /* collision probe */

int   r4c_FxCollide(R4cNode *o);                               /* 0x00190B40 regargs: p1=EAX */
int   sub_000F61D0(R4cNode *o, R4iSphere *s, int mask, float *hit); /* -1 when no hit */
extern float r4i_spin32C658[3];   /* 0x0032C658 spin rate of kind 0x19 */
extern float r4i_spin32C668[3];   /* 0x0032C668 spin rate of kind 0x18 */

extern R4cNode *r4i_player;       /* 0x00420E98 Jack's model node (g_playerObj) */
/* work block of the lobbed shot (0x00190BC0 family) */
typedef struct R4iShot {
    int32_t i00, i04;
    float   glow08;           /* +0x08 glow size */
    uint8_t unk0C[0x10 - 0x0C];
    uint8_t unk10[4];
    float   vel14[4];         /* +0x14 velocity */
    float   dist24;           /* +0x24 distance travelled */
} R4iShot;
void  sub_00101340(float *out);                                /* target position */
float r4c_VecLen(const float *v);                              /* 0x000F5F10 */

void r4i_FxShotUpdate(R4cNode *o, R4cActor *a);                /* 0x00190D50 */
void r4i_FxLobInit(R4cNode *o, R4cActor *a);                   /* 0x00190BC0 */

/* Scene node seen by the newer effect callbacks (same object as R4cNode,
   with more fields named). */
typedef struct R4iNode {
    uint8_t  unk00[0x08];
    int32_t  kind08;          /* +0x08 */
    uint32_t flagsC;          /* +0x0C */
    uint32_t flags10;         /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    struct R4iChainSet *set20; /* +0x20 chain/animation set */
    uint8_t  unk24[0x50 - 0x24];
    float    rot50[4];        /* +0x50 euler angles */
    float    pos60[4];        /* +0x60 */
    uint8_t  unk70[0x80 - 0x70];
    float    vel80[4];        /* +0x80 */
    uint8_t  unk90[0x9C - 0x90];
    float    alpha9C;         /* +0x9C fade level */
    uint8_t  unkA0[0xF0 - 0xA0];
    uint32_t flagsF0;         /* +0xF0 */
    uint8_t  unkF4[0x128 - 0xF4];
    uint32_t flags128;        /* +0x128 contact bits */
} R4iNode;
typedef struct R4iActor {
    uint8_t  unk00[0x60];
    int32_t  state60;         /* +0x60 */
    uint8_t  unk64[0x6C - 0x64];
    float    time6C;          /* +0x6C state time */
    float    f70;             /* +0x70 */
    void    *work;            /* +0x74 per-effect work block */
} R4iActor;
/* work block of the falling effect (0x00190260 family) */
typedef struct R4iFall {
    int32_t i00;
    int32_t landed04;         /* +0x04 */
    int32_t bounce08;         /* +0x08 bounce count / spin mode */
    float   vel0C[4];         /* +0x0C */
    float   f1C;
    float   scale20;          /* +0x20 */
} R4iFall;
extern float r4i_frameUnits;     /* 0x0042C858 */
extern float r4i_fps;            /* 0x0042C964 */
void  sub_000F5ED0(float *angle);                              /* wrap an angle */
void  r4i_SetScale(R4iNode *o, float k);                       /* 0x000EE760 */
int r4i_ObjDestroy(R4iNode *o);                              /* 0x000ED780 */
typedef struct R4iMgr {          /* returned by 0x00100110 */
    uint8_t  unk00[0x6C];
    int32_t  state6C;         /* +0x6C */
    uint8_t  unk70[0x8C - 0x70];
    R4iNode *node8C;          /* +0x8C */
    uint8_t  unk90[0x134 - 0x90];
    int32_t  h134;            /* +0x134 sound handle, -1 none */
    uint8_t  unk138[0x1CA - 0x138];
    int16_t  steer1CA;        /* +0x1CA */
    uint8_t  unk1CC[0x1E4 - 0x1CC];
    float    turn1E4;         /* +0x1E4 */
} R4iMgr;
/* work block of the homing effect (0x00190070) */
typedef struct R4iHome {
    void    *p00;
    int32_t  i04, i08;
    float    vel0C[4];        /* +0x0C */
} R4iHome;
R4iMgr *r4i_GetMgr(void);                                      /* 0x00100110 */
int   r4i_HomeHit(R4iHome *w);                                 /* 0x0018F950 regargs: p1=EDI */
void  r4i_FxDetach(R4iNode *o);                                /* 0x0018F8D0 regargs: p1=EAX */
void  sub_00048250(int h);
float sub_001A3EC0(float y, float x);                          /* atan2 */
void  sub_001AD7E0(float *d, const float *s);                  /* normalise */
/* 0x108-byte link of a chain (frames of a kind-1 set) */
typedef struct R4iChainLink {
    float    m00[16];         /* +0x00 rotation step; row 3 (+0x30) is the velocity */
    float    m40[16];         /* +0x40 world matrix; row 3 (+0x70) is the position */
    uint8_t  unk80[0xE8 - 0x80];
    float    fadeE8;          /* +0xE8 */
    uint8_t  unkEC[0x108 - 0xEC];
} R4iChainLink;
typedef struct R4iChainSet {
    float    mtx00[16];       /* +0x00 node matrix */
    uint8_t  unk40[0x8C - 0x40];
    int32_t  kind8C;          /* +0x8C must be 1 */
    uint8_t  unk90[0xC0 - 0x90];
    int32_t  countC0;         /* +0xC0 */
    R4iChainLink *linksC4;    /* +0xC4 */
} R4iChainSet;
typedef struct R4iChainWork { int32_t i00; int32_t calm04; } R4iChainWork;
float r4i_VecLenXZ(const float *v);                             /* 0x000F5F50 */
void  r4i_VecSub(float *d, const float *a, const float *b);     /* 0x001AD9F0 */
/* 0x88-byte slot record at 0x00400A88 (x4), also the slot effects' work */
typedef struct R4iSlot {
    R4iNode *obj;             /* +0x00 */
    R4iActor *actor;          /* +0x04 */
    int32_t  idx08;           /* +0x08 slot index 0..3 */
    float    t0C;             /* +0x0C state time, seconds */
    uint8_t  unk10[0x1C - 0x10];
    float    dir1C[4];        /* +0x1C per-frame velocity change */
    float    vel2C[4];        /* +0x2C velocity */
    float    off3C[4];        /* +0x3C */
    float    g4C;             /* +0x4C gravity step */
    float    v50;             /* +0x50 */
    float    v54;             /* +0x54 */
    float    scale58;         /* +0x58 */
    float    time5C;          /* +0x5C flight time, frames */
    int16_t  bounce60;        /* +0x60 */
    int16_t  flown62;         /* +0x62 */
    uint8_t  unk64[0x88 - 0x64];
} R4iSlot;
typedef struct R4iSys { uint8_t unk00[0x8C]; struct R4iSysNode *node8C; uint8_t unk90[0x114 - 0x90]; float yaw114; } R4iSys;
typedef struct R4iSysNode { uint8_t unk00[0x130]; void *motion130; } R4iSysNode;
extern R4iSlot r4i_slots400A88[4];   /* 0x00400A88 */
extern float   r4i_frameSeconds;     /* 0x0042C85C */
extern float   r4i_spin32C708[3];    /* 0x0032C708 */
void   r4i_SpinNode(R4iNode *o, const float *rate);             /* 0x000F6450 */
void   r4i_SlotScale(int idx, float s);                         /* 0x00192630 regargs: p1=EAX */
void   r4i_SetState(R4iNode *o, R4iActor *a, int st);           /* 0x00189DA0 */
int    sub_000F40C0(void);
R4iSys *r4i_GetSys(void);                                       /* 0x000F3F80 */
typedef struct R4iJoint {
    uint8_t  unk00[0x38];
    float    f38;             /* +0x38 */
    uint8_t  unk3C[0x70 - 0x3C];
    float    pos70[4];        /* +0x70 */
} R4iJoint;
R4iJoint *r4i_Joint(void *n, int part);                      /* joint record of a node */
void   sub_00033880(void *fx, float *m);
void   sub_00034DD0(void *fx, const float *pos, const float *dir, const float *col);
void   sub_000F3F90(int a);
typedef struct R4iMsg { int32_t id; uint8_t unk04[0x1C]; float v20[4]; } R4iMsg;
void   sub_001ADBA0(float *d, const float *s, float k);         /* 4-float scale */
int    sub_00087500(void);
void   sub_001AD8B0(void *d, const void *m, float pitch);       /* rotate about X */
void r4i_FxSlotLand(R4iNode *o, R4iActor *a);                   /* 0x00193040 */
int  r4i_FxSlotThrow(R4iNode *o, R4iActor *a);                  /* 0x00193260 */
typedef struct R4iDrop { float drop; int32_t i4; } R4iDrop;
typedef struct R4iChainRec {
    R4iNode *node;            /* +0x00 */
    int32_t  calm04;          /* +0x04 */
    R4iDrop  e08[13];         /* +0x08 per-link vertical drop */
} R4iChainRec;
void r4i_ChainFall(R4iChainRec *r);                             /* 0x00197BA0 */typedef struct R4iFollow {     /* work of the 0x00195F60 effect */
    R4iNode *target;          /* +0x00 */
    uint8_t  unk04[0x18 - 0x04];
    float    size18;          /* +0x18 */
    uint8_t  unk1C[0x88 - 0x1C];
    int16_t  sink88;          /* +0x88 */
    int16_t  follow8A;        /* +0x8A */
} R4iFollow;
extern R4iNode *r4i_jack;         /* 0x00420E98 Jack's model node (g_playerObj) */
float sub_001A3EE0(float a);                                    /* cosine (fcos) */
float sub_001A3ED0(float a);                                    /* sine (fsin) */
typedef struct R4iAim {        /* work of the 0x00199090 effect */
    int32_t  i00;
    void    *h04;             /* +0x04 attached effect */
    uint8_t  unk08[0x0C - 0x08];
    float    v0C[4];          /* +0x0C per-frame motion */
} R4iAim;
extern float r4i_aimTime;         /* 0x0032C8E0 0.15 */
extern float r4i_aimBase;         /* 0x0032C8E4 -40 */
extern float r4i_aimSpread;       /* 0x0032C8E8 10 */
extern float r4i_aimYawSpread;    /* 0x0032C8EC 5 degrees */
void  r4i_CamPoint(float *out, R4iNode *o);                     /* 0x00198DA0 regargs: p1=ESI p2=EDI */
void  sub_00034CF0(void *h, float a, float b, float c, float d);
void r4i_FxAimInit(R4iNode *o, R4iActor *a);                    /* 0x00199090 */
void r4i_FxFollow(R4iNode *o, R4iActor *a);                     /* 0x00195F60 */
typedef struct R4iBolt {        /* work of the 0x001961D0 effect */
    R4iSysNode *owner;        /* +0x00 */
    uint8_t  unk04[0x24 - 0x04];
    float    v24[4];          /* +0x24 origin */
    uint8_t  unk34[0x44 - 0x34];
    float    vel44[4];        /* +0x44 */
    uint8_t  unk54[0x58 - 0x54];
    int16_t  hit58;           /* +0x58 */
    uint8_t  unk5A[2];
    float    t5C;             /* +0x5C */
    float    prev60[4];       /* +0x60 */
} R4iBolt;
typedef struct R4iNodeV {     /* view of the node with the +0xF8 / +0x108 vectors */
    uint8_t  unk00[0x60];
    float    pos60[4];        /* +0x60 */
    uint8_t  unk70[0xF8 - 0x70];
    float    vF8[4];          /* +0xF8 */
    float    v108[4];         /* +0x108 */
    uint8_t  unk118[0x128 - 0x118];
    uint32_t flags128;        /* +0x128 */
} R4iNodeV;
int   r4i_PartFind(R4iSysNode *n, int a, int b);                 /* 0x000F5CD0 */
int   sub_000F6A80(void);
int   r4i_BoltProbe(R4iBolt *w, int k);                          /* 0x001954C0 regargs: p1=EAX */
float sub_001B2770(const float *a, const float *b);              /* XZ distance */
int r4i_Effect494D0(int id, float *pos, int c);                /* 0x000494D0 */
int r4i_ObjDestroyV(R4iNodeV *o);                              /* 0x000ED780 */
void *r4i_ListPlayMotion(R4iNodeV *o, void *motion, int a, int b); /* 0x00035DD0 */
void r4i_FxBoltUpdate(R4iNodeV *o, R4iActor *a);                 /* 0x001961D0 */
typedef struct R4iCyl { float pos[4]; float r10; float h14; } R4iCyl;   /* upright cylinder below pos */
int  r4i_SegHitCyl(const R4iCyl *c, const float *seg, float *out); /* 0x00194F00 */
void r4i_FxChainUpdate(R4iNode *o, R4iActor *a);               /* 0x00191860 */
void r4i_FxFallMove(R4iNode *o, R4iActor *a);                  /* 0x001902D0 */
void r4i_FxHomeUpdate(R4iNode *o, R4iActor *a);                /* 0x00190070 */

/* ------------------------------------------------------------ world model draw (0x001A2EB0) */
extern const char r4i_strDrawWorldModel27B5D4[];   /* 0x0027B5D4 "DrawWorldModel" */
extern int32_t r4i_rs1E243C;                        /* 0x001E243C render-state shadow */
int  r4i_DrawWorldModel(R4fDrawObj *o);             /* 0x001A2EB0 */

/* ------------------------------------------------------------ sound driver init (0x001AC680) */
typedef struct R4iRec3C { int32_t f00; int32_t f04; int32_t f08; uint8_t unk0C[0x3C - 0x0C]; } R4iRec3C;
typedef struct R4iRec18 { int32_t f00; uint8_t unk04[0x18 - 0x04]; } R4iRec18;
typedef struct R4iDevDesc { int32_t f00, f04, f08, f0C, f10; } R4iDevDesc;       /* 20 bytes */
typedef struct R4iDrvStat { uint16_t state00; uint16_t w02; int32_t f04; uint8_t unk08[0x28 - 0x08]; } R4iDrvStat;
typedef struct R4iPair { int32_t a, b; } R4iPair;
typedef struct R4iPairList { int32_t count; R4iPair *pairs; } R4iPairList;
typedef struct R4iBankDesc { int32_t a, b; } R4iBankDesc;
extern int32_t  r4i_refreshHz365168;     /* 0x00365168 50 or 60 */
extern R4iRec3C r4i_recs40C880[11];       /* 0x0040C880 */
extern R4iRec18 r4i_recs40CB20[45];       /* 0x0040CB20 */
extern void    *r4i_voiceA40E310;         /* 0x0040E310 */
extern void    *r4i_voiceB40E314;         /* 0x0040E314 */
extern void    *r4i_dev40E690;            /* 0x0040E690 */
extern int32_t  r4i_devId40E694;          /* 0x0040E694 */
extern int32_t  r4i_retries40EDD0;        /* 0x0040EDD0 */
extern const char r4i_strVoice27B968[];   /* "VOICE" */
extern const char r4i_strDemo27B960[];    /* "DEMO" */
extern const char r4i_strEffectBin27B940[]; /* "d:\Xact_data\effect\effect.bin" */
int   sub_001A88B0(void);
void  OOG_STDCALL sub_00203D52(void);
void  OOG_STDCALL sub_00223FCE(R4iDevDesc *d, void **dev);
void  sub_001AB9B0(void);
void  sub_001AB880(int id, const char *name);
int   OOG_STDCALL r4i_DrvQuery(void *dev, void *a, R4iDrvStat *out);          /* 0x00222573 */
int OOG_STDCALL r4i_DrvStatus(void *dev, R4fDrvQuery *q);                 /* 0x002225B2 */
void  OOG_STDCALL r4i_DrvStatus2(void *dev, R4fDrvQuery *q);                /* 0x002224FD */
void  OOG_STDCALL r4i_DrvVoice(void *dev, int kind, void **slot);           /* 0x0022239E */
void  OOG_STDCALL sub_002227BE(void *voice, R4iPairList *l);
void  OOG_STDCALL sub_0020578E(const char *path, R4iBankDesc *d, int a, int b);
void  r4i_SoundInit(void);                                                  /* 0x001AC680 */


#endif
