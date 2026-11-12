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
typedef struct M1DtObj { uint32_t x00; uint32_t id; } M1DtObj;
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
#endif
