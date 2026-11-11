#ifndef AAB_H
#define AAB_H
#include "oogie.h"
/* Area aab (0x000A0000..0x000C0000), second pass. All names inferred. */

/* Animation controller reached through actor +0x30 -> +0x14. */
typedef struct AabAnimCtl {
    uint8_t  unk00[0xBC];
    uint8_t  flagsBC;        /* +0xBC bit1 */
    uint8_t  unkBD[0xC8 - 0xBD];
    int32_t  busyC8;         /* +0xC8 */
} AabAnimCtl;
typedef struct AabAnimState {
    uint8_t     unk00[0x08];
    int32_t     cur08;       /* +0x08 */
    uint8_t     unk0C[0x14 - 0x0C];
    AabAnimCtl *ctl14;       /* +0x14 */
} AabAnimState;
/* Actor attached to a slot (+0x120). Only the fields used here. */
typedef struct AabActor {
    uint32_t      unk00;
    int32_t       a04;       /* +0x04 */
    int32_t       a08;       /* +0x08 */
    uint32_t      flags0C;   /* +0x0C */
    uint32_t      flags10;   /* +0x10 */
    uint8_t       unk14[0x30 - 0x14];
    AabAnimState *anim30;    /* +0x30 */
    uint8_t       unk34[0x3C - 0x34];
    void         *model3C;   /* +0x3C */
    uint8_t       unk40[0x50 - 0x40];
    float         vec50[4];  /* +0x50 */
    float         vec60[4];  /* +0x60 position (Hypothesis) */
} AabActor;

/* 0x004242C0: 32 records of 0x260 bytes (same table as aa0_slots). */
typedef struct AabSlot {
    uint32_t  flags;         /* +0x000 bit0 = active, bit29 hidden, bit30 done */
    int32_t   id;            /* +0x004 */
    uint8_t   unk008[0x0C - 0x08];
    float     f0C;           /* +0x00C */
    uint8_t   unk010[0x3C - 0x10];
    int32_t   state;         /* +0x03C */
    int32_t   timer;         /* +0x040 */
    uint8_t   unk044[0x48 - 0x44];
    int32_t   anim48;        /* +0x048 */
    uint8_t   unk04C[0x70 - 0x4C];
    float     vec70[4];      /* +0x070 */
    float     vec80[4];      /* +0x080 */
    uint8_t   unk090[0x100 - 0x90];
    float     f100[4];       /* +0x100 */
    int32_t   i110[4];       /* +0x110 [0] indexes aab_rec134 */
    AabActor *obj120;        /* +0x120 */
    uint8_t   unk124[0x14C - 0x124];
    void     *h14C[2];       /* +0x14C handles from 0x00036750 */
    int32_t   h154[2];       /* +0x154 handles released by 0x00048250, -1 = none */
    uint8_t   unk15C[0x260 - 0x15C];
} AabSlot;
extern AabSlot aab_slots[32];                 /* 0x004242C0 */

/* 0x00424040: 0x134-byte records indexed by slot +0x110. */
typedef struct AabRec134 {
    uint8_t unk00[0x54];
    float   f54;             /* +0x54 */
    float   f58;             /* +0x58 */
    uint8_t unk5C[0x134 - 0x5C];
} AabRec134;
extern AabRec134 aab_rec134[2];               /* 0x00424040 (count Hypothesis) */

/* 0x00420F20: 0xDC-byte records, flags first. */
typedef struct AabRecDC {
    uint32_t flags;
    uint8_t  unk04[0x1C - 4];
    int32_t  inUse1C;        /* +0x1C */
    uint8_t  unk20[0xDC - 0x20];
} AabRecDC;
extern AabRecDC aab_recDC[8];                 /* 0x00420F20 (count Hypothesis) */

/* 0x003ED748: pointer to 16-byte callback records; 0x003ED750 count. */
typedef struct AabCb16 {
    void  (*fn)(int msg, void *arg);
    int8_t  flag;            /* +0x04, its address is the callback argument */
    uint8_t unk5[11];
} AabCb16;
extern AabCb16 *aab_cbTable;                  /* 0x003ED748 */
extern int32_t  aab_cbCount;                  /* 0x003ED750 */

/* 0x003ED768: 10 records of 0x34 bytes. */
typedef struct AabRec34 {
    uint8_t  unk00[0x14];
    float    f14;            /* +0x14 */
    uint8_t  unk18[0x30 - 0x18];
    uint32_t flags30;        /* +0x30 */
} AabRec34;
extern AabRec34 aab_rec34[10];                /* 0x003ED768 */

/* Objects with a kind word dispatched through a handler table. */
typedef struct AabKindObj { uint32_t flags; int32_t kind; } AabKindObj;
typedef struct AabObj1C { uint8_t unk00[0x1C]; int32_t kind; } AabObj1C;
extern void (*aab_kindHandlers[])(AabKindObj *o);   /* 0x002E4258 */
extern void (*aab_obj1CHandlers[])(AabObj1C *o);    /* 0x002E40D8 */

typedef struct AabSfxSrc { uint8_t unk00[0x20]; int32_t ready20; } AabSfxSrc;
typedef struct AabSfxHolder { uint8_t unk00[0x134]; void *h134; } AabSfxHolder;
typedef struct AabSfxObj {
    uint8_t       unk00[0xD4];
    void         *hD4;       /* +0xD4 */
    AabSfxSrc    *srcD8;     /* +0xD8 */
} AabSfxObj;

extern uint32_t aab_flags420010;              /* 0x00420010 */
extern uint8_t *aab_player;                   /* 0x00420E98 */
extern uint8_t  aab_stats[];                  /* 0x0041FEC0 */
extern int32_t  aab_mode41316C;               /* 0x0041316C */
extern int32_t  aab_val413170;                /* 0x00413170 */
extern int32_t  aab_res3ED760;                /* 0x003ED760 */

void  aab_Vec4Copy(void *dst, const void *src);   /* 0x000F5D40 */
void *aab_Attach36750(void *o, int a);            /* 0x00036750 */
void  aab_Free33A40(void *h);                       /* 0x00033A40 */
void  aab_Free33A70(void *h);                       /* 0x00033A70 */
void  aab_Free33C20(void *h);                       /* 0x00033C20 */
void  aab_Release48250(int h);                    /* 0x00048250 */
void  aab_Vec1AD9F0(float *out, const float *a, const void *b); /* 0x001AD9F0 */
float aab_Use82D70(float *v);                     /* 0x00082D70 */
void  aab_Rec32A0(AabRec134 *r, float *pos, int a, int b); /* 0x000A32A0 */
int aab_Actor1F070(AabActor *o, int);                /* 0x0001F070 */
void  aab_Show1B3A0(AabActor *o);                 /* 0x0001B3A0 */
void  aab_Hide1B3F0(AabActor *o);                 /* 0x0001B3F0 */
void  aab_SetAnim832D0(AabAnimState *a, int anim);       /* 0x000832D0 */
void  aab_Model1D7F0(void *m, int anim, int c);          /* 0x0001D7F0 */
int   aab_Ctl1AEE50(AabAnimCtl *c, int b);               /* 0x001AEE50 */
void  aab_SlotA4050(AabSlot *s, int a, int b, int c);    /* 0x000A4050 */
void  aab_SlotA4870(AabSlot *s);                         /* 0x000A4870 */
void  aab_SlotA4DE0(AabSlot *s);                         /* 0x000A4DE0 */
int aab_StatD1E10(void *stats, int id, int n);         /* 0x000D1E10 */
int aab_Effect494D0(int id, void *pos, int c);         /* 0x000494D0 */
int   aab_Get324A0(int a);                               /* 0x000324A0 */
int   aab_Rand(void);                                    /* 0x001C7EE1 (CRT rand, Hypothesis) */
void  aab_Hide1D700(AabActor *o);                       /* 0x0001D700 */
void  aab_Show1D610(AabActor *o);                       /* 0x0001D610 */
int   aab_CountA81C0(void);                             /* 0x000A81C0 */
int   aab_FindA88B0(void *a, int b, const float *v);    /* 0x000A88B0 */
void  aab_TimerA94B0(void);                             /* 0x000A94B0 */
int   aab_StatGet(void *stats, int id);                 /* 0x000CF790 */
int   aab_StatMax(int kind);                            /* 0x000CF8E0 */
int aab_StatFlag2(void *stats);                       /* 0x000CF9C0 */
void  aab_Sound260C0(int a, int b, int c);              /* 0x000260C0 */
void  aab_Add261A0(int a, int n);                       /* 0x000261A0 */
void  aab_Add24D30(int a, int n);                       /* 0x00024D30 */
void  aab_SoulsAdd(int n);                              /* 0x000CF910 */
void  aab_ResetA9DC0(void);                             /* 0x000A9DC0 */
extern uint32_t aab_flags420EF8;              /* 0x00420EF8 */
extern float    aab_timer420EFC;              /* 0x00420EFC */
extern float    aab_frameUnits;               /* 0x0042C858 */
extern int32_t  aab_word3ED970, aab_word3ED974;   /* 0x003ED970, 0x003ED974 */
extern float    aab_vec3ED978[5];             /* 0x003ED978 */
extern uint8_t  aab_data2E4A48[];             /* 0x002E4A48 */
extern uint8_t  aab_data2E5700[];             /* 0x002E5700 */
/* Two-word state block driven by message handlers (0x000B7E90). */
typedef struct AabMsgState { uint32_t flags; int32_t step; } AabMsgState;
#endif
