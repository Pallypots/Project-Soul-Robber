/* Area m1, file 250: math and effect helpers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Ang250 { uint8_t unk00[0x10]; float v10[4]; } M1Ang250;
void sub_000F5D40(void *dst, const void *src);
void sub_001AD940(float *m);
void sub_001AD8B0(float *out, const float *in, float ang);
void sub_001AD8E0(float *out, const float *in, float ang);
void sub_001AD9B0(float *out, const float *m, const float *v);

/* 0x0003D2A0: turn the pitch/yaw pair at p+0x10 (degrees) into a unit forward vector in out (regargs: p=EAX). */
void m1_DirFromAngles03D2A0(M1Ang250 *p, float *out)
{
    float a[4], d[4], m[16];
    float rx, ry;
    d[0] = 0.0f;
    d[1] = 0.0f;
    d[2] = 1.0f;
    d[3] = 1.0f;
    sub_000F5D40(a, p->v10);
    rx = a[0] * 3.14159274f * 0.00555555569f;
    d[0] = 0.0f;
    d[2] = 1.0f;
    ry = a[1] * 3.14159274f * 0.00555555569f;
    sub_001AD940(m);
    sub_001AD8B0(m, m, rx);
    sub_001AD8E0(m, m, ry);
    sub_001AD9B0(out, m, d);
}

typedef struct M1UO250 { uint8_t unk00[0x108]; uint8_t v108[4]; float f10C; } M1UO250;
typedef struct M1US250 { uint8_t unk00[0x58]; int32_t st58; float t5C; } M1US250;
typedef struct M1UP250 { uint8_t unk00[0x10]; float f10; } M1UP250;
void sub_0001D610(M1UO250 *o);
float *sub_0001D0F0(M1UO250 *o, int32_t slot);
void sub_0001EF00(M1UO250 *o, void *p);
M1UP250 *sub_001133E0(M1US250 *s, int32_t k);
void sub_00113040(M1UO250 *o, M1US250 *s, int32_t mode);

/* 0x0017B660: stand-up: step 0 after 0.5 s shows o, lays its root bone flat (-90 degrees) and advances; step 1 tilts
   it back up over the next second (bone scale 2*(1-t)) and at the end resets the bone, clears the hold and goes to
   mode 3. */
void m1_StandUp17B660(M1UO250 *o, M1US250 *s)
{
    float *n;
    float t;
    switch (s->st58) {
    case 0:
        if (s->t5C >= 0.5f) {
            sub_0001D610(o);
            n = sub_0001D0F0(o, 0);
            sub_001AD940(n);
            sub_001AD8B0(n, n, -1.57079637f);
            o->f10C = 0.0f;
            sub_0001EF00(o, o->v108);
            s->st58++;
        }
        return;
    case 1:
        t = 1.5f - s->t5C;
        n = sub_0001D0F0(o, 0);
        sub_001AD940(n);
        if (t <= 0.0f) {
            sub_001AD8B0(n, n, 0.0f);
            o->f10C = 2.0f;
            sub_0001EF00(o, o->v108);
            sub_001133E0(s, 0)->f10 = 0.0f;
            sub_00113040(o, s, 3);
            return;
        }
        sub_001AD8B0(n, n, t * -1.57079637f);
        o->f10C = (1.0f - t) * 2.0f;
        sub_0001EF00(o, o->v108);
        return;
    }
}

typedef struct M1VN250 { uint8_t unk00[0x40]; float v40[0x10]; uint8_t *p80; } M1VN250;
typedef struct M1VS250 { uint8_t unk00[0x58]; int32_t st58; float t5C; uint8_t unk60[0x18]; float f78; uint8_t unk7C[4];
    float f80; uint8_t unk84[4]; float f88; uint8_t unk8C[4]; float f90; } M1VS250;
extern void *a80_ctx42C8E4;
extern float a50_frameUnits;
void sub_0001EB80(M1UO250 *o);
void sub_0001E9B0(void *ctx, M1UO250 *o, int32_t a, int32_t b, int32_t c);
int32_t sub_00036750(M1UO250 *o, int32_t pose);
void sub_000EE6D0(M1UO250 *o, float k);
void sub_000ED780(M1UO250 *o);
M1VN250 *sub_0001D0F0v(M1UO250 *o, int32_t slot);   /* 0x1D0F0 */
void sub_001AD7C0(float *out, const float *m, const float *in);

/* 0x0017BEA0: fade-out death: step 0 after 1 s detaches and fires the death effect, step 1 at 1.5 s sets pose 1,
   steps 1-2 fade (destroy at 2 s); every tick spins the root bone and scales the two drift speeds by (1 - t/2)^2. */
void m1_Death17BEA0(M1UO250 *o, M1VS250 *s)
{
    M1VN250 *n;
    float m[16];
    float k;
    switch (s->st58) {
    case 0:
        if (s->t5C >= 1.0f) {
            sub_0001EB80(o);
            sub_0001E9B0(a80_ctx42C8E4, o, 0xE, 5, 0x11);
            s->st58++;
        }
        break;
    case 1:
        if (s->t5C >= 1.5f) {
            sub_00036750(o, 1);
            s->st58++;
        }
    case 2:
        sub_000EE6D0(o, 1.0f - (s->t5C - 1.0f));
        if (s->t5C >= 2.0f)
            sub_000ED780(o);
        break;
    }
    k = (1.0f - s->t5C * 0.5f) * (1.0f - s->t5C * 0.5f);
    n = sub_0001D0F0v(o, 0);
    sub_001AD940(m);
    sub_001AD8B0(m, m, 0.0f - a50_frameUnits * 0.52359879f * k);
    sub_001AD7C0((float *)n, m, (float *)n);
    sub_001AD7C0(n->v40, (float *)(n->p80 + 0x40), (float *)n);
    s->f78 = s->f88 * k;
    s->f80 = s->f90 * k;
}

typedef struct M1WN250 { uint8_t unk00[0x40]; float v40[0x10]; uint8_t *p80; uint8_t unk84[0xC]; uint32_t f90; } M1WN250;
typedef struct M1WO250 { uint8_t unk00[0xC]; uint32_t flagsC; uint8_t unk10[0x50]; uint8_t pos60[0xC8]; uint8_t flags128; } M1WO250;
typedef struct M1WS250 { uint8_t unk00[0x58]; int32_t st58; uint8_t unk5C[0x18]; float t74, f78, f7C, f80, f84; } M1WS250;
extern M1WO250 *g_playerObj;
M1WN250 *sub_0001D0F0w(M1WO250 *o, int32_t slot);   /* 0x1D0F0 */
float sub_001B2770(const void *a, const void *b);
void m1_LockMark0C56B0(M1WO250 *o);
void m1_PlShot0C62A0(M1WO250 *o);
void sub_0017B010(M1WO250 *o);                       /* regargs: o=EAX */
int32_t sub_00036750w(M1WO250 *o, int32_t pose);    /* 0x36750 */
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);
void sub_000EE6D0w(M1WO250 *o, float k);            /* 0xEE6D0 */
void sub_000ED780w(M1WO250 *o);                      /* 0xED780 */

/* 0x0017BBD0: launched-enemy tick: step 0 marks the lock-on while the player is within 60 (and not on contact), else
   fires: flag 0x20, reset hold, pose 3, shot, root flag 0x40 and 0x17B010; step 1 spins the root bone until it lands
   (pose 1, sound 0x19C, 1 s fade); step 2 fades out and destroys (calls 0x17B010 with o=EAX). */
void m1_Launch17BBD0(M1WO250 *o, M1WS250 *s)
{
    M1WN250 *n = sub_0001D0F0w(o, 0);
    float m[16];
    switch (s->st58) {
    case 0:
        float d;
        if (!(o->flags128 & 6) && (d = sub_001B2770(o->pos60, g_playerObj->pos60), !_mm_comige_ss(_mm_load_ss(&d), _mm_set_ss(60.0f)))) {
            m1_LockMark0C56B0(o);
            s->f7C = 0.0f;
            return;
        }
        o->flagsC |= 0x20;
        s->f78 = 0.0f;
        s->f7C = 0.0f;
        s->f80 = 0.0f;
        s->f84 = 1.0f;
        sub_00036750w(o, 3);
        m1_PlShot0C62A0(o);
        n->f90 |= 0x40;
        sub_0017B010(o);
        s->st58++;
        return;
    case 1:
        if (!(o->flags128 & 0x18)) {
            sub_001AD940(m);
            sub_001AD8B0(m, m, a50_frameUnits * 0.52359879f * 0.5f);
            sub_001AD7C0((float *)n, m, (float *)n);
            sub_001AD7C0(n->v40, (float *)(n->p80 + 0x40), (float *)n);
            return;
        }
        sub_00036750w(o, 1);
        aab_Effect494D0(0x19C, o->pos60, 0);
        s->t74 = 1.0f;
        s->st58++;
        return;
    case 2:
        sub_000EE6D0w(o, s->t74);
        if (_mm_comige_ss(_mm_setzero_ps(), _mm_load_ss(&s->t74)))
            sub_000ED780w(o);
        return;
    }
}

typedef struct M1BL250 { int32_t id; float v4[4]; } M1BL250;
typedef struct M1BM250 { uint8_t unk00[0xC4]; uint8_t *bonesC4; } M1BM250;
typedef struct M1BH250 { uint8_t unk00[0x20]; M1BM250 *mdl20; } M1BH250;
typedef struct M1BE250 { uint8_t unk00[4]; int32_t n4; uint8_t unk08[0x14]; float t1C; uint8_t unk20[0x30]; M1BH250 *p50; } M1BE250;
void sub_001ADC60(float *out, const float *a, const float *b, float t);
void sub_001AD910(float *out, const float *in, float ang);

/* 0x000CDBE0: blend each listed bone's rotation from zero toward its stored angles by t and rebuild the bone matrix
   about its saved position (regargs: list=EAX). */
void m1_BonesBlend0CDBE0(M1BL250 *list, M1BE250 *e)
{
    M1BM250 *m = e->p50->mdl20;
    float ang[4], spare[4], zero[4], pos[4];
    float t;
    int i;
    ang[0] = 0.0f;
    ang[1] = 0.0f;
    ang[2] = 0.0f;
    ang[3] = 0.0f;
    spare[0] = 0.0f;
    spare[1] = 0.0f;
    spare[2] = 0.0f;
    spare[3] = 0.0f;
    zero[0] = 0.0f;
    zero[1] = 0.0f;
    zero[2] = 0.0f;
    zero[3] = 0.0f;
    t = e->t1C;
    for (i = 0; i < e->n4; i++, list++) {
        sub_001ADC60(ang, list->v4, zero, t);
        sub_000F5D40(pos, m->bonesC4 + list->id * 0x180 + 0x30);
        sub_001AD940((float *)(m->bonesC4 + list->id * 0x180));
        sub_001AD8B0((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[0]);
        sub_001AD8E0((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[1]);
        sub_001AD910((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[2]);
        sub_000F5D40(m->bonesC4 + list->id * 0x180 + 0x30, pos);
    }
    (void)spare;
}

/* 0x000CDEC0: as 0x0CDBE0 but blends every listed bone from zero toward one shared angle set (other+4) (regargs:
   list=EAX). */
void m1_BonesBlend0CDEC0(M1BL250 *list, M1BE250 *e, M1BL250 *other)
{
    M1BM250 *m = e->p50->mdl20;
    float ang[4], spare[4], zero[4], pos[4];
    float t;
    int i;
    ang[0] = 0.0f;
    ang[1] = 0.0f;
    ang[2] = 0.0f;
    ang[3] = 0.0f;
    spare[0] = 0.0f;
    spare[1] = 0.0f;
    spare[2] = 0.0f;
    spare[3] = 0.0f;
    zero[0] = 0.0f;
    zero[1] = 0.0f;
    zero[2] = 0.0f;
    zero[3] = 0.0f;
    t = e->t1C;
    for (i = 0; i < e->n4; i++, list++) {
        sub_001ADC60(ang, zero, other->v4, t);
        sub_000F5D40(pos, m->bonesC4 + list->id * 0x180 + 0x30);
        sub_001AD940((float *)(m->bonesC4 + list->id * 0x180));
        sub_001AD8B0((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[0]);
        sub_001AD8E0((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[1]);
        sub_001AD910((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[2]);
        sub_000F5D40(m->bonesC4 + list->id * 0x180 + 0x30, pos);
    }
    (void)spare;
}

/* 0x000CDD30: as 0x0CDEC0 but each bone's own entry supplies the blend: its first value is the blend factor and its
   second is scaled by 0.8 * t1C before blending toward the shared angle set (regargs: list=EAX). */
void m1_BonesBlend0CDD30(M1BL250 *list, M1BE250 *e, M1BL250 *other)
{
    M1BM250 *m = e->p50->mdl20;
    float ang[4], zero[4], tmp[4], pos[4];
    float t;
    int i;
    ang[0] = 0.0f;
    ang[1] = 0.0f;
    ang[2] = 0.0f;
    ang[3] = 0.0f;
    zero[0] = 0.0f;
    zero[1] = 0.0f;
    zero[2] = 0.0f;
    zero[3] = 0.0f;
    tmp[0] = 0.0f;
    tmp[1] = 0.0f;
    tmp[2] = 0.0f;
    tmp[3] = 0.0f;
    t = e->t1C;
    for (i = 0; i < e->n4; i++, list++) {
        sub_000F5D40(tmp, list->v4);
        tmp[1] = tmp[1] * 0.8f * t;
        sub_001ADC60(ang, zero, other->v4, tmp[0]);
        sub_000F5D40(pos, m->bonesC4 + list->id * 0x180 + 0x30);
        sub_001AD940((float *)(m->bonesC4 + list->id * 0x180));
        sub_001AD8B0((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[0]);
        sub_001AD8E0((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[1]);
        sub_001AD910((float *)(m->bonesC4 + list->id * 0x180), (float *)(m->bonesC4 + list->id * 0x180), ang[2]);
        sub_000F5D40(m->bonesC4 + list->id * 0x180 + 0x30, pos);
    }
}
