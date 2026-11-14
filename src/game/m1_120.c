/* Area m1, file 120: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Obj120 { uint8_t unk000[0xF0]; float vF0[4]; uint8_t unk100[0x110 - 0x100]; int32_t a110; int32_t a114; } M1Obj120;
extern float m1_frameRate42C85C;

/* 0x000F1E80: zero the +0xF0 velocity (scaled by frameRate) and the +0x110 pair; hangs
 * without an object. */
void m1_ZeroVel0F1E80(void *a, M1Obj120 *o)
{
    int32_t *p;
    if (o == 0)
        for (;;) ;
    o->vF0[0] = m1_frameRate42C85C * 0.0f;
    o->vF0[1] = m1_frameRate42C85C * 0.0f;
    o->vF0[2] = m1_frameRate42C85C * 0.0f;
    o->vF0[3] = m1_frameRate42C85C * 0.0f;
    p = &o->a110;
    p[0] = 0;
    p[1] = 0;
}

extern uint8_t ***m1_lists3E6050;

/* 0x0005ED30: insert an entry at idx (0..99) of list (t, flag): shift the run of live
 * entries (byte 1 not negative) up by one and write (flag ? 1 : 0x40, 1). Returns 0 when
 * idx is out of range. */
int m1_ListInsert05ED30(int t, unsigned int idx, int flag)
{
    uint8_t *p;
    uint8_t *c;
    int n;
    if (idx > 0x63)
        return 0;
    p = m1_lists3E6050[t][flag] + idx * 2;
    n = 1;
    c = p;
    if ((int8_t)p[1] >= 0) {
        int8_t b;
        do {
            b = (int8_t)c[3];
            c += 2;
            n++;
        } while (b >= 0);
    }
    for (; n > 0; n--) {
        *(uint16_t *)(c + 2) = *(uint16_t *)c;
        c -= 2;
    }
    p[1] = 1;
    if (flag) {
        p[0] = 1;
        return 1;
    }
    p[0] = 0x40;
    return 1;
}
