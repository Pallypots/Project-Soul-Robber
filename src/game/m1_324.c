/* Area m1, group 324. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[0x18]; uint32_t f18; uint8_t _1c[0x88 - 0x1C]; float f88, f8c, f90; } M1Hs324;
typedef struct { uint8_t _0[0x60]; float f60; uint8_t _64[4]; float f68; } M1Ht324;
typedef struct { uint8_t _0[0x4C]; uint32_t f4c; uint8_t _50[8]; int32_t st58; uint8_t _5c[0x74 - 0x5C];
    float wait74; uint8_t _78[0x104 - 0x78]; M1Ht324 *p104; uint8_t _108[0x278 - 0x108]; M1Hs324 *s278; } M1Ha324;
typedef struct { uint8_t _0[0x30]; int32_t h30; uint8_t _34[0x2C]; uint8_t pos60[0x10]; } M1Ho324;

extern float m1_frameRate42C85C;
int  sub_00145780(M1Ho324 *o, float t);
int  sub_00145780b(M1Ho324 *o, float t);
int  sub_00145780c(M1Ho324 *o, float t);
int  sub_00145780d(M1Ho324 *o, float t);
int  sub_000494D0(int id, void *p, int f);
int  sub_000494D0b(int id, void *p, int f);
int  sub_00145940(M1Ho324 *o, float x, float z, float lo, float hi);
int  m1_AiSetState1456E0(M1Ho324 *o, M1Ha324 *a, int st, int f);
int  b4c_Enter1456E0d(M1Ho324 *o, M1Ha324 *a, int st, int f);
void sub_00113480y(M1Ha324 *a, int k);
void sub_00186470(M1Ho324 *o, M1Ha324 *a, int st);          /* regargs: o=EBX a=EDI */
void sub_00186470b(M1Ho324 *o, M1Ha324 *a, int st);
void sub_00186470c(M1Ho324 *o, M1Ha324 *a, int st);
void sub_00186470d(M1Ho324 *o, M1Ha324 *a, int st);
int32_t sub_000833E0(int32_t h);

/* 0x00187040: hover strike: a pending high hit (flags 0x2000 and 0x8000)
   cancels it (state 0xA). Step 0 plays the whoosh at 2.5 and 9.5, turns
   toward the target within 5 degrees and when the wait ends (or it faces
   the target at height) starts the rise command; step 1 rises to 15 at
   60/s (move 0x21); step 2 cancels on a block (state 5) or a high hit
   (0xA), else starts the dive command when at height; step 3 dives to 8 at
   20/s (move 0x22); step 4 waits to land and for the clip; step 5 goes to
   state 0xA after a high hit, else 2. */
void m1_HoverStrike187040(M1Ho324 *o, M1Ha324 *a)
{
    M1Hs324 *t = a->s278;
    uint32_t f = t->f18;
    uint32_t g = f & 0x2000;
    M1Ht324 *p;
    int32_t r;
    volatile int32_t k;
    if (g && (int16_t)f < 0)
        goto fin_hi;
    switch (a->st58) {
    case 0:
        if (sub_00145780(o, 2.5f) || sub_00145780b(o, 9.5f))
            sub_000494D0(0x114, o->pos60, 0);
        p = a->p104;
        r = sub_00145940(o, p->f60, p->f68, -0.0872664675f, 0.0872664675f);
        if (!(0.0f >= a->wait74)) {
            if (r != 1) return;
            if (!(t->f8c >= t->f88)) return;
        }
        k = 1;
        goto adv;
    case 1:
        m1_AiSetState1456E0(o, a, 0x21, 0);
        t->f8c = 15.0f;
        t->f90 = m1_frameRate42C85C * 60.0f;
        a->st58++;
    case 2:
        if (sub_00145780c(o, 2.5f) || sub_00145780d(o, 9.5f))
            sub_000494D0b(0x114, o->pos60, 0);
        if (a->f4c & 0x100) {
            sub_00186470(o, a, 5);
            return;
        }
        if (t->f18 & 0x10000) {
            sub_00186470b(o, a, 0xA);
            return;
        }
        if (!(t->f88 >= t->f8c)) return;
        k = 2;
    adv:
        sub_00113480y(a, k);
        a->st58++;
        return;
    case 3:
        b4c_Enter1456E0d(o, a, 0x22, 0);
        t->f8c = 8.0f;
        t->f90 = m1_frameRate42C85C * 20.0f;
        a->st58++;
        return;
    case 4:
        if (t->f8c >= t->f88 && sub_000833E0(o->h30))
            a->st58++;
        return;
    case 5:
        if (g) {
        fin_hi:
            sub_00186470c(o, a, 0xA);
            return;
        }
        sub_00186470d(o, a, 2);
        return;
    }
}
