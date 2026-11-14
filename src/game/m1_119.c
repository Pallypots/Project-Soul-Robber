/* Area m1, file 119. Names inferred. */
#include <stdint.h>

typedef struct M1Pl119 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl119;
typedef struct M1Rig119 { uint32_t flags00; uint8_t unk04[0x50 - 4]; uint32_t flags50; } M1Rig119;
typedef struct M1Step119 {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t state58;           /* +0x58 */
    uint8_t unk05C[0x6C - 0x5C];
    int32_t snd6C;             /* +0x6C */
    void   *fx70;              /* +0x70 */
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x104 - 0x78];
    M1Pl119 *tgt104;           /* +0x104 */
    uint8_t unk108[0x278 - 0x108];
    M1Rig119 *rig278;          /* +0x278 */
} M1Step119;
typedef struct M1Obj119 { uint8_t unk000[0xC]; uint32_t flags0C; uint32_t flags10; uint8_t unk014[0x30 - 0x14]; void *anim30; uint8_t unk034[0x60 - 0x34]; float pos60[4]; uint8_t unk070[0x13C - 0x70]; int32_t i13C; } M1Obj119;
extern float m1_frameRate42C85C;
int  sub_000833E0(void *a);
int  sub_00156040(void);
void sub_001134B0(void *h);
void sub_001561D0(void *r, float a, float b);
void sub_00113AA0(void *o, void *h);
void sub_00113190(void *o, void *h, int a);
void sub_00048250(int h);
int  sub_000494D0(int id, const void *pos, int c);
void sub_0005BE30(int v);
void sub_00033A70(void *fx);
void sub_00113040(void *o, void *h, int state);
int  sub_00145940(void *o, float x, float z, float lo, float hi);

#define M1_REC119_HEAD                                              \
    r = h->rig278;                                                  \
    sub_001134B0(h);                                                \
    o->flags0C |= 0xE0;                                             \
    o->flags10 &= ~0x137u;                                          \
    h->flags4C &= ~0x100u;                                          \
    r->flags00 &= ~0x17u;                                           \
    r->flags50 &= ~0x241140u;                                       \
    sub_001561D0(r, -10.0f, m1_frameRate42C85C * 10.0f);            \
    if (r->flags50 & 0x10000) {                                     \
        sub_00113AA0(o, h);                                         \
        h->flags4C |= 0x200;                                        \
        r->flags50 &= ~0x10000u;                                    \
    }                                                               \
    if (r->flags50 & 0x100000) {                                    \
        r->flags50 &= ~0x100000u;                                   \
        sub_00113190(o, h, 1);                                      \
    }
#define M1_REC119_STOP                                              \
    if (h->snd6C != -1) {                                           \
        sub_00048250(h->snd6C);                                     \
        h->snd6C = -1;                                              \
    }
#define M1_REC119_TAIL(st)                                          \
    sub_0005BE30(o->i13C);                                          \
    if (h->fx70 != 0) {                                             \
        sub_00033A70(h->fx70);                                      \
        h->fx70 = 0;                                                \
    }                                                               \
    sub_00113040(o, h, st);                                         \
    return;

/* 0x0014CF50: lunge wind-up: phase 0 holds until the wait runs out or rig flag 0x80 (then
 * phase 1), and once the target is within the 30-degree front cone and the clip ends,
 * recovers into state 0xC (when 0x156040 says so, sound stopped) or 0x13 (looping sound
 * 0x10F); phase 1 recovers into state 0xC or 1 once the clip ends. */
void m1_Lunge14CF50(M1Obj119 *o, M1Step119 *h)
{
    M1Rig119 *r;
    switch (h->state58) {
    case 0:
        if (0.0f >= h->wait74 || (int8_t)h->rig278->flags50 < 0) {
            h->state58 = 1;
            return;
        }
        if (!sub_00145940(o, h->tgt104->pos60[0], h->tgt104->pos60[2], -0.261799395f, 0.261799395f))
            return;
        if (!sub_000833E0(o->anim30))
            return;
        if (sub_00156040())
            goto rec_c;
        M1_REC119_HEAD
        if (h->snd6C == -1)
            h->snd6C = sub_000494D0(0x10F, o->pos60, 1);
        M1_REC119_TAIL(0x13)
    case 1:
        if (!sub_000833E0(o->anim30))
            return;
        if (sub_00156040()) {
rec_c:
            M1_REC119_HEAD
            M1_REC119_STOP
            M1_REC119_TAIL(0xC)
        }
        M1_REC119_HEAD
        M1_REC119_STOP
        M1_REC119_TAIL(1)
    }
}
