/* Area m2, file 23. Names inferred. */
#include <stdint.h>

typedef struct M2SndRec23 { uint8_t unk00[0x10]; int32_t kind10; int32_t base14; int32_t a18, b1C, c20, prio24; float vol28; } M2SndRec23;
typedef struct M2SndDef23 { uint8_t unk00[8]; int32_t i8, iC; M2SndRec23 *rec10; } M2SndDef23;
typedef struct M2SndEnt23 { uint8_t unk00[0x28]; int32_t bit28; } M2SndEnt23;
typedef struct M2SndSlot23 { void *obj0; uint8_t unk04[0x10]; int32_t h14; M2SndEnt23 *ent18; int32_t prio1C; float vol20; uint8_t unk24[4]; int32_t bit28; } M2SndSlot23;
extern int a5b_g3E6040;
extern int r1d_fxBank420DA8;
extern int r1_modeOverride;
extern M2SndSlot23 r1e_sndSlots3E5AC0[32];
uint8_t *r1e_ChildSlot(M2SndEnt23 *e, int a, int b);
int  r2b_TestBit(int bit);
int  sub_00048510(int kind);
int  sub_00049700(int id, int a, int b, int c, void *pos, int prio, float vol, int d);

/* 0x5BC90: start the sound of entity e (when its gate flag is set and sounds are not blocked): kind 12 uses the effect bank offset (none: give up; unset: bank 4 of kind 0), volume defaults to 280, priority from the override or the record; positioned at the child object when there is one. The voice is remembered in the first free sound slot. */
void m2_SndStart5BC90(M2SndEnt23 *e, M2SndDef23 *d) {
    M2SndRec23 *r = d->rec10;
    uint8_t *o;
    float vol;
    int kind, id, prio, h, i;
    M2SndSlot23 *s;
    if (e->bit28 != -1 && r2b_TestBit(e->bit28) == 0) return;
    if (a5b_g3E6040 != 0) return;
    o = r1e_ChildSlot(e, d->i8, d->iC);
    if (r->vol28 > 0.0f) vol = r->vol28;
    else vol = 280.0f;
    kind = r->kind10;
    if (kind == 0xC) {
        if (r1d_fxBank420DA8 == -1) { int volatile four = 4; kind = 0; id = four; }
        else {
            if (r1d_fxBank420DA8 == 0) return;
            id = r->base14 + r1d_fxBank420DA8 - 1;
        }
    } else id = r->base14;
    prio = r1_modeOverride;
    if (o != 0) {
        if (prio == -1) prio = r->prio24;
        h = sub_00049700(sub_00048510(kind) + id, r->a18, r->b1C, r->c20, o + 0x70, prio, vol, 1);
        if (h == -1) return;
        for (i = 0, s = r1e_sndSlots3E5AC0; i < 32; i++, s++) {
            if (s->h14 == -1) {
                s->obj0 = o; s->ent18 = e; s->h14 = h; s->prio1C = r->prio24; s->vol20 = vol; s->bit28 = e->bit28;
                return;
            }
        }
    } else {
        if (prio == -1) prio = r->prio24;
        h = sub_00049700(sub_00048510(kind) + id, r->a18, r->b1C, r->c20, r, prio, vol, 1);
        if (h == -1) return;
        for (i = 0, s = r1e_sndSlots3E5AC0; i < 32; i++, s++) {
            if (s->h14 == -1) {
                s->obj0 = 0; s->h14 = h; s->ent18 = e; s->prio1C = r->prio24; s->vol20 = vol; s->bit28 = e->bit28;
                return;
            }
        }
    }
}

#include <math.h>
typedef struct M2PRec23 { uint8_t unk00[0x14]; uint8_t flags14; uint8_t unk15[0x27]; uint8_t b3C, b3D, b3E, b3F; uint8_t unk40[0xC]; } M2PRec23;
extern M2PRec23 m2_rec42CA20[];
void r4e_MatIdentity(float *m);
void rbj_MatRotX(float *d, const float *s, float a);
void rbj_MatRotY(float *d, const float *s, float a);
void rbj_MatRotZ(float *d, const float *s, float a);
void rbj_MatMul(float *d, const float *a, const float *b);
void rbi_MatCopy(float *d, const float *s);
void rbi_MatLoad385D0(float *d, const float *s);
void rbj_VecTransform(float *d, const float *m, const float *v);
void r4c_VecAdd(float *d, const float *a, const float *b);
void a3c_VecCopy(float *d, const float *s);

/* 0x38650: build a pose matrix from record idx's four packed bytes (128 = centre): unless flag 1, two of them give rotations (scaled by s5, flag 8 flips the first, wrapped to -pi..pi); unless flag 2, two give an offset (scaled by s4; record flag 4 picks y, else -z). Flag 0x10 swaps which bytes are used. The rotation is applied on top of base; flag 4 levels the offset frame first. Result in out (translation = base position + offset). */
void m2_PoseFromBytes38650(float *out, float *base, int idx, float s4, float s5, uint8_t fl) {
    float r[3], a, b, c, x;
    float t[4], m[16], n[16];
    M2PRec23 *p = &m2_rec42CA20[idx];
    r[0] = 0.0f; r[1] = 0.0f; r[2] = 0.0f;
    if (fl & 0x10) { c = (float)p->b3C; a = (float)p->b3E; b = (float)p->b3F; x = (float)p->b3D; }
    else { a = (float)p->b3C; b = (float)p->b3D; c = (float)p->b3E; x = (float)p->b3F; }
    if (!(fl & 1)) {
        float xs = (x - 127.0f) * s5;
        float volatile nk = -0.017453289f;
        if (fl & 8) r[0] = (0.0f - xs) * nk;
        else r[0] = xs * nk;
        r[1] = (c - 127.0f) * s5 * 0.017453289f;
        r[0] = (float)(fmod(r[0] + 3.1415920f, 6.283184051513672) - 3.141592025756836);
        r[1] = (float)(fmod(r[1] + 3.1415920f, 6.283184051513672) - 3.141592025756836);
        r[2] = (float)(fmod(3.141592025756836, 6.283184051513672) - 3.141592025756836);
    }
    t[3] = 0.0f; t[2] = 0.0f; t[1] = 0.0f; t[0] = 0.0f;
    if (!(fl & 2)) {
        if (p->flags14 & 4) t[1] = (b - 127.0f) * s4;
        else t[2] = 0.0f - (b - 127.0f) * s4;
        t[0] = (a - 127.0f) * s4;
    }
    r4e_MatIdentity(m);
    rbj_MatRotX(m, m, r[0]);
    rbj_MatMul(m, base, m);
    rbj_MatRotY(m, m, r[1]);
    rbj_MatRotZ(m, m, r[2]);
    m[14] = 0.0f; m[13] = 0.0f; m[12] = 0.0f;
    rbi_MatCopy(n, m);
    if (fl & 4) {
        n[9] = 0.0f; n[6] = 0.0f; n[4] = 0.0f; n[5] = 1.0f;
        rbi_MatLoad385D0(n, n);
    }
    rbj_VecTransform(t, n, t);
    r4c_VecAdd(t, base + 12, t);
    rbi_MatCopy(out, m);
    a3c_VecCopy(out + 12, t);
    out[15] = 1.0f;
}
