#ifndef R4E_H
#define R4E_H
#include "oogie.h"
#include "shared_decls.h"
#include "r4d.h"
#include <string.h>
/* Area r4e: remaining game functions in 0x00190000..0x001BC6D0 (fifth pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4e.csv. */

/* Zero a block (the original inlines this as rep stosd). The intrinsic is
 * used only for the 32-bit x86 comparison build; every other target gets
 * plain memset, which is the same behaviour. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <intrin.h>
#define R4E_ZERO(p, n) __stosd((unsigned long *)(p), 0, (n) / 4)
#else
#define R4E_ZERO(p, n) memset((p), 0, (n))
#endif

/* ------------------------------------------------------------ sound init (0x0019B500) */
typedef struct R4eMusicSlot { /* 0x00401AF8 x1 */
    int32_t  used00;          /* +0x00 */
    int32_t  on04;            /* +0x04 */
    int32_t  f08;             /* +0x08 */
    int32_t  track0C;         /* +0x0C */
    int32_t  i10;             /* +0x10 */
    uint8_t  b14;             /* +0x14 */
    uint8_t  unk15[0x20 - 0x15];
    int32_t  w20, w24, w28;   /* +0x20 */
    int32_t  n2C;             /* +0x2C */
} R4eMusicSlot;
extern R4eMusicSlot r4e_music401AF8[1];
extern int32_t r4e_g402758, r4e_g40275C, r4e_g402760, r4e_g40276C;
void   sub_001AA1D0(void *lock);
void   r4e_Trace102FA0();     /* 0x00102FA0 empty debug stub, one-argument call sites */
void   sub_001995A0(void);
void   r4e_SoundInit(void);             /* 0x0019B500 */

/* ------------------------------------------------------------ game init and main loop (0x0019BA70..0x0019C5C6) */
extern int32_t r4e_g402FA0, r4e_g402FA8, r4e_g402FC0;
extern void   *r4e_g402F88, *r4e_g402F8C, *r4e_g402F90;
extern void  (*r4e_g402F94)(void);
extern int32_t r4e_g402F98, r4e_g402F9C, r4e_g402FB0, r4e_g402FB4, r4e_g402FB8, r4e_g402FBC;
extern int32_t r4e_g413160, r4e_g413164, r4e_g413168, r4e_g41316C, r4e_g413170, r4e_g413174;
extern uint8_t r4e_g402788[];
extern int32_t r4e_g42CA34, r4e_g42CA38, r4e_g42CA3C, r4e_g42CB00;
extern uint64_t r4e_frame42C918;
void   sub_001A11F0(void);
void   sub_00053C40(void);
void   sub_0004EAE0(void);
void   sub_00036BC0(void);
void   sub_000527B0(void);
void   sub_00012F90(void);
void   sub_001BBD90(void);
void   sub_00012000(void);
void   sub_00052970(float k);
void   sub_001BB2A0(void *p, int size);
void   sub_001BB2E0(int a, int b, int c);
void   sub_001BB780(void *p, int a, int b, int c, int d);
void   sub_001BB1D0(int a, int b, int c);
void   sub_001BB1F0(int a, int b, int c);
void   sub_001BB210(int a, int b, int c);
void   sub_001BA650(void *p, int size);
void   sub_001B9720(void);
void   sub_001B9730(void);
void   sub_001B16E0(void);
void   sub_00037AE0(void);
void   sub_00038FA0(void);
void   sub_000390B0(void);
int sub_00037F10(void);
void   sub_00075EF0(void);
void   sub_000186C0(void);
void   sub_000792F0(void);
void   sub_0005EDE0(void);
void   sub_0005EB40(int lang);
void   sub_001A1A70(void);
void   sub_000E6CE0(int a);
void   sub_0008CD50(void);
void   sub_0003DC90(void);
void   sub_000D9BF0(void);
int    sub_001A1CD0(void);
void   sub_001A1B90(void);
void   sub_00048590(void);
int    sub_00047950(void);
void   sub_00034B70(void);
void   sub_000E4F70(void);
int    sub_000E3050(void);
void   sub_00022920(void);
void   sub_000E7630(void);
void   sub_00031A10(void);
void   sub_0005FFA0(void);
void   sub_0006C1C0(int a, int b);
void   sub_0004F660(void);
void   sub_00079370(void);
void   sub_001A0DB0(void);
void   sub_000583C0(void);
void   sub_0019C3B0(void);
int sub_0019C2D0(void);
int sub_001A0660(float a, int b, int c, int d, int e, int f);
void   sub_001AD6A0(void);
void   sub_0019BCF0(void);
void   sub_0019C200(void);
void   sub_0004EB50(void);
void   sub_0004EC40(void);
void   sub_0004EC60(void);
void   sub_001BA640(int frame);
void   r4e_GameInit(void);              /* 0x0019BA70 */
void   r4e_GameStart(void);             /* 0x0019BC60 */
int    r4e_GameFrame(void);             /* 0x0019C4D0 */

/* ------------------------------------------------------------ menu/task flow (0x0019D460..0x0019E5EA) */
typedef struct R4eTask { int32_t f00; int32_t f04; } R4eTask;      /* argument of the 0x00058540 jobs */
typedef struct R4eStageCfg { int32_t a00; int32_t b04; } R4eStageCfg;   /* 0x00336DD8 [chapter][18] */
typedef struct R4eThreadDesc {  /* passed to 0x001AD720 */
    int32_t  f00;
    void    *entry04;           /* +0x04 */
    int32_t  f08, f0C;
    void    *arg10;             /* +0x10 */
    int32_t  prio14;            /* +0x14 */
} R4eThreadDesc;
extern R4eStageCfg r4e_stageCfg336DD8[][18];
extern int32_t r4e_g402FDC, r4e_g402FE0, r4e_g402FE4, r4e_g402FE8;
extern int32_t r4e_g402FF0, r4e_g402FF4, r4e_g402FF8, r4e_g402FFC;
extern int32_t a19_g337498;
extern uint8_t r4e_g40B860[];
void   sub_00032140(int a, int b, int c);
void   sub_000DDF20(int *a, int *b);
void   sub_00031B60(int a);
void   sub_00031AC0(int a);
void   sub_0019D360(void *p);
void   sub_0019D2A0(void *p);
void   sub_0019DFD0(void *p);
void   sub_0019D8E0(void);
void   sub_00086EF0(void);
void   sub_00085DE0(void);
void   sub_000AA4C0(void);
void   sub_000DE330(int a);
void   sub_00036FD0(float k);
void   sub_001A0D70(void);
int    sub_001AD720(R4eThreadDesc *d, void *arg);
void   sub_001A0CF0(int a, int b);
void   sub_001A0D30(int a, int b);
void   sub_000408B0(int a);
void   sub_000408C0(int a);
void   sub_0019D870(int a);
void   r4e_StageEnter(R4eTask *t);      /* 0x0019D460 */
void   r4e_LoaderInit(void);            /* 0x0019DF20 */
void   r4e_TitleTask(R4eTask *t);       /* 0x0019E530 */

/* ------------------------------------------------------------ scene setup and fades (0x0019FCF0..0x001A0633) */
typedef struct R4eScene {     /* 0x00403950, 0xAC0 bytes, cleared by 0x0019FCF0 */
    uint8_t  unk00[0x20];
    int32_t  stage20;         /* +0x20 (0x00403970) index into r4e_stageTab337518 */
    int32_t  b24;             /* +0x24 */
    int32_t  mode28;          /* +0x28 (0x00403978) */
    int32_t  c2C, d30, e34;   /* +0x2C */
    uint8_t  unk38[0xAC0 - 0x38];
} R4eScene;
typedef struct R4eStageEnt { int32_t fx00; uint8_t unk04[0x10]; } R4eStageEnt;   /* 0x00337518, 0x14 bytes */
extern R4eScene    r4e_scene403950;
extern R4eStageEnt r4e_stageTab337518[];
extern int32_t r4e_g404320, r4e_g404324, r4e_g404328, r4e_g40432C;
extern uint8_t r4c_opt413140;
int    sub_000529F0(void);
void   sub_00022750(int a);
void   sub_00022780(float k);
void   sub_001A5310(void);
int    sub_001A7FD0(void);
void   sub_001A8020(int a, int b, int c, int d);
void   sub_001A7FE0(void);
uint32_t *sub_00022900(uint32_t *cmd);
void   r4e_SceneSetup(int stage, int b, int mode, int c, int d, int e);   /* 0x0019FCF0 */
void   r4e_SceneRunLoop(int *state);    /* 0x001A0540 */

/* ------------------------------------------------------------ scene end and scene job (0x001A0660..0x001A0929) */
extern int32_t r4e_g404330;           /* fade channel 0, also the master volume set by 0x001A0830 */
extern int32_t r4e_g404334;           /* fade steps active */
extern uint8_t r4e_g3DE5B0[];
extern uint8_t r4c_opt413148;
void  *r4e_JobCurrent57E90(void);                     /* 0x00057E90 current job function */
void *r4e_SetFrameHook19BE50(void (*fn)(void));      /* 0x0019BE50 */
int r4e_AD090();                     /* 0x000AD090 */
void   r4e_Release4F5D0(int id);                      /* 0x0004F5D0 */
void   r4e_Nop102FA0();                      /* 0x00102FA0 used as an empty job */
void   sub_001A0640(void *arg);
void   sub_001A0200(void);
void   sub_0019FEF0(float a, int b, int c, int d, int e, int f);
void   sub_001A53F0(void);
void   sub_0019FFE0(void);
void   sub_001A0970(void *);
int    sub_001A7C10(int stage);
void   sub_001A80D0(int vol);
int    r4e_SceneEnd(float a, int b, int c, int d, int e, int f);   /* 0x001A0660 */
void   r4e_SceneJob(int *state);        /* 0x001A0830 */

/* ------------------------------------------------------------ render threads and setup (0x001A1320..0x001A224F) */
typedef struct R4eDrawJob { int32_t f00; int32_t mode04; } R4eDrawJob;   /* argument of 0x001A1320 */
typedef struct R4eStreamDesc { int32_t f00; uint32_t addr04; int32_t f08; } R4eStreamDesc;   /* 0x0040AFF8 x16, 12 bytes */
typedef struct R4eVtxHdr { int32_t count00; uint32_t flags04; uint8_t unk08[8]; } R4eVtxHdr;  /* data follows at +0x10 */
extern R4eStreamDesc r4e_streams40AFF8[16];
extern uint32_t r4e_rtSizeA341638[14], r4e_rtSizeB341670[14];
uint32_t *sub_0006D310(uint32_t *cmd);
int    sub_0006C260(void);
float  sub_00036FF0(void);
uint32_t *sub_0003DCE0(uint32_t *cmd);
uint32_t *sub_00036D70(uint32_t *cmd);
void   sub_001A7B90(void);
int    OOG_STDCALL sub_001D2330(uint32_t w, uint32_t h, void **out, int flags);   /* XDK, stdcall */
void   OOG_STDCALL sub_001D2870(int a);                                          /* XDK, stdcall */
void   OOG_STDCALL sub_001D26C0(int stream, R4eStreamDesc *d, int stride);       /* XDK, stdcall */
void   OOG_STDCALL sub_001D5C30(int prim, int start, int count);                 /* XDK, stdcall */
void   r4e_DrawThread(R4eDrawJob *job); /* 0x001A1320 */
int    r4e_RenderTargetsInit(void);     /* 0x001A1DA0 */
void   r4e_DrawVertexBlock(R4eVtxHdr **pp);   /* 0x001A2130 */

typedef struct R4eMeshTex { int32_t f00; uint32_t kind04; } R4eMeshTex;
typedef struct R4eModel {     /* draw model: mesh count at +0, first mesh at +0x60 */
    int32_t  count00;
    uint32_t flags04;         /* +0x04 bit 0..2: optional vertex arrays */
} R4eModel;
typedef struct R4eMesh { int32_t count00; uint32_t flags04; int32_t tex08; } R4eMesh;
void   r4e_DrawVertexBlockOpt(R4eVtxHdr **pp, int flags);  /* 0x001A2250 */
R4eMeshTex *sub_001AE8C0(void *texset, int id);
R4eMesh *sub_001AE920(R4eModel *m, R4eMesh *mesh);
void   sub_001A2480(void *ctx, R4eMeshTex *t);
int sub_001A1EE0(int mode);
void   sub_001A2370(R4eModel *m, R4eMesh *mesh);

/* ------------------------------------------------------------ immediate-mode draws (0x001A2D80, 0x001A36A0) */
extern uint32_t r4e_g40AD48, r4e_g40AD4C;     /* init guards of two function-local statics (empty initialisers) */
extern uint32_t r4e_rs1E245C;                 /* cached render state 0x40358 (D3D device block) */
int r4c_TargetSelect(int mode);            /* 0x001A1EE0 */
int    sub_001A1D50(int target);
void   OOG_STDCALL sub_001D4720(int a);
void   OOG_STDCALL sub_001D2E10(int state, R4dMat *out);                        /* GetTransform */
void   R4D_FASTCALL r4e_SetVSConst1D24F0(int reg, const R4dMat *m);             /* 0x001D24F0 */
void   OOG_STDCALL sub_001D5AC0(int prim, int count, const void *data, int stride);   /* DrawVerticesUP */
int    r4e_DrawPrimsUP(const void *verts, int count);    /* 0x001A2D80 */
int    r4e_DrawQuadsUP(const void *verts, int count);    /* 0x001A36A0 */

/* ------------------------------------------------------------ D3D wrappers (0x001A5480..0x001A70F8) */
typedef struct R4eRect { int32_t x0, y0, x1, y1; } R4eRect;
typedef struct R4eTexHdr { uint8_t unk00[0x10]; uint32_t data10; uint8_t unk14[0x28]; } R4eTexHdr;  /* 0x0040AE98, 0x0040AED4: 0x3C bytes */
typedef struct R4eSurf { uint32_t f00; uint32_t res04; uint8_t unk08[8]; uint32_t data10; } R4eSurf;
extern R4eRect   r4e_viewport361AE4;
extern R4eTexHdr r4e_backTex40AE98, r4e_depthTex40AED4;
int8_t sub_0019BA20(void);
int8_t sub_0019BA30(void);
void  OOG_STDCALL r4e_SetScissor1D3D80(int n, int flags, R4eRect *r);         /* 0x001D3D80 */
R4eSurf *OOG_STDCALL r4e_GetBackBuffer1D3490(int index);                     /* 0x001D3490 */
R4eSurf *OOG_STDCALL sub_001D3810(void);                                      /* GetDepthStencilSurface */
void  OOG_STDCALL r4e_GetDesc1D7D50(R4eSurf *s, R4dSurfDesc *d);             /* 0x001D7D50 */
int OOG_STDCALL r4e_Release1D5F50(void *res);                               /* 0x001D5F50 */
void   r4e_SetSafeViewport(void);                     /* 0x001A5480 */
void   r4e_SetRenderState4035C(int on);               /* 0x001A6E80 */
void   r4e_WrapFrameBuffers(void);                    /* 0x001A6F90 */
R4eTexHdr *r4e_WrapBackBuffer(void);                  /* 0x001A7040 */
R4eTexHdr *r4e_WrapDepthBuffer(void);                 /* 0x001A70A0 */

/* ------------------------------------------------------------ render init and pads (0x001A7640..0x001A8B53) */
typedef struct R4eLockedRect { int32_t pitch; uint8_t *bits; } R4eLockedRect;
typedef struct R4ePad {       /* 0x0040B9A8 x4, 0x11C bytes (same records as R4dPad11C) */
    uint8_t  unk00[0xB6];
    uint8_t  capsB6[0x1A];    /* +0xB6 capabilities */
    void    *hD0;             /* +0xD0 device handle */
    uint8_t  unkD4[0x11C - 0xD4];
} R4ePad;
extern float   r4e_depth40AE88[4];
extern float   r4e_g361AE0;
extern void   *r4e_g40AECC;
extern int32_t r4e_g40B0F0;
extern void   *g_presentEvent;
extern int32_t r4d_g40B0E8;
extern void   *r4d_g40AE68;
extern R4ePad  r4e_pads40B9A8[4];
extern uint8_t r4e_padType257FEC[];
extern int32_t r4d_padSel3650C8, aac_g3650CC;
void   OOG_STDCALL sub_001D4080(float a, float b);
void  *OOG_STDCALL sub_001BCE98(void *sa, int manual, int initial, const char *name);   /* CreateEvent */
void   OOG_STDCALL sub_001D2EB0(void (*fn)(void));
void   OOG_STDCALL sub_001D7310(void (*fn)(void));
void   sub_001A53A0(void);
void   sub_001A53B0(void);
int sub_001A1CE0(void);
void  *OOG_STDCALL sub_001D60F0(int w, int h, int levels, int usage, int fmt, int pool, int c);  /* CreateTexture */
void   OOG_STDCALL sub_002039F4(int a, int b, int c, int d, R4eStreamDesc *s, int e);
void   sub_001A72C0(void);
uint32_t OOG_STDCALL sub_00259432(void *type);                          /* XGetDevices */
void  *OOG_STDCALL sub_0025912B(void *type, int port, int slot, void *params);   /* XInputOpen */
int    OOG_STDCALL sub_0025918D(void *h, void *caps);                   /* XInputGetCapabilities */
int    sub_001BD792(void);
int    sub_001BD749(void);
void   r4e_SetDepthRange(float a, float b);   /* 0x001A7640 */
int    r4e_RenderInit(void);                  /* 0x001A7750 */


/* ------------------------------------------------------------ sound driver slot wait (0x001AB210) */
typedef struct R4eDrvSlot { uint8_t unk00[0xB4]; } R4eDrvSlot;   /* 0x0040E604, 0xB4 bytes */
extern R4eDrvSlot aac_g40E604[];
void *OOG_STDCALL sub_001BD128(void *sa, int manual, const char *name);                     /* CreateWaitableTimer */
int   OOG_STDCALL sub_001BD186(void *h, const int64_t *due, int period, void *fn, void *arg, int resume);  /* SetWaitableTimer */
int   R4D_FASTCALL sub_001ACF30(R4eDrvSlot *d);
int   R4D_FASTCALL sub_001ACF00(R4eDrvSlot *d);
int    r4e_DrvSlotSettle(int unused, int i);     /* 0x001AB210 */

/* ------------------------------------------------------------ frame timer and small math helpers (0x001AE430..0x001AF294) */
extern int64_t r4e_now40F0E0, r4e_total40F0F0, r4e_delta40F108, r4e_delta40F110, r4e_last40F118;
extern float   r4e_tick40F0E8;        /* seconds per counter tick */
extern float   r4e_dt40F0EC, r4e_nowSec40F0F8, r4e_dt40F0FC, r4e_totalSec40F100;
int   OOG_STDCALL sub_001BD58D(int64_t *count);   /* QueryPerformanceCounter */
typedef struct R4eImgHdr { uint8_t unk00[0x0C]; int32_t h0C; int32_t w10; uint8_t unk14[4]; int32_t f18; } R4eImgHdr;
void   r4e_TimerInit(void);             /* 0x001AE430 */
void   r4e_TimerTick(void);             /* 0x001AE710 */
int32_t *r4e_ImgLevelPtr(R4eImgHdr *img, int k);              /* 0x001AE8E0 */
R4eMesh *r4e_MeshNext(R4eModel *m, R4eMesh *mesh);            /* 0x001AE920 */
void   r4e_VecLerp(float *out, float k, const float *a, const float *b);   /* 0x001AF260 regargs: a=EAX b=ESI */

/* ------------------------------------------------------------ rotation order and motion timing (0x001AEAF0, 0x001AEFD0) */
typedef struct R4eMotion {    /* object driven by 0x001AEFD0 */
    uint8_t  unk00[0xBC];
    uint32_t flagsBC;         /* +0xBC low byte: state flags */
    uint8_t  unkC0[8];
    void    *animC8;          /* +0xC8 */
    int32_t  framesCC;        /* +0xCC */
    int32_t  frameD0;         /* +0xD0 */
} R4eMotion;
void   sub_001AD8B0(void *out, const void *in, float a);       /* rotate about X */
void   sub_001AD910(R4dMat *out, const R4dMat *in, float a);   /* rotate about Z */
float  sub_001BBD80(void);
void   sub_001AEF60(R4eMotion *o);                             /* regargs: o=EAX */
void   r4e_MotionStart(R4eMotion *o, void *anim, int flags, int frames);   /* 0x001AEFD0 */

/* ------------------------------------------------------------ vector and matrix helpers (0x001AD7E0..0x001AE055) */
typedef struct R4eVec4 { float x, y, z, w; } R4eVec4;
void  OOG_STDCALL sub_001E51AB(float *out, const float *in);   /* D3DX normalise */
void   r4e_VecNormalize3(float *out, const float *in);                       /* 0x001AD7E0 */
void   r4e_MatIdentity(float *m);                                            /* 0x001AD940 */
void   r4e_VecSub4(float *d, const float *a, const float *b);                /* 0x001AD9F0 */
void   r4e_VecCross3(R4eVec4 *d, const float *a, const float *b);            /* 0x001ADA60 */
void   r4e_VecAdd4(float *d, const float *a, const float *b);                /* 0x001ADAF0 */
void   r4e_VecScale4(float *d, const float *s, float k);                     /* 0x001ADBA0 */
void   r4e_VecLerp4(float *d, const float *a, const float *b, float t);      /* 0x001ADC60 */
void   r4e_VecLerp3(float *d, const float *a, const float *b, float t);      /* 0x001ADCD0 */
void   r4e_VecClamp4(R4eVec4 *d, const float *v, float lo, float hi);        /* 0x001ADD30 */
void   r4e_VecMul4(float *d, const float *a, const float *b);                /* 0x001ADE90 */
void   r4e_MatCopyTranslate(R4dMat *d, const R4dMat *s, const float *t);     /* 0x001AE010 */

/* ------------------------------------------------------------ view helpers and node init (0x001AE060..0x001AE9F7) */
typedef struct R4eNode {      /* node set up by 0x001AE970 */
    uint8_t  unk00[0x8C];
    int32_t  kind8C;          /* +0x8C */
    uint32_t flags90;         /* +0x90 */
    uint8_t  unk94[0xB0 - 0x94];
    int32_t  iB0, iB4, iB8, iBC, iC0;   /* +0xB0 */
    float    scaleC4;         /* +0xC4 */
    int32_t  iC8, iCC, iD0, iD4;        /* +0xC8 */
    float    fD8, fDC;        /* +0xD8 */
} R4eNode;
void   sub_001A73F0(R4dMat *m);
void   sub_001B25B0(R4eNode *n);
R4eNode *r4e_NodeInit(R4eNode *n);                                 /* 0x001AE970 */

/* ------------------------------------------------------------ more node initialisers (0x001B2FE0, 0x001B3450) */
typedef struct R4eNode1 {     /* kind 1 node, 0x001B2FE0 */
    uint8_t  unk00[0x8C];
    int32_t  kind8C;          /* +0x8C */
    uint8_t  unk90[0xB0 - 0x90];
    int32_t  iB0, iB4, iB8, iBC, iC0, iC4, iC8;   /* +0xB0 */
    float    colCC[4];        /* +0xCC */
    int32_t  iDC;
    int32_t  iE0, iE4, iE8, iEC;                   /* +0xE0 */
} R4eNode1;
typedef struct R4eNode14 {    /* kind 14 node, 0x001B3450 */
    uint8_t  unk00[0x8C];
    int32_t  kind8C;          /* +0x8C */
    uint8_t  unk90[0xB8 - 0x90];
    int32_t  iB8;             /* +0xB8 */
    float    fBC, fC0, fC4, fC8;   /* +0xBC */
    int32_t  iCC;             /* +0xCC */
    float    fD0, fD4, fD8;   /* +0xD0 */
} R4eNode14;
void   r4e_SubNodeBase(void *n);        /* 0x001B25B0 (same callee as sub_001B25B0) */
R4eNode1 *r4e_Node1Init(R4eNode1 *n);   /* 0x001B2FE0 */
void   r4e_Node14Init(R4eNode14 *n);    /* 0x001B3450 */

/* ------------------------------------------------------------ options and game-state threads (0x0019BED0, 0x0019FC60) */
extern uint8_t  r4c_opt413145, r4c_opt413146, r4c_opt413147, r4c_opt413149;
extern uint8_t  r4c_opt41314A, r4c_opt41314B;
extern uint16_t r4c_opt41314C;
extern int32_t  a19_g3374A0;
extern float    a19_g403004, a19_g403120, a9c_g403124;
extern void    *a19_g403128;
extern int32_t  r4c_g403130;
extern uint8_t  r4e_g403008[], r4e_g3374A8[];
void   sub_0003CFC0(int a);
void   sub_000479E0(int unused);   /* 0x000479E0 ignores its argument (tail jmp to 0x1997D0); the original caller pushes one */
void   sub_00048620(int v);
void   sub_000486F0(int v);
void   sub_001A76A0(int a);
void   sub_0019E990(void);
void   sub_0019FAC0(void);
void   sub_0001AE70(void *a, void *b);
void   r4e_ApplyOptions(void);          /* 0x0019BED0 */
void   r4e_GameStateStart(int *state);  /* 0x0019FC60 */

/* ------------------------------------------------------------ fade jobs (0x0019C6F0, 0x001A1280) */
extern int32_t a19_g336DD0;
extern float   a9b_g402FC8, a9b_g402FCC, a9b_g402FD0;
extern int32_t r4e_g402FD4;
int    sub_00036D40(void);
void   sub_00036C90(void);
void   sub_00036F90(float a, float b, float c);
void   sub_0003DD10(void);
void   sub_000325A0(int a);
void   r4e_FadeInJob(int *job);          /* 0x0019C6F0 */
void   r4e_ShakeFadeJob(int *job);       /* 0x001A1280 */

#endif
