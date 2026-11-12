/* Area m1: functions recovered directly (no helper). Names inferred. */
#ifndef M1_H
#define M1_H
#include "oogie.h"
#include "shared_decls.h"

typedef struct M1Fade {
    uint16_t on;        /* +0 */
    uint16_t mode;      /* +2 */
    uint8_t  b4, b5;    /* +4, +5 */
    uint16_t w6;        /* +6 */
    uint8_t  unk08[4];
    float    time;      /* +0xC */
} M1Fade;

void sub_00072DD0(M1Fade *f, int mode, float time, int arg);
void m1_FadeStart72EE0(M1Fade *f, int mode, float time, int arg);   /* 0x00072EE0 */
const char *sub_00052A10(void);  /* language suffix string (used with %s) */
void m1_PathOp53D70(const char *name);                        /* 0x00053D70 */
void sub_00053E20(const char *name, void *dst);
void m1_LoadFmt53ED0(const char *name, void *dst);                  /* 0x00053ED0 */
extern const char m1_fmt2DDCCC[];                                   /* 0x002DDCCC */
extern uint8_t *a60_work42C5E8;                                     /* 0x0042C5E8 */
void m1_LoadNum65A50(int n);                                        /* 0x00065A50 */
typedef struct M1DtObj { uint32_t x00; uint32_t id; uint8_t unk08[0x20]; uint8_t slot[0x10]; void *loaded; /* +0x38 (XBOX32) */ } M1DtObj;
void a80_PrintId(M1DtObj *o, void *out);                            /* 0x00089670 */
extern const char m1_fmtYca270200[];                                /* 0x00270200 */
extern const char m1_fmtClp270290[];                                /* 0x00270290 */
extern const char m1_fmtDfd270364[];                                /* 0x00270364 */
void m1_PathYca8DC40(char *out, int n, M1DtObj *o);                 /* 0x0008DC40 regargs: o=ESI */
void m1_PathClp8E8B0(char *out, int n, M1DtObj *o);                 /* 0x0008E8B0 regargs: o=ESI */
void m1_PathDfd8ED70(char *out, int n, M1DtObj *o);                 /* 0x0008ED70 regargs: o=ESI */
/* 0x00089690: a80 declares this as returning int32_t; the value is used with %s here,
 * so it is a string pointer (XBOX32) in the id table at 0x2E0908. */
const char *a80_IdValue(M1DtObj *o, int i);                         /* 0x00089690 */
extern const char m1_fmtLgt2703C8[];                                /* 0x002703C8 */
extern const char m1_fmtBms270408[];                                /* 0x00270408 */
void m1_PathLgt8EFB0(char *out, M1DtObj *o, int n);                 /* 0x0008EFB0 */
void m1_PathBms8F210(char *out, int i, M1DtObj *o);                 /* 0x0008F210 regargs: o=ESI */
extern const char m1_fmtEnemy26F904[];  /* 0x0026F904 */
extern void *m1_enemyArg3ED1CC;  /* 0x003ED1CC loaded enemy.arg */
void m1_LoadEnemyArg85300(int a, int b);  /* 0x00085300 */
extern const char m1_fmtLoadset26F95C[];  /* 0x0026F95C */
extern void *m1_loadsetArg3ED208;  /* 0x003ED208 loaded loadset.arg */
void m1_LoadLoadsetArg861A0(int a, int b);  /* 0x000861A0 */
extern const char m1_fmtBgobject26F98C[];  /* 0x0026F98C */
extern void *m1_bgobjectArg3ED210;  /* 0x003ED210 loaded bgobject.arg */
void m1_LoadBgobjectArg86E60(int a, int b);  /* 0x00086E60 */
extern const char m1_fmtResident26F9BC[];  /* 0x0026F9BC */
extern void *m1_residentArg3ED214;  /* 0x003ED214 loaded resident.arg */
void m1_LoadResidentArg86FA0(int a, int b);  /* 0x00086FA0 */
extern const char m1_fmtArrangeLin26F9EC[];                         /* 0x0026F9EC */
extern void *m1_arrangeLin3ED248;                                   /* 0x003ED248 */
extern int32_t m1_arrangeReady3ED21C;                               /* 0x003ED21C */
void m1_LoadArrangeLin873D0(int a, int b);                          /* 0x000873D0 */
void sub_0004F580_m1(const char *path, int arg);                    /* 0x0004F580 (a50.h types arg 1 as int) */
void sub_0004F6F0(void);
void m1_LoadRun53DC0(const char *name, int arg);                    /* 0x00053DC0 */
int sub_0007E070(char *buf, int size, const char *fmt, ...);        /* 0x0007E070 snprintf-like */
extern int32_t m1_worldA41316C, m1_worldB413170;                    /* 0x0041316C, 0x00413170 */
extern const char m1_fmtEvent2775D4[], m1_fmtTalk277604[], m1_fmtShop277634[];
extern void *m1_eventBms417868, *m1_talkBms41786C, *m1_shopBms417874;
int m1_LoadEventBmsE0010(void);                                     /* 0x000E0010 */
int m1_LoadTalkBmsE0070(void);                                      /* 0x000E0070 */
int m1_LoadShopBmsE00D0(void);                                      /* 0x000E00D0 */
void sub_000DFED0(void);
extern const char m1_fmtQuiz277660[], m1_fmtEventLgc277690[], m1_fmtRubber2776C0[], m1_fmtMb277744[];
extern void *m1_quizBms417870, *m1_eventLgc417864;                 /* 0x00417870, 0x00417864 */
extern int32_t m1_lgcState3F0734;                                   /* 0x003F0734 */
extern uint8_t *m1_rubber3F0748, *m1_rubberBody3F074C;              /* 0x003F0748, 0x003F074C */
extern const char *const m1_langTab317CF0[8];                       /* 0x00317CF0 (XBOX32 pointers) */
int m1_LoadQuizBmsE0150(void);                                      /* 0x000E0150 */
int m1_LoadEventLgcE05B0(void);                                     /* 0x000E05B0 */
int m1_LoadRubberE0700(void);                                       /* 0x000E0700 */
void *m1_LoadMbBmsE0DD0(int lang, int n);                           /* 0x000E0DD0 */
void *sub_001C7DB0(void *dst, const void *src, unsigned n);       /* 0x001C7DB0 CRT copy */
int  sub_00084CE0(const char *path);
void sub_0005EBB0(int i, const char *path);
typedef struct M1PigOwner { uint8_t unk00[0x44]; int32_t pigA; int32_t pigB; } M1PigOwner;
typedef struct M1PigDir { uint8_t unk00[8]; const char *dir; /* +8 (XBOX32) */ } M1PigDir;
extern const char m1_fmtPig25FBE8[];                                /* 0x0025FBE8 "%spig/%s.pig" */
extern const char m1_fmtShd26CDE4[], m1_fmtShd26CDC8[];             /* 0x0026CDE4, 0x0026CDC8 */
int  m1_LoadPigA1DBF0(M1PigOwner *o, const char *name, const M1PigDir *d);   /* 0x0001DBF0 */
int  m1_LoadPigB1DC70(M1PigOwner *o, const char *name, const M1PigDir *d);   /* 0x0001DC70 */
int  sub_00057660(int a, int b);
void sub_000340D0_m1(char *out, int id);    /* 0x000340D0 regargs: id=ESI */
int  sub_000364A0_m1(const char *path, int arg);  /* 0x000364A0 regargs: path=EAX */
extern const char m1_fmtDemoEff2614C8[];                            /* 0x002614C8 */
extern int32_t m1_flip3DF2F0;                                       /* 0x003DF2F0 */
extern uint8_t *m1_stage3DFA5C;                                     /* 0x003DFA5C */
extern const char *const m1_stageNames2C58C4[];                     /* 0x002C58C4 (XBOX32 pointers) */
int  m1_LoadById36660(int arg, int a, int b);                       /* 0x00036660 */
int  m1_LoadDemoEff366F0(int arg, int n);                           /* 0x000366F0 */
void m1_LoadStageFlip40E90(const char *fmt, int idx);               /* 0x00040E90 regargs: idx=EDX */
/* XDK library routines (stdcall), names left neutral. */
void OOG_STDCALL sub_001BD5DF(int a, void *info);
int  sub_001C7FDE(char *buf, const char *fmt, ...);                 /* CRT sprintf */
int  OOG_STDCALL sub_001BED78(const char *path);
int  OOG_STDCALL sub_001BE721(int a);
void OOG_STDCALL sub_001BE735(int h, const void *data, int size);
void OOG_STDCALL sub_001BE783(int h, uint32_t *digest);
extern char m1_saveRoot40C040[];                                    /* 0x0040C040 path buffer */
extern const char m1_fmtSS2780E0[], m1_strTitleMeta27B694[];        /* "%s%s", "TitleMeta.xbx" */
typedef struct M1SysInfo { int32_t a, b, c, d; uint8_t rest[0xBF0]; } M1SysInfo;
void m1_SysCall1A88D0(void);                                        /* 0x001A88D0 */
int  m1_TitleMetaExists1A9A30(void);                                /* 0x001A9A30 */
void sub_00053710(int heap);
void sub_00053740(void);
void sub_0001E9B0(void *scene, void *o, void *p, int a, int b);
typedef struct M1Node { uint8_t unk000[0x14C]; void *x14C; /* +0x14C (XBOX32) */ } M1Node;
extern void   *m1_figTmpl3DA0C0;                                    /* 0x003DA0C0 */
extern M1Node *m1_figNode3DA0B8;                                    /* 0x003DA0B8 */
extern void   *m1_scene42C8E4;                                      /* 0x0042C8E4 */
extern const char m1_fmtFigure261558[];                             /* 0x00261558 */
M1Node *m1_LoadFigure371A0(int n);                                  /* 0x000371A0 */
typedef struct M1Task { uint8_t unk00[0x1A]; uint8_t kind; /* +0x1A */ uint8_t unk1B[9]; } M1Task;  /* 0x24 bytes */
M1Task *sub_0008C350_m1(M1Task *n, const M1Task *ref, uint32_t mask);  /* 0x0008C350 */
M1Task *m1_FindKind8C3C0(M1Task *n, int kind);                      /* 0x0008C3C0 */
int   sub_0008BCD0(int heap);
void  sub_0007F4A0(int slot, int heap);
void *sub_0007F510(void *key, int *out);
typedef struct M1Res {
    uint8_t  unk00[0x18];
    uint16_t flags;     /* +0x18: 2 = loaded */
    uint8_t  unk1A[2];
    int32_t  n;         /* +0x1C */
    int8_t   kind;      /* +0x20 */
    int8_t   heap;      /* +0x21 */
    uint8_t  unk22[6];
    void    *data;      /* +0x28 (XBOX32) */
} M1Res;
int m1_LoadClpRes8E900(M1Res *r, M1DtObj *o);                       /* 0x0008E900 */
void sub_0007F540(void *slot, void *out);   /* 0x0007F540: *out = slot+0x10, then clears slot+0x10/+0x14 */
typedef struct M1ModelDesc { int32_t kind; uint8_t unk04[4]; const char *dir; /* +8 (XBOX32) */ void *data; /* +0xC (XBOX32) */ } M1ModelDesc;
void sub_0001D1E0(void *o, const char *name);
extern const char m1_fmtBmd25FBC8[], m1_fmtPod25FBD8[];             /* "%smodel/%s.bmd", "%smodel/%s.pod" */
char *sub_001C80F6(char *s, const char *sep);                       /* 0x001C80F6 CRT strtok */
extern const char m1_strSlash26B81C[], m1_strEmpty26B818[];         /* "/", "" */
void m1_SplitPath4F810(const char *src, char *first, char *rest);   /* 0x0004F810 regargs: first=ESI, rest=EDI */
typedef struct M1Stream { int32_t packed; const char *name; /* +4 (XBOX32) */ uint8_t unk08[0x18]; } M1Stream;  /* 0x20 */
extern M1Stream m1_streams2C8900[0x21E];                            /* 0x002C8900 (r1e: movies) */
extern const char m1_fmtStm26B828[], m1_fmtLz26B820[];             /* "%s.stm", "%s.lz" */
int  sub_001C9A37(const char *a, const char *b);                    /* 0x001C9A37 CRT string compare */
M1Stream *m1_FindStream4F8E0(const char *name);                     /* 0x0004F8E0 regargs: name=EDI */
int sub_0007DAF0(char *buf, int size, const char *fmt, void *ap);
int sub_0002E560(int a1, int a2, int a3, int a4, int a5, int a6, float sx, float sy, const char *text);
int m1_DrawTextf2E8C0(int a1, int a2, int a3, int a4, int a5, int a6, const char *fmt, ...);  /* 0x0002E8C0 */
extern int32_t *m1_pg2C4B08;                                        /* 0x002C4B08: [0] tag colour, [1] normal, [2] selected */
extern const char m1_strFmtBracket266FB0[];                         /* 0x00266FB0 "[%s]
" */
int m1_DrawTagf3E4B0(int a1, int a2, int a3, int a4, int a5, const char *fmt, ...);  /* 0x0003E4B0 */
extern const char m1_fmtItem266FC8[];                               /* 0x00266FC8 "%c%s 
" */
#endif
