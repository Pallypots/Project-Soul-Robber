/* Area m1, file 31: small record and actor helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Act16C {
    uint8_t unk000[0x16C];
    int32_t mode16C;           /* +0x16C */
} M1Act16C;
void sub_000CA850(M1Act16C *a, float v, float lim, int on, int mode, float b);
void sub_000CA9C0(M1Act16C *a, float v, float lim, int mode, float b);

/* 0x000CAB30: scales x and feeds it to the two actor limiters 0xCA850 and 0xCA9C0. */
void m1_FeedLimitsCAB30(M1Act16C *a, float x)
{
    float v = x * 0.096f;
    int mode = a->mode16C;
    sub_000CA850(a, v, 80.0f, 1, mode, 50.0f);
    sub_000CA9C0(a, v, 10000.0f, mode, 30.0f);
}
