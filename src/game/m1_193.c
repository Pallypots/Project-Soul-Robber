/* Area m1, file 193: player turn and table helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Pl193 { uint8_t unk00[0x54]; float yaw54; } M1Pl193;
typedef struct M1PlE193 { uint8_t unk00[0xA4]; float turnA4; uint8_t unkA8[0x48]; float velF0[4]; uint8_t unk100[0x10]; int32_t i110, i114; } M1PlE193;
extern float m1_frameRate42C85C;

/* Twin bodies: stop movement, then turn by the pending amount plus a fixed step and set the next pending turn. */
#define M1_TURN193(name, step, next) \
void name(M1Pl193 *o, M1PlE193 *e) { \
    int32_t *z; \
    if (e == 0) for (;;) ; \
    e->velF0[0] = m1_frameRate42C85C * 0.0f; \
    e->velF0[1] = m1_frameRate42C85C * 0.0f; \
    e->velF0[2] = m1_frameRate42C85C * 0.0f; \
    e->velF0[3] = m1_frameRate42C85C * 0.0f; \
    { int32_t *volatile zv = &e->i110; z = zv; } \
    z[0] = 0; z[1] = 0; \
    o->yaw54 -= e->turnA4 + (step); \
    e->turnA4 = (next); \
}

/* 0xF0BE0: quarter turn (pi/2), next pending -pi/2. */
M1_TURN193(m1_TurnQuarter0F0BE0, 1.57079637f, -1.57079637f)
/* 0xF1DE0: half turn (pi), next pending -pi. */
M1_TURN193(m1_TurnHalf0F1DE0, 3.14159274f, -3.14159274f)

typedef struct M1Rng193 { float lo0, hi4; int32_t id8; } M1Rng193;
typedef struct M1Zn193 { uint8_t unk00[0x128]; uint32_t i128; uint8_t unk12C[4]; float pos130; uint8_t unk134[0x1C]; uint32_t flags150; uint8_t unk154[0x10]; int32_t zone164; uint8_t unk168[0x50]; void *p1B8; } M1Zn193;
extern M1Rng193 *m1_zoneTbl2E6C40[];

/* 0xC4600: update an object's zone: look up its area's range record and set flag 0x400 while its position is inside [lo, hi) (hi < 0 means open-ended). */
void m1_ZoneUpdate0C4600(M1Zn193 *o) {
    uint32_t k = o->i128 & 0xFF; uint32_t f; M1Rng193 *r;
    if (k >= 0x90 || ((f = o->flags150) & 0x82000)) {
        o->flags150 &= ~0x400u; o->zone164 = -1; return;
    }
    if (o->p1B8 != 0) return;
    r = m1_zoneTbl2E6C40[k];
    if (0.0f > r->lo0 || o->pos130 < r->lo0) goto off;
    if (0.0f > r->hi4 || r->hi4 > o->pos130) { o->flags150 = f | 0x400; o->zone164 = r->id8; return; }
off:
    o->flags150 = f & ~0x400u; o->zone164 = r->id8;
}

typedef struct M1Wh193 { uint8_t unk00[4]; int32_t kind4; } M1Wh193;
typedef struct M1Gr193 { uint32_t flags0; uint8_t unk04[0x128]; M1Wh193 *slots12C[8]; } M1Gr193;
extern uint8_t abc_player[];
void PlayerObj_ClearFlags(void *p, uint32_t f, int k);

/* 0xA22C0: release a grab slot: advance the grab phase flags, then clear the slot holding who (for the player, only once released and after dropping its held flags). */
void m1_GrabRelease0A22C0(M1Gr193 *o, M1Wh193 *who) {
    uint32_t f = o->flags0; short i;
    if (f & 4) return;
    if (f & 0x20000) f = (f & ~2u) | 0x40000; else f |= 0x20000;
    o->flags0 = f;
    for (i = 0; i < 8; i++)
        if (o->slots12C[i] == who) break;
    if (i >= 8) return;
    if (who->kind4 == 1) {
        if (!(o->flags0 & 0x40000)) return;
        PlayerObj_ClearFlags(abc_player, 0x800000, 0);
        PlayerObj_ClearFlags(abc_player, 0x80, 0);
        o->slots12C[i] = 0;
        return;
    }
    o->slots12C[i] = 0;
}

typedef struct M1OrT193 { uint8_t unk00[0x128]; uint8_t b128; } M1OrT193;
typedef struct M1Orb193 { uint32_t flags0; uint8_t unk04[0x3C]; int32_t i40; uint8_t unk44[0x40]; float ang84; uint8_t unk88[0x98]; M1OrT193 *t120; } M1Orb193;
extern float m1_frameTime42C858;
extern uint8_t *g_playerObj;
void  m1_LockMark0C56B0(M1OrT193 *t);
void  m1_WrapAngleA35B0(float *a);
int   sub_000A33E0(M1Orb193 *o);
float sub_000A2EF0(M1Orb193 *o, void *p);
void  sub_000A41D0(M1Orb193 *o, int k);

/* 0x94440: orbiting pickup: spin 10 degrees per frame, and despawn (0xA41D0) when it hits something, or when its owner is idle and the player is over 1000 away. */
void m1_OrbitTick094440(M1Orb193 *o) {
    M1OrT193 *t; int hit;
    if (o->i40 != 0) return;
    t = o->t120;
    m1_LockMark0C56B0(t);
    o->ang84 += m1_frameTime42C858 * 0.174532935f;
    m1_WrapAngleA35B0(&o->ang84);
    hit = 0;
    if (sub_000A33E0(o)) hit = 1;
    if (!(t->b128 & 0x1E) && !(sub_000A2EF0(o, g_playerObj) > 1000.0f) && !hit) return;
    sub_000A41D0(o, 1);
    o->flags0 &= ~0x10u;
}
