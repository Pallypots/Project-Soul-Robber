/* Area m1, file 178: random throw direction. Names inferred. */
#include <stdint.h>

int  sub_001C7EE1(void);
void sub_000F5D40(float *d, const void *s);
void sub_001AD7E0(float *d, const float *s);
void sub_00082A30(float *out, const float *a, const float *b);
void sub_001ADBA0(float *d, const float *s, float k);

/* 0xA8330: random throw vector around a direction (wider spread straight up), scaled by level, with upward speed. */
void m1_ThrowDir0A8330(const float *dir, float *out, int lvl) {
    struct { float t; float a[4]; float b[4]; } l; float f;
    l.a[0] = 0.0f; l.a[1] = 0.0f; l.a[2] = 0.0f; l.a[3] = 1.0f;
    l.b[0] = 0.0f; l.b[1] = 0.0f; l.b[2] = 0.0f; l.b[3] = 1.0f;
    sub_000F5D40(l.a, dir);
    l.a[1] = 0.0f; l.a[3] = 1.0f;
    sub_001AD7E0(l.a, l.a);
    if (l.a[0] == 0.0f && l.a[2] == 0.0f) {
        l.t = (float)(sub_001C7EE1() % 180) * 0.00555555569f * 3.14159274f;
        l.a[2] = -1.0f;
    } else {
        l.t = (float)(sub_001C7EE1() % 60) * 0.00555555569f * 3.14159274f;
    }
    if (!(sub_001C7EE1() & 1)) l.t *= -1.0f;
    l.b[1] = l.t;
    sub_00082A30(l.a, l.b, l.a);
    f = (float)(3 - lvl);
    sub_001ADBA0(l.a, l.a, (float)(sub_001C7EE1() % 10 + 5) * 0.100000001f * (f * 0.0500000007f + 0.100000001f));
    l.a[1] = (float)(sub_001C7EE1() % 10 + 5) * 0.100000001f * (f * 0.100000001f + 1.0f) * -1.0f;
    sub_000F5D40(out, l.a);
}
