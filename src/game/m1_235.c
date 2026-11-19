/* Area m1, file 235: player state helpers (register-argument callers per docs/verification.md). Names inferred. */
#include <stdint.h>

typedef struct M1P235 { uint8_t unk00[0x70]; int32_t kind70; uint8_t unk74[0x7C]; float vF0[4]; int32_t n100, n104;
    float f108; uint8_t unk10C[4]; int32_t q110[2]; } M1P235;
extern float a50_frameSeconds;
void m1_PlPose0F0B10(void *o, int kind);   /* regargs: o=EDI */
void r2c_SetSoundD8(int32_t snd, int32_t k);

/* 0x000F2300: stop the player's motion (velocity 0 per frame), clear +0x110, set effect 3 unless kind is 0x1B-0x1D
   or 0x1F, play sound 0x1B5 and reset +0x100.. (hangs on a null record; calls 0xF0B10 with o=EDI). */
void m1_PlStop0F2300(void *o, M1P235 *p)
{
    int k;
    if (!p)
        for (;;) ;
    p->vF0[0] = a50_frameSeconds * 0.0f;
    p->vF0[1] = a50_frameSeconds * 0.0f;
    p->vF0[2] = a50_frameSeconds * 0.0f;
    p->vF0[3] = a50_frameSeconds * 0.0f;
    p->q110[0] = 0;
    p->q110[1] = 0;
    k = p->kind70;
    if (k < 0x1B || (k > 0x1D && k != 0x1F))
        m1_PlPose0F0B10(o, 3);
    r2c_SetSoundD8(0x1B5, 1);
    p->n100 = 1;
    p->n104 = 0;
    p->f108 = 0.0f;
}

typedef struct M1Clip235 { uint8_t unk00[8]; int32_t len8; uint16_t wC, wE; uint8_t data10[1]; } M1Clip235;
typedef struct M1Slot235 { int32_t id, len, fmt; uint8_t *data; uint8_t unk10[4]; } M1Slot235;
typedef struct M1Bank235 { uint8_t unk00[0xC]; M1Slot235 slots0C[8];
    M1Clip235 *cAC, *cB0, *cB4, *cB8; M1Clip235 *grid[8][16]; M1Clip235 *c2BC, *c2C0, *c2C4;
    uint8_t unk2C8[0x50]; int32_t col318; } M1Bank235;

/* 0x000E0A80: bind clip source `src` (0-3, 4 = grid[row][col], 5-7) to slot `slot` (0-7, else hang); copies its id,
   length, format and data pointer, or clears the slot and returns 1 when there is none. */
int m1_BindClip0E0A80(M1Bank235 *b, int slot, int src, int row, int col)
{
    M1Clip235 *c = 0;
    M1Slot235 *s;
    if (slot < 0 || slot >= 8)
        for (;;) ;
    switch (src) {
    case 0: c = b->cAC; break;
    case 1: c = b->cB0; break;
    case 2: c = b->cB4; break;
    case 3: c = b->cB8; break;
    case 4:
        b->col318 = col;
        if (row >= 0 && col >= 0)
            c = b->grid[row][col];
        else
            c = 0;
        break;
    case 5: c = b->c2BC; break;
    case 6: c = b->c2C0; break;
    case 7: c = b->c2C4; break;
    }
    s = &b->slots0C[slot];
    if (c) {
        s->id = c->wE;
        s->len = c->len8;
        s->data = c->data10;
        s->fmt = c->wC;
        return 0;
    }
    s->id = 0;
    s->len = 0;
    s->fmt = 0;
    s->data = 0;
    return 1;
}

typedef struct M1BO235 { uint8_t unk00[0x54]; float r54; uint8_t unk58[8]; uint8_t pos60[0x10]; } M1BO235;
typedef struct M1BS235 { uint8_t unk00[0x44]; int32_t ids44[2]; uint8_t unk4C[0x20]; int32_t kind6C; } M1BS235;
extern M1BO235 *g_playerObj;
float sub_00113200(M1BO235 *o, const void *target);
void *sub_000ED630(int32_t a, int32_t kind, const void *pos, const float *rot, int32_t mode);
void sub_000EDF30(void *h, int32_t i, int32_t id);
void sub_000EDF90(void *h);

/* 0x00170570: spawn the break-apart effect for s's kind facing the player (variant by mode), give it s's two ids and
   start it (regargs: mode=EAX o=ECX, s on stack). */
void m1_BreakFx170570(int32_t mode, M1BO235 *o, M1BS235 *s)
{
    float rot[4];
    void *h;
    int k, i;
    rot[0] = 0.0f;
    rot[1] = 0.0f;
    rot[2] = 0.0f;
    rot[3] = 1.0f;
    rot[1] = sub_00113200(o, g_playerObj->pos60) + o->r54;
    k = s->kind6C;
    switch (k) {
    case 0: case 14:
        mode = mode ? 4 : 5;
        break;
    case 1:
        mode = mode ? 2 : 3;
        break;
    case 5: case 15:
        mode = (mode != 0) + 5;
        break;
    default:
        mode = 0;
        break;
    }
    h = sub_000ED630(2, k, o->pos60, rot, mode);
    if (!h)
        return;
    for (i = 0; i < 2; i++)
        sub_000EDF30(h, i, s->ids44[i]);
    sub_000EDF90(h);
}

typedef struct M1CS235 { uint8_t unk00[0x4C]; uint32_t flags4C; } M1CS235;
int  r3_CheckConds186160(int table, void *a, void *b);   /* regargs: table=EAX a=EBX b=EDI */
void sub_00186470(void *obj, void *act, int state);       /* regargs: obj=EBX act=EDI state=stack */

/* 0x001869A0: pick the next state: 5 if flag 0x100, 10 if any of tables 0/13/3/4/5 holds, else 9/7/6 for tables
   12/7/8 (calls 0x186160 with table=EAX a=EBX b=EDI, 0x186470 with obj=EBX act=EDI). */
void m1_PickState1869A0(void *o, M1CS235 *s)
{
    if (s->flags4C & 0x100) {
        sub_00186470(o, s, 5);
        return;
    }
    if (r3_CheckConds186160(0, o, s) || r3_CheckConds186160(13, o, s) || r3_CheckConds186160(3, o, s)
        || r3_CheckConds186160(4, o, s) || r3_CheckConds186160(5, o, s)) {
        sub_00186470(o, s, 10);
        return;
    }
    if (r3_CheckConds186160(12, o, s)) {
        sub_00186470(o, s, 9);
        return;
    }
    if (r3_CheckConds186160(7, o, s)) {
        sub_00186470(o, s, 7);
        return;
    }
    if (r3_CheckConds186160(8, o, s))
        sub_00186470(o, s, 6);
}

/* 0x00186E20: as 0x1869A0 but the last test is table 9 -> state 2. */
void m1_PickState186E20(void *o, M1CS235 *s)
{
    if (s->flags4C & 0x100) {
        sub_00186470(o, s, 5);
        return;
    }
    if (r3_CheckConds186160(0, o, s) || r3_CheckConds186160(13, o, s) || r3_CheckConds186160(3, o, s)
        || r3_CheckConds186160(4, o, s) || r3_CheckConds186160(5, o, s)) {
        sub_00186470(o, s, 10);
        return;
    }
    if (r3_CheckConds186160(12, o, s)) {
        sub_00186470(o, s, 9);
        return;
    }
    if (r3_CheckConds186160(7, o, s)) {
        sub_00186470(o, s, 7);
        return;
    }
    if (r3_CheckConds186160(9, o, s))
        sub_00186470(o, s, 2);
}
