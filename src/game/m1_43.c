/* Area m1, file 43: entry pose sync. Names inferred. */
#include <stdint.h>

typedef struct M1PoseObj {
    uint8_t unk00[0x50];
    float   rot50[4];          /* +0x50 */
    float   pos60[4];          /* +0x60 */
} M1PoseObj;
typedef struct M1EntP {
    uint8_t    unk000[0x70];
    float      pos070[4];      /* +0x070 */
    float      rot080[4];      /* +0x080 */
    uint8_t    unk090[0x120 - 0x90];
    M1PoseObj *obj120;         /* +0x120 */
} M1EntP;
void sub_000F5D40(void *dst, const void *src);

/* 0x000A3D40: copies e's position and rotation to its object (w = 1 on both sides). */
void m1_SyncPoseA3D40(M1EntP *e)
{
    sub_000F5D40(e->obj120->pos60, e->pos070);
    e->pos070[3] = 1.0f;
    e->obj120->pos60[3] = 1.0f;
    sub_000F5D40(e->obj120->rot50, e->rot080);
    e->rot080[3] = 1.0f;
    e->obj120->rot50[3] = 1.0f;
}

/* 0x000A35B0: wraps the angle at a into [-pi, pi] in 2*pi steps. */
void m1_WrapAngleA35B0(float *a)
{
    float x;
    if (a == 0)
        return;
    if (*a > 3.1415927f) {
        x = *a;
        do
            x = x - 6.2831855f;
        while (x > 3.1415927f);
        *a = x;
    }
    if (-3.1415927f > *a) {
        x = *a;
        do
            x = x + 6.2831855f;
        while (-3.1415927f > x);
        *a = x;
    }
}
