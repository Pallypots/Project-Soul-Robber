/* Area m1, file 137: small helpers. Names inferred. */
#include <stdint.h>

void sub_000F5D40(float *d, const float *s);

/* 0x00082840: bounding box of two points: lo = component minimum of a and b, hi = maximum,
 * with hi pushed out so each of x, y, z spans at least 0.01. */
void m1_BoxOf082840(float *hi, float *lo, const float *a, const float *b)
{
    sub_000F5D40(lo, b);
    if (lo[0] > a[0])
        lo[0] = a[0];
    if (lo[1] > a[1])
        lo[1] = a[1];
    if (lo[2] > a[2])
        lo[2] = a[2];
    if (lo[3] > a[3])
        lo[3] = a[3];
    sub_000F5D40(hi, a);
    if (b[0] > hi[0])
        hi[0] = b[0];
    if (b[1] > hi[1])
        hi[1] = b[1];
    if (b[2] > hi[2])
        hi[2] = b[2];
    if (b[3] > hi[3])
        hi[3] = b[3];
    if (0.00999999978f > hi[0] - lo[0])
        hi[0] = hi[0] + 0.00999999978f;
    if (0.00999999978f > hi[1] - lo[1])
        hi[1] = hi[1] + 0.00999999978f;
    if (0.00999999978f > hi[2] - lo[2])
        hi[2] = hi[2] + 0.00999999978f;
}

typedef struct M1Shop137 {
    int32_t mode000;           /* +0x000 */
    uint8_t unk004[0x314 - 4];
    int32_t sel314;            /* +0x314 */
    uint8_t unk318[0x40C - 0x318];
    int32_t total40C, max410;  /* +0x40C */
    uint8_t unk414[4];
    int32_t limit418, count41C; /* +0x418 */
    uint8_t unk420[0x51C - 0x420];
    int32_t full51C;           /* +0x51C */
} M1Shop137;
typedef struct M1Buy137 { int32_t item00; uint8_t unk04[8]; int32_t gain0C; } M1Buy137;
extern uint8_t m1_snd3E1270[];
extern uint8_t m1_stats41FEC0[];
void sub_00019000(void *s, int a);
void sub_000D0200(void *s, int a, int b);
void sub_000D2A50(void *s, int a);
void m1_MenuSlide0E8920(int mode);
void sub_000E8A50(int a, int b);
void sub_000E8690(int a, int v);
void sub_000E0B70(void *o, int a, int b, int c);
void sub_000E0A80(void *o, int a, int b, int c, int d);
void sub_0012D600(int a);
void sub_000E63A0(int a);

/* 0x000EB4F0: confirm a purchase: confirm sound, close the menus, and when the counter has
 * reached its limit add the item's gain (capped at the maximum, flag +0x51C when full) and
 * restart the counter; then refresh the item and price panels and the selection. */
void m1_ShopBuy0EB4F0(M1Shop137 *o, M1Buy137 *b)
{
    sub_00019000(m1_snd3E1270, 1);
    sub_000D0200(m1_stats41FEC0, 0, 0);
    sub_000D2A50(m1_stats41FEC0, 3);
    if (o == 0)
        return;
    if (b == 0)
        return;
    m1_MenuSlide0E8920(0);
    sub_000E8A50(0, 0);
    if (o->count41C >= o->limit418) {
        o->total40C += b->gain0C;
        sub_000E8690(2, b->gain0C);
        if (o->total40C >= o->max410)
            o->total40C = o->max410;
        o->full51C = 1;
    } else {
        o->full51C = 0;
    }
    o->limit418 = 0;
    o->count41C = 0;
    sub_000E0B70(o, 1, b->item00, 0);
    sub_000E0B70(o, 7, b->item00, 0);
    sub_000E0A80(o, 4, o->mode000, o->sel314, 0);
    if (o->mode000 == 0)
        sub_0012D600(2);
    sub_000E63A0(1);
}
