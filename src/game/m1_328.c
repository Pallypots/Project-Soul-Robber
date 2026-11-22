/* Area m1, file 328: enemy hit handler with knockback. Names inferred. */
#include <stdint.h>

typedef struct M1Hit328 { int32_t kind00; uint8_t unk04[4]; int32_t i08; float f0C; uint8_t unk10[0x10]; float v20[4]; } M1Hit328;
typedef struct M1En328 {
    uint8_t unk000[0x50]; int32_t i50; uint8_t unk054[0x78 - 0x54];
    float   v78[3]; int32_t i84; float v88[4];
    uint8_t unk098[0x274 - 0x98]; float f274;
} M1En328;
typedef struct M1Fx328 { uint8_t unk00[0x10]; float f10; } M1Fx328;
extern float m1_frameTime42C858, m1_frameRate42C85C;
void     sub_001ADB60(float *d, const float *s, float k);   /* d = s * k */
void     sub_000F5D40(void *d, const void *s);
void     sub_00036750(void *o, int k);
void     sub_000494D0(int id, void *pos, int k);
int      m1_AiGoto113040(void *o, void *e, int st);
M1Fx328 *sub_001133E0(void *e, int k);
M1Fx328 *m1_Quest113430(void *e, int k);

/* 0x17ABE0: handle a hit on enemy e: pick the reaction (knockback for most kinds, stun,
   grab, special states), take the damage from +0x274 and enter the reaction state when
   the health runs out, otherwise the secondary state; on a normal hit start the 5-unit
   flash. Returns 1 for a normal hit, -1 for a special one, 0 for kinds it ignores.
   Stack args (o e hit). */
int m1_HitReact17ABE0(void *o, M1En328 *e, M1Hit328 *hit) {
    float v[4];
    int st = -1;
    int st2 = -1;
    int res = 1;
    M1Fx328 *f;
    switch (hit->kind00) {
    case 1: case 2: case 3: case 5: case 6: case 7: case 8: case 9: case 10: case 11:
    case 32: case 34: case 35:
        sub_001ADB60(v, hit->v20, 50.0f);
        e->v78[0] = e->v78[0] + v[0];
        e->v78[1] = e->v78[1] + v[1];
        e->v78[2] = e->v78[2] + v[2];
        *(volatile int32_t *)&e->i84 = *(volatile int32_t *)&e->i84;
        if (hit->kind00 == 0x23 || (hit->kind00 == 5 && hit->i08))
            st = 10;
        else
            st = 9;
        break;
    case 12:
        st = 9;
        if (e->i50 == 8)
            e->f274 = 0.0f;
        break;
    case 13:
        st = 9;
        sub_00036750(o, 4);
        sub_000494D0(0x77, (uint8_t *)o + 0x60, 0);
        break;
    case 14: case 15:
        st2 = 7;
        res = st;
        break;
    case 16: case 17:
        res = st;
        break;
    case 26: case 28:
        st2 = 3;
        res = st;
        break;
    case 42:
        st2 = 8;
        res = st;
        sub_000F5D40(e->v88, hit->v20);
        break;
    default:
        return 0;
    }
    e->f274 = e->f274 - hit->f0C;
    if (0.0f >= e->f274 && st >= 0) {
        sub_000F5D40(e->v88, hit->v20);
        m1_AiGoto113040(o, e, st);
        return res;
    }
    if (st2 >= 0)
        m1_AiGoto113040(o, e, st2);
    if (res > 0) {
        f = sub_001133E0(e, 1);
        if (!f)
            f = m1_Quest113430(e, 1);
        f->f10 = 5.0f / m1_frameTime42C858 * m1_frameRate42C85C;
    }
    return res;
}
