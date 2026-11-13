/* Area m1, file 69: rig setups by difficulty. Names inferred. */
#include <stdint.h>

typedef struct M1RigD {
    uint8_t unk00[0x20];
    float   f20;               /* +0x20 */
    int32_t f24;               /* +0x24 */
    int16_t w28;               /* +0x28 */
    uint8_t unk2A[2];
    float   f2C;               /* +0x2C */
    int16_t hits30;            /* +0x30 */
    uint8_t unk32[2];
    float   f34;               /* +0x34 */
    uint8_t unk38[4];
    float   pos3C[4];          /* +0x3C */
} M1RigD;
typedef struct M1StepD { uint8_t unk000[0x278]; M1RigD *rig278; } M1StepD;
extern uint32_t m1_level413178;
extern const int32_t m1_hitsA27A684[3], m1_hitsB27A690[3];
int    sub_000F40B0(void);
float *sub_0001D0F0(void *o, int v);
void   sub_000F5D40(float *dst, const float *src);

/* 0x0017DCF0: rig setup: +0x28 = 2, +0x2C = 0, +0x20 = 0, +0x24 = 1; hit count +0x30 from
 * the level (capped at 2) table, 0x27A684 with scale 1.5 or 0x27A690 with 1.0 when
 * 0xF40B0 says so; position +0x3C from o's frame (+0x70) raised by 18, w = 1.0. */
void m1_RigSetup17DCF0(void *o, M1StepD *h)
{
    M1RigD *r = h->rig278;
    uint32_t lvl;
    float s;
    r->w28 = 2;
    r->f2C = 0.0f;
    r->f20 = 0.0f;
    r->f24 = 1;
    lvl = m1_level413178;
    if (lvl > 2)
        lvl = 2;
    if (sub_000F40B0() == 0) {
        r->hits30 = (int16_t)m1_hitsA27A684[lvl];
        s = 1.5f;
    } else {
        r->hits30 = (int16_t)m1_hitsB27A690[lvl];
        s = 1.0f;
    }
    r->f34 = s;
    sub_000F5D40(r->pos3C, sub_0001D0F0(o, 1) + 0x1C);
    r->pos3C[1] = r->pos3C[1] + 18.0f;
    r->pos3C[3] = 1.0f;
}

typedef struct M1RigN2 { uint8_t unk00[0x20]; float q20[4]; uint8_t unk30[0x8C - 0x30]; float f8C, f90; } M1RigN2;
typedef struct M1StepN2 { uint8_t unk000[0x278]; M1RigN2 *rig278; } M1StepN2;
typedef struct M1CmdN2 { uint8_t unk00[0x10]; float f10, f14, f18, f1C; } M1CmdN2;
extern float m1_frameRate42C85C;
int      sub_001456E0(void *o, void *s, int a, int b);
int      sub_00036750(void *o, int v);
M1CmdN2 *sub_00113400(void *h, int v);

/* 0x00187280: 0x1456E0(0x10), rig quaternion +0x20 = (0, 0, 0, 1), 0x36750(0), rig +0x8C = 4,
 * rig +0x90 = frame rate * 50, command 3 = (0.3, 0.3, 10, 1). */
void m1_RigStep187280(void *o, M1StepN2 *h)
{
    M1RigN2 *r = h->rig278;
    M1RigN2 *p;
    M1CmdN2 *c;
    sub_001456E0(o, h, 0x10, 0);
    p = h->rig278;
    p->q20[2] = 0.0f;
    p->q20[1] = 0.0f;
    p->q20[0] = 0.0f;
    p->q20[3] = 1.0f;
    sub_00036750(o, 0);
    r->f8C = 4.0f;
    r->f90 = m1_frameRate42C85C * 50.0f;
    c = sub_00113400(h, 3);
    c->f10 = 0.3f;
    c->f14 = 0.3f;
    c->f18 = 10.0f;
    c->f1C = 1.0f;
}

typedef struct M1Model08b { uint8_t unk00[8]; uint8_t *bones08; } M1Model08b;
typedef struct M1Scene1E8b { uint8_t unk000[0x1E8]; void *root1E8; } M1Scene1E8b;
extern M1Scene1E8b *m1_scene42C8E4;
int  sub_000ED780(void *o);
void sub_0001D030(void *root, M1Model08b *m);
void sub_00020170(M1Model08b *m);
void sub_000341A0(void *o);
void sub_0001E550(void *o);

/* Shared body of 0x166BD0 / 0x172280 (undo 0x166B30 / 0x1721E0): ends every active bone
 * object (byte +0xC bit 0, stride 0x150), detaches and frees the model and clears both
 * pointers; then releases the objects (stride 0x150) at objs (0x341A0, 0x1E550). Nothing
 * to do without them. */
#define M1_FX_FREE(name, objs, model, bones, bonesEnd, objsEnd)        extern uint8_t *objs;                                                  extern M1Model08b *model;                                              extern uint8_t *bones;                                                 void name(void)                                                        {                                                                          int off;                                                               if (objs == 0)                                                             return;                                                            if (bones != 0) {                                                          for (off = 0; off < (bonesEnd); off += 0x150) {                            uint8_t *b = bones + off;                                              if (b[0xC] & 1)                                                            sub_000ED780(b);                                               }                                                                      sub_0001D030(m1_scene42C8E4->root1E8, model);                          sub_00020170(model);                                                   model = 0;                                                             bones = 0;                                                         }                                                                      for (off = 0; off < (objsEnd); off += 0x150) {                             sub_000341A0(objs + off);                                              sub_0001E550(objs + off);                                          }                                                                  }

/* 0x00166BD0: frees the 0x166B30 model (16 bones, 3 objects at 0x3F8404). */
M1_FX_FREE(m1_FxModelFree166BD0, m1_fxObjs3F8404, m1_fxModel3F8408, m1_fxBones3F840C, 0x1500, 0x3F0)
/* 0x00172280: frees the 0x1721E0 model (6 bones, 6 objects at 0x3FD7B4). */
M1_FX_FREE(m1_FxModelFree172280, m1_fxObjs3FD7B4, m1_fxModel3FD7B8, m1_fxBones3FD7BC, 0x7E0, 0x7E0)
/* 0x00174EF0: frees the effect model at 0x3FD7D0 (16 bones, 7 objects at 0x3FD7CC). */
M1_FX_FREE(m1_FxModelFree174EF0, m1_fxObjs3FD7CC, m1_fxModel3FD7D0, m1_fxBones3FD7D4, 0x1500, 0x930)

typedef struct M1Part340 { uint8_t a00[0x10]; uint8_t b10[0x340 - 0x10]; } M1Part340;
extern void *m1_fxRes3FD7C8;
extern M1Part340 m1_fxParts414460[16];
M1Model08b *sub_0001F930(int kind, void *res);
void sub_0001CFF0(void *root, M1Model08b *m, int layer);
void sub_0001D8B0(void *part, int kind);
void sub_0001D8D0(void *bone, void *part);

/* 0x00174E50: once (bones 0x3FD7D4 null): loads model kind 0x10 (res 0x3FD7C8) into
 * 0x3FD7D0, attaches it to the scene root on layer 4 and binds the 16 part pairs at
 * 0x414460 (stride 0x340; kinds 0xD and 6) to bones (stride 0x150). */
void m1_FxModel174E50(void)
{
    M1Part340 *p;
    int i, off;
    if (m1_fxBones3FD7D4 != 0)
        return;
    m1_fxModel3FD7D0 = sub_0001F930(0x10, m1_fxRes3FD7C8);
    m1_fxBones3FD7D4 = m1_fxModel3FD7D0->bones08;
    sub_0001CFF0(m1_scene42C8E4->root1E8, m1_fxModel3FD7D0, 4);
    for (i = 0, off = 0; i < 16; i++, off += 0x150) {
        p = &m1_fxParts414460[i];
        sub_0001D8B0(p->b10, 0xD);
        sub_0001D8B0(p, 6);
        sub_0001D8D0(m1_fxBones3FD7D4 + off, p->b10);
        sub_0001D8D0(m1_fxBones3FD7D4 + off, p);
    }
}
