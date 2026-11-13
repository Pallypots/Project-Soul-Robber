/* Area m1, file 61: packed command list. Names inferred. */
#include <stdint.h>

typedef struct M1Cmd16 { int64_t packed00; int32_t on08; int32_t f0C; } M1Cmd16;
extern int32_t m1_cmdCount3DA390;
extern M1Cmd16 m1_cmds3DA398[16];

/* 0x00038E80: appends a command packing four bytes (d, c, b, a from high to low) above
 * the tag 0x3F80000000 (sign-extended ors); spins once 16 are queued. */
void m1_CmdPush038E80(int a, int b, int c, int d)
{
    int64_t v;
    if (m1_cmdCount3DA390 >= 16)
        for (;;) ;
    v = (int64_t)d | 0x3F80000000LL;
    v = (v << 8) | (int64_t)c;
    v = (v << 8) | (int64_t)b;
    v = (v << 8) | (int64_t)a;
    m1_cmds3DA398[m1_cmdCount3DA390].packed00 = v;
    m1_cmds3DA398[m1_cmdCount3DA390].on08 = 1;
    m1_cmds3DA398[m1_cmdCount3DA390].f0C = 0;
    m1_cmdCount3DA390++;
}

typedef struct M1TurnObj2 { uint8_t unk000[0x54]; float yaw54; uint8_t unk058[0x10C - 0x58]; float f10C; } M1TurnObj2;
typedef struct M1TurnSt2 { uint8_t unk00[0xA4]; float fA4; } M1TurnSt2;
float *sub_0001D0F0(void *o, int v);
void   sub_001AD940(float *m);
void   sub_001AD8E0(float *out, const float *m, float a);
void   sub_000F5D40(float *dst, const float *src);

/* 0x000EFAF0: as 0xEFA60 but h +0xA4 = -pi: clears +0x10C, yaw +0x54 -= pi, and resets
 * the first three rows of the frame matrix (0x1D0F0(o, 1)) to identity. */
void m1_TurnAround0EFAF0(M1TurnObj2 *o, M1TurnSt2 *h)
{
    float m[16];
    float *f;
    o->f10C = 0.0f;
    o->yaw54 -= 3.1415927f;
    h->fA4 = -3.1415927f;
    f = sub_0001D0F0(o, 1);
    sub_001AD940(m);
    sub_001AD8E0(m, m, 0.0f);
    sub_000F5D40(f, m);
    sub_000F5D40(f + 4, m + 4);
    sub_000F5D40(f + 8, m + 8);
}

typedef struct M1PosB { uint8_t unk00[0x60]; float pos60[4]; } M1PosB;
typedef struct M1Climb {
    uint8_t unk000[0x24];
    float   v24[4];            /* +0x24 */
    uint8_t unk034[0x318 - 0x34];
    int32_t on318;             /* +0x318 */
    uint8_t unk31C[0xFD8 - 0x31C];
    M1PosB *refFD8;            /* +0xFD8 */
} M1Climb;
float sub_00082D70(const float *v);
void  sub_001AD9F0(float *out, const float *a, const float *b);

/* 0x000CBB70: 0 when +0x318 is off, else the distance from +0x24 to the reference
 * object's position lowered by 8 (0x1AD9F0, length 0x82D70). */
float m1_RefDist0CBB70(M1Climb *p)
{
    float v[4];
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    if (p->on318 == 0)
        return 0.0f;
    sub_000F5D40(v, p->refFD8->pos60);
    v[1] = v[1] - 8.0f;
    sub_001AD9F0(v, v, p->v24);
    return sub_00082D70(v);
}
