/* Area m1, file 157: figure viewer setup. Names inferred. */
#include <stdint.h>

typedef struct M1Sk157 { uint8_t unk00[0x1B0]; float f1B0; float f1B4; } M1Sk157;
typedef struct M1Md157 { uint8_t unk00[0xC4]; M1Sk157 *skC4; } M1Md157;
typedef struct M1Fig157 { uint8_t unk00[0x20]; M1Md157 *mdl20; uint8_t unk24[0x3C]; float v60[4]; float v70[4]; } M1Fig157;
typedef struct M1Lt157 { uint8_t unk00[8]; void *cb8; uint8_t rest[0x40]; } M1Lt157;
typedef struct M1Scn157 { uint8_t unk00[0x198]; float f198; uint8_t unk19C[0x10]; float f1AC; } M1Scn157;
extern int32_t m1_figIdx3E0020;
extern uint8_t m1_figTbl2C7E08[];
extern M1Fig157 *m1_fig3E00E8;
extern M1Lt157 m1_figLight3E0530;
extern int32_t m1_figMode3E0000[4];
extern uint8_t m1_fadeBuf428F40[];
extern M1Scn157 *m1_scene42C8E4;
void m1_SysInit037230(void);
void m1_SysInit037060(void);
void m1_FigLoad037000(int id);
void sub_0004F4E0(void);
void sub_000580D0(void);
M1Fig157 *m1_LoadFigure371A0(int id);
void sub_0001EBF0(void *o, int k);
void sub_001AD8E0(void *d, void *s, float a);
void sub_001B2150(M1Lt157 *l);
void m1_LightInit1B2160(void *m, M1Lt157 *l);
void m1_FigLightCb04BF00(void);
void m1_FadeStart72EE0(void *buf, int a, float t, int b);

/* 0x4E030: open the figure viewer: load the chosen figure, face it to the camera, light it, fade in. */
void m1_FigViewOpen04E030(void) {
    m1_SysInit037230();
    m1_SysInit037060();
    m1_FigLoad037000(m1_figTbl2C7E08[m1_figIdx3E0020]);
    sub_0004F4E0();
    sub_000580D0();
    sub_000580D0();
    sub_000580D0();
    m1_fig3E00E8 = m1_LoadFigure371A0(m1_figTbl2C7E08[m1_figIdx3E0020]);
    sub_0001EBF0(m1_fig3E00E8, 3);
    sub_001AD8E0(m1_fig3E00E8->mdl20, m1_fig3E00E8->mdl20, 3.14159274f);
    m1_fig3E00E8->v60[0] = 0.0f - m1_fig3E00E8->mdl20->skC4->f1B0;
    m1_fig3E00E8->v60[1] = 0.0f - m1_fig3E00E8->mdl20->skC4->f1B4;
    m1_fig3E00E8->v60[2] = 0.0f - m1_fig3E00E8->mdl20->skC4->f1B0;
    m1_fig3E00E8->v60[3] = 1.0f;
    m1_fig3E00E8->v70[0] = 1.0f;
    m1_fig3E00E8->v70[1] = 1.0f;
    m1_fig3E00E8->v70[2] = 1.0f;
    m1_fig3E00E8->v70[3] = 0.0f;
    m1_scene42C8E4->f1AC = 50.0f;
    m1_scene42C8E4->f198 = 3.14159274f;
    sub_001B2150(&m1_figLight3E0530);
    m1_figLight3E0530.cb8 = (void *)m1_FigLightCb04BF00;
    m1_LightInit1B2160(m1_fig3E00E8->mdl20, &m1_figLight3E0530);
    m1_figMode3E0000[0] = 2; m1_figMode3E0000[1] = 1; m1_figMode3E0000[2] = 0; m1_figMode3E0000[3] = 0;
    m1_FadeStart72EE0(m1_fadeBuf428F40, 0, 8.0f, 0);
}

#include <stdlib.h>
#include <xmmintrin.h>
typedef struct M1Bn157 { uint8_t unk00[0x20]; uint8_t *x20; } M1Bn157;
typedef struct M1Pw157 {
    uint8_t unk00[0x1B8]; int32_t mode1B8; uint8_t unk1BC[0xD94 - 0x1BC]; float tD94;
    uint8_t unkD98[0xFC0 - 0xD98]; float vFC0[4]; uint8_t unkFD0[8]; void *mdlFD8;
} M1Pw157;
typedef struct M1Sc157 { uint8_t unk00[0x3B0]; void *x3B0; } M1Sc157;
extern M1Sc157 *m1_scene2_42C8EC;
extern float m1_col418B30[3];
void m1_PowerGlow0C9E30(M1Pw157 *o);
void sub_000D04E0(void *t, float *c);
M1Bn157 *m1_ObjBone01D290(void *o, int k);

/* 0xCA6C0: ease the power-up glow colour toward its target and push it to the light and the model. */
void m1_PowerTint0CA6C0(M1Pw157 *o) {
    void *t = m1_scene2_42C8EC->x3B0; float c[4], r, d; float *p; int i; M1Bn157 *b;
    c[0] = 0.0f; c[1] = 0.0f; c[2] = 255.0f; c[3] = 1.0f;
    m1_PowerGlow0C9E30(o);
    r = o->tD94 * 0.00138888892f;
    for (i = 0, p = o->vFC0; i < 3; i++, p++) {
        d = (float)abs(_mm_cvtt_ss2si(_mm_set_ss(*p - c[i])));
        if (c[i] > *p) d *= -1.0f;
        c[i] = r * d + c[i];
        if (c[i] > 255.0f) c[i] = 255.0f;
        if (0.0f > c[i]) c[i] = 0.0f;
    }
    c[3] = 128.0f;
    sub_000D04E0(t, c);
    m1_col418B30[0] = c[0]; m1_col418B30[1] = c[1]; m1_col418B30[2] = c[2];
    if (o->mode1B8 != 0) return;
    b = m1_ObjBone01D290(o->mdlFD8, 1);
    c[3] = 128.0f;
    ((float *)(b->x20 + 0xD0))[0] = c[0];
    ((float *)(b->x20 + 0xD0))[1] = c[1];
    ((float *)(b->x20 + 0xD0))[2] = c[2];
    ((float *)(b->x20 + 0xD0))[3] = c[3];
}
