/* Area m1, file 287: mesh hit tests. Names inferred. */
#include <stdint.h>

typedef struct M1Vx287 { float v[4]; } M1Vx287;
typedef struct M1Mb287 { uint8_t unk00[0x80]; float c80[4]; float r90; } M1Mb287;
typedef struct M1Hit287 { uint8_t unk00[0x40]; float pos40[4]; } M1Hit287;
float sub_001B2770(const float *a, const float *b);           /* distance */
void *sub_00080970(void);                                    /* new hit list */
void m1_BandTri1B8D0(int32_t n, M1Mb287 *base, M1Vx287 **b, M1Vx287 **c, M1Vx287 **a);
void sub_0001B7B0(void *lst, M1Vx287 *c, M1Vx287 *a, M1Vx287 *b, const float *p, float r);   /* regargs: lst=EDI c=EBX */
M1Hit287 *sub_00080CF0(void *lst, const float *p);
void sub_000F5D40(float *d, const float *s);
void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
void sub_001AD7E0(float *d, const float *s);                  /* normalise */

/* 0x0001B9E0: test sphere (p, r) against band mesh m: skip when out of m's bounding sphere; otherwise collect
   the sphere's contacts with all 12 triangles and take the nearest. On a hit store the contact point and the
   unit push-out direction (either may be omitted) and return 1, else 0. */
int32_t m1_MeshSphereHit1B9E0(M1Mb287 *m, const float *p, float r, float *hitPos, float *hitDir)
{
    void *lst;
    int32_t i;
    M1Vx287 *a, *b, *c;
    M1Hit287 *h;
    if (sub_001B2770(m->c80, p) > r + m->r90) return 0;
    lst = sub_00080970();
    for (i = 0; i < 12; i++) {
        m1_BandTri1B8D0(i, m, &b, &c, &a);
        sub_0001B7B0(lst, c, a, b, p, r);
    }
    h = sub_00080CF0(lst, p);
    if (!h) return 0;
    if (hitPos)
        sub_000F5D40(hitPos, h->pos40);
    if (hitDir) {
        sub_001AD9F0(hitDir, h->pos40, p);
        sub_001AD7E0(hitDir, hitDir);
    }
    return 1;
}

typedef struct M1Tp287 { int16_t on0, id2; float vol4; int16_t b8, aA; void *srcC; float f10; } M1Tp287;   /* 0x14 */
typedef struct M1Tr287 { int16_t on0, w2; M1Tp287 part[4]; } M1Tr287;                                     /* 0x54 */
extern M1Tr287 m1_tracks3DFEE0[];
extern float m1_frameRate42C85C;
void sub_00048B70(void *src, int32_t *a, int32_t *b, int32_t x, float y, int32_t z0, int32_t z1);   /* regargs: src=EAX a=EDI b=EBX */
void sub_0019AC70(int32_t t, int32_t p, int32_t id, int32_t b, int32_t a);

/* 0x00049180: set part p of track t: id, volume, source and parameters (the source's two values, or 0x5A /
   0x80 without a source); start it right away unless the volume is above one frame step. */
void m1_TrackSetPart49180(int32_t t, int32_t p, int32_t id, float vol, void *src, int32_t w, float f)
{
    int32_t a, b;
    M1Tp287 *e;
    if (src) {
        sub_00048B70(src, &a, &b, w, f, 0, 0);
    } else {
        b = 0x5A;
        a = 0x80;
    }
    m1_tracks3DFEE0[t].w2 = (int16_t)w;
    m1_tracks3DFEE0[t].on0 = 1;
    e = &m1_tracks3DFEE0[t].part[p];
    e->f10 = f;
    e->on0 = 1;
    e->id2 = (int16_t)id;
    e->vol4 = vol;
    e->b8 = (int16_t)b;
    e->aA = (int16_t)a;
    e->srcC = src;
    if (m1_frameRate42C85C >= vol)
        sub_0019AC70(t, p, id, b, a);
}
