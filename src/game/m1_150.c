/* Area m1, file 150: HUD popup helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Pop150 { int32_t used; int32_t x; int32_t lo; int32_t hi; int32_t col; void *txt; int32_t k; } M1Pop150;
typedef struct M1Hud150 { uint8_t unk00[0x408]; int32_t on408; uint8_t unk40C[0xC]; int32_t n418; uint8_t unk41C[0x14]; M1Pop150 pop[8]; } M1Hud150;
typedef struct M1Ev150 { int32_t x0; uint8_t unk04[8]; int32_t kC; int32_t n10; int32_t k14; } M1Ev150;
extern int32_t m1_hudCol318608[8];
void *m1_HudText0E85D0(int k, float size);

/* 0xEB2A0: show a score popup in a free HUD slot (or just draw the text when there is no HUD). */
void m1_HudPopup0EB2A0(M1Hud150 *h, M1Ev150 *e) {
    int i; void *t; M1Pop150 *p;
    if (e == 0) return;
    if (h == 0) { m1_HudText0E85D0(e->kC, (float)e->n10 * 0.0299999993f); return; }
    if (h->on408 == 0) return;
    for (i = 0; i < 8; i++)
        if (h->pop[i].used == 0) break;
    if (i >= 8) return;
    t = m1_HudText0E85D0(e->kC, (float)e->n10 * 0.0299999993f);
    h->n418++;
    p = &h->pop[i];
    p->used = 1;
    p->x = e->x0;
    p->lo = e->x0 - e->n10 / 2;
    p->hi = e->n10 / 2 + e->x0;
    *(void **)&((M1Pop150 *)h)[i + 0x27] = t;
    p->col = m1_hudCol318608[e->kC];
    p->k = e->k14;
}


typedef struct M1Mdl150 { uint8_t unk00[0x20]; void *f20; } M1Mdl150;
typedef struct M1Pw150 {
    uint8_t unk00[0x61C]; void *fx61C; uint8_t unk620[0xD60 - 0x620]; uint32_t flagsD60;
    uint8_t unkD64[0xD94 - 0xD64]; float tD94; uint8_t unkD98[0xFC0 - 0xD98]; uint8_t vFC0[0x18]; M1Mdl150 *mdlFD8;
} M1Pw150;
typedef struct M1Sc150 { uint8_t unk00[0x3B0]; void *x3B0; } M1Sc150;
extern M1Sc150 *m1_scene2_42C8EC;
extern float m1_frameTime42C858;
void  sub_000D04E0(void *a, void *b);
void  m1_PowerEnd0C9E00(void *b);
void  m1_PowerAura0CA6C0(M1Pw150 *o);
void  sub_00033A40(void *fx);
void *sub_00036750(M1Mdl150 *m, int id);
void  m1_FxTint034D30(void *fx, float r, float g, float b, float a);

/* 0xD1F90: run the second timed power-up (720 frames): aura each frame, effect fades near the end. */
void m1_Power2Tick0D1F90(M1Pw150 *o) {
    void *p;
    if (!(o->flagsD60 & 2)) return;
    if (o->tD94 >= 720.0f) {
        sub_000D04E0(m1_scene2_42C8EC->x3B0, o->vFC0);
        m1_PowerEnd0C9E00(o->vFC0);
        o->flagsD60 &= ~2u; o->tD94 = 0.0f;
        if (o->fx61C != 0) { sub_00033A40(o->fx61C); o->fx61C = 0; }
        return;
    }
    m1_PowerAura0CA6C0(o);
    o->tD94 += m1_frameTime42C858;
    p = o->fx61C;
    if (p == 0) {
        if (o->mdlFD8 != 0 && o->mdlFD8->f20 != 0) p = sub_00036750(o->mdlFD8, 0x4C);
        o->fx61C = p;
        return;
    }
    if (o->tD94 >= 710.0f) m1_FxTint034D30(p, 1.0f, 1.0f, 1.0f, 0.800000012f);
}

typedef struct M1Slot150 { uint8_t fx0[0x10]; uint8_t fx10[0x14]; void *cb24; void *cb28; void *cb2C; uint8_t unk30[0x1C]; int32_t x4C; uint8_t rest[0x118 - 0x50]; } M1Slot150;
typedef struct M1Ob150 { uint8_t unk00[0xC]; uint32_t fC; uint8_t unk10[0x40]; float v50[4]; float v60[4]; uint8_t unk70[0x14C - 0x70]; int32_t i14C; } M1Ob150;
extern M1Slot150 *m1_pool3F60F0;
extern void *m1_scene42C8E4;
extern uint8_t m1_snd3E1270[];
int  m1_PoolCount0F30E0(int k);
void sub_0001D8B0(void *fx, int k);
void m1_ObjAddFx01D8D0(M1Ob150 *o, void *fx);
void sub_0001E9B0(void *sc, M1Ob150 *o, int k, int a, int b);
void sub_0001EBF0(M1Ob150 *o, int k);
void m1_PoolRefresh0F2D30(void);
void sub_000F5D40(float *d, const void *s);
void sub_000192B0(void *list, M1Ob150 *o);
void m1_CbUpd0EFDE0(void);
void m1_CbDraw0F2A60(void);
void m1_CbKill0EEE10(void);

/* 0xF2FE0: attach a pooled effect pair to an object, place it, and hook up its callbacks. */
M1Ob150 *m1_PoolAttach0F2FE0(M1Ob150 *o, const float *pos, const float *vel) {
    int i = 0; M1Slot150 *s; uint8_t *s2;
    if (o == 0) for (;;) ;
    for (i = 0; i < m1_PoolCount0F30E0(7); i++)
        if (m1_pool3F60F0[i].x4C == 0) break;
    s = &m1_pool3F60F0[i];
    s2 = s->fx10;
    sub_0001D8B0(s, 5);
    m1_ObjAddFx01D8D0(o, s);
    sub_0001D8B0(s2, 0xD);
    m1_ObjAddFx01D8D0(o, s2);
    sub_0001E9B0(m1_scene42C8E4, o, o->i14C, 5, 0x11);
    sub_0001EBF0(o, 1);
    m1_PoolRefresh0F2D30();
    if (pos != 0) sub_000F5D40(o->v60, pos);
    if (vel != 0) sub_000F5D40(o->v50, vel);
    o->fC |= 0x200;
    sub_000192B0(m1_snd3E1270, o);
    s->cb24 = (void *)m1_CbUpd0EFDE0;
    s->cb28 = (void *)m1_CbDraw0F2A60;
    s->cb2C = (void *)m1_CbKill0EEE10;
    return o;
}
