/* Area m1, file 139: small helpers. Names inferred. */
#include <stdint.h>


typedef struct M1Anim139 { uint8_t unk00[8]; int32_t cur08; } M1Anim139;
typedef struct M1Mdl139 { uint8_t unk00[0x30]; M1Anim139 *anim30; } M1Mdl139;
typedef struct M1Act139 {
    uint8_t unk00[0xD4]; int32_t d4; int32_t d8; uint8_t unkDC[4]; int32_t e0; float e4; float e8; int32_t ec;
    uint8_t unkF0[0x128 - 0xF0]; int32_t anim128; int32_t anim12C; uint8_t unk130[0x150 - 0x130]; uint32_t flags150;
    uint8_t unk154[0x1B8 - 0x154]; int32_t mode1B8; uint8_t unk1BC[0xFD8 - 0x1BC]; M1Mdl139 *mdlFD8;
} M1Act139;
void sub_000D1930(M1Act139 *o);
void sub_000832D0(M1Anim139 *a, int id);

/* 0xD1D00: reset the actor's motion and pick its idle animation. */
void m1_ActIdle0D1D00(M1Act139 *o) {
    int a;
    sub_000D1930(o);
    o->d8 = 1; o->e0 = 0; o->e4 = 0.0f; o->e8 = 0.0f;
    switch (o->mode1B8) {
    case 0: a = (o->d4 == 0 && o->ec == 0) ? 0 : 2; break;
    case 1: a = (o->d4 != 0 || o->ec != 0) ? 0x302 : 0; break;
    case 2: a = 0x200; break;
    default: goto out;
    }
    if (o->anim128 == a) { o->mdlFD8->anim30->cur08 = -1; o->anim128 = -1; }
    o->anim12C = a;
    sub_000832D0(o->mdlFD8->anim30, a);
    o->anim128 = a;
out:
    o->flags150 |= 0x22;
}

typedef struct M1Src139 { uint8_t unk00[4]; int32_t a04; int32_t a08; } M1Src139;
typedef struct M1Fx139 {
    uint32_t flags00; int32_t kind04; int32_t arg08; float c0C; float c10; float c14; float c18;
    int32_t s1C; int32_t s20; float v24[4]; float v34[4]; float v44[4]; M1Src139 *src54; uint8_t unk58[0xE0 - 0x58];
} M1Fx139;
extern M1Fx139 m1_entsE41E2A0[];
void sub_000C4B70(M1Fx139 *s);
void sub_000F5D40(float *d, const void *s);

static int m1_FxFree139(void) {
    int i;
    for (i = 0; i < 32; i++)
        if (!(m1_entsE41E2A0[i].flags00 & 1)) return i;
    return -1;
}

/* 0xC4DF0: claim a free effect slot and fill it in. */
int m1_FxAdd0C4DF0(int unused, int kind, float c0, int arg, float c2, float c3, float c1,
                   M1Src139 *src, const float *v1, const float *v2) {
    M1Fx139 *s; int i = m1_FxFree139();
    if (i < 0) return -1;
    s = &m1_entsE41E2A0[i];
    sub_000C4B70(s);
    s->c0C = c0; s->c10 = c1; s->kind04 = kind; s->flags00 |= 0x80000001;
    s->c14 = c2; s->c18 = c3; s->arg08 = arg;
    sub_000F5D40(s->v24, src); sub_000F5D40(s->v34, v1); sub_000F5D40(s->v44, v2);
    s->src54 = src;
    if (src != 0) { s->s1C = src->a04; s->s20 = src->a08; }
    return i;
}

