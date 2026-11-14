/* Area m1, file 169: player character reset (range revisit). Names inferred. */
#include <stdint.h>

typedef struct M1Ctx169 { uint8_t unk00[8]; int32_t kind08; } M1Ctx169;
typedef struct M1Sk169 { uint8_t unk00[4]; uint32_t f4; uint8_t unk08[8]; uint32_t f10; } M1Sk169;
typedef struct M1Pl169 {
    uint8_t unk00[0x6C]; int32_t n6C; uint8_t unk70[0x1C]; M1Sk169 *o8C; uint8_t unk90[0x14];
    int16_t wA4; int16_t wA6; int16_t wA8; uint8_t unkAA[0x12]; int16_t wBC;
} M1Pl169;
M1Pl169 *sub_00100110(void);
M1Pl169 *sub_000FBAF0(void);
M1Pl169 *sub_000FE3D0(void);
void sub_0001D610(M1Sk169 *s);
void m1_PlFlag0FE540(int k);
void m1_PlIdleA0FE3E0(void);
void m1_PlIdleB100120(void);
void m1_PlIdleC0FBB00(void);
void m1_PlCarry0F6FE0(void);

/* 0xF8860: reset the active character after a hit: clear attack flags, pick its idle (or carry) pose. */
void m1_PlReset0F8860(M1Ctx169 *c) {
    M1Pl169 *p; volatile int k;
    if (c != 0 && c->kind08 != 3) {
        if (c->kind08 == 4) p = sub_00100110();
        else if (c->kind08 == 5) p = sub_000FBAF0();
        else p = sub_000FE3D0();
    } else p = sub_000FE3D0();
    if (p->wBC == 0) return;
    if (c->kind08 == 3) {
        k = p->n6C;
        if (k >= 0x22 && k <= 0x29 && (p->o8C->f4 & 0x10000)) sub_0001D610(p->o8C);
        m1_PlFlag0FE540(0);
    }
    p->wA6 = 0;
    if (p->wA8 == 0) {
        if (c->kind08 == 3) m1_PlIdleA0FE3E0();
        else if (c->kind08 == 4) m1_PlIdleB100120();
        else if (c->kind08 == 5) m1_PlIdleC0FBB00();
    } else m1_PlCarry0F6FE0();
    p->wA4 = 0;
    p->o8C->f10 &= ~0x44u;
    p->o8C->f10 |= 0x220;
}

typedef struct M1Pl169b { uint8_t unk00[0x70]; int32_t n70; uint8_t unk74[0x7C]; float vF0[4]; int32_t i100; uint8_t unk104[0xC]; int32_t i110[2]; } M1Pl169b;
extern float m1_frameRate42C85C;
void m1_PlPose0F0B10(int k);
void sub_000F3B00(void *p, int k);

/* 0xF2400: stop the character's motion and return it to its stand pose unless it is already in a stand state. */
void m1_PlStop0F2400(void *p, M1Pl169b *o) {
    int32_t *q; volatile int k;
    if (o == 0) for (;;) ;
    o->vF0[0] = m1_frameRate42C85C * 0.0f;
    o->vF0[1] = m1_frameRate42C85C * 0.0f;
    o->vF0[2] = m1_frameRate42C85C * 0.0f;
    o->vF0[3] = m1_frameRate42C85C * 0.0f;
    { int32_t *volatile qq = o->i110; q = qq; }
    q[0] = 0; q[1] = 0;
    k = o->n70;
    if (!(k >= 0x1B && k <= 0x1D) && k != 0x1F) m1_PlPose0F0B10(3);
    sub_000F3B00(p, 1);
    o->i100 = 1;
}

typedef int (*M1Filt169)(int a, int b);
typedef struct M1Ent169 { uint8_t unk00[4]; int32_t x4; int32_t x8; } M1Ent169;
typedef struct M1Nd169 { struct M1Nd169 *next0; uint8_t unk04[8]; M1Ent169 *xC; } M1Nd169;
extern M1Filt169 m1_filtTbl3189C0[3];
extern M1Filt169 m1_filtFn3189CC;
extern M1Nd169 *m1_filtList3F5DC4;
extern M1Nd169 *m1_filtNext3F60E4;

/* 0xEDB10: start a filtered walk of the entity list (filter 0..2); returns the first match and remembers the next node. */
M1Ent169 *m1_FiltFirst0EDB10(int kind) {
    M1Nd169 *n; volatile int k = kind;
    if (k < 0 || k >= 3) {
        m1_filtNext3F60E4 = 0;
        m1_filtFn3189CC = m1_filtTbl3189C0[0];
        return 0;
    }
    *(M1Filt169 volatile *)&m1_filtFn3189CC = m1_filtTbl3189C0[kind];
    for (n = m1_filtList3F5DC4; n != 0; n = n->next0)
        if (m1_filtFn3189CC(n->xC->x4, n->xC->x8) != 0) { m1_filtNext3F60E4 = n->next0; return n->xC; }
    m1_filtNext3F60E4 = 0;
    return 0;
}

extern int32_t m1_worldA41316C;
extern int32_t m1_worldB413170;
extern int32_t m1_hudMode3ED760;
int m1_HudPick0324A0(int k);

/* 0xA9EB0: in world 7 pick the HUD layout (rooms 0..7 use layout 0, others 1); hangs outside world 7. */
void m1_HudLayout0A9EB0(void) {
    volatile int k;
    if (m1_worldA41316C != 7) for (;;) ;
    k = m1_worldB413170;
    if (k >= 0 && k <= 7) { m1_hudMode3ED760 = m1_HudPick0324A0(0); return; }
    m1_hudMode3ED760 = m1_HudPick0324A0(1);
}

typedef struct M1Rm169 { int32_t world; int32_t room; int32_t file; int32_t sub; } M1Rm169;
extern M1Rm169 m1_rooms2C5AA0[25];
extern int32_t m1_roomCur413164;
extern int32_t m1_font413174;
extern int32_t m1_roomPrev3DF9BC;
int  sub_000D9A70(int id);
void m1_RoomLoad0DDEF0(int file, int sub);

/* 0x40950: enter room n (1..24): set the world/room globals and load it (room 9 picks its variant by flag 0x57). */
void m1_RoomEnter040950(int n) {
    volatile int k = n; M1Rm169 *e;
    if (k < 1 || k > 0x18) for (;;) ;
    e = &m1_rooms2C5AA0[n];
    m1_worldA41316C = e->world;
    m1_roomCur413164 = n;
    m1_worldB413170 = e->room;
    m1_font413174 = 0;
    m1_roomPrev3DF9BC = n;
    if (n != 9) { m1_RoomLoad0DDEF0(e->file, e->sub); return; }
    m1_RoomLoad0DDEF0(m1_rooms2C5AA0[9].file, (sub_000D9A70(0x57) != 0) + 1);
}
