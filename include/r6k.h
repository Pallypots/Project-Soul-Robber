#ifndef R6K_H
#define R6K_H
#include "oogie.h"
#include "shared_decls.h"
/* Area r6k: larger functions (300-2500 bytes) in 0x00060000..0x000D0000.
   All names inferred. Register mappings are in the comments and in
   config/function_states_r6k.csv. Callees are declared under their sub_ name
   (or an existing name with the same VA). */

/* Float to int truncation (copy of RFL_FTOI). */
#if defined(_MSC_VER) && defined(_M_IX86)
#include <xmmintrin.h>
#define R6K_FTOI(x) _mm_cvtt_ss2si(_mm_set_ss(x))
#else
#define R6K_FTOI(x) ((int)(x))
#endif

/* ------------------------------------------------------------ actors and room helpers */
/* Model record of an actor (0x150 bytes, pools at *0x003ED530; only
   touched fields). */
typedef struct R6kMdlInfo {
    uint8_t  unk00[0xBC];
    void   **meshBC;          /* +0xBC first entry is the mesh */
} R6kMdlInfo;
typedef struct R6kMdlAnim {
    uint8_t  unk00[8];
    int32_t  i08;             /* +0x08 */
} R6kMdlAnim;
typedef struct R6kModel {
    uint8_t  unk00[4];
    int32_t  kind04;          /* +0x004 */
    int32_t  type08;          /* +0x008 */
    uint32_t flags0C;         /* +0x00C bit 0 in use */
    int32_t  i10;             /* +0x010 */
    uint8_t  unk14[0x20 - 0x14];
    R6kMdlInfo *info20;       /* +0x020 */
    uint8_t  unk24[0x30 - 0x24];
    R6kMdlAnim *anim30;       /* +0x030 */
    uint8_t  unk34[0x40 - 0x34];
    float    pos40[4];        /* +0x040 */
    float    pos50[4];        /* +0x050 */
    float    pos60[4];        /* +0x060 */
    uint8_t  unk70[0x128 - 0x70];
    uint32_t flags128;        /* +0x128 hit bits */
    uint8_t  unk12C[0x14C - 0x12C];
    int32_t  id14C;           /* +0x14C */
} R6kModel;
/* Actor record (0x260 bytes each at 0x004242C0; layout of R6jActor). */
typedef struct R6kActor {
    uint32_t flags;           /* +0x000 bit 0 active, 0x800 motion done */
    int32_t  type04;          /* +0x004 */
    uint8_t  unk008[0x18 - 0x08];
    int32_t  kind18;          /* +0x018 index into the update table 0x002E40B0 */
    uint8_t  unk01C[0x40 - 0x1C];
    int32_t  step40;          /* +0x040 */
    uint8_t  unk044[0x48 - 0x44];
    int32_t  state48;         /* +0x048 */
    uint8_t  unk04C[0x70 - 0x4C];
    float    pos70[4];        /* +0x070 x, y, z, w */
    float    vec80[4];        /* +0x080 (+0x84 an angle) */
    float    vec90[4];        /* +0x090 */
    uint8_t  unk0A0[0x120 - 0xA0];
    R6kModel *model120;       /* +0x120 */
    uint8_t  unk124[0x128 - 0x124];
    int32_t  i128;            /* +0x128 */
    uint8_t  unk12C[0x15C - 0x12C];
    float    local15C[8][4];  /* +0x15C points relative to the actor */
    float    world1DC[8][4];  /* +0x1DC the same points in the world */
    int32_t  id25C;           /* +0x25C */
} R6kActor;
extern R6kActor aa0_slots[32];            /* 0x004242C0 actor records */
void  sub_00053710(int heap);
void  sub_00053740(void);

int   sub_000D9A70(int bit);              /* event flag bit test */
void  sub_000D9AB0(int bit);              /* set event flag */
void  sub_000D9B30(int bit);              /* clear event flag */
R6kActor *sub_000A4290(int idx);          /* actor record idx of 0x004242C0 */
void  sub_000A42F0(int idx, int motion);
int   sub_000A4370(int idx);
void  sub_000A2CA0(int idx, uint32_t mask);
void  sub_000A2CC0(int idx, uint32_t mask);
void  sub_000A2D10(int idx, uint32_t mask);
void  sub_000A2D40(int idx, uint32_t mask);
int   sub_000A2CE0(int idx, uint32_t mask);
void  sub_000A4410(int id, int on);
extern uint8_t ae0_obj3E1270[];           /* 0x003E1270 camera object */
void  sub_00019000(void *cam, int mode);
void  sub_0001AB00(void *cam, int a, int b, int c, int d);
void  sub_0019BE90(int id);
void  sub_0019BEB0(int id);
void  sub_000D1930(PlayerStats *p);
void  sub_000A43C0(int idx, int v);
void  sub_000A5450(int idx);
void  sub_000DFD40(int32_t *chapter, int32_t *stage);
int   sub_00036D40(void);                 /* fade running */
extern float a50_framesPerSecond;         /* 0x0042C964 */

/* ------------------------------------------------------------ demo task list loader (0x8B9E0) */
/* Kind descriptor records (0x24 bytes; +0x08 = stored size of the kind). */
typedef struct R6kDesc {
    uint8_t  unk00[8];
    int32_t  size;            /* +0x08 */
    uint8_t  unk0C[0x24 - 0x0C];
} R6kDesc;
typedef R6kDesc *(*R6kDescGetter)(void);
extern R6kDescGetter a8b_descGetters[8];  /* 0x002E0D68 per kind */
/* Serialized task record header (copied into the task work block). */
typedef struct R6kRec {
    uint8_t  unk00[4];
    int8_t   kind;            /* +0x04 -1 ends the list */
    int8_t   sub;             /* +0x05 */
    uint8_t  unk06[2];
    int32_t  link;            /* +0x08 index of the linked node, -1 none */
    uint8_t  unk0C[4];
    union { uint32_t u; uint8_t b[4]; } bits; /* +0x10 */
} R6kRec;
typedef struct R6kTask {
    uint8_t  unk00[0x1C];
    R6kRec  *work;            /* +0x1C */
} R6kTask;
R6kTask *sub_0008B980(int kind, int sub);
void    *a6b_Node_Nth(void *list, int n);           /* 0x0007F390 */
void     a8b_SetLink(R6kRec *w, void *node);        /* 0x0008B3B0 */
R6kTask *a6b_Node_First(R6kTask *n);                /* 0x0007F330 */
void     r6f_TaskFreeChain(R6kTask *n);             /* 0x0008B400 */

/* ------------------------------------------------------------ new game reset (0x77EF0) */
extern int32_t a9b_g413164, a9b_g413168;  /* 0x00413164, 0x00413168 */
extern int32_t a19_g413174;               /* 0x00413174 */
extern float   r6k_f41317C;               /* 0x0041317C */
void  sub_00049A40(int a, int b);
void  sub_00049AA0(int a);
void  sub_00049B00(int a);
void  r2b_ResetBits(void);                /* 0x000D9BF0 */

/* ------------------------------------------------------------ actor update loop (0xA4F50) */
typedef struct R6kScene {
    uint8_t  unk00[0x44];
    void    *list44;          /* +0x44 passed to 0x000847F0 */
} R6kScene;
extern R6kScene *r6k_scene42C8E4;         /* 0x0042C8E4 scene context */
typedef void (*R6kActorFn)(R6kActor *a);
extern R6kActorFn r6k_actorUpdate2E40B0[]; /* 0x002E40B0 per-kind update */
void  sub_00090560(R6kActor *a);
void  sub_000A3AE0(R6kActor *a);          /* regargs: a=ESI */
void  sub_000A3990(R6kActor *a);          /* regargs: a=EAX */
void  sub_000A2FB0(R6kActor *a, void *player);
int   sub_00082E50(void *pts, void *p);
void  sub_0001D700(void *o);
int   sub_000A0FD0(void *o);
void  sub_000A1020(void);

/* ------------------------------------------------------------ Jack action states (0xC0C90) */
/* Jack's character object (the same object as PlayerStats, 0x0041FEC0)
   seen with the action-state fields used here. */
typedef struct R6kJackAnim { uint8_t unk00[8]; int32_t i08; } R6kJackAnim;
typedef struct R6kJackNode {
    uint8_t  unk00[0x30];
    R6kJackAnim *anim30;      /* +0x30 */
    uint8_t  unk34[0x60 - 0x34];
    float    pos60[4];        /* +0x60 */
} R6kJackNode;
typedef struct R6kJack {
    uint8_t  unk000[0xD4];
    int32_t  unkD4;           /* +0x0D4 */
    uint8_t  unkD8[0xE0 - 0xD8];
    int32_t  subE0;           /* +0x0E0 step inside the action */
    uint8_t  unkE4[4];
    float    timerE8;         /* +0x0E8 seconds in the step */
    uint32_t modeEC;          /* +0x0EC */
    uint8_t  unkF0[0x110 - 0xF0];
    float    vel110[3];       /* +0x110 */
    uint8_t  unk11C[0x128 - 0x11C];
    int32_t  anim128;         /* +0x128 current animation, -1 none */
    int32_t  anim12C;         /* +0x12C requested animation */
    uint8_t  unk130[0x150 - 0x130];
    uint32_t flags150;        /* +0x150 */
    uint8_t  unk154[0x1C0 - 0x154];
    int32_t  f1C0;            /* +0x1C0 */
    uint8_t  unk1C4[0x1D8 - 0x1C4];
    int32_t  f1D8;            /* +0x1D8 */
    uint8_t  unk1DC[0x204 - 0x1DC];
    int32_t  f204;            /* +0x204 */
    uint8_t  unk208[0xD74 - 0x208];
    int32_t  fD74;            /* +0xD74 (PlayerStats slotsD6C[2]) */
    uint8_t  unkD78[0xFD8 - 0xD78];
    R6kJackNode *nodeFD8;     /* +0xFD8 model node (g_playerObj) */
} R6kJack;
void  sub_000CB990(R6kJack *j, float t);

/* ------------------------------------------------------------ trigger zones (0x877E0) */
typedef struct R6kZone {
    int32_t  id;              /* +0x00 0 = unused */
    float    box[7];          /* +0x04 */
} R6kZone;
typedef struct R6kZoneList {
    uint8_t  unk00[4];
    int32_t  count;           /* +0x04 */
    uint8_t  unk08[8];
    R6kZone  zones[1];        /* +0x10 count entries */
} R6kZoneList;
typedef struct R6kNode374 { uint8_t unk000[0x374]; float y374; } R6kNode374;
typedef struct R6kPlayerInfo { uint8_t unk00[0xC4]; R6kNode374 *nodeC4; } R6kPlayerInfo;
typedef struct R6kPlayerMdl {
    uint8_t  unk00[0x20];
    R6kPlayerInfo *info20;    /* +0x20 */
    uint8_t  unk24[0x60 - 0x24];
    float    pos60[4];        /* +0x60 */
} R6kPlayerMdl;
extern R6kPlayerMdl *r6k_player420E98;    /* 0x00420E98 (g_playerObj) */
extern R6kZoneList *r6c_v3ED248;          /* 0x003ED248 zone list */
extern int32_t  r6c_v3ED234;              /* 0x003ED234 current zone index, -1 none */
extern R6kZone *r6c_v3ED240;              /* 0x003ED240 current zone */
extern int32_t  r6c_v3ED238;              /* 0x003ED238 */
extern int32_t  r6c_v3ED23C;              /* 0x003ED23C forced zone id, -1 none */
extern int32_t  r6c_state3ED21C;          /* 0x003ED21C */
extern float    r6c_target3ED224[4];      /* 0x003ED224 last tested position */
int   sub_00086C30(void);
int   sub_00087AE0(void);
int   sub_000875E0(R6kZone *z, float *pos, float *last); /* regargs: z=ESI pos=EDI last=EBX */
float sub_001B2730(const float *a, const float *b);
int   sub_00085390(int a);

/* ------------------------------------------------------------ gimmick actors (0x92490) */
extern float a50_frameUnits;              /* 0x0042C858 frame time in 1/60 s units */
extern int32_t a30_g41316C, a30_g413170;  /* 0x0041316C, 0x00413170 */
void  sub_000A41D0(R6kActor *a, int v);
void  sub_000A4740(R6kActor *a, int v);
void  sub_000C56B0(R6kModel *m);
void  sub_000A35B0(float *angle);
R6kModel *sub_000A42A0(int idx);          /* model of actor record idx (+0x120) */
int   sub_000A2630(R6kActor *a, R6kModel *m, const float *v);

/* ------------------------------------------------------------ Jack action states (0xBE260) */
void  sub_00019370(int mode, float t);
void  sub_000193C0(void);
void  sub_000CFF90(R6kJack *j, int a, float t);
void  sub_000D0200(R6kJack *j, int a, int id);
void  sub_000C53B0(R6kJack *j);
void  sub_000D0530(R6kJack *j, int a, int b);
void  sub_000D0560(R6kJack *j, int a, int b);
void  sub_000CA600(R6kJack *j);
void  sub_000D5620(int a);
void  sub_000CEE40(int a, int b);
int   sub_000D08F0(R6kJack *j, int a);
void  sub_000C5930(R6kJack *j);
void  sub_000BC5D0(void);
void  sub_000BC5F0(void *sm);
void  sub_000D2CC0(R6kJack *j, int a);
void  sub_000AA2E0(int id);
extern uint8_t r6e_obj420EC0[];           /* 0x00420EC0 action input state machine (g_stats + 0x1000) */

/* @@APPEND@@ */

#endif
