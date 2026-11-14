/* Area m1, file 123: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Voice123 { uint8_t unk00[0x90]; float size90; uint8_t unk94[0xA0 - 0x94]; float posA0[3]; uint8_t unkAC[0xDC - 0xAC]; } M1Voice123;
extern M1Voice123 m1_voices420F20[];
int  sub_001C7EE1(void);
int  sub_000A8990(int id, int kind, int a, const float *pos, float *v0, float *v1);

/* 0x000A92A0: spawn one of four random spark effects (0x47..0x4A, kind 0xD) at pos and set
 * its size and position in the effect slot. */
void m1_Spark0A92A0(const float *pos, int unused, float size)
{
    float v[4];
    int i;
    M1Voice123 *e;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    i = sub_000A8990(sub_001C7EE1() % 4 + 0x47, 0xD, 0, pos, v, v);
    if (i < 0)
        return;
    e = &m1_voices420F20[i];
    e->size90 = size;
    e->posA0[0] = pos[0];
    e->posA0[1] = pos[1];
    e->posA0[2] = pos[2];
}

typedef struct M1CamO123 { uint8_t unk00[0x60]; float pos60[4]; } M1CamO123;
typedef struct M1Cam123 { uint8_t unk000[0x8C]; M1CamO123 *obj8C; uint8_t unk090[0x110 - 0x90]; float shake110; } M1Cam123;
extern M1Cam123 *m1_cam3F610C;
extern void *m1_camH3F6110;
extern const float m1_camOff318DB8[4];
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_000A9140(int a, int b, const float *pos, const float *dir);
void sub_000F3D10(void *o, void *c, int mode);

/* 0x000F4470: camera shake: set the strength, fire effect (7, 1) at the camera position plus
 * the offset 0x318DB8 pointing down, and switch the camera to mode 3 (hangs without the
 * camera object or controller). */
void m1_CamShake0F4470(float k)
{
    float d[4];
    float p[4];
    M1CamO123 *c;
    d[0] = 0.0f;
    d[2] = 0.0f;
    d[3] = 0.0f;
    m1_cam3F610C->shake110 = k;
    d[1] = -1.0f;
    sub_001ADAF0(p, m1_cam3F610C->obj8C->pos60, m1_camOff318DB8);
    sub_000A9140(7, 1, p, d);
    c = m1_cam3F610C->obj8C;
    if (c == 0)
        for (;;) ;
    if (m1_camH3F6110 == 0)
        for (;;) ;
    sub_000F3D10(c, m1_camH3F6110, 3);
}

typedef struct M1Fall123 { uint8_t unk000[0xBC]; int16_t doneBC; uint8_t unk0BE[0x178 - 0xBE]; float vy178; } M1Fall123;
typedef struct M1Obj123F { uint8_t unk000[0x50]; float v50[4]; float pos60[4]; uint8_t unk070[0x128 - 0x70]; uint8_t b128; } M1Obj123F;
typedef struct M1Step123F { uint8_t unk00[0x68]; float t68; } M1Step123F;
extern float m1_fps42C964;
M1Fall123 *sub_000F5F80(void *o);
void sub_000C7540(void *o, float a, float size, const float *pos, const float *v);
void sub_000F6AA0(void *e);
void sub_000F63D0(float *v);

/* 0x000FB310: falling actor: shadow marker at the object, finish the clip after 2.5 s, drop by
 * the fall speed, accelerate it by 3 per second (clamped by 0xF63D0) and stop it on landing. */
void m1_FallActor0FB310(M1Obj123F *o, M1Step123F *h)
{
    M1Fall123 *e = sub_000F5F80(o);
    float *v;
    sub_000C7540(o, 1.0f, 0.649999976f, o->pos60, o->v50);
    if (h->t68 >= 2.5f) {
        sub_000F6AA0(e);
        e->doneBC = 1;
    }
    o->pos60[1] += e->vy178;
    v = &e->vy178;
    *v = 3.0f / m1_fps42C964 + *v;
    sub_000F63D0(v);
    if (o->b128 & 0x18)
        *v = 0.0f;
}

typedef struct M1Spr123 { uint8_t unk00[3]; uint8_t a03; uint8_t unk04[0x28 - 4]; } M1Spr123;
extern int32_t m1_mode3DDC80;
extern uint8_t *m1_heap3DDC70;
extern uint8_t m1_alpha3DDC94;
extern M1Spr123 m1_spr2C4660[];
int  sub_00017AE0(int x, void *e);
void sub_00014E80(void *e);

/* 0x0003C740: draw the HUD sprite list: 18 entries in modes 0..2 (else 20); entries past the
 * sixteenth take their alpha from the table scaled by the global fade; each is submitted
 * (0x17AE0, chaining x) and flushed. */
int m1_HudSprites03C740(int x)
{
    volatile int vn = (-(int)((unsigned int)m1_mode3DDC80 < 3) & -2) + 0x14;
    int n = vn;
    M1Spr123 *p;
    int off;
    uint8_t *e;
    unsigned int a;
    if (n > 0) {
        off = 0;
        p = m1_spr2C4660;
        do {
            e = m1_heap3DDC70;
            if (!((int)p < (int)(m1_spr2C4660 + 16))) {
                a = (unsigned int)(p->a03 * m1_alpha3DDC94) >> 7;
                e[off + 0x8F] = 0;
                *(uint32_t *)(e + off + 0x8C) |= a << 24;
                e = m1_heap3DDC70;
            }
            x = sub_00017AE0(x, e + off);
            sub_00014E80(m1_heap3DDC70 + off);
            p++;
            off += 0x9C;
        } while (--n);
    }
    return x;
}

typedef struct M1V4 { float x, y, z, w; } M1V4;
typedef struct M1Part123 { uint8_t unk00[0x70]; float v70[4]; } M1Part123;
typedef struct M1Act123 { uint8_t unk000[0x9C]; int32_t state9C; } M1Act123;
typedef struct M1Obj123M { uint8_t unk00[0x34]; M1Part123 *p34; uint8_t unk38[0x60 - 0x38]; M1V4 pos60; } M1Obj123M;
int  sub_000F5D00(void *o);
void sub_000F62F0(void *e, int v);
void sub_000F62C0(void *e, int v);

/* 0x000F92C0: actor walk-in: phase 0 moves by the part offset each frame and, when 0xF5D00
 * says so, plays 0x37 and goes to phase 1; phase 1 plays 9 when 0xF5D00 says so. */
void m1_WalkIn0F92C0(M1Obj123M *o)
{
    M1Act123 *e = (M1Act123 *)sub_000F5F80(o);
    M1V4 q;
    float *p;
    switch (e->state9C) {
    case 0:
        p = o->p34->v70;
        q = o->pos60;
        q.x += p[0];
        q.y += p[1];
        q.z += p[2];
        o->pos60 = q;
        if (sub_000F5D00(o)) {
            sub_000F62F0(e, 0x37);
            e->state9C++;
        }
        return;
    case 1:
        if (sub_000F5D00(o))
            sub_000F62C0(e, 9);
        return;
    }
}

typedef struct M1Path123 { float c00[7]; float c1C[7]; float c38[7]; float t54; float dt58; uint8_t unk5C[0x134 - 0x5C]; } M1Path123;
typedef struct M1Obj123P { uint8_t unk000[0x70]; float pos70[3]; uint8_t unk07C[0x90 - 0x7C]; float v90[3]; uint8_t unk09C[0x110 - 0x9C]; int32_t path110; } M1Obj123P;
extern M1Path123 m1_paths424040[];
float sub_00062080(const float *c, float t);

/* 0x000A33E0: follow path +0x110: advance its time (capped at 60), place the object on the
 * three curves, stop its velocity, and return 1 at the end of the path. */
int m1_PathFollow0A33E0(M1Obj123P *o)
{
    M1Path123 *s = &m1_paths424040[o->path110];
    float v = s->dt58 + s->t54;
    s->t54 = v;
    if (v > 60.0f)
        s->t54 = 60.0f;
    o->pos70[0] = sub_00062080(s->c00, s->t54);
    o->pos70[1] = sub_00062080(s->c1C, s->t54);
    o->pos70[2] = sub_00062080(s->c38, s->t54);
    o->v90[2] = 0.0f;
    o->v90[1] = 0.0f;
    o->v90[0] = 0.0f;
    if (s->t54 >= 60.0f)
        return 1;
    return 0;
}
