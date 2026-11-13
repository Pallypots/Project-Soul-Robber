/* Area m1, file 51: rig blends with turn speeds. Names inferred. */
#include <stdint.h>

typedef struct M1RigT { uint32_t flags00; } M1RigT;
typedef struct M1StepT {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1RigT *rig278;            /* +0x278 */
} M1StepT;
typedef struct M1ObjT { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[3]; } M1ObjT;
extern float m1_frameTime42C858, m1_frameRate42C85C;
int  sub_001456E0(void *o, void *s, int a, int b);
void sub_00156180(void *rig, float x, float y, float z, float t);
int  sub_00036750(void *o, int v);
int  sub_000494D0(int id, const void *pos, int c);

/* 0x00146E50: 0x1456E0(6), rig blend 0x156180(frame rate * 10, frame rate * -5, 0,
 * frame time * 0.003), o flags |= 5, h +0x4C: clear 0x70 set 0x1000000, rig flags |= 3,
 * 0x36750(0), sound 0x12F at o. */
void m1_RigBlend146E50(M1ObjT *o, M1StepT *h)
{
    M1RigT *r = h->rig278;
    sub_001456E0(o, h, 6, 0);
    sub_00156180(r, m1_frameRate42C85C * 10.0f, m1_frameRate42C85C * -5.0f, 0.0f,
                 m1_frameTime42C858 * 0.003f);
    o->flags10 |= 5;
    h->flags4C = (h->flags4C & ~0x70u) | 0x1000000;
    r->flags00 |= 3;
    sub_00036750(o, 0);
    sub_000494D0(0x12F, o->pos60, 0);
}
