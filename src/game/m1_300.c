/* Area m1, group 300: 0x001172F0. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[4]; uint32_t f4; } M1Bs300;
typedef struct {
    uint8_t _0[0x58]; int32_t st58; uint8_t _5c[8]; int32_t st64; uint8_t _68[4];
    int32_t h6c; int32_t h70; uint8_t _74[0x278 - 0x74]; M1Bs300 *s278;
} M1Ba300;
typedef struct { uint8_t _0[0x60]; uint8_t f60[4]; } M1Bo300;

int  m1_AiSetState1456E0(M1Bo300 *o, M1Ba300 *a, int st, int f);
int  b4c_Enter1456E0f(M1Bo300 *o, M1Ba300 *a, int st, int f);
int  b4c_Enter1456E0d(M1Bo300 *o, M1Ba300 *a, int st, int f);
void sub_0001D4E0f(M1Bo300 *o);
void sub_0001D4E0g(M1Bo300 *o);
void sub_0001D4E0h(M1Bo300 *o);
int  sub_000494D0(int id, void *p, int f);
int  sub_00036750(M1Bo300 *o, int k);
void a80_ModeSetFlag4(void);

/* 0x001172F0: pick the follow-up action for the finished move. */
void m1_NextAction1172F0(M1Bo300 *o, M1Ba300 *a)
{
    M1Bs300 *s;
    int st;
    switch (a->st64) {
    case 0x30: case 0x31: case 0x32: case 0x33: case 0x37: case 0x3B:
        if (m1_AiSetState1456E0(o, a, 0x14, 0) == 1)
            sub_0001D4E0f(o);
        goto spawn;
    case 0x36:
        st = 0x37;
        goto enter;
    case 0x3A:
        st = 0x3B;
    enter:
        if (b4c_Enter1456E0f(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        a->st58 = 0;
        break;
    default:
        if (b4c_Enter1456E0d(o, a, 0x14, 0) == 1)
            sub_0001D4E0h(o);
    spawn:
        a->h6c = sub_000494D0(0x174, o->f60, 0);
        a->h70 = sub_00036750(o, 2);
        a->st58 = 0x63;
        break;
    }
    s = a->s278;
    if (s->f4 & 0x200) {
        s->f4 &= ~0x200;
        a80_ModeSetFlag4();
    }
}

typedef struct { uint8_t _0[0xC]; uint32_t fC; uint8_t _10[0x184 - 0x10]; float f184; } M1Bs300b;
typedef struct {
    uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[0x74 - 0x50]; float wait74;
    uint8_t _78[0x278 - 0x78]; M1Bs300b *s278;
} M1Ba300b;
typedef struct { uint8_t _0[0x20]; uint8_t *p20; uint8_t _24[0x60 - 0x24]; float x60, y64, z68;
    uint8_t _6c[0xA0 - 0x6C]; float xa0, _a4, za8; } M1Bo300b;
typedef struct { float x, y, z, w; } M1V4300;

float m1_Height145B60(void *p);
void  m1_XfAlloc0C7540(M1Bo300b *o, float a, float b, M1V4300 *p, M1V4300 *d);
void  sub_00113AA0(void *o, void *h);
int32_t r2_PlayerInFrontB(M1Ba300b *a, M1Bo300b *o);       /* regargs: a=EAX */
void  r3_SetStateA(M1Bo300b *o, M1Ba300b *a, int st);       /* regargs: o=EBX a=EDI */
int   sub_001C7EE1(void);                                   /* rand */

/* 0x00133FC0: boss phase step: while the wait runs, spawn the effect at o's offset
   position; when it ends, react to the player (0x2B, 0x15 1 in 4, 0xE, or 5). */
void m1_BossPhase133FC0(M1Bo300b *o, M1Ba300b *a)
{
    M1Bs300b *s = a->s278;
    M1V4300 d, p;
    if (a->wait74 > 0.0f) {
        p.x = o->xa0 + o->x60;
        p.z = o->za8 + o->z68;
        p.y = o->y64;
        p.w = 1.0f;
        d.x = 0.0f; d.y = 0.0f; d.z = 0.0f; d.w = 1.0f;
        d.y = m1_Height145B60(o->p20 + 0x20);
        m1_XfAlloc0C7540(o, 1.0f, 0.6f, &p, &d);
        return;
    }
    sub_00113AA0(o, a);
    a->f4c |= 0x200;
    s->fC &= ~0x2000;
    if (s->fC & 0x20) {
        r3_SetStateA(o, a, 0x2B);
        return;
    }
    if (r2_PlayerInFrontB(a, o)) {
        s->f184 = 0.3f;
        if (sub_001C7EE1() & 3) {
            r3_SetStateA(o, a, 0xE);
            return;
        }
        r3_SetStateA(o, a, 0x15);
        return;
    }
    r3_SetStateA(o, a, 5);
}
