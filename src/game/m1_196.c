/* Area m1, file 196: pickup and lookup helpers. Names inferred. */
#include <stdint.h>

typedef struct M1OrT196 { uint8_t unk00[0x128]; uint8_t b128; } M1OrT196;
typedef struct M1Orb196 { uint32_t flags0; uint8_t unk04[0x3C]; int32_t i40; uint8_t unk44[0x40]; float ang84; uint8_t unk88[8]; float v90[4]; uint8_t unkA0[0x80]; M1OrT196 *t120; } M1Orb196;
extern float m1_frameTime42C858;
extern uint8_t *g_playerObj;
void  m1_LockMark0C56B0(M1OrT196 *t);
void  m1_WrapAngleA35B0(float *a);
float sub_000A2EF0(M1Orb196 *o, void *p);
void  sub_000A41D0(void *o, int k);

/* 0x94150: slow orbiting pickup: spin 20 degrees per frame; when its owner is busy or the player is over 1000 away, stop it and despawn. */
void m1_OrbitSlow094150(M1Orb196 *o) {
    M1OrT196 *t; uint32_t f;
    if (o->i40 != 0) return;
    t = o->t120;
    m1_LockMark0C56B0(t);
    o->ang84 += m1_frameTime42C858 * 0.34906587f;
    m1_WrapAngleA35B0(&o->ang84);
    if (!(t->b128 & 0x1E) && !(sub_000A2EF0(o, g_playerObj) > 1000.0f)) return;
    f = o->flags0 & ~0x10u;
    o->v90[0] = 0.0f; o->v90[1] = 0.0f; o->v90[2] = 0.0f; o->v90[3] = 0.0f;
    o->flags0 = f;
    sub_000A41D0(o, 1);
}

typedef struct M1RbH196 { uint8_t unk00[4]; int32_t n4; } M1RbH196;
typedef struct M1RbE196 { int32_t id0; float pos4[3]; float rot10[3]; } M1RbE196;
extern M1RbH196 *m1_rubber3F0748;
extern M1RbE196 *m1_rubberBody3F074C;
void a3c_VecCopy(float *dst, const float *src);

/* 0xE0640: look up a placed object by id and return its position and rotation (w = 1); 0 when not found. */
int m1_PlaceGet0E0640(int id, float *pos, float *rot) {
    M1RbE196 *e; int i, n; float v[4];
    if (m1_rubber3F0748 == 0) return 0;
    n = m1_rubber3F0748->n4;
    e = m1_rubberBody3F074C;
    for (i = 0; i < n; i++, e++)
        if (e->id0 == id) goto found;
    return 0;
found:
    v[0] = e->pos4[0]; v[1] = e->pos4[1]; v[2] = e->pos4[2]; v[3] = 1.0f;
    a3c_VecCopy(pos, v);
    v[0] = e->rot10[0]; v[1] = e->rot10[1]; v[2] = e->rot10[2];
    a3c_VecCopy(rot, v);
    return 1;
}

typedef struct M1Pr196 { uint8_t unk00[8]; int32_t kind8; uint32_t flagsC; uint8_t unk10[0x140]; } M1Pr196;
typedef struct M1Pc196 { uint8_t unk00[0x4C]; int32_t i4C; } M1Pc196;
extern uint8_t m1_snd3E1270[];
void *rbi_Comp1D960(void *o, int comp);
void  m1_ListAdd0192B0(void *l, int k);
int   sub_000F3140(int kind);
void  r1b_RecDetachNodes(M1Pr196 *r);
void  sub_000EE270(void *c);
void  sub_000F3AA0(M1Pc196 *c);
void  r1b_RecRemoveItem(void *o, void *c);

/* 0xEFDE0: tear down an object's parts: detach every active part record, reset components 0xD and 5 and remove them (hangs on a null object). */
int m1_PartsTeardown0EFDE0(M1Pr196 *o) {
    M1Pr196 *r; void *c13; M1Pc196 *c5; int i;
    if (o == 0) for (;;) ;
    rbi_Comp1D960(o, 0xD);
    rbi_Comp1D960(o, 5);
    m1_ListAdd0192B0(m1_snd3E1270, 0);
    for (i = 0, r = o; i < sub_000F3140(o->kind8); i++, r++)
        if (r->flagsC & 1) { r->flagsC &= ~1u; r1b_RecDetachNodes(r); }
    c13 = rbi_Comp1D960(o, 0xD);
    c5 = (M1Pc196 *)rbi_Comp1D960(o, 5);
    sub_000EE270(c13);
    sub_000F3AA0(c5);
    c5->i4C = 0;
    r1b_RecRemoveItem(o, c5);
    r1b_RecRemoveItem(o, c13);
    return 1;
}

typedef struct M1Tg196 { uint32_t flags0; int32_t phase4; } M1Tg196;
typedef struct M1Sl196 { uint8_t unk00[0x48]; int32_t on48; } M1Sl196;
M1Sl196 *m1_SlotGet0A4290(int k);
int  r2b_TestBit(int bit);
void sub_000A42F0(int k, int on);

/* 0xB6EB0: event toggle handler: message 0 clears, 1 arms (phase 0xA), 3 or phase 0x14 resets; while armed, switch slot 0 on or off to follow story bit 0xC1. */
int m1_BitToggle0B6EB0(int msg, M1Tg196 *t) {
    M1Sl196 *s;
    if (msg == 0) { t->flags0 = 0; t->phase4 = 0; return 1; }
    if (msg == 1) { t->flags0 |= 1; t->phase4 = 0xA; return 1; }
    if (msg != 3) {
        if (t->phase4 == 0xA) goto run;
        if (t->phase4 != 0x14) return 1;
    }
    t->flags0 = 0; t->phase4 = 0;
    return 0;
run:
    s = m1_SlotGet0A4290(0);
    if (r2b_TestBit(0xC1)) {
        if (s->on48 != 1) sub_000A42F0(0, 1);
    } else if (s->on48 != 0) {
        sub_000A42F0(0, 0);
        return 1;
    }
    return 1;
}

#include <xmmintrin.h>
typedef struct M1Tm196 { uint32_t flags0; int32_t phase4; int32_t wait8; } M1Tm196;
extern float m1_fps42C964;
void sub_000A4340(int a, int b);

/* 0xABB60: timed event handler: message 0 clears, 1 arms with a 3-second wait, 3 resets; when armed fire 0xA4340(2, 3) once and move to phase 0x14, which resets on the next call. */
int m1_TimedEvent0ABB60(int msg, M1Tm196 *t) {
    if (msg == 0) { t->flags0 = 0; t->phase4 = 0; return 1; }
    if (msg == 1) {
        t->flags0 |= 1; t->phase4 = 0xA;
        t->wait8 = _mm_cvtt_ss2si(_mm_set_ss(m1_fps42C964 * 3.0f));
        return 1;
    }
    if (msg == 3) { t->flags0 = 0; t->phase4 = 0; return 0; }
    if (t->phase4 == 0xA) { sub_000A4340(2, 3); t->phase4 = 0x14; return 1; }
    if (t->phase4 == 0x14) { t->flags0 = 0; t->phase4 = 0; return 0; }
    return 1;
}

typedef struct M1Ev196 { uint8_t unk00[0xC]; int32_t a0C, b10, c14; int16_t type18, sub1A; } M1Ev196;
void r2c_MinionAnim(int a);
void r2c_CtlAnim(int a);
void r2c_BodyAnim(int a);
void sub_000FE330(int a);
void sub_00100070(int a);
void sub_000FBA50(int a);
void m1_EvWarp0F0430(int a, int b, int c);
void m1_EvLog0E3FF0(int type, int sub);
void m1_EvRun0E4050(int type, int sub, int a, int b, int c);

/* Twin event dispatchers: type 3 sub 3/4/5 go to the minion, control and body handlers, sub 7 warps; anything else is logged and run generically. */
#define M1_EVDISP196(name, f3, f4, f5) \
void name(int unused, M1Ev196 *e) { \
    if (e == 0) return; \
    if (e->type18 == 3 && e->sub1A == e->type18) { f3(e->a0C); return; } \
    if (e->type18 == 3 && e->sub1A == 4) { f4(e->a0C); return; } \
    if (e->type18 == 3 && e->sub1A == 5) { f5(e->a0C); return; } \
    if (e->type18 == 3 && e->sub1A == 7) { m1_EvWarp0F0430(e->a0C, e->b10, e->c14); return; } \
    m1_EvLog0E3FF0(e->type18, e->sub1A); \
    m1_EvRun0E4050(e->type18, e->sub1A, e->a0C, e->b10, e->c14); \
}

/* 0xEA5A0: event dispatcher, start set. */
M1_EVDISP196(m1_EvDispA0EA5A0, r2c_MinionAnim, r2c_CtlAnim, r2c_BodyAnim)
/* 0xEB430: event dispatcher, stop set. */
M1_EVDISP196(m1_EvDispB0EB430, sub_000FE330, sub_00100070, sub_000FBA50)
