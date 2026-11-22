/* Area m1, file 331: distance-range condition check. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Cond331 { int32_t kind00; uint8_t unk04[0x0C]; float min10; float max14; } M1Cond331;
typedef struct M1St331 { uint8_t unk00[4]; uint8_t *tgt04; } M1St331;
typedef struct M1En331 { uint8_t unk000[0x278]; M1St331 *s278; } M1En331;
extern uint8_t *g_playerObj;
float sub_001B2770(const void *a, const void *b);   /* distance */

/* 0x1861F0: 1 when the chosen target (1 player, 3 the enemy's own target, 4 the object
   itself; kinds 2 and 5 never pass) lies between the condition's min and max distance
   from o. Any other kind hangs. Stack args (o e c). */
int m1_CondInRange1861F0(uint8_t *o, M1En331 *e, M1Cond331 *c) {
    uint8_t *t;
    float d;
    switch (c->kind00) {
    case 1:
        t = g_playerObj;
        break;
    case 3:
        t = e->s278->tgt04;
        break;
    case 4:
        t = o;
        break;
    case 2:
    case 5:
        return 0;
    default:
        for (;;);
    }
    if (!t)
        return 0;
    d = sub_001B2770(o + 0x60, t + 0x60);
    if (!_mm_comige_ss(_mm_set_ss(d), _mm_load_ss(&c->min10)))
        return 0;
    if (!_mm_comige_ss(_mm_load_ss(&c->max14), _mm_set_ss(d)))
        return 0;
    return 1;
}
