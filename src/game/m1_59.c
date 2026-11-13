/* Area m1, file 59: message queue. Names inferred. */
#include <stdint.h>

typedef struct M1Msg150 { uint8_t unk000[4]; int32_t kind04; int32_t id08; uint8_t unk00C[0x150 - 0xC]; } M1Msg150;
extern int32_t m1_msgCount423F60;
extern int32_t m1_msgIds423F64[];
extern M1Msg150 *m1_msgs420F04;
extern void *m1_msgText2E4118[];
void sub_00022630(M1Msg150 *m, void *text);

/* 0x000A7570: queues message id (up to 29): copies its text (0x22630) into the next
 * record, records the id and sets kind 0xB. */
void m1_MsgQueue0A7570(int id)
{
    void *t;
    if (m1_msgCount423F60 > 0x1C)
        return;
    t = m1_msgText2E4118[id];
    if (t == 0)
        return;
    sub_00022630(&m1_msgs420F04[m1_msgCount423F60], t);
    m1_msgIds423F64[m1_msgCount423F60] = id;
    m1_msgs420F04[m1_msgCount423F60].kind04 = 0xB;
    m1_msgs420F04[m1_msgCount423F60].id08 = id;
    m1_msgCount423F60++;
}

typedef struct M1PoolDef { int32_t size00; int32_t align04; } M1PoolDef;
extern uint8_t *m1_poolBase3E27FC;
extern int32_t m1_poolTotal3E27F8;
extern int32_t m1_poolUsed3E26CC;
extern uint8_t *m1_pools3E26A8[9];
extern int32_t m1_poolAux3E26D0[9];
extern const M1PoolDef m1_poolDefs26BE90[9];
extern const char m1_poolFile26BED8[];
void sub_000471B0(uint8_t *mem, int size, int align, const char *file, int line);

/* 0x00053760: carves the 9 memory pools (sizes at 0x26BE90) out of the arena at 0x3E27FC
 * (0x471B0 each, source line 0x16A); spins when they exceed 0x3E27F8; stores the total. */
void m1_PoolsInit053760(void)
{
    uint8_t *base = m1_poolBase3E27FC;
    int used = 0;
    const M1PoolDef *d;
    int i;
    for (i = 0; i < 9; i++) {
        d = &m1_poolDefs26BE90[i];
        m1_pools3E26A8[i] = 0;
        if ((d->size00 + 31) & ~31) {
            m1_pools3E26A8[i] = base;
            sub_000471B0(base, d->size00, d->align04, m1_poolFile26BED8, 0x16A);
            base += d->size00;
            used += d->size00;
            if (used > m1_poolTotal3E27F8)
                for (;;) ;
        }
        m1_poolAux3E26D0[i] = 0;
    }
    m1_poolUsed3E26CC = used;
}

typedef struct M1TurnObj { uint8_t unk000[0x54]; float yaw54; uint8_t unk058[0x10C - 0x58]; float f10C; } M1TurnObj;
typedef struct M1TurnSt { uint8_t unk00[0xA4]; float fA4; } M1TurnSt;
float *sub_0001D0F0(void *o, int v);
void   sub_001AD940(float *m);
void   sub_001AD8E0(float *out, const float *m, float a);
void   sub_000F5D40(float *dst, const float *src);

/* 0x000EFA60: turns o around (yaw +0x54 -= pi), clears +0x10C and h +0xA4, and resets the
 * first three rows of o's frame matrix (0x1D0F0(o, 1)) to identity rotated by 0
 * (0x1AD940 / 0x1AD8E0). */
void m1_TurnAround0EFA60(M1TurnObj *o, M1TurnSt *h)
{
    float m[16];
    float *f;
    o->f10C = 0.0f;
    o->yaw54 -= 3.1415927f;
    h->fA4 = 0.0f;
    f = sub_0001D0F0(o, 1);
    sub_001AD940(m);
    sub_001AD8E0(m, m, 0.0f);
    sub_000F5D40(f, m);
    sub_000F5D40(f + 4, m + 4);
    sub_000F5D40(f + 8, m + 8);
}
