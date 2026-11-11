#ifndef R4D_H
#define R4D_H
#include "oogie.h"
#include "r4c.h"
/* Area r4d: remaining game functions in 0x00190000..0x001BC6D0 (fourth pass).
   All names inferred. Register mappings are in the comments and in
   config/function_states_r4d.csv. */

/* ------------------------------------------------------------ sound voices and cues (0x00199980..0x00199D88) */
int    sub_001AB150(int ch);
void   sub_001AAE20(int ch);
int    sub_001AB210(int cue, int bank);
int    sub_001AB1F0(int cue, int bank);
int    sub_001AB280(int cue, int bank);
int    sub_001AC2E0(int cue, int bank);
void   r4d_VoiceTick(int i);            /* 0x00199980 */
void   r4d_VoiceStop(int i);            /* 0x00199A40 */
void   r4d_VoiceSetVolume(int i, int vol);   /* 0x00199A90 */
void   r4d_VoiceStoreVolume(int i, int vol); /* 0x00199B20 */
void   r4d_VoiceUpdateAll(void);        /* 0x00199B50 */
void   r4d_CueStart(int cue, int bank); /* 0x00199C10 */
int    r4d_CuePoll(int cue);            /* 0x00199CA0 */

/* ------------------------------------------------------------ sound streams (0x00199EB0..0x0019A7DB) */
typedef struct R4dStream {    /* 0x00401D70 x45 (same table as r4c_streams401D70, more fields) */
    int32_t  used00;          /* +0x00 */
    int32_t  busy04;          /* +0x04 */
    int32_t  cue08;           /* +0x08 */
    int32_t  bank0C;          /* +0x0C */
    int32_t  state10;         /* +0x10 */
    int32_t  snd14;           /* +0x14 index into r4d_snd32C930 */
    uint8_t  unk18[4];
    int32_t  f1C;             /* +0x1C */
    uint8_t  unk20[8];
    int32_t  vol28;           /* +0x28 */
    int32_t  f2C;             /* +0x2C */
    int32_t  f30;             /* +0x30 */
    int32_t  n34;             /* +0x34 */
} R4dStream;
typedef struct R4dSnd { uint8_t p0[2]; uint16_t vol2; uint8_t p4[0x0E]; } R4dSnd;  /* 0x0032C930 x996 */
extern R4dStream r4d_streams401D70[45];
extern R4dSnd    r4d_snd32C930[996];
extern int32_t   r4d_g402768;          /* stream master volume */
int    sub_001AB0A0(int i);
void   sub_001AB850(void);
void   sub_001AC080(void);
void   sub_001AB2A0(int cue, int bank);
void   sub_001AB640(int vol, int a, int b, int j);
void   sub_001AC1D0(int snd, int bank, int j);
void   sub_001AB810(int a, float b, int j);
void   sub_001AB050(int a, int j, int x);
int    sub_00199E20(int j);
void   r4d_CueStartAll(int cue);        /* 0x00199EB0 */
void   r4d_StreamResume(int j);         /* 0x0019A230 */
void   r4d_StreamSetVolume(int j, int vol);  /* 0x0019A2F0 */
void   r4d_BankStopAll(int bank);       /* 0x0019A0E0 */
void   r4d_StreamSetParams(int j, int vol, int a, unsigned b, float c, int d);  /* 0x0019A390 */
void   r4d_BankPause(int bank, int x);  /* 0x0019A5A0 */

/* ------------------------------------------------------------ semaphore slots (0x001AA1A0..0x001AA51E) */
typedef struct R4dSemInfo {   /* the 0x18 bytes copied out by 0x001AA4D0 */
    int32_t  count;           /* +0x00 (slot +0x04) */
    int32_t  max;             /* +0x04 (slot +0x08) */
    int32_t  init;            /* +0x08 (slot +0x0C) */
    int32_t  waiters;         /* +0x0C (slot +0x10) */
    int32_t  f10;             /* +0x10 (slot +0x14) */
    int32_t  f14;             /* +0x14 (slot +0x18) */
} R4dSemInfo;
typedef struct R4dSem {       /* 0x0040C058 x64 */
    void      *h;             /* +0x00 semaphore handle */
    R4dSemInfo info;          /* +0x04 */
    int32_t    open1C;        /* +0x1C */
} R4dSem;
typedef struct R4dSemDesc { int32_t f00; int32_t max; int32_t init; int32_t f0C; int32_t f10; int32_t f14; } R4dSemDesc;
extern R4dSem  r4d_sems40C058[64];
extern void   *r4d_semLock40C858;     /* mutex guarding the table */
uint32_t OOG_STDCALL sub_001BD1CC(void *h, uint32_t ms);       /* WaitForSingleObject */
int      OOG_STDCALL sub_001BCFF2(void *h);                    /* ReleaseMutex */
int      OOG_STDCALL sub_001BC6FD(void *h);                    /* CloseHandle */
int      OOG_STDCALL sub_001BC741(void);                       /* GetLastError */
void    *OOG_STDCALL sub_001BD517(int size, int max, int align, int prot);
void    *OOG_STDCALL sub_001BCF19(void *attr, int init, int max, const char *name);  /* CreateSemaphore */
int      OOG_STDCALL sub_001BCF74(void *h, int n, int *prev);  /* ReleaseSemaphore */
OOG_IMPORT void OOG_STDCALL r4d_Kernel25F8E8(void *p);          /* kernel thunk slot 2 */
void  *r4d_AllocPersist(void);                 /* 0x001AA1A0 */
int    r4d_SemCreate(const R4dSemDesc *d);     /* 0x001AA240 */
int    r4d_SemSignal(int i, int n);            /* 0x001AA3E0 */
int    r4d_SemWait(int i);                     /* 0x001AA460 */
int    r4d_SemGetInfo(int i, R4dSemInfo *out); /* 0x001AA4D0 */

/* ------------------------------------------------------------ music tracks (0x0019AA00..0x0019AE82) */
typedef struct R4dTrackPart { int32_t vol; int32_t a; int32_t b; int32_t pad; } R4dTrackPart;
typedef struct R4dTrack {     /* 0x004019D8 x3 */
    int32_t  used00;          /* +0x00 */
    int32_t  busy04;          /* +0x04 */
    int32_t  state08;         /* +0x08 */
    int32_t  snd0C;           /* +0x0C index into r4d_snd3317C0 */
    uint8_t  unk10[8];
    int32_t  parts18;         /* +0x18 number of parts */
    uint8_t  unk1C[4];
    R4dTrackPart part[3];     /* +0x20 */
    uint8_t  unk50[0x0C];
    int32_t  n5C;             /* +0x5C pause depth */
} R4dTrack;
typedef struct R4dSndPart { uint8_t p0[6]; uint16_t vol6; } R4dSndPart;
typedef struct R4dSnd24 { uint8_t p0[0x24]; } R4dSnd24;   /* 0x003317C0 x612; 8-byte parts from +0 */
extern R4dTrack r4d_tracks4019D8[3];
extern R4dSnd24 r4d_snd3317C0[612];
extern int32_t  r4d_g402748, r4d_g401B28, r4d_g402770, r4d_g402774;
int    sub_0019A900(int i);
void   sub_001AB4A0(int snd, int kind);
void   sub_001AC9C0(int snd, int i, int k, int n, int a, int x, int b);
int    sub_001AAA20(int i, int x);
void   sub_001ABFE0(int i, int a);
void   sub_001ACAD0(int k, int a, int vol, int pa, int pb, int snd, int i, int n);
int    sub_001ACCE0(int i);
void   r4d_TrackRestart(int i, int x);          /* 0x0019AA00 */
void   r4d_TrackPlay(int i, int x);             /* 0x0019AAC0 */
void   r4d_TrackPause(int i);                   /* 0x0019AB40 */
void   r4d_TrackApplyPart(R4dTrack *t, int k, int vol, int i);  /* 0x0019ABB0 regargs: t=EAX k=ESI vol=EDX */
void   r4d_TrackSetPartVolume(int i, int k, int vol);           /* 0x0019AC20 */
void   r4d_TrackSetPart(int i, int k, int vol, int a, int b);   /* 0x0019AC70 */
void   r4d_TrackSetPartVolumeIfPlaying(int i, int k, int vol);  /* 0x0019AD50 */
void   r4d_TrackUpdateAll(void);                /* 0x0019AE00 */

/* ------------------------------------------------------------ sound driver (0x001AA970..0x001AB3C5) */
typedef struct R4dDrvVoice {  /* 0x0040CF50, 0x70 bytes each */
    int32_t  id00;            /* +0x00 */
    uint8_t  unk04[0x0C];
    int32_t  f10;             /* +0x10 */
    uint8_t  unk14[0x16];
    uint8_t  b2A;             /* +0x2A */
    uint8_t  unk2B[0x70 - 0x2B];
} R4dDrvVoice;
typedef struct R4dDrvMsg { int32_t kind; int32_t x; int32_t f08; int32_t f0C; } R4dDrvMsg;
extern R4dDrvVoice r4d_drvVoices40CF50[];
extern uint8_t  r4d_g40E6AA;
extern int32_t  r4d_g40E6AC, r4d_g40E6B0;
extern int32_t  r4d_drvFirst27B6AC[];  /* first object index per group */
extern int32_t  r4d_drvEnd27B6D4[];    /* end object index per group */
extern void    *r4d_drvObjs40E518[];
extern void    *r4d_drvDev40E690;
extern void    *r4d_drv40C868;
extern int32_t  r4d_drvMode40E348;
extern uint8_t  r4d_g40E6A8;
extern int32_t  r4d_g40E350, r4d_g40E310;
extern uint8_t  r4d_g40E300[];
void OOG_STDCALL sub_002227C8(void *o);
void OOG_STDCALL sub_00222790(void *o);
void OOG_STDCALL sub_0022239E(void *dev, int kind, void **slot);
int  OOG_STDCALL sub_002226F3(void *eng, R4dDrvMsg *m, void *out);
void   r4d_DrvSetFade(int x);                     /* 0x001AA970 */
void   r4d_DrvVoiceStop(int x, int j, int y);     /* 0x001AB050 */
void   r4d_DrvReleaseGroup(int unused, int g);    /* 0x001AB370 */

/* ------------------------------------------------------------ timers, files and render state (0x001A6E80..0x001A96BC) */
#ifdef _MSC_VER
#define R4D_FASTCALL __fastcall
#else
#define R4D_FASTCALL
#endif
extern int64_t  r4d_timerStart40B848;
extern int64_t  r4d_timerLen40B850;
extern int64_t  r4d_timerFreq40B858;
extern int32_t  r4d_timerOn40B87C;
extern char     r4d_path27B658[];
extern int32_t  r4d_padSel3650C8;
typedef struct R4dPad11C { uint8_t p0[0xD0]; int32_t fD0; uint8_t pD4[0x11C - 0xD4]; } R4dPad11C;
extern R4dPad11C *r4d_pads40B9A4;
extern int32_t  r4d_g1E2450;
int   OOG_STDCALL sub_001BD59E(int64_t *freq);   /* QueryPerformanceFrequency */
int   OOG_STDCALL sub_001BD58D(int64_t *count);  /* QueryPerformanceCounter */
void *OOG_STDCALL sub_001BCD0D(const char *name, uint32_t access, uint32_t share, void *sa, uint32_t disp, uint32_t flags, void *tmpl); /* CreateFile */
uint32_t OOG_STDCALL sub_001BCCD2(void *h, void *hi);   /* GetFileSize */
int   OOG_STDCALL sub_001BC813(void *h, void *buf, uint32_t n, uint32_t *read, void *ov);  /* ReadFile */
typedef struct R4dSysTime { uint16_t year, month, dow, day, hour, minute, second, ms; } R4dSysTime;
void  OOG_STDCALL sub_001BDD62(R4dSysTime *t);   /* GetSystemTime */
void *R4D_FASTCALL sub_001D24F0(int reg, const void *m);   /* set 4 shader constants from matrix m */
void  R4D_FASTCALL sub_001D2680(int kind, void *p, int n);
void  R4D_FASTCALL sub_001D4350(int reg, int v);
void   sub_001A5F50(void *o, int b);               /* regargs: o=ECX, b on the stack */
void   r4d_RenderUpload(uint8_t *p);               /* 0x001A7280 */
void   r4d_Call1A5F50(void *o);                   /* 0x001A7890 */
void   r4d_TimerStart(void);                       /* 0x001A8720 */
void   r4d_TimerStartMs(int ms);                   /* 0x001A8770 */
int    r4d_LoadFile(void *buf);                    /* 0x001A8860 */
void   r4d_GetDateTime(uint16_t *year, uint16_t *month, uint16_t *day, uint16_t *hour, uint16_t *minute, uint16_t *second); /* 0x001A8920 */
int    r4d_PadCheck(int a, int unused, int c);     /* 0x001A9630 */
int    r4d_PadPresent(int a);                      /* 0x001A9680 */

/* ------------------------------------------------------------ pads and save data (0x001A8680..0x001A9E50) */
typedef struct R4dPad {       /* 0x11C-byte pad records at *r4d_pads40B9A4 */
    uint16_t buttons;         /* +0x00 digital buttons */
    uint8_t  analog[8];       /* +0x02 analog buttons */
    uint8_t  unk0A[0x70 - 0x0A];
    int32_t  rumble70;        /* +0x70 rumble block, 0x3E5 = busy */
    uint8_t  unk74[0xB2 - 0x74];
    uint16_t motorL;          /* +0xB2 */
    uint16_t motorR;          /* +0xB4 */
    uint8_t  unkB6[0xD0 - 0xB6];
    void    *hD0;             /* +0xD0 device handle */
    uint8_t  unkD4[0x11C - 0xD4];
} R4dPad;
typedef struct R4dSaveSlot { int32_t f[3]; } R4dSaveSlot;   /* 0x003650E0, 12 bytes each */
extern R4dPad  *r4d_padRecs40B9A4;     /* same pointer as r4d_pads40B9A4 */
extern int32_t  r4d_saveLen40BF20;
extern uint8_t *r4d_saveBuf40BF24;
extern int32_t  r4d_saveLen40C028;
extern int32_t  r4d_saveOff40C03C;
extern R4dSaveSlot r4d_saveSlots3650E0[];
int   OOG_STDCALL sub_002593D8(void *h, void *rumble);   /* XInputSetState */
int    sub_001A9A90(R4dSaveSlot *s, int *size);
int    sub_001A9910(R4dSaveSlot *s, uint8_t *buf);
int    sub_001A9B90(uint8_t *buf, int len, uint8_t *end);
int    sub_001A9C00(uint8_t *buf, int len);
int64_t  r4d_TimerElapsedMs(void);                   /* 0x001A8680 */
void     r4d_PadRumble(int a, int right, int left);  /* 0x001A90B0 */
int      r4d_SaveCheck(int slot);                    /* 0x001A9D80 */

/* ------------------------------------------------------------ mode switching (0x0019BF80, 0x0019D2A0) */
extern int32_t r4d_g41316C, r4d_g413170;
void   sub_00047B70(int m);
int    sub_00047B90(int m);
void   sub_00047A80(int m);
int    sub_00047B10(int m);
void   sub_00047B30(int m);
int    sub_00047B50(int m);
void   sub_000576F0(int a, int b);
int    sub_00032470(int a);
void   sub_00087A50(void);
void   sub_000D1D00(PlayerStats *s);
void   sub_000D1930(PlayerStats *s);
void   sub_0019BEB0(int id);
int    sub_000DFC00(void);
void   sub_0005BBC0(void);
void   sub_0005C430(int a);
int    sub_000DFD00(void);
void   sub_000E0570(void);
typedef struct R4dCtx1F0 { uint8_t p0[0x1F0]; int32_t f1F0; } R4dCtx1F0;
typedef struct R4dDoneFlag { int32_t f00; int32_t done04; } R4dDoneFlag;
void   r4d_SwitchMode(int from, int to);       /* 0x0019BF80 */
void   r4d_ReturnToGame(R4dDoneFlag *job);     /* 0x0019D2A0 */

/* ------------------------------------------------------------ stage flow and jobs (0x0019E750..0x001A1716) */
typedef struct R4dJobNode {   /* 0x004044B8 x16, 0x1C bytes each */
    uint8_t  unk00[0x0C];
    struct R4dJobNode *self0C;  /* +0x0C */
    int32_t  f10, f14, f18;   /* +0x10 */
} R4dJobNode;
extern R4dJobNode   r4d_jobNodes4044B8[16];
extern uint8_t      r4d_jobQueue4044A8[], r4d_jobQueue404410[];
extern int32_t      r4d_g4044A0, r4d_g4044A4;
extern int32_t      r4d_g403960;
extern void        *r4d_g403964;
extern int32_t      r4d_g40396C;
extern int32_t      r4d_g403978;
extern R4cShockTab *r4d_shocks403988;
extern uint8_t      r4d_shake4042F8[];
extern int32_t      r4d_names337748[3];
extern int32_t      r4d_objs4046A4[3];
extern int32_t      r4d_ids404688[3];
extern int32_t      r4d_g40467C;
void   sub_000DFD40(int *a, int *b);
int    sub_000E6840(int a);
void   sub_0004F0B0(void);
void   sub_0005E9B0(void);
void   sub_0004F4C0(void);
void   sub_00049470(void);
void   sub_00048EE0(int ms);
void   sub_000481B0(int a);
void   sub_000483A0(int a);
void   sub_0005CCD0(int a, int b);
void   sub_000DF990(void);
void   sub_000226B0(void);
void   sub_0005EB50(void);
void   sub_001A7F90(int a);
int    sub_001A7DC0(void);
void   sub_001BB6E0(void);
void   sub_0003FC10(void *s);
int    sub_0003FA70(int a, int b);
void   sub_0003FCB0(void *s, int a, int b, float c, float d);
void   sub_0003FCE0(void *s);
void   sub_0003D860(void *q);
void   sub_0003D880(void *q, void *node);
void  *sub_0003DC70(void *q);
int    sub_0019B9D0(void);
void   sub_000774C0(void);
int    sub_00037570(int name, int a);
int    sub_00084C00(int obj, int a);
void   sub_000588D0(int a);
void   sub_00058170(void);
void   r4d_StageEnd(int a);                    /* 0x0019E750 */
void   r4d_StageUnload(void *g);               /* 0x0019FD60 */
void   r4d_StageShocks(int hi, int lo);        /* 0x001A0020 */
void   r4d_JobsInit(void);                     /* 0x001A11F0 */
void   r4d_StageLoadCommon(void);              /* 0x001A1680 */

/* ------------------------------------------------------------ temporary data slot and small lists (0x001A1AC0..0x001A24CC) */
extern int32_t r4d_g4046BC;
extern void   *r4d_blob4046C0, *r4d_blob4046C4, *r4d_blob4046C8;
extern int32_t r4d_g4046CC, r4d_tempOn4046D0;
void  *sub_000532B0(int a, int b);
void  *sub_00052CB0(void *p);
void   sub_0004F620(int id);
void   sub_000539C0(int a, int b, int c);
void   sub_00053A00(int a);
int    sub_000512D0(int id, int b);
void   sub_00052B00(void *p);
void   sub_00052CF0(void *p, void *blob);
void   sub_000535F0(int a, int b, int c);
void   sub_00034370(void);
typedef struct R4dVec16 { int32_t v[4]; } R4dVec16;
typedef struct R4dList8 { uint32_t n; int32_t pad; R4dVec16 e[8]; } R4dList8;
typedef struct R4dIdxList { uint32_t n; int32_t pad; int32_t idx[1]; } R4dIdxList;
void   r4d_TempSave(void);                         /* 0x001A1AC0 */
void   r4d_TempRestore(void);                      /* 0x001A1B90 */
void   r4d_List8Add(R4dList8 *l, const R4dVec16 *v);  /* 0x001A1F50 */
void   r4d_UploadBones(uint8_t *obj, R4dIdxList *l);  /* 0x001A2480 */

/* ------------------------------------------------------------ D3D surface helpers (0x001A5310..0x001A748F) */
typedef struct R4dSurfDesc { uint32_t f[7]; } R4dSurfDesc;   /* 0x1C-byte surface description */
typedef struct R4dSurfOwner { uint8_t p0[0x54]; void *surf54; } R4dSurfOwner;
extern int32_t r4d_g40B0E8;
extern void   *r4d_g40AE68;
uint32_t sub_0003DDE0(int a);
void  OOG_STDCALL sub_001D6ED0(int n, void *rects, uint32_t flags, uint32_t color, float z, uint32_t stencil);  /* Clear */
void *OOG_STDCALL sub_001D3490(int index);                       /* GetBackBuffer */
void  OOG_STDCALL sub_001D34E0(void *dst, void *a, void *b, void *src, void *c);  /* copy surface */
void *OOG_STDCALL sub_001D61C0(void *tex, int level);           /* GetSurfaceLevel */
void  OOG_STDCALL sub_001D7D50(void *surf, R4dSurfDesc *d);     /* GetDesc */
void   r4d_ClearToBackColour(void);    /* 0x001A5310 */
void   r4d_ClearAllBuffers(void);      /* 0x001A5400 */
void   r4d_CopyBackBuffers(void);      /* 0x001A5500 */
int    r4d_CopyToBackBuffer(void);     /* 0x001A7430 */

/* ------------------------------------------------------------ model part tables (0x001AEE90..0x001BB928) */
typedef struct R4dBone { uint8_t p0[0x38]; int32_t idx38; } R4dBone;
typedef struct R4dPart130 {   /* 0x130-byte parts */
    uint8_t  p0[0xB8];
    uint32_t maskB8;          /* +0xB8 */
    void    *pBC;             /* +0xBC */
    uint8_t  pC0[0x130 - 0xC0];
} R4dPart130;
typedef struct R4dModel130 { uint8_t p0[0xB0]; int32_t nB0; R4dPart130 *partsB4; } R4dModel130;
typedef struct R4dPart108 {   /* 0x108-byte parts */
    uint8_t  p0[0xBC];
    R4dBone *boneBC;          /* +0xBC */
    uint8_t  pC0[0xD8 - 0xC0];
    int32_t  valD8;           /* +0xD8 */
    uint8_t  pDC[0x108 - 0xDC];
} R4dPart108;
typedef struct R4dModel108 { uint8_t p0[0xC0]; uint32_t nC0; R4dPart108 *partsC4; } R4dModel108;
typedef struct R4dPart100 {   /* 0x100-byte parts */
    uint8_t  p0[0xBC];
    R4dBone *boneBC;          /* +0xBC */
    uint8_t  pC0[0xD0 - 0xC0];
    int32_t  valD0;           /* +0xD0 */
    uint8_t  pD4[0x100 - 0xD4];
} R4dPart100;
typedef struct R4dModel100 { uint8_t p0[0xC0]; uint32_t nC0; R4dPart100 *partsC4; } R4dModel100;
uint32_t r4d_PartsMask(R4dModel130 *m);                    /* 0x001AEE90 */
uint32_t r4d_PartsSetMask(R4dModel130 *m, uint32_t bits);  /* 0x001AEED0 */
uint32_t r4d_PartsClearMask(R4dModel130 *m, uint32_t bits);/* 0x001AEF10 */
void     r4d_PartsBoneOffset(R4dModel108 *m, int base);    /* 0x001B30C0 */
void     r4d_PartsBoneLookup(R4dModel108 *m, const int32_t *tbl);  /* 0x001B3110 */
void     r4d_Parts100BoneLookup(R4dModel100 *m, const int32_t *tbl); /* 0x001BB8E0 */

/* ------------------------------------------------------------ thread table (0x001AD2C0..0x001AD4A0) */
typedef struct R4dThread {    /* 0x0040EDD8 x32 */
    void    *h00;             /* +0x00 thread handle */
    int32_t  id04;            /* +0x04 */
    void    *f08;             /* +0x08 thread entry (descriptor +0x04) */
    int32_t  state0C;         /* +0x0C */
    int32_t  f10;
    void    *ev14;            /* +0x14 event handle */
} R4dThread;
extern R4dThread r4d_threads40EDD8[32];
extern void     *r4d_threadLock40F0D8;
int   OOG_STDCALL sub_001BD2B6(void *h);   /* ResumeThread */
int   OOG_STDCALL sub_001BCEF9(void *h);   /* SetEvent */
int   sub_001BD50A(void);                  /* GetCurrentThreadId */
#ifdef _MSC_VER
__declspec(noreturn)
#endif
void  OOG_STDCALL sub_001BD345(int code);  /* ExitThread, does not return */
int    r4d_ThreadClose(int id);            /* 0x001AD2C0 */
int    r4d_ThreadStart(int id);            /* 0x001AD3D0 */
int    r4d_ThreadStop(int id);             /* 0x001AD440 */
void   r4d_ThreadExitSelf(void);           /* 0x001AD520 */

/* ------------------------------------------------------------ matrices (0x001ADBF0) */
typedef struct R4dMat { float m[4][4]; } R4dMat;
void OOG_STDCALL sub_001E4D28(R4dMat *out, float angle);   /* rotation about Z */
void OOG_STDCALL sub_001E4CAD(R4dMat *out, float angle);   /* rotation about Y */
void OOG_STDCALL sub_001E4C33(R4dMat *out, float angle);   /* rotation about X */
void OOG_STDCALL sub_001E522D(R4dMat *out, const R4dMat *a, const R4dMat *b);  /* multiply */
void   r4d_MatRotateZYX(R4dMat *out, const R4dMat *in, const float *rot);  /* 0x001ADBF0 */

#endif
