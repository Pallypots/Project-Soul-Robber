/* Area m1, file 56: helper camera reset. Names inferred. */
#include <stdint.h>

typedef struct M1Anim30b { uint8_t unk00[0x30]; void *anim30; } M1Anim30b;
typedef struct M1Helper8C {
    uint8_t unk000[0x8C];
    M1Anim30b *cam8C;          /* +0x8C */
    uint8_t unk090[0xAC - 0x90];
    float   fAC;               /* +0xAC */
    uint8_t unk0B0[0xDC - 0xB0];
    int32_t fDC, fE0;          /* +0xDC */
    uint8_t unk0E4[0xF4 - 0xE4];
    float   fF4;               /* +0xF4 */
} M1Helper8C;
extern M1Helper8C *m1_helper3F611C;
void sub_000832D0(void *a, int v);

/* 0x000FCDD0: spins on a null camera; camera animation 0x832D0(4), +0xAC = 0.25,
 * +0xDC = +0xE0 = 0, +0xF4 = 0. */
void m1_HelperCam0FCDD0(void)
{
    M1Helper8C *s = m1_helper3F611C;
    M1Anim30b *c = s->cam8C;
    if (c == 0)
        for (;;) ;
    sub_000832D0(c->anim30, 4);
    s->fAC = 0.25f;
    s->fDC = 0;
    s->fE0 = 0;
    s->fF4 = 0.0f;
}
