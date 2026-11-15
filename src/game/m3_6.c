/* Area m3, file 6: boss move-toward helpers. Names inferred. */
#include <stdint.h>

typedef struct M3Tgt6 { uint8_t unk00[0x60]; float pos60[4]; } M3Tgt6;
typedef struct M3Boss6 { uint8_t unk00[0x5B0]; float home5B0[4]; uint8_t unk5C0[0x10]; float vel5D0[4]; float acc5E0[4]; uint8_t unk5F0[0x9E8]; M3Tgt6 *tgtFD8; } M3Boss6;
void r4c_VecSub(float *dst, const float *a, const float *b);
float m1_VecLen082D70(const float *v);
void rbi_VecNorm(float *d, const float *s);
void rbi_VecScale(float *d, const float *s, float k);

/* 0xCBD60: aim the boss from its target back to its home point: velocity = direction * (distance / 30 * 3), acceleration = direction * -(that * 0.02). */
void m3_BossHomeVelCBD60(M3Boss6 *b) {
    float v[4]; float d;
    v[0] = 0.0f; v[1] = 0.0f; v[2] = 0.0f; v[3] = 1.0f;
    r4c_VecSub(v, b->home5B0, b->tgtFD8->pos60);
    d = m1_VecLen082D70(v);
    rbi_VecNorm(v, v);
    d = d * 0.033333335f * 3.0f;
    rbi_VecScale(b->vel5D0, v, d);
    rbi_VecScale(b->acc5E0, v, (float)(d * 0.02 * -1.0));
}

typedef struct M3Soul6 { uint32_t f0; int32_t kind4; uint8_t unk08[0x38]; float pos40[4]; } M3Soul6;
typedef struct M3SoulTab6 { int32_t amount[4]; int32_t sfx[4]; } M3SoulTab6;
extern float m3_soulCool423EE0[];
extern uint8_t g_stats[];
void aab_Effect494D0(int id, void *pos, int a);
void aab_Add24D30(int a, int n);
void aab_StatD1E10(void *s, int id, int n);
void aab_SoulsAdd(int n);

/* 0xA9B80: collect a soul pickup (kinds 0x18..0x1B worth 1, 10, 30, 100): mark it taken, play its sound once per cooldown, add the amount to the counter, the stats and the soul total. */
void m3_SoulPickupA9B80(M3Soul6 *s) {
    M3SoulTab6 t; int k;
    t.sfx[0] = 0x57; t.sfx[1] = 0x57;
    s->f0 |= 0x40000000;
    t.amount[0] = 1; t.amount[1] = 10; t.amount[2] = 30; t.amount[3] = 100;
    t.sfx[2] = 0x58; t.sfx[3] = 0x59;
    { volatile int vk = (s->kind4 - 0x18) * 4; k = vk; }
    if (*(float *)((uint8_t *)m3_soulCool423EE0 + 0x60 + k) > 0.0f) {
        aab_Effect494D0(*(int *)((uint8_t *)t.sfx + k), s->pos40, 0);
        m3_soulCool423EE0[s->kind4] = 0.0f;
    }
    aab_Add24D30(2, t.amount[s->kind4 - 0x18]);
    aab_StatD1E10(g_stats, 0xC, t.amount[s->kind4 - 0x18]);
    aab_SoulsAdd(t.amount[s->kind4 - 0x18]);
}
