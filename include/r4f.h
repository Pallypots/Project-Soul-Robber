#ifndef R4F_H
#define R4F_H
#include "oogie.h"
#include "shared_decls.h"
#include "r4e.h"
/* Area r4f: remaining game functions in 0x00190000..0x001BC6D0 (sixth pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4f.csv. */

/* Float to int truncation. The original inlines cvttss2si where the value
   is in an SSE register (modern cl calls __ftol2_sse instead); the
   intrinsic is used only for the 32-bit x86 comparison build. */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R4F_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R4F_FTOI(x) ((int)(x))
#endif
#if 0 /* PORT: this block was hidden by a misplaced #endif and never compiled on any target;
         enabling it gives redefinition errors against declarations later in this header. */
/* ------------------------------------------------------------ driver slot reset and stream file close (0x001A3A80, 0x001AD150) */
typedef struct R4fStrFile {   /* streamed file: a std::string name, a handle and a lock */
    uint8_t  name00[0x1C];    /* +0x00 std::string */
    uint8_t  unk1C[4];
    void    *h20;             /* +0x20 file handle (-1 when closed) */
    uint8_t  unk24[0x2C - 0x24];
    void    *lock2C;          /* +0x2C */
    int32_t  open30;          /* +0x30 */
    uint8_t  unk34[4];
    int32_t  f38;             /* +0x38 */
    uint8_t  unk3C[0x50 - 0x3C];
} R4fStrFile;
typedef struct R4fSlot {      /* driver slot, 0xB4 bytes (0x0040E604 table) */
    int32_t  id00;            /* +0x00 */
    void    *h04;             /* +0x04 */
    R4fStrFile file08;        /* +0x08 */
    void    *h58;             /* +0x58 */
    R4fStrFile file5C;        /* +0x5C */
    int32_t  fAC;             /* +0xAC */
    int32_t  fB0;             /* +0xB0 */
} R4fSlot;
void   OOG_STDCALL r4f_StrErase1A38C0(void *str, int pos, int n);   /* 0x001A38C0 thiscall, ECX=str */
void   OOG_STDCALL sub_00222662(void *o);
void   R4D_FASTCALL r4f_FileClose(R4fStrFile *f);   /* 0x001A3A80 regargs: f=ECX */
void   R4D_FASTCALL r4f_SlotReset(R4fSlot *s);      /* 0x001AD150 regargs: s=ECX */

/* ------------------------------------------------------------ thread table (0x001AD260, 0x001AD720) */
typedef struct R4fThreadDesc { uint8_t unk00[4]; void *fn04; uint8_t unk08[0x14 - 0x08]; int32_t prio14; } R4fThreadDesc;
void   OOG_STDCALL sub_001BD3B2(int a);
void  *OOG_STDCALL sub_001BD49C(void *sa, uint32_t stack, void *fn, void *arg, uint32_t flags, int32_t *id);   /* CreateThread */
int    sub_001AD570(int id, int prio);
void   r4f_ThreadTableInit(void);                          /* 0x001AD260 */
int    r4f_ThreadCreate(const R4fThreadDesc *d, void *arg);  /* 0x001AD720 */

/* ------------------------------------------------------------ track part fades (0x001AC8F0) */
typedef struct R4fFadePart { uint32_t target; uint32_t cur; } R4fFadePart;
typedef struct R4fTrackFade { /* 0x0040C880 x10, 0x3C bytes */
    int32_t  id00;            /* +0x00 */
    int32_t  mode04;          /* +0x04 */
    int32_t  f08;             /* +0x08 */
    uint32_t steps0C;         /* +0x0C */
    uint8_t  unk10[4];
    int32_t  n14;             /* +0x14 */
    uint8_t  b18;             /* +0x18 */
    uint8_t  unk19[3];
    R4fFadePart part1C[4];    /* +0x1C */
} R4fTrackFade;
void   sub_001AC3E0(int id, int k, uint32_t vol, int x);
void   r4f_TrackFadeStep(R4fTrackFade *f);   /* 0x001AC8F0 */

/* ------------------------------------------------------------ music players (0x001ABC10..0x001AC078) */
typedef struct R4fMusTrack {  /* 0x0040E358 x4, 0x70 bytes */
    int32_t  cue00;           /* +0x00 cue map id, -1 when free */
    int32_t  mode04;          /* +0x04 engine index */
    uint8_t  unk08[4];
    int32_t  f0C;             /* +0x0C */
    uint8_t  unk10[4];
    int32_t  f14, f18, f1C;   /* +0x14 */
    uint8_t  unk20[4];
    int32_t  id24;            /* +0x24 */
    uint8_t  b28;             /* +0x28 */
    uint8_t  paused29;        /* +0x29 */
    uint8_t  unk2A[2];
    uint16_t w2C;             /* +0x2C start of the status block */
    uint16_t w2E;             /* +0x2E */
    void    *f30;             /* +0x30 */
    uint8_t  unk34[4];
    void    *h38;             /* +0x38 */
    uint8_t  unk3C[0x70 - 0x3C];
} R4fMusTrack;
typedef struct R4fCueRec { uint8_t unk00[0x14]; } R4fCueRec;   /* 0x14-byte cue records */
extern R4fMusTrack r4f_mus40E358[4];
extern void   *r4f_musPlay40E300[];      /* 0x0040E300 per-player handles (same address as r4d_g40E300) */
extern R4fCueRec r4f_cues338858[], r4f_cues33AE40[];
extern int32_t r4f_g365164, aac_g365158;
int    OOG_STDCALL sub_0022268D(void *eng, R4fCueRec *c, void *out);
void   OOG_STDCALL sub_00222538(void *dev, void *status);
void   OOG_STDCALL sub_002224FD(void *dev, void *status);
int    r4f_MusStop(int a, int id);       /* 0x001ABC10 */
void   r4f_MusPlay(int unused, int id);  /* 0x001ABF20 */
void   r4f_MusPause(int id, int pause);  /* 0x001ABFE0 */

/* ------------------------------------------------------------ particle emitters (0x001B3160..0x001B8383) */
typedef struct R4fPartA {     /* 0x108-byte particle */
    uint8_t  unk00[0xDC];
    float    posDC[4];        /* +0xDC */
    uint8_t  unkEC[0x100 - 0xEC];
    int32_t  f100, f104;      /* +0x100 */
} R4fPartA;
typedef struct R4fPartB {     /* 0x110-byte particle */
    uint8_t  unk00[0xD8];
    float    posD8[4];        /* +0xD8 */
    int32_t  fE8, fEC;        /* +0xE8 */
    uint8_t  unkF0[0x110 - 0xF0];
} R4fPartB;
typedef struct R4fEmitter {
    uint8_t  unk00[0xC0];
    int32_t  n0C0;            /* +0xC0 */
    void    *parts0C4;        /* +0xC4 */
    uint8_t  unkC8[4];
    float    posCC[4];        /* +0xCC */
    uint8_t  unkDC[4];
    int32_t  fE0, fE4;        /* +0xE0 */
} R4fEmitter;
void   r4f_EmitASetPos(R4fEmitter *e);                    /* 0x001B3160 */
void   r4f_EmitASetPair(R4fEmitter *e, int a, int b);     /* 0x001B3210 */
void   r4f_EmitBSetPos(R4fEmitter *e);                    /* 0x001B8320 */
typedef struct R4fPartC { uint8_t unk00[0xF8]; int32_t fF8, fFC; } R4fPartC;   /* 0x100-byte particle */
typedef struct R4fEmitterC {
    uint8_t  unk00[0x90];
    uint32_t flags90;         /* +0x90 bit 0x100: particles keep their own pair */
    uint8_t  unk94[0xC0 - 0x94];
    int32_t  n0C0;            /* +0xC0 */
    R4fPartC *parts0C4;       /* +0xC4 */
    uint8_t  unkC8[0xD8 - 0xC8];
    int32_t  fD8, fDC;        /* +0xD8 */
} R4fEmitterC;
typedef struct R4fPartD { uint8_t unk00[0xB0]; int32_t fB0; uint8_t unkB4[0x118 - 0xB4]; int32_t f118; uint8_t unk11C[0x12C - 0x11C]; } R4fPartD;   /* 0x12C bytes */
typedef struct R4fEmitterD { uint8_t unk00[0xB0]; uint32_t n0B0; R4fPartD *parts0B4; } R4fEmitterD;
void   sub_001B6270(R4fEmitterD *e);
void   r4f_EmitCSetPair(R4fEmitterC *e, int a, int b);    /* 0x001BB990 */
void   r4f_EmitDReset(R4fEmitterD *e);                    /* 0x001B6D70 */

#endif

/* ------------------------------------------------------------ fade start (0x0019FEF0) */
extern int32_t a19_g403974;
extern int32_t r4f_g404338, r4f_g40433C, r4f_g404340, r4f_g404344, r4f_g404348, r4f_g40434C;
void   r4f_FadeStart(float a, int b, int c, int d, int e, int f);   /* 0x0019FEF0 */

/* ------------------------------------------------------------ idle draw loop (0x0019D390) */
uint32_t *sub_000AA500(uint32_t *cmd);
uint32_t *sub_000325E0(uint32_t *cmd);
void   r4f_IdleDrawLoop(void);          /* 0x0019D390 never returns */

/* ------------------------------------------------------------ blend presets (0x001A2500) */
/* sub_001D4350 (SetRenderState, fastcall ECX EDX) is declared in r4d.h */
void   OOG_STDCALL sub_001D55A0(int a);
void   OOG_STDCALL sub_001D5630(int a);
void   OOG_STDCALL sub_001D56D0(int a);
void   OOG_STDCALL sub_001D4720(int a);
extern int32_t  aac_g1E243C, aac_g1E2440;
extern int32_t  r4f_rs1E2460, r4f_rs1E2464, r4f_rs1E2468, r4f_rs1E246C, r4f_rs1E2470, r4f_rs1E2474;
void   r4f_SetBlendPreset(int mode);    /* 0x001A2500 */
void   r4f_SetBlendPresetB(int mode);   /* 0x001A27D0 */

/* ------------------------------------------------------------ normal model draw (0x001A3080) */
typedef struct R4fTexInfo {   /* texture block at draw object +0xC0 */
    uint8_t  unk00[0xE0];
    uint32_t fmtE0;           /* +0xE0 */
    int32_t  fE4;             /* +0xE4 */
    uint32_t fmtE8;           /* +0xE8 */
    int32_t  fEC;             /* +0xEC */
} R4fTexInfo;
typedef struct R4fMeshGrp {   /* group header; its vertex blocks start at +0x60 */
    int32_t  count00;         /* +0x00 blocks */
    int32_t  flags04;         /* +0x04 optional arrays of the blocks */
} R4fMeshGrp;
typedef struct R4fModelHdr {  /* model at draw object +0xBC; first group at +0x30 */
    int32_t  count00;         /* +0x00 groups */
} R4fModelHdr;
typedef struct R4fDrawObj {
    uint8_t  unk00[0xBC];
    R4fModelHdr *model0BC;    /* +0xBC */
    R4fTexInfo  *tex0C0;      /* +0xC0 */
    uint8_t  unkC4[0xCC - 0xC4];
    void    *blend0CC;        /* +0xCC blend block (one of three known globals) */
    int32_t  tex0D0;          /* +0xD0 */
    uint8_t  unkD4[0xD8 - 0xD4];
    int32_t  tex0D8;          /* +0xD8 */
    uint8_t  vsc0DC[8];       /* +0xDC vertex shader constants */
    uint8_t  fE4[8];          /* +0xE4 */
    uint8_t  fEC[4];          /* +0xEC */
} R4fDrawObj;
extern int32_t r4f_rs1E2498;
extern const char r4f_strDrawNormalModel27B5E4[];
extern uint8_t r4f_blk42C7E0[], r4f_blk42C860[], r4f_blk42CA00[];
int    r4f_PerfBegin1D60E0(uint32_t colour, const char *name);   /* 0x001D60E0 (stub, returns 0) */
int    r4f_PerfEnd1D60E0(void);                                  /* 0x001D60E0 (same folded stub) */
void   R4D_FASTCALL r4f_SetVSConsts1D2490(int reg, const void *p);  /* 0x001D2490 */
void  *r4f_TexLookup1B9650(int handle);                          /* 0x001B9650 */
void   r4f_TexBind1A6820(void *tex);                             /* 0x001A6820 */
void   sub_001A6C60(void *p);
void   sub_001A6F10(int a);
void   sub_001A6F50(int a);
void   sub_001A6E40(int a);
void   sub_001A69C0(uint32_t fmt, int b);
int    sub_001A7630(void);
int    r4f_DrawNormalModel(R4fDrawObj *o);   /* 0x001A3080 */

/* ------------------------------------------------------------ DDS textures (0x001A6540) */
typedef struct R4fDDS {       /* DDS file image ("DDS " magic) */
    uint32_t magic00;         /* +0x00 */
    uint8_t  unk04[0x0C - 0x04];
    int32_t  height0C;        /* +0x0C */
    uint8_t  unk10[4];
    int32_t  linear14;        /* +0x14 pitch or linear size */
    uint8_t  unk18[4];
    int32_t  mips1C;          /* +0x1C */
    uint8_t  unk20[0x54 - 0x20];
    uint32_t fourcc54;        /* +0x54 */
} R4fDDS;
extern int32_t a1a_g40F124;          /* D3D device */
extern int32_t a1a_g1E2148;          /* device dirty flags */
extern int32_t r4f_rs1E2190, r4f_rs1E2448, r4f_rs1E244C, r4f_rs1E2478;
void   OOG_STDCALL r4f_AddRef1D5F10(void *res);       /* 0x001D5F10 */
int    OOG_STDCALL r4f_TexFromMemEx1E5CCD(int dev, const void *src, int size, int w, int h, int mips,
           int usage, int fmt, int pool, int filter, int mipFilter, int key, void *info, void *pal, void **out);  /* 0x001E5CCD */
void   r4f_TexCreateDDS(R4fDDS *d, void **out);       /* 0x001A6540 */

/* ------------------------------------------------------------ pad selection (0x001A8980) */
typedef struct R4fPadView {   /* view of the 0x0040B9A8 pad records used here */
    uint8_t  unk00[0x48];
    uint8_t  flags48;         /* +0x48 bit 0x10: button held */
    uint8_t  unk49[0xD0 - 0x49];
    void    *hD0;             /* +0xD0 device handle */
    uint8_t  unkD4[0x11C - 0xD4];
} R4fPadView;
extern R4fPadView r4f_padView40B9A8[4];   /* same records as r4e_pads40B9A8 */
extern int32_t r4f_padMode40BE18;
int    r4f_PadPickActive(void);        /* 0x001A8980 */

/* ------------------------------------------------------------ projection and fog (0x001A6D70, 0x001A7100) */
typedef struct R4fFog {
    float    near00;          /* +0x00 */
    float    far04;           /* +0x04 */
    float    start08;         /* +0x08 */
    float    end0C;           /* +0x0C */
    uint32_t colour10;        /* +0x10 ARGB */
} R4fFog;
typedef struct R4fLens {
    float    w00;             /* +0x00 */
    uint8_t  unk04[4];
    float    d08;             /* +0x08 */
    uint8_t  unk0C[0x20 - 0x0C];
    float    far20;           /* +0x20 */
} R4fLens;
extern float   r4e_g361AE0;          /* near plane */
extern float   r4f_g1E24C8, r4f_g1E24CC;
extern int32_t r4f_g1E24C4, a1a_g1E24C0;
float  r4f_Atan1A3EB0(float x);                                   /* 0x001A3EB0 atan via fpatan */
void   OOG_STDCALL r4f_PerspFovLH1E4E86(R4dMat *out, float fov, float aspect, float zn, float zf);  /* 0x001E4E86 */
void   OOG_STDCALL r4f_SetTransform1D2CF0(int state, const R4dMat *m);   /* 0x001D2CF0 */
void   OOG_STDCALL r4f_SetFogColour1D46D0(uint32_t abgr);         /* 0x001D46D0 */
void   r4f_MatCopy1ADA40(float *dst, const R4dMat *src);           /* 0x001ADA40 */
void   r4f_SetProjection(float *out, const R4fLens *l);   /* 0x001A6D70 */
void   r4f_SetFogRange(const R4fFog *f);                  /* 0x001A7100 */

/* ------------------------------------------------------------ screen copy (0x001A7490) */
typedef struct R4fQuad {      /* screen quad drawn by 0x001A5D90 */
    float    rgba[4];         /* +0x00 */
    float    x0, y0;          /* +0x10 */
    float    u0, v0;          /* +0x18 */
    float    x1, y1;          /* +0x20 */
    float    u1, v1;          /* +0x28 */
    float    z;               /* +0x30 */
} R4fQuad;
extern int32_t r4f_tss1E2150, r4f_tss1E2154, r4f_tss1E215C, r4f_tss1E2160;
void  *OOG_STDCALL r4f_GetTexture1D3A80(int stage);               /* 0x001D3A80 */
void   OOG_STDCALL r4f_SetTexture1D3AB0(int stage, void *tex);    /* 0x001D3AB0 */
void   r4f_DrawScreenCopy(void);        /* 0x001A7490 */

/* ------------------------------------------------------------ screen quads (0x001A5BD0, 0x001A5D90) */
typedef struct R4fTLVert { float x, y, z, rhw; uint32_t colour; float u, v; } R4fTLVert;   /* 0x1C bytes */
extern int32_t r4f_g1E24E8;
int    r4f_DrawQuadT2(const R4fQuad *q);         /* 0x001A5BD0 */
int    r4f_DrawQuad1A5D90(const R4fQuad *q);     /* 0x001A5D90 */

/* ------------------------------------------------------------ whole-file load (0x001AA810) */
typedef struct R4fOverlapped { uint32_t internal, internalHigh, offset, offsetHigh; void *event; } R4fOverlapped;
int    OOG_STDCALL r4f_GetOverlapped1BC7AE(void *h, R4fOverlapped *ov, uint32_t *n, int wait);   /* 0x001BC7AE GetOverlappedResult */
void  *r4f_Alloc1A8630(uint32_t size);                                      /* 0x001A8630 */
int    r4f_FileLoad(const char *path, void **outBuf, uint32_t *outSize);    /* 0x001AA810 */

/* ------------------------------------------------------------ music cue commands (0x001AAAE0) */
typedef struct R4fCueMap { int32_t id; int32_t cueA; int32_t cueB; } R4fCueMap;   /* 0x0027B720 x16 */
extern R4fCueMap r4f_cueMap27B720[16];
extern void   *r4f_engines40C868[];        /* 0x0040C868, indexed by r4d_drvMode40E348 */
extern void   *r4f_playA40E5CC, *r4f_playB40E34C;
extern int32_t r4f_g40E314, r4f_curB40C864, r4f_curA40E5D0;
int    OOG_STDCALL sub_002226C0(void *eng, R4dDrvMsg *m, void *out);
void   r4f_MusicCueCmd(int cmd, int id);     /* 0x001AAAE0 */

/* ------------------------------------------------------------ driver voice poll (0x001AB150) */
typedef struct R4fDrvVoice {  /* 0x0040CF50 x45, 0x70 bytes (same records as R4dDrvVoice) */
    int32_t  id00;            /* +0x00 */
    int32_t  f04;             /* +0x04 */
    uint8_t  unk08[0x24 - 0x08];
    int32_t  f24;             /* +0x24 */
    uint8_t  b28;             /* +0x28 */
    uint8_t  b29;             /* +0x29 */
    uint8_t  b2A;             /* +0x2A */
    uint8_t  unk2B;
    uint16_t w2C;             /* +0x2C start of the status block passed to 0x001AB0D0 */
    uint16_t w2E;             /* +0x2E */
    void    *f30;             /* +0x30 */
    int32_t  f34;             /* +0x34 */
    void    *h38;             /* +0x38 */
    uint8_t  unk3C[0x48 - 0x3C];
    uint16_t state48;         /* +0x48 */
    uint8_t  unk4A[0x70 - 0x4A];
} R4fDrvVoice;
extern R4fDrvVoice r4f_voices40CF50[45];
extern void   *r4f_voiceH40E5D8[];         /* 0x0040E5D8 per-voice handles */
typedef struct R4fDrvQuery { uint16_t kind00; uint16_t w02; void *f04; int32_t f08; void *h0C; int32_t f10, f14; } R4fDrvQuery;  /* 0x18 bytes */
typedef struct R4fDrvStatus { uint16_t state00; uint8_t flags02; uint8_t unk03[0x28 - 3]; } R4fDrvStatus;
extern int32_t r4f_queryKinds27B7E0[4];
int    OOG_STDCALL sub_00222573(void *dev, R4fDrvQuery *q, void *out);
int    r4f_DrvStatus1AB0D0(const R4fDrvQuery *q, void *out);         /* 0x001AB0D0 */
void   r4f_DrvVoicePoll(int v);        /* 0x001AAE20 */
void   sub_001AAD40(int a, int id, int b, int v);
int    r4f_DrvVoiceBusy(int v);        /* 0x001AB150 */

/* ------------------------------------------------------------ driver start and wait (0x001AC2E0, 0x001AC370) */
extern R4eDrvSlot r4f_slots40E6B8[];     /* 0x0040E6B8 = aac_g40E604 + 1, indexed by group - 1 */
typedef struct R4fSndDesc { uint8_t unk00[0x30]; } R4fSndDesc;   /* 0x00365780, 0x30 bytes per sound */
extern R4fSndDesc r4f_snd365780[];
void   R4D_FASTCALL sub_001AD150(R4eDrvSlot *d);
int    R4D_FASTCALL sub_001ACF20(R4eDrvSlot *d);
void   OOG_STDCALL r4f_SlotPrepare1AD1B0(R4eDrvSlot *d, int snd);     /* 0x001AD1B0 thiscall, ECX=d */
void   OOG_STDCALL sub_001BD0D6(int a, int b);
void   OOG_STDCALL sub_002224DD(void *dev, R4fSndDesc *d, int c);
int    r4f_DrvStart(int snd, int g);         /* 0x001AC2E0 */
void   r4f_DrvStartWait(int snd, int i);     /* 0x001AC370 */

/* ------------------------------------------------------------ driver slot reset and stream file close (0x001A3A80, 0x001AD150) */
typedef struct R4fStrFile {   /* streamed file: a std::string name, a handle and a lock */
    uint8_t  name00[0x1C];    /* +0x00 std::string */
    uint8_t  unk1C[4];
    void    *h20;             /* +0x20 file handle (-1 when closed) */
    uint8_t  unk24[0x2C - 0x24];
    void    *lock2C;          /* +0x2C */
    int32_t  open30;          /* +0x30 */
    uint8_t  unk34[4];
    int32_t  f38;             /* +0x38 */
    uint8_t  unk3C[0x50 - 0x3C];
} R4fStrFile;
typedef struct R4fSlot {      /* driver slot, 0xB4 bytes (0x0040E604 table) */
    int32_t  id00;            /* +0x00 */
    void    *h04;             /* +0x04 */
    R4fStrFile file08;        /* +0x08 */
    void    *h58;             /* +0x58 */
    R4fStrFile file5C;        /* +0x5C */
    int32_t  fAC;             /* +0xAC */
    int32_t  fB0;             /* +0xB0 */
} R4fSlot;
void   OOG_STDCALL r4f_StrErase1A38C0(void *str, int pos, int n);   /* 0x001A38C0 thiscall, ECX=str */
void   OOG_STDCALL sub_00222662(void *o);
void   R4D_FASTCALL r4f_FileClose(R4fStrFile *f);   /* 0x001A3A80 regargs: f=ECX */
void   R4D_FASTCALL r4f_SlotReset(R4fSlot *s);      /* 0x001AD150 regargs: s=ECX */

/* ------------------------------------------------------------ thread table (0x001AD260, 0x001AD720) */
typedef struct R4fThreadDesc { uint8_t unk00[4]; void *fn04; uint8_t unk08[0x14 - 0x08]; int32_t prio14; } R4fThreadDesc;
void   OOG_STDCALL sub_001BD3B2(int a);
void  *OOG_STDCALL sub_001BD49C(void *sa, uint32_t stack, void *fn, void *arg, uint32_t flags, int32_t *id);   /* CreateThread */
int    sub_001AD570(int id, int prio);
void   r4f_ThreadTableInit(void);                          /* 0x001AD260 */
int    r4f_ThreadCreate(const R4fThreadDesc *d, void *arg);  /* 0x001AD720 */


/* ------------------------------------------------------------ track part fades (0x001AC8F0) */
typedef struct R4fFadePart { uint32_t target; uint32_t cur; } R4fFadePart;
typedef struct R4fTrackFade { /* 0x0040C880 x10, 0x3C bytes */
    int32_t  id00;            /* +0x00 */
    int32_t  mode04;          /* +0x04 */
    int32_t  f08;             /* +0x08 */
    uint32_t steps0C;         /* +0x0C */
    uint8_t  unk10[4];
    int32_t  n14;             /* +0x14 */
    uint8_t  b18;             /* +0x18 */
    uint8_t  unk19[3];
    R4fFadePart part1C[4];    /* +0x1C */
} R4fTrackFade;
void   sub_001AC3E0(int id, int k, uint32_t vol, int x);
void   r4f_TrackFadeStep(R4fTrackFade *f);   /* 0x001AC8F0 */

/* ------------------------------------------------------------ music players (0x001ABC10..0x001AC078) */
typedef struct R4fMusTrack {  /* 0x0040E358 x4, 0x70 bytes */
    int32_t  cue00;           /* +0x00 cue map id, -1 when free */
    int32_t  mode04;          /* +0x04 engine index */
    uint8_t  unk08[4];
    int32_t  f0C;             /* +0x0C */
    uint8_t  unk10[4];
    int32_t  f14, f18, f1C;   /* +0x14 */
    uint8_t  unk20[4];
    int32_t  id24;            /* +0x24 */
    uint8_t  b28;             /* +0x28 */
    uint8_t  paused29;        /* +0x29 */
    uint8_t  unk2A[2];
    uint16_t w2C;             /* +0x2C start of the status block */
    uint16_t w2E;             /* +0x2E */
    void    *f30;             /* +0x30 */
    uint8_t  unk34[4];
    void    *h38;             /* +0x38 */
    uint8_t  unk3C[0x70 - 0x3C];
} R4fMusTrack;
typedef struct R4fCueRec { uint8_t unk00[0x14]; } R4fCueRec;   /* 0x14-byte cue records */
extern R4fMusTrack r4f_mus40E358[4];
extern void   *r4f_musPlay40E300[];      /* 0x0040E300 per-player handles (same address as r4d_g40E300) */
extern R4fCueRec r4f_cues338858[], r4f_cues33AE40[];
extern int32_t r4f_g365164, aac_g365158;
int    OOG_STDCALL sub_0022268D(void *eng, R4fCueRec *c, void *out);
void   OOG_STDCALL sub_00222538(void *dev, void *status);
void   OOG_STDCALL sub_002224FD(void *dev, void *status);
int    r4f_MusStop(int a, int id);       /* 0x001ABC10 */
void   r4f_MusPlay(int unused, int id);  /* 0x001ABF20 */
void   r4f_MusPause(int id, int pause);  /* 0x001ABFE0 */

/* ------------------------------------------------------------ particle emitters (0x001B3160..0x001B8383) */
typedef struct R4fPartA {     /* 0x108-byte particle */
    uint8_t  unk00[0xDC];
    float    posDC[4];        /* +0xDC */
    uint8_t  unkEC[0x100 - 0xEC];
    int32_t  f100, f104;      /* +0x100 */
} R4fPartA;
typedef struct R4fPartB {     /* 0x110-byte particle */
    uint8_t  unk00[0xD8];
    float    posD8[4];        /* +0xD8 */
    int32_t  fE8, fEC;        /* +0xE8 */
    uint8_t  unkF0[0x110 - 0xF0];
} R4fPartB;
typedef struct R4fEmitter {
    uint8_t  unk00[0xC0];
    int32_t  n0C0;            /* +0xC0 */
    void    *parts0C4;        /* +0xC4 */
    uint8_t  unkC8[4];
    float    posCC[4];        /* +0xCC */
    uint8_t  unkDC[4];
    int32_t  fE0, fE4;        /* +0xE0 */
} R4fEmitter;
void   r4f_EmitASetPos(R4fEmitter *e);                    /* 0x001B3160 */
void   r4f_EmitASetPair(R4fEmitter *e, int a, int b);     /* 0x001B3210 */
void   r4f_EmitBSetPos(R4fEmitter *e);                    /* 0x001B8320 */
typedef struct R4fPartC { uint8_t unk00[0xF8]; int32_t fF8, fFC; } R4fPartC;   /* 0x100-byte particle */
typedef struct R4fEmitterC {
    uint8_t  unk00[0x90];
    uint32_t flags90;         /* +0x90 bit 0x100: particles keep their own pair */
    uint8_t  unk94[0xC0 - 0x94];
    int32_t  n0C0;            /* +0xC0 */
    R4fPartC *parts0C4;       /* +0xC4 */
    uint8_t  unkC8[0xD8 - 0xC8];
    int32_t  fD8, fDC;        /* +0xD8 */
} R4fEmitterC;
typedef struct R4fPartD { uint8_t unk00[0xB0]; int32_t fB0; uint8_t unkB4[0x118 - 0xB4]; int32_t f118; uint8_t unk11C[0x12C - 0x11C]; } R4fPartD;   /* 0x12C bytes */
typedef struct R4fEmitterD { uint8_t unk00[0xB0]; uint32_t n0B0; R4fPartD *parts0B4; } R4fEmitterD;
void   sub_001B6270(R4fEmitterD *e);
void   r4f_EmitCSetPair(R4fEmitterC *e, int a, int b);    /* 0x001BB990 */
void   r4f_EmitDReset(R4fEmitterD *e);                    /* 0x001B6D70 */


#endif
