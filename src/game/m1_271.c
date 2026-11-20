/* Area m1, file 271: actor fades. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Bn271 { uint8_t unk00[0x34]; float alpha34; } M1Bn271;
typedef struct M1Cm271 { uint8_t unk00[0xC4]; float lo0C4; uint8_t unkC8[0x10]; float cur0D8; } M1Cm271;
typedef struct M1Ow271 { uint8_t unk00[0x14]; M1Cm271 *c14; } M1Ow271;
typedef struct M1Oa271 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[4]; uint32_t flags10; uint8_t unk14[0x1C];
    M1Ow271 *w30; } M1Oa271;
typedef struct M1Sa271 { uint8_t unk00[0x50]; int32_t st50; int32_t k54; float t58; } M1Sa271;
M1Bn271 *sub_0001D0F0(M1Oa271 *o, int32_t bone);
void sub_0001D610(M1Oa271 *o);
int32_t sub_00036750(M1Oa271 *o, int32_t kind);
void sub_00170470(M1Oa271 *o);                               /* regargs: o=EAX */

/* 0x00170660: fade-out step: bone 1's alpha falls with the step time (scaled by kind). Step 0 hides o, spawns
   its effect and refreshes it; step 1 waits 1 s, then clears o's flags 1 and 4 and picks the next state (2 for
   kinds 0-9, else 1). Finally refresh again while o's camera value is within range of its low mark. */
void m1_FadeOut170660(M1Oa271 *o, M1Sa271 *s)
{
    M1Bn271 *b = sub_0001D0F0(o, 1);
    float k;
    M1Cm271 *m;
    k = 15.0f;
    if (o->kind8 == 3)
        k = 22.5f;
    b->alpha34 = (1.0f - s->t58) * k;
    switch (s->k54) {
    case 0:
        sub_0001D610(o);
        sub_00036750(o, 1);
        sub_00170470(o);
        s->k54++;
        break;
    case 1:
        if (s->t58 >= 1.0f) {
            o->flags10 &= ~5u;
            s->k54 = 0;
            s->t58 = 0.0f;
            s->st50 = (o->kind8 < 10) + 1;
        }
        break;
    }
    m = o->w30->c14;
    if (m->cur0D8 > 25.0f - m->lo0C4 && m->lo0C4 + 25.0f > m->cur0D8)
        sub_00170470(o);
}

