/* Area m1, file 161: helper speed setters (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Anm161 { uint8_t unk00[0x30]; void *anim30; } M1Anm161;
typedef struct M1Hlp161 { uint8_t unk00[0x8C]; M1Anm161 *o8C; uint8_t unk90[0x18]; float fA8; uint8_t unkAC[0x1C]; float fC8; int32_t iCC; uint8_t unkD0[0x28]; int32_t xF8; } M1Hlp161;
extern M1Hlp161 *m1_helper3F611C;
extern float m1_fps42C964;
void sub_000832D0(void *a, int id);

/* Pick the helper's walk (1, 16.5) or run (2, 40) animation and set its speed and spin rate. */
#define M1_HLPSPEED161(name, K, TAIL) \
void name(void) { \
    M1Hlp161 *m = m1_helper3F611C; M1Anm161 *p = m->o8C; volatile float r; float q; \
    if (m->xF8 != 0) { \
        if (p == 0) for (;;) ; \
        sub_000832D0(p->anim30, 1); r = 16.5f; \
    } else { \
        if (p == 0) for (;;) ; \
        sub_000832D0((*(M1Anm161 *volatile *)&p)->anim30, 2); r = 40.0f; \
    } \
    q = r / m1_fps42C964; \
    m1_helper3F611C->fA8 = q; \
    m1_helper3F611C->fC8 = q * K * 6.28318548f; \
    TAIL \
}

/* 0xFC8F0, 0xFCC20, 0xFC970: three helper speed variants (0xFC970 also clears the spin phase). */
M1_HLPSPEED161(m1_HelperSpeedA0FC8F0, 0.0039788736f, )
M1_HLPSPEED161(m1_HelperSpeedB0FCC20, 0.0056841047f, )
M1_HLPSPEED161(m1_HelperSpeedC0FC970, 0.0039788736f, m1_helper3F611C->iCC = 0;)


typedef struct M1Ob161b { uint8_t unk00[0x60]; float pos60[4]; } M1Ob161b;
typedef struct M1Fx161b { uint8_t unk00[0xE4]; int32_t snd0E4; } M1Fx161b;
M1Fx161b *sub_0001D960(M1Ob161b *o, int k);
int  sub_000494D0(int id, void *pos, int k);
void *sub_00036750(M1Ob161b *o, int id);

/* 0x10FA20: start the object's loop sound once, then play its open (8) or close (9) animation. */
void m1_ObjSndAnim10FA20(M1Ob161b *o, int open) {
    M1Fx161b *f;
    if (o == 0) for (;;) ;
    f = sub_0001D960(o, 5);
    if (f->snd0E4 < 0) f->snd0E4 = sub_000494D0(0x3B2, o->pos60, 1);
    { void *volatile r;
    if (open != 0) r = sub_00036750(o, 8);
    else r = sub_00036750(o, 9); }
}

uint8_t *sub_0001D0F0(void *o, int b);

/* Hit reaction: impact sound at the hit bone, then the light (4) or heavy (5) flinch animation. */
#define M1_HITREACT161(name, K) \
void name(M1Ob161b *o, int light) { \
    void *volatile r; \
    if (o == 0) for (;;) ; \
    sub_000494D0(0x3B2, sub_0001D0F0(o, 0x11) + 0x70, K); \
    if (light != 0) r = sub_00036750(o, 4); \
    else r = sub_00036750(o, 5); \
}

/* 0x107760 / 0xEEF40: twins that differ only in the sound flag. */
M1_HITREACT161(m1_HitReact107760, 0)
M1_HITREACT161(m1_HitReact0EEF40, 1)


typedef struct M1Fog161 {
    uint8_t unk00[0x44]; void *x44; uint8_t unk48[0x1B8 - 0x48]; uint8_t b1B8; uint8_t unk1B9[3];
    float near1BC; float far1C0; int32_t c1C4; int32_t c1C8; int32_t c1CC;
} M1Fog161;
int m1_FogSet084910(void *ctx, float n, float f, int a, int b, int c, float d);

/* 0x79EF0: apply the scene fog (or a neutral setting when fog is off). */
void m1_FogApply079EF0(M1Fog161 *s) {
    int volatile r;
    if (s->b1B8 & 1) r = m1_FogSet084910(s->x44, s->near1BC, s->far1C0, s->c1C4, s->c1C8, s->c1CC, 128.0f);
    else r = m1_FogSet084910(s->x44, 1.0f, 0.0f, s->c1C4, s->c1C8, s->c1CC, 128.0f);
}

