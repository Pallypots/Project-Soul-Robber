/* Area m1, file 349: enemy jump-down landing sequence. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1St349 {
    uint8_t unk00[0x18]; uint32_t f18; uint8_t unk1C[4]; float f20, f24, f28, f2C;
    uint8_t unk30[0x8C - 0x30]; float f8C; float f90;
} M1St349;
typedef struct M1Ai349 { uint8_t unk000[0x20]; uint8_t b20; uint8_t unk021[0x58 - 0x21]; int32_t n58; uint8_t unk05C[0x278 - 0x5C]; M1St349 *s278; } M1Ai349;
typedef struct M1Ob349 { uint8_t unk000[0x30]; void *anim30; uint8_t unk034[0x60 - 0x34]; float p60[4]; uint8_t unk070[0x128 - 0x70]; uint8_t b128; } M1Ob349;
extern float m1_frameTime42C858, m1_frameRate42C85C;
void sub_00147710(void *e, int k, float a, int b, float c, float d);   /* regargs: e=ECX k=EAX */
void sub_00113480(void *e, int k);
int  m1_AiSetState1456E0(void *o, void *e, int st, int f);
void sub_000494D0(int id, void *pos, int k);
int  sub_000833E0(void *a);
void sub_00186470(void *o, void *e, int st);   /* regargs: o=EBX e=EDI */
void sub_00186470b(void *o, void *e, int st);  /* alias: keeps the second 0xA exit apart */

/* 0x188440: jump down. Steps 0/1 advance; step 2 starts the leap (stronger with the guard
   bit; flag 0x2000 adds the spin) and goes to step 0xA; step 0xA falls (speeds decay by 2
   percent per unit) until ground contact, then step 0xB lands (pose 6 with a bounce, or
   pose 5) with the landing effect; step 0xC on the animation end picks the next state. */
void m1_AiJumpDown188440(M1Ob349 *o, M1Ai349 *e) {
    M1St349 *s = e->s278;
    M1St349 *t;
    float f;
    uint32_t g;
    switch (e->n58) {
    case 0:
    case 1:
        e->n58++;
        return;
    case 2:
        if (e->b20 & 1) {
            f = 1.0f;
            if (!(s->f18 & 0x2000))
                f = 0.0f;
            sub_00147710(e, 2, 5.0f, 0, 1.0f, f);
        } else {
            f = 1.0f;
            if (!(s->f18 & 0x2000))
                f = 0.0f;
            sub_00147710(e, 2, 4.0f, 0, 1.0f, f);
        }
        e->n58 = 0xA;
        return;
    case 0xA:
        if (!(o->b128 & 0x18)) {
            s->f20 = (1.0f - m1_frameTime42C858 * 0.02f) * s->f20;
            s->f28 = (1.0f - m1_frameTime42C858 * 0.02f) * s->f28;
            return;
        }
        sub_00113480(e, 2);
        s->f18 &= ~0x800u;
        e->n58++;
    case 0xB:
        if (e->b20 & 1) {
            m1_AiSetState1456E0(o, e, 6, 0);
            _mm_store_ss(&s->f8C, _mm_set_ss(4.0f));   /* keeps the .rdata load */
            s->f90 = m1_frameRate42C85C * 50.0f;
        } else {
            m1_AiSetState1456E0(o, e, 5, 0);
        }
        t = e->s278;
        t->f28 = 0.0f;
        t->f24 = 0.0f;
        t->f20 = 0.0f;
        t->f2C = 1.0f;
        sub_000494D0(0x112, o->p60, 0);
        e->n58++;
    case 0xC:
        if (!sub_000833E0(o->anim30))
            return;
        g = s->f18;
        if (g & 0x2000) {
            if (g & 0x18000)
                sub_00186470(o, e, 0xA);
            else if (e->b20 & 1)
                sub_00186470(o, e, 7);
            else
                sub_00186470b(o, e, 0xA);
        } else if (e->b20 & 1) {
            sub_00186470(o, e, 2);
        } else {
            sub_00186470(o, e, 1);
        }
        return;
    }
}
