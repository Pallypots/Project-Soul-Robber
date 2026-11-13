/* Area m1, file 45: enemy actor default state. Names inferred. */
#include <stdint.h>

typedef void (*M1CbE)(void);
typedef struct M1EnemyAct {
    uint8_t  unk000[0x4C];
    int32_t  f04C, f050, f054, f058;   /* +0x4C */
    float    f05C;             /* +0x5C */
    int32_t  f060_unused;
    int32_t  f064;             /* +0x64 */
    float    f068;             /* +0x68 */
    int32_t  snd06C;           /* +0x6C, -1 */
    int32_t  f070;             /* +0x70 */
    float    f074;             /* +0x74 */
    float    v078[4];          /* +0x78: 0, 0, 0, 1 */
    float    v088[4];          /* +0x88: 0, 0, 0, 1 */
    uint8_t  unk098[0xF8 - 0x98];
    int32_t  f0F8;             /* +0xF8 */
    float    f0FC, f100;       /* +0xFC */
    int32_t  f104;             /* +0x104 */
    uint8_t  unk108[0x270 - 0x108];
    float    f270, f274;       /* +0x270 */
    uint8_t  unk278[4];
    M1CbE    cb27C, cb280, cb284, cb288;   /* +0x27C */
    void    *p28C, *p290;      /* +0x28C */
    uint8_t  unk294[4];
    M1CbE    cb298, cb29C;     /* +0x298 */
} M1EnemyAct;
void sub_001141F0(M1EnemyAct *a);
void sub_000AD090(void);
void m1_Stub102FA0(void);
void sub_00113B20(void);

/* 0x00114300: resets an enemy actor to its defaults (no sound, unit vectors), runs
 * 0x1141F0 and installs the default callbacks (debug stubs, draw 0x113B20). */
void m1_EnemyDefaults114300(M1EnemyAct *a)
{
    a->f05C = 0.0f;
    a->f068 = 0.0f;
    a->snd06C = -1;
    a->f074 = 0.0f;
    a->f0FC = 0.0f;
    a->f100 = 0.0f;
    a->f270 = 0.0f;
    a->f274 = 0.0f;
    a->f04C = 0;
    a->f050 = 0;
    a->f054 = 0;
    a->f058 = 0;
    a->f064 = 0;
    a->f070 = 0;
    a->f0F8 = 0;
    a->f104 = 0;
    a->v078[0] = 0.0f;
    a->v078[1] = 0.0f;
    a->v078[2] = 0.0f;
    a->v078[3] = 1.0f;
    a->v088[0] = 0.0f;
    a->v088[1] = 0.0f;
    a->v088[2] = 0.0f;
    a->v088[3] = 1.0f;
    sub_001141F0(a);
    a->p28C = 0;
    a->p290 = 0;
    a->cb27C = sub_000AD090;
    a->cb280 = m1_Stub102FA0;
    a->cb284 = m1_Stub102FA0;
    a->cb288 = sub_00113B20;
    a->cb298 = m1_Stub102FA0;
    a->cb29C = sub_000AD090;
}
