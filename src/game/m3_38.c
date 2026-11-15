/* Area m3, batch 38. Names inferred. */
#include <stdint.h>

typedef struct M3BmO38 { uint8_t unk00[0x20]; float *m20; uint8_t unk24[0x3C]; float pos60[4]; } M3BmO38;
typedef struct M3BmL38 { M3BmO38 *a; M3BmO38 *b; M3BmO38 *c; } M3BmL38;
typedef struct M3BmH38 { uint8_t unk000[0x520]; int on520; uint8_t unk524[0x10]; M3BmL38 lk534[8]; } M3BmH38;
extern uint8_t *g_playerObj;
extern float m3_beamLen317D10;
void sub_001B8320(void *p);
uint8_t *sub_0001D0F0(void *o, int part);
void a3c_VecCopy(float *dst, const float *src);
float aab_Use82D70(const float *v);
float sub_001A3F20(float a);
void sub_001AD7E0(float *d, const float *s);
void sub_001AD940(float *m);
void sub_001AD8B0(float *d, const float *m, float a);
void sub_001AD8E0(float *d, const float *m, float a);
void sub_001ADA40(void *node, const float *m);
void sub_000E15C0(void *o);

/* 0xE4160: aim up to 8 beam links: for each full link point A's matrix at C's part 2 (pitch and yaw from acos) placed at A, and scale B's matrix by the distance over 35 placed one unit below C's part; then finish the holder. */
void m3_BeamsAimE4160(M3BmH38 *o) {
    float s, d[4], len;
    int n;
    float sc, h, p[4], pitch, yaw, m[16];
    M3BmL38 *e;
    sub_001B8320(*(void **)(g_playerObj + 0x28));
    if (o->on520) {
        e = o->lk534;
        n = 8;
        do {
            M3BmO38 *a = e->a, *b = e->b, *c = e->c;
            if (a && b && c) {
                a3c_VecCopy(p, (float *)(sub_0001D0F0(c, 2) + 0x70));
                p[1] = c->pos60[1];
                d[0] = p[0] - e->a->pos60[0];
                d[1] = p[1] - e->a->pos60[1];
                d[2] = p[2] - e->a->pos60[2];
                d[3] = p[3];
                h = p[1] - e->a->pos60[1];
                len = aab_Use82D70(d);
                s = h / len;
                if (s > 1.0f) s = 1.0f;
                else if (-1.0f > s) s = -1.0f;
                pitch = sub_001A3F20(s);
                d[1] = 0.0f;
                sub_001AD7E0(d, d);
                if (d[2] > 1.0f) d[2] = 1.0f;
                else if (-1.0f > d[2]) d[2] = -1.0f;
                if (d[0] > 0.0f) yaw = sub_001A3F20(d[2]);
                else yaw = -sub_001A3F20(d[2]);
                sub_001AD940(m);
                sub_001AD8B0(m, m, pitch);
                sub_001AD8E0(m, m, yaw);
                sub_001ADA40(a->m20, m);
                a3c_VecCopy(a->m20 + 12, e->a->pos60);
                p[1] = c->pos60[1] - 1.0f;
                sc = len / m3_beamLen317D10;
                sub_001AD940(b->m20);
                b->m20[10] = sc;
                b->m20[5] = sc;
                b->m20[0] = sc;
                a3c_VecCopy(b->m20 + 12, p);
            }
            e++;
        } while (--n);
    }
    sub_000E15C0(o);
}

typedef struct M3SbOb38 { uint8_t unk00[0x10]; uint32_t f10; uint8_t unk14[0x4C]; float pos60[4]; uint8_t unk70[0x30]; float offA0[4]; } M3SbOb38;
typedef struct M3SbRec38 { M3SbOb38 *o; uint8_t unk04[0x10]; float t14; uint8_t unk18[0x3C]; } M3SbRec38;
typedef struct M3SbAc38 { uint8_t unk00[0x54]; float yaw54; } M3SbAc38;
typedef struct M3SbB38 { uint8_t unk00[0x6C]; int mode6C; uint8_t unk70[0x1C]; M3SbAc38 *p8C; void *p90; int show94; int show98;
                         uint8_t unk9C[0x3C]; M3SbRec38 rec[3]; } M3SbB38;
extern M3SbB38 *b10_scr;
extern int m3_minPart278E5C[2];
extern float m3_minOffB278E78[2][4];
void sub_001AD9B0(float *d, const float *m, const float *p);
void sub_001ADB60(float *d, const float *s, int k);

/* 0x101C60: place the screen boss's three sub-objects: pick which are visible by mode (7-9) or the player's height (above -30 shows only the first), pin the first to the hand part and the others to parts 8 and 14 plus rotated offsets, and flag each shown (bit 4) while its timer runs or its show flag is set. */
void m3_ScrParts101C60(void) {
    float v[4], m[16];
    const float *tb;
    M3SbB38 *b = b10_scr;
    M3SbB38 *bb = b;
    M3SbOb38 *s;
    const int *pp;
    uint32_t f;
    uint8_t *tq;
    {
        volatile int md = b->mode6C;
        if (md >= 7 && md <= 9) {
            b->rec[0].o->f10 &= ~1u;
            b->rec[1].o->f10 |= 1;
            b->rec[2].o->f10 |= 1;
        } else if (!(((float *)g_playerObj)[0x19] > -30.0f)) {
            b->rec[0].o->f10 &= ~1u;
            b->rec[1].o->f10 |= 1;
            b->rec[2].o->f10 |= 1;
        } else {
            b->rec[0].o->f10 |= 1;
            b->rec[1].o->f10 &= ~1u;
            b->rec[2].o->f10 &= ~1u;
        }
    }
    s = b->rec[0].o;
    {
        uint8_t *volatile vb = (uint8_t *)b + 0x9C;
        uint8_t *bx = vb;
        a3c_VecCopy(s->pos60, (float *)(sub_0001D0F0(b->p90, 0xC) + 0x70));
        f = s->f10;
        if (b->show94) f |= 4;
        else if (*(float *)(bx + 0x50) > 0.0f) f |= 4;
        else f &= ~4u;
        s->f10 = f;
    }
    sub_001AD940(m);
    sub_001AD8E0(m, m, b->p8C->yaw54);
    tb = m3_minOffB278E78[0];
    tq = (uint8_t *)&b->rec[1].t14;
    for (pp = m3_minPart278E5C; (int32_t)pp < (int32_t)&m3_minPart278E5C[2]; pp++) {
        uint8_t *volatile vq = tq;
        uint8_t *q = vq;
        s = *(M3SbOb38 **)(q - 0x14);
        a3c_VecCopy(s->pos60, (float *)(sub_0001D0F0(bb->p8C, *pp) + 0x70));
        a3c_VecCopy(v, tb);
        sub_001AD9B0(s->offA0, m, v);
        sub_001ADB60(s->offA0, s->offA0, 0x3F800000);
        f = s->f10;
        if (bb->show98) f |= 4;
        else if (*(float *)q > 0.0f) f |= 4;
        else f &= ~4u;
        s->f10 = f;
        tb += 4;
        tq += sizeof(M3SbRec38);
    }
}

typedef struct M3DrS38 { uint8_t unk00[4]; uint8_t *pc4; } M3DrS38;
typedef struct M3DrE38 { uint8_t unk00[0x70]; float f70; } M3DrE38;
int  sub_001C7EE1(void);
void sub_001AE010(float *d, const float *m, const float *v);
void sub_001ADAF0(float *d, const float *a, const float *b);
M3DrE38 *sub_00034390(int a, int b, int c, float *p, float *q, int r, float t);
int  sub_00036750(void *o, int v);
void *sub_00035D80(void *a, int fx, int k);
void sub_00034E00(void *h, const float *pos, const float *dir, const float *up);
extern float a50_framesPerSecond;

/* 0xDCF20: script command: drop effect 0x10 from a random spot around the player (random heading, up to 3 out) to 100-150 below it with radius 6 over a third of a second, play sound 0x39, and when the command's flag byte is set add spark 0x4E 20 below the player; continue (0x2001). */
int m3_ScrDropDCF20(M3DrS38 *s) {
    float a[4], b[4], z[4], x[4], y[4], m[16];
    float ang;
    uint8_t *pl = g_playerObj;
    float *pp = (float *)(pl + 0x60);
    void *h;
    x[0] = 0.0f; x[2] = 0.0f;
    y[0] = 0.0f; y[1] = 0.0f;
    x[1] = 1.0f; x[3] = 1.0f;
    y[2] = -1.0f; y[3] = 1.0f;
    a3c_VecCopy(a, pp);
    a3c_VecCopy(b, a);
    b[1] = (float)((double)b[1] - ((float)sub_001C7EE1() * 3.0518509e-05f * 50.0 + 100.0));
    ang = (float)sub_001C7EE1() * 3.0518509e-05f * 6.2831855f - 3.1415927f;
    sub_001AD940(m);
    z[0] = 0.0f; z[1] = 0.0f; z[2] = 0.0f; z[3] = 1.0f;
    z[2] = (float)((float)sub_001C7EE1() * 3.0518509e-05f * 3.0);
    sub_001AE010(m, m, z);
    sub_001AD8E0(m, m, ang);
    sub_001ADAF0(a, a, m + 12);
    sub_00034390(0, -1, 0x10, a, b, 0x40C00000, a50_framesPerSecond * 0.33333334f)->f70 = 2.0f;
    sub_00036750(pl, 0x39);
    if (*s->pc4) {
        h = sub_00035D80(pl, 0x4E, 3);
        a3c_VecCopy(a, pp);
        a[1] -= 20.0f;
        sub_00034E00(h, a, y, x);
    }
    return 0x2001;
}
