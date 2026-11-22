/* Area m1, file 350: enemy knocked into the air, landing and recovery. Names inferred. */
#include <stdint.h>

typedef struct M1St350 { uint8_t unk00[4]; uint32_t f04; uint8_t unk08[0x2C - 8]; float v2C[4]; uint8_t unk3C[0x48 - 0x3C]; float f48; } M1St350;
typedef struct M1Ai350 { uint8_t unk000[0x58]; int32_t n58; uint8_t unk05C[0x64 - 0x5C]; int32_t pose64; uint8_t unk068[0x278 - 0x68]; M1St350 *s278; } M1Ai350;
typedef struct M1Ob350 { uint8_t unk000[0x10]; uint32_t f10; uint8_t unk014[0x30 - 0x14]; void *anim30; uint8_t unk034[0x128 - 0x34]; uint8_t b128; } M1Ob350;
extern float m1_frameTime42C858;
int  sub_001154D0(M1Ai350 *a, M1Ob350 *o);            /* regargs: a=EAX */
void sub_00117580(void *o, int st);
int  sub_000833E0(void *a);
int  m1_AiSetState1456E0(void *o, void *e, int st, int f);
void sub_0001D4E0(void *o);

/* 0x119050: launched: once past step 5 a ready counter (unless flag 0x10) ends it in state 9.
   Steps: wait, enter the flight pose (0x35 after 0x34, 0x39 after 0x38; others hang), wait
   for ground contact (clearing the airborne flags), the landing pose (0x36 / 0x3A), wait,
   the get-up pose (0x37 / 0x3B), wait, then finish into 0x23 (flag 0x10), 9 (counter ready,
   with a 0.3 delay) or 1. While airborne the side speeds decay by 5 percent per unit. */
void m1_AiLaunched119050(M1Ob350 *o, M1Ai350 *e) {
    M1St350 *s = e->s278;
    M1St350 *t;
    int r;
    if (!(s->f04 & 0x10) && e->n58 >= 5 && sub_001154D0(e, o))
        goto counter;
    switch (e->n58) {
    case 0:
        if (!sub_000833E0(o->anim30))
            break;
        e->n58++;
    case 1:
        if (e->pose64 == 0x34)
            r = m1_AiSetState1456E0(o, e, 0x35, 0);
        else if (e->pose64 == 0x38)
            r = m1_AiSetState1456E0(o, e, 0x39, 0);
        else
            for (;;);
        if (r == 1)
            sub_0001D4E0(o);
        e->n58++;
    case 2:
        if (o->b128 & 0x18) {
            o->f10 &= ~0x10u;
            s->f04 &= ~0x4000u;
            e->n58++;
        }
        break;
    case 3:
        if (e->pose64 == 0x35)
            r = m1_AiSetState1456E0(o, e, 0x36, 0);
        else if (e->pose64 == 0x39)
            r = m1_AiSetState1456E0(o, e, 0x3A, 0);
        else
            for (;;);
        if (r == 1)
            sub_0001D4E0(o);
        t = e->s278;
        t->v2C[2] = 0.0f;
        t->v2C[1] = 0.0f;
        t->v2C[0] = 0.0f;
        t->v2C[3] = 1.0f;
        e->n58++;
        break;
    case 4:
        if (!sub_000833E0(o->anim30))
            break;
        e->n58++;
    case 5:
        if (e->pose64 == 0x36)
            r = m1_AiSetState1456E0(o, e, 0x37, 0);
        else if (e->pose64 == 0x3A)
            r = m1_AiSetState1456E0(o, e, 0x3B, 0);
        else
            for (;;);
        if (r == 1)
            sub_0001D4E0(o);
        t = e->s278;
        t->v2C[2] = 0.0f;
        t->v2C[1] = 0.0f;
        t->v2C[0] = 0.0f;
        t->v2C[3] = 1.0f;
        o->f10 |= 4;
        e->n58++;
        break;
    case 6:
        if (!sub_000833E0(o->anim30))
            break;
        e->n58++;
    case 7:
        if (s->f04 & 0x10) {
            sub_00117580(o, 0x23);
            return;
        }
        if (sub_001154D0(e, o)) {
        counter:
            s->f48 = 0.3f;
            sub_00117580(o, 9);
            return;
        }
        sub_00117580(o, 1);
        return;
    }
    if (e->n58 <= 2) {
        s->v2C[0] = (1.0f - m1_frameTime42C858 * 0.05f) * s->v2C[0];
        s->v2C[2] = (1.0f - m1_frameTime42C858 * 0.05f) * s->v2C[2];
    }
}

typedef struct M1St350b { uint8_t unk000[0x0C]; uint32_t f0C; uint8_t unk010[0x164 - 0x10]; float f164, f168, f16C, f170; } M1St350b;
typedef struct M1Ai350b { uint8_t unk000[0x58]; int32_t n58; uint8_t unk05C[0x278 - 0x5C]; M1St350b *s278; } M1Ai350b;
extern float m1_frameRate42C85C;
void sub_00131310(int next);                          /* regargs: o=EBX e=EDI */
void sub_00131310b(int next);                         /* alias of 0x131310 */

/* 0x132890: thrown backwards: wait, pose 0x39 flying back at 10/s, wait, pose 0x3A sliding
   back at 30/s, wait, pose 0x3B, wait, then finish into state 3 (flag 1) or 5. While in the
   first steps the slide speeds decay by 2 percent per unit. */
void m1_AiThrownBack132890(M1Ob350 *o, M1Ai350b *e) {
    M1St350b *s = e->s278;
    M1St350b *t;
    switch (e->n58) {
    case 0:
        if (!sub_000833E0(o->anim30))
            break;
        e->n58++;
    case 1:
        if (m1_AiSetState1456E0(o, e, 0x39, 0) == 1)
            sub_0001D4E0(o);
        t = e->s278;
        t->f168 = 0.0f;
        t->f164 = 0.0f;
        t->f170 = 1.0f;
        t->f16C = 0.0f - m1_frameRate42C85C * 10.0f;
        e->n58++;
        break;
    case 2:
        if (sub_000833E0(o->anim30))
            e->n58++;
        break;
    case 3:
        if (m1_AiSetState1456E0(o, e, 0x3A, 0) == 1)
            sub_0001D4E0(o);
        t = e->s278;
        t->f168 = 0.0f;
        t->f164 = 0.0f;
        t->f16C = 0.0f - m1_frameRate42C85C * 30.0f;
        t->f170 = 1.0f;
        e->n58++;
        break;
    case 4:
        if (!sub_000833E0(o->anim30))
            break;
        e->n58++;
    case 5:
        if (m1_AiSetState1456E0(o, e, 0x3B, 0) == 1)
            sub_0001D4E0(o);
        t = e->s278;
        t->f16C = 0.0f;
        t->f168 = 0.0f;
        t->f164 = 0.0f;
        t->f170 = 1.0f;
        e->n58++;
        break;
    case 6:
        if (!sub_000833E0(o->anim30))
            break;
        e->n58++;
    case 7:
        if (s->f0C & 1)
            sub_00131310(3);
        else
            sub_00131310b(5);   /* alias keeps the two calls apart */
        return;
    }
    if (e->n58 <= 4) {
        s->f164 = (1.0f - m1_frameTime42C858 * 0.02f) * s->f164;
        s->f16C = (1.0f - m1_frameTime42C858 * 0.02f) * s->f16C;
    }
}
