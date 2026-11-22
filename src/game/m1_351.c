/* Area m1, file 351: two enemy damage handlers (shared shape). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Hit351 { int32_t kind00; uint8_t unk04[8]; float dmg0C; uint8_t unk10[0x20]; } M1Hit351;   /* 0x30 bytes */
typedef struct M1St351a { uint8_t unk00[4]; uint32_t f04; uint8_t unk08[0x50 - 8]; int32_t n50; uint8_t unk54[8]; M1Hit351 hit5C; } M1St351a;
typedef struct M1Ai351 { uint8_t unk000[0x270]; float f270; float f274; void *s278; } M1Ai351;
typedef struct M1Ob351 { uint8_t unk00[0x10]; uint32_t f10; } M1Ob351;
typedef struct M1Kc351 { uint8_t unk00[0x10]; float f10, f14, f18, f1c; } M1Kc351;
extern uint8_t m1_stats41FEC0[];
int      sub_0019BE60(int k);
void     sub_0019BE90(int k);
void     sub_000253D0(int a, int b);
void     PlayerObj_SetFlags(void *s, uint32_t f, int k);
void     sub_00087510(void);
int      sub_001146D0(void *o, M1Ai351 *e);          /* regargs: o=EDX e=EBX */
int      sub_00146030(int kind);
void     sub_00117580(void *o, int st);              /* regargs: e=EDI */
M1Kc351 *m1_Quest113400(void *e, int v);

/* 0x1177A0: take a hit: god mode zeroes the damage; dead enemies ignore it. Store the hit,
   subtract the damage (reporting whole points lost), on death clear health, flag the body,
   award the kill and play the sting. Then react with the state 0x1146D0 picks (0x13 means
   none); at half health or below (unless flag 0x40) also start the stagger turn and move
   the guard state 2 to 3. Returns 1 for kind-1 hits, else -1. */
int m1_TakeHit1177A0(M1Ob351 *o, M1Ai351 *e, M1Hit351 *hit) {
    M1St351a *s;
    M1Kc351 *c;
    float v;
    int was, now, k, r;
    if (sub_0019BE60(0x10000))
        hit->dmg0C = 0.0f;
    if (o->f10 & 8)
        return 0;
    s = (M1St351a *)e->s278;
    s->hit5C = *hit;
    v = e->f274 - s->hit5C.dmg0C;
    was = _mm_cvttss_si32(_mm_set_ss(e->f274));
    now = _mm_cvttss_si32(_mm_set_ss(v));
    e->f274 = v;
    if (now < was)
        sub_000253D0(2, was - now);
    if (0.0f >= e->f274) {
        sub_0019BE90(0x10000);
        e->f274 = 0.0f;
        o->f10 |= 8;
        s->f04 |= 0x10;
        PlayerObj_SetFlags(m1_stats41FEC0, 0x10, 0);
        sub_00087510();
    }
    k = sub_001146D0(o, e);
    r = sub_00146030(s->hit5C.kind00) == 1 ? 1 : -1;
    if (k != 0x13) {
        sub_00117580(o, k);
        if (!(s->f04 & 0x40) && e->f270 * 0.5f >= e->f274) {
            c = m1_Quest113400(e, 3);
            c->f10 = 0.0f;
            c->f14 = 0.0f;
            c->f18 = 0.0f;
            c->f1c = 0.0f;
            if (s->n50 == 2)
                s->n50 = 3;
        }
    }
    return r;
}

typedef struct M1St351b { uint8_t unk000[0x0C]; uint32_t f0C; uint8_t unk010[0x18C - 0x10]; int32_t n18C; uint8_t unk190[8]; M1Hit351 hit198; } M1St351b;
int  sub_0012D6F0(void *o, M1Ai351 *e);              /* regargs: o=EDX */
void sub_00131310(int next);                         /* regargs: o=EBX e=EDI */
void sub_00147710(void *e, int k, int a, int b, int c, int d);   /* regargs: e=ECX k=EAX */

/* 0x1318F0: twin of 0x1177A0 for another enemy: also ignores hits while flag 1 is set or,
   with flag 0x20000, any kind but 0x23; death sets flag 0x20 (the kill is awarded only
   without flag 1); "no reaction" is 0x1A; the half-health reaction starts the 5 effect
   and moves the guard state 2 to 3 when flag 1 is clear. */
int m1_TakeHit1318F0(M1Ob351 *o, M1Ai351 *e, M1Hit351 *hit) {
    M1St351b *s;
    float v;
    int was, now, k, r;
    if (sub_0019BE60(0x10000))
        hit->dmg0C = 0.0f;
    if (o->f10 & 8)
        return 0;
    s = (M1St351b *)e->s278;
    if ((s->f0C & 1) || ((s->f0C & 0x20000) && hit->kind00 != 0x23))
        return 0;
    s->hit198 = *hit;
    v = e->f274 - s->hit198.dmg0C;
    was = _mm_cvttss_si32(_mm_set_ss(e->f274));
    now = _mm_cvttss_si32(_mm_set_ss(v));
    e->f274 = v;
    if (now < was)
        sub_000253D0(2, was - now);
    if (0.0f >= e->f274) {
        sub_0019BE90(0x10000);
        e->f274 = 0.0f;
        o->f10 |= 8;
        s->f0C |= 0x20;
        if (!(s->f0C & 1)) {
            PlayerObj_SetFlags(m1_stats41FEC0, 0x10, 0);
            sub_00087510();
        }
    }
    k = sub_0012D6F0(o, e);
    r = sub_00146030(s->hit198.kind00) == 1 ? 1 : -1;
    if (k != 0x1A) {
        sub_00131310(k);
        if (!(s->f0C & 0x100) && e->f270 * 0.5f >= e->f274) {
            sub_00147710(e, 5, 0, 0, 0, 0);
            if (!(s->f0C & 1) && s->n18C == 2)
                s->n18C = 3;
        }
    }
    return r;
}
