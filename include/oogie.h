/* Shared declarations for recovered game code.
 * Reference build OOGIE-XBOX-US-RETAIL. All names are INFERRED (ours, not the
 * developer's). The VA of every global and external function is listed in
 * config/symbols.csv, which the checker (tools/xcompare.py) uses to confirm
 * that recovered code touches the same addresses as the original.
 * Functions named sub_XXXXXXXX are not analysed yet. */
#ifndef OOGIE_H
#define OOGIE_H
#include <stdint.h>

#ifdef _MSC_VER
#define OOG_STDCALL __stdcall
#define OOG_IMPORT  __declspec(dllimport)
#else
#define OOG_STDCALL
#define OOG_IMPORT
#endif

/* ------------------------------------------------------------ grading */
/* 0x00413180: the current chapter's grading block (24 bytes). Also the
 * layout of each per-chapter record at 0x00413198 + 24*chapter. */
typedef struct GradeBlock {
    float   time;        /* +0x00 chapter time, seconds (from the chapter clock) */
    int32_t bestCombo;   /* +0x04 */
    int32_t damage;      /* +0x08 damage taken, 0..999 */
    int32_t exclaim;     /* +0x0C exclamation points, 0..999 */
    int8_t  rank[4];     /* +0x10 per-category rank: time, combo, damage, exclaim */
    int32_t grade;       /* +0x14 overall grade 0..4; -1 in a record = never played */
} GradeBlock;

extern GradeBlock g_grade;                  /* 0x00413180 */
extern GradeBlock g_chapterRecords[25];     /* 0x00413198, index 1..24 used */

void Grade_AddBestCombo(int combo);         /* 0x00041480 */
void Grade_AddExclamations(int amount);     /* 0x000414A0 */
void Grade_AddDamage(int amount);           /* 0x000414F0 */
void Grade_CommitChapter(int chapter);      /* 0x00040C10, chapter passed in EAX in the original */

/* ------------------------------------------------------------ player stats */
/* 0x0041FEC0: player stats object. Only the fields reached by the accessor
 * functions are named; the rest is unanalysed. */
typedef struct PlayerStats {
    uint8_t unk000[0xD8];
    int32_t unkD8;            /* +0x0D8  (0x0041FF98) */
    uint8_t unkDC[0x1B8 - 0xDC];
    int32_t unk1B8;           /* +0x1B8  (0x00420078) */
    uint8_t unk1BC[0xD5C - 0x1BC];
    int32_t unkD5C;           /* +0xD5C  base of stat slots: stat i (4..6, 8..11) at +0xD5C + 4*i */
    uint32_t flags;           /* +0xD60  (0x00420C20) */
    int32_t maxHealth;        /* +0xD64  stat 0  (0x00420C24) */
    int32_t health;           /* +0xD68  stat 1  (0x00420C28) */
    uint8_t unkD6C[0xD8C - 0xD6C];
    int32_t stat3;            /* +0xD8C  stat 3 (read only through Stats_Get) */
    float   timerD90;         /* +0xD90  zeroed when flag bit 0 is set */
    float   timerD94;         /* +0xD94  zeroed when flag bit 1 is set (0x00420C54) */
    float   stat2;            /* +0xD98  stat 2, float, read truncated */
    uint8_t unkD9C[0xDA0 - 0xD9C];
    int32_t soulsLifetime;    /* +0xDA0  (0x00420C60) */
    int32_t soulsWallet;      /* +0xDA4  stat 12 (0x00420C64) */
    uint8_t unkDA8[0xEFC - 0xDA8];
    int32_t unkEFC;           /* +0xEFC  (0x00420DBC) */
} PlayerStats;

extern PlayerStats g_stats;                 /* 0x0041FEC0 */
extern uint8_t     g_cheatFlags;            /* 0x00413130, bit 0: health never below 1 */
extern uint32_t    g_eventFlagBits[];       /* 0x004133F0, bit (i - 13) set by Stats_Set */

int  Stats_Get(PlayerStats *s, int index);              /* 0x000CF790 */
int  Stats_Set(PlayerStats *s, int index, int value);   /* 0x000CF810 */
void Souls_AddLifetime(int amount);                     /* 0x000CF910 */
int  Souls_Spend(int amount);                           /* 0x000D1F40 */
int  Souls_GetLifetime(void);                           /* 0x000CF940 */
int  Stats_GetMax(int index);                           /* 0x000CF8E0 */
int  Player_TakeDamage(PlayerStats *s, int damage);     /* 0x000CF950 */
int  Stats_SetFlag2(PlayerStats *s);                    /* 0x000CF9C0 */
void Stats_UpdateFlag2(void);                           /* 0x000CF9F0 */
int  Stats_SetFlag1(PlayerStats *s);                    /* 0x000CFA20 */
uint32_t Stats_TestFlags(PlayerStats *s, uint32_t mask);/* 0x000CFA50 */
int  Stats_GetD8(void);                                 /* 0x000CF6A0 */
int  Stats_Get1B8(void);                                /* 0x000CF6B0 */
int  Stats_HasEFC(void);                                /* 0x000CF6C0 */
extern const int32_t g_statMaxTable[0x50];              /* 0x002E7AE0 */

/* ------------------------------------------------------------ player character object */
/* Object taken by the 0x000CF180-0x000CF4EB helpers (same original source
 * file as the stats code). Probably Jack's character object (pointer at
 * 0x00420E98): Hypothesis. Only touched fields are named. */
typedef struct PlayerObj {
    uint8_t  unk000[0xD4];
    int32_t  unkD4;           /* +0x0D4 */
    uint8_t  unkD8[0xEC - 0xD8];
    int32_t  modeEC;          /* +0x0EC  low byte tested with 0x33 */
    uint8_t  unkF0[0xFC - 0xF0];
    float    angleFC;         /* +0x0FC  an angle in radians (Hypothesis: facing) */
    uint8_t  unk100[0x108 - 0x100];
    float    angle108;        /* +0x108  reference angle */
    uint8_t  unk10C[0x130 - 0x10C];
    float    timer130;        /* +0x130  limit for timer134 */
    float    timer134;        /* +0x134 */
    uint8_t  unk138[0x150 - 0x138];
    uint32_t flags[2];        /* +0x150, +0x154: 64 flag bits */
    uint8_t  unk158[0xFD8 - 0x158];
    uint8_t *unkFD8;          /* +0xFD8  sub-object; +0x60 passed to 0x000F5D40 */
} PlayerObj;

int      PlayerObj_ModeSign(PlayerObj *p);                              /* 0x000CF180 */
int      PlayerObj_IsActive(PlayerObj *p);                              /* 0x000CF1A0 */
int      PlayerObj_IsIdle(PlayerObj *p);                                /* 0x000CF1D0 */
void     PlayerObj_SetFlags(PlayerObj *p, uint32_t lo, uint32_t hi);    /* 0x000CF3C0 */
void     PlayerObj_ClearFlags(PlayerObj *p, uint32_t lo, uint32_t hi);  /* 0x000CF3F0 */
uint32_t PlayerObj_TestFlags(PlayerObj *p, uint32_t mask, int high);    /* 0x000CF420 */
int      PlayerObj_ForwardFD8(PlayerObj *p);                            /* 0x000CF450 */
int      PlayerObj_Call1ADAF0(int a, int b);                            /* 0x000CF470 */
void     PlayerObj_ClearFlags22(PlayerObj *p);                          /* 0x000CF4E0 */
int      PlayerObj_TimerDone(PlayerObj *p);                             /* 0x000CF070 */
float    PlayerObj_AngleDelta(PlayerObj *p);                            /* 0x000CF120 */
void     Player_Refresh(void);                                          /* 0x000CF0D0 */
extern PlayerObj *g_playerObj;              /* 0x00420E98 */
extern uint8_t   *g_42C8EC;                 /* 0x0042C8EC, object with a pointer at +0x3B0 */

/* ------------------------------------------------------------ chapter unlocks */
extern const uint8_t g_chapterUnlockTable[25][8];   /* 0x002C5C30, stat ids - 13 */
void Grade_ApplyChapterUnlocks(int chapter);        /* 0x00040A50 */

/* ------------------------------------------------------------ session (same file as the clock) */
typedef struct SessionSlot {
    uint8_t b[4];             /* +0 cleared on reset */
    float   scale;            /* +4 reset to 1.0 */
    uint8_t unk08[0xF0 - 8];
} SessionSlot;
extern SessionSlot g_sessionSlots[2];       /* 0x003DE6B0, 0xF0 bytes each */
extern uint64_t g_playTicks;                /* 0x00402FB8, second 300 Hz counter (Hypothesis: total play time) */
extern int32_t  g_402FC0;                   /* 0x00402FC0 */
extern int32_t  g_402F9C, g_402FA0, g_402FA4, g_402FA8, g_402FC4, g_402780;
void  Clock_ResetChapter(void);             /* 0x0019C100 */
float Clock_GetPlayTime(void);              /* 0x0019C110 */
void  Clock_SetPlayTime(float seconds);     /* 0x0019C190 */
void  Clock_ResetPlayTime(void);            /* 0x0019C1E0 */
void  Clock_Set402FC0(int v);               /* 0x0019C1F0 */
void  Session_Reset(void);                  /* 0x0019C200 */
int   Session_Request(int value);           /* 0x0019C270 */

/* ------------------------------------------------------------ clock / video */
extern uint64_t g_chapterTicks;             /* 0x00402FB0, 300 ticks per second */
extern int32_t  g_videoRateMode;            /* 0x003E2544, 0 = 59.94 Hz timing (Hypothesis) */
int   Video_GetRateMode(void);              /* 0x000529E0 */
float Clock_GetChapterTime(void);           /* 0x0019C030 */
void  Clock_SetChapterTime(float seconds);  /* 0x0019C0B0 */

/* ------------------------------------------------------------ background job */
typedef void (*JobFunc)(void *arg);
typedef struct BackgroundJob {
    int32_t state;        /* +0x00 */
    void   *thread;       /* +0x04 */
    uint8_t unk08[0x10];
    JobFunc func;         /* +0x18 non-NULL while the job runs */
    void   *arg;          /* +0x1C */
} BackgroundJob;
extern BackgroundJob g_job;                 /* 0x003E3F64 */
JobFunc Job_IsRunning(void);                /* 0x00057E90 */

/* ------------------------------------------------------------ frame */
extern void *g_renderLock;                  /* 0x0040B0E0 */
extern void *g_presentEvent;                /* 0x0040B0E4 */
void Frame_Present(void);                   /* 0x001A7BA0 */

/* ------------------------------------------------------------ not analysed */
void sub_00024D30(int a, int b);            /* cdecl, 2 args; called with (2, -souls) */
void sub_00025FD0(int a, int b);            /* cdecl, 2 args; called with (1, 0x78) */
void sub_001A7940(void);
int  sub_000F5D40(void *a);                 /* tail-called with (obj->unkFD8 + 0x60) */
int  sub_001ADAF0(int a, int b, int c);     /* cdecl, 3 args; called as (a, a, b) */
int  sub_00171CD0(PlayerStats *s);          /* stat 0x17 maximum = result * 10 */
void sub_00023D80(int a, int b);            /* cdecl; called with (3, damage) */
void sub_000CEF00(void);                    /* Jack's death sequence */
void sub_000CA6C0(PlayerStats *s);
int  sub_001AEE50(void *obj, int b);
void sub_0001D610(void *obj);
void sub_000CE970(void);
void sub_000CEF60(void);
void sub_0019BA70(void);
void sub_00102FA0(void);
int  sub_0019FEE0(void);
int  sub_001A0CC0(void);
int  sub_000479F0(void);

/* ------------------------------------------------------------ XDK / kernel */
int      OOG_STDCALL D3DDevice_Swap(uint32_t flags);                        /* 0x001D6D20 */
OOG_IMPORT void OOG_STDCALL RtlEnterCriticalSection(void *cs);              /* thunk slot 0, ordinal 277 */
OOG_IMPORT void OOG_STDCALL RtlLeaveCriticalSection(void *cs);              /* thunk slot 1, ordinal 294 */
int      OOG_STDCALL SwitchToThread(void);                                  /* 0x001BD332 */
uint32_t OOG_STDCALL WaitForSingleObjectEx(void *h, uint32_t ms, int alertable); /* 0x001BD012 */

#endif
