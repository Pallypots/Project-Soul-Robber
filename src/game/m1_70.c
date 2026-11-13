/* Area m1, file 70: effect model with 19 parts. Names inferred. */
#include <stdint.h>

typedef struct M1Model08c { uint8_t unk00[8]; uint8_t *bones08; } M1Model08c;
typedef struct M1Scene1E8c { uint8_t unk000[0x1E8]; void *root1E8; } M1Scene1E8c;
typedef struct M1Part08C { uint8_t a00[0x10]; uint8_t b10[0x8C - 0x10]; } M1Part08C;
extern M1Scene1E8c *m1_scene42C8E4;
extern void *m1_fxRes3FF57C;
extern M1Model08c *m1_fxModel414440;
extern uint8_t *m1_fxBones414444;
extern uint8_t *m1_fxObjs3FF584;
extern M1Part08C m1_fxParts3FEB18[19];
M1Model08c *sub_0001F930(int kind, void *res);
void sub_0001CFF0(void *root, M1Model08c *m, int layer);
void sub_0001D8B0(void *part, int kind);
void sub_0001D8D0(void *bone, void *part);
int  sub_000ED780(void *o);
void sub_0001D030(void *root, M1Model08c *m);
void sub_00020170(M1Model08c *m);
void sub_000341A0(void *o);
void sub_0001E550(void *o);

/* 0x00189B90: once (bones 0x414444 null): model kind 0x13 (res 0x3FF57C) into 0x414440,
 * scene root layer 5, binds 19 part pairs at 0x3FEB18 (stride 0x8C; kinds 0xD/7) to bones
 * (stride 0x150), base part first. */
void m1_FxModel189B90(void)
{
    M1Part08C *p;
    int i, off;
    if (m1_fxBones414444 != 0)
        return;
    m1_fxModel414440 = sub_0001F930(0x13, m1_fxRes3FF57C);
    m1_fxBones414444 = m1_fxModel414440->bones08;
    sub_0001CFF0(m1_scene42C8E4->root1E8, m1_fxModel414440, 5);
    for (i = 0, off = 0; i < 19; i++, off += 0x150) {
        p = &m1_fxParts3FEB18[i];
        sub_0001D8B0(p->b10, 0xD);
        sub_0001D8B0(p, 7);
        sub_0001D8D0(m1_fxBones414444 + off, p);
        sub_0001D8D0(m1_fxBones414444 + off, p->b10);
    }
}

/* 0x00189C30: undoes 0x189B90: ends active bone objects (19 x 0x150), detaches and frees
 * the model, clears both pointers; releases the 11 objects at 0x3FF584 (0x341A0, 0x1E550). */
void m1_FxModelFree189C30(void)
{
    int off;
    if (m1_fxObjs3FF584 == 0)
        return;
    if (m1_fxBones414444 != 0) {
        for (off = 0; off < 0x18F0; off += 0x150) {
            uint8_t *b = m1_fxBones414444 + off;
            if (b[0xC] & 1)
                sub_000ED780(b);
        }
        sub_0001D030(m1_scene42C8E4->root1E8, m1_fxModel414440);
        sub_00020170(m1_fxModel414440);
        m1_fxModel414440 = 0;
        m1_fxBones414444 = 0;
    }
    for (off = 0; off < 0xE70; off += 0x150) {
        sub_000341A0(m1_fxObjs3FF584 + off);
        sub_0001E550(m1_fxObjs3FF584 + off);
    }
}

typedef struct M1Part078 { uint8_t a00[0x10]; uint8_t b10[0x78 - 0x10]; } M1Part078;
typedef struct M1Part088 { uint8_t a00[0x10]; uint8_t b10[0x88 - 0x10]; } M1Part088;
extern void *m1_fxRes3F92E8;
extern M1Model08c *m1_fxModel3F92F0, *m1_fxModel3F92F8;
extern uint8_t *m1_fxBones3F92F4, *m1_fxBones3F92FC;
extern M1Part078 m1_fxParts3F8CE8[6];
extern M1Part088 m1_fxParts3F8FB8[6];

/* 0x0016FA40: once (bones 0x3F92F4 null) loads two kind-6 models from res 0x3F92E8: the
 * first (0x3F92F0, layer 8) binds 6 parts at 0x3F8CE8 (stride 0x78, kind 0xA), the second
 * (0x3F92F8, layer 9) 6 parts at 0x3F8FB8 (stride 0x88, kind 0xB); base part first. */
void m1_FxModels16FA40(void)
{
    M1Part078 *p;
    M1Part088 *q;
    int i, off;
    if (m1_fxBones3F92F4 != 0)
        return;
    m1_fxModel3F92F0 = sub_0001F930(6, m1_fxRes3F92E8);
    m1_fxBones3F92F4 = m1_fxModel3F92F0->bones08;
    sub_0001CFF0(m1_scene42C8E4->root1E8, m1_fxModel3F92F0, 8);
    for (i = 0, off = 0; i < 6; i++, off += 0x150) {
        p = &m1_fxParts3F8CE8[i];
        sub_0001D8B0(p->b10, 0xD);
        sub_0001D8B0(p, 0xA);
        sub_0001D8D0(m1_fxBones3F92F4 + off, p);
        sub_0001D8D0(m1_fxBones3F92F4 + off, p->b10);
    }
    m1_fxModel3F92F8 = sub_0001F930(6, m1_fxRes3F92E8);
    m1_fxBones3F92FC = m1_fxModel3F92F8->bones08;
    sub_0001CFF0(m1_scene42C8E4->root1E8, m1_fxModel3F92F8, 9);
    for (i = 0, off = 0; i < 6; i++, off += 0x150) {
        q = &m1_fxParts3F8FB8[i];
        sub_0001D8B0(q->b10, 0xD);
        sub_0001D8B0(q, 0xB);
        sub_0001D8D0(m1_fxBones3F92FC + off, q);
        sub_0001D8D0(m1_fxBones3F92FC + off, q->b10);
    }
}
