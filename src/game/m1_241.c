/* Area m1, file 241: effect slot spawn (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1Slot241 { uint32_t flags0; int32_t id4; uint8_t unk08[0x48]; uint8_t v50[0x10]; uint8_t v60[0x10];
    uint8_t v70[0x10]; uint8_t v80[0x10]; uint8_t unk90[0x260 - 0x90]; } M1Slot241;
typedef struct M1Rec241 { uint8_t unk00[0x150]; } M1Rec241;
extern int32_t m1_handles423FEC[16];
extern M1Rec241 *m1_idA3ED52C;
extern void *m1_lut2E2958[];
extern int32_t m1_keyA423FE4;
extern M1Slot241 aa0_slots[32];
void m1_SetupA5730(int32_t id);
void sub_000A3810(M1Slot241 *e);   /* regargs: e=ESI */
void sub_000F5D40(void *dst, const void *src);

/* 0x000A57C0: spawn effect id (<= 253) at pos/rot in the first free of 32 slots, loading it first through 0xA5730 in
   mode 12 when it is not resident; returns the slot index or -1 (calls 0xA3810 with e=ESI). */
int m1_FxSpawn0A57C0(int32_t id, const float *pos, const float *rot)
{
    int i;
    M1Slot241 *e;
    if (id > 0xFD)
        return -1;
    for (i = 0; i < 16; i++)
        if (*(volatile int32_t *)&m1_handles423FEC[i] == id)
            break;
    if (i >= 16 || !&m1_idA3ED52C[i]) {
        if (!m1_lut2E2958[id])
            return -1;
        if (m1_keyA423FE4 != 12)
            return -1;
        m1_SetupA5730(id);
    }
    {
        M1Slot241 *q;
        for (i = 0, q = aa0_slots; (intptr_t)q < (intptr_t)(aa0_slots + 32); q++, i++)
            if (!(q->flags0 & 0x80000001))
                goto found;
        return -1;
    }
found:
    if (*(volatile int *)&i < 0)
        return -1;
    e = &aa0_slots[i];
    sub_000A3810(e);
    e->id4 = id;
    e->flags0 |= 0x80000000;
    sub_000F5D40(e->v70, pos);
    sub_000F5D40(e->v50, pos);
    sub_000F5D40(e->v80, rot);
    sub_000F5D40(e->v60, rot);
    return i;
}

typedef struct M1BE241 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x2C]; int32_t n34; } M1BE241;
typedef struct M1BS241 { uint8_t unk00[0x20]; uint8_t flags20; uint8_t unk21[0x2B]; uint32_t flags4C; uint8_t unk50[8];
    int32_t st58; uint8_t unk5C[0x18]; float t74; uint8_t unk78[0x200]; M1BE241 *ext278; } M1BS241;
typedef struct M1BO241 { uint8_t unk00[0x30]; void *mdl30; } M1BO241;
typedef int (*M1BFn241)(M1BO241 *o, M1BS241 *s, const void *t);
extern M1BFn241 b3b_checkFns31D0B8[];
extern const uint8_t b3b_tbl2797C8[];
extern float a50_frameUnits, a50_frameSeconds;
int32_t sub_000833E0(void *m);
int r3b_Dispatch140040(int idx, M1BS241 *b, M1BO241 *a);   /* regargs: idx=EAX b=EDX a=stack */
int r3b_TryCharge13D8B0(M1BS241 *act, M1BO241 *obj);        /* regargs: act=EAX obj=ECX */
void sub_00113040(M1BO241 *o, M1BS241 *s, int32_t mode);

/* 0x001419E0: step 0 advances once the charge starts; step 1 on clip end picks mode 10 (check passes, or no target ->
   flag 8), 0x27 after a successful dispatch, or 12 with a 60-frame (flag 0x10), zero or 90-frame timer, then hands over
   to 0x113040 (calls 0x13D8B0 with act=EAX obj=ECX, 0x140040 with idx=EAX b=EDX). */
void m1_Next1419E0(M1BO241 *o, M1BS241 *s)
{
    M1BE241 *e;
    int m;
    float t;
    switch (s->st58) {
    case 0:
        if (r3b_TryCharge13D8B0(s, o))
            s->st58++;
        return;
    case 1:
        if (!sub_000833E0(o->mdl30))
            return;
        e = s->ext278;
        if (b3b_checkFns31D0B8[0](o, s, b3b_tbl2797C8)) {
            m = 10;
        } else if (!e->n34) {
            e->flags4 |= 8;
            m = 10;
        } else {
            if (e->flags4 & 0x10) {
                t = 60.0f / a50_frameUnits * a50_frameSeconds;
            } else if (s->flags20 & 1) {
                if (r3b_Dispatch140040(1, s, o)) {
                    m = 0x27;
                    goto call;
                }
                t = 0.0f;
            } else {
                t = 90.0f / a50_frameUnits * a50_frameSeconds;
            }
            m = 12;
            s->t74 = t;
        }
call:
        s->flags4C |= 0x10;
        sub_00113040(o, s, *(volatile int *)&m);
        return;
    }
}
