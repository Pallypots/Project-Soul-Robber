/* Area m1, file 224: register-input helpers (docs/verification.md policy). Names inferred. */
#include <stdint.h>

typedef struct M1Fx224 { uint8_t unk00[0x20]; float f20; uint8_t unk24[0xC]; float f30; } M1Fx224;
typedef struct M1Ob224 { uint8_t unk00[0x74]; uint32_t *fx74; } M1Ob224;
typedef struct M1Nd224 { uint8_t unk00[0x374]; float f374; } M1Nd224;
typedef struct M1Mdl224 { uint8_t unk00[0xC4]; M1Nd224 *ndC4; } M1Mdl224;
typedef struct M1Pl224 { uint8_t unk00[0x20]; M1Mdl224 *mdl20; } M1Pl224;
extern M1Pl224 *g_playerObj;
int sub_001C7EE1(void);   /* rand */

/* 0x00167D00: jitter the effect height +0x20: when flag bit 1 is set, the player's node height minus 4.5 minus
   rand()%6; otherwise the effect's own +0x30 plus 10 minus rand()%11 (regargs: o=EAX). */
void m1_FxJitter167D00(M1Ob224 *o)
{
    M1Fx224 *f = (M1Fx224 *)o->fx74;
    float v;
    if (*o->fx74 & 2) {
        v = g_playerObj->mdl20->ndC4->f374 - 4.5f;
        f->f20 = v - (float)(sub_001C7EE1() % 6);
    } else {
        v = f->f30 + 10.0f;
        f->f20 = v - (float)(sub_001C7EE1() % 11);
    }
}

typedef struct M1Ka224 { uint8_t unk00[8]; int32_t kind8; } M1Ka224;
typedef struct M1Fl224 { uint8_t unk00[0x5C]; uint32_t flags5C; } M1Fl224;

/* 0x00172400: for mode k (0..11, hang otherwise) set b's +0x5C bit 0x1000 when a's kind matches:
   k 0: kinds 1/3; k 2: kinds 3/9/0x15/0x16; k 3 and 5: kind 9 (regargs: k=EAX a=ECX b=EDX). */
void m1_ModeKindFlag172400(int k, M1Ka224 *a, M1Fl224 *b)
{
    volatile int kk = k;
    if (kk < 0 || kk >= 12) for (;;) ;
    switch (kk) {
    case 0:
        switch (a->kind8) { case 1: case 3: b->flags5C |= 0x1000; break; }
        break;
    case 2:
        switch (a->kind8) {
        case 3: case 9: case 0x15: case 0x16: b->flags5C |= 0x1000; break;
        }
        break;
    case 3: case 5:
        if (a->kind8 == 9) b->flags5C |= 0x1000;
        break;
    }
}
