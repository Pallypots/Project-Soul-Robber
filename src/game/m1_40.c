/* Area m1, file 40: Jack per-frame item/target update. Names inferred. */
#include <stdint.h>

typedef struct M1JackT {
    uint8_t  unk000[0x150];
    uint32_t flags150;         /* +0x150, 0x10000000 = busy */
    uint8_t  unk154[0x318 - 0x154];
    int32_t  count318;         /* +0x318 */
    uint8_t  unk31C[0x328 - 0x31C];
    float    dist328[0x20];    /* +0x328 */
    int32_t  kind3A8[0x20];    /* +0x3A8 */
    void    *a428[0x20];       /* +0x428 target object */
    int32_t  a4A8[0x20];       /* +0x4A8 */
    int32_t  order528[0x20];   /* +0x528 */
    uint8_t  b5A8;             /* +0x5A8 bit 0: add an entry this frame */
    uint8_t  unk5A9[0xEFC - 0x5A9];
    void    *target0EFC;       /* +0xEFC current target */
    uint8_t  unkF00[0xFD8 - 0xF00];
    uint8_t *node0FD8;         /* +0xFD8 Jack's model node (+0x60 position) */
} M1JackT;
void  sub_000CB340(M1JackT *p);
void *m1_FindFirstEDB10(int k);
void *sub_000EDB90(void);
void  sub_000CB390(M1JackT *p, void *it);
void  m1_ApplyActiveCC030(M1JackT *p);
void  sub_000CB490(M1JackT *p);
void  sub_000CB540(M1JackT *p);
void  sub_000CB640(M1JackT *p);
void  sub_0003AF70(void);
void  sub_000CC180(M1JackT *p);

/* 0x000CC2A0: per-frame update: unless busy, offers every filter-0 item to 0xCB390;
 * applies active entries; unless busy, appends an entry of kind 1 when requested;
 * then the remaining per-frame steps. */
void m1_JackFrameCC2A0(M1JackT *p)
{
    void *it;
    int i;
    sub_000CB340(p);
    if (!(p->flags150 & 0x10000000)) {
        for (it = m1_FindFirstEDB10(0); it != 0; it = sub_000EDB90())
            sub_000CB390(p, it);
    }
    m1_ApplyActiveCC030(p);
    if (!(p->flags150 & 0x10000000) && (p->b5A8 & 1)) {
        i = p->count318;
        p->order528[i] = i;
        p->a428[i] = 0;
        p->kind3A8[i] = 1;
        p->a4A8[i] = 0;
        p->count318++;
    }
    sub_000CB490(p);
    sub_000CB540(p);
    sub_000CB640(p);
    sub_0003AF70();
    sub_000CC180(p);
}

typedef struct M1Tgt {
    uint8_t  unk00[4];
    int32_t  kind04;           /* +0x04 */
    uint8_t  unk08[4];
    uint32_t flags0C;          /* +0x0C */
    uint32_t flags10;          /* +0x10 */
    uint8_t  unk14[0x60 - 0x14];
    float    pos60[4];         /* +0x60 */
} M1Tgt;
extern int32_t m1_range2E72A0;   /* 0x002E72A0 */
void  sub_001AD9F0(float *d, const float *a, const void *b);   /* d = a - b */
float sub_00082D70(float *v);                                  /* length */

/* 0x000CB390: adds target t to Jack's list when it is active, not excluded and
 * within range (30 for kind 6, else the global range). */
void m1_GatherTargetCB390(M1JackT *p, M1Tgt *t)
{
    float v[4];
    float range, d;
    int i;
    v[0] = 0.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 1.0f;
    if (t == 0 || t == p->target0EFC)
        return;
    range = (t->kind04 == 6) ? 30.0f : (float)m1_range2E72A0;
    if (!(t->flags0C & 1) || (t->flags0C & 0x10000) || (t->flags10 & 9))
        return;
    i = p->count318;
    sub_001AD9F0(v, t->pos60, p->node0FD8 + 0x60);
    d = sub_00082D70(v);
    if (!(range >= d))
        return;
    p->dist328[i] = d;
    p->kind3A8[i] = t->kind04;
    p->a428[i] = t;
    p->order528[i] = i;
    p->a4A8[i] = 0;
    p->count318++;
}
