/* Area m1, file 211: enemy effects. Names inferred. */
#include <stdint.h>

typedef struct M1DeS211 { uint8_t unk00[8]; int32_t i8; uint8_t unk0C[0x18]; float f24, f28, f2C, f30; } M1DeS211;
typedef struct M1DeE211 { uint8_t unk00[0x4C]; float f4C, f50, f54, f58; uint8_t unk5C[0x18]; M1DeS211 *st74; } M1DeE211;
typedef struct M1DeO211 { uint8_t unk00[0x10]; uint32_t i10; uint8_t unk14[0xC]; uint8_t *m20; uint8_t unk24[0x3C]; uint8_t pos60[0x10]; } M1DeO211;
void  aab_Hide1D700(void *o);
int   aab_Effect494D0(int id, void *pos, int arg);
void *sub_00035DD0(void *o, int a, int b, int c);
void  sub_00034E00(void *fx, void *pos, void *a, void *b);

/* 0x18B9C0: enemy defeat: hide it, clear its motion, play effect 0x11A and a burst at its position along its axes, then flag it gone. */
void m1_EnemyDefeat18B9C0(M1DeO211 *o, M1DeE211 *e) {
    M1DeS211 *s = e->st74; void *fx;
    aab_Hide1D700(o);
    s->f24 = 0.0f; s->f28 = 0.0f; s->f2C = 0.0f; s->f30 = 1.0f;
    e->f4C = 0.0f; e->f50 = 0.0f; e->f54 = 0.0f; e->f58 = 1.0f;
    aab_Effect494D0(0x11A, o->pos60, 0);
    fx = sub_00035DD0(o, s->i8, 3, 3);
    if (fx != 0) sub_00034E00(fx, o->pos60, o->m20 + 0x20, o->m20 + 0x10);
    o->i10 |= 0x10D;
}

typedef struct M1WdS211 { uint32_t i0; uint8_t unk04[0x1C]; float f20, f24, f28, f2C; uint8_t unk30[4]; float f34; uint8_t unk38[8]; int32_t i40; } M1WdS211;
typedef struct M1WdE211 { uint8_t unk00[0x5C]; float t5C; uint8_t unk60[0x14]; M1WdS211 *st74; } M1WdE211;
extern uint8_t *g_playerObj;
extern float m1_frameTime42C858;
extern float m1_frameRate42C85C;
int aab_Rand(void);

/* 0x16E4D0: start wandering: wait 120..240 frames, aim at the player's root bone, clear the move bits and stand still (speed 3). */
void m1_EnemyWander16E4D0(void *o, M1WdE211 *e) {
    M1WdS211 *s = e->st74, *t; uint32_t f;
    e->t5C = ((float)(aab_Rand() % 120) + 120.0f) / m1_frameTime42C858 * m1_frameRate42C85C;
    f = s->i0;
    s->f34 = 0.0f;
    s->i40 = *(int32_t *)(*(uint8_t **)(*(uint8_t **)(g_playerObj + 0x20) + 0xC4) + 0x374);
    s->i0 = (f & ~0x2C00u) | 0x1000;
    t = e->st74;
    f = t->i0;
    t->f24 = 0.0f; t->f2C = 0.0f; t->f20 = 0.0f; t->f28 = 3.0f;
    t->i0 = f | 0x1000;
}

typedef struct M1FgS211 { uint8_t b0; } M1FgS211;
typedef struct M1FgE211 { uint8_t unk00[0x54]; int32_t i54; uint8_t unk58[4]; float t5C; uint8_t unk60[0x14]; M1FgS211 *st74; } M1FgE211;
typedef struct M1FgO211 { uint8_t unk00[0x10]; uint32_t i10; } M1FgO211;
void sub_000ED780(void *o);
void sub_000D9AB0(int bit);

/* 0x16AD00: timed story flag: after 30 frames set story bit 0x92 (phase 2) or 0x91 (phase 3, when not flagged), then remove the object. */
void m1_StoryFlagTimer16AD00(M1FgO211 *o, M1FgE211 *e) {
    M1FgS211 *s = e->st74;
    switch (e->i54) {
    case 0:
        if (!(s->b0 & 2)) o->i10 |= 0x880;
        e->t5C = 30.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        e->i54++;
    case 1:
        if (0.0f > e->t5C) {
            if (s->b0 & 2) { sub_000D9AB0(0x92); e->i54++; }
            else { sub_000D9AB0(0x91); e->i54 += 2; }
        }
        return;
    case 2:
        sub_000ED780(o);
        return;
    }
}
