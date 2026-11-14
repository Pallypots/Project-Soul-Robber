/* Area m1, file 135: screen markers. Names inferred. */
#include <stdint.h>

typedef struct M1View135 { uint8_t unk000[0x1F0]; float proj1F0[16]; float view230[16]; } M1View135;
typedef struct M1Scene135 { uint8_t unk00[0x44]; void *cams44; } M1Scene135;
extern M1Scene135 *m1_scene42C8E4;
extern uint8_t m1_flags37C4F8;
extern int32_t m1_mkIdTbl2826B0[];
M1View135 *sub_000847F0(void *c, int id);
void sub_000F5D40(float *d, const float *s);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_001AE140(int32_t *d, const float *m, const float *v, int a);

/* Screen marker: unless markers are off, project pos raised by h through camera 9; when it is
 * in front and nearer than 300, store the screen position (biased fixed point), the depth
 * scale 1.5 - z/250, the marker id for idx (0..2, hangs otherwise) and mark it shown. */
#define M1_MARK135(name, tblofs, on, x, y, w, id)                   \
extern int32_t on, x, y, id;                                        \
extern float w;                                                     \
void name(const float *pos, float h, unsigned int idx)              \
{                                                                   \
    struct { float p[4]; int32_t s[4]; float q[4]; } l;             \
    M1View135 *c;                                                   \
    if (idx >= 3)                                                   \
        for (;;) ;                                                  \
    if (!(m1_flags37C4F8 & 1))                                      \
        return;                                                     \
    c = sub_000847F0(m1_scene42C8E4->cams44, 9);                    \
    sub_000F5D40(l.p, pos);                                         \
    l.p[1] = l.p[1] + h;                                            \
    sub_001AD9B0(l.q, c->view230, l.p);                             \
    if (!(l.q[2] > 0.0f) || !(300.0f > l.q[2]))                     \
        return;                                                     \
    sub_001AE140(l.s, c->proj1F0, l.p, 0);                          \
    x = (l.s[0] - 0x8000) >> 4;                                     \
    y = (l.s[1] - 0x8000) >> 3;                                     \
    w = 1.5f - l.q[2] * 0.00400000019f;                             \
    id = m1_mkIdTbl2826B0[idx + (tblofs)];                          \
    on = 1;                                                         \
}

/* 0x000262A0: marker A. */
M1_MARK135(m1_MarkerA0262A0, 0, m1_mkA37F0CC, m1_mkA37F0D0, m1_mkA37F0D4, m1_mkA37F0D8, m1_mkA37F3D4)
/* 0x000263B0: marker B (ids from the table's second triple). */
M1_MARK135(m1_MarkerB0263B0, 3, m1_mkB37F0E0, m1_mkB37F0E4, m1_mkB37F0E8, m1_mkB37F0EC, m1_mkB37F470)
