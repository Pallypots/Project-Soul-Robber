/* Area m1, file 230: effect-slot helpers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>
#include <xmmintrin.h>

typedef struct M1Ent230 { uint8_t unk00[0xC]; int32_t onC; uint8_t unk10[0x54 - 0x10]; } M1Ent230;
extern M1Ent230 m1_ents41C7C0[16];
void sub_0001D4B0(void *o, int32_t n);
void sub_0001D470(void *o, int32_t n);
void sub_0001D470b(void *o, int32_t n);   /* same function as 0x1D470 (alias keeps cl from merging the branches) */
int  m1_FindEntryCDAB0(void *m, int key);   /* regargs: m=EAX key=ESI */

/* 0x000CE590: clear model flags 0..10, set 8/1/10/7 (off) or 9/3/5 (on), and clear the active bit of the
   key-0 and key-1 entries (calls 0xCDAB0 with m=EAX key=ESI). */
void m1_FlagSet0CE590(void *o, int32_t on)
{
    int i;
    sub_0001D4B0(o, 8);
    sub_0001D4B0(o, 9);
    sub_0001D4B0(o, 10);
    sub_0001D4B0(o, 0);
    sub_0001D4B0(o, 1);
    sub_0001D4B0(o, 2);
    sub_0001D4B0(o, 3);
    sub_0001D4B0(o, 4);
    sub_0001D4B0(o, 5);
    sub_0001D4B0(o, 6);
    sub_0001D4B0(o, 7);
    if (!on) {
        sub_0001D470(o, 8);
        sub_0001D470(o, 1);
        sub_0001D470(o, 10);
        sub_0001D470(o, 7);
    } else {
        sub_0001D470b(o, 9);
        sub_0001D470b(o, 3);
        sub_0001D470b(o, 5);
    }
    i = m1_FindEntryCDAB0(o, 0);
    if (i < 0)
        return;
    m1_ents41C7C0[i].onC = 0;
    i = m1_FindEntryCDAB0(o, 1);
    if (i < 0)
        return;
    m1_ents41C7C0[i].onC = 0;
}

typedef struct M1EntR230 { uint32_t f00, f04, f08, f0C, f10; float s14, s18, f1C, f20, f24; int32_t f28, f2C;
    int32_t f30[8]; void *mdl50; } M1EntR230;
extern M1EntR230 m1_ents41C7C0U[16];

#define M1_ENT_RESET(e) do { \
    (e)->s14 = 1.0f; (e)->s18 = 1.0f; \
    (e)->f00 = 0; (e)->f04 = 0; (e)->f08 = 0; (e)->f0C = 0; (e)->f10 = 0; \
    (e)->f1C = 0.0f; (e)->f20 = 0.0f; (e)->f24 = 0.0f; \
    (e)->f28 = 0; (e)->f2C = 0; (e)->mdl50 = 0; \
    (e)->f30[0] = 0; (e)->f30[1] = 0; (e)->f30[2] = 0; (e)->f30[3] = 0; \
    (e)->f30[4] = 0; (e)->f30[5] = 0; (e)->f30[6] = 0; (e)->f30[7] = 0; } while (0)

/* 0x000CE9F0: free the model's key-0 and key-1 entries (stops at the first one missing)
   (calls 0xCDAB0 with m=EAX key=ESI). */
void m1_EntsFree0CE9F0(void *m)
{
    M1EntR230 *e;
    int i = m1_FindEntryCDAB0(m, 0);
    if (i < 0)
        return;
    e = &m1_ents41C7C0U[i];
    M1_ENT_RESET(e);
    i = m1_FindEntryCDAB0(m, 1);
    if (i < 0)
        return;
    e = &m1_ents41C7C0U[i];
    M1_ENT_RESET(e);
}

typedef struct M1Fx230 { uint8_t unk00[0xC]; int32_t state0C; uint8_t unk10[0x14]; float t24; uint8_t unk28[0x28];
    void *ent50; } M1Fx230;
extern float a50_frameUnits;
int32_t sub_00172950(void *e);

/* 0x000CE680: three-step toggle of entity flags 8/9/10 with a 100-unit hold and an 8-unit cooldown
   (regargs: f=ESI). */
void m1_FlagCycle0CE680(M1Fx230 *f)
{
    void *e = f->ent50;
    __m128 t;
    switch (f->state0C) {
    case 0:
        if (!sub_00172950(e)) {
            sub_0001D470(e, 8);
            sub_0001D4B0(e, 9);
        } else {
            sub_0001D4B0(e, 10);
        }
        break;
    case 1:
        t = _mm_add_ss(_mm_load_ss(&f->t24), _mm_load_ss(&a50_frameUnits));
        _mm_store_ss(&f->t24, t);
        if (!_mm_comige_ss(t, _mm_set_ss(100.0f)))
            return;
        if (!sub_00172950(e)) {
            sub_0001D4B0(e, 8);
            sub_0001D470(e, 9);
        } else {
            sub_0001D470(e, 10);
        }
        break;
    case 2:
        t = _mm_add_ss(_mm_load_ss(&f->t24), _mm_load_ss(&a50_frameUnits));
        _mm_store_ss(&f->t24, t);
        if (_mm_comige_ss(t, _mm_set_ss(8.0f)))
            f->state0C = 0;
    default:
        return;
    }
    f->t24 = 0.0f;
    f->state0C++;
}

#include <math.h>
void sub_0010FD50(void *o);   /* regargs: o=EAX */

/* 0x00110090: forwards to 0x10FD50 (regargs: o=EAX, passed through). */
void m1_Fwd110090(void *o)
{
    sub_0010FD50(o);
}

/* 0x001A3F00: fmodf through the CRT x87 helper. */
float m1_Fmodf1A3F00(float a, float b)
{
    return (float)fmod(a, b);
}

typedef struct M1Ext230 { uint32_t flags0; uint8_t unk04[0x14]; float t18; uint8_t unk1C[8]; int32_t pose24; } M1Ext230;
typedef struct M1Obj230 { uint8_t unk00[0x60]; uint8_t pos60[0x10]; } M1Obj230;
typedef struct M1Act230 { uint8_t unk00[0x4C]; uint32_t flags4C; uint8_t unk50[8]; int32_t st58; uint8_t unk5C[0x10];
    int32_t h6C; uint8_t unk70[0x278 - 0x70]; M1Ext230 *ext278; } M1Act230;
extern float a50_frameSeconds;
int32_t aab_Effect494D0(int32_t snd, void *pos, int32_t z);
int32_t sub_00036750(M1Obj230 *o, int32_t pose);
void r2b_SetBit(int32_t bit);
void r3_SetStateD(M1Obj230 *obj, M1Act230 *act, int state);   /* regargs: obj=EBX act=ESI state=stack */

/* 0x0017A780: two-step timed state: start sound 0x195, pose 0 and bit 0x5C, then when the +0x18 timer runs out
   switch to state 1 and clear flags 0x18 (calls 0x17A2B0 with obj=EBX act=ESI). */
void m1_TimedState17A780(M1Obj230 *o, M1Act230 *a)
{
    M1Ext230 *e = a->ext278;
    e->t18 -= a50_frameSeconds;
    switch (a->st58) {
    case 0:
        e->flags0 = (e->flags0 & ~0x10u) | 8;
        a->flags4C &= ~0x200u;
        a->h6C = aab_Effect494D0(0x195, o->pos60, 1);
        e->pose24 = sub_00036750(o, 0);
        r2b_SetBit(0x5C);
        a->st58++;
        return;
    case 1:
        if (0.0f > e->t18) {
            r3_SetStateD(o, a, 1);
            e->flags0 &= ~0x18u;
        }
        return;
    }
}

typedef struct M1Rig230 { uint8_t unk00[0x30]; void *mdl30; } M1Rig230;
typedef struct M1RigS230 { uint8_t unk00[0x58]; int32_t st58; } M1RigS230;
int32_t sub_000833E0(void *m);
int32_t b4c_Enter1456E0(M1Rig230 *o, M1RigS230 *s, int32_t a, int32_t b);
void sub_0001D4E0(M1Rig230 *o);
void sub_00117580b(M1Rig230 *o, int32_t mode, M1RigS230 *s);   /* 0x117580 regargs: s=EDI */

/* 0x00118330: four-step sequence: wait for the clip, enter state 0x15 (nudge the model if it took), wait again,
   then hand over to 0x117580 mode 1 (calls 0x117580 with s=EDI). */
void m1_RigSeq118330(M1Rig230 *o, M1RigS230 *s)
{
    switch (s->st58) {
    case 0:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 1:
        if (b4c_Enter1456E0(o, s, 0x15, 0) == 1)
            sub_0001D4E0(o);
        s->st58++;
        return;
    case 2:
        if (!sub_000833E0(o->mdl30))
            return;
        s->st58++;
    case 3:
        sub_00117580b(o, 1, s);
        return;
    }
}

typedef struct M1RigE230 { uint8_t unk00[4]; uint8_t flags4; uint8_t unk05[0x43]; float f48; } M1RigE230;
typedef struct M1RigS2_230 { uint8_t unk00[0x278]; M1RigE230 *ext278; } M1RigS2_230;
int32_t sub_001457C0(M1Rig230 *o, float a, float b);
int32_t r2_PlayerInFrontA(M1RigS2_230 *s, M1Rig230 *o);   /* regargs: s=EAX */
void sub_00117580c(M1Rig230 *o, int32_t mode, M1RigS2_230 *s);   /* 0x117580 regargs: s=EDI */

/* 0x00118870: if not flagged 0x10 and the player is within 11 units in front, set f48 = 0.3 and go to mode 9;
   otherwise when the clip ends go to mode 0x23 (flag 0x10) or 1 (calls 0x1154D0 with s=EAX, 0x117580 with
   s=EDI). */
void m1_RigWatch118870(M1Rig230 *o, M1RigS2_230 *s)
{
    M1RigE230 *e = s->ext278;
    if (!(e->flags4 & 0x10) && sub_001457C0(o, 11.0f, 3.40282347e+38f) && r2_PlayerInFrontA(s, o)) {
        e->f48 = 0.3f;
        sub_00117580c(o, 9, s);
        return;
    }
    if (sub_000833E0(o->mdl30)) {
        if (e->flags4 & 0x10) {
            sub_00117580c(o, 0x23, s);
            return;
        }
        sub_00117580b((M1Rig230 *)o, 1, (M1RigS230 *)s);
    }
}
