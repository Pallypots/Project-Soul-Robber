/* Area m1, file 288: model drawing. Names inferred. */
#include <stdint.h>

typedef struct M1Mt288 { uint8_t unk00[4]; uint32_t kind4; } M1Mt288;
typedef struct M1Blk288 { uint8_t unk00[8]; int32_t mat8; } M1Blk288;
typedef struct M1Md288 { int32_t nParts0; uint8_t unk04[0x5C]; M1Blk288 first60; } M1Md288;
M1Mt288 *sub_001AE8C0(int32_t part, int32_t mat);
M1Blk288 *sub_001AE920(M1Md288 *m, M1Blk288 *b);             /* next block */
M1Blk288 *sub_001AE920b(M1Md288 *m, M1Blk288 *b);            /* same function (alias keeps the skip path's call) */
void sub_001A2480(void *ctx, M1Mt288 *mt);                    /* bind material */
void sub_001A1EE0(int32_t mode);
void sub_001A1EE0b(int32_t mode);                             /* aliases keep the four mode calls apart */
void sub_001A1EE0c(int32_t mode);
void sub_001A1EE0d(int32_t mode);
void r4e_DrawVertexBlockFmt(M1Md288 *fmt, M1Blk288 *h);

/* 0x001A2AA0: draw every part of model m: parts without a material are skipped; when the material changes it
   is bound and the blend mode set (6 for flag 2, 7 for flag 1, else 5 for kinds 0-2 and 4 otherwise); then the
   part's vertex block is drawn. */
void m1_DrawModel1A2AA0(void *ctx, int32_t unused, M1Md288 *m, uint32_t flags)
{
    M1Blk288 *b = &m->first60;
    M1Mt288 *mt, *cur = 0;
    int32_t i;
    for (i = 0; i < m->nParts0; i++) {
        mt = sub_001AE8C0(i, b->mat8);
        if (!mt) {
            b = sub_001AE920b(m, b);
            continue;
        }
        if (mt != cur) {
            sub_001A2480(ctx, mt);
            cur = mt;
            if (flags & 2)
                sub_001A1EE0(6);
            else if (flags & 1)
                sub_001A1EE0b(7);
            else if (mt->kind4 <= 2)
                sub_001A1EE0c(5);
            else
                sub_001A1EE0d(4);
        } else {
            cur = mt;
        }
        r4e_DrawVertexBlockFmt(m, b);
        b = sub_001AE920(m, b);
    }
}
