/* Area m1, file 124: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Tgt124 { uint8_t unk000[0x60]; float pos60[4]; uint8_t unk070[0xE8 - 0x70]; float rE8; } M1Tgt124;
typedef struct M1Obj124 { uint8_t unk000[0x120]; M1Tgt124 *tgt120; } M1Obj124;
extern uint8_t m1_stats41FEC0[];
int  sub_000CFFB0(void);
void sub_000F5D40(float *d, const float *s);
void sub_000C4250(void *s, float *a, float *b);
int  sub_000EE2B0(const float *p, const float *ray, float *out);

/* 0x00098090: aim pick: when 0xCFFB0 finds something, cast the player's aim ray (0xC4250)
 * against the target sphere at +0x120 (radius +0xE8); 0 unless both aim offsets are set. */
int m1_AimPick098090(M1Obj124 *o)
{
    struct { float a[4]; float out[4]; float p[4]; float r; float rv[4]; float rx, ry; } l;
    M1Tgt124 *e;
    if (sub_000CFFB0() == -1)
        return 0;
    e = o->tgt120;
    sub_000F5D40(l.p, e->pos60);
    l.r = e->rE8;
    sub_000C4250(m1_stats41FEC0, l.rv, l.a);
    l.rx = l.a[0];
    l.ry = l.a[1];
    if (l.a[0] != 0.0f && l.a[1] != 0.0f)
        return sub_000EE2B0(l.p, l.rv, l.out);
    return 0;
}

typedef struct M1Seq124 { uint32_t flags00; int32_t step04; int32_t n08; } M1Seq124;
void sub_000DFD40(int *a, int *b);
void sub_000A43C0(int a, int b);
void sub_000A5450(int a);

/* 0x000AAB60: scripted sequence: mode 0 clears it, mode 1 starts it (flag 1, step 10), mode 3
 * moves to step 0x14 and counts; step 10 polls 0xDFD40 (sound 0xF/0x32 and effect 0x10 on 2)
 * and advances, step 0x14 ends it (returns 0). */
int m1_Seq0AAB60(int mode, M1Seq124 *s)
{
    int k;
    if (mode == 0) {
        s->flags00 = 0;
        s->step04 = 0;
        s->n08 = 0;
        return 1;
    }
    if (mode == 1) {
        s->flags00 |= 1;
        s->step04 = 10;
        s->n08 = 0;
        return 1;
    }
    if (mode == 3) {
        s->flags00 = 0;
        s->step04 = 0x14;
        s->n08++;
    }
    if (s->step04 == 10) {
        sub_000DFD40(&k, &mode);
        if (mode == 2) {
            sub_000A43C0(0xF, 0x32);
            sub_000A5450(0x10);
        }
        s->step04++;
        return 1;
    }
    if (s->step04 == 0x14) {
        s->flags00 = 0;
        s->step04 = 0;
        return 0;
    }
    return 1;
}

int  sub_000A8330(void *src, float *out, int a);
int  sub_000A8990(int id, int kind, int a, const float *pos, float *v0, float *v1);

/* 0x000A9090: dust burst: read the source's motion (0xA8330, mode 3) and spawn effect 0x4F
 * (kind 8) 12 below pos. */
void m1_DustBurst0A9090(const float *pos, void *src)
{
    struct { float p[4]; float m[4]; float u[4]; } l;
    l.m[0] = 0.0f;
    l.m[1] = 0.0f;
    l.m[2] = 0.0f;
    l.m[3] = 1.0f;
    l.p[0] = 0.0f;
    l.p[1] = 0.0f;
    l.p[2] = 0.0f;
    l.p[3] = 1.0f;
    l.u[0] = 0.0f;
    l.u[1] = 0.0f;
    l.u[2] = 0.0f;
    l.u[3] = 1.0f;
    sub_000A8330(src, l.m, 3);
    sub_000F5D40(l.p, pos);
    l.p[1] -= 12.0f;
    sub_000A8990(0x4F, 8, 0, l.p, l.m, l.u);
}
