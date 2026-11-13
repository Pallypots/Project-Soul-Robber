/* Area m1, file 47: scene globals reset. Names inferred. */
#include <stdint.h>

extern void   *m1_sceneObj3FDE68, *m1_sceneAct3FDE6C;   /* 0x003FDE68 pair */
extern void   *m1_resA3FDE70, *m1_resB3FDE74, *m1_resC3FDE78, *m1_resD3FDE7C, *m1_resE3FDE80, *m1_resF3FDE84;
extern float   m1_f3FDE88;
extern int32_t m1_i3FDE8C;
extern int16_t m1_w3FDE90;
extern float   m1_f3FDE94;
extern int16_t m1_w3FDE98;
extern float   m1_f3FDE9C, m1_f3FDEA0, m1_f3FDEB4, m1_f3FDEB8, m1_f3FDEBC, m1_f3FDEC0;

/* 0x0017D780: clears the scene's pair, six resources and state values; +0xC0 = 1.0. */
void m1_SceneReset17D780(void)
{
    m1_f3FDE88 = 0.0f;
    m1_f3FDE94 = 0.0f;
    m1_f3FDE9C = 0.0f;
    m1_f3FDEA0 = 0.0f;
    m1_f3FDEB4 = 0.0f;
    m1_f3FDEB8 = 0.0f;
    m1_f3FDEBC = 0.0f;
    m1_sceneObj3FDE68 = 0;
    m1_sceneAct3FDE6C = 0;
    m1_resA3FDE70 = 0;
    m1_resB3FDE74 = 0;
    m1_resC3FDE78 = 0;
    m1_resD3FDE7C = 0;
    m1_resE3FDE80 = 0;
    m1_resF3FDE84 = 0;
    m1_i3FDE8C = 0;
    m1_w3FDE90 = 0;
    m1_w3FDE98 = 0;
    m1_f3FDEC0 = 1.0f;
}

typedef struct M1Cam850 {
    uint8_t unk000[0x794];
    float   f794, f798;        /* +0x794 */
    int32_t v79C[4];           /* +0x79C */
    int32_t f7AC;              /* +0x7AC */
    float   f7B0;              /* +0x7B0 */
    uint8_t unk7B4[0x850 - 0x7B4];
    int32_t v850[5];           /* +0x850 */
} M1Cam850;
typedef struct M1Info0C { uint8_t unk00[0xC]; int32_t n0C; } M1Info0C;

/* 0x000EACC0: sets both scale values to info's count * 0.001, copies the five saved
 * words back from +0x850 and sets +0x7B0 = 1.0. */
void m1_RestoreViewEACC0(M1Cam850 *c, M1Info0C *in)
{
    if (c == 0 || in == 0)
        return;
    c->f794 = (float)in->n0C * 0.001f;
    c->v79C[0] = c->v850[0];
    c->v79C[1] = c->v850[1];
    c->f798 = (float)in->n0C * 0.001f;
    c->v79C[2] = c->v850[2];
    c->v79C[3] = c->v850[3];
    c->f7AC = c->v850[4];
    c->f7B0 = 1.0f;
}
