#ifndef M1_ENEMY_H
#define M1_ENEMY_H
/* Shared types for enemy AI in area m1 (the second enemy type's state routines, 0x15A000-0x166000).
   Declare these types here once; do not redeclare them per file. Field names are inferred from
   use unless a comment says otherwise; offsets are Verified against the disassembly. */
#include <stdint.h>

/* Body orientation: three rows of four floats; 0x1ADA60 rebuilds it from up and forward. */
typedef struct M1Basis {
    float side[4];          /* +0x00 */
    float up[4];            /* +0x10 */
    float fwd[4];           /* +0x20 */
} M1Basis;

/* World object (the body the AI drives, the player, a target). */
typedef struct M1Actor {
    uint8_t  unk000[4];
    int32_t  kind;          /* +0x04  0xD = throwable body (inferred) */
    uint8_t  unk008[4];
    uint32_t drawFlags;     /* +0x0C */
    uint32_t bodyFlags;     /* +0x10  bit 8 = dead body, bit 0x10 = airborne */
    uint8_t  unk014[0x20 - 0x14];
    M1Basis *basis;         /* +0x20 */
    uint8_t  unk024[0x30 - 0x24];
    void    *anim;          /* +0x30 */
    uint8_t  unk034[0x60 - 0x34];
    float    pos[3];        /* +0x60 */
    uint8_t  unk06C[0x128 - 0x6C];
    uint8_t  contact;       /* +0x128 bits 0x02-0x10 = touching something (0x18 = ground) */
    uint8_t  unk129[0x13C - 0x129];
    int32_t  loopSnd;       /* +0x13C */
} M1Actor;

/* One received hit, copied whole into the state block (0x30 bytes). */
typedef struct M1Hit {
    int32_t  kind;          /* +0x00 */
    uint8_t  unk04[8];
    float    damage;        /* +0x0C */
    uint8_t  unk10[0x20];
} M1Hit;

/* Movement/behaviour block of the SECOND enemy type (M1EnemyAi.st). The first enemy type uses a
   different layout at the same pointer (e.g. +0x50 is flags there, a timer here); give it its own
   struct rather than reusing this one. */
typedef struct M1Enemy2State {
    uint32_t moveFlags;     /* +0x00 */
    float    moveSpeed;     /* +0x04 */
    float    turnSpeed;     /* +0x08 */
    float    fall;          /* +0x0C */
    float    f10;           /* +0x10 */
    uint8_t  unk14[0x24 - 0x14];
    float    vel[3];        /* +0x24 x, y, z */
    float    velScale;      /* +0x30 */
    uint8_t  unk34[0x38 - 0x34];
    void    *helper;        /* +0x38 */
    uint8_t  unk3C[4];
    uint32_t flags;         /* +0x40  M1ES_* */
    uint32_t hits;          /* +0x44  hits taken in the current combo */
    float    dashSpeed;     /* +0x48 */
    uint8_t  unk4C[0x50 - 0x4C];
    float    downTimer;     /* +0x50  0..900 */
    float    landDist;      /* +0x54 */
    uint8_t  unk58[0x74 - 0x58];
    float    launchPos[3];  /* +0x74 */
    uint8_t  unk80[0xD8 - 0x80];
    float    stepTimer;     /* +0xD8 */
    uint8_t  unkDC[0x1B8 - 0xDC];
    M1Hit    lastHit;       /* +0x1B8 */
} M1Enemy2State;

#define M1ES_ANGRY        0x00004u  /* armed for an angry dash */
#define M1ES_DEAD         0x00010u
#define M1ES_GRABBED      0x00020u
#define M1ES_HELPER_CUE   0x01000u
#define M1ES_PENDING_DROP 0x04000u
#define M1ES_ANGRY_READY  0x20000u

/* Enemy AI controller (the second argument of every state routine). */
typedef struct M1EnemyAi {
    uint8_t  unk000[0x20];
    union {                 /* +0x20  bit 1 and bit 0x10000 pick reactions (meaning unknown) */
        uint32_t aiFlags;
        uint8_t  aiFlagByte[4];   /* some routines test one byte (aiFlagByte[2] & 1 == bit 0x10000) */
    };
    uint8_t  unk024[0x4C - 0x24];
    uint32_t ctlFlags;      /* +0x4C */
    uint8_t  unk050[0x58 - 0x50];
    int32_t  phase;         /* +0x58 */
    uint8_t  unk05C[0x64 - 0x5C];
    int32_t  animId;        /* +0x64 */
    uint8_t  unk068[0x6C - 0x68];
    int32_t  voice;         /* +0x6C  sound handle, -1 = none */
    void    *fx;            /* +0x70 */
    float    timer;         /* +0x74 */
    uint8_t  unk078[0xF8 - 0x78];
    int32_t  targetKind;    /* +0xF8 */
    uint8_t  unk0FC[0x104 - 0xFC];
    M1Actor *target;        /* +0x104 */
    uint8_t  unk108[0x270 - 0x108];
    float    hpMax;         /* +0x270 */
    float    hp;            /* +0x274 */
    M1Enemy2State *st;       /* +0x278 */
} M1EnemyAi;

/* A spin/sway channel returned by 0x113400. */
typedef struct M1Spin {
    uint8_t  unk00[0x10];
    float    a, b, c, d;    /* +0x10 .. +0x1C */
} M1Spin;

extern float    m1_frameRate42C85C;
extern float    m1_frameTime42C858;
extern float    m1_gF3F7504;
extern uint8_t  m1_stats41FEC0[];
extern M1Actor *g_playerObj;

int   sub_000833E0(void *anim);                             /* animation finished */
int   sub_00156040(void);                                   /* regargs: stand-up trigger test */
void  m1_AiReset1134B0(M1EnemyAi *e);
void  sub_00113AA0(M1Actor *o, M1EnemyAi *e);
void  m1_SndStop048250(int h);
void  m1_ObjSnd05BE30(int h);
void  sub_00033A70(void *fx);
int   m1_AiGoto113040(M1Actor *o, M1EnemyAi *e, int st);
void  sub_00147FD0(void *helper, int k);
int   sub_001C7EE1(void);                                   /* rand */
int   sub_001550E0(void);                                   /* regargs: pick hit reaction */
int   sub_00146030(int kind);
void  sub_0015A270(M1Actor *o, int k);                      /* regargs: e=ESI; react with state k */
int   sub_00185420(M1Actor *o);
int   sub_000494D0(int id, const float *pos, int k);        /* start a 3D sound */
void  sub_00185540(M1Actor *o);
void  sub_000ED780(M1Actor *o);
void  sub_00036750(M1Actor *o, int k);
void  m1_AiSetState1456E0(M1Actor *o, M1EnemyAi *e, int st, int k);
int   sub_00145780(M1Actor *o, float r);
void  sub_00113190(M1Actor *o, M1EnemyAi *e, int k);
void  sub_00113480(M1EnemyAi *e, int k);
void  sub_00147710(M1EnemyAi *e, int k, float a, float b, float c, int d);   /* regargs: e=ECX k=EAX */
M1Spin *m1_Quest113400(M1EnemyAi *e, int k);
int   sub_000CF4F0(void *stats);                            /* current stage index */

/* Leave a down/stand-up state into state k: reset the controller, clear the knock-down
   flags, restore walking speeds, drop a pending item, stop the voice and effect. */
#define M1_STANDUP2_EXIT(k)                                  \
    s = e->st;                                               \
    m1_AiReset1134B0(e);                                     \
    o->drawFlags |= 0xE0;                                    \
    o->bodyFlags &= 0xFFFFFECAu;                             \
    e->ctlFlags &= ~0x100u;                                  \
    f = s->flags & 0xFFFBF579u;                              \
    s->moveFlags &= ~0x17u;                                  \
    s->flags = f;                                            \
    s->moveSpeed = -10.0f;                                   \
    s->turnSpeed = m1_frameRate42C85C * 10.0f;               \
    if (f & M1ES_PENDING_DROP) {                             \
        sub_00113AA0(o, e);                                  \
        e->ctlFlags |= 0x200;                                \
        s->flags &= ~M1ES_PENDING_DROP;                      \
    }                                                        \
    if (e->voice != -1) {                                    \
        m1_SndStop048250(e->voice);                          \
        e->voice = -1;                                       \
    }                                                        \
    m1_ObjSnd05BE30(o->loopSnd);                             \
    if (e->fx) {                                             \
        sub_00033A70(e->fx);                                 \
        e->fx = 0;                                           \
    }                                                        \
    m1_AiGoto113040(o, e, k)

/* Same, but starts sound 0x10F at the body (if no voice is playing) instead of stopping it. */
#define M1_STANDUP2_EXIT_SND(k)                              \
    s = e->st;                                               \
    m1_AiReset1134B0(e);                                     \
    o->drawFlags |= 0xE0;                                    \
    o->bodyFlags &= 0xFFFFFECAu;                             \
    e->ctlFlags &= ~0x100u;                                  \
    f = s->flags & 0xFFFBF579u;                              \
    s->moveFlags &= ~0x17u;                                  \
    s->flags = f;                                            \
    s->moveSpeed = -10.0f;                                   \
    s->turnSpeed = m1_frameRate42C85C * 10.0f;               \
    if (f & M1ES_PENDING_DROP) {                             \
        sub_00113AA0(o, e);                                  \
        e->ctlFlags |= 0x200;                                \
        s->flags &= ~M1ES_PENDING_DROP;                      \
    }                                                        \
    if (e->voice == -1)                                      \
        e->voice = sub_000494D0(0x10F, o->pos, 1);           \
    m1_ObjSnd05BE30(o->loopSnd);                             \
    if (e->fx) {                                             \
        sub_00033A70(e->fx);                                 \
        e->fx = 0;                                           \
    }                                                        \
    m1_AiGoto113040(o, e, k)

/* Zero the movement velocity and set the default fall rate. */
#define M1_ZERO_SPEEDS(s)                                    \
    (s)->vel[2] = 0.0f;                                      \
    (s)->vel[1] = 0.0f;                                      \
    (s)->vel[0] = 0.0f;                                      \
    (s)->velScale = 1.0f;                                    \
    (s)->f10 = 0.0f;                                         \
    (s)->fall = m1_frameTime42C858 * 0.005f

#endif
