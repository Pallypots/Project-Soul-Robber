/* Area m1, group 323: second flyer spawn. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct { uint32_t f0; uint8_t _4[0x10]; float f14, f18; uint8_t _1c[0x10]; float v2c[4];
    uint8_t _3c[8]; void *o44; void *a48; } M1Gp323;
typedef struct {
    uint8_t _0[0x20]; uint32_t f20; uint8_t _24[4]; float f28, f2c; const void *t30;
    uint8_t _34[0x5C - 0x34]; float f5c; uint8_t _60[0x14]; M1Gp323 *flags74;
    uint8_t _78[0xB4 - 0x78]; const void *cbb4; uint8_t _b8[4]; const void *cbbc, *cbc0, *cbc4,
    *cbc8, *cbcc;
} M1Ga323;
typedef struct {
    uint8_t _0[0xC]; uint32_t fc, f10; uint8_t _14[0x4C]; float pos60[4]; float f70, f74, f78, f7c;
    uint8_t _80[0xA4 - 0x80]; float fa4; uint8_t _a8[8]; float fb0, fb4; uint8_t _b8[0xD0 - 0xB8];
    int32_t fd0; uint8_t _d4[0x14]; float fe8; int32_t fec, ff0, ff4; uint8_t _f8[0x10C - 0xF8];
    float f10c; uint8_t _110[8]; int32_t f118; uint8_t _11c[8]; int32_t f124;
} M1Go323;

extern float m1_frameTime42C858, m1_frameRate42C85C;
extern const uint8_t m1_fly2TabA31F0AC[], m1_fly2TabB31F07C[], m1_fly2Tab31F064[];
M1Gp323 *b16_Pool60Alloc(void);
void b16_WorkFree(void);
void sub_00167690(void);
void sub_001677F0(void);
void sub_00168FB0(void);
int32_t sub_0001BC40(M1Go323 *o);
void sub_000F5D40(float *d, const float *s);
void aab_Actor1F070(M1Go323 *o, int k);
void sub_0001EBF0(M1Go323 *o, int k);
int  sub_001C7EE1(void);                                    /* rand */
int  sub_000D9A70(int k);
void sub_001671D0(M1Go323 *o, M1Ga323 *a, int st);

/* 0x001693E0: spawn the second flyer type in mode k (0-6): take a work slot,
   install its handlers, set its body and motion limits, its reach by mode
   (160/150/100/120/150/990/100) and its home position; modes 0/3/4/5 start
   perched (and face the target), 1 and 2 wait 3-9 s (2 also flags it
   aggressive), 6 is a boss summon. Modes 0, 3, 4 and 5 also need their
   spawn slot (0x1C8 + bit index). Starts in state 1 (aggressive) or 5 with
   a random 420-900 unit lifetime. Returns 1 when spawned. */
int32_t m1_Flyer2Spawn1693E0(M1Go323 *o, M1Ga323 *a, int32_t k)
{
    float reach[7];
    uint32_t mask[7];
    M1Gp323 *p;
    uint32_t f, m;
    int32_t r, n, i;
    volatile int32_t st;

    reach[0] = 160.0f;
    reach[1] = 150.0f;
    reach[2] = 100.0f;
    reach[3] = 120.0f;
    reach[4] = 150.0f;
    reach[5] = 990.0f;
    reach[6] = 100.0f;
    if (k < 0) return 0;
    p = b16_Pool60Alloc();
    a->flags74 = p;
    if (p == 0) return 0;
    a->cbb4 = (const void *)b16_WorkFree;
    a->cbbc = (const void *)sub_00167690;
    a->cbc0 = (const void *)sub_001677F0;
    a->cbc4 = (const void *)sub_00168FB0;
    a->cbcc = m1_fly2TabB31F07C;
    a->cbc8 = m1_fly2TabA31F0AC;
    o->f70 = 1.0f; o->f74 = 1.0f; o->f78 = 1.0f; o->f7c = 1.0f;
    r = sub_0001BC40(o);
    o->fb0 = o->f70 * 3.0f;
    o->fa4 = o->fb0;
    o->fb4 = o->f70 * -6.0f;
    o->fe8 = o->f70 * 5.0f;
    o->fd0 = r;
    o->f10c = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(o->f70), _mm_set_ss(2.0f)));
    o->fec = 0;
    o->f118 = 0;
    o->f124 = 1;
    a->f28 = o->f70 * 0.0f;
    a->f2c = o->f70 * -7.0f;
    a->t30 = m1_fly2Tab31F064;
    o->fc = (o->fc & ~0x20u) | 0xC0;
    o->ff0 = 3;
    o->ff4 = 2;
    o->f10 |= 0x202;
    sub_000F5D40(p->v2c, o->pos60);
    p->f18 = reach[k];
    switch (k) {
    case 0: case 3: case 4: case 5:
        p->f0 |= 0x20;
        aab_Actor1F070(o, 1);
        sub_0001EBF0(o, 3);
        a->f20 |= 1;
        break;
    case 2:
        p->f0 |= 0x10;
    case 1:
        a->f5c = (float)(sub_001C7EE1() % 7 + 3) * m1_frameRate42C85C * 60.0f;
        break;
    case 6:
        p->f0 |= 0x20000040;
        o->f10 |= 0x101;
        break;
    }
    f = p->f0;
    mask[0] = 0x100000;
    mask[1] = 0;
    mask[2] = 0;
    mask[3] = 0x200000;
    mask[4] = 0x400000;
    mask[5] = 0x800000;
    mask[6] = 0;
    m = mask[k];
    f = (f & 0xFF0FFFFFu) | m;
    p->f0 = f;
    if (m != 0) {
        n = (f >> 20) & 0xF;
        i = 0;
        if (n) {
            while (!(n & 1)) {
                n >>= 1;
                i++;
                if (n == 0) break;
            }
        }
        if (!sub_000D9A70(i + 0x1C8)) {
            p->f0 &= ~1u;
            return 0;
        }
    }
    st = 5;
    if (p->f0 & 0x10) st = 1;
    sub_001671D0(o, a, st);
    p->f14 = ((float)(sub_001C7EE1() % 0x1E0) + 420.0f) / m1_frameTime42C858 * m1_frameRate42C85C;
    p->o44 = o;
    p->a48 = a;
    return 1;
}

