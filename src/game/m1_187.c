/* Area m1, file 187: model pose helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Pose187 { uint8_t unk00[0x60]; uint8_t node60[0x84]; float v[4][4]; float w[4][4]; } M1Pose187;
void r4b_NodeRebuild(void *node);
void sub_00079B40(M1Pose187 *p);

/* 0x7ABB0: reset a model pose: rebuild its node, set its seven 4-vectors (from +0xE4) to (0,0,0,1), then rebuild (0x79B40). */
void m1_PoseReset07ABB0(M1Pose187 *p) {
    float *f = (float *)((uint8_t *)p + 0xE4);
    r4b_NodeRebuild(p->node60);
#define Z(o) f[(o) / 4] = 0.0f, f[(o) / 4 + 1] = 0.0f, f[(o) / 4 + 2] = 0.0f, f[(o) / 4 + 3] = 1.0f
    Z(0x60); Z(0x00); Z(0x20); Z(0x40); Z(0x10); Z(0x30); Z(0x50);
#undef Z
    sub_00079B40(p);
}

#include <string.h>
#pragma intrinsic(strcmp)
typedef struct M1Scr187 { char *text0; uint8_t unk04[0xE34]; } M1Scr187;
extern M1Scr187 a60_save3E83F0;
extern M1Scr187 m1_scrCopy4326A0;
extern const char *m1_scrCmds2E0138[];
char *r1d_ReadLine(char **cur);
char *r1b_NextToken(char **cur);
void  sub_0007A4F0(char *s);
void  sub_0007A610(char *s);
void  m1_CmdColor07A8B0(char *s);

/* 0x7AD20: run the saved script text: copy it to the work buffer, then for each line look up its command word and run commands 0x2D..0x2F. */
int m1_ScriptRun07AD20(int unused, int r) {
    char *line, *cur, *tok; const char *s; int k;
    if (a60_save3E83F0.text0 == 0) return r;
    m1_scrCopy4326A0 = a60_save3E83F0;
    cur = m1_scrCopy4326A0.text0;
    for (line = r1d_ReadLine(&cur); line != 0; line = r1d_ReadLine(&cur)) {
        tok = r1b_NextToken(&line);
        if (tok == 0) continue;
        k = 0;
        for (s = m1_scrCmds2E0138[0]; s != 0 && strcmp(s, tok) != 0; s = m1_scrCmds2E0138[++k]) ;
        switch (k) {
        case 0x2D: sub_0007A4F0(line); break;
        case 0x2E: sub_0007A610(line); break;
        case 0x2F: m1_CmdColor07A8B0(line); break;
        }
    }
    return r;
}

void a3c_VecCopy(float *dst, const float *src);
void r6c_RotateVec(float *out, const float *ang, const float *axis);
void r4_MatBuildW1(void *m, const float *r0, const float *r1, const float *r2);
void rtc_MatrixOp40(void *m, void *a, void *b, void *c, void *d);

/* 0x79B40: rebuild a pose matrix from its three Euler angle rows (degrees, at +0xF4 stride 0x20), then from its translation/scale vectors. */
void m1_PoseBuild079B40(uint8_t *p) {
    float v[4], q[4], r[3][4]; float *src, *dst; int n;
    uint8_t *b = p + 0xE4;
    src = (float *)(b + 0x10); dst = r[0];
    for (n = 3; n != 0; n--, src += 8, dst += 4) {
        a3c_VecCopy(v, src);
        v[0] = v[0] * 3.14159274f * 0.00555555569f;
        v[1] = v[1] * 3.14159274f * 0.00555555569f;
        v[2] = v[2] * 3.14159274f * 0.00555555569f;
        v[3] = 1.0f;
        q[0] = 0.0f; q[1] = 0.0f; q[2] = 1.0f; q[3] = 1.0f;
        r6c_RotateVec(dst, v, q);
    }
    r4_MatBuildW1(p + 0x60, r[0], r[1], r[2]);
    rtc_MatrixOp40(p + 0x60, b, b + 0x20, b + 0x40, p + 0x144);
}
