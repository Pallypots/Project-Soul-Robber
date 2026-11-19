/* Area m1, file 229: animation timing helpers (register inputs per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Clip229 { uint8_t unk00[0x10]; float len10; } M1Clip229;
typedef struct M1Anm229 { uint8_t unk00[0xDC]; float rateDC; } M1Anm229;
typedef struct M1Mdl229 { uint8_t unk00[0x14]; M1Anm229 *anim14; } M1Mdl229;
typedef struct M1Obj229 { uint8_t unk00[0x30]; M1Mdl229 *mdl30; } M1Obj229;
typedef struct M1Tm229 { uint8_t unk00[0x58]; float t58; uint8_t unk5C[4]; int32_t clip60; } M1Tm229;
extern float a50_frameSeconds;
M1Clip229 *sub_00083120(M1Mdl229 *m, int32_t clip);
int sub_001C7EE1(void);   /* rand */

/* 0x00172D20: pick a random 15/30/45/60 limit and set t58 to the largest whole number of animation steps
   (frameSeconds*rate/len) that fits under it (regargs: o=EAX t=ESI). */
__declspec(noinline) void m1_RandHold172D20(M1Obj229 *o, M1Tm229 *t)
{
    M1Mdl229 *m = o->mdl30;
    M1Anm229 *a = m->anim14;
    M1Clip229 *c = sub_00083120(m, t->clip60);
    float step = a50_frameSeconds * (a->rateDC / c->len10);
    float lim, x;
    if (sub_001C7EE1() % 2 < 1) {
        if (sub_001C7EE1() % 2 < 1)
            lim = 60.0f;
        else
            lim = 45.0f;
    } else if (sub_001C7EE1() % 2 < 1) {
        if (sub_001C7EE1() % 2 < 1)
            lim = 45.0f;
        else
            lim = 30.0f;
    } else {
        lim = 15.0f;
    }
    x = 0.0f;
    while (x + step <= lim)
        x += step;
    t->t58 = x;
}

/* 0x00172E00: as 0x172D20 with limits 2/3/4/5 (regargs: o=EAX t=ESI). */
__declspec(noinline) void m1_RandHold172E00(M1Obj229 *o, M1Tm229 *t)
{
    M1Mdl229 *m = o->mdl30;
    M1Anm229 *a = m->anim14;
    M1Clip229 *c = sub_00083120(m, t->clip60);
    float step = a50_frameSeconds * (a->rateDC / c->len10);
    float lim, x;
    if (sub_001C7EE1() % 2 < 1) {
        if (sub_001C7EE1() % 2 < 1)
            lim = 2.0f;
        else
            lim = 3.0f;
    } else if (sub_001C7EE1() % 2 < 1) {
        if (sub_001C7EE1() % 2 < 1)
            lim = 4.0f;
        else
            lim = 5.0f;
    } else {
        lim = 3.0f;
    }
    x = 0.0f;
    while (x + step <= lim)
        x += step;
    t->t58 = x;
}

typedef struct M1SndE229 { int32_t kind, id, snd; } M1SndE229;
typedef struct M1Cur229 { uint8_t unk00[8]; int32_t clip8; } M1Cur229;
typedef struct M1Act229 { uint8_t unk00[8]; int32_t kind8; uint8_t unk0C[4]; uint32_t flags10; uint8_t unk14[0x1C];
    M1Cur229 *mdl30; uint8_t unk34[8]; void *mdl3C; uint8_t unk40[0x14]; float f54; uint8_t unk58[8]; uint8_t pos60[0x10];
    uint8_t unk70[0x40]; float fB0; } M1Act229;
typedef struct M1Vo229 { uint8_t unk00[0x4C]; int32_t n4C, sub50; float f54; float t58; uint32_t flags5C; int32_t id60; float t64; int32_t h68;
    uint8_t unk6C[8]; uint8_t blk74[0x44]; int32_t nB8; } M1Vo229;
int32_t sub_000494D0(int32_t snd, void *pos, int32_t z);
void sub_00048250(int32_t h);

/* 0x00172B80: start (on != 0) or stop the looping voice for the (actor kind, clip id) pair from a 4-entry table;
   starting while one is playing hangs (regargs: o=EAX v=EBX). */
__declspec(noinline) void m1_VoiceLoop172B80(M1Act229 *o, M1Vo229 *v, int32_t on)
{
    M1SndE229 tab[5];
    M1SndE229 *e;
    int i;
    tab[0].snd = 0x1A5;
    tab[1].snd = 0x1A5;
    tab[2].kind = 4;
    tab[3].kind = 4;
    tab[0].kind = 10;
    tab[0].id = 8;
    tab[1].kind = 10;
    tab[1].id = 7;
    tab[2].id = 2;
    tab[2].snd = 0x18E;
    tab[3].id = 3;
    tab[3].snd = 0x186;
    tab[4].kind = -1;
    tab[4].id = -1;
    tab[4].snd = -1;
    if (on) {
        for (i = 0, e = tab; e->kind >= 0; e++, i++) {
            if (o->kind8 == e->kind && v->id60 == e->id) {
                if (v->h68 >= 0)
                    for (;;) ;
                v->h68 = sub_000494D0(tab[i].snd, o->pos60, 0);
                return;
            }
        }
        return;
    }
    if (v->h68 < 0)
        return;
    for (e = tab; e->kind >= 0; e++) {
        if (o->kind8 == e->kind && v->id60 == e->id) {
            sub_00048250(v->h68);
            v->h68 = -1;
            return;
        }
    }
}

void *sub_00083120b(M1Cur229 *m, int32_t clip);
void sub_000832D0(M1Cur229 *m, int32_t clip);
void aab_Model1D7F0(void *m, int32_t clip, int32_t z);
void sub_0001D4E0(M1Act229 *o);

/* 0x00172C90: switch o to clip (or restart it if already current), hang if the model did not take it, reset t64,
   nudge the model unless kind 15/1, and restart the looping voice (regargs: v=EAX o=ESI clip=EDI; calls 0x172B80
   with o=EAX v=EBX). */
__declspec(noinline) void m1_PlayClip172C90(M1Vo229 *v, M1Act229 *o, int32_t clip)
{
    m1_VoiceLoop172B80(o, v, 0);
    if (!sub_00083120b(o->mdl30, clip))
        return;
    if (v->id60 == clip) {
        sub_000832D0(o->mdl30, -1);
    } else {
        sub_000832D0(o->mdl30, clip);
        v->id60 = clip;
    }
    aab_Model1D7F0(o->mdl3C, clip, 0);
    if (o->mdl30->clip8 != v->id60)
        for (;;) ;
    v->t64 = 0.0f;
    if (o->kind8 != 15 && o->kind8 != 1)
        sub_0001D4E0(o);
    m1_VoiceLoop172B80(o, v, 1);
}

extern void *a80_ctx42C8E4;
void sub_0001EB80(M1Act229 *o);
void sub_0001E9B0(void *ctx, M1Act229 *o, int32_t a, int32_t b, int32_t c);
void sub_000EE6D0(M1Act229 *o, int32_t z);
float sub_00113200(M1Act229 *o, void *blk);
extern float a50_frameUnits;

/* 0x00173440: enter the hit state: flags |= 0x104, play clip 1 (8 for kind 9 with v flag 0x1000), hold 2.0,
   and set f54 from 0x113200 (calls 0x172C90 with v=EAX o=ESI clip=EDI). */
void m1_HitEnter173440(M1Act229 *o, M1Vo229 *v)
{
    int k;
    o->flags10 |= 0x104;
    sub_0001EB80(o);
    sub_0001E9B0(a80_ctx42C8E4, o, 0xE, 5, 0x11);
    k = 0;
    if (o->kind8 == 9 && (v->flags5C & 0x1000))
        k = 7;
    m1_PlayClip172C90(v, o, k + 1);
    v->nB8 = 0;
    v->flags5C |= 1;
    v->t58 = 2.0f;
    sub_000EE6D0(o, 0);
    o->f54 = 0.0f;
    o->f54 += sub_00113200(o, v->blk74);
    o->fB0 = 0.0f;
}

/* 0x00173570: enter the turn state: clear o flag 4 and v flag 1, play clip 3 (10 for kind 9 with v flag 0x1000),
   turn at +/-0.7 degrees per frame unit at random, and pick a hold time with 0x172E00 (calls 0x172C90 with v=EAX
   o=ESI clip=EDI, 0x172E00 with o=EAX v=ESI). */
void m1_TurnEnter173570(M1Act229 *o, M1Vo229 *v)
{
    int k;
    float d;
    o->flags10 &= ~4u;
    v->flags5C &= ~1u;
    k = 0;
    if (o->kind8 == 9 && (v->flags5C & 0x1000))
        k = 7;
    m1_PlayClip172C90(v, o, k + 3);
    v->nB8 = 1;
    d = a50_frameUnits * 0.0122173047f;
    if (sub_001C7EE1() % 2 < 1) {
        *(volatile float *)&v->f54 = d;
        m1_RandHold172E00((M1Obj229 *)o, (M1Tm229 *)v);
        return;
    }
    *(volatile float *)&v->f54 = 0.0f - d;
    m1_RandHold172E00((M1Obj229 *)o, (M1Tm229 *)v);
}

typedef void (*M1TnCb229)(M1Act229 *o, M1Vo229 *v);
extern M1TnCb229 m1_tnDone32B1B4;
int32_t sub_000833E0(M1Cur229 *m);

/* 0x00173B30: two-step wait: step 0 finishes through the 0x32B1B4 handler when the clip ends; step 1 counts three
   clip ends then plays clip 15 (calls 0x172C90 with v=EAX o=ESI clip=EDI). */
void m1_WaitStep173B30(M1Act229 *o, M1Vo229 *v)
{
    switch (v->sub50) {
    case 0:
        if (sub_000833E0(o->mdl30)) {
            v->n4C = 1;
            v->sub50 = 0;
            v->f54 = 0.0f;
            m1_tnDone32B1B4(o, v);
        }
        return;
    case 1:
        if (sub_000833E0(o->mdl30) && ++v->h68 >= 3) {
            m1_PlayClip172C90(v, o, 15);
            v->sub50 = 0;
        }
        return;
    }
}

