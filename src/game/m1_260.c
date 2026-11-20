/* Area m1, file 260: AI choices. Names inferred. */
#include <stdint.h>

typedef struct M1Ob260 { uint8_t unk00[0x30]; int32_t h30; } M1Ob260;
typedef struct M1Ac260 { uint8_t unk00[0x20]; uint8_t b20; } M1Ac260;
int32_t sub_000833E0(int32_t h);
int32_t sub_001C7EE1(void);                                   /* rand */
int32_t sub_001C7EE1b(void);                                  /* rand again (alias stops cl merging the branches) */
void m1_AiGoto113040(M1Ob260 *o, M1Ac260 *a, int32_t st);
void sub_00113040b(M1Ob260 *o, M1Ac260 *a, int32_t st);

/* 0x00138FB0: once o's animation finishes, pick the next AI state: usually 0xD, but one time in eight 0x10
   (flagged actors) or 0x1B. */
void m1_AiNext138FB0(M1Ob260 *o, M1Ac260 *a)
{
    if (sub_000833E0(o->h30) == 0) return;
    if (a->b20 & 1)
        m1_AiGoto113040(o, a, sub_001C7EE1() % 8 >= 1 ? 0xD : 0x10);
    else
        sub_00113040b(o, a, sub_001C7EE1b() % 8 >= 1 ? 0xD : 0x1B);
}

typedef struct M1Quad260 { float uv0[4]; float uv1[4]; uint32_t col[4]; int32_t tex30; int32_t z34; } M1Quad260;
extern int32_t m1_mode3E3950;
extern int32_t m1_tex3E3914;
void sub_00072420(void *dl, M1Quad260 *q);

/* 0x000541B0: in modes 0 and 1, draw a full 512x448 screen quad with texture 0x003E3914 at mid grey.
   regargs: dl=EAX. */
void m1_ScreenQuad541B0(void *dl)
{
    M1Quad260 q;
    if (m1_mode3E3950 != 0 && m1_mode3E3950 != 1) return;
    q.col[0] = 0x80808080;
    q.col[1] = 0x80808080;
    q.col[2] = 0x80808080;
    q.col[3] = 0x80808080;
    q.uv0[0] = 0.0f;
    q.uv0[1] = 0.0f;
    q.uv0[2] = 512.0f;
    q.uv0[3] = 448.0f;
    q.uv1[0] = 0.0f;
    q.uv1[1] = 0.0f;
    q.uv1[2] = 512.0f;
    q.uv1[3] = 448.0f;
    q.tex30 = m1_tex3E3914;
    q.z34 = 0;
    sub_00072420(dl, &q);
}

typedef struct M1Pk260 { uint8_t unk00[8]; int32_t total8; int32_t left0C; uint8_t unk10[4]; int32_t n14; uint32_t nib18[0x58];
    int32_t chunk178; } M1Pk260;
typedef struct M1Cmd260 { uint64_t tag0; uint64_t regs8; } M1Cmd260;

/* 0x00038B50: emit one GIF-style tag: pack s's n 4-bit register ids (last first) into the 64-bit register
   word, take as many of the remaining loops as fit below 0x7FFF (rounded to s->chunk178), and write the tag
   (count | 0x8000, n in the top nibble). Returns the address after the 16-byte tag. regargs: s=ECX. */
M1Cmd260 *m1_PackTag38B50(M1Pk260 *s, M1Cmd260 *out)
{
    uint64_t regs = 0;
    int32_t n = s->n14;
    int32_t i, take, lim;
    const uint32_t *p;
    i = n - 1;
    if (i >= 0) {
        p = &s->nib18[i];
        i++;
        do {
            regs = (regs << 4) | (*p & 0xF);
            p--;
        } while (--i);
    }
    lim = 0x7FFF - 0x7FFF % s->chunk178;
    take = s->left0C;
    if (take >= lim)
        take = lim;
    s->total8 = n * take;
    s->left0C -= take;
    out->regs8 = regs;
    out->tag0 = (int64_t)(take | 0x8000) | ((int64_t)s->n14 << 60);
    return out + 1;
}
