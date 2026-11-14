/* Area m1, file 183: sound effect helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Fx183 {
    uint32_t flags0; uint8_t unk04[0xC]; void *owner10; uint8_t list14[0xC]; struct M1Fx183 *self20; float f24; int32_t i28;
} M1Fx183;
typedef struct M1Own183 { uint8_t unk00[0x13C]; M1Fx183 *fx13C; } M1Own183;
extern uint8_t r1e_fxPool3E4B70[];
extern uint8_t r1e_fxListA3E4B60[];
void  r1c_SndOwnerFree(M1Fx183 *fx);
void *r1c_PoolTake(void *pool, int size);
void  a3c_Clear16(void *l);
void  a5b_RangeInit(M1Fx183 *fx);
void  a4c_ListAppend(void *list, void *node);
void  a5b_PairSet(M1Fx183 *fx, void *e);

/* 0x5CB90: give an owner a new pooled sound effect bound to entry e (old effect freed first). */
void m1_SndAttachNew05CB90(M1Own183 *o, uint8_t *e) {
    uint8_t *p; M1Fx183 *fx;
    if (o == 0) return;
    if (o->fx13C) { r1c_SndOwnerFree(o->fx13C); o->fx13C = 0; }
    p = r1c_PoolTake(r1e_fxPool3E4B70, 0x3C);
    if (p == 0) fx = 0;
    else {
        fx = (M1Fx183 *)(p + 0x10);
        if (fx) {
            a3c_Clear16(fx->list14);
            a5b_RangeInit(fx);
            fx->f24 = 1.0f; fx->i28 = -1; fx->self20 = fx;
            a4c_ListAppend(r1e_fxListA3E4B60, fx->list14);
        }
    }
    o->fx13C = fx;
    if (fx == 0) return;
    fx->owner10 = o;
    *(uint8_t **)(e + 0xC) = e + 0x10;
    a5b_PairSet(o->fx13C, e);
    o->fx13C->flags0 |= 1;
}

extern uint8_t m1_menuSprA3E49E4[];
extern uint8_t m1_menuSprB3E4948[];
extern int32_t r1h_g3E4764;
void *r1k_FieldStarsDraw(void);
void  sub_000150B0(void *spr, int frame);
void *r1d_TrackApplyA(void *dl, void *spr);
void  r1i_SeqPlayUpdate(void *spr);

/* 0x595D0: draw the star field and the three-item menu: the selected item uses the animated sprite, the others the plain one, then the frame and cursor. */
void *m1_FieldMenuDraw0595D0(void) {
    void *dl; int i;
    dl = r1k_FieldStarsDraw();
    sub_000150B0(m1_menuSprA3E49E4, 0);
    dl = r1d_TrackApplyA(dl, m1_menuSprA3E49E4);
    for (i = 0; i < 3; i++) {
        if (r1h_g3E4764 == i) {
            sub_000150B0(m1_menuSprB3E4948, i + 4);
            dl = r1d_TrackApplyA(dl, m1_menuSprB3E4948);
            r1i_SeqPlayUpdate(m1_menuSprB3E4948);
        } else {
            sub_000150B0(m1_menuSprA3E49E4, i + 1);
            dl = r1d_TrackApplyA(dl, m1_menuSprA3E49E4);
        }
    }
    sub_000150B0(m1_menuSprA3E49E4, 7);
    dl = r1d_TrackApplyA(dl, m1_menuSprA3E49E4);
    sub_000150B0(m1_menuSprA3E49E4, r1h_g3E4764 + 8);
    return r1d_TrackApplyA(dl, m1_menuSprA3E49E4);
}
