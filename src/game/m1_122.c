/* Area m1, file 122: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Clip122 { uint8_t unk00[0xD8]; float speedD8; } M1Clip122;
typedef struct M1Anim122 {
    uint8_t unk00[0x84];
    struct M1Anim122 *sub84;   /* +0x84 */
    struct M1Anim122 *sub88;   /* +0x88 */
    int32_t kind8C;            /* +0x8C */
    uint8_t unk90[0xD8 - 0x90];
    float   speedD8;           /* +0xD8 */
} M1Anim122;
typedef struct M1Obj122 { uint8_t unk00[0x28]; M1Anim122 *anim28; } M1Obj122;
typedef struct M1Clock122 { uint8_t unk00[0xC]; int32_t rate0C; } M1Clock122;
typedef struct M1Scene122 { uint8_t unk00[0x40]; M1Clock122 *clock40; } M1Scene122;
extern M1Scene122 *m1_scene42C8E4;
void sub_000EE660(void *o, float t);
void sub_001B3160(void *a);
void sub_001B8320(void *a);

/* 0x000EE6D0: set the animation time scale t (0xEE660), then speed the clip to t times the
 * clock rate: kind 0xC directly, kind 1 through its nested clip. */
void m1_AnimScale0EE6D0(M1Obj122 *o, float t)
{
    M1Anim122 *m;
    M1Anim122 *e;
    sub_000EE660(o, t);
    m = o->anim28;
    if (m == 0)
        return;
    switch (m->kind8C) {
    case 1:
        e = m->sub88->sub84->sub84;
        e->speedD8 = (float)m1_scene42C8E4->clock40->rate0C * t;
        sub_001B3160(e);
        return;
    case 0xC:
        m->speedD8 = (float)m1_scene42C8E4->clock40->rate0C * t;
        sub_001B8320(m);
        return;
    }
}

typedef struct M1Hit122 { uint8_t unk00[0x44]; float y44; } M1Hit122;
typedef struct M1Obj122F { uint8_t unk000[0x64]; float y64; uint8_t unk068[0x11C - 0x68]; int32_t mask11C; } M1Obj122F;
void *sub_00080970(void);
void sub_000824F0(void *coll, void *w, const float *a, const float *b, int c, int d);
M1Hit122 *sub_00080CB0(void *w, const float *a, const float *b);

/* 0x0001C7B0: snap height: cast from a to b in the collision world (mask +0x11C) and, on a
 * hit, move the object up by the hit height above the lower of the two points. Returns 1 on
 * a hit. */
int m1_SnapHeight01C7B0(M1Obj122F *o, const float *a, const float *b, const int *c)
{
    void *w = sub_00080970();
    M1Hit122 *r;
    sub_000824F0(0, w, a, b, *c, (int)&o->mask11C);
    r = sub_00080CB0(w, a, b);
    if (r == 0)
        return 0;
    if (a[1] > b[1])
        o->y64 = r->y44 - a[1] + o->y64;
    else
        o->y64 = r->y44 - b[1] + o->y64;
    return 1;
}

typedef struct M1Help122 {
    uint8_t unk000[0x94];
    void   *mdl94;             /* +0x94 */
    uint8_t unk098[4];
    int32_t state9C;           /* +0x9C */
    float   tA0;               /* +0xA0 */
    uint8_t unk0A4[0xBC - 0xA4];
    int16_t doneBC;            /* +0xBC */
} M1Help122;
extern M1Help122 *m1_helper3F6114;
extern float m1_frameRate42C85C;
int  sub_000F5D00(void *o);
void sub_0001D700(void *m);

/* 0x000FC380: helper wait: phase 0 starts when 0xF5D00 says so (timer cleared); phase 1 counts
 * up and after 0.2 stops the model and marks the helper done. */
void m1_HelperWait0FC380(void *o)
{
    M1Help122 *g = m1_helper3F6114;
    switch (g->state9C) {
    case 0:
        if (sub_000F5D00(o)) {
            g->state9C++;
            g->tA0 = 0.0f;
        }
        return;
    case 1:
        if (g->tA0 > 0.200000003f) {
            sub_0001D700(g->mdl94);
            g->doneBC = 1;
            return;
        }
        g->tA0 += m1_frameRate42C85C;
        return;
    }
}
