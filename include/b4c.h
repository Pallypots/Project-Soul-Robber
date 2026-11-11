#ifndef B4C_H
#define B4C_H
#include "oogie.h"

/* Area b4c (0x00140000-0x0016FFFF, third pass): small actor state handlers
 * of the second actor state machine and level sound/task helpers.
 * Names inferred. */

/* Per-actor work block at actor+0x74 (Hypothesis). */
typedef struct B4cWork {
    uint32_t flags;            /* +0x00 */
    uint32_t w04, w08;         /* +0x04 */
    float    v0C[4];           /* +0x0C (+0x10 also read as a word) */
    uint8_t  unk1C[0x34 - 0x1C];
    float    f34;              /* +0x34 */
    float    f38;              /* +0x38 */
    int32_t  i3C;              /* +0x3C */
    int32_t  i40;              /* +0x40 */
    uint8_t  unk44[0x4C - 0x44];
    void    *obj4C;            /* +0x4C */
} B4cWork;

typedef struct B4cModel {
    uint8_t  unk00[0x30];
    void    *anim;             /* +0x30 */
    uint8_t  unk34[0x50 - 0x34];
    float    f50;              /* +0x50 */
    int32_t  i54;              /* +0x54 */
} B4cModel;

typedef struct B4cAct {
    uint8_t  unk00[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t  unk50[0x5C - 0x50];
    float    timer;            /* +0x5C */
    uint8_t  unk60[0x74 - 0x60];
    B4cWork *work;             /* +0x74 */
} B4cAct;

int  b16_SetState(B4cModel *m, B4cAct *a, int state);   /* 0x001671D0 */
void sub_00167200(B4cModel *m, B4cAct *a, int anim);    /* play animation */
void sub_000EE6D0(B4cModel *m, int b);
int  sub_000833E0(void *anim);
void aab_Hide1D700(B4cModel *m);
void sub_00033A70(void *o);
void b4c_VecCopy(void *dst, const void *src);   /* 0x000F5D40 */
int  sub_001C7EE1(void);
extern float a50_frameUnits;            /* 0x0042C858 */
extern float a50_frameSeconds;          /* 0x0042C85C */
extern float b4c_vec31F400[4];          /* 0x0031F400 */
extern float b4c_vec31F420[4];          /* 0x0031F420 */

/* sound / command ids */
void sub_000ED600(int v);
void sub_000ED560(int v);
int  sub_0004F6D0(int id);
void sub_0004F5D0(int id);
typedef struct B4cSnd { int32_t id; void *p04; void *p08; } B4cSnd;   /* 12 bytes */
extern B4cSnd b4c_sndTab279924[4];      /* 0x00279924 */
typedef struct B4cTask { uint8_t unk00[8]; int32_t id; } B4cTask;
extern B4cTask *b16_task3F92E8; extern int32_t b16_taskId3F92EC;
void sub_00020170(B4cTask *t);

/* objects with a handler block from 0x0001D960 */
typedef struct B4cObj B4cObj;
typedef struct B4cHandler {
    uint8_t unk00[0xB4];
    int  (*fnB4)(B4cObj *o, struct B4cHandler *h);           /* +0xB4 */
    uint8_t unkB8[4];
    int  (*fnBC)(B4cObj *o, struct B4cHandler *h, int arg);  /* +0xBC */
    uint8_t unkC0[0xD0 - 0xC0];
    void (*fnD0)(B4cObj *o, struct B4cHandler *h);           /* +0xD0 */
} B4cHandler;
struct B4cObj { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x150 - 0x10]; };  /* 0x150 bytes */
B4cHandler *sub_0001D960(B4cObj *o, int type);
void sub_0001EB80(B4cObj *o);
int  sub_000EE5F0(B4cObj *o);
void sub_00025D50(int a, int b);
extern B4cObj *b4c_objs3F840C;          /* 0x003F840C, 16 records */
/* ---- enemies (state switch 0x00113040 / set-state 0x00113090) */
typedef struct B4cEWork {
    uint8_t  unk00[4];
    uint32_t flags04;          /* +0x04 */
    uint8_t  unk08[0x18 - 0x08];
    float    f18;              /* +0x18 */
    float    f1C;              /* +0x1C */
    void    *res20;            /* +0x20 */
    uint8_t  unk24[0x3C - 0x24];
    void    *obj3C;            /* +0x3C */
} B4cEWork;
typedef struct B4cEnemy {
    uint8_t  unk000[0x20];
    uint32_t w20;              /* +0x20 bit 0 */
    uint8_t  unk024[0x4C - 0x24];
    uint32_t flags4C;          /* +0x4C */
    uint8_t  unk050[0x58 - 0x50];
    int32_t  i58;              /* +0x58 */
    uint8_t  unk05C[0x64 - 0x5C];
    int32_t  i64;              /* +0x64 */
    uint8_t  unk068[0x6C - 0x68];
    int32_t  fx6C;             /* +0x6C */
    void    *i70;              /* +0x70 attached handle (0x00036750) */
    float    f74;              /* +0x74 */
    uint8_t  unk078[0xF8 - 0x78];
    int32_t  iF8;              /* +0xF8 */
    float    distFC;           /* +0xFC */
    float    f100;             /* +0x100 */
    void      *target104;      /* +0x104 (g_playerObj, Jack's model node) */
    uint8_t  unk108[0x270 - 0x108];
    float    maxHp270;         /* +0x270 */
    float    hp274;            /* +0x274 */
    B4cEWork *work;            /* +0x278 */
} B4cEnemy;
#define B4C_SIDE(e) (((const uint8_t *)(e))[0x22] & 1)
typedef struct B4cOwner {
    uint8_t  unk00[0x0C];
    uint32_t flagsC;           /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x20 - 0x14];
    uint8_t *model20;          /* +0x20 (+0x30 = position) */
    uint8_t  unk24[0x30 - 0x24];
    void    *anim30;           /* +0x30 */
} B4cOwner;
typedef struct B4cTimer { int32_t on; uint8_t unk04[0x0C]; float f10, f14, f18, f1C; } B4cTimer;
void sub_00113090(B4cOwner *o, B4cEnemy *e, int state);
int  sub_00113040(B4cOwner *o, B4cEnemy *e, int state);
B4cTimer *sub_00113430(B4cEnemy *e, int slot);
float sub_001A3F30(float v);
float sub_001135C0(B4cOwner *o, B4cEnemy *e);
float sub_00113570(B4cOwner *o, B4cEnemy *e);
int  sub_001401C0(void);
int  aab_Effect494D0(int id, void *pos, int c);
void sub_0013B960(B4cOwner *o, B4cEnemy *e);
extern float b10_f3F7504;               /* 0x003F7504 */
B4cTimer *sub_001133E0(B4cEnemy *e, int slot);
void sub_00113370(B4cEnemy *e, B4cTimer *t);
int  sub_00083450(void *anim, int id);
void sub_00048250(int h);
void b16_ClearBit0(void *o);            /* 0x001661B0 */
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *dst, const float *a, const void *b);
void sub_001ADA40(float *m, const void *src);
typedef struct B4cAnimState { uint8_t unk00[0xC4]; float rateC4; uint8_t unkC8[0xD8 - 0xC8]; float timeD8; } B4cAnimState;
typedef struct B4cMdl { uint8_t unk00[0x14]; B4cAnimState *anim14; } B4cMdl;
typedef struct B4cActor { uint8_t unk00[0x30]; B4cMdl *model30; } B4cActor;
/* Work block variant used by the 0x00146xxx enemy (Hypothesis). */
typedef struct B4cEWork2 {
    uint32_t flags;            /* +0x00 */
    uint8_t  unk04[0x40 - 0x04];
    float    v40[4];           /* +0x40 */
    uint32_t flags50;          /* +0x50 */
    uint8_t  unk54[4];
    int32_t  i58;              /* +0x58 */
    uint8_t  unk5C[0x64 - 0x5C];
    int32_t  i64;              /* +0x64 */
    uint8_t  unk68[4];
    int32_t  i6C;              /* +0x6C */
    uint8_t  unk70[0x78 - 0x70];
    int32_t  i78;              /* +0x78 */
    uint8_t  unk7C[4];
    int32_t  i80;              /* +0x80 */
} B4cEWork2;
typedef struct B4cArgs { uint8_t unk00[0x10]; int32_t p10, p14, p18; } B4cArgs;
int  b4c_Enter1456E0(B4cOwner *o, B4cEnemy *e, int s, int unused);
typedef struct B4cMotion {
    uint32_t flags;            /* +0x00 */
    uint8_t  unk04[0x0C - 0x04];
    float    fC, f10;          /* +0x0C */
    uint8_t  unk14[0x24 - 0x14];
    float    f24, f28, f2C, f30; /* +0x24 */
} B4cMotion;
void b4c_MotionSet156180(B4cMotion *m, float a, float b, float c, float t);
void sub_00155FB0(int a, int b, int c);
typedef struct B4cBody { uint8_t unk000[0x128]; uint8_t b128; } B4cBody;
void sub_000414A0(int n);
int  sub_00145940(B4cOwner *o, int a, int b, int c, int d);
void sub_001459D0(B4cOwner *o, int a, int b, int c);
#endif
