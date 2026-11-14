/* Area m1, file 149: player and minion setup helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Anm149 { uint8_t unk00[0x30]; void *anim30; } M1Anm149;
typedef struct M1Min149 {
    uint8_t unk00[0x8C]; M1Anm149 *o8C; M1Anm149 *o90; uint8_t unk94[8]; int32_t i9C;
    uint8_t unkA0[0x168 - 0xA0]; float f168; float f16C; uint8_t unk170[4]; float f174; float f178;
    uint8_t unk17C[8]; float v184[4]; float v194[4]; uint8_t unk1A4[0x10]; float f1B4;
} M1Min149;
extern M1Min149 *m1_minion3F6120;
extern float m1_fps42C964;
void sub_000832D0(void *a, int id);
void sub_000F5D40(float *d, const void *s);

/* 0xFEBF0: launch the minion toward a target on a ballistic arc. */
void m1_MinionLaunch0FEBF0(uint8_t *tgt) {
    M1Min149 *p = m1_minion3F6120; float a, b, x; volatile float k = 2.0f;
    if (p == 0) for (;;) ;
    if (p->o8C == 0) for (;;) ;
    sub_000832D0(p->o8C->anim30, 0x25);
    sub_000832D0(m1_minion3F6120->o90->anim30, 0x25);
    p->i9C = 0;
    sub_000F5D40(p->v194, tgt + 0x60);
    p->f1B4 = 65.0f / m1_fps42C964;
    p->v184[3] = 0.0f; p->v184[2] = 0.0f; p->v184[1] = 0.0f; p->v184[0] = 0.0f;
    a = p->f168; b = p->f16C;
    x = b / a * k * k;
    p->f174 = (b - x * a * 0.5f) * 8.0f / (a * a);
    p->f178 = x;
}

typedef struct M1Pl149 {
    uint8_t unk00[0xD4]; int32_t d4; uint8_t unkD8[0x150 - 0xD8]; uint32_t flags150;
    uint8_t unk154[0x1B8 - 0x154]; uint32_t mode1B8; uint8_t unk1BC[0xD60 - 0x1BC]; int32_t d60;
} M1Pl149;
extern M1Pl149 m1_stats41FEC0;
extern void *m1_scene2_42C8EC;
extern void *g_playerObj;
extern uint8_t m1_tbl276DBC[];
void m1_StatsTick0D1930(M1Pl149 *s);
void sub_000BD4D0(M1Pl149 *s, int st);
void m1_SndPlay023D80(int a, int b);
void m1_SndBank0243B0(int a, int b);
void m1_SceneFade0D4C10(void *sc);
void m1_SceneCam0D45B0(void *sc, int a, int b, float t);
void sub_000BC6F0(void *t, int k);
void m1_BoneEntsClearKeptCE970(void);
void m1_MarkJackEntriesCEF60(void);
void *m1_ObjBone01D290(void *o, int k);
void m1_BoneRelease0CED50(void *b);

/* 0xD3680: return the player to normal control after a cutscene or event. */
void m1_PlayerResume0D3680(void) {
    M1Pl149 *s = &m1_stats41FEC0; uint32_t f;
    m1_StatsTick0D1930(s);
    f = s->flags150 & ~0x80000u;
    s->flags150 = f;
    s->d60 = 0;
    if (!(*(volatile uint32_t *)&f & 0x80000)) {
        if (!(f & 0x80000807)) sub_000BD4D0(s, 6);
        m1_SndPlay023D80(0, 0);
        m1_SndBank0243B0(0, s->mode1B8);
        s->d4 = 0;
        if (s->mode1B8 == 0 && !(s->flags150 & 0x800)) {
            m1_SceneFade0D4C10(m1_scene2_42C8EC);
            m1_SceneCam0D45B0(m1_scene2_42C8EC, 0, 0, -1.0f);
        }
        if (s->mode1B8 <= 1) {
            sub_000BC6F0(m1_tbl276DBC, 0);
            m1_BoneEntsClearKeptCE970();
            m1_MarkJackEntriesCEF60();
            m1_BoneRelease0CED50(m1_ObjBone01D290(g_playerObj, 0));
        }
    }
    if (s->mode1B8 != 2) m1_BoneRelease0CED50(m1_ObjBone01D290(g_playerObj, 0));
}

typedef struct M1Bo149 { uint8_t unk00[0x88]; int32_t i88; } M1Bo149;
typedef struct M1Grp149 { uint8_t unk00[4]; struct M1Grp149 *next4; uint8_t unk08[0x14]; M1Bo149 *obj1C; } M1Grp149;
typedef struct M1Par149 { float f0; uint8_t unk04[0x18]; float f1C; float f20; } M1Par149;
typedef struct M1Tr149 { void *root0; M1Grp149 *list4; uint8_t *src8; M1Par149 *parC; } M1Tr149;
extern float m1_bvhMat3EC8F8[16];
extern float m1_bvhScaleA3ECA34, m1_bvhF3ECA2C, m1_bvhScaleB3ECA50, m1_bvhF3ECA08;
void sub_001ADA40(void *d, const void *m);
void sub_001AE060(float *d, const float *s);
void m1_BvhWalk081D50(void *root);

/* 0x81E60: prepare a collision tree for a query (clear marks, load its matrix, set scales). */
void m1_BvhPrepare081E60(M1Tr149 *t, int flags) {
    M1Grp149 *g; M1Par149 *p; float r;
    if (t == 0 || t->list4 == 0) return;
    for (g = t->list4; g != 0; g = g->next4)
        if (g->obj1C != 0) g->obj1C->i88 = 0;
    sub_001ADA40(m1_bvhMat3EC8F8, t->src8 + 0xB0);
    if (flags & 1) {
        sub_001AE060(m1_bvhMat3EC8F8, m1_bvhMat3EC8F8);
        m1_bvhMat3EC8F8[14] = 0.0f; m1_bvhMat3EC8F8[13] = 0.0f; m1_bvhMat3EC8F8[12] = 0.0f; m1_bvhMat3EC8F8[15] = 1.0f;
        sub_001AE060(m1_bvhMat3EC8F8, m1_bvhMat3EC8F8);
    }
    p = t->parC;
    r = 1.0f / p->f0;
    m1_bvhScaleA3ECA34 = r * 240.0f;
    m1_bvhF3ECA2C = p->f20;
    m1_bvhScaleB3ECA50 = r * 320.0f;
    m1_bvhF3ECA08 = p->f1C;
    if (t->root0 != 0) m1_BvhWalk081D50(t->root0);
}
