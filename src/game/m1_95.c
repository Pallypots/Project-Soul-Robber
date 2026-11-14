/* Area m1, file 95: stage setup and attach. Names inferred. */
#include <stdint.h>

typedef struct M1Obj95 {
    uint8_t unk00[0xC];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t unk14[0x20 - 0x14];
    float  *node20;            /* +0x20 */
    uint8_t unk24[0x50 - 0x24];
    float   q50[4];            /* +0x50 */
    float   pos60[4];          /* +0x60 */
    float   scale70[3];        /* +0x70 */
    float   f7C;               /* +0x7C */
} M1Obj95;
extern int32_t m1_stage3FE064;
extern int32_t m1_stageIds3FE080[6];
extern const float m1_stageYaw27A798[6];
extern uint32_t b7c_slots3FE068[6];
M1Obj95 *sub_000A42A0(int id);
void  sub_001B2080(float *node);
void *sub_0001D0F0(void *o, int a);
void  sub_001B2020(void *parent, float *node);
void  sub_000F3FD0(void *o);
void *sub_00036750(void *o, int b);
void  sub_0001D610(void *o);
void  sub_0001D700(void *o);
void  sub_000A5450(int id);

/* 0x0017F2A0: stage piece: attach the current stage object (id from 0x3FE080) to bone 1 of
 * object 0, reset its rotation and position, set its yaw from 0x27A798, start it (0xF3FD0,
 * effect 0, 0x1D610), activate the next piece (+2) and mark the stage slot. */
void m1_StagePiece17F2A0(void)
{
    int i = m1_stage3FE064;
    int n;
    M1Obj95 *o;
    M1Obj95 *p;
    if (m1_stageIds3FE080[i] < 0)
        return;
    o = sub_000A42A0(m1_stageIds3FE080[i]);
    p = sub_000A42A0(0);
    if (o == 0 || p == 0)
        return;
    n = m1_stage3FE064 + 2;
    sub_001B2080(o->node20);
    sub_001B2020(sub_0001D0F0(p, 1), o->node20);
    o->q50[0] = 0.0f;
    o->q50[1] = 0.0f;
    o->q50[2] = 0.0f;
    o->q50[3] = 1.0f;
    o->pos60[0] = 0.0f;
    o->pos60[1] = 0.0f;
    o->pos60[2] = 0.0f;
    o->pos60[3] = 1.0f;
    o->q50[1] = m1_stageYaw27A798[i];
    sub_000F3FD0(o);
    sub_00036750(o, 0);
    sub_0001D610(o);
    sub_0001D700(sub_000A42A0(n));
    sub_000A5450(n);
    b7c_slots3FE068[i] |= 1;
}

typedef struct M1Sub95 { uint32_t flags00; uint8_t unk04[8]; void *tgt0C; float pos10[4]; } M1Sub95;
typedef struct M1Comp95 { uint8_t unk00[0x74]; M1Sub95 *sub74; } M1Comp95;
M1Comp95 *sub_0001D960(void *o, int kind);
void sub_000F5D40(float *d, const float *s);
void sub_001AD940(float *m);
void sub_00189DA0(void *o, void *h, int k);

/* 0x0018C450: attach to target bone: component 7's sub record takes the target and its
 * position (flag 2, and flag 0x20 when mode is 1), the node is parented to the target's
 * bone, scale, rotation and position reset, o flags (+0xC clear 0xE0, +0x10 |= 5), step 0. */
void m1_AttachBone18C450(M1Obj95 *o, uint8_t *t, int bone, int mode)
{
    M1Comp95 *c = sub_0001D960(o, 7);
    M1Sub95 *s;
    void *n;
    if (c == 0)
        for (;;) ;
    s = c->sub74;
    s->tgt0C = t;
    s->flags00 |= 2;
    sub_000F5D40(s->pos10, (const float *)(t + 0x60));
    n = sub_0001D0F0(t, bone);
    if (n == 0)
        for (;;) ;
    sub_001B2080(o->node20);
    sub_001B2020(n, o->node20);
    o->scale70[2] = 1.0f;
    o->scale70[1] = 1.0f;
    o->scale70[0] = 1.0f;
    o->f7C = 0.0f;
    o->q50[0] = 0.0f;
    o->q50[1] = 0.0f;
    o->q50[2] = 0.0f;
    o->q50[3] = 1.0f;
    o->pos60[0] = 0.0f;
    o->pos60[1] = 0.0f;
    o->pos60[2] = 0.0f;
    o->pos60[3] = 1.0f;
    sub_001AD940(o->node20);
    o->flags0C &= ~0xE0u;
    o->flags10 |= 5;
    if (mode == 1)
        s->flags00 |= 0x20;
    sub_00189DA0(o, c, 0);
}

typedef struct M1Comp95B { uint8_t unk00[0x6C]; int32_t anim6C; } M1Comp95B;
typedef struct M1Mov95 {
    uint8_t unk00[0x54];
    float   f54;               /* +0x54 */
    uint8_t unk58[0x94 - 0x58];
    void   *p94;               /* +0x94 */
    uint8_t unk98[0xB4 - 0x98];
    float   fB4, fB8, fBC, fC0, fC4, fC8, fCC, fD0, fD4;   /* +0xB4..+0xD4 */
    uint8_t unkD8[0xF8 - 0xD8];
    float   fF8;               /* +0xF8 */
} M1Mov95;
extern float m1_frameRate42C85C;
extern float m1_fps42C964;
extern float m1_jumpTime319910;
void *sub_00109050(void *o, int v);
void  sub_000F3D10(void *o, void *c, int anim);

/* 0x0010ACA0: start a jump: +0xB4 = 98 * frameRate, clear +0xB8..+0xD0; with +0x54 > 0 the
 * rise +0xB8 = +0xD4 * frameRate / (fps * 0.4), otherwise play animation 0x1A (component 5);
 * create the +0x94 helper (0x109050(4)) if missing and clear +0xF8. */
void m1_JumpStart10ACA0(void *o, M1Mov95 *s)
{
    M1Comp95B *c;
    s->fB4 = m1_frameRate42C85C * 98.0f;
    s->fC0 = 0.0f;
    s->fBC = 0.0f;
    s->fB8 = 0.0f;
    s->fD0 = 0.0f;
    s->fCC = 0.0f;
    s->fC8 = 0.0f;
    s->fC4 = 0.0f;
    if (s->f54 > 0.0f) {
        s->fB8 = s->fD4 * m1_frameRate42C85C / (m1_fps42C964 * m1_jumpTime319910);
    } else {
        if (o == 0)
            for (;;) ;
        c = (M1Comp95B *)sub_0001D960(o, 5);
        if (c->anim6C != 0x1A)
            sub_000F3D10(o, c, 0x1A);
    }
    if (s->p94 == 0)
        s->p94 = sub_00109050(o, 4);
    s->fF8 = 0.0f;
}
