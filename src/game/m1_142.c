/* Area m1, file 142: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Lt142 { uint8_t unk00[0x8C]; int32_t type8C; uint8_t unk90[0xCC - 0x90]; float c[4]; int32_t w; } M1Lt142;
typedef struct M1Ln142 {
    uint8_t unk00[0x20]; M1Lt142 *obj20; uint8_t unk24[0x3C - 0x24]; struct M1Ln142 *next3C;
    uint8_t unk40[0x90 - 0x40]; float c90; float c94; float c98; int32_t w9C;
} M1Ln142;
void sub_001B3160(M1Lt142 *o);

/* 0xEE760: scale the colour of every light in a list by one factor. */
void m1_LightDim0EE760(M1Ln142 *n, float s) {
    M1Lt142 *o;
    if (n == 0) return;
    do {
        o = n->obj20;
        if (o != 0) {
            switch (o->type8C) {
            case 9:
                o->c[1] = n->c90 * s; o->c[2] = n->c94 * s; o->c[3] = n->c98 * s; o->w = n->w9C;
                break;
            case 1:
                o->c[0] = n->c90 * s; o->c[1] = n->c94 * s; o->c[2] = n->c98 * s;
                *(int32_t *)&o->c[3] = n->w9C;
                sub_001B3160(o);
                break;
            }
        }
        n = n->next3C;
    } while (n != 0);
}

typedef struct M1Scr142 { void *top; int32_t a; int32_t b; } M1Scr142;
typedef struct M1Clr142 { float r0[4]; float r1[4]; uint32_t c[4]; int32_t fade; int32_t z; } M1Clr142;
extern int32_t m1_scrIdx42CAC0;
extern M1Scr142 m1_scrTbl42CAC8[];
extern int32_t m1_mode3816D0;
extern uint32_t m1_wipe381400;
extern int32_t m1_wipeT3813FC;
void  sub_001A5310(void);
void  sub_001A7B90(void);
void  sub_000580D0(void);
void *sub_00072420(void *s, M1Clr142 *c);
void *m1_ScrWrap02C760(void *s);
void *sub_0002CF80(void *s);

/* 0x2E2F0: main frame loop; draws the wipe overlay while it is active. */
void m1_MainLoop02E2F0(void) {
    M1Clr142 l; void *s;
    for (;;) {
        s = m1_scrTbl42CAC8[m1_scrIdx42CAC0].top;
        sub_001A5310();
        if (m1_mode3816D0 == 10000 && m1_wipe381400 < 3) {
            l.fade = m1_wipeT3813FC; l.z = 0;
            l.r0[0] = 0.0f; l.r0[2] = 512.0f; l.r0[1] = 0.0f; l.r0[3] = 448.0f;
            l.r1[0] = 0.0f; l.r1[1] = 0.0f; l.r1[2] = 512.0f; l.r1[3] = 448.0f;
            l.c[3] = 0x80808080; l.c[2] = 0x80808080; l.c[1] = 0x80808080; l.c[0] = 0x80808080;
            s = sub_0002CF80(m1_ScrWrap02C760(sub_00072420(s, &l)));
        }
        sub_001A7B90();
        m1_scrTbl42CAC8[m1_scrIdx42CAC0].top = s;
        sub_000580D0();
    }
}


typedef struct M1Cam142 {
    uint8_t unk00[0xA8]; int16_t wA8; uint8_t unkAA[0x100 - 0xAA];
    int32_t m100; int32_t m104; int32_t m108; float t10C;
} M1Cam142;
extern M1Cam142 *m1_cam3F610C;
extern uint32_t m1_level413178;
extern float m1_frameRate42C85C;
extern float m1_shkLimA27886C[3];
extern float m1_shkLimB278878[3];
extern float m1_shkRateA27889C[3];
extern float m1_shkRateB2788A8[3];
void m1_CamShake0F4470(float r);

/* 0xF50E0: run the camera shake timer; fires the shake when it passes the limit. */
void m1_CamShakeTick0F50E0(void) {
    M1Cam142 *c = m1_cam3F610C; uint32_t n; float r, lim;
    if (c->m104 == 2 || c->m100 != 1) return;
    if (c->m108 != 2) { c->t10C = 0.0f; return; }
    n = m1_level413178;
    if (n > 2) n = 2;
    if (c->wA8 == 0) { r = 10.0f; lim = 0.800000012f; }
    else if (c->m104 == 0) { r = m1_shkRateA27889C[n]; lim = m1_shkLimA27886C[n]; }
    else if (c->m104 == 1) { r = m1_shkRateB2788A8[n]; lim = m1_shkLimB278878[n]; }
    else lim = r;
    if (c->t10C > lim) { m1_CamShake0F4470(r); return; }
    c->t10C += m1_frameRate42C85C;
}
