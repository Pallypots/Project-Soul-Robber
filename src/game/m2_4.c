/* Area m2, file 4. Names inferred. */
#include <stdint.h>

typedef struct M2Obj4 { uint32_t flags0; int32_t id4; uint8_t unk08[4]; float timerC; uint8_t unk10[0x30]; int32_t state40; } M2Obj4;
extern M2Obj4 m2_obj424C40, m2_obj424EA0, m2_obj425100;
extern int r1e_g413170;
void sub_000A41D0(M2Obj4 *o, int v);
int  r2b_TestBit(int bit);

/* 0x92EA0: step one of three timed objects: state 0 counts its timer down and then goes to state 10 (state 1 for object 0x73 in area 1); state 1 waits until the object's flag (0x2C5..0x2C8) is clear and then goes to state 10; state 10 releases it and sets flag 0x80. */
void m2_ObjStep92EA0(M2Obj4 *o) {
    switch (o->state40) {
    case 0:
        o->timerC -= 1.0f;
        if (o->timerC <= 0.0f) {
            o->state40 = 10;
            if (o->id4 == 0x73 && r1e_g413170 == 1) o->state40 = 1;
        }
        break;
    case 1: {
        int bit;
        if (o == &m2_obj424C40) bit = 0x2C5;
        else if (o == &m2_obj424EA0) bit = 0x2C6;
        else bit = (o != &m2_obj425100) + 0x2C7;
        if (r2b_TestBit(bit) == 0) o->state40 = 10;
        break;
    }
    case 10:
        sub_000A41D0(o, -1);
        o->flags0 |= 0x80;
        break;
    }
}

typedef struct M2Tgt4 { uint8_t unk00[0xE8]; uint32_t phaseE8; uint32_t doneEC; } M2Tgt4;
typedef struct M2Ent4 { uint32_t flags0; uint8_t unk04[0x64]; M2Tgt4 *tgt68; uint8_t unk6C[4]; uint32_t num70; uint32_t div74; uint8_t unk78[0xB4]; } M2Ent4;
typedef struct M2Hdr4 { int32_t busy0; uint32_t flags4; } M2Hdr4;
typedef struct M2Grp4 { uint8_t unk00[0x10]; M2Hdr4 hdr10; uint8_t unk18[0xC8]; uint32_t nE0; uint8_t unkE4[0xD8]; M2Ent4 ents[1]; } M2Grp4;

/* 0x342C0: when the group is idle (header bit 0 and busy word clear), give every flagged (0x20000) entry's target a start phase once: 1 unless num is 0 and div non-zero (then num/div), and mark it done. Always 0. */
int m2_GrpPhase342C0(M2Grp4 *g) {
    M2Hdr4 *h = &g->hdr10;
    uint32_t i;
    if (h != 0 && (h->flags4 & 1)) return 0;
    if (h->busy0 != 0) return 0;
    for (i = 0; i < g->nE0; i++) {
        M2Ent4 *e = &g->ents[i];
        if (!(e->flags0 & 0x20000)) continue;
        if (e->tgt68->phaseE8 != 0 && e->tgt68->doneEC != 0) continue;
        if (e->num70 == 0 && e->div74 != 0) e->tgt68->phaseE8 = e->num70 / e->div74;
        else e->tgt68->phaseE8 = 1;
        e->tgt68->doneEC = 1;
    }
    return 0;
}
