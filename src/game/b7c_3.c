/* Area b7c, group 3: enemy state handlers 0x0017D590-0x0017FB10. Names inferred. */
#include "b7c.h"

typedef struct B7CMode324 { uint8_t unk00[0x324]; int32_t mode; } B7CMode324;
B7CMode324 *sub_000E0770(void);
void  sub_0001EB80(void *o);
void *sub_000ED630(int a, int b, int c, int d, int e);
int   sub_00101360(void);
void  sub_001456E0(void *o, void *e, int a, int b);
extern void *b7c_owner3FDE68;           /* 0x003FDE68 */
extern void *b7c_enemy3FDE6C;           /* 0x003FDE6C */
extern int32_t b7c_stage3FE060;         /* 0x003FE060 */
typedef struct B7CSlot4 { uint8_t flags; uint8_t unk01[3]; } B7CSlot4;
extern B7CSlot4 b7c_slots3FE068[6];     /* 0x003FE068 */

typedef struct B7CWorkE { uint8_t unk00[0x10]; int32_t i10; int32_t i14; uint8_t unk18[8]; float f20;
                          uint8_t unk24[4]; int16_t s28; } B7CWorkE;
typedef struct B7CEnemyF { uint8_t unk00[0x50]; int32_t i50; uint8_t unk54[8]; float f5C; } B7CEnemyF;
typedef struct B7CAnim { uint8_t unk00[8]; int32_t phase; } B7CAnim;
typedef struct B7COwnerA { uint8_t unk00[0x30]; B7CAnim *anim; } B7COwnerA;

/* 0x0017D590: when the controller is in mode 1, put the stored enemy into state 1. */
void b7c_Wake17D590(void)
{
    if (sub_000E0770()->mode == 1)
        sub_00113040(b7c_owner3FDE68, b7c_enemy3FDE6C, 1);
}

/* 0x0017D8E0: detach: set owner flags 0x0D, clear flag 1, drop the work block, free. */
int b7c_Detach17D8E0(B7COwner *o, B7CEnemy *e)
{
    o->flags10 |= 0xD;
    o->flags0C &= ~1u;
    e->work = 0;
    sub_0001EB80(o);
    return 1;
}

/* 0x0017DB70: clear work timer +0x20 and halfword +0x28. */
void b7c_Clear17DB70(void *o, B7CEnemy *e)
{
    B7CWorkE *w = e->work;
    w->f20 = 0.0f;
    w->s28 = 0;
}

/* 0x0017E4B0: create two effect 0x25 instances in group 4. */
void b7c_Spawn17E4B0(void)
{
    int i;
    for (i = 0; i < 2; i++)
        sub_000ED630(4, 0x25, 0, 0, i);
}

/* 0x0017E6E0: in mode 1, on condition 0x22/0x23 go to state 2. */
int b7c_Cond17E6E0(void *o, B7CEnemyF *e, int32_t *cond)
{
    if (e->i50 == 1 && sub_00101360() && *cond >= 0x22 && *cond <= 0x23)
        sub_00113040(o, e, 2);
    return 0;
}

/* 0x0017EA70: work mode +0x10 = 2. */
void b7c_Mode2_17EA70(void *o, B7CEnemy *e) { ((B7CWorkE *)e->work)->i10 = 2; }

/* 0x0017EA90: go to state 1 once the timer passes 60. */
void b7c_Timeout17EA90(void *o, B7CEnemyF *e)
{
    if (e->f5C > 60.0f)
        sub_00113040(o, e, 1);
}

/* 0x0017ED10..0x0017ED50: forward to 0x001456E0 with a fixed kind. */
void b7c_Kind1_17ED10(void *o, void *e) { sub_001456E0(o, e, 1, 0); }
void b7c_Kind2_17ED30(void *o, void *e) { sub_001456E0(o, e, 2, 0); }
void b7c_Kind3_17ED50(void *o, void *e) { sub_001456E0(o, e, 3, 0); }

/* 0x0017EE00: in animation phase 0, go to state 2 when the animation ends. */
void b7c_AnimEnd17EE00(B7COwnerA *o, void *e)
{
    if (o->anim->phase == 0 && sub_000833E0(o->anim))
        sub_00113040(o, e, 2);
}

/* 0x0017EE30: switch to state 3. */
void b7c_Switch3_17EE30(void *o, void *e) { sub_00113040(o, e, 3); }

/* 0x0017EE50: in animation phase 2, go to state 4 when the animation ends. */
void b7c_AnimEnd17EE50(B7COwnerA *o, void *e)
{
    if (o->anim->phase == 2 && sub_000833E0(o->anim))
        sub_00113040(o, e, 4);
}

/* 0x0017EE80: switch to state 1. */
void b7c_Switch1_17EE80(void *o, void *e) { sub_00113040(o, e, 1); }

/* 0x0017F000: 1 if slot i (0..5) has bit 2 clear. */
int b7c_SlotFree17F000(int i)
{
    if (i >= 0 && i < 6)
        return (char)~b7c_slots3FE068[i].flags & 2 ? 1 : 0;
    return 0;
}

/* 0x0017F030: 1 if the stage number is 1..5. */
int b7c_StageValid17F030(void)
{
    return b7c_stage3FE060 >= 1 && b7c_stage3FE060 <= 5;
}

/* 0x0017FAF0: clear work +0x14. */
void b7c_Clear17FAF0(void *o, B7CEnemy *e) { ((B7CWorkE *)e->work)->i14 = 0; }
