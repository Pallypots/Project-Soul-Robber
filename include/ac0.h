/* Area ac0 (0x000C0000-0x000CFFFF): character/actor helpers. Names inferred. */
#ifndef AC0_H
#define AC0_H
#include "oogie.h"
#include "shared_decls.h"

/* Sub-object reached through Ac0Actor::linkEFC. */
typedef struct Ac0Link {
    uint8_t  unk00[0x0C];
    uint32_t flags;           /* +0x0C */
    uint8_t  flags10;         /* +0x10 */
    uint8_t  unk11[0xE8 - 0x11];
    float    fE8;             /* +0xE8 */
} Ac0Link;

/* Object with a 32-entry list at +0x58 (not the actor: the list overlaps
 * the actor's +0xD4 field). */
typedef struct Ac0ListObj {
    uint8_t  unk00[0x58];
    int32_t  count;           /* +0x58 */
    int32_t  items[32];       /* +0x5C */
} Ac0ListObj;

/* Jack's character object. Its layout family covers both PlayerObj and
 * PlayerStats in oogie.h (flags at +0xD60, stat3 at +0xD8C): Hypothesis that
 * they are one object. Only touched fields named. */
typedef struct Ac0Actor {
    uint8_t  unk000[0xD4];
    int32_t  kindD4;          /* +0x0D4 */
    int32_t  vD8;             /* +0x0D8 */
    uint8_t  unkDC2[4];
    int32_t  stateE0;         /* +0x0E0 */
    float    fE4;             /* +0x0E4 */
    float    fE8;             /* +0x0E8 */
    uint32_t flagsEC;         /* +0x0EC */
    float    fF0;             /* +0x0F0 */
    uint8_t  unkF4[0xFC - 0xF4];
    int32_t  argFC;           /* +0x0FC */
    uint8_t  unk100[0x10C - 0x100];
    float    f10C;            /* +0x10C */
    float    vel[3];          /* +0x110 */
    uint8_t  unk11C[0x12C - 0x11C];
    int32_t  anim12C;         /* +0x12C */
    uint8_t  unk130[0x150 - 0x130];
    uint32_t flags150;        /* +0x150 */
    uint8_t  unk154[0x16C - 0x154];
    int32_t  v16C;            /* +0x16C */
    uint8_t  unk170[0x178 - 0x170];
    int32_t  slots[3];        /* +0x178 */
    int32_t  curSlot;         /* +0x184 */
    int32_t  v188;            /* +0x188 */
    uint8_t  unk18C[4];
    int32_t  v190;            /* +0x190 */
    int32_t  v194;            /* +0x194 */
    float    vec198[4];       /* +0x198 */
    uint8_t  unk1A8[0x1B8 - 0x1A8];
    int32_t  mode1B8;         /* +0x1B8 */
    uint8_t  unk1BC[0x318 - 0x1BC];
    int32_t  cycCount;        /* +0x318 */
    int32_t  cycIndex;        /* +0x31C */
    int32_t  cycPrev;         /* +0x320 */
    int32_t  cycValue;        /* +0x324 */
    float    cycF[32];        /* +0x328 */
    int32_t  cycKind[32];     /* +0x3A8 */
    int32_t  cycVal[32];      /* +0x428 */
    int32_t  cyc4A8[32];      /* +0x4A8 */
    int32_t  cycOrder[32];    /* +0x528 */
    uint32_t flags5A8;        /* +0x5A8 */
    int32_t  v5AC;            /* +0x5AC */
    float    vec5B0[4];       /* +0x5B0 */
    float    vec5C0[4];       /* +0x5C0 */
    uint8_t  unk5D0[0x624 - 0x5D0];
    int32_t  listBCount;      /* +0x624 */
    int32_t  listB[32];       /* +0x628 */
    int32_t  listCCount;      /* +0x6A8 */
    uint8_t  unk6AC[0xCAC - 0x6AC];
    int32_t  listC[32];       /* +0xCAC */
    int32_t  vD2C;            /* +0xD2C */
    float    fD30;            /* +0xD30 */
    uint8_t  unkD34[0xD60 - 0xD34];
    uint32_t flagsD60;        /* +0xD60 */
    uint8_t  unkD64[0xD6C - 0xD64];
    int32_t  levD6C[4];       /* +0xD6C */
    int32_t  slotD7C[4];      /* +0xD7C */
    int32_t  stat3;           /* +0xD8C */
    uint8_t  unkD90[0xEF8 - 0xD90];
    int32_t  vEF8;            /* +0xEF8 */
    Ac0Link *linkEFC;         /* +0xEFC */
    uint8_t  unkF00[0xFA8 - 0xF00];
    int32_t  vFA8;            /* +0xFA8 */
    float    fFAC;            /* +0xFAC */
    uint8_t  unkFB0[0xFD8 - 0xFB0];
    uint8_t *subFD8;          /* +0xFD8 */
} Ac0Actor;

/* 0x0041CEC0: three 0x68-byte companion slots. */
typedef struct Ac0Slot {
    uint32_t flags;           /* +0x00 */
    uint8_t  unk04[0x64 - 4];
    Ac0Link *owner;           /* +0x64 */
} Ac0Slot;
extern Ac0Slot g_ac0_slots[3];          /* 0x0041CEC0 */

/* 0x004242C0: 32 0x260-byte entity records. */
typedef struct Ac0Entity {
    int8_t   flags;           /* +0x000, bit 7 = live */
    uint8_t  unk001[0x120 - 1];
    int32_t  handle;          /* +0x120 */
    uint8_t  unk124[0x260 - 0x124];
} Ac0Entity;
extern Ac0Entity g_ac0_entities[32];    /* 0x004242C0 */

typedef struct Ac0Rec41E2A0 { uint8_t b[0xE0]; } Ac0Rec41E2A0;
extern Ac0Rec41E2A0 g_ac0_41E2A0[32];   /* 0x0041E2A0 */
extern void   *g_ac0_handles[8];        /* 0x0041FEA0 */

extern const int32_t g_ac0_soundTable[];  /* 0x002E7140 */
extern const int32_t g_ac0_effectTable[]; /* 0x002E71F0 */
extern int32_t g_ac0_41CD50, g_ac0_41CDAC, g_ac0_41CE08, g_ac0_41CE64;
extern float   g_ac0_418B30[3];         /* 0x00418B30 */
extern float   g_ac0_420EB0;            /* 0x00420EB0 */
extern int32_t g_ac0_4201D8, g_ac0_4201DC;
extern int32_t g_ac0_4203E8[], g_ac0_420268[], g_ac0_4202E8[];
extern float   g_ac0_41FEE4[4];         /* 0x0041FEE4 */

void  sub_000AA2E0(int id);
int   sub_00033AD0(void *h);
void  sub_00033AC0(void *h);
void  sub_000C4B70(void *rec);
void  sub_000C7CC0(int a);
float sub_00171B40(Ac0Actor *a);
void  ac0_VecCopy(void *dst, const void *src);  /* 0x000F5D40 */
void *sub_000EDB10(int a);
void *sub_000EDB90(void);
void  sub_000CB390(Ac0Actor *a, void *e);
void  sub_000CCA40(Ac0Actor *a, int b);
int   sub_000CD180(Ac0Actor *a, int i);

/* 0x0041D020: 20 0xEC-byte transform records. */
typedef struct Ac0Xform {
    int32_t  i00;             /* +0x00 */
    float    f04, f08, f0C;   /* +0x04 */
    int32_t  i10;             /* +0x10 */
    float    f14, f18, f1C;   /* +0x14 */
    float    f20;             /* +0x20 */
    float    f24, f28, f2C;   /* +0x24 */
    float    f30;             /* +0x30 */
    uint8_t  unk34[0xE8 - 0x34];
    int32_t  iE8;             /* +0xE8 */
} Ac0Xform;
extern Ac0Xform g_ac0_xforms[20];       /* 0x0041D020 */

extern uint8_t g_ac0_413144;            /* 0x00413144 */
extern uint32_t g_ac0_41CD28, g_ac0_42CA38;
extern uint8_t g_ac0_stickX, g_ac0_stickY;   /* 0x0042CA5E, 0x0042CA5F */
extern float   g_ac0_stickFX, g_ac0_stickFY; /* 0x00420EA0, 0x00420EA4 */
typedef struct Ac0SndEntry { int32_t level; int32_t a; int32_t b; } Ac0SndEntry;
extern const Ac0SndEntry g_ac0_sndEntries[];  /* 0x002E6F30 */

void  sub_000D0560(Ac0Actor *a, int anim, int c);
void  sub_00033AB0(void *h);
int   sub_000D0DC0(const float *pos, float r, void *dst40, void *dst30);   /* r2b_PoolGetA */
int   sub_000CCD60(int a, int b, int c);
int   sub_0019BE60(int k);
void  sub_000C72C0(void);
void  sub_000C7B00(void);
void  sub_000C93D0(void);

int   ac0_Slots_CountActive(Ac0Actor *unused);
void  ac0_Slots_Promote(Ac0Actor *a);
void  ac0_SetTarget(Ac0Actor *a, int v, const float *p, const float *q);
void  ac0_Handle_Start(int a, void *b);
void  ac0_Xforms_Reset(void);

#endif
