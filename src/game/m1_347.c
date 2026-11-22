/* Area m1, file 347: enemy idle decision (approach, close attack or keep distance). Names inferred. */
#include <stdint.h>

typedef struct M1St347 { uint8_t unk00[4]; uint8_t b04; uint8_t unk05[0x1C - 5]; float f1C; } M1St347;
typedef struct M1Ai347 {
    uint8_t unk000[0x20]; uint8_t b20; uint8_t unk021[0x74 - 0x21]; float f74;
    uint8_t unk078[0xFC - 0x78]; float fFC; float f100; uint8_t unk104[0x278 - 0x104]; M1St347 *s278;
} M1Ai347;
typedef int (*M1Fn347)(void *o, M1Ai347 *e, const void *t);
extern M1Fn347 m1_chkFn31D0B8;
extern const uint8_t m1_chkTbl2797C8[];
extern float m1_frameTime42C858, m1_frameRate42C85C;
extern float m1_g3F7504;
void  sub_00113C60(float *v, float a, float b);
float sub_001A3F30(float x);                           /* fabs */
int   sub_00140040(int a, void *e, void *o);           /* regargs: a=EAX e=EDX, o on stack */
int   sub_001401C0(void);                              /* regargs */
int   sub_001C7EE1(void);                              /* rand */
void  sub_00113480(void *e, int k);
int   m1_AiGoto113040(void *o, void *e, int st);

/* 0x141BC0: idle decision. A table check sends it to 0x2A; otherwise the glow fades and,
   once the +0x74 wait is over, by the target's distance and angle: with flag 0x10 or a
   ready attack go to 0x14; with the guard bit pick 0x14 (a free attack slot, cooldown over,
   half the time), 0x2A (closer than 20), 0x2D (within 40 and 40 degrees), 0x2C (70 or
   more) or wait another 30 units; without it 0x14 (in front, fewer than 6 attackers,
   cooldown over) or 0x2A. */
void m1_AiIdle141BC0(void *o, M1Ai347 *e) {
    M1St347 *s = e->s278;
    float d, a;
    int k;
    if (m1_chkFn31D0B8(o, e, m1_chkTbl2797C8)) {
        k = 0x2A;
        goto go;
    }
    sub_00113C60(&s->f1C, m1_frameTime42C858 * 0.002f, 1.0f);
    if (!(0.0f >= e->f74))
        return;
    d = e->f100;
    a = sub_001A3F30(e->fFC);
    if (s->b04 & 0x10) {
        k = 0x14;
        goto go;
    }
    if (e->b20 & 1) {
        if (sub_00140040(4, e, o)) {
            k = 0x14;
            goto go;
        }
        if (0.698131740f >= a && sub_001401C0() < 6 && 0.0f >= m1_g3F7504 && sub_001C7EE1() % 2 < 1) {
            k = 0x14;
            goto go;
        }
        if (20.0f > d) {
            k = 0x2A;
            goto go;
        }
        if (40.0f > d && 0.698131740f >= a) {
            k = 0x2D;
            goto go;
        }
        if (d >= 70.0f) {
            k = 0x2C;
            goto go;
        }
        e->f74 = 30.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        return;
    }
    if (0.698131740f >= a && sub_001401C0() < 6 && 0.0f >= m1_g3F7504)
        k = 0x14;
    else
        k = 0x2A;
go:
    sub_00113480(e, 0xA);
    m1_AiGoto113040(o, e, k);
}
