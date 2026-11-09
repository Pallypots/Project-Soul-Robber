/* Area b7c, group 4: boss part tables 0x00180930-0x00182300. Names inferred. */
#include "b7c.h"

typedef struct B7CMode324b { uint8_t unk00[0x324]; int32_t mode; } B7CMode324b;
B7CMode324b *sub_000E0770(void);
void  sub_00182770(int st);


/* id-keyed record at 0x003FE2D8 (0x24 bytes) */
typedef struct B7CIdRec { void *owner; void *x4; void *enemy; int32_t id; uint8_t unk10[0x14]; } B7CIdRec;
extern B7CIdRec b7c_idRecs3FE2D8[4];    /* 0x003FE2D8 */

typedef struct B7CWorkH { uint8_t unk00[0x10]; float f10; int32_t i14; } B7CWorkH;

/* 0x001812C0: play animation 2, zero work timer, set work flag +0x14. */
void b7c_Anim2_1812C0(B7COwner *o, B7CEnemy *e)
{
    B7CWorkH *w = e->work;
    sub_000832D0(o->anim30, 2);
    w->f10 = 0.0f;
    w->i14 = 1;
}

/* 0x00181BE0: field +4 of the record with the given id (hangs if absent). */
void *b7c_IdX4_181BE0(int id)
{
    int i;
    for (i = 0; i < 4; i++)
        if (b7c_idRecs3FE2D8[i].id == id)
            break;
    if (i >= 4)
        for (;;) ;
    return b7c_idRecs3FE2D8[i].x4;
}

/* 0x00181C20: owner of the record with the given id (hangs if absent). */
void *b7c_IdOwner181C20(int id)
{
    int i;
    for (i = 0; i < 4; i++)
        if (b7c_idRecs3FE2D8[i].id == id)
            break;
    if (i >= 4)
        for (;;) ;
    return b7c_idRecs3FE2D8[i].owner;
}

/* 0x00181C60: switch the record with the given id to a state (hangs if absent). */
void b7c_IdSwitch181C60(int id, int st)
{
    int i = 0;
    B7CIdRec *r;
    for (r = b7c_idRecs3FE2D8; r < b7c_idRecs3FE2D8 + 4; r++, i++)
        if (r->id == id)
            break;
    if (i >= 4)
        for (;;) ;
    sub_00113040(r->owner, r->enemy, st);
}

/* 0x00181D20: in controller mode 1, switch the boss to state 3. */
void b7c_Boss3_181D20(void)
{
    if (sub_000E0770()->mode == 1)
        sub_00182770(3);
}

typedef struct B7CHealth { uint8_t unk00[0x270]; float maxHp; float hp; } B7CHealth;
typedef struct B7CWorkI { uint8_t unk00[4]; B7COwner *h4; uint8_t unk08[8]; int16_t s10; } B7CWorkI;
typedef struct B7CFlag4C { uint8_t unk00[0x4C]; uint32_t flags; } B7CFlag4C;

/* 0x00182180: refill the linked object's health to its maximum. */
void b7c_Refill182180(void *o, B7CEnemy *e)
{
    B7CHealth *c = sub_0001D960(((B7CWorkI *)e->work)->h4, 6);
    c->hp = c->maxHp;
}

/* 0x001822D0: reset the linked object: flags 0x0C, clear component bit 24. */
void b7c_Link1822D0(void *o, B7CEnemy *e)
{
    B7CWorkI *w = e->work;
    B7CFlag4C *c;
    w->s10 = 0;
    w->h4->flags10 |= 0xC;
    c = sub_0001D960(w->h4, 6);
    if (c)
        c->flags &= ~0x01000000u;
}
