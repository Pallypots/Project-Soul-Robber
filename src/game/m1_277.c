/* Area m1, file 277: target picking. Names inferred. */
#include <stdint.h>

typedef struct M1Pt277 { float v[4]; uint8_t unk10[8]; } M1Pt277;   /* 0x18 */
typedef struct M1St277 { uint8_t unk00[4]; uint32_t flags4; } M1St277;
typedef struct M1Ac277 { uint8_t unk00[0x278]; M1St277 *s278; } M1Ac277;
extern const M1Pt277 m1_swayPts31A3B0[6];
void sub_000F5D40(float *d, const float *s);
void sub_000F5D40b(float *d, const float *s);                /* same function (alias stops cl merging the copies) */
int32_t sub_001153D0(void);
int32_t sub_001C7EE1(void);                                   /* rand */

/* 0x001176A0: pick the next point for a to move to: the first call returns the first fixed point, the second
   call the second one; after that a random one of six table points, retried (up to 4 times) until 0x1153D0
   says it is clear. Returns 1 for the fixed points, else the last clear-check result. regargs: a=EAX, out=ECX. */
int32_t m1_PickPoint1176A0(M1Ac277 *a, float *out)
{
    float p1[4], p2[4];
    M1St277 *s;
    uint32_t fl;
    int32_t i, r;
    p1[0] = -42.97f;
    p1[1] = 223.64f;
    p2[0] = -17.89f;
    p1[2] = 61.46f;
    p2[1] = 225.45f;
    p1[3] = 1.0f;
    p2[2] = 47.42f;
    p2[3] = 1.0f;
    s = a->s278;
    fl = s->flags4;
    if (!(fl & 0x10000)) {
        s->flags4 = fl | 0x10000;
        sub_000F5D40(out, p1);
        return 1;
    }
    if (!(fl & 0x20000)) {
        s->flags4 = fl | 0x20000;
        sub_000F5D40b(out, p2);
        return 1;
    }
    for (i = 0; i < 4; i++) {
        sub_000F5D40(out, m1_swayPts31A3B0[sub_001C7EE1() % 6].v);
        r = sub_001153D0();
        if (r == 1) break;
    }
    return r;
}

typedef struct M1Spr277 { uint8_t unk[0x9C]; } M1Spr277;
typedef struct M1Pp277 { uint32_t flags0; int32_t f4, f8; int32_t stC; float t10; uint8_t alpha14; uint8_t unk15[0xF];
    float size24; uint8_t unk28[0xC]; float scale34; uint8_t unk38[0x70]; M1Spr277 sprA8; } M1Pp277;
extern uint32_t m1_capKind3F4B1C;
extern M1Spr277 m1_ch3F4BD8, m1_ch3F4C74;
void sub_000150E0(M1Spr277 *s, int32_t v);
void sub_000150B0(M1Spr277 *s, int32_t frame);
void sub_000720A0(float *v, int32_t target);

/* 0x000E8E80: pop-up panel step. Step 0 resets its sprite (and, for caption kinds 3-4, the two side icons) and
   starts a 20-frame timer; step 1 counts down, fading alpha and shrinking the scale from 1.5x size, and when the
   timer ends hides the panel and resets it. regargs: p=ESI. */
void m1_PopupStepE8E80(M1Pp277 *p)
{
    float t, h;
    volatile uint32_t k;   /* keeps the two separate range compares */
    switch (p->stC) {
    case 0:
        sub_000150E0(&p->sprA8, 0);
        k = m1_capKind3F4B1C;
        if (k >= 3 && k <= 4) {
            sub_000150B0(&m1_ch3F4BD8, 9);
            sub_000150B0(&m1_ch3F4C74, 0xA);
            sub_000150E0(&m1_ch3F4BD8, 0);
            sub_000150E0(&m1_ch3F4C74, 0);
        }
        p->t10 = 20.0f;
        p->stC++;
        return;
    case 1:
        sub_000720A0(&p->t10, 0);
        t = p->t10 * 0.05f;
        p->alpha14 = (uint8_t)(int32_t)(double)(t * 128.0f);
        h = p->size24 * 0.5f;
        p->scale34 = h * t + h;
        if (!(0.0f >= p->t10)) return;
        p->flags0 &= ~1u;
        p->alpha14 = 0;
        p->f4 = 0;
        p->f8 = 0;
        p->stC = 0;
        p->scale34 = 1.0f;
        return;
    }
}
