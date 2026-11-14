/* Area m1, file 172: voice slot starters (revisited). Names inferred. */
#include <stdint.h>

typedef struct M1Vc172 { uint32_t f0; int32_t kind4; uint8_t unk08[0x28]; float v30[4]; float v40[4]; float v50[4]; uint8_t rest[0xDC - 0x60]; } M1Vc172;
extern M1Vc172 m1_voices420F20[56];
void sub_000A7700(M1Vc172 *v);
void sub_000F5D40(float *d, const void *s);
void m1_VoiceInit0A7DD0(M1Vc172 *v);

static int m1_VcFree172(void) {
    int i;
    for (i = 0; i < 56; i++)
        if (!(m1_voices420F20[i].f0 & 0x80000001)) return i;
    return -1;
}

/* 0xA88B0: start a voice in a free slot at a position; kinds 0x4C/0x4D/0x4F become looping variants. */
int m1_VoiceStart0A88B0(int kind, const float *pos, const float *dir) {
    M1Vc172 *v; volatile int i = m1_VcFree172();
    if (i < 0) return -1;
    v = &m1_voices420F20[i];
    sub_000A7700(v);
    v->f0 |= 0x80000000;
    v->kind4 = kind;
    sub_000F5D40(v->v40, pos);
    sub_000F5D40(v->v30, pos);
    sub_000F5D40(v->v50, dir);
    m1_VoiceInit0A7DD0(v);
    if (kind == 0x4C || kind == 0x4D || kind == 0x4F) {
        v->f0 |= 0x8000000;
        if (kind == 0x4C) kind = 4;
        else if (kind == 0x4D) kind = 0x17;
        else if (kind == 0x4F) kind = 0x4E;
        v->kind4 = kind;
    }
    return i;
}

typedef struct M1Vc172b { uint32_t f0; int32_t kind4; uint8_t unk08[0x10]; int32_t a18; int32_t a1C; uint8_t unk20[0x10]; float v30[4]; float v40[4]; float v50[4]; float v60[4]; } M1Vc172b;

/* 0xA8990: start a voice with two parameters and a second direction; same looping-variant mapping as 0xA88B0. */
int m1_VoiceStart20A8990(int kind, int p1C, int p18, const float *pos, const float *v2, const float *dir) {
    M1Vc172b *v; volatile int i = m1_VcFree172();
    if (i < 0) return -1;
    v = (M1Vc172b *)&m1_voices420F20[i];
    sub_000A7700((M1Vc172 *)v);
    v->f0 |= 0x80000000;
    v->kind4 = kind;
    v->a1C = p1C;
    v->a18 = p18;
    sub_000F5D40(v->v40, pos);
    sub_000F5D40(v->v30, pos);
    sub_000F5D40(v->v60, v2);
    sub_000F5D40(v->v50, dir);
    m1_VoiceInit0A7DD0((M1Vc172 *)v);
    if (kind == 0x4C || kind == 0x4D || kind == 0x4F) {
        v->f0 |= 0x8000000;
        if (kind == 0x4C) kind = 4;
        else if (kind == 0x4D) kind = 0x17;
        else if (kind == 0x4F) kind = 0x4E;
        v->kind4 = kind;
    }
    return i;
}

typedef struct M1Lv172 { uint8_t unk00[4]; int32_t x4; int32_t kind8; uint8_t fC; uint8_t rest[0x150 - 0xD]; } M1Lv172;
typedef struct M1Sc172 { uint8_t unk00[0x1E8]; void *x1E8; } M1Sc172;
extern M1Lv172 *m1_lvlA3F74F4;
extern M1Lv172 *m1_lvlB3F74FC;
extern void *m1_g3F74F8;
extern M1Sc172 *m1_scene42C8E4;
void sub_000ED780(void *o);
void m1_SceneDetach01D030(void *sc, void *m);
void sub_00020170(void *m);
void sub_00039820(int k);
void sub_000341A0(M1Lv172 *e);
void sub_0001E550(M1Lv172 *e);

/* 0x112890: tear down the level objects: remove the six spawned pieces, then release the three fixed objects. */
void m1_LevelFree112890(void) {
    int i; M1Lv172 *e; volatile int k;
    if (m1_lvlA3F74F4 == 0) return;
    if (m1_lvlB3F74FC != 0) {
        for (i = 0; i < 6; i++)
            if (m1_lvlB3F74FC[i].fC & 1) sub_000ED780(&m1_lvlB3F74FC[i]);
        m1_SceneDetach01D030(m1_scene42C8E4->x1E8, m1_g3F74F8);
        sub_00020170(m1_g3F74F8);
        m1_g3F74F8 = 0;
        m1_lvlB3F74FC = 0;
    }
    for (i = 0; i < 3; i++) {
        e = &m1_lvlA3F74F4[i];
        k = e->kind8;
        if (k == 3 || k == 4) sub_00039820(0);
        if (e->x4 != -1 && e->kind8 != -1) { sub_000341A0(e); sub_0001E550(e); }
    }
}

typedef struct M1Pt172 { uint8_t fx0[0x10]; uint8_t fx10[0x330]; } M1Pt172;
typedef struct M1Grp172 { uint8_t unk00[8]; M1Lv172 *x8; } M1Grp172;
extern M1Pt172 m1_parts3F6170[6];
extern int32_t *m1_lvlRes3F74F0;
M1Grp172 *sub_0001F930(int k, void *res);
void sub_0001CFF0(void *sc, void *m, int k);
void sub_0001D8B0(void *fx, int k);
void m1_ObjAddFx01D8D0(void *o, void *fx);

/* 0x1127B0: build the level objects once: spawn six pieces with their effects, then start the fixed-object sound. */
void m1_LevelBuild1127B0(void) {
    M1Pt172 *p; uint8_t *q; int i, n; volatile int k;
    if (m1_lvlB3F74FC != 0) return;
    m1_g3F74F8 = sub_0001F930(6, m1_lvlRes3F74F0);
    m1_lvlB3F74FC = ((M1Grp172 *)m1_g3F74F8)->x8;
    sub_0001CFF0(m1_scene42C8E4->x1E8, m1_g3F74F8, 2);
    for (i = 0, p = m1_parts3F6170; (int32_t)p < (int32_t)(m1_parts3F6170 + 6); p++, i += 0x150) {
        q = p->fx10;
        sub_0001D8B0(q, 0xD);
        sub_0001D8B0(p, 4);
        m1_ObjAddFx01D8D0((uint8_t *)m1_lvlB3F74FC + i, q);
        m1_ObjAddFx01D8D0((uint8_t *)m1_lvlB3F74FC + i, p);
    }
    n = *m1_lvlRes3F74F0;
    for (i = 0; i < n; i++) {
        k = m1_lvlA3F74F4[i].kind8;
        if (k == 3 || k == 4) { sub_00039820(3); return; }
    }
}

typedef struct M1An172 { uint8_t unk00[8]; int32_t kind8; } M1An172;
typedef struct M1Mv172 { uint8_t unk00[0x30]; M1An172 *anim30; uint8_t *x34; uint8_t unk38[0x28]; float pos60[4]; } M1Mv172;

/* 0xF9230: during the slide animation (0x1C), move the object by its motion vector (w kept). */
void m1_ObjSlide0F9230(M1Mv172 *o) {
    float *s;
    if (o->anim30->kind8 != 0x1C) return;
    s = (float *)(o->x34 + 0x70);
    o->pos60[0] = o->pos60[0] + s[0];
    o->pos60[1] = o->pos60[1] + s[1];
    o->pos60[2] = o->pos60[2] + s[2];
    *(volatile int32_t *)&o->pos60[3] = *(int32_t *)&o->pos60[3];
}
