#ifndef ABC_H
#define ABC_H
#include "oogie.h"
#include "shared_decls.h"
/* Area abc (0x000B0000..0x000C0000), third pass. All names inferred. */

/* State of an event message handler. */
typedef struct AbcEvt {
    uint32_t flags;  /* +0x00 bit 0 running */
    int32_t  step;   /* +0x04 */
    int32_t  count;  /* +0x08 frames since start */
} AbcEvt;
typedef struct AbcEvt2 {
    uint32_t flags;  /* +0x00 */
    int32_t  step;   /* +0x04 */
} AbcEvt2;

/* Slot record returned by 0x000A4290. */
typedef struct AbcSlot {
    uint8_t  unk000[0x48];
    int32_t  mode48;  /* +0x048 */
    uint8_t  unk04C[0x14C - 0x4C];
    void    *h14C;   /* +0x14C handle freed by 0x00033A70 */
    uint32_t unk150;
    int32_t  i154;   /* +0x154 id freed by 0x00048250, -1 none */
} AbcSlot;

/* Record returned by 0x000A9DA0. */
typedef struct AbcRec9DA0 {
    uint32_t unk00[2];
    int32_t  i08;    /* +0x08 */
} AbcRec9DA0;

/* Pose pair copied between parts (+0xBC, +0xC0). */
typedef struct AbcPart {
    uint8_t  unk00[0xBC];
    int32_t  poseBC;     /* +0xBC */
    int32_t  poseC0;     /* +0xC0 */
} AbcPart;
typedef struct AbcPartRec {
    uint8_t  unk00[0x20];
    AbcPart *part20;     /* +0x20 */
    uint8_t  unk24[0x150 - 0x24];
} AbcPartRec;            /* 0x150 bytes */
typedef struct AbcPartSet {
    uint8_t     unk00[8];
    AbcPartRec *recs;    /* +0x08 */
} AbcPartSet;
extern AbcPartSet *abc_partSet;   /* 0x00420E9C */
AbcPartRec *sub_0001D2D0(void *model, const void *id);

/* Ring queue of ints (0x000BC5F0..0x000BC6B0). */
typedef struct AbcQueue {
    int32_t  cap;    /* +0x00 */
    int32_t  head;   /* +0x04 read index */
    int32_t  tail;   /* +0x08 write index */
    int32_t  c0C;    /* +0x0C */
    int32_t *buf;    /* +0x10 */
} AbcQueue;

/* The player object at 0x0041FEC0 (g_stats in oogie.h), with the fields the
 * code near 0x000BC000..0x000BE000 touches. Hypothesis: the same type as
 * PlayerStats and PlayerObj (offsets +0xD4, +0x128.., +0x150, +0xD64 agree). */
typedef struct AbcPlayer {
    uint8_t  unk000[0x10];
    float    pos10[3];      /* +0x010 */
    uint8_t  unk01C[0x54 - 0x1C];
    float    v54[4];        /* +0x054 */
    uint8_t  unk064[0x7C - 0x64];
    void    *p7C;           /* +0x07C */
    uint8_t  unk080[0x90 - 0x80];
    float    v90[4];        /* +0x090 */
    uint8_t  unkA0[0xB8 - 0xA0];
    void    *pB8;           /* +0x0B8 */
    uint8_t  unkBC[0xD4 - 0xBC];
    int32_t  modeD4;        /* +0x0D4 */
    int32_t  stateD8;       /* +0x0D8 current state */
    int32_t  prevStateDC;   /* +0x0DC previous state */
    int32_t  stepE0;        /* +0x0E0 step within the state */
    float    fE4;           /* +0x0E4 */
    float    timeE8;        /* +0x0E8 */
    int32_t  iEC;           /* +0x0EC */
    float    fF0;           /* +0x0F0 */
    float    headingF4;     /* +0x0F4 */
    uint8_t  unkF8[0x108 - 0xF8];
    float    f108;          /* +0x108 */
    float    f10C;          /* +0x10C */
    float    vel110[3];     /* +0x110 velocity (Hypothesis) */
    uint8_t  unk11C[0x120 - 0x11C];
    int32_t  nonzero120;    /* +0x120 */
    uint8_t  unk124[0x128 - 0x124];
    uint32_t anim128;       /* +0x128 current animation */
    int32_t  anim12C;       /* +0x12C requested animation */
    float    timer130;      /* +0x130 */
    float    f134;          /* +0x134 */
    int32_t  i138;          /* +0x138 */
    uint8_t  unk13C[0x150 - 0x13C];
    uint32_t flags150;      /* +0x150 */
    uint8_t  unk154[0x1B8 - 0x154];
    int32_t  busy1B8;       /* +0x1B8 */
    int32_t  mode1BC;       /* +0x1BC */
    uint8_t  unk1C0[0xD64 - 0x1C0];
    int32_t  maxHealth;     /* +0xD64 */
    int32_t  health;        /* +0xD68 */
} AbcPlayer;

/* Jack's model object (g_playerObj, 0x00420E98) as used here. */
typedef struct AbcModel {
    uint8_t  unk00[0x30];
    void    *anim30;        /* +0x30 */
    uint8_t  unk34[0x60 - 0x34];
    uint8_t  sub60[0x30];   /* +0x60 */
    float    pos90[4];      /* +0x90 */
} AbcModel;

typedef struct AbcObjD4 {
    uint8_t unk00[0xD4];
    int32_t modeD4;  /* +0xD4 */
} AbcObjD4;

extern AbcPlayer abc_player;     /* 0x0041FEC0 */
extern AbcModel *abc_model;      /* 0x00420E98 */
extern uint32_t  abc_flags420010;/* 0x00420010 */
extern uint32_t  abc_flags418B40;/* 0x00418B40 */
extern uint8_t   abc_d418A80[];  /* 0x00418A80 */
extern void     *abc_p42C8E0;    /* 0x0042C8E0 */
extern float     abc_frameUnits; /* 0x0042C858 */
extern uint8_t abc_d2E5DE0[];    /* 0x002E5DE0 */
extern uint8_t abc_d2E5EEC[];    /* 0x002E5EEC */
extern char abc_s276D28[], abc_s276CFC[], abc_s276CD0[], abc_s276CA4[], abc_s276C78[];

void  sub_0001D720(void *o);
void  sub_0001D7A0(void *o);
void  sub_00019370(int mode, float t);
void  sub_000193C0(void);
float sub_00082A90(float y, float x);
void  sub_000D24A0(AbcPlayer *s);
void  sub_000BCA60(int a);
void  abc_Vec3Copy(float *dst, const float *src);   /* 0x000F5D40 */
void  sub_00053710(int heap);
void  sub_00053740(void);
void  sub_0004F700(int id);
void  sub_0004F720(void);
void  sub_001BA8F0(void *o);
void  sub_000D0530(AbcPlayer *s, int a, int b);
void  sub_000D51E0(void *o);
void  sub_000D2F60(AbcPlayer *s);
void  sub_000D2D90(AbcPlayer *s);
void  sub_000D9A30(void *o, float a);
void  sub_000BC770(void);
void  abc_SetState(AbcPlayer *p, int state);   /* 0x000BD4D0 */
void  sub_00026280(int maxHealth, int health);
void  sub_000CA580(AbcPlayer *s);
void  sub_000CA600(AbcPlayer *s);
void  sub_000D5620(int a);
void  sub_000CEE40(int a, int b);
int   abc_TimerDone(AbcPlayer *p);          /* 0x000CF070 */
int   abc_IsActive(AbcPlayer *p);           /* 0x000CF1A0 */

int   sub_000D9A70(int ev);
void  sub_000A4410(int slot, int on);
void  sub_000A43C0(int slot, int fx);
void  sub_000A42F0(int slot, int a);
void  sub_000A5450(int a);
void  sub_000A2CA0(int slot, uint32_t f);
void  sub_000A2CC0(int slot, uint32_t f);
void  sub_000A2D10(int slot, uint32_t f);
void  sub_000A2D40(int slot, uint32_t f);
void  sub_000A3620(int slot, int a);
void  sub_000A2E10(int slot, int a);
AbcSlot *sub_000A4290(int slot);
void  sub_00048250(int id);
void  sub_000B1EF0(void);
void  sub_000A2D70(int slot, int a);
void  sub_000A3690(int slot, int a);
void  sub_000A3480(int slot, int a, int b);
void  sub_000D9B30(int ev);
AbcRec9DA0 *sub_000A9DA0(int i);
int   sub_000A4370(int slot);
void *abc_PlayerD0030(AbcPlayer *p, int a);   /* 0x000D0030 */

#endif
