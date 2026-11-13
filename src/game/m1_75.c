/* Area m1, file 75: sway setup variants. Names inferred. */
#include <stdint.h>

typedef struct M1SwayR {
    uint32_t unk00;
    uint32_t flags04;          /* +0x04 */
    uint8_t unk08[0x2C - 8];
    float   q2C[4];            /* +0x2C */
    int32_t i3C;               /* +0x3C */
    int32_t i40;               /* +0x40 */
} M1SwayR;
typedef struct M1SwayR2 {
    uint8_t unk000[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint8_t unk010[0x164 - 0x10];
    float   q164[4];           /* +0x164 */
    int32_t i174;              /* +0x174 */
    int32_t i178;              /* +0x178 */
} M1SwayR2;
typedef struct M1SwayH {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x6C - 0x50];
    int32_t snd6C;             /* +0x6C */
    uint8_t unk070[0x74 - 0x70];
    float   f74;               /* +0x74 */
    uint8_t unk078[0xF8 - 0x78];
    int32_t mode0F8;           /* +0xF8 */
    uint8_t unk0FC[0x104 - 0xFC];
    void   *tgt104;            /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    void   *rig278;            /* +0x278 */
} M1SwayH;
typedef struct M1SwayC { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1SwayC;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
extern void *g_playerObj;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_0001D4E0(void *o);
M1SwayC *sub_00113400(void *h, int v);
int  sub_000494D0(int id, const void *pos, int c);
void *sub_00036750(void *o, int b);

/* Sway setup: enter state st, reset the rig quaternion (Q), PRE, h +0x4C |= 0x70, BODY,
 * command 1 = (a, b, T unless -1, 0). RT is the rig type. */
#define M1_SWAYQ(name, RT, st, Q, PRE, BODY, T, a, b)      \
void name(uint8_t *o, M1SwayH *h)                           \
{                                                           \
    RT *r = (RT *)h->rig278;                                \
    RT *p;                                                  \
    M1SwayC *c;                                             \
    float t;                                                \
    if (sub_001456E0(o, h, st, 0) == 1)                     \
        sub_0001D4E0(o);                                    \
    p = (RT *)h->rig278;                                    \
    Q                                                       \
    PRE                                                     \
    h->flags4C |= 0x70;                                     \
    BODY                                                    \
    t = (T);                                                \
    c = sub_00113400(h, 1);                                 \
    c->f10 = (a);                                           \
    c->f14 = (b);                                           \
    if (t != -1.0f)                                         \
        c->f18 = t;                                         \
    c->f1C = 0.0f;                                          \
}

#define M1_QRESET p->q2C[2] = 0.0f; p->q2C[1] = 0.0f; p->q2C[0] = 0.0f; p->q2C[3] = 1.0f;
#define M1_QRESET2 p->q164[2] = 0.0f; p->q164[1] = 0.0f; p->q164[0] = 0.0f; p->q164[3] = 1.0f;
#define M1_SWAYX(name, st, BODY, T, a, b) M1_SWAYQ(name, M1SwayR, st, M1_QRESET, ;, BODY, T, a, b)
/* rig flag 1 set: clear o +0xC bits 0xE0, o +0x10 |= 0x105, rig +0xC |= 4 */
#define M1_SWAYPRE if (r->flags0C & 1) { *(uint32_t *)(o + 0xC) &= ~0xE0u; \
    *(uint32_t *)(o + 0x10) |= 0x105; r->flags0C |= 4; }
#define M1_T10 180.0f / (0.3f / m1_frameRate42C85C) * 0.017453292f

/* 0x00115760: sway, state 2, +-10 degrees over 0.3 s (h +0x74 = 0.3, rig +0x3C = +0x40). */
M1_SWAYX(m1_Sway115760, 2, r->i3C = r->i40; h->f74 = 0.3f;,
         M1_T10, 0.17453294f, -0.17453294f)
/* 0x00115E70: sway, state 0x21, +-5 degrees, rig +4 |= 4, plays sound 0x16D at the object. */
M1_SWAYX(m1_Sway115E70, 0x21, r->flags04 |= 4; h->snd6C = sub_000494D0(0x16D, o + 0x60, 0);,
         m1_frameTime42C858 * 0.052359879f, 0.087266468f, -0.087266468f)
/* 0x00115F50: sway, state 1, rig quaternion z = -15*frameRate, rig +4 |= 4, 0x36750(o, 5),
 * h +0x74 = 5, +-5 degrees at frameTime*2 degrees. */
M1_SWAYQ(m1_Sway115F50, M1SwayR, 1,
         p->q2C[1] = 0.0f; p->q2C[0] = 0.0f; p->q2C[3] = 1.0f;
         p->q2C[2] = 0.0f - m1_frameRate42C85C * 15.0f;, ;,
         r->flags04 |= 4; sub_00036750(o, 5); h->f74 = 5.0f;,
         m1_frameTime42C858 * 0.034906585f, 0.087266468f, -0.087266468f)
/* 0x0012EDC0: sway (rig at +0x164), state 2, +-10 degrees over 0.3 s, rig +0x174 = +0x178. */
M1_SWAYQ(m1_Sway12EDC0, M1SwayR2, 2, M1_QRESET2, ;, r->i174 = r->i178; h->f74 = 0.3f;,
         M1_T10, 0.17453294f, -0.17453294f)
/* 0x0012EF90: sway (rig at +0x164), state 0x16, rig +0xC |= 2, +-5 degrees. */
M1_SWAYQ(m1_Sway12EF90, M1SwayR2, 0x16, M1_QRESET2, M1_SWAYPRE, r->flags0C |= 2;,
         m1_frameTime42C858 * 0.034906585f, 0.087266468f, -0.087266468f)
/* 0x0012F080: sway (rig at +0x164), state 0x17, rig +0xC clears 0x800, +-5 degrees. */
M1_SWAYQ(m1_Sway12F080, M1SwayR2, 0x17, M1_QRESET2, M1_SWAYPRE, r->flags0C &= ~0x800u;,
         m1_frameTime42C858 * 0.034906585f, 0.087266468f, -0.087266468f)
/* 0x0012F550: sway (rig at +0x164), state 0x21, target = player (mode 1), rig +0xC |= 2,
 * +-5 degrees at frameTime*22.5 degrees. */
M1_SWAYQ(m1_Sway12F550, M1SwayR2, 0x21, M1_QRESET2, ;,
         h->tgt104 = g_playerObj; h->mode0F8 = 1; r->flags0C |= 2;,
         m1_frameTime42C858 * 0.39269909f, 0.087266468f, -0.087266468f)

typedef struct M1SwayPt { float pos[4]; float pad[2]; } M1SwayPt;
extern M1SwayPt m1_swayPts31A3B0[6];
typedef struct M1SwayR3 {
    uint32_t unk00;
    uint32_t flags04;          /* +0x04 */
    uint8_t unk08[0x1C - 8];
    float   pos1C[4];          /* +0x1C */
    float   q2C[4];            /* +0x2C */
    int32_t i3C;               /* +0x3C */
    int32_t pt40;              /* +0x40 */
} M1SwayR3;
int  aab_Rand(void);
void sub_000F5D40(float *d, const float *s);

/* 0x00115620: sway, state 2, quaternion z = -30*frameRate, random sound 0x16B, rig and target
 * go to sway point +0x40 (table 0x31A3B0, mode 2), rig +4 |= 4, +-0.1 degree at 5 deg/s. */
void m1_Sway115620(uint8_t *o, M1SwayH *h)
{
    M1SwayR3 *r = (M1SwayR3 *)h->rig278;
    M1SwayR3 *p;
    M1SwayC *c;
    float v[4];
    float t;
    if (sub_001456E0(o, h, 2, 0) == 1)
        sub_0001D4E0(o);
    p = (M1SwayR3 *)h->rig278;
    p->q2C[1] = 0.0f;
    p->q2C[0] = 0.0f;
    p->q2C[2] = 0.0f - m1_frameRate42C85C * 30.0f;
    p->q2C[3] = 1.0f;
    h->flags4C |= 0x70;
    if (aab_Rand() & 1)
        sub_000494D0(0x16B, o + 0x60, 0);
    sub_000F5D40(v, m1_swayPts31A3B0[r->pt40].pos);
    sub_000F5D40(r->pos1C, v);
    h->mode0F8 = 2;
    sub_000F5D40((float *)&h->tgt104, v);
    r->flags04 |= 4;
    t = m1_frameTime42C858 * 0.087266468f;
    c = sub_00113400(h, 1);
    c->f10 = 0.0017453294f;
    c->f14 = -0.0017453294f;
    if (t != -1.0f)
        c->f18 = t;
    c->f1C = 0.0f;
}
