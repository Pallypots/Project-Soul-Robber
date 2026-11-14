/* Area m1, file 148: object state helpers. Names inferred. */
#include <stdint.h>

typedef struct M1Anm148 { uint8_t unk00[4]; } M1Anm148;
typedef struct M1Obj148 { uint8_t unk00[0xC]; uint32_t fC; uint32_t f10; uint8_t unk14[0x1C]; M1Anm148 *anim30; uint8_t unk34[0x3C]; float pos70[4]; } M1Obj148;

typedef struct M1Hold148 { M1Obj148 *obj0; int32_t a4; float f8; int32_t iC; uint8_t unk10[4]; volatile int16_t w14; volatile int16_t w16; float f18, f1C, f20; } M1Hold148;
typedef struct M1Own148 { uint8_t unk00[0x278]; void *x278; } M1Own148;
extern M1Hold148 m1_recs3FDAF8[9];
void sub_00033B30(M1Obj148 *o);
void sub_0001EB80(M1Obj148 *o);

/* 0x179190: release a held object: clear its hold slot and hide it. */
int m1_HoldRelease179190(M1Obj148 *o, M1Own148 *own) {
    M1Hold148 *h; int i;
    if (!(o->fC & 1)) return 0;
    for (i = 0; i < 9; i++)
        if (m1_recs3FDAF8[i].obj0 == o) break;
    if (i >= 9) return 0;
    h = &m1_recs3FDAF8[i];
    sub_00033B30(o);
    h->obj0 = 0; h->a4 = 0; h->f8 = 0.0f; h->iC = 0; h->w14 = 0; h->w16 = 0;
    h->f18 = 0.0f; h->f1C = 0.0f; h->f20 = 0.0f;
    own->x278 = 0;
    sub_0001EB80(o);
    o->fC &= ~1u; o->f10 |= 0xD;
    return 1;
}

typedef struct M1Task148 { int32_t on; int32_t id; uint8_t rest[0xA0 - 8]; } M1Task148;
extern M1Task148 m1_tasks3FE488[8];

/* 0x185420: count active tasks with this id. */
int m1_TaskCount185420(int id) {
    int n = 0, i;
    for (i = 0; i < 8; i++)
        if (m1_tasks3FE488[i].on != 0 && m1_tasks3FE488[i].id == id) n++;
    return n;
}


