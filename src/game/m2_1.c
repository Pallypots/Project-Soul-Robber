/* Area m2, file 1. Names inferred. */
#include <stdint.h>

extern uint8_t *r2d_ctx;
int r6c_CollectBetween(void *list, const float *hi, const float *lo, int key);

/* 0x1C590: collect the scene objects inside a 40-unit box centred on obj+0x60 (corners pos-20 and pos+20, w = 1), matching key *pk. */
int m2_CollectNear1C590(uint8_t *obj, int *pk) {
    float lo[4], hi[4];
    float *p = (float *)(obj + 0x60);
    hi[0] = p[0] + 20.0f; lo[0] = p[0] - 20.0f;
    hi[1] = p[1] + 20.0f; lo[1] = p[1] - 20.0f;
    hi[2] = p[2] + 20.0f; lo[2] = p[2] - 20.0f;
    hi[3] = 1.0f; lo[3] = 1.0f;
    return r6c_CollectBetween(*(void **)(r2d_ctx + 0x54), hi, lo, *pk);
}

typedef struct M2Chan1 { uint8_t *a0, *a1; uint8_t ab; uint8_t pad9; uint16_t apr; uint8_t *b0, *b1; uint8_t bb; uint8_t pad15; uint16_t bpr; float bv; } M2Chan1;
typedef struct M2ChSrc1 { uint8_t *a, *b; uint16_t prio; } M2ChSrc1;
extern M2Chan1 a5b_chans[2];

/* 0x5EA60: offer channel idx a new pair of sources; each half (a, b) is taken only when its source is set and the offer's priority is at least the current one (b also takes value v). 0 if anything was taken, -1 otherwise or when there is no offer. */
int m2_ChanOffer5EA60(int idx, M2ChSrc1 *s, float v) {
    int r = -1;
    M2Chan1 *c;
    if (s == 0) return -1;
    c = &a5b_chans[idx];
    if (c->apr <= s->prio && s->a != 0) {
        c->a0 = s->a; c->a1 = s->a; c->ab = s->a[1]; c->apr = s->prio; r = 0;
    }
    if (c->bpr <= s->prio && s->b != 0) {
        c->bv = v; c->b0 = s->b; c->b1 = s->b; c->bb = s->b[1]; c->bpr = s->prio; r = 0;
    }
    return r;
}
