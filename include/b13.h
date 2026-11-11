#ifndef B13_H
#define B13_H
#include "oogie.h"
#include "shared_decls.h"

/* Area b13 (0x00130000-0x0015FFFF): enemy state handlers. Names inferred. */

/* Sub-object at enemy+0x278 (Hypothesis: per-enemy behaviour block). */
typedef struct B13Behav {
    uint8_t  unk00[4];
    uint32_t flags4;         /* +0x04 */
    uint32_t flags8;         /* +0x08 */
    uint8_t  unk0C[0x20 - 0x0C];
    void    *res20;          /* +0x20 */
    uint8_t  unk24[0x34 - 0x24];
    void    *res34;          /* +0x34 */
    void    *res38[2];       /* +0x38 */
} B13Behav;

/* Owner object passed first to the state handlers (Hypothesis: actor). */
typedef struct B13Owner {
    uint8_t  unk00[0x0C];
    uint32_t flagsC;         /* +0x0C */
    uint32_t flags10;        /* +0x10 */
    uint8_t  unk14[0x30 - 0x14];
    struct B13Model { uint8_t unk00[0x14]; void *handle14; } *model; /* +0x30 */
    uint8_t  unk34[0x54 - 0x34];
    float    f54;            /* +0x54 (Hypothesis: heading) */
} B13Owner;

/* Enemy component, second argument of the state handlers. */
typedef struct B13Enemy {
    uint8_t  unk000[0x22];
    uint8_t  side22;         /* +0x22 bit 0 selects a mirrored animation */
    uint8_t  unk023[0x4C - 0x23];
    uint32_t flags4C;        /* +0x4C */
    uint8_t  unk050[0x58 - 0x50];
    int32_t  counter58;      /* +0x58 */
    uint8_t  unk05C[0x68 - 0x5C];
    float    stateTime68;    /* +0x68 */
    int32_t  sound6C;        /* +0x6C -1 none */
    void    *effect70;       /* +0x70 0 none */
    float    f74;            /* +0x74 */
    uint8_t  unk078[0xF8 - 0x78];
    int32_t  hasTarget;      /* +0xF8 */
    float    fFC;            /* +0xFC */
    uint8_t  unk100[4];
    void    *target;         /* +0x104 */
    uint8_t  unk108[0x274 - 0x108];
    float    health;         /* +0x274 */
    B13Behav *behav;         /* +0x278 */
} B13Enemy;

typedef struct B13Timer { uint8_t unk00[0x10]; int32_t a; int32_t b; } B13Timer;

void      sub_00113480(B13Enemy *e, int slot);
void      sub_0018E7C0(void *p);
int       sub_0013A0A0(B13Owner *o, B13Enemy *e);
void      sub_00048250(int h);
void      sub_0001D700(void *o);
void      Grade_AddExclamations(int amount);
typedef struct B13FTimer { uint8_t unk00[0x10]; float t; } B13FTimer;
B13FTimer *sub_00113400(B13Enemy *e, int slot);
float     sub_00113200(B13Owner *o, void *target);
void      sub_00113A40(B13Owner *o, B13Enemy *e);
void      sub_0018E7F0(void *p, int arg);
extern float a50_frameUnits;     /* 0x0042C858 */
extern float a50_frameSeconds;   /* 0x0042C85C */
void      sub_0018E6C0(void *p, float v);
int       sub_0013A670(B13Owner *o, B13Enemy *e);
int       sub_0013A7B0(B13Owner *o, B13Enemy *e);
void     *sub_000EDC20(int kind, int start);
int       sub_0018E680(void *p);
void      sub_00189DE0(void *p, int arg);
void      b13_VecCopy(void *dst, const void *src);   /* 0x000F5D40 with two args */
int       sub_001C7EE1(void);
typedef struct B13Pair { uint8_t unk00[0x20]; uint8_t *p20; /* +0x20 */ uint8_t unk24[0x3C]; uint8_t v60[1]; /* +0x60 */ } B13Pair;
#endif
