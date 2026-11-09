#ifndef B10_H
#define B10_H
#include "oogie.h"
#include <string.h>

/* Object at *0x003F6128 (Hypothesis: a menu/HUD controller). */
typedef struct B10Ctl {
    uint8_t  unk000[0x8C];
    void    *res8C;          /* +0x8C  resource, waited on until loaded */
    uint8_t  unk090[0xA8 - 0x90];
    int16_t  wA8;            /* +0xA8 */
    uint8_t  unkAA[0xBC - 0xAA];
    int16_t  wBC;            /* +0xBC */
    uint8_t  unkBE[0x138 - 0xBE];
    int32_t  i138;           /* +0x138 -1 = none */
    uint8_t  unk13C[0x1C8 - 0x13C];
    int16_t  w1C8;           /* +0x1C8 */
} B10Ctl;

typedef struct B10Res { uint8_t unk00[0x30]; int32_t handle; /* +0x30 */ } B10Res;

typedef struct B10Entry { int32_t value; uint8_t unk04[0x50]; } B10Entry; /* 0x54 bytes */

/* Object at *0x003F6130 (Hypothesis: a second menu screen). */
typedef struct B10Scr {
    uint8_t  unk000[0x8C];
    B10Res  *res8C;          /* +0x8C */
    B10Res  *res90;          /* +0x90 */
    uint8_t  unk094[0xD8 - 0x94];
    B10Entry entries[1];     /* +0xD8, 0x54-byte records */
    uint8_t  unk12C[0x1A8 - 0x12C];
    int16_t  w1A8;           /* +0x1A8 */
    uint8_t  unk1AA[2];
    float    f1AC;           /* +0x1AC */
    uint8_t  unk1B0[0x1C0 - 0x1B0];
    int32_t  i1C0;           /* +0x1C0 */
    uint8_t  unk1C4[0x20C - 0x1C4];
    int32_t  i20C;           /* +0x20C */
    uint8_t  unk210[0x224 - 0x210];
    uint8_t  sub224[4];      /* +0x224 */
} B10Scr;

extern B10Ctl *b10_ctl;      /* 0x003F6128 */
extern void   *b10_res3F612C;/* 0x003F612C */
extern B10Scr *b10_scr;      /* 0x003F6130 */
extern void   *b10_obj3F6134, *b10_obj3F6138, *b10_obj3F6150, *b10_obj3F6160;

void  sub_000F3D10(void *a, void *b, int c);
int   sub_000F3B50(void *o);
void  sub_000F3CD0(void *o, void *p);
int   sub_000F30E0(int kind);
void *sub_00053AB0(int size, int a, int b);
void  sub_000F3B30(void *o, int v);
void  sub_000F3B00(void *o, int v);
void  sub_000F3F00(void *o, float v);
void *sub_000FC4D0(void);
void  sub_00184610(void);
int   sub_000F5D00(int a);
int   b10_VecOp2(int a, void *b);      /* 0x000F5D40 with two args */
void  sub_00053880(void *p);
void  sub_000832D0(int handle, int id);
void  sub_00101280(int id);

typedef struct B10Obj90 { uint8_t unk00[0x8C]; int32_t i8C; uint8_t unk90[4]; } B10Obj90; /* 0x90 bytes */
typedef struct B10Act {
    uint8_t unk000[0x54];  float f54;  /* +0x54 */
    uint8_t unk058[0xBC - 0x58]; float fBC; /* +0xBC */
    uint8_t unk0C0[0xD0 - 0xC0]; float fD0; /* +0xD0 */
} B10Act;
typedef struct B10Pawn { uint8_t unk000[0x50]; float f50; uint8_t unk054[0x128 - 0x54]; uint8_t b128; } B10Pawn;

/* ---- enemy component (0x00112xxx-0x00113xxx) */
typedef struct B10Node {
    int32_t kind;            /* +0x00 0 = free, 1 = used, 2 = locked (Hypothesis) */
    int32_t id;              /* +0x04 */
    uint8_t unk08[0x24 - 8];
    struct B10Node *next;    /* +0x24 */
} B10Node;

struct B10Enemy;
typedef int (*B10StateFn)(void *owner, struct B10Enemy *e);
typedef struct B10Enemy {
    uint8_t  unk000[0x20];
    uint32_t flags20;        /* +0x20 */
    void    *fn24;           /* +0x24 */
    void    *fn28;           /* +0x28 */
    void    *fn2C;           /* +0x2C */
    uint8_t  unk030[0x50 - 0x30];
    int32_t  state;          /* +0x50 */
    int32_t  prevState;      /* +0x54 */
    int32_t  stateTicks;     /* +0x58 */
    float    stateTime;      /* +0x5C */
    B10Node *nodes;          /* +0x60 list head */
    uint8_t  unk064[0x274 - 0x64];
    float    health;         /* +0x274 */
    uint8_t  unk278[0x28C - 0x278];
    B10StateFn *stateFns;    /* +0x28C */
} B10Enemy;

typedef struct B10Cmd { int32_t id; const char *name; void *fn; } B10Cmd;
extern B10Cmd b10_cmdTable[17];        /* 0x00279330 */
extern float  b10_f3F7504;             /* 0x003F7504 */
extern float  b10_frameDelta;          /* 0x0042C85C (Hypothesis) */

int      sub_0004F6D0(int id);
void     sub_0001D470(void *a, int b);
void     sub_0001D4B0(void *a, int b);
B10Node *sub_00113300(B10Enemy *e);
void     sub_00113370(B10Enemy *e, B10Node *n);
void     sub_000EE270(void *o);
int      sub_00113E00();
int      sub_00112970();
int      b10_SkelHit(void *o, int unused, int arg);
typedef struct B10Hit B10Hit;   /* component returned by 0x0001D960 */
struct B10Hit {
    uint8_t unk000[0x6C];
    int32_t mode6C;                              /* +0x6C current mode */
    uint8_t unk070[0x29C - 0x70];
    int (*onHit)(void *o, B10Hit *h, int arg);   /* +0x29C */
};
int     sub_000EE5F0(void *o);
B10Hit *sub_0001D960(void *o, int t);
void    sub_00025D50(int a, int b);
/* ---- actor checks 0x0011AE20-0x0012D2A0 */
typedef struct B10Info {
    uint8_t  unk00[4];
    uint32_t flags;          /* +0x04 */
    uint8_t  unk08[8];
    int32_t  i10;            /* +0x10 */
    uint8_t  unk14[4];
    int32_t  i18;            /* +0x18 */
    uint8_t  unk1C[0x7C - 0x1C];
    float    f7C;            /* +0x7C */
    uint8_t  unk80[0x8C - 0x80];
    float    f8C;            /* +0x8C */
} B10Info;
typedef struct B10Actor {
    uint8_t  unk000[0x30];
    int32_t  handle;         /* +0x30 */
    uint8_t  unk034[0x5C - 0x34];
    float    f5C;            /* +0x5C */
    uint8_t  unk060[0x278 - 0x60];
    B10Info *info;           /* +0x278 */
} B10Actor;
/* condition record: (+0x08 mask/lo, +0x0C mode/hi, +0x10, +0x14, +0x18) */
typedef struct B10Cond {
    uint8_t  unk00[8];
    uint32_t a;              /* +0x08 */
    uint32_t b;              /* +0x0C */
    int32_t  c;              /* +0x10 */
    int32_t  d;              /* +0x14 */
    int32_t  e;              /* +0x18 */
} B10Cond;
typedef struct B10CondF { uint8_t unk00[0x10]; float lo; float hi; } B10CondF;
extern int32_t b10_list31DBD4[];         /* 0x0031DBD4 */
int  sub_000833E0(int handle);
void sub_000ED780(void *o);
int  sub_00145940(void *a, int b, int c, int d, int e);
void sub_001459D0(void *a, int b, int c, int d);
void sub_001AD7C0(void *dst, void *a, void *b);
void sub_0013A380(void *o, int n, int32_t *list);
uint32_t sub_00135E10(void);
#endif
