/* Area m1, file 292: placement spawning. Names inferred. */
#include <stdint.h>

typedef struct M1Pl292 { uint8_t unk00[0x60]; float pos60[4]; } M1Pl292;
typedef struct M1Pe292 { int8_t kind0, sub1; uint8_t unk02[6]; int8_t arg8, opt9, optA; uint8_t unkB; uint8_t faceC;
    uint8_t unkD[3]; float x10, y14, z18, yaw1C; } M1Pe292;
extern M1Pl292 *g_playerObj;
M1Pe292 *sub_000854B0(void *list);                           /* regargs: list=EDI; first entry */
M1Pe292 *sub_00085520(void);                                 /* next entry */
int32_t sub_00086250(int32_t kind, int32_t sub);
void sub_001AD9F0(float *d, const float *a, const float *b);   /* d = a - b */
float sub_001B27C0(const float *a, const float *b);           /* angle from a to b */
void *m1_SpawnKindED630(int32_t kind, int32_t a, float *pos, float *rot, int32_t b);
void sub_000EDF30(void *e, int32_t which, int32_t v);
void sub_000EDF90(void *e);

/* 0x00085590: spawn every enabled entry of placement list l at its position, facing its stored yaw or (when
   flagged) the player; set its two options and start it. Returns how many were spawned. */
int32_t m1_SpawnPlacements85590(void *l)
{
    float fwd[4], pos[4], rot[4], d[4];
    M1Pe292 *e;
    void *o;
    int32_t n = 0;
    fwd[0] = 0.0f;
    fwd[1] = 0.0f;
    fwd[2] = -1.0f;
    fwd[3] = 1.0f;
    for (e = sub_000854B0(l); e; e = sub_00085520()) {
        if (!sub_00086250(e->kind0, e->sub1)) continue;
        pos[0] = e->x10;
        pos[1] = e->y14;
        pos[2] = e->z18;
        pos[3] = 1.0f;
        rot[0] = 0.0f;
        rot[2] = 0.0f;
        rot[3] = 0.0f;
        if (e->faceC == 0) {
            rot[1] = e->yaw1C;
        } else {
            sub_001AD9F0(d, g_playerObj->pos60, pos);
            rot[1] = sub_001B27C0(fwd, d);
        }
        o = m1_SpawnKindED630(e->kind0, e->sub1, pos, rot, e->arg8);
        if (!o) continue;
        sub_000EDF30(o, 0, e->opt9);
        sub_000EDF30(o, 1, e->optA);
        sub_000EDF90(o);
        n++;
    }
    return n;
}

typedef struct M1Ss292 { uint8_t unk00[4]; uint32_t flags4; uint8_t unk08[0x48]; int32_t max50; int32_t left54; int32_t f58; } M1Ss292;
typedef struct M1Sa292 { uint8_t unk00[0x270]; float hpMax270, hp274; M1Ss292 *s278; } M1Sa292;
void *sub_000EDC20(int32_t a, int32_t b);                    /* filtered entity walk */
int32_t m1_PickPoint1176A0(M1Sa292 *a, float *out);           /* regargs: a=EAX out=ECX */
float sub_00145B60(const float *v);                           /* heading of v */

/* 0x001199C0: summon a minion for a: only while fewer than max50 are out. Pick the kind by a's stage (0xF before
   both points are used, then 0xD above half health or 0xE below), pick a clear point, spawn it there facing away
   from the player (hangs if it cannot spawn), and count it; after the last one the wait resets to 19 - out. */
int32_t m1_Summon1199C0(void *o, M1Sa292 *a)
{
    M1Ss292 *s = a->s278;
    int32_t n = 0, kind, flag;
    float p[4], r[4], d[4];
    void *e;
    (void)o;
    if (sub_000EDC20(2, 1)) {
        do {
            n++;
        } while (sub_000EDC20(-1, -1));
    }
    if (n >= s->max50) return 0;
    if ((*(volatile uint32_t *)&s->flags4 & 0x10000) && (*(volatile uint32_t *)&s->flags4 & 0x20000)) {
        if (a->hp274 / a->hpMax270 > 0.5f) {
            kind = 0xD;
            flag = 1;
        } else {
            kind = 0xE;
            flag = 0;
        }
    } else {
        kind = 0xF;
        flag = 1;
    }
    if (!m1_PickPoint1176A0(a, p)) return 0;
    r[0] = 0.0f;
    r[1] = 0.0f;
    r[2] = 0.0f;
    r[3] = 1.0f;
    sub_001AD9F0(d, p, g_playerObj->pos60);
    r[1] = sub_00145B60(d);
    e = m1_SpawnKindED630(2, 1, p, r, kind);
    if (!e) for (;;) ;
    s->left54--;
    sub_000EDF30(e, 0, flag);
    sub_000EDF30(e, 1, 1);
    sub_000EDF90(e);
    if (s->left54 <= 0) {
        s->left54 = 0x13 - n;
        s->f58 = 0;
    }
    return 1;
}
