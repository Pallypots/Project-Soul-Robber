/* Area m1, file 233: actor state helpers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Md233 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[8]; void *anim14; } M1Md233;
typedef struct M1O233 { uint8_t unk00[0xC]; uint32_t flags0C; uint8_t unk10[0x20]; M1Md233 *mdl30; } M1O233;
typedef struct M1S233 { uint8_t unk00[0xC8]; void *partC8; uint8_t unkCC[4]; int32_t nD0; uint8_t unkD4[0xB0];
    float f184; } M1S233;
void sub_000F3B30(void *o, int32_t k);
void sub_0001D610(M1O233 *o);
void sub_0001EEC0(M1O233 *o, float k);
uint32_t sub_001AEE90(void *a, int32_t z);
void *sub_0001D960(M1O233 *o, int32_t slot);
void sub_000F3D10(M1O233 *o, void *fx, int32_t k);
void sub_0010FD50(M1O233 *o);   /* regargs: o=EAX */

/* 0x00110540: hit reaction: detach (flag 0x10000), f184 = 3.5, 0x1EEC0 3.5; on clip 0x13 with bit 2 set mode 4 on
   o and its part, then fall back to 0x10FD50 (tail call, o=EAX) unless nD0 == 1, which plays effect slot 5. */
void m1_HitReact110540(M1O233 *o, M1S233 *s)
{
    if (o->flags0C & 0x10000) {
        sub_000F3B30(o, 1);
        sub_0001D610(o);
        if (s->nD0 != 1)
            sub_000F3B30(s->partC8, 1);
    }
    s->f184 = 3.5f;
    sub_0001EEC0(o, 3.5f);
    if (o->mdl30->kind8 == 0x13 && (sub_001AEE90(o->mdl30->anim14, 0) & 2)) {
        sub_000F3B30(o, 4);
        sub_000F3B30(s->partC8, 4);
        if (s->nD0 != 1) {
            sub_0010FD50(o);
            return;
        }
        sub_000F3D10(o, sub_0001D960(o, 5), 10);
    }
}

typedef struct M1Fx233 { uint8_t unk00[0x6C]; int32_t k6C; } M1Fx233;
typedef struct M1O233b { uint8_t unk00[8]; int32_t kind8; uint32_t flags0C; uint8_t unk10[0x20]; M1Md233 *mdl30; } M1O233b;
M1Fx233 *sub_0001D960b(M1O233b *o, int32_t slot);
void sub_000F3D10b(M1O233b *o, M1Fx233 *fx, int32_t k);
void sub_000F3DA0(M1O233b *o, int32_t a, int32_t b, int32_t c);
void sub_0001D610b(M1O233b *o);
void sub_0010FD50b(M1O233b *o);   /* 0x10FD50 regargs: o=EAX */

/* 0x0010FF80: hit reaction variant: detach (flag 0x10000); on clip 0x13 with bit 2 call 0xF3DA0 20; on clip 0x14 with
   bit 2 set mode 4 on o and its part, then kind 15 plays effect slot 5 mode 6 (unless already 6), other kinds fall
   back to 0x10FD50 (tail call, o=EAX). */
void m1_HitReact10FF80(M1O233b *o, M1S233 *s)
{
    M1Fx233 *e;
    if (o->flags0C & 0x10000) {
        sub_000F3B30(o, 1);
        sub_000F3B30(s->partC8, 1);
        sub_0001D610b(o);
    }
    switch (o->mdl30->kind8) {
    case 0x13:
        if (sub_001AEE90(o->mdl30->anim14, 0) & 2)
            sub_000F3DA0(o, 0x14, 0, 0);
        return;
    case 0x14:
        if (!(sub_001AEE90(o->mdl30->anim14, 0) & 2))
            return;
        sub_000F3B30(o, 4);
        sub_000F3B30(s->partC8, 4);
        if (o->kind8 == 15) {
            e = sub_0001D960b(o, 5);
            if (e->k6C != 6)
                sub_000F3D10b(o, e, 6);
            return;
        }
        sub_0010FD50b(o);
        return;
    }
}

typedef struct M1WE233 { uint32_t flags0; uint8_t unk04[0xC]; uint32_t m10; uint8_t unk14[0x14]; void *slot28[3]; } M1WE233;
typedef struct M1WS233 { uint8_t unk00[0x278]; M1WE233 *ext278; } M1WS233;
typedef struct M1WO233 { uint8_t unk00[0x50]; uint8_t v50[0x10]; uint8_t pos60[4]; float y64; } M1WO233;
extern M1WO233 *g_playerObj;
void *sub_000ED630(int32_t a, int32_t b, int32_t c, void *v, M1WO233 *o);
uint32_t r4h_FxWaveSpawn(void *h, M1WO233 *o, int32_t fl, uint32_t m);
void sub_00049700(int32_t snd, int32_t r, int32_t g, int32_t b, void *pos, int32_t a, float k, int32_t z);

/* 0x00177AC0: spawn a wave effect into the first free of three slots (flag 1 if e flag 4, flag 2 if o is more
   than 40 below the player), merge its mask into m10 and play sound 0x209 (regargs: s=EAX o=ECX). */
void m1_WaveFx177AC0(M1WS233 *s, M1WO233 *o)
{
    M1WE233 *e = s->ext278;
    float dy = o->y64 - g_playerObj->y64;
    int fl = 0;
    int i;
    void *h;
    for (i = 0; i < 3; i++)
        if (!e->slot28[i])
            break;
    if (i == 3)
        return;
    h = sub_000ED630(5, 0x13, 0, o->v50, o);
    e->slot28[i] = h;
    if (!h)
        return;
    if (e->flags0 & 4)
        fl = 1;
    if (-40.0f > dy)
        fl |= 2;
    e->m10 |= r4h_FxWaveSpawn(h, o, fl, e->m10);
    sub_00049700(0x209, 0x80, 0x80, 0x80, o->pos60, 1, 100.0f, 0);
}

typedef struct M1VE233 { uint32_t flags0; uint8_t unk04[0x20]; void *slot24[3]; } M1VE233;
typedef struct M1VS233 { uint8_t unk00[0x278]; M1VE233 *ext278; } M1VS233;
void sub_0018D400(void *h, M1WO233 *o, int32_t fl);

/* 0x001757C0: as 0x177AC0 for the slots at +0x24, effect 5/15 via 0x18D400 and sound 0x206 (regargs: s=EAX o=ECX). */
void m1_SplashFx1757C0(M1VS233 *s, M1WO233 *o)
{
    M1VE233 *e = s->ext278;
    float dy = o->y64 - g_playerObj->y64;
    int fl = 0;
    int i;
    void *h;
    for (i = 0; i < 3; i++)
        if (!e->slot24[i])
            break;
    if (i == 3)
        return;
    h = sub_000ED630(5, 0xF, 0, o->v50, o);
    e->slot24[i] = h;
    if (!h)
        return;
    if (e->flags0 & 4)
        fl = 1;
    if (-40.0f > dy)
        fl |= 2;
    sub_0018D400(h, o, fl);
    sub_00049700(0x206, 0x80, 0x80, 0x80, o->pos60, 1, 100.0f, 0);
}

typedef struct M1Pl233 { uint8_t unk00[0xEC]; uint8_t flagsEC; uint8_t unkED[0x63]; uint32_t flags150;
    uint8_t unk154[0x5F0 - 0x154]; int32_t snd5F0; uint8_t unk5F4[0xC]; int32_t h600; } M1Pl233;
extern int32_t g_42C8EC;
extern uint8_t r6e_obj420EC0[];
void sub_00048250(int32_t h);
int32_t Player_D00A0(M1Pl233 *o, int32_t h);
void sub_000BC5D0(void);
void m1_SceneFade0D4C10(int32_t rig);
void sub_000D45B0b(int32_t rig, int32_t a, int32_t b, float c);
void sub_000BC5F0(void *p);
void sub_000CCC50(M1Pl233 *o, int32_t k);
int32_t PlayerObj_IsActive(M1Pl233 *o);
void abc_SetState(M1Pl233 *o, int32_t st);
void abc_SetStateB(M1Pl233 *o, int32_t st);   /* same function (alias stops cl merging calls) */

/* 0x000C03E0: player reset: if flag 0x40 at +0xEC stop its sound and release h600; reset the scene, clear flag
   0x10000000, clear both 0xCCC50 slots, then state 1 if still active else 6 (regargs: o=ESI). */
void m1_PlayerReset0C03E0(M1Pl233 *o)
{
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
    if (PlayerObj_IsActive(o) > 0) {
        abc_SetState(o, 1);
        return;
    }
    abc_SetStateB(o, 6);
}

typedef struct M1BO233 { uint8_t unk00[0x60]; uint8_t pos60[0xC8]; uint8_t flags128; } M1BO233;
typedef struct M1BS233 { uint8_t unk00[0x104]; uint8_t v104[0x10]; } M1BS233;
int  r3_CheckConds135730(int table, M1BO233 *obj, M1BS233 *act);   /* regargs: table=EAX obj=EBX act=EDI */
void r3_SetStateB(M1BO233 *obj, M1BS233 *act, int state);          /* regargs: obj=ESI act=EDI state=stack */
void r3_SetStateB2(M1BO233 *obj, M1BS233 *act, int state);         /* same function (alias stops cl merging calls) */
float sub_001B2770(const void *a, const void *b);

/* 0x00136710: pick the next state: tables 1/2/3 -> 10/11/9, within 20 of the target -> 6, else 9 when flag 1 at
   +0x128 (calls 0x135730 with table=EAX obj=EBX act=EDI, 0x135A70 with obj=ESI act=EDI). */
void m1_PickState136710(M1BO233 *o, M1BS233 *s)
{
    if (r3_CheckConds135730(1, o, s)) {
        r3_SetStateB(o, s, 10);
        return;
    }
    if (r3_CheckConds135730(2, o, s)) {
        r3_SetStateB(o, s, 11);
        return;
    }
    if (r3_CheckConds135730(3, o, s)) {
        r3_SetStateB(o, s, 9);
        return;
    }
    if (sub_001B2770(o->pos60, s->v104) <= 20.0f) {
        r3_SetStateB(o, s, 6);
        return;
    }
    if (o->flags128 & 1)
        r3_SetStateB2(o, s, 9);
}
