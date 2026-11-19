/* Area m1, file 237: event step helpers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1St237 { uint32_t flags0; int32_t n4; } M1St237;
int32_t sub_000D9A70(int32_t bit);
void sub_000A4410(int32_t id, int32_t on);
void sub_000A2D40(int32_t id, int32_t f);
void sub_000A2CC0(int32_t id, uint32_t f);
void sub_000A3690(int32_t id, int32_t z);
void sub_000A3480(int32_t id, int32_t a, int32_t b);
void sub_000A43C0(int32_t id, int32_t k);

/* 0x000BA6F0: event step handler: 0 resets, 1 arms (flag 1, phase 10), 3 resets and returns 0; in phase 10 it swaps
   objects id/id+1 one way or the other depending on bit `bit` and moves to phase 20; phase 20 resets and returns 0
   (regargs: step=EAX st=EDI id=ESI). */
int m1_EvStep0BA6F0(int step, M1St237 *st, int id, int bit)
{
    if (step == 0) {
        st->flags0 = 0;
        st->n4 = 0;
        return 1;
    }
    if (step == 1) {
        st->flags0 |= 1;
        st->n4 = 10;
        return 1;
    }
    if (step != 3) {
        if (st->n4 == 10) {
            if (sub_000D9A70(bit)) {
                sub_000A4410(id, 0);
                sub_000A4410(id + 1, 1);
                sub_000A2D40(id, 0x20);
                sub_000A2CC0(id, 0x10000000);
                st->n4 = 0x14;
                return 1;
            }
            sub_000A4410(id, 1);
            sub_000A4410(id + 1, 0);
            sub_000A3690(id, 0);
            sub_000A3480(id, 0, 1);
            sub_000A43C0(id, 2);
            st->n4 = 0x14;
            return 1;
        }
        if (st->n4 != 0x14)
            return 1;
    }
    st->flags0 = 0;
    st->n4 = 0;
    return 0;
}

typedef struct M1St237b { uint32_t flags0; int32_t n4; int32_t n8; } M1St237b;
void sub_000A42F0(int32_t id, int32_t on);
int32_t sub_000A4370(int32_t id);

/* 0x000B8800: event step handler: 0 resets, 1 arms (phase 10), 3 releases id and resets (returns 0); phase 0 shows
   id unless bit 0x63, phase 10 grabs id, phase 11 releases it when 0xA4370 says done (phase 20), phase 20 resets
   (returns 0) (regargs: step=EAX st=ESI id=EDI). */
int m1_EvStep0B8800(int step, M1St237b *st, int id)
{
    if (step == 0) {
        st->flags0 = 0;
        st->n4 = 0;
        return 1;
    }
    if (step == 1) {
        st->flags0 |= 1;
        st->n8 = 0;
        st->n4 = 10;
        return 1;
    }
    if (step == 3) {
        sub_000A42F0(id, 0);
        goto reset;
    }
    switch (st->n4) {
    case 0:
        if (sub_000D9A70(0x63)) {
            sub_000A4410(id, 0);
            return 1;
        }
        sub_000A4410(id, 1);
        return 1;
    case 10:
        sub_000A42F0(id, 1);
        st->n4++;
        return 1;
    case 11:
        if (sub_000A4370(id)) {
            sub_000A42F0(id, 0);
            st->n4 = 0x14;
        }
        return 1;
    case 20:
    reset:
        st->flags0 = 0;
        st->n4 = 0;
        return 0;
    }
    return 1;
}

typedef struct M1Pl237 { uint8_t unk00[0xEC]; uint8_t flagsEC; uint8_t unkED[0x63]; uint32_t flags150;
    uint8_t unk154[0x84]; int32_t k1D8; uint8_t unk1DC[0x5F0 - 0x1DC]; int32_t snd5F0; uint8_t unk5F4[0xC];
    int32_t h600; } M1Pl237;
extern uint32_t r6e_g41CD18, g_ac0_42CA38;
extern int32_t g_42C8EC;
extern uint8_t r6e_obj420EC0[];
void sub_00048250(int32_t h);
int32_t Player_D00A0(M1Pl237 *o, int32_t h);
void sub_000BC5D0(void);
void m1_SceneFade0D4C10(int32_t rig);
void sub_000D45B0b(int32_t rig, int32_t a, int32_t b, float c);
void sub_000BC5F0(void *p);
void sub_000CCC50(M1Pl237 *o, int32_t k);
void sub_000D5620(int32_t z);
int  sub_000CD300(M1Pl237 *p);   /* regargs: p=EAX */
void abc_SetState(M1Pl237 *o, int32_t st);

/* 0x000CD750: if the current mode bit is enabled, reset the player like 0xC03E0, set flags 0x101 and enter state
   0x13 + 0xCD300's pick (stored at +0x1D8); returns 1, or -1 when disabled (calls 0xCD300 with p=EAX). */
int m1_PlayerRestart0CD750(M1Pl237 *o)
{
    int k;
    if (!(g_ac0_42CA38 & r6e_g41CD18))
        return -1;
    if (o->flagsEC & 0x40) {
        if (o->snd5F0 >= 0) {
            sub_00048250(o->snd5F0);
            o->snd5F0 = -1;
        }
        if (o->h600)
            o->h600 = Player_D00A0(o, o->h600);
    }
    sub_000BC5D0();
    m1_SceneFade0D4C10(g_42C8EC);
    sub_000D45B0b(g_42C8EC, 0, 0, -1.0f);
    o->flags150 &= ~0x10000000u;
    sub_000BC5F0(r6e_obj420EC0);
    sub_000CCC50(o, 0);
    sub_000CCC50(o, 1);
    sub_000D5620(0);
    o->flags150 |= 0x101;
    k = sub_000CD300(o);
    o->k1D8 = k;
    abc_SetState(o, k + 0x13);
    return 1;
}
