/* Area m1, file 141: small helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Pk141 {
    uint8_t unk00[4]; int32_t live04; int32_t mode08; uint32_t flags0C; uint8_t unk10[0x60 - 0x10];
    float v60[4]; uint8_t unk70[0x14C - 0x70]; int32_t i14C;
} M1Pk141;
typedef struct M1Sp141 {
    uint32_t flags00; uint8_t unk04[0xC]; int32_t kind10; float v14[4]; uint8_t unk24[0xE8 - 0x24]; M1Pk141 *pk0E8;
} M1Sp141;
extern M1Sp141 m1_slots41D020[20];
extern M1Pk141 *m1_rbFData41E298;
extern uint8_t *m1_rbEData41CEB4;
extern void *m1_scene42C8E4;
void sub_00022380(M1Pk141 *p, void *src, void *scene);
void sub_0001E9B0(void *scene, M1Pk141 *p, int k, int a, int b);
void sub_000F5D40(float *d, const void *s);

static M1Pk141 *m1_PkFree141(void) {
    M1Pk141 *p = m1_rbFData41E298; int i;
    for (i = 0; i < 20; i++, p++)
        if (!(p->flags0C & 1)) return p;
    return 0;
}

/* 0xC7460: give every armed spawner a free pickup object. */
void m1_PkSpawn0C7460(void) {
    void *sc = m1_scene42C8E4; M1Sp141 *s; int i;
    for (i = 0; i < 20; i++) {
        s = &m1_slots41D020[i];
        if ((int32_t)s->flags00 >= 0) continue;
        s->pk0E8 = m1_PkFree141();
        if (s->pk0E8 == 0) continue;
        sub_00022380(s->pk0E8, m1_rbEData41CEB4 + (s->kind10 / 8) * 0x150, sc);
        sub_0001E9B0(sc, s->pk0E8, s->pk0E8->i14C, 5, 0x11);
        s->pk0E8->flags0C |= 1;
        s->pk0E8->live04 = 1;
        s->pk0E8->mode08 = 3;
        s->flags00 = (s->flags00 & 0x7FFFFFFE) | 1;
        sub_000F5D40(s->pk0E8->v60, s->v14);
    }
}


typedef struct M1Lt141 { uint8_t unk00[0x8C]; int32_t type8C; uint8_t unk90[0xCC - 0x90]; float c[4]; int32_t w; } M1Lt141;
typedef struct M1Ln141 {
    uint8_t unk00[0x20]; M1Lt141 *obj20; uint8_t unk24[0x3C - 0x24]; struct M1Ln141 *next3C;
    uint8_t unk40[0x90 - 0x40]; float c90; float c94; float c98; int32_t w9C;
} M1Ln141;
void sub_001B3160(M1Lt141 *o);

/* 0xEE980: scale the colour of every light in a list by s. */
void m1_LightTint0EE980(M1Ln141 *n, const float *s) {
    M1Lt141 *o;
    if (n == 0) return;
    do {
        o = n->obj20;
        if (o != 0) {
            switch (o->type8C) {
            case 9:
                o->c[1] = n->c90 * s[0]; o->c[2] = n->c94 * s[1]; o->c[3] = n->c98 * s[2]; o->w = n->w9C;
                break;
            case 1:
                o->c[0] = n->c90 * s[0]; o->c[1] = n->c94 * s[1]; o->c[2] = n->c98 * s[2];
                *(int32_t *)&o->c[3] = n->w9C;
                sub_001B3160(o);
                break;
            }
        }
        n = n->next3C;
    } while (n != 0);
}

