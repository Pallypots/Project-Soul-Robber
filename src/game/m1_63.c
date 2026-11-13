/* Area m1, file 63: effect models with bone-linked parts. Names inferred. */
#include <stdint.h>

typedef struct M1Part0D4 { uint8_t a00[0x10]; uint8_t b10[0xD4 - 0x10]; } M1Part0D4;
typedef struct M1Model08 { uint8_t unk00[8]; uint8_t *bones08; } M1Model08;
typedef struct M1Scene1E8 { uint8_t unk000[0x1E8]; void *root1E8; } M1Scene1E8;
extern M1Scene1E8 *m1_scene42C8E4;
M1Model08 *sub_0001F930(int kind, void *res);
void sub_0001CFF0(void *root, M1Model08 *m, int layer);
void sub_0001D8B0(void *part, int kind);
void sub_0001D8D0(void *bone, void *part);

/* Shared body of 0x166B30 / 0x1721E0: once (bones still null) loads the model (0x1F930),
 * attaches it to the scene root on a layer (0x1CFF0) and binds each part pair to its
 * bone (stride 0x150): 0x1D8B0 kinds 0xD and k, then 0x1D8D0 for both. */
#define M1_FX_MODEL(name, res, model, bones, parts, n, kind, layer, k)  \
extern void *res;                                                       \
extern M1Model08 *model;                                                \
extern uint8_t *bones;                                                  \
extern M1Part0D4 parts[n];                                              \
void name(void)                                                         \
{                                                                       \
    M1Part0D4 *p;                                                       \
    int i, off;                                                         \
    if (bones != 0)                                                     \
        return;                                                         \
    model = sub_0001F930(kind, res);                                    \
    bones = model->bones08;                                             \
    sub_0001CFF0(m1_scene42C8E4->root1E8, model, layer);                \
    for (i = 0, off = 0; i < (n); i++, off += 0x150) {                  \
        p = &parts[i];                                                  \
        sub_0001D8B0(p->b10, 0xD);                                      \
        sub_0001D8B0(p, k);                                             \
        sub_0001D8D0(bones + off, p->b10);                              \
        sub_0001D8D0(bones + off, p);                                   \
    }                                                                   \
}

/* 0x00166B30: 16 parts at 0x3F76C0, model kind 0x10, layer 7, part kind 9. */
M1_FX_MODEL(m1_FxModel166B30, m1_fxRes3F8400, m1_fxModel3F8408, m1_fxBones3F840C, m1_fxParts3F76C0, 16, 0x10, 7, 9)
/* 0x001721E0: 6 parts at 0x3FD2B8, model kind 6, layer 6, part kind 8. */
M1_FX_MODEL(m1_FxModel1721E0, m1_fxRes3FD7B0, m1_fxModel3FD7B8, m1_fxBones3FD7BC, m1_fxParts3FD2B8, 6, 6, 6, 8)

typedef struct M1RigY { uint8_t unk00[0x18]; uint32_t flags18; uint8_t unk1C[4]; float q20[4]; } M1RigY;
typedef struct M1StepY { uint8_t unk000[0x74]; float t74; uint8_t unk078[0x278 - 0x78]; M1RigY *rig278; } M1StepY;
typedef struct M1ObjY { uint8_t unk00[0xC]; uint32_t flags0C, flags10; uint8_t unk14[0x60 - 0x14]; float pos60[3]; } M1ObjY;
typedef struct M1CmdY { uint8_t unk00[0x10]; float v10[4]; } M1CmdY;
int     sub_001456E0(void *o, void *s, int a, int b);
int     sub_00036750(void *o, int v);
int     sub_000494D0(int id, const void *pos, int c);
M1CmdY *sub_00113400(void *h, int v);

/* 0x00186B50: 0x1456E0(0x23), rig quaternion +0x20 = (0, 0, 0, 1), timer +0x74 = 4,
 * 0x36750(4), sound 0x114 at o, clear o +0xC bits 0xC0, rig flag 0x10, o flag 4,
 * command 4 vector = 0. */
void m1_RigStep186B50(M1ObjY *o, M1StepY *h)
{
    M1RigY *r = h->rig278;
    M1RigY *p;
    M1CmdY *c;
    sub_001456E0(o, h, 0x23, 0);
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    h->t74 = 4.0f;
    sub_00036750(o, 4);
    sub_000494D0(0x114, o->pos60, 0);
    o->flags0C &= ~0xC0u;
    r->flags18 |= 0x10;
    o->flags10 |= 4;
    c = sub_00113400(h, 4);
    c->v10[0] = 0.0f;
    c->v10[1] = 0.0f;
    c->v10[2] = 0.0f;
    c->v10[3] = 0.0f;
}

typedef struct M1Face { uint8_t unk00[0xC]; uint32_t flags0C; uint8_t unk10[0x10]; void *node20; uint8_t unk24[0x60 - 0x24]; float pos60[4]; } M1Face;
typedef struct M1PlPos { uint8_t unk00[0x60]; float pos60[4]; } M1PlPos;
extern M1PlPos *g_playerObj;
void  sub_001AD9F0(float *out, const float *a, const float *b);
float sub_001B27C0(const float *a, const float *b);
void  sub_001AD940(float *m);
void  sub_001AD910(float *out, const float *m, float a);
void  sub_001AD8E0(float *out, const float *m, float a);
void  sub_001ADA40(void *node, const float *m);

/* 0x0018AB70: clears o flag 0x20 and turns o's node to face the player: the angle
 * between (0, 0, -1) and the direction to the player (0x1B27C0) becomes the y rotation
 * of a matrix pre-rotated by pi/2 (0x1AD910, 0x1AD8E0), applied with 0x1ADA40. */
void m1_FacePlayer18AB70(M1Face *o)
{
    float fwd[4];
    float d[4];
    float m[16];
    float a;
    fwd[0] = 0.0f;
    fwd[1] = 0.0f;
    fwd[2] = -1.0f;
    fwd[3] = 0.0f;
    o->flags0C &= ~0x20u;
    sub_001AD9F0(d, o->pos60, g_playerObj->pos60);
    a = sub_001B27C0(fwd, d);
    sub_001AD940(m);
    sub_001AD910(m, m, 1.5707964f);
    sub_001AD8E0(m, m, a);
    sub_001ADA40(o->node20, m);
}

typedef struct M1RigF2 { uint8_t unk00[4]; uint32_t flags04; uint8_t unk08[0x2C - 8]; float q2C[4]; } M1RigF2;
typedef struct M1StepF2 { uint8_t unk000[0x278]; M1RigF2 *rig278; } M1StepF2;
typedef struct M1ObjF2 { uint8_t unk00[0x10]; uint32_t flags10; } M1ObjF2;
void sub_0001D4E0(void *o);

/* 0x00116630: 0x1456E0(0x30) (0x1D4E0 on 1), rig quaternion +0x2C = (0, 0, 0, 1),
 * o flag 4, clears rig flag 0x80000; when rig flag 8 was set clears it too and sets
 * command 2 to (0.1, 0, 0); o flags |= 0xD with rig flag 0x10. */
void m1_RigStep116630(M1ObjF2 *o, M1StepF2 *h)
{
    M1RigF2 *r = h->rig278;
    M1RigF2 *p;
    M1CmdY *c;
    uint32_t f;
    if (sub_001456E0(o, h, 0x30, 0) == 1)
        sub_0001D4E0(o);
    p = h->rig278;
    p->q2C[2] = 0.0f;
    p->q2C[1] = 0.0f;
    p->q2C[0] = 0.0f;
    p->q2C[3] = 1.0f;
    o->flags10 |= 4;
    f = r->flags04 & ~0x80000u;
    r->flags04 = f;
    if (f & 8) {
        r->flags04 = f & ~8u;
        c = sub_00113400(h, 2);
        c->v10[0] = 0.1f;
        c->v10[1] = 0.0f;
        c->v10[2] = 0.0f;
    }
    if (*(uint8_t *)&r->flags04 & 0x10)
        o->flags10 |= 0xD;
}

typedef struct M1Shot { uint8_t unk00[0x10]; float n10; } M1Shot;
typedef struct M1StepS { uint8_t unk00[0x4C]; uint32_t flags4C; } M1StepS;
typedef struct M1ObjS { uint8_t unk00[0x60]; float pos60[4]; } M1ObjS;
extern uint8_t m1_stats41FEC0[];
int  sub_00113670(void *o, void *h, int n, float *tgt);
void sub_001AD7E0(float *out, const float *v);
int  sub_000D3BF0(void *stats, void *o, int n, const float *tgt, const float *dir);
void sub_00113370(void *h, void *s);

/* 0x001556D0: fires shot type (int)+0x10: when 0x113670 finds a target, the flat unit
 * direction from o to the player goes with it to 0xD3BF0; a hit sets h flag 0x100;
 * then the step is finished (0x113370). */
void m1_Shoot1556D0(M1ObjS *o, M1StepS *h, M1Shot *s)
{
    float d[4];
    float tgt[4];
    if (sub_00113670(o, h, (int)s->n10, tgt) < 0)
        return;
    sub_001AD9F0(d, g_playerObj->pos60, o->pos60);
    d[1] = 0.0f;
    d[3] = 1.0f;
    sub_001AD7E0(d, d);
    if (sub_000D3BF0(m1_stats41FEC0, o, (int)s->n10, tgt, d) != -1)
        h->flags4C |= 0x100;
    sub_00113370(h, s);
}
