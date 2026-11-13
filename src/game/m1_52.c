/* Area m1, file 52: enemy group resets. Names inferred. */
#include <stdint.h>

typedef struct M1Anim30 { uint8_t unk00[8]; int32_t clip08; } M1Anim30;
typedef struct M1GrpObj {
    uint8_t unk00[0x10];
    uint32_t flags10;          /* +0x10 */
    uint8_t unk14[0x30 - 0x14];
    M1Anim30 *anim30;          /* +0x30 */
    uint8_t unk34[0x50 - 0x34];
    float   q50[4];            /* +0x50 */
} M1GrpObj;
typedef struct M1Fx90 { uint8_t unk00[0x90]; uint32_t flags90; } M1Fx90;
typedef struct M1Grp44 {
    M1GrpObj *obj00;           /* +0x00 */
    void    *h04;              /* +0x04 */
    uint8_t unk08[0x14 - 8];
    int32_t f14;               /* +0x14 */
    uint8_t unk18[0x34 - 0x18];
    M1Fx90  *fx34;             /* +0x34 */
    uint8_t unk38[0x44 - 0x38];
} M1Grp44;
extern M1Grp44 m1_grp3FE1C8[4];
void sub_00195110(void);
void sub_00113040(void *o, void *h, int next);
void sub_000832D0(M1Anim30 *a, int v);

/* 0x00180A60: 0x195110, then for each of the 4 group slots at 0x3FE1C8: clears +0x14,
 * resets the object's quaternion to (0, 0, 0, 1), state 0, animation clip -1 and
 * 0x832D0(0), clears effect flag 0x40 and sets object flags 0xD. */
void m1_GroupReset180A60(void)
{
    M1Grp44 *e;
    int i;
    sub_00195110();
    for (i = 0; i < 4; i++) {
        float *q;
        e = &m1_grp3FE1C8[i];
        q = e->obj00->q50;
        e->f14 = 0;
        q[0] = 0.0f;
        q[1] = 0.0f;
        q[2] = 0.0f;
        q[3] = 1.0f;
        sub_00113040(e->obj00, e->h04, 0);
        e->obj00->anim30->clip08 = -1;
        sub_000832D0(e->obj00->anim30, 0);
        e->fx34->flags90 &= ~0x40u;
        e->obj00->flags10 |= 0xD;
    }
}
