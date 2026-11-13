/* Area m1, file 78: bounds and misc. Names inferred. */
#include <stdint.h>

typedef struct M1BoxO { uint8_t unk00[0x60]; float pos60[4]; float size70; } M1BoxO;
void sub_0001B420(const float *hi, const float *lo, void *arg);

/* 0x0018A880: box around the object: pos +- size * 12 (w = 1), passed to 0x1B420. */
void m1_Bounds18A880(M1BoxO *o, void *arg)
{
    float lo[4], hi[4];
    float d = o->size70 * 12.0f;
    hi[0] = d + o->pos60[0];
    lo[0] = o->pos60[0] - d;
    hi[1] = d + o->pos60[1];
    lo[1] = o->pos60[1] - d;
    hi[2] = d + o->pos60[2];
    hi[3] = 1.0f;
    lo[2] = o->pos60[2] - d;
    lo[3] = 1.0f;
    sub_0001B420(hi, lo, arg);
}

typedef struct M1RigS {
    uint8_t unk00[8];
    void   *res08;             /* +0x08 */
    void   *fx0C;              /* +0x0C */
    int32_t i10;               /* +0x10 */
    uint8_t unk14[0x1C - 0x14];
    int32_t i1C;               /* +0x1C */
    int32_t snd20;             /* +0x20 */
    int32_t snd24;             /* +0x24 */
    float   f28;               /* +0x28 */
    int32_t z2C[6];            /* +0x2C..+0x40 */
} M1RigS;
typedef struct M1StepS { uint8_t unk000[0x278]; void *rig278; } M1StepS;
void sub_00033A40(void *r);
void sub_00048250(int snd);
int  sub_000494D0(int id, const void *pos, int c);
void *sub_00036750(void *o, int b);

/* 0x0017E910: rig start: +0x10 = 1, +0x28 = 0.2, clear +0x1C and +0x2C..+0x40, free the +8
 * resource, stop sound +0x20, start looping sound 0x334 (+0x24) and effect 1 (+0xC) if absent. */
void m1_RigStart17E910(uint8_t *o, M1StepS *h)
{
    M1RigS *r = (M1RigS *)h->rig278;
    r->i10 = 1;
    r->f28 = 0.2f;
    r->i1C = 0;
    r->z2C[0] = 0;
    r->z2C[1] = 0;
    r->z2C[2] = 0;
    r->z2C[3] = 0;
    r->z2C[4] = 0;
    r->z2C[5] = 0;
    if (r->res08 != 0) {
        sub_00033A40(r->res08);
        r->res08 = 0;
    }
    if (r->snd20 != -1) {
        sub_00048250(r->snd20);
        r->snd20 = -1;
    }
    if (r->snd24 == -1)
        r->snd24 = sub_000494D0(0x334, o + 0x60, 1);
    if (r->fx0C == 0)
        r->fx0C = sub_00036750(o, 1);
}

typedef struct M1Rec54 {
    void   *owner00;           /* +0x00 */
    int32_t i04;               /* +0x04 */
    int32_t i08;               /* +0x08 */
    uint8_t unk0C[0x18 - 0xC];
    int32_t i18;               /* +0x18 */
    uint8_t unk1C[0x24 - 0x1C];
    int16_t w24;               /* +0x24 */
    uint8_t unk26[0x50 - 0x26];
    int16_t w50;               /* +0x50 */
    uint8_t unk52[2];
} M1Rec54;
extern M1Rec54 r3c_recs3FDC70[6];
typedef struct M1ObjR { uint8_t unk00[0xC]; uint32_t flags0C; uint32_t flags10; } M1ObjR;
void sub_00033B30(void *o);
void sub_0001EB80(void *o);

/* 0x0017C530: release the record of an active object (table 0x3FDC70, 6 entries): 0x33B30,
 * reset the record, detach the rig, 0x1EB80, clear o flag 1, set o +0x10 bits 0x44D. */
int m1_RecRelease17C530(M1ObjR *o, M1StepS *h)
{
    M1Rec54 *e;
    int i;
    if (!(o->flags0C & 1))
        return 0;
    for (i = 0; i < 6; i++)
        if (r3c_recs3FDC70[i].owner00 == o)
            break;
    if (i >= 6)
        return 0;
    e = &r3c_recs3FDC70[i];
    if (i >= 6)
        return 0;
    sub_00033B30(o);
    e->i18 = -1;
    e->w50 = -1;
    e->owner00 = 0;
    e->i04 = 0;
    e->i08 = 0;
    e->w24 = 0;
    h->rig278 = 0;
    sub_0001EB80(o);
    o->flags0C &= ~1u;
    o->flags10 |= 0x44D;
    return 1;
}

typedef struct M1ObjT { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[4]; uint8_t unk70[0x128 - 0x70]; uint8_t b128; } M1ObjT;
typedef struct M1StepT { uint8_t unk00[0x20]; uint8_t b20; uint8_t unk21[0x6C - 0x21]; float t6C; } M1StepT;
int  sub_000CF6C0(void);
void sub_00189DA0(void *o, void *h, int next);
void sub_000C4DF0(void *o, int kind, float a, float b, float c, float d, float e, const float *pos,
                  float *v1, float *v2);

/* 0x0018EB50: o flag 1 follows 0xCF6C0 > 0; once landed (o +0x128 bits 6) or after 4 s go to
 * step 7 (0x189DA0) and, with h +0x20 bit 0, spawn a kind 2 burst at the object. */
void m1_Land18EB50(M1ObjT *o, M1StepT *h)
{
    float v[4];
    if (sub_000CF6C0() > 0)
        o->flags10 |= 1;
    else
        o->flags10 &= ~1u;
    if ((o->b128 & 6) || h->t6C >= 4.0f) {
        sub_00189DA0(o, h, 7);
        if (h->b20 & 1) {
            v[0] = 0.0f;
            v[1] = 0.0f;
            v[2] = 0.0f;
            v[3] = 0.0f;
            sub_000C4DF0(o, 2, 10.0f, 0.0f, 12.5f, 1.0f, 2.5f, o->pos60, v, v);
        }
    }
}

typedef struct M1RigU { uint8_t unk00[0xC]; float rate0C; float f10; uint8_t unk14[0x24 - 0x14]; float q24[4]; uint8_t unk34[0x38 - 0x34]; int32_t i38; uint8_t unk3C[0x50 - 0x3C]; float f50; } M1RigU;
typedef struct M1StepU {
    uint8_t unk000[0x20];
    uint8_t b20;               /* +0x20 */
    uint8_t unk021[0x4C - 0x21];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1RigU *rig278;            /* +0x278 */
} M1StepU;
extern float m1_frameTime42C858;
int  sub_001456E0(void *o, void *h, int a, int b);

/* 0x001566D0: enter state 0, reset the rig quaternion, rig +0xC = frameTime * 0.005, o flag
 * 0x20, h +0x4C |= 0x70, rig +0x50 = 120 (h +0x20 bit 0), else 150 with +0x38 set, else 198. */
void m1_RigIdle1566D0(M1ObjT *o, M1StepU *h)
{
    M1RigU *r = h->rig278;
    sub_001456E0(o, h, 0, 0);
    r->q24[2] = 0.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    o->flags10 |= 0x20;
    h->flags4C |= 0x70;
    if (h->b20 & 1)
        r->f50 = 120.0f;
    else
        r->f50 = r->i38 ? 150.0f : 198.0f;
}

typedef struct M1FxPart { uint8_t a00[0x10]; uint8_t b10[0x340 - 0x10]; } M1FxPart;
extern M1FxPart m1_fxParts414460[16];
extern int32_t m1_fxRes3FD7C8, m1_fxObjs3FD7CC, m1_fxModel3FD7D0, m1_fxBones3FD7D4, r3d_i3FD7D8;
void sub_0001D8B0(void *p, int kind);
void sub_001853E0(void); void sub_00185130(void); void sub_00181870(void);
void sub_00182FE0(void); void sub_00182400(void); void sub_0017E300(void);
void sub_00188FD0(void); void sub_00175170(void); void sub_00176480(void);
void sub_00177740(void); void sub_0017FF30(void); void sub_001799E0(void);
void sub_0017EAC0(void); void sub_00184020(void); void sub_00183A70(void);
void sub_0017CDC0(void);

/* 0x00174B40: effects reset: clear the effect globals, reinit the 16 effect parts (0x1D8B0
 * kinds 6 and 13), then run every effect family's reset. */
void m1_FxResetAll174B40(void)
{
    int i;
    m1_fxRes3FD7C8 = 0;
    m1_fxObjs3FD7CC = 0;
    m1_fxModel3FD7D0 = 0;
    m1_fxBones3FD7D4 = 0;
    for (i = 0; i < 16; i++) {
        sub_0001D8B0(m1_fxParts414460[i].a00, 6);
        sub_0001D8B0(m1_fxParts414460[i].b10, 0xD);
    }
    r3d_i3FD7D8 = 0;
    sub_001853E0(); sub_00185130(); sub_00181870(); sub_00182FE0(); sub_00182400();
    sub_0017E300(); sub_00188FD0(); sub_00175170(); sub_00176480(); sub_00177740();
    sub_0017FF30(); sub_001799E0(); sub_0017EAC0(); sub_00184020(); sub_00183A70();
    sub_0017CDC0();
}

typedef struct M1AnimK { uint8_t unk00[0xB8]; uint32_t flagsB8; } M1AnimK;
typedef struct M1ClipK { uint8_t unk00[0x14]; M1AnimK *anim14; } M1ClipK;
typedef struct M1ObjK {
    uint8_t unk000[0x30];
    M1ClipK *clip30;           /* +0x30 */
    uint8_t unk034[0x54 - 0x34];
    float   yaw54;             /* +0x54 */
    uint8_t unk058[0x60 - 0x58];
    float   pos60[4];          /* +0x60 */
    uint8_t unk070[0x128 - 0x70];
    uint32_t flags128;         /* +0x128 */
} M1ObjK;
void sub_001AD940(float *m);
void sub_001AD8E0(float *d, const float *s, float a);
void sub_001AD9B0(float *d, const float *m, const float *v);
void sub_00035D80(void *o, int a, int b);

/* 0x0017B1C0: knockback: h +0x78 = (0, -60, -60) turned by the object yaw, clear o +0x128
 * bits 0x18, clip flag 2, 0x35D80(2, 1), sound 0x197 at the object. */
void m1_Knockback17B1C0(M1ObjK *o, uint8_t *h)
{
    float v[4];
    float m[16];
    v[0] = 0.0f;
    v[1] = -60.0f;
    v[2] = -60.0f;
    sub_001AD940(m);
    sub_001AD8E0(m, m, o->yaw54);
    sub_001AD9B0((float *)(h + 0x78), m, v);
    o->flags128 &= ~0x18u;
    o->clip30->anim14->flagsB8 |= 2;
    sub_00035D80(o, 2, 1);
    sub_000494D0(0x197, o->pos60, 0);
}

typedef struct M1RigH { uint8_t unk00[0x34]; float v34[4]; } M1RigH;
typedef struct M1StepHv { uint8_t unk000[0x278]; M1RigH *rig278; } M1StepHv;
typedef struct M1ObjHv { uint8_t unk000[0x60]; float pos60[3]; float f6C; uint8_t unk70[0x128 - 0x70]; uint8_t b128; } M1ObjHv;
extern float m1_fps42C964;
extern uint8_t r3d_rate32B698[];
void sub_001ADAF0(float *d, const float *a, const float *b);
void sub_000F6450(void *o, const void *k);
void sub_00113040(void *o, void *h, int state);

/* 0x0017CA70: hover: move by the rig velocity, o +0x6C = 1, speed up +0x38 by 3/fps up to
 * 120/fps, 0xF6450 with 0x32B698, state 8 on o +0x128 bits 0xA. */
void m1_Hover17CA70(M1ObjHv *o, M1StepHv *h)
{
    M1RigH *r = h->rig278;
    float lim = 120.0f / m1_fps42C964;
    sub_001ADAF0(o->pos60, o->pos60, r->v34);
    o->f6C = 1.0f;
    if (lim > r->v34[1]) {
        r->v34[1] = 3.0f / m1_fps42C964 + r->v34[1];
        if (r->v34[1] > lim)
            r->v34[1] = lim;
    }
    sub_000F6450(o, r3d_rate32B698);
    if (o->b128 & 0xA)
        sub_00113040(o, h, 8);
}
