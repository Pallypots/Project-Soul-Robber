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
