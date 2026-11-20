/* Area m1, file 259: model node matrices. Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Skin259 { uint8_t unk00[0x8C]; int32_t kind8C; uint8_t unk90[0x34]; uint8_t *mats0C4; } M1Skin259;
typedef struct M1Anim259 { uint8_t unk00[0xB4]; uint8_t *matsB4; } M1Anim259;
typedef struct M1Mdl259 { uint8_t unk00[0xC8]; M1Anim259 *animC8; uint8_t unkCC[0x1C]; M1Skin259 *skinE8; } M1Mdl259;
typedef struct M1Node259 { float world[16]; float local40[16]; float *parent80; uint8_t unk84[0x3C]; M1Mdl259 *mdlC0;
    uint8_t unkC4[0x10]; int32_t animD4; uint8_t unkD8[0x24]; int16_t boneFC; } M1Node259;
void sub_001ADA40(float *d, const void *s);                    /* copy a 4x4 matrix */
void sub_001ADA40b(float *d, const void *s);                   /* aliases stop cl merging the per-kind copies */
void sub_001ADA40c(float *d, const void *s);
void sub_001AD7C0(float *d, const float *a, const float *b);   /* d = a * b */

/* 0x001B86B0: refresh node n's matrices. An animated node with a bone copies its world matrix from the
   animation's 0x130-byte bone records; a skinned node copies world and local from the skin's bone records
   (0x108 bytes for kind 1, 0x180 for kind 9); a node without a bone takes local = parent's local * world. */
void m1_NodeMats1B86B0(M1Node259 *n)
{
    M1Skin259 *k;
    if (n->animD4 && n->boneFC >= 0) {
        sub_001ADA40(n->world, n->mdlC0->animC8->matsB4 + n->boneFC * 0x130);
        return;
    }
    k = n->mdlC0->skinE8;
    if (k && n->boneFC >= 0) {
        switch (k->kind8C) {
        case 1:
            sub_001ADA40(n->world, k->mats0C4 + n->boneFC * 0x108);
            sub_001ADA40(n->local40, n->mdlC0->skinE8->mats0C4 + n->boneFC * 0x108 + 0x40);
            return;
        case 9:
            sub_001ADA40b(n->world, k->mats0C4 + n->boneFC * 0x180);
            sub_001ADA40c(n->local40, n->mdlC0->skinE8->mats0C4 + n->boneFC * 0x180 + 0x40);
            return;
        }
        return;
    }
    if (n->boneFC < 0 && n->parent80)
        sub_001AD7C0(n->local40, n->parent80 + 16, n->world);
}

typedef struct M1Ob259 { uint8_t unk00[0x60]; float pos60[1]; float y64; } M1Ob259;
typedef struct M1St259 { void *o0; void *a4; uint8_t unk08[0xC]; int32_t h14; uint8_t unk18[8]; float t20; uint8_t unk24[4];
    int16_t step28; uint8_t unk2A[2]; float t2C; } M1St259;
typedef struct M1Ac259 { uint8_t unk00[0x5C]; float f5C; uint8_t unk60[0x218]; M1St259 *s278; } M1Ac259;
extern float m1_frameRate42C85C, m1_fps42C964;
int32_t sub_00036750(M1Ob259 *o, int32_t kind);
int32_t sub_000494D0(int32_t snd, float *pos, int32_t z);
void sub_00182770(int32_t a);
void m1_AiGoto113040(void *o, void *a, int32_t st);

/* 0x0017DB90: rise-out sequence. After 1.5 s spawn an effect once. Step 0 waits until a->f5C passes 0.5,
   then plays sound 0x1D2; steps 1 and 3 wait 1 s; step 2 raises o by 8 units/s up to -88 for 1 s; step 4
   waits 1.5 s and hands the actor to AI state 2. */
void m1_RiseOut17DB90(M1Ob259 *o, M1Ac259 *a)
{
    M1St259 *s = a->s278;
    int16_t w;
    if (s->h14 == 0) {
        if (s->t20 > 1.5f)
            s->h14 = sub_00036750(o, 4);
        else
            s->t20 += m1_frameRate42C85C;
    }
    w = s->step28;
    switch (w) {
    case 0:
        if (a->f5C > 0.5f) {
            sub_000494D0(0x1D2, o->pos60, 1);
            sub_00182770(1);
            s->step28++;
            s->t2C = 0.0f;
        }
        return;
    case 2:
        o->y64 += 8.000002f / m1_fps42C964;
        if (o->y64 > -88.0f)
            o->y64 = -88.0f;
        if (s->t2C > 1.0f) {
            s->step28++;
            s->t2C = 0.0f;
            return;
        }
        break;
    case 1: case 3:
        if (s->t2C > 1.0f) {
            s->step28 = w + 1;
            s->t2C = 0.0f;
            return;
        }
        break;
    case 4:
        if (s->t2C > 1.5f) {
            m1_AiGoto113040(s->o0, s->a4, 2);
            return;
        }
        break;
    default:
        return;
    }
    s->t2C += m1_frameRate42C85C;
}

typedef struct M1Bl259 { uint32_t flags0; int32_t step4; int32_t wait8; } M1Bl259;
void sub_000A4340(void *w, int32_t pose);
void sub_000A4340b(void *w, int32_t pose);   /* same function (alias stops cl merging calls) */
int32_t sub_000A4370(void *w);

/* 0x000ABBF0: two-pose idle loop for menu widget w. Command 0 stops, 1 starts (step 10, wait 3 s), 3 stops and
   returns 0; otherwise run a step: pose 0, wait for it then pose 1 and hold 3 s, pose 2, wait then pose 3 and
   hold 3 s, repeat. Step 20 also stops and returns 0. regargs: cmd=EAX, w=ECX, s=ESI. */
int32_t m1_IdleLoopABBF0(int32_t cmd, void *w, M1Bl259 *s)
{
    int32_t st;
    if (cmd == 0) {
        s->flags0 = 0;
        s->step4 = 0;
        return 1;
    }
    if (cmd == 1) {
        s->flags0 |= 1;
        s->step4 = 10;
        s->wait8 = _mm_cvttss_si32(_mm_set_ss(m1_fps42C964 * 3.0f));
        return 1;
    }
    if (cmd == 3)
        goto stop;
    st = s->step4;
    switch (st) {
    case 10:
        sub_000A4340(w, 0);
        s->step4++;
        return 1;
    case 11:
        if (sub_000A4370(w)) {
            sub_000A4340(w, 1);
            s->wait8 = _mm_cvttss_si32(_mm_set_ss(m1_fps42C964 * 3.0f));
            s->step4++;
        }
        return 1;
    case 12:
        if (--s->wait8 > 0) return 1;
        s->step4 = st + 1;
        return 1;
    case 13:
        sub_000A4340b(w, 2);
        s->step4++;
        return 1;
    case 14:
        if (sub_000A4370(w)) {
            sub_000A4340(w, 3);
            s->step4++;
            s->wait8 = _mm_cvttss_si32(_mm_set_ss(m1_fps42C964 * 3.0f));
        }
        return 1;
    case 15:
        if (--s->wait8 > 0) return 1;
        s->step4 = 10;
        return 1;
    case 20:
        goto stop;
    }
    return 1;
stop:
    s->flags0 = 0;
    s->step4 = 0;
    return 0;
}
