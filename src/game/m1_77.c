/* Area m1, file 77: rig steps. Names inferred. */
#include <stdint.h>

typedef struct M1Anim77 { uint8_t unk00[0xC4]; float lenC4; uint8_t unkC8[0xDC - 0xC8]; float speedDC; } M1Anim77;
typedef struct M1Clip77 { uint8_t unk00[0x14]; M1Anim77 *anim14; } M1Clip77;
typedef struct M1Act77 { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x30 - 0x14]; M1Clip77 *clip30; } M1Act77;
typedef struct M1Step77 {
    uint8_t unk000[0x20];
    uint32_t flags20;          /* +0x20 */
    uint8_t unk024[0x64 - 0x24];
    int32_t state64;           /* +0x64 */
    uint8_t unk068[0x74 - 0x68];
    float   rate74;            /* +0x74 */
} M1Step77;
typedef struct M1Cmd77 { uint8_t unk00[0x10]; float f10; } M1Cmd77;
typedef struct M1Cmd77I { uint8_t unk00[0x10]; int32_t i10, i14; } M1Cmd77I;
extern float m1_frameRate42C85C;
int  sub_00139DB0(void *h);
void sub_00139D50(void *o);
void *sub_00113430(void *h, int v);
void *sub_00113400(void *h, int v);
void sub_00113040(void *o, void *h, int state);
void sub_00113090(void *o, void *h, int state);

/* 0x0013B620: if 0x139DB0 holds, command 8 = (0x50 + h +0x22 bit, 13) and state 0; otherwise
 * enter state 2 + (bit 0 ? 2 : 0) + bit 16 of h +0x20 (with 0x139D50) if not already in it,
 * set o flag 0x20, play rate = clip speed / length * frameRate, command 3 = 0. */
void m1_RigStep13B620(M1Act77 *o, M1Step77 *h)
{
    int s;
    if (sub_00139DB0(h)) {
        M1Cmd77I *d = (M1Cmd77I *)sub_00113430(h, 8);
        d->i14 = 0xD;
        d->i10 = (((uint8_t *)h)[0x22] & 1) + 0x50;
        sub_00113040(o, h, 0);
        return;
    }
    s = (-(((uint8_t)h->flags20 & 1) != 0) & 2) + 2 + ((h->flags20 >> 16) & 1);
    if (h->state64 != s) {
        sub_00113090(o, h, s);
        sub_00139D50(o);
    }
    o->flags10 |= 0x20;
    h->rate74 = o->clip30->anim14->speedDC / o->clip30->anim14->lenC4 * m1_frameRate42C85C;
    ((M1Cmd77 *)sub_00113400(h, 3))->f10 = 0.0f;
}

typedef struct M1Obj77 { uint8_t unk00[0x20]; uint8_t *mdl20; } M1Obj77;
typedef struct M1StepP {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x58 - 0x50];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x74 - 0x5C];
    float   wait74;            /* +0x74 */
} M1StepP;
extern float m1_frameTime42C858;
int  sub_00139FE0(void *o, void *h);
int  sub_000494D0(int id, const void *pos, int c);
int  aab_Rand(void);

/* 0x0013BA30: while 0x139FE0 holds: phase 0 plays sound 0xA5 at the model and waits (K /
 * frameTime * frameRate), phase 1 goes to 2, phase 2 sets h +0x4C bits 0x38 and picks state
 * 0x10 (1 in 16) or 0xC with the wait cleared. */
void m1_RigStep13BA30(M1Obj77 *o, M1StepP *h)
{
    if (!sub_00139FE0(o, h))
        return;
    switch (h->phase58) {
    case 0:
        sub_000494D0(0xA5, o->mdl20 + 0x30, 0);
        h->wait74 = 22.0f / m1_frameTime42C858 * m1_frameRate42C85C;
        h->phase58++;
        break;
    case 1:
        h->phase58 = 2;
        break;
    case 2:
        h->flags4C |= 0x38;
        if (aab_Rand() % 16 < 1) {
            sub_00113040(o, h, 0x10);
            return;
        }
        h->wait74 = 0.0f;
        sub_00113040(o, h, 0xC);
        break;
    }
}

typedef struct M1ClipE { uint8_t unk00[0x10]; int32_t len10; } M1ClipE;
typedef struct M1AnimE { uint8_t unk00[0x14]; void *track14; } M1AnimE;
typedef struct M1RigE { uint8_t unk00[0x20]; void *fx20; } M1RigE;
typedef struct M1ObjE {
    uint8_t unk00[8];
    int32_t kind08;            /* +0x08 */
    uint8_t unk0C[0x10 - 0xC];
    uint32_t flags10;          /* +0x10 */
    uint8_t unk14[0x30 - 0x14];
    M1AnimE *anim30;           /* +0x30 */
} M1ObjE;
typedef struct M1StepE {
    uint8_t unk000[0x58];
    int32_t phase58;           /* +0x58 */
    uint8_t unk05C[0x64 - 0x5C];
    int32_t state64;           /* +0x64 */
    uint8_t unk068[0x74 - 0x68];
    float   wait74;            /* +0x74 */
    uint8_t unk078[0x278 - 0x78];
    M1RigE *rig278;            /* +0x278 */
} M1StepE;
void sub_0001D610(void *o);
M1ClipE *sub_00083120(M1AnimE *a, int clip);
void sub_001AEDD0(void *track, int len);
void sub_0001D720(void *fx);
int  sub_000833E0(M1AnimE *a);

/* 0x00139FE0: phase check: phase 0 when the wait ran out restarts the state clip (0x1D610,
 * clip length into the track) and for kinds 2-4 and 16 fires the rig effect; phase 1 when the
 * wait ran out clears o flags 5; phase 2 when the clip is done (0x833E0). Returns 1 on those. */
int m1_PhaseCheck139FE0(M1ObjE *o, M1StepE *h)
{
    int k;
    switch (h->phase58) {
    case 0:
        if (0.0f >= h->wait74) {
            sub_0001D610(o);
            sub_001AEDD0(o->anim30->track14, sub_00083120(o->anim30, h->state64)->len10);
            k = o->kind08;
            if (k >= 2 && (k <= 4 || k == 0x10)) {
                void *fx = h->rig278->fx20;
                if (fx != 0)
                    sub_0001D720(fx);
            }
            return 1;
        }
        break;
    case 1:
        if (0.0f >= h->wait74) {
            o->flags10 &= ~5u;
            return 1;
        }
        break;
    case 2:
        if (sub_000833E0(o->anim30))
            return 1;
        break;
    }
    return 0;
}

typedef struct M1RigF { uint8_t unk00[0xC]; float rate0C; float f10; uint8_t unk14[0x24 - 0x14]; float q24[4]; } M1RigF;
typedef struct M1StepF {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1RigF *rig278;            /* +0x278 */
} M1StepF;
typedef struct M1ObjF { uint8_t unk00[0x20]; float *node20; } M1ObjF;
int  sub_001456E0(void *o, void *h, int a, int b);
void sub_001AD7E0(float *out, const float *v);
void sub_000F5D40(float *d, const float *s);
void sub_001ADA60(float *out, const float *a, const float *b);

/* 0x00159B30: enter state 0x39, reset the rig quaternion, rig +0x10 = 0, +0xC = frameTime *
 * 0.005, clear h +0x4C bits 0x70, then rebuild the node frame with y = (0, 1, 0, 0). */
void m1_RigReset159B30(M1ObjF *o, M1StepF *h)
{
    M1RigF *r = h->rig278;
    float *n;
    float up[4];
    up[0] = 0.0f;
    up[1] = 1.0f;
    up[2] = 0.0f;
    up[3] = 0.0f;
    sub_001456E0(o, h, 0x39, 0);
    r->q24[2] = 0.0f;
    r->q24[1] = 0.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    h->flags4C &= ~0x70u;
    o->node20[1] = 0.0f;
    sub_001AD7E0(o->node20, o->node20);
    sub_000F5D40(o->node20 + 4, up);
    n = o->node20;
    sub_001ADA60(n + 8, n, n + 4);
}

typedef struct M1RigG {
    uint32_t flags00;          /* +0x00 */
    uint8_t unk04[0xC - 4];
    float   rate0C;            /* +0x0C */
    float   f10;               /* +0x10 */
    uint8_t unk14[0x24 - 0x14];
    float   q24[4];            /* +0x24 */
    uint8_t unk34[0x40 - 0x34];
    uint32_t flags40;          /* +0x40 */
} M1RigG;
typedef struct M1StepG {
    uint8_t unk000[0x4C];
    uint32_t flags4C;          /* +0x4C */
    uint8_t unk050[0x278 - 0x50];
    M1RigG *rig278;            /* +0x278 */
} M1StepG;
typedef struct M1ObjG { uint8_t unk00[0x10]; uint32_t flags10; uint8_t unk14[0x60 - 0x14]; float pos60[4]; } M1ObjG;
void *sub_00036750(void *o, int b);
int  sub_000494D0(int id, const void *pos, int c);

/* 0x00159E30: enter state 6, rig quaternion (0, K*frameRate, -15*frameRate, 1), rig +0xC =
 * frameTime * 0.005, o flags 5, h +0x4C clears 0x70 sets 0x1000000, rig flags 3; the first
 * time (rig +0x40 bit 0x40) also 0x36750(o, 0) and sound 0x12F at the object. */
void m1_RigTumble159E30(M1ObjG *o, M1StepG *h)
{
    M1RigG *r = h->rig278;
    sub_001456E0(o, h, 6, 0);
    r->q24[2] = 0.0f - m1_frameRate42C85C * 15.0f;
    r->q24[1] = m1_frameRate42C85C * -15.0f;
    r->q24[0] = 0.0f;
    r->q24[3] = 1.0f;
    r->f10 = 0.0f;
    r->rate0C = m1_frameTime42C858 * 0.005f;
    o->flags10 |= 5;
    h->flags4C = (h->flags4C & ~0x70u) | 0x1000000;
    r->flags00 |= 3;
    if (!(r->flags40 & 0x40)) {
        r->flags40 |= 0x40;
        sub_00036750(o, 0);
        sub_000494D0(0x12F, o->pos60, 0);
    }
}

typedef struct M1VecH { float v[4]; int32_t i10; } M1VecH;
extern M1VecH *r3d_vecs31F3E0[];
typedef struct M1SubH {
    uint32_t flags00;          /* +0x00 */
    int32_t idx04;             /* +0x04 */
    int32_t i08;               /* +0x08 */
    float   v0C[4];            /* +0x0C */
    int32_t i1C;               /* +0x1C */
    uint8_t unk20[0x3C - 0x20];
    int32_t i3C;               /* +0x3C */
    uint8_t unk40[0x4C - 0x40];
    void   *fx4C;              /* +0x4C */
} M1SubH;
typedef struct M1StepH { uint8_t unk00[0x5C]; float f5C; uint8_t unk60[0x74 - 0x60]; M1SubH *sub74; } M1StepH;
typedef struct M1ObjH { uint8_t unk00[0x54]; int32_t i54; } M1ObjH;
int  sub_000D9A70(int id);
void sub_001671D0(void *o, void *h, int v);

/* 0x0016DED0: when 0x0D9A70(0x1E, or 0x12 without flag 0x10000) holds: 0x1D610, an effect
 * (0x36750) below 1.0 with flag 0x800000, reload the sub vector from table 0x31F3E0, clear
 * flags 0xC00, 0x1671D0(5), then flag 0x2000 (and +0x3C = o +0x54) unless 0xC00 came back. */
void m1_SubStep16DED0(M1ObjH *o, M1StepH *h)
{
    M1SubH *s = h->sub74;
    M1VecH *v;
    if (!sub_000D9A70((s->flags00 & 0x10000) ? 0x1E : 0x12))
        return;
    sub_0001D610(o);
    if (1.0f > h->f5C && (s->flags00 & 0x800000) && s->fx4C == 0)
        s->fx4C = sub_00036750(o, 0);
    v = r3d_vecs31F3E0[s->idx04];
    sub_000F5D40(s->v0C, v->v);
    s->i08 = 0;
    s->i1C = v->i10;
    s = h->sub74;
    s->flags00 &= ~0xC00u;
    sub_001671D0(o, h, 5);
    if (!(s->flags00 & 0xC00)) {
        s->flags00 |= 0x2000;
        s->i3C = o->i54;
    } else {
        s->flags00 &= ~0x2000u;
    }
}
