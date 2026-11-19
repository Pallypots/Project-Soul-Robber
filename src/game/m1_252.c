/* Area m1, file 252: enemy turn/approach pickers. Names inferred. */
#include <stdint.h>

typedef struct M1O252 { uint8_t unk00[0x54]; float r54; uint8_t unk58[8]; uint8_t pos60[0x10]; } M1O252;
typedef struct M1S252 { uint8_t unk00[0x74]; float t74; } M1S252;
typedef struct M1P252 { uint8_t unk00[0x10]; int32_t n10; } M1P252;
extern M1O252 *g_playerObj;
float sub_00113200(M1O252 *o, const void *target);
float sub_001B2770(const void *a, const void *b);
float sub_001A3F30(float v);
M1P252 *sub_001133E0(M1S252 *s, int32_t k);
void sub_00113040(M1O252 *o, M1S252 *s, int32_t mode);

/* 0x0017B890: turn toward the player at up to 2 degrees per tick while more than 5 degrees off; once facing and the
   timer t74 is out, within 40 units pick mode 6 (queued counter set: clears slot 3), 5 between 20 and 30 units, else 4. */
void m1_Face17B890(M1O252 *o, M1S252 *s)
{
    float a = sub_00113200(o, g_playerObj->pos60);
    float d = sub_001B2770(o->pos60, g_playerObj->pos60);
    M1P252 *p;
    int m;
    if (sub_001A3F30(a) >= 0.0872664675f) {
        if (a > 0.0349065848f)
            a = 0.0349065848f;
        else if (-0.0349065848f > a)
            a = -0.0349065848f;
        o->r54 += a;
        return;
    }
    if (s->t74 > 0.0f || d > 40.0f)
        return;
    p = sub_001133E0(s, 2);
    if (p && p->n10 > 0) {
        sub_001133E0(s, 3)->n10 = 0;
        sub_00113040(o, s, 6);
        return;
    }
    m = 4;
    if (d >= 20.0f && 30.0f >= d)
        m = 5;
    sub_00113040(o, s, m);
}

struct M1TA252;
typedef void (*M1TFn252)(void *o, struct M1TA252 *a);
typedef void (*M1TNFn252)(void *o, struct M1TA252 *a, void *n);
typedef struct M1TN252 { uint8_t unk00[4]; int32_t n4; float t8; uint8_t unk0C[0x18]; struct M1TN252 *next24; } M1TN252;
typedef struct M1TA252 { uint8_t unk00[0x2C]; int32_t n2C; uint8_t unk30[0x1C]; uint32_t flags4C; int32_t st50; uint8_t unk54[8];
    float t5C; M1TN252 *list60; uint8_t unk64[4]; float t68; uint8_t unk6C[8]; float t74; uint8_t unk78[0x1F8]; float f270, f274;
    uint8_t unk278[8]; M1TFn252 cb280, cb284, cb288; uint8_t unk28C[4]; M1TFn252 *tbl290; M1TNFn252 *tbl294; M1TFn252 cb298; } M1TA252;
typedef struct M1TO252 { uint8_t unk00[0xC]; uint8_t flagsC; uint8_t unk0D[0x53]; uint8_t pos60[0x10]; } M1TO252;
extern float a50_frameUnits, a50_frameSeconds;
int m1_KindMapEE5F0(M1TO252 *o);
M1TA252 *sub_0001D960(M1TO252 *o, int32_t slot);
void sub_000264F0(void *pos, int32_t a, int32_t b, int32_t c);

/* 0x00112970: actor tick: find its behaviour slot (hang if missing), run the pre and post hooks, every queued node
   handler (aging each node), the current state's handler (hang if missing), and while active the update hooks, timers
   (+0x5C/+0x68 up, +0x74 down) and, with flag 0x1000000, the health bar. */
void m1_ActorTick112970(M1TO252 *o)
{
    M1TA252 *a = sub_0001D960(o, m1_KindMapEE5F0(o));
    M1TN252 *n, *next;
    M1TFn252 fn;
    if (!a)
        for (;;) ;
    a->cb298(o, a);
    a->cb280(o, a);
    for (n = a->list60; n; n = next) {
        next = n->next24;
        a->tbl294[n->n4](o, a, n);
        n->t8 += a50_frameSeconds;
    }
    fn = a->tbl290[a->st50];
    if (!fn)
        for (;;) ;
    fn(o, a);
    if (!(o->flagsC & 1))
        return;
    a->cb284(o, a);
    a->t5C += a50_frameSeconds;
    a->t68 += a50_frameSeconds;
    a->t74 -= a50_frameSeconds;
    a->cb288(o, a);
    if (a->flags4C & 0x1000000)
        sub_000264F0(o->pos60, a->n2C, (int)(__int64)a->f270, (int)(__int64)a->f274);
}


typedef struct M1BE252 { uint8_t unk00[8]; int32_t n8; uint16_t wC, wE; uint8_t unk10[2]; uint16_t w12; } M1BE252;
typedef struct M1BA252 { uint8_t unk00[0x6C]; float t6C; uint8_t unk70[4]; M1BE252 *e74; } M1BA252;
typedef struct M1BO252 { uint8_t unk00[0x60]; uint8_t pos60[0x3C]; float f9C; } M1BO252;
extern uint8_t m1_spin32C848[];
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);
void r4c_Spin(M1BO252 *o, const void *t);
int32_t sub_000F60C0(M1BO252 *o, int32_t a, int32_t b);
void m1_GreenFx196DB0(int32_t k, M1BO252 *o);   /* regargs: k=EAX o=ECX */
void sub_000ED780(M1BO252 *o);
void sub_000ED780b(M1BO252 *o);                 /* same function (aliases stop cl merging calls) */
void sub_000ED780c(M1BO252 *o);
void sub_0001D7A0(M1BO252 *o);
void sub_000EE760(M1BO252 *o, float k);

/* 0x00197040: bubble tick: play the spawn sound once, spin, burst (green effect, sound 0x1BC, destroy) when its anchor
   is hit before step 5; after step 5 fade out at 128 per 45 frame units and destroy when empty; destroy after 5 s
   (calls 0x196DB0 with k=EAX o=ECX). */
void m1_Bubble197040(M1BO252 *o, M1BA252 *a)
{
    M1BE252 *e = a->e74;
    if (!e->wC && a->t6C >= a50_frameSeconds) {
        aab_Effect494D0(0x1A6, o->pos60, 1);
        e->wC = 1;
    }
    r4c_Spin(o, m1_spin32C848);
    if (!e->w12 && sub_000F60C0(o, 0, 0) != -1) {
        m1_GreenFx196DB0(e->n8, o);
        aab_Effect494D0(0x1BC, o->pos60, 1);
        sub_000ED780(o);
        return;
    }
    if (!e->wE) {
        if (e->w12 == 5) {
            e->wE = 1;
            sub_0001D7A0(o);
        }
    } else {
        o->f9C -= 128.0f / (45.0f / a50_frameUnits);
        if (0.0f >= o->f9C) {
            o->f9C = 0.0f;
            sub_000ED780b(o);
            return;
        }
    }
    sub_000EE760(o, 1.0f);
    if (a->t6C > 5.0f)
        sub_000ED780c(o);
}

