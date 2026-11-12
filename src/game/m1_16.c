/* Area m1, file 16: table sweeps. Names inferred; array start is a Hypothesis
 * (only fields +0x00, +0x0C and +0x54 of each 0x8C entry are touched here). */
#include <stdint.h>

typedef struct M1Ent8C {
    void    *obj00;            /* +0x00 */
    uint8_t  unk04[8];
    int32_t  state0C;          /* +0x0C */
    uint8_t  unk10[0x54 - 0x10];
    int16_t  live54;           /* +0x54 */
    uint8_t  unk56[0x8C - 0x56];
} M1Ent8C;
extern M1Ent8C m1_ents400E54[18];   /* 0x00400E54 */
int r4i_ObjDestroy(void *o);

/* 0x00194EB0: destroys every live entry in state 3 or 4; 1 if any was destroyed. */
int m1_DestroyDone194EB0(void)
{
    int any = 0;
    int i;
    for (i = 0; i < 18; i++) {
        if ((m1_ents400E54[i].state0C == 3 || m1_ents400E54[i].state0C == 4) &&
            m1_ents400E54[i].obj00 != 0 && m1_ents400E54[i].live54 != 0) {
            r4i_ObjDestroy(m1_ents400E54[i].obj00);
            any = 1;
        }
    }
    return any != 0;
}

typedef struct M1Kind50 {
    uint8_t unk00[0x50];
    int32_t kind50;            /* +0x50 */
} M1Kind50;
typedef struct M1Pair44 {
    void     *owner00;         /* +0x00 */
    M1Kind50 *obj04;           /* +0x04 */
    uint8_t   unk08[0x44 - 8];
} M1Pair44;
extern M1Pair44 m1_pairs3FE1C8[4];  /* 0x003FE1C8 */
void sub_00113040(void *owner, void *obj, int what);

/* 0x00180970: sends event 4 to every pair whose object is in state 2 or 3. */
void m1_NotifyPairs180970(void)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (m1_pairs3FE1C8[i].obj04->kind50 == 2 || m1_pairs3FE1C8[i].obj04->kind50 == 3)
            sub_00113040(m1_pairs3FE1C8[i].owner00, m1_pairs3FE1C8[i].obj04, 4);
    }
}

typedef struct M1Mode324 {
    uint8_t unk000[0x324];
    int32_t mode324;           /* +0x324 */
} M1Mode324;
M1Mode324 *sub_000E0770(void);

/* 0x00180930: in mode 1, sends event 1 to every pair whose object is in state 0. */
void m1_WakePairs180930(void)
{
    int i;
    if (sub_000E0770()->mode324 != 1)
        return;
    for (i = 0; i < 4; i++) {
        if (m1_pairs3FE1C8[i].obj04->kind50 == 0)
            sub_00113040(m1_pairs3FE1C8[i].owner00, m1_pairs3FE1C8[i].obj04, 1);
    }
}


typedef struct M1Slot10 {
    uint8_t unk00[8];
    int32_t used08;            /* +0x08 */
    void   *data0C;            /* +0x0C */
} M1Slot10;
extern M1Slot10 m1_slots3F5D30[8];  /* 0x003F5D30 */
extern uint8_t  m1_slotList3F5DB0[]; /* 0x003F5DB0 list head */
void sub_0003D880(void *list, void *node);

/* 0x000ED9A0: takes the first free slot (hangs if none), stores data and links it in. */
void m1_TakeSlotED9A0(void *data)
{
    int i;
    M1Slot10 *s;
    for (i = 0; i < 8; i++) {
        s = &m1_slots3F5D30[i];
        if (s->used08 == 0 && s->data0C == 0)
            goto found;
    }
    for (;;) ;
found:
    s->data0C = data;
    sub_0003D880(m1_slotList3F5DB0, s);
}

typedef struct M1Ent260 {
    int8_t  flags00;           /* +0x000 bit 7 = active */
    uint8_t unk001[0x120 - 1];
    int32_t id120;             /* +0x120 */
    uint8_t unk124[0x260 - 0x124];
} M1Ent260;
extern M1Ent260 m1_ents4242C0[32];  /* 0x004242C0 */
typedef struct M1Flags150 {
    uint8_t  unk000[0x150];
    uint32_t flags150;         /* +0x150 */
} M1Flags150;
void sub_000CB390(M1Flags150 *o, int id);

/* 0x000CC030: unless flag 0x10000000 is set, applies every active entry's id to o. */
void m1_ApplyActiveCC030(M1Flags150 *o)
{
    int i;
    if (o->flags150 & 0x10000000)
        return;
    for (i = 0; i < 32; i++) {
        if (m1_ents4242C0[i].flags00 < 0)
            sub_000CB390(o, m1_ents4242C0[i].id120);
    }
}


typedef struct M1Hold34 {
    void     *obj00;           /* +0x00 */
    int32_t   f04;             /* +0x04 */
    M1Kind50 *watch08;         /* +0x08 */
    int32_t   f0C;             /* +0x0C */
    uint8_t   unk10[0x34 - 0x10];
} M1Hold34;
extern M1Hold34 m1_holds3FE3B0[4];  /* 0x003FE3B0 */
typedef struct M1Snd138 {
    uint8_t unk000[0x138];
    int32_t snd138;            /* +0x138, -1 = none */
} M1Snd138;
M1Snd138 *sub_00100110(void);
void sub_00048250(int h);

/* 0x00185370: destroys held objects whose watched object is in state 1, then
 * stops the player's looping sound. */
void m1_DropHolds185370(void)
{
    int i;
    M1Snd138 *p;
    for (i = 0; i < 4; i++) {
        if (m1_holds3FE3B0[i].obj00 != 0 && m1_holds3FE3B0[i].watch08->kind50 == 1) {
            r4i_ObjDestroy(m1_holds3FE3B0[i].obj00);
            m1_holds3FE3B0[i].obj00 = 0;
            m1_holds3FE3B0[i].f04 = 0;
            m1_holds3FE3B0[i].watch08 = 0;
            m1_holds3FE3B0[i].f0C = 0;
        }
    }
    p = sub_00100110();
    if (p->snd138 != -1) {
        sub_00048250(p->snd138);
        p->snd138 = -1;
    }
}

