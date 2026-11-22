/* Area m1, file 353: enemy leap-back then slam sequence. Names inferred. */
#include <stdint.h>

typedef struct M1St353 { uint8_t unk000[0x0C]; uint32_t f0C; uint8_t unk010[0x164 - 0x10]; float f164, f168, f16C, f170; uint8_t unk174[0x188 - 0x174]; float f188; } M1St353;
typedef struct M1Ai353 {
    uint8_t unk000[0x4C]; uint32_t f4C; uint8_t unk050[0x58 - 0x50]; int32_t n58; uint8_t unk05C[0x64 - 0x5C]; int32_t pose64;
    uint8_t unk068[0x74 - 0x68]; float f74; uint8_t unk078[0x278 - 0x78]; M1St353 *s278;
} M1Ai353;
typedef struct M1Ob353 { uint8_t unk000[0x30]; void *anim30; uint8_t unk034[0x60 - 0x34]; float p60[4]; uint8_t unk070[0x128 - 0x70]; uint8_t b128; } M1Ob353;
typedef struct M1Kc353 { uint8_t unk00[0x10]; float f10, f14, f18, f1c; } M1Kc353;
extern float m1_frameTime42C858, m1_frameRate42C85C;
extern uint8_t *g_playerObj;
int      sub_000833E0(void *a);
int      m1_AiSetState1456E0(void *o, void *e, int st, int f);
void     sub_0001D4E0(void *o);
float    sub_001B2770(const void *a, const void *b);   /* distance */
void     sub_00147710(void *e, int k, float a, float b, float c, int d);   /* regargs: e=ECX k=EAX */
void     sub_00147710b(void *e, int k, int a, int b, int c, int d);        /* same function */
void     sub_00113480(void *e, int k);
void     sub_000494D0(int id, void *pos, int k);
M1Kc353 *m1_Quest113400(void *e, int v);
void     sub_00131310(int next);                      /* regargs: o=EBX e=EDI */
void     sub_00131310b(int next);                     /* alias of 0x131310 */

/* 0x132DA0: leap back from the player (farther leaps when farther away), keep the pose
   until the rise ends, land (state 0x16 on flag 0x100), slam (pose 0x2C, effect 0x149, a
   3-unit stun, wait 2 or 3), recover (pose 0x2D with the 2-unit effect) and finish into
   state 0xF (flag 0x100) or 5. */
void m1_AiLeapSlam132DA0(M1Ob353 *o, M1Ai353 *e) {
    M1St353 *s = e->s278;
    M1St353 *t;
    M1Kc353 *c;
    float d, side, back;
    switch (e->n58) {
    case 0:
        if (!sub_000833E0(o->anim30))
            return;
        e->n58++;
        return;
    case 1:
        if (m1_AiSetState1456E0(o, e, 0x26, 0) == 1)
            sub_0001D4E0(o);
        d = sub_001B2770(o->p60, g_playerObj + 0x60);
        if (20.0f >= d) {
            side = m1_frameRate42C85C * -80.0f;
            back = m1_frameRate42C85C * 40.0f;
        } else if (40.0f >= d) {
            side = m1_frameRate42C85C * -100.0f;
            back = m1_frameRate42C85C * 60.0f;
        } else {
            side = m1_frameRate42C85C * -120.0f;
            back = m1_frameRate42C85C * 80.0f;
        }
        t = e->s278;
        t->f16C = 0.0f - back;
        t->f168 = side;
        t->f164 = 0.0f;
        t->f170 = 1.0f;
        sub_00147710(e, 1, 0.0872664675f, -0.0872664675f, m1_frameTime42C858 * 0.0698131695f, 0);
        s->f0C |= 0x10000;
        e->n58++;
        return;
    case 2:
        if (e->pose64 == 0x26 && s->f168 >= 0.0f) {
            if (m1_AiSetState1456E0(o, e, 0x27, 0) == 1)
                sub_0001D4E0(o);
            sub_00113480(e, 1);
            sub_00147710b(e, 2, 0, 0, 0, 0);
        }
        s->f164 = (1.0f - m1_frameTime42C858 * 0.02f) * s->f164;
        s->f16C = (1.0f - m1_frameTime42C858 * 0.02f) * s->f16C;
        if (e->f4C & 0x100) {
            sub_00131310(0x16);
            return;
        }
        if (o->b128 & 0x18)
            e->n58++;
        return;
    case 3:
        if (m1_AiSetState1456E0(o, e, 0x2C, 0) == 1)
            sub_0001D4E0(o);
        t = e->s278;
        t->f16C = 0.0f;
        t->f168 = 0.0f;
        t->f164 = 0.0f;
        t->f170 = 1.0f;
        sub_00113480(e, 1);
        sub_00113480(e, 2);
        e->f4C &= ~0x70u;
        sub_000494D0(0x149, o->p60, 0);
        s->f0C |= 0x1000000;
        s->f188 = 3.0f;
        e->f74 = (e->f4C & 0x100) ? 2.0f : 3.0f;
        s->f0C &= ~0x10000u;
        e->n58++;
        return;
    case 4:
        if (!(0.0f >= e->f74))
            return;
        e->n58 = 5;
        return;
    case 5:
        if (m1_AiSetState1456E0(o, e, 0x2D, 0) == 1)
            sub_0001D4E0(o);
        t = e->s278;
        t->f16C = 0.0f;
        t->f168 = 0.0f;
        t->f164 = 0.0f;
        t->f170 = 1.0f;
        e->f4C &= ~0x100u;
        c = m1_Quest113400(e, 2);
        c->f10 = 2.0f;
        c->f14 = 0.0f;
        c->f18 = 0.0f;
        c->f1c = 0.0f;
        e->n58++;
        return;
    case 6:
        if (!sub_000833E0(o->anim30))
            return;
        if (e->f4C & 0x100)
            sub_00131310(0xF);
        else
            sub_00131310b(5);
        return;
    }
}
