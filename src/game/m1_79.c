/* Area m1, file 79: record releases. Names inferred. */
#include <stdint.h>

typedef struct M1Rec58 {
    void   *owner00;           /* +0x00 */
    int32_t i04;               /* +0x04 */
    int32_t i08;               /* +0x08 */
    uint8_t unk0C[0x1C - 0xC];
    float   f1C;               /* +0x1C */
    float   f20;               /* +0x20 */
    uint8_t unk24[0x40 - 0x24];
    float   f40;               /* +0x40 */
    uint8_t unk44[0x58 - 0x44];
} M1Rec58;
extern M1Rec58 r3e_recs3FE0C0[3];
typedef struct M1ObjR9 { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } M1ObjR9;
typedef struct M1StepR9 { uint8_t unk000[0x278]; void *rig278; } M1StepR9;
void sub_00033B30(void *o);
void sub_0001EB80(void *o);

/* 0x0017F050: release the record of an active object (table 0x3FE0C0, 3 entries): 0x33B30,
 * reset the record, detach the rig, 0x1EB80, clear o flag 1, set o +0x10 bits 0xD. */
int m1_RecRelease17F050(M1ObjR9 *o, M1StepR9 *h)
{
    M1Rec58 *e;
    int i;
    if (!(o->flags0C & 1))
        return 0;
    for (i = 0; i < 3; i++)
        if (r3e_recs3FE0C0[i].owner00 == o)
            break;
    if (i >= 3)
        return 0;
    e = &r3e_recs3FE0C0[i];
    if (i >= 3)
        return 0;
    sub_00033B30(o);
    e->owner00 = 0;
    e->i04 = 0;
    e->i08 = 0;
    e->f40 = 0.0f;
    e->f1C = 0.0f;
    e->f20 = 0.0f;
    h->rig278 = 0;
    sub_0001EB80(o);
    o->flags0C &= ~1u;
    o->flags10 |= 0xD;
    return 1;
}

typedef struct M1Rec44 {
    void   *owner00;           /* +0x00 */
    int32_t i04;               /* +0x04 */
    int32_t i08;               /* +0x08 */
    int16_t w0C;               /* +0x0C */
    uint8_t unk0E[2];
    float   f10;               /* +0x10 */
    uint8_t unk14[4];
    float   f18, f1C, f20;     /* +0x18..+0x20 */
    float   f24, f28, f2C, f30;/* +0x24..+0x30 */
    int32_t i34;               /* +0x34 */
    float   f38, f3C, f40;     /* +0x38..+0x40 */
} M1Rec44;
extern M1Rec44 r3c_slots3FE1C8[4];

/* 0x00180AF0: release the record of an active object (table 0x3FE1C8, 4 entries), detaching
 * the rig before the record is cleared. */
int m1_RecRelease180AF0(M1ObjR9 *o, M1StepR9 *h)
{
    M1Rec44 *e;
    int i;
    if (!(o->flags0C & 1))
        return 0;
    for (i = 0; i < 4; i++)
        if (r3c_slots3FE1C8[i].owner00 == o)
            break;
    if (i >= 4)
        return 0;
    e = &r3c_slots3FE1C8[i];
    if (i >= 4)
        return 0;
    sub_00033B30(o);
    h->rig278 = 0;
    sub_0001EB80(o);
    e->owner00 = 0;
    e->i04 = 0;
    e->i34 = 0;
    e->i08 = 0;
    e->w0C = 0;
    e->f10 = 0.0f;
    e->f18 = 0.0f;
    e->f1C = 0.0f;
    e->f20 = 0.0f;
    e->f38 = 0.0f;
    e->f3C = 0.0f;
    e->f40 = 0.0f;
    e->f24 = 0.0f;
    e->f28 = 0.0f;
    e->f2C = 0.0f;
    e->f30 = 0.0f;
    o->flags0C &= ~1u;
    o->flags10 |= 0xD;
    return 1;
}

typedef struct M1Slot48 {
    uint32_t flags00;          /* +0x00 */
    float   f04, f08, f0C;     /* +0x04..+0x0C */
    float   v10[4];            /* +0x10 */
    float   v20[4];            /* +0x20 */
    float   v30[4];            /* +0x30 */
    uint8_t sub40[8];          /* +0x40 */
} M1Slot48;
extern M1Slot48 m1_slots3F750C[6];
void sub_00080D20(void *p);

/* 0x00166110: take a free slot from table 0x3F750C (6 entries): mark it used, f04 = 0,
 * f08 = 100, f0C = 50, three unit vectors (0,0,0,1), init the +0x40 part; 0 if none free. */
M1Slot48 *m1_SlotNew166110(void)
{
    M1Slot48 *e;
    int i;
    for (i = 0, e = m1_slots3F750C; i < 6; i++, e++)
        if (!(e->flags00 & 1))
            break;
    if (i >= 6)
        return 0;
    e->f08 = 100.0f;
    e->f0C = 50.0f;
    e->flags00 = 1;
    e->f04 = 0.0f;
    e->v10[0] = 0.0f;
    e->v10[1] = 0.0f;
    e->v10[2] = 0.0f;
    e->v10[3] = 1.0f;
    e->v30[0] = 0.0f;
    e->v30[1] = 0.0f;
    e->v30[2] = 0.0f;
    e->v30[3] = 1.0f;
    e->v20[0] = 0.0f;
    e->v20[1] = 0.0f;
    e->v20[2] = 0.0f;
    e->v20[3] = 1.0f;
    sub_00080D20(e->sub40);
    return e;
}

typedef struct M1RigW { uint32_t unk00; uint32_t flags04; } M1RigW;
typedef struct M1StepW {
    uint8_t unk000[0x20];
    uint32_t flags20;          /* +0x20 (byte +0x22 is bit 16) */
    uint8_t unk024[0x58 - 0x24];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x100 - 0x78];
    float   f100;              /* +0x100 */
    uint8_t unk104[0x278 - 0x104];
    M1RigW *rig278;            /* +0x278 */
} M1StepW;
typedef struct M1ObjW { uint8_t unk00[0x30]; void *anim30; } M1ObjW;
int  sub_000833E0(void *a);
void sub_00113040(void *o, void *h, int state);
void sub_00113090(void *o, void *h, int state);

/* 0x00138DF0: phase 0 enters state 0x1D or 0x1E (bit 16 of h +0x20) once +0x100 leaves the
 * KA..KB band (flag 1), or when the wait ran out (rig flag 4) or +0x100 drops to KA, then
 * phase 1: state 0x1D once the clip is done. */
void m1_RigStep138DF0(M1ObjW *o, M1StepW *h)
{
    M1RigW *r = h->rig278;
    uint32_t f;
    int s;
    switch (h->phase58) {
    case 0:
        f = h->flags20;
        if (f & 1) {
            if (!(25.0f >= h->f100 || h->f100 >= 60.0f))
                return;
            s = ((f >> 16) & 1) + 0x1D;
        } else if (0.0f >= h->wait74) {
            r->flags04 |= 4;
            s = (((uint8_t *)h)[0x22] & 1) + 0x1D;
        } else {
            if (!(25.0f >= h->f100))
                return;
            s = ((f >> 16) & 1) + 0x1D;
        }
        sub_00113090(o, h, s);
        h->phase58++;
        /* fall through */
    case 1:
        if (sub_000833E0(o->anim30))
            sub_00113040(o, h, 0x1D);
        break;
    }
}
