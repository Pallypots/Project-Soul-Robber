/* Area m1, file 37: save screen shutdown. Names inferred. */
#include <stdint.h>

extern int32_t a5b_g3E3944;              /* 0x003E3944 mode */
extern int32_t m1_handles3E3914[7];      /* 0x003E3914 */
extern int32_t m1_handle3E3948;          /* 0x003E3948 */
extern int32_t m1_g3E3940;               /* 0x003E3940 */
extern uint8_t *m1_save3E3934;           /* 0x003E3934 */
void a1a_GroupFreeAll(void *g);
void sub_001B9FC0(int h);
void sub_0004F5D0(int id);
void sub_00053880(void *p);
void sub_001A1B90(void);

/* 0x000540C0: frees the group, stops the seven handles and the extra handle (unless
 * in mode 2), releases resources 0xB8, 0xBA, 0xA7 and the save buffer, then 0x1A1B90. */
void m1_SaveShutdown540C0(void *group)
{
    int i;
    a1a_GroupFreeAll(group);
    if (a5b_g3E3944 != 2) {
        for (i = 0; i < 7; i++) {
            if (m1_handles3E3914[i] != -1) {
                sub_001B9FC0(m1_handles3E3914[i]);
                m1_handles3E3914[i] = -1;
            }
        }
        if (m1_handle3E3948 != -1) {
            sub_001B9FC0(m1_handle3E3948);
            m1_handle3E3948 = -1;
        }
    }
    sub_0004F5D0(0xB8);
    sub_0004F5D0(0xBA);
    sub_0004F5D0(0xA7);
    m1_g3E3940 = 0;
    sub_00053880(m1_save3E3934);
    sub_001A1B90();
}

typedef struct M1Blk510 { uint32_t w[0x144]; } M1Blk510;   /* 0x510 bytes copied whole */
typedef struct M1V4C { float v[4]; } M1V4C;
typedef struct M1Set560 {
    uint8_t  unk000[4];
    int32_t  f004;             /* +0x004 */
    int32_t  f008;             /* +0x008 */
    uint8_t  unk00C[4];
    M1Blk510 blk010;           /* +0x010 */
    M1V4C    v520[2];          /* +0x520 */
    int32_t  f540, f544, f548, f54C;   /* +0x540..+0x54C */
    uint8_t  unk550[8];
    int32_t  f558;             /* +0x558 */
} M1Set560;
void sub_000195F0(M1Set560 *s);
void sub_000F5D40(void *dst, const void *src);

/* 0x00018840: resets dst (0x195F0) and copies src into it; +0x558 = -1 and +0x54C
 * takes src +0x548 (as in the original). regargs: dst=EBX */
void m1_SetCopy18840(M1Set560 *dst, const M1Set560 *src)
{
    int i;
    sub_000195F0(dst);
    dst->f004 = src->f004;
    dst->f008 = src->f008;
    dst->blk010 = src->blk010;
    for (i = 0; i < 2; i++)
        sub_000F5D40(&dst->v520[i], &src->v520[i]);
    dst->f558 = -1;
    dst->f540 = src->f540;
    dst->f544 = src->f544;
    dst->f548 = src->f548;
    dst->f54C = src->f548;
}
