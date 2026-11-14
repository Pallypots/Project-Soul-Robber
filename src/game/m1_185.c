/* Area m1, file 185: transform helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Nd185 { uint8_t unk00[0x20]; float *mtx20; } M1Nd185;
typedef struct M1Xf185 { uint8_t unk00[0x10]; M1Nd185 *nd10; float scale14, mul18; float off1C[3]; } M1Xf185;
void r4c_VecScale(float *dst, const float *src, float s);

/* 0x1ECD0: copy a node's matrix into out with its three axes scaled by scale*mul and its position offset. */
void m1_XfApply01ECD0(float *out, M1Xf185 *x) {
    M1Nd185 *n = x->nd10;
    float *m;
    if (n->mtx20 == 0) return;
    r4c_VecScale(out, n->mtx20, x->scale14 * x->mul18);
    r4c_VecScale(out + 4, n->mtx20 + 4, x->scale14 * x->mul18);
    r4c_VecScale(out + 8, n->mtx20 + 8, x->scale14 * x->mul18);
    m = n->mtx20 + 12;
    out[12] = m[0] + x->off1C[0];
    out[13] = m[1] + x->off1C[1];
    out[14] = m[2] + x->off1C[2];
    ((int32_t *)out)[15] = ((int32_t *)m)[3];
}

typedef struct M1Spr185 { float x0, y4; uint8_t unk08[0x84]; uint32_t col8C; uint8_t unk90[0xC]; } M1Spr185;
extern uint8_t r6i_alpha42AC84;
extern int8_t m1_opt413147;
extern uint32_t m1_iconMask26E728[];
extern int32_t a60_val3E6938;
extern uint8_t m1_meter428F82;
extern M1Spr185 m1_icons42BCFC[5];
void  sub_000150B0(void *spr, int frame);
void *m1_TextDraw017C00(void *dl, void *spr);
void  r1i_SeqPlayUpdate(void *spr);

/* 0x6E960: draw the five status icons: off (frame 3i), on (3i+1) or full (3i+2, when forced or the meter is at 0xF0+), faded by the global alpha. */
void *m1_IconsDraw06E960(void *dl) {
    uint32_t col = ((uint32_t)r6i_alpha42AC84 << 24) + 0x808080;
    M1Spr185 *s; int i, f, fr;
    for (i = 0, f = 2, s = m1_icons42BCFC; (int32_t)s < (int32_t)&m1_icons42BCFC[5]; s++, i++, f += 3) {
        s->col8C = col; s->x0 = 0.0f; s->y4 = 0.0f;
        fr = f - 2;
        if ((1 << i) & m1_iconMask26E728[m1_opt413147]) {
            if (a60_val3E6938 == 1) fr = f;
            else { fr = f - 1; if (m1_meter428F82 >= 0xF0) fr = f; }
        }
        sub_000150B0(s, fr);
        dl = m1_TextDraw017C00(dl, s);
        r1i_SeqPlayUpdate(s);
    }
    return dl;
}

typedef struct M1Key185 { float dur0; int32_t a4, a8, aC, a10, a14, a18; int32_t unk1C; } M1Key185;
typedef struct M1Seq185 { int32_t unk0; int32_t n4; int32_t unk8[2]; M1Key185 keys10[1]; } M1Seq185;
typedef struct M1UvA185 { struct M1UvA185 *next0; uint8_t unk04[0xC]; M1Seq185 *seq10; int32_t tex14; int32_t arg18; int32_t idx1C; float t20; } M1UvA185;
extern M1UvA185 *m1_uvAnims3E6978;
extern float m1_frameTime42C858;
void sub_00084C90(int tex, int a, int b, int c, int d, int e, int f, int g);
uint8_t *r4b_TexEntGet(int tex);

/* 0x754F0: step every texture-UV animation: advance to the next key when its time runs out (wrapping), apply the key on entry and mark the texture dirty. */
void m1_UvAnimStep0754F0(void) {
    M1UvA185 *a; M1Seq185 *s; M1Key185 *k;
    for (a = m1_uvAnims3E6978; a != 0; a = a->next0) {
        s = a->seq10;
        k = &s->keys10[a->idx1C];
        if (a->t20 > k->dur0) {
            a->idx1C++; a->t20 = 0.0f; k++;
            if (a->idx1C >= s->n4) { a->idx1C = 0; k = s->keys10; }
        }
        if (a->t20 == 0.0f) {
            sub_00084C90(a->tex14, k->a4, k->a8, a->arg18, k->aC, k->a10, k->a14, k->a18);
            r4b_TexEntGet(a->tex14)[0x10] |= 8;
        }
        a->t20 += m1_frameTime42C858;
    }
}

typedef struct M1Pt185 { float f0, f4; } M1Pt185;
typedef struct M1Ob185 { uint8_t unk00[0x10]; M1Pt185 pos10; uint8_t unk18[0x4C]; int32_t pack64; } M1Ob185;
typedef struct M1Hit185 { int32_t kind0; uint8_t unk04[0xCC]; uint32_t nD0; uint8_t unkD4[0xF4]; float f1C8; uint8_t unk1CC[0x128]; } M1Hit185;
void r1d_KeyDecode(int pack, int ctx, int *a, int *b);
M1Hit185 *sub_00035000(int ctx, M1Pt185 *pos, int x, int y, int z);

/* 0x35C60: spawn hits at an object's position; a packed cell (bytes 2 and 3 of +0x64) overrides x/y when set, and new hits face away (-y). */
void m1_HitSpawn035C60(M1Ob185 *o, int ctx, int x, int y, int z) {
    int a, b; M1Hit185 *r; uint32_t i; M1Pt185 *p;
    if (o == 0) return;
    a = (int8_t)(o->pack64 >> 16);
    b = (int8_t)(o->pack64 >> 24);
    p = &o->pos10;
    if (a != -1) { r1d_KeyDecode(o->pack64, ctx, &a, &b); x = a; y = b; }
    r = sub_00035000(ctx, p, x, y, z);
    if (r == 0 || r->kind0 != 0) return;
    for (i = 0; i < r->nD0; i++) (&r->f1C8)[i * (0x12C / 4)] = 0.0f - p->f4;
}
