/* Area m1, group 302: boss phases. Names inferred. */
#include <stdint.h>

typedef struct { uint8_t _0[0x30]; int32_t h30; uint8_t _34[0x128 - 0x34]; uint8_t b128; } M1Bo302;
typedef struct { uint8_t _0[0x164]; float f164, f168, f16c, f170; } M1Bs302;
typedef struct {
    uint8_t _0[0x58]; int32_t st58; uint8_t _5c[8]; int32_t st64;
    uint8_t _68[0x278 - 0x68]; M1Bs302 *s278;
} M1Ba302;

extern float m1_frameTime42C858, m1_frameRate42C85C;
int32_t sub_000833E0(int32_t h);
int  m1_AiSetState1456E0(M1Bo302 *o, M1Ba302 *a, int st, int f);
int  b4c_Enter1456E0f(M1Bo302 *o, M1Ba302 *a, int st, int f);
void sub_0001D4E0f(M1Bo302 *o);
void sub_0001D4E0g(M1Bo302 *o);
void r3_SetStateA(M1Bo302 *o, M1Ba302 *a, int st);          /* regargs: o=EBX a=EDI */

/* 0x00134B80: jump attack: wait for the wind-up clip, take off (move 0x34 ->
   0x35 or 0x38 -> 0x39), wait to land, play the landing move (+1), wait for
   it, then go to state 0x2B. While airborne (steps 0..4) the horizontal speed
   decays by 2% per frame unit. Unknown moves hang. */
void m1_JumpAttack134B80(M1Bo302 *o, M1Ba302 *a)
{
    M1Bs302 *s = a->s278;
    M1Bs302 *t;
    int32_t k, st;
    switch (a->st58) {
    case 0:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 1:
        k = a->st64;
        if (k == 0x34)      st = 0x35;
        else if (k == 0x38) st = 0x39;
        else for (;;) ;
        if (m1_AiSetState1456E0(o, a, st, 0) == 1)
            sub_0001D4E0f(o);
        a->st58++;
    case 2:
        if (o->b128 & 0x18)
            a->st58++;
        break;
    case 3:
        k = a->st64;
        if (k == 0x35)      st = 0x36;
        else if (k == 0x39) st = 0x3A;
        else for (;;) ;
        if (b4c_Enter1456E0f(o, a, st, 0) == 1)
            sub_0001D4E0g(o);
        t = a->s278;
        t->f16c = 0.0f;
        t->f168 = 0.0f;
        t->f164 = 0.0f;
        t->f170 = 1.0f;
        a->st58++;
        break;
    case 4:
        if (!sub_000833E0(o->h30)) break;
        a->st58++;
    case 5:
        r3_SetStateA(o, a, 0x2B);
        return;
    }
    if (a->st58 <= 4) {
        s->f164 = (1.0f - m1_frameTime42C858 * 0.02f) * s->f164;
        s->f16c = (1.0f - m1_frameTime42C858 * 0.02f) * s->f16c;
    }
}

typedef struct { uint8_t _0[0x10]; uint32_t f10; uint8_t _14[0x1C]; int32_t h30;
    uint8_t _34[0x128 - 0x34]; uint8_t b128; } M1Bo302b;
typedef struct { uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x164 - 0x10]; float f164, f168, f16c, f170; } M1Bs302b;
typedef struct { uint8_t _0[0x58]; int32_t st58; uint8_t _5c[0x278 - 0x5C]; M1Bs302b *s278; } M1Ba302b;

int  b4c_Enter1456E0d(M1Bo302b *o, M1Ba302b *a, int st, int f);
int  b4c_Enter1456E0i(M1Bo302b *o, M1Ba302b *a, int st, int f);
void sub_0001D4E0h(M1Bo302b *o);
void sub_0001D4E0i(M1Bo302b *o);
void r3_SetStateA2(M1Bo302b *o, M1Ba302b *a, int st);       /* regargs: o=EBX a=EDI */

/* 0x00133640: hop: wait for the clip, take off (move 0x29), wait to land,
   play the landing move 0x2A (stop the speed, clear the airborne flags), wait
   for it, then go to state 5. Speed decays by 2% per frame unit in steps 0..2. */
void m1_Hop133640(M1Bo302b *o, M1Ba302b *a)
{
    M1Bs302b *s = a->s278;
    M1Bs302b *t;
    switch (a->st58) {
    case 0:
    case 4:
        if (sub_000833E0(o->h30))
            a->st58++;
        break;
    case 1:
        if (b4c_Enter1456E0d(o, a, 0x29, 0) == 1)
            sub_0001D4E0h(o);
        a->st58++;
        break;
    case 2:
        if (o->b128 & 0x18)
            a->st58 = 3;
        break;
    case 3:
        if (b4c_Enter1456E0i(o, a, 0x2A, 0) == 1)
            sub_0001D4E0i(o);
        t = a->s278;
        t->f16c = 0.0f;
        t->f168 = 0.0f;
        t->f164 = 0.0f;
        t->f170 = 1.0f;
        o->f10 &= ~1u;
        s->fc &= ~0x10000u;
        a->st58++;
        break;
    case 5:
        r3_SetStateA2(o, a, 5);
        break;
    }
    if (a->st58 <= 2) {
        s->f164 = (1.0f - m1_frameTime42C858 * 0.02f) * s->f164;
        s->f16c = (1.0f - m1_frameTime42C858 * 0.02f) * s->f16c;
    }
}

typedef struct {
    uint8_t _0[0xC]; uint32_t fc; uint8_t _10[0x70 - 0x10]; float f70, f74, f78, f7c;
    uint8_t _80[0xF0 - 0x80]; int32_t ff0, ff4; uint8_t _f8[0x11C - 0xF8]; int32_t f11c, f120, f124;
} M1Mo302;
typedef struct { uint8_t _0[0x18]; float f18, f1c; } M1Me302;
typedef struct {
    uint8_t _0[0x74]; const void *t74, *t78; uint8_t _7c[0xC0 - 0x7C]; float fc0, fc4;
    const void *tc8, *tcc, *td0, *td4, *td8, *tdc; uint8_t _e0[0x1A8 - 0xE0]; void *h1a8;
} M1Mh302;

extern M1Mh302 *m1_minion3F6120;
extern const float m1_v278C44[], m1_v278C58[], m1_v278C68[], m1_v278C78[];
extern const uint8_t m1_tab319208[], m1_tab3192B8[];
extern const uint8_t m1_tab318E38[], m1_tab318E48[], m1_tab318E58[],
                     m1_tab318E68[], m1_tab318E78[], m1_tab318E88[];
M1Me302 *sub_0001D960(M1Mo302 *o, int k);
void sub_000F5D60(M1Mo302 *o, float a, float b, float c, const float *v);
void sub_000F5DD0(M1Mo302 *o, float a, float b, const float *v);
void r2d_MoverSet(M1Mo302 *o, float a, const float *v, const float *w);
void *sub_000ED630(int a, int b, int c, int d, int e);
void sub_0001D7A0(void *h);
void sub_000F90D0(M1Mh302 *h);

/* 0x000FE660: set up the minion's body: scale 1.25, movement limits and
   event offsets, its animation tables, and (once) its handle.
   Regargs: o=ESI. */
void m1_MinionInitFE660(M1Mo302 *o)
{
    M1Me302 *e;
    M1Mh302 *h;
    void *r;

    e = sub_0001D960(o, 0xD);
    h = m1_minion3F6120;
    o->f78 = 1.25f; o->f74 = 1.25f; o->f70 = 1.25f;
    o->fc |= 3;
    o->f7c = 1.0f;
    o->f124 = 1;
    sub_000F5D60(o, 1.25f, -10.0f, 4.0f, m1_v278C44);
    sub_000F5DD0(o, 1.25f, 5.0f, m1_v278C58);
    o->ff0 = 2;
    o->ff4 = 2;
    r2d_MoverSet(o, 1.25f, m1_v278C68, m1_v278C78);
    o->f11c = 1;
    o->f120 = 2;
    e->f18 = -6.25f;
    e->f1c = -12.5f;
    h->t74 = m1_tab319208;
    h->t78 = m1_tab3192B8;
    if (h->h1a8 == 0) {
        r = sub_000ED630(5, 0x14, 0, 0, 2);
        h->h1a8 = r;
        if (r == 0) for (;;) ;
        sub_0001D7A0(r);
    }
    sub_000F90D0(h);
    h->fc0 = 40.0f;
    h->fc4 = 80.0f;
    h->tc8 = m1_tab318E68;
    h->tcc = m1_tab318E38;
    h->td0 = m1_tab318E78;
    h->td4 = m1_tab318E48;
    h->td8 = m1_tab318E88;
    h->tdc = m1_tab318E58;
}

typedef struct { uint8_t _0[0x50]; float f50; uint8_t _54[0xC]; uint8_t pos60[0x10];
    uint8_t _70[0x128 - 0x70]; uint8_t b128; } M1Wo302;
typedef struct {
    uint8_t _0[0x68]; float f68; uint8_t _6c[0xA8 - 0x6C]; int32_t sta8; uint8_t _ac[8];
    float fb4, fb8, fbc, fc0, fc4, fc8, fcc, fd0;
} M1Wa302;
typedef struct { uint8_t _0[0x60]; uint8_t pos60[0x10]; } M1Wp302;

extern M1Wp302 *g_playerObj;
float r4_DistanceXZ(void *a, void *b);
void m1_LockMark0C56B0(M1Wo302 *o);
void m1_PlShot0C62A0(M1Wo302 *o);
void r2_SetComp5Mode(M1Wo302 *o, int k);                    /* regargs: o=ESI k=EDI */

/* 0x0010BB50: wolf lunge: lock on when the player comes within 60 units
   (unless flags 6), otherwise crouch (state 1); after 0.02 s leap (state 2);
   once airborne and touching ground again switch to mode 0x17. */
void m1_Lunge10BB50(M1Wo302 *o, M1Wa302 *a)
{
    switch (a->sta8) {
    case 0:
        if (!(o->b128 & 6) && r4_DistanceXZ(o->pos60, g_playerObj->pos60) < 60.0f) {
            m1_LockMark0C56B0(o);
            return;
        }
        m1_PlShot0C62A0(o);
        a->fb4 = m1_frameRate42C85C * 98.0f;
        a->fc0 = 0.0f; a->fbc = 0.0f; a->fb8 = 0.0f;
        a->fd0 = 0.0f; a->fcc = 0.0f; a->fc8 = 0.0f; a->fc4 = 0.0f;
        o->f50 = 1.57079637f;
        a->sta8 = 1;
        a->f68 = 0.0f;
        return;
    case 1:
        if (!(a->f68 >= 0.02f)) return;
        a->fb4 = m1_frameRate42C85C * 1.2f;
        a->fc0 = m1_frameRate42C85C * -36.0f;
        a->fc4 = m1_frameRate42C85C * 0.69813174f;
        a->sta8 = 2;
        a->f68 = 0.0f;
        return;
    case 2:
        if (a->fbc > 0.0f && (o->b128 & 0x18))
            r2_SetComp5Mode(o, 0x17);
        return;
    }
}
