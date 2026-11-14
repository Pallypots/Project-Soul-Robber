/* Area m1, file 132: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Strm132 { uint8_t unk00[0x1C]; float vol1C; int32_t pos20; int32_t len24; } M1Strm132;
typedef struct M1Chan132 { int32_t flags00; int32_t on04; M1Strm132 *strm08; float rate0C; float vol10, vol14; } M1Chan132;
void sub_00076060(void *s);
void sub_00076760(void *s, void *a, void *b);
void sub_00076700(void *s, void *a);
void sub_00076000(void *s, int a);
int  sub_00076180(void *s);
int  sub_00076210(void *s);
void sub_00076040(void *s, int loop);

/* 0x0003FAF0: start a sound stream on a channel: stop the current one (unless flag 0x80
 * keeps it), load data (with an optional second part), rewind, take its length; flag 1
 * sets the rate from rate60/60 (else volume -1); loop it unless flag 0x10 or 0x76210 says
 * no; set both volumes. */
void m1_StreamStart03FAF0(M1Chan132 *c, void *data, void *data2, int flags, float rate60, float vol)
{
    M1Strm132 *s = c->strm08;
    if (s && !((signed char)flags < 0))
        sub_00076060(s);
    if (data == 0)
        return;
    c->flags00 = flags;
    if (data2)
        sub_00076760(s, data, data2);
    else
        sub_00076700(s, data);
    sub_00076000(s, 1);
    s->pos20 = 0;
    s->len24 = sub_00076180(s);
    s->vol1C = 0.0f;
    if (flags & 1) {
        s->vol1C = 0.0f;
        c->rate0C = rate60 * 0.0166666675f;
    } else {
        s->vol1C = -1.0f;
    }
    c->on04 = 1;
    if (!(flags & 0x10) && sub_00076210(s))
        sub_00076040(s, 1);
    else
        sub_00076040(s, 0);
    c->vol10 = vol;
    c->vol14 = vol;
}

typedef struct M1Cam132 {
    uint8_t unk000[4];
    int32_t i04;               /* +0x04 */
    float   f08;               /* +0x08 */
    uint8_t unk00C[0x10 - 0xC];
    int32_t i10;               /* +0x10 */
    uint8_t unk014[0x20 - 0x14];
    float   m20[16];           /* +0x20 */
    float   f60, f64;          /* +0x60 */
    uint8_t unk068[0x520 - 0x68];
    float   v520[4];           /* +0x520 */
    float   v530[4];           /* +0x530 */
    float   f540, f544, f548, f54C, f550, f554; /* +0x540 */
    int32_t i558;              /* +0x558 */
} M1Cam132;
void sub_001AD940(float *m);

/* 0x000195F0: reset a camera record: blend 0.05, two identity offsets, lag 0.1, zoom 0.3,
 * no target (-1), active, identity matrix, field of view 45. */
void m1_CamInit0195F0(M1Cam132 *c)
{
    c->f08 = 0.0500000007f;
    c->i04 = 0;
    c->v520[3] = 1.0f;
    c->v530[3] = 1.0f;
    c->v520[2] = 0.0f;
    c->v520[1] = 0.0f;
    c->v520[0] = 0.0f;
    c->v530[2] = 0.0f;
    c->v530[1] = 0.0f;
    c->v530[0] = 0.0f;
    c->f544 = 0.100000001f;
    c->f540 = 0.0f;
    c->f548 = 0.300000012f;
    c->f54C = 0.300000012f;
    c->f550 = 0.0f;
    c->f554 = 0.0f;
    c->i558 = -1;
    c->i10 = 1;
    sub_001AD940(c->m20);
    c->f60 = 45.0f;
    c->f64 = 1.0f;
}

typedef struct M1Pair132 { void *a; void *b; int32_t c; } M1Pair132;
typedef struct M1Res132 {
    uint8_t unk000[0x520];
    int32_t i520;              /* +0x520 */
    void   *mdl524, *mdl528;   /* +0x524 */
    void   *obj52C, *obj530;   /* +0x52C */
    M1Pair132 pairs534[8];     /* +0x534 */
} M1Res132;
void sub_0001F300(void *m);
void sub_00020170(void *m);
void sub_0001E550(void *o);
void sub_00053880(void *p);

/* 0x000E1270: free a scene's models: the eight pairs, the two models and the two objects
 * (unlinked, freed and released), then clear the slots. */
void m1_SceneFree0E1270(M1Res132 *r)
{
    void **q = &r->pairs534[0].b;
    int n = 8;
    do {
        if (q[-1] != 0)
            sub_0001F300(q[-1]);
        if (q[0] != 0)
            sub_0001F300(q[0]);
        q[-1] = 0;
        q[0] = 0;
        q = (void **)((uint8_t *)q + sizeof(M1Pair132));
    } while (--n);
    if (r->mdl524 != 0)
        sub_00020170(r->mdl524);
    if (r->mdl528 != 0)
        sub_00020170(r->mdl528);
    if (r->obj52C != 0) {
        sub_0001E550(r->obj52C);
        sub_0001F300(r->obj52C);
        sub_00053880(r->obj52C);
    }
    if (r->obj530 != 0) {
        sub_0001E550(r->obj530);
        sub_0001F300(r->obj530);
        sub_00053880(r->obj530);
    }
    r->mdl524 = 0;
    r->mdl528 = 0;
    r->obj52C = 0;
    r->obj530 = 0;
    r->i520 = 0;
}
