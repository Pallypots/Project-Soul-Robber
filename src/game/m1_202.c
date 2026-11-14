/* Area m1, file 202: 2D rectangle draw helpers. Names inferred. */
#include <stdint.h>

void sub_001A78A0(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, int col, int a, int b, int c, int d);
void sub_001A78F0(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3, int col, int a, int b, int c, int d);

/* Twin rect emitters: flip negative width/height, then pass the four corners (TL, TR, BL, BR order as the callee expects) with the colour biased by 0x7FFFFF00; return the display list unchanged. */
#define M1_RECT202(name, emit) \
void *name(void *dl, float x, float y, float w, float h, int col, int a, int b, int c, int d) { \
    if (0.0f > w) { x += w; w = 0.0f - w; } \
    if (0.0f > h) { y += h; h = 0.0f - h; } \
    h = y + h; \
    w = x + w; \
    emit(x, y, w, y, x, h, w, h, col + 0x7FFFFF00, a, b, c, d); \
    return dl; \
}

/* 0x720D0: filled rect. */
M1_RECT202(m1_RectA0720D0, sub_001A78A0)
/* 0x72180: outlined rect. */
M1_RECT202(m1_RectB072180, sub_001A78F0)

typedef struct M1EmS202 { int32_t state0; uint32_t f4; uint8_t unk08[0x58]; float m60[16]; } M1EmS202;
typedef struct M1Em202 { uint8_t unk00[0x10]; M1EmS202 s10; } M1Em202;
typedef struct M1EmO202 {
    uint8_t unk00[0x10]; int32_t st10; uint32_t f14; int32_t bit18; uint8_t unk1C[0x14]; uint8_t emit30[0x38];
    float t68, life6C; uint8_t unk70[0x78]; uint8_t bE8;
} M1EmO202;
extern void *a80_ctx42C8E4;
int  r2b_TestBit(int bit);
void r1c_NodeFreeChain(void *c);
void sub_00033560(void *s);
int  r4_EmitIsFree(void *e);
void r4f_MatCopy1ADA40(float *dst, const float *src);
void sub_00034F60(void *s, void *ctx);
void sub_00034DD0(void *s, float *a, float *b, float *c);
int  sub_00033AD0(void *s);

/* 0x36180: emitter upkeep: drop it when its story bit clears or its life runs out; when its spawner is free, re-place it at its own matrix (unless flagged to die); kill it once finished. */
int m1_EmitterTick036180(M1EmO202 *o) {
    float m[16]; uint8_t *s = (uint8_t *)o + 0x10; int32_t done;
    if (o->bit18 != -1 && !r2b_TestBit(o->bit18)) r1c_NodeFreeChain(s);
    switch (o->st10) {
    case 1:
        if (o->t68 > o->life6C) { sub_00033560(*(uint8_t *volatile *)&s); return 0; }
        break;
    case 0:
        if (!r4_EmitIsFree(o->emit30)) break;
        if (o->bE8 & 0x10) goto kill;
        if (s != 0 && *(int32_t *)s == 0) r4f_MatCopy1ADA40(m, (float *)(s + 0x60));
        sub_00034F60(s, a80_ctx42C8E4);
        sub_00034DD0(s, &m[12], &m[8], &m[4]);
        break;
    }
    if (s != 0) { done = *(uint32_t *)(s + 4) & 1; if (done) return 0; }
    if (sub_00033AD0(s)) return 0;
kill:
    sub_00033560(s);
    return 0;
}
