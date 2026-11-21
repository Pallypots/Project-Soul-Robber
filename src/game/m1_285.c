/* Area m1, file 285: pickup spawning. Names inferred. */
#include <stdint.h>

int32_t sub_000A81C0(void);                                   /* live pickup count */
void sub_000A8330(void *src, float *vel, int32_t tier);
void sub_000F5D40(float *d, const float *s);
void sub_000A8990(int32_t kind, int32_t life, int32_t mode, float *pos, float *vel, float *spin);

/* 0x000A8ED0: burst amount n out of src at pos as pickups, split into tiers (ones, tens, thirties, hundreds),
   one spawn per unit of each tier, 12 units below pos. Mode 0 uses kinds 0x18+tier, otherwise 0x47+tier.
   Nothing spawns while 48 or more pickups are live. */
void m1_SpawnPickupsA8ED0(int32_t n, float *pos, void *src, int32_t mode)
{
    int32_t cnt[4], i, k, r, kind, m;
    volatile int32_t life;   /* keeps the separate 8 / 12 stores instead of a branch-free select */
    volatile int32_t d100 = 100, d30 = 30, d10 = 10;   /* real idiv like the orig */
    float p[4], v[4], w[4];
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    p[0] = 0.0f; p[1] = 0.0f; p[2] = 0.0f; p[3] = 1.0f;
    w[0] = 0.0f; w[1] = 0.0f; w[2] = 0.0f; w[3] = 1.0f;
    i = 0;
    cnt[0] = 0;
    cnt[1] = 0;
    cnt[2] = 0;
    cnt[3] = 0;
    if (sub_000A81C0() >= 0x30) return;
    cnt[3] = n / d100;
    r = n % d100;
    cnt[2] = r / d30;
    r = r % d30;
    cnt[1] = r / d10;
    cnt[0] = r % d10;
    for (; i < 4; i++) {
        if (cnt[i] <= 0) continue;
        k = cnt[i];
        do {
            sub_000A8330(src, v, i);
            sub_000F5D40(p, pos);
            p[1] = p[1] - 12.0f;
            if (mode == 0) {
                kind = i + 0x18;
                life = 8;
                m = mode;
            } else {
                kind = i + 0x47;
                life = 0xC;
                m = 0;
            }
            sub_000A8990(kind, life, m, p, v, w);
        } while (--k);
    }
}
